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


#ifndef _AUTO_SWITCH_SERVICE_H_
#define _AUTO_SWITCH_SERVICE_H_

#if defined(CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Public define -------------------------------------------------------------*/

/* Auto switch mode definitions */
#define AUTO_SWITCH_MODE_AUTO       0x00    /* default mode, auto switch mode */
#define AUTO_SWITCH_MODE_MANUAL     0x01    /* manual switch mode */
typedef uint8_t auto_switch_mode_t;

/* VPA voltage index definitions */
#define AUTO_SWITCH_VPA_0_96V       0       /* VPA = 0.96V */
#define AUTO_SWITCH_VPA_1_2V        1       /* VPA = 1.2V */
#define AUTO_SWITCH_VPA_1_45V       2       /* VPA = 1.45V */

typedef struct {
    uint8_t snr_boost;
    uint8_t snr_boost_distance;
    uint8_t snr_drop;
    uint8_t snr_recovery_phy;
    uint8_t stable_boost_limit;
    uint8_t stable_drop_limit;
    uint8_t stable_drop_phy_limit;
    uint8_t good_ch_cnt;
}auto_switch_control_param_t;

typedef struct {
    int8_t      rx_rssi;
    uint16_t    aver_per;
    uint16_t    snr_perd;
}auto_service_link_quality_t;

typedef uint32_t auto_switch_event_t;
#define AUTO_SWITCH_EVENT_LINK_QUALITY_IND                           0x01   /**< Notify user that the PER or RSSI. for parameter please refer to structure #auto_service_link_quality_t. */

/**
 * @brief   Defines a function pointer to function which is used to listen and handle the events reported from Ultra Low Latency service.
 * @param[in] event       is the callback event type.
 * @param[in] param       is the payload of the callback event.
 * @param[in] param_len   is the payload length.
 * @return  Void.
 */
typedef void (* auto_switch_callback)(auto_switch_event_t event, void *param, uint32_t param_len);

/* Public functions ----------------------------------------------------------*/

/**
 * @brief   This function is used for application to init Auto Switch Service.
 * @param[in]             #void.
 * @return                #int
 */
int auto_switch_init(void);

/**
 * @brief   This function is used for application to deinit Auto Switch Service.
 * @param[in]             #void.
 * @return                #NULL
 */
void auto_switch_deinit(void);

/**
 * @brief   This function is used for application to start Auto Switch Service.
 * @param[in]             #voide.
 * @return                #int
 */
int auto_switch_start(void);

/**
 * @brief   This function is used for application to stop Auto Switch Service.
 * @param[in]             #void.
 * @return                #int
 */
int auto_switch_stop(void);

/**
 * @brief   This function is used for application to set Auto Switch Service Paramters.
 * @param[in]             #*param.
 * @return                #int
 */
int auto_switch_set_parameter(auto_switch_control_param_t *param);

/**
 * @brief   This function is used for application to Control Auto Switch Service.
 * @param[in]             #control.
 * @return                #int
 */
int auto_switch_control(uint8_t control);

/**
 * @brief   This function is used for application to Set Auto Switch Service power info.
 * @param[in]  vpa     VPA voltage index: 0=0.96V, 1=1.2V, 2=1.45V
 * @param[in]  tx_gc   TX Gain Control value (37-61)
 * @return             void
 */
void auto_switch_set_power_info(uint8_t vpa, uint8_t tx_gc);

/**
 * @brief   This function is used for application to Set Auto Switch Service mode.
 * @param[in]             #mode.
 * @return                #void
 */
void auto_switch_set_mode(auto_switch_mode_t mode);

/**
 * @brief   This function is used for application to Get Auto Switch Service mode.
 * @param[in]             #mode.
 * @return                #auto_switch_mode_t
 */
auto_switch_mode_t auto_switch_get_mode(void);

/**
 * @brief   This function is used for application to Set VPA & TX_GC.
 * @param[in]  vpa     VPA voltage index: 0=0.96V, 1=1.2V, 2=1.45V
 * @param[in]  tx_gc   TX Gain Control value (37-61)
 * @return             0 on success, negative error code on failure
 */
int auto_switch_set_vap_tx_gc(uint8_t vpa, uint8_t tx_gc);

/**
 * @brief   This function is used to register callback funtion to Auto Switch Service.
 * @param[in] module is module type.
 * @param[in] cb is callback function.
 * @return                #0, the operation completed successfully.
 *                             #others, the operation has failed.
 */
int auto_switch_srv_register_callback(auto_switch_callback cb);

#endif /* CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER */

#endif /* _AUTO_SWITCH_SERVICE_H_ */