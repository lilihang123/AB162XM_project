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
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include <stdint.h>
#include <stdlib.h>
#include "hid_key_remap.h"
#include "hid_key_remap_mouse.h"

#define thisMODULE  remap_m
#define thisMOD    "remap_m"

LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  macro                                                                     */
/******************************************************************************/
/* Definitions related to the range of the mouse dpi parameter. */
#define SENSOR_DPI_MIN_VALUE                    50
#define SENSOR_DPI_STEP_VALUE                   50
#define SENSOR_DPI_MAX_VALUE                    26000
/******************************************************************************/
/*  typedef enum                                                              */
/******************************************************************************/

/******************************************************************************/
/*  union definition                                                          */
/******************************************************************************/


/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/


/******************************************************************************/
/* typedef struct                                                             */
/******************************************************************************/
typedef struct{
    uint8_t profile_idx;
    uint8_t during_restore;
}T_KEY_REMAP_CTRL_S;
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
static const uint32_t mouse_key_bit[] = 
{
    KEY_BIT_DISABLE,
    M_KEY_BIT_L,
    M_KEY_BIT_R,
    M_KEY_BIT_M,
    M_KEY_BIT_NK,
    M_KEY_BIT_PK,
    M_KEY_BIT_DPI,
    M_KEY_BIT_RR,
    M_KEY_BIT_PAIRING,
    WHEEL_UP_BIT,
    WHEEL_DOWN_BIT,
};

uint8_t s_key_remap_profile[KEY_REMAP_PROFILE_LEN];

T_KEY_REMAP_CTRL_S kr_crtl;


#ifdef MS_KEY_REMAP_TEST
const uint8_t s_key_remap_test_profile[KEY_REMAP_PROFILE_LEN] = {
    REMAP_TO_MACRO, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_LEFT_KEY, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_KBD_KEY, 0x00, 0x00, 0x04, 0x00,
    REMAP_TO_KBD_KEY, 0xe9, 0x00, 0x00, 0x00,
    REMAP_TO_FIRE_KEY, 0x03, 0x2F, 0x00, 0x00,
    #if defined (CONFIG_AIR_WHEEL_REMAP)
    REMAP_TO_MIDDLE_KEY, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_DPI_CONTROL, 0x01, 0x00, 0x00, 0x00,
    #endif
};

// static T_KEY_REMAP_MACRO_PARAM_S macro_key_test_data = {
//     .name = "abc",             
//     .play_mode = 0x00,         
//     .repeat_times = 0x03,     
//     .rcds = {
//         MACRO_XY(0,   16, 0),
//         MACRO_XY(0,   16, 0),
//         MACRO_XY(50,  16, 0),
//         MACRO_XY(0,   16, 0),
//         MACRO_XY(10,   0, 16),
//         MACRO_XY(50,   0, 16),
//         MACRO_XY(100,  0, 16),
//         MACRO_XY(200,  0, 16),
//         MACRO_XY(0,   -16, 0),
//         MACRO_XY(10,  -16, 0),
//         MACRO_XY(50,  -16, 0),
//         MACRO_XY(50,  -16, 0),
//         MACRO_XY(1,     0, -16),
//         MACRO_XY(100,   0, -16),
//         MACRO_XY(0,     0, -16),
//         MACRO_XY(200,   0, -16),
//     }
// };

