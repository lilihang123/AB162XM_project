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


#if defined(HAL_USB_MODULE_ENABLED) || defined(HAL_USB_HOST_MODULE_ENABLED)

#define USB_BRINGUP_WORKAROUND

#include <zephyr/kernel.h>
#include "hal_flash_disk_internal.h"
#include "hal_gpt.h"
#include "hal_log.h"
#include "hal_usb.h"
#include "hal_usb_internal.h"

#include <zephyr/sys/printk.h>
#undef log_hal_msgid_info
#undef log_hal_msgid_error
#define log_hal_msgid_info(msg, cnt, ...)   printk("[HAL_USB]" msg "\r\n", ##__VA_ARGS__)
#define log_hal_msgid_error(msg, cnt, ...)  printk("[HAL_USB]" msg "\r\n", ##__VA_ARGS__)
#define USB_WAIT_RECALIBRATION_TIME 1000 /* us */
static volatile USBPHY_REGISTER_T *usbphy = (USBPHY_REGISTER_T *)(USB_PHY_MSTAR);

#if !defined(FPGA_ENV)
#if defined(USB_BRINGUP_WORKAROUND)
#include "air_chip.h"
#include "hal_clock.h"
#include "hal_clock_internal.h"

static void hal_usb_phy_workaround_init(void) __unused;
static void hal_usb_phy_workaround_init(void)
{
    log_hal_msgid_info("hal_usb_phy_workaround_init", 0);

#if 0
	*((uint32_t *)0x4203002C) = 0x1;
	*((uint32_t *)0x4203004C) = 0x1;
	*((uint32_t *)0x42030028) = 0x1;
	hal_gpt_delay_ms(100);
	*((uint32_t *)0x4203004C) = 0x0;
#endif

    RGU_MISC->sw_rst3.field.USB_SW_RST = (0x1 << 8) | WDT_USB_SW_RST_KEY;
    RGU_MISC->sw_rst3.field.USB_SW_RST = WDT_USB_SW_RST_KEY;
    RGU_MISC->sw_rst3.field.USBSIF_SW_RST = (0x1 << 8) | WDT_USBIF_SW_RST_KEY;
    RGU_MISC->sw_rst3.field.USBSIF_SW_RST = WDT_USBIF_SW_RST_KEY;

    log_hal_msgid_info("usb 0x42040000: 0x%08X", 1, *((uint32_t *)0x42040000));
    log_hal_msgid_info("usb 0x4203004C: 0x%08X", 1, *((uint32_t *)0x4203004C));
    log_hal_msgid_info("usb 0x40230028: 0x%08X", 1, *((uint32_t *)0x40230028));
    log_hal_msgid_info("usb 0x42090070: 0x%08X", 1, *((uint32_t *)0x42090070));

    log_hal_msgid_info("usb f_fusb_ck %d, DBL_en:%d",2, hal_clock_get_freq_meter(f_fusb_ck, 10000), *DCXO_PCON8__DBL_64M_EN);
    log_hal_msgid_info("usb AD_CLKO_UPLL_TEST_DIG %d",2, hal_clock_get_freq_meter(AD_CLKO_UPLL_TEST_DIG, 10000));
    log_hal_msgid_info("usb AD_CLKO_UPLL_FB %d",2, hal_clock_get_freq_meter(AD_CLKO_UPLL_FB, 10000));
    log_hal_msgid_info("usb AD_CLKO_UPLL_REF %d",2, hal_clock_get_freq_meter(AD_CLKO_UPLL_REF, 10000));
}
#endif

static void ca_calibration(void)
{
    uint32_t i = (USB_WAIT_RECALIBRATION_TIME / 20);

    DRV_WriteReg32(&usbphy->usbphyacr2, 0x80404004);
    k_usleep(7000);
    DRV_WriteReg32((USB_PHY_MSTAR + 0x824), 0x00610000);
    DRV_WriteReg32((USB_PHY_MSTAR + 0x838), 0x00000001);
    DRV_WriteReg32((USB_PHY_MSTAR + 0x838), 0x00000000);
    while(((DRV_Reg32(USB_PHY_MSTAR + 0x838) & 0x2) == 0) && i) {
        hal_gpt_delay_us(20);
        i--;
    }

    if (!i) {
        log_hal_msgid_info("wait recalibration timeout, 0x838: 0x%x", 1, DRV_Reg32(USB_PHY_MSTAR + 0x838));
    }
}


