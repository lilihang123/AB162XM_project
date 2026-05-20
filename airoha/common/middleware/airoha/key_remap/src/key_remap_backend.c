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

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) || defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33) || defined(AIR_KEY_REMAP_BACKEND_RISCV)
/* Includes ------------------------------------------------------------------*/
#include "key_remap_backend.h"
#include "hal_gpt.h"
#include "assert.h"
#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
#include "af_events_declaration.h"
#include "app_scenario.h"
#if defined (CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "hid_game_controller.h"
#endif /* CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER */
#endif /* CONFIG_AIR_KEY_REMAP_BACKEND_CM33 */

_Static_assert(sizeof(T_REMAP_VALUES_S) % sizeof(uint32_t) == 0, "Struct size must be multiple of 4 bytes");
/* Private define ------------------------------------------------------------*/
#define FIRE_KEY_MIN_INTERVAL_TIME    8 // ms
#define FIRE_KEY_RR_IDX_THRESHOLD     2 // ms

#define MOUSE_KEY_BITS_SIZE           5
#define MACRO_BUFFER_SIZE             2
#define GET_3BITS(val, shift)         (((val) >> (shift)) & 0x07)
#if defined (CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
#define POSTPROCESS_EVENT             0xFF
#endif
/* Private typedef -----------------------------------------------------------*/
typedef struct {
    uint32_t macro_key_idx;
    uint32_t during_macro_idx;
    uint32_t repeat_cnt;
    uint32_t macro_process_state;
    uint32_t process_state;
    uint32_t key_status_update;
    uint32_t dpi_attr;
    uint32_t key_num;
    #if defined (AIR_FN_KEY_ENABLE)
    uint32_t fn_key;
    #endif /* AIR_FN_KEY_ENABLE */
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    uint32_t remap_pairing;
    uint32_t key_remap_enable;
    uint32_t new_key;
    uint32_t last_all_key;
    #elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    uint32_t key_remap_enable[2]; /* [1] for linear LT, RT key remap*/
    uint32_t new_key[2];
    uint32_t last_all_key[2];
    uint32_t deb_cnt_for_lt;
    uint32_t deb_cnt_for_lt_deep;
    uint32_t deb_cnt_for_rt;
    uint32_t deb_cnt_for_rt_deep;
    uint32_t lt_threshold;
    uint32_t rt_threshold;
    #endif /* AIR_PRODUCT_TYPE_MOUSE */
    #if defined(AIR_WHEEL_REMAP)
    int new_z1;
    #endif /* AIR_WHEEL_REMAP */
    #if defined (CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
    uint8_t rr_idx;
    #endif /* CONFIG_AIR_KEY_REMAP_BACKEND_CM33*/
} T_HID_KEY_REMAP_CTRL_S;

/* Private macro -------------------------------------------------------------*/
#define thisMODULE kr_backend
#define thisMOD    "kr_backend"

#if defined(CORE_MCU)
LOG_MODULE_REGISTER(thisMODULE);
#else
log_create_module(kr_backend, PRINT_LEVEL_INFO);
#endif
/* Private variables ---------------------------------------------------------*/
const static uint32_t mouse_key_bits[] = 
{
    M_KEY_BIT_L,
    M_KEY_BIT_R,
    #if !defined (AIR_BASIC_LA_DEBUG)
    M_KEY_BIT_M,
    M_KEY_BIT_NK,
    M_KEY_BIT_PK,
    #endif
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    M_KEY_BIT_DPI,
    M_KEY_BIT_RR,
    M_KEY_BIT_PAIRING,
    #endif
};

static uint32_t macro_gpt_hdl = 0; 

static T_HID_KEY_REMAP_CTRL_S kr_ctrl = {0};
T_HID_KEY_REMAP_BACKEND_S macro_setting[KEY_NUMBER];
static T_REMAP_QUEUE_CTRL_S *Kr_q_Ctrl;
T_REMAP_VALUES_S macro_data = {0};
/* Public variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
ATTR_TEXT_IN_TCM
#endif
static uint32_t key_remap_combo_judgement(uint8_t key_code)
{
    switch(key_code & 0xFF) 
    {
        case KC_LSHIFT:
            return LSHIFT_VALUE_IN_COMBO;
        case KC_RSHIFT:
            return RSHIFT_VALUE_IN_COMBO;

        case KC_LCTRL:
            return LCTRL_VALUE_IN_COMBO;
        case KC_RCTRL:
            return RCTRL_VALUE_IN_COMBO;

        case KC_LALT:
            return LALT_VALUE_IN_COMBO;
        case KC_RALT:
            return RALT_VALUE_IN_COMBO;

        case KC_LGUI:
            return LWIN_VALUE_IN_COMBO;
        case KC_RGUI:
            return RWIN_VALUE_IN_COMBO;

        default:
            return false;
    }
}


/**
 * Add a key to the macro key buffer.
 * Fills the first available empty slot.
 */
#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
ATTR_TEXT_IN_TCM
#endif
static void key_remap_macro_key_press(uint32_t *macro_key, uint8_t key) 
{
    if((key & KC_LCTRL) == KC_LCTRL)
    {
        *macro_key |= key_remap_combo_judgement(key);
        return;
    }

    /* Ignore combo key */
    for (uint8_t i = 1; i <= STD_KB_NUM; i++) 
    {
        /* Calculate the pointer adjustment and bit shift for the current position */
        uint32_t *p = macro_key + ((i & 0x4) >> 2);
        uint8_t shift = (i & 0x3) << 3;
        
        /* Check if the current position is empty */
        if (((*p >> shift) & 0xFF) == 0) 
        {
            /* Place the key in the first available empty slot and exit */
            *p |= (key << shift);
            return;
        }
    }
}

/**
 * Remove a key from the macro key buffer.
 * Shifts subsequent keys forward to fill the gap.
 */
