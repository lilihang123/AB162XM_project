/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#include "hal_wdt.h"

#ifdef HAL_WDT_MODULE_ENABLED
#include "air_chip.h"
#include "hal_gpt.h"
#include "hal_nvic.h"
#include "hal_wdt_internal.h"

#define     WDT_TIMEOUT_SECONDS_MAX  (1023)

#ifdef CONFIG_WDT_FAST_MODE_ENABLE

void wdt_wait_restart_update_done(uint32_t  channel)
{
    if (channel == 0) {
        while((RGU->wdt_sw_restart.word) & 0x1);
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        while((RGU_1->wdt_sw_restart.word) & 0x1);
    }
#endif
}

void wdt_set_length(uint32_t channel, uint32_t seconds)
{
    uint32_t length_register_value = 0;
    if (seconds > WDT_TIMEOUT_SECONDS_MAX) {
        seconds = WDT_TIMEOUT_SECONDS_MAX;
    }
    length_register_value = (seconds * 1000000) / WDT_TICK_UNIT;
    length_register_value <<= WDT_LENGTH_WDT_LENGTH_OFFSET;

    if (channel == 0) {
        /* write the length register */
        length_register_value |= WDT_LENGTH_KEY << WDT_LENGTH_KEY_OFFSET;
        wdt_wait_restart_update_done(channel);
        RGU->wdt_length.word = length_register_value;
        /*restart WDT to let the new value take effect */
        RGU->wdt_sw_restart.word = WDT_SW_RESTART_KEY;
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        /* write the length register */
        length_register_value |= WDT1_LENGTH_KEY << WDT_LENGTH_KEY_OFFSET;
        wdt_wait_restart_update_done(channel);
        RGU_1->wdt_length.word = length_register_value;
        /*restart WDT to let the new value take effect */
        RGU_1->wdt_sw_restart.word = WDT1_SW_RESTART_KEY;
    }
#endif
}

void wdt_set_restart(uint32_t channel)
{
    if (channel == 0) {
        if ((RGU->wdt_sw_restart.word) & 0x1) {
            return;
        }
        RGU->wdt_sw_restart.word = WDT_SW_RESTART_KEY;
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        if ((RGU_1->wdt_sw_restart.word) & 0x1) {
            return;
        }
        RGU_1->wdt_sw_restart.word = WDT1_SW_RESTART_KEY;
    }
#endif
}

#else

#define     WDT_HW_BLOCK_TICK        8
#define     WDT_OP_FEED_DOG          1
#define     WDT_OP_SET_LENGTH        2

typedef enum {
    WDT_O_SAFE = 0,
    WDT_O_IGNORE,
    WDT_O_DELAY
} wdt_op_statue_t;


/*For resolve WDT HW limitation*/
wdt_op_statue_t     wdt_check_operate_is_safe(uint32_t  channel, uint32_t curr_stat)
{
    static uint32_t prev_tick[2] = {0, 0};
    static uint32_t prev_stat[2] = {0, 0};

    uint32_t        curr_tick = 0;
    uint32_t        dura_tick = 0;
    uint32_t        status;
    wdt_op_statue_t ret;

    /*Disable IRQ */
    hal_nvic_save_and_set_interrupt_mask(&status);

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &curr_tick);
    hal_gpt_get_duration_count(prev_tick[channel], curr_tick, &dura_tick);

    if (dura_tick < WDT_HW_BLOCK_TICK) {
        switch (prev_stat[channel]) {
            case WDT_OP_FEED_DOG:
                if (curr_stat == WDT_OP_FEED_DOG) {
                    ret = WDT_O_IGNORE;
                } else {
                    ret = WDT_O_DELAY;
                }
                break;
            case WDT_OP_SET_LENGTH:
                if (curr_stat == WDT_OP_FEED_DOG) {
                    ret = WDT_O_SAFE;
                } else {
                    ret = WDT_O_DELAY;
                }
                break;
            default:
                ret = WDT_O_SAFE;
                break;
        }

    } else {
        ret = WDT_O_SAFE;
    }
    /* Update tick only operate WDT HW */
    if (ret != WDT_O_IGNORE) {
        prev_tick[channel] = curr_tick;
        prev_stat[channel] = curr_stat;
    }
    /*Enable IRQ */
    hal_nvic_restore_interrupt_mask(status);
    return ret;
}


