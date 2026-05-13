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

/* Includes ------------------------------------------------------------------*/
#include "riscv_hid_express_usb_mode.h"
#include "pka_share.h"
#include "pka.h"
#include "hal_gpt.h"
#include "hal_gpio.h"
#include "hal_ccni.h"
#include "hal_ccni_config.h"
#include "riscv_hid_express_xy_queue.h"
#if defined (CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
#include "riscv_hid_express_key_queue_keyboard.h"
#elif defined (AIR_PRODUCT_TYPE_MOUSE)
#include "riscv_hid_express_key_queue_mouse.h"
#elif defined (AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "riscv_hid_express_key_queue_game_controller.h"
#endif
#include "riscv_hid_report_id_selector.h"
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/


// #define USB_REPORT_LOG_SN

#define CCNI_EVENT_TO_CM33_USB    IRQGEN_RISCV2MCU_EVENT0

#define CCNI_MSG_USB   0x80
#define CANDIDATE_NUM    CANDIDATE_NUM_1R1T

/* Private variables ---------------------------------------------------------*/
uint32_t ccni_evt_status;
#if defined(AIR_PRODUCT_TYPE_MOUSE)
#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
static uint32_t last_report_id = REPORT_ID_MOUSE;
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP  */
T_ASSEMBLE_VAL_CTRL_S *usb_vCtrl_x;
T_ASSEMBLE_VAL_CTRL_S *usb_vCtrl_y;
#endif /* defined(AIR_PRODUCT_TYPE_MOUSE) */
#if !defined(AIR_USB_CCNI_WAKEUP_CM33)
T_HID_CCNI_USB_REPORT_S outgoing_report[1];
#endif

#if defined(USB_REPORT_LOG_SN)
uint32_t dbg_sn_num = 0;
#endif

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void hid_express_usb_mode_send_report_to_CM33(hal_ccni_message_t* outgoing_rep)
{
    // DBG_PING_H(DBG_SIGNAL_DEBUG_2);
    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    hal_ccni_set_event(CCNI_EVENT_TO_CM33_USB, NULL);
    #else
    hal_ccni_set_event(CCNI_EVENT_TO_CM33_USB, outgoing_rep);
    #endif
    // DBG_PING_L(DBG_SIGNAL_DEBUG_2);
}

#if defined(AIR_PRODUCT_TYPE_KEYBOARD) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void hid_express_usb_mode_generate_kb_consumer_reports(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result)
{
    tx_result &= 0x01;  // 2 candidates only. Ack or Nack
    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].kb_consumer2.report_id
                        , REPORT_ID_KB_CONSUMER
                        , outgoing->kb_consumer & LSB
                        , (outgoing->kb_consumer >> 8) & LSB
                        , (outgoing->kb_consumer >> 16) & LSB
                        );
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].kb_consumer2.consumer[3]
                        , (outgoing->kb_consumer >> 24) & LSB
                        , 0x00
                        , 0x00
                        , 0x00
                        );
    #else
    FAST_WORD_WRITE(    outgoing_report[0].ccni_msg_id
                        , CCNI_MSG_USB
                        , REPORT_ID_KB_CONSUMER
                        , outgoing->kb_consumer & LSB
                        , (outgoing->kb_consumer >> 8) & LSB
                        );
    FAST_WORD_WRITE(    outgoing_report[0].kb_consumer2.consumer[2]
                        , (outgoing->kb_consumer >> 16) & LSB
                        , (outgoing->kb_consumer >> 24) & LSB
                        , 0x00
                        , 0x00
                        );
    #endif
}
#endif

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void hid_express_usb_mode_generate_kb_std_reports(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result)
{
    tx_result &= 0x01;  // 2 candidates only. Ack or Nack
    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].kb_std5.report_id
                        , REPORT_ID_KB_STD
                        , outgoing->kb_std[0] & LSB
                        , (outgoing->kb_std[0] >> 8) & LSB
                        , (outgoing->kb_std[0] >> 16) & LSB
                        );
    FAST_WORD_WRITE(   hid_common->outgoing_report[0].kb_std5.keycode[2]
                        , (outgoing->kb_std[0] >> 24) & LSB
                        , outgoing->kb_std[1] & LSB
                        , (outgoing->kb_std[1] >> 8) & LSB
                        , 0
                        );
    #else
    FAST_WORD_WRITE(    outgoing_report[0].ccni_msg_id
                        , CCNI_MSG_USB
                        , REPORT_ID_KB_STD
                        , outgoing->kb_std[0] & LSB
                        , (outgoing->kb_std[0] >> 8) & LSB
                        );
    FAST_WORD_WRITE(   outgoing_report[0].kb_std5.keycode[1]
                        , (outgoing->kb_std[0] >> 16) & LSB
                        , (outgoing->kb_std[0] >> 24) & LSB
                        , outgoing->kb_std[1] & LSB
                        , (outgoing->kb_std[1] >> 8) & LSB
                        );
    #endif
}
#endif