static void key_remap_macro_key_release(uint32_t *macro_key, uint8_t key)
{
    if((key & KC_LCTRL) == KC_LCTRL)
    {
        *macro_key &= ~key_remap_combo_judgement(key);;
        return;
    }

    /* Ignore combo key */
    for (uint8_t i = 1; i <= STD_KB_NUM; i++)
    {
        /* Calculate the pointer adjustment and the bit shift for the current position */
        uint32_t *p = macro_key + ((i & 0x4) >> 2);
        uint8_t shift = (i & 0x3) << 3;

        /* Check if the current position contains the key to be released */
        if (((*p >> shift) & 0xFF) == key) 
        { 
            /* If found, clear the key and start moving subsequent keys forward */
            do {
                if (i < 7) 
                { 
                    /* If not at the last position, move the next key into the current position */
                    uint8_t next_shift = ((i + 1) & 0x3) << 3;
                    uint8_t next_index = ((i + 1) & 0x4) >> 2;
                    uint8_t next_val = (macro_key[next_index] >> next_shift) & 0xFF;
                    *p = (*p & ~(0xFFu << shift)) | (next_val << shift);
                } 
                else 
                { 
                    /* If at the last position, clear it as there is no subsequent key */
                    *p &= ~(0xFFu << shift);
                }

                i++; 
                p = macro_key + ((i & 0x4) >> 2);
                shift = (i & 0x3) << 3;
            } while (i < 6);

            return;
        }
    }
}

/**
 * Insert a uint16 value into the uint32_t macro key.
 * If any 16-bit segment in macro_key is 0, the value will be placed there.
 * Otherwise, it skips to the next segment.
 */
#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
ATTR_TEXT_IN_TCM
#endif
void key_remap_csm_key_press(uint32_t *macro_key, uint16_t value) 
{
    for (int i = 0; i < CSM_KB_NUM; ++i) { // Iterate over two 16-bit segments in macro_key
        uint16_t current_value = (*macro_key >> (i * 16)) & 0xFFFF;
        if (current_value == 0) {
            *macro_key |= ((uint32_t)value << (i * 16)); // Assign the new value
            break;
        }
    }
}

/**
 * Find a uint16 value in the uint32_t macro key and set it to 0.
 * Once matched, shift higher bits down to ensure compact storage.
 */
void key_remap_csm_key_release(uint32_t *macro_key, uint16_t value)
{
    if (value == 0) return; // Do not process zero values

    for (int i = 0; i < CSM_KB_NUM; ++i) { // Iterate over two 16-bit segments in macro_key
        uint16_t current_value = (*macro_key >> (i * 16)) & 0xFFFF;
        if (current_value == value) {
            *macro_key &= ~(0xFFFF << (i * 16)); // Clear the matched segment
            break;
        }
    }

    // After clearing, shift higher bits to lower positions to maintain compactness.
    if ((*macro_key & 0xFFFF) == 0) {
        *macro_key >>= 16;
    }
}

#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
ATTR_TEXT_IN_TCM
#endif
static void key_remap_update_record(uint32_t macro_key_idx)
{
    uint32_t idx = kr_ctrl.during_macro_idx;
    macro_setting[idx].macro = hid_common->mapped_data[idx].macro[macro_key_idx];
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    if(MACRO_TYPE(macro_setting[idx].macro) == KEY_EVENT_MOUSE_XY) /* Mouse X,Y event */
    {
        macro_setting[idx].x_y = hid_common->mapped_data[idx].x_y[macro_key_idx];
    }
    else /* Keyboard or MS key */
    #endif
    {
        macro_setting[idx].keycode = hid_common->mapped_data[idx].keycode[macro_key_idx];
    }
    // HID_DBG_LOG(key_remap, "key_remap_update_record macro_key_idx = %d, idx = %d, macro_setting[idx].keycode = %x", 3, macro_key_idx, idx, macro_setting[idx].keycode);
}

/**
 * Stop macro playback and clear related state.
 * Stop the macro timer and clear all macro control variables.
 * Reset macro state for the current macro index and reset record
 */
#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
ATTR_TEXT_IN_TCM
#endif
static void key_remap_macro_stop()
{
    hal_gpt_sw_stop_timer_ms(macro_gpt_hdl); 
    kr_ctrl.repeat_cnt = 0;
    kr_ctrl.macro_key_idx = 0;
    if(kr_ctrl.during_macro_idx != KEY_NUMBER)
    {
        key_remap_update_record(0);
        macro_setting[kr_ctrl.during_macro_idx].status = MACRO_REMAP;
        kr_ctrl.during_macro_idx = KEY_NUMBER;
    }
    memset(&macro_data, 0, sizeof(macro_data));
}

#if defined(AIR_PRODUCT_TYPE_MOUSE)
static void key_remap_get_ms_x_y(uint32_t setting_idx) 
{
    uint32_t gpt_free_count = 0;
    uint32_t outgoing_x;
    uint32_t outgoing_y;
    uint32_t delta_x = ((int8_t)((GET_3BITS(gpt_free_count, 0) ^ GET_3BITS(gpt_free_count, 15)) << 5)) >> 5;
    uint32_t delta_y = ((int8_t)((GET_3BITS(gpt_free_count, 3) ^ GET_3BITS(gpt_free_count, 12)) << 5)) >> 5;

    if (setting_idx < KEY_NUMBER) 
    {
        outgoing_x = MACRO_X_SIGNED(macro_setting[setting_idx].x_y);
        if (delta_x != -4) {
            outgoing_x += delta_x;
        }

        outgoing_y = MACRO_Y_SIGNED(macro_setting[setting_idx].x_y);
        if (delta_y != -4) {
            outgoing_y += delta_y;
        }
        key_remap_xy_push(outgoing_x, outgoing_y);
    }
}
#endif

