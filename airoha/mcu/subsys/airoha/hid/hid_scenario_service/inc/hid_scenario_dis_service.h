/* Copyright Statement:
 *
 * (C) 2026  Airoha Technology Corp. All rights reserved.
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
#if !defined (CONFIG_BT_DIS)
#ifndef __HID_SCENARIO_DIS_SERVICE_H__
#define __HID_SCENARIO_DIS_SERVICE_H__

#include <zephyr/kernel.h>
#include <zephyr/settings/settings.h>

#ifdef CONFIG_BT_DIS_MANUF
#define CONF_MANUF CONFIG_BT_DIS_MANUF
#else
#define CONF_MANUF NULL
#endif

#ifdef CONFIG_BT_DIS_SERIAL_NUMBER_STR
#define CONF_SERIAL CONFIG_BT_DIS_SERIAL_NUMBER_STR
#else
#define CONF_SERIAL NULL
#endif

#ifdef CONFIG_BT_DIS_HW_REV_STR
#define CONF_HW_REV CONFIG_BT_DIS_HW_REV_STR
#else
#define CONF_HW_REV NULL
#endif

#ifdef CONFIG_BT_DIS_SW_REV_STR
#define CONF_SW_REV CONFIG_BT_DIS_SW_REV_STR
#else
#define CONF_SW_REV NULL
#endif

#ifdef CONFIG_BT_DIS_PNP_VID_SRC
#define CONF_PNP_VID_SRC CONFIG_BT_DIS_PNP_VID_SRC
#else
#define CONF_PNP_VID_SRC 0
#endif

#ifdef CONFIG_BT_DIS_PNP_VID
#define CONF_PNP_VID CONFIG_BT_DIS_PNP_VID
#else
#define CONF_PNP_VID 0
#endif

#ifdef CONFIG_BT_DIS_PNP_PID
#define CONF_PNP_PID CONFIG_BT_DIS_PNP_PID
#else
#define CONF_PNP_PID 0
#endif

#ifdef CONFIG_BT_DIS_PNP_VER
#define CONF_PNP_VER CONFIG_BT_DIS_PNP_VER
#else
#define CONF_PNP_VER 0
#endif

#endif /* __HID_SCENARIO_DIS_SERVICE_H__ */
#endif /* CONFIG_BT_DIS */