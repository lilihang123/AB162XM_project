/* Copyright Statement:
*
* (C) 2024 Airoha Technology Corp. All rights reserved.
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
* the License Agreement ("Permitted User"). If you are not a Permitted User,
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
/* Airoha restricted information */

#ifndef __BT_ULL_LE_H__
#define __BT_ULL_LE_H__

#include <zephyr/device.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/buf.h>
#include <zephyr/bluetooth/bluetooth.h>

/**
 * @addtogroup Bluetooth
 * @{
 *
 * @addtogroup BluetoothULL ULL
 * @{
 * The Ultra Low Latency (ULL) is Airoha proprietary profile that defines the low wireless audio latency.
 * This section introduces the ULL profile APIs and events and how to use this module.
 *
 * Terms and Acronyms
 * ======
 * |Terms                         |Details                                                                  |
 * |------------------------------|-------------------------------------------------------------------------|
 * |\b ULL                        | Ultra low latency.                   |
 * |\b AIR CIS                    | Airoha connected isochronous stream. |
 * |\b AIR CIG                    | Airoha connected isochronous group.  |
 * |\b AIR ISO DATA PATH          | Airoha isochronous data path.        |
 *
 * @section bt_ull_api_usage How to use this module
 *  - Step1: Mandatory, initialize Bluetooth Ultra Low Latency profile.
 *  - Sample code:
 *    @code
 *        bt_ull_le_init();
 *    @endcode
 *
 *  - Step2: Mandatory, implement the event callback to process the ULL events, such as #BT_ULL_LE_AIR_CIS_ESTABLISHED_IND, #BT_ULL_LE_AIR_CIS_DISCONNECT_COMPLETE_IND.
 *  - Sample code:
 *    @code
 *       void bt_app_event_callback(bt_msg_type_t msg_type, bt_status_t status, void *data)
 *       {
 *          switch (msg_type)
 *          {
 *              case BT_ULL_LE_AIR_CIS_CONNECT_REQUEST_IND:
 *              {
 *                  bt_ull_le_air_cis_request_ind_t *request =
 *                      (bt_ull_le_air_cis_request_ind_t *)data;;
 *                  bt_ull_le_air_cis_connect_request_handler(status, request);
 *                  // Respond to the connection request.
 *                  break;
 *              }
 *              case BT_ULL_LE_AIR_CIS_ESTABLISHED_IND:
 *              {
 *                  bt_ull_le_air_cis_established_ind_t *established =
 *                      (bt_ull_le_air_cis_established_ind_t *)data;;
 *                  bt_ull_le_air_cis_established_handler(status, established);
 *                  // Handle the air cis established event.
 *                  break;
 *              }
 *              case BT_ULL_LE_AIR_CIS_DISCONNECT_COMPLETE_IND:
 *              {
 *                  bt_ull_le_air_cis_disconnect_complete_ind_t *disconnect =
 *                      (bt_ull_le_air_cis_disconnect_complete_ind_t *)data;
 *                  bt_ull_le_air_cis_disconnect_handler(status, disconnect);
 *                  // Handle the air cis disconnect complete event.
 *                  break;
 *              }
 *              case BT_ULL_LE_SETUP_AIR_ISO_DATA_PATH_CNF:
 *              {
 *                  bt_ull_le_setup_air_iso_data_path_cnf_t *iso_cnf =
 *                      (bt_ull_le_setup_air_iso_data_path_cnf_t *)data;;
 *                  bt_ull_le_air_cis_set_air_iso_data_path_cnf_handler(status, iso_cnf);
 *                  // Handle the air iso data path confirmation event.
 *                  break;
 *              }
 *              case BT_ULL_LE_CREATE_AIR_CIS_CNF:
 *              {
 *                  ...
 *                  break;
 *              }
 *
 *              ...
 *
 *              default:
 *              {
 *                  break;
 *              }
 *           }
 *       }
 *    @endcode
 *
 *  - Step3: Mandatory, set an air cig parameter to bt controller.
 *  - Sample code:
 *    @code
 *        bt_ull_le_air_cig_params_t params;
 *        uint8_t cis_count = 0x02;
 *        uint8_t count = 0;
 *        bt_ull_le_air_cis_params_t *cis_list = bt_ull_le_srv_memory_alloc(sizeof(bt_ull_le_air_cis_params_t) * cis_count);
 *        for (count = 0; count < cis_count; count ++) {
 *            cis_list[count].cis_id = BT_ULL_LE_CONN_SRV_AIR_CIS_ID_INVANLID + count;
 *            cis_list[count].max_sdu_m_to_s = BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_190/cis_count;
 *            cis_list[count].max_sdu_s_to_m = BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_40;
 *            cis_list[count].phy_m_to_s = BT_ULL_LE_CONN_SRV_PHY_LE_2M;
 *            cis_list[count].phy_s_to_m = BT_ULL_LE_CONN_SRV_PHY_LE_2M;
 *        }
 *        params.cig_id = BT_ULL_LE_CONN_SRV_AIR_CIG_ID_1;
 *        params.client_type = BT_ULL_HEADSET_CLIENT;
 *        params.sdu_interval_m_to_s = BT_ULL_LE_SDU_INTERVAL_5000_US;
 *        params.sdu_interval_s_to_m = BT_ULL_LE_SDU_INTERVAL_5000_US;
 *        params.sca = 0x00;
 *        params.max_share_count = 0x02;
 *        params.iso_interval = BT_ULL_LE_CONN_SRV_ISO_INTERVAL_5MS;
 *        params.max_uplink_num = 0x01;
 *        params.ft_m_to_s = BT_ULL_LE_CONN_SRV_FT_1;
 *        params.ft_s_to_m = BT_ULL_LE_CONN_SRV_FT_1;
 *        params.cis_count = cis_count;
 *        params.cis_list = cis_list;
 *        bt_ull_le_set_air_cig_parameters(&params);
 *        bt_ull_le_srv_memory_free(cis_list);
 *
 *    @endcode
 *  - Step4: Mandatory, create the air cis connection with remote device to transport audio streaming.
 *  - Sample code:
 *    @code
 *        bt_ull_le_create_air_cis_t param;
 *        uint8_t cis_count = 0x02;
 *        uint8_t count = 0;
 *        bt_ull_le_air_cis_set_t *cis_list = bt_ull_le_srv_memory_alloc(sizeof(bt_ull_le_air_cis_set_t) * cis_count);
 *        for (i = 0; i < cis_count; i ++) {
 *            cis_list[i].cis_connection_handle = cis_handle;
 *            // Cis handle return by controller after set air cig parameter.
 *            cis_list[i].acl_connection_handle = acl_handle;
 *            // Acl handle realte to the le acl link
 *            cis_list[i].ul_enable = (cis == BT_ULL_LE_CONN_SRV_AIR_CIS_ID_SINK1) ? true : false;
 *        }
 *        param.cis_count = cis_count;
 *        param.cis_list = cis_list;
 *        bt_ull_le_create_air_cis(&param);
 *        bt_ull_le_srv_memory_free(cis_list);
 *    @endcode
 *
 *  - Step5: Mandatory, set the air iso data path to enable audio streaming.
 *  - Sample code:
 *    @code
 *        bt_ull_le_setup_air_iso_data_path_t param;
 *        param.cis_connection_handle = cis_handle;
 *        param.data_path_id = BT_ULL_LE_CONN_SRV_DATA_PATH_ID_1;
 *        param.codec_format = 0x00;
 *        param.company_id = 0x00;
 *        param.vendor_codec_id = 0x00;
 *        param.controller_delay = 0x00;
 *        bt_ull_le_setup_air_iso_data_path(&param);
 *    @endcode
 *
 */


