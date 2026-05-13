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

#ifndef _BT_RAS_H_
#define _BT_RAS_H_

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/cs.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/hci_types.h>

/** @file
 *  @defgroup bt_ras Ranging Service API
 *  @{
 *  @brief API for the Ranging Service (RAS).
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief Ranging Service UUID value
 */
#define BT_UUID_RAS_VAL 0x185B
/**
 *  @brief Ranging Service
 */
#define BT_UUID_RAS \
    BT_UUID_DECLARE_16(BT_UUID_RAS_VAL)
/**
 *  @brief RAS Features UUID value
 */
#define BT_UUID_RAS_FEATURES_VAL 0x2C14
/**
 *  @brief RAS Features
 */
#define BT_UUID_RAS_FEATURES \
    BT_UUID_DECLARE_16(BT_UUID_RAS_FEATURES_VAL)

/**
 *  @brief Real-time Ranging Data UUID value
 */
#define BT_UUID_REALTIME_RANGING_DATA_VAL 0x2C15
/**
 *  @brief Real-time Ranging Data
 */
#define BT_UUID_REALTIME_RANGING_DATA \
    BT_UUID_DECLARE_16(BT_UUID_REALTIME_RANGING_DATA_VAL)

/**
 *  @brief On-demand Ranging Data UUID value
 */
#define BT_UUID_ONDEMAND_RANGING_DATA_VAL 0x2C16
/**
 *  @brief On-demand Ranging Data
 */
#define BT_UUID_ONDEMAND_RANGING_DATA \
    BT_UUID_DECLARE_16(BT_UUID_ONDEMAND_RANGING_DATA_VAL)

/**
 *  @brief RAS Control Point UUID value
 */
#define BT_UUID_RAS_CP_VAL 0x2C17
/**
 *  @brief RAS Control Point
 */
#define BT_UUID_RAS_CP \
    BT_UUID_DECLARE_16(BT_UUID_RAS_CP_VAL)

/**
 *  @brief Ranging Data Ready UUID value
 */
#define BT_UUID_RANGING_DATA_READY_VAL 0x2C18
/**
 *  @brief Ranging Data Ready
 */
#define BT_UUID_RANGING_DATA_READY \
    BT_UUID_DECLARE_16(BT_UUID_RANGING_DATA_READY_VAL)

/**
 *  @brief Ranging Data Overwritten UUID value
 */
#define BT_UUID_RANGING_DATA_OVERWRITTEN_VAL 0x2C19
/**
 *  @brief Ranging Data Overwritten
 */
#define BT_UUID_RANGING_DATA_OVERWRITTEN \
    BT_UUID_DECLARE_16(BT_UUID_RANGING_DATA_OVERWRITTEN_VAL)

/**
 *  @brief Ranging Counter is lower 12-bits of CS Procedure_Counter (see Volume 4, Part E, Section 7.7.65.44 in [1]) provided by the Core Controller.
 */
#define BT_RAS_GET_RANGING_COUNTER(CS_PROC_COUNTER) ((CS_PROC_COUNTER) & 0x0FFF)

#define BT_RAS_MAX_SEGMENT_NUM         (63)
#define BT_RAS_UNKNOWN_SEGMENT_NUM     (0xFF)

/** @brief RAS Features */
enum bt_ras_features {
	BT_RAS_FEATURES_REALTIME_RANG_DATA          = BIT(0),
	BT_RAS_FEATURES_RETRIEVE_LOST_RANG_DATA_SEG = BIT(1),
	BT_RAS_FEATURES_ABORT_OPERATION             = BIT(2),
	BT_RAS_FEATURES_FILTER_RANG_DATA            = BIT(3),
};
typedef uint32_t bt_ras_features_t;

/* The RAS Control Point Op Codes for Operations. */
enum {
    /** Get Rang Data.*/
    BT_RAS_CP_PROC_GET_RANG_DATA                 = 0x00,
    /** ACK Rang Data.*/
    BT_RAS_CP_PROC_ACK_RANG_DATA                 = 0x01,
    /** Retrieve Lost Ranging Data Segments.*/
    BT_RAS_CP_PROC_RETIEVE_LOST_RANG_DATA        = 0x02,
    /** Abort Operation.*/
    BT_RAS_CP_PROC_ABORT                         = 0x03,
    /** Set Filter.*/
    BT_RAS_CP_PROC_SET_FILTER                    = 0x04
};
typedef uint8_t bt_ras_cp_proc_type_t;

