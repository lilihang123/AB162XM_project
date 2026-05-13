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
#include "riscv_hid_express_2_4G_mode.h"
#include "pka_share.h"
#include "pka.h"
#include <stdint.h>
#include "riscv_hid_express_xy_queue.h"
#include "riscv_hid_express_key_queue_mouse.h"
#include "riscv_hid_report_id_selector.h"
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "hid_common.h"
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

#if defined(AIR_EXCEPTION_HANDLER_ENABLE)
#include "exception_handler.h"
#else
#define light_assert(EXPR, FILE, LINE)
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
#define CONTROLLER_HEADER_BYTES 4 // temp value



#define TX0_NAK_NAK 0
#define TX0_NAK_ACK 1
#define TX0_ACK_NAK 2
#define TX0_ACK_ACK 3
#define TX1 4

#define TX_STATUS_LOG    0

/* Private macro -------------------------------------------------------------*/

#define IDX_0 0


/* Private variables ---------------------------------------------------------*/
extern uint32_t last_tx_result;
extern uint32_t hid_flags;
extern uint32_t rr_idx_2_4g;
extern uint8_t report_rate_pka;

uint32_t sn_num = 0;
typedef union {
    #if defined(AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    T_HID_MOUSE_2_4G_REPORT_K8_S16_Z8        ms_s16_z8;
    #endif /* AIR_PRODUCT_TYPE_MOUSE*/
    #if defined(AIR_PRODUCT_TYPE_KEYBOARD) && defined(AIR_KEYBOARD_M607)
    T_HID_MOUSE_2_4G_REPORT_K8_S16_Z8        ms_s16_z8;
    #endif /* AIR_PRODUCT_TYPE_KEYBOARD && AIR_KEYBOARD_M607*/
    #if defined(AIR_PRODUCT_TYPE_KEYBOARD) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    T_HID_2_4G_REPORT_KB_CONSUMER2_S         kb_consumer2;
    #endif /* (AIR_PRODUCT_TYPE_KEYBOARD) || (AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */
    #if defined (AIR_PRODUCT_TYPE_MOUSE) && defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    T_HID_2_4G_REPORT_KB_STD2_XY_S           kb_std2;
    T_HID_2_4G_REPORT_KB_CONSUMER1_XY_S      kb_consumer1;
    #endif /* AIR_PRODUCT_TYPE_MOUSE && AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    T_HID_2_4G_REPORT_KB_STD5_S              kb_std5;
    #endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
    #if !defined (AIR_PRODUCT_TYPE_MOUSE)
    T_HID_MOUSE_2_4G_REPORT_K8_S16_Z8_17B    ms_s16_z8_17b;
    T_HID_2_4G_REPORT_KB_STD5_17B_S          kb_std5_17b;
    T_HID_2_4G_REPORT_KB_CONSUMER2_17B_S     kb_consumer2_17b;
    #endif /* !AIR_PRODUCT_TYPE_MOUSE */
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    T_HID_REPORT_GAME_CONTROLLER_PAYLOAD_0_S gc_payload_0;
    T_HID_REPORT_GAME_CONTROLLER_PAYLOAD_1_S gc_payload_1;
    T_HID_REPORT_GAME_CONTROLLER_PAYLOAD_ALL_IN_ONE_S gc_payload_all_in_one;
    #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
    #if defined(AIR_PRODUCT_TYPE_KEYBOARD)
    T_HID_REPORT_KB_COMBO_N7_S              kb_payload_0;
    T_HID_REPORT_KB_N8_S                    kb_payload_1;
    // T_HID_REPORT_KB_CONSUMER2_S             kb_payload_csm;
    T_HID_REPORT_KB_NKEY_16_S               kb_payload;
    #endif /* AIR_PRODUCT_TYPE_KEYBOARD */
} __attribute__((__packed__)) U_CCNI_REPORT;

#if defined(AIR_PRODUCT_TYPE_MOUSE)
T_ASSEMBLE_VAL_CTRL_S *g_vCtrl_x;
T_ASSEMBLE_VAL_CTRL_S *g_vCtrl_y;
#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
static uint32_t last_xy_over_12bits = false;
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP  */
#endif /* defined(AIR_PRODUCT_TYPE_MOUSE) */

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
static uint32_t last_report_id = REPORT_ID_MOUSE;
#endif /* AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP  */

#define RELIABLE_PAYLOAD_OFFSET 20
uint8_t* reliable_tx_ptr = NULL;
uint8_t* reliable_tx_ptr_previous = NULL;
extern uint8_t *pka_tx_ptr;
// uint8_t payload_offset;
static U_CCNI_REPORT outgoing_report;

/* Public variables ----------------------------------------------------------*/
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
extern uint32_t lt_digital;
extern uint32_t rt_digital;
#endif
/* Private functions ---------------------------------------------------------*/
__attribute__ ((optimize("O3")))  int hid_express_gaming_get_tx_status()
{
    reliable_tx_ptr = pka_share_get_hid_tx_ptr();

    if(reliable_tx_ptr == NULL) {
        return 1; /* NACK */
    }
    return 0;
}

#if defined(AIR_PRODUCT_TYPE_MOUSE)

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
__attribute__ ((optimize("O3"))) void hid_express_gaming_axis_data_update(int32_t *axis12, int32_t raw, void *ctrl)
{
    int32_t overflow = 0;
    if (raw > MAX_12BIT) {
        overflow = raw - MAX_12BIT;
        raw = MAX_12BIT;
        hid_express_generate_value_candidate_1R1T_concurrent(ctrl, 1, -MAX_12BIT);
    }
    else if (raw < MIN_12BIT) {
        overflow = raw - MIN_12BIT;
        raw = MIN_12BIT;
        hid_express_generate_value_candidate_1R1T_concurrent(ctrl, 1, -MIN_12BIT);
    }

    *axis12 = raw;

    if(overflow)
    {
        last_xy_over_12bits = true;
    }
}
#endif

