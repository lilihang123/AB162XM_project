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


#ifndef BT_RAS_INTERNAL_H_
#define BT_RAS_INTERNAL_H_

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <../inc/bt_ras.h>
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define BT_RAS_CS_PROCEDURE_COUNTER_MAX     (0xFFFF)
#define BT_RAS_CS_PROCEDURE_COUNTER_INVALID (BT_RAS_CS_PROCEDURE_COUNTER_MAX + 1)
#define BT_RAS_RANGING_COUNTER_MAX          (0x0FFF)
#define BT_RAS_RANGING_COUNTER_INVALID      (BT_RAS_RANGING_COUNTER_MAX + 1)

#define BT_RAS_MAX_SUBEVENTS_PER_PROCEDURE 32
#define BT_RAS_MAX_STEPS_PER_PROCEDURE     256

#define BT_RAS_STEP_MODE_0_MAX_LEN MAX(sizeof(struct bt_hci_le_cs_step_data_mode_0_initiator), sizeof(struct bt_hci_le_cs_step_data_mode_0_reflector))
#define BT_RAS_STEP_MODE_1_MAX_LEN MAX(sizeof(struct bt_hci_le_cs_step_data_mode_1), sizeof(struct bt_hci_le_cs_step_data_mode_1_ss_rtt))
#define BT_RAS_STEP_MODE_2_MAX_LEN (sizeof(struct bt_hci_le_cs_step_data_mode_2) + ((CONFIG_BT_RAS_MAX_ANTENNA_PATHS + 1) * sizeof(struct bt_hci_le_cs_step_data_tone_info)))
#define BT_RAS_STEP_MODE_3_MAX_LEN (sizeof(struct bt_hci_le_cs_step_data_mode_3) + ((CONFIG_BT_RAS_MAX_ANTENNA_PATHS + 1) * sizeof(struct bt_hci_le_cs_step_data_tone_info)))                                           \

#define BT_RAS_STEP_MODE_0_1_MAX_LEN   MAX(BT_RAS_STEP_MODE_0_MAX_LEN, BT_RAS_STEP_MODE_1_MAX_LEN)
#define BT_RAS_STEP_MODE_0_1_2_MAX_LEN MAX(BT_RAS_STEP_MODE_0_1_MAX_LEN, BT_RAS_STEP_MODE_2_MAX_LEN)

#define BT_RAS_RANGING_HEADER_LEN  4 //sizeof(struct bt_ras_ranging_header_t)
#define BT_RAS_SUBEVENT_HEADER_LEN 8 //sizeof(struct bt_ras_subevent_header_t)
#define BT_RAS_STEP_MODE_LEN       1
#define BT_RAS_STEP_DATA_MAX_LEN MAX(MAX(BT_RAS_STEP_MODE_0_MAX_LEN, BT_RAS_STEP_MODE_1_MAX_LEN), MAX(BT_RAS_STEP_MODE_0_MAX_LEN, BT_RAS_STEP_MODE_1_MAX_LEN))

#define BT_RAS_CS_PROCEDURE_MEM                                                                  \
    (BT_RAS_RANGING_HEADER_LEN +                                                              \
    (BT_RAS_MAX_SUBEVENTS_PER_PROCEDURE * BT_RAS_SUBEVENT_HEADER_LEN) +                       \
    (BT_RAS_MAX_STEPS_PER_PROCEDURE * BT_RAS_STEP_MODE_LEN) +                                 \
    (BT_RAS_MAX_STEPS_PER_PROCEDURE * BT_RAS_STEP_DATA_MAX_LEN))

#define BT_RAS_PROCEDURE_SUBEVENTS_MEM (BT_RAS_CS_PROCEDURE_MEM - BT_RAS_RANGING_HEADER_LEN)

BUILD_ASSERT(sizeof(bt_ras_ranging_header_t) == BT_RAS_RANGING_HEADER_LEN);
BUILD_ASSERT(sizeof(bt_ras_subevent_header_t) == BT_RAS_SUBEVENT_HEADER_LEN);

 /** @brief RAS Ranging Data buffer structure.
  *
  *  RAS V1.0 Section 3.2.1.2 Ranging Data Body
  *  Ranging Data stored by a RAS Server may contain zero or more CS Subevent Data elements,
  *  up to a maximum of 32 elements. The CS Subevent Data can have 1-3 Mode 0 Step results
  *  and multiple non-Mode 0 Step results, where the maximum number of CS Steps per CS Subevent
  *  is 160 and the maximum number of CS Steps per CS Procedure is 256 (see Volume 6,
  *  Part B, Section 4.5.18.1 in [1]).
  *
  *  @note The following CS subevent fields are not included by specification:
  *        subevent count, step channel, step length.
  */
typedef struct {
     /** Connection with an RRSP instance owning this buffer. */
     struct bt_conn *conn;
     /** CS Procedure Ranging Counter stored in this buffer. */
     uint16_t procedure_counter;
     /** Ranging Counter stored in this buffer. */
     uint16_t ranging_counter;
     /** Cursor of the subevents buffer. */
     uint16_t subevent_cursor;
     /** The cursor is out of the subevents buffer. */
     bool oom_occur;
     /** The storage is taken. */
     //bool taken;
     /** All ranging data of the CS procedure has been received, it is ready to send. */
     bool ready;
     /** Complete ranging data procedure buffer. */
     union {
         uint8_t buf[BT_RAS_CS_PROCEDURE_MEM];
         struct {
             bt_ras_ranging_header_t ranging_header;
             uint8_t subevents[];
         } __packed;
     } procedure;
 } bt_ras_cs_procedure_storage_t;

extern void bt_ras_rrsp_new_ranging_data_ready(struct bt_conn *conn, uint16_t ranging_counter);
extern void bt_ras_rrsp_ranging_data_overwritten(struct bt_conn *conn, uint16_t ranging_counter);
extern bt_ras_cs_procedure_storage_t *bt_ras_cs_procedure_storage_take(struct bt_conn *conn, uint16_t ranging_counter);
extern uint16_t bt_ras_cs_procedure_storage_pull_data(bt_ras_cs_procedure_storage_t *storage, uint8_t *out, uint16_t out_len, uint16_t *offset, bool *empty);
extern void bt_ras_cs_procedure_storage_free(bt_ras_cs_procedure_storage_t *storage);

#ifdef __cplusplus
 }
#endif

#endif /* BT_RAS_INTERNAL_H_ */

