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
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#include <stdint.h>
#include "hid_key_remap.h"
#include "hid_key_remap_mouse.h"
#include "hid_key_remap_game_controller.h"

#define thisMODULE  remap
#define thisMOD    "remap"

LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
const uint8_t key_type_len_mapping_table[] = {
    /* Disable and mouse five key doesn't need */
    0, 0, 0, 0, 0, 0,

    /* REMAP_TO_KBD_KEY */
    4,

    /* REMAP_TO_REPORT_RATE_SWITCH */
    0,

    /* REMAP_TO_MACRO */
    0,      /* need more operation */

    /* REMAP_TO_FIRE_KEY */
    6,

    /* REMAP_RESERVED_FUNCTION */
    0,

    /* REMAP_TO_DPI_CONTROL */
    3,

    /* REMAP_TO_WHEEL_UP */
    0,

    /* REMAP_TO_WHEEL_DOWN */
    0,

    /* REMAP_TO_PAIRING_KEY */
    0,

    /* REMAP_TO_GAME_CONTOLLER_KEY*/
    1,

    /* REMAP_TO_LIFT_SENSITIVITY */
    1,

    /* REMAP_TO_RIGHT_SENSITIVITY */
    1,
};


#ifdef MS_KEY_REMAP_TEST
extern uint8_t s_key_remap_test_profile[KEY_REMAP_PROFILE_LEN];
extern T_KEY_REMAP_MACRO_PARAM_S macro_key_test_data;
#endif
extern uint8_t s_key_remap_default_profile[KEY_REMAP_PROFILE_LEN];
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static void hid_kr_handle_key_event(const T_KEY_REMAP_MACRO_RECORD_VER2_S *record, uint32_t *pressType, uint32_t *releaseType, uint32_t *key_code, uint8_t key_type)
{
    if(record->type == MACRO_CONSUMER_KEYCODE)
    {
        *pressType = KEY_EVENT_CSM_PRESS;
        *releaseType = KEY_EVENT_CSM_RELEASE;
        *key_code = record->consumer_key[0] | (record->consumer_key[1] << 8);
    }
    else if(record->type == MACRO_STD_KEYCODE)
    {
        *pressType = KEY_EVENT_STD_PRESS;
        *releaseType = KEY_EVENT_STD_RELEASE;
        *key_code = record->std_key;
    }
    #if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    else if(record->type == MACRO_GAME_CONTROLLER_KEY)
    {
        hid_kr_game_controller_macro_parsing(record->game_controller_key, pressType, releaseType, key_code);
    }
    #endif
    else
    {
        *pressType = KEY_EVENT_MS_PRESS;
        *releaseType = KEY_EVENT_MS_RELEASE;
        *key_code = record->type;
    }
}

static void hid_kr_handle_macro_key_event(const T_KEY_REMAP_MACRO_RECORD_VER2_S *record, T_MACRO_EVENT_S *macro_events, int *macro_idx, uint32_t temp_time) {
    uint32_t duration_time = ARR3_TO_U24(record->relative_time_in_ms);
    uint32_t pressType, releaseType;
    uint32_t key_code;

    hid_kr_handle_key_event(record, &pressType, &releaseType, &key_code, REMAP_TO_MACRO);

    DBG_LOGI(thisMOD, "macro_idx = %d, key_code = %x", *macro_idx, key_code);
    /** Standard key event: press */
    macro_events[*macro_idx].abs_time = temp_time;
    macro_events[*macro_idx].type = pressType;
    macro_events[*macro_idx].key_code = key_code;
    (*macro_idx)++;

    /** Standard key event: release */
    macro_events[*macro_idx].abs_time = temp_time + duration_time;
    macro_events[*macro_idx].type = releaseType;
    macro_events[*macro_idx].key_code = key_code;
    (*macro_idx)++;
}