__attribute__ ((optimize("O3")))  void hid_express_gaming_buffer_full_update_report()
{
    uint8_t report_id_of_submitted_report = (outgoing_report.ms_s16_z8.report_id & REPORT_ID_VALID_BITS);

    switch (report_id_of_submitted_report)
    {
        case REPORT_ID_MOUSE_16BIT:
        {
            #if defined(AIR_MOUSE_9B_DATA)
            FAST_WORD_WRITE(outgoing_report.ms_s16_z8.dummy_2,
                TX_STATUS_LOG,
                outgoing_report.ms_s16_z8.wheel_key,
                g_vCtrl_x->predict_n[IDX_0] & LSB,
                (g_vCtrl_x->predict_n[IDX_0] >> 8) & LSB
            );

            FAST_WORD_WRITE(outgoing_report.ms_s16_z8.y,
                g_vCtrl_y->predict_n[IDX_0] & LSB,
                (g_vCtrl_y->predict_n[IDX_0] >> 8) & LSB,
                ATTACHE_SN_AT(sn_num),
                TX_STATUS_LOG
            );
            outgoing_report.ms_s16_z8.report_id = outgoing_report.ms_s16_z8.report_id | MERGE_X_Y_NOTIFICATION;
            #else
            FAST_WORD_WRITE(outgoing_report.ms_s16_z8.ac_pan,
                ATTACHE_SN_AT(sn_num),
                outgoing_report.ms_s16_z8.wheel_key,
                g_vCtrl_x->predict_n[IDX_0] & LSB,
                (g_vCtrl_x->predict_n[IDX_0] >> 8) & LSB
            );

            FAST_WORD_WRITE(outgoing_report.ms_s16_z8.y,
                g_vCtrl_y->predict_n[IDX_0] & LSB,
                (g_vCtrl_y->predict_n[IDX_0] >> 8) & LSB,
                outgoing_report.ms_s16_z8.report_id | MERGE_X_Y_NOTIFICATION,
                TX_STATUS_LOG
            );
            #endif /* AIR_MOUSE_9B_DATA */
        }
        break;

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case REPORT_ID_KB_STD_XY:
        case REPORT_ID_KB_CONSUMER_XY:
        {
            if(!last_xy_over_12bits)
            {
                int32_t x12 = 0, y12 = 0;
                hid_express_gaming_axis_data_update(&x12, g_vCtrl_x->predict_n[IDX_0], g_vCtrl_x);
                hid_express_gaming_axis_data_update(&y12, g_vCtrl_y->predict_n[IDX_0], g_vCtrl_y);
                /* Update standard key or consumer key x_y data */
                #if defined(AIR_MOUSE_9B_DATA)
                FAST_WORD_WRITE(outgoing_report.kb_std2.dummy_2,
                    ATTACHE_SN_AT(sn_num),
                    outgoing_report.kb_std2.combo,
                    outgoing_report.kb_std2.keycode[0],
                    outgoing_report.kb_std2.keycode[1]
                );

                FAST_WORD_WRITE(outgoing_report.kb_std2.x_y[0],
                    (g_vCtrl_x->predict_n[IDX_0] >> 0) & LSB,
                    ((g_vCtrl_x->predict_n[IDX_0] >> 8) & LNB) | ((g_vCtrl_y->predict_n[IDX_0] & LNB) << 4),
                    (g_vCtrl_y->predict_n[IDX_0] >> 4) & LSB,
                    0x00
                );
                outgoing_report.kb_std2.report_id = outgoing_report.kb_std2.report_id | MERGE_X_Y_NOTIFICATION;
                #else
                FAST_WORD_WRITE(outgoing_report.kb_std2.last_x_y,
                    (g_vCtrl_y->predict_n[IDX_0] >> 4) & LSB,
                    outgoing_report.kb_std2.combo,
                    outgoing_report.kb_std2.keycode[0],
                    outgoing_report.kb_std2.keycode[1]
                );

                FAST_WORD_WRITE(outgoing_report.kb_std2.x_y[0],
                    (g_vCtrl_x->predict_n[IDX_0] >> 0) & LSB,
                    ((g_vCtrl_x->predict_n[IDX_0] >> 8) & LNB) | ((g_vCtrl_y->predict_n[IDX_0] & LNB) << 4),
                    outgoing_report.kb_std2.report_id | MERGE_X_Y_NOTIFICATION,
                    ATTACHE_SN_AT(sn_num)
                );
                #endif /* AIR_MOUSE_9B_DATA */
            }
        }
        break;
        #endif

        #if defined(AIR_ACL_PACKET_VIA_HID_REPORT)
        case REPORT_ID_MS_ACL_PACKET_CUST_PROTOCOL:
        {
            #if defined(AIR_MOUSE_9B_DATA)
            FAST_WORD_WRITE(*((uint8_t*)&outgoing_report+4),
                (g_vCtrl_x->predict_n[IDX_0]),
                (g_vCtrl_y->predict_n[IDX_0]),
                0x00,
                TX_STATUS_LOG
            );
            outgoing_report.ms_s16_z8.report_id = outgoing_report.ms_s16_z8.report_id | MERGE_X_Y_NOTIFICATION;
            #else
            FAST_WORD_WRITE(*((uint8_t*)&outgoing_report+4),
                (g_vCtrl_x->predict_n[IDX_0]),
                (g_vCtrl_y->predict_n[IDX_0]),
                outgoing_report.ms_s16_z8.report_id | MERGE_X_Y_NOTIFICATION,
                TX_STATUS_LOG
            );
            #endif /* AIR_MOUSE_9B_DATA */
        }
        break;
        #endif

        default:
        break;

    }
}

__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_reports_1R1T_12bits(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;

        /** Prepare report for reliable buffer */
        #if defined(AIR_MOUSE_9B_DATA)
        FAST_WORD_WRITE(outgoing_report.ms_s16_z8.dummy_2,
            TX_STATUS_LOG, /* Byte 8 */
            (LAST_3_BITS(outgoing->z1) << 5) | (outgoing->k & LSB),
            g_vCtrl_x->predict_n[IDX_0] & LSB,
            (g_vCtrl_x->predict_n[IDX_0] >> 8) & LSB
        );

        FAST_WORD_WRITE(outgoing_report.ms_s16_z8.y,
            g_vCtrl_y->predict_n[IDX_0] & LSB,
            (g_vCtrl_y->predict_n[IDX_0] >> 8) & LSB,
            ATTACHE_SN_AT(sn_num),
            0x00 /* Byte 7 */
        );
        outgoing_report.ms_s16_z8.report_id = REPORT_ID_MOUSE_16BIT;
        #else
        FAST_WORD_WRITE(outgoing_report.ms_s16_z8.ac_pan,
            ATTACHE_SN_AT(sn_num),
            (LAST_3_BITS(outgoing->z1) << 5) | (outgoing->k & LSB),
            g_vCtrl_x->predict_n[IDX_0] & LSB,
            (g_vCtrl_x->predict_n[IDX_0] >> 8) & LSB
        );

        FAST_WORD_WRITE(outgoing_report.ms_s16_z8.y,
            g_vCtrl_y->predict_n[IDX_0] & LSB,
            (g_vCtrl_y->predict_n[IDX_0] >> 8) & LSB,
            REPORT_ID_MOUSE_16BIT,
            TX_STATUS_LOG
        );
        #endif /* AIR_MOUSE_9B_DATA */
    }
    else
    {
        /** Update report for previous reliable buffer */
        hid_express_gaming_buffer_full_update_report();
    }
}

