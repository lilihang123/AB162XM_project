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

#include "bt_ull_le_hid_conn_service.h"
#include "bt_ull_le_hid_device_manager.h"
#include "zephyr/logging/log.h"

LOG_MODULE_DECLARE(ULL_HID);

#define BT_ULL_LE_HID_CONN_SRV_DEBUG

#define BT_ULL_LE_HID_CONN_LOG   "[ULL][HID][CONN]"

#define MAKE_CMD_PARAM(N, T) T *N = (T*)k_malloc(sizeof(T))
#define BT_ULL_LE_HID_MAKE_CMD_PARAM(name, CMD) MAKE_CMD_PARAM(name, CMD##_T)
#define BT_ULL_LE_HID_GET_CMD_PARAM_LEN(CMD) sizeof(CMD##_T)
#define BT_ULL_LE_HID_GET_CMD_PARAM(CMD, node) (CMD##_T *)node->cache_item.data
#define BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM                  0x03
#define BT_ULL_LE_HID_CONN_SRV_INVALID                     (0xFF)
#define BT_ULL_LE_HID_CONN_SRV_LOCK                        (0x01)

#define BT_ULL_LE_HID_REPORT_RATE_NUMBER                    (0x07)

#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_100             (100U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_108             (108U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_190             (190U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_126             (126U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_63              (63U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_200             (200U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_158             (158U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_350             (350U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_588             (588U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_170             (170U)
#define BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_250             (250U)

#define BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_20                (20U)
#define BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_25                (25U)
#define BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_40                (40U)
#define BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_65                (65U)


#define BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED        (0x00)
#define BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING          (0x01)
#define BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CANCEL_CONNECTING   (0x02)
#define BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTED           (0x03)
#define BT_ULL_LE_HID_CONN_SRV_AIR_CIS_SET_DATA_PATH       (0x04)
#define BT_ULL_LE_HID_CONN_SRV_AIR_CIS_STREAMING           (0x05)
#define BT_ULL_LE_HID_CONN_SRV_AIR_CIS_REMOVE_DATA_PATH    (0x06)
#define BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTING       (0x07)
#define BT_ULL_LE_HID_CONN_SRV_AIR_CIS_STATE_MAX           (0x08)
typedef uint8_t bt_ull_le_hid_conn_srv_air_cis_state_t;

#define BT_ULL_LE_HID_CONN_SRV_CIG_STATE_NONE              (0x00)
#define BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATING          (0x01)
#define BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATED           (0x02)
#define BT_ULL_LE_HID_CONN_SRV_CIG_STATE_REMOVING          (0x03)
typedef uint8_t bt_ull_le_hid_conn_srv_cig_state_t;

#define BT_ULL_LE_HID_CONN_SRV_CIG_ID_NONE                 (0x00)    /* none */
#define BT_ULL_LE_HID_CONN_SRV_CIG_ID_1                    (0x01)    /* unidirectional (c->s) */

#define BT_ULL_LE_HID_CONN_SRV_FT_0                        (0x00)
#define BT_ULL_LE_HID_CONN_SRV_FT_1                        (0x01)
#define BT_ULL_LE_HID_CONN_SRV_FT_2                        (0x02)
#define BT_ULL_LE_HID_CONN_SRV_FT_3                        (0x03)
#define BT_ULL_LE_HID_CONN_SRV_FT_4                        (0x04)
#define BT_ULL_LE_HID_CONN_SRV_FT_5                        (0x05)
typedef uint8_t bt_ull_le_conn_srv_flush_timeout_t; /*times*/


typedef uint16_t bt_ull_le_hid_conn_srv_cmd_lock;

#define BT_ULL_LE_SRV_DATA_PATH_ID_HCI            (0x00)
#define BT_ULL_LE_SRV_DATA_PATH_ID_1              (0x01)
#define BT_ULL_LE_SRV_DATA_PATH_ID_2              (0x02)
// for wireless mic
#define BT_ULL_LE_SRV_DATA_PATH_ID_3              (0x03)
#define BT_ULL_LE_SRV_DATA_PATH_ID_4              (0x04)
#define BT_ULL_LE_SRV_DATA_PATH_ID_SPK_SPECIAL    (0x30)
#define BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE        (0xFF)
typedef uint8_t bt_ull_le_srv_iso_data_path_t;

typedef enum {
    BT_ULL_LE_SRV_AIR_CIS_ID_INVALID = 0x00,
    BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,                /* Left, for media streaming, cis_info[0] */
    BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,               /* Right, for media streaming, cis_info[1]*/
    BT_ULL_LE_SRV_AIR_CIS_ID_SINK3,                /* for mic streaming, cis_info[0] */
    BT_ULL_LEN_SRV_AIR_CIS_ID_SINK4,                /* for mic streaming, cis_info[1]  */
    BT_ULL_LE_SRV_AIR_CIS_ID_MAX
} bt_ull_le_srv_air_cis_id_enum;

typedef struct {
    uint8_t           cis_id;
    uint8_t           device_type;
    uint16_t          cis_handle;
    uint16_t          acl_handle;
    uint8_t           state;
    uint32_t          conn_to;
    bt_addr_le_t         peer_addr;
} bt_ull_le_hid_conn_srv_cis_link_t;

typedef enum {
    BT_ULL_LE_HID_CONN_SRV_CMD_REMOVE_CIG,
    BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS,
    BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS,
    BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS,
    BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS,
    BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS,
    BT_ULL_LE_HID_CONN_SRV_CMD_MAX
} bt_ull_le_hid_conn_srv_cmd_enum;

typedef struct {
    bt_ull_le_hid_conn_srv_cmd_enum cmd;
    uint16_t                        data_len;
    void                            *data;
} bt_ull_le_hid_conn_srv_cmd_cache_item_t;

typedef struct bt_ull_le_hid_conn_srv_cache_cmd_node_t bt_ull_le_hid_conn_srv_cache_cmd_node_t;
struct bt_ull_le_hid_conn_srv_cache_cmd_node_t {
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *next;
    bt_ull_le_hid_conn_srv_cmd_cache_item_t cache_item;
};

typedef struct {
    bt_ull_le_hid_conn_srv_cmd_enum cmd;
    bt_ull_le_hid_conn_srv_cmd_lock lock;
} bt_ull_le_hid_conn_srv_cmd_lock_t;

typedef struct {
    bt_ull_le_hid_srv_device_t device_type;
} BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS_T, BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS_T;

typedef struct {
    uint16_t                acl_handle;
    uint8_t                    reason;
} BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS_T;

typedef struct {
    bt_ull_le_hid_srv_device_t device_type;
    bt_addr_le_t                  peer_addr;
} BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS_T;

typedef struct {
    uint8_t data;
} BT_ULL_LE_HID_CONN_SRV_CMD_REMOVE_CIG_T;

typedef struct {
    bt_ull_le_hid_srv_conn_params_t *kb;
    bt_ull_le_hid_srv_conn_params_t *ms;
    bt_ull_le_hid_srv_conn_params_t *gp;
} BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS_T;

typedef struct {
    uint8_t                                  cig_id;
    uint8_t                                  cis_count; /*set by ull le service*/
    uint8_t                                  cig_state;
    bt_ull_le_srv_phy_t                      phy;
    bt_ull_le_hid_srv_app_scenario_t         scenario;
    bt_ull_le_hid_srv_idle_time_t            idle_time;
    uint8_t                                  rr_level;
    bt_ull_role_t                            role;
    bt_ull_le_hid_srv_report_rate_t          report_rate;
    bt_ull_le_hid_conn_srv_callback_t            cb;
    bt_ull_le_hid_conn_srv_cache_cmd_node_t  *cmd_list_header;
    bt_ull_le_hid_conn_srv_cis_link_t        cis_info[BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM];
} bt_ull_le_hid_conn_srv_contex_t;

typedef struct {
    bt_ull_le_hid_srv_device_t              dev_type;
    uint8_t                                 cis_id;
    uint8_t                                 data_path_id;
    uint32_t                                sdu_interval_m_to_s;
    uint32_t                                sdu_interval_s_to_m;
    uint8_t                                 share_num;
    uint8_t                                 uplink_num;
    uint32_t                                sdu_m_to_s;
    uint32_t                                sdu_s_to_m;
    bt_ull_le_srv_phy_t                     phy_m_to_s;
    bt_ull_le_srv_phy_t                     phy_s_to_m;
    uint8_t                                 ft_m_to_s;
    uint8_t                                 ft_s_to_m;
} bt_ull_le_hid_conn_srv_dev_params_t;

typedef struct {
    bt_ull_le_hid_srv_app_scenario_t        scenario;
    uint16_t                                slave_latency;
    uint32_t                                iso_interval;
    uint8_t                                 default_se;
    uint8_t                                 cis_count;
    bt_ull_le_hid_conn_srv_dev_params_t     tab[3];
} bt_ull_le_hid_conn_srv_cig_params_t;

static bt_ull_le_hid_conn_srv_contex_t g_ull_hid_srv_ctx;
static uint16_t g_ull_hid_conn_timeout = 100;

