# Copyright Statement:
#
# (C) 2025  Airoha Technology Corp. All rights reserved.
#
# This software/firmware and related documentation ("Airoha Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
# Without the prior written permission of Airoha and/or its licensors,
# any reproduction, modification, use or disclosure of Airoha Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.
# You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
# if you have agreed to and been bound by the applicable license agreement with
# Airoha ("License Agreement") and been granted explicit permission to do so within
# the License Agreement ("Permitted User").  If you are not a Permitted User,
# please cease any access or use of Airoha Software immediately.
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
# RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
# TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
# WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
# CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
# AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
#


add_subdirectory(${SOC_SERIES}/sensor)
add_subdirectory_ifdef(CONFIG_AIR_OST ${SOC_SERIES}/os_timer)
add_subdirectory_ifdef(CONFIG_AIR_GPIO ${SOC_SERIES}/gpio)
add_subdirectory_ifdef(CONFIG_AIR_PINMUX ${SOC_SERIES}/pinmux)
add_subdirectory_ifdef(CONFIG_AIR_FLASH ${SOC_SERIES}/flash)
add_subdirectory_ifdef(CONFIG_AIR_CACHE ${SOC_SERIES}/cache)
add_subdirectory_ifdef(CONFIG_AIR_WDT ${SOC_SERIES}/watchdog)
add_subdirectory_ifdef(CONFIG_AIR_INTC ${SOC_SERIES}/interrupt_controller)
add_subdirectory_ifdef(CONFIG_AIR_I2C ${SOC_SERIES}/i2c)
add_subdirectory_ifdef(CONFIG_AIR_RTC ${SOC_SERIES}/rtc)
add_subdirectory_ifdef(CONFIG_AIR_LED ${SOC_SERIES}/led)
add_subdirectory_ifdef(CONFIG_AIR_PWM ${SOC_SERIES}/pwm)
add_subdirectory_ifdef(CONFIG_AIR_PWMDMA ${SOC_SERIES}/pwm_dma)
add_subdirectory_ifdef(CONFIG_AIR_UART ${SOC_SERIES}/uart)
add_subdirectory_ifdef(CONFIG_AIR_SPIM ${SOC_SERIES}/spim)
add_subdirectory_ifdef(CONFIG_AIR_SPIS ${SOC_SERIES}/spis)
add_subdirectory_ifdef(CONFIG_AIR_USB ${SOC_SERIES}/usb)
add_subdirectory_ifdef(CONFIG_AIR_PINCTRL ${SOC_SERIES}/pinctrl)
add_subdirectory_ifdef(CONFIG_AIR_CLOCK_CONTROL ${SOC_SERIES}/clock_control)
add_subdirectory_ifdef(CONFIG_AIR_PMU ${SOC_SERIES}/pmu)
add_subdirectory_ifdef(CONFIG_AIR_SARADC ${SOC_SERIES}/adc/saradc)
add_subdirectory_ifdef(CONFIG_AIR_ENTROPY_ENABLE ${SOC_SERIES}/random)
add_subdirectory_ifdef(CONFIG_IO_EXPANDER_AW95124 ${SOC_SERIES}/aw_951xx)