typedef struct {
    uint16_t ranging_counter;
} bt_ras_cp_get_ranging_data_params_t;

typedef struct {
    uint16_t ranging_counter;
} bt_ras_cp_ack_ranging_data_params_t;

typedef struct {
    uint16_t ranging_counter;
    uint8_t first_segment_index;
    uint8_t last_segment_index;
} bt_ras_cp_retrieve_lost_ranging_data_seg_params_t;

typedef struct {
    uint16_t filter;
} bt_ras_cp_filter_params_t;

/* RAS Control Point procedure definition. */
typedef struct {
    bt_ras_cp_proc_type_t type;
    union {
        bt_ras_cp_get_ranging_data_params_t get_ranging_data_params;
        bt_ras_cp_ack_ranging_data_params_t ack_ranging_data_params;
        bt_ras_cp_retrieve_lost_ranging_data_seg_params_t retrieve_lost_ranging_data_seg_params;
        bt_ras_cp_filter_params_t set_filter_params;
    };
} bt_ras_cp_proc_t;

/** @brief RAS Control Point Op Codes for Responses.  */
enum {
	BT_RAS_CP_RES_COMPLETE_RANG_DATA                = 0x00,
	BT_RAS_CP_RES_COMPLETE_LOST_RANG_DATA_SEG       = 0x01,
	BT_RAS_CP_RES_CODE                              = 0x02,
};
typedef uint8_t bt_ras_cp_res_type_t;

typedef struct {
    uint16_t ranging_counter;
} bt_ras_cp_res_complete_ranging_data_params_t;

typedef struct {
    uint16_t ranging_counter;
    uint8_t first_segment_index;
    uint8_t last_segment_index;
} bt_ras_cp_res_complete_lost_ranging_data_params_t;

/** @brief Response Code Values associated with BT_RAS_CP_RES_CODE  */
enum {
	BT_RAS_CP_RES_ERR_RFU                     = 0x00,
	BT_RAS_CP_RES_ERR_SUCCESS                 = 0x01,
	BT_RAS_CP_RES_ERR_OPCODE_NOT_SUPPORTED    = 0x02,
	BT_RAS_CP_RES_ERR_INVALID_PARAMETER       = 0x03,
	BT_RAS_CP_RES_ERR_SUCCESS_PERSISTED       = 0x04,
	BT_RAS_CP_RES_ERR_ABORT_UNSUCCESSFUL      = 0x05,
	BT_RAS_CP_RES_ERR_PROCEDURE_NOT_COMPLETED = 0x06,
	BT_RAS_CP_RES_ERR_SERVER_BUSY             = 0x07,
	BT_RAS_CP_RES_ERR_NO_RECORDS_FOUND        = 0x08,
};
typedef uint8_t bt_ras_cp_res_params_t;

/* RAS Control Point response definition. */
typedef struct {
    bt_ras_cp_res_type_t type;
    union {
        bt_ras_cp_res_complete_ranging_data_params_t complete_ranging_data_params;
        bt_ras_cp_res_complete_lost_ranging_data_params_t complete_lost_ranging_data_params;
        bt_ras_cp_res_params_t res_params;
    };
} bt_ras_cp_res_t;

/** @brief Segmentation Header */
typedef struct __packed {
	uint8_t first_seg   : 1;
	uint8_t last_seg    : 1;
	uint8_t seg_counter : 6;
} bt_ras_segment_header_t;

/** @brief Ranging data Segment */
typedef struct __packed {
    bt_ras_segment_header_t header;
	uint8_t ranging_data[];
} bt_ras_ranging_data_segment_t;