static bt_ull_le_hid_conn_srv_cmd_lock_t g_bt_ull_hid_cmd_lock_table[BT_ULL_LE_HID_CONN_SRV_CMD_MAX + 1] = {
    {BT_ULL_LE_HID_CONN_SRV_CMD_REMOVE_CIG, 0},
    {BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS, 0},
    {BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS, 0},
    {BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS, 0},
    {BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS, 0},
    {BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS, 0},
    {BT_ULL_LE_HID_CONN_SRV_CMD_MAX, 0} /*max*/
};
#if defined(CONFIG_ULL_HID_LE_CENTRAL)
static uint16_t g_ull_hid_usb_tx_anchor = 0;
static uint16_t g_ull_hid_create_cis_timeout = 0;
#define BT_ULL_LE_HID_CONN_SRV_AIR_PARAMS_MAX_NUM           16
const bt_ull_le_hid_conn_srv_cig_params_t g_air_cig_params_tab[BT_ULL_LE_HID_CONN_SRV_AIR_PARAMS_MAX_NUM] = {
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_1,
        0x0,
        5000,
        0x3,
        0x3,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_HEADSET,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_SPK_SPECIAL,
                5000,
                5000,
                0x02,
                0x01,
                BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_126,
                BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_20,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                5000,
                5000,
                0x02,
                0x02,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK3,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                5000,
                5000,
                0x02,
                0x02,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            }
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_2,
        0x0,
        5000,
        3,
        3,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_HEADSET,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_SPK_SPECIAL,
                5000,
                5000,
                0x02,
                0x01,
                0x35,
                14,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                5000,
                5000,
                0x02,
                0x01,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK3,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                5000,
                5000,
                0x02,
                0x01,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            }
        }

    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_3,
        0x0,
        664,
        0x1,
        0x2,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                664,
                664,
                0x01,
                0x01,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                664,
                664,
                0x01,
                0x02,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0}
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_4,
        0x20,
        500,
        0x1,
        0x1,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                500,
                500,
                0x01,
                0x02,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0},
            {0}
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_5,
        0x10,
        1000,
        0x1,
        0x2,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                1000,
                1000,
                0x01,
                0x02,
                0x2F,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                1000,
                1000,
                0x01,
                0x02,
                0x2F,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0}
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_6,
        0x8,
        2000,
        0x1,
        0x2,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                2000,
                2000,
                0x01,
                0x02,
                0x86,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                2000,
                2000,
                0x01,
                0x02,
                0x86,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0}
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_7,
        0x8,
        2000,
        0x1,
        0x2,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                2000,
                2000,
                0x01,
                0x01,
                0x86,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                2000,
                2000,
                0x01,
                0x01,
                0x86,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0}
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_8,
        0x4,
        2000,
        0x1,
        0x2,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                2000,
                2000,
                0x01,
                0x01,
                0x86,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                2000,
                2000,
                0x01,
                0x01,
                0x86,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0}
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_9,
        0x2,
        2000,
        0x1,
        0x2,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                2000,
                2000,
                0x01,
                0x01,
                0x86,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                2000,
                2000,
                0x01,
                0x01,
                0x86,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0}
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_10,
        0x0,
        5000,
        0x1,
        0x3,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_HEADSET,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_SPK_SPECIAL,
                5000,
                5000,
                0x01,
                0x01,
                BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_100,
                BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_20,
                BT_ULL_LE_SRV_PHY_EDR_LE_4M,
                BT_ULL_LE_SRV_PHY_EDR_LE_4M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                1000,
                1000,
                0x01,
                0x01,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK3,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                1000,
                1000,
                0x01,
                0x01,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            }
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_11,
        0x0,
        5000,
        0x1,
        0x3,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_HEADSET,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_SPK_SPECIAL,
                5000,
                5000,
                0x01,
                0x01,
                BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_190,
                BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_40,
                BT_ULL_LE_SRV_PHY_EDR_LE_8M,
                BT_ULL_LE_SRV_PHY_EDR_LE_8M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                1000,
                1000,
                0x01,
                0x01,
                0x1E,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK3,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                1000,
                1000,
                0x01,
                0x01,
                0x1E,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            }
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_12,
        0x0,
        5000,
        0x1,
        0x2,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_HEADSET,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_SPK_SPECIAL,
                5000,
                5000,
                0x01,
                0x01,
                BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_100,
                BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_20,
                BT_ULL_LE_SRV_PHY_EDR_LE_4M,
                BT_ULL_LE_SRV_PHY_EDR_LE_4M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                1000,
                1000,
                0x01,
                0x01,
                0x18,
                0x14,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0}
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_13,
        0x0,
        5000,
        0x1,
        0x2,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_HEADSET,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_SPK_SPECIAL,
                5000,
                5000,
                0x01,
                0x01,
                BT_ULL_LE_DEFAULT_DOWNLINK_SDU_SIZE_190,
                BT_ULL_LE_DEFAULT_UPLINK_SDU_SIZE_40,
                BT_ULL_LE_SRV_PHY_EDR_LE_8M,
                BT_ULL_LE_SRV_PHY_EDR_LE_8M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK2,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                1000,
                1000,
                0x01,
                0x01,
                0x28,
                0x14,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_SRV_PHY_LE_2M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0}
        }
    },
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_81,
        0x20,
        500,
        0x1,
        0x1,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_MOUSE,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                500,
                500,
                0x01,
                0x01,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_4M,
                BT_ULL_LE_SRV_PHY_LE_4M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0},
            {0}
        }
    },    
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_82,
        0x20,
        500,
        0x1,
        0x1,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                500,
                500,
                0x01,
                0x01,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_4M,
                BT_ULL_LE_SRV_PHY_LE_4M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0},
            {0}
        }
    },    
    {
        BT_ULL_LE_HID_SRV_APP_SCENARIO_83,
        0x20,
        500,
        0x1,
        0x1,
        {
            {
                BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD,
                BT_ULL_LE_SRV_AIR_CIS_ID_SINK1,
                BT_ULL_LE_SRV_DATA_PATH_ID_DISABLE,
                500,
                500,
                0x01,
                0x01,
                0x7,
                0x7,
                BT_ULL_LE_SRV_PHY_LE_4M,
                BT_ULL_LE_SRV_PHY_LE_4M,
                BT_ULL_LE_HID_CONN_SRV_FT_1,
                BT_ULL_LE_HID_CONN_SRV_FT_1
            },
            {0},
            {0}
        }
    }
};
#endif
#if defined(CONFIG_ULL_HID_LE_CENTRAL)
static void bt_ull_le_hid_conn_srv_create_cig_params_cnf_hdl(int status, bt_ull_le_set_air_hid_cig_cnf_t *cnf);
static uint8_t bt_ull_le_hid_conn_srv_get_sub_event(uint8_t report_rate);
static void bt_ull_le_hid_conn_srv_remove_cig_params_cnf_hdl(int status, bt_ull_le_remove_air_hid_cig_cnf_t *cnf);
static void bt_ull_le_hid_conn_srv_create_cis_cnf_hdl(int status, void *cnf);
static void bt_ull_le_hid_conn_srv_cancel_create_cnf_hdl(int status, void *cnf);
static const bt_ull_le_hid_conn_srv_cig_params_t * bt_ull_le_hid_conn_srv_get_cig_params(bt_ull_le_hid_srv_app_scenario_t scenario);
#endif
#if defined (CONFIG_ULL_HID_LE_PERIPHERAL)
static uint16_t g_ull_hid_hid_tx_anchor[BT_ULL_LE_HID_REPORT_RATE_NUMBER] = {0};
static uint16_t g_ull_hid_sync_cis_timeout = 0;
static void bt_ull_le_hid_conn_srv_sync_cis_cnf_hdl(int status, void *cnf);
static void bt_ull_le_hid_conn_srv_cancel_sync_cnf_hdl(int status, void *cnf);
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
static uint16_t g_ull_hid_sync_adv_interval = 0;
static struct bt_data *g_ull_hid_sync_adv_data = NULL;
static uint8_t g_ull_hid_sync_adv_num = 0;
#endif
#endif
static void bt_ull_le_hid_conn_srv_notify_msg(bt_ull_le_hid_conn_srv_msg_t msg, void *data);
static void bt_ull_le_hid_conn_srv_cis_established_hdl(int status, bt_ull_le_air_hid_cis_established_ind_t *ind);
static void bt_ull_le_hid_conn_srv_cis_disconnect_complete_hdl(int status, bt_ull_le_air_hid_cis_disconnect_complete_ind_t *ind);
static void bt_ull_le_hid_conn_srv_disconnect_cis_cnf_hdl(int status, void *cnf);
static int bt_ull_le_hid_conn_srv_next_action_hdl(bt_ull_le_hid_conn_srv_cmd_enum next_act, void *data);
static int bt_ull_le_hid_conn_srv_event_callback(uint32_t msg, int ret, void *data);


#if defined(CONFIG_ULL_HID_LE_CENTRAL)
void bt_ull_le_hid_conn_srv_set_create_cis_timeout(uint16_t create_cis_timeout)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_create_cis_timeout, create_cis_timeout: %d", create_cis_timeout);
    g_ull_hid_create_cis_timeout = create_cis_timeout;
}

void bt_ull_le_hid_conn_srv_set_usb_tx_anchor( uint16_t usb_tx_anchor)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_usb_tx_anchor: %d", usb_tx_anchor);
    g_ull_hid_usb_tx_anchor = usb_tx_anchor;
}

static uint8_t bt_ull_le_hid_conn_srv_get_scenario(void)
{
    return g_ull_hid_srv_ctx.scenario;
}

static uint8_t bt_ull_le_hid_conn_srv_get_idx_by_cis_id(uint8_t cis_id)
{
    uint8_t i = 0;
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
        if (g_ull_hid_srv_ctx.cis_info[i].cis_id == cis_id && cis_id != BT_ULL_LE_SRV_AIR_CIS_ID_INVALID) {
            return i;
        }
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_idx_by_cis_id, can not found link!");
    return BT_ULL_LE_HID_CONN_SRV_INVALID;
}

static void bt_ull_le_hid_conn_srv_set_conn_timout(uint8_t idx, uint32_t timeout)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_conn_timout, invalid idx!");
        return;
    }
    g_ull_hid_srv_ctx.cis_info[idx].conn_to = timeout;
}

static uint8_t bt_ull_le_hid_conn_srv_get_cig_state(void)
{
    return g_ull_hid_srv_ctx.cig_state;
}

#endif

#if defined (CONFIG_ULL_HID_LE_PERIPHERAL)
void bt_ull_le_hid_conn_srv_set_sync_cis_timeout(uint16_t sync_cis_timeout)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_sync_cis_timeout, sync_cis_timeout: %d", sync_cis_timeout);
    g_ull_hid_sync_cis_timeout = sync_cis_timeout;
}

void bt_ull_le_hid_conn_srv_set_hid_tx_anchor( uint16_t *hid_tx_anchor, uint8_t rr_num)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_usb_tx_anchor,hid_tx_anchor: 0x%x rr_num: %d", hid_tx_anchor, rr_num);
    if (BT_ULL_LE_HID_REPORT_RATE_NUMBER != rr_num || !hid_tx_anchor) {
        return;
    }
    bt_ull_le_srv_memcpy(&g_ull_hid_hid_tx_anchor[0], hid_tx_anchor, sizeof(uint16_t) * BT_ULL_LE_HID_REPORT_RATE_NUMBER);
}

#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
void bt_ull_le_hid_conn_srv_set_adv_interval(uint16_t adv_interval)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_adv_interval, adv_interval: %d", adv_interval);
    g_ull_hid_sync_adv_interval = adv_interval;
}

void bt_ull_le_hid_conn_srv_set_adv_data(struct bt_data *adv_data, uint8_t adv_data_array_size)
{
    g_ull_hid_sync_adv_num = adv_data_array_size;
    g_ull_hid_sync_adv_data = adv_data;
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_adv_data, array_size: %d, type: 0x%x, adv_data: 0x%x", 
            g_ull_hid_sync_adv_num, adv_data->type, adv_data);
}
#endif

static uint8_t bt_ull_le_hid_conn_srv_get_empty_link(void)
{
    uint8_t i = 0;
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
        if (g_ull_hid_srv_ctx.cis_info[i].state == BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED) {
            return i;
        }
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_empty_link, not resource!");
    return BT_ULL_LE_HID_CONN_SRV_INVALID;
}
#endif

static void bt_ull_le_hid_conn_srv_set_cig_state(uint8_t state)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_cig_state, cig state:0x%x -> 0x%x", g_ull_hid_srv_ctx.cig_state, state);
    g_ull_hid_srv_ctx.cig_state = state;
}

void bt_ull_le_hid_conn_srv_set_cis_connection_timeout(uint16_t conn_timeout)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_cis_connection_timeout, conn_timeout: %d", conn_timeout);
    g_ull_hid_conn_timeout = conn_timeout;
}

static bt_ull_le_hid_conn_srv_contex_t *bt_ull_le_hid_conn_srv_get_ctx(void)
{
    return &g_ull_hid_srv_ctx;
}

static void bt_ull_le_hid_conn_srv_set_phy_internal(bt_ull_le_srv_phy_t phy)
{
    g_ull_hid_srv_ctx.phy = phy;
}

static bt_ull_role_t bt_ull_le_hid_conn_srv_get_role(void)
{
    return g_ull_hid_srv_ctx.role;
}

static void bt_ull_le_hid_conn_srv_set_role(bt_ull_role_t role)
{
    g_ull_hid_srv_ctx.role = role;
}

static uint8_t bt_ull_le_hid_conn_srv_get_rr_level(void)
{
    return g_ull_hid_srv_ctx.rr_level;
}

static bt_ull_role_t bt_ull_le_hid_conn_srv_get_cig_id(void)
{
    return g_ull_hid_srv_ctx.cig_id;
}

static void bt_ull_le_hid_conn_srv_set_cig_id(uint8_t cig_id)
{
    g_ull_hid_srv_ctx.cig_id = cig_id;
}

static void bt_ull_le_hid_conn_srv_set_peer_addr(uint8_t idx, bt_addr_le_t *addr)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_peer_addr, invalid idx!");
        return;
    }
    bt_ull_le_srv_memcpy(&g_ull_hid_srv_ctx.cis_info[idx].peer_addr, addr, sizeof(bt_addr_le_t));
}

static void bt_ull_le_hid_conn_srv_set_cis_state(uint8_t idx, uint8_t state)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_cis_state, invalid idx!");
        return;
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_cis_state, idx: 0x%x, state:0x%x -> 0x%x", idx, g_ull_hid_srv_ctx.cis_info[idx].state, state);
    g_ull_hid_srv_ctx.cis_info[idx].state = state;
}

static uint8_t bt_ull_le_hid_conn_srv_get_cis_state(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_cis_state, invalid idx!");
        return BT_ULL_LE_HID_CONN_SRV_INVALID;
    }
    return g_ull_hid_srv_ctx.cis_info[idx].state;
}

static void bt_ull_le_hid_conn_srv_set_device_type(uint8_t idx, uint8_t device_type)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_device_type, invalid idx!");
        return;
    }
    g_ull_hid_srv_ctx.cis_info[idx].device_type = device_type;
}

static uint8_t bt_ull_le_hid_conn_srv_get_device_type(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_device_type, invalid idx!");
        return BT_ULL_LE_HID_CONN_SRV_INVALID;
    }
    return g_ull_hid_srv_ctx.cis_info[idx].device_type;
}

static void bt_ull_le_hid_conn_srv_set_cis_id(uint8_t idx, uint8_t cis_id)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_cis_id, invalid idx!");
        return;
    }
    g_ull_hid_srv_ctx.cis_info[idx].cis_id = cis_id;
}

static void bt_ull_le_hid_conn_srv_set_cis_handle(uint8_t idx, uint16_t handle)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_cis_handle, invalid idx!");
        return;
    }
    g_ull_hid_srv_ctx.cis_info[idx].cis_handle = handle;
}

static void bt_ull_le_hid_conn_srv_set_acl_handle(uint8_t idx, uint16_t handle)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_acl_handle, invalid idx!");
        return;
    }
    g_ull_hid_srv_ctx.cis_info[idx].acl_handle = handle;
}

static uint16_t bt_ull_le_hid_conn_srv_get_acl_handle(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_acl_handle, invalid idx!");
        return 0xFFFF;
    }
    return g_ull_hid_srv_ctx.cis_info[idx].acl_handle;
}

