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

#if defined(AIR_PRODUCT_TYPE_KEYBOARD)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "syslog.h"
#include "rv_ccni.h"
#include "rv_application.h"
#include "riscv_keyboard_key.h"
#include "riscv_peripheral_sampling.h"
#include "pka_share.h"
#include "pka.h"
#include "hal_gpio_internal.h"
#include "hal_eint_internal.h"
#include "hal_gpt.h"
#include "hal_spi_master.h"
#include "hid_common.h"
#include "hid_keycode_id.h"
#include "hal_cross_core_config.h"
#include "riscv_hid_express.h"
#include "riscv_hid_express_key_queue_keyboard.h"

#include "memory_attribute.h"

/* Private define ------------------------------------------------------------*/
#define COMBO_KEY_NONE                          0xFF
#define PAIRING_COMBO_HOLD                      0

#define KEYBOARD_KEY_NUMBER_IN_BIT              128
#define KEYBOARD_KEY_NUMBER_IN_BYTE             (KEYBOARD_KEY_NUMBER_IN_BIT/8)
#define KEYBOARD_KEY_NUMBER_IN_WORD             (KEYBOARD_KEY_NUMBER_IN_BIT/32)

#define KEYBOARD_KEY_MAX                        32

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
uint8_t rv_key_ids[KEYBOARD_KEY_MAX] = {0};

/* the pressed state of all keys expressed in bitmap form */
/* Keyboard/Keypad Usage ID:
 *     0xE0 ~ 0xE7 (LeftControl/LeftShit/...)
 *     0x00 ~ 0x77 (04<->a/A, 0A<->g/G/, ...)
 */
ATTR_ALIGN(16) uint8_t kbd_key_bitmap[KEYBOARD_KEY_NUMBER_IN_BYTE];

static uint32_t combo_key_result = COMBO_KEY_NONE;
static uint32_t new_keys_status;
/* Public variables ----------------------------------------------------------*/
#define CRC8_POLY 0x07

bool kbd_check_crc(uint8_t *crc_check_data, uint8_t crc_length, uint8_t crc_value)
{
    uint8_t crc = 0;
    for(uint8_t i = 0; i < crc_length; i++){
        crc ^= crc_check_data[i];
    }
    return (crc == crc_value);
}

