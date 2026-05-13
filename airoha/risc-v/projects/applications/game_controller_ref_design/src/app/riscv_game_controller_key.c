/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "syslog.h"
#include "riscv_ccni.h"
#include "riscv_game_controller_key.h"
#include "riscv_peripheral_sampling.h"
#include "pka_share.h"
#include "pka.h"
#include "hal_gpio_internal.h"
#include "hal_eint_internal.h"
#include "hal_gpt.h"
#include "hid_common.h"
#include "riscv_hid_express_key_queue_game_controller.h"

/* Private define ------------------------------------------------------------*/
#define COMBO_KEY_NONE                          0xFF
#define PAIRING_COMBO_HOLD                         0

#define GPIO_FIRST_SECTION_MAX                  32
#define GPIO_SECOND_SECTION_MAX                 64
#define GPIO_THIRD_SECTION_MAX                  96
#define GAME_CONTROLLER_KEY_MAX                 32

/* Private typedef -----------------------------------------------------------*/
typedef struct {
    T_AIR_COMBO_KEY_S *combo_key_list;
    uint32_t combo_key_list_size;
    uint32_t hold_timeout;
    uint32_t app_state;
}T_COMBO_KEY_CFG_S;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
log_create_module(riscv_key, PRINT_LEVEL_INFO);

static uint32_t start_gpt_free_count = 0;
static T_COMBO_KEY_CFG_S combo_cfg;

static uint32_t rv_key_num;
uint8_t rv_key_ids[GAME_CONTROLLER_KEY_MAX] = {0};

static uint32_t game_controller_32key = 0;
static uint32_t game_controller_32key_printed = 0;
static uint32_t combo_key_result = COMBO_KEY_NONE;
static uint32_t new_keys_status;
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void riscv_game_controller_key_polling_io_expander(uint32_t idx, uint32_t all_gpio_status_expand)
{
    if (rv_key_ids[idx] >= 0x80 && rv_key_ids[idx] != 0xFF){
        if ( all_gpio_status_expand & (1 << (rv_key_ids[idx]-0x80))){
            game_controller_32key |= (1 << (idx));
        }
    }
}

uint32_t riscv_game_controller_key_polling_all_key_status(void)
{
    uint32_t idx;
    uint32_t key_ids;

    game_controller_32key = 0;
    gpio_data_in_mask_t gpio_data_in_mask_temp;
    /* pre-processing expand button */
    uint32_t all_gpio_status_expand = hid_common->hid.expand_io.status;

    for (idx = 17 ; idx < rv_key_num; idx++ )
    {
        riscv_game_controller_key_polling_io_expander(idx, all_gpio_status_expand);
    }
    /* LT mode / RT mode */
    for (idx = 6; idx < 8; idx++ )
    {
        riscv_game_controller_key_polling_io_expander(idx, all_gpio_status_expand);
    }
    DBG_PING_L(DBG_SIGNAL_SPI_CB);

    /* process critical key */
    hal_eint_get_debounce_out_value_by_mask(&gpio_data_in_mask_temp.register0, &gpio_data_in_mask_temp.register1);
    // gpio : 0  is pressed , 1 is released
    // key : 1  is pressed , 0 is released
    uint32_t all_gpio_status_1 = ~gpio_data_in_mask_temp.register0;
    uint32_t all_gpio_status_2 = ~gpio_data_in_mask_temp.register1;
    for (idx = 0 ; idx < 17; idx++ )
    {
        key_ids = rv_key_ids[idx];
        if (key_ids < GPIO_FIRST_SECTION_MAX ){
            if ( all_gpio_status_1 & (1 << (key_ids))){
                game_controller_32key |= (1 << (idx));
            }
        }
        else {
            if ( all_gpio_status_2 & (1 << (key_ids-GPIO_FIRST_SECTION_MAX))){
                game_controller_32key |= (1 << (idx));
            }
        }   
    }
    return game_controller_32key;
}

uint32_t riscv_game_controller_key_combo_key_check(void)
{
    uint32_t ret = COMBO_KEY_NONE;
    uint32_t combo_key_1, combo_key_2, combo_key_3;
    uint32_t combo_idx;
    gpio_data_in_mask_t gpio_data_in_mask_temp;

    hal_eint_get_debounce_out_value_by_mask(&gpio_data_in_mask_temp.register0, &gpio_data_in_mask_temp.register1);

    // gpio: 0  is pressed , 1 is released
    // key : 1  is pressed , 0 is released
    uint32_t all_gpio_status_1 = ~gpio_data_in_mask_temp.register0;
    uint32_t all_gpio_status_2 = ~gpio_data_in_mask_temp.register1;
    uint32_t all_gpio_status_3 = hid_common->hid.expand_io.status;

    for (combo_idx = 0; combo_idx < combo_cfg.combo_key_list_size; combo_idx++)
    {
        combo_key_1 = combo_cfg.combo_key_list[combo_idx].combo_bit_00_31;
        combo_key_2 = combo_cfg.combo_key_list[combo_idx].combo_bit_32_63;
        combo_key_3 = combo_cfg.combo_key_list[combo_idx].combo_bit_64_95;

        if(((combo_key_1 & all_gpio_status_1) == combo_key_1)
            && ((combo_key_2 & all_gpio_status_2) == combo_key_2)
            && ((combo_key_3 & all_gpio_status_3) == combo_key_3))
        {
            ret = combo_idx;
            break;
        }
    }
    return ret;
}