void key_remap_macro_timeout(void* user_data)
{
    uint32_t idx = kr_ctrl.during_macro_idx;
    if (idx >= KEY_NUMBER) return;

    T_HID_KEY_REMAP_BACKEND_S *setting = &macro_setting[idx];
    uint32_t while_count = 0;

    while (1)
    {
        uint32_t type = MACRO_TYPE(setting->macro);
        uint32_t relative_time;

        /* If macro sequence ends (KEY_EVENT_NONE), play the macro again or stop */
        if (type == KEY_EVENT_NONE) 
        {
            kr_ctrl.macro_key_idx = 0;

            /* If repeat times reached, stop macro */
            if (setting->play_mode == REPEAT_SPECIFIED_TIMES && kr_ctrl.repeat_cnt >= setting->repeat_times) 
            {
                key_remap_macro_stop();
                // HID_DBG_LOG(key_remap, "Stop macro due to repeat times reached", 0);
                return;
            }

            /* Continue macro and increment repeat count */
            kr_ctrl.repeat_cnt++;

            key_remap_update_record(kr_ctrl.macro_key_idx);
            relative_time = MACRO_REL_TIME(macro_setting[idx].macro);
            hal_gpt_sw_stop_timer_ms(macro_gpt_hdl);
            hal_gpt_sw_start_timer_ms(macro_gpt_hdl, relative_time, key_remap_macro_timeout, NULL);
            // HID_DBG_LOG(key_remap, "TYPE = %d, macro_key_idx=%d, relative_time=%d",
            //            4, type, kr_ctrl.macro_key_idx, relative_time);
            // HID_DBG_LOG(key_remap, "repeat_cnt=%d repeat_times=%d", 3, kr_ctrl.repeat_cnt, setting->repeat_times);
            return;
        }

        #if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
        unsigned int lock = irq_lock();
        #endif /* CONFIG_AIR_KEY_REMAP_BACKEND_CM33 */

        #if defined(AIR_PRODUCT_TYPE_MOUSE)
        if(type == KEY_EVENT_MOUSE_XY)
        {
            key_remap_get_ms_x_y(idx);
        }
        else
        #endif
        {
            switch (type) {
                case KEY_EVENT_STD_PRESS:
                    key_remap_macro_key_press(&macro_data.kb_std[0], setting->keycode);
                    break;

                case KEY_EVENT_STD_RELEASE:
                    key_remap_macro_key_release(&macro_data.kb_std[0], setting->keycode);
                    break;

                case KEY_EVENT_CSM_PRESS:
                    key_remap_csm_key_press(&macro_data.kb_consumer, setting->keycode);
                    break;

                case KEY_EVENT_CSM_RELEASE:
                    key_remap_csm_key_release(&macro_data.kb_consumer, setting->keycode);
                    break;

                case KEY_EVENT_MS_PRESS:
                case KEY_EVENT_MS_RELEASE: 
                {
                    int index = setting->keycode & 0x0F;
                    if (index < MOUSE_KEY_BITS_SIZE) {
                        if (type == KEY_EVENT_MS_PRESS) {
                            macro_data.ms_k |= mouse_key_bits[index];
                        } else {
                            macro_data.ms_k &= ~mouse_key_bits[index];
                        }
                    }
                    break;
                }

            #if defined (CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
                case KEY_EVENT_GC_KEY_PRESS:
                    macro_data.gc_k = setting->keycode;
                    break;

                case KEY_EVENT_GC_KEY_RELEASE:
                    macro_data.gc_k &= ~setting->keycode;
                    break;

                case KEY_EVENT_GC_LT_PRESS:
                    macro_data.gc_lt = setting->keycode;
                    break;

                case KEY_EVENT_GC_LT_RELEASE:
                    macro_data.gc_lt = 0;
                    break;

                case KEY_EVENT_GC_RT_PRESS:
                    macro_data.gc_rt = setting->keycode;
                    break;

                case KEY_EVENT_GC_RT_RELEASE:
                    macro_data.gc_rt = 0;
                    break;
            #endif

                default:
                    break;
            }
        }

        #if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
        irq_unlock(lock);
        #endif

        kr_ctrl.macro_key_idx++;
        key_remap_update_record(kr_ctrl.macro_key_idx);
        relative_time = MACRO_REL_TIME(macro_setting[idx].macro);
        #if !defined(CORE_MCU)
        // HID_DBG_LOG(kr_backend, "relative_time = %d", 1, relative_time);
        #endif
        if (relative_time)
        {
            #if defined(AIR_KEY_REMAP_BACKEND_RISCV)
            if((hid_ctrl.rr_idx < FIRE_KEY_RR_IDX_THRESHOLD) && (relative_time < FIRE_KEY_MIN_INTERVAL_TIME))
            {
                relative_time = FIRE_KEY_MIN_INTERVAL_TIME >> hid_ctrl.rr_idx;
            }
            #else
            if((kr_ctrl.rr_idx < FIRE_KEY_RR_IDX_THRESHOLD) && (relative_time < FIRE_KEY_MIN_INTERVAL_TIME))
            {
                relative_time = FIRE_KEY_MIN_INTERVAL_TIME >> kr_ctrl.rr_idx;
            }
            #endif
            hal_gpt_sw_stop_timer_ms(macro_gpt_hdl);
            hal_gpt_sw_start_timer_ms(macro_gpt_hdl, relative_time, key_remap_macro_timeout, NULL);
            return;
        }
        else
        {
            /* If relative time is 0, continue to next macro step immediately */
            if(while_count > 10)
            {
                assert(0 && "Infinite loop detected");
            }
            while_count++;
            continue;
        }

        break;
    }
    return;
}

#if defined (CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
static void key_remap_announce_processing_event(T_HID_KEY_REMAP_STATUS_E status, uint32_t param)
{
    struct evt_key_remap_processing* event = create_evt_key_remap_processing();
    if (event){
        event->status = status;
        event->param = param;
        AF_EVT_SUBMIT(event);
    }
    if(status == POSTPROCESS_EVENT)
    {
        kr_ctrl.process_state &= ~MACRO_PROCESS;
    }
}

static bool key_remap__evt_rr_status(const struct af_evt_header *evt_header)
{
    uint32_t type = app_scenario_get_scenario_type();

    if (type == HID_SCENARIO_USB_MODE){
        kr_ctrl.rr_idx = hid_common->app.rr.rr_idx_usb;
    }
    else if(type == HID_SCENARIO_GAMING_MODE){
        kr_ctrl.rr_idx =  hid_common->app.rr.rr_idx_2_4g;
    }
    else {
        kr_ctrl.rr_idx = 0;
    }

    return AF_TRAVERSE_NEXT;
}

