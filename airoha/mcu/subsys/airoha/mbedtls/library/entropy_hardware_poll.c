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

#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT)
#include <string.h>
#include "entropy_poll.h"

//#define AIR_PLATFORM_SUPPORT_TRNG

#ifdef AIR_PLATFORM_SUPPORT_TRNG
#include "hal_rng.h"
#endif


int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
#ifdef AIR_PLATFORM_SUPPORT_TRNG
    uint32_t random_seed = 0;
    hal_rng_status_t ret = HAL_RNG_STATUS_ERROR;

    ((void) data);

    if (len < sizeof(uint32_t)) {
        return (-1);
    }

    ret = hal_rng_get_generated_random_number(&random_seed);
    //printf("mbedtls_hardware_poll ret=%d output=0x%08X\r\n", ret, random_seed);
    if (HAL_RNG_STATUS_OK != ret) {
        return (-2);
    }

    memcpy(output, &random_seed, sizeof(uint32_t));
#else
    if (len < sizeof(uint32_t)) {
        return (-1);
    }
    uint32_t random_seed = rand();
    memcpy(output, &random_seed, sizeof(uint32_t));
#endif

    *olen = sizeof(uint32_t);
    return (0);
}
#endif /* MBEDTLS_ENTROPY_HARDWARE_ALT */

