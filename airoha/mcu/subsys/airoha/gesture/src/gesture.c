/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

#include "gesture.h"
#include "hal_eint.h"
#include "hal_gpt.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hal_eint_internal.h"
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "hid_game_controller.h"
#endif
#if defined(CONFIG_IO_EXPANDER_AW95124)
#include "io_expander_sensor_mgr.h"
#endif
#if defined (AIR_SWLA_ENABLE)
#include "swla.h"
#endif
#include "air_daemon_work_q.h"

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#define thisMODULE  gesture
#define thisMOD    "gesture"

LOG_MODULE_REGISTER(thisMODULE);


static void gesture_key_changed(struct k_work *work);
static K_WORK_DEFINE(job_gesture, gesture_key_changed);


#if defined(CONFIG_LOG)
#define DBG_LOGI(module_name, format, ...)   \
        LOG_INF("[srv-i]["module_name"]" format, ## __VA_ARGS__)

#else
#define DBG_LOGI(module_name, format, ...)   \
        printk("[I]["module_name"]"format, ## __VA_ARGS__)
#endif

#define MIN_HOLD_TIMEOUT            500   //ms  如果 PRESS_AND_HOLE_LV_0_TO_1触发小于这个，就会触发断言，芯片卡死，卡死位置在airo_key_init
#define MAX_HOLD_TIMEOUT          10000   //ms

#define MIN_MULTI_CLICK_TIMEOUT      100  //ms
#define MAX_MULTI_CLICK_TIMEOUT     1000  //ms

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)

#define MAX_MULTI_CLICK_NUM          32
#define MAX_AK_NUM                   32

#else

#define MAX_MULTI_CLICK_NUM          9 // 5 clicks key at maximum
#define MAX_AK_NUM                   8 // 8 gpio key

#endif

#define TIMER_ID_KEY_HOLD_BASE             20
#define TIMER_ID_KEY_MULTI_CLICK_BASE      23
#define COMBO_KEY_NONE                    0xFF

#define GPIO_UNDEFINE 0xFF
#define GPIO_EXTERNAL_FLAG 0x80

typedef struct {
    void *fifo_reserved;
    uint8_t id;
} eint_fifo_t;

typedef struct {
    T_AIROHA_KEY_CONFIGURATION_S cfg;
    uint8_t    multi_click_counts[MAX_AK_NUM];
    uint8_t    reported_event[MAX_AK_NUM];
    struct k_fifo eint_id_fifo;
}AK_CTRL;



AK_CTRL akey;
uint8_t gesture_gpio_pin=0;

struct k_timer * hold_key_timers;
struct k_timer * multi_click_key_timers;


uint32_t gpio_level_record = 0xFFFFFFFF;
extern void hal_eint_enable(uint32_t eint_number);

#if defined(CONFIG_IO_EXPANDER_AW95124)
uint32_t airo_io_expander_key_mask;
uint32_t airo_io_expander_key_status_record;
#endif /* CONFIG_IO_EXPANDER_AW95124 */

/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/

/**
 * @brief Initialize the GPIO pins as input or output.
 * @param[in] gpio_id GPIO pin number.
 * @retval index of the key in akey.cfg.key_list.
*/
uint8_t airo_key_get_key_index(uint8_t gpio_id)
{
    uint8_t idx = 0xFF;

    for (idx = 0 ; idx < akey.cfg.key_list_size; idx++)
    {
        if (akey.cfg.key_list[idx] == gpio_id){
            return idx;
            break;
        }
    }

    return idx; // Not found
}

/**
 * @brief Retrieve the GPIO pin number based on its index in the key list.
 * @param[in] idx Index of the key in akey.cfg.key_list.
 * @retval GPIO pin number if valid index, else 0xFF to indicate an invalid index.
 */
uint8_t airo_key_get_gpio_id_by_index(uint8_t idx)
{
    // Check if the index is within the bounds of the key list size
    if (idx < akey.cfg.key_list_size) {
        return akey.cfg.key_list[idx];
    } else {
        // Return 0xFF if the index is invalid
        return 0xFF;
    }
}

void air_key_all_status_update(uint8_t *output_status,uint32_t key_id)
{
#if defined(CONFIG_IO_EXPANDER_AW95124)
    uint32_t byte_idx;
    uint32_t bit_idx;

    if (key_id < GPIO_EXTERNAL_FLAG)
    {
        byte_idx = key_id / 8;
        bit_idx = key_id % 8;
        output_status[byte_idx] |= (1<<bit_idx);
    }
    else if (key_id != GPIO_UNDEFINE)
    {
        byte_idx = (key_id-GPIO_EXTERNAL_FLAG) / 8 + 8;
        bit_idx = (key_id-GPIO_EXTERNAL_FLAG) % 8;
        output_status[byte_idx] |= (1<<bit_idx);
    }
#else
    #define BYTE_IDX    (key_id / 8)
    #define BIT_IDX    (key_id % 8)
    output_status[BYTE_IDX] |= (1<<BIT_IDX);
#endif  /* CONFIG_IO_EXPANDER_AW95124 */
}

uint8_t air_combo_key_check(uint8_t key_idx)
{
    uint8_t combo_idx, idx, ret = COMBO_KEY_NONE;
    uint32_t comboKey_0;
    uint32_t comboKey_1;
    #if defined(CONFIG_IO_EXPANDER_AW95124)
    uint32_t comboKey_2;
    #endif /* CONFIG_IO_EXPANDER_AW95124 */

    //uint32_t all_key_status = 0;
    #if defined(CONFIG_IO_EXPANDER_AW95124)
    uint8_t all_key_status[12] = {0};
    #else
    uint8_t all_key_status[8] = {0};
    #endif /* CONFIG_IO_EXPANDER_AW95124 */

    for(idx = 0 ; idx < akey.cfg.key_list_size ; idx ++  ){
        if(akey.reported_event[idx] == AK_LONG_PRESS_LV_1)
        {
            air_key_all_status_update(all_key_status, akey.cfg.key_list[idx]);
        }
    }

    air_key_all_status_update(all_key_status, akey.cfg.key_list[key_idx]);
    uint32_t all_key_status_0 = *(uint32_t*)&all_key_status[0];
    uint32_t all_key_status_1 = *(uint32_t*)&all_key_status[4];
    #if defined(CONFIG_IO_EXPANDER_AW95124)
    uint32_t all_key_status_2 = *(uint32_t*)&all_key_status[8];
    #endif /* CONFIG_IO_EXPANDER_AW95124 */

    if (akey.cfg.combo_key_list ){
        for(combo_idx = 0 ; combo_idx < akey.cfg.combo_key_list_size ; combo_idx ++  ){
            comboKey_0 = akey.cfg.combo_key_list[combo_idx].combo_bit_00_31;
            comboKey_1 = akey.cfg.combo_key_list[combo_idx].combo_bit_32_63;
            #if defined(CONFIG_IO_EXPANDER_AW95124)
            comboKey_2 = akey.cfg.combo_key_list[combo_idx].combo_bit_64_95;
            #endif /* CONFIG_IO_EXPANDER_AW95124 */

            #if defined(CONFIG_IO_EXPANDER_AW95124)
            DBG_LOGI(thisMOD, "air_combo_key_check[%d] = 0x%08X-%08X-%08X ,  all_key_status = 0x%08X-%08X-%08X  "
                    , combo_idx
                    , comboKey_0
                    , comboKey_1
                    , comboKey_2
                    , all_key_status_0
                    , all_key_status_1
                    , all_key_status_2
                     );
            #else
            DBG_LOGI(thisMOD, "air_combo_key_check[%d] = 0x%08X-%08X ,  all_key_status = 0x%08X-%08X  "
                    , combo_idx
                    , comboKey_0
                    , comboKey_1
                    , all_key_status_0
                    , all_key_status_1
                     );
            #endif /* CONFIG_IO_EXPANDER_AW95124 */

            if (((comboKey_0 & all_key_status_0) == comboKey_0) 
                && ((comboKey_1 & all_key_status_1) == comboKey_1)
                #if defined(CONFIG_IO_EXPANDER_AW95124)
                && ((comboKey_2 & all_key_status_2) == comboKey_2)
                #endif /* CONFIG_IO_EXPANDER_AW95124 */
                ) {
                ret = combo_idx;
                break;
            }
        }
    }

    DBG_LOGI(thisMOD, "ret = %d,  akey.combo_key_list_size = %d  ", ret, akey.cfg.combo_key_list_size );
    return ret;
}

hal_gpio_status_t air_gpio_get_input(uint8_t key_idx,  hal_gpio_pin_t gpio_pin, hal_gpio_data_t *gpio_data)
{
    #ifdef FPGA_SIM
    *gpio_data = FPGA_gpio_lv_sim[key_idx] & 0x01;

    uint32_t all_key_status = pka_share_ptr->app.all_key_status;

    if (*gpio_data & 0x01) {
        // 1 is press
        // set the corresponded bit of all_key_status to 0
        all_key_status &= ~(1 << akey.cfg.key_list[key_idx]);
    }
    else {
        // 0 is release
        // set the corresponded bit of all_key_status to 1
        all_key_status |= (1 << akey.cfg.key_list[key_idx]);
    }

    pka_share_ptr->app.all_key_status = all_key_status;
    DBG_LOGI(thisMOD, "all_key_status = 0x%04X, FPGA_gpio_lv_sim[%d] = %d ", all_key_status, key_idx, FPGA_gpio_lv_sim[key_idx]);
    FPGA_gpio_lv_sim[key_idx]++;
    return 0;
    #else

    #if defined(CONFIG_IO_EXPANDER_AW95124)
    if ((gpio_pin >= GPIO_EXTERNAL_FLAG) && (GPIO_UNDEFINE != gpio_pin))
    {
        uint32_t external_gpio_status = io_expander_mgr_get_all_input_status();
        *gpio_data = (external_gpio_status & (0x1 << (gpio_pin - GPIO_EXTERNAL_FLAG))) ? HAL_GPIO_DATA_HIGH : HAL_GPIO_DATA_LOW;
        return HAL_GPIO_STATUS_OK;
    }
    #endif /* CONFIG_IO_EXPANDER_AW95124 */

    return hal_gpio_get_input(gpio_pin, gpio_data);
    #endif
}

void airo_key_hold_timeout(struct k_timer *timer)
{
    uint8_t key_event = AK_RELEASE;
    if (akey.cfg.key_handle_cb == NULL){
        return;
    }

    uint8_t key_idx = timer - hold_key_timers;

    DBG_LOGI(thisMOD," hold_timeout handle, idx = %d, io = %d, last evt = 0x%x "
        , key_idx
        , akey.cfg.key_list[key_idx]
        , akey.reported_event[key_idx]
        );

    switch(akey.reported_event[key_idx])
    {
        case AK_RELEASE:
        {
            if (akey.multi_click_counts[key_idx] == 1){
                uint8_t combo_id = COMBO_KEY_NONE;

                if (akey.cfg.combo_key_list && akey.cfg.combo_key_list_size){
                    combo_id = air_combo_key_check(key_idx);
                }

                if (combo_id == COMBO_KEY_NONE) {
                    // press and hold event
                    key_event = AK_LONG_PRESS_LV_1;
                    k_timer_start(&hold_key_timers[key_idx], K_MSEC(akey.cfg.hold_timeout_LP2_ms) , K_NO_WAIT);
                }
                else {
                    key_event = AK_COMBO_HOLD_LV1_0 + combo_id ;
                }

                // DBG_LOGI(thisMOD,"key_event = 0x%x", key_event);
            }
            else if (akey.multi_click_counts[key_idx] <= (MAX_MULTI_CLICK_NUM + 1)){
                // click + hold event
                key_event = AK_SLONG + akey.multi_click_counts[key_idx] - 2;
            }
            else {
                // Not supported
                DBG_LOGI(thisMOD,"%d click and hold is NOT Supportted", akey.multi_click_counts[key_idx]-1);
            }
        }
        break;

        case AK_LONG_PRESS_LV_1:
        {
            key_event = AK_LONG_PRESS_LV_2;
            // restart timer for key hold check
            k_timer_start(&hold_key_timers[key_idx], K_MSEC(akey.cfg.hold_timeout_LP3_ms) , K_NO_WAIT);
        }
        break;

        case AK_LONG_PRESS_LV_2:
        {
            key_event = AK_LONG_PRESS_LV_3;
        }
        break;
    }

    // DBG_LOGI(thisMOD,"akey.cfg.key_list[key_idx] = 0x%x", akey.cfg.key_list[key_idx]);
    akey.cfg.key_handle_cb(key_event, akey.cfg.key_list[key_idx]);
    akey.reported_event[key_idx]=key_event;
}

void airo_key_multi_click_timeout(struct k_timer *timer)
{
    if (akey.cfg.key_handle_cb == NULL){
        return;
    }
    uint8_t key_idx = (timer - multi_click_key_timers);
    DBG_LOGI(thisMOD," multi_click_timeout handle = 0x%x, key_idx = %d, click count = %d, rep_evt = %d"
        , (int)timer
        , key_idx
        , akey.multi_click_counts[key_idx]
        , akey.reported_event[key_idx]
        );

    switch(akey.reported_event[key_idx])
    {
        case AK_RELEASE:
        {
            if (akey.multi_click_counts[key_idx] > 0 && akey.multi_click_counts[key_idx] <= MAX_MULTI_CLICK_NUM){
                //1: AK_SHORT_CLICK
                //2: AK_DOUBLE_CLICK
                //3: AK_TRIPLE_CLICK
                akey.cfg.key_handle_cb(AK_SHORT_CLICK + akey.multi_click_counts[key_idx] - 1, akey.cfg.key_list[key_idx]);
            }
        }
        break;

        case AK_SLONG:
        {
            akey.cfg.key_handle_cb(AK_SLONG_RELEASE, akey.cfg.key_list[key_idx]);
        }
        break;

        case AK_DLONG:
        {
            akey.cfg.key_handle_cb(AK_DLONG_RELEASE, akey.cfg.key_list[key_idx]);
        }
        break;

        case AK_TLONG:
        {
            akey.cfg.key_handle_cb(AK_TLONG_RELEASE, akey.cfg.key_list[key_idx]);
        }
        break;

        default:
            if ( (akey.reported_event[key_idx] >= AK_SLONG) && akey.reported_event[key_idx] <= AK_SLONG + 8 ){
                akey.cfg.key_handle_cb(akey.reported_event[key_idx] - AK_CLICK_AND_LONG_PRESS_TYPE_MASK + AK_CLICK_AND_LONG_PRESS_RELEASE_TYPE_MASK, akey.cfg.key_list[key_idx]);
            }
            else {
                DBG_LOGI(thisMOD,"Unknow in airo_key_multi_click_timeout");
            }
            break;
    }

    akey.reported_event[key_idx]=AK_RELEASE;

    // Multi click timeout, reset the counter
    akey.multi_click_counts[key_idx] = 0;
}

void airo_key_eint_callback(void *id)
{
    hal_eint_mask(*(uint8_t*)id);

    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_gesture, SWLA_DIRECTION_START);
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_gesture, SWLA_DIRECTION_LABEL);
    #endif

    //DBG_LOGI(thisMOD, "airo_key_eint_callback, id = 0x%X", *(uint8_t*)id );
    eint_fifo_t * eint_fifo = k_malloc(sizeof(eint_fifo_t));

    assert(eint_fifo != NULL);

    if (eint_fifo) {
        eint_fifo->id = *(uint8_t*)id;
        k_fifo_put(&akey.eint_id_fifo, eint_fifo);
        air_daemon_wq_work_submit(&job_gesture); // gesture_key_changed will be executed
    }
    else {
        DBG_LOGI(thisMOD, "k_malloc failed for eint_fifo");
    }

    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_gesture, SWLA_DIRECTION_STOP);
    #endif
}

