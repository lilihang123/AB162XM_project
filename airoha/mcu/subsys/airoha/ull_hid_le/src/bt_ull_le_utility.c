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

#include "bt_ull_le_hid_utility.h"
#include <stdlib.h>

/**************************************************************************************************
* Public Functions
**************************************************************************************************/
void *bt_ull_le_srv_memcpy(void *dest, const void *src, uint32_t size)
{
    if ((NULL == dest) || (NULL == src)) {
        return NULL;
    }
    return memcpy(dest, src, size);
}

void *bt_ull_le_srv_memory_alloc(uint16_t size)
{
    void *memory = (void *)k_malloc(size);
    if (NULL != memory) {
        memset(memory, 0, size);
    }
    return memory;
}

void bt_ull_le_srv_memory_free(void *point)
{
	/* This log is for QC test */
	printk("[ULL][LE][Util]bt_ull_le_srv_memory_free point = 0x%x", point);
    if (point) {
        k_free(point);
    }
}

void *bt_ull_le_srv_memset(void *buf, uint8_t value, uint32_t size)
{
    return memset(buf, value, size);
}

int32_t bt_ull_le_srv_memcmp(const void *buf1, const void *buf2, uint32_t size)
{
    return memcmp(buf1, buf2, size);
}

int bt_ull_le_bytes_from_str(uint8_t *buf, int buf_len, const char *src)
{
	unsigned int i;
	char *endptr;

	for (i = 0U; i < strlen(src); i++) {
		if (!(src[i] >= '0' && src[i] <= '9') &&
		    !(src[i] >= 'A' && src[i] <= 'F') &&
		    !(src[i] >= 'a' && src[i] <= 'f') &&
		    src[i] != ':') {
			return -EINVAL;
		}
	}

	(void)memset(buf, 0, buf_len);

	for (i = 0U; i < buf_len; i++) {
		buf[i] = strtol(src, &endptr, 16);
		src = ++endptr;
	}

	return 0;
}