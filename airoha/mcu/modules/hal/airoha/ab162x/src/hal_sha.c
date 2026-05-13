/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#include "hal_sha.h"

#ifdef HAL_SHA_MODULE_ENABLED

#include "stddef.h"
#include "hal_crypt_sha.h"
#include "hal_log.h"
#include "hal_crypt_internal.h"
#include "hal_clock.h"
#ifdef HAL_SLEEP_MANAGER_ENABLED
#include "hal_spm.h"
#endif

#include <zephyr/sys/printk.h>
#define printf(msg, ...) printk("[HAL_SHA]" msg "\r\n", ##__VA_ARGS__)
#undef log_hal_msgid_info
#define log_hal_msgid_info(msg, cnt, ...) printk("[HAL_SHA]" msg "\r\n", ##__VA_ARGS__)
#undef log_hal_msgid_error
#define log_hal_msgid_error(msg, cnt, ...) printk("[HAL_SHA]" msg "\r\n", ##__VA_ARGS__)

#ifdef HAL_SLEEP_MANAGER_ENABLED
static void hal_sha_mtcmos_perisys_enable(bool en_req)
{
   static bool cur_setting = false;

   log_hal_msgid_info("hal_sha_mtcmos_perisys_enable, en_req = %d, cur_setting = %d", 2, en_req, cur_setting);
   if (en_req == true && cur_setting == false) {
       spm_control_mtcmos(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_ENABLE);
   } else if (en_req == false && cur_setting == true) {
       spm_control_mtcmos(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
   }
   cur_setting = en_req;
}
#endif

static void hal_sha_hw_enable(void)
{
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(true);
#endif
#ifndef FPGA_ENV
    hal_clock_enable(HAL_CLOCK_CG_CRYPTO);
#endif
}
static void hal_sha_hw_disable(void)
{
#ifndef FPGA_ENV
    hal_clock_disable(HAL_CLOCK_CG_CRYPTO);
#endif
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(false);
#endif
}

hal_sha_status_t hal_sha1_init(hal_sha1_context_t *context)
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }

    hal_sha_hw_enable();

    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA1);

    hal_sha_hw_disable();

    hal_crypt_lock_give();
    return status;
}

hal_sha_status_t hal_sha1_append(hal_sha1_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_msgid_error("context is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_msgid_error("message is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }

    hal_sha_hw_enable();

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA1_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA1);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA1_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA1);
            break;
        }
    }
    hal_sha_hw_disable();
    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}

hal_sha_status_t hal_sha1_end(hal_sha1_context_t *context, uint8_t digest_message[HAL_SHA1_DIGEST_SIZE])
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
    hal_sha_hw_enable();

    status = crypt_sha_end((SHA1_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA1);

    hal_sha_hw_disable();
    hal_crypt_lock_give();
    return status;
}

hal_sha_status_t hal_sha224_init(hal_sha224_context_t *context)
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
    hal_sha_hw_enable();

    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA224);

    hal_sha_hw_disable();
    hal_crypt_lock_give();
    return status;
}

hal_sha_status_t hal_sha224_append(hal_sha224_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_msgid_error("context is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_msgid_error("message is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
    hal_sha_hw_enable();

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA224_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA224);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA224_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA224);
            break;
        }
    }

    hal_sha_hw_disable();
    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}

hal_sha_status_t hal_sha224_end(hal_sha224_context_t *context, uint8_t digest_message[HAL_SHA224_DIGEST_SIZE])
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
    hal_sha_hw_enable();

    status = crypt_sha_end((SHA224_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA224);

    hal_sha_hw_disable();
    hal_crypt_lock_give();
    return status;
}

hal_sha_status_t hal_sha256_init(hal_sha256_context_t *context)
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
    hal_sha_hw_enable();

    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA256);

    hal_sha_hw_disable();
    hal_crypt_lock_give();
    return status;
}

hal_sha_status_t hal_sha256_append(hal_sha256_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_msgid_error("context is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_msgid_error("message is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
    hal_sha_hw_enable();

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA256_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA256);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA256_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA256);
            break;
        }
    }

    hal_sha_hw_disable();
    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}

hal_sha_status_t hal_sha256_end(hal_sha256_context_t *context, uint8_t digest_message[HAL_SHA256_DIGEST_SIZE])
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
    hal_sha_hw_enable();

    status = crypt_sha_end((SHA256_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA256);

    hal_sha_hw_disable();
    hal_crypt_lock_give();
    return status;
}

