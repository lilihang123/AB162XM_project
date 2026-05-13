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
 

#ifndef __HID_LEBTEST_SERVICE_H__
#define __HID_LEBTEST_SERVICE_H__

#define LABTEST_MODEM_PHY_1M     1
#define LABTEST_MODEM_PHY_2M     2

/* Public typedef ------------------------------------------------------------*/
typedef enum {
	LABTEST_MODE_DC_TONE,  //continue tx with tx pattern 8
	LABTEST_MODE_TX_MODE,  //continue tx with tx pattern 0
	LABTEST_MODE_RX_MODE,  //burst rx
    LABTEST_MODE_MAX_NUM
} T_LABTEST_MODE_E;

typedef enum {
	LABTEST_RF_FREQ_L,   //2402 for 2M phy, 2404 for 1M phy
	LABTEST_RF_FREQ_M,   //2440
	LABTEST_RF_FREQ_H,   //2478 for 2M phy, 2480 for 1M phy
    LABTEST_RF_FREQ_MAX_NUM
} T_LABTEST_RF_FREQ_BAND_E;

typedef enum {
    LABTEST_RF_CH_0,       // 2402
    LABTEST_RF_CH_1,       // 2404
    LABTEST_RF_CH_19 = 19, // 2440
    LABTEST_RF_CH_38 = 38, // 2478
    LABTEST_RF_CH_39,      // 2480
    LABTEST_RF_CH_MAX_NUM
} T_LABTEST_RF_CH_IDX_E;

typedef enum
{
    LABTEST_CTX_MODE,      //continue tx mode      
    LABTEST_BTX_MODE,      //burst tx mode
    LABTEST_BRX_MODE,      //burst rx mode
    LABTEST_RTX_MODE_MAX_NUM,
}T_LABTEST_RTX_MODE_E;

typedef struct
{
  uint8_t mode;
  uint16_t payload_len;
  uint8_t tx_pattern;
  uint8_t rf_ch_idx;
  uint8_t tx_gc1;
  uint8_t tx_gc2;
  uint8_t phy;
}__attribute__((packed)) ble_gap_labtest_start_params_t;

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/


/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
uint8_t hid_labtest__change_action_by_key_press(uint8_t key, uint8_t action);

#endif