static bool key_remap__evt_key_remap_processing(const struct af_evt_header *evt_header)
{
    struct evt_key_remap_processing* event = (struct evt_key_remap_processing*)evt_header;
    if(event->status == POSTPROCESS_EVENT)
    {
        key_remap_backend_postprocess();
    }
    return AF_TRAVERSE_NEXT;
}
#endif
/* Public functions ---------------------------------------------------------*/
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
ATTR_TEXT_IN_TCM void key_remapping(uint32_t idx, uint32_t new_value, T_REMAP_VALUES_S *remap_values)
#elif defined(AIR_PRODUCT_TYPE_MOUSE)
void key_remapping(uint32_t idx, uint32_t new_value, T_REMAP_VALUES_S *remap_values, uint32_t last_all_key)
#endif
{
    uint32_t during_macro_idx = kr_ctrl.during_macro_idx;
    uint32_t new_key_press = 0;
    T_HID_KEY_REMAP_BACKEND_S *setting = NULL;

    /* Determine if there is a new key press for remapping */
    #if defined (AIR_PRODUCT_TYPE_MOUSE)
    if(idx <= M_KEY_PAIRING_IDX)
    #else
    if(idx < KEY_NUMBER)
    #endif
    {
        #if defined(AIR_PRODUCT_TYPE_MOUSE)
        uint32_t key_bit = mouse_key_bits[idx];
        new_key_press = (((~last_all_key & new_value) & key_bit) == key_bit);
        #elif defined (CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        uint32_t word_idx = idx >> 5;
        uint32_t bit_mask = 1U << (idx & 0x1F);
        new_key_press = (((~kr_ctrl.last_all_key[word_idx] & kr_ctrl.new_key[word_idx]) & bit_mask) == bit_mask);
        #endif
    }

    #if defined (AIR_WHEEL_REMAP)
    if(idx <= M_WHEEL_DOWN_IDX)
    #else
    if(idx < KEY_NUMBER)
    #endif
    {
        setting = &macro_setting[idx];
    }
    else
    {
        assert(0 && "key idx over range");
        return;
    }

    #if defined (AIR_WHEEL_REMAP)
    if (new_key_press || ((new_value != 0) && (idx >= M_WHEEL_UP_IDX)))
    #else
    if (new_key_press)
    #endif
    {
        /* If macro is playing and key state changed, reset macro status */
        if(macro_setting[during_macro_idx].status == MACRO_CONTINUE)
        {
            macro_setting[during_macro_idx].status = MACRO_REMAP;
        }
    }

    switch (setting->status) 
    {
        case REMAP_MS_KEY:
            remap_values->ms_k |= setting->item;
            break;

        case REMAP_KB_STD:
            uint32_t keycode = setting->item >> 8;
            remap_values->kb_std[0] |= setting->item & LSB;
            if((keycode & KC_LCTRL) == KC_LCTRL)
            {
                remap_values->kb_std[0] |= key_remap_combo_judgement(keycode);
            }
            else
            {
                key_remap_macro_key_press(&remap_values->kb_std[0], keycode);
            }
            break;

        case REMAP_KB_CONSUMER:
            key_remap_csm_key_press(&remap_values->kb_consumer, setting->item);
            break;

        case MACRO_REMAP:
            /* If this is a new key press, start or restart macro */
            if ( new_key_press
                #if defined (AIR_WHEEL_REMAP)
                || ((new_value != 0) && (idx >= M_WHEEL_UP_IDX))
                #endif
                || (kr_ctrl.macro_process_state == MACRO_RESTART)) 
            {
                if (kr_ctrl.during_macro_idx != KEY_NUMBER) {
                    kr_ctrl.macro_process_state = MACRO_STOP_TO_RESTART;
                    #if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
                    kr_ctrl.process_state |= MACRO_PROCESS;
                    #endif
                    // HID_DBG_LOG(key_remap, "MACRO_STOP_TO_RESTART", 0);
                    return;
                }

                 /* Update buffer configurations excluding mouse movement keys */
                uint32_t keycode = setting->keycode;
                switch(MACRO_TYPE(setting->macro))
                {
                    case KEY_EVENT_STD_PRESS:
                    {
                        if((keycode & KC_LCTRL) == KC_LCTRL)
                        {
                            remap_values->kb_std[0] = key_remap_combo_judgement(keycode);
                        }
                        else
                        {
                            key_remap_macro_key_press(&remap_values->kb_std[0], keycode);
                        }
                        macro_data.kb_std[0] = remap_values->kb_std[0];
                    }
                    break;

                    case KEY_EVENT_CSM_PRESS:
                    {
                        key_remap_csm_key_press(&remap_values->kb_consumer, setting->item);
                        macro_data.kb_consumer = remap_values->kb_consumer;
                    }
                    break;

                    #if defined(AIR_PRODUCT_TYPE_MOUSE)
                    case KEY_EVENT_MOUSE_XY:
                    {
                        key_remap_get_ms_x_y(idx);
                    }
                    break;
                    #endif

                    case KEY_EVENT_MS_PRESS:
                    {
                        int index = keycode & 0x0F;
                        if(index < MOUSE_KEY_BITS_SIZE)
                        {
                            remap_values->ms_k |= mouse_key_bits[index];
                            macro_data.ms_k |= mouse_key_bits[index];
                        }
                    }
                    break;

                    #if defined (CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
                    case KEY_EVENT_GC_KEY_PRESS:
                        remap_values->gc_k = keycode;
                        macro_data.gc_k |= keycode;
                    break;

                    case KEY_EVENT_GC_LT_PRESS:
                        remap_values->gc_lt = keycode;
                        macro_data.gc_lt |= keycode;
                    break;

                    case KEY_EVENT_GC_RT_PRESS:
                        remap_values->gc_rt = keycode;
                        macro_data.gc_rt |= keycode;
                    break;
                    #endif /* CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER */

                }
                kr_ctrl.during_macro_idx = idx;
                setting->status = MACRO_CONTINUE; 
                kr_ctrl.macro_process_state = MACRO_START;
                #if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
                kr_ctrl.process_state |= MACRO_PROCESS;
                #endif
            }
            break;

        #if defined (AIR_PRODUCT_TYPE_MOUSE)
        case REMAP_TO_RR:
            #if defined (AIR_WHEEL_REMAP)
            if (new_key_press || ((new_value != 0) && (idx >= M_WHEEL_UP_IDX)))
            #else
            if (new_key_press)
            #endif
            {
                kr_ctrl.process_state = SWITCH_RR;
            }
            break;

        case REMAP_TO_DPI:
            #if defined (AIR_WHEEL_REMAP)
            if (new_key_press || ((new_value != 0) && (idx >= M_WHEEL_UP_IDX)))
            #else
            if (new_key_press)
            #endif
            {
                kr_ctrl.process_state = SWITCH_DPI;
                kr_ctrl.dpi_attr = setting->item;
            }
            break;

        #if defined (AIR_WHEEL_REMAP)
        case REMAP_TO_SCROLL_UP:
            if (new_key_press || ((new_value != 0) && (idx >= M_WHEEL_UP_IDX)))
            {
                remap_values->ms_z1 = 1;
            }
            break;

        case REMAP_TO_SCROLL_DOWN:
            if (new_key_press || ((new_value != 0) && (idx >= M_WHEEL_UP_IDX)))
            {
                remap_values->ms_z1 = -1;
            }
            break;
        #endif /* AIR_WHEEL_REMAP */

        case REMAP_TO_PAIRING:
            if (new_key_press) 
            {
                kr_ctrl.process_state = PRESS_PAIRING_KEY;
            }
            else if((new_value != 0) && (idx >= M_WHEEL_UP_IDX))
            {
                kr_ctrl.process_state = WHEEL_PAIRING_KEY;
            }
            break;
        #endif /* AIR_PRODUCT_TYPE_MOUSE */

        #if defined (CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        case REMAP_GAME_CONTROLLER_KEY:
            remap_values->gc_k |= setting->item;
            break;

        case REMAP_GAME_CONTROLLER_LT:
            remap_values->gc_lt = setting->item;
            break;

        case REMAP_GAME_CONTROLLER_RT:
            remap_values->gc_rt = setting->item;
            break;

        case REMAP_LIFT_SENSITIVITY:
            if (new_key_press)
            {
                /* setting->item is precent to be set */
                game_controller_set_sensitivity(GAME_CONTROLLER_LEFT_SENSITIVITY, setting->item);
                kr_ctrl.process_state |= PRESSED_LEFT_SENITIVITY;
            }
            break;

        case REMAP_RIGHT_SENSITIVITY:
            if (new_key_press)
            {
                /* setting->item is precent to be set */
                game_controller_set_sensitivity(GAME_CONTROLLER_RIGHT_SENSITIVITY, setting->item);
                kr_ctrl.process_state |= PRESSED_RIGHT_SENITIVITY;
            }
            break;

        case REMAP_CURSOR_MODE:
        case REMAP_CHANGE_PROFILE:
        case REMAP_GYROSCOPE:
        case REMAP_COMPETITIVE_MODE:
            if (new_key_press)
            {
                key_remap_announce_processing_event(setting->status, 0);
            }
            break;
        #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

        default:
            break;
    }
}

