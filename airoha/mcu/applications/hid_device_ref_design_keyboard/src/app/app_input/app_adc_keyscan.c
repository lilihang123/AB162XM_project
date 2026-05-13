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

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#if defined(AIR_ADC_KEYSCAN_ENABLE)

#include "app_adc_keyscan.h"
#include "hid_keycode_id.h"
#include "memory_attribute.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"
#include "hid_scenario_USB_mode.h"
#include "hal_usb.h"
#include "hal_usb_internal.h"
#include "air_usb_hid.h"
#include "hal_gpt.h"

#if defined(CONFIG_AIR_KB_DEFAULT_MATRIX_ENABLE)
#include "app_kb_matrix_demo.h"
#endif

#include "pka_share.h"
#include "pka.h"

typedef struct __attribute__((__packed__)) {
    uint8_t report_id;
    uint8_t data[6];
    uint8_t reserved;
} hid_keyboard_gaming_mode_data_t;

sw_keyscan_keybit_data_t output_data;
air_usb_hid_gaming_kb_nkey_report_t hid_keyboard_report_wired_mode_data;
air_usb_hid_gaming_kb_nkey_report_t last_hid_keyboard_report_wired_mode_data;
air_usb_hid_consumer_report_t hid_keyboard_report_consumer_key;
air_usb_hid_consumer_report_t last_hid_keyboard_report_consumer_key;

air_usb_hid_gaming_kb_nkey_report_t hid_keyboard_report_gaming_mode_data;
air_usb_hid_gaming_kb_nkey_report_t hid_keyboard_report_gaming_mode_data_last;

static bool fn_key_press_flag;
static uint16_t fn_key_pos_byte;
static uint16_t fn_key_pos_bit;

extern uint32_t usb_user_id;
extern const struct device *hdev3;

#ifdef KB_USB_MODE
ATTR_TEXT_IN_TCM void keyboard_send_report_wired_mode(void)
{
    hid_keyboard_report_wired_mode_data.report_id = REPORT_ID_KB_STD;
    hid_keyboard_report_consumer_key.report_id = AIR_USB_HID_CONSUMER_REPORT_ID;
#if 0
    printk("modifier_key = 0x%x\n",hid_keyboard_report_wired_mode_data.modifier);
    int i=0;
    for(i = 0;i<15;i++)
    {
        printk("data[%d] = 0x%x\n",i,hid_keyboard_report_wired_mode_data.keymap[i]);
    }
#endif
    if(memcmp(&hid_keyboard_report_wired_mode_data, &last_hid_keyboard_report_wired_mode_data, sizeof(air_usb_hid_gaming_kb_nkey_report_t)))
    {
        air_usb_hid_tx(usb_user_id, hdev3, sizeof(air_usb_hid_gaming_kb_nkey_report_t), (uint8_t *)&hid_keyboard_report_wired_mode_data);
        last_hid_keyboard_report_wired_mode_data = hid_keyboard_report_wired_mode_data;
    }
    memset(&hid_keyboard_report_wired_mode_data, 0, sizeof(air_usb_hid_gaming_kb_nkey_report_t));

    if(memcmp(&hid_keyboard_report_consumer_key, &last_hid_keyboard_report_consumer_key, sizeof(air_usb_hid_consumer_report_t)))
    {
        air_usb_hid_tx(usb_user_id, hdev3, sizeof(air_usb_hid_consumer_report_t), (uint8_t *)&hid_keyboard_report_consumer_key);
        last_hid_keyboard_report_consumer_key = hid_keyboard_report_consumer_key;

    }
    memset(&hid_keyboard_report_consumer_key, 0, sizeof(air_usb_hid_consumer_report_t));
}

ATTR_TEXT_IN_TCM void send_keyboard_keycode_n_key()
{
    keyboard_send_report_wired_mode();
}
#endif/*KB_USB_MODE*/

