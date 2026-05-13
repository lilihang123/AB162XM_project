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

#define DT_DRV_COMPAT airoha_air_flash_controller

#include <string.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/sys/printk.h>

#ifdef FPGA_ENV
#include "hal_gpt.h"
#endif
#include "hal_flash.h"
#ifdef FPGA_ENV
#include "hal_flash_sf.h"
#endif
#include "hal_nvic.h"

#define SOC_NV_FLASH_NODE DT_NODELABEL(flash0)

#define AIR_FLASH_DBG_LOG 0


static int flash_airoha_read(const struct device *dev,
    off_t offset, void *data, size_t len)
{
    // printk("flash_airoha_read was called with dev: 0x%08X, offset: 0x%08X, data: 0x%08X, len: %d\r\n", dev, offset, data, len);
    return (int)hal_flash_read(offset, data, len);
}

static int flash_airoha_write(const struct device *dev, off_t offset,
    const void *data, size_t len)
{
#if AIR_FLASH_DBG_LOG
    uint32_t lr = (uint32_t)__builtin_return_address(0);
    printk("flash_airoha_write was called with dev: 0x%08X, offset: 0x%08X, data: 0x%08X, len: %d by 0x%08X\r\n",
        (unsigned int)dev,
        (unsigned int)offset,
        (unsigned int)data,
        len,
        (unsigned int)lr);
#endif
    return (int)hal_flash_write(offset, data, len);
}

static int flash_airoha_erase(const struct device *dev, off_t offset,
    size_t size)
{
    __ASSERT(!(offset % 0x1000) && !(size % 0x1000), "Offset and size must be 4KB align\r\n");
    int op_ret = 0;

    while(size){
#if AIR_FLASH_DBG_LOG
        printk("flash_airoha_erase was called with offset(0x%08lX) and size(0x%08X)\r\n", offset, size);
#endif
        if((!(offset % 0x10000)) && (size >= 0x10000)){
#if AIR_FLASH_DBG_LOG
            printk("hal_flash_erase 64K\r\n");
#endif
            op_ret = (int)hal_flash_erase(offset, HAL_FLASH_BLOCK_64K);
            offset += 0x10000;
            size -= 0x10000;
        } else if((!(offset % 0x8000)) && (size >= 0x8000)){
#if AIR_FLASH_DBG_LOG
            printk("hal_flash_erase 32K\r\n");
#endif
            op_ret = (int)hal_flash_erase(offset, HAL_FLASH_BLOCK_32K);
            offset += 0x8000;
            size -= 0x8000;
        } else {
#if AIR_FLASH_DBG_LOG
            printk("hal_flash_erase 4K\r\n");
#endif
#if IS_ENABLED(CONFIG_AIR_PURE_GAMING_DONGLE_ENABLE)
            uint32_t mask;
            hal_nvic_save_and_set_interrupt_mask(&mask);
            op_ret = (int)hal_flash_erase(offset, HAL_FLASH_BLOCK_4K);
            hal_nvic_restore_interrupt_mask(mask);
#else
            op_ret = (int)hal_flash_erase(offset, HAL_FLASH_BLOCK_4K);
#endif
            offset += 0x1000;
            size -= 0x1000;
        }
        if( op_ret != 0 ){
            printk("Erase fail at 0x%08lX(%dK)\r\n", offset, size >> 10);
            break;
        }
    }
    return op_ret;
}

static const struct flash_parameters* flash_airoha_get_parameters(const struct device *dev)
{
    static const struct flash_parameters para = {
        .write_block_size = (size_t)1,
        .erase_value = (uint8_t)0xFF,
    };
    return &para;
}

extern uint8_t nor_id[4];
static int flash_airoha_read_jedec_id(const struct device *dev, uint8_t *id)
{
    memcpy((void*)id, (void*)nor_id, 3);
    return 0;
}