static void hal_usb_phy_ca_sw_offset(void)
{
    uint32_t ca = DRV_Reg32(USB_PHY_MSTAR + 0x838) >> 4;
    DRV_WriteReg32((USB_PHY_MSTAR + 0x820), 0x00000240 + ((ca >> 6) & 0x3F)-10);
    DRV_WriteReg32((USB_PHY_MSTAR + 0x834), 0x40008001 + (((ca & 0x3F)-10) << 24));
    log_hal_msgid_info("[HAL_USB_PHY] CA RG 0x%08X: 0x%08X, RG 0x%08X: 0x%08X, RG 0x%08X: 0x%08X,", 6, 
        (USB_PHY_MSTAR + 0x838), DRV_Reg32(USB_PHY_MSTAR + 0x838), (USB_PHY_MSTAR + 0x820), DRV_Reg32(USB_PHY_MSTAR + 0x820), (USB_PHY_MSTAR + 0x834), DRV_Reg32(USB_PHY_MSTAR + 0x834));
}
/**
 * @brief Power on USB related peripheral hw.
 */
void hal_usb_phy_peri_on(void)
{
    /* Switch UPLL 62.4MHz */
    clock_mux_sel(CLK_USB_SEL, 1);

    /* Enable clock source */
    hal_clock_enable(HAL_CLOCK_CG_USB_BUS);
    hal_clock_enable(HAL_CLOCK_CG_USB_DMA);
    hal_clock_enable(HAL_CLOCK_CG_USB);
}

/**
 * @brief Power off USB related peripheral hw.
 */
void hal_usb_phy_peri_off(void)
{
    /* Disable clock source */
    hal_clock_disable(HAL_CLOCK_CG_USB_DMA);
    hal_clock_disable(HAL_CLOCK_CG_USB_BUS);
    hal_clock_disable(HAL_CLOCK_CG_USB);
}

/**
 * @brief Reset USB MAC & PHY.
 */
void hal_usb_phy_reset(void)
{
    /* USB IP Reset */
    RGU_MISC->sw_rst3.field.USB_SW_RST = (0x1 << 8) | WDT_USB_SW_RST_KEY;
    RGU_MISC->sw_rst3.field.USB_SW_RST = WDT_USB_SW_RST_KEY;
    RGU_MISC->sw_rst3.field.USBSIF_SW_RST = (0x1 << 8) | WDT_USBIF_SW_RST_KEY;
    RGU_MISC->sw_rst3.field.USBSIF_SW_RST = WDT_USBIF_SW_RST_KEY;
}

/**
 * @brief Power on
 *
 */
