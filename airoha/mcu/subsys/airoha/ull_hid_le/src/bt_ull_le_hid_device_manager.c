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

#include "nvkey.h"
#include "hal_trng.h"
#include "bt_ull_le_hid_device_manager.h"
#include "bt_ull_le_hid_utility.h"
#include "zephyr/logging/log.h"

LOG_MODULE_DECLARE(ULL_HID);

#define BT_ULL_HID_DM_LOG   "[ULL][LE][HID][DM] "
static uint8_t uni_aa[BT_ULL_LE_HID_DM_UNI_AA_LEN] = {0x6D, 0xEB, 0x98, 0xE9};
static uint8_t uni_ltk[BT_ULL_LE_HID_DM_LTK_LEN]   = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
static uint8_t uni_skd[BT_ULL_LE_HID_DM_SKD_LEN]   = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20};
static uint8_t uni_iv[BT_ULL_LE_HID_DM_IV_LEN]     = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};

#define BT_ULL_LE_HID_DEFAULT_PAIRING_INFO_NUM        (0x05)
static bt_ull_le_hid_dm_device_info_t g_default_pairing_inf_tab[BT_ULL_LE_HID_DEFAULT_PAIRING_INFO_NUM] = {0};

static bt_addr_le_t g_default_addr[BT_ULL_LE_HID_DEFAULT_PAIRING_INFO_NUM] = {
    {0, {{0, 0, 0, 0, 0, 0}}},
    {BT_ADDR_LE_RANDOM, {{0xFF, 0xFE, 0xFD, 0xFc, 0x02, 0x03}}}, //KB
    {BT_ADDR_LE_RANDOM, {{0xFF, 0xFE, 0xFD, 0xFc, 0x04, 0x05}}}, //MS
    {0, {{0, 0, 0, 0, 0, 0}}},
    {BT_ADDR_LE_RANDOM, {{0xFF, 0xFE, 0xFD, 0xFc, 0x06, 0x07}}}, //GP
};

static uint8_t g_default_ltk[BT_ULL_LE_HID_DEFAULT_PAIRING_INFO_NUM][BT_ULL_LE_HID_DM_LTK_LEN] = {
    {0},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10}, // KB
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10}, // MS
    {0},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10}, // GP
};

static uint8_t g_default_skd[BT_ULL_LE_HID_DEFAULT_PAIRING_INFO_NUM][BT_ULL_LE_HID_DM_LTK_LEN] = {
    {0},
    {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20}, // KB
    {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20}, // MS
    {0},
    {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20}, // GP
};

static uint8_t g_default_iv[BT_ULL_LE_HID_DEFAULT_PAIRING_INFO_NUM][BT_ULL_LE_HID_DM_LTK_LEN] = {
    {0},
    {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38}, // KB
    {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38}, // MS
    {0},
    {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38}, // GP
};

typedef struct {
    bool                        used;
    bt_ull_le_hid_dm_device_info_t device_info;
} bt_ull_le_hid_dm_device_nvkey_t;

bt_ull_le_hid_dm_device_nvkey_t g_mouse[BT_ULL_LE_HID_DM_DEVICE_NUM_MAX];
bt_ull_le_hid_dm_device_nvkey_t g_keyboard[BT_ULL_LE_HID_DM_DEVICE_NUM_MAX];
bt_ull_le_hid_dm_device_nvkey_t g_gamepad[BT_ULL_LE_HID_DM_DEVICE_NUM_MAX];
bool g_ull_le_hid_device_manager_init = false;
static bool g_ull_le_hid_dm_test_mode = false;