#define BT_CHANNEL_NUMBER 40
/*for ull hid service*/

#define BT_HCI_CMD_VENDOR_SET_AIR_HID_LOCAL_TX_GC            0xFE10
#define BT_HCI_CMD_VENDOR_SET_AIR_HID_CIG_PARAMS             0xFE30
#define BT_HCI_CMD_VENDOR_CREATE_AIR_HID_CIS                 0xFE31
#define BT_HCI_CMD_VENDOR_CANCEL_CREATE_AIR_HID_CIS          0xFE32
#define BT_HCI_CMD_VENDOR_REMOVE_AIR_HID_CIG                 0xFE33
#define BT_HCI_CMD_VENDOR_SYNC_AIR_HID_CIS                   0xFE34
#define BT_HCI_CMD_VENDOR_CANCEL_SYNC_AIR_HID_CIS            0xFE35
#define BT_HCI_CMD_VENDOR_SET_REPORT_RATE                    0xFE37
#define BT_HCI_CMD_VENDOR_DISCONNECT_AIR_HID_CIS             0xFE3A
#define BT_HCI_CMD_VENDOR_TX_POWER_REMOTE_CONTROL            0xFE3B
#define BT_HCI_CMD_VENDOR_SET_PRI_ENABLE                     0xFE3C
#define BT_HCI_CMD_VENDOR_GET_AIR_HID_CONN_INFO              0xFE3D
#define BT_HCI_CMD_VENDOR_SET_AIR_HID_TX_POWER               0xFE3E
#define BT_HCI_CMD_VENDOR_ENABLE_AIR_HID_SCAN                0xFE3F