/* Private functions ---------------------------------------------------------*/
uint32_t riscv_keyboard_key_polling_all_key_status(void)
{
    DBG_PING_H(DBG_SIGNAL_SPI_CB);

#if 0
    static uint32_t demo_cnt = 0;
    demo_cnt++;
    // static const uint8_t key_id_pressed[][2] = {
    //     { KEYBOARD_A, KEYBOARD_LSHIFT },
    //     { KEYBOARD_I, KEYBOARD_NO },
    //     { KEYBOARD_R, KEYBOARD_NO },
    //     { KEYBOARD_O, KEYBOARD_NO },
    //     { KEYBOARD_H, KEYBOARD_NO },
    //     { KEYBOARD_A, KEYBOARD_NO },
    //     { KEYBOARD_MINUS, KEYBOARD_RSHIFT },
    //     { KEYBOARD_M, KEYBOARD_LSHIFT },
    //     { KEYBOARD_6, KEYBOARD_NO },
    //     { KEYBOARD_0, KEYBOARD_NO },
    //     { KEYBOARD_7, KEYBOARD_NO },
    //     { KEYBOARD_MINUS, KEYBOARD_RSHIFT },
    //     { KEYBOARD_D, KEYBOARD_RSHIFT },
    //     { KEYBOARD_U, KEYBOARD_NO },
    //     { KEYBOARD_M, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },           /* Release M & Press M */
    //     { KEYBOARD_M, KEYBOARD_NO },
    //     { KEYBOARD_Y, KEYBOARD_NO },
    //     { KEYBOARD_MINUS, KEYBOARD_RSHIFT },
    //     { KEYBOARD_I, KEYBOARD_RSHIFT },
    //     { KEYBOARD_N, KEYBOARD_NO },
    //     { KEYBOARD_P, KEYBOARD_NO },
    //     { KEYBOARD_U, KEYBOARD_NO },
    //     { KEYBOARD_T, KEYBOARD_NO },
    //     { KEYBOARD_KP_6, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_KP_6, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_KP_6, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_ENTER, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },           /* Nothing about 1s */
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    //     { KEYBOARD_NO, KEYBOARD_NO },
    // };
    // static uint32_t key_id_pressed_idx = 0;
    // uint32_t keyboard_usage_id;

    if((demo_cnt % 500) == 0){
        // LOG_MSGID_I(riscv_key, "received data = %02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-",
        //     8,
        //     ccm_spi_sensor[0], ccm_spi_sensor[1], ccm_spi_sensor[2], ccm_spi_sensor[3],
        //     ccm_spi_sensor[4], ccm_spi_sensor[5], ccm_spi_sensor[6], ccm_spi_sensor[7]
        // );
        // LOG_MSGID_I(riscv_key, "         data = %02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X",
        //     8,
        //     ccm_spi_sensor[8], ccm_spi_sensor[9], ccm_spi_sensor[10], ccm_spi_sensor[11],
        //     ccm_spi_sensor[12], ccm_spi_sensor[13], ccm_spi_sensor[14], ccm_spi_sensor[15]
        // );

        /* change the data 16Hz */
        memset((void*)kbd_key_bitmap, 0, sizeof(kbd_key_bitmap));
        // keyboard_usage_id = key_id_pressed[key_id_pressed_idx][0];
        // if(keyboard_usage_id != KEYBOARD_NO){
        //     if((KEYBOARD_LCTRL <= keyboard_usage_id) && (keyboard_usage_id <= KEYBOARD_RGUI)){
        //         kbd_key_bitmap[0] |= 1<< (keyboard_usage_id - KEYBOARD_LCTRL);
        //     } else if ((KEYBOARD_A <= keyboard_usage_id) && (keyboard_usage_id <= KEYBOARD_KP_DOT)){
        //         kbd_key_bitmap[keyboard_usage_id/8 + 1] |= 1 << (keyboard_usage_id % 8);
        //     } else {
        //         ;
        //     }
        // }

        // keyboard_usage_id = key_id_pressed[key_id_pressed_idx][1];
        // if(keyboard_usage_id != KEYBOARD_NO){
        //     if((KEYBOARD_LCTRL <= keyboard_usage_id) && (keyboard_usage_id <= KEYBOARD_RGUI)){
        //         kbd_key_bitmap[0] |= 1<< (keyboard_usage_id - KEYBOARD_LCTRL);
        //     } else if ((KEYBOARD_A <= keyboard_usage_id) && (keyboard_usage_id <= KEYBOARD_KP_DOT)){
        //         kbd_key_bitmap[keyboard_usage_id/8 + 1] |= 1 << (keyboard_usage_id % 8);
        //     } else {
        //         ;
        //     }
        // }
        static uint32_t test_cnt = 0;
        test_cnt++;
        uint8_t cycle = (test_cnt) % 6;
        uint8_t header = (cycle / 2) + 0x01;
        kbd_key_bitmap[0] = header;
        kbd_key_bitmap[1] = 0x00;
        kbd_key_bitmap[2] = (cycle % 2 == 0) ? 0x01 : 0x00;
        LOG_MSGID_I(riscv_key, "kbd_key_bitmap(hex) = %02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-",
            8,
            kbd_key_bitmap[0], kbd_key_bitmap[1], kbd_key_bitmap[2], kbd_key_bitmap[3],
            kbd_key_bitmap[4], kbd_key_bitmap[5], kbd_key_bitmap[6], kbd_key_bitmap[7]
        );
        LOG_MSGID_I(riscv_key, "           continue = %02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X",
            8,
            kbd_key_bitmap[8], kbd_key_bitmap[9], kbd_key_bitmap[10], kbd_key_bitmap[11],
            kbd_key_bitmap[12], kbd_key_bitmap[13], kbd_key_bitmap[14], kbd_key_bitmap[15]
        );
        LOG_MSGID_I(riscv_key, "kbd_key_bitmap addr = %08X-%08X",
            2,
            &kbd_key_bitmap[0],
            &kbd_key_bitmap[8]
        );
        // extern uint32_t psd_running_cnt[4];
        // LOG_MSGID_I(riscv_key, "psd_running_cnt = %08X-%08X-%08X-%08X",
        //     4,
        //     psd_running_cnt[0],
        //     psd_running_cnt[1],
        //     psd_running_cnt[2],
        //     psd_running_cnt[3]
        // );
        // key_id_pressed_idx = (key_id_pressed_idx + 1) % (sizeof(key_id_pressed)/2);
    }
#else

    // int detect_data_ready_count = 5;
    // hal_gpio_data_t mcu_to_rf = HAL_GPIO_DATA_HIGH;
    // while(mcu_to_rf != HAL_GPIO_DATA_LOW){
    //     hal_gpio_get_input(MCU_TO_RF_IO, &mcu_to_rf);
    //     hal_gpt_delay_us(3);
    //     if(detect_data_ready_count == 0){
    //         break;
    //     }
    //     detect_data_ready_count--;
    // }

    static ATTR_ALIGN(16) uint8_t spi_dummy_write_buffer[16];
    static hal_spi_master_send_and_receive_config_t cfg = {
        .send_data = &spi_dummy_write_buffer[0],
        .send_length = sizeof(spi_dummy_write_buffer),
        .receive_buffer = &kbd_key_bitmap[0],
        .receive_length = sizeof(kbd_key_bitmap)
    };
    // if (detect_data_ready_count > 0){
        // hal_spi_master_status_t spi_ret =
        hal_spi_master_send_and_receive_polling(HAL_SPI_MASTER_1, &cfg);
        /* timing sync done */
        hal_gpio_set_output(TIMING_SYNC_IO, HAL_GPIO_DATA_HIGH);
        // if(spi_ret != HAL_SPI_MASTER_STATUS_OK){
            // HID_DBG_LOG(riscv_key, "communication fail !!! spi_ret=%d@%d", 2, spi_ret, __LINE__);
            // assert(spi_ret == HAL_SPI_MASTER_STATUS_OK);
        // }
    // }
    kbd_check_crc(kbd_key_bitmap, 15, kbd_key_bitmap[15]);
#endif
    DBG_PING_L(DBG_SIGNAL_SPI_CB);
    return (uint32_t)(&kbd_key_bitmap[0]);
}