// static T_KEY_REMAP_MACRO_PARAM_S macro_key_test_data = {
//     .name = "abc",            
//     .play_mode = 0x00,        
//     .repeat_times = 0x03,     
//     .rcds = {
//         MACRO_KEY(0x04, 0,   100),
//         MACRO_XY(0,     10, 0),
//         MACRO_KEY(0x05, 50,  100),
//         MACRO_XY(0,     0,    10),
//         MACRO_XY(10,    10, 0),
//         MACRO_KEY(0x06, 100,  100),
//         MACRO_KEY(0x07, 100, 50),
//         MACRO_KEY(0x08, 50, 100),
//         MACRO_KEY(0x04, 0,   100),
//         MACRO_XY(10,     -10, 0),
//         MACRO_KEY(0x05, 100,  10),
//         MACRO_KEY(0x06, 50,  50),
//         MACRO_XY(1,     -10, 0),
//         MACRO_KEY(0x07, 100, 50),
//         MACRO_XY(0,     0,    -10),
//         MACRO_KEY(0x08, 200, 70),
//     }
// };
#if defined (AIR_EXPAND_MACRO)
T_KEY_REMAP_MACRO_PARAM_S macro_key_test_data = {
    .name = "abc",
    .play_mode = 0x00,    
    .repeat_times = 0x03, 
    .rcds = {
        MACRO_MS_KEY(L_KEY_KEYCODE, 50,   100, 0x00),
        MACRO_STD_KEY(MACRO_STD_KEYCODE, 150,  100, 0x04),
        MACRO_XY(250,   100,    50),
        MACRO_CSM_KEY(MACRO_CONSUMER_KEYCODE, 350,   100, 0x00E9),
    }
};
#else
T_KEY_REMAP_MACRO_PARAM_S macro_key_test_data = {
    .name = "abc",            
    .play_mode = 0x00,        
    .repeat_times = 0x03,     
    .rcds = {
        MACRO_KEY(L_KEY_KEYCODE, 50,   100),
        MACRO_KEY(0x04, 150,  100),
        MACRO_XY(250,   100,    50),
        MACRO_KEY(L_KEY_KEYCODE, 350,   100),
    }
};
#endif
#endif

const uint8_t s_key_remap_default_profile[KEY_REMAP_PROFILE_LEN] = {
    REMAP_TO_LEFT_KEY, 0x00, 0x00, 0x00, 0x00,
    #if !defined (CONFIG_AIR_HID_DEBUG_PIN)
    REMAP_TO_RIGHT_KEY, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_MIDDLE_KEY, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_FOURTH_KEY, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_FIFTH_KEY, 0x00, 0x00, 0x00, 0x00,
    #endif
    REMAP_TO_DPI_CONTROL, 0x03, 0x00, 0x00, 0x00,
    REMAP_TO_REPORT_RATE_SWITCH, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_PAIRING_KEY, 0x00, 0x00, 0x00, 0x00,
    #if defined (CONFIG_AIR_WHEEL_REMAP)
    REMAP_TO_WHEEL_UP, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_WHEEL_DOWN, 0x00, 0x00, 0x00, 0x00,
    #endif

};

#if defined (CONFIG_AIR_REMAP_FN_KEY)
const uint32_t key_remap_fn_key_default = M_KEY_BIT_NK | M_KEY_BIT_PK;
uint32_t key_remap_fn_key;
#endif
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
/* Check which keys have remap, then set the bit */
static uint32_t hid_kr_mouse_remap_enable()
{
    uint32_t key_remap_enable = 0;
    for(int idx = 0; idx < KEY_NUMBER; idx++)
    {
        if(memcmp(&s_key_remap_profile[idx * KEY_REMAP_MAX_FUNC_DESC_LEN], &s_key_remap_default_profile[idx * KEY_REMAP_MAX_FUNC_DESC_LEN], KEY_REMAP_MAX_FUNC_DESC_LEN)){
            key_remap_enable |= mouse_key_bit[idx + 1];
        }
    }

    DBG_LOGI(thisMOD, "hid_kr_mouse_remap_enable = %x", key_remap_enable);
    return key_remap_enable;
}

static uint32_t hid_kr_mouse_has_click_key(const uint8_t *key_type_array)
{
    uint32_t left_key_count = 0;
    for (uint8_t idx = 0; idx < KEY_NUMBER; idx++) {
        if (key_type_array[idx] == REMAP_TO_LEFT_KEY) {
            left_key_count++;
        }
    }
    return left_key_count;
}