static uint16_t bt_ull_le_hid_conn_srv_get_cis_handle(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_cis_handle, invalid idx!");
        return 0xFFFF;
    }
    return g_ull_hid_srv_ctx.cis_info[idx].cis_handle;
}

static uint8_t bt_ull_le_hid_conn_srv_get_idx_by_cis_handle(uint16_t handle)
{
    uint8_t i = 0;
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
        if (g_ull_hid_srv_ctx.cis_info[i].cis_handle == handle) {
            return i;
        }
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_idx_by_cis_handle, can not found link!");
    return BT_ULL_LE_HID_CONN_SRV_INVALID;
}

static uint8_t bt_ull_le_hid_conn_srv_get_idx_by_acl_handle(uint16_t handle)
{
    uint8_t i = 0;
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
        if (g_ull_hid_srv_ctx.cis_info[i].acl_handle == handle) {
            return i;
        }
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_idx_by_cis_handle, can not found link!");
    return BT_ULL_LE_HID_CONN_SRV_INVALID;
}

static uint8_t bt_ull_le_hid_conn_srv_get_idx_by_type(uint8_t device_type)
{
    uint8_t i = 0;
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
        if (g_ull_hid_srv_ctx.cis_info[i].device_type == device_type) {
            return i;
        }
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_idx_by_type, invalid cis type!");
    return BT_ULL_LE_HID_CONN_SRV_INVALID;
}

static uint8_t bt_ull_le_hid_conn_srv_get_connected_link(void)
{
    uint8_t i = 0;
    uint8_t count = 0;
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
        if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTED <= g_ull_hid_srv_ctx.cis_info[i].state \
            && BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTING >= g_ull_hid_srv_ctx.cis_info[i].state) {
            count ++;
        }
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_connected_link, count = %d", count);
    return count;
}

static bool bt_ull_le_hid_conn_srv_cis_link_is_connectded(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cis_link_is_connectded, invalid idx!");
        return false;
    }

    if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTED <= g_ull_hid_srv_ctx.cis_info[idx].state \
        && BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTING >= g_ull_hid_srv_ctx.cis_info[idx].state) {
        return true;
    }
    return false;
}

static void bt_ull_le_hid_conn_srv_unlock_cmd(bt_ull_le_hid_conn_srv_cmd_enum cmd)
{
    uint8_t i = 0;
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_unlock_cmd, type: 0x%x", cmd);
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CMD_MAX ; i ++) {
        if (g_bt_ull_hid_cmd_lock_table[i].cmd == cmd) {
            g_bt_ull_hid_cmd_lock_table[i].lock = 0;
        }
    }
}

static void bt_ull_le_hid_conn_srv_lock_cmd(bt_ull_le_hid_conn_srv_cmd_enum cmd, uint16_t lock)
{
    uint8_t i = 0;
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_lock_cmd, type: 0x%x", cmd);
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CMD_MAX ; i ++) {
        if (g_bt_ull_hid_cmd_lock_table[i].cmd == cmd) {
            g_bt_ull_hid_cmd_lock_table[i].lock = lock;
        }
    }
}

static bt_ull_le_hid_conn_srv_cmd_cache_item_t* bt_ull_le_hid_conn_srv_create_cmd_node(bt_ull_le_hid_conn_srv_cmd_enum cmd)
{
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *node;
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *new_node;
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *last_node;
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_cache_cmd_node, type: 0x%x", cmd);
    new_node = (bt_ull_le_hid_conn_srv_cache_cmd_node_t *)bt_ull_le_srv_memory_alloc(sizeof(bt_ull_le_hid_conn_srv_cache_cmd_node_t));
    if (NULL == new_node) {
        return NULL;
    }
    bt_ull_le_srv_memset(new_node, 0, sizeof(bt_ull_le_hid_conn_srv_cache_cmd_node_t));
    new_node->next = NULL;
    new_node->cache_item.cmd = cmd;

    node = g_ull_hid_srv_ctx.cmd_list_header;
    last_node = node;
    if (node == NULL) {
        g_ull_hid_srv_ctx.cmd_list_header = new_node;
    } else {
        while (node) {
            last_node = node;
            node = (bt_ull_le_hid_conn_srv_cache_cmd_node_t *)node->next;
        }
        last_node->next = new_node;
    }
    return &new_node->cache_item;
}

static uint8_t bt_ull_le_hid_conn_srv_delete_cmd_node(bt_ull_le_hid_conn_srv_cache_cmd_node_t *delete_node)
{
    if (delete_node == NULL) {
        return true;
    }
#ifdef BT_ULL_LE_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_conn_srv_delete_cache_cmd_node, node addr: 0x%x", delete_node);
#endif
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *header = g_ull_hid_srv_ctx.cmd_list_header;
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *node = header;
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *prv_node = header;
    while (node) {
        if (node == delete_node) {
            if (node == header) {
                g_ull_hid_srv_ctx.cmd_list_header = (bt_ull_le_hid_conn_srv_cache_cmd_node_t *)node->next;
            } else {
                prv_node->next = node->next;
            }
            bt_ull_le_srv_memory_free(node);
            return true;
        }
        prv_node = node;
        node = (bt_ull_le_hid_conn_srv_cache_cmd_node_t *)node->next;
    }
    return false;

}

static void bt_ull_le_hid_conn_srv_delete_all_cmd_node(void)
{
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *header = g_ull_hid_srv_ctx.cmd_list_header;
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *node = header;
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *next_node = node;
    if (NULL == header) {
        return;
    }
    while (node) {
        next_node = node->next;
        bt_ull_le_srv_memory_free(node);
        node = next_node;
    }
    g_ull_hid_srv_ctx.cmd_list_header = NULL;
}

static uint16_t bt_ull_le_hid_conn_srv_cmd_is_lock(bt_ull_le_hid_conn_srv_cmd_enum cmd)
{
    uint8_t i = 0;
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CMD_MAX ; i ++) {
        if (g_bt_ull_hid_cmd_lock_table[i].cmd == cmd) {
            return g_bt_ull_hid_cmd_lock_table[i].lock;
        }
    }
    return 0;
}

static int bt_ull_le_hid_conn_srv_register_callback(bt_ull_le_hid_conn_srv_callback_t cb)
{
    if (!cb) {
        return -EPERM;
    }
    g_ull_hid_srv_ctx.cb = cb;
    return 0;
}

static void bt_ull_le_hid_conn_srv_clear_cis_info(uint8_t idx)
{
    if (idx >= BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_reset_cis_info, invalid idx!");
        return;
    }
    g_ull_hid_srv_ctx.cis_info[idx].device_type = BT_ULL_LE_HID_SRV_DEVICE_NONE;
    g_ull_hid_srv_ctx.cis_info[idx].cis_id = 0x0;
    g_ull_hid_srv_ctx.cis_info[idx].acl_handle = 0xFFFF;
    g_ull_hid_srv_ctx.cis_info[idx].cis_handle = 0xFFFF;
    g_ull_hid_srv_ctx.cis_info[idx].state = BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED;
    g_ull_hid_srv_ctx.cis_info[idx].conn_to = 0x00;
    bt_ull_le_srv_memset(&g_ull_hid_srv_ctx.cis_info[idx].peer_addr, 0, sizeof(bt_addr_le_t));
}

static void bt_ull_le_hid_conn_srv_notify_msg(bt_ull_le_hid_conn_srv_msg_t msg, void *data)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_notify_msg, event: 0x%x", msg);
    if (g_ull_hid_srv_ctx.cb) {
        g_ull_hid_srv_ctx.cb(msg, data);
    } else {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_notify_msg error, event: 0x%x", msg);
    }
}

static bt_ull_le_hid_conn_srv_cache_cmd_node_t* bt_ull_le_hid_conn_srv_search_cmd_node_by_type(bt_ull_le_hid_conn_srv_cmd_enum cmd)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_conn_srv_search_cache_cmd_node_by_type, type: 0x%x", cmd);
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *node;
    node = g_ull_hid_srv_ctx.cmd_list_header;
    while (node) {
        if (node->cache_item.cmd == cmd) {
            return node;
        }
        node = (bt_ull_le_hid_conn_srv_cache_cmd_node_t *)node->next;
    }
    return NULL;
}

int bt_ull_le_hid_conn_srv_set_idle_time(bt_ull_le_hid_srv_idle_time_t idle_time)
{
    bt_ull_le_hid_conn_srv_contex_t *ctx = bt_ull_le_hid_conn_srv_get_ctx();
    if (idle_time > 200) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" error idle_time!");
        ctx->idle_time = BT_ULL_LE_HID_CONN_SRV_INVALID;
        return -EPERM;
    }

    ctx->idle_time = idle_time;
    return 0;
}

int bt_ull_le_hid_conn_srv_set_report_rate(bt_ull_le_hid_srv_report_rate_t *report_rate, bt_ull_le_hid_srv_device_t device_type)
{
    bt_ull_le_hid_conn_srv_contex_t *ctx = bt_ull_le_hid_conn_srv_get_ctx();
    ctx->report_rate.rr_level = report_rate->rr_level;
    ctx->report_rate.phy = report_rate->phy;
/* set report rate to hci */
    /* check cis status, only cis connected can set report rate */
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_type(device_type);
    bool cis_connected = bt_ull_le_hid_conn_srv_cis_link_is_connectded(idx);
    LOG_INF("[ULL][LE] bt_ull_le_hid_conn_srv_set_report_rate, idx: %d, cis_connected: %d, dt: %d", idx, cis_connected, device_type);
    if (idx != BT_ULL_LE_HID_CONN_SRV_INVALID && cis_connected) { 
        bt_ull_le_change_air_hid_cis_report_rate_t rr_params;
        rr_params.cis_handle = bt_ull_le_hid_conn_srv_get_cis_handle(idx);
        rr_params.cig_id = bt_ull_le_hid_conn_srv_get_cig_id();
        rr_params.report_rate = ctx->report_rate.rr_level;
        rr_params.phy = ctx->report_rate.phy;
        rr_params.Used_SE = 0;
        LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_report_rate, idx: %d, cis_handle: %d, cig_id: %d, report_rate: %d, phy: %d",
                idx, rr_params.cis_handle, rr_params.cig_id, rr_params.report_rate, rr_params.phy);
        if(bt_ull_le_set_report_rate(&rr_params)){
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_report_rate, set rr fail");
            return -EPERM;
        }
    }
    return 0;
}

#if defined (CONFIG_ULL_HID_LE_PERIPHERAL)
int bt_ull_le_hid_conn_srv_sync_air_cis(bt_ull_le_hid_srv_device_t type, bt_addr_le_t *addr)
{
    int status = -EPERM;
    if (BT_ULL_ROLE_CLIENT != bt_ull_le_hid_conn_srv_get_role()) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_sync_air_cis, invalid role!");
        return status;
    }
    bt_ull_le_hid_dm_device_info_t *device_info = bt_ull_le_hid_dm_read_device_info(type, addr);
    if (!device_info) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_sync_air_cis, No Bonding! %2x-%2x-%2x-%2x-%2x-%2x",\
            addr->a.val[0], addr->a.val[1], addr->a.val[2], addr->a.val[3], addr->a.val[4], addr->a.val[5]);
        return status;
    }
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_type(type);
    if (BT_ULL_LE_HID_CONN_SRV_INVALID != idx) {
        if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED != bt_ull_le_hid_conn_srv_get_cis_state(idx)) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_sync_air_cis, idex %d, busy state: %x", \
                            idx, bt_ull_le_hid_conn_srv_get_cis_state(idx));
            return status;
        }
    } else {
        idx = bt_ull_le_hid_conn_srv_get_empty_link();
    }

    if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_sync_air_cis, no link resource!");
        return status;
    }
    if (bt_ull_le_hid_conn_srv_cmd_is_lock(BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS)) {
        bt_ull_le_hid_conn_srv_cmd_cache_item_t* node = bt_ull_le_hid_conn_srv_create_cmd_node(BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS);
        if (node == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" node is NULL !");
            return -EPERM;
        }
        BT_ULL_LE_HID_MAKE_CMD_PARAM(sync, BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS);
        if (sync == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" sync is NULL !");
            return -EPERM;
        }
        sync->device_type = type;
        bt_ull_le_srv_memcpy(&sync->peer_addr, addr, sizeof(bt_addr_le_t));
        node->cmd = BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS;
        node->data_len = BT_ULL_LE_HID_GET_CMD_PARAM_LEN(BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS);
        node->data = sync;
        return EINPROGRESS;
    }

    bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING);
    bt_ull_le_hid_conn_srv_set_device_type(idx, type);
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    uint8_t adv_data_len = 0;
    uint8_t i = 0;
    for (i = 0; i < g_ull_hid_sync_adv_num; i++) {
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] total_len: %d, adv_data_len: %d", adv_data_len, g_ull_hid_sync_adv_data[i].data_len);
        adv_data_len += g_ull_hid_sync_adv_data[i].data_len + 2;
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] total_len: %d, num: %d", adv_data_len, g_ull_hid_sync_adv_num);
    bt_ull_le_sync_air_hid_cis_t *params = bt_ull_le_srv_memory_alloc(sizeof(bt_ull_le_sync_air_hid_cis_t) + adv_data_len);