void wdt_set_length(uint32_t channel, uint32_t seconds)
{
    uint32_t length_register_value = 0;
    wdt_op_statue_t  status;
    if (seconds > WDT_TIMEOUT_SECONDS_MAX) {
        seconds = WDT_TIMEOUT_SECONDS_MAX;
    }
    length_register_value = (seconds * 1000000) / WDT_TICK_UNIT;
    length_register_value <<= WDT_LENGTH_WDT_LENGTH_OFFSET;

    status = wdt_check_operate_is_safe(channel, WDT_OP_SET_LENGTH);
    switch (status) {
        case WDT_O_DELAY:
            hal_gpt_delay_us(WDT_HW_BLOCK_TICK * 32);
            break;
        case WDT_O_SAFE:
            break;
        default:
            break;
    }

    if (channel == 0) {
        /* write the length register */
        length_register_value |= WDT_LENGTH_KEY << WDT_LENGTH_KEY_OFFSET;
        RGU->wdt_length.word = length_register_value;
        /*restart WDT to let the new value take effect */
        RGU->wdt_sw_restart.word = WDT_SW_RESTART_KEY;
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        /* write the length register */
        length_register_value |= WDT1_LENGTH_KEY << WDT_LENGTH_KEY_OFFSET;
        RGU_1->wdt_length.word = length_register_value;
        /*restart WDT to let the new value take effect */
        RGU_1->wdt_sw_restart.word = WDT1_SW_RESTART_KEY;
    }
#endif
}

void wdt_set_restart(uint32_t channel)
{
    wdt_op_statue_t  status;

    status = wdt_check_operate_is_safe(channel, WDT_OP_FEED_DOG);

    switch (status) {
        case WDT_O_IGNORE:
            return;
        case WDT_O_DELAY:
            hal_gpt_delay_us(WDT_HW_BLOCK_TICK * 32);
            break;
        case WDT_O_SAFE:
            break;
        default:
            break;
    }
    if (channel == 0) {
        RGU->wdt_sw_restart.word = WDT_SW_RESTART_KEY;
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        RGU_1->wdt_sw_restart.word = WDT1_SW_RESTART_KEY;
    }
#endif
}

#endif

void wdt_set_mode(uint32_t channel, uint32_t value)
{
    if (value == HAL_WDT_MODE_INTERRUPT) {
        if (channel == 0) {
            RGU->wdt_ie.word = (WDT_IE_WDT_IRQ_IE_MASK | (WDT_IRQ_IE_KEY << WDT_IE_KEY_IRQ_OFFSET)) |
                                   (WDT_IE_WDT_NMI_IE_MASK | (WDT_NMI_IE_KEY << WDT_IE_KEY_NMI_OFFSET));
        }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
        else {
            RGU_1->wdt_ie.word = (WDT_IE_WDT_IRQ_IE_MASK | (WDT1_IRQ_IE_KEY << WDT_IE_KEY_IRQ_OFFSET)) |
                                    (WDT_IE_WDT_NMI_IE_MASK | (WDT1_NMI_IE_KEY << WDT_IE_KEY_NMI_OFFSET));
        }
#endif
    } else {
        if (channel == 0) {
            RGU->wdt_ie.word = (WDT_IRQ_IE_KEY << WDT_IE_KEY_IRQ_OFFSET) |
                                   (WDT_NMI_IE_KEY << WDT_IE_KEY_NMI_OFFSET);
        }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
        else {
            RGU_1->wdt_ie.word = (WDT1_IRQ_IE_KEY << WDT_IE_KEY_IRQ_OFFSET) |
                                    (WDT1_NMI_IE_KEY << WDT_IE_KEY_NMI_OFFSET);
        }
#endif
    }
}

void wdt_set_sw_rst(uint32_t channel)
{
    if (channel == 0) {
        RGU->wdt_sw_rst.word = WDT_SW_RST_KEY;
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        RGU_1->wdt_sw_rst.word = WDT1_SW_RST_KEY;
    }
#endif
}