#if defined(AIR_PRODUCT_TYPE_MOUSE)
void key_remap_backend_process()
{
    uint32_t new_key = kr_ctrl.new_key;
    uint32_t last_all_key = kr_ctrl.last_all_key;
    uint32_t during_macro_idx = kr_ctrl.during_macro_idx;
    T_REMAP_VALUES_S remap_data = {0};
    uint32_t *dst = (uint32_t *)&remap_data;
    uint32_t *src = (uint32_t *)&macro_data;
    uint32_t word_count = sizeof(T_REMAP_VALUES_S) / sizeof(uint32_t);

    for (uint32_t i = 0; i < word_count; i++) {
        dst[i] = src[i];
    }

    #if defined(AIR_WHEEL_REMAP)
    int new_z1 = kr_ctrl.new_z1;
    #endif
    #if defined(AIR_FN_KEY_ENABLE)
    uint32_t fn_key_is_pressed  = (new_key & kr_ctrl.fn_key) == kr_ctrl.fn_key;
    #endif

    /* Stop macro if play mode is REPEAT_UNTIL_ANY_KEY_PRESS and any key is pressed */
    if (during_macro_idx != KEY_NUMBER) 
    {
        if ((macro_setting[during_macro_idx].play_mode == REPEAT_UNTIL_ANY_KEY_PRESS) &&
            (new_key != last_all_key) && (new_key != 0)) 
        {
            int key_transition = last_all_key & ~new_key;
            if (key_transition == 0) {
                kr_ctrl.macro_process_state = MACRO_STOP;
                // HID_DBG_LOG(key_remap, "Stop macro due to any key press", 0);
            }
        }
    }

    /* Loop through all possible keys */
    for (int idx = 0; (idx < kr_ctrl.key_num) && (idx <= M_KEY_PAIRING_IDX); ++idx)
    {
        if (new_key & mouse_key_bits[idx])
        {
            key_remapping(idx, new_key, &remap_data, last_all_key);
        }
        else 
        {
            /* If macro is running for this key and key is released, handle stop */
            if ((during_macro_idx == idx) && (during_macro_idx < KEY_NUMBER))
            {
                if ((macro_setting[during_macro_idx].play_mode == REPEAT_UNTIL_THE_KEY_RELEASE) &&
                    (new_key != last_all_key))
                {
                    /* Stop macro when key is released */
                    kr_ctrl.macro_process_state = MACRO_STOP;
                }
            }
            else if((macro_setting[idx].status) == REMAP_TO_DPI && (last_all_key & mouse_key_bits[idx]))
            {
                /* DPI_STAGE_LOCK Stop */
                if((macro_setting[idx].item & LSB) == DPI_STAGE_LOCK)
                {
                    kr_ctrl.process_state = SWITCH_DPI_STOP;
                }
            }
            else if((kr_ctrl.process_state == UPDATE_PAIRING_KEY) && (macro_setting[idx].status == REMAP_TO_PAIRING))
            {
                kr_ctrl.process_state = STATUS_NONE;
                kr_ctrl.key_status_update = true;
            }
        }
    }

    #if defined (AIR_WHEEL_REMAP)
    int idx = (new_z1 < 0) ? M_WHEEL_DOWN_IDX : M_WHEEL_UP_IDX;
    if (new_z1)
    {
        #if defined (AIR_FN_KEY_ENABLE)
        if(fn_key_is_pressed && kr_ctrl.fn_key)
        {
            kr_ctrl.process_state = SWITCH_DPI;
            if(new_z1 < 0)
            {
                kr_ctrl.dpi_attr = DPI_STAGE_MINUS;
            }
            else if(new_z1 > 0)
            {
                kr_ctrl.dpi_attr = DPI_STAGE_PLUS;
            }
        }
        else
        #endif
        if((((kr_ctrl.key_remap_enable & WHEEL_UP_BIT) != 0) && (new_z1 > 0))||
            (((kr_ctrl.key_remap_enable & WHEEL_DOWN_BIT) != 0) && (new_z1 < 0)))
        {
            key_remapping(idx, new_z1, &remap_data, last_all_key);
        }
    }
    #endif
    
    #if defined (AIR_WHEEL_REMAP)
    key_remap_queue_push(Kr_q_Ctrl, &remap_data, new_key | new_z1);
    #else
    key_remap_queue_push(Kr_q_Ctrl, &remap_data, new_key);
    #endif

    // DPI Key
    #ifdef M_KEY_DPI
    if (((last_all_key ^ new_key) & M_KEY_BIT_DPI) &&
        (macro_setting[M_KEY_DPI_IDX].status == NO_REMAP))
    {
        kr_ctrl.key_status_update = true;
    }
    #endif
    // RR Key
    if (((last_all_key ^ new_key) & M_KEY_BIT_RR) &&
        (macro_setting[M_KEY_RR_IDX].status == NO_REMAP))
    {
        kr_ctrl.key_status_update = true;
    }

    // Pairing Key
    if ((((last_all_key ^ new_key) & M_KEY_BIT_PAIRING) &&
        (macro_setting[M_KEY_PAIRING_IDX].status == NO_REMAP)))
    {
        kr_ctrl.key_status_update = true;
    }

    // Remap to pairing Key 
    if(kr_ctrl.process_state == PRESS_PAIRING_KEY)
    {
        kr_ctrl.key_status_update = true;
        kr_ctrl.process_state = UPDATE_PAIRING_KEY;
    }

    /* Update last key status */
    kr_ctrl.last_all_key = new_key;
    // if(kr_ctrl.last_all_key || outgoing->k || new_key)
    // {
    //     HID_DBG_LOG(key_remap, "kr_ctrl.last_all_key = %x, outgoing->k = %x, new_key = %x", 3, kr_ctrl.last_all_key, outgoing->k, new_key);
    // }
}
#elif defined (CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
ATTR_TEXT_IN_TCM void key_remap_backend_process()
{
    if(!(kr_ctrl.key_remap_enable[0] || kr_ctrl.key_remap_enable[1]))
    {
        return;
    }

    uint32_t new_key_0 = kr_ctrl.new_key[0];
    uint32_t new_key_1 = kr_ctrl.new_key[1];
    uint32_t during_macro_idx = kr_ctrl.during_macro_idx;
    uint32_t last_all_key_0 = kr_ctrl.last_all_key[0];
    uint32_t last_all_key_1 = kr_ctrl.last_all_key[1];
    uint32_t released_0 = last_all_key_0 & ~new_key_0;
    uint32_t released_1 = last_all_key_1 & ~new_key_1;
    uint32_t key_status_change = ((new_key_0 != last_all_key_0) || (new_key_1 != last_all_key_1));

    T_REMAP_VALUES_S remap_data = {0};
    uint32_t *dst = (uint32_t *)&remap_data;
    uint32_t *src = (uint32_t *)&macro_data;
    uint32_t word_count = sizeof(T_REMAP_VALUES_S) / sizeof(uint32_t);

    for (uint32_t i = 0; i < word_count; i++) {
        dst[i] = src[i];
    }

    /* Stop macro if play mode is REPEAT_UNTIL_ANY_KEY_PRESS and any key is pressed */
    if (during_macro_idx != KEY_NUMBER)
    {
        if ((macro_setting[during_macro_idx].play_mode == REPEAT_UNTIL_ANY_KEY_PRESS) && key_status_change)
        {
            if (((~last_all_key_0 & new_key_0) | (~last_all_key_1 & new_key_1)) != 0) {
                kr_ctrl.macro_process_state = MACRO_STOP;
                kr_ctrl.process_state |= MACRO_PROCESS;
            }
        }
    }

    for (int word_idx = 0; word_idx < 2; word_idx++) {
        uint32_t key_bits = kr_ctrl.new_key[word_idx];
        int base_idx = word_idx << 5;
        while (key_bits) {
            int bit_idx = __builtin_ctz(key_bits);
            int idx = base_idx + bit_idx;
            key_remapping(idx, 0, &remap_data);
            key_bits &= ~(1U << bit_idx);
        }
    }

    for (int word_idx = 0; word_idx < 2; word_idx++) {
        uint32_t released = (word_idx == 0) ? released_0 : released_1;
        int base_idx = word_idx << 5;
        while (released) {
            int bit_idx = __builtin_ctz(released);
            int idx = base_idx + bit_idx;

            /* If macro is running for this key and key is released, handle stop */
            if ((during_macro_idx == idx) && (during_macro_idx < KEY_NUMBER))
            {
                if ((macro_setting[during_macro_idx].play_mode == REPEAT_UNTIL_THE_KEY_RELEASE) &&
                    key_status_change)
                {
                    /* Stop macro when key is released */
                    kr_ctrl.macro_process_state = MACRO_STOP;
                    kr_ctrl.process_state |= MACRO_PROCESS;
                }
            }
            else if((kr_ctrl.process_state & PRESSED_LEFT_SENITIVITY) && (macro_setting[idx].status == REMAP_LIFT_SENSITIVITY))
            {
                kr_ctrl.process_state &= ~PRESSED_LEFT_SENITIVITY;
                game_controller_set_sensitivity(GAME_CONTROLLER_LEFT_SENSITIVITY, JOYSTICK_DEFAULT_SENSITIVITY);
            }
            else if((kr_ctrl.process_state & PRESSED_RIGHT_SENITIVITY) && (macro_setting[idx].status == REMAP_RIGHT_SENSITIVITY))
            {
                kr_ctrl.process_state &= ~PRESSED_RIGHT_SENITIVITY;
                game_controller_set_sensitivity(GAME_CONTROLLER_RIGHT_SENSITIVITY, JOYSTICK_DEFAULT_SENSITIVITY);
            }

            released &= ~(1U << bit_idx);
        }
    }

    key_remap_queue_push(Kr_q_Ctrl, &remap_data, (new_key_0 | new_key_1));
    kr_ctrl.last_all_key[0] = new_key_0;
    kr_ctrl.last_all_key[1] = new_key_1;
    if(kr_ctrl.process_state & MACRO_PROCESS)
    {
        key_remap_announce_processing_event(POSTPROCESS_EVENT, 0);
    }
}
#endif