static uint32_t hid_key_remap_mouse_param_check(const uint8_t *key_type_array, uint8_t key_type, uint8_t *setting, uint16_t len)
{
    uint8_t repeat_times, repeat_interval;

    /* During app key remap during_restore flow, ignore key remap setting */
    if (kr_crtl.during_restore) {
        return RACE_ERRCODE_STORAGE_READ_FAIL;
    }

    /* Check if the mouse has a click key */
    if (!hid_kr_mouse_has_click_key(key_type_array)) {
        return RACE_ERRCODE_FAIL;
    }

    /* Validate key type */
    if (key_type > REMAP_TO_PAIRING_KEY)
    {
        return RACE_ERRCODE_MORE_OPERATION;
    }

    uint8_t expected_len = key_type_len_mapping_table[key_type];
    /* Validate length, except for macro remap type */
    if ((len != expected_len) && (key_type != REMAP_TO_MACRO)) {
        return RACE_ERRCODE_FAIL;
    }

    /* Process keyboard key remap type */
    if (key_type == REMAP_TO_KBD_KEY) 
    {
        uint16_t consumer_key_code = *(uint16_t*)setting;
        uint16_t std_key_code = *(uint16_t*)(setting + 2);
        if ((consumer_key_code != 0) && (std_key_code != 0)) {
            return RACE_ERRCODE_NOT_SUPPORT;
        }
    }
    /* Process macro remap type */
    else if (key_type == REMAP_TO_MACRO) 
    {
        if(*(setting + KEY_REMAP_MACRO_DESCRIP_LEN) == MACRO_VERSION2)
        {
            /* Version E8, ignore version to check */
            len -= 1;

            /* Validate macro pattern length */
            if ((len - KEY_REMAP_MACRO_DESCRIP_LEN) % KEY_REMAP_VER2_MACRO_KEY_EVENT_IN_BYTES != 0) {
                return RACE_ERRCODE_PARAMETER_ERROR;
            }
        }
        else
        {
            /* Validate macro pattern length, Last version is 7 bytes */
            if (((len - KEY_REMAP_MACRO_DESCRIP_LEN) % KEY_REMAP_VER1_MACRO_KEY_EVENT_IN_BYTES) != 0) {
                return RACE_ERRCODE_PARAMETER_ERROR;
            }
        }

        /* NVKEY limitation and minimum macro frame constraint */
        /* 255 => NVKEY limitation
         * 25 <==> 18 + 7 => at least one macro frame
         */
        if ((len > 1024U) || (len < 25)) {
            return RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        }

        T_MACRO_PLAY_MODE_E mode = (T_MACRO_PLAY_MODE_E)(*(setting + 16U));
        repeat_times = *(setting + 17U);

        /* Validate macro play mode */
        if (mode > REPEAT_UNTIL_ANY_KEY_PRESS) {
            return RACE_ERRCODE_NOT_ALLOWED;
        }

        /* Validate repeat times based on play mode */
        if (((mode != REPEAT_SPECIFIED_TIMES) && (repeat_times != 0)) 
            || (mode == REPEAT_SPECIFIED_TIMES && repeat_times == 0)) {
            return RACE_ERRCODE_CONFLICT;
        }
    }
    /* Process DPI control remap type */
    else if (key_type == REMAP_TO_DPI_CONTROL) 
    {
        if (*setting == (uint8_t)DPI_STAGE_LOCK) 
        {
            /* Address of setting+1 may not be 2 bytes aligned */
            uint16_t dpi_lock_target = (*(setting + 1)) | (*(setting + 2) << 8);
            dpi_lock_target = (dpi_lock_target / SENSOR_DPI_STEP_VALUE) * SENSOR_DPI_STEP_VALUE;

            /* Validate DPI lock target range */
            if ((dpi_lock_target < SENSOR_DPI_MIN_VALUE) || (dpi_lock_target > SENSOR_DPI_MAX_VALUE)) {
                return RACE_ERRCODE_PARAMETER_ERROR;
            }

            *(uint8_t *)(setting + 1) = (uint8_t)(dpi_lock_target % 0x100);
            *(uint8_t *)(setting + 2) = (uint8_t)(dpi_lock_target / 0x100);
        }
    }
    /* Process fire key remap type */
    else if (key_type == REMAP_TO_FIRE_KEY) 
    {
        repeat_times = *(setting);
        repeat_interval = *(setting + 1);
        if (repeat_interval == 0)
        {
            return RACE_ERRCODE_PARAMETER_ERROR;
        }
    }

    return RACE_ERRCODE_SUCCESS;
}