void bt_ull_le_hid_dm_init_default_pairing_info(void)
{
    uint8_t i = 0x0;
    bt_ull_le_hid_dm_device_info_t *dev = NULL;
    for (i = 0; i < BT_ULL_LE_HID_DEFAULT_PAIRING_INFO_NUM; i ++) {
        dev = &g_default_pairing_inf_tab[i];
        dev->device_type = i + 1;
        bt_ull_le_srv_memcpy(&dev->addr, &g_default_addr[i], sizeof(bt_addr_le_t));  
        bt_ull_le_srv_memcpy(dev->ltk, &g_default_ltk[i], BT_ULL_LE_HID_DM_LTK_LEN);
        bt_ull_le_srv_memcpy(dev->skd, &g_default_skd[i], BT_ULL_LE_HID_DM_SKD_LEN);
        bt_ull_le_srv_memcpy(dev->iv, &g_default_iv[i], BT_ULL_LE_HID_DM_IV_LEN);
    }
    bt_ull_le_bytes_from_str((uint8_t *)&g_default_pairing_inf_tab[BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD - 1].uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)CONFIG_KB_DEFAULT_ULL_HID_LE_UNIAA);
    bt_ull_le_bytes_from_str((uint8_t *)&g_default_pairing_inf_tab[BT_ULL_LE_HID_SRV_DEVICE_MOUSE - 1].uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)CONFIG_MS_DEFAULT_ULL_HID_LE_UNIAA);
    bt_ull_le_bytes_from_str((uint8_t *)&g_default_pairing_inf_tab[BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD - 1].uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)CONFIG_GP_DEFAULT_ULL_HID_LE_UNIAA);
}

int bt_ull_le_hid_dm_init(void)
{
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    if (g_ull_le_hid_device_manager_init) {
        return 0;
    }
    bt_ull_le_hid_dm_init_default_pairing_info();
    uint32_t size_kb = sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX;
    uint32_t size_ms = sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX;
    uint32_t szie_gp = sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX;
    bt_ull_le_srv_memset(&g_mouse[0], 0, size_kb);
    bt_ull_le_srv_memset(&g_keyboard[0], 0, size_ms);
    bt_ull_le_srv_memset(&g_gamepad[0], 0, szie_gp);
    LOG_INF(BT_ULL_HID_DM_LOG"dm_init_device_info, size_kb: %d, size_ms: %d, szie_gp: %d", size_kb, size_ms, szie_gp);
    status = nvkey_read_data(NVID_BT_HOST_ULL_HID_KB_INFO, (uint8_t *)&g_keyboard[0], &size_kb);
    if (NVKEY_STATUS_OK != status && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
        LOG_ERR(BT_ULL_HID_DM_LOG"dm_init_device_info, error status-kb:%d, size: %d", status, size_kb);
        return -EPERM;
    }
    status = nvkey_read_data(NVID_BT_HOST_ULL_HID_MS_INFO, (uint8_t *)&g_mouse[0], &size_ms);
    if (NVKEY_STATUS_OK != status && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
        LOG_ERR(BT_ULL_HID_DM_LOG"dm_init_device_info, error status-ms:%d, size: %d", status, size_ms);
        return -EPERM;
    }
    status = nvkey_read_data(NVID_BT_HOST_ULL_HID_GP_INFO, (uint8_t *)&g_gamepad[0], &szie_gp);
    if (NVKEY_STATUS_OK != status && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
        LOG_ERR(BT_ULL_HID_DM_LOG"dm_init_device_info, error status-gp:%d, size: %d", status, szie_gp);
        return -EPERM;
    }
    g_ull_le_hid_device_manager_init = true;
    LOG_INF(BT_ULL_HID_DM_LOG"dm_init_device_info, init success!!");

    return 0;
}

bool bt_ull_le_hid_dm_is_default_addr(uint8_t dev_type, bt_addr_le_t *addr)// 1: ture, 0: false
{
    if (dev_type > BT_ULL_LE_HID_DEFAULT_PAIRING_INFO_NUM || NULL == addr) {
        return false;
    }
    return !bt_ull_le_srv_memcmp(&g_default_addr[dev_type-1].a, &addr->a, sizeof(bt_addr_t));
}

int bt_ull_le_hid_dm_write_nvdm(bt_ull_le_hid_srv_device_t device_type)
{
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    uint32_t size = sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX;
    switch (device_type) {
    case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
        status = nvkey_write_data(NVID_BT_HOST_ULL_HID_KB_INFO, (uint8_t *)&g_keyboard[0], size);
        break;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
        status = nvkey_write_data(NVID_BT_HOST_ULL_HID_MS_INFO, (uint8_t *)&g_mouse[0], size);
        break;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
        status = nvkey_write_data(NVID_BT_HOST_ULL_HID_GP_INFO, (uint8_t *)&g_gamepad[0], size);
        break;
    }
    default:
        break;
    }
    LOG_INF(BT_ULL_HID_DM_LOG"dm_write_nvdm, status: %d, device_type: %d", status, device_type);
    return NVKEY_STATUS_OK == status ? 0 : -EPERM;
}