void hal_usb_phy_poweron_initialize(void)
{
    hal_usb_phy_peri_on();
    hal_usb_phy_reset();

    log_hal_msgid_info("[HAL_USB_PHY] hal_usb_phy_poweron_initialize", 0);

    DRV_WriteReg32(&usbphy->u2phydtm0, 0x0F20B720);
    DRV_WriteReg32(&usbphy->u2phydtm1, 0x00011004);

    DRV_WriteReg32(&usbphy->usbphyacr2, 0x80400084);
    DRV_WriteReg32((USB_PHY_MSTAR + 0x81C), 0x008880A1);
    DRV_WriteReg32(&usbphy->usbphyacr0, 0x94006BC3);
    hal_gpt_delay_us(2000);
    DRV_WriteReg32(&usbphy->usbphyacr0, 0x940069C3);
    hal_gpt_delay_us(2000);
    DRV_WriteReg32(&usbphy->usbphyacr0, 0x94000001);
    hal_gpt_delay_us(2000);

    DRV_WriteReg32((USB_PHY_MSTAR + 0x810), 0x01FF0040);
    DRV_WriteReg32((USB_PHY_MSTAR + 0x810), 0x00FF0040);
    ca_calibration();

#if 1
#if 0
    log_hal_msgid_info("[HAL_USB_PHY] CA RG before 0x%08X: 0x%08X", 2,
                       (USB_PHY_MSTAR + 0x838), DRV_Reg32(USB_PHY_MSTAR + 0x838));
    log_hal_msgid_info("[HAL_USB_PHY] CA RG before 0x%08X: 0x%08X", 2,
                       (USB_PHY_MSTAR + 0x820), DRV_Reg32(USB_PHY_MSTAR + 0x820));
    log_hal_msgid_info("[HAL_USB_PHY] CA RG before 0x%08X: 0x%08X", 2,
                       (USB_PHY_MSTAR + 0x834), DRV_Reg32(USB_PHY_MSTAR + 0x834));
#endif
    hal_usb_phy_ca_sw_offset();
#endif
    DRV_WriteReg32(&usbphy->usbphyacr0, 0x28840001);
    DRV_WriteReg32(&usbphy->usbphyacr1, 0x00403060);
    DRV_WriteReg32(&usbphy->usbphyacr2, 0x8040D507);
    DRV_WriteReg32(&usbphy->usbphyacr1, 0x00433060);
    DRV_WriteReg32(&usbphy->usbphyacr1, 0x00403060);
    DRV_WriteReg32(&usbphy->usbphyacr5, 0x0000000B);

    /* adjust slew rate*/
    // USB_DRV_SetData32((USB_PHY_MSTAR+0x824), 0x00000007, 0x00000001);
    // USB_DRV_SetData32((USB_PHY_MSTAR+0x828), 0x000003FF, 0x00000281);
    USB_DRV_SetData32((USB_PHY_MSTAR+0x828), 0x00000070, 0x00000020);
    log_hal_msgid_info("[HAL_USB_PHY] RG 0x%08X : 0x%08X", 2, (USB_PHY_MSTAR + 0x828), DRV_Reg32(USB_PHY_MSTAR + 0x828));

#if 1
    uint8_t otp152;
    uint8_t otp153;
    uint8_t otp154;

    hal_flash_otp_read(152, &otp152, 1);
    hal_flash_otp_read(153, &otp153, 1);
    hal_flash_otp_read(154, &otp154, 1);

    /* Set USB PHY register from OTP Trim value */
    if (otp152 == 0x1) {
        USB_DRV_SetData32((USB_PHY_MSTAR + 0x824), 0x00000600, ((uint32_t)(otp154 & 0x03)) <<  9); /* bit 10:09 */
        USB_DRV_SetData32((USB_PHY_MSTAR + 0x824), 0x000001E0, ((uint32_t)(otp153 & 0x0F)) <<  5); /* bit 08:05 */
        USB_DRV_SetData32((USB_PHY_MSTAR + 0x824), 0x00006000, ((uint32_t)(otp154 & 0x0C)) << 11); /* bit 14:13 */
    }

    log_hal_msgid_info("[HAL_USB_PHY] OTP otp152 : 0x%02X, otp153 : 0x%02X, otp154 : 0x%02X, trim RG 0x%08X : 0x%08X", 5, otp152, otp153, otp154, (USB_PHY_MSTAR + 0x824), DRV_Reg32(USB_PHY_MSTAR + 0x824));
#endif

    /* Set reg_test_bus_select bit 3:0 to 5, get linestate(DM,DP) from 0xA1030854 */
    // USB_DRV_SetData32((USB_PHY_MSTAR + 0x810), 0x0000000F, (5 << 0));

    /* For Suspend & Resume Flow - "Pre-Set" configuration */
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x870), 0x1 << 8);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x870), 0x1 << 9);
}

void hal_usb_phy_speed_set(bool hs)
{
    if (hs) {
        DRV_WriteReg32(&usbphy->usbphyacr0, 0x28840001);
    } else {
        DRV_WriteReg32(&usbphy->usbphyacr0, 0x28840001 | 0x4C00);
    }
}

void hal_usb_phy_deinit_case(void)
{
    hal_usb_phy_reset();
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x86C), (1<<3));
    hal_usb_phy_peri_off();
}

void hal_usb_phy_enter_suspend(void)
{
    // Power Down USB Analog
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x800), 0x1 << 2);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x800), 0x1 << 8);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x800), 0x1 << 10);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x800), 0x1 << 11);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x800), 0x1 << 12);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x800), 0x1 << 14);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x870), 0x1 << 10);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x800), 0x1 << 15);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x808), 0x1 << 7);
    // Power Off U2PLL
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x800), 0x1 << 9);
    hal_gpt_delay_us(2);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x86C), 0x1 << 3);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x868), 0x1 << 9);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x868), 0x1 << 10);
}

