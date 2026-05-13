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

#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include "factory_reset.h"
#include "nvkey.h"
#include <hal_wdt.h>

#define thisMODULE fctrst
#define thisMOD    "fctrst"
LOG_MODULE_REGISTER(thisMODULE);

void factory_reset_enable(void)
{
    uint8_t factory_reset = true;
    nvkey_status_t nvkey_ret = nvkey_write_data(NVID_FACTORY_RESET, &factory_reset, sizeof(factory_reset));
    DBG_LOGI(thisMOD, "factory_reset_enable nvkey_ret = %d", nvkey_ret);
    if (nvkey_ret == NVKEY_STATUS_OK) {
        hal_wdt_software_reset();
    }
}

uint8_t factory_reset_handler(const uint16_t *nvkey_id_list, uint32_t list_size)
{
    uint8_t setting;
    uint32_t nvkey_size = sizeof(setting);
    nvkey_status_t nvkey_ret = nvkey_read_data(NVID_FACTORY_RESET, &setting, &nvkey_size);

    if (nvkey_ret != NVKEY_STATUS_OK) {
        return WITHOUT_FACTORY_RESET;
    }

    for (uint32_t i = 0; i < list_size; i++) {
        nvkey_ret = nvkey_delete_data_item(nvkey_id_list[i]);
        if (nvkey_ret != NVKEY_STATUS_OK) {
            return FACTORY_RESET_FAIL;
        }
        DBG_LOGI(thisMOD, "Delete nvkey_id = %x, nvkey_ret = %d", nvkey_id_list[i], nvkey_ret);
    }

    nvkey_ret = nvkey_delete_data_item(NVID_FACTORY_RESET);
    if (nvkey_ret == NVKEY_STATUS_OK) {
        return FACTORY_RESET_OK;
    } 
    else {
        return FACTORY_RESET_FAIL;
    }
}