/*for ull service*/
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_ESTABLISHED                 0xFA
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_DISCONNECT_COMPLETE         0xFB
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_RR_CHANGE                   0xFC
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_TX_POWER                    0xFD
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_CONN_INFO                   0xFE
#define BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_ADV_REPORT                  0xFF

/**
 *  @brief Define the ULL role.
 */
typedef uint8_t bt_ull_role_t;
#define BT_ULL_ROLE_UNKNOWN         0x00    /**< Unknown role. */
#define BT_ULL_ROLE_CLIENT          0x01    /**< Headset/Earbuds/WirelessMic. */
#define BT_ULL_ROLE_SERVER          0x02    /**< Dongle. */

typedef uint8_t bt_ull_phy_t;
#define BT_ULL_PHY_1M                0x00    /**< 1M PHY. */
#define BT_ULL_PHY_2M                0x01    /**< 2M PHY. */
#define BT_ULL_PHY_4M                0x07    /**< 4M PHY. */

/*************************************************************************AIR HID CIS**********************************************************************************************************/
/*******************************************************************************************************************************************************************************
* 
* Define AIR HID CIS event type
*
*******************************************************************************************************************************************************************************/
#define BT_MODULE_OFFSET                26          /**< Module range: 0x00 ~ 0x3F. The maximum number of modules: 64. */
#define BT_MODULE_ULL                   (0x1EU<<BT_MODULE_OFFSET) /**< Prefix of the ULL module. 0x78000000 */