#ifdef FPGA_ENV
extern void SFI_Dev_Command_Ext(const uint16_t CS, const uint8_t *cmd, uint8_t *data, const uint16_t outl, const uint16_t inl);
static void flash_airoha_reset(void)
{
    uint8_t id[4];
    id[0] = 0x66;
    SFI_Dev_Command_Ext((uint16_t)SPI, (uint8_t *)&id[0], (uint8_t *)NULL, 1, 0);
    id[0] = 0x99;
    SFI_Dev_Command_Ext((uint16_t)SPI, (uint8_t *)&id[0], (uint8_t *)NULL, 1, 0);
    hal_gpt_delay_ms(10);

    id[0] = 0x66;
    SFI_Dev_Command_Ext((uint16_t)QPI, (uint8_t *)&id[0], (uint8_t *)NULL, 1, 0);
    id[0] = 0x99;
    SFI_Dev_Command_Ext((uint16_t)QPI, (uint8_t *)&id[0], (uint8_t *)NULL, 1, 0);
    hal_gpt_delay_ms(10);
}
#endif

#if IS_ENABLED(CONFIG_MCUBOOT) || defined(AIR_DOWNLOAD_AGENT)
static int flash_apply_parameter(void)
{
    /* set SFC 4bit on real chip at bootloader stage */
    extern int custom_setSFIExt(void);
    custom_setSFIExt();
    return 0;
}

SYS_INIT(flash_apply_parameter, CONFIG_FLASH_CFG_INIT_LEVEL, CONFIG_FLASH_CFG_INIT_PRIORITY);
#endif


int g_flash_init_res = -1;
static int flash_airoha_init(const struct device *dev)
{
#ifdef FPGA_ENV
    flash_airoha_reset();
#endif
    int op_ret = (int)hal_flash_init();
    printk("flash_airoha_init was called and return %d\r\n", op_ret);
    if(op_ret == 0){
        printk("Flash ID: 0x%02X 0x%02X 0x%02X\r\n", nor_id[0], nor_id[1], nor_id[2]);
    }
    g_flash_init_res = op_ret;
    return op_ret;
}

#if defined(CONFIG_FLASH_PAGE_LAYOUT)
static const struct flash_pages_layout air_flash_pages_layout = {
    .pages_count = DT_REG_SIZE(SOC_NV_FLASH_NODE)/DT_PROP(SOC_NV_FLASH_NODE, erase_block_size),
    .pages_size = DT_PROP(SOC_NV_FLASH_NODE, erase_block_size),
};
static void flash_airoha_page_layout(const struct device *dev,
                 const struct flash_pages_layout **layout,
                 size_t *layout_size)
{
    printk("flash_airoha_page_layout return (%d, 0x%X)\r\n",
        air_flash_pages_layout.pages_count,
        (uint32_t)(air_flash_pages_layout.pages_size)
    );
    *layout = &air_flash_pages_layout;
    *layout_size = 1;
}
#endif


static const struct flash_driver_api flash_airoha_drv_apis = {
    .read = flash_airoha_read,
    .write = flash_airoha_write,
    .erase = flash_airoha_erase,
    .get_parameters = flash_airoha_get_parameters,
#if defined(CONFIG_FLASH_PAGE_LAYOUT)
    .page_layout = flash_airoha_page_layout,
#endif /* CONFIG_FLASH_PAGE_LAYOUT */
#if defined(CONFIG_FLASH_JESD216_API)
    .sfdp_read = NULL,
    .read_jedec_id = flash_airoha_read_jedec_id,
#endif /* CONFIG_FLASH_JESD216_API */
};


/* Currently airoha's flash controller can only connect to one flash device. */
DEVICE_DT_INST_DEFINE(0, flash_airoha_init, NULL,
    NULL, NULL,
    CONFIG_FLASH_INIT_LEVEL, CONFIG_FLASH_INIT_PRIORITY,
    &flash_airoha_drv_apis);