static bt_ull_le_hid_dm_device_nvkey_t *bt_ull_le_hid_dm_get_available_info(bt_ull_le_hid_srv_device_t device_type)
{
    uint8_t i = 0x0;
    bt_ull_le_hid_dm_device_nvkey_t temp_device[BT_ULL_LE_HID_DM_DEVICE_NUM_MAX] = {0};
    LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_get_available_info, Device_type: %d", device_type);
    switch (device_type) {
    case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
        if (BT_ULL_LE_HID_DM_DEVICE_NUM_MAX > 1) {
            for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
                bt_ull_le_srv_memcpy(&temp_device[i], &g_keyboard[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            }
            bt_ull_le_srv_memset(&g_keyboard[0], 0, sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
            for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX - 1; i ++) {
                bt_ull_le_srv_memcpy(&g_keyboard[i+1], &temp_device[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            }
        } else if (BT_ULL_LE_HID_DM_DEVICE_NUM_MAX == 1) {
            bt_ull_le_srv_memset(&g_keyboard[0], 0, sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
        } else {
            __ASSERT_NO_MSG(0);
        }
        return &g_keyboard[0];
        break;

    }
    case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
        if (BT_ULL_LE_HID_DM_DEVICE_NUM_MAX > 1) {
            for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
                bt_ull_le_srv_memcpy(&temp_device[i], &g_mouse[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            }
            bt_ull_le_srv_memset(&g_mouse[0], 0, sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
            for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX - 1; i ++) {
                bt_ull_le_srv_memcpy(&g_mouse[i+1], &temp_device[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            }
        } else if (BT_ULL_LE_HID_DM_DEVICE_NUM_MAX == 1) {
            bt_ull_le_srv_memset(&g_mouse[0], 0, sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
        } else {
            __ASSERT_NO_MSG(0);
        }
        return &g_mouse[0];
        break;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
        if (BT_ULL_LE_HID_DM_DEVICE_NUM_MAX > 1) {
            for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
                bt_ull_le_srv_memcpy(&temp_device[i], &g_gamepad[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            }
            bt_ull_le_srv_memset(&g_gamepad[0], 0, sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
            for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX - 1; i ++) {
                bt_ull_le_srv_memcpy(&g_gamepad[i+1], &temp_device[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            }
        } else if (BT_ULL_LE_HID_DM_DEVICE_NUM_MAX == 1) {
            bt_ull_le_srv_memset(&g_gamepad[0], 0, sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
        } else {
            __ASSERT_NO_MSG(0);
        }
        return &g_gamepad[0];
        break;
    }
    default:
        break;
    }
    return NULL;

}

bt_ull_le_hid_dm_device_info_t *bt_ull_le_hid_dm_read_device_info(bt_ull_le_hid_srv_device_t device_type, const bt_addr_le_t *addr)
{
    uint8_t i = 0x0;
    LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_read_device_info, device_type: %d", device_type);
    switch (device_type) {
    case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_keyboard[i].device_info.addr, sizeof(bt_addr_le_t)) && g_keyboard[i].used) {
                return &g_keyboard[i].device_info;
            }
        }
        break;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_mouse[i].device_info.addr, sizeof(bt_addr_le_t)) && g_mouse[i].used) {
                return &g_mouse[i].device_info;
            }
        }
        break;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_gamepad[i].device_info.addr, sizeof(bt_addr_le_t)) && g_gamepad[i].used) {
                return &g_gamepad[i].device_info;
            }
        }
        break;
    }
    default:
        break;
    }
    return NULL;
}

int bt_ull_le_hid_dm_write_device_info(bt_ull_le_hid_dm_device_info_t *info)
{
    LOG_INF(BT_ULL_HID_DM_LOG"dm_write_device_info, init: %d, test mode: %d", g_ull_le_hid_device_manager_init, g_ull_le_hid_dm_test_mode);
    if (!info || !g_ull_le_hid_device_manager_init || g_ull_le_hid_dm_test_mode) {
        return -EPERM;
    }
    if (bt_ull_le_hid_dm_read_device_info(info->device_type, &info->addr)) {
        LOG_ERR(BT_ULL_HID_DM_LOG"dm_write_device_info, device has exist, delete it first!!");
        bt_ull_le_hid_dm_delete_device_info(info->device_type, &info->addr);
        // return 0;
    }

    bt_ull_le_hid_dm_device_nvkey_t *device = bt_ull_le_hid_dm_get_available_info(info->device_type);
    if (NULL == device) {
        LOG_ERR(BT_ULL_HID_DM_LOG"dm_write_device_info, no source!!");
        return -EPERM;
    }
    device->used = true;
    bt_ull_le_srv_memcpy(&device->device_info, info, sizeof(bt_ull_le_hid_dm_device_info_t));
    bt_ull_le_hid_srv_print_addr(&info->addr);
    return bt_ull_le_hid_dm_write_nvdm(info->device_type);
}