#define BT_ULL_LE_AIR_HID_CIS_ESTABLISHED_IND                    (BT_MODULE_ULL | 0x0030)       /**< AIR HID CIS established indication with #bt_ull_le_air_hid_cis_established_ind_t. */
#define BT_ULL_LE_AIR_HID_CIS_DISCONNECT_COMPLETE_IND            (BT_MODULE_ULL | 0x0031)       /**< AIR HIID CIS disconnected indication with #bt_ull_le_air_hid_cis_disconnect_t. */
#define BT_ULL_LE_SET_AIR_HID_CIG_PARAMS_CNF                     (BT_MODULE_ULL | 0x0032)       /**< Set AIR HID CIG parameters confirmation with #bt_ull_le_set_air_hid_cig_cnf_t. */
#define BT_ULL_LE_REMOVE_AIR_HID_CIG_CNF                         (BT_MODULE_ULL | 0x0033)       /**< Remove AIR HID CIG confirmation with #bt_ull_le_remove_air_hid_cig_cnf_t. */
#define BT_ULL_LE_CREATE_AIR_HID_CIS_CNF                         (BT_MODULE_ULL | 0x0034)       /**< Create AIR HID CIS connection confirmation with NULL payload. */
#define BT_ULL_LE_SYNC_AIR_HID_CIS_CNF                           (BT_MODULE_ULL | 0x0035)       /**< Create AIR HID CIS connection confirmation with NULL payload. */
#define BT_ULL_LE_CANCEL_CREATE_AIR_HID_CIS_CNF                  (BT_MODULE_ULL | 0x0036)       /**< Create AIR HID CIS connection confirmation with NULL payload. */
#define BT_ULL_LE_CANCEL_SYNC_AIR_HID_CIS_CNF                    (BT_MODULE_ULL | 0x0037)       /**< Create AIR HID CIS connection confirmation with NULL payload. */
#define BT_ULL_LE_SETUP_AIR_HID_ISO_DATA_PATH_CNF                (BT_MODULE_ULL | 0x0038)       /**< Setup AIR HID ISO data path confirmation with #bt_ull_le_setup_air_hid_iso_data_path_cnf_t. */
#define BT_ULL_LE_REMOVE_AIR_HID_ISO_DATA_PATH_CNF               (BT_MODULE_ULL | 0x0039)       /**< Remove AIR HID ISO data path confirmation with #bt_ull_le_remove_air_hid_iso_data_path_cnf_t. */
#define BT_ULL_LE_DISCONNECT_AIR_HID_CIS_CNF                     (BT_MODULE_ULL | 0x003A)       /**< Disconnect AIR HID CIS confirmation with NULL payload. */
#define BT_ULL_LE_SET_AIR_HID_CIS_SUB_EVENT_CNF                  (BT_MODULE_ULL | 0x003B)       /**< Set AIR HID CIS connectuion sub event with NULL payload. */
#define BT_ULL_LE_SET_AIR_HID_REPORT_RATE_CHANGE_IND             (BT_MODULE_ULL | 0x003C)       /**< AIR HID REPORT RATE CAHNGED INDICATION with #bt_ull_le_air_hid_report_rate_change_ind. */
#define BT_ULL_LE_SET_AIR_HID_CIS_TX_POWER_CHANGE_IND            (BT_MODULE_ULL | 0x003D)       /**< AIR HID CIS TX POWER CHANGED INDICATION with #bt_ull_le_air_hid_cis_tx_power_change_ind. */
#define BT_ULL_LE_SET_AIR_HID_CIS_CONN_INFO_IND                  (BT_MODULE_ULL | 0x003E)       /**< AIR HID CIS CONNECTION INFO CONFIRMATION with #bt_ull_le_air_hid_conn_info_ind_t. */
#define BT_ULL_LE_SET_AIR_HID_CIS_ADV_REPORT_IND                 (BT_MODULE_ULL | 0x0040)       /**< AIR HID CIS PHY CHANGED INDICATION with #bt_ull_le_air_hid_cis_adv_report_ind. */
/*******************************************************************************************************************************************************************************
* 
* Define AIR HID CIS data type
*
*******************************************************************************************************************************************************************************/

/** @brief      The structure definition for the AIR HID CIS parameters of #bt_ull_le_set_air_hid_cig_t. */
typedef struct {
    uint8_t   cis_id;                                     /**< Identifies an AIR HID CIS and is set by the master's Host and passed to the slave's Host through the Link Layers during the process of establishing an AIR HID CIS. */
    uint8_t   slave_type;                                 /**< The type of slave device . */
    uint32_t  sdu_interval_m_to_s : 24;                   /**< The interval, in microseconds, of periodic SDUs. (0x000FF to 0xFFFFF) */
    uint32_t  sdu_interval_s_to_m : 24;                   /**< The interval, in microseconds, of periodic SDUs. (0x000FF to 0xFFFFF) */
    uint8_t   share_num;                                  /**< The maximum number of times that every CIS Data PDU should be retransmitted. */
    uint8_t   max_uplink_num;                             /**< The max uplink number in the AIR HID CIG*/
    uint16_t  max_sdu_m_to_s;                             /**< The maximum size of an SDU from the master's Host. */
    uint16_t  max_sdu_s_to_m;                             /**< The maximum size of an SDU from the slave's Host. */
    uint8_t   phy_m_to_s;                                 /**< identifies which PHY to use for transmission from the master to the slave. */
    uint8_t   phy_s_to_m;                                 /**< identifies which PHY to use for transmission from the slave to the master. */
    uint8_t   ft_m_to_s;                                  /**< The flush timeout in multiples of ISO_Interval for each payload sent from the master to slave. (0x01 to 0xFF) */
    uint8_t   ft_s_to_m;                                  /**< The flush timeout in multiples of ISO_Interval for each payload sent from the slave to master. (0x01 to 0xFF) */
} __packed bt_ull_le_air_hid_cis_params_t;

/**
 *  @brief      The structure definition for the command to set AIR HID CIG parameters.
 */
