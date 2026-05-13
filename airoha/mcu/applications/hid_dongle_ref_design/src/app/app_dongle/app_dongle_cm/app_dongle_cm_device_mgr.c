
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

#include "app_dongle_cm_device_mgr.h"

#include "app_debug.h"
#include "app_dongle_event.h"
#include "app_porting.h"
#include "nvkey.h"
#include "nvkey_id_def.h"



/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG             "[APP_DONGLE][CM][DEVICE_MGR]"

#define APP_DONGLE_CM_DEVICE_INFO_LENGTH          sizeof(app_dongle_cm_device_info_t)
#define APP_DONGLE_CM_DEVICE_LIST_LENGTH          (APP_DONGLE_CM_DEVICE_INFO_LENGTH * APP_DONGLE_CM_DEVICE_LIST_MAX_NUM)

typedef enum {
    APP_DONGLE_CM_DEVICE_MGR_ACTION_ADD           = 0,
    APP_DONGLE_CM_DEVICE_MGR_ACTION_REMOVE,
    APP_DONGLE_CM_DEVICE_MGR_ACTION_CLEAR,
} app_dongle_cm_device_mgr_action_t;

static app_dongle_cm_device_info_t                app_dongle_cm_device_list[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM] = {0};



/**================================================================================*/
/**                                   Internal API                                 */
/**================================================================================*/
static void app_dongle_cm_device_mgr_print(void)
{
    for (int i = 0; i < APP_DONGLE_CM_DEVICE_LIST_MAX_NUM; i++) {
        app_dongle_cm_device_info_t item = app_dongle_cm_device_list[i];
        uint8_t *addr = item.addr;
        APPS_LOG_MSGID_I(LOG_TAG" print, [%d] addr=%d %08X%04X link_type=%d device_type=%d",
                         6, i, item.addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr),
                         item.link_type, item.device_type);
    }
}

static void app_dongle_cm_device_mgr_remove_bond_info(uint8_t addr_type, uint8_t *addr)
{

}

static void app_dongle_cm_device_mgr_save(void)
{
    nvkey_status_t status = nvkey_write_data(NVID_APP_DONGLE_CM_DEVICE_LIST,
                                             (const uint8_t *)&app_dongle_cm_device_list[0],
                                             APP_DONGLE_CM_DEVICE_LIST_LENGTH);
    APPS_LOG_MSGID_I(LOG_TAG" save, status=%d", 1, status);
}

static bool app_dongle_cm_device_mgr_add_fun(uint8_t addr_type, uint8_t *addr, uint8_t link_type, uint8_t device_type)
{
    bool duplicate = FALSE;
    int duplicate_index = -1;

    for (int i = 0; i < APP_DONGLE_CM_DEVICE_LIST_MAX_NUM; i++) {
        uint8_t *device_addr = app_dongle_cm_device_list[i].addr;
        if (memcmp(addr, device_addr, BT_ADDR_SIZE) == 0) {
            duplicate = TRUE;
            duplicate_index = i;
            if (app_dongle_cm_device_list[i].addr_type != addr_type) {
                APPS_LOG_MSGID_E(LOG_TAG" add_fun, duplicate but diff addr_type=%d->%d",
                                 2, app_dongle_cm_device_list[i].addr_type, addr_type);
                app_dongle_cm_device_list[i].addr_type = addr_type;
            }
            break;
        }
    }

    if (duplicate) {
        if (duplicate_index != 0) {
            app_dongle_cm_device_info_t temp = {0};
            memcpy(&temp, &app_dongle_cm_device_list[duplicate_index], sizeof(app_dongle_cm_device_info_t));
            for (int i = duplicate_index - 1; i >= 0; i--) {
                memcpy(&app_dongle_cm_device_list[i + 1], &app_dongle_cm_device_list[i], sizeof(app_dongle_cm_device_info_t));
            }
            memcpy(&app_dongle_cm_device_list[0], &temp, sizeof(app_dongle_cm_device_info_t));
            app_dongle_cm_device_mgr_print();
        }
        return TRUE;
    }


    //app_dongle_cm_device_mgr_print();
    uint8_t *last_device_addr = app_dongle_cm_device_list[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM - 1].addr;
    if (app_porting_bt_check_addr_valid(last_device_addr)) {
        app_dongle_cm_device_mgr_remove_bond_info(app_dongle_cm_device_list[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM - 1].addr_type,
                                                  last_device_addr);
    }

    for (int i = (APP_DONGLE_CM_DEVICE_LIST_MAX_NUM - 1 - 1); i >= 0; i--) {
        uint8_t *device_addr = app_dongle_cm_device_list[i].addr;
        if (app_porting_bt_check_addr_valid(device_addr)) {
            memcpy(&app_dongle_cm_device_list[i + 1], &app_dongle_cm_device_list[i], sizeof(app_dongle_cm_device_info_t));
        }
    }

    memset(&app_dongle_cm_device_list[0], 0, sizeof(app_dongle_cm_device_info_t));
    app_dongle_cm_device_list[0].link_type = link_type;
    app_dongle_cm_device_list[0].device_type = device_type;
    app_dongle_cm_device_list[0].addr_type = addr_type;
    memcpy(app_dongle_cm_device_list[0].addr, addr, BT_ADDR_SIZE);
    app_dongle_cm_device_list[0].reserved = 0;

    app_dongle_cm_device_mgr_print();
    return TRUE;
}