#if defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
ATTR_TEXT_IN_TCM
#endif /* CONFIG_AIR_KEY_REMAP_BACKEND_CM33 */
void key_remap_backend_postprocess()
{
    switch (kr_ctrl.macro_process_state)
    {
        case MACRO_START:
        {
            kr_ctrl.macro_key_idx = 1;
            kr_ctrl.repeat_cnt = 1;
            key_remap_update_record(kr_ctrl.macro_key_idx);

            uint32_t rel_time = MACRO_REL_TIME(macro_setting[kr_ctrl.during_macro_idx].macro);
            #if defined(AIR_KEY_REMAP_BACKEND_RISCV)
            if((hid_ctrl.rr_idx <= FIRE_KEY_RR_IDX_THRESHOLD) && (rel_time <= FIRE_KEY_MIN_INTERVAL_TIME))
            {
                rel_time = FIRE_KEY_MIN_INTERVAL_TIME >> hid_ctrl.rr_idx;
            }
            #else
            if((kr_ctrl.rr_idx < FIRE_KEY_RR_IDX_THRESHOLD) && (rel_time < FIRE_KEY_MIN_INTERVAL_TIME))
            {
                rel_time = FIRE_KEY_MIN_INTERVAL_TIME >> kr_ctrl.rr_idx;
            }
            #endif   
            DBG_LATENCY_H(DBG_SIGNAL_USB_TX_DONE);
            hal_gpt_sw_start_timer_ms(macro_gpt_hdl, rel_time, key_remap_macro_timeout, NULL);
            DBG_LATENCY_L(DBG_SIGNAL_USB_TX_DONE);
            kr_ctrl.macro_process_state = NONE;
        }
        break;

        case MACRO_STOP_TO_RESTART:
        {
            key_remap_macro_stop();
            kr_ctrl.macro_process_state = MACRO_RESTART;
        }
        break;

        case MACRO_STOP:
        {
            key_remap_macro_stop();
            kr_ctrl.macro_process_state = NONE;
        }
        break;

        default:
            break;
    }
}