bt_addr_le_t *bt_ull_le_hid_dm_addr_by_device_type(bt_ull_le_hid_srv_device_t cur_device_type)
{
    bt_ull_le_hid_dm_device_nvkey_t *device = bt_ull_le_hid_dm_get_available_info(cur_device_type);
    if (NULL == device) {
        LOG_ERR(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_clear_by_device_type, no source!!");
        return NULL;
    }
    return &device->device_info.addr;
}

#if defined (AIR_PURE_GAMING_ENABLE)
#include "bt_avm.h"

uint8_t bt_ull_le_hid_dm_get_default_tx_gc()
{
    #define DEFAULT_TX_GC_VALUE (0x3C)

    uint8_t tx_gc_buf[11*4] = {0};
    uint32_t tx_gc_len = sizeof(tx_gc_buf);
    nvkey_status_t status = nvkey_read_data(NVID_CAL_PWR_CTL_MP_K, (uint8_t *)tx_gc_buf, &tx_gc_len);
    if (status != NVKEY_STATUS_OK && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
        LOG_ERR(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_get_default_tx_gc fail(%d)!", status);
        return DEFAULT_TX_GC_VALUE;
    }
    LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_get_default_tx_gc, tx gc(0x%02X)", tx_gc_buf[0]);
    
    return tx_gc_buf[0];
}

uint8_t bt_ull_le_hid_dm_get_qc_tx_gc()
{
    #define QC_TX_GC_VALUE (0x23)

    uint8_t tx_gc_buf[1] = {0};
    uint32_t tx_gc_len = sizeof(tx_gc_buf);
    nvkey_status_t status = nvkey_read_data(NVID_APP_DONGLE_QC_TX_GC, (uint8_t *)tx_gc_buf, &tx_gc_len);
    if (status != NVKEY_STATUS_OK && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
        LOG_ERR(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_get_qc_tx_gc fail!");
        return QC_TX_GC_VALUE;
    }
    LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_get_qc_tx_gc, tx gc(0x%02X)", tx_gc_buf[0]);

    return tx_gc_buf[0];
}

int bt_avm_vendor_set_tx_gc_value(uint8_t value)
{
    bt_avm_vendor_set_tx_power_t tx_power;
    tx_power.info[0] = 0x41;
    tx_power.info[1] = 0x50;
    tx_power.info[2] = 0x50;
    tx_power.info[3] = 0x7E;
    tx_power.info[4] = value;
    tx_power.info[5] = value;
    return bt_avm_vendor_set_tx_power(&tx_power);
}

/*          
    if QC Dongle[KB] Connect KB:
        QC Dongle KB uniaa == Normal KB uniaa == 60:71:82:96;
    if QC Dongle[MS] Connect MS:
        QC Dongle MS uniaa == Normal MS uniaa == 61:72:83:EF; 
    if Normal Dongle[KB] Connect QC KB:
        Normal Dongle KB uniaa == QC KB uniaa == 61:72:83:97;
    if Normal Dongle[KB] Connect QC MS:
        Normal Dongle MS uniaa == QC KB uniaa == 61:72:8:F0;
*/
int bt_ull_le_hid_dm_enter_test_mode(bt_ull_le_hid_srv_device_t device_type)
{
    LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_enter_test_mode, dt: %d", device_type);
    uint8_t kb_test_uni_aa[BT_ULL_LE_HID_DM_UNI_AA_LEN];
    uint8_t mouse_test_uni_aa[BT_ULL_LE_HID_DM_UNI_AA_LEN];
    switch (device_type) {
        case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
            uint32_t size = sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX;
            bt_ull_le_srv_memset(&g_keyboard[0], 0, size);
            bt_ull_le_hid_dm_device_nvkey_t dv_info;
            dv_info.used = true;
            dv_info.device_info.device_type = device_type;
            bt_addr_le_t test_addr = {0x01, {0x01, 0x02, 0x03, 0x04, 0x05, 0x08}};
            bt_ull_role_t role = bt_ull_le_hid_srv_get_role();
            if (BT_ULL_ROLE_CLIENT == role) {
#if defined (AIR_QC_ENABLE)
            bt_ull_le_bytes_from_str(&mouse_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)QC_KB_NM_DG_ULL_HID_LE_UNIAA);
#else
            bt_ull_le_bytes_from_str(&mouse_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)QC_DG_NM_KB_ULL_HID_LE_UNIAA);
#endif
            } else (BT_ULL_ROLE_SERVER == role) {
#if defined (AIR_QC_ENABLE)
            bt_ull_le_bytes_from_str(&mouse_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)QC_DG_NM_KB_ULL_HID_LE_UNIAA);
#else
            bt_ull_le_bytes_from_str(&mouse_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)QC_KB_NM_DG_ULL_HID_LE_UNIAA);
#endif
            }
            bt_ull_le_srv_memcpy(&dv_info.device_info.addr, &test_addr, sizeof(bt_addr_le_t));
            bt_ull_le_srv_memcpy(&dv_info.device_info.uni_aa, &kb_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
            bt_ull_le_srv_memcpy(&dv_info.device_info.ltk, &uni_ltk, BT_ULL_LE_HID_DM_LTK_LEN);
            bt_ull_le_srv_memcpy(&dv_info.device_info.skd, &uni_skd, BT_ULL_LE_HID_DM_SKD_LEN);
            bt_ull_le_srv_memcpy(&dv_info.device_info.iv, &uni_iv, BT_ULL_LE_HID_DM_IV_LEN);
            bt_ull_le_srv_memcpy(&g_keyboard[0], &dv_info, sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            break;
        }
        case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
            uint32_t size = sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX;
            bt_ull_le_srv_memset(&g_mouse[0], 0, size);
            bt_ull_le_hid_dm_device_nvkey_t dv_info;
            dv_info.used = true;
            dv_info.device_info.device_type = device_type;
            bt_addr_le_t test_addr = {0x01, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06}};
            if (BT_ULL_ROLE_CLIENT == role) {/* MS */
#if defined (AIR_QC_ENABLE)
            bt_ull_le_bytes_from_str(&mouse_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)QC_MS_NM_DG_ULL_HID_LE_UNIAA);
#else
            bt_ull_le_bytes_from_str(&mouse_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)CONFIG_QC_DG_NM_MS_ULL_HID_LE_UNIAA);