#if !defined(AIR_PRODUCT_TYPE_MOUSE) && defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void hid_express_usb_mode_generate_12bits_reports(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result)
{
    tx_result &= 0x01;  // 2 candidates only. Ack or Nack

    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].ms_s16_z8.report_id
                        , REPORT_ID_MOUSE
                        , outgoing->ms_k
                        , 0
                        , 0
                        );
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].ms_s16_z8.y
                        , 0
                        , 0
                        , 0
                        , 0
                        );
    #else
    FAST_WORD_WRITE(    outgoing_report[0].ccni_msg_id
                        , CCNI_MSG_USB
                        , REPORT_ID_MOUSE
                        , outgoing->ms_k
                        , 0
                        );
    FAST_WORD_WRITE(    outgoing_report[0].ms_s16_z8.xy_val[1]
                        , 0
                        , 0
                        , 0
                        , 0
                        );
    #endif
}
#endif /* !defined(AIR_PRODUCT_TYPE_MOUSE) && (AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
void hid_express_usb_mode_generate_game_controller_reports(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result)
{
    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    if (lt_is_digital()){
        outgoing->lt = (outgoing->lt_rt_digital & 0x1) ? 1023 : 0;
    }
    if (rt_is_digital()){
        outgoing->rt = (outgoing->lt_rt_digital & 0x2) ? 1023 : 0;
    }
    hid_common->outgoing_report[0].gc_usb_payload.report_id = REPORT_ID_GAME_CONTROLLER;
    hid_common->outgoing_report[0].gc_usb_payload.x  = outgoing->x;
    hid_common->outgoing_report[0].gc_usb_payload.y  = outgoing->y;
    hid_common->outgoing_report[0].gc_usb_payload.z  = outgoing->z;
    hid_common->outgoing_report[0].gc_usb_payload.rz = outgoing->rz;
    hid_common->outgoing_report[0].gc_usb_payload.breake = outgoing->lt;
    hid_common->outgoing_report[0].gc_usb_payload.accelerator = outgoing->rt;
    hid_common->outgoing_report[0].gc_usb_payload.hat_switch = outgoing->hat_switch_byte;
    hid_common->outgoing_report[0].gc_usb_payload.button = outgoing->key_air_byte;
    outgoing->last_x  = outgoing->x;
    outgoing->last_y  = outgoing->y;
    outgoing->last_z  = outgoing->z;
    outgoing->last_rz = outgoing->rz;
    outgoing->last_lt = outgoing->lt;
    outgoing->last_rt = outgoing->rt;
    #endif
}
#elif defined (AIR_PRODUCT_TYPE_MOUSE)
void hid_express_usb_mode_generate_12bits_reports(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result)
{
    tx_result &= 0x01;  // 2 candidates only. Ack or Nack

    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].ms_s16_z8.report_id
                        , REPORT_ID_MOUSE
                        , outgoing->k
                        , (usb_vCtrl_x->predict_n[tx_result] & LSB)
                        , ((usb_vCtrl_x->predict_n[tx_result] >> 8) & LSB)
                        );
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].ms_s16_z8.y
                        , (usb_vCtrl_y->predict_n[tx_result] & LSB)
                        , ((usb_vCtrl_y->predict_n[tx_result] >> 8) & LSB)
                        , outgoing->z1
                        , outgoing->z2
                        );
    #else
    FAST_WORD_WRITE(    outgoing_report[0].ms_s16_z8.ccni_msg_id
                        , CCNI_MSG_USB
                        , REPORT_ID_MOUSE
                        , outgoing->k
                        , (usb_vCtrl_x->predict_n[tx_result] & LSB)
                        );
    FAST_WORD_WRITE(    outgoing_report[0].ms_s16_z8.y
                        , ((usb_vCtrl_x->predict_n[tx_result] >> 8) & LSB)
                        , (usb_vCtrl_y->predict_n[tx_result] & LSB)
                        , ((usb_vCtrl_y->predict_n[tx_result] >> 8) & LSB)
                        , outgoing->z1
                        );
    #endif
}

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void hid_express_usb_mode_generate_kb_std_xy_reports(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result)
{
    tx_result &= 0x01;  // 2 candidates only. Ack or Nack

    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].kb_std2.report_id
                        , REPORT_ID_KB_STD_XY
                        , outgoing->kb_std[0] & LSB
                        , (outgoing->kb_std[0] >> 8) & LSB
                        , (outgoing->kb_std[0] >> 16) & LSB
                        );
    FAST_WORD_WRITE(   hid_common->outgoing_report[0].kb_std2.x
                        , (usb_vCtrl_x->predict_n[tx_result] & LSB)
                        , ((usb_vCtrl_x->predict_n[tx_result] >> 8) & LSB)
                        , (usb_vCtrl_y->predict_n[tx_result] & LSB)
                        , ((usb_vCtrl_y->predict_n[tx_result] >> 8) & LSB)
                        );
    #else
    FAST_WORD_WRITE(    outgoing_report[0].ccni_msg_id
                        , CCNI_MSG_USB
                        , REPORT_ID_KB_STD_XY
                        , outgoing->kb_std[0] & LSB
                        , (outgoing->kb_std[0] >> 8) & LSB
                        );
    FAST_WORD_WRITE(   outgoing_report[0].kb_std2.keycode[1]
                        , (outgoing->kb_std[0] >> 16) & LSB
                        , ((usb_vCtrl_x->predict_n[tx_result] >> 0) & LSB)
                        , ((usb_vCtrl_x->predict_n[tx_result] >> 8) & LNB) | ((usb_vCtrl_y->predict_n[tx_result] & LNB) << 4)
                        , ((usb_vCtrl_y->predict_n[tx_result] >> 4) & LSB)
                        );
    #endif
}

