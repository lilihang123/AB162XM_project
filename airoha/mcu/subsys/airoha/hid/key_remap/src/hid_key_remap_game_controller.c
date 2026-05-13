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
#if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include "hid_key_remap.h"
#include "hid_key_remap_game_controller.h"

#define thisMODULE  remap_k
#define thisMOD    "remap_k"

LOG_MODULE_REGISTER(thisMODULE);

/* A/B/X/Y + Joystick buttons * 2 + LB + RB (0~7) + Menu 8 + View 9*/
typedef enum{
    GAME_CONTROLLER_KEY_A = 0,
    GAME_CONTROLLER_KEY_VIEW = 8,
    GAME_CONTROLLER_KEY_MENU,
    GAME_CONTROLLER_KEY_LT,
    GAME_CONTROLLER_KEY_RT,
}GAME_CONTROLLER_KEY_ID_E;

#define MAX_LT_RT_VALUE                 1023
/* Key up, down, left, right (12 ~ 15)*/
#define GAME_CONTROLLER_KEY_D_UP        12

#define GAME_CONTROLLER_KEY_ID_START    16
#define GAME_CONTROLLER_KEY_ID_END      25
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
typedef struct{
    uint8_t profile_idx;
    uint8_t during_restore;
}T_KEY_REMAP_CTRL_S;
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#ifdef MS_KEY_REMAP_TEST
const uint8_t s_key_remap_test_profile[KEY_REMAP_PROFILE_LEN] = {
    REMAP_TO_LEFT_KEY, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_KBD_KEY, 0x00, 0x00, 0x04, 0x00,
    REMAP_TO_KBD_KEY, 0xe9, 0x00, 0x00, 0x00,
    REMAP_TO_DISABLE, 0x03, 0x2F, 0x00, 0x00,
    REMAP_TO_MACRO, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_MIDDLE_KEY, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_DISABLE, 0x01, 0x00, 0x00, 0x00,
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00,
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00,
};

T_KEY_REMAP_MACRO_PARAM_S macro_key_test_data = {
    .name = "abc",
    .play_mode = 0x00,
    .repeat_times = 0x03,
    .version = MACRO_VERSION2,
    .rcds = {
        MACRO_MS_KEY(L_KEY_KEYCODE, 50,   100, 0x00),
        MACRO_GC_KEY(MACRO_GAME_CONTROLLER_KEY, 350,   100, 0),
        MACRO_GC_KEY(MACRO_GAME_CONTROLLER_KEY, 350,   100, 10),
        MACRO_GC_KEY(MACRO_GAME_CONTROLLER_KEY, 350,   100, 14),
    }
};
#endif

const uint8_t s_key_remap_origin_profile[KEY_REMAP_PROFILE_LEN] = {
    REMAP_TO_GAME_CONTOLLER_KEY, D_UP_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_D_UP
    REMAP_TO_GAME_CONTOLLER_KEY, D_DOWN_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_D_DOWN
    REMAP_TO_GAME_CONTOLLER_KEY, D_LEFT_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_D_LEFT
    REMAP_TO_GAME_CONTOLLER_KEY, D_RIGHT_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_D_RIGHT
    REMAP_TO_GAME_CONTOLLER_KEY, LT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_LT_SW
    REMAP_TO_GAME_CONTOLLER_KEY, RT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_RT_SW
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_LT_MODE
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_RT_MODE
    REMAP_TO_GAME_CONTOLLER_KEY, A_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_A
    REMAP_TO_GAME_CONTOLLER_KEY, B_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_B
    REMAP_TO_GAME_CONTOLLER_KEY, X_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_X
    REMAP_TO_GAME_CONTOLLER_KEY, Y_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_Y
    REMAP_TO_GAME_CONTOLLER_KEY, JOYS_L_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_JOYS_L
    REMAP_TO_GAME_CONTOLLER_KEY, JOYS_R_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_JOYS_R
    REMAP_TO_GAME_CONTOLLER_KEY, LB_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_LB
    REMAP_TO_GAME_CONTOLLER_KEY, RB_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_RB
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_HOME1
    REMAP_TO_GAME_CONTOLLER_KEY, MENU_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_MENU
    REMAP_TO_GAME_CONTOLLER_KEY, VIEW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_VIEW
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M1
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M2
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M3
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M4
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M5
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M6
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G1
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G2
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G3
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G4
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G5
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_PAIR
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_RESERVED_KEY1
    REMAP_TO_GAME_CONTOLLER_KEY, LT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_ANALOG_LT_LIGHT
    REMAP_TO_GAME_CONTOLLER_KEY, LT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_ANALOG_LT_DEEP
    REMAP_TO_GAME_CONTOLLER_KEY, RT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_ANALOG_RT_LIGHT
    REMAP_TO_GAME_CONTOLLER_KEY, RT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_ANALOG_RT_DEEP
};