#if defined(CONFIG_IO_EXPANDER_AW95124)
void airo_io_expander_key_eint_callback(uint32_t *keys)
{
    uint8_t gpio_num;
    uint32_t key_status = (~(*keys)) & airo_io_expander_key_mask;
    uint32_t key_changed = key_status ^ airo_io_expander_key_status_record;
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    hid_common->hid.expand_io.status = key_status;
    game_controller_set_expand_button(keys);
    #endif
    if (key_changed != 0)
    {
        /* some extneral key status is changed */
        for (gpio_num = 0; gpio_num < 32; gpio_num++)
        {
            if (key_changed & (0x1<<gpio_num))
            {
                eint_fifo_t *eint_fifo = k_malloc(sizeof(eint_fifo_t));
                assert(eint_fifo != NULL);
                if (eint_fifo) {
                    eint_fifo->id = gpio_num+GPIO_EXTERNAL_FLAG;
                    k_fifo_put(&akey.eint_id_fifo, eint_fifo);
                    air_daemon_wq_work_submit(&job_gesture); // gesture_key_changed will be executed
                }
                else {
                    DBG_LOGI(thisMOD, "k_malloc failed for eint_fifo");
                }
            }
        }
    }
    airo_io_expander_key_status_record = key_status;
    // DBG_LOGI(thisMOD, "airo_io_expander_key_eint_callback, keys: 0x%x, changed 0x%x, status = 0x%x, record = 0x%x", *keys, key_changed, hid_common->hid.expand_io.status, airo_io_expander_key_status_record);
}
#endif /* CONFIG_IO_EXPANDER_AW95124 */