typedef struct {
    uint8_t  cig_id;                                      /**< Identifies a AIR HID CIG. This parameter is allocated by the master's Host and passed to the slave's Host through the Link Layers during the process of establishing a AIR HID CIS. */
    uint8_t  scnario;                                     /**< Current scnario.*/
    uint16_t slave_latency;                               /**< The defualt latency of slave device.*/
    uint8_t  d4_sub_event;                                /**< The defualt sub event.*/
    uint16_t iso_interval;                                /**< The time between two consecutive anchor points. (Time = N * us.)*/
    uint8_t  cis_count;                                   /**< Total number of CISes in the AIR HID CIG being added or modified. The maximum value is limited to 16. */
    bt_ull_le_air_hid_cis_params_t *cis_list;             /**< The parameters of each AIR HID CIS list in the AIR HID CIG. */
} __packed bt_ull_le_set_air_hid_cig_t;

/**
 * @brief       The structure definition parameters for AIR HID CISes of #bt_ull_le_set_air_hid_cig_cnf_t.
 */
typedef struct {
    uint16_t cis_connection_handle;                    /**< Connection handles of the CISes. */
    uint8_t     cis_id;                                   /**< identifies an AIR HID CIS*/
} __packed bt_ull_le_set_air_hid_cis_info_t;

/**
 * @brief       LE set AIR HID CIG parameters complete event.
 */
typedef struct {
    uint8_t status;                               /**< Status. */
    uint8_t         cig_id;                               /**< Identifies a AIR HID CIG. This parameter is allocated by the master's Host and passed to the slave's Host through the Link Layers during the process of establishing a AIR HID CIS. */
    uint8_t         cis_count;                            /**< Total count of the AIR HID CISes.*/
    bt_ull_le_set_air_hid_cis_info_t    cis_info[1];      /**< Connection info of the AIR HID CISes. */
} __packed bt_ull_le_set_air_hid_cig_cnf_t;

/**
 * @brief       The structure definition for AIR HID CIS connection parameters of #bt_ull_le_create_air_hid_cis_params_t.
 */
typedef struct {
    uint8_t     uni_aa[4];                                /**< Universal vendor access address. */
    bt_addr_le_t   peer_addr;                                /**< Address information of the remote device. */
} __packed bt_ull_le_air_hid_cis_dev_info_t;

/**
 * @brief       The structure definition for sub parameters of #bt_ull_le_create_air_hid_cis_t.
 */
typedef struct {
    uint16_t    cis_connection_handle;                    /**< Connection handles of the AIR HID CIS.*/
    uint16_t    connection_timeout;                       /**< Supervision timeout of AIR HID CIS.  unit: N * 10ms.*/
    uint8_t     dev_count;                                /**< Total number of devices to connect. The maximum value is limited to 3. */
    uint8_t     dev_list[1];                              /**< The dynamic buffer of #bt_ull_le_air_hid_cis_dev_info_t*/
} __packed bt_ull_le_create_air_hid_cis_params_t;

/**
 * @brief       The structure definition for the command to create AIR HID CIS parameters.
 */
typedef struct {
    uint16_t    create_timeout;                           /**< The create AIR HID CIS tiemout. unit: N * 10ms. */
    uint8_t     ltk[16];                                  /**< The long term key of AIR HID CISes. */
    uint8_t     skd[16];                                  /**< The session key diversifier of AIR HID CISes. */
    uint8_t     iv[8];                                    /**< The initialization vector of AIR HID CISes. */
    uint16_t    usb_tx_rsvd_anchor;                       /**< The USB TX reserved anchor, Uint: us. */
    uint8_t     cis_count;                                /**< The number of AIR HID CISes*/
    uint8_t     cis_list[1];                              /**< The dynamic buffer of #bt_ull_le_create_air_hid_cis_params_t. */
} __packed bt_ull_le_create_air_hid_cis_t;

/**
 * @brief       The structure definition for the command to sync AIR HID CIS parameters.
 */