#if 0
static void hid_kr_mouse_fill_fire_data(uint8_t *s_key_remap_profile, T_HID_KEY_REMAP_S *remapped_data, uint8_t key_idx)
{
    uint32_t i;
    #ifdef MS_KEY_REMAP_TEST
    uint32_t fire_repeat_times = 3;
    uint32_t fire_repeat_interval = 100;
    #else 
    uint32_t fire_repeat_times = s_key_remap_profile[(key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN) + 1];
    uint32_t fire_repeat_interval = s_key_remap_profile[(key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN) + 2];
    #endif

    remapped_data->status = MACRO_REMAP;
    if(fire_repeat_times != 0)
    {
        remapped_data->play_mode = REPEAT_SPECIFIED_TIMES;
        remapped_data->repeat_times = 1;
    }
    else
    {
        remapped_data->play_mode = REPEAT_UNTIL_THE_KEY_RELEASE;
        fire_repeat_times = 1;
    }

    for (i = 0; i < (fire_repeat_times * 2); i += 2)
    {
        /** First: Press event */
        remapped_data->macro[i] = MACRO_PACK(
            KEY_EVENT_MS_PRESS,                              /* type */
            (i != 0) ? fire_repeat_interval : 0              /* relative_time */
        );
        remapped_data->keycode[i] = L_KEY_KEYCODE;

        /** Second: Release event */
        remapped_data->macro[i+1] = MACRO_PACK(
            KEY_EVENT_MS_RELEASE,                            /* type */
            FIRE_KEY_INTERVAL                                /* relative_time */
        );
        remapped_data->keycode[i+1] = L_KEY_KEYCODE;

        DBG_LOGI(thisMOD, "key_code = %x type = %d relative_time = %d",
            remapped_data->keycode[i],
            MACRO_TYPE(remapped_data->macro[i]),
            MACRO_REL_TIME(remapped_data->macro[i])
        );
    }
    remapped_data->macro[i] = MACRO_PACK(KEY_EVENT_NONE, FIRE_KEY_INTERVAL); /* Macro End */
    DBG_LOGI(thisMOD, "REMAP_TO_FIRE_KEY  repeat_time = %d, repeat_interval = %d", fire_repeat_times, fire_repeat_interval);
}
#endif