/* Public functions ----------------------------------------------------------*/
void riscv_game_controller_key_early_handle(void)
{
    hal_gpt_get_free_run_count( HAL_GPT_CLOCK_SOURCE_1M , &riscv_app.read_key_timestamp );
}

int riscv_game_controller_key_get_key_status(uint32_t * outgoing_keys)
{
    new_keys_status = 0;

    hal_gpt_get_free_run_count( HAL_GPT_CLOCK_SOURCE_1M , &riscv_app.read_key_timestamp );
    new_keys_status = riscv_game_controller_key_polling_all_key_status();
    *outgoing_keys = new_keys_status;

    return SUCCESS;
}

void riscv_game_controller_key_post_process(void)
{

}

void riscv_game_controller_key_get_combo_key(void)
{
    // hid_common_get_combo_key_list(&combo_cfg.combo_key_list, &combo_cfg.combo_key_list_size, &combo_cfg.hold_timeout);
}

void riscv_game_controller_key_change_state(uint32_t state)
{
    combo_cfg.app_state = state;
}

uint32_t riscv_game_controller_keys_get_polling_key_status(void)
{
    return game_controller_32key;
}

void riscv_game_controller_key_pairing_key_check(void)
{
    if((combo_cfg.app_state & APP_STATE_CONNECTED) && (combo_cfg.app_state & 0x01))
    {
        uint32_t end_gpt_free_count = 0;
        uint32_t duration_count = 0;
        combo_key_result = riscv_game_controller_key_combo_key_check();
        if((start_gpt_free_count != 0) && (combo_key_result == PAIRING_COMBO_HOLD))
        {
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &end_gpt_free_count);
            hal_gpt_get_duration_count(start_gpt_free_count, end_gpt_free_count, &duration_count);
            if(duration_count >= (combo_cfg.hold_timeout << 15))
            {
                hid_common_set_hid_exp_flag(FLAG_BIT_FORCE_RELEASE_KEY);
                start_gpt_free_count = 0;
            }
        }
        else if(combo_key_result == PAIRING_COMBO_HOLD)
        {
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &start_gpt_free_count);
        }
        else
        {
            start_gpt_free_count = 0;
        }
    }
}

void riscv_game_controller_key__app_state_update(uint32_t new_state)
{
    switch(new_state)
    {
        case APP_STATE_STANDBY:
        case APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_BT_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_USB_ENTERING_ACTIVE:
        case APP_STATE_BT_CONNECTED:
        case APP_STATE_2_4G_CONNECTED:
        case APP_STATE_USB_CONNECTED:
        {
        }
        break;

        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_RECONNECT:
        case APP_STATE_USB_SUSPEND:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        {
        }
        break;

        case APP_STATE_DISCONNECTED:
        {
            riscv_game_controller_key_deinit();
        }
        break;

        default:
        break;
    }
}

void riscv_game_controller_key_common_para_update(void)
{
}

void riscv_game_controller_key_debug_print(void)
{
    if (game_controller_32key_printed != game_controller_32key){
        LOG_MSGID_I(riscv_key, "game_controller_32key = 0x%x --> 0x%x,  combo_key_list = 0x%08X-%08X-%08X, combo_key_list_size = 0x%x, combo_key_result = 0x%x, flags = 0x%x"
            , 7
            , game_controller_32key_printed
            , game_controller_32key
            , combo_cfg.combo_key_list[0].combo_bit_00_31
            , combo_cfg.combo_key_list[0].combo_bit_32_63
            , combo_cfg.combo_key_list[0].combo_bit_64_95
            , combo_cfg.combo_key_list_size
            , combo_key_result
            , hid_common->hid.flags
            );

        game_controller_32key_printed = game_controller_32key;
    }
}

uint32_t riscv_game_controller_key_id_to_key_status(uint32_t key_id)
{
    int found_idx = -1;
    for (int idx = 0; idx < rv_key_num; idx++) {
        if (rv_key_ids[idx] == key_id) {
            found_idx = idx;
            break;
        }
    }

    if (found_idx >= 0) {
        return (1 << found_idx);
    } else {
        return 0;
    }
}

int riscv_game_controller_key_init(void)
{
    uint32_t idx;

    rv_key_num = hid_common->app.device_key_num;
    for (idx = 0; idx < rv_key_num; idx++)
    {
        rv_key_ids[idx] = hid_common->app.device_key_list[idx];
    }

    riscv_game_controller_key_get_combo_key();

    LOG_MSGID_I(riscv_key, "riscv_game_controller_key_init, key_num = %d, rv_key_ids = 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x"
        , 9
        , rv_key_num
        , *(uint32_t *)(&rv_key_ids[0])
        , *(uint32_t *)(&rv_key_ids[4])
        , *(uint32_t *)(&rv_key_ids[8])
        , *(uint32_t *)(&rv_key_ids[12])
        , *(uint32_t *)(&rv_key_ids[16])
        , *(uint32_t *)(&rv_key_ids[20])
        , *(uint32_t *)(&rv_key_ids[24])
        , *(uint32_t *)(&rv_key_ids[28])
        );

    return 0;
}

int riscv_game_controller_key_deinit(void)
{
    return 0;
}
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
