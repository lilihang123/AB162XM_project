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
#ifndef __AW95124_IO_EXPANDER_H__
#define __AW95124_IO_EXPANDER_H__

#include <zephyr/drivers/sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

// AW95124 register definitions
#define AW951XX_P0DI_REG				(0x00)
#define AW951XX_P1DI_REG				(0x01)
#define AW951XX_P2DI_REG				(0x02)
#define AW951XX_P0DO_REG				(0x04)
#define AW951XX_P1DO_REG				(0x05)
#define AW951XX_P2DO_REG				(0x06)
#define AW951XX_P0INV_REG				(0x08)
#define AW951XX_P1INV_REG				(0x09)
#define AW951XX_P2INV_REG				(0x0A)
#define AW951XX_P0OEN_REG				(0x0C)
#define AW951XX_P1OEN_REG				(0x0D)
#define AW951XX_P2OEN_REG				(0x0E)
#define AW951XX_P0DSR1_REG				(0x40)
#define AW951XX_P0DSR2_REG				(0x41)
#define AW951XX_P1DSR1_REG				(0x42)
#define AW951XX_P1DSR2_REG				(0x43)
#define AW951XX_P2DSR1_REG				(0x44)
#define AW951XX_P2DSR2_REG				(0x45)
#define AW951XX_P0LE_REG				(0x48)
#define AW951XX_P1LE_REG				(0x49)
#define AW951XX_P2LE_REG				(0x4A)
#define AW951XX_P0PE_REG				(0x4C)
#define AW951XX_P1PE_REG				(0x4D)
#define AW951XX_P2PE_REG				(0x4E)
#define AW951XX_P0PMD_REG				(0x50)
#define AW951XX_P1PMD_REG				(0x51)
#define AW951XX_P2PMD_REG				(0x52)
#define AW951XX_P0MSK_REG				(0x54)
#define AW951XX_P1MSK_REG				(0x55)
#define AW951XX_P2MSK_REG				(0x56)
#define AW951XX_P0INST_REG				(0x58)
#define AW951XX_P1INST_REG				(0x59)
#define AW951XX_P2INST_REG				(0x5A)
#define AW951XX_OPC_REG					(0x5C)
#define AW951XX_P0EDGE1_REG				(0x60)
#define AW951XX_P0EDGE2_REG				(0x61)
#define AW951XX_P1EDGE1_REG				(0x62)
#define AW951XX_P1EDGE2_REG				(0x63)
#define AW951XX_P2EDGE1_REG				(0x64)
#define AW951XX_P2EDGE2_REG				(0x65)
#define AW951XX_P0INTCLR_REG			(0x68)
#define AW951XX_P1INTCLR_REG			(0x69)
#define AW951XX_P2INTCLR_REG			(0x6A)
#define AW951XX_P0DIST_REG				(0x6C)
#define AW951XX_P1DIST_REG				(0x6D)
#define AW951XX_P2DIST_REG				(0x6E)
#define AW951XX_P0DOMD_REG				(0x70)
#define AW951XX_P1DOMD_REG				(0x71)
#define AW951XX_P2DOMD_REG				(0x72)
#define AW951XX_P0DEBEN_REG				(0x74)
#define AW951XX_P1DEBEN_REG				(0x75)
#define AW951XX_DEBCNT_REG				(0x76)
#define AW951XX_PDEG_EN_REG				(0xF7)
#define AW951XX_SOFT_RSTN_REG			(0xF8)
#define AW951XX_I2C_RSTEN_REG			(0xF9)
#define AW951XX_CHIPID_REG				(0xFB)


#define AW951XX_RESET				(0x16)
#define MAX_BANK			3
#define BANK_SZ				8
#define DRIVER_LEVEL_BANK_SZ		4
#define TRIG_MODE_BANK_SZ		4

#define AW951XX_I2C_RW_RETRIES			(3)
#define AW951XX_I2C_RETRY_DELAY			(2)
#define AW951XX_READ_CHIPID_RETRIES		(3)
#define AW951XX_REGADD_SIZE_8BIT		(1)
#define AW951XX_REGDATA_SIZE_8BIT		(1)




enum aw951xx_gpio_dir {
	AW951XX_GPIO_INPUT = 1,
	AW951XX_GPIO_OUTPUT = 0,
};

enum aw951xx_gpio_drive {
	AW951XX_GPIO_DRIVE_0P25X = 0,
	AW951XX_GPIO_DRIVE_0P5X = 1,
	AW951XX_GPIO_DRIVE_0P75X = 2,
	AW951XX_GPIO_DRIVE_1X = 3
};

enum aw951xx_gpio_pull {
	AW951XX_GPIO_PULL_DOWN = 0,
	AW951XX_GPIO_PULL_UP = 1,
	AW951XX_GPIO_PULL_DISABLE = 2,
};

enum aw951xx_interrupt_trigger_type {
	AW951XX_INI_TRIGGER_RISING,
	AW951XX_INI_TRIGGER_FALLING,
	AW951XX_INI_TRIGGER_DUAL_EDGE,
	AW951XX_INI_TRIGGER_HIGH,
	AW951XX_INI_TRIGGER_LOW,
};

enum aw_err {
	AW_OK = 0,
	AW_ERR,
};

enum aw951xx_chipid {
	AW95124QNR = 0x04,
	AW95124FOR = 0x05,
};

#ifdef __cplusplus
}
#endif

#endif // AW95124_IO_EXPANDER_H