typedef struct {
    uint16_t    sync_timeout;                             /**< The sync AIR HID CIS tiemout. unit: N * 10ms. */
    uint16_t    connection_timeout;                       /**< Supervision timeout of AIR HID CIS.  unit: N * 10ms.*/
    uint8_t     ltk[16];                                  /**< The long term key of AIR HID CISes. */
    uint8_t     skd[16];                                  /**< The session key diversifier of AIR HID CISes. */
    uint8_t     iv[8];                                    /**< The initialization vector of AIR HID CISes. */
    uint8_t     slave_type;                               /**< The type of slave device . */
    uint8_t     uni_aa[4];                                /**< Universal vendor access address. */
    bt_addr_le_t   peer_addr;                             /**< Address information of the remote device. */
    uint8_t     scenario;                                 /**< The version of HID. */
    uint16_t    hid_tx_rsvd_anchor[7];                    /**< Anchor handle of reserved TX for all RR[125--8K][0--6] Uint: us. */
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    uint16_t        adv_interval;                         /**< The advertising interval of the device. */
    uint8_t         adv_data_len;                         /**< The length of the advertising data. */
    uint8_t         adv_data[0];                          /**< The pointer to the advertising data: n*(type+data_len+data) */
#endif
} __packed bt_ull_le_sync_air_hid_cis_t;

/**
 * @brief       The structure definition for the command to Set Tx power parameters.
 */
typedef struct {
    uint16_t    handle;                             /**< The connection handle. */
    int8_t      remote_tx_power_control;            /**< The remote tx power control. [bit0:6]:step of 0.5dBm. [bit7]:0:increase, 1:decrease. */
} __packed bt_ull_le_set_air_hid_cis_tx_power_t;

/**
 * @brief       The structure definition for the command to Set local Tx Gain Control parameters.
 */
typedef struct {
    uint8_t     local_tx_gc;                        /**< The local tx gain control. lookup TXGC-TXPower table*/
} __packed bt_ull_le_set_air_hid_cis_local_tx_gc_t;

/**
 * @brief       The structure definition for the command to Set Remote Tx power parameters.
 */
typedef struct {
    uint16_t    handle;                             /**< The CIS connection handle. */
    uint8_t     tx_gc;                              /**< The remote tx gain control. lookup TXGC-TXPower table*/
    uint8_t     pa_vol;                             /**< The PA voltage. */
} __packed bt_ull_le_set_air_hid_cis_remote_tx_power_t;

/**
 * @brief       The structure definition for the command to Get Conn Info parameters.
 */
typedef struct {
    uint16_t    handle;                             /**< The connection handle. */
    uint8_t     update_period;                      /**< The interval of conn information update.[n*500ms] */
} __packed bt_ull_le_get_air_hid_cis_conn_info_t;

/**
 * @brief       The structure definition for the command to Get Conn Info parameters.
 */
typedef struct {
    uint8_t     enable;
    uint16_t    scan_interval;                            /**< The Scan interval. */
    uint16_t    scan_window;                              /**< The Scan window. */
    uint8_t     uni_aa[4];                                /**< The Uniaa value.  */
} __packed bt_ull_le_enable_air_hid_cis_scan_t;

/**
 * @brief       The structure definition for the event of AIR HID CIS established.
 */
typedef struct {
    uint8_t           status;                             /**< The status of the AIR CIS. */
    uint16_t          acl_connection_handle;              /**< Pseudo connection handle of the LE ACL. */
    uint16_t          cis_connection_handle;              /**< Connection handle of the AIR CIS. */
    uint8_t           cis_id;                             /**< Identifies an AIR CIS and is set by the master's Host and passed to the slave's Host through the Link Layers during the process of establishing an AIR CIS. */
    uint8_t           slave_type;                         /**< The type of slave device . */
    uint8_t           uni_aa[4];                          /**< Universal vendor access address. */
    bt_addr_le_t      peer_aadr;                          /**< Address information of the remote device. */
    uint16_t          iso_interval;                       /**< The time between two consecutive AIR CIS anchor points.*/
} __packed bt_ull_le_air_hid_cis_established_ind_t;

/**
 * @brief       The structure definition for the command to cancel create AIR HID CIS parameters.
 */
typedef struct {
    uint16_t    cis_handle;                               /**< Connection handles of the CISes. */
    uint8_t     reason;                                   /**< The reason to cancel. */
} __packed bt_ull_le_cancel_create_air_hid_cis_params_t;

/**
 * @brief       The structure definition for the command to disconnect AIR HID CIS parameters.
 */
typedef struct {
    uint16_t  connection_handle; /**< The connection handle to disconnect. */
    uint8_t  reason;            /**< The reason to disconnect. */
} __packed bt_ull_le_air_hid_cis_disconnect_t;

/**
 *  @brief      The structure definition for the command to remove the AIR HID CIG parameters.
 */