static void gesture_key_changed(struct k_work *work)
{
    eint_fifo_t* eint_fifo = k_fifo_get(&akey.eint_id_fifo, K_NO_WAIT);

    while (eint_fifo != NULL)
    {
        hal_gpio_data_t gpio_level = 1;
        uint8_t key_idx = airo_key_get_key_index(eint_fifo->id);
        if (air_gpio_get_input(key_idx, eint_fifo->id, &gpio_level) == HAL_GPIO_STATUS_OK) {
            gesture_key_changed_handler(eint_fifo->id, gpio_level, key_idx);
        }
        else{
            DBG_LOGI(thisMOD, "air_gpio_get_input failed, gpio_pin = %d, key_idx = %d", eint_fifo->id, key_idx);
        }

        k_free(eint_fifo);
        eint_fifo = k_fifo_get(&akey.eint_id_fifo, K_NO_WAIT);
    }
}

void gesture_key_changed_handler(uint8_t gpio_pin, uint8_t gpio_level, uint8_t key_idx)
{
    if (key_idx >= akey.cfg.key_list_size)
        return;

    uint8_t last_gpio_level = (gpio_level_record >> key_idx) & 0x01;

    DBG_LOGI(thisMOD,"gesture_key_changed_handler gpio_pin = %d, last_gpio_level = %d, gpio_level = %d, akey.cfg.key_list_size = %d, reported_event[key_idx] = 0x%d "
        , gpio_pin
        , last_gpio_level
        , gpio_level
        , akey.cfg.key_list_size
        , akey.reported_event[key_idx]
    );

    if(last_gpio_level != gpio_level)
    {
        if (gpio_level == 0 ){
            // restart timer for key hold check
            k_timer_start(&hold_key_timers[key_idx], K_MSEC(akey.cfg.hold_timeout_ms) , K_NO_WAIT);

            // stop key hold timer once the key is released
            k_timer_stop(&multi_click_key_timers[key_idx]);
            akey.multi_click_counts[key_idx]++;

        // DBG_LOGI(thisMOD, "[Press]  key_idx = %d, akey.multi_click_counts[key_idx] = %d ", key_idx, akey.multi_click_counts[key_idx]); 

            // send key event to callback function
            akey.cfg.key_handle_cb(AK_PRESS, gpio_pin);
            gpio_level_record &= ~(0x01 << key_idx);
        }
        else {
            // restart multi click check
            k_timer_start(&multi_click_key_timers[key_idx], K_MSEC(akey.cfg.click_timeout_ms) , K_NO_WAIT );
        // DBG_LOGI(thisMOD, "[Release], key_idx = %d, akey.multi_click_counts[key_idx] = %d"
        //     , key_idx
        //     , akey.multi_click_counts[key_idx]
        //     ); 

            // stop key hold timer once the key is released
            k_timer_stop(&hold_key_timers[key_idx]);

            if ((akey.reported_event[key_idx] & AK_LONG_PRESS_TYPE_MASK) == AK_LONG_PRESS_TYPE_MASK){
                // send long press release event
                akey.cfg.key_handle_cb(akey.reported_event[key_idx] - AK_LONG_PRESS_TYPE_MASK +  AK_LONG_PRESS_RELEASE_TYPE_MASK , gpio_pin);
            }

            // send key event to callback function
            akey.cfg.key_handle_cb(AK_RELEASE, gpio_pin);
            gpio_level_record |= (0x01 << key_idx);
        }
    }

    #if defined(CONFIG_IO_EXPANDER_AW95124)
    if (gpio_pin >= GPIO_EXTERNAL_FLAG)
    {
        return;
    }
    #endif /* CONFIG_IO_EXPANDER_AW95124 */
    hal_eint_unmask(gpio_pin);
}

