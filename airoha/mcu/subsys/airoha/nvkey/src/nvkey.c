/* Copyright Statement:
 *
 * (C) 2023  Airoha Technology Corp. All rights reserved.
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
#include "air_chip.h"
#include "nvkey_internal.h"


#if IS_ENABLED(CONFIG_SETTINGS) && \
    IS_ENABLED(CONFIG_SETTINGS_NVS) && \
    IS_ENABLED(CONFIG_NVS)

#include <zephyr/fs/nvs.h>
#include <settings/settings_nvs.h>
#include <zephyr/settings/settings.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>

#if CONFIG_NVS_OTA_PARTITION_SECTOR_COUNT > 0
#define NVS_OTA_ARTITION                                storage_ota_partition
#define NVS_OTA_PARTITION_DEVICE                        FIXED_PARTITION_DEVICE(NVS_OTA_ARTITION)
#define NVS_OTA_PARTITION_OFFSET                        FIXED_PARTITION_OFFSET(NVS_OTA_ARTITION)

#define AIR_FLASH_MEMORY_DT_NODE                        DT_ALIAS(flash_memory)
#define NVS_OTA_SECTOR_SIZE                             DT_PROP(AIR_FLASH_MEMORY_DT_NODE, erase_block_size)

struct nvs_fs nvs_ota_fs = {
    .flash_device = NVS_OTA_PARTITION_DEVICE,
    .offset = NVS_OTA_PARTITION_OFFSET,
    .sector_size = NVS_OTA_SECTOR_SIZE,
    .sector_count = CONFIG_NVS_OTA_PARTITION_SECTOR_COUNT
};
#endif

extern int nvs_trigger_gc(struct nvs_fs *fs, uint32_t gc_cnt);
extern int nvs_get_free_sector_cnt(struct nvs_fs *fs);

#ifdef CONFIG_MBEDTLS_CIPHER_CHACHA20_ENABLED
#include "mbedtls/chacha20.h"
#endif

static int nvkey_init(void)
{
    int rc;
    rc = settings_subsys_init();
    if (rc) {
        __ASSERT(rc == 0, "settings subsys initialization: fail (err %d)\r\n", rc);
        return rc;
    }
    /* Note that we cannot actively call settings_load here.
     * This is because we only need to initialize settings here
     * to make the nvkey & settings API available, and we DO NOT
     * need to write the registered data into settings.
     * This behavior should be actively controlled by the app level,
     * otherwise it may cause unexpected initialization errors, so comment it out.
     * linked issue: BTD-3400
     */
    /* rc = settings_load(); */

    nvkey_factory_reset_check();
    nvkey_upgrade_check();

#if CONFIG_NVS_OTA_PARTITION_SECTOR_COUNT > 0
    if(rc == 0){
        if(!device_is_ready(nvs_ota_fs.flash_device)){
            return -1;
        }
        rc = nvs_mount(&nvs_ota_fs);
    }
#endif
    return rc;
}

struct nvs_fs* nvkey_judge_paratition(uint16_t id)
{
#if CONFIG_NVS_OTA_PARTITION_SECTOR_COUNT > 0
    void *storage = NULL;
    settings_storage_get(&storage);
    if((id >= NVID_CAN_BE_OTA_BEGIN) && (id <= NVID_CAN_BE_OTA_END)){
        return &nvs_ota_fs;
    } else {
        return (struct nvs_fs*)(storage);
    }
#else
    void *storage = NULL;
    settings_storage_get(&storage);
    return (struct nvs_fs*)(storage);
#endif
}

#ifdef CONFIG_MBEDTLS_CIPHER_CHACHA20_ENABLED
const static uint8_t  g_nvkey_crypt_key[32] = {
    0x41, 0x49, 0x52, 0x4f,
    0x48, 0x41, 0x5f, 0x48,
    0x49, 0x4e, 0x54, 0x45,
    0x47, 0x52, 0x49, 0x54,
    0x59, 0x5f, 0x4b, 0x45,
    0x59, 0x5f, 0x54, 0x45,
    0x53, 0x54, 0x52, 0x49,
    0x4e, 0x47, 0x5f, 0x53
};

const static uint8_t g_nvkey_crypt_nonce[12] = {
    0x41, 0x49, 0x52, 0x4f,
    0x48, 0x41, 0x43, 0x4f,
    0x52, 0x45, 0x5f, 0x56
};

static const uint8_t *s_nvkey_crypt_key = g_nvkey_crypt_key;
static const uint8_t *s_nvkey_crypt_nonce = g_nvkey_crypt_nonce;

#endif

