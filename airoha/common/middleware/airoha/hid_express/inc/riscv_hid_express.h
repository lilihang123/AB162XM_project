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

#ifndef _RISCV_HID_EXPRESS_H_
#define _RISCV_HID_EXPRESS_H_

#include "stdio.h"
#include "stdint.h"
#include "swla.h"
#include "hid_common.h"
#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
#include "hal_ccni.h"
#include "hal_ccni_config.h"
#endif

#if defined(AIR_PRODUCT_TYPE_KEYBOARD)
#include "riscv_hid_express_key_queue_keyboard.h"
#endif
#include <assert.h>
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "riscv_hid_express_key_queue_game_controller.h"
#endif /* AIR_PRODUCT_TYPE_GAME_CONTROLLER */

//#define SUPPORT_1R2T        /** Support 1R2T feature. (1627 Dongle) */
#define ENHANCED_LATENCY
#define HID_REPORT_VIA_CM33  /** HID report is transmitted via CM33 for GATT path test.   */

//#define ENABLE_FORCE_NACK  /** a force nack process when a nack is happened*/


//#define ENABLE_XY_MERGE_AT_NACK_BUFFER  /** Enable XY merge at nack buffer. */

//#define SEND_DUMMY_DATA_IF_NO_REPORT_TO_GO  /** Workaround for controller, keep tx size to 7 bytes */

#define IGNORE_SENSOR_DATA_IN_FAKE_REPORT





#define INVALID_TX_COUNT 0xFF
#define REPORT_ID_VALID_BITS 0x3F

//Special flag in  HID report byte
#define MERGE_X_Y_NOTIFICATION              0x80  // bit 7 is used as x y data merge notification flag

#define FORCE_REPORT_REPEAT_COUNTS  0

#define FORCE_TO_32BITS(parameter)   *(uint32_t*)&parameter
#define FORCE_TO_16BITS(parameter)   *(uint16_t*)&parameter

//#define TIMESTAMP_MAX 65535
#define EINT_TIMESTAMP_MAX 0x10000



#define RISCV_HID_LOG_ENA

#ifdef RISCV_HID_LOG_ENA
#define HID_DBG_LOG(module, message, arg_cnt, ...)        LOG_MSGID_I(module, message, arg_cnt, ##__VA_ARGS__ )
#else
#define HID_DBG_LOG(module, message, arg_cnt, ...)
#endif

#if defined (AIR_ONLINE_SWLA_ENABLE)
#define SWLA_START(label) HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label, SWLA_DIRECTION_START)
#define SWLA_STOP(label) HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label, SWLA_DIRECTION_STOP)
#define SWLA_LABEL(label) HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label, SWLA_DIRECTION_LABEL)
#else
#define SWLA_START(label)
#define SWLA_STOP(label)
#define SWLA_LABEL(label)
#endif

typedef  struct
{
    uint8_t rr_idx;
}T_hid_ctrl_S;

extern T_hid_ctrl_S hid_ctrl; // HID control structure

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
typedef struct{
    uint32_t    type;  // 0 for mouse report, 1 for standare keyboard report, 2 for consumer key report, 3 for n keyboard report, 4 for gamepad report
    uint32_t    last_type;  // 0 for mouse report, 1 for standare keyboard report, 2 for consumer key report, 3 for n keyboard report, 4 for gamepad report
    uint32_t     x;
    uint32_t     y;
    uint32_t     z;
    uint32_t     rz;
    uint32_t     last_x;
    uint32_t     last_y;
    uint32_t     last_z;
    uint32_t     last_rz;
    uint32_t     lt;
    uint32_t     rt;
    uint32_t     lt_rt_digital;
    uint32_t     last_lt;
    uint32_t     last_rt;
    GAME_CONTROLLEER_KEY_INFO_T k;
    uint32_t    hat_switch_byte; // only the lowest byte is used, but use the word size for better perfomance
    uint32_t    key_air_byte; // only the lower 8 bit is used in 8K RR or the lower 16bit is used in not 8K RR, but use the word size for better perfomance
    uint32_t    last_key_air_byte;  // only the lower 8 bit is used in 8K RR or the lower 16bit is used in not 8K RR, but use the word size for better perfomance
    uint32_t    ms_k;
    int32_t     z1;
    int32_t     z2;
    uint32_t    kb_std[2];
    uint32_t    kb_consumer;
}T_OUTGOING_VALUES_S;
#elif defined (AIR_PRODUCT_TYPE_MOUSE)
typedef struct{
    uint32_t    type;  // 0 for mouse report, 1 for standare keyboard report, 2 for consumer key report, 3 for n keyboard report, 4 for gamepad report
    uint32_t    k;
    int32_t     x;
    int32_t     y;
    int32_t     z1;
    int32_t     z2;
    uint32_t    k_old;
    uint32_t    kb_std[2];
    uint32_t    kb_consumer;

    #if defined(AIR_ACL_PACKET_VIA_HID_REPORT)
    uint32_t    acl_packet_data;
    #endif

}T_OUTGOING_VALUES_S;
#elif defined (AIR_PRODUCT_TYPE_KEYBOARD)
typedef struct{
    uint32_t    type;  // 0 for mouse report, 1 for standare keyboard report, 2 for consumer key report, 3 for n keyboard report, 4 for gamepad report
    uint32_t    kb_std[2];
    /* consumer key:2 bytes */
    uint32_t    kb_consumer;
    /* 1 combo + 15 data */
    uint32_t    kb_nkey_map[4];
    /* ms key remap:2 bytes (key + wheel)*/
    uint32_t    kb_ms;
    /* nkey addr */
    uint32_t    kb_nkey_map_addr;
}T_OUTGOING_VALUES_S;
#else
    #error "Unknown type for T_OUTGOING_VALUES_S"
