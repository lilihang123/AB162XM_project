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

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "app_debug.h"
#include "af_framework.h"
#include "af_events_declaration.h"
#include "app_state.h"
#include "hid_scenario_dongle.h"
#include "app_acl_conn.h"
#include "app_bt_ull_conn.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_bt_conn_mag
#define thisMOD    "app_bt_conn_mag"
LOG_MODULE_REGISTER(thisMODULE);

#define APP_BT_CONN_HANDLE_MAX     (1+1)

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
app_bt_conn_handle_t app_bt_conn_handle[APP_BT_CONN_HANDLE_MAX];

/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void *app_bt_conn_manager_malloc(uint32_t size)
{
    return k_malloc(size);
}

void app_bt_conn_manager_free(void *ptr)
{
    k_free(ptr);
}

app_bt_conn_handle_t *app_bt_conn_manager_get_handle(app_bt_conn_role_t role)
{
    uint32_t i;
    app_bt_conn_handle_t *link_handle = NULL;

    /* TODO: mutex proection */
    for (i = 0; i < APP_BT_CONN_HANDLE_MAX; i++)
    {
        if (app_bt_conn_handle[i].role == APP_BT_CONN_ROLE_UNKNOWN)
        {
            memset((void *)(&(app_bt_conn_handle[i])), 0 , sizeof(app_bt_conn_handle_t));
            app_bt_conn_handle[i].role = role;
            link_handle = &(app_bt_conn_handle[i]);
            break;
        }
    }

    LOG_INF("[app_hid_dongle] bt conn manager get handle 0x%x, role %u", link_handle, role);

    return link_handle;
}

int app_bt_conn_manager_release_handle(app_bt_conn_handle_t *link_handle)
{
    LOG_INF("[app_hid_dongle] bt conn manager release handle 0x%x", link_handle);

    if (link_handle == NULL)
    {
        return -ENXIO;
    }

    /* TODO: mutex proection */
    memset((void *)link_handle, 0 , sizeof(app_bt_conn_handle_t));
    link_handle->role = APP_BT_CONN_ROLE_UNKNOWN;
    return 0;
}

int app_bt_conn_manager_set_handle_conn(app_bt_conn_handle_t *link_handle, app_bt_conn_type_t type, struct bt_conn *conn)
{
    LOG_INF("[app_hid_dongle] bt conn manager set type %u handle 0x%x conn 0x%x", type, link_handle, conn);

    if (link_handle == NULL)
    {
        return -ENXIO;
    }

    if (type == APP_BT_CONN_TYPE_ACL)
    {
        link_handle->acl_conn = conn;
    }
    else if (type == APP_BT_CONN_TYPE_ULL)
    {
        link_handle->ull_conn = conn;
    }

    return 0;
}

app_bt_conn_handle_t *app_bt_conn_manager_query_handle_by_conn(app_bt_conn_type_t type, struct bt_conn *conn)
{
    uint32_t i;
    app_bt_conn_handle_t *link_handle = NULL;

    // LOG_INF("[app_hid_dongle] bt conn manager query type %u conn 0x%x start", type, conn);

    if (conn == NULL)
    {
        return NULL;
    }

    for (i = 0; i < APP_BT_CONN_HANDLE_MAX; i++)
    {
        if ((type == APP_BT_CONN_TYPE_ACL) && (app_bt_conn_handle[i].acl_conn == conn))
        {
            link_handle = &app_bt_conn_handle[i];
            break;
        }
        else if ((type == APP_BT_CONN_TYPE_ULL) && (app_bt_conn_handle[i].ull_conn == conn))
        {
            link_handle = &app_bt_conn_handle[i];
            break;
        }
    }

    LOG_INF("[app_hid_dongle] bt conn manager query type %u handle 0x%x conn 0x%x done", type, link_handle, conn);

    return link_handle;
}