void wdt_set_enable(uint32_t channel, uint32_t enable)
{
    if (channel == 0) {
        if (enable) {
            RGU->wdt_en.word = (WDT_EN_WDT_EN_MASK | (WDT_EN_KEY << WDT_EN_KEY0_OFFSET)) | ((WDT_EN_TEST_MODE_KEY << WDT_EN_KEY1_OFFSET));
            RGU->wdt_auto_restart_en.word = (WDT_AUTO_RESTART_EN_WDT_AUTO_RESTART_EN_MASK | (WDT_AUTO_RESTART_EN_KEY << WDT_AUTO_RESTART_EN_KEY_OFFSET));
        } else {
            RGU->wdt_en.word = (WDT_EN_KEY << WDT_EN_KEY0_OFFSET) | (WDT_EN_TEST_MODE_KEY << WDT_EN_KEY1_OFFSET);
            RGU->wdt_auto_restart_en.word = (WDT_AUTO_RESTART_EN_KEY << WDT_AUTO_RESTART_EN_KEY_OFFSET);
        }
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        if (enable) {
            RGU_1->wdt_en.word = (WDT_EN_WDT_EN_MASK | (WDT1_EN_KEY << WDT_EN_KEY0_OFFSET));
            RGU_1->wdt_auto_restart_en.word = (WDT_AUTO_RESTART_EN_WDT_AUTO_RESTART_EN_MASK | (WDT1_AUTO_RESTART_EN_KEY << WDT_AUTO_RESTART_EN_KEY_OFFSET));
        } else {
            RGU_1->wdt_en.word = (WDT1_EN_KEY << WDT_EN_KEY0_OFFSET);
            RGU_1->wdt_auto_restart_en.word = (WDT1_AUTO_RESTART_EN_KEY << WDT_AUTO_RESTART_EN_KEY_OFFSET);
        }
    }
#endif
}

hal_wdt_reset_status_t wdt_get_reset_status(uint32_t channel)
{
    uint32_t status_register_value = 0;

    if (channel == 0) {
        status_register_value = RGU->wdt_sta.word;
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        status_register_value = RGU_1->wdt_sta.word;
    }
#endif

    if (status_register_value & WDT_STA_WDT_HW_STA_MASK) {
        return HAL_WDT_TIMEOUT_RESET;
    } else if (status_register_value & WDT_STA_WDT_SW_STA_MASK) {
        return HAL_WDT_SOFTWARE_RESET;
    }

    return HAL_WDT_NONE_RESET;
}

bool wdt_get_enable_status(uint32_t channel)
{
    if (channel == 0) {
        if (RGU->wdt_en.word & WDT_EN_WDT_EN_MASK) {
            return true;
        } else {
            return false;
        }
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        if (RGU_1->wdt_en.word & WDT_EN_WDT_EN_MASK) {
            return true;
        } else {
            return false;
        }
    }
#else
    return false;
#endif
}

hal_wdt_mode_t wdt_get_mode_status(uint32_t channel)
{
    if (channel == 0) {
        if (RGU->wdt_ie.word & (WDT_IE_WDT_IRQ_IE_MASK | WDT_IE_WDT_NMI_IE_MASK)) {
            return HAL_WDT_MODE_INTERRUPT;
        } else {
            return HAL_WDT_MODE_RESET;
        }
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        if (RGU->wdt_ie.word & (WDT_IE_WDT_IRQ_IE_MASK | WDT_IE_WDT_NMI_IE_MASK)) {
            return HAL_WDT_MODE_INTERRUPT;
        } else {
            return HAL_WDT_MODE_RESET;
        }
    }
#else
    __ASSERT_NO_MSG("can not run to here");
    return HAL_WDT_MODE_RESET;
#endif
}

bool wdt_clear_irq(uint32_t channel)
{
    uint32_t status = 0;

    if (channel == 0) {
        status = RGU->wdt_int.word;
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        status = RGU_1->wdt_int.word;
    }
#endif

    if (status & WDT_INT_WDT_INT_MASK) {
        return true;
    } else {
        return false;
    }
}

void wdt_set_pmu_mask(uint32_t enable)
{
    if (enable) {
        RGU_MISC->rst_mask1.field.PMU_RESET = ((0x1 << 8) | (WDT_PMU_MASK_SW_RST_KEY));
    } else {
        RGU_MISC->rst_mask1.field.PMU_RESET = (WDT_PMU_MASK_SW_RST_KEY);
    }
}

void wdt_set_core_mask(uint32_t enable)
{
    if (enable) {
        RGU_MISC->rst_mask0.field.AIRCR_RESET = (0x1 << 8) | WDT_AIRCR_MASK_SW_RST_KEY;
    } else {
        RGU_MISC->rst_mask0.field.AIRCR_RESET = WDT_AIRCR_MASK_SW_RST_KEY;
    }
}


void wdt_set_jtag_mask(uint32_t enable)
{
    if (enable) {
        RGU_MISC->rst_mask0.field.JTAG_RESET = (0x1 << 8) | WDT_JTAG_MASK_SW_RST_KEY;
    } else {
        RGU_MISC->rst_mask0.field.JTAG_RESET = WDT_JTAG_MASK_SW_RST_KEY;
    }
}