const uint8_t s_key_remap_default_profile[KEY_REMAP_PROFILE_LEN] = {
    REMAP_TO_GAME_CONTOLLER_KEY, D_UP_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_D_UP
    REMAP_TO_GAME_CONTOLLER_KEY, D_DOWN_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_D_DOWN
    REMAP_TO_GAME_CONTOLLER_KEY, D_LEFT_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_D_LEFT
    REMAP_TO_GAME_CONTOLLER_KEY, D_RIGHT_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_D_RIGHT
    REMAP_TO_GAME_CONTOLLER_KEY, LT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_LT_SW
    REMAP_TO_GAME_CONTOLLER_KEY, RT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_RT_SW
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_LT_MODE
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_RT_MODE
    REMAP_TO_GAME_CONTOLLER_KEY, A_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_A
    REMAP_TO_GAME_CONTOLLER_KEY, B_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_B
    REMAP_TO_GAME_CONTOLLER_KEY, X_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_X
    REMAP_TO_GAME_CONTOLLER_KEY, Y_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_Y
    REMAP_TO_GAME_CONTOLLER_KEY, JOYS_L_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_JOYS_L
    REMAP_TO_GAME_CONTOLLER_KEY, JOYS_R_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_JOYS_R
    REMAP_TO_GAME_CONTOLLER_KEY, LB_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_LB
    REMAP_TO_GAME_CONTOLLER_KEY, RB_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_RB
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_HOME1
    REMAP_TO_GAME_CONTOLLER_KEY, MENU_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_MENU
    REMAP_TO_GAME_CONTOLLER_KEY, VIEW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_VIEW
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M1
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M2
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M3
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M4
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M5
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_M6
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G1
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G2
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G3
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G4
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_G5
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_KEY_PAIR
    REMAP_TO_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_RESERVED_KEY1
    REMAP_TO_GAME_CONTOLLER_KEY, LT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_ANALOG_LT_LIGHT
    REMAP_TO_GAME_CONTOLLER_KEY, LT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_ANALOG_LT_DEEP
    REMAP_TO_GAME_CONTOLLER_KEY, RT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_ANALOG_RT_LIGHT
    REMAP_TO_GAME_CONTOLLER_KEY, RT_SW_KEY, 0x00, 0x00, 0x00, 0x00, 0x00, // GC_ANALOG_RT_DEEP
};

static const uint32_t mouse_key_bit[] = 
{
    KEY_BIT_DISABLE,
    M_KEY_BIT_L,
    M_KEY_BIT_R,
    M_KEY_BIT_M,
    M_KEY_BIT_NK,
    M_KEY_BIT_PK,
};