static void hid_kr_mouse_set_mapped_data()
{
    for (uint8_t key_idx = 0; key_idx < KEY_NUMBER; key_idx++) 
    {
        T_HID_KEY_REMAP_S *remapped_data = k_malloc(sizeof(T_HID_KEY_REMAP_S));
        if (remapped_data == NULL) {
            assert(0 && "remapped_data alloc failed");
            return;
        }
        uint8_t key_type = s_key_remap_profile[key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN];
        uint8_t *p_key_func_descrip = (uint8_t*)(&(s_key_remap_profile[key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN]));

        memset(remapped_data, 0, sizeof(T_HID_KEY_REMAP_S));
        if(key_type == s_key_remap_default_profile[key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN])
        {
            remapped_data->status = NO_REMAP;
        }
        else if(key_type <= REMAP_TO_FIFTH_KEY)
        {
            remapped_data->status = REMAP_MS_KEY;
            remapped_data->item = mouse_key_bit[key_type];
        }
        else if(key_type == REMAP_TO_KBD_KEY)
        {
            hid_kr_fill_kb_data(p_key_func_descrip, remapped_data);
        }
        else if(key_type == REMAP_TO_MACRO)
        {
            hid_kr_fill_macro_data(remapped_data, key_idx, kr_crtl.profile_idx);
        }
        else if(key_type == REMAP_TO_FIRE_KEY)
        {
            hid_kr_fill_fire_data(s_key_remap_profile, remapped_data, key_idx);
        }
        else if(key_type == REMAP_TO_REPORT_RATE_SWITCH)
        {
            remapped_data->status = REMAP_TO_RR;
        }
        else if(key_type == REMAP_TO_DPI_CONTROL)
        {
            remapped_data->status = REMAP_TO_DPI;
            remapped_data->item = *(p_key_func_descrip + 1) | (*(p_key_func_descrip + 2) << 8) | (*(p_key_func_descrip + 3) << 16); /* DPI type and target value*/
            DBG_LOGI(thisMOD, "item = %d, type = %d, value = %d", remapped_data->item, *(p_key_func_descrip + 1)  , *(p_key_func_descrip + 2)|(*(p_key_func_descrip + 3) << 8));
        }
        #if defined (CONFIG_AIR_WHEEL_REMAP)
        else if(key_type == REMAP_TO_WHEEL_UP)
        {
            remapped_data->status = REMAP_TO_SCROLL_UP;
        }
        else if(key_type == REMAP_TO_WHEEL_DOWN)
        {
            remapped_data->status = REMAP_TO_SCROLL_DOWN;
        }
        #endif
        else if(key_type == REMAP_TO_PAIRING_KEY)
        {
            remapped_data->status = REMAP_TO_PAIRING;
        }
        hid_common_set_key_remap_data(remapped_data, key_idx);
        DBG_LOGI(thisMOD, "key_type = %d, key_id = %d, status = %d", key_type, key_idx ,remapped_data->status);
        k_free(remapped_data);
    }
    uint32_t key_remap_enable = hid_kr_mouse_remap_enable();
    hid_common_set_app_para(RAPA_TYPE_KEY_REMAP_ENABLE, (uint8_t*)&key_remap_enable,  sizeof(key_remap_enable));
}

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint8_t hid_key_remap_mouse_get_type(uint8_t key_idx)
{
    uint8_t type = s_key_remap_profile[key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN];
    DBG_LOGI(thisMOD, "hid_key_remap_mouse_get_type = %d", type);
    return type;
}

bool hid_key_remap_mouse_has_remap(uint8_t key_idx)
{
    return s_key_remap_profile[key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN] != s_key_remap_default_profile[key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN];
}

#if defined (CONFIG_AIR_REMAP_FN_KEY)
uint32_t hid_key_remap_mouse_set_fn_key(uint8_t fn_key)
{
    uint32_t result = RACE_ERRCODE_SUCCESS;

    key_remap_fn_key = fn_key;
    hid_common_set_app_para(RAPA_TYPE_REMAP_FN_KEY, (uint8_t*)&key_remap_fn_key,  sizeof(key_remap_fn_key));
    DBG_LOGI(thisMOD, "hid_key_remap_mouse_set_fn_key = %x", fn_key);
    
    result = HID_SCENARIO_NVKEY_SAVE(NVID_KEY_REMAP_FN_KEY_1 + kr_crtl.profile_idx, (const uint8_t*)&fn_key, sizeof(fn_key));
    if (result != RACE_ERRCODE_SUCCESS) {
        DBG_LOGI(thisMOD, "Set fn key fail and return %d", result);
        return result;
    }

    return result;
}

uint32_t hid_key_remap_mouse_get_fn_key()
{
    return key_remap_fn_key;
}
#endif