static bool app_dongle_cm_device_mgr_remove_fun(uint8_t addr_type, uint8_t *addr)
{
    bool success = FALSE;
    int index = -1;

    for (int i = 0; i < APP_DONGLE_CM_DEVICE_LIST_MAX_NUM; i++) {
        uint8_t *device_addr = app_dongle_cm_device_list[i].addr;
        if (memcmp(addr, device_addr, BT_ADDR_SIZE) == 0 && addr_type == app_dongle_cm_device_list[i].addr_type) {
            success = TRUE;
            app_dongle_cm_device_mgr_print();
            index = i;
            APPS_LOG_MSGID_W(LOG_TAG" remove_fun, [%d] addr_type=%d addr=%08X%04X",
                             4, i, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));
            app_dongle_cm_device_mgr_remove_bond_info(addr_type, addr);
            break;
        }
    }

    if (success && index >= 0) {
        for (int i = index; i <= APP_DONGLE_CM_DEVICE_LIST_MAX_NUM - 1 - 1; i++) {
            memcpy(&app_dongle_cm_device_list[i], &app_dongle_cm_device_list[i + 1], sizeof(app_dongle_cm_device_info_t));
        }
        memset(&app_dongle_cm_device_list[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM - 1], 0, sizeof(app_dongle_cm_device_info_t));
        app_dongle_cm_device_mgr_print();
    }

    return success;
}

static bool app_dongle_cm_device_mgr_operate(uint8_t action, uint8_t addr_type, uint8_t *addr, uint8_t link_type, uint8_t device_type)
{
    bool success = FALSE;
    // ToDo Switch task? if same APP task - not switch? duplicate, > 3 KB/MS
    if (action == APP_DONGLE_CM_DEVICE_MGR_ACTION_ADD || action == APP_DONGLE_CM_DEVICE_MGR_ACTION_REMOVE) {
        APPS_LOG_MSGID_I(LOG_TAG" operate, action=%d addr_type=%d addr=%08X%04X link_type=%d device_type=%d",
                         6, action, addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr), link_type, device_type);
        if (addr == NULL || !app_porting_bt_check_addr_valid(addr)) {
            goto exit;
        } else if (action == APP_DONGLE_CM_DEVICE_MGR_ACTION_ADD
                   && (link_type == APP_DONGLE_CM_LINK_TYPE_NONE || device_type == APP_DONGLE_CM_DEVICE_TYPE_NONE)) {
            goto exit;
        }
    } else if (action == APP_DONGLE_CM_DEVICE_MGR_ACTION_CLEAR) {
        APPS_LOG_MSGID_I(LOG_TAG" operate, clear", 0);
    } else {
        goto exit;
    }

    if (action == APP_DONGLE_CM_DEVICE_MGR_ACTION_ADD) {
        success = app_dongle_cm_device_mgr_add_fun(addr_type, addr, link_type, device_type);
    } else if (action == APP_DONGLE_CM_DEVICE_MGR_ACTION_REMOVE) {
        success = app_dongle_cm_device_mgr_remove_fun(addr_type, addr);
    } else if (action == APP_DONGLE_CM_DEVICE_MGR_ACTION_CLEAR) {
        memset(&app_dongle_cm_device_list[0], 0, APP_DONGLE_CM_DEVICE_LIST_LENGTH);
        success = TRUE;
    }

exit:
    if (success) {
        app_dongle_cm_device_mgr_print();
        app_dongle_cm_device_mgr_save();
    }
    return TRUE;
}