int app_bt_conn_manager_set_handle_addr(app_bt_conn_handle_t *link_handle, app_bt_conn_type_t type, bt_addr_le_t *addr)
{
    LOG_INF("[app_hid_dongle] bt conn manager set type %u handle 0x%x addr 0x%x", type, link_handle, addr);

    if ((link_handle == NULL) || (addr == NULL))
    {
        return -ENXIO;
    }

    if (type == APP_BT_CONN_TYPE_ACL)
    {
        memcpy(&(link_handle->acl_addr), addr, sizeof(bt_addr_le_t));
    }
    else if (type == APP_BT_CONN_TYPE_ULL)
    {
        memcpy(&(link_handle->ull_addr), addr, sizeof(bt_addr_le_t));
    }

    return 0;
}

int app_bt_conn_manager_set_handle_disable(app_bt_conn_handle_t *link_handle, app_bt_conn_type_t type, bool is_disable)
{
    LOG_INF("[app_hid_dongle] bt conn manager set type %u handle 0x%x disable: %d", type, link_handle, is_disable);

    if (link_handle == NULL)
    {
        return -ENXIO;
    }

    if (type == APP_BT_CONN_TYPE_ACL)
    {
        link_handle->acl_disable = is_disable;
    }
    else if (type == APP_BT_CONN_TYPE_ULL)
    {
        link_handle->ull_disable = is_disable;
    }

    return 0;
}

app_bt_conn_handle_t *app_bt_conn_manager_query_handle_by_addr(app_bt_conn_type_t type, bt_addr_le_t *addr)
{
    uint32_t i;
    app_bt_conn_handle_t *link_handle = NULL;

    LOG_INF("[app_hid_dongle] bt conn manager query type %u addr 0x%x start", type, addr);

    if (addr == NULL)
    {
        return NULL;
    }

    for (i = 0; i < APP_BT_CONN_HANDLE_MAX; i++)
    {
        if ((type == APP_BT_CONN_TYPE_ACL) && (app_bt_conn_handle[i].acl_disable == false) && (!memcmp(&(app_bt_conn_handle[i].acl_addr), addr, sizeof(bt_addr_le_t))))
        {
            link_handle = &app_bt_conn_handle[i];
            break;
        }
        else if ((type == APP_BT_CONN_TYPE_ULL) && (app_bt_conn_handle[i].ull_disable == false) && (!memcmp(&(app_bt_conn_handle[i].ull_addr), addr, sizeof(bt_addr_le_t))))
        {
            link_handle = &app_bt_conn_handle[i];
            break;
        }
    }

    LOG_INF("[app_hid_dongle] bt conn manager query type %u handle 0x%x addr 0x%x done", type, link_handle, addr);

    return link_handle;
}

app_bt_conn_handle_t *app_bt_conn_manager_query_handle_by_role(app_bt_conn_role_t role)
{
    uint32_t i;
    app_bt_conn_handle_t *link_handle = NULL;

    LOG_INF("[app_hid_dongle] bt conn manager query role %u start", role);

    for (i = 0; i < APP_BT_CONN_HANDLE_MAX; i++)
    {
        if (app_bt_conn_handle[i].role == role)
        {
            link_handle = &app_bt_conn_handle[i];
            break;
        }
    }

    LOG_INF("[app_hid_dongle] bt conn manager query role %u handle 0x%x\n done", role, link_handle);

    return link_handle;
}

int app_bt_conn_manager_set_scenario_handle(app_bt_conn_handle_t *link_handle, void *scenario_handle)
{
    if (link_handle == NULL)
    {
        return -ENXIO;
    }

    link_handle->scenario_handle = scenario_handle;

    LOG_INF("[app_hid_dongle] bt conn manager set handle 0x%x sceanrio 0x%x", link_handle, scenario_handle);

    return 0;
}

void *app_bt_conn_manager_get_scenario_handle(app_bt_conn_handle_t *link_handle)
{
    return link_handle->scenario_handle;
}

void app_bt_conn_init(void)
{
    /* ACL service init */
    app_bt_acl_connection_init();

    /* CIS service init */
    app_bt_ull_connection_init();
}
#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