#endif
            } else (BT_ULL_ROLE_SERVER == role) { /* Dongle */
#if defined (AIR_QC_ENABLE)
            bt_ull_le_bytes_from_str(&mouse_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)CONFIG_QC_DG_NM_MS_ULL_HID_LE_UNIAA);
#else
            bt_ull_le_bytes_from_str(&mouse_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN, (char *)QC_MS_NM_DG_ULL_HID_LE_UNIAA);
#endif
            }

            bt_ull_le_srv_memcpy(&dv_info.device_info.addr, &test_addr, sizeof(bt_addr_le_t));
            bt_ull_le_srv_memcpy(&dv_info.device_info.uni_aa, &mouse_test_uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
            bt_ull_le_srv_memcpy(&dv_info.device_info.ltk, &uni_ltk, BT_ULL_LE_HID_DM_LTK_LEN);
            bt_ull_le_srv_memcpy(&dv_info.device_info.skd, &uni_skd, BT_ULL_LE_HID_DM_SKD_LEN);
            bt_ull_le_srv_memcpy(&dv_info.device_info.iv, &uni_iv, BT_ULL_LE_HID_DM_IV_LEN);
            bt_ull_le_srv_memcpy(&g_mouse[0], &dv_info, sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            break;
        }
        default:
            return -EPERM;
    }
    g_ull_le_hid_dm_test_mode = true;

    uint8_t qc_tx_gc_value = bt_ull_le_hid_dm_get_qc_tx_gc();
    return bt_avm_vendor_set_tx_gc_value(qc_tx_gc_value);
}