uint8_t hid_key_remap_mouse_set(uint8_t key_id, KEY_REMAP_TYPE_E key_type, uint8_t *setting, uint16_t len)
{
    uint8_t key_type_array[KEY_NUMBER];
    uint8_t result = RACE_ERRCODE_SUCCESS;

    DBG_LOGI(thisMOD, "hid_key_remap_mouse_set key_id = %d, key_type = %d in profile_%d, len = %d",key_id, key_type, kr_crtl.profile_idx, len);

    /* Get key type from s_key_remap_profile */
    for (uint8_t idx = 0; idx < KEY_NUMBER; idx++) {
        key_type_array[idx] = s_key_remap_profile[idx * KEY_REMAP_MAX_FUNC_DESC_LEN];
    }
   
    /* Set new key type for specified key_id */
    if (key_id > 0 && key_id <= KEY_NUMBER) {
    key_type_array[key_id - 1] = key_type;
    } else {
        DBG_LOGI(thisMOD, "Unknown key_id = %d", key_id);
        return RACE_ERRCODE_FAIL;
    }

    /* Check the validity of parameters */
    result = hid_key_remap_mouse_param_check(key_type_array, key_type, setting, len);

    if (result != RACE_ERRCODE_SUCCESS) {
        DBG_LOGI(thisMOD, "Set remap fail and return %d", result);
        return result;
    }

    result = hid_key_remap_set(key_id, key_type, setting, len, s_key_remap_profile, kr_crtl.profile_idx);
    hid_kr_mouse_set_mapped_data();

    return result;
}

uint32_t hid_key_remap_mouse_get(uint8_t key_id, KEY_REMAP_TYPE_E *key_type, uint8_t *setting, uint16_t report_rate) 
{
    uint32_t len = hid_key_remap_get(key_id, key_type, setting, s_key_remap_profile, kr_crtl.profile_idx);

    if (*key_type == REMAP_TO_REPORT_RATE_SWITCH) 
    {
        len = sizeof(report_rate);
        memcpy(setting, &report_rate, len);
        DBG_LOGI(thisMOD, "report_rate = %d", report_rate);
    } 

    DBG_LOGI(thisMOD, "hid_key_remap_mouse_get type = %d, key_id = %d, len = %d", *key_type, key_id, len);
    
    return len;
}

uint8_t hid_key_remap_mouse_delete_macro(const uint8_t macro_name[], uint8_t name_len)
{
    return hid_key_remap_delete_macro(macro_name, name_len, kr_crtl.profile_idx, s_key_remap_profile);
}

void hid_key_remap_mouse_remap_enable_clear(uint8_t key_idx)
{
    uint32_t key_remap_enable = hid_common->app.key_remap_enable & ~(hid_common->app.key_remap_enable & mouse_key_bit[key_idx + 1]);
    hid_common_set_app_para(RAPA_TYPE_KEY_REMAP_ENABLE, (uint8_t*)&key_remap_enable, sizeof(key_remap_enable));
}