uint32_t key_remap_get_process_status()
{
    return kr_ctrl.process_state;
}


void key_remap_state_reset()
{
    kr_ctrl.process_state = STATUS_NONE;
}

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
/* Debounce for Linear LT and RT remap */
ATTR_TEXT_IN_TCM static void key_remap_lt_rt_debounce_press(uint32_t val, uint32_t threshold, uint32_t debounce, uint32_t *debounce_cnt, uint32_t key_idx, uint32_t *val_ptr)
{
    if (val >= (threshold + debounce))
    {
        /* Set the key as pressed */
        kr_ctrl.new_key[1] |= (1U << key_idx);
        *debounce_cnt = 0;
        *val_ptr = 0;
    }
    else
    {
        /* Check if the key is already pressed */
        if ((kr_ctrl.new_key[1]) & (1U << key_idx)) {
            *val_ptr = 0;
            if ((val <= (threshold - debounce)) && (*debounce_cnt < MAX_DEBOUNCE_COUNT(kr_ctrl.rr_idx))) {
                /* Increment debounce count, when val is less than threshold - debounce */
                (*debounce_cnt)++;
            }
            else {
                /* Reset, when value is less than threshold - debounce */
                *debounce_cnt = 0;
            }
            if (*debounce_cnt >= MAX_DEBOUNCE_COUNT(kr_ctrl.rr_idx)) {
                /* Debounce count larger than debounce threshold, key released */
                kr_ctrl.new_key[1] &= ~(1U << key_idx);
                *debounce_cnt = 0;
            }
        }
        else {
            *debounce_cnt = 0;
        }
    }
}
#endif

#if defined(AIR_WHEEL_REMAP)
void key_remap_update_key_status(uint32_t new_key, int new_z1)
#elif defined(CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
ATTR_TEXT_IN_TCM void key_remap_update_key_status(uint32_t new_key)
#else
void key_remap_update_key_status(uint32_t new_key)
#endif
{
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    kr_ctrl.new_key[0] = new_key;
    uint32_t lt_rt_enable = kr_ctrl.key_remap_enable[1];

    /*Linear LT or RT */
    if(!lt_is_digital())
    {
        uint32_t lt = hid_common->hid.lt;
        if(lt_rt_enable & (0x01 << LT_LIGHT_PRESS_IDX))
        {
            hid_common->hid.lt = 0;
            key_remap_lt_rt_debounce_press(lt, kr_ctrl.lt_threshold & 0xFFFF, FIRST_DEBOUNCE, &kr_ctrl.deb_cnt_for_lt, LT_LIGHT_PRESS_IDX, &hid_common->hid.lt);
        }

        if(lt_rt_enable & (0x01 << LT_DEEP_PRESS_IDX))
        {
            key_remap_lt_rt_debounce_press(lt, (kr_ctrl.lt_threshold >> 16) & 0xFFFF, SECOND_DEBOUNCE, &kr_ctrl.deb_cnt_for_lt_deep, LT_DEEP_PRESS_IDX, &hid_common->hid.lt);
        }
    }

    if(!rt_is_digital())
    {
        uint32_t rt = hid_common->hid.rt;
        if(lt_rt_enable & (0x01 << RT_LIGHT_PRESS_IDX))
        {
            hid_common->hid.rt = 0;
            key_remap_lt_rt_debounce_press(rt, kr_ctrl.rt_threshold & 0xFFFF, FIRST_DEBOUNCE, &kr_ctrl.deb_cnt_for_rt, RT_LIGHT_PRESS_IDX, &hid_common->hid.rt);
        }

        if(lt_rt_enable & (0x01 << RT_DEEP_PRESS_IDX))
        {
            key_remap_lt_rt_debounce_press(rt, (kr_ctrl.rt_threshold >> 16) & 0xFFFF, SECOND_DEBOUNCE, &kr_ctrl.deb_cnt_for_rt_deep, RT_DEEP_PRESS_IDX, &hid_common->hid.rt);
        }
    }
    #else
    kr_ctrl.new_key = new_key;
    #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
    #if defined(AIR_WHEEL_REMAP)
    kr_ctrl.new_z1 = new_z1;
    #endif
}