airo_key_status_t gesture_key_set_irq(uint8_t* key_list, uint8_t key_list_size, uint8_t enable)
{
    uint8_t idx;
    uint8_t j;

    for (idx = 0 ; idx <key_list_size ; idx++ )
    {
        uint8_t key_matched = false;
        for (j = 0; j <akey.cfg.key_list_size; j++ )
        {
            if (akey.cfg.key_list[j] == key_list[idx]){
                key_matched = true;
            }
        }

        if (key_matched == false){
            return AIRO_STATUS_INVALID_PARAM;
        }
    }

    // all keys valid
    for (idx = 0 ; idx <key_list_size ; idx++ )
    {
        #if defined(CONFIG_IO_EXPANDER_AW95124)
        if (key_list[idx] >= GPIO_EXTERNAL_FLAG)
        {
            continue;
        }
        #endif /* CONFIG_IO_EXPANDER_AW95124 */
        if (enable){
            hal_eint_enable(key_list[idx]);
        }
        else {
            hal_eint_disable(key_list[idx]);
        }
    }

    DBG_LOGI(thisMOD, "gesture_key_set_irq success,  %d keys's irq = %d"
        , key_list_size
        , enable
        );

    return AIRO_STATUS_SUCCESS;
}

airo_key_status_t gesture_key_set_eint_counter(uint8_t* key_list, uint8_t key_list_size, uint8_t enable)
{
    if(enable){
        hal_eint_counter_enable();
    }
    else
    {
        hal_eint_counter_disable();
        return AIRO_STATUS_SUCCESS;
    }

    for(uint8_t idx = 0; idx < key_list_size; idx++)
    {
        uint8_t key_matched = false;
        for(uint8_t j = 0; j < akey.cfg.key_list_size; j++)
        {
            if (akey.cfg.key_list[j] == key_list[idx]){
                key_matched = true;
            }
        }
        if(key_matched == false){
            return AIRO_STATUS_INVALID_PARAM;
        }
    }

    for(uint8_t idx = 0; idx < key_list_size; idx++)
    {
        #if defined(CONFIG_IO_EXPANDER_AW95124)
        if (key_list[idx] >= GPIO_EXTERNAL_FLAG)
        {
            continue;
        }
        #endif /* CONFIG_IO_EXPANDER_AW95124 */
        hal_eint_set_counter_number(key_list[idx], idx);
        hal_eint_unmask(key_list[idx]);
    }

    DBG_LOGI(thisMOD, "gesture_key_set_eint_counter success,  %d keys's eint_counter = %d", key_list_size, enable);
    return AIRO_STATUS_SUCCESS;
}