static uint8_t app_dongle_cm_device_mgr_get_num_fun(uint8_t link_type, uint8_t device_type)
{
    uint8_t num = 0;
    //app_dongle_cm_device_mgr_print();

    for (int i = 0; i < APP_DONGLE_CM_DEVICE_LIST_MAX_NUM; i++) {
        uint8_t *device_addr = app_dongle_cm_device_list[i].addr;
        if (app_porting_bt_check_addr_valid(device_addr)) {
            if (link_type != APP_DONGLE_CM_LINK_TYPE_NONE
                && device_type != APP_DONGLE_CM_DEVICE_TYPE_NONE
                && app_dongle_cm_device_list[i].link_type == link_type
                && app_dongle_cm_device_list[i].device_type == device_type) {
                num++;
            } else if (link_type != APP_DONGLE_CM_LINK_TYPE_NONE
                       && device_type == APP_DONGLE_CM_DEVICE_TYPE_NONE
                       && app_dongle_cm_device_list[i].link_type == link_type) {
                num++;
            } else if (link_type == APP_DONGLE_CM_DEVICE_TYPE_NONE
                       && device_type != APP_DONGLE_CM_DEVICE_TYPE_NONE
                       && app_dongle_cm_device_list[i].device_type == device_type) {
                num++;
            } else {
                num++;
            }
        }
    }
    return num;
}

static uint8_t app_dongle_cm_device_mgr_get_info_by_link_device_type_fun(uint8_t link_type, uint8_t device_type, app_dongle_cm_device_info_t list[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM])
{
    memset(&list[0], 0, sizeof(app_dongle_cm_device_info_t) * APP_DONGLE_CM_DEVICE_LIST_MAX_NUM);
    uint8_t num = 0;
    //app_dongle_cm_device_mgr_print();

    for (int i = 0; i < APP_DONGLE_CM_DEVICE_LIST_MAX_NUM; i++) {
        uint8_t *device_addr = app_dongle_cm_device_list[i].addr;
        if (app_porting_bt_check_addr_valid(device_addr)) {
            if (link_type != APP_DONGLE_CM_LINK_TYPE_NONE
                && device_type != APP_DONGLE_CM_DEVICE_TYPE_NONE
                && app_dongle_cm_device_list[i].link_type == link_type
                && app_dongle_cm_device_list[i].device_type == device_type) {
                memcpy(&list[num], &app_dongle_cm_device_list[i], sizeof(app_dongle_cm_device_info_t));
                num++;
            } else if (link_type != APP_DONGLE_CM_LINK_TYPE_NONE
                       && device_type == APP_DONGLE_CM_DEVICE_TYPE_NONE
                       && app_dongle_cm_device_list[i].link_type == link_type) {
                memcpy(&list[num], &app_dongle_cm_device_list[i], sizeof(app_dongle_cm_device_info_t));
                num++;
            } else if (link_type == APP_DONGLE_CM_DEVICE_TYPE_NONE
                       && device_type != APP_DONGLE_CM_DEVICE_TYPE_NONE
                       && app_dongle_cm_device_list[i].device_type == device_type) {
                memcpy(&list[num], &app_dongle_cm_device_list[i], sizeof(app_dongle_cm_device_info_t));
                num++;
            } else if (link_type == APP_DONGLE_CM_LINK_TYPE_NONE
                       && device_type == APP_DONGLE_CM_DEVICE_TYPE_NONE) {
                memcpy(&list[num], &app_dongle_cm_device_list[i], sizeof(app_dongle_cm_device_info_t));
                num++;
            }
        }
    }

    APPS_LOG_MSGID_I(LOG_TAG" get_info_by_link_device_type, link_type=%d device_type=%d num=%d", 3, link_type, device_type, num);
    for (int i = 0; i < num; i++) {
        app_dongle_cm_device_info_t item = list[i];
        uint8_t *addr = item.addr;
        APPS_LOG_MSGID_I(LOG_TAG" get_info_by_link_device_type, [%d] addr=%d %08X%04X",
                         4, i, item.addr_type, *((uint32_t *)(addr + 2)), *((uint16_t *)addr));
    }

    return num;
}

