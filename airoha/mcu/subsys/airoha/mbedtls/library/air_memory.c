/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("\r\nAiroha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("\r\nAiroha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("\r\nLicense Agreement") and been granted explicit permission to do so within
 * the License Agreement ("\r\nPermitted User").  If you are not a Permitted User,
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



#include "common.h"

#ifdef AIR_MBEDTLS_CODE_OPTIMIZE
#include "air_memory.h"

void* mbedtls_air_malloc(size_t size)
{
    // Brom change
    return k_malloc(size);
}

void  mbedtls_air_free(void *ptr)
{
    // Brom change
    k_free(ptr);
}

void *mbedtls_air_calloc(size_t nmemb, size_t size)
{
    // Brom change, sboot_malloc->memset(0)
    return k_calloc(nmemb, size);
}

void* air_mbedtls_word_memset(void* dst, size_t value, size_t size)
{
#ifndef _WIN32
      __asm(
          ".syntax unified\n"
          "push {r3-r4, LR} \n"
          "movs  r3, r0\n"
          "lsrs r4, r2, #2\n"
          "BEQ  memset_end\n"
     "memset_loop:\n"
          "STMIA  r3!, {r1}\n"
          "SUBS   r4, r4, #1\n"
          "BNE  memset_loop\n"
     "memset_end:\n"
          "pop {r3-r4, PC} \n"
    );
#else
    unsigned int  i, len;
    int* pdst = (int*)dst;

    for (i = size >> 2; i != 0; i--) {
        *pdst++ = (int)value;
    }

    len = size & 3;
    if (len != 0) {
        printk("air_mbedtls_word_memset, not_align_4 size=%d %d\r\n", size, len);
        char* p_pdst = (char*)pdst;
        for (i = len; i != 0; i--) {
            *p_pdst++ = value;
        }
    }
#endif
    return dst;
}

void *air_mbedtls_word_memcpy(void *dst, const void *src, size_t size)
{
#ifndef _WIN32
      __asm(
          ".syntax unified\n"
          "push {r3-r6, LR} \n"
          "movs r4, r0\n"
          "movs r5, r1\n"
          "lsrs r3, r2, #2\n"
     "memcpy_loop:\n"
          "LDMIA  r5!, {r6}\n"
          "STMIA  r4!, {r6}\n"
          "SUBS   r3, r3, #1\n"
          "BNE  memcpy_loop\n"
          "pop {r3-r6, PC} \n"
    );
#else
    unsigned int  i, len;
    int* pdst = (int*)dst;
    int* psrc = (int*)src;

    for (i = size >> 2; i != 0; i--) {
        *pdst++ = *psrc++;
    }

    len = size & 3;
    if (len != 0) {
        printk("air_mbedtls_word_memcpy, not_align_4 size=%d %d\r\n", size, len);
        char* p_pdst = (char*)pdst;
        char* p_psrc = (char*)psrc;
        for (i = len; i != 0; i--) {
            *p_pdst++ = *p_psrc++;
        }
    }

#endif
    return dst;
}

#endif  // AIR_MBEDTLS_CODE_OPTIMIZE