#ifdef KB_24G_MODE
ATTR_TEXT_IN_TCM void keyboard_send_report_gaming_mode(void)
{
    hid_keyboard_gaming_mode_data_t bt_packet = {0};
    uint8_t* outgoing_buf[2] = {NULL};
    uint8_t* outgoing_payload[2] = {NULL};
    bool data_change_flag =false;

    /* genetor air packet and update the sent key info */
    /* TODO: improve it by word access */
    if ((hid_keyboard_report_gaming_mode_data_last.modifier != hid_keyboard_report_gaming_mode_data.modifier)
        || (hid_keyboard_report_gaming_mode_data_last.keymap[0] != hid_keyboard_report_gaming_mode_data.keymap[0])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[1] != hid_keyboard_report_gaming_mode_data.keymap[1])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[2] != hid_keyboard_report_gaming_mode_data.keymap[2])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[3] != hid_keyboard_report_gaming_mode_data.keymap[3])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[4] != hid_keyboard_report_gaming_mode_data.keymap[4]))
    {
        bt_packet.report_id = REPORT_ID_KEYBOARD_BIT_REP_1;
        bt_packet.data[0] = hid_keyboard_report_gaming_mode_data.modifier;
        bt_packet.data[1] = hid_keyboard_report_gaming_mode_data.keymap[0];
        bt_packet.data[2] = hid_keyboard_report_gaming_mode_data.keymap[1];
        bt_packet.data[3] = hid_keyboard_report_gaming_mode_data.keymap[2];
        bt_packet.data[4] = hid_keyboard_report_gaming_mode_data.keymap[3];
        bt_packet.data[5] = hid_keyboard_report_gaming_mode_data.keymap[4];

        data_change_flag =true;
        hid_keyboard_report_gaming_mode_data_last.modifier  = hid_keyboard_report_gaming_mode_data.modifier;
        hid_keyboard_report_gaming_mode_data_last.keymap[0] = hid_keyboard_report_gaming_mode_data.keymap[0];
        hid_keyboard_report_gaming_mode_data_last.keymap[1] = hid_keyboard_report_gaming_mode_data.keymap[1];
        hid_keyboard_report_gaming_mode_data_last.keymap[2] = hid_keyboard_report_gaming_mode_data.keymap[2];
        hid_keyboard_report_gaming_mode_data_last.keymap[3] = hid_keyboard_report_gaming_mode_data.keymap[3];
        hid_keyboard_report_gaming_mode_data_last.keymap[4] = hid_keyboard_report_gaming_mode_data.keymap[4];
    }
    else if ((hid_keyboard_report_gaming_mode_data_last.keymap[5] != hid_keyboard_report_gaming_mode_data.keymap[5])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[6] != hid_keyboard_report_gaming_mode_data.keymap[6])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[7] != hid_keyboard_report_gaming_mode_data.keymap[7])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[8] != hid_keyboard_report_gaming_mode_data.keymap[8])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[9] != hid_keyboard_report_gaming_mode_data.keymap[9]))
    {
        bt_packet.report_id = REPORT_ID_KEYBOARD_BIT_REP_2;
        bt_packet.data[0] = 0;
        bt_packet.data[1] = hid_keyboard_report_gaming_mode_data.keymap[5];
        bt_packet.data[2] = hid_keyboard_report_gaming_mode_data.keymap[6];
        bt_packet.data[3] = hid_keyboard_report_gaming_mode_data.keymap[7];
        bt_packet.data[4] = hid_keyboard_report_gaming_mode_data.keymap[8];
        bt_packet.data[5] = hid_keyboard_report_gaming_mode_data.keymap[9];

        data_change_flag =true;
        hid_keyboard_report_gaming_mode_data_last.keymap[5]  = hid_keyboard_report_gaming_mode_data.keymap[5];
        hid_keyboard_report_gaming_mode_data_last.keymap[6]  = hid_keyboard_report_gaming_mode_data.keymap[6];
        hid_keyboard_report_gaming_mode_data_last.keymap[7]  = hid_keyboard_report_gaming_mode_data.keymap[7];
        hid_keyboard_report_gaming_mode_data_last.keymap[8]  = hid_keyboard_report_gaming_mode_data.keymap[8];
        hid_keyboard_report_gaming_mode_data_last.keymap[9]  = hid_keyboard_report_gaming_mode_data.keymap[9];
        hid_keyboard_report_gaming_mode_data_last.keymap[10] = hid_keyboard_report_gaming_mode_data.keymap[10];
    }
    else if ((hid_keyboard_report_gaming_mode_data_last.keymap[10] != hid_keyboard_report_gaming_mode_data.keymap[10])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[11] != hid_keyboard_report_gaming_mode_data.keymap[11])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[12] != hid_keyboard_report_gaming_mode_data.keymap[12])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[13] != hid_keyboard_report_gaming_mode_data.keymap[13])
        || (hid_keyboard_report_gaming_mode_data_last.keymap[14] != hid_keyboard_report_gaming_mode_data.keymap[14]))
    {
        bt_packet.report_id = REPORT_ID_KEYBOARD_BIT_REP_3;
        bt_packet.data[0] = 0;
        bt_packet.data[1] = hid_keyboard_report_gaming_mode_data.keymap[10];
        bt_packet.data[2] = hid_keyboard_report_gaming_mode_data.keymap[11];
        bt_packet.data[3] = hid_keyboard_report_gaming_mode_data.keymap[12];
        bt_packet.data[4] = hid_keyboard_report_gaming_mode_data.keymap[13];
        bt_packet.data[5] = hid_keyboard_report_gaming_mode_data.keymap[14];

        data_change_flag =true;
        hid_keyboard_report_gaming_mode_data_last.keymap[10] = hid_keyboard_report_gaming_mode_data.keymap[10];
        hid_keyboard_report_gaming_mode_data_last.keymap[11] = hid_keyboard_report_gaming_mode_data.keymap[11];
        hid_keyboard_report_gaming_mode_data_last.keymap[12] = hid_keyboard_report_gaming_mode_data.keymap[12];
        hid_keyboard_report_gaming_mode_data_last.keymap[13] = hid_keyboard_report_gaming_mode_data.keymap[13];
        hid_keyboard_report_gaming_mode_data_last.keymap[14] = hid_keyboard_report_gaming_mode_data.keymap[14];
    }

    if(data_change_flag)
    {
        /* deliver the air packet to controller */
        outgoing_buf[0] = pka_share_tx_buf_get_by_idx(0);
        outgoing_payload[0] = pka_share_tx_buf_get_payload(outgoing_buf[0]);
        outgoing_buf[1] = pka_share_tx_buf_get_by_idx(1);
        outgoing_payload[1] = pka_share_tx_buf_get_payload(outgoing_buf[1]);
        /* ack buffer */
        if (outgoing_payload[0] != NULL)
        {
            *((uint32_t *)(outgoing_payload[0]) + 0) = *((uint32_t *)(&bt_packet) + 0);
            *((uint32_t *)(outgoing_payload[0]) + 1) = *((uint32_t *)(&bt_packet) + 1);
            pka_share_tx_buf_set_pkt_len((uint16_t*)outgoing_buf[0], sizeof(hid_keyboard_gaming_mode_data_t));
        }
        /* nack buffer */
        if (outgoing_payload[1] != NULL)
        {
            *((uint32_t *)(outgoing_payload[1]) + 0) = *((uint32_t *)(&bt_packet) + 0);
            *((uint32_t *)(outgoing_payload[1]) + 1) = *((uint32_t *)(&bt_packet) + 1);
            pka_share_tx_buf_set_pkt_len((uint16_t*)outgoing_buf[1], sizeof(hid_keyboard_gaming_mode_data_t));
        }
    }

    memset(&hid_keyboard_report_gaming_mode_data, 0, sizeof(air_usb_hid_gaming_kb_nkey_report_t));
}