bool gesture_key_check_key_list_validation(uint8_t* key_list, uint8_t key_list_size)
{
    for(uint8_t idx = 0; idx < key_list_size; idx++)
    {
        uint8_t key_matched = false;
        for(uint8_t j = 0; j < akey.cfg.key_list_size; j++)
        {
            if (akey.cfg.key_list[j] == key_list[idx]){
                key_matched = true;
                break;
            }
        }

        if (key_matched == false){
            DBG_LOGI(thisMOD, "gesture_key_check_key_list_validation Fail" );
            return false;
        }
    }

    return true;
}

airo_key_status_t gesture_key_set_pull(uint8_t* key_list, uint8_t key_list_size, uint8_t option)
{
    // DBG_LOGI(thisMOD, "gesture_key_set_pull" );

    if (gesture_key_check_key_list_validation(key_list, key_list_size)){

        if (option == INPUT_PULL_NONE){
            for(uint8_t idx = 0; idx < key_list_size; idx++)
            {
                #if defined(CONFIG_IO_EXPANDER_AW95124)
                hal_gpio_status_t ret;
                if (key_list[idx] < GPIO_EXTERNAL_FLAG)
                {
                    ret = hal_gpio_disable_pull(key_list[idx]);
                }
                else if (akey.cfg.key_list[idx] != GPIO_UNDEFINE)
                {
                    // io_expander_set_pull(key_list[idx]-GPIO_EXTERNAL_FLAG, false);
                    ret = HAL_GPIO_STATUS_OK;
                }
                else
                {
                    ret = HAL_GPIO_STATUS_OK;
                }
                #else
                hal_gpio_status_t ret = hal_gpio_disable_pull(key_list[idx]);
                #endif /* CONFIG_IO_EXPANDER_AW95124 */

                DBG_LOGI(thisMOD, "gesture_key_set_pull GPIO_%d ret = %d"
                    , key_list[idx]
                    , ret
                    );

                if (HAL_GPIO_STATUS_OK != ret){
                    return AIRO_STATUS_FAIL;
                }
            }

            return AIRO_STATUS_SUCCESS;
        }
    }

    return AIRO_STATUS_INVALID_PARAM;
}