static void hid_kr_change_macro_to_default(uint16_t key_idx, uint8_t *s_key_remap_profile)
{
    uint8_t *p_key_func_descrip;

    p_key_func_descrip = (uint8_t*)(&(s_key_remap_profile[key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN]));
    if((*p_key_func_descrip) == REMAP_TO_MACRO)
    {
        DBG_LOGI(thisMOD, "restore key %d to default mouse function", key_idx);
        memcpy(p_key_func_descrip, &s_key_remap_default_profile[key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN], KEY_REMAP_MAX_FUNC_DESC_LEN);
        hid_common_clear_key_remap_data(key_idx);
    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
        hid_key_remap_mouse_remap_enable_clear(key_idx);
    #elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        hid_kr_game_controller_remap_enable_clear(key_idx);
    #endif
    }
}

static void hid_key_remap_delete_nvkey(const uint8_t macro_name[], uint8_t name_len, uint8_t *modify_profile, uint16_t nvkey_id_start, 
                                        uint16_t nvkey_id_end, uint8_t profile_idx, uint8_t *s_key_remap_profile)
{
    uint32_t nvkey_size = KEY_REMAP_MACRO_MAX_LEN;
    nvkey_status_t nvkey_ret;
    uint8_t *setting = (uint8_t *) k_malloc(nvkey_size);

    if(setting == NULL)
    {
        assert(0 && "remapped_data alloc failed");
        return;
    }

    DBG_LOGI(thisMOD, "nvkey_id_start = %x, nvkey_id_end = %x", nvkey_id_start, nvkey_id_end);
    for(uint16_t nvkey_id = nvkey_id_start; nvkey_id < nvkey_id_end; nvkey_id++)
    {
        nvkey_size = KEY_REMAP_MACRO_MAX_LEN;
        nvkey_ret = nvkey_read_data(nvkey_id, (uint8_t *)setting, &nvkey_size);

        /* Check if the read was successful and if the data matches the macro name, then set default and delete macro*/
        if((nvkey_ret == NVKEY_STATUS_OK) && (0 == memcmp(setting, macro_name, name_len)))
        {
            DBG_LOGI(thisMOD, "restore key remap function and delete macro nvkey: 0x%02X nvkey_size: %d", nvkey_id, nvkey_size);
            uint8_t key_idx = nvkey_id - nvkey_id_start;
            if(nvkey_id < NVID_KEY_REMAP_MACRO_1_9)
            {
                hid_kr_change_macro_to_default(key_idx, s_key_remap_profile);
            }
            else if(nvkey_id < NVID_KEY_REMAP_MACRO_1_14)
            {
                hid_kr_change_macro_to_default(key_idx + MACRO_NVKEY_IDX, s_key_remap_profile);
            }
            else
            {
                hid_kr_change_macro_to_default(key_idx + MACRO_NVKEY_IDX_2, s_key_remap_profile);
            }

            nvkey_delete_data_item(nvkey_id);
            (*modify_profile)++;
        }
    }
    k_free(setting);
}
/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
uint32_t hid_key_remap_init(uint8_t profile_idx)
{
    #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
    hid_key_remap_mouse_init(profile_idx);
    #elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    hid_key_remap_game_controller_init(profile_idx);
    #endif
    return 0;
}

int hid_kr_compare_macro_by_time(const void *a, const void *b)
{
    const T_MACRO_EVENT_S *ma = (const T_MACRO_EVENT_S *)a;
    const T_MACRO_EVENT_S *mb = (const T_MACRO_EVENT_S *)b;
    if (ma->abs_time < mb->abs_time) return -1;
    if (ma->abs_time > mb->abs_time) return 1;
    return 0;
}