uint32_t riscv_keyboard_key_combo_key_check(void)
{
    uint32_t ret = COMBO_KEY_NONE;
    uint32_t combo_key_1, combo_key_2;
    uint32_t combo_idx;
    gpio_data_in_mask_t gpio_data_in_mask_temp;

    hal_eint_get_debounce_out_value_by_mask(&gpio_data_in_mask_temp.register0, &gpio_data_in_mask_temp.register1);

    // gpio: 0  is pressed , 1 is released
    // key : 1  is pressed , 0 is released
    uint32_t all_gpio_status_1 = ~gpio_data_in_mask_temp.register0;
    uint32_t all_gpio_status_2 = ~gpio_data_in_mask_temp.register1;

    for (combo_idx = 0; combo_idx < combo_cfg.combo_key_list_size; combo_idx++)
    {
        combo_key_1 = combo_cfg.combo_key_list[combo_idx].combo_bit_00_31;
        combo_key_2 = combo_cfg.combo_key_list[combo_idx].combo_bit_32_63;

        if(((combo_key_1 & all_gpio_status_1) == combo_key_1)
            && ((combo_key_2 & all_gpio_status_2) == combo_key_2))
        {
            ret = combo_idx;
            break;
        }
    }
    return ret;
}

static void riscv_keyboard_key__ccni_send_status(uint32_t key_status)
{
    hal_ccni_message_t ccni_msg = {0};
    ccni_msg.data[0] = key_status;

    hal_ccni_set_event(IRQGEN_RISCV2MCU_EVENT6, &ccni_msg);
}