bool gesture_key_click_timer_running(uint8_t key_idx)
{
    return k_timer_remaining_get(&hold_key_timers[key_idx]) > 0;
}

void gesture_key_all_click_reset(uint8_t* key_list, uint8_t key_list_size, bool multi_click_counts_reset)
{
    DBG_LOGI(thisMOD, "gesture_key_all_click_reset idx, key_list_size = %d", key_list_size);
    for (uint8_t idx = 0 ; idx < key_list_size ; idx++ )
    {
        uint8_t key_idx = airo_key_get_key_index(key_list[idx]);
        gesture_key_click_reset(key_idx, multi_click_counts_reset);
    }
}

void gesture_key_click_reset(uint8_t key_idx, bool multi_click_counts_reset)
{
    k_timer_stop(&hold_key_timers[key_idx]);
    akey.reported_event[key_idx] = AK_RELEASE;
    if(multi_click_counts_reset)
    {
        akey.multi_click_counts[key_idx] = 0;
        k_timer_stop(&multi_click_key_timers[key_idx]);
    }
}

airo_key_status_t gesture_key_reconfiguration(uint8_t* key_list, uint8_t key_list_size, uint8_t config_option)
{
    DBG_LOGI(thisMOD, "gesture_key_reconfiguration = %d, key_list_size = %d"
        , config_option
        , key_list_size
        );

    switch(config_option)
    {
        case GESTURE_CFG_OPT_ENABLE_KEY_IRQ:
        {
            return gesture_key_set_irq(key_list, key_list_size, true);
        }
        break;

        case GESTURE_CFG_OPT_DISABLE_KEY_IRQ:
        {
            return gesture_key_set_irq(key_list, key_list_size, false);
        }
        break;

        case GESTURE_CFG_OPT_ENABLE_EINT_COUNTER:
        {
            return gesture_key_set_eint_counter(key_list, key_list_size, true);
        }
        break;

        case GESTURE_CFG_OPT_DISABLE_PULL:
        {
            return gesture_key_set_pull(key_list, key_list_size, 0 );
        }

        default:
        break;
    }

    return AIRO_STATUS_INVALID_PARAM;
}

void airo_key_gpio_configuration(uint8_t* key_list, uint8_t key_list_size, uint8_t* debounce_time_list)
{
    uint8_t idx;
    hal_eint_status_t ret_log[3];
    hal_eint_config_t eint_config;
    eint_config.trigger_mode = HAL_EINT_EDGE_FALLING_AND_RISING;


    for (idx = 0 ; idx < key_list_size; idx ++ )
    {
        eint_config.debounce_time = debounce_time_list[idx];
        #if defined(CONFIG_IO_EXPANDER_AW95124)
        if (key_list[idx] < GPIO_EXTERNAL_FLAG)
        #else
        if (GPIO_UNDEFINE != key_list[idx])
        #endif
        {
            ret_log[0] = hal_eint_init(key_list[idx], &eint_config);
            ret_log[1] = hal_eint_register_callback(key_list[idx], airo_key_eint_callback, (void*)&key_list[idx]);
            hal_eint_enable(key_list[idx]);
            ret_log[2] = hal_eint_unmask(key_list[idx]);

            DBG_LOGI(thisMOD, "hal_eint_init = %d, hal_eint_register_callback = %d, hal_eint_unmask = %d, debounce_time = %d"
                , ret_log[0]
                , ret_log[1]
                , ret_log[2]
                , eint_config.debounce_time
                );
        }
        #if defined(CONFIG_IO_EXPANDER_AW95124)
        else if ((GPIO_UNDEFINE != key_list[idx]) && (key_list[idx] >= GPIO_EXTERNAL_FLAG))
        {
            // io_expander_set_debounce_time(akey.cfg.key_list[idx]-GPIO_EXTERNAL_FLAG, eint_config.debounce_time);
            DBG_LOGI(thisMOD, "io_expander = %d, debounce_time = %d"
                , akey.cfg.key_list[idx]
                , eint_config.debounce_time
                );
        }
        #endif /* CONFIG_IO_EXPANDER_AW95124 */
    }
}