void hid_kr_fill_macro_data(T_HID_KEY_REMAP_S *remapped_data, uint8_t key_idx, uint8_t profile_idx)
{
    uint32_t nvkey_size = KEY_REMAP_MACRO_MAX_LEN;
    uint32_t item_num = 0;
    uint16_t nvkey_id = hid_kr_get_macro_nvkey_id(key_idx, profile_idx);
    uint8_t *setting = (uint8_t *) k_malloc(KEY_REMAP_MACRO_MAX_LEN);
    uint8_t *p = setting;
    uint8_t version = 0;

    nvkey_status_t nvkey_ret = NVKEY_STATUS_ERROR;
    if(setting == NULL)
    {
        DBG_LOGI(thisMOD, "setting is NULL");
        return;
    }
    #ifdef MS_KEY_REMAP_TEST
    memcpy(setting, &macro_key_test_data, sizeof(macro_key_test_data));
    nvkey_ret = NVKEY_STATUS_OK;
    nvkey_size = sizeof(macro_key_test_data);
    HID_SCENARIO_NVKEY_SAVE(nvkey_id, (const uint8_t*)setting, nvkey_size);
    #else
    nvkey_ret = nvkey_read_data(nvkey_id, (uint8_t *)setting, &nvkey_size);
    #endif

    if (nvkey_ret == NVKEY_STATUS_OK && nvkey_size >= KEY_REMAP_MACRO_NAME_LEN) {
        p += KEY_REMAP_MACRO_NAME_LEN;
        remapped_data->play_mode = *p;
        remapped_data->repeat_times = *(p + 1);

        if (*(p + 2) == MACRO_VERSION2) {
            if (nvkey_size >= (KEY_REMAP_MACRO_DESCRIP_LEN + 1)) {
                item_num = (nvkey_size - KEY_REMAP_MACRO_DESCRIP_LEN - 1) / KEY_REMAP_VER2_MACRO_KEY_EVENT_IN_BYTES;
                version = MACRO_VERSION2;
                p += 3;
            }
            else {
                DBG_LOGI(thisMOD, "Insufficient nvkey size for MACRO_VERSION2");
                return;
            }
        }
        #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
        else {
            if (nvkey_size >= KEY_REMAP_MACRO_DESCRIP_LEN) {
                item_num = (nvkey_size - KEY_REMAP_MACRO_DESCRIP_LEN) / KEY_REMAP_VER1_MACRO_KEY_EVENT_IN_BYTES;
                p += 2;
            }
            else {
                DBG_LOGI(thisMOD, "Insufficient nvkey size for MACRO_VERSION1");
                return;
            }
        }
        #endif /* CONFIG_AIR_PRODUCT_TYPE_MOUSE */
    }
    else {
        DBG_LOGI(thisMOD, "Failed to read nvkey data or size too small size = %d", nvkey_size);
        return;
    }

    DBG_LOGI(thisMOD, "REMAP_TO_MACRO nvkey_id = %x nvkey_size = %d, play_mode = %d, repeat_times = %d, version = %x",
             nvkey_id, nvkey_size, remapped_data->play_mode, remapped_data->repeat_times, version);

    if (nvkey_ret == NVKEY_STATUS_OK)
    {
        uint32_t temp_time = 0, macro_idx = 0;

        DBG_LOGI(thisMOD, "item_num = %d", item_num);

        remapped_data->status = MACRO_REMAP;

        /** Allocate memory for macro events (each key record may generate up to 2 events) */
        T_MACRO_EVENT_S *macro_events = (T_MACRO_EVENT_S *)
            k_malloc(KEY_REMAP_MACRO_SUPPORT_ITEM_NUM * 2 * sizeof(T_MACRO_EVENT_S));

        if(macro_events == NULL)
        {
            DBG_LOGI(thisMOD, "macro_events is NULL");
            return;
        }

        /** Step 1: Expand all macro records to event list */
        for (uint32_t i = 0; i < item_num; i++)
        {
            if(version == MACRO_VERSION2)
            {
                T_KEY_REMAP_MACRO_RECORD_VER2_S *record = (T_KEY_REMAP_MACRO_RECORD_VER2_S *)(p + i * KEY_REMAP_VER2_MACRO_KEY_EVENT_IN_BYTES);
                /** Convert 3-byte offset_time_in_ms to uint32_t */
                uint32_t offset_time = ARR3_TO_U24(record->offset_time_in_ms);
                temp_time += offset_time;
                DBG_LOGI(thisMOD, "offset = %d, record->offset_time_in_ms = %d", i * KEY_REMAP_VER2_MACRO_KEY_EVENT_IN_BYTES, offset_time);
                #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
                /** Check if this is a mouse XY event */
                if(record->type ==  MACRO_X_Y_KEYCODE)
                {
                    /** Mouse XY event only needs one event per record */
                    macro_events[macro_idx].abs_time = temp_time;
                    macro_events[macro_idx].type = KEY_EVENT_MOUSE_XY;

                    /** Unpack x, y from 3 bytes (each 12 bits) */
                    uint16_t x = (((uint16_t)record->x_y[1] & 0xF0) >> 4) | (((uint16_t)record->x_y[0]) << 4);
                    uint16_t y = ((uint16_t)record->x_y[2]) | (((uint16_t)record->x_y[1] & 0x0F) << 8);

                    macro_events[macro_idx].x_y = MACRO_XY_PACK(x, y);
                    macro_idx++;
                }
                else
                #endif  /* CONFIG_AIR_PRODUCT_TYPE_MOUSE */
                {
                    hid_kr_handle_macro_key_event(record, macro_events, &macro_idx, temp_time);
                }
            }
            #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
            else
            {
                T_KEY_REMAP_MACRO_RECORD_VER1_S *record = (T_KEY_REMAP_MACRO_RECORD_VER1_S *)(p + i * KEY_REMAP_VER1_MACRO_KEY_EVENT_IN_BYTES);
                /** Convert 3-byte offset_time_in_ms to uint32_t */
                uint32_t offset_time = ARR3_TO_U24(record->offset_time_in_ms);
                temp_time += offset_time;

                /** Check if this is a mouse XY event */
                if (record->key_code == MACRO_X_Y_KEYCODE)
                {
                    /** Mouse XY event only needs one event per record */
                    temp_time += offset_time;
                    macro_events[macro_idx].abs_time = temp_time;
                    macro_events[macro_idx].type = KEY_EVENT_MOUSE_XY;
                    /** Unpack x, y from 3 bytes (each 12 bits) */
                    uint16_t x = (((uint16_t)record->x_y[1] & 0xF0) >> 4) | (((uint16_t)record->x_y[0]) << 4);
                    uint16_t y = ((uint16_t)record->x_y[2]) | (((uint16_t)record->x_y[1] & 0x0F) << 8);
                    macro_events[macro_idx].x_y = MACRO_XY_PACK(x, y);
                    macro_idx++;
                }
                else
                {
                    /** Standard key event: press */
                    uint32_t duration_time = ARR3_TO_U24(record->relative_time_in_ms);

                    temp_time += offset_time;
                    macro_events[macro_idx].abs_time = temp_time;
                    macro_events[macro_idx].type = KEY_EVENT_STD_PRESS;
                    macro_events[macro_idx].key_code = record->key_code;
                    macro_idx++;

                    /** Standard key event: release */
                    macro_events[macro_idx].abs_time = temp_time + duration_time;
                    macro_events[macro_idx].type = KEY_EVENT_STD_RELEASE;
                    macro_events[macro_idx].key_code = record->key_code;
                    macro_idx++;
                }
            }
            #endif  /* CONFIG_AIR_PRODUCT_TYPE_MOUSE */
        }

        /** Step 2: Sort all macro events by absolute time */
        qsort(macro_events, macro_idx, sizeof(T_MACRO_EVENT_S), hid_kr_compare_macro_by_time);

        /** Step 3: Pack to remapped_data->macro[], keycode[]/x_y[] */
        temp_time = 0;
        uint32_t out_idx = 0;
        for (uint32_t i = 0; i < macro_idx; i++) {
            if (macro_events[i].type == 0) continue; /** Skip invalid events */

            uint32_t rel_time = macro_events[i].abs_time - temp_time;

            /** Pack type and relative_time into macro[] */
            remapped_data->macro[out_idx] = MACRO_PACK(macro_events[i].type, rel_time);

            #if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
            if (macro_events[i].type == KEY_EVENT_MOUSE_XY) {
                /** Pack x, y into x_y[] for mouse XY event */
                remapped_data->x_y[out_idx] = macro_events[i].x_y;
                DBG_LOGI(thisMOD, "MOUSE XY: type = %d, x = %d, y = %d, rel_time = %d",
                    MACRO_TYPE(remapped_data->macro[out_idx]),
                    MACRO_X_SIGNED(remapped_data->x_y[out_idx]),
                    MACRO_Y_SIGNED(remapped_data->x_y[out_idx]),
                    rel_time
                );
            } else
            #endif /* CONFIG_AIR_PRODUCT_TYPE_MOUSE */
            {
                /** Pack keycode into keycode[] for key event */
                remapped_data->keycode[out_idx] = macro_events[i].key_code;
                DBG_LOGI(thisMOD, "KEY: type = %d, key_code = %x, relative_time = %d",
                    MACRO_TYPE(remapped_data->macro[out_idx]),
                    remapped_data->keycode[out_idx],
                    rel_time
                );
            }
            temp_time = macro_events[i].abs_time;
            out_idx++;
        }

        /** Mark the end of macro sequence */
        remapped_data->macro[out_idx] = MACRO_PACK(KEY_EVENT_NONE, MACRO_INTERVAL);
        k_free(macro_events);
    }
    k_free(setting);
}