#if defined(AIR_ACL_PACKET_VIA_HID_REPORT)
__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_acl_response_reports(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        /** Prepare report for reliable buffer */
        *(uint32_t*)&outgoing_report = outgoing->acl_packet_data;

        #if defined(AIR_MOUSE_9B_DATA)
        FAST_WORD_WRITE(*((uint8_t*)&outgoing_report+4),
            (g_vCtrl_x->predict_n[IDX_0]),
            (g_vCtrl_y->predict_n[IDX_0]),
            0x00,
            TX_STATUS_LOG
        );
        outgoing_report.ms_s16_z8.report_id = outgoing->type;
        #else
        FAST_WORD_WRITE(*((uint8_t*)&outgoing_report+4),
            (g_vCtrl_x->predict_n[IDX_0]),
            (g_vCtrl_y->predict_n[IDX_0]),
            outgoing->type,
            TX_STATUS_LOG
        );
        #endif
    }
    else
    {
        /** Update report for previous reliable buffer */
        hid_express_gaming_buffer_full_update_report();
    }
}
#endif

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_kb_std_xy_reports_1R1T(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;
        int32_t x12 = 0, y12 = 0;
        last_xy_over_12bits = false;
        hid_express_gaming_axis_data_update(&x12, g_vCtrl_x->predict_n[IDX_0], g_vCtrl_x);
        hid_express_gaming_axis_data_update(&y12, g_vCtrl_y->predict_n[IDX_0], g_vCtrl_y);

        /** Prepare report for reliable buffer */
        #if defined(AIR_MOUSE_9B_DATA)
        FAST_WORD_WRITE(outgoing_report.kb_std2.dummy_2,
            ATTACHE_SN_AT(sn_num),
            outgoing->kb_std[0] & LSB,
            (outgoing->kb_std[0] >> 8) & LSB,
            (outgoing->kb_std[0] >> 16) & LSB
        );

        FAST_WORD_WRITE(outgoing_report.kb_std2.x_y[0],
            x12 & LSB,
            (((x12 >> 8) & LNB) | (y12 & LNB) << 4),
            (y12 >> 4) & LSB,
            0x00
        );
        outgoing_report.kb_std2.report_id = REPORT_ID_KB_STD_XY;
        #else
        FAST_WORD_WRITE(outgoing_report.kb_std2.last_x_y,
            (y12 >> 4) & LSB,
            outgoing->kb_std[0] & LSB,
            (outgoing->kb_std[0] >> 8) & LSB,
            (outgoing->kb_std[0] >> 16) & LSB
        );

        FAST_WORD_WRITE(outgoing_report.kb_std2.x_y[0],
            x12 & LSB,
            (((x12 >> 8) & LNB) | (y12 & LNB) << 4),
            REPORT_ID_KB_STD_XY,
            ATTACHE_SN_AT(sn_num)
        );
        #endif /* AIR_MOUSE_9B_DATA */
    }
    else
    {
        /** Update report for previous reliable buffer */
        hid_express_gaming_buffer_full_update_report();
    }
}

__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_kb_consumer_xy_reports_1R1T(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;
        int32_t x12 = 0, y12 = 0;
        last_xy_over_12bits = false;
        hid_express_gaming_axis_data_update(&x12, g_vCtrl_x->predict_n[IDX_0], g_vCtrl_x);
        hid_express_gaming_axis_data_update(&y12, g_vCtrl_y->predict_n[IDX_0], g_vCtrl_y);
        /** Prepare report for reliable buffer */
        #if defined(AIR_MOUSE_9B_DATA)
        FAST_WORD_WRITE(outgoing_report.kb_consumer1.dummy_2,
            ATTACHE_SN_AT(sn_num),
            outgoing->kb_consumer & LSB,
            (outgoing->kb_consumer >> 8) & LSB,
            0x00
        );

        FAST_WORD_WRITE(outgoing_report.kb_consumer1.x_y[0],
            (x12 >> 0) & LSB,
            ((x12 >> 8) & LNB) | ((y12 & LNB) << 4),
            (y12 >> 4) & LSB,
            0x00
        );
        outgoing_report.kb_consumer1.report_id = REPORT_ID_KB_CONSUMER_XY;
        #else
        FAST_WORD_WRITE(outgoing_report.kb_consumer1.last_x_y,
            (y12 >> 4) & LSB,
            outgoing->kb_consumer & LSB,
            (outgoing->kb_consumer >> 8) & LSB,
            0x00
        );

        FAST_WORD_WRITE(outgoing_report.kb_consumer1.x_y[0],
            (x12 >> 0) & LSB,
            ((x12 >> 8) & LNB) | ((y12 & LNB) << 4),
            REPORT_ID_KB_CONSUMER_XY,
            ATTACHE_SN_AT(sn_num)
        );
        #endif /* AIR_MOUSE_9B_DATA */
    }
    else
    {
        /** Update report for previous reliable buffer */
        hid_express_gaming_buffer_full_update_report();
    }
}
#endif

int hid_express_2_4G_x_y_data_prepare(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result, uint32_t  tx_idx, uint32_t dongle_scenario)
{
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    if((last_report_id == REPORT_ID_KB_STD) || (last_report_id == REPORT_ID_KB_CONSUMER) || last_xy_over_12bits)
    {
        tx_result = 1;
    }
    #endif
    hid_express_generate_value_candidate_1R1T_concurrent( g_vCtrl_x, tx_result, outgoing->x);
    hid_express_generate_value_candidate_1R1T_concurrent( g_vCtrl_y, tx_result, outgoing->y);

    return 0;
}
#endif /* defined(AIR_PRODUCT_TYPE_MOUSE) */