hal_sha_status_t hal_sha384_init(hal_sha384_context_t *context)
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(true);
#endif
#ifndef FPGA_ENV
    hal_clock_enable(HAL_CLOCK_CG_CRYPTO);
#endif

    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA384);

#ifndef FPGA_ENV
    hal_clock_disable(HAL_CLOCK_CG_CRYPTO);
#endif
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(false);
#endif
    hal_crypt_lock_give();
    return status;
}
hal_sha_status_t hal_sha384_append(hal_sha384_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_msgid_error("context is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_msgid_error("message is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(true);
#endif
#ifndef FPGA_ENV
    hal_clock_enable(HAL_CLOCK_CG_CRYPTO);
#endif

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA384_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA384);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA384_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA384);
            break;
        }
    }

#ifndef FPGA_ENV
    hal_clock_disable(HAL_CLOCK_CG_CRYPTO);
#endif
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(false);
#endif
    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}
hal_sha_status_t hal_sha384_end(hal_sha384_context_t *context, uint8_t digest_message[HAL_SHA384_DIGEST_SIZE])
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(true);
#endif
#ifndef FPGA_ENV
    hal_clock_enable(HAL_CLOCK_CG_CRYPTO);
#endif

    status = crypt_sha_end((SHA384_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA384);

#ifndef FPGA_ENV
    hal_clock_disable(HAL_CLOCK_CG_CRYPTO);
#endif
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(false);
#endif
    hal_crypt_lock_give();
    return status;
}
hal_sha_status_t hal_sha512_init(hal_sha512_context_t *context)
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(true);
#endif
#ifndef FPGA_ENV
    hal_clock_enable(HAL_CLOCK_CG_CRYPTO);
#endif

    status = crypt_sha_init((SHA_CTX_STRUC *)context, HAL_SHA_INTERNAL_SHA512);

#ifndef FPGA_ENV
    hal_clock_disable(HAL_CLOCK_CG_CRYPTO);
#endif
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(false);
#endif
    hal_crypt_lock_give();
    return status;
}
hal_sha_status_t hal_sha512_append(hal_sha512_context_t *context, uint8_t *message, uint32_t length)
{
    if (NULL == context) {
        log_hal_msgid_error("context is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }
    if (NULL == message) {
        log_hal_msgid_error("message is NULL.", 0);
        return HAL_SHA_STATUS_ERROR;
    }

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(true);
#endif
#ifndef FPGA_ENV
    hal_clock_enable(HAL_CLOCK_CG_CRYPTO);
#endif

    while (1) {
        if (length >= MAX_APPEND_LENGTH) {
            crypt_sha_append((SHA512_CTX_STRUC *)context, message, MAX_APPEND_LENGTH, HAL_SHA_INTERNAL_SHA512);
            message += MAX_APPEND_LENGTH;
            length -= MAX_APPEND_LENGTH;
        } else {
            crypt_sha_append((SHA512_CTX_STRUC *)context, message, length, HAL_SHA_INTERNAL_SHA512);
            break;
        }
    }

#ifndef FPGA_ENV
    hal_clock_disable(HAL_CLOCK_CG_CRYPTO);
#endif
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(false);
#endif
    hal_crypt_lock_give();
    return HAL_SHA_STATUS_OK;
}
hal_sha_status_t hal_sha512_end(hal_sha512_context_t *context, uint8_t digest_message[HAL_SHA512_DIGEST_SIZE])
{
    hal_sha_status_t status;

    if (hal_crypt_lock_take() == HAL_SHA_STATUS_BUSY) {
        return HAL_SHA_STATUS_BUSY;
    }
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(true);
#endif
#ifndef FPGA_ENV
    hal_clock_enable(HAL_CLOCK_CG_CRYPTO);
#endif

    status = crypt_sha_end((SHA512_CTX_STRUC *)context, digest_message, HAL_SHA_INTERNAL_SHA512);

#ifndef FPGA_ENV
    hal_clock_disable(HAL_CLOCK_CG_CRYPTO);
#endif
#ifdef HAL_SLEEP_MANAGER_ENABLED
    hal_sha_mtcmos_perisys_enable(false);
#endif
    hal_crypt_lock_give();
    return status;
}

#endif /* HAL_SHA_MODULE_ENABLED */