uint8_t s_key_remap_profile[KEY_REMAP_PROFILE_LEN];
T_KEY_REMAP_CTRL_S kr_crtl;
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
static void hid_kr_game_controller_remap_enable()
{
    uint32_t key_remap_enable[2] = {0};
    uint32_t key_remap_not_disable[2] = {0}; /* Key doesn't remap to disable */
    for(int idx = 0; idx < KEY_NUMBER; idx++) {
        int array_idx = idx / 32;
        int bit_idx = idx % 32;
        if(memcmp(&s_key_remap_profile[idx * KEY_REMAP_MAX_FUNC_DESC_LEN], &s_key_remap_origin_profile[idx * KEY_REMAP_MAX_FUNC_DESC_LEN], KEY_REMAP_MAX_FUNC_DESC_LEN))
        {
            key_remap_enable[array_idx] |= (0x01 << bit_idx);
            key_remap_not_disable[array_idx] |= (0x01 << bit_idx);
        }
        else if(s_key_remap_default_profile[idx * KEY_REMAP_MAX_FUNC_DESC_LEN] == REMAP_TO_DISABLE)
        {
            key_remap_enable[array_idx] |= (0x01 << bit_idx);
        }
    }
    hid_common_set_app_para(RAPA_TYPE_KEY_REMAP_ENABLE, (uint8_t*)&key_remap_enable,  sizeof(key_remap_enable));
    hid_common_set_app_para(RAPA_TYPE_KEY_NOT_REMAP_DISABLE, (uint8_t*)&key_remap_not_disable,  sizeof(key_remap_not_disable));
    DBG_LOGI(thisMOD, "hid_kr_mouse_remap_enable = %x %x, disable key = %x %x", key_remap_enable[0], key_remap_enable[1], key_remap_not_disable[0], key_remap_not_disable[1]);
}