void hid_express_usb_mode_generate_kb_consumer_xy_reports(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result)
{
    tx_result &= 0x01;  // 2 candidates only. Ack or Nack

    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].kb_consumer1.report_id
                        , REPORT_ID_KB_CONSUMER_XY
                        , outgoing->kb_consumer & LSB
                        , (outgoing->kb_consumer >> 8) & LSB
                        , 0x00
                        );
    FAST_WORD_WRITE(    hid_common->outgoing_report[0].kb_consumer1.x
                        , (usb_vCtrl_x->predict_n[tx_result] & LSB)
                        , ((usb_vCtrl_x->predict_n[tx_result] >> 8) & LSB)
                        , (usb_vCtrl_y->predict_n[tx_result] & LSB)
                        , ((usb_vCtrl_y->predict_n[tx_result] >> 8) & LSB)
                        );
    #else
    FAST_WORD_WRITE(    outgoing_report[0].ccni_msg_id
                        , CCNI_MSG_USB
                        , REPORT_ID_KB_CONSUMER_XY
                        , outgoing->kb_consumer & LSB
                        , (outgoing->kb_consumer >> 8) & LSB
                        );
    FAST_WORD_WRITE(    outgoing_report[0].kb_consumer1.numeric_key_pad
                        , 0x00
                        , ((usb_vCtrl_x->predict_n[tx_result] >> 0) & LSB)
                        , ((usb_vCtrl_x->predict_n[tx_result] >> 8) & LNB) | ((usb_vCtrl_y->predict_n[tx_result] & LNB) << 4)
                        , ((usb_vCtrl_y->predict_n[tx_result] >> 4) & LSB)
                        );
    #endif
}

uint32_t hid_express_usb_last_report_is_kb()
{
    /* When last report send standard kb or consumer without xy data, need to merge */
    if((last_report_id == REPORT_ID_KB_STD) || (last_report_id == REPORT_ID_KB_CONSUMER))
    {
        return 1; // Nack
    }
    return 0;
}
#endif

int hid_express_usb_x_y_data_prepare(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result, uint32_t  tx_idx)
{
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    if(hid_express_usb_last_report_is_kb())
    {
        tx_result = 1;
    }
    #endif
    hid_express_generate_value_candidate( usb_vCtrl_x, tx_result, outgoing->x);
    hid_express_generate_value_candidate( usb_vCtrl_y, tx_result, outgoing->y);
    return 0;
}
#endif /* !defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) */

void hid_express_usb_delay_for_latency()
{
    //delay before key polling
    uint8_t delay_us = 0;
    uint8_t reduce_us = hid_common->hid.delay_for_key_polling_ms;
    if(reduce_us <= USB_KEY_DELAY_TIME) {
        delay_us = USB_KEY_DELAY_TIME - reduce_us;
    }

    if(delay_us){
        // DBG_PING_H(DBG_SIGNAL_DEBUG_3)
        hal_gpt_delay_us(delay_us);
        // DBG_PING_H(DBG_SIGNAL_DEBUG_3)
    }
    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    hid_common->hid.outgoing_report_ready = USB_REPORT_NONE;
    #endif
}