int bt_ull_le_hid_dm_exit_test_mode(bt_ull_le_hid_srv_device_t device_type)
{
    LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_exit_test_mode, dt: %d", device_type);

    uint32_t size = sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX;
    int status = -EPERM;
    switch (device_type) {
        case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
            bt_ull_le_srv_memset(&g_mouse[0], 0, size);
            status = nvkey_read_data(NVID_BT_HOST_ULL_HID_MS_INFO, (uint8_t *)&g_mouse[0], &size);
            if (NVKEY_STATUS_OK != status && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
                LOG_ERR(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_exit_test_mode, error status-1:%d, size: %d", status, size);
                return -EPERM;
            }
            bt_ull_le_hid_srv_print_addr(&g_mouse[0].device_info.addr);
            break;
        }
        case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
            bt_ull_le_srv_memset(&g_keyboard[0], 0, size);
            status = nvkey_read_data(NVID_BT_HOST_ULL_HID_KB_INFO, (uint8_t *)&g_keyboard[0], &size);
            if (NVKEY_STATUS_OK != status && NVKEY_STATUS_ITEM_NOT_FOUND != status) {
                LOG_ERR(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_exit_test_mode, error status-1:%d, size: %d", status, size);
                return -EPERM;
            }
            bt_ull_le_hid_srv_print_addr(&g_keyboard[0].device_info.addr);
            break;
        }
        default:
            return -EPERM;
    }
    g_ull_le_hid_dm_test_mode = false;

    uint8_t default_tx_gc_value = bt_ull_le_hid_dm_get_default_tx_gc();
    return bt_avm_vendor_set_tx_gc_value(default_tx_gc_value);
}
#endif

int bt_ull_le_hid_dm_shift_device_front(bt_ull_le_hid_srv_device_t device_type, const bt_addr_le_t *addr)
{
    uint8_t i, j = 0;
    int status = -EPERM;
    LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_shift_device_front, init: %d, test mode: %d", g_ull_le_hid_device_manager_init, g_ull_le_hid_dm_test_mode);
    if (!g_ull_le_hid_device_manager_init || g_ull_le_hid_dm_test_mode) {
        return -EPERM;
    }
    bt_ull_le_hid_dm_device_nvkey_t temp_device[BT_ULL_LE_HID_DM_DEVICE_NUM_MAX] = {0};
    switch (device_type) {
    case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
        if (!bt_ull_le_hid_dm_read_device_info(device_type, addr)) {
            return status;
        }
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_keyboard[i].device_info.addr, sizeof(bt_addr_le_t)) && g_keyboard[i].used) {
                if (0 == i) {
                    return 0;
                }
                bt_ull_le_srv_memcpy(&temp_device[0], &g_keyboard[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
                continue;
            }
            if (j >= BT_ULL_LE_HID_DM_DEVICE_NUM_MAX) {
                return -EPERM;
            }
            bt_ull_le_srv_memcpy(&temp_device[j+1], &g_keyboard[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            j ++;
        }
        bt_ull_le_srv_memcpy(&g_keyboard[0], &temp_device[0], sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
        status = bt_ull_le_hid_dm_write_nvdm(device_type);
        break;

    }
    case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
        if (!bt_ull_le_hid_dm_read_device_info(device_type, addr)) {
            return status;
        }
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_mouse[i].device_info.addr, sizeof(bt_addr_le_t)) && g_mouse[i].used) {
                if (0 == i) {
                    return 0;
                }
                bt_ull_le_srv_memcpy(&temp_device[0], &g_mouse[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
                continue;
            }
            if (j >= BT_ULL_LE_HID_DM_DEVICE_NUM_MAX) {
                return -EPERM;
            }
            bt_ull_le_srv_memcpy(&temp_device[j+1], &g_mouse[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            j ++;
        }
        bt_ull_le_srv_memcpy(&g_mouse[0], &temp_device[0], sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
        status = bt_ull_le_hid_dm_write_nvdm(device_type);
        break;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
        if (!bt_ull_le_hid_dm_read_device_info(device_type, addr)) {
            return status;
        }
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_gamepad[i].device_info.addr, sizeof(bt_addr_le_t)) && g_gamepad[i].used) {
                if (0 == i) {
                    return 0;
                }
                bt_ull_le_srv_memcpy(&temp_device[0], &g_gamepad[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
                continue;
            }
            if (j >= BT_ULL_LE_HID_DM_DEVICE_NUM_MAX) {
                return -EPERM;
            }
            bt_ull_le_srv_memcpy(&temp_device[j+1], &g_gamepad[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            j ++;
        }
        bt_ull_le_srv_memcpy(&g_gamepad[0], &temp_device[0], sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
        status = bt_ull_le_hid_dm_write_nvdm(device_type);
        break;
    }
    default:
        break;
    }
    return status;
}

int bt_ull_le_hid_dm_delete_device_info(bt_ull_le_hid_srv_device_t device_type, const bt_addr_le_t *addr)
{
    uint8_t i , j = 0x0;
    int status = -EPERM;
    LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_delete_device_info, init: %d, test mode: %d", g_ull_le_hid_device_manager_init, g_ull_le_hid_dm_test_mode);
    if (!g_ull_le_hid_device_manager_init || g_ull_le_hid_dm_test_mode) {
        return -EPERM;
    }

    bt_ull_le_hid_dm_device_nvkey_t temp_device[BT_ULL_LE_HID_DM_DEVICE_NUM_MAX] = {0};
    switch (device_type) {
    case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
        if (!bt_ull_le_hid_dm_read_device_info(device_type, addr)) {
            return status;
        }
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_keyboard[i].device_info.addr, sizeof(bt_addr_le_t)) && g_keyboard[i].used) {
                continue;
            }
            bt_ull_le_srv_memcpy(&temp_device[j], &g_keyboard[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            j ++;
        }
        bt_ull_le_srv_memcpy(&g_keyboard[0], &temp_device[0], sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
        status = bt_ull_le_hid_dm_write_nvdm(device_type);
        break;

    }
    case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
        if (!bt_ull_le_hid_dm_read_device_info(device_type, addr)) {
            return status;
        }
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_mouse[i].device_info.addr, sizeof(bt_addr_le_t)) && g_mouse[i].used) {
                continue;
            }
            bt_ull_le_srv_memcpy(&temp_device[j], &g_mouse[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            j ++;
        }
        bt_ull_le_srv_memcpy(&g_mouse[0], &temp_device[0], sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
        status = bt_ull_le_hid_dm_write_nvdm(device_type);
        break;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
        if (!bt_ull_le_hid_dm_read_device_info(device_type, addr)) {
            return status;
        }
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_gamepad[i].device_info.addr, sizeof(bt_addr_le_t)) && g_gamepad[i].used) {
                continue;
            }
            bt_ull_le_srv_memcpy(&temp_device[j], &g_gamepad[i], sizeof(bt_ull_le_hid_dm_device_nvkey_t));
            j ++;
        }
        bt_ull_le_srv_memcpy(&g_gamepad[0], &temp_device[0], sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX);
        status = bt_ull_le_hid_dm_write_nvdm(device_type);
        break;
    }
    default:
        break;
    }
    return status;
}

