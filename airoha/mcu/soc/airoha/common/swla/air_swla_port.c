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

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <string.h>

#ifdef AIR_MUX_ENABLE
#include "mux_port_common.h"
#endif

#ifdef AIR_SWLA_ENABLE
#include "swla.h"
#endif

#ifdef AIR_ONLINE_DUMP_ENABLE
#include "system_online_dump.h"
#endif


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
extern void online_swla_trigger_dump(void);

/* Private macro -------------------------------------------------------------*/
#define PORT_SWLA_CURRENT_CPU_ID()    (0)

/* Private variables ---------------------------------------------------------*/
// ################# step-1, add customeized HCLA label start #################
const SWLA_USERLABEL_INFO_t swla_user_label_info[] = {
    /* 0   */ {label_dpm, "dpm"},
    /* 1   */ {label_wfi, "wfi"},
    /* 2   */ {label_msk, "msk"},
    /* 3   */ {label_excp, "excp"},
    /* 4   */ {label_app_evt_dispatcher, "app_evt_dispatcher"},
    /* 5   */ {label_gesture, "gesture"},
    /* 6   */ {label_app_wheel_wakeup, "app_wheel_wakeup"},
    /* 7   */ {label_app_sensor_wakeup, "app_sensor_wakeup"},
    /* 8   */ {label_app_exit_low_power, "app_exit_low_power"},
    /* 9   */ {label_app_bt_connecting, "app_bt_connecting"},
    /*10   */ {label_app_10, "app_10"},
    /*11   */ {label_app_11, "app_11"},
    /*12   */ {label_usb_tx_send, "usb_tx_send"},

    /* max support 1byte */
    /* 255 */ {SWLA_LABEL_MAX_ID, "SLA_LABEL_MAX_ID"},
};
const uint8_t swla_user_label_array_count = (sizeof(swla_user_label_info) / sizeof(swla_user_label_info[0]));
// ################# step-1, add customeized HCLA label end #################

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
uint32_t port_swla_query_max_cpu_number(void)
{
#ifdef AIR_MUX_ENABLE
    return AIR_MAX_CPU_NUMBER;
#else
    return 1; /* only mcu core */
#endif
}

uint32_t port_swla_query_package_header_size(void)
{
#if defined(AIR_SWLA_ENABLE) && defined(AIR_ONLINE_DUMP_ENABLE)
    return sizeof(system_online_dump_header_t);
#else
    /* not support online dump, bypass this data */
    return 0;
#endif
}

bool port_swla_online_mode_is_enable(void)
{
#ifdef AIR_ONLINE_SWLA_ENABLE
    return true;
#else
    return false;
#endif
}


void port_swla_dump_package(uint8_t version, uint16_t seq, uint16_t drop_count, uint8_t *p_buf, uint32_t buf_size)
{
#if defined(AIR_SWLA_ENABLE) && defined(AIR_ONLINE_DUMP_ENABLE)
    System_Info_Dump(SYSTEM_ONLINE_DUMP_SWLA, PORT_SWLA_CURRENT_CPU_ID(), version, seq, drop_count, (uint8_t*)p_buf, buf_size);
#else
    (void) version;
    (void) seq;
    (void) drop_count;
    (void) p_buf;
    (void) buf_size;
#endif
}

ATTR_TEXT_IN_TCM void port_swla_trigger_dump(void)
{
#ifdef AIR_ONLINE_SWLA_ENABLE
    online_swla_trigger_dump();
#endif
}

#if KERNELVERSION == 0x3030000
static int swla_enable_init(const struct device *dev)
#elif KERNELVERSION >= 0x3070000
static int swla_enable_init(void)
#else
#error "Unkown supported kernel version"
#endif
{
#ifdef AIR_SWLA_ENABLE
    SLA_Enable();
#ifdef AIR_ONLINE_DUMP_ENABLE
    online_swla_init();
#endif  /* AIR_ONLINE_DUMP_ENABLE */
#endif  /* AIR_SWLA_ENABLE */

    return 0;
}

SYS_INIT(swla_enable_init, CONFIG_SWLA_INIT_LEVEL, CONFIG_SWLA_INIT_PRIORITY);