ATTR_TEXT_IN_TCM void adc_keyscan_output_decode_gaming_mode(sw_keyscan_keybit_data_t *keybit_data)
{
#if 0
    printk("sw_keyscan_output_decode data");
    int a;
    for(a=0;a<7;a++)
    {
        printk("data[%d]=0x%x",a,keybit_data->keyid_bit[a]);
    }
#endif
    /*convert keybit map report to hid keycode map report */
    uint8_t i,j,k;
    uint8_t consumer_key_num = 0;
    uint16_t* ary_ptr_16 = (&(keybit_data->keyid_bit[0]));

    /*check fn key status*/
    if((*(ary_ptr_16 + fn_key_pos_byte))&(fn_key_pos_bit))
    {
        fn_key_press_flag = true;
        *(ary_ptr_16 + fn_key_pos_byte) &= (~fn_key_pos_bit);//clear fn key bit status
    }else{
        fn_key_press_flag = false;
    }

    /*keybit -> keycode*/
    for (i = 0; i < KEY_MATRIX_MUX_MAX_INDEX; i++) {
        if (*(ary_ptr_16 + i))
        {
            uint8_t* ary_ptr_8 = (uint8_t*)(ary_ptr_16 + i);
            for(j=0;j<2;j++)
            {
                if(*(ary_ptr_8 + j))
                {
                    uint8_t idx = 0;
                    uint16_t keycode;
                    for(k=0;k<8;k++)
                    {
                        if ((*(ary_ptr_8 + j)) & (0x01 << k))
                        {
                            idx = 16*i+8*j+k;
                            if(fn_key_press_flag)
                            {
                                keycode = FN_KEY_MATRIX[idx];
                            }else
                            {
                                keycode = KEY_MATRIX[idx];
                            }

                            /*check function key*/
                            if((keycode >> 12) == FN_KEY_FLAG)
                            {
                                uint16_t func_idx = keycode & 0xFFF;
                                if ((KEYBOARD_FUNCTION_POINTER_NUMBER > func_idx) && (keyboard_fun_ptr_list[func_idx]))
                                {
                                    keyboard_fun_ptr_list[func_idx](keycode);
                                }
                            }
                            else if ((keycode >> 12 ) == REPORT_ID_KB_STD)
                            {
                                uint8_t key_code_temp;
                                uint8_t pos_byte;
                                uint8_t pos_bit;
                                key_code_temp = keycode & 0x00FF;
                                pos_byte = (key_code_temp >> 3);     // divide by 8
                                pos_bit = 0x01 << (key_code_temp & 0x7);
                                if ( (keycode >= KC_LCTRL) &&  (keycode <= KC_RGUI ))
                                {
                                    uint8_t bit_shift = keycode - KC_LCTRL;
                                    hid_keyboard_report_gaming_mode_data.modifier |= (0x01 << bit_shift);
                                }
                                else if (key_code_temp < 120)
                                {
                                    hid_keyboard_report_gaming_mode_data.keymap[pos_byte] |= pos_bit;
                                }else
                                {
                                    // something wrong
                                }
                            }
                            else if ((keycode >> 12 ) == KEYCODE_FLAG_CONSUMER_KEY )
                            {
                                if(consumer_key_num < 2)
                                {
                                    hid_keyboard_report_consumer_key.consumer_usage[consumer_key_num++] = keycode & 0x0FFF;
                                }
                            }
                        }
                    }
                }else
                {
                    //no key in this 8 keybit
                }
            }
        }else
        {
            //no key in this 16 keybit
        }
    }

    pka_share_callback_type_t type;
    uint32_t tx_cnt;
    int ret;
    ret = pka_spi_callback_pre_process(&type, &tx_cnt);
    if(ret != 0)
    {
        printk("pka_spi_callback_pre_process failed");
    }

    keyboard_send_report_gaming_mode();
    pka_spi_callback_post_process();
}
#endif/*KB_24G_MODE*/