void airo_key_gpio_debounce_config(uint8_t idx, uint8_t debounce_time)
{
    hal_eint_status_t ret_log = HAL_EINT_STATUS_OK;

    #if defined(CONFIG_IO_EXPANDER_AW95124)
    if (akey.cfg.key_list[idx] < GPIO_EXTERNAL_FLAG)
    {
        ret_log = hal_eint_set_debounce_time(akey.cfg.key_list[idx], debounce_time);
    }
    else if (akey.cfg.key_list[idx] != GPIO_UNDEFINE)
    {
        // ret_log = io_expander_set_debounce_time(akey.cfg.key_list[idx]-GPIO_EXTERNAL_FLAG, debounce_time);
    }
    #else
    if (akey.cfg.key_list[idx] != GPIO_UNDEFINE)
    {
        ret_log = hal_eint_set_debounce_time(akey.cfg.key_list[idx], debounce_time);
    }
    #endif

    DBG_LOGI(thisMOD, "hal_eint_set_debounce_time gpio = %d, debounce_time = %d, ret_log = %d", akey.cfg.key_list[idx], debounce_time, ret_log);
}

void airo_key_gpio_extslp_debounce_config(uint8_t idx, uint8_t debounce_time)
{
    hal_eint_status_t ret_log = HAL_EINT_STATUS_OK;

    #if defined(CONFIG_IO_EXPANDER_AW95124)
    if (akey.cfg.key_list[idx] < GPIO_EXTERNAL_FLAG)
    #else
    if (akey.cfg.key_list[idx] != GPIO_UNDEFINE)
    #endif
    {
        ret_log = hal_eint_ext_sleep_set_debounce_time(akey.cfg.key_list[idx], debounce_time);
    }

    DBG_LOGI(thisMOD, "hal_eint_ext_sleep_set_debounce_time gpio = %d, debounce_time = %d, ret_log = %d", akey.cfg.key_list[idx], debounce_time, ret_log);
}

void airo_key_timer_init(uint8_t key_num)
{
    /** Timer for the Follow Up discard. */
    uint8_t idx;

    // DBG_LOGI(thisMOD, "airo_key_timer_init  sizeof(struct k_timer ) = %d ", sizeof(struct k_timer ) ); 

    if (hold_key_timers == NULL)
        hold_key_timers = (struct k_timer * )k_malloc(sizeof(struct k_timer ) * key_num);

    if (multi_click_key_timers == NULL)
        multi_click_key_timers = (struct k_timer *)k_malloc(sizeof(struct k_timer ) * key_num);

    __ASSERT( (hold_key_timers && multi_click_key_timers) , "airo_key_timer_init timer handle malloc fail");

    if(hold_key_timers && multi_click_key_timers)
    {
	    for (idx = 0 ; idx < key_num; idx ++ )
	    {
	        k_timer_init(&hold_key_timers[idx] , airo_key_hold_timeout, NULL);
			k_timer_init(&multi_click_key_timers[idx] , airo_key_multi_click_timeout, NULL);
	    }
	}
}

airo_key_status_t airo_key_init(T_AIROHA_KEY_CONFIGURATION_S * cfg)
{
    if (cfg == NULL)
        return AIRO_STATUS_INVALID_PARAM;

    memset((uint8_t*)&akey, 0, sizeof(akey));

    if (cfg->key_handle_cb && cfg->key_list && cfg->key_list_size){
        akey.cfg.key_handle_cb = cfg->key_handle_cb;
        akey.cfg.key_list = cfg->key_list;
        akey.cfg.key_list_size = cfg->key_list_size;
    }
    else {
        return AIRO_STATUS_INVALID_PARAM;
    }

    if ( akey.cfg.key_list_size > MAX_AK_NUM){
        return AIRO_STATUS_INVALID_PARAM;
    }

    k_fifo_init(&akey.eint_id_fifo);

    uint8_t idx;
    DBG_LOGI(thisMOD, "airo_key_init, key_list_size = %d,  key = %d",akey.cfg.key_list_size  ,akey.cfg.key_list[0]);
    for (idx = 1 ; idx < akey.cfg.key_list_size; idx++)
        DBG_LOGI(thisMOD, ", %d" ,akey.cfg.key_list[idx]);

    airo_key_timer_init(akey.cfg.key_list_size);
    akey.cfg.hold_timeout_ms = cfg->hold_timeout_ms;
    akey.cfg.hold_timeout_LP2_ms  = cfg->hold_timeout_LP2_ms;
    akey.cfg.hold_timeout_LP3_ms  = cfg->hold_timeout_LP3_ms;

    akey.cfg.click_timeout_ms = cfg->click_timeout_ms;

    DBG_LOGI(thisMOD,"airo_key_init Hold time = %u-%u-%u, multi click time = %u"
        , (uint32_t)akey.cfg.hold_timeout_ms
        , (uint32_t)akey.cfg.hold_timeout_LP2_ms
        , (uint32_t)akey.cfg.hold_timeout_LP3_ms
        , (uint32_t)akey.cfg.click_timeout_ms
        );

    akey.cfg.combo_key_list = cfg->combo_key_list;
    akey.cfg.combo_key_list_size = cfg->combo_key_list_size;

    if (akey.cfg.combo_key_list && akey.cfg.combo_key_list_size){
        for (idx = 0 ; idx < akey.cfg.combo_key_list_size ; idx ++){
            DBG_LOGI(thisMOD,"combo_key_list[%d] = 0x%08X"
                , idx
                , akey.cfg.combo_key_list[idx]
                );
        }
    }
    else {
        DBG_LOGI(thisMOD,"combo_key_list is NULL");
    }

    if (( akey.cfg.hold_timeout_ms < MIN_HOLD_TIMEOUT) || ( akey.cfg.hold_timeout_ms > MAX_HOLD_TIMEOUT)){
        return AIRO_STATUS_INVALID_PARAM;
    }

    if (( akey.cfg.click_timeout_ms < MIN_MULTI_CLICK_TIMEOUT ) || ( akey.cfg.click_timeout_ms > MAX_MULTI_CLICK_TIMEOUT)){
        return AIRO_STATUS_INVALID_PARAM;
    }

    akey.cfg.debounce_time_list = cfg->debounce_time_list;

    // every thing is ok now
    if (akey.cfg.debounce_time_list && akey.cfg.key_list){
        airo_key_gpio_configuration((uint8_t *)akey.cfg.key_list, akey.cfg.key_list_size, akey.cfg.debounce_time_list);
    }

    #if defined(CONFIG_IO_EXPANDER_AW95124)
    if (akey.cfg.key_list)
    {
        for (idx = 0 ; idx < akey.cfg.key_list_size ; idx ++ )
        {
            if ((akey.cfg.key_list[idx] != GPIO_UNDEFINE) && (akey.cfg.key_list[idx] >= GPIO_EXTERNAL_FLAG))
            {
                airo_io_expander_key_mask |= 0x1 << (akey.cfg.key_list[idx]-GPIO_EXTERNAL_FLAG);
            }
        }
    }
    io_expander_mgr_init();
    io_expander_mgr_register_callback(airo_io_expander_key_eint_callback);
    airo_io_expander_key_status_record = io_expander_mgr_get_all_input_status();
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    hid_common->hid.expand_io.status = (~airo_io_expander_key_status_record) & airo_io_expander_key_mask;
    game_controller_set_expand_button(&airo_io_expander_key_status_record);
    #endif
    airo_io_expander_key_status_record = ~(airo_io_expander_key_status_record);
    airo_io_expander_key_status_record &= airo_io_expander_key_mask;
    DBG_LOGI(thisMOD,"io expander init done, mask = 0x%x, status = 0x%x", airo_io_expander_key_mask, airo_io_expander_key_status_record);
    #endif /* CONFIG_IO_EXPANDER_AW95124 */

    return AIRO_STATUS_SUCCESS;
}