void wdt_set_pmu_reset_polarity(uint32_t pmu_rst_inv_en)
{
    if (0 == pmu_rst_inv_en) {
        /*PMU reset active low*/
        RGU_MISC->rst_func_cont1.field.PMU_RST_INV_EN = (WDT_PMU_SW_RST_POLARITY_KEY);
    } else {
        /*PMU reset active high*/
        RGU_MISC->rst_func_cont1.field.PMU_RST_INV_EN = ((0x1 << 8) | (WDT_PMU_SW_RST_POLARITY_KEY));
    }
}

void wdt_clear_reset_status(wdt_reset_type_t type)
{
    switch (type) {
        case SYSTEM_RESET:
            RGU_MISC->sw_rstsys.word = SW_RSTSYS_SYSTEM_SW_RST_MASK | WDT_SW_RSTSYS_KEY;
            RGU_MISC->sw_rstsys.word = WDT_SW_RSTSYS_KEY;
            break;
        case RISCV_RESET:
            RGU_MISC->sw_rst0.field.RISCV_SW_RST = SW_RST0_MODULE0_SW_RST_MASK | WDT_SW_RESET_RISCV_KEY;
            RGU_MISC->sw_rst0.field.RISCV_SW_RST = WDT_SW_RESET_RISCV_KEY;
            break;
        case CONNSYS_RESET:
            RGU_MISC->sw_rst1.field.CONNSYS_SW_RST = SW_RST1_MODULE2_SW_RST_MASK | WDT_CONNSYS_SW_RST_KEY;
            RGU_MISC->sw_rst1.field.CONNSYS_SW_RST = WDT_CONNSYS_SW_RST_KEY;
            break;
        case AUDIOSYS_RESET:
            RGU_MISC->sw_rst2.field.AUDIOSYS_SW_RST = SW_RST2_MODULE4_SW_RST_MASK | WDT_AUDIOSYS_SW_RST_KEY;
            RGU_MISC->sw_rst2.field.AUDIOSYS_SW_RST = WDT_AUDIOSYS_SW_RST_KEY;
            break;
        case USB_RESET:
            RGU_MISC->sw_rst3.field.USB_SW_RST = (0x1 << 8) | WDT_USB_SW_RST_KEY;
            RGU_MISC->sw_rst3.field.USB_SW_RST = WDT_USB_SW_RST_KEY;
            break;
        case USBIF_RESET:
            RGU_MISC->sw_rst3.field.USBSIF_SW_RST = (0x1 << 8) | WDT_USBIF_SW_RST_KEY;
            RGU_MISC->sw_rst3.field.USBSIF_SW_RST = WDT_USBIF_SW_RST_KEY;
            break;
        default:
            break;
    }
}

void wdt_reset_default_value(uint32_t channel)
{
    uint32_t temp_value;

    if (channel == 0) {
        temp_value = RGU->wdt_int.word;
        (void)temp_value;
        RGU->wdt_en.word = (WDT_EN_KEY << WDT_EN_KEY0_OFFSET);
        RGU->wdt_length.word = 0x07FF0000 | (WDT_LENGTH_KEY << WDT_LENGTH_KEY_OFFSET);
        RGU->wdt_interval.word = 0x0FFF0000 | (WDT_INTERVAL_KEY << WDT_INTERVAL_KEY_OFFSET);
        RGU->wdt_auto_restart_en.word = WDT_AUTO_RESTART_EN_KEY << WDT_AUTO_RESTART_EN_KEY_OFFSET;
        RGU->wdt_ie.word = (WDT_IE_KEY_IRQ_OFFSET << WDT_IE_KEY_IRQ_OFFSET) | (WDT_NMI_IE_KEY << WDT_IE_KEY_NMI_OFFSET);
        RGU->wdt_wakeup.word = WDT_WAKEUP_EN_KEY << WDT_WAKEUP_EN_KEY_WAKEUP_EN_OFFSET;
        temp_value = RGU->wdt_wakeup.word;
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        temp_value = RGU_1->wdt_int.word;
        (void)temp_value;
        RGU_1->wdt_en.word = (WDT1_EN_KEY << WDT_EN_KEY0_OFFSET);
        RGU_1->wdt_length.word = 0x07FF0000 | (WDT1_LENGTH_KEY << WDT_LENGTH_KEY_OFFSET);
        RGU_1->wdt_interval.word = 0x0FFF0000 | (WDT1_INTERVAL_KEY << WDT_INTERVAL_KEY_OFFSET);
        RGU_1->wdt_auto_restart_en.word = WDT1_AUTO_RESTART_EN_KEY << WDT_AUTO_RESTART_EN_KEY_OFFSET;
        RGU_1->wdt_ie.word = (WDT1_IRQ_IE_KEY << WDT_IE_KEY_IRQ_OFFSET) | (WDT1_NMI_IE_KEY << WDT_IE_KEY_NMI_OFFSET);
        RGU_1->wdt_wakeup.word = WDT1_WAKEUP_EN_KEY << WDT_WAKEUP_EN_KEY_WAKEUP_EN_OFFSET;
        temp_value = RGU_1->wdt_wakeup.word;
    }
#endif
}