typedef struct {
    uint8_t cig_id;                                     /**< Identifies an AIR CIG. */
} __packed bt_ull_le_remove_air_hid_cig_t;

/************************************************************event ind**************************************************************************************/
/**
 *  @brief      The structure definition for the event of AIR HID CIS disconnect complete parameters.
 */
typedef struct {
    uint8_t        status;                           /**< Status. */
    uint16_t       cis_connection_handle;            /**< AIR CIS connection handle. */
    uint8_t        reason;                           /**< Disconnect reason. */
} __packed bt_ull_le_air_hid_cis_disconnect_complete_ind_t;

/**
 *  @brief      The structure definition for the event of BT_ULL_LE_SET_AIR_HID_REPORT_RATE_CHANGE_IND parameters.
 */
typedef struct {
    uint8_t     status;                           /**< Status. */
    uint8_t     cig_id;
    uint8_t     report_rate_level;
    uint8_t     phy;
}__packed bt_ull_le_air_hid_report_rate_change_ind;

/**
 *  @brief      The structure definition for the event of BT_ULL_LE_SET_AIR_HID_CIS_ADV_REPORT_IND parameters.
 */
typedef struct {
    uint8_t     adv_data_len;                           /**< Status. */
    uint8_t     adv_data[0];
}__packed bt_ull_le_air_hid_cis_adv_report_ind;

/**
 *  @brief      The structure definition for the event of BT_ULL_LE_SET_AIR_HID_CIS_CONN_INFO_IND parameters.
 */
typedef struct {
    uint8_t     status;                                 /**< Status. */
    uint16_t    handle;
    uint8_t     phy;
    int8_t      tx_power;                                /**< TX power. Range: -128 to 127*/
    int8_t      rx_rssi;                                 /**< RX RSSI. Range: -128 to 127*/
    uint32_t    wb_duration;                             /**< WB duration. Uint: 312.5us*/
    int8_t      wb_rssi[BT_CHANNEL_NUMBER];              /**< WB RSSI.  -128 to 127*/
    uint16_t    PER[BT_CHANNEL_NUMBER];                  /**< PER. Range: 0 to 0x3E8; 0x64:10%, 0xC8:20%; Uint: 0.1%*/
    uint8_t     channel_map[BT_CHANNEL_NUMBER/8];        /**< channel map. Range: 0 to 0x39; 0: channel is unused, 1: channel is used*/
}__packed bt_ull_le_air_hid_conn_info_ind_t;
/***********************************************************************************************************************************************************/

/******************************************************cmd compelet or command status cnf**********************************************************************/
/**
 * @brief This structure defines the associated parameter type in the callback for #BT_ULL_LE_REMOVE_AIR_HID_CIG_CNF event.
 */
/**
 * @brief       LE remove Air HID CIG complete event.
 */
typedef struct {
    uint8_t     status;                     /**< Status. */
    uint8_t     cig_id;                     /**< CIG id. */
} __packed bt_ull_le_remove_air_hid_cig_cnf_t;

/**
 * @brief       The structure definition for the command to switch report rate.
 */
typedef struct {
    uint16_t    cis_handle;                               /**< The handle of the CIS for which the report rate is to be switched. */
    uint8_t     cig_id;                                   /**< Identifies a AIR HID CIG. This parameter is allocated by the master's Host and passed to the slave's Host through the Link Layers during the process of establishing a AIR HID CIS. */
    uint8_t     Used_SE;                                  /**< Reserved.*/
    uint8_t     report_rate;                              /**< The report rate to be switched. */
    uint8_t     phy;                                      /**< PHY type used in the connection. */
}__packed bt_ull_le_change_air_hid_cis_report_rate_t;

/**
 * @brief       The structure definition for the command to set peripheral.
 */
typedef struct {
    uint16_t    connection_handle;                               /**< The ACL handle of the CIS for set peripheral. */
    uint8_t     enable;                                   /**< Enable or Disable peripheral. */
}__packed bt_ull_le_set_peripheral_t;

/***********************************************************************************************************************************************************************************/
typedef int (*bt_ull_le_event_cb)(uint32_t msg, int ret, void *data);

void bt_ull_le_register_cb(bt_ull_le_event_cb cb);

/**
 * @brief    This function init bt ull profile.
 */
void bt_ull_le_init(void);