void hid_kr_fill_fire_data(uint8_t *s_key_remap_profile, T_HID_KEY_REMAP_S *remapped_data, uint8_t key_idx)
{
    uint32_t i = 0;
    #ifdef MS_KEY_REMAP_TEST
    uint32_t repeat_times = 3;
    uint32_t repeat_interval = 100;
    #else
    uint32_t repeat_times = s_key_remap_profile[(key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN) + 1];
    uint32_t repeat_interval = s_key_remap_profile[(key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN) + 2] * 2;
    #endif

    remapped_data->status = MACRO_REMAP;
    if(repeat_times != 0)
    {
        remapped_data->play_mode = REPEAT_SPECIFIED_TIMES;
        remapped_data->repeat_times = repeat_times;
    }
    else
    {
        remapped_data->play_mode = REPEAT_UNTIL_THE_KEY_RELEASE;
        repeat_times = 1;
    }

    uint32_t pressType, releaseType, key_code;
    uint32_t press_duration = (uint32_t)(repeat_interval * (float)(FIRE_PRESS_RELEASE_RATIO/100.0f));
    T_KEY_REMAP_FIRE_RECORD_S *fire_record = (T_KEY_REMAP_FIRE_RECORD_S *)&s_key_remap_profile[(key_idx * KEY_REMAP_MAX_FUNC_DESC_LEN) + 3];
    T_KEY_REMAP_MACRO_RECORD_VER2_S record = {0};
    record.type = fire_record->type;
    record.ms_key = fire_record->ms_key;
    hid_kr_handle_key_event(&record, &pressType, &releaseType, &key_code, REMAP_TO_FIRE_KEY);

    remapped_data->macro[i] = MACRO_PACK(
            pressType,                              /* type */
            0                                       /* relative_time */
    );
    remapped_data->keycode[i] = key_code;

    remapped_data->macro[i+1] = MACRO_PACK(
            releaseType,                            /* type */
            press_duration                          /* relative_time */
    );
    remapped_data->keycode[i+1] = key_code;

    remapped_data->macro[i+2] = MACRO_PACK(KEY_EVENT_NONE, repeat_interval - press_duration); /* Macro End */
    DBG_LOGI(thisMOD, "REMAP_TO_FIRE_KEY  repeat_time = %d, repeat_interval = %d, pressType = %d, key_code = %x, press_duration = %d", repeat_times, repeat_interval, pressType, key_code, press_duration);
}