#else
    bt_ull_le_sync_air_hid_cis_t *params = bt_ull_le_srv_memory_alloc(sizeof(bt_ull_le_sync_air_hid_cis_t));
#endif
    if (!params){
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" params is NULL !");
        return -EPERM;
    }
    // params->scenario = device_info->scenario;
#ifdef CONFIG_AIR_PRODUCT_TYPE_KEYBOARD
    params->scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_82;
#elif CONFIG_AIR_PRODUCT_TYPE_MOUSE
    params->scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_81;
#elif CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER
    params->scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_83;
#endif
    params->sync_timeout = g_ull_hid_sync_cis_timeout;
    params->connection_timeout = 100;
    params->slave_type = type;
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    params->adv_interval = g_ull_hid_sync_adv_interval;
    params->adv_data_len = adv_data_len;
    uint8_t set_data_len = 0;
    for (i = 0; i < g_ull_hid_sync_adv_num; i++) {
        bt_ull_le_srv_memcpy((uint8_t *)params->adv_data + set_data_len,
                            &g_ull_hid_sync_adv_data[i].type,
                            sizeof(g_ull_hid_sync_adv_data[i].type));
        bt_ull_le_srv_memcpy((uint8_t *)params->adv_data + set_data_len + sizeof(g_ull_hid_sync_adv_data[i].type), 
                            &g_ull_hid_sync_adv_data[i].data_len, 
                            sizeof(g_ull_hid_sync_adv_data[i].data_len));
        bt_ull_le_srv_memcpy((uint8_t *)params->adv_data + set_data_len + sizeof(g_ull_hid_sync_adv_data[i].type) + sizeof(g_ull_hid_sync_adv_data[i].data_len), 
                            g_ull_hid_sync_adv_data[i].data, 
                            g_ull_hid_sync_adv_data[i].data_len);
        set_data_len += sizeof(g_ull_hid_sync_adv_data[i].type) + sizeof(g_ull_hid_sync_adv_data[i].data_len) + g_ull_hid_sync_adv_data[i].data_len;
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] set_data_len: %d, type: %d, len: %d", 
                set_data_len, g_ull_hid_sync_adv_data[i].type, g_ull_hid_sync_adv_data[i].data_len);
    }
    
#endif
    bt_ull_le_srv_memcpy(&params->hid_tx_rsvd_anchor, &g_ull_hid_hid_tx_anchor, sizeof(uint16_t) * BT_ULL_LE_HID_REPORT_RATE_NUMBER);
    bt_ull_le_srv_memcpy(&params->ltk, &device_info->ltk, BT_ULL_LE_HID_DM_LTK_LEN);
    bt_ull_le_srv_memcpy(&params->skd, &device_info->skd, BT_ULL_LE_HID_DM_SKD_LEN);
    bt_ull_le_srv_memcpy(&params->iv, &device_info->iv, BT_ULL_LE_HID_DM_IV_LEN);
    bt_ull_le_srv_memcpy(&params->peer_addr, addr, sizeof(bt_addr_le_t));
    bt_ull_le_srv_memcpy(&params->uni_aa, &device_info->uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
    bt_ull_le_hid_conn_srv_lock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS, BT_ULL_LE_HID_CONN_SRV_LOCK);
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    bt_ull_le_hid_srv_print_addr(&params->peer_addr);
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_sync_air_cis, scenario: %d", params->scenario);
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] sync_air_cis, param(HS): Sync_To: %d, Conn_To: %d, ST: %d, LTK: %x..%x, AA: %x-%x-%x-%x, hid_tx_anchor: %d, params: 0x%x", \
        params->sync_timeout,
        params->connection_timeout,
        params->slave_type,
        params->ltk[0],
        params->ltk[15],
        device_info->uni_aa[0],
        device_info->uni_aa[1],
        device_info->uni_aa[2],
        device_info->uni_aa[3],
        params->hid_tx_rsvd_anchor,
        params
        );
#endif

    status = bt_ull_le_sync_air_hid_cis(params);
    if (status < 0) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_sync_air_cis, hci status error: %d!", status);
        bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED);
        bt_ull_le_hid_conn_srv_set_device_type(idx, BT_ULL_LE_HID_SRV_DEVICE_NONE);
        bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS);
    } else {
        bt_ull_le_hid_conn_srv_set_peer_addr(idx, addr);
    }
    bt_ull_le_srv_memory_free(params);
    return status;
}

int bt_ull_le_hid_conn_srv_cancel_sync_air_cis(bt_ull_le_hid_srv_device_t device_type)
{
    int status = -EPERM;
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_type(device_type);
    if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx || BT_ULL_ROLE_CLIENT != bt_ull_le_hid_conn_srv_get_role()) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cancel_sync_air_cis, invalid role!");
        return status;
    }
    uint8_t state = bt_ull_le_hid_conn_srv_get_cis_state(idx);
    if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING != state) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cancel_sync_air_cis, not in creating state!");
        return status;
    }
    bool is_lock =bt_ull_le_hid_conn_srv_cmd_is_lock(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS);
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cancel_sync_air_cis, state: %d, cmd_is_lock: %d!",\
        state, is_lock);

#endif

    if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CANCEL_CONNECTING == state) {
        return 0;
    }
    if (is_lock) {
        bt_ull_le_hid_conn_srv_cmd_cache_item_t* node = bt_ull_le_hid_conn_srv_create_cmd_node(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS);
        if (node == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" node is NULL !");
            return -EPERM;
        }
        BT_ULL_LE_HID_MAKE_CMD_PARAM(cancel, BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS);
        if (cancel == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" cancel is NULL !");
            return -EPERM;
        }
        cancel->device_type = device_type;
        node->cmd = BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS;
        node->data_len = BT_ULL_LE_HID_GET_CMD_PARAM_LEN(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS);
        node->data = cancel;
        return EINPROGRESS;
    }
    bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CANCEL_CONNECTING);
    bt_ull_le_hid_conn_srv_lock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS, BT_ULL_LE_HID_CONN_SRV_LOCK);
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] bt_ull_le_hid_conn_srv_cancel_sync_air_cis");
#endif
    status = bt_ull_le_cancel_sync_air_hid_cis();
    if (status < 0) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cancel_sync_air_cis, hci status error: %x!", status);
        bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS);
        bt_ull_le_hid_conn_srv_set_cis_state(idx, state);
    }
    return status;
}
#endif

int bt_ull_le_hid_conn_srv_disconnect_air_cis(uint16_t acl_handle, uint8_t reason)
{
    int status = -EPERM;
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_acl_handle(acl_handle);
    if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_disconnect_air_cis, invalid cis type!");
        return status;
    }
    uint8_t state = bt_ull_le_hid_conn_srv_get_cis_state(idx);
    if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTED > state) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_disconnect_air_cis, not connected link!");
        return status;
    }
    uint16_t is_lock = bt_ull_le_hid_conn_srv_cmd_is_lock(BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS);
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_disconnect_air_cis, state: %d, cmd_is_lock: %d!", \
        state, is_lock);
#endif
    if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTING == state) {
        return 0;
    }
    if (is_lock) {
        bt_ull_le_hid_conn_srv_cmd_cache_item_t* node = bt_ull_le_hid_conn_srv_create_cmd_node(BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS);
        if (node == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" node is NULL !");
            return -EPERM;
        }
        BT_ULL_LE_HID_MAKE_CMD_PARAM(disconnect, BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS);
        if (disconnect == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" disconnect is NULL !");
            return -EPERM;
        }
        disconnect->acl_handle = acl_handle;
        disconnect->reason = reason;
        node->cmd = BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS;
        node->data_len = BT_ULL_LE_HID_GET_CMD_PARAM_LEN(BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS);
        node->data = disconnect;
        LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_disconnect_air_cis, pending!");
        return EINPROGRESS;
    }
    bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTING);
    bt_ull_le_hid_conn_srv_lock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS, BT_ULL_LE_HID_CONN_SRV_LOCK);
    bt_ull_le_air_hid_cis_disconnect_t params;
    params.connection_handle = bt_ull_le_hid_conn_srv_get_cis_handle(idx);
    params.reason = reason;
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] bt_ull_le_hid_conn_srv_disconnect_air_cis, cis_handle: %x, reason: %x!", \
        params.connection_handle, params.reason);
#endif

    status = bt_ull_le_disconnect_air_hid_cis(&params);
    if (status < 0) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_disconnect_air_cis, hci status error: %x!", status);
        bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS);
        bt_ull_le_hid_conn_srv_set_cis_state(idx, state);
    }
    return status;

}

#if defined (CONFIG_ULL_HID_LE_CENTRAL)
int bt_ull_le_hid_conn_srv_change_scenario(bt_ull_le_hid_srv_app_scenario_t scenario)
{
    uint8_t cig_state = bt_ull_le_hid_conn_srv_get_cig_state();
    bt_ull_le_hid_conn_srv_contex_t *ctx = bt_ull_le_hid_conn_srv_get_ctx();
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_change_scenario, curr_sc: %d, cig_state: %d",\
        ctx->scenario, cig_state);
    int status = -EPERM;
    if (BT_ULL_LE_HID_SRV_APP_SCENARIO_NONE == scenario) {
        return status;
    }
    if (scenario == ctx->scenario) {
        return 0;
    }
    ctx->scenario = scenario;
    return 0;
}

int bt_ull_le_hid_conn_srv_set_tx_power(bt_ull_le_hid_srv_set_tx_power_t *param)
{
    /* check cis status, only cis connected can set report rate */
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_type(param->device_type);
    bool cis_connected = bt_ull_le_hid_conn_srv_cis_link_is_connectded(idx);
    LOG_INF("[ULL][LE] bt_ull_le_hid_conn_srv_set_tx_power, idx: %d, cis_connected: %d, dt: %d", idx, cis_connected, param->device_type);
    if (idx != BT_ULL_LE_HID_CONN_SRV_INVALID && cis_connected) { 
        bt_ull_le_set_air_hid_cis_tx_power_t tx_power_param;
        tx_power_param.handle =  bt_ull_le_hid_conn_srv_get_cis_handle(idx);
        tx_power_param.remote_tx_power_control = param->remote_tx_power_control;
        if(bt_ull_le_set_tx_power(&tx_power_param)){
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_tx_power fail");
            return -EPERM;
        }
    }
    return 0;
}

int bt_ull_le_hid_conn_srv_set_remote_tx_power(bt_ull_le_hid_srv_set_vpa_tx_gc_t *param)
{
    /* check cis status, only cis connected can set report rate */
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_type(param->device_type);
    bool cis_connected = bt_ull_le_hid_conn_srv_cis_link_is_connectded(idx);
    LOG_INF("[ULL][LE] bt_ull_le_hid_conn_srv_set_remote_tx_power, idx: %d, cis_connected: %d, dt: %d", idx, cis_connected, param->device_type);
    if (idx != BT_ULL_LE_HID_CONN_SRV_INVALID && cis_connected) { 
        bt_ull_le_set_air_hid_cis_remote_tx_power_t tx_power_param;
        tx_power_param.handle =  bt_ull_le_hid_conn_srv_get_cis_handle(idx);
        tx_power_param.tx_gc = param->tx_gc;
        tx_power_param.pa_vol = param->pa_vol;
        if(bt_ull_le_set_remote_tx_power(&tx_power_param)){
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_set_remote_tx_power fail");
            return -EPERM;
        }
    }
    return 0;
}

int bt_ull_le_hid_conn_srv_get_conn_info(bt_ull_le_hid_srv_get_conn_quality_info_t *quality_info)
{
    /* check cis status, only cis connected can set report rate */
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_type(quality_info->device_type);
    bool cis_connected = bt_ull_le_hid_conn_srv_cis_link_is_connectded(idx);
    LOG_INF("[ULL][LE] bt_ull_le_hid_conn_srv_get_conn_info, idx: %d, cis_connected: %d, dt: %d", idx, cis_connected, quality_info->device_type);
    if (idx != BT_ULL_LE_HID_CONN_SRV_INVALID && cis_connected) { 
        bt_ull_le_get_air_hid_cis_conn_info_t params;
        params.handle = bt_ull_le_hid_conn_srv_get_cis_handle(idx);
        params.update_period = quality_info->update_period;
        if(bt_ull_le_get_connection_info(&params)){
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_get_conn_info fail");
            return -EPERM;
        }
    }
    return 0;
}