/** @brief Ranging Header structure */
typedef struct __packed {
	/** Ranging Counter is lower 12-bits of CS Procedure_Counter provided by the Core Controller
	 *  (Core Specification, Volume 4, Part E, Section 7.7.65.44).
	 */
	uint16_t ranging_counter : 12;
	/** CS configuration identifier. Range: 0 to 3. */
	uint16_t config_id       : 4;
	/** Transmit power level used for the CS Procedure. Range: -127 to 20. Units: dBm. */
	int8_t   selected_tx_power;
	/** Antenna paths that are reported:
	 *  Bit0: 1 if Antenna Path_1 included; 0 if not.
	 *  Bit1: 1 if Antenna Path_2 included; 0 if not.
	 *  Bit2: 1 if Antenna Path_3 included; 0 if not.
	 *  Bit3: 1 if Antenna Path_4 included; 0 if not.
	 *  Bits 4-7: RFU
	 */
	uint8_t  antenna_paths_mask;
} bt_ras_ranging_header_t;

/** @brief Subevent Header structure */
typedef struct __packed {
	/** Starting ACL connection event count for the results reported in the event */
	uint16_t start_acl_conn_event;
	/** Frequency compensation value in units of 0.01 ppm (15-bit signed integer).
	 *  Note this value can be BT_HCI_LE_CS_SUBEVENT_RESULT_FREQ_COMPENSATION_NOT_AVAILABLE
	 *  if the role is not the initiator, or the frequency compensation value is unavailable.
	 */
	uint16_t freq_compensation;
	/** Ranging Done Status:
	 *  0x0: All results complete for the CS Procedure
	 *  0x1: Partial results with more to follow for the CS procedure
	 *  0xF: All subsequent CS Procedures aborted
	 *  All other values: RFU
	 */
	uint8_t ranging_done_status   : 4;
	/** Subevent Done Status:
	 *  0x0: All results complete for the CS Subevent
	 *  0xF: Current CS Subevent aborted.
	 *  All other values: RFU
	 */
	uint8_t subevent_done_status  : 4;
	/** Indicates the abort reason when Procedure_Done Status received from the Core Controller
	 *  (Core Specification, Volume 4, Part 4, Section 7.7.65.44) is set to 0xF,
	 *  otherwise the value is set to zero.
	 *  0x0: Report with no abort
	 *  0x1: Abort because of local Host or remote request
	 *  0x2: Abort because filtered channel map has less than 15 channels
	 *  0x3: Abort because the channel map update instant has passed
	 *  0xF: Abort because of unspecified reasons
	 *  All other values: RFU
	 */
	uint8_t ranging_abort_reason  : 4;
	/** Indicates the abort reason when Subevent_Done_Status received from the Core Controller
	 * (Core Specification, Volume 4, Part 4, Section 7.7.65.44) is set to 0xF,
	 * otherwise the default value is set to zero.
	 * 0x0: Report with no abort
	 * 0x1: Abort because of local Host or remote request
	 * 0x2: Abort because no CS_SYNC (mode 0) received
	 * 0x3: Abort because of scheduling conflicts or limited resources
	 * 0xF: Abort because of unspecified reasons
	 * All other values: RFU
	 */
	uint8_t subevent_abort_reason : 4;
	/** Reference power level. Range: -127 to 20. Units: dBm */
	int8_t  reference_power_level;
	/** Number of steps in the CS Subevent for which results are reported.
	 *  If the Subevent is aborted, then the Number Of Steps Reported can be set to zero
	 */
	uint8_t num_steps_reported;
} bt_ras_subevent_header_t;

/** @brief Ranging Data Body Structure */
typedef struct __packed {
   /** Bit 0-1: Mode type; range: 0x00-0x03
	*  Bit 2-6: RFU
	*  Bit 7: 1 means Aborted, 0 means Success
	*  If the Step is aborted and bit 7 is set to 1, then bits 0-6 do not contain any valid data and the length of Step_Data [i] is 0.
    */
    uint8_t step_mode;
    /** Mode- and role-specific information being reported.*/
    uint8_t step_data[];
} bt_ras_subevent_data_t;

/** @brief Subevent Structure */
typedef struct __packed {
    bt_ras_subevent_header_t subevent_header;
    bt_ras_subevent_data_t subevent_data;
} bt_ras_subevent_t;


/** @brief Ranging Data Body Structure */
typedef struct __packed {
    bt_ras_ranging_header_t ranging_header;
    uint8_t subevents[];
} bt_ras_ranging_data_body_t;

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _BT_RAS_H_ */