uint8_t hid_key_remap_mouse_reload(uint8_t profile_idx, bool restore)
{
    nvkey_status_t nvkey_ret;
    uint32_t nvkey_size = sizeof(s_key_remap_profile);
    uint16_t nvkey_id = NVID_KEY_REMAP_PROFILE_1 + profile_idx;
    DBG_LOGI(thisMOD, "hid_key_remap_mouse_reload profile = %d", profile_idx);
    
    kr_crtl.during_restore = 1;
    nvkey_ret = nvkey_read_data(nvkey_id, (uint8_t*)&s_key_remap_profile, &nvkey_size);

    if ((nvkey_ret != NVKEY_STATUS_OK) || (restore == true)) 
    {
        #ifdef MS_KEY_REMAP_TEST
        memcpy(s_key_remap_profile, s_key_remap_test_profile, sizeof(s_key_remap_test_profile));
        #else
        memcpy(s_key_remap_profile, s_key_remap_default_profile, sizeof(s_key_remap_default_profile));
        #endif
        if(restore)
        {
            for(int i = 0; i < MAX_PROFILE_COUNT; i++)
            {
                nvkey_ret = nvkey_write_data(nvkey_id + i, (const uint8_t*)&s_key_remap_profile, sizeof(s_key_remap_profile));
                DBG_LOGI(thisMOD, "Save default data to nvkey of %x and return %d", nvkey_id, nvkey_ret);
            }
        }
        else
        {
            nvkey_ret = nvkey_write_data(nvkey_id, (const uint8_t*)&s_key_remap_profile, sizeof(s_key_remap_profile));
            DBG_LOGI(thisMOD, "Save default data to nvkey of %x and return %d", nvkey_id, nvkey_ret);
        }
        hid_common_clear_all_key_remap_data();
    } 
    else
    {
        if(nvkey_size != sizeof(s_key_remap_profile))
        {
            memcpy(&s_key_remap_profile[nvkey_size], &s_key_remap_default_profile[nvkey_size], sizeof(s_key_remap_profile) - nvkey_size);
            nvkey_ret = nvkey_write_data(nvkey_id, (const uint8_t*)&s_key_remap_profile, sizeof(s_key_remap_profile));
            DBG_LOGI(thisMOD, "nvkey_size != sizeof(s_key_remap_profile), save s_key_remap_profile to nvkey of %x and return %d", nvkey_id, nvkey_ret);
        }
        DBG_LOGI(thisMOD, "hid_kr_mouse_nvkey_load s_key_remap_profile from nvkey of %x ok ", nvkey_id);
    }
    kr_crtl.profile_idx = profile_idx;

    hid_kr_mouse_set_mapped_data();

    #if defined (CONFIG_AIR_REMAP_FN_KEY)
    nvkey_size = sizeof(key_remap_fn_key);
    nvkey_id = NVID_KEY_REMAP_FN_KEY_1 + profile_idx;
    nvkey_ret = nvkey_read_data(nvkey_id, (uint8_t*)&key_remap_fn_key, &nvkey_size);

    if ((nvkey_ret != NVKEY_STATUS_OK) || (restore == true)) 
    {
        key_remap_fn_key = key_remap_fn_key_default;
        nvkey_ret = nvkey_write_data(nvkey_id, (const uint8_t*)&key_remap_fn_key, sizeof(key_remap_fn_key));
        DBG_LOGI(thisMOD, "Save default data to nvkey of %x and return %d", nvkey_id, nvkey_ret);
    } 
    else
    {
        DBG_LOGI(thisMOD, "hid_kr_mouse_nvkey_load key_remap_fn_key from nvkey of %x ok ", nvkey_id);
    }
    
    hid_common_set_app_para(RAPA_TYPE_REMAP_FN_KEY, (uint8_t*)&key_remap_fn_key,  sizeof(key_remap_fn_key));
    DBG_LOGI(thisMOD, "hid_common->app.key_remap_fn_key = %x", hid_common->app.key_remap_fn_key);
    #endif

    kr_crtl.during_restore = 0;

    for (int i = 0; i < KEY_REMAP_PROFILE_LEN; ++i) {
         if ((i + 1) % KEY_REMAP_MAX_FUNC_DESC_LEN == 0 && (i >= (KEY_REMAP_MAX_FUNC_DESC_LEN - 1))) 
         {
            DBG_LOGI(thisMOD, "%d %d %d %d %d", 
                     s_key_remap_profile[i - 4],
                     s_key_remap_profile[i - 3],
                     s_key_remap_profile[i - 2],
                     s_key_remap_profile[i - 1],
                     s_key_remap_profile[i]);
        }
    }

    return RACE_ERRCODE_SUCCESS;
}

uint32_t hid_key_remap_mouse_init(uint8_t profile_idx)
{
    hid_key_remap_mouse_reload(profile_idx, false);
    return 0;
}
#endif