int bt_ull_le_hid_conn_srv_create_air_cig(bt_ull_le_hid_srv_app_scenario_t scenario)
{
    uint8_t i = 0;
    int status = -EPERM;
    uint8_t cig_state = bt_ull_le_hid_conn_srv_get_cig_state();
    if (BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATED == cig_state) {
        return 0;
    } else if (BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATING == cig_state) {
        return -EPERM;
    }

    const bt_ull_le_hid_conn_srv_cig_params_t *cig_params = bt_ull_le_hid_conn_srv_get_cig_params(scenario);
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_air_cig, sc: %d", scenario);
    if (!cig_params) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG"bt_ull_le_hid_conn_srv_create_air_cig, invalid cig_params");
        return -EPERM;
    }

    bt_ull_le_set_air_hid_cig_t hid_cig;
    bt_ull_le_air_hid_cis_params_t *cis_list = bt_ull_le_srv_memory_alloc(cig_params->cis_count * sizeof(*cis_list));
    if (BT_ULL_ROLE_SERVER != bt_ull_le_hid_conn_srv_get_role() || !cig_params->cis_count) {
        __ASSERT(0, BT_ULL_LE_HID_CONN_LOG" invalid role or cis count!");
        return -EPERM;
    }

    if (!cis_list) {
        __ASSERT(0, BT_ULL_LE_HID_CONN_LOG" out of memory!");
        return -ENOBUFS;
    } else {
        bt_ull_le_srv_memset(cis_list, 0, sizeof(*cis_list) * cig_params->cis_count);
    }
    for (i = 0; i < cig_params->cis_count; i++) {
        cis_list[i].cis_id = cig_params->tab[i].cis_id;
        cis_list[i].slave_type = cig_params->tab[i].dev_type;
        bt_ull_le_hid_conn_srv_set_cis_id(i, cis_list[i].cis_id );
        bt_ull_le_hid_conn_srv_set_device_type(i, cis_list[i].slave_type);
        cis_list[i].sdu_interval_m_to_s = cig_params->tab[i].sdu_interval_m_to_s;
        cis_list[i].sdu_interval_s_to_m = cig_params->tab[i].sdu_interval_s_to_m;
        cis_list[i].share_num = cig_params->tab[i].share_num;
        cis_list[i].max_uplink_num  = cig_params->tab[i].uplink_num;
        cis_list[i].phy_m_to_s = cig_params->tab[i].phy_m_to_s;
        cis_list[i].phy_s_to_m = cig_params->tab[i].phy_s_to_m;
        cis_list[i].ft_m_to_s = cig_params->tab[i].ft_m_to_s;
        cis_list[i].ft_s_to_m = cig_params->tab[i].ft_s_to_m;

        if (BT_ULL_LE_HID_SRV_DEVICE_HEADSET == cig_params->tab[i].dev_type \
            || BT_ULL_LE_HID_SRV_DEVICE_EARBUDS == cig_params->tab[i].dev_type) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG"Device Type error!,  Not support HS && EB!!");
        } else {
            cis_list[i].max_sdu_m_to_s = cig_params->tab[i].sdu_m_to_s;
            cis_list[i].max_sdu_s_to_m = cig_params->tab[i].sdu_s_to_m;
        }
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] bt_ull_le_hid_conn_srv_create_air_cig, param(%d): %d, %d, %d, %d, %d, %d, %d, %d",
            cis_list[i].slave_type,
            cis_list[i].cis_id,
            cis_list[i].slave_type,
            cis_list[i].sdu_interval_m_to_s,
            cis_list[i].sdu_interval_s_to_m,
            cis_list[i].share_num,
            cis_list[i].max_uplink_num,
            cis_list[i].max_sdu_m_to_s,
            cis_list[i].max_sdu_s_to_m
            );
#endif

    }
    uint8_t sub_event = bt_ull_le_hid_conn_srv_get_sub_event(bt_ull_le_hid_conn_srv_get_rr_level());
    bt_ull_le_hid_conn_srv_contex_t *ctx = bt_ull_le_hid_conn_srv_get_ctx();
    hid_cig.cig_id = BT_ULL_LE_HID_CONN_SRV_CIG_ID_1;
    bt_ull_le_hid_conn_srv_set_cig_id(BT_ULL_LE_HID_CONN_SRV_CIG_ID_1);
    hid_cig.scnario = scenario;
    hid_cig.slave_latency = ((ctx->scenario < BT_ULL_LE_HID_SRV_APP_SCENARIO_4) || (ctx->idle_time == BT_ULL_LE_HID_CONN_SRV_INVALID)) ? cig_params->slave_latency : ((ctx->idle_time * 1000)/cig_params->iso_interval); //iso_interval unit is us.

    if (BT_ULL_LE_HID_SRV_APP_SCENARIO_1 == scenario || BT_ULL_LE_HID_SRV_APP_SCENARIO_2 == scenario) {
        hid_cig.d4_sub_event = sub_event;
    } else {
        hid_cig.d4_sub_event = cig_params->default_se;
    }
    hid_cig.iso_interval = cig_params->iso_interval;
    hid_cig.cis_count = cig_params->cis_count;
    hid_cig.cis_list = cis_list;
    bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATING);
    status = bt_ull_le_set_air_hid_cig_parameters(&hid_cig);
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] bt_ull_le_hid_conn_srv_create_air_cig, status: %x, sc: %d, sl: %d, d4_sub_event: %d, iso_interval: %d, cis_num: %d", \
        status, hid_cig.scnario, hid_cig.slave_latency, hid_cig.d4_sub_event, hid_cig.iso_interval, hid_cig.cis_count);
#endif
    bt_ull_le_srv_memory_free(cis_list);
    return status;
}

int bt_ull_le_hid_conn_srv_remove_air_cig(void)
{
    int status = -EPERM;
    uint8_t cig_id = bt_ull_le_hid_conn_srv_get_cig_id();
    uint8_t cig_state = bt_ull_le_hid_conn_srv_get_cig_state();
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_remove_air_cig, cig id: %d, cig_state: %d", \
        cig_id, cig_state);
    if (BT_ULL_LE_HID_CONN_SRV_CIG_ID_1 != cig_id || BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATED != cig_state) {
        return ENXIO;
    }
    if (bt_ull_le_hid_conn_srv_get_role() != BT_ULL_ROLE_SERVER) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" error role!");
        return status;
    }

    bt_ull_le_remove_air_hid_cig_t params;
    params.cig_id = cig_id;
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] bt_ull_le_hid_conn_srv_remove_air_cig, cig id: %x", \
            params.cig_id);
#endif
    bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_REMOVING);
    status = bt_ull_le_remove_air_hid_cig_parameters(&params);
    if (status < 0) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_remove_air_cig, hci status error: %x!", status);
    }
    return status;
}

static bt_ull_le_create_air_hid_cis_params_t *bt_ull_le_hid_conn_srv_create_conn_params(bt_ull_le_hid_srv_conn_params_t *param, uint8_t *ltk, uint8_t *skd, uint8_t *iv, uint32_t *len)
{
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_type(param->device_type);
    if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" invalid link!");
        return NULL;
    }
    bt_ull_le_create_air_hid_cis_params_t *conn = NULL;
    uint32_t comm_len = sizeof(*conn) - 1;
    uint8_t i = 0;
    bool set_key = false;
    uint32_t list_len = 0x0;
    if (bt_ull_le_hid_conn_srv_get_cis_state(idx) != BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED) {
        LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_conn_params, (%d) is connecting!", param->device_type);
    } else {
        list_len = comm_len + param->list_num * sizeof(bt_ull_le_air_hid_cis_dev_info_t);
        *len = list_len;
        conn = bt_ull_le_srv_memory_alloc(list_len);
        if (!conn) {
            __ASSERT(0, BT_ULL_LE_HID_CONN_LOG" Conn OOM!");
        }
        conn->cis_connection_handle = bt_ull_le_hid_conn_srv_get_cis_handle(idx);
        conn->connection_timeout = g_ull_hid_conn_timeout;
        bt_ull_le_hid_conn_srv_set_conn_timout(idx, conn->connection_timeout);
        conn->dev_count = param->list_num;
        bt_ull_le_hid_dm_device_info_t *conn_info = NULL;
        bt_ull_le_air_hid_cis_dev_info_t *dev_list = (bt_ull_le_air_hid_cis_dev_info_t *)&conn->dev_list;
        for (i = 0; i < param->list_num; i ++) {
            conn_info = bt_ull_le_hid_dm_read_device_info(param->device_type, (bt_addr_le_t *)&param->peer_addr_list + i);
            if (conn_info == NULL) {
                LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_conn_params(%d), NO Bonding!", param->device_type);
                bt_ull_le_hid_srv_print_addr((bt_addr_le_t *)&param->peer_addr_list + i);
                continue;
            }
            if (!set_key) {
                set_key = true;
                bt_ull_le_srv_memcpy(ltk, &conn_info->ltk, BT_ULL_LE_HID_DM_LTK_LEN);
                bt_ull_le_srv_memcpy(skd, &conn_info->skd, BT_ULL_LE_HID_DM_SKD_LEN);
                bt_ull_le_srv_memcpy(iv, &conn_info->iv, BT_ULL_LE_HID_DM_IV_LEN);
            }
            bt_ull_le_srv_memcpy(&dev_list[i].uni_aa, &conn_info->uni_aa, BT_ULL_LE_HID_DM_UNI_AA_LEN);
            bt_ull_le_srv_memcpy(&dev_list[i].peer_addr, (bt_addr_le_t *)&param->peer_addr_list + i, sizeof(bt_addr_le_t));
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
            LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] create_air_cis(%d), uni_aa: %x-%x-%x-%x", \
                param->device_type,
                dev_list[i].uni_aa[0],
                dev_list[i].uni_aa[1],
                dev_list[i].uni_aa[2],
                dev_list[i].uni_aa[3]
                );
            bt_ull_le_hid_srv_print_addr(&dev_list[i].peer_addr);
#endif
        }
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] create_air_cis, param(%d): Cis_Handle: %x, Conn_TO:%d, Dev_Count: %d", \
        param->device_type,
        conn->cis_connection_handle,
        conn->connection_timeout,
        conn->dev_count
        );
#endif
        bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING);
    }
    return conn;
}

