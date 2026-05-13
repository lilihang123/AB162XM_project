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
 
#include "application.h"

#define LOG_LEVEL LOG_LEVEL_INFO

#define thisMODULE main
#define thisMOD    "main"
LOG_MODULE_REGISTER(main);


#include "air_version.h"
#include "hal_gpio.h"
#include "pinctrl_airoha.h"
#include "air_logging.h"

#include <zephyr/random/random.h>

#include "avm_external.h"
#include "app_state.h"
#include "nvkey.h"
#include "hid_common.h"
#include "hal_spm.h"
#include "app_factory_reset_mouse.h"
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
#include "app_custom_protocol.h"
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */

int main(void)
{
    APP_LOGI(thisMOD,"=========== main ===========");
    #if 0
    APP_LOGI(thisMOD,"[SWLA]label_app_main START");
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_main, SWLA_DIRECTION_START);
    #endif
    app_factory_reset_mouse_init();
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
    app_epio_custom_protocol_init();
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */


    /* disable unused systems */
    uint32_t ret;
    ret = spm_control_mtcmos(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
    audio_memif_sram_power_down();
    APP_LOGI(thisMOD,"audio system power off, %u", ret);
    ret = spm_control_mtcmos(SPM_MTCMOS_CONN_ZIGBEE , SPM_MTCMOS_PWR_DISABLE);
    APP_LOGI(thisMOD,"zigbee system power off, %u", ret);
    APP_LOGI(thisMOD,"mtcmos status 0x%x", *(uint32_t *) 0x4213018C);
    cmsys_rom_0_sram_power_down();
    cmsys_rom_1_sram_power_down();
    infra_irtx_sram_power_down();
    
    /* TODO: This is dummy log, logging tool check TEXT LOG auto send query command */
    print_module_log(NULL, NULL, 0, PRINT_LEVEL_INFO, "This is main thread log.");


    struct evt_module_init* event = create_evt_module_init();
    
    if (event){
        AF_EVT_SUBMIT(event);
    }
    return 0;
}