void hal_usb_phy_leave_suspend(void)
{
    uint32_t i = (USB_WAIT_RECALIBRATION_TIME / 20);

    // Power On U2PLL
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x86C), 0x1 << 3);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x868), 0x1 << 9);
    USB_DRV_SetBits32((USB_PHY_MSTAR+0x868), 0x1 << 10);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x800), 0x1 << 9);
    // Power On USB Analog
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x800), 0x1 << 2);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x800), 0x1 << 8);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x800), 0x1 << 10);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x800), 0x1 << 11);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x800), 0x1 << 12);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x800), 0x1 << 14);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x800), 0x1 << 15);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x870), 0x1 << 10);
    USB_DRV_ClearBits32((USB_PHY_MSTAR+0x808), 0x1 << 7);
    hal_gpt_delay_us(2);

    /*clr manual setting in 0x820[6] & 0x834[30]*/
    DRV_WriteReg32((USB_PHY_MSTAR+0x820), 0x200);
    DRV_WriteReg32((USB_PHY_MSTAR+0x834), 0x00008001);

    DRV_WriteReg32((USB_PHY_MSTAR + 0x838), 0x00000001);
    DRV_WriteReg32((USB_PHY_MSTAR + 0x838), 0x00000000);

    while(((DRV_Reg32(USB_PHY_MSTAR + 0x838) & 0x2) == 0) && i) {
        hal_gpt_delay_us(20);
        i--;
    }
    if (!i) {
        log_hal_msgid_info("wait recalibration timeout, 0x838: 0x%x", 1, DRV_Reg32(USB_PHY_MSTAR + 0x838));
    } else {
        hal_usb_phy_ca_sw_offset();
    }
}

hal_usb_linestate_t hal_usb_phy_detect_linestate(void)
{
    hal_usb_linestate_t ls = (hal_usb_linestate_t)(0x3 & (USB_DRV_Reg32(U2PHYDMON1) >> 22));
#if 0
    log_hal_msgid_info("hal_usb_phy_detect_linestate DM_%d DP_%d", 2, (ls >> 1) & 0x01, ls & 0x01);
#endif

    return ls;
}

#else /* FPGA_ENV */

#include "hal_i2c_master.h"
#include "hal_i2c_master_internal.h"

#define TM_CTRL ((TOP_MISC_CFG_BASE) + 0x0120)

#define HAL_USB_PHY_BOARD_STATUS_OK              0
#define HAL_USB_PHY_BOARD_STATUS_I2C_INIT_ERROR  1
#define HAL_USB_PHY_BOARD_STATUS_I2C_WRITE_ERROR 2
#define HAL_USB_PHY_BOARD_STATUS_I2C_READ_ERROR  3

#define PHYBOARD_SLAVE_ADDR 0x60
#define PHYBOARD_I2C_PORT   HAL_I2C_MASTER_0

static void hal_usb_phy_board_init(void);

void hal_usb_phy_poweron_initialize(void)
{
    log_hal_msgid_info("hal_usb_phy_poweron_initialize", 0);
    hal_usb_phy_board_init();
}

void hal_usb_phy_leave_suspend(void)
{
}

void hal_usb_phy_enter_suspend(void)
{
}

hal_usb_linestate_t hal_usb_phy_detect_linestate(void)
{
    return HAL_USB_LINESTATE_DM_0_DP_0;
}

static uint8_t hal_usb_phy_board_read_rg(uint8_t rg, uint8_t *data)
{
    hal_i2c_status_t status;
    uint8_t i2c_wr[1] = {rg};
    hal_i2c_send_to_receive_config_t i2c_rx_config = {
        .slave_address = PHYBOARD_SLAVE_ADDR,
        .send_data = i2c_wr,
        .send_length = 1,
        .receive_buffer = data,
        .receive_length = 1,
    };

    status = hal_i2c_master_send_to_receive_polling(PHYBOARD_I2C_PORT, &i2c_rx_config);
    if (HAL_I2C_STATUS_OK != status) {
        return HAL_USB_PHY_BOARD_STATUS_I2C_READ_ERROR;
    }

    return HAL_USB_PHY_BOARD_STATUS_OK;
}

static uint8_t hal_usb_phy_board_write_rg(uint8_t rg, uint8_t data)
{
    hal_i2c_status_t status;
    uint8_t i2c_wr[2] = {rg, data};

    status = hal_i2c_master_send_polling(PHYBOARD_I2C_PORT, PHYBOARD_SLAVE_ADDR, i2c_wr, 2);
    if (HAL_I2C_STATUS_OK != status) {
        return HAL_USB_PHY_BOARD_STATUS_I2C_WRITE_ERROR;
    }

    return 0;
}