#ifdef KB_USB_MODE
ATTR_TEXT_IN_TCM void adc_keyscan_output_decode(sw_keyscan_keybit_data_t *keybit_data)
{
#if 0
    printk("sw_keyscan_output_decode data");
    int i;
    for(i=0;i<7;i++)
    {
        printk("data[%d]=0x%x",i,keybit_data->keyid_bit[i]);
    }
#endif
    /*convert keybit map report to hid keycode map report */
    uint8_t i,j,k;
    uint8_t consumer_key_num = 0;
    uint16_t* ary_ptr_16 = (&(keybit_data->keyid_bit[0]));

    /*check fn key status*/
    if((*(ary_ptr_16 + fn_key_pos_byte))&(fn_key_pos_bit))
    {
        fn_key_press_flag = true;
        *(ary_ptr_16 + fn_key_pos_byte) &= (~fn_key_pos_bit);//clear fn key bit status
    }else{
        fn_key_press_flag = false;
    }

    /*keybit -> keycode*/
    for (i = 0; i < KEY_MATRIX_MUX_MAX_INDEX; i++) {
        if (*(ary_ptr_16 + i))
        {
            uint8_t* ary_ptr_8 = (uint8_t*)(ary_ptr_16 + i);
            for(j=0;j<2;j++)
            {
                if(*(ary_ptr_8 + j))
                {
                    uint8_t idx = 0;
                    uint16_t keycode;
                    for(k=0;k<8;k++)
                    {
                        if ((*(ary_ptr_8 + j)) & (0x01 << k))
                        {
                            idx = 16*i+8*j+k;
                            if(fn_key_press_flag)
                            {
                                keycode = FN_KEY_MATRIX[idx];
                            }else
                            {
                                keycode = KEY_MATRIX[idx];
                            }

                            /*check function key*/
                            if((keycode >> 12) == FN_KEY_FLAG)
                            {
                                uint16_t func_idx = keycode & 0xFFF;
                                if ((KEYBOARD_FUNCTION_POINTER_NUMBER > func_idx) && (keyboard_fun_ptr_list[func_idx]))
                                {
                                    keyboard_fun_ptr_list[func_idx](keycode);
                                }
                            }
                            else if ((keycode >> 12 ) == REPORT_ID_KB_STD)
                            {
                                uint8_t key_code_temp;
                                uint8_t pos_byte;
                                uint8_t pos_bit;
                                key_code_temp = keycode & 0x00FF;
                                pos_byte = (key_code_temp >> 3);     // divide by 8
                                pos_bit = 0x01 << (key_code_temp & 0x7);
                                if ( (keycode >= KC_LCTRL) &&  (keycode <= KC_RGUI ))
                                {
                                    uint8_t bit_shift = keycode - KC_LCTRL;
                                    hid_keyboard_report_wired_mode_data.modifier |= (0x01 << bit_shift);
                                }
                                else if (key_code_temp < 120)
                                {
                                    hid_keyboard_report_wired_mode_data.keymap[pos_byte] |= pos_bit;
                                }else
                                {
                                    // something wrong
                                }
                            }
                            else if ((keycode >> 12 ) == REPORT_ID_KB_CONSUMER )
                            {
                                if(consumer_key_num < 2)
                                {
                                    hid_keyboard_report_consumer_key.consumer_usage[consumer_key_num++] = keycode & 0x0FFF;
                                }
                            }
                        }
                    }
                }else
                {
                    //no key in this 8 keybit
                }
            }
        }else
        {
            //no key in this 16 keybit
        }
    }
    send_keyboard_keycode_n_key();

}
#endif/*KB_USB_MODE*/