#if defined(AIR_PRODUCT_TYPE_MOUSE)
uint32_t key_remap_get_dpi_attr()
{
    kr_ctrl.process_state = STATUS_NONE;
    return kr_ctrl.dpi_attr;
}

uint32_t key_remap_get_key_status(uint32_t *key_status)
{
    if(kr_ctrl.key_status_update)
    {
        *key_status =  kr_ctrl.new_key & ~(kr_ctrl.key_remap_enable & ~kr_ctrl.remap_pairing);
        kr_ctrl.key_status_update = false;
        return true;
    }
    return false;
}
#endif

void key_remap_set_queue(T_REMAP_QUEUE_CTRL_S *q_Ctrl)
{
    Kr_q_Ctrl = q_Ctrl;
}

/* Load key remap settings from share memory */
void key_remap_backend_setting()
{
    // HID_DBG_LOG(key_remap, "key_remap_backend_setting", 0);
    #if defined(AIR_FN_KEY_ENABLE)
    kr_ctrl.fn_key = hid_common->app.key_remap_fn_key;
    // HID_DBG_LOG(key_remap, "kr_ctrl.fn_key = %x", 1, kr_ctrl.fn_key);
    #endif

    for(uint32_t i = 0; i < KEY_NUMBER; i++)
    {
        hid_common_get_backend_key_remap_data(&macro_setting[i], i);
        #if !defined(CORE_MCU)
        // HID_DBG_LOG(kr_backend, "key_remap_backend_setting idx = %d, status = %d, play_mode = %d, repeat_time = %d", 4, i, 
        // macro_setting[i].status, macro_setting[i].play_mode, macro_setting[i].repeat_times);

        // HID_DBG_LOG(key_remap, "idx = %d macro = %d %02x %02x", 4, i,
        //     MACRO_REL_TIME(macro_setting[i].macro),
        //     MACRO_TYPE(macro_setting[i].macro),
        //     macro_setting[i].keycode);

        // HID_DBG_LOG(key_remap, "idx = %d macro = %d %d %d", 4, i,
        //          MACRO_REL_TIME(macro_setting[i].keycode),
        //          MACRO_X_SIGNED(macro_setting[i].keycode),
        //          MACRO_Y_SIGNED(macro_setting[i].keycode));
        #else
        // REMAP_LOGI(thisMOD, "key_remap_backend_setting idx = %d, status = %d, play_mode = %d, repeat_time = %d", i, 
        // macro_setting[i].status, macro_setting[i].play_mode, macro_setting[i].repeat_times);

        // REMAP_LOGI(thisMOD, "idx = %d macro = %d %02x %02x",  i,
        //    MACRO_REL_TIME(macro_setting[i].macro),
        //    MACRO_TYPE(macro_setting[i].macro),
        //    macro_setting[i].keycode);
        #endif
        #if defined(AIR_PRODUCT_TYPE_MOUSE)
        if(macro_setting[i].status == REMAP_TO_PAIRING)
        {
            kr_ctrl.remap_pairing |= (0x01 << i);
        }
        #endif
    }

    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    kr_ctrl.key_remap_enable = hid_common->app.key_remap_enable;
    #elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    /* lt / rt level threshold setting */
    kr_ctrl.lt_threshold = hid_common->app.linear_threshold[0] | (hid_common->app.linear_threshold[1] << 16);
    kr_ctrl.rt_threshold = hid_common->app.linear_threshold[2] | (hid_common->app.linear_threshold[3] << 16);
    kr_ctrl.key_remap_enable[0] = hid_common->app.key_remap_enable[0] & hid_common->app.key_not_remap_disable[0];
    kr_ctrl.key_remap_enable[1] = hid_common->app.key_remap_enable[1] & hid_common->app.key_not_remap_disable[1];
    #endif
}

void key_remap_backend_init()
{
    // HID_DBG_LOG(key_remap, "key_remap_init", 0);
    hal_gpt_sw_get_timer(&macro_gpt_hdl);
    key_remap_backend_setting();
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    kr_ctrl.key_num = hid_common->app.mouse_key_num;
    #elif defined (CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    kr_ctrl.key_num = hid_common->app.device_key_num;
    #endif
    kr_ctrl.during_macro_idx = KEY_NUMBER;
    // APP_LOGI(thisMOD, "kr_ctrl.key_num = %d", kr_ctrl.key_num);
}

void key_remap_backend_deinit()
{
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    kr_ctrl.last_all_key = 0;
    #elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    memset(kr_ctrl.last_all_key, 0, sizeof(kr_ctrl.last_all_key));
    #endif
    key_remap_macro_stop();
    key_remap_state_reset();
    hal_gpt_sw_free_timer(macro_gpt_hdl);
}

/*============================Application Framework============================*/
#if defined (CONFIG_AIR_KEY_REMAP_BACKEND_CM33)
AF_EVT_SUBSCRIBE_FUN_LAST(thisMODULE, evt_rr_status, key_remap__evt_rr_status);
AF_EVT_SUBSCRIBE_FUN_LAST(thisMODULE, evt_key_remap_processing, key_remap__evt_key_remap_processing);
#endif /* CONFIG_AIR_KEY_REMAP_BACKEND_CM33 */
/*=============================================================================*/

#endif /* CONFIG_AIR_KEY_REMAP_BACKEND_CM33, AIR_KEY_REMAP_BACKEND_RISCV */
#endif /*  */