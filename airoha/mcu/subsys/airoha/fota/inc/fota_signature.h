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

#ifndef __FOTA_SIGNATURE_H__
#define __FOTA_SIGNATURE_H__

#include "fota_util.h"


#ifdef FOTA_STORE_IN_EXTERNAL_FLASH
#define FOTA_HASH_LONG_DATA_READ_MAX_SIZE      (1024)
/* For non-block API */
#define FOTA_HASH_LONG_DATA_PROCESS_MAX_SIZE   (0x400000)
#else
#define FOTA_HASH_LONG_DATA_READ_MAX_SIZE      (256)
/* For non-block API */
#define FOTA_HASH_LONG_DATA_PROCESS_MAX_SIZE   (0x400000)
#endif /* FOTA_STORE_IN_EXTERNAL_FLASH */


typedef enum {
    FOTA_HASH_TYPE_CRC32,
    FOTA_HASH_TYPE_SHA224,
    FOTA_HASH_TYPE_SHA256,
    FOTA_HASH_TYPE_SHA384,
    FOTA_HASH_TYPE_SHA512,

    FOTA_HASH_TYPE_MAX = 0xFF
} fota_hash_type_enum;


#define FOTA_HASH_CRC32_SIZE     (4)

#define FOTA_HASH_SHA224_SIZE    (28)
#define FOTA_HASH_SHA256_SIZE    (32)
#define FOTA_HASH_SHA384_SIZE    (48)
#define FOTA_HASH_SHA512_SIZE    (64)

#define FOTA_HASH_MAX_SIZE    (FOTA_HASH_SHA512_SIZE)


/* Normally, ECDSA signature size could be 102, 103 or 104 bytes. */
#define FOTA_SIGNATURE_ECDSA384_MAX_SIZE (104)
#define FOTA_SIGNATURE_ECDSA384_MIN_SIZE (102)

/* 256 bytes are reserved for the signature in the header of the FOTA package file. However, the longest signature
  * for now is ECDSA signature. 128 bytes is long enough for a ECDSA signature.
  */
#define FOTA_SIGNATURE_MAX_SIZE (128)


typedef struct {
    uint32_t crc32_value;
} fota_hash_crc32_context_struct;

typedef void(*fota_hash_nb_generate_callback)(FOTA_ERRCODE result, \
                                                 fota_hash_type_enum hash_type, \
                                                 uint8_t *hash, \
                                                 uint32_t hash_len, \
                                                 void *user_data);

typedef struct {
    void *hash_context;
    fota_hash_type_enum hash_type;
    uint32_t data_address;
    uint32_t data_length;
    FotaStorageType storage_type;
    uint32_t processed_length;
    fota_hash_nb_generate_callback callback;
    void *user_data;
    FOTA_ERRCODE result;
    uint32_t hash_len;
    uint8_t hash[0];
} fota_hash_nb_context_struct;


uint32_t fota_hash_get_hash_length(fota_hash_type_enum hash_type);

void fota_hash_context_free(void *context);

void *fota_hash_sha_context_create(fota_hash_type_enum hash_type);

FOTA_ERRCODE fota_hash_sha_init(fota_hash_type_enum hash_type, void *context);

FOTA_ERRCODE fota_hash_sha_start(fota_hash_type_enum hash_type, void *context);

FOTA_ERRCODE fota_hash_sha_update(fota_hash_type_enum hash_type,
                         void *context,
                         const unsigned char *input,
                         size_t ilen);

FOTA_ERRCODE fota_hash_sha_finish(fota_hash_type_enum hash_type,
                                       void *context,
                                       uint8_t *output,
                                       uint32_t output_length);

void fota_hash_sha_free(fota_hash_type_enum hash_type, void *context);

FOTA_ERRCODE fota_hash_sha_generate(fota_hash_type_enum hash_type,
                                     unsigned char *hash,
                                     uint32_t hash_len,
                                     uint32_t data_address,
                                     uint32_t data_length,
                                     FotaStorageType storage_type);

#ifndef FOTA_BL_ENABLE
void *fota_hash_crc32_context_create(void);

FOTA_ERRCODE fota_hash_crc32_init(void *context);

FOTA_ERRCODE fota_hash_crc32_update(void *context, const unsigned char *input, size_t ilen);

FOTA_ERRCODE fota_hash_crc32_generate(unsigned char *hash,
                                            uint32_t hash_len,
                                            uint32_t data_address,
                                            uint32_t data_length,
                                            FotaStorageType storage_type);
#endif

FOTA_ERRCODE fota_hash_generate(fota_hash_type_enum hash_type,
                                     unsigned char *hash,
                                     uint32_t hash_len,
                                     uint32_t data_address,
                                     uint32_t data_length,
                                     FotaStorageType storage_type);

FOTA_ERRCODE fota_hash_nb_generate(void **context,
                                         fota_hash_type_enum hash_type,
                                         uint32_t data_address,
                                         uint32_t data_length,
                                         FotaStorageType storage_type,
                                         fota_hash_nb_generate_callback callback,
                                         void *user_data);

FOTA_ERRCODE fota_hash_nb_generate_continue(void *context);

void fota_hash_nb_generate_cancel(void *context);

/* Get the actual size of an ECDSA signature.
  * signature[IN]: a pointer points to a buffer which stores a signature.
  * signature_length[IN]: the length of the buffer.
  * return: 0: error occurrs; otherwise, the actual size of the signature.
  */
uint32_t fota_signature_ecdsa_get_signature_size(uint8_t *signature, uint32_t signature_length);

FOTA_ERRCODE fota_signature_verify(fota_integrity_check_type_enum integrity_check_type,
                                      uint8_t *signature,
                                      uint32_t signature_length,
                                      uint8_t *hash,
                                      uint32_t hash_length);

fota_hash_type_enum fota_signature_get_hash_type(fota_integrity_check_type_enum integrity_check_type);
#endif /*__FOTA_SIGNATURE_H__*/