/**
 * @brief    This function deinit bt ull profile.
 */
void bt_ull_le_deinit(void);

/*******************************************************************************************************************************************************************************
* 
* Define AIR HID CIS APIS
*
*******************************************************************************************************************************************************************************/

/**
 * @brief     This function set AIR HID CIG.
 * @param[in] params             is the parameters to set air hid cig #bt_ull_le_set_air_hid_cig_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_set_air_hid_cig_parameters(bt_ull_le_set_air_hid_cig_t *params);

/**
 * @brief     This function removes AIR HID CIG.
 * @param[in] params             is the parameters to set air hid cig #bt_ull_le_remove_air_hid_cig_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_remove_air_hid_cig_parameters(bt_ull_le_remove_air_hid_cig_t *params);

/**
 * @brief     This function creates AIR HID CIS.
 * @param[in] params             is the parameters to set air hid cig #bt_ull_le_create_air_hid_cis_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_create_air_hid_cis(bt_ull_le_create_air_hid_cis_t *params);

/**
 * @brief     This function sync AIR HID CIS.
 * @param[in] params             is the parameters to set air hid cig #bt_ull_le_sync_air_hid_cis_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_sync_air_hid_cis(bt_ull_le_sync_air_hid_cis_t *params);

/**
 * @brief     This function disconnects the AIR HID CIS.
 * @param[in] disconnect         is the disconnect air cis parameters #bt_ull_le_air_hid_cis_disconnect_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_disconnect_air_hid_cis(bt_ull_le_air_hid_cis_disconnect_t *disconnect);

/**
 * @brief     This function cancel creating AIR HID CIS.
 * @param[in] params             is the parameters to set air hid cig #bt_ull_le_cancel_create_air_hid_cis_params_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_cancel_creating_air_hid_cis(bt_ull_le_cancel_create_air_hid_cis_params_t *params);

/**
 * @brief     This function cancel sync AIR HID CIS.
 * @param[in] params            void.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_cancel_sync_air_hid_cis(void);

/**
 * @brief     This function set hid report rate.
 * @param[in] params             is the parameters to set air hid cig #bt_ull_le_change_air_hid_cis_report_rate_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_set_report_rate(bt_ull_le_change_air_hid_cis_report_rate_t *params);

/**
 * @brief     This function set peripheral.
 * @param[in] params             is the parameters to set air hid cig #bt_ull_le_set_peripheral_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_set_peripheral(bt_ull_le_set_peripheral_t *params);

#if defined(CONFIG_ULL_HID_LE_CENTRAL)
/**
 * @brief     This function get connection info.
 * @param[in] params             is the parameters to get connection info #bt_ull_le_get_air_hid_cis_conn_info_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_get_connection_info(bt_ull_le_get_air_hid_cis_conn_info_t *params);

/**
 * @brief     This function set tx power.
 * @param[in] params             is the parameters to set tx power #bt_ull_le_set_air_hid_cis_tx_power_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_set_tx_power(bt_ull_le_set_air_hid_cis_tx_power_t *params);

/**
 * @brief     This function set local tx gain control.
 * @param[in] params             is the parameters to set tx power #bt_ull_le_set_air_hid_cis_local_tx_gc_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_set_tx_local_tx_gc(bt_ull_le_set_air_hid_cis_local_tx_gc_t *params);

/**
 * @brief     This function set tx power.
 * @param[in] params             is the parameters to set tx power #bt_ull_le_set_air_hid_cis_remote_tx_power_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_set_remote_tx_power(bt_ull_le_set_air_hid_cis_remote_tx_power_t *params);

/**
 * @brief     This function enable cis scan.
 * @param[in] params             is the parameters to set phy #bt_ull_le_enable_air_hid_cis_scan_t.
 * @return                       #0, the operation completed successfully.
 *                               #otherwise, the operation has failed.
 */
int bt_ull_le_enbale_cis_scan(bt_ull_le_enable_air_hid_cis_scan_t *params);

#endif

/**
 * @brief     This function free AIR HID CIS conn.
 * @param[in] role               is server or client.
 * @return                       NULL
 */
void bt_ull_le_free_air_hid_cis_conn(bt_ull_role_t role);
/***********************************************************************************************************************************************************************************/
/**
 * @}
 * @}
 */

#endif