/* Public functions ----------------------------------------------------------*/
void riscv_keyboard_key_early_handle(void)
{
    hal_gpt_get_free_run_count( HAL_GPT_CLOCK_SOURCE_1M , &riscv_app.read_key_timestamp );
}

int riscv_keyboard_key_get_key_status(uint32_t * outgoing_keys)
{
    new_keys_status = 0;

    hal_gpt_get_free_run_count( HAL_GPT_CLOCK_SOURCE_1M , &riscv_app.read_key_timestamp );
    new_keys_status = riscv_keyboard_key_polling_all_key_status();
    *outgoing_keys = new_keys_status;

    return SUCCESS;
}

void riscv_keyboard_key_post_process(void)
{
    riscv_keyboard_key__ccni_send_status(new_keys_status);
}

void riscv_keyboard_key_get_combo_key(void)
{
    // hid_common_get_combo_key_list(&combo_cfg.combo_key_list, &combo_cfg.combo_key_list_size, &combo_cfg.hold_timeout);
}

void riscv_keyboard_key_change_state(uint32_t state)
{
    combo_cfg.app_state = state;
}

uint32_t riscv_keyboard_keys_get_polling_key_status(void)
{
    return (uint32_t)(&kbd_key_bitmap[0]);
}

void riscv_keyboard_key_pairing_key_check(void)
{
    if((combo_cfg.app_state & APP_STATE_CONNECTED) && (combo_cfg.app_state & 0x01))
    {
        uint32_t end_gpt_free_count = 0;
        uint32_t duration_count = 0;
        combo_key_result = riscv_keyboard_key_combo_key_check();
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

void riscv_keyboard_key__app_state_update(uint32_t new_state)
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
            riscv_keyboard_key_deinit();
        }
        break;

        default:
        break;
    }
}

void riscv_keyboard_key_common_para_update(void)
{
}

void riscv_keyboard_key_debug_print(void)
{
    if (kbd_key_bitmap[15] != kbd_key_bitmap[0]){ /* crc value != header data contains nonzero value */
        // LOG_MSGID_I(riscv_ps, "keyboard key bitmap = 0x%x --> 0x%x,  combo_key_list = 0x%08X-%08X, combo_key_list_size = 0x%x, combo_key_result = 0x%x, flags = 0x%x"
        //     , 7
        //     , mouse_5key_printed
        //     , mouse_5key
        //     , combo_cfg.combo_key_list[0].combo_bit_00_31
        //     , combo_cfg.combo_key_list[0].combo_bit_32_63
        //     , combo_cfg.combo_key_list_size
        //     , combo_key_result
        //     , hid_common->hid.flags
        //     );
        LOG_MSGID_I(riscv_key, "kbd_key_bitmap(hex) = %02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-",
            8,
            kbd_key_bitmap[0], kbd_key_bitmap[1], kbd_key_bitmap[2], kbd_key_bitmap[3],
            kbd_key_bitmap[4], kbd_key_bitmap[5], kbd_key_bitmap[6], kbd_key_bitmap[7]
        );
        LOG_MSGID_I(riscv_key, "           continue = %02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X",
            8,
            kbd_key_bitmap[8], kbd_key_bitmap[9], kbd_key_bitmap[10], kbd_key_bitmap[11],
            kbd_key_bitmap[12], kbd_key_bitmap[13], kbd_key_bitmap[14], kbd_key_bitmap[15]
        );
    }
}

uint32_t riscv_keyboard_key_id_to_key_status(uint32_t key_id)
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

int riscv_keyboard_key_init(void)
{
    uint32_t idx;

    rv_key_num = hid_common->app.device_key_num;
    for (idx = 0; idx < rv_key_num; idx++)
    {
        rv_key_ids[idx] = hid_common->app.device_key_list[idx];
    }

    riscv_keyboard_key_get_combo_key();

    LOG_MSGID_I(riscv_key, "riscv_keyboard_key_init, key_num = %d, rv_key_ids = 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x"
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

int riscv_keyboard_key_deinit(void)
{
    return 0;
}
#endif /* AIR_PRODUCT_TYPE_KEYBOARD */
