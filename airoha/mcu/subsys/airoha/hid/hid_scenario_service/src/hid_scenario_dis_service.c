/* Copyright Statement:
 *
 * (C) 2026  Airoha Technology Corp. All rights reserved.
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
#if !defined (CONFIG_BT_DIS)

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/sys/util.h>
#include <zephyr/settings/settings.h>
#include "hid_scenario_dis_service.h"
#include <string.h>
#include "app_nvkey.h"
#include <stdint.h>

// Length definitions for each DIS string field
#define DIS_NAME_MAX_LEN     32
#define DIS_SERIAL_MAX_LEN   24
#define DIS_HW_REV_MAX_LEN   16
#define DIS_SW_REV_MAX_LEN   16

// Unified structure for all DIS info, with custom FF FF field termination
typedef struct {
    uint8_t manufacturer_name[DIS_NAME_MAX_LEN];
    uint8_t serial_number[DIS_SERIAL_MAX_LEN];
    uint8_t hw_rev_str[DIS_HW_REV_MAX_LEN];
    uint8_t sw_rev_str[DIS_SW_REV_MAX_LEN];
    uint8_t pnp_vid_src;
    uint16_t pnp_vid;
    uint16_t pnp_pid;
    uint16_t pnp_ver;
} __attribute__((packed)) dis_info_ff_t;

// Utility: find length before 0x00 (custom field ending tag)
int dis_field_buflen(const uint8_t *buf, int max) {
    for (int i = 0; i < max; ++i) {
        if (buf[i] == 0x00)
            return i;
    }
    return max;
}

// Global cache for parsed DIS values from NVKEY
static dis_info_ff_t g_dis_info;

// Default values for DIS fields (will be used when NVKEY is empty)
static const char* g_manuf_default = "airoha";
static const char* g_serial_default = "09710067104021";
static const char* g_hw_default = "5.9.2709.0";
static const char* g_sw_default = "5.9.2709.0";

// PNP default values (in binary)
static const uint8_t g_pnp_default[7] = {
    0x02,        // vid_src
    0x5E, 0x04,  // vid (0x045E)
    0x13, 0x0B,  // pid (0x0B13)
    0x09, 0x05   // ver (0x0509)
};

// Field selector for characteristic read callback
enum dis_field {
    DIS_FIELD_MANUFACTURER,
    DIS_FIELD_SERIAL,
    DIS_FIELD_HW_REV,
    DIS_FIELD_SW_REV,
    DIS_FIELD_PNP
};

//getter
static const char* get_dis_str(const char* nvkey_val, const char* conf_val, const char* default_val) {
    if (nvkey_val && nvkey_val[0])  return nvkey_val;
    if (conf_val && conf_val[0])    return conf_val;
    return default_val;
}

// PNP getter
static uint8_t get_pnp_vid_src(void) {
    if (g_dis_info.pnp_vid_src) return g_dis_info.pnp_vid_src;
    if (CONF_PNP_VID_SRC)       return (uint8_t)CONF_PNP_VID_SRC;
    return g_pnp_default[0];
}
static uint16_t get_pnp_vid(void) {
    if (g_dis_info.pnp_vid) return g_dis_info.pnp_vid;
    if (CONF_PNP_VID)       return (uint16_t)CONF_PNP_VID;
    return (g_pnp_default[2]<<8) | g_pnp_default[1];
}
static uint16_t get_pnp_pid(void) {
    if (g_dis_info.pnp_pid) return g_dis_info.pnp_pid;
    if (CONF_PNP_PID)       return (uint16_t)CONF_PNP_PID;
    return (g_pnp_default[4]<<8) | g_pnp_default[3];
}
static uint16_t get_pnp_ver(void) {
    if (g_dis_info.pnp_ver) return g_dis_info.pnp_ver;
    if (CONF_PNP_VER)       return (uint16_t)CONF_PNP_VER;
    return (g_pnp_default[6]<<8) | g_pnp_default[5];
}

// BLE characteristic read callback: parses each field from NVKEY or uses default
static ssize_t read_dis_info_ff(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf,
                            uint16_t len, uint16_t offset)
{
    enum dis_field field = (enum dis_field)(uintptr_t)attr->user_data;
    uint8_t nvkey_raw[128] = {0};
    uint32_t read_size = sizeof(nvkey_raw);
    nvkey_status_t status = nvkey_read_data(NVID_BT_DIS_SERVICE, nvkey_raw, &read_size);
    if (status != NVKEY_STATUS_OK) {
    // If read failed, clear struct to trigger default behaviors
        memset(&g_dis_info, 0x00, sizeof(g_dis_info));
    } else {
        int idx = 0, len = 0;
        len = dis_field_buflen(&nvkey_raw[idx], DIS_NAME_MAX_LEN);
        memcpy(g_dis_info.manufacturer_name, &nvkey_raw[idx], len); g_dis_info.manufacturer_name[len]=0; idx+=len+1;
        len = dis_field_buflen(&nvkey_raw[idx], DIS_SERIAL_MAX_LEN);
        memcpy(g_dis_info.serial_number, &nvkey_raw[idx], len); g_dis_info.serial_number[len]=0; idx+=len+1;
        len = dis_field_buflen(&nvkey_raw[idx], DIS_HW_REV_MAX_LEN);
        memcpy(g_dis_info.hw_rev_str, &nvkey_raw[idx], len); g_dis_info.hw_rev_str[len]=0; idx+=len+1;
        len = dis_field_buflen(&nvkey_raw[idx], DIS_SW_REV_MAX_LEN);
        memcpy(g_dis_info.sw_rev_str, &nvkey_raw[idx], len); g_dis_info.sw_rev_str[len]=0; idx+=len+1;

        if(idx+7<=read_size) {
            g_dis_info.pnp_vid_src = nvkey_raw[idx];
            g_dis_info.pnp_vid = nvkey_raw[idx+1] | (nvkey_raw[idx+2]<<8);
            g_dis_info.pnp_pid = nvkey_raw[idx+3] | (nvkey_raw[idx+4]<<8);
            g_dis_info.pnp_ver = nvkey_raw[idx+5] | (nvkey_raw[idx+6]<<8);
        }
    }

    // Parse field info as requested by BLE characteristic registration
    switch (field) {
        case DIS_FIELD_MANUFACTURER: {
            const char* out = get_dis_str(g_dis_info.manufacturer_name, CONF_MANUF, g_manuf_default);
            int outlen = strlen(out);
            return bt_gatt_attr_read(conn, attr, buf, len, offset, out, outlen);
        }
        case DIS_FIELD_SERIAL: {
            const char* out = get_dis_str(g_dis_info.serial_number, CONF_SERIAL, g_serial_default);
            int outlen = strlen(out);
            return bt_gatt_attr_read(conn, attr, buf, len, offset, out, outlen);
        }
        case DIS_FIELD_HW_REV: {
            const char* out = get_dis_str(g_dis_info.hw_rev_str, CONF_HW_REV, g_hw_default);
            int outlen = strlen(out);
            return bt_gatt_attr_read(conn, attr, buf, len, offset, out, outlen);
        }
        case DIS_FIELD_SW_REV: {
            const char* out = get_dis_str(g_dis_info.sw_rev_str, CONF_SW_REV, g_sw_default);
            int outlen = strlen(out);
            return bt_gatt_attr_read(conn, attr, buf, len, offset, out, outlen);
        }
        case DIS_FIELD_PNP: {
            uint8_t pnp_payload[7];
            pnp_payload[0] = get_pnp_vid_src();
            uint16_t vendor_id = get_pnp_vid();
            pnp_payload[1] = vendor_id & 0xFF;
            pnp_payload[2] = (vendor_id >> 8) & 0xFF;
            uint16_t product_id = get_pnp_pid();
            pnp_payload[3] = product_id & 0xFF;
            pnp_payload[4] = (product_id >> 8) & 0xFF;
            uint16_t version = get_pnp_ver();
            pnp_payload[5] = version & 0xFF;
            pnp_payload[6] = (version >> 8) & 0xFF;
            return bt_gatt_attr_read(conn, attr, buf, len, offset, pnp_payload, sizeof(pnp_payload));
        }
        default: return 0;
        }
}

// BLE GATT characteristic registration: each field uses the unified read callback and field selector as user_data
BT_GATT_SERVICE_DEFINE(dis_service,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DIS),
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_MANUFACTURER_NAME, BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
        read_dis_info_ff, NULL, (void *)DIS_FIELD_MANUFACTURER),
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_SERIAL_NUMBER, BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
        read_dis_info_ff, NULL, (void *)DIS_FIELD_SERIAL),
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_HARDWARE_REVISION, BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
        read_dis_info_ff, NULL, (void *)DIS_FIELD_HW_REV),
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_SOFTWARE_REVISION, BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
        read_dis_info_ff, NULL, (void *)DIS_FIELD_SW_REV),
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_PNP_ID, BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
        read_dis_info_ff, NULL, (void *)DIS_FIELD_PNP)
);


#endif /* CONFIG_BT_DIS */