int nvkey_port_encrypt_data(
    const uint8_t *ibuff,
    uint32_t ibuff_sz,
    uint8_t *obuff,
    uint32_t obuff_sz,
    uint32_t option)
{
#ifdef CONFIG_MBEDTLS_CIPHER_CHACHA20_ENABLED
    int res = 0;

    res = mbedtls_chacha20_crypt(s_nvkey_crypt_key, s_nvkey_crypt_nonce, option, ibuff_sz, ibuff, obuff);
    if (res != 0) {
        return (int)NVKEY_STATUS_CRYPT_ERROR;
    } else {
        return (int) ibuff_sz;
    }
#else
    return (int)NVKEY_STATUS_CRYPT_ERROR;
#endif
}

int  nvkey_port_set_crypt_key(const uint8_t key[32], const uint8_t nonce[12])
{
#ifdef CONFIG_MBEDTLS_CIPHER_CHACHA20_ENABLED
    s_nvkey_crypt_key = key;
    s_nvkey_crypt_nonce = nonce;
    return NVKEY_STATUS_OK;
#else
    return (int)NVKEY_STATUS_CRYPT_ERROR;
#endif
}


#if !IS_ENABLED(CONFIG_AIR_NVKEY_ASYNC_ENABLE)
nvkey_status_t nvkey_read_data(uint16_t id, uint8_t *buffer, uint32_t *size)
{
    struct nvs_fs* fs = nvkey_judge_paratition(id);
    ssize_t rd_size;
    if(fs == NULL){
        printk("ERROR because of NULL fs.\r\n");
        return NVKEY_STATUS_ERROR;
    }
    rd_size = nvs_read(fs, id, (void *)buffer, (size_t)(*size));
    if(rd_size < 0){
        *size = 0;
        return rd_size;
    }
    *size = (uint32_t)rd_size;
    return NVKEY_STATUS_OK;
}
#endif /* !IS_ENABLED(CONFIG_AIR_NVKEY_ASYNC_ENABLE) */

nvkey_status_t nvkey_read_data_crypt(uint16_t id, uint8_t *buffer, uint32_t *size)
{
    nvkey_status_t status = NVKEY_STATUS_OK;
    uint8_t *p_tempbuff = NULL;
    int encryp_sz = 0;
    uint32_t tempbuff_sz = 0;

    tempbuff_sz = *size + 32;
    p_tempbuff  = k_malloc(tempbuff_sz);
    if (p_tempbuff == NULL) {
        return NVKEY_STATUS_MALLOC_ERROR;
    }
    status = nvkey_read_data(id, p_tempbuff, &tempbuff_sz);
    if (status != NVKEY_STATUS_OK) {
        k_free(p_tempbuff);
        return status;
    }
    if (*size < tempbuff_sz) {
        k_free(p_tempbuff);
        return NVKEY_STATUS_INVALID_PARAMETER;
    }

    /* option as "NVS" */
    encryp_sz = nvkey_port_encrypt_data(p_tempbuff, tempbuff_sz, buffer, tempbuff_sz, 0x4E5653);
    if (encryp_sz <= 0) {
        status = NVKEY_STATUS_CRYPT_ERROR;
    }
    k_free(p_tempbuff);
    *size = tempbuff_sz;
    return status;
}

nvkey_status_t nvkey_write_data(uint16_t id, const uint8_t *buffer, uint32_t size)
{
    struct nvs_fs* fs = nvkey_judge_paratition(id);
    ssize_t wt_size;
    if(fs == NULL){
        printk("ERROR because of NULL fs.\r\n");
        return NVKEY_STATUS_ERROR;
    }
    __ASSERT(size <= CONFIG_AIR_NVKEY_LEN_MAX, "size is too large");
    wt_size = nvs_write(fs, id, (const void *)buffer, (size_t)(size));
    if(wt_size < 0){
        return wt_size;
    }
    return NVKEY_STATUS_OK;
}

static void *nvkey_malloc_crypt(const uint8_t *buff, uint32_t size, uint32_t option)
{
    uint8_t *p_tempbuff = NULL;
    uint32_t crypt_sz = 0;

    p_tempbuff = k_malloc(size + 32);
    if (p_tempbuff == NULL) {
        return NULL;
    }
    crypt_sz = nvkey_port_encrypt_data(buff, size, p_tempbuff, size, option);
    if (crypt_sz <= 0) {
        k_free(p_tempbuff);
        return NULL;
    }
    return p_tempbuff;
}

static void nvkey_free_crypt(void *ptr)
{
    k_free(ptr);
}