#if defined(AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
void hid_express_usb_wakeup_cm33_handler()
{
    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    hid_common->hid.outgoing_report_ready = USB_REPORT_NONE;
    // send a notification to wakeup CM33
    if(!hid_common->hid.outgoing_report_ready){
        hid_express_usb_mode_send_report_to_CM33((hal_ccni_message_t*)&(hid_common->outgoing_report[0]));
    }
    #endif
}
#endif

void hid_express_usb_data_set_report_ready(){
    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    hid_common->hid.outgoing_report_ready = USB_REPORT_SKIP;
    #endif
}

int hid_express_usb_data_send(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result, uint32_t tx_idx, bool report_go)
{
    uint32_t report_id = riscv_hid_report_id_select(outgoing);

    #if defined(AIR_PRODUCT_TYPE_MOUSE) && defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    if(hid_express_usb_last_report_is_kb())
    {
        tx_result = 1;
    }
    last_report_id = report_id;
    #endif

    switch (report_id)
    {
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        case REPORT_ID_GAME_CONTROLLER:
        case REPORT_ID_GAME_CONTROLLER_GROUP0:
        case REPORT_ID_GAME_CONTROLLER_GROUP1:
        case REPORT_ID_GAME_CONTROLLER_GROUP2:
            hid_express_usb_mode_generate_game_controller_reports(outgoing, tx_result);
            break;
    #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
    #if defined(AIR_PRODUCT_TYPE_MOUSE) && defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case REPORT_ID_KB_STD_XY:
            hid_express_usb_mode_generate_kb_std_xy_reports(outgoing, tx_result);
            break;
        case REPORT_ID_KB_CONSUMER_XY:
            hid_express_usb_mode_generate_kb_consumer_xy_reports(outgoing, tx_result);
            break;
    #endif
    #if defined(AIR_PRODUCT_TYPE_KEYBOARD) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case REPORT_ID_KB_CONSUMER:
            hid_express_usb_mode_generate_kb_consumer_reports(outgoing, tx_result);
            break;
    #endif /* defined(AIR_PRODUCT_TYPE_KEYBOARD) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case REPORT_ID_KB_STD:
            hid_express_usb_mode_generate_kb_std_reports(outgoing, tx_result);
            break;
    #endif /* defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */
    #if defined(AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case REPORT_ID_MOUSE:
            DBG_PING_H(DBG_SIGNAL_DEBUG_3);

            if(report_go){
                hid_express_usb_mode_generate_12bits_reports(outgoing, tx_result);
            }
            DBG_PING_L(DBG_SIGNAL_DEBUG_3);
            break;
    #endif
        default:
            return 0;
    }

    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    hid_common->hid.outgoing_report_ready = USB_REPORT_COMPLETE;
    #else
    // send a notification to CM33
    hid_express_usb_mode_send_report_to_CM33((hal_ccni_message_t*)&outgoing_report[0]);
    #endif /* AIR_USB_CCNI_WAKEUP_CM33 */


    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    #if defined(AIR_REPORT_DATA_LOG)
    #if defined(USB_REPORT_LOG_SN)
    dbg_sn_num++;
    if (dbg_sn_num >= 0x80 ){
        dbg_sn_num = 1;
    }
    if (tx_result){
        dbg_sn_num |= 0x80;
    }

    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    hid_common->outgoing_report[0].ms_s16_z8.ac_pan = dbg_sn_num;
    #else
    outgoing_report[0].ms_s16_z8.ac_pan = dbg_sn_num;
    #endif /* _AIR_USB_CCNI_WAKEUP_CM33_ */
    #endif /* _USB_REPORT_LOG_SN_ */

    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    hid_express_copy_report_for_debug_print((uint8_t*)&hid_common->outgoing_report[0].ms_s16_z8.report_id  , (uint8_t*)&hid_common->outgoing_report[0].ms_s16_z8.report_id);
    #else
    hid_express_copy_report_for_debug_print((uint8_t*)&outgoing_report[0].ms_s16_z8.report_id  , (uint8_t*)&outgoing_report[0].ms_s16_z8.report_id);
    #endif /* _AIR_USB_CCNI_WAKEUP_CM33_ */
    #endif /* _AIR_REPORT_DATA_LOG_ */
    #endif /* _AIR_PRODUCT_TYPE_MOUSE */
    return 0;
}

void hid_express_usb_mode_init()
{
    #if defined(AIR_USB_CCNI_WAKEUP_CM33)
    hid_common->hid.outgoing_report_ready = USB_REPORT_NONE;
    #endif

    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    hid_express_x_y_buf_init(&usb_vCtrl_x, &usb_vCtrl_y);
    #endif /* defined(AIR_PRODUCT_TYPE_MOUSE) */

    #if defined(AIR_REPORT_DATA_LOG)
    memset((uint8_t*)&report_log, 0, sizeof(report_log));
    #endif
}