static uint8_t create_cis_ltk[16] = {0};
static uint8_t create_cis_skd[16] = {0};
static uint8_t create_cis_iv[8] = {0};
int bt_ull_le_hid_conn_srv_create_air_cis(bt_ull_le_hid_srv_conn_params_t *kb, bt_ull_le_hid_srv_conn_params_t *ms, bt_ull_le_hid_srv_conn_params_t *gp)
{
    int status = -EPERM;
    uint8_t cis_count = 0;
    uint8_t idx = BT_ULL_LE_HID_CONN_SRV_INVALID;
    uint32_t kb_list_len = 0x0, ms_list_len = 0x0, gp_list_len = 0x0;
    bt_ull_le_create_air_hid_cis_params_t *keyboard = NULL;
    bt_ull_le_create_air_hid_cis_params_t *mouse = NULL;
    bt_ull_le_create_air_hid_cis_params_t *gamepad = NULL;
    uint8_t cig_state = bt_ull_le_hid_conn_srv_get_cig_state();
    
    if (BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATED != cig_state || bt_ull_le_hid_conn_srv_cmd_is_lock(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS)) {
        bt_ull_le_hid_conn_srv_cmd_cache_item_t* node = bt_ull_le_hid_conn_srv_create_cmd_node(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS);
        if (node == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" node is NULL !");
            return -EPERM;
        }
        BT_ULL_LE_HID_MAKE_CMD_PARAM(create, BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS);
        if (create == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" create is NULL !");
            return -EPERM;
        }
        node->cmd = BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS;
        uint16_t q_total_len = 0;
        uint16_t q_comm_len = sizeof(bt_ull_le_hid_srv_conn_params_t) - 1;

        if (ms) {
            uint16_t ms_len = q_comm_len + sizeof(bt_addr_le_t) * (ms->list_num);
            bt_ull_le_hid_srv_conn_params_t *ms_q = bt_ull_le_srv_memory_alloc(ms_len);
            if (!ms_q) {
                __ASSERT(0, BT_ULL_LE_HID_CONN_LOG" mouse OOM!");
            }
            bt_ull_le_srv_memcpy(ms_q, ms, ms_len);
            q_total_len += ms_len;
            create->ms = ms_q;
        } else {
            create->ms = NULL;
        }
        if (kb) {
            uint16_t kb_len = q_comm_len + sizeof(bt_addr_le_t) * (kb->list_num);
            bt_ull_le_hid_srv_conn_params_t *kb_q = bt_ull_le_srv_memory_alloc(kb_len);
            if (!kb_q) {
                __ASSERT(0, BT_ULL_LE_HID_CONN_LOG" keyboard OOM!");
            }
            bt_ull_le_srv_memcpy(kb_q, kb, kb_len);
            q_total_len += kb_len;
            create->kb = kb_q;
        } else {
            create->kb = NULL;
        }
        if (gp) {
            uint16_t gp_len = q_comm_len + sizeof(bt_addr_le_t) * (gp->list_num);
            bt_ull_le_hid_srv_conn_params_t *gp_q = bt_ull_le_srv_memory_alloc(gp_len);
            if (!gp_q) {
                __ASSERT(0, BT_ULL_LE_HID_CONN_LOG" gamepad OOM!");
            }
            bt_ull_le_srv_memcpy(gp_q, gp, gp_len);
            q_total_len += gp_len;
            create->gp = gp_q;
        } else {
            create->gp = NULL;
        }
        node->data_len = q_total_len;
        node->data = create;

        if (BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATED != cig_state) {
            bt_ull_le_hid_srv_app_scenario_t scen = bt_ull_le_hid_conn_srv_get_scenario();
            status = bt_ull_le_hid_conn_srv_create_air_cig(scen);
            if (status < 0) {
                if (create) {
                    if (create->ms) {
                        bt_ull_le_srv_memory_free(create->ms);
                    }
                    if (create->kb) {
                        bt_ull_le_srv_memory_free(create->kb);
                    }
                    if (create->gp) {
                        bt_ull_le_srv_memory_free(create->gp);
                    }
                    bt_ull_le_srv_memory_free(create);
                }
                bt_ull_le_hid_conn_srv_cache_cmd_node_t *create = bt_ull_le_hid_conn_srv_search_cmd_node_by_type(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS);
                if (create) {
                    bt_ull_le_hid_conn_srv_delete_cmd_node(create);
                }
                LOG_ERR(BT_ULL_LE_HID_CONN_LOG" Create CIG Fail!");
                return status;
            }
        }
        return EINPROGRESS;
    }

    if (kb) {
        keyboard = bt_ull_le_hid_conn_srv_create_conn_params(kb, create_cis_ltk, create_cis_skd, create_cis_iv, &kb_list_len);
        if (keyboard) {
            cis_count ++;
        }
    }
    if (ms) {
        mouse = bt_ull_le_hid_conn_srv_create_conn_params(ms, create_cis_ltk, create_cis_skd, create_cis_iv, &ms_list_len);
        if (mouse) {
            cis_count ++;
        }
    }
    if (gp) {
        gamepad = bt_ull_le_hid_conn_srv_create_conn_params(gp, create_cis_ltk, create_cis_skd, create_cis_iv, &gp_list_len);
        if (gamepad) {
            cis_count ++;
        }
    }

    uint32_t total_len = sizeof(bt_ull_le_create_air_hid_cis_t) -1 + kb_list_len + ms_list_len + gp_list_len;
    bt_ull_le_create_air_hid_cis_t *hid_cis = \
            (bt_ull_le_create_air_hid_cis_t *)bt_ull_le_srv_memory_alloc(total_len); //kb + ms + gp total size
    if (!hid_cis) {
        __ASSERT(0, BT_ULL_LE_HID_CONN_LOG" hid_cis OOM!");
    }
    uint8_t *start_cpy_addr = hid_cis->cis_list;
    uint8_t offset = 0x0;
    if (keyboard) {
        memcpy(start_cpy_addr + offset, keyboard, kb_list_len);
        offset += kb_list_len;
    }
    if (mouse) {
        memcpy(start_cpy_addr + offset, mouse, ms_list_len);
        offset += ms_list_len;
    }
    if (gamepad) {
        memcpy(start_cpy_addr + offset, gamepad, gp_list_len);
        offset += gp_list_len;
    }
    hid_cis->create_timeout = g_ull_hid_create_cis_timeout;
    bt_ull_le_srv_memcpy(&hid_cis->ltk, create_cis_ltk, BT_ULL_LE_HID_DM_LTK_LEN);
    bt_ull_le_srv_memcpy(&hid_cis->skd, create_cis_skd, BT_ULL_LE_HID_DM_SKD_LEN);
    bt_ull_le_srv_memcpy(&hid_cis->iv, create_cis_iv, BT_ULL_LE_HID_DM_IV_LEN);
    hid_cis->cis_count = cis_count;
    hid_cis->usb_tx_rsvd_anchor = g_ull_hid_usb_tx_anchor;
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] create_air_cis, ALL: cre_to: %d, ltk:%x-%x..%x, skd: %x-%x-..%x, usb_tx_anchor: %d, cis count: %d", \
        hid_cis->create_timeout,
        hid_cis->ltk[0],
        hid_cis->ltk[1],
        hid_cis->ltk[15],
        hid_cis->skd[0],
        hid_cis->skd[1],
        hid_cis->skd[15],
        hid_cis->usb_tx_rsvd_anchor,
        hid_cis->cis_count
        );
#endif

    bt_ull_le_hid_conn_srv_lock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS, BT_ULL_LE_HID_CONN_SRV_LOCK);
    if (keyboard || mouse || gamepad) {
        status = bt_ull_le_create_air_hid_cis(hid_cis);
    } else {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" Create CIS Fail!");
        bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS);
        if (hid_cis) {
            bt_ull_le_srv_memory_free(hid_cis);
        }
        return status;
    }
    if (status < 0) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" create_air_cis, hci status error: %x!", status);
        bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS);
        if (kb) {
            idx = bt_ull_le_hid_conn_srv_get_idx_by_type(BT_ULL_LE_HID_SRV_DEVICE_KEYBOARD);
            bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED);
        }
        if (ms) {
            idx = bt_ull_le_hid_conn_srv_get_idx_by_type(BT_ULL_LE_HID_SRV_DEVICE_MOUSE);
            bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED);
        }
        if (gp) {
            idx = bt_ull_le_hid_conn_srv_get_idx_by_type(BT_ULL_LE_HID_SRV_DEVICE_GAMEPAD);
            bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED);
        }
    }
    if (keyboard) {
        bt_ull_le_srv_memory_free(keyboard);
    }
    if (mouse) {
        bt_ull_le_srv_memory_free(mouse);
    }
    if (gamepad) {
        bt_ull_le_srv_memory_free(gamepad);
    }
    if (hid_cis) {
        bt_ull_le_srv_memory_free(hid_cis);
    }
    return status;

}

int bt_ull_le_hid_conn_srv_cancel_create_air_cis(bt_ull_le_hid_srv_device_t device_type)
{
    int status = -EPERM;
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_type(device_type);
    if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx || BT_ULL_ROLE_SERVER != bt_ull_le_hid_conn_srv_get_role()) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cancel_create_air_cis, invalid cis type!");
        return status;
    }
    uint8_t state = bt_ull_le_hid_conn_srv_get_cis_state(idx);
    uint16_t is_lock = bt_ull_le_hid_conn_srv_cmd_is_lock(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS);
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] bt_ull_le_hid_conn_srv_cancel_create_air_cis, status: %d, is_lock: %d", \
        state,
        is_lock);
#endif
    if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING != state) {
        return status;
    }
    if (is_lock) {
        bt_ull_le_hid_conn_srv_cmd_cache_item_t* node = bt_ull_le_hid_conn_srv_create_cmd_node(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS);
        if (node == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" node is NULL !");
            return -EPERM;
        }
        BT_ULL_LE_HID_MAKE_CMD_PARAM(cancel, BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS);
        if (cancel == NULL) {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" cancel is NULL !");
            return -EPERM;
        }
        cancel->device_type = device_type;
        node->cmd = BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS;
        node->data_len = BT_ULL_LE_HID_GET_CMD_PARAM_LEN(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS);
        node->data = cancel;
        return EINPROGRESS;
    }

    bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CANCEL_CONNECTING);
    bt_ull_le_cancel_create_air_hid_cis_params_t params;
    params.cis_handle = bt_ull_le_hid_conn_srv_get_cis_handle(idx);
    params.reason = BT_HCI_ERR_LOCALHOST_TERM_CONN;
    bt_ull_le_hid_conn_srv_lock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS, BT_ULL_LE_HID_CONN_SRV_LOCK);
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
    LOG_INF(BT_ULL_LE_HID_CONN_LOG"[CMD] bt_ull_le_hid_conn_srv_cancel_create_air_cis, cis_handle: %x, reason: %d",\
        params.cis_handle,
        params.reason);
#endif
    status = bt_ull_le_cancel_creating_air_hid_cis(&params);
    if (status < 0) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cancel_create_air_cis, error status: %x!", status);
        bt_ull_le_hid_conn_srv_set_cis_state(idx, state);
        bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS);
    }
    return status;
}

static uint8_t bt_ull_le_hid_conn_srv_get_sub_event(uint8_t report_rate)
{
    uint8_t sub_evt = 0x00;
    if (BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_1 == report_rate) {
        sub_evt  = 0x03;
    } else if (BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_2 == report_rate) {
        sub_evt  = 0x02;
    } else {
        sub_evt = BT_ULL_LE_HID_CONN_SRV_INVALID;
    }
    return sub_evt ;
}

static void bt_ull_le_hid_conn_srv_create_cig_params_cnf_hdl(int status, bt_ull_le_set_air_hid_cig_cnf_t *cnf)
{
    uint8_t i = 0;
    uint8_t idx = 0x0;
    uint8_t cig_id = bt_ull_le_hid_conn_srv_get_cig_id();
    uint8_t cig_state = bt_ull_le_hid_conn_srv_get_cig_state();
    uint16_t rr_cis_handle = 0x0;
    //bt_ull_le_hid_conn_srv_msg_ind_t msg;
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_cig_params_cnf_hdl, status : %x, cig_id: %d, cis_count: %d", \
        cnf->status, cnf->cig_id, cnf->cis_count);

    bt_ull_le_hid_conn_srv_cache_cmd_node_t *create_cis = bt_ull_le_hid_conn_srv_search_cmd_node_by_type(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS);
    if(status < 0) {
        bt_ull_le_hid_conn_srv_set_cig_id(BT_ULL_LE_HID_CONN_SRV_CIG_ID_NONE);
        if (BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATING == cig_state) {
            bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_NONE);
        }
        for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
            bt_ull_le_hid_conn_srv_clear_cis_info(i);
        }
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_cig_params_cnf_hdl, status error!");
    } else {
        if (cig_id == cnf->cig_id && BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATING == cig_state) {
            if (cnf->cis_count > BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM) {
                __ASSERT_NO_MSG(0);
            }
            bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATED);
            bt_ull_le_set_air_hid_cis_info_t *cis_info = cnf->cis_info;
            for (i = 0; i < cnf->cis_count; i ++) {
                idx = bt_ull_le_hid_conn_srv_get_idx_by_cis_id(cis_info[i].cis_id);
                if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx) {
                    __ASSERT_NO_MSG(0);
                }
                LOG_INF(BT_ULL_LE_HID_CONN_LOG" cis_id: %d, link idx: %d, CIS_Handle: %x", cis_info[i].cis_id, idx, cis_info[i].cis_connection_handle);
                bt_ull_le_hid_conn_srv_set_cis_handle(idx, cis_info[i].cis_connection_handle);
                rr_cis_handle = cis_info[i].cis_connection_handle;
            }
        } else {
            bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_NONE);
            for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
                bt_ull_le_hid_conn_srv_clear_cis_info(i);
            }
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_cig_params_cnf_hdl, cig state or cig id error!");
        }
    }

#if 1
/* temp solution for Switch RR start*/
    bt_ull_le_hid_conn_srv_contex_t *ctx = bt_ull_le_hid_conn_srv_get_ctx();
    bt_ull_le_change_air_hid_cis_report_rate_t rr_params = {0};
    rr_params.cis_handle = rr_cis_handle;
    rr_params.cig_id = cig_id;
    rr_params.report_rate = ctx->report_rate.rr_level;
    rr_params.phy = ctx->report_rate.phy;
    if(bt_ull_le_set_report_rate(&rr_params)){
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_cig_params_cnf_hdl, set rr fail");
        return;
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_cig_params_cnf_hdl, scenario: %d, cig_id: %d, report_rate: %d, phy: %d",\
        ctx->scenario, cig_id, rr_params.report_rate, rr_params.phy);

/* temp solution for Switch RR end */
#endif
    if (create_cis) {
        /* only remove cig execute this flow */
        BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS_T *data = BT_ULL_LE_HID_GET_CMD_PARAM(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS, create_cis);
        if (0 == status && data) {
            int ret = bt_ull_le_hid_conn_srv_next_action_hdl(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS, data);
            LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_cig_params_cnf_hdl, ret: %d", ret);
        }
        /* 
            remove cig[backup create cis] then create cig, will free data when bt_ull_le_hid_conn_srv_remove_cig_params_cnf_hdl
        */
        if (data) {
            if (data->ms) {
                bt_ull_le_srv_memory_free(data->ms);
            }
            if (data->kb) {
                bt_ull_le_srv_memory_free(data->kb);
            }
            if (data->gp) {
                bt_ull_le_srv_memory_free(data->gp);
            }
            bt_ull_le_srv_memory_free(data);
        }
        bt_ull_le_hid_conn_srv_delete_cmd_node(create_cis);
    }
}
#endif