static uint8_t hal_usb_phy_board_modify_rg(uint8_t rg, uint8_t mask, uint8_t data)
{
    uint8_t o = 0;
    uint8_t n = 0;
    uint8_t ret = 0;

    /* Read from usb phy board */
    ret = hal_usb_phy_board_read_rg(rg, &o);
    if (ret) {
        goto _hal_usb_phy_board_write_out;
    }

    /* Modify value */
    n = (o & ~mask) | (data & mask);

    /* Write back to usb phy board */
    ret = hal_usb_phy_board_write_rg(rg, n);
    if (ret) {
        goto _hal_usb_phy_board_write_out;
    }

_hal_usb_phy_board_write_out:
    log_hal_msgid_info("phyboard rg:0x%02X, old:0x%02X, new:0x%02X, status:%d", 4, rg, o, n, ret);

    return ret;
}

static uint8_t hal_usb_phy_board_i2c_init(void)
{
    hal_i2c_config_t i2c_config = {
        .frequency = HAL_I2C_FREQUENCY_400K,
    };
    hal_i2c_status_t i2c_status;
    i2c_status = hal_i2c_master_init(HAL_I2C_MASTER_0, &i2c_config);
    if (HAL_I2C_STATUS_OK != i2c_status) {
        return HAL_USB_PHY_BOARD_STATUS_I2C_INIT_ERROR;
    }
    return HAL_USB_PHY_BOARD_STATUS_OK;
}

static void hal_usb_phy_board_init(void)
{
    uint8_t status = HAL_USB_PHY_BOARD_STATUS_OK;

    /* USB PHY board initialize sequence */
    // I2C  0x60  0xFC[31:24] 0x00  RW
    // I2C  0x60  0x00[00:00] 0x01  RW  RG_SIFSLV_BGR_EN
    // I2C  0x60  0x00[05:05] 0x01  RW  RG_USB20_INTR_EN
    // I2C  0x60  0x04[23:19] 0x10  RW  RG_USB20_INTR_CAL
    // I2C  0x60  0x18[23:23] 0x00  RW  RG_USB20_BC11_SW_EN
    // I2C  0x60  0x68[18:18] 0x00  RW  force_suspendm
    // I2C  0x60  0x68[03:03] 0x01  RW  RG_SUSPENDM
    // I2C  0x60  0x14[14:12] 0x04  RW  RG_USB20_HSTX_SRCTRL
    // I2C  0x60  0x18[03:00] 0x03  RW  RG_USB20_SQTH

    const uint8_t rg[9] = {0xFF, 0x00, 0x00, 0x06, 0x1A, 0x6A, 0x68, 0x15, 0x18};
    const uint8_t mask[9] = {0xFF, 0x01, 0x20, 0xF8, 0x80, 0x04, 0x08, 0x70, 0x0F};
    const uint8_t data[9] = {0x00, 0x01, 0x20, 0x80, 0x00, 0x00, 0x08, 0x40, 0x03};

    log_hal_msgid_info("hal_usb_phy_board_init 1: i2c init", 0);
    status = hal_usb_phy_board_i2c_init();
    if (status) {
        log_hal_msgid_info("hal_usb_phy_board_init 1: failed, status:%d", 1, status);
        return;
    }

    log_hal_msgid_info("hal_usb_phy_board_init 2: Set SuspendM", 0);
    /* Set USB20_SUSPENDM_FPGA in TM_CTRL */
    USB_DRV_SetBits32(TM_CTRL, (1 << 4));

    log_hal_msgid_info("hal_usb_phy_board_init 3: Setup phy board", 0);
    /* Setup phy board */
    for (uint8_t i = 0; i < 9; i++) {
        status = hal_usb_phy_board_modify_rg(rg[i], mask[i], data[i]);
        if (status) {
            log_hal_msgid_info("hal_usb_phy_board_init 3: failed, status:%d", 1, status);
            return;
        }
    }

    log_hal_msgid_info("hal_usb_phy_board_init 4: Done", 0);
    return;
}

#endif /* FPGA_ENV */

#endif /* HAL_USB_MODULE_ENABLED or HAL_USB_HOST_MODULE_ENABLED */