void hid_kr_fill_kb_data(uint8_t *p_key_func_descrip, T_HID_KEY_REMAP_S *remapped_data)
{
    uint16_t csm_key_code = *(p_key_func_descrip + 1) | (*(p_key_func_descrip + 2) << 8);
    if(csm_key_code == 0x0)
    {
        remapped_data->status = REMAP_KB_STD;
        /* This means that it is not possible to respond to the situation
        * where two physical keys are mapped to keyboard key functions and
        * the two physical keys are pressed at the same time. */
        remapped_data->item = *(p_key_func_descrip + 4) | (*(p_key_func_descrip + 3) << 8);
    } 
    else 
    {
        remapped_data->status = REMAP_KB_CONSUMER;
        remapped_data->item = csm_key_code;
    }
}

/* Key remap macro nvkey id */
uint32_t hid_kr_get_macro_nvkey_id(uint8_t key_idx, uint8_t profile_idx)
{
    /* key 1~8 macro nvkey */
    const uint16_t macro_nvkey_id_start[MAX_PROFILE_COUNT] = {
        NVID_KEY_REMAP_MACRO_1_1,
        NVID_KEY_REMAP_MACRO_2_1,
        NVID_KEY_REMAP_MACRO_3_1,
        NVID_KEY_REMAP_MACRO_4_1,
    };
    /* key 9~ macro nvkey */
    const uint16_t macro_nvkey_id_key_9_start[MAX_PROFILE_COUNT] = {
        NVID_KEY_REMAP_MACRO_1_9,
        NVID_KEY_REMAP_MACRO_2_9,
        NVID_KEY_REMAP_MACRO_3_9,
        NVID_KEY_REMAP_MACRO_4_9,
    };

    /* key 14~ macro nvkey */
    const uint16_t macro_nvkey_id_key_14_start[MAX_PROFILE_COUNT] = {
        NVID_KEY_REMAP_MACRO_1_14,
        NVID_KEY_REMAP_MACRO_2_14,
        NVID_KEY_REMAP_MACRO_3_14,
        NVID_KEY_REMAP_MACRO_4_14,
    };

    uint16_t nvkey_id;

    if(key_idx < MACRO_NVKEY_IDX)
    {
        nvkey_id = macro_nvkey_id_start[profile_idx] + key_idx;
    }
    else if(key_idx < MACRO_NVKEY_IDX_2)
    {
        nvkey_id = macro_nvkey_id_key_9_start[profile_idx] + key_idx - MACRO_NVKEY_IDX;
    }
    else
    {
        nvkey_id = macro_nvkey_id_key_14_start[profile_idx] + key_idx - MACRO_NVKEY_IDX_2;
    }
    return nvkey_id;
}