uint8_t bt_ull_le_hid_dm_get_bonded_device_num(bt_ull_le_hid_srv_device_t device_type)
{
    if (!g_ull_le_hid_device_manager_init) {
        return 0;
    }

    uint8_t i, count = 0x0;
    switch (device_type) {
    case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (g_keyboard[i].used) {
                count ++;
            }
        }
        return count;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (g_mouse[i].used) {
                count ++;
            }
        }
        return count;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (g_gamepad[i].used) {
                count ++;
            }
        }
        return count;
    }
    default:
        break;
    }
    LOG_INF(BT_ULL_HID_DM_LOG"dm_get_bonded_device_num, dt: %d, num: %d", device_type, count);
    return count;
}
void bt_ull_le_hid_dm_get_bonded_device_list(bt_ull_le_hid_srv_device_t device_type, uint8_t count, bt_addr_le_t *list)
{
    if (!list || !count || !g_ull_le_hid_device_manager_init) {
        return;
    }
    uint8_t i = 0x0;
    switch (device_type) {
    case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
        for (i = 0; i < count; i ++) {
            if (g_keyboard[i].used) {
                bt_ull_le_srv_memcpy(&list[i], &g_keyboard[i].device_info.addr, sizeof(bt_addr_le_t));
            }
        }
        break;

    }
    case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
        for (i = 0; i < count; i ++) {
            if (g_mouse[i].used) {
                bt_ull_le_srv_memcpy(&list[i], &g_mouse[i].device_info.addr, sizeof(bt_addr_le_t));
            }
        }
        break;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
        for (i = 0; i < count; i ++) {
            if (g_gamepad[i].used) {
                bt_ull_le_srv_memcpy(&list[i], &g_gamepad[i].device_info.addr, sizeof(bt_addr_le_t));
            }
        }
        break;
    }
    default:
        break;
    }

}