static void bt_ull_le_hid_conn_srv_cis_established_hdl(int status, bt_ull_le_air_hid_cis_established_ind_t *ind)
{
    if (!ind) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_air_cis_established_hdl, ind is null!");
        return;
    }

    bt_ull_role_t role = bt_ull_le_hid_conn_srv_get_role();
    bt_ull_le_hid_conn_srv_msg_ind_t msg;
    uint8_t idx = bt_ull_le_hid_conn_srv_get_idx_by_type(ind->slave_type);
    if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cis_established_hdl, error idx! handle: %x", ind->cis_connection_handle);
        return;
    }
    uint8_t cis_state = bt_ull_le_hid_conn_srv_get_cis_state(idx);

    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cis_established_hdl, status: %x, idx: %d, state: %x, dt: %d, cis_handle: %x, acl_handle: %x", \
        status, idx, cis_state, ind->slave_type, ind->cis_connection_handle, ind->acl_connection_handle);
    if (status != 0) {
        msg.status = status;
        msg.cis_connected.acl_handle = 0xFFFF;
        msg.cis_connected.device_type = ind->slave_type;
        msg.cis_connected.rr_level = bt_ull_le_hid_conn_srv_get_rr_level();
        bt_ull_le_srv_memcpy(&msg.cis_connected.peer_addr, &ind->peer_aadr, sizeof(bt_addr_le_t));
        bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_CIS_CONNECTED_IND, &msg);
        if (BT_ULL_ROLE_SERVER == role) {
            if (BT_HCI_ERR_ADV_TIMEOUT == status) {
                /* free create cis conn */
                bt_ull_le_free_air_hid_cis_conn(BT_ULL_ROLE_SERVER);
            }
            if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING == cis_state || BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CANCEL_CONNECTING == cis_state) {
                bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED);
            } else {
                return;
            }
            if (BT_HCI_ERR_CONN_FAIL_TO_ESTAB == status) {
                //TODO
            }
        } else {
            if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING == cis_state || BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CANCEL_CONNECTING == cis_state) {
                bt_ull_le_hid_conn_srv_clear_cis_info(idx);
                if (!bt_ull_le_hid_conn_srv_get_connected_link()) {
                    bt_ull_le_hid_conn_srv_set_cig_id(BT_ULL_LE_HID_CONN_SRV_CIG_ID_NONE);
                    bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_NONE);
                }
            }
        }
    } else {
        if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING == cis_state) {
            bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTED);
            bt_ull_le_hid_conn_srv_set_acl_handle(idx, ind->acl_connection_handle);
            bt_ull_le_hid_conn_srv_set_cis_handle(idx, ind->cis_connection_handle);
            bt_ull_le_hid_conn_srv_set_peer_addr(idx, &ind->peer_aadr);
            if (BT_ULL_ROLE_CLIENT == role) {
                bt_ull_le_hid_conn_srv_set_cig_id(BT_ULL_LE_HID_CONN_SRV_CIG_ID_1);
                bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATED);
                bt_ull_le_hid_conn_srv_set_cis_id(idx, ind->cis_id);
            } else if (BT_ULL_ROLE_SERVER == role) {

            }
            msg.status = status;
            msg.cis_connected.acl_handle = ind->acl_connection_handle;
            msg.cis_connected.device_type = ind->slave_type;
            msg.cis_connected.rr_level = bt_ull_le_hid_conn_srv_get_rr_level();
            bt_ull_le_srv_memcpy(&msg.cis_connected.peer_addr, &ind->peer_aadr, sizeof(bt_addr_le_t));
            bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_CIS_CONNECTED_IND, &msg);
        } else {
            LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_air_cis_established_hdl, error state: %d!", cis_state);
            return;
        }
    }
}

static void bt_ull_le_hid_conn_srv_cis_disconnect_complete_hdl(int status, bt_ull_le_air_hid_cis_disconnect_complete_ind_t *ind)
{
    if (!ind) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cis_disconnect_complete_hdl, ind is null!");
        return;
    }
    uint8_t idx = BT_ULL_LE_HID_CONN_SRV_INVALID;
    bt_ull_role_t role = bt_ull_le_hid_conn_srv_get_role();
    uint8_t cis_state = 0x0;
    bt_ull_le_hid_conn_srv_msg_ind_t msg;
    idx = bt_ull_le_hid_conn_srv_get_idx_by_cis_handle(ind->cis_connection_handle);
    if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cis_disconnect_complete_hdl, idx is invalid!");
        return;
    }
    cis_state = bt_ull_le_hid_conn_srv_get_cis_state(idx);
    msg.cis_disconnected.acl_handle = bt_ull_le_hid_conn_srv_get_acl_handle(idx);
    msg.cis_disconnected.device_type = bt_ull_le_hid_conn_srv_get_device_type(idx);
    msg.cis_disconnected.reason = ind->reason;
    msg.status = status;
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cis_disconnect_complete_hdl, cis_state: %d, status: %d", cis_state, status);
    if (status < 0) {
        if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTING == cis_state) {
            __ASSERT_NO_MSG(0);
        }
    } else {
        if (role == BT_ULL_ROLE_SERVER) {
            bt_ull_le_hid_conn_srv_set_acl_handle(idx, 0xFFFF);
            bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED);
        } else {
            bt_ull_le_hid_conn_srv_clear_cis_info(idx);
            if (!bt_ull_le_hid_conn_srv_get_connected_link()) {
                bt_ull_le_hid_conn_srv_set_cig_id(BT_ULL_LE_HID_CONN_SRV_CIG_ID_NONE);
                bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_NONE);
            }
        }
    }
    bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_CIS_DISCONNECTED_IND, &msg);
}

#if defined(CONFIG_ULL_HID_LE_CENTRAL)
static void bt_ull_le_hid_conn_srv_remove_cig_params_cnf_hdl(int status, bt_ull_le_remove_air_hid_cig_cnf_t *cnf)
{
    uint8_t i = 0;
    uint8_t cig_state = bt_ull_le_hid_conn_srv_get_cig_state();
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_remove_cig_params_cnf_hdl, cig state: %d, status: %d: %d, cnf: %x", \
        cig_state, status, cnf);
    if (status < 0) {
        if (BT_ULL_LE_HID_CONN_SRV_CIG_STATE_REMOVING != cig_state) {
            return;
        }
        bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_CREATED);
        return;
    } else {
        if (BT_ULL_LE_HID_CONN_SRV_CIG_STATE_REMOVING != cig_state) {
            return;
        }
        bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_NONE);
        bt_ull_le_hid_conn_srv_set_cig_id(BT_ULL_LE_HID_CONN_SRV_CIG_ID_NONE);
        for (i = 0;i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
            bt_ull_le_hid_conn_srv_clear_cis_info(i);
        }

        bt_ull_le_hid_conn_srv_msg_ind_t msg;
        msg.status = status;
        bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_CIG_REMOVED_IND, &msg);
    }

}

static void bt_ull_le_hid_conn_srv_create_cis_cnf_hdl(int status, void *cnf)
{
    uint8_t i =0;
    bt_ull_le_hid_conn_srv_msg_ind_t msg;
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_create_cis_cnf_hdl, status: %d", status);
    bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS);
    if (status < 0) {
        for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
            if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING == bt_ull_le_hid_conn_srv_get_cis_state(i)) {
                bt_ull_le_hid_conn_srv_set_cis_state(i, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED);
                msg.status = status;
                msg.cis_connected.acl_handle = 0xFFFF;
                msg.cis_connected.device_type = bt_ull_le_hid_conn_srv_get_device_type(i);
                msg.cis_connected.rr_level = bt_ull_le_hid_conn_srv_get_rr_level();
                bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_CIS_CONNECTED_IND, &msg);
            }
        }
    }
}

static void bt_ull_le_hid_conn_srv_cancel_create_cnf_hdl(int status, void *cnf)
{
    uint8_t i = 0;
    uint8_t idx = BT_ULL_LE_HID_CONN_SRV_INVALID;
    bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS);
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
        if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CANCEL_CONNECTING == bt_ull_le_hid_conn_srv_get_cis_state(i)) {
            idx = i;
            break;
        }
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cancel_create_cnf_hdl, status: %d, idx: %d", status, idx);
    if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx) {
        return;
    }

    if (status < 0) {
        bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING);
    }
    bt_ull_le_hid_conn_srv_msg_ind_t msg;
    msg.status = status;
    msg.cancel_create.device_type = bt_ull_le_hid_conn_srv_get_device_type(idx);
    bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_CIS_CANCEL_CREATE_IND, &msg);
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *cancel = bt_ull_le_hid_conn_srv_search_cmd_node_by_type(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS);
    if (cancel) {
        BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS_T *data = BT_ULL_LE_HID_GET_CMD_PARAM(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS, cancel);
        bt_ull_le_hid_conn_srv_next_action_hdl(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS, data);
        if (data) {
            bt_ull_le_srv_memory_free(data);
        }
        bt_ull_le_hid_conn_srv_delete_cmd_node(cancel);
    }
}

static const bt_ull_le_hid_conn_srv_cig_params_t* bt_ull_le_hid_conn_srv_get_cig_params(bt_ull_le_hid_srv_app_scenario_t scenario)
{
    uint8_t i = 0;
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_AIR_PARAMS_MAX_NUM; i ++) {
        if (g_air_cig_params_tab[i].scenario == scenario) {
            return &g_air_cig_params_tab[i];
        }
    }
    return NULL;
}
#endif

#if defined(CONFIG_ULL_HID_LE_PERIPHERAL)
static void bt_ull_le_hid_conn_srv_sync_cis_cnf_hdl(int status, void *cnf)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_sync_cis_cnf_hdl, status: %d", status);
    uint8_t i = 0;
    bt_ull_le_hid_conn_srv_msg_ind_t msg;
    bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS);
    if (status < 0) {
        for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
            if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING == bt_ull_le_hid_conn_srv_get_cis_state(i)) {
                bt_ull_le_hid_conn_srv_set_cis_state(i, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTED);
                bt_ull_le_hid_conn_srv_set_device_type(i, BT_ULL_LE_HID_SRV_DEVICE_NONE);
                break;
            }
        }
        msg.status = status;
        msg.cis_connected.acl_handle = 0xFFFF;
        msg.cis_connected.device_type = bt_ull_le_hid_conn_srv_get_device_type(i);
        msg.cis_connected.rr_level = bt_ull_le_hid_conn_srv_get_rr_level();
        bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_CIS_CONNECTED_IND, &msg);
    }
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *sync = bt_ull_le_hid_conn_srv_search_cmd_node_by_type(BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS);
    if (sync) {
        BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS_T *data = BT_ULL_LE_HID_GET_CMD_PARAM(BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS, sync);
        bt_ull_le_hid_conn_srv_next_action_hdl(BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS, data);
        if (data) {
            bt_ull_le_srv_memory_free(data);
        }
        bt_ull_le_hid_conn_srv_delete_cmd_node(sync);
    }

}

static void bt_ull_le_hid_conn_srv_cancel_sync_cnf_hdl(int status, void *cnf)
{
    uint8_t i = 0;
    uint8_t idx = BT_ULL_LE_HID_CONN_SRV_INVALID;
    bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS);
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
        if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CANCEL_CONNECTING == bt_ull_le_hid_conn_srv_get_cis_state(i)) {
            idx = i;
            break;
        }
    }
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_cancel_sync_cnf_hdl, status: %d, idx: %d", status, idx);
    if (BT_ULL_LE_HID_CONN_SRV_INVALID == idx) {
        return;
    }

    if (status < 0) {
        bt_ull_le_hid_conn_srv_set_cis_state(idx, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTING);
    }
    bt_ull_le_hid_conn_srv_msg_ind_t msg;
    msg.status = status;
    msg.cancel_sync.device_type = bt_ull_le_hid_conn_srv_get_device_type(idx);
    bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_CIS_CANCEL_SYNC_IND, &msg);
    bt_ull_le_hid_conn_srv_cache_cmd_node_t *cancel = bt_ull_le_hid_conn_srv_search_cmd_node_by_type(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS);
    if (cancel) {
        BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS_T *data = BT_ULL_LE_HID_GET_CMD_PARAM(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS, cancel);
        bt_ull_le_hid_conn_srv_next_action_hdl(BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS, data);
        if (data) {
            bt_ull_le_srv_memory_free(data);
        }
        bt_ull_le_hid_conn_srv_delete_cmd_node(cancel);
    }

}
#endif

static int bt_ull_le_hid_conn_srv_next_action_hdl(bt_ull_le_hid_conn_srv_cmd_enum next_act, void *data)
{
    int status = 0;
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_next_action_hdl, NEXT ACTION: %d", next_act);
    switch (next_act) {
        #if defined(CONFIG_ULL_HID_LE_CENTRAL)
        case BT_ULL_LE_HID_CONN_SRV_CMD_REMOVE_CIG: {
            status = bt_ull_le_hid_conn_srv_remove_air_cig();
            break;
        }
        case BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS: {
            if (!data) {
                status = -EPERM;
                break;
            }
            BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS_T *cmd = (BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_CREATE_CIS_T *)data;
            status = bt_ull_le_hid_conn_srv_cancel_create_air_cis(cmd->device_type);
            break;
        }
        case BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS: {
            if (!data) {
                status = -EPERM;
                break;
            }
            BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS_T *cmd = (BT_ULL_LE_HID_CONN_SRV_CMD_CREATE_CIS_T *)data;
            status = bt_ull_le_hid_conn_srv_create_air_cis(cmd->kb, cmd->ms, cmd->gp);
            break;
        }
        #endif
        #if defined(CONFIG_ULL_HID_LE_PERIPHERAL)
        case BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS: {
            if (!data) {
                status = -EPERM;
                break;
            }
            BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS_T *cmd = (BT_ULL_LE_HID_CONN_SRV_CMD_SYNC_CIS_T *)data;
            status = bt_ull_le_hid_conn_srv_sync_air_cis(cmd->device_type, &cmd->peer_addr);
            break;
        }
        case BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS: {
            if (!data) {
                status = -EPERM;
                break;
            }
            BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS_T *cmd = (BT_ULL_LE_HID_CONN_SRV_CMD_CANCEL_SYNC_CIS_T *)data;
            status = bt_ull_le_hid_conn_srv_cancel_sync_air_cis(cmd->device_type);
            break;
        }
        #endif
        case BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS: {
            if (!data) {
                status = -EPERM;
                break;
            }
            BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS_T *cmd = (BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS_T *)data;

            status = bt_ull_le_hid_conn_srv_disconnect_air_cis(cmd->acl_handle, cmd->reason);
            break;
        }
        default:
            break;
    }

    return status;
}

static void bt_ull_le_hid_conn_srv_disconnect_cis_cnf_hdl(int status, void *cnf)
{
    bt_ull_le_hid_conn_srv_unlock_cmd(BT_ULL_LE_HID_CONN_SRV_CMD_DISCONNECT_CIS);
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_disconnect_cis_cnf_hdl, status: %x", status);
    if (status < 0) {
        uint8_t i = 0;
        for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
            if (BT_ULL_LE_HID_CONN_SRV_AIR_CIS_DISCONNECTING == bt_ull_le_hid_conn_srv_get_cis_state(i)) {
                bt_ull_le_hid_conn_srv_set_cis_state(i, BT_ULL_LE_HID_CONN_SRV_AIR_CIS_CONNECTED);
            }
        }
    } else {
    }
}

static int bt_ull_le_hid_conn_srv_event_callback(uint32_t msg, int ret, void *data)
{
    switch (msg) {
    case BT_ULL_LE_AIR_HID_CIS_ESTABLISHED_IND: {
        bt_ull_le_air_hid_cis_established_ind_t *event = (bt_ull_le_air_hid_cis_established_ind_t *)data;
        if (!event) {
            __ASSERT_NO_MSG(0);
        }
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] cis established event: status: %x, acl_handle: %x, cis_handle: %x, cis_id: %d, slave_type: %d, uni_AA: %x-%x-%x-%x", \
            ret, event->acl_connection_handle, event->cis_connection_handle, \
            event->cis_id, event->slave_type, \
            event->uni_aa[0], event->uni_aa[1], event->uni_aa[2], event->uni_aa[3]);
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] cis established event: addr: %x:%x:%x:%x:%x:%x", \
            event->peer_aadr.a.val[0], event->peer_aadr.a.val[1], event->peer_aadr.a.val[2], event->peer_aadr.a.val[3], event->peer_aadr.a.val[4], event->peer_aadr.a.val[5]);

#endif
        bt_ull_le_hid_conn_srv_cis_established_hdl(ret, event);
        break;
    }
    case BT_ULL_LE_AIR_HID_CIS_DISCONNECT_COMPLETE_IND: {
        bt_ull_le_air_hid_cis_disconnect_complete_ind_t *event = (bt_ull_le_air_hid_cis_disconnect_complete_ind_t *)data;
        if (!event) {
            __ASSERT_NO_MSG(0);
        }
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] cis disconnect complete event: status: %x, acl_handle: %x, reason: %x", \
            ret, event->cis_connection_handle, event->reason);
#endif

        bt_ull_le_hid_conn_srv_cis_disconnect_complete_hdl(ret, event);
        break;
    }
    case BT_ULL_LE_SET_AIR_HID_REPORT_RATE_CHANGE_IND: {
        bt_ull_le_air_hid_report_rate_change_ind *rr_change = (bt_ull_le_air_hid_report_rate_change_ind *)data;
        bt_ull_le_hid_conn_srv_msg_report_rate_changed_t rr_msg = {0};
        rr_msg.status = rr_change->status;
        rr_msg.report_rate.rr_level = rr_change->report_rate_level;
        rr_msg.report_rate.phy = rr_change->phy;
        bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_REPORT_RATE_CHANGED_IND, &rr_msg);
        break;
    }
    case BT_ULL_LE_SET_AIR_HID_CIS_ADV_REPORT_IND: {
        bt_ull_le_air_hid_cis_adv_report_ind *adv_report = (bt_ull_le_air_hid_cis_adv_report_ind *)data;
        bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_ADV_REPORT_IND, adv_report);
        break;
    }
    #if defined(CONFIG_ULL_HID_LE_CENTRAL)
    case BT_ULL_LE_SET_AIR_HID_CIS_CONN_INFO_IND: {
        bt_ull_le_air_hid_conn_info_ind_t *conn_info_ind = (bt_ull_le_air_hid_conn_info_ind_t *)data;
        bt_ull_le_hid_conn_srv_msg_ind_t msg;
        msg.conn_info.status = conn_info_ind->status;
        msg.conn_info.phy = conn_info_ind->phy;
        msg.conn_info.tx_power = conn_info_ind->tx_power;
        msg.conn_info.rx_rssi = conn_info_ind->rx_rssi;
        msg.conn_info.wb_duration = conn_info_ind->wb_duration;
        memcpy(msg.conn_info.wb_rssi, conn_info_ind->wb_rssi, BT_CHANNEL_NUMBER);
        memcpy(msg.conn_info.PER, conn_info_ind->PER, BT_CHANNEL_NUMBER * sizeof(uint16_t));
        memcpy(msg.conn_info.channel_map, conn_info_ind->channel_map, BT_CHANNEL_NUMBER/8);
        bt_ull_le_hid_conn_srv_notify_msg(BT_ULL_LE_HID_CONN_SRV_MSG_CONN_INFO_IND, &msg);
        break;
    }
    case BT_ULL_LE_SET_AIR_HID_CIG_PARAMS_CNF: {
        bt_ull_le_set_air_hid_cig_cnf_t *event = (bt_ull_le_set_air_hid_cig_cnf_t *)data;
        if (!event) {
            __ASSERT_NO_MSG(0);
        }
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] set cig parameter cmd status: status: %x, cig_id: %x, cis_count: %x", \
            ret, event->cig_id, event->cis_count);
#endif

        bt_ull_le_hid_conn_srv_create_cig_params_cnf_hdl(ret, event);
        break;
    }
    case BT_ULL_LE_REMOVE_AIR_HID_CIG_CNF: {
        bt_ull_le_remove_air_hid_cig_cnf_t *event = (bt_ull_le_remove_air_hid_cig_cnf_t *)data;
        if (!event) {
            __ASSERT_NO_MSG(0);
        }
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] remove cig parameter cmd status: status: %x, cig_id: %x", \
            ret, event->cig_id);
#endif

        bt_ull_le_hid_conn_srv_remove_cig_params_cnf_hdl(ret, event);
        break;
    }
    case BT_ULL_LE_CREATE_AIR_HID_CIS_CNF: {
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] create air cis cmd status: status: %x", \
            ret);
#endif

        bt_ull_le_hid_conn_srv_create_cis_cnf_hdl(ret, data);
        break;
    }

    case BT_ULL_LE_CANCEL_CREATE_AIR_HID_CIS_CNF: {
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] cacnel create air cis cmd status: status: %x", \
            ret);
#endif
        bt_ull_le_hid_conn_srv_cancel_create_cnf_hdl(ret, data);
        break;
    }
    #endif
    #if defined(CONFIG_ULL_HID_LE_PERIPHERAL)
    case BT_ULL_LE_SYNC_AIR_HID_CIS_CNF: {
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] sync air cis cmd status: status: %x", \
            ret);
#endif

        bt_ull_le_hid_conn_srv_sync_cis_cnf_hdl(ret, data);
        break;
    }
    case BT_ULL_LE_CANCEL_SYNC_AIR_HID_CIS_CNF: {
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] cacnel sync air cis cmd status: status: %x", \
            ret);
#endif
        bt_ull_le_hid_conn_srv_cancel_sync_cnf_hdl(ret, data);
        break;
    }
    #endif
    case BT_ULL_LE_DISCONNECT_AIR_HID_CIS_CNF: {
#ifdef BT_ULL_LE_HID_CONN_SRV_DEBUG
        LOG_INF(BT_ULL_LE_HID_CONN_LOG"[EVT] disconnect air cis cmd status: status: %x", \
            ret);
#endif
        bt_ull_le_hid_conn_srv_disconnect_cis_cnf_hdl(ret, data);
        break;
    }
    default:
        break;
    }
    return 0;
}

int bt_ull_le_hid_conn_srv_init(bt_ull_role_t role, bt_ull_le_hid_conn_srv_callback_t cb)
{
    LOG_INF(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_init, callback: 0x%x, role: %d", cb, role);
    int status = -EPERM;
    bt_ull_le_srv_memset(&g_ull_hid_srv_ctx, 0, sizeof(bt_ull_le_hid_conn_srv_contex_t));
    if (0 != bt_ull_le_hid_conn_srv_register_callback(cb)) {
        LOG_ERR(BT_ULL_LE_HID_CONN_LOG" bt_ull_le_hid_conn_srv_init, call back function is null!");
        return -EPERM;
    }

    g_ull_hid_srv_ctx.cmd_list_header = NULL;
#ifdef CONFIG_AIR_PRODUCT_TYPE_KEYBOARD
    g_ull_hid_srv_ctx.scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_82;
#elif CONFIG_AIR_PRODUCT_TYPE_MOUSE
    g_ull_hid_srv_ctx.scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_81;
#elif CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER
    g_ull_hid_srv_ctx.scenario = BT_ULL_LE_HID_SRV_APP_SCENARIO_83;
#endif
    g_ull_hid_srv_ctx.report_rate.rr_level = BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_8;
    g_ull_hid_srv_ctx.report_rate.phy = BT_ULL_LE_SRV_PHY_LE_4M;
    bt_ull_le_hid_conn_srv_set_role(role);
    bt_ull_le_hid_conn_srv_set_phy_internal(BT_ULL_LE_SRV_PHY_LE_2M);
    bt_ull_le_init();
    bt_ull_le_register_cb(bt_ull_le_hid_conn_srv_event_callback);
    return status;
}

void bt_ull_le_hid_conn_srv_deinit(void)
{
    uint8_t i = 0;
    bt_ull_le_hid_conn_srv_delete_all_cmd_node();
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CIS_MAX_NUM; i ++) {
        bt_ull_le_hid_conn_srv_clear_cis_info(i);
        bt_ull_le_srv_memset(&g_ull_hid_srv_ctx.cis_info[i].peer_addr, 0, sizeof(bt_addr_le_t));
    }
    for (i = 0; i < BT_ULL_LE_HID_CONN_SRV_CMD_MAX; i ++) {
        bt_ull_le_hid_conn_srv_unlock_cmd(i);
    }
    bt_ull_le_hid_conn_srv_set_cig_state(BT_ULL_LE_HID_CONN_SRV_CIG_STATE_NONE);
    bt_ull_le_hid_conn_srv_set_cig_id(BT_ULL_LE_HID_CONN_SRV_CIG_ID_NONE);
}