/* Set key remap profile data */
uint8_t hid_key_remap_set(uint8_t key_id, KEY_REMAP_TYPE_E key_type, uint8_t *setting, uint16_t len, uint8_t *s_key_remap_profile, uint8_t profile_idx)
{
    int ret_macro = 0, ret_profile = 0;
    uint8_t result = RACE_ERRCODE_SUCCESS;

    if (key_type == REMAP_TO_MACRO)
    {
        uint16_t nvkey_id = hid_kr_get_macro_nvkey_id(key_id - 1, profile_idx);
        ret_macro = HID_SCENARIO_NVKEY_SAVE(nvkey_id, (const uint8_t*)setting, len);
        if(key_type != s_key_remap_profile[(key_id - 1) *KEY_REMAP_MAX_FUNC_DESC_LEN])
        {
            uint8_t *ptr = &(s_key_remap_profile[(key_id - 1) *KEY_REMAP_MAX_FUNC_DESC_LEN]);
            *ptr = key_type;
            ptr = &(s_key_remap_profile[0]);
            ret_profile = HID_SCENARIO_NVKEY_SAVE(NVID_KEY_REMAP_PROFILE_1 + profile_idx, (const uint8_t*)ptr, KEY_REMAP_PROFILE_LEN);
        }
    }
    else
    {
        /* Protect critical section as ISR might read profile configuration */
        uint8_t *ptr = &(s_key_remap_profile[(key_id - 1) *KEY_REMAP_MAX_FUNC_DESC_LEN]);
        *ptr = key_type;
        ++ptr;
        memset(ptr, 0x0, KEY_REMAP_MAX_FUNC_DESC_LEN - 1);

        /* If length is non-zero and not a macro type, copy setting content */
        if ((len != 0)) {
            memcpy(ptr, setting, len);
        }

        ptr = &(s_key_remap_profile[0]);
        ret_profile = HID_SCENARIO_NVKEY_SAVE(NVID_KEY_REMAP_PROFILE_1 + profile_idx, (const uint8_t*)ptr, KEY_REMAP_PROFILE_LEN);
    }

    if (ret_macro < 0 || ret_profile < 0) {
        result = RACE_ERRCODE_FAIL;
    } else {
        result = RACE_ERRCODE_SUCCESS;
    }

    return result;
}