void    wdt_dump_register(uint32_t channel)
{
    static uint8_t  idx = 0;

    (void)idx;
    printk("wdt channel %d dump(%d):", channel, idx++);
    if (channel == 0) {
        printk("en(%x), length(%x), interval(%x), auto_restart_en(%x), pmu(%x)",
            RGU->wdt_en.word,
            RGU->wdt_length.word,
            RGU->wdt_interval.word,
            RGU->wdt_auto_restart_en.word,
            RGU_MISC->rst_mask1.word
        );
        printk("sta(%x), ie(%x), interrupt(%x), wakeup(%x)",
            RGU->wdt_sta.word,
            RGU->wdt_ie.word,
            RGU->wdt_int.word,
            RGU->wdt_wakeup.word
        );
    }
#if IS_ENABLED(CONFIG_AIR_WDT_2ND)
    else {
        printk("en(%x), length(%x), interval(%x), auto_restart_en(%x), pmu(%x)",
            RGU_1->wdt_en.word,
            RGU_1->wdt_length.word,
            RGU_1->wdt_interval.word,
            RGU_1->wdt_auto_restart_en.word,
            RGU_MISC->rst_mask1.word
        );
        printk("sta(%x), ie(%x), int(%x), wakeup(%x)",
            RGU_1->wdt_sta.word,
            RGU_1->wdt_ie.word,
            RGU_1->wdt_int.word,
            RGU_1->wdt_wakeup.word
        );
    }
#endif
}

void    wdt_exception_config_internal_use(uint32_t seconds)
{
    uint32_t length_register_value = 0;
    /* read clear WDT NMI/IRQ status */
    length_register_value = RGU->wdt_int.word;

    /* between two wdt feed / length set needs to be greater than 6 Tick * 32K */
    hal_gpt_delay_us(8 * 32);//256us

    /* disable wdt */
    RGU->wdt_en.word = (WDT_EN_KEY << WDT_EN_KEY0_OFFSET) | (WDT_EN_TEST_MODE_KEY << WDT_EN_KEY1_OFFSET);
    RGU->wdt_auto_restart_en.word = (WDT_AUTO_RESTART_EN_KEY << WDT_AUTO_RESTART_EN_KEY_OFFSET);

    /* set length */
    length_register_value = (seconds * 1000000) / WDT_TICK_UNIT;
    length_register_value <<= WDT_LENGTH_WDT_LENGTH_OFFSET;

    /* write the length register */
    length_register_value |= WDT_LENGTH_KEY << WDT_LENGTH_KEY_OFFSET;
    RGU->wdt_length.word = length_register_value;
    /*restart WDT to let the new value take effect */
    RGU->wdt_sw_restart.word = WDT_SW_RESTART_KEY;

    /* set reset mode */
    RGU->wdt_ie.word = (WDT_IRQ_IE_KEY << WDT_IE_KEY_IRQ_OFFSET) | (WDT_NMI_IE_KEY << WDT_IE_KEY_NMI_OFFSET);

    /* set cold reset */
    RGU_MISC->rst_mask1.field.PMU_RESET = (WDT_PMU_MASK_SW_RST_KEY);

    /* enable wdt */
    RGU->wdt_en.word = (WDT_EN_WDT_EN_MASK | (WDT_EN_KEY << WDT_EN_KEY0_OFFSET)) | ((WDT_EN_TEST_MODE_KEY << WDT_EN_KEY1_OFFSET));
    RGU->wdt_auto_restart_en.word = (WDT_AUTO_RESTART_EN_WDT_AUTO_RESTART_EN_MASK | (WDT_AUTO_RESTART_EN_KEY << WDT_AUTO_RESTART_EN_KEY_OFFSET));
}

#endif