__attribute__ ((optimize("O3"))) void hid_express_gaming_submit_report_to_pka()
{
#if defined(AIR_PRODUCT_TYPE_KEYBOARD)
    uint8_t *ptr = (reliable_tx_ptr != NULL) ? (reliable_tx_ptr) : (reliable_tx_ptr_previous);
    uint8_t report_rate = pka_share_get_current_report_rate();
    switch (report_rate){
        case HID_REPORT_RATE_125_HZ:
        case HID_REPORT_RATE_250_HZ:
        case HID_REPORT_RATE_500_HZ:
        case HID_REPORT_RATE_1K_HZ:
        case HID_REPORT_RATE_2K_HZ:
        case HID_REPORT_RATE_4K_HZ:
/* NOTE:
 * controller RR & app RR not sync
 * switch the data length may cause disconnection  */
            // 17 bytes when 2.4G connection and RR lower than 8K
            *((uint32_t *)(ptr + RELIABLE_PAYLOAD_OFFSET) + 0) = *((uint32_t *)&outgoing_report + 0);
            *((uint32_t *)(ptr + RELIABLE_PAYLOAD_OFFSET) + 1) = *((uint32_t *)&outgoing_report + 1);
            *((uint32_t *)(ptr + RELIABLE_PAYLOAD_OFFSET) + 2) = *((uint32_t *)&outgoing_report + 2);
            *((uint32_t *)(ptr + RELIABLE_PAYLOAD_OFFSET) + 3) = *((uint32_t *)&outgoing_report + 3);
            *((uint8_t *)(ptr + RELIABLE_PAYLOAD_OFFSET) + 16) = *((uint8_t *)&outgoing_report + 16);
            *((uint16_t *)(ptr + pka_share_get_tx_datalen_offset())) = 17;
            *((uint16_t *)(ptr + pka_share_get_tx_pdulen_offset())) = 17;
            // light_assert("RR ERROR", __FILE__, __LINE__);
            break;
        case HID_REPORT_RATE_8K_HZ:
            // 9 bytes when 2.4G connection and 8K RR
            *((uint32_t *)(ptr + RELIABLE_PAYLOAD_OFFSET) + 0) = *((uint32_t *)&outgoing_report + 0);
            *((uint32_t *)(ptr + RELIABLE_PAYLOAD_OFFSET) + 1) = *((uint32_t *)&outgoing_report + 1);
            *((uint8_t *)(ptr + RELIABLE_PAYLOAD_OFFSET) + 8) = *((uint8_t *)&outgoing_report + 8);
            *((uint16_t *)(ptr + pka_share_get_tx_datalen_offset())) = 9;
            *((uint16_t *)(ptr + pka_share_get_tx_pdulen_offset())) = 9;
            break;
        default:
            // light_assert("NOT Expected RR", __FILE__, __LINE__);
            break;
    }
#elif defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    //DBG_PING_H(DBG_SIGNAL_DEBUG_1);
    
    #if !defined (AIR_HID_DUMMY_REPORT_RATE)
    if (report_rate_pka == HID_REPORT_RATE_8K_HZ)
    #endif /* not AIR_HID_DUMMY_REPORT_RATE */
    {
        *((uint32_t *)(pka_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 0) = *((uint32_t *)&outgoing_report + 0);
        *((uint32_t *)(pka_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 1) = *((uint32_t *)&outgoing_report + 1);
        *((uint8_t *)(pka_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 8) = *((uint8_t *)&outgoing_report + 8);
    }
    #if !defined (AIR_HID_DUMMY_REPORT_RATE)
    else
    {
        *((uint32_t *)(pka_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 0) = *((uint32_t *)&outgoing_report + 0);
        *((uint32_t *)(pka_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 1) = *((uint32_t *)&outgoing_report + 1);
        *((uint32_t *)(pka_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 2) = *((uint32_t *)&outgoing_report + 2);
        *((uint32_t *)(pka_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 3) = *((uint32_t *)&outgoing_report + 3);
        *((uint8_t *)(pka_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 16) = *((uint8_t *)&outgoing_report + 16);
    }
    #endif /* not AIR_HID_DUMMY_REPORT_RATE */
#else
    //DBG_PING_H(DBG_SIGNAL_DEBUG_1);
    if(reliable_tx_ptr != NULL)
    {
        *((uint32_t *)(reliable_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 0) = *((uint32_t *)&outgoing_report + 0);
        *((uint32_t *)(reliable_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 1) = *((uint32_t *)&outgoing_report + 1);
        #if defined(AIR_GAME_CONTROLLER_9B_DATA) || defined(AIR_MOUSE_9B_DATA)
        *((uint8_t *)(reliable_tx_ptr + RELIABLE_PAYLOAD_OFFSET) + 8) = *((uint8_t *)&outgoing_report + 8);
        *((uint16_t *)(reliable_tx_ptr + pka_share_get_tx_datalen_offset())) = 9;
        *((uint16_t *)(reliable_tx_ptr + pka_share_get_tx_pdulen_offset())) = 9;
        #else
//        *((uint16_t *)(reliable_tx_ptr + pka_share_get_tx_datalen_offset())) = 7;
//        *((uint16_t *)(reliable_tx_ptr + pka_share_get_tx_pdulen_offset())) = 7;
        #endif
    }
    else
    {
        *((uint32_t *)(reliable_tx_ptr_previous + RELIABLE_PAYLOAD_OFFSET) + 0) = *((uint32_t *)&outgoing_report + 0);
        *((uint32_t *)(reliable_tx_ptr_previous + RELIABLE_PAYLOAD_OFFSET) + 1) = *((uint32_t *)&outgoing_report + 1);
        #if defined(AIR_GAME_CONTROLLER_9B_DATA) || defined(AIR_MOUSE_9B_DATA)
        *((uint8_t *)(reliable_tx_ptr_previous + RELIABLE_PAYLOAD_OFFSET) + 8) = *((uint8_t *)&outgoing_report + 8);
        *((uint16_t *)(reliable_tx_ptr_previous + pka_share_get_tx_datalen_offset())) = 9;
        *((uint16_t *)(reliable_tx_ptr_previous + pka_share_get_tx_pdulen_offset())) = 9;
        #else
//        *((uint16_t *)(reliable_tx_ptr_previous + pka_share_get_tx_datalen_offset())) = 7;
//        *((uint16_t *)(reliable_tx_ptr_previous + pka_share_get_tx_pdulen_offset())) = 7;
        #endif
    }
#endif
}

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_reports_game_controller(T_OUTGOING_VALUES_S* outgoing)
{
    static uint32_t game_controller_tx_idx = 0;
    #if defined(AIR_GAME_CONTROLLER_12BIT_ADC)
    int32_t x,y,z,rz;
    #endif
    if(reliable_tx_ptr != NULL)
    {
        #if !defined (AIR_HID_DUMMY_REPORT_RATE)
        if (report_rate_pka == HID_REPORT_RATE_8K_HZ)
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
        {
            /* 8K case, there are at most 9B data on Air */
            if (outgoing->type != REPORT_ID_GAME_CONTROLLER && game_controller_tx_idx == 0){
                game_controller_tx_idx++;
            }
            if (game_controller_tx_idx == 0)
            {
                // DBG_PING_H(42);
                /* only report joystick */
                #if defined(AIR_GAME_CONTROLLER_12BIT_ADC)
                x  = (((int32_t)(outgoing->x))-0x8000)>>4;
                y  = (((int32_t)(outgoing->y))-0x8000)>>4;
                z  = (((int32_t)(outgoing->z))-0x8000)>>4;
                rz = (((int32_t)(outgoing->rz))-0x8000)>>4;
                // outgoing_report.gc_payload_0.x_y_z_rz[0] = x&0xff;
                // outgoing_report.gc_payload_0.x_y_z_rz[1] = ((y&0x0f)<<4) | ((x>>8)&0xf);
                // outgoing_report.gc_payload_0.x_y_z_rz[2] = (y>>4)&0xff;
                // outgoing_report.gc_payload_0.x_y_z_rz[3] = z&0xff;
                // outgoing_report.gc_payload_0.x_y_z_rz[4] = ((rz&0x0f)<<4) | ((z>>8)&0xf);
                // outgoing_report.gc_payload_0.x_y_z_rz[5] = (rz>>4)&0xff;
                FAST_WORD_WRITE(outgoing_report.gc_payload_0.x_y_z_rz[0],
                    x&0xff,
                    ((y&0x0f)<<4) | ((x>>8)&0xf),
                    (y>>4)&0xff,
                    z&0xff
                );

                #if defined(AIR_GAME_CONTROLLER_9B_DATA)
                FAST_WORD_WRITE(outgoing_report.gc_payload_0.x_y_z_rz[4],
                    ((rz&0x0f)<<4) | ((z>>8)&0xf),
                    (rz>>4)&0xff,
                    outgoing->last_key_air_byte & 0x000000ff,
                    outgoing_report.gc_payload_0.button2 = (outgoing->last_key_air_byte & 0x0000ff00)>>8
                );
                #else
                outgoing_report.gc_payload_0.x_y_z_rz[4] = ((rz&0x0f)<<4) | ((z>>8)&0xf);
                outgoing_report.gc_payload_0.x_y_z_rz[5] = (rz>>4)&0xff;
                #endif/* CONFIG_AIR_GAME_CONTROLLER_9B_DATA */
                #else
                // outgoing_report.gc_payload_0.x  = (uint16_t)(outgoing->x) - 0x8000;
                // outgoing_report.gc_payload_0.y  = (uint16_t)(outgoing->y) - 0x8000;
                // outgoing_report.gc_payload_0.z  = (uint16_t)(outgoing->z) - 0x8000;
                // outgoing_report.gc_payload_0.rz = (uint16_t)(outgoing->rz) - 0x8000;
                FAST_WORD_WRITE_BY_TWO_HALF(outgoing_report.gc_payload_0.x,
                    (uint16_t)(outgoing->x) - 0x8000,
                    (uint16_t)(outgoing->y) - 0x8000
                );
                FAST_WORD_WRITE_BY_TWO_HALF(outgoing_report.gc_payload_0.x,
                    (uint16_t)(outgoing->z) - 0x8000,
                    (uint16_t)(outgoing->rz) - 0x8000
                );
                #endif/* CONFIG_AIR_GAME_CONTROLLER_12BIT_ADC */
                outgoing->last_x  = outgoing->x;
                outgoing->last_y  = outgoing->y;
                outgoing->last_z  = outgoing->z;
                outgoing->last_rz = outgoing->rz;
                outgoing_report.gc_payload_0.report_id = REPORT_ID_GAME_CONTROLLER;
                // DBG_PING_L(42);
            }
            else
            {
                // DBG_PING_H(40);
                uint8_t temp_button = 0;
                if (outgoing->type == REPORT_ID_GAME_CONTROLLER)
                {
                    outgoing->type = REPORT_ID_GAME_CONTROLLER_GROUP0;
                    temp_button = (outgoing->last_key_air_byte & 0x000000ff);
                }
                else if (outgoing->type == REPORT_ID_GAME_CONTROLLER_GROUP0)
                {
                    outgoing->last_key_air_byte = ((outgoing->last_key_air_byte & 0x0000ff00) | (outgoing->key_air_byte));
                    temp_button = outgoing->key_air_byte;
                }
                else if (outgoing->type == REPORT_ID_GAME_CONTROLLER_GROUP1)
                {
                    outgoing->last_key_air_byte = ((outgoing->last_key_air_byte & 0x000000ff) | (outgoing->key_air_byte << 8));
                    temp_button = outgoing->key_air_byte;
                }
                if (lt_digital){
                    outgoing->lt = (outgoing->lt_rt_digital & 0x1) ? 1023 : 0;
                }
                if (rt_digital){
                    outgoing->rt = (outgoing->lt_rt_digital & 0x2) ? 1023 : 0;
                }
                /* button + hat switch + triggers + joystick diff */
                // outgoing_report.gc_payload_1.hat_switch_and_trigger[0] = ((outgoing->lt&0xf)<<4) | (outgoing->hat_switch_byte&0xf);
                // outgoing_report.gc_payload_1.hat_switch_and_trigger[1] = ((outgoing->rt&0x3)<<6) | ((outgoing->lt>>4)&0x3f);
                // outgoing_report.gc_payload_1.hat_switch_and_trigger[2] = outgoing->rt>>2;
                FAST_WORD_WRITE(outgoing_report.gc_payload_1.button,
                    temp_button,
                    ((outgoing->lt&0xf)<<4) | (outgoing->hat_switch_byte&0xf),
                    ((outgoing->rt&0x3)<<6) | ((outgoing->lt>>4)&0x3f),
                    outgoing->rt>>2
                );
                #if defined(AIR_GAME_CONTROLLER_9B_DATA)
                x  = (int32_t)outgoing->x - (int32_t)outgoing->last_x;
                x  = x >> 4;
                if (x < -128)
                {
                    x = -128;
                }
                else if (x > 127)
                {
                    x = 127;
                }
                y  = (int32_t)outgoing->y - (int32_t)outgoing->last_y;
                y  = y >> 4;
                if (y < -128)
                {
                    y = -128;
                }
                else if (y > 127)
                {
                    y = 127;
                }
                z  = (int32_t)outgoing->z - (int32_t)outgoing->last_z;
                z  = z >> 4;
                if (z < -128)
                {
                    z = -128;
                }
                else if (z > 127)
                {
                    z = 127;
                }
                rz = (int32_t)outgoing->rz - (int32_t)outgoing->last_rz;
                rz  = rz >> 4;
                rz  = rz < -128 ? -128 : (rz > 127 ? 127 : rz);

                // outgoing_report.gc_payload_1.diff_x  = (uint8_t)x;
                // outgoing_report.gc_payload_1.diff_y  = (uint8_t)y;
                // outgoing_report.gc_payload_1.diff_z  = (uint8_t)z;
                // outgoing_report.gc_payload_1.diff_rz = (uint8_t)rz;
                FAST_WORD_WRITE(outgoing_report.gc_payload_1.diff_x,
                    (uint8_t)x,
                    (uint8_t)y,
                    (uint8_t)z,
                    (uint8_t)rz
                );
                #else
                outgoing_report.gc_payload_1.diff_x_y_z_rz[0] = (((outgoing->y - outgoing->last_y)&0xf)<<4) | ((outgoing->x - outgoing->last_x)&0xf);
                outgoing_report.gc_payload_1.diff_x_y_z_rz[1] = (((outgoing->rz - outgoing->last_rz)&0xf)<<4) | ((outgoing->z - outgoing->last_z)&0xf);
                #endif
                outgoing->last_x  += x;
                outgoing->last_y  += y;
                outgoing->last_z  += z;
                outgoing->last_rz += rz;
                outgoing->last_lt = outgoing->lt;
                outgoing->last_rt = outgoing->rt;
                outgoing_report.gc_payload_1.report_id = outgoing->type;
                // DBG_PING_L(40);
            }

            game_controller_tx_idx++;
            if (game_controller_tx_idx >= 8)
            {
                game_controller_tx_idx = 0;
            }
        }
        #if !defined (AIR_HID_DUMMY_REPORT_RATE)
        else
        {
            /* not 8K case, there are at most 17B data on Air  */
            if (lt_is_digital()){
                outgoing->lt = (outgoing->lt_rt_digital & 0x1) ? 1023 : 0;
            }
            if (rt_is_digital()){
                outgoing->rt = (outgoing->lt_rt_digital & 0x2) ? 1023 : 0;
            }
            outgoing_report.gc_payload_all_in_one.x  = outgoing->x;
            outgoing_report.gc_payload_all_in_one.y  = outgoing->y;
            outgoing_report.gc_payload_all_in_one.z  = outgoing->z;
            outgoing_report.gc_payload_all_in_one.rz = outgoing->rz;
            outgoing_report.gc_payload_all_in_one.breake = outgoing->lt;
            outgoing_report.gc_payload_all_in_one.accelerator = outgoing->rt;
            outgoing_report.gc_payload_all_in_one.hat_switch = outgoing->hat_switch_byte;
            outgoing_report.gc_payload_all_in_one.button = outgoing->key_air_byte;
            outgoing_report.gc_payload_all_in_one.report_id = REPORT_ID_GAME_CONTROLLER_ALL_IN_ONE;
            outgoing->last_x  = outgoing->x;
            outgoing->last_y  = outgoing->y;
            outgoing->last_z  = outgoing->z;
            outgoing->last_rz = outgoing->rz;
            outgoing->last_lt = outgoing->lt;
            outgoing->last_rt = outgoing->rt;
        }
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
    }
    else
    {
        // DBG_PING_H(38);
        // DBG_PING_L(38);
    }
}
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

#if defined(AIR_PRODUCT_TYPE_KEYBOARD)
__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_reports_keyboard_combo(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;
        DBG_PING_H(DBG_SIGNAL_DEBUG_1);
        /** Prepare report for reliable buffer */

        switch (rr_idx_2_4g){
            case HID_REPORT_RATE_8K_HZ:
                // 9 bytes when 2.4G connection and 8K RR
                *((uint32_t*)(&outgoing_report.kb_payload_0.combo)) = outgoing->kb_nkey_map[0];
                *((uint32_t*)(&outgoing_report.kb_payload_0.nkey[3])) = outgoing->kb_nkey_map[1];
                outgoing_report.kb_payload_0.report_id = REPORT_ID_KEYBOARD_GROUP0;
                break;
            default:
                break;
        }

        DBG_PING_L(DBG_SIGNAL_DEBUG_1);
    }
}

__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_reports_keyboard_nkey(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;
        DBG_PING_H(DBG_SIGNAL_DEBUG_1);
        /** Prepare report for reliable buffer */

        switch (rr_idx_2_4g){
            case HID_REPORT_RATE_8K_HZ:
                // 9 bytes when 2.4G connection and 8K RR
                *((uint32_t*)(&outgoing_report.kb_payload_1.nkey[0])) = outgoing->kb_nkey_map[2];
                *((uint32_t*)(&outgoing_report.kb_payload_1.nkey[4])) = outgoing->kb_nkey_map[3];
                outgoing_report.kb_payload_1.report_id = REPORT_ID_KEYBOARD_GROUP1;
                break;
            default:
                break;
        }

        DBG_PING_L(DBG_SIGNAL_DEBUG_1);
    }
}

__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_reports_keyboard(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;
        DBG_PING_H(DBG_SIGNAL_DEBUG_1);
        /** Prepare report for reliable buffer */

        switch (rr_idx_2_4g){
            case HID_REPORT_RATE_125_HZ:
            case HID_REPORT_RATE_250_HZ:
            case HID_REPORT_RATE_500_HZ:
            case HID_REPORT_RATE_1K_HZ:
            case HID_REPORT_RATE_2K_HZ:
            case HID_REPORT_RATE_4K_HZ:
                /* NOTE:
                 * controller RR & app RR not sync
                 * switch the data length may cause disconnection  */

                /* 17 bytes when 2.4G connection and RR lower than 8K */
                memset(&(outgoing_report.kb_payload), 0, sizeof(T_HID_REPORT_KB_NKEY_16_S));
                // 9 bytes when 2.4G connection and 8K RR
                *((uint32_t*)(&outgoing_report.kb_payload.combo)) = outgoing->kb_nkey_map[0];
                *((uint32_t*)(&outgoing_report.kb_payload.nkey[3])) = outgoing->kb_nkey_map[1];
                *((uint32_t*)(&outgoing_report.kb_payload.nkey[7])) = outgoing->kb_nkey_map[2];
                *((uint32_t*)(&outgoing_report.kb_payload.nkey[11])) = outgoing->kb_nkey_map[3];
                outgoing_report.kb_payload.report_id = REPORT_ID_KEYBOARD;
                break;

            default:
                break;
        }

        DBG_PING_L(DBG_SIGNAL_DEBUG_1);
    }
}

#endif /* AIR_PRODUCT_TYPE_KEYBOARD */

#if !defined(AIR_PRODUCT_TYPE_MOUSE) && defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_reports_1R1T_12bits(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;

        #if !defined (AIR_HID_DUMMY_REPORT_RATE)
        if (rr_idx_2_4g == HID_REPORT_RATE_8K_HZ)
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
        {
            /** Prepare report for reliable buffer */
            #if defined(AIR_GAME_CONTROLLER_9B_DATA)
            FAST_WORD_WRITE(outgoing_report.ms_s16_z8.wheel_key,
                outgoing->ms_k,
                0,
                0,
                0
            );

            FAST_WORD_WRITE(outgoing_report.ms_s16_z8.y,
                0,
                0,
                0,
                ATTACHE_SN_AT(sn_num)
            );
            outgoing_report.ms_s16_z8.report_id = REPORT_ID_MOUSE_16BIT;
            #else
            FAST_WORD_WRITE(outgoing_report.ms_s16_z8.ac_pan,
                ATTACHE_SN_AT(sn_num),
                outgoing->ms_k,
                0,
                0
            );


            FAST_WORD_WRITE(outgoing_report.ms_s16_z8.y,
                0,
                0,
                REPORT_ID_MOUSE_16BIT,
                TX_STATUS_LOG
            );
            #endif
        }
        #if !defined (AIR_HID_DUMMY_REPORT_RATE)
        else
        {
            memset(&outgoing_report.ms_s16_z8_17b, 0, sizeof(T_HID_MOUSE_2_4G_REPORT_K8_S16_Z8_17B));
            outgoing_report.ms_s16_z8_17b.wheel_key = outgoing->ms_k;
            outgoing_report.ms_s16_z8_17b.report_id = REPORT_ID_MOUSE_16BIT;
        }
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
    }
}
#endif /* !defined(AIR_PRODUCT_TYPE_MOUSE) && defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */

#if defined(AIR_KEYBOARD_M607)
__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_reports_1R1T_12bits(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;

        /** Prepare report for reliable buffer */
        FAST_WORD_WRITE(outgoing_report.ms_s16_z8.wheel_key,
            (LAST_3_BITS(outgoing->kb_ms) << 5) | ((outgoing->kb_ms >> 8) & LSB),
            0,
            0,
            0
        );

        FAST_WORD_WRITE(outgoing_report.ms_s16_z8.y,
            0,
            0,
            0,
            ATTACHE_SN_AT(sn_num)
        );
        outgoing_report.ms_s16_z8.report_id = REPORT_ID_MOUSE_16BIT;
    }
}
#endif /* defined(AIR_KEYBOARD_M607) */

#if defined(AIR_PRODUCT_TYPE_KEYBOARD) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_kb_consumer_reports_1R1T(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;
        #if !defined (AIR_HID_DUMMY_REPORT_RATE) && !defined (AIR_PRODUCT_TYPE_MOUSE)
        if (rr_idx_2_4g == HID_REPORT_RATE_8K_HZ)
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
        {
            /** Prepare report for reliable buffer */
            #if defined(AIR_GAME_CONTROLLER_9B_DATA) || defined(AIR_PRODUCT_TYPE_KEYBOARD)
            FAST_WORD_WRITE(outgoing_report.kb_consumer2.consumer[0],
                outgoing->kb_consumer & LSB,
                (outgoing->kb_consumer >> 8) & LSB,
                (outgoing->kb_consumer >> 16) & LSB,
                (outgoing->kb_consumer >> 24) & LSB
            );

            FAST_WORD_WRITE(outgoing_report.kb_consumer2.numeric_key_pad,
                0x00,
                0x00,
                0x00,
                ATTACHE_SN_AT(sn_num)
            );
            outgoing_report.kb_consumer2.report_id = REPORT_ID_KB_CONSUMER;
            #elif defined(AIR_MOUSE_9B_DATA)
            FAST_WORD_WRITE(outgoing_report.kb_consumer2.dummy_2,
                ATTACHE_SN_AT(sn_num),
                outgoing->kb_consumer & LSB,
                (outgoing->kb_consumer >> 8) & LSB,
                (outgoing->kb_consumer >> 16) & LSB
            );

            FAST_WORD_WRITE(outgoing_report.kb_consumer2.consumer[3],
                (outgoing->kb_consumer >> 24) & LSB,
                0x00,
                0x00,
                0x00
            );
            outgoing_report.kb_consumer2.report_id = REPORT_ID_KB_CONSUMER;
            #else
            FAST_WORD_WRITE(outgoing_report.kb_consumer2.numeric_key_pad,
                0x00,
                outgoing->kb_consumer & LSB,
                (outgoing->kb_consumer >> 8) & LSB,
                (outgoing->kb_consumer >> 16) & LSB
            );

            FAST_WORD_WRITE(outgoing_report.kb_consumer2.consumer[3],
                (outgoing->kb_consumer >> 24) & LSB,
                0x00,
                REPORT_ID_KB_CONSUMER,
                ATTACHE_SN_AT(sn_num)
            );
            #endif
        }
        #if !defined (AIR_HID_DUMMY_REPORT_RATE) && !defined (AIR_PRODUCT_TYPE_MOUSE)
        else
        {
            memset(&outgoing_report.kb_consumer2_17b, 0, sizeof(T_HID_2_4G_REPORT_KB_CONSUMER2_17B_S));
            FAST_WORD_WRITE(outgoing_report.kb_consumer2_17b.consumer[0],
                outgoing->kb_consumer & LSB,
                (outgoing->kb_consumer >> 8) & LSB,
                (outgoing->kb_consumer >> 16) & LSB,
                (outgoing->kb_consumer >> 24) & LSB
            );
            outgoing_report.kb_consumer2_17b.report_id = REPORT_ID_KB_CONSUMER;
        }
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
    }
}
#endif /* defined(AIR_PRODUCT_TYPE_KEYBOARD) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */

#if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
__attribute__ ((optimize("O3")))  void hid_express_gaming_generate_kb_std_reports_1R1T(T_OUTGOING_VALUES_S* outgoing)
{
    if(reliable_tx_ptr != NULL)
    {
        sn_num++;

        #if !defined (AIR_HID_DUMMY_REPORT_RATE)
        if (rr_idx_2_4g == HID_REPORT_RATE_8K_HZ)
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
        {
            /** Prepare report for reliable buffer */
            #if defined(AIR_GAME_CONTROLLER_9B_DATA)
            FAST_WORD_WRITE(outgoing_report.kb_std5.combo,
                outgoing->kb_std[0] & LSB,
                (outgoing->kb_std[0] >> 8) & LSB,
                (outgoing->kb_std[0] >> 16) & LSB,
                (outgoing->kb_std[0] >> 24) & LSB
            );

            FAST_WORD_WRITE(outgoing_report.kb_std5.keycode[3],
                outgoing->kb_std[1] & LSB,
                (outgoing->kb_std[1] >> 8) & LSB,
                0,
                ATTACHE_SN_AT(sn_num)
            );
            outgoing_report.kb_std5.report_id = REPORT_ID_KB_STD;
            #elif defined(AIR_MOUSE_9B_DATA)
            FAST_WORD_WRITE(outgoing_report.kb_std5.dummy_2,
                ATTACHE_SN_AT(sn_num),
                outgoing->kb_std[0] & LSB,
                (outgoing->kb_std[0] >> 8) & LSB,
                (outgoing->kb_std[0] >> 16) & LSB
            );

            FAST_WORD_WRITE(outgoing_report.kb_std5.keycode[2],
                (outgoing->kb_std[0] >> 24) & LSB,
                outgoing->kb_std[1] & LSB,
                (outgoing->kb_std[1] >> 8) & LSB,
                0x00
            );
            outgoing_report.kb_std5.report_id = REPORT_ID_KB_STD;
            #else
            FAST_WORD_WRITE(outgoing_report.kb_std5.last_keycode,
                (outgoing->kb_std[1] >> 8) & LSB,
                outgoing->kb_std[0] & LSB,
                (outgoing->kb_std[0] >> 8) & LSB,
                (outgoing->kb_std[0] >> 16) & LSB
            );

            FAST_WORD_WRITE(outgoing_report.kb_std5.keycode[2],
                (outgoing->kb_std[0] >> 24) & LSB,
                outgoing->kb_std[1] & LSB,
                REPORT_ID_KB_STD,
                ATTACHE_SN_AT(sn_num)
            );
            #endif
        }
        #if !defined (AIR_HID_DUMMY_REPORT_RATE) && !defined (AIR_PRODUCT_TYPE_MOUSE)
        else
        {
            memset(&outgoing_report.kb_std5_17b, 0, sizeof(T_HID_2_4G_REPORT_KB_STD5_17B_S));
            FAST_WORD_WRITE(outgoing_report.kb_std5_17b.combo,
                outgoing->kb_std[0] & LSB,
                (outgoing->kb_std[0] >> 8) & LSB,
                (outgoing->kb_std[0] >> 16) & LSB,
                (outgoing->kb_std[0] >> 24) & LSB
            );

            FAST_WORD_WRITE(outgoing_report.kb_std5_17b.keycode[3],
                outgoing->kb_std[1] & LSB,
                (outgoing->kb_std[1] >> 8) & LSB,
                0,
                ATTACHE_SN_AT(sn_num)
            );
            outgoing_report.kb_std5_17b.report_id = REPORT_ID_KB_STD;
        }
        #endif /* not AIR_HID_DUMMY_REPORT_RATE */
    }
}
#endif /* defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */

int hid_express_gaming_data_send(T_OUTGOING_VALUES_S* outgoing, uint32_t tx_result, uint32_t  tx_idx, uint32_t dongle_scenario)
{
    uint32_t report_id = riscv_hid_report_id_select(outgoing);

    switch (report_id)
    {
    #if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
        case REPORT_ID_GAME_CONTROLLER:
        case REPORT_ID_GAME_CONTROLLER_GROUP0:
        case REPORT_ID_GAME_CONTROLLER_GROUP1:
        case REPORT_ID_GAME_CONTROLLER_GROUP2:
        case REPORT_ID_GAME_CONTROLLER_ALL_IN_ONE:
            DBG_PING_H(41);
            hid_express_gaming_generate_reports_game_controller(outgoing);
            DBG_PING_L(41);
            break;
    #endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */
    #if defined(AIR_PRODUCT_TYPE_MOUSE) && defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case REPORT_ID_KB_STD_XY:
            hid_express_gaming_generate_kb_std_xy_reports_1R1T(outgoing);
            break;
        case REPORT_ID_KB_CONSUMER_XY:
            hid_express_gaming_generate_kb_consumer_xy_reports_1R1T(outgoing);
            break;
    #endif
    #if defined(AIR_PRODUCT_TYPE_KEYBOARD) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case REPORT_ID_KB_CONSUMER:
            hid_express_gaming_generate_kb_consumer_reports_1R1T(outgoing);
            break;
    #endif /* defined(AIR_PRODUCT_TYPE_KEYBOARD) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
        case REPORT_ID_KB_STD:
            hid_express_gaming_generate_kb_std_reports_1R1T(outgoing);
            break;
    #endif /* defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */
    #if defined(AIR_PRODUCT_TYPE_MOUSE) || defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) || defined(AIR_KEYBOARD_M607)
        case REPORT_ID_MOUSE:
            hid_express_gaming_generate_reports_1R1T_12bits(outgoing);
            break;
    #endif
    #if defined(AIR_PRODUCT_TYPE_KEYBOARD)
        case REPORT_ID_KEYBOARD:
            hid_express_gaming_generate_reports_keyboard(outgoing);
            break;
        case REPORT_ID_KEYBOARD_GROUP0:
            hid_express_gaming_generate_reports_keyboard_combo(outgoing);
            break;
        case REPORT_ID_KEYBOARD_GROUP1:
            hid_express_gaming_generate_reports_keyboard_nkey(outgoing);
            break;
    #endif /* AIR_PRODUCT_TYPE_KEYBOARD */

    #if defined(AIR_ACL_PACKET_VIA_HID_REPORT)
        case REPORT_ID_MS_ACL_PACKET_CUST_PROTOCOL:
            hid_express_gaming_generate_acl_response_reports(outgoing);
            break;
    #endif

        default:
            return 0;
    }

    // DBG_PING_H(40);
    hid_express_gaming_submit_report_to_pka();
    #if !defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    if(reliable_tx_ptr != NULL)
    {
        reliable_tx_ptr_previous = reliable_tx_ptr;
    }
    #endif
    #if defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
    last_report_id = report_id;
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    if(last_xy_over_12bits)
    {
        /* Previous has no buffer, and current has buffer to send */
        last_report_id = REPORT_ID_KB_STD;
        if(tx_result == 0)
        {
            last_xy_over_12bits = false;
        }
    }
    #endif /* defined(AIR_PRODUCT_TYPE_MOUSE) */
    #endif /* defined(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP) */
    // DBG_PING_L(40);
    return 0;
}

void hid_express_gaming_init()
{
    #if defined(AIR_PRODUCT_TYPE_MOUSE)
    hid_express_x_y_buf_init(&g_vCtrl_x, &g_vCtrl_y);
    #endif /* defined(AIR_PRODUCT_TYPE_MOUSE) */

    #if defined(AIR_REPORT_DATA_LOG)
    memset((uint8_t*)&report_log, 0, sizeof(report_log));
    #endif
}

void hid_express_2_4g_post_process(uint32_t tx_result)
{

}


#if defined(AIR_REPORT_DATA_LOG)
void hid_express_2_4g_copy_report_for_debug(uint32_t tx_result, uint32_t report_go_previous)
{
    // if(tx_result == 0 && report_go_previous == 1)
    // {
    //      hid_express_copy_report_for_debug_print((uint8_t*)&outgoing_report, NULL);
    // }
}
#endif
// #endif /*  */