void bt_ull_le_hid_dm_get_default_pairing_list(bt_ull_le_hid_srv_device_t device_type, bt_addr_le_t *list)
{
    if (!list || !g_ull_le_hid_device_manager_init) {
        return;
    }
    if (BT_ULL_LE_HID_SRV_DEVICE_NONE != device_type && device_type < BT_ULL_LE_HID_SRV_DEVICE_MAX_TYPE) {
        bt_ull_le_srv_memcpy(list, &g_default_pairing_inf_tab[device_type - 1].addr, sizeof(bt_addr_le_t));
    }
}

bt_ull_le_hid_dm_device_info_t *bt_ull_le_hid_dm_read_default_pairing_info(bt_ull_le_hid_srv_device_t device_type)
{
    if (!g_ull_le_hid_device_manager_init) {
        return NULL;
    }

    if (BT_ULL_LE_HID_SRV_DEVICE_NONE != device_type && device_type < BT_ULL_LE_HID_SRV_DEVICE_MAX_TYPE) {
        return &g_default_pairing_inf_tab[device_type - 1];
    }
    return NULL;
}

bool bt_ull_le_hid_dm_is_bonded_device(bt_ull_le_hid_srv_device_t device_type, const bt_addr_le_t *addr)
{
    uint8_t i = 0;
    switch (device_type) {
    case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_keyboard[i].device_info.addr, sizeof(bt_addr_le_t)) && g_keyboard[i].used) {
                return true;
            }

        }
        break;

    }
    case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_mouse[i].device_info.addr, sizeof(bt_addr_le_t)) && g_mouse[i].used) {
                return true;
            }
        }
        break;
    }
    case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
        for (i = 0; i < BT_ULL_LE_HID_DM_DEVICE_NUM_MAX; i ++) {
            if (!bt_ull_le_srv_memcmp(addr, &g_gamepad[i].device_info.addr, sizeof(bt_addr_le_t)) && g_gamepad[i].used) {
                return true;
            }
        }
        break;
    }
    default:
        break;
    }
    return false;
}

uint8_t *bt_ull_le_hid_dm_generate_uni_aa(void)
{
    uint32_t random_aa = 0x00;
    hal_trng_status_t status = hal_trng_get_generated_random_number(&random_aa);
    if (HAL_TRNG_STATUS_OK != status) {
        LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_generate_uni_aa, fail! status : %d", status);
        return &uni_aa[0];
    }
    bt_ull_le_srv_memcpy(&uni_aa[0], &random_aa, sizeof(BT_ULL_LE_HID_DM_UNI_AA_LEN));
    return &uni_aa[0];
}
uint8_t *bt_ull_le_hid_dm_get_ltk(void)
{
    return &uni_ltk[0];

}
uint8_t *bt_ull_le_hid_dm_get_skd(void)
{
    return &uni_skd[0];

}
uint8_t *bt_ull_le_hid_dm_get_iv(void)
{
    return &uni_iv[0];
}
int bt_ull_le_hid_dm_clear_bonded_list(bt_ull_le_hid_srv_device_t device_type)
{
    int status = 0;
    uint32_t size = sizeof(bt_ull_le_hid_dm_device_nvkey_t) * BT_ULL_LE_HID_DM_DEVICE_NUM_MAX;
    switch (device_type) {
        case BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD: {
            bt_ull_le_srv_memset(&g_keyboard[0], 0, size);
            status = bt_ull_le_hid_dm_write_nvdm(BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD);
            break;
        }
        case BT_ULL_LE_HID_SRV_DEVICE_MOUSE: {
            bt_ull_le_srv_memset(&g_mouse[0], 0, size);
            status = bt_ull_le_hid_dm_write_nvdm(BT_ULL_LE_HID_SRV_DEVICE_MOUSE);
            break;
        }
        case BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD: {
            bt_ull_le_srv_memset(&g_gamepad[0], 0, size);
            status = bt_ull_le_hid_dm_write_nvdm(BT_ULL_LE_HID_SRV_DEVICE_MOUSE);
            break;
        }
        default:
            break;
    }
    LOG_INF(BT_ULL_HID_DM_LOG"bt_ull_le_hid_dm_clear_bonded_list, dt: %d, status: %x", device_type, status);
    return status;
}