void app_adc_keyscan_init(void)
{
    sw_keyscan_cfg_t sw_keyscan_cfg = {
        .row_gpio_num = KEY_MATRIX_ROWS_NUM,
        .row_gpio_map = KEY_MATRIX_ROWS,
        .mux_en_gpio = KEY_MATRIX_MUX_EN,
        .mux_max_index = KEY_MATRIX_MUX_MAX_INDEX,
        .mux_trigger_index = KEY_MATRIX_MUX_YRIGGER_INDEX,
        .v_threshold = ADC_THRESHOLD,
    };

    adc_keyscan_status_t ret;
    ret = sw_keyscan_mcu_init(&sw_keyscan_cfg);
    if(ret != ADC_KEYSCAN_STATUS_OK)
    {
        printk("sw_keyscan_mcu_init failed");
    }

    #ifdef KB_USB_MODE
    sw_keyscan_mcu_register_callback(adc_keyscan_output_decode);
    #endif/*KB_USB_MODE*/
    fn_key_pos_byte = (KEY_MATRIX_FN_KEY_INDEX >> 4);     // divide by 16
    fn_key_pos_bit = 0x01 << (KEY_MATRIX_FN_KEY_INDEX & 0xf);
}

#endif /* AIR_ADC_KEYSCAN_ENABLE */