nvkey_status_t nvkey_write_data_crypt(uint16_t id, uint8_t *buffer, uint32_t size)
{
    uint8_t *p_tempbuff = NULL;
    nvkey_status_t status;

    p_tempbuff = nvkey_malloc_crypt(buffer, size, 0x4E5653);
    if (p_tempbuff == NULL) {
        return NVKEY_STATUS_CRYPT_ERROR;
    }
    status = nvkey_write_data(id, p_tempbuff, size);
    nvkey_free_crypt(p_tempbuff);
    return status;
}

nvkey_status_t nvkey_trigger_gc(uint32_t gc_cnt)
{
    struct nvs_fs* fs = nvkey_judge_paratition(0);
    nvs_trigger_gc(fs, 3);
    return NVKEY_STATUS_OK;
}

int nvkey_get_free_sector()
{
    struct nvs_fs* fs = nvkey_judge_paratition(0);
    return nvs_get_free_sector_cnt(fs);
}


#if !IS_ENABLED(CONFIG_AIR_NVKEY_ASYNC_ENABLE)
nvkey_status_t nvkey_write_data_non_blocking(
    uint16_t id,
    const uint8_t *buffer,
    uint32_t size,
    const nvkey_user_callback_t callback,
    const void *user_data)
{
    ARG_UNUSED(id);
    ARG_UNUSED(buffer);
    ARG_UNUSED(size);
    ARG_UNUSED(callback);
    ARG_UNUSED(user_data);
    return NVKEY_STATUS_ERROR;
}

nvkey_status_t nvkey_write_data_non_blocking_crypt(
    uint16_t id,
    const uint8_t *buffer,
    uint32_t size,
    const nvkey_user_callback_t callback,
    const void *user_data)
{
    ARG_UNUSED(id);
    ARG_UNUSED(buffer);
    ARG_UNUSED(size);
    ARG_UNUSED(callback);
    ARG_UNUSED(user_data);
    return NVKEY_STATUS_ERROR;
}
#endif

nvkey_status_t nvkey_delete_data_item(uint16_t id)
{
    struct nvs_fs* fs = nvkey_judge_paratition(id);
    if(fs == NULL){
        printk("ERROR because of NULL fs.\r\n");
        return NVKEY_STATUS_ERROR;
    }
    return nvs_delete(fs, id);
}


SYS_INIT(nvkey_init, CONFIG_NVDATA_INIT_LEVEL, CONFIG_NVDATA_INIT_PRIORITY);

#else

/* for not settings+nvs backend cases */

nvkey_status_t nvkey_read_data(uint16_t id, uint8_t *buffer, uint32_t *size)
{
    ARG_UNUSED(id);
    ARG_UNUSED(buffer);
    ARG_UNUSED(size);
    return NVKEY_STATUS_ERROR;
}


nvkey_status_t nvkey_read_data_crypt(uint16_t id, uint8_t *buffer, uint32_t *size)
{
    ARG_UNUSED(id);
    ARG_UNUSED(buffer);
    ARG_UNUSED(size);
    return NVKEY_STATUS_ERROR;
}

nvkey_status_t nvkey_write_data(uint16_t id, const uint8_t *buffer, uint32_t size)
{
    ARG_UNUSED(id);
    ARG_UNUSED(buffer);
    ARG_UNUSED(size);
    return NVKEY_STATUS_ERROR;
}

nvkey_status_t nvkey_write_data_crypt(uint16_t id, uint8_t *buffer, uint32_t size)
{
    ARG_UNUSED(id);
    ARG_UNUSED(buffer);
    ARG_UNUSED(size);
    return NVKEY_STATUS_ERROR;
}

nvkey_status_t nvkey_write_data_non_blocking(
    uint16_t id,
    const uint8_t *buffer,
    uint32_t size,
    const nvkey_user_callback_t callback,
    const void *user_data)
{
    ARG_UNUSED(id);
    ARG_UNUSED(buffer);
    ARG_UNUSED(size);
    ARG_UNUSED(callback);
    ARG_UNUSED(user_data);
    return NVKEY_STATUS_ERROR;
}

nvkey_status_t nvkey_write_data_non_blocking_crypt(
    uint16_t id,
    const uint8_t *buffer,
    uint32_t size,
    const nvkey_user_callback_t callback,
    const void *user_data)
{
    ARG_UNUSED(id);
    ARG_UNUSED(buffer);
    ARG_UNUSED(size);
    ARG_UNUSED(callback);
    ARG_UNUSED(user_data);
    return NVKEY_STATUS_ERROR;
}

nvkey_status_t nvkey_delete_data_item(uint16_t id)
{
    ARG_UNUSED(id);
    return NVKEY_STATUS_ERROR;
}

#endif /* IS_ENABLED(CONFIG_SETTINGS) && IS_ENABLED(CONFIG_SETTINGS_NVS) && IS_ENABLED(CONFIG_NVS) */