uint32_t airo_key_read_all_key_status(uint32_t *all_key_status_0, uint32_t *all_key_status_1)
{
    #if defined(CONFIG_IO_EXPANDER_AW95124)
    uint8_t all_key_status[12] = {0};
    #else
    uint8_t all_key_status[8] = {0};
    #endif /* CONFIG_IO_EXPANDER_AW95124 */
    uint8_t idx;
    hal_gpio_data_t gpio_data = 1;
    #if defined(CONFIG_IO_EXPANDER_AW95124)
    uint32_t external_gpio_status = io_expander_mgr_get_all_input_status();
    #endif /* CONFIG_IO_EXPANDER_AW95124 */

    if (akey.cfg.key_list && akey.cfg.key_list_size <= 32){
        for (idx = 0 ; idx < akey.cfg.key_list_size ; idx ++ )
        {
            #if defined(CONFIG_IO_EXPANDER_AW95124)
            if (akey.cfg.key_list[idx] < GPIO_EXTERNAL_FLAG)
            #else
            if (akey.cfg.key_list[idx] != GPIO_UNDEFINE)
            #endif
            {
                if(hal_gpio_get_input(akey.cfg.key_list[idx], &gpio_data) == HAL_GPIO_STATUS_OK) {
                    if (gpio_data == 0){
                        air_key_all_status_update(all_key_status, akey.cfg.key_list[idx]);
                        gpio_level_record &= ~(0x01 << idx);
                    }
                    else{
                        gpio_level_record |= (0x01 << idx);
                    }
                }
                else {
                    DBG_LOGI(thisMOD, "hal_gpio_get_input failed for idx %d", idx);
                }
            }
            #if defined(CONFIG_IO_EXPANDER_AW95124)
            else if (akey.cfg.key_list[idx] != GPIO_UNDEFINE)
            {
                if ((external_gpio_status & (0x1 << (akey.cfg.key_list[idx] - GPIO_EXTERNAL_FLAG))) == 0)
                {
                    air_key_all_status_update(all_key_status, akey.cfg.key_list[idx]);
                    gpio_level_record &= ~(0x01 << idx);
                }
                else{
                    gpio_level_record |= (0x01 << idx);
                }
            }
            #endif /* CONFIG_IO_EXPANDER_AW95124 */
        }
    }

    *all_key_status_0 = *(uint32_t*)&all_key_status[0];
    *all_key_status_1 = *(uint32_t*)&all_key_status[4];
    DBG_LOGI(thisMOD, "airo_key_read_all_key_status = 0x%08X 0x%08X, gpio_level_record = 0x%08X", *all_key_status_1, *all_key_status_0, gpio_level_record);
    return ~gpio_level_record;
}