static uint32_t hid_kr_game_controller_param_check(const uint8_t *key_type_array, uint8_t key_type, uint8_t *setting, uint16_t len)
{
    uint8_t repeat_times, repeat_interval;
    
    /* During app key remap during_restore flow, ignore key remap setting */
    if (kr_crtl.during_restore) {
        return RACE_ERRCODE_STORAGE_READ_FAIL;
    }

    /* Validate key type, To do */
    if (((key_type > REMAP_TO_FIRE_KEY) && (key_type < REMAP_TO_GAME_CONTOLLER_KEY)) 
        || (key_type > REMAP_TO_COMPETITIVE_MODE) || (key_type == REMAP_TO_REPORT_RATE_SWITCH))
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
        /* Version E8, ignore version to check */
        len -= 1;

        /* Validate macro pattern length */
        if ((len - KEY_REMAP_MACRO_DESCRIP_LEN) % KEY_REMAP_VER2_MACRO_KEY_EVENT_IN_BYTES != 0) {
            return RACE_ERRCODE_PARAMETER_ERROR;
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
    /* Process game controller sensitivity */
    else if (key_type == REMAP_TO_LIFT_SENSITIVITY || key_type == REMAP_TO_RIGHT_SENSITIVITY)
    {
        if((*(uint8_t*)setting < 0) || (*(uint8_t*)setting > 100))
        {
            return RACE_ERRCODE_PARAMETER_ERROR;
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
        /* To Do check type */
    }

    return RACE_ERRCODE_SUCCESS;
}

static void hid_game_controller_fill_gc_data(uint8_t *p_key_func_descrip, T_HID_KEY_REMAP_S *remapped_data)
{
    uint8_t key_idx = *(p_key_func_descrip + 1);

    /* bits:0-7, hat_switch */
    /* bits:8-15, A/B/X/Y + Joystick buttons * 2 + LB + RB */
    /* bits:16-23, Home + Menu(Start) + View(Back) + external buttons * 5 */
    /* bits:24-31, external buttons * 8 */

    /* A/B/X/Y + Joystick buttons * 2 + LB + RB + Menu + View */
    if((key_idx >= GAME_CONTROLLER_KEY_A) && (key_idx <= GAME_CONTROLLER_KEY_MENU))
    {
        remapped_data->status = REMAP_GAME_CONTROLLER_KEY;
        if(key_idx == GAME_CONTROLLER_KEY_MENU)
        {
            remapped_data->item = 0x01 << 17;
        }
        else if(key_idx == GAME_CONTROLLER_KEY_VIEW)
        {
            remapped_data->item = 0x01 << 18;
        }
        else
        {
            remapped_data->item = 0x01 << (key_idx + 8);
        }
    }
    /* LT */
    else if(key_idx == GAME_CONTROLLER_KEY_LT)
    {
        remapped_data->status = REMAP_GAME_CONTROLLER_LT;
        remapped_data->item = MAX_LT_RT_VALUE;
    }
    /* RT */
    else if(key_idx == GAME_CONTROLLER_KEY_RT)
    {
        remapped_data->status = REMAP_GAME_CONTROLLER_RT;
        remapped_data->item = MAX_LT_RT_VALUE;
    }
    /* Key up, down, left, right */
    else
    {
        remapped_data->status = REMAP_GAME_CONTROLLER_KEY;
        remapped_data->item = 0x01 << (key_idx - GAME_CONTROLLER_KEY_D_UP);
    }
    DBG_LOGI(thisMOD, "hid_game_controller_fill_gc_data status = %d, item = %x, key_idx = %d", remapped_data->status, remapped_data->item, key_idx);
}

static void hid_kr_game_controller_set_mapped_data()
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
        if(key_type == REMAP_TO_DISABLE)
        {
            remapped_data->status = REMAP_GAME_CONTROLLER_KEY;
            remapped_data->item = KEY_BIT_DISABLE;
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
        else if(key_type == REMAP_TO_GAME_CONTOLLER_KEY)
        {
            hid_game_controller_fill_gc_data(p_key_func_descrip, remapped_data);
        }
        else if(key_type == REMAP_TO_LIFT_SENSITIVITY)
        {
            remapped_data->status = REMAP_LIFT_SENSITIVITY;
            remapped_data->item = *(p_key_func_descrip+1);
        }
        else if(key_type == REMAP_TO_RIGHT_SENSITIVITY)
        {
            remapped_data->status = REMAP_RIGHT_SENSITIVITY;
            remapped_data->item = *(p_key_func_descrip+1);
        }
        else if(key_type == REMAP_TO_MACRO)
        {
            hid_kr_fill_macro_data(remapped_data, key_idx, kr_crtl.profile_idx);
        }
        else if(key_type == REMAP_TO_FIRE_KEY)
        {
            hid_kr_fill_fire_data(s_key_remap_profile, remapped_data, key_idx);
        }
        else if(key_type == REMAP_TO_CURSOR_MODE)
        {
            remapped_data->status = REMAP_CURSOR_MODE;
        }
        else if(key_type == REMAP_TO_CHANGE_PROFILE)
        {
            remapped_data->status = REMAP_CHANGE_PROFILE;
        }
        else if(key_type == REMAP_TO_GYROSCOPE)
        {
            remapped_data->status = REMAP_GYROSCOPE;
        }
        else if(key_type == REMAP_TO_COMPETITIVE_MODE)
        {
            remapped_data->status = REMAP_COMPETITIVE_MODE;
        }

        hid_common_set_key_remap_data(remapped_data, key_idx);
        DBG_LOGI(thisMOD, "key_type = %d, key_id = %d, status = %d", key_type, key_idx ,remapped_data->status);
        k_free(remapped_data);
    }
    hid_kr_game_controller_remap_enable();
}

static void hid_kr_gc_remap_threshold_split(uint32_t threshold, uint8_t *percents)
{
    percents[0] = (threshold      ) & 0xFF; // lt_light
    percents[1] = (threshold >> 8 ) & 0xFF; // lt_deep
    percents[2] = (threshold >> 16) & 0xFF; // rt_light
    percents[3] = (threshold >> 24) & 0xFF; // rt_deep
}

static void hid_kr_gc_remap_threshold_set_to_common(uint8_t percents[4])
{
    hid_common->app.linear_threshold[0] = (uint16_t)((percents[0] * MAX_LT_RT_VALUE) / 100); // lt_light
    hid_common->app.linear_threshold[1]  = (uint16_t)((percents[1] * MAX_LT_RT_VALUE) / 100); // lt_deep
    hid_common->app.linear_threshold[2] = (uint16_t)((percents[2] * MAX_LT_RT_VALUE) / 100); // rt_light
    hid_common->app.linear_threshold[3]  = (uint16_t)((percents[3] * MAX_LT_RT_VALUE) / 100); // rt_deep
}

static uint32_t hid_kr_gc_remap_read_linear_threshold(bool restore)
{
    uint32_t threshold;
    uint32_t nvkey_size = sizeof(threshold);
    nvkey_status_t nvkey_ret = nvkey_read_data(NVID_LINEAR_REMAP_THRESHOLD_1  + kr_crtl.profile_idx, (uint8_t*)&threshold, &nvkey_size);
    if((nvkey_ret != NVKEY_STATUS_OK) || restore)
    {
        threshold = DEFAULT_LINEAR_REMAP_THRESHOLD;
        nvkey_ret = nvkey_write_data(NVID_LINEAR_REMAP_THRESHOLD_1 + kr_crtl.profile_idx, (const uint8_t*)&threshold, sizeof(threshold));
    }
    DBG_LOGI(thisMOD, "hid_kr_gc_remap_read_linear_threshold = %x, nvkey_ret = %d", threshold, nvkey_ret);
    return threshold;
}
/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void hid_kr_game_controller_macro_parsing(uint8_t key_idx, uint32_t *pressType, uint32_t *releaseType, uint32_t *item)
{
    /* bits:0-7, hat_switch */
    /* bits:8-15, A/B/X/Y + Joystick buttons * 2 + LB + RB */
    /* bits:16-23, Home + Menu(Start) + View(Back) + external buttons * 5 */
    /* bits:24-31, external buttons * 8 */

    /* A/B/X/Y + Joystick buttons * 2 + LB + RB */
    if((key_idx >= GAME_CONTROLLER_KEY_A) && (key_idx <= GAME_CONTROLLER_KEY_MENU))
    {
        *pressType = KEY_EVENT_GC_KEY_PRESS;
        *releaseType = KEY_EVENT_GC_KEY_RELEASE;
        if(key_idx == GAME_CONTROLLER_KEY_MENU)
        {
            *item = 0x01 << 17;
        }
        else if(key_idx == GAME_CONTROLLER_KEY_VIEW)
        {
            *item = 0x01 << 18;
        }
        else
        {
            *item = 0x01 << (key_idx + 8);
        }
    }
    /* LT */
    else if(key_idx == GAME_CONTROLLER_KEY_LT)
    {
        *pressType = KEY_EVENT_GC_LT_PRESS;
        *releaseType = KEY_EVENT_GC_LT_RELEASE;
        *item = MAX_LT_RT_VALUE;
    }
    /* RT */
    else if(key_idx == GAME_CONTROLLER_KEY_RT)
    {
        *pressType = KEY_EVENT_GC_RT_PRESS;
        *releaseType = KEY_EVENT_GC_RT_RELEASE;
        *item = MAX_LT_RT_VALUE;
    }
    /* Key up, down, left, right */
    else
    {
        *pressType = KEY_EVENT_GC_KEY_PRESS;
        *releaseType = KEY_EVENT_GC_KEY_RELEASE;
        *item = 0x01 << (key_idx - GAME_CONTROLLER_KEY_D_UP);
    }
    DBG_LOGI(thisMOD, "hid_game_controller_macro_parsing pressType = %d, item = %x, key_idx = %d", *pressType, *item , key_idx);
}

uint8_t hid_key_remap_game_controller_set(uint8_t key_id, KEY_REMAP_TYPE_E key_type, uint8_t *setting, uint16_t len)
{
    uint8_t key_type_array[KEY_NUMBER];
    uint8_t result = RACE_ERRCODE_SUCCESS;
    key_id = key_id - GAME_CONTROLLER_KEY_ID_START + 1;
    
    DBG_LOGI(thisMOD, "hid_key_remap_game_controller_set key_id = %d, key_type = %d in profile_%d, len = %d",key_id, key_type, kr_crtl.profile_idx, len);

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
    result = hid_kr_game_controller_param_check(key_type_array, key_type, setting, len);

    if (result != RACE_ERRCODE_SUCCESS) {
        DBG_LOGI(thisMOD, "Set remap fail and return %d", result);
        return result;
    }

    result = hid_key_remap_set(key_id, key_type, setting, len, s_key_remap_profile, kr_crtl.profile_idx);
    hid_kr_game_controller_set_mapped_data();

    return result;
}

uint32_t hid_key_remap_game_controller_get(uint8_t key_id, KEY_REMAP_TYPE_E *key_type, uint8_t *setting) 
{
    key_id = key_id - GAME_CONTROLLER_KEY_ID_START + 1;
    uint32_t len = hid_key_remap_get(key_id, key_type, setting, s_key_remap_profile, kr_crtl.profile_idx);

    DBG_LOGI(thisMOD, "hid_key_remap_game_controller_get type = %d, key_id = %d, len = %d", *key_type, key_id, len);
    
    return len;
}

uint8_t hid_key_remap_game_controller_reload(uint8_t profile_idx, bool restore)
{
    nvkey_status_t nvkey_ret;
    uint32_t threshold, nvkey_size = sizeof(s_key_remap_profile);
    uint16_t nvkey_id = NVID_KEY_REMAP_PROFILE_1 + profile_idx;
    uint8_t percents[4];
    DBG_LOGI(thisMOD, "hid_key_remap_game_controller_reload profile = %d", profile_idx);

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

    threshold = hid_kr_gc_remap_read_linear_threshold(restore);
    hid_kr_gc_remap_threshold_split(threshold, percents);
    hid_kr_gc_remap_threshold_set_to_common(percents);

    kr_crtl.profile_idx = profile_idx;
    hid_kr_game_controller_set_mapped_data();

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

uint8_t hid_kr_game_controller_delete_macro(const uint8_t macro_name[], uint8_t name_len)
{
    return hid_key_remap_delete_macro(macro_name, name_len, kr_crtl.profile_idx, s_key_remap_profile);
}

void hid_kr_game_controller_remap_enable_clear(uint8_t key_idx)
{
    int array_idx = key_idx / 32;
    int bit_idx = key_idx % 32;
    hid_common->app.key_remap_enable[array_idx] &= ~(0x01 << bit_idx);
}

/* Set linear lt/rt level threshold */
uint8_t hid_kr_gc_remap_linear_threshold_set(uint32_t threshold)
{
    uint8_t percents[4];

    hid_kr_gc_remap_threshold_split(threshold, percents);
    for (int i = 0; i < 4; ++i) {
        if (percents[i] < THRESHOLD_MIN_PERCENT || percents[i] > THRESHOLD_MAX_PERCENT) {
            return RACE_ERRCODE_PARAMETER_ERROR;
        }
    }

    hid_kr_gc_remap_threshold_set_to_common(percents);
    nvkey_status_t nvkey_ret = nvkey_write_data(NVID_LINEAR_REMAP_THRESHOLD_1 + kr_crtl.profile_idx, (const uint8_t*)&threshold, sizeof(threshold));
    DBG_LOGI(thisMOD, "Save threshold %X to nvkey of %x and return %d", threshold, NVID_LINEAR_REMAP_THRESHOLD_1 + kr_crtl.profile_idx, nvkey_ret);
    return nvkey_ret;
}

uint32_t hid_kr_gc_remap_linear_threshold_get()
{
    return hid_kr_gc_remap_read_linear_threshold(false);
}

uint32_t hid_key_remap_game_controller_init(uint8_t profile_idx)
{
    hid_key_remap_game_controller_reload(profile_idx, false);
    return 0;
}
#endif