static app_dongle_cm_device_info_t *app_dongle_cm_device_mgr_get_info_by_addr(uint8_t addr_type, uint8_t *addr)
{
    app_dongle_cm_device_info_t *info = NULL;
    if (!app_porting_bt_check_addr_valid(addr)) {
        return NULL;
    }

    for (int i = 0; i < APP_DONGLE_CM_DEVICE_LIST_MAX_NUM; i++) {
        if (memcmp(app_dongle_cm_device_list[i].addr, addr, BT_ADDR_SIZE) == 0
            && app_dongle_cm_device_list[i].addr_type == addr_type) {
            info = &app_dongle_cm_device_list[i];
            break;
        }
    }
    return info;
}



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
void app_dongle_cm_device_mgr_init(void)
{
    memset(&app_dongle_cm_device_list[0], 0, APP_DONGLE_CM_DEVICE_LIST_LENGTH);
    uint32_t size = APP_DONGLE_CM_DEVICE_LIST_LENGTH;
    nvkey_status_t status = nvkey_read_data(NVID_APP_DONGLE_CM_DEVICE_LIST,
                                            (uint8_t *)&app_dongle_cm_device_list[0],
                                            &size);
    APPS_LOG_MSGID_I(LOG_TAG" init, read status=%d info_length=%d num=%d size=%d",
                     4, status, APP_DONGLE_CM_DEVICE_INFO_LENGTH, APP_DONGLE_CM_DEVICE_LIST_MAX_NUM, size);

    if (status == NVKEY_STATUS_OK && size == APP_DONGLE_CM_DEVICE_LIST_LENGTH) {
        app_dongle_cm_device_mgr_print();
    }
}

bool app_dongle_cm_device_mgr_add(uint8_t addr_type, uint8_t *addr, uint8_t link_type, uint8_t device_type)
{
    return app_dongle_cm_device_mgr_operate(APP_DONGLE_CM_DEVICE_MGR_ACTION_ADD, addr_type, addr, link_type, device_type);
}

bool app_dongle_cm_device_mgr_remove(uint8_t addr_type, uint8_t *addr)
{
    return app_dongle_cm_device_mgr_operate(APP_DONGLE_CM_DEVICE_MGR_ACTION_REMOVE, addr_type, addr,
                                            APP_DONGLE_CM_LINK_TYPE_NONE, APP_DONGLE_CM_DEVICE_TYPE_NONE);
}

bool app_dongle_cm_device_mgr_clear(void)
{
    return app_dongle_cm_device_mgr_operate(APP_DONGLE_CM_DEVICE_MGR_ACTION_CLEAR, 0, NULL,
                                            APP_DONGLE_CM_LINK_TYPE_NONE, APP_DONGLE_CM_DEVICE_TYPE_NONE);
}

uint8_t app_dongle_cm_device_mgr_get_num(void)
{
    return app_dongle_cm_device_mgr_get_num_fun(APP_DONGLE_CM_LINK_TYPE_NONE, APP_DONGLE_CM_DEVICE_TYPE_NONE);
}

uint8_t app_dongle_cm_device_mgr_get_num_by_link_type(uint8_t link_type)
{
    return app_dongle_cm_device_mgr_get_num_fun(link_type, APP_DONGLE_CM_DEVICE_TYPE_NONE);
}

uint8_t app_dongle_cm_device_mgr_get_num_by_device_type(uint8_t device_type)
{
    return app_dongle_cm_device_mgr_get_num_fun(APP_DONGLE_CM_DEVICE_TYPE_NONE, device_type);
}

uint8_t app_dongle_cm_device_mgr_get_num_by_link_device_type(uint8_t link_type, uint8_t device_type)
{
    return app_dongle_cm_device_mgr_get_num_fun(link_type, device_type);
}

uint8_t app_dongle_cm_device_mgr_get_info_by_link_device_type(uint8_t link_type, uint8_t device_type,
                                                              app_dongle_cm_device_info_t list[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM])
{
    return app_dongle_cm_device_mgr_get_info_by_link_device_type_fun(link_type, device_type, list);
}

bool app_dongle_cm_device_mgr_is_exist(uint8_t addr_type, uint8_t *addr)
{
    app_dongle_cm_device_info_t *info = app_dongle_cm_device_mgr_get_info_by_addr(addr_type, addr);
    return (info != NULL);
}

uint8_t app_dongle_cm_device_mgr_get_link_type(uint8_t addr_type, uint8_t *addr)
{
    app_dongle_cm_device_info_t *info = app_dongle_cm_device_mgr_get_info_by_addr(addr_type, addr);
    return (info != NULL ? info->link_type : APP_DONGLE_CM_LINK_TYPE_NONE);
}

uint8_t app_dongle_cm_device_mgr_get_device_type(uint8_t addr_type, uint8_t *addr)
{
    app_dongle_cm_device_info_t *info = app_dongle_cm_device_mgr_get_info_by_addr(addr_type, addr);
    return (info != NULL ? info->device_type : APP_DONGLE_CM_DEVICE_TYPE_NONE);
}