uint32_t hid_key_remap_get(uint8_t key_id, KEY_REMAP_TYPE_E *key_type, uint8_t *setting, uint8_t *s_key_remap_profile, uint8_t profile_idx) 
{
    /* Pointer to the specific key remap profile based on key_id */
    uint8_t *ptr = &(s_key_remap_profile[(key_id - 1) * KEY_REMAP_MAX_FUNC_DESC_LEN]);
    uint32_t nvkey_len = KEY_REMAP_MACRO_MAX_LEN, len = 0;

    *key_type = (KEY_REMAP_TYPE_E)(*ptr);
    
    if (*key_type == REMAP_TO_MACRO) 
    {
        uint16_t nvkey_id = hid_kr_get_macro_nvkey_id(key_id - 1, profile_idx);
        nvkey_len = HID_SCENARIO_NVKEY_READ_DATA(nvkey_id, (void *)setting, nvkey_len);
        DBG_LOGI(thisMOD, " nvkey_len = %d, setting = %x%x%x%x", nvkey_len, setting[0], setting[1], setting[2], setting[3]);
        if (nvkey_len) {
            DBG_LOGI(thisMOD, "Get nvkey 0x%02X length %d", nvkey_id, nvkey_len);
            len = nvkey_len;
        }
    } 
    else 
    {
        /* Default case: other types of remap scenarios */
        len = key_type_len_mapping_table[*key_type];
        if (len) {
            memcpy(setting, ptr + 1, len);
        }
    }
    
    return len;
}

uint8_t hid_key_remap_delete_macro(const uint8_t macro_name[], uint8_t name_len, uint8_t profile_idx, uint8_t *s_key_remap_profile)
{
    uint16_t nvkey_id_start, nvkey_id_end;
    uint8_t modify_profile = 0;

    DBG_LOGI(thisMOD, "hid_key_remap_delete_macro macro_name[0] = %x, name_len = %d", macro_name[0], name_len);

    if(name_len > 16){
        return RACE_ERRCODE_FAIL;
    }

    nvkey_id_start = hid_kr_get_macro_nvkey_id(0, profile_idx);
    nvkey_id_end = nvkey_id_start + MACRO_NVKEY_IDX;
    hid_key_remap_delete_nvkey(macro_name, name_len, &modify_profile, nvkey_id_start, nvkey_id_end, profile_idx, s_key_remap_profile);

    nvkey_id_start = hid_kr_get_macro_nvkey_id(MACRO_NVKEY_IDX, profile_idx);
    nvkey_id_end = nvkey_id_start + KEY_NUMBER - MACRO_NVKEY_IDX;
    hid_key_remap_delete_nvkey(macro_name, name_len, &modify_profile, nvkey_id_start, nvkey_id_end, profile_idx, s_key_remap_profile);

    nvkey_id_start = hid_kr_get_macro_nvkey_id(MACRO_NVKEY_IDX_2, profile_idx);
    nvkey_id_end = nvkey_id_start + KEY_NUMBER - MACRO_NVKEY_IDX_2;
    hid_key_remap_delete_nvkey(macro_name, name_len, &modify_profile, nvkey_id_start, nvkey_id_end, profile_idx, s_key_remap_profile);

    /* If any profiles were modified, update the profile configuration */
    if(modify_profile)
    {
        nvkey_status_t nvkey_ret;
        nvkey_ret = nvkey_write_data(profile_idx + NVID_KEY_REMAP_PROFILE_1, (const uint8_t*)&(s_key_remap_profile[0]), KEY_REMAP_PROFILE_LEN);
        DBG_LOGI(thisMOD, "Update profile cfg(0x%02X) return %d", 2 , profile_idx + NVID_KEY_REMAP_MACRO_1_1, nvkey_ret);
    }

    return RACE_ERRCODE_SUCCESS;
}
#endif