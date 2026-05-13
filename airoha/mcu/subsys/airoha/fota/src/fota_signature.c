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


#ifdef AIR_FOTA_ECDSA_ENABLE
#include "mbedtls/build_info.h"
#if defined(MBEDTLS_SHA512_C) || defined(MBEDTLS_SHA384_C)
#include "mbedtls/sha512.h"
#endif
#if defined(MBEDTLS_PK_C) && defined(MBEDTLS_PK_PARSE_C)
#include "mbedtls/pk.h"
#endif
#if defined(MBEDTLS_ASN1_PARSE_C)
#include "mbedtls/asn1.h"
#endif
#endif

#ifdef HAL_SHA_MODULE_ENABLED
#include "hal_sha.h"
#endif
// #include "utils/crc32.h"
#include "hal_gpt.h"
#include "fota_flash.h"
#include "fota_signature.h"
#include "fota_signature_pubkey.h"


/****************** Macro Definition ******************/


#if (PRODUCT_VERSION != 3335 && !defined(AIR_BTA_IC_PREMIUM_G2) && !defined(AIR_BTA_IC_PREMIUM_G3)) || !defined(AIR_FOTA_UPGRADE_ENABLE) || defined(MTK_BOOTLOADER_USE_MBEDTLS)
#define FOTA_USE_MBEDTLS_ENABLE /* Enable FOTA to ues the mbedtls algorithms. */

#ifdef FOTA_USE_MBEDTLS_ENABLE
#if (PRODUCT_VERSION != 3335 && !defined(AIR_BTA_IC_PREMIUM_G2) && !defined(AIR_BTA_IC_PREMIUM_G3)) || !defined(AIR_FOTA_UPGRADE_ENABLE)
#define FOTA_USE_MBEDTLS_SHA256_ENABLE /* Enable FOTA to ues the mbedtls SHA256 algorithm. */
#endif
#define FOTA_USE_MBEDTLS_RSA_ENABLE /* Enable FOTA to ues the mbedtls RSA algorithm. */
#endif
#endif


/* Currently HW algorithm only supports SHA224 and SHA256. */
#ifdef HAL_SHA_MODULE_ENABLED
#define FOTA_HASH_HW_ALGORITHM_ENABLE
#endif

#ifndef FOTA_BL_ENABLE
//#define FOTA_HASH_PERFORMANCE_DEBUG_ENABLE
#else
#define FOTA_HASH_CONTEXT_DEFAULT_SIZE  (128)
#endif

/****************** Structure Definition ******************/

#ifdef FOTA_BL_ENABLE
typedef union {
#if defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
    hal_sha224_context_t sha224_context;
    hal_sha224_context_t sha256_context;
#elif defined(MBEDTLS_SHA256_C)
    mbedtls_sha256_context sha224_context;
    mbedtls_sha256_context sha256_context;
#endif
#if defined(MBEDTLS_SHA384_C)
    mbedtls_sha512_context sha384_conext;
#endif
#if defined(MBEDTLS_SHA512_C)
    mbedtls_sha512_context sha512_conext;
#endif
    // fota_hash_crc32_context_struct crc32_conext; /* BL disabled CRC32 */
    uint8_t default_context[FOTA_HASH_CONTEXT_DEFAULT_SIZE];
} fota_hash_conext_union;

typedef struct {
    fota_hash_conext_union hash_context;
    bool in_use;
} fota_hash_context_struct;
#endif


/****************** Varable Definition ******************/

#ifdef FOTA_BL_ENABLE
fota_hash_context_struct g_fota_hash_context;
#endif


/****************** API sDefinition ******************/
#ifdef FOTA_HASH_HW_ALGORITHM_ENABLE
static void fota_hash_sha_hw_delay(void)
{
    /* When it is not bootloader use vTaskDelay() to release mcu to other task. Otherwise, if the reason of busy
        * returned is that a lower priority task is using sha hw algorithm, it will cause dead loop since the lower
        * priority task can never get mcu when using hal_gpt_delay_ms() and resource it taken will never be released.
        */

    hal_gpt_delay_ms(1);
}
#endif


uint32_t fota_hash_get_hash_length(fota_hash_type_enum hash_type)
{
    switch (hash_type) {
        case FOTA_HASH_TYPE_CRC32:  return FOTA_HASH_CRC32_SIZE;
        case FOTA_HASH_TYPE_SHA224: return FOTA_HASH_SHA224_SIZE;
        case FOTA_HASH_TYPE_SHA256: return FOTA_HASH_SHA256_SIZE;
        case FOTA_HASH_TYPE_SHA384: return FOTA_HASH_SHA384_SIZE;
        case FOTA_HASH_TYPE_SHA512: return FOTA_HASH_SHA512_SIZE;
        default:                    return 0;
    }
}


void fota_hash_context_free(void *context)
{
#ifndef FOTA_BL_ENABLE
    if (context) {
        k_free(context);
    }
#else
    g_fota_hash_context.in_use = FALSE;
#endif
}


void *fota_hash_sha_context_create(fota_hash_type_enum hash_type)
{
#ifndef FOTA_BL_ENABLE
#if defined(MBEDTLS_SHA256_C) || defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
    if (FOTA_HASH_TYPE_SHA224 == hash_type ||
        FOTA_HASH_TYPE_SHA256 == hash_type) {
#if defined(MBEDTLS_SHA256_C) && !defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
        return k_malloc(sizeof(mbedtls_sha256_context));
#else
        if (FOTA_HASH_TYPE_SHA224 == hash_type) {
            return k_malloc(sizeof(hal_sha224_context_t));
        }
        else {
            return k_malloc(sizeof(hal_sha256_context_t));
        }
#endif
    }
#endif

#if defined(MBEDTLS_SHA512_C) || defined(MBEDTLS_SHA384_C)
    if (FOTA_HASH_TYPE_SHA384 == hash_type ||
        FOTA_HASH_TYPE_SHA512 == hash_type) {
        return k_malloc(sizeof(mbedtls_sha512_context));
    }
#endif
#else
    if (!g_fota_hash_context.in_use) {
        g_fota_hash_context.in_use = TRUE;
        memset(&(g_fota_hash_context.hash_context), 0, sizeof(fota_hash_conext_union));
        return &(g_fota_hash_context.hash_context);
    }
#endif

    //FOTA_LOG_MSGID_E("fota_hash_sha_context_create fail. hash_type:%d", 1, hash_type);
    return NULL;
}


FOTA_ERRCODE fota_hash_sha_init(fota_hash_type_enum hash_type, void *context)
{
    FOTA_ERRCODE ret = FOTA_ERRCODE_UNSUPPORTED;

#if defined(MBEDTLS_SHA256_C) || defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
    if (FOTA_HASH_TYPE_SHA224 == hash_type ||
        FOTA_HASH_TYPE_SHA256 == hash_type) {
#if defined(MBEDTLS_SHA256_C) && !defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
        mbedtls_sha256_init((mbedtls_sha256_context *)context);
        ret = FOTA_ERRCODE_SUCCESS;
#else
        hal_sha_status_t status;
        memset(context, 0, hash_type == FOTA_HASH_TYPE_SHA224 ? sizeof(hal_sha224_context_t) : sizeof(hal_sha256_context_t));
        if (FOTA_HASH_TYPE_SHA224 == hash_type) {
            do {
                status = hal_sha224_init((hal_sha224_context_t *)context);
                if (HAL_SHA_STATUS_BUSY == status) {
                    fota_hash_sha_hw_delay();
                }
            } while (HAL_SHA_STATUS_BUSY == status);
        } else {
            do {
                status = hal_sha256_init((hal_sha256_context_t *)context);
                if (HAL_SHA_STATUS_BUSY == status) {
                    fota_hash_sha_hw_delay();
                }
            } while (HAL_SHA_STATUS_BUSY == status);
        }

        ret = (HAL_SHA_STATUS_OK == status) ? FOTA_ERRCODE_SUCCESS : FOTA_ERRCODE_FAIL;
#endif
    }
#endif

#if defined(MBEDTLS_SHA512_C) || defined(MBEDTLS_SHA384_C)
    if (FOTA_HASH_TYPE_SHA384 == hash_type ||
        FOTA_HASH_TYPE_SHA512 == hash_type) {
        mbedtls_sha512_init((mbedtls_sha512_context *)context);
        ret = FOTA_ERRCODE_SUCCESS;
    }
#endif

    printk("fota_hash_sha_init ret:%d", ret);
    return ret;
}


FOTA_ERRCODE fota_hash_sha_start(fota_hash_type_enum hash_type, void *context)
{
    int ret = 0;

#if defined(MBEDTLS_SHA256_C) && !defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
    if (FOTA_HASH_TYPE_SHA224 == hash_type) {
        ret = mbedtls_sha256_starts((mbedtls_sha256_context *)context, 1);
    } else if (FOTA_HASH_TYPE_SHA256 == hash_type) {
        ret = mbedtls_sha256_starts((mbedtls_sha256_context *)context, 0);
    }
/* #else Do nothing for hw algorithm. */
#endif

#if defined(MBEDTLS_SHA512_C) || defined(MBEDTLS_SHA384_C)
    if (FOTA_HASH_TYPE_SHA384 == hash_type) {
        ret = mbedtls_sha512_starts((mbedtls_sha512_context *)context, 1);
    } else if (FOTA_HASH_TYPE_SHA512 == hash_type) {
        ret = mbedtls_sha512_starts((mbedtls_sha512_context *)context, 0);
    }
#endif

    ret = ret ? FOTA_ERRCODE_FAIL : FOTA_ERRCODE_SUCCESS;
    printk("fota_hash_sha_start ret:%d", ret);
    return ret;
}


FOTA_ERRCODE fota_hash_sha_update(fota_hash_type_enum hash_type,
                                        void *context,
                                        const unsigned char *input,
                                        size_t ilen)
{
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;

#if defined(MBEDTLS_SHA256_C) || defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
    if (FOTA_HASH_TYPE_SHA224 == hash_type ||
        FOTA_HASH_TYPE_SHA256 == hash_type) {
#if defined(MBEDTLS_SHA256_C) && !defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
        ret = (mbedtls_sha256_update((mbedtls_sha256_context *)context, input, ilen) == 0) ? FOTA_ERRCODE_SUCCESS : FOTA_ERRCODE_FAIL;
#else
        hal_sha_status_t status;
        //FOTA_LOG_MSGID_I("hal_sha224_append start", 0);

        if (FOTA_HASH_TYPE_SHA224 == hash_type) {
            do {
                status = hal_sha224_append((hal_sha224_context_t *)context, (uint8_t *)input, ilen);
                if (HAL_SHA_STATUS_BUSY == status) {
                    fota_hash_sha_hw_delay();
                }
            } while (HAL_SHA_STATUS_BUSY == status);
        } else {
            do {
                status = hal_sha256_append((hal_sha256_context_t *)context, (uint8_t *)input, ilen);
                if (HAL_SHA_STATUS_BUSY == status) {
                    fota_hash_sha_hw_delay();
                }
            } while (HAL_SHA_STATUS_BUSY == status);
        }
        ret = (HAL_SHA_STATUS_OK == status) ? FOTA_ERRCODE_SUCCESS : FOTA_ERRCODE_FAIL;
#endif
    }
#endif

#if defined(MBEDTLS_SHA512_C) || defined(MBEDTLS_SHA384_C)
    if (FOTA_HASH_TYPE_SHA384 == hash_type ||
        FOTA_HASH_TYPE_SHA512 == hash_type) {

        ret = (mbedtls_sha512_update((mbedtls_sha512_context *)context, input, ilen) == 0) ? FOTA_ERRCODE_SUCCESS : FOTA_ERRCODE_FAIL;
    }
#endif

    //FOTA_LOG_MSGID_D("fota_hash_sha_update ret:%d", 1, ret);
    return ret;
}


FOTA_ERRCODE fota_hash_sha_finish(fota_hash_type_enum hash_type,
                                       void *context,
                                       uint8_t *output,
                                       uint32_t output_length)
{
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;

    if (!output || output_length < fota_hash_get_hash_length(hash_type)) {
        printk("fota_hash_sha_finish invalid param: output:%x output_length:%d hash_type:%d",
                         (unsigned int)output, output_length, hash_type);
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    memset(output, 0, output_length);

#if defined(MBEDTLS_SHA256_C) || defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
    if (FOTA_HASH_TYPE_SHA224 == hash_type ||
        FOTA_HASH_TYPE_SHA256 == hash_type) {
#if defined(MBEDTLS_SHA256_C) && !defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
        ret = (mbedtls_sha256_finish((mbedtls_sha256_context *)context, output) == 0) ? FOTA_ERRCODE_SUCCESS : FOTA_ERRCODE_FAIL;
#else
        hal_sha_status_t status;

        if (FOTA_HASH_TYPE_SHA224 == hash_type) {
            do {
                status = hal_sha224_end((hal_sha224_context_t *)context, (uint8_t*)output);
                if (HAL_SHA_STATUS_BUSY == status)
                    fota_hash_sha_hw_delay();
            } while (HAL_SHA_STATUS_BUSY == status);
        } else {
            do {
                status = hal_sha256_end((hal_sha256_context_t *)context, (uint8_t*)output);
                if (HAL_SHA_STATUS_BUSY == status)
                    fota_hash_sha_hw_delay();
            } while (HAL_SHA_STATUS_BUSY == status);
        }
        ret = (HAL_SHA_STATUS_OK == status) ? FOTA_ERRCODE_SUCCESS : FOTA_ERRCODE_FAIL;
#endif
    }
#endif

#if defined(MBEDTLS_SHA512_C) || defined(MBEDTLS_SHA384_C)
    if (FOTA_HASH_TYPE_SHA384 == hash_type ||
        FOTA_HASH_TYPE_SHA512 == hash_type) {

        ret = (mbedtls_sha512_finish((mbedtls_sha512_context *)context, output) == 0) ? FOTA_ERRCODE_SUCCESS : FOTA_ERRCODE_FAIL;
    }
#endif

    //FOTA_LOG_MSGID_D("fota_hash_sha_finish ret:%d", 1, ret);
    return ret;
}


void fota_hash_sha_free(fota_hash_type_enum hash_type, void *context)
{
#if defined(MBEDTLS_SHA256_C) && !defined(FOTA_HASH_HW_ALGORITHM_ENABLE)
    if (FOTA_HASH_TYPE_SHA224 == hash_type ||
        FOTA_HASH_TYPE_SHA256 == hash_type) {
        mbedtls_sha256_free((mbedtls_sha256_context *)context);
    }
/* #else Do nothing for hw algorithm. */
#endif

#if defined(MBEDTLS_SHA512_C) || defined(MBEDTLS_SHA384_C)
    if (FOTA_HASH_TYPE_SHA384 == hash_type ||
        FOTA_HASH_TYPE_SHA512 == hash_type) {
        mbedtls_sha512_free((mbedtls_sha512_context *)context);
    }
#endif
}


FOTA_ERRCODE fota_hash_sha_generate(fota_hash_type_enum hash_type,
                                          unsigned char *hash,
                                          uint32_t hash_len,
                                          uint32_t data_address,
                                          uint32_t data_length,
                                          FotaStorageType storage_type)
{
    int read_length = FOTA_LONG_DATA_READ_MAX_SIZE;
#ifdef FOTA_BL_ENABLE
    uint8_t buffer[FOTA_LONG_DATA_READ_MAX_SIZE] = {0};
#else
    uint8_t *buffer = NULL;
#endif
    void *hash_context = NULL;

    if (!data_length || !hash || hash_len < fota_hash_get_hash_length(hash_type) ||
        (InternalFlash != storage_type &&
         ExternalFlash != storage_type)) {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    hash_context = fota_hash_sha_context_create(hash_type);
    if (!hash_context) {
        return FOTA_ERRCODE_NOT_ENOUGH_MEMORY;
    }

#ifndef FOTA_BL_ENABLE
    buffer = (uint8_t *)k_malloc(FOTA_LONG_DATA_READ_MAX_SIZE);
    if (!buffer) {
        fota_hash_context_free(hash_context);
        return FOTA_ERRCODE_NOT_ENOUGH_MEMORY;
    }
#endif

    fota_hash_sha_init(hash_type, hash_context);
    fota_hash_sha_start(hash_type, hash_context);

    while (data_length > 0) {
        if (data_length < FOTA_LONG_DATA_READ_MAX_SIZE) {
            read_length = data_length;
        }

        if (true != fota_flash_read(data_address, buffer, read_length)) {
#ifndef FOTA_BL_ENABLE
            k_free(buffer);
#endif
            fota_hash_context_free(hash_context);
            return FOTA_ERRCODE_READ_FOTA_HEADER_FAIL;
        }

        fota_hash_sha_update(hash_type, hash_context, buffer, read_length);

        data_address += read_length;
        data_length -= read_length;
    }

#ifndef FOTA_BL_ENABLE
    k_free(buffer);
#endif

    fota_hash_sha_finish(hash_type, hash_context, hash, hash_len);
    fota_hash_sha_free(hash_type, hash_context);

    fota_hash_context_free(hash_context);
    return FOTA_ERRCODE_SUCCESS;
}


#ifndef FOTA_BL_ENABLE
/* Do not remove FOTA_BL_ENABLE within crc32 APIs in case that it is needed for bootloader in the future. */
void *fota_hash_crc32_context_create(void)
{
#ifndef FOTA_BL_ENABLE
    return k_malloc(sizeof(fota_hash_crc32_context_struct));
#else
    if (!g_fota_hash_context.in_use) {
        g_fota_hash_context.in_use = TRUE;
        memset(&(g_fota_hash_context.hash_context), 0, sizeof(fota_hash_conext_union));
        return &(g_fota_hash_context.hash_context);
    } else {
        return NULL;
    }
#endif
}


FOTA_ERRCODE fota_hash_crc32_init(void *context)
{
    if (context) {
        ((fota_hash_crc32_context_struct *)context)->crc32_value = 0xFFFFFFFF;
        return FOTA_ERRCODE_SUCCESS;
    }

    return FOTA_ERRCODE_INVALID_PARAMETER;
}


FOTA_ERRCODE fota_hash_crc32_update(void *context, const unsigned char *input, size_t ilen)
{
    // uint32_t *crc32_value = NULL;

    // if (context) {
    //     crc32_value = &(((fota_hash_crc32_context_struct *)context)->crc32_value);
    //     *crc32_value = crc32((uint8_t *)input, ilen, *crc32);
    //     return FOTA_ERRCODE_SUCCESS;
    // }

    return FOTA_ERRCODE_INVALID_PARAMETER;
}


FOTA_ERRCODE fota_hash_crc32_generate(unsigned char *hash,
                                            uint32_t hash_len,
                                            uint32_t data_address,
                                            uint32_t data_length,
                                            FotaStorageType storage_type)
{
#if defined(FOTA_RACE_CMD_CRC_SUPPORT)
    uint32_t crc32_init_value = 0xFFFFFFFF;
    int read_length = FOTA_LONG_DATA_READ_MAX_SIZE;
#ifdef FOTA_BL_ENABLE
    uint8_t buffer[FOTA_LONG_DATA_READ_MAX_SIZE] = {0};
#else
    uint8_t *buffer = NULL;
#endif

    if (!data_length || !hash || hash_len < FOTA_HASH_CRC32_SIZE ||
        (InternalFlash != storage_type &&
         ExternalFlash != storage_type)) {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

#ifndef FOTA_BL_ENABLE
    buffer = (uint8_t *)pvPortCalloc(1, FOTA_LONG_DATA_READ_MAX_SIZE);
    if (!buffer) {
        return FOTA_ERRCODE_NOT_ENOUGH_MEMORY;
    }
#endif

    while (data_length > 0) {
        if (data_length < FOTA_LONG_DATA_READ_MAX_SIZE) {
            read_length = data_length;
        }

        if (true != fota_flash_read(data_address, buffer, read_length)) {
#ifndef FOTA_BL_ENABLE
            vPortFree(buffer);
#endif
            return FOTA_ERRCODE_READ_FOTA_HEADER_FAIL;
        }

        crc32_init_value = crc32(buffer, read_length, crc32_init_value);
        data_address += read_length;
        data_length -= read_length;
    }

#ifndef FOTA_BL_ENABLE
    vPortFree(buffer);
#endif
    memcpy(hash, &crc32_init_value, FOTA_HASH_CRC32_SIZE);
    return FOTA_ERRCODE_SUCCESS;
#else
    return FOTA_ERRCODE_UNSUPPORTED;
#endif
}
#endif  /* FOTA_BL_ENABLE */


FOTA_ERRCODE fota_hash_generate(fota_hash_type_enum hash_type,
                                     unsigned char *hash,
                                     uint32_t hash_len,
                                     uint32_t data_address,
                                     uint32_t data_length,
                                     FotaStorageType storage_type)
{
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;

    if (FOTA_HASH_TYPE_CRC32 != hash_type) {
        ret = fota_hash_sha_generate( hash_type, hash, hash_len, data_address, data_length, storage_type);
    }
#ifndef FOTA_BL_ENABLE
    else {
        ret = fota_hash_crc32_generate(hash, hash_len, data_address, data_length, storage_type);
    }
#endif

    //FOTA_LOG_MSGID_I("fota_hash_generate ret:%d", 1, ret);
    return ret;
}

#ifndef FOTA_BL_ENABLE

/* Create context for non-blocking hash alogrithm. hash_context member and hash member of fota_hash_nb_context_struct will be created also. */
static void *fota_hash_nb_context_create(fota_hash_type_enum hash_type)
{
    void *hash_context = NULL, *nb_hash_context = NULL;
    uint32_t hash_len = fota_hash_get_hash_length(hash_type);

    if (hash_len) {
        hash_context = (FOTA_HASH_TYPE_CRC32 == hash_type) ?
                        fota_hash_crc32_context_create() :
                        fota_hash_sha_context_create(hash_type);

        if (hash_context) {
            nb_hash_context = k_malloc(sizeof(fota_hash_nb_context_struct) + hash_len);
            if (!nb_hash_context) {
                fota_hash_context_free(hash_context);
            } else {
                ((fota_hash_nb_context_struct*)nb_hash_context)->hash_context = hash_context;
                //uint8_t **hash = &(((fota_hash_nb_context_struct *)nb_hash_context)->hash);
                uint8_t *hash_ptr = (uint8_t *)nb_hash_context + sizeof(fota_hash_nb_context_struct);
                memmove(((fota_hash_nb_context_struct*)nb_hash_context)->hash, hash_ptr, hash_len);
                ((fota_hash_nb_context_struct*)nb_hash_context)->hash_len = hash_len;
            }
        }
    }

    return nb_hash_context;
}


/* Free context for non-blocking hash alogrithm. hash_context member of fota_hash_nb_context_struct will be created also. */
static void fota_hash_nb_context_free(void *context)
{
    if (context) {
        fota_hash_context_free(((fota_hash_nb_context_struct *)context)->hash_context);
        k_free(context);
    }
}


static FOTA_ERRCODE fota_hash_nb_context_init(void *context,
                                    fota_hash_type_enum hash_type,
                                    uint32_t data_address,
                                    uint32_t data_length,
                                    FotaStorageType storage_type,
                                    fota_hash_nb_generate_callback callback,
                                    void *user_data)
{
    fota_hash_nb_context_struct *nb_hash_context = context;
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;

    if (nb_hash_context) {
        nb_hash_context->hash_type = hash_type;
        nb_hash_context->data_address = data_address;
        nb_hash_context->data_length = data_length;
        nb_hash_context->storage_type = storage_type;
        nb_hash_context->processed_length = 0;
        nb_hash_context->callback = callback;
        nb_hash_context->user_data = user_data;
        nb_hash_context->result = FOTA_ERRCODE_FAIL;

        /* Init hash algorithm */
        if (FOTA_HASH_TYPE_CRC32 == hash_type) {
            ret = fota_hash_crc32_init(nb_hash_context->hash_context);
        } else {
            ret = fota_hash_sha_init(hash_type, nb_hash_context->hash_context);

        }
    }

    return ret;
}


static FOTA_ERRCODE fota_hash_nb_context_start(void *context)
{
    fota_hash_nb_context_struct *nb_hash_context = context;
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;

    if (nb_hash_context) {
        if (FOTA_HASH_TYPE_CRC32 == nb_hash_context->hash_type) {
            ret = FOTA_ERRCODE_SUCCESS; /* Do nothing for crc32 */
        } else {
            ret = fota_hash_sha_start(nb_hash_context->hash_type, nb_hash_context->hash_context);
        }
    }

    return ret;
}


static FOTA_ERRCODE fota_hash_nb_context_update(void *context)
{
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;
    uint8_t *buffer = NULL;
    uint32_t read_length = FOTA_HASH_LONG_DATA_READ_MAX_SIZE, unprocess_length = 0;
    fota_hash_nb_context_struct *nb_context_struct = (fota_hash_nb_context_struct *)context;
#ifdef FOTA_HASH_PERFORMANCE_DEBUG_ENABLE
    uint32_t local_time[2] = {0, 0};
#endif

    if (!nb_context_struct || !nb_context_struct->hash_context) {
        ret = FOTA_ERRCODE_INVALID_PARAMETER;
        if (nb_context_struct) {
            nb_context_struct->result = ret;
        }
        return ret;
    }

    if (nb_context_struct->data_length <= nb_context_struct->processed_length) {
        return FOTA_ERRCODE_SUCCESS;
    }

    buffer = k_malloc(FOTA_HASH_LONG_DATA_READ_MAX_SIZE);
    if (!buffer) {
        ret = FOTA_ERRCODE_NOT_ENOUGH_MEMORY;
        nb_context_struct->result = ret;
        return ret;
    }

    unprocess_length = nb_context_struct->data_length - nb_context_struct->processed_length;
    /* Only process FOTA_HASH_LONG_DATA_PROCESS_MAX_SIZE at a time to avoid block task. */
    if (FOTA_HASH_LONG_DATA_PROCESS_MAX_SIZE < unprocess_length) {
        unprocess_length = FOTA_HASH_LONG_DATA_PROCESS_MAX_SIZE;
    }

    fota_dvfs_lock();

#ifdef FOTA_HASH_PERFORMANCE_DEBUG_ENABLE
    printk("[FOTA HASH] hash calc start. %d bytes", unprocess_length);
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &local_time[0]);
#endif
    ret = FOTA_ERRCODE_SUCCESS;
    while (0 < unprocess_length) {
        if (read_length > unprocess_length) {
            read_length = unprocess_length;
        }

        ret = fota_flash_read(nb_context_struct->data_address + nb_context_struct->processed_length,
                              buffer, read_length);
        if (true != ret) {
            break;
        }

        if (FOTA_HASH_TYPE_CRC32 == nb_context_struct->hash_type) {
            ret = fota_hash_crc32_update(nb_context_struct->hash_context, buffer, read_length);
        } else {
            ret = fota_hash_sha_update(nb_context_struct->hash_type, nb_context_struct->hash_context, buffer, read_length);
        }

        if (FOTA_ERRCODE_SUCCESS != ret) {
            break;
        }

        nb_context_struct->processed_length += read_length;
        unprocess_length -= read_length;
    }

#ifdef FOTA_HASH_PERFORMANCE_DEBUG_ENABLE
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &local_time[1]);
    hal_gpt_get_duration_count(local_time[0], local_time[1], &local_time[0]);
    printk("[FOTA HASH] hash calc end. ret:%d duration:%d ms", ret, local_time[0] / 1000);
#endif

    fota_dvfs_unlock();

    k_free(buffer);
    buffer = NULL;

    if (FOTA_ERRCODE_SUCCESS == ret) {
        if (nb_context_struct->data_length > nb_context_struct->processed_length) {
            ret = FOTA_ERRCODE_WOULDBLOCK;
        } else {
            /* Finish */
            nb_context_struct->result = FOTA_ERRCODE_SUCCESS;
        }
    }

    return ret;
}


/* Finish hash algorithm and invoke callback. */
static void fota_hash_nb_context_finish(void *context)
{
    fota_hash_nb_context_struct *nb_context_struct = (fota_hash_nb_context_struct *)context;

    if (!nb_context_struct || !nb_context_struct->hash_context) {
        return;
    }

    if (FOTA_ERRCODE_SUCCESS == nb_context_struct->result) {
        if (FOTA_HASH_TYPE_CRC32 == nb_context_struct->hash_type) {
            memcpy(nb_context_struct->hash, &(((fota_hash_crc32_context_struct *)nb_context_struct->hash_context)->crc32_value), FOTA_HASH_CRC32_SIZE);
        } else {
            nb_context_struct->result = fota_hash_sha_finish(nb_context_struct->hash_type,
                                                             nb_context_struct->hash_context,
                                                             nb_context_struct->hash,
                                                             nb_context_struct->hash_len);
            fota_hash_sha_free(nb_context_struct->hash_type, nb_context_struct->hash_context);
        }
    }
}
#endif


/* If return value is not FOTA_ERRCODE_WOULDBLOCK, callback will be inovked. Otherwise, context will be returned and call
 * fota_hash_nb_generate_continue() using the context returned to continue the hash calculation.
 */
FOTA_ERRCODE fota_hash_nb_generate(void **context,
                                         fota_hash_type_enum hash_type,
                                         uint32_t data_address,
                                         uint32_t data_length,
                                         FotaStorageType storage_type,
                                         fota_hash_nb_generate_callback callback,
                                         void *user_data)
{
#ifndef FOTA_BL_ENABLE
    fota_hash_nb_context_struct *nb_hash_context = fota_hash_nb_context_create(hash_type);
    FOTA_ERRCODE ret = FOTA_ERRCODE_FAIL;

    if (!context || *context || !callback) {
        ret = FOTA_ERRCODE_INVALID_PARAMETER;
        goto end;
    }

    if (nb_hash_context) {
        ret = fota_hash_nb_context_init(nb_hash_context, hash_type, data_address,
                                        data_length, storage_type, callback, user_data);
        if (FOTA_ERRCODE_SUCCESS != ret) {
            goto end;
        }

        ret = fota_hash_nb_context_start(nb_hash_context);
        if (FOTA_ERRCODE_SUCCESS != ret) {
            goto end;
        }

        ret = fota_hash_nb_context_update(nb_hash_context);
        if (FOTA_ERRCODE_WOULDBLOCK == ret) {
            *context = nb_hash_context;
            //FOTA_LOG_MSGID_D("fota_hash_nb_generate ret:%d", 1, ret);
            return ret;
        } else if (FOTA_ERRCODE_SUCCESS == ret) {
            fota_hash_nb_context_finish(nb_hash_context);
        }
    }

end:
    if (callback) {
        if (FOTA_ERRCODE_SUCCESS != ret) {
            callback(ret,
                     hash_type,
                     NULL,
                     0,
                     user_data);
        } else {
            callback(nb_hash_context->result,
                     hash_type,
                     nb_hash_context->hash,
                     nb_hash_context->hash_len,
                     user_data);
        }
    }

    if (nb_hash_context) {
        fota_hash_nb_context_free(nb_hash_context);
    }

    //FOTA_LOG_MSGID_I("fota_hash_nb_generate ret:%d", 1, ret);
    return ret;
#else
    return FOTA_ERRCODE_UNSUPPORTED;
#endif
}


/* If return value is not FOTA_ERRCODE_WOULDBLOCK, callback will be inovked. Otherwise,  call fota_hash_nb_generate_continue()
 * to continue the hash calculation.
 */
FOTA_ERRCODE fota_hash_nb_generate_continue(void *context)
{
#ifndef FOTA_BL_ENABLE
    FOTA_ERRCODE ret = FOTA_ERRCODE_INVALID_PARAMETER;
    fota_hash_nb_context_struct *nb_hash_context = context;

    if (nb_hash_context) {
        ret = fota_hash_nb_context_update(nb_hash_context);
        if (FOTA_ERRCODE_WOULDBLOCK == ret) {
            return ret;
        } else if (FOTA_ERRCODE_SUCCESS == ret) {
            fota_hash_nb_context_finish(nb_hash_context);
        }

        if (nb_hash_context->callback) {
            nb_hash_context->callback(nb_hash_context->result,
                                      nb_hash_context->hash_type,
                                      nb_hash_context->hash,
                                      nb_hash_context->hash_len,
                                      nb_hash_context->user_data);
        }

        fota_hash_nb_context_free(nb_hash_context);
    }

    return ret;
#else
    return FOTA_ERRCODE_UNSUPPORTED;
#endif
}


void fota_hash_nb_generate_cancel(void *context)
{
#ifndef FOTA_BL_ENABLE
    fota_hash_nb_context_struct *nb_hash_context = context;

    if (nb_hash_context) {
        if (nb_hash_context->callback) {
            nb_hash_context->callback(nb_hash_context->result,
                                      nb_hash_context->hash_type,
                                      nb_hash_context->hash,
                                      nb_hash_context->hash_len,
                                      nb_hash_context->user_data);
        }

        fota_hash_nb_context_free(nb_hash_context);
    }
#endif
}

#ifdef AIR_FOTA_ECDSA_ENABLE
static FOTA_ERRCODE fota_signature_ecdsa384_verify(const unsigned char *public_key,
                                                         uint32_t public_key_size,
                                                         uint8_t *signature,
                                                         uint32_t signature_length,
                                                         uint8_t *hash,
                                                         uint32_t hash_length)
{
#if defined(MBEDTLS_PK_C) && defined(MBEDTLS_PK_PARSE_C) && defined(MBEDTLS_ECDSA_C) && defined(AIR_FOTA_ECDSA_ENABLE)
    int ret = 0;
    mbedtls_pk_context pub_pk;

    if (!public_key || !public_key_size || !signature || !hash ||
        (FOTA_HASH_SHA384_SIZE > hash_length)) {
        printk("into fota_signature_ecdsa384_verify, hash_length:%d", hash_length);
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }

    mbedtls_pk_init(&pub_pk);
    ret = mbedtls_pk_parse_public_key(&pub_pk, public_key, public_key_size);
    printk("mbedtls_pk_parse_public_key:%x", -ret);
    if (0 == ret) {
        ret = mbedtls_pk_verify_ext(MBEDTLS_PK_ECDSA,
                                    NULL,
                                    &pub_pk,
                                    MBEDTLS_MD_SHA384,
                                    (const unsigned char *)hash,
                                    FOTA_HASH_SHA384_SIZE,
                                    signature,
                                    signature_length);
        //FOTA_LOG_MSGID_I("mbedtls_pk_verify_ext:%x", 1, -ret);
    }

    return ret ? FOTA_ERRCODE_CHECK_INTEGRITY_FAIL : FOTA_ERRCODE_SUCCESS;
#else
    return FOTA_ERRCODE_UNSUPPORTED;
#endif
}


uint32_t fota_signature_ecdsa_get_signature_size(uint8_t *signature, uint32_t signature_length)
{
    size_t size = 0;
    int ret = -1;

#if defined(MBEDTLS_ASN1_PARSE_C)
    if (signature && signature_length) {
        ret = mbedtls_asn1_get_tag(&signature, signature + signature_length - 1, &size,
                                   MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
        if (0 == ret) {
            size += 2; /* Tag is TLV format. Add 2 bytes for the type byte and the length byte. */
        }
    }
#endif

    printk("signature size:%x ret:%x", size, ret);
    return size;
}
#endif


FOTA_ERRCODE fota_signature_verify(fota_integrity_check_type_enum integrity_check_type,
                                      uint8_t *signature,
                                      uint32_t signature_length,
                                      uint8_t *hash,
                                      uint32_t hash_length)
{
    if (!signature || !hash) {
        return FOTA_ERRCODE_INVALID_PARAMETER;
    }
#ifndef AIR_FOTA_ECDSA_ENABLE
    int ret = -1;

    if (FOTA_INTEGRITY_CHECK_TYPE_CRC32 == integrity_check_type) {
        if (FOTA_HASH_CRC32_SIZE <= signature_length &&
            FOTA_HASH_CRC32_SIZE <= hash_length) {
            ret = memcmp(signature, hash, FOTA_HASH_CRC32_SIZE);
        }
        return ret ? FOTA_ERRCODE_CHECK_INTEGRITY_FAIL : FOTA_ERRCODE_SUCCESS;
    } else if (FOTA_INTEGRITY_CHECK_TYPE_SHA256 == integrity_check_type) {
        if (FOTA_HASH_SHA256_SIZE <= signature_length &&
            FOTA_HASH_SHA256_SIZE <= hash_length) {
            ret = memcmp(signature, hash, FOTA_HASH_SHA256_SIZE);
        }
        return ret ? FOTA_ERRCODE_CHECK_INTEGRITY_FAIL : FOTA_ERRCODE_SUCCESS;
    }
#else
    uint32_t signature_size = fota_signature_ecdsa_get_signature_size(signature, signature_length);

    if (signature_size) {
        return fota_signature_ecdsa384_verify((const unsigned char *)FOTA_SIGNATURE_ECDSA384_PUBKEY,
                                              strlen(FOTA_SIGNATURE_ECDSA384_PUBKEY) + 1,
                                              signature, signature_size, hash, hash_length);
    }
#endif

    return FOTA_ERRCODE_UNSUPPORTED;
}


fota_hash_type_enum fota_signature_get_hash_type(fota_integrity_check_type_enum integrity_check_type)
{
    if (FOTA_INTEGRITY_CHECK_TYPE_CRC32 == integrity_check_type) {
        return FOTA_HASH_TYPE_CRC32;
    } else if (FOTA_INTEGRITY_CHECK_TYPE_SHA256 == integrity_check_type ||
               FOTA_INTEGRITY_CHECK_TYPE_SHA256_RSA == integrity_check_type) {
        return FOTA_HASH_TYPE_SHA256;
    } else if (FOTA_INTEGRITY_CHECK_TYPE_ECDSA384 == integrity_check_type) {
        return FOTA_HASH_TYPE_SHA384;
    }

    return FOTA_HASH_TYPE_MAX;
}