#endif

#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
typedef struct {
    uint8_t    msg_id;
    uint8_t    payload[7];
}T_APP_CCNI_MSG_S;
#endif

#define DONGLE_1627_1R2T_2K 0x00
#define DONGLE_1620_1R1T_8K 0x51

#define MODE_USB    0x00
#define MODE_2_4G   0x01
#define MODE_BT     0x02

#define HALF        0x0000FFFF
#define LSB         0x000000FF
#define HNB         0x000000F0
#define LNB         0x0000000F
#define LAST_3_BITS(x) ((x) & 0x7)
#define MAX_12BIT   2047
#define MIN_12BIT   -2048

#define XY16_TO_3_BYTES(x, y, bytes)                    \
    bytes[0] = ((x >> 0) & LSB);                        \
    bytes[1] = ((x >> 8) & LNB) | ((y & LNB) << 4) ;    \
    bytes[2] = ((y >> 4) & LSB);

typedef uint32_t __attribute__((may_alias)) u32_may_alias_t;
#define FAST_WORD_WRITE(target, src_0, src_1, src_2, src_3 ) do { \
    u32_may_alias_t temp = ((src_0) & LSB) \
                        | (((src_1) & LSB) << 8) \
                        | (((src_2) & LSB) << 16) \
                        | (((src_3) & LSB) << 24); \
    *((u32_may_alias_t *)&target) = temp; \
} while(0)

#define FAST_WORD_WRITE_BY_TWO_HALF(target, src_half_0, src_half_1) \
    *((uint32_t *)&target ) =  ((src_half_0) & HALF)                     \
                            |  (((src_half_1) & HALF) <<  16);


#define FAST_WORD_COPY(target_ptr, src_ptr, u32_offset)                         \
    *((uint32_t *)(target_ptr) + u32_offset) = *((uint32_t *)(src_ptr) + u32_offset) ;

extern uint32_t hid_flags;

#if defined(AIR_REPORT_DATA_LOG)
extern T_HID_REPORT_LOG_S report_log;
#endif



typedef enum {
    BUF_IDX_ACK = 0,
    BUF_IDX_NACK,
    BUF_IDX_T1_ACK_T0_NACK,     /** Used for 1R2T only. For 1R1T, this is not used. */
    BUF_IDX_T1_NACK_T0_NACK,    /** Used for 1R2T only. For 1R1T, this is not used. */
} T_REPORT_BUF_IDX_E;

typedef enum {
    IDX_TX_0 = 0,
    IDX_TX_1,
} T_TX_RECORD_BUF_IDX_E;


typedef enum {
    HID_EXP_1ST_CB = 0,                         /** It is called at the begging of spi isr */
    HID_EXP_2ND_CB,                             /** It is called to get x,y,z data of mouse */
    HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL,    /** Get latest key status. It timing critical. The more process time, the more latency   */
    HID_EXP_4TH_CB_POST_PROCESS,                /** Used to process that is excluded in HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL*/
    HID_EXP_NO_REPORT_PROCESS,                  /** It is called if the traffice is stopped in idle state. app can do the things that is not related to report processing. somthing like pherial io control*/
} T_PS_CB_TYPE_E;

typedef void (*riscv_ps_callback_t)(T_PS_CB_TYPE_E type,  T_OUTGOING_VALUES_S * outgoing);

int hid_express_init(riscv_ps_callback_t ps_callback);
uint32_t hid_express_get_outgpoig_report_result();
void hid_express_report_go_update(bool go);

#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
void hid_express_entrance();
#endif
uint32_t current_tx_count();

int hid_express_prepare_X_Y(T_OUTGOING_VALUES_S * outgoing );
int hid_express_send(T_OUTGOING_VALUES_S * outgoing, uint32_t timestamp_key_press );

uint32_t hid_express_get_hid_flag();
T_OUTGOING_VALUES_S *hid_express_get_outgoing_data();
uint32_t hid_express_get_get_tx_result();
void hid_express_dongle_scenario_update(uint32_t scenario);
void hid_express_debug_print();
void hid_express_clear_key_pushed();

#ifdef  ENHANCED_LATENCY
void hid_express_memcpy32(uint8_t *tgt, uint8_t *src, uint32_t len_in_bytes);
#endif

#if defined(AIR_REPORT_DATA_LOG)
bool hid_express_report__get_log_data_ptr(T_HID_REPORT_LOG_S ** log_data_ptr);
void hid_express_copy_report_for_debug_print(uint8_t* ack, uint8_t* nack);
void hid_express_report_log_print();
#endif

void hid_express_set_features(uint32_t hid_exp_features);


#define CLEAR_PTR   0
#define GET_PTR     1

void hid_express_deinit();
void hid_express_set_report_rate_idx(uint32_t rr);
void hid_express__push_to_key_queue(uint32_t value_type, uint32_t value);
uint32_t hid_express_get_report_go_previous();
uint32_t hid_express_get_last_report_go();
uint32_t hid_express_get_previous_tx_result();
#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
void hid_express_set_mode(uint8_t mode);
uint8_t hid_express_get_mode(void);
#endif
#endif /* _RISCV_HID_EXPRESS_H_ */
