/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 * Copyright (c) 2026 Airoha Technology Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Modifications:
2026-03-05 by Airoha - Merge PAST from zephyr 4.0.0
2026-03-05 by Airoha - Add PAwR implmentation.
*/

#define LL_SYNC_STATE_IDLE       0x00
#define LL_SYNC_STATE_ADDR_MATCH 0x01
#define LL_SYNC_STATE_CREATED    0x02

#if defined(CONFIG_BT_CTLR_SYNC_ISO)
struct ll_sync_iso_set;
#endif /* CONFIG_BT_CTLR_SYNC_ISO */

#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC_RSP)
#define MAX_PAWR_SYNC_SUBEVENT 0x80
#define MAX_PAWR_SUBEVENT_RSP_DATA_LEN 251
#define PAWR_DATA_NON_USED 0
#define PAWR_DATA_USED 1

typedef struct ll_per_adv_sync_subevent {
    uint8_t  data_state;
    uint16_t sync_handle;
    uint16_t properties;
    uint8_t  num_subevents;
    uint8_t  subevents[MAX_PAWR_SYNC_SUBEVENT];
} LE_PER_ADV_SYNC_SUBEVENT_STRUCT;



typedef struct stru_le_per_adv_rsp_param {
    uint8_t  data_state;
    uint16_t sync_handle;
    uint16_t req_event;  //event counter
    uint8_t  req_subevent;
    uint8_t  rsp_subevent;
    uint8_t  rsp_slot;
    uint8_t  rsp_data_length;
    uint8_t  rsp_data[MAX_PAWR_SUBEVENT_RSP_DATA_LEN];

} LE_PER_ADV_RSP_PARAM_STRUCT;

typedef struct stru_le_per_adv_rsp_timing {
    //uint32_t   rsp_aa;
    uint8_t    num_subevent;
    uint8_t    subevent_interval;

    uint8_t    rsp_slot_delay;
    uint8_t    rsp_slot_spacing;

    uint8_t    subevent;
	uint8_t    rsp_aa[4];
	uint32_t   subevent_interval_us;
    uint32_t   persync_ticks_anchor;//subevent#0 ticks_anchor
    uint32_t   subevent_ticks_anchor;
    uint32_t   rsp_ticks_anchor;
    uint32_t   radio_aa_us;
    uint32_t   rsp_offset_us;
    uint32_t   interval_us;
} LE_PER_ADV_RSP_TIMING_STRUCT;
#endif
struct ll_sync_set {
	struct ull_hdr ull;
	struct lll_sync lll;

	uint16_t skip;
	uint16_t timeout;
	/* Non-zero when sync is setup. It can be in two sub-stated:
	 * - Waiting for first AUX_SYNC_IND, before sync established was notified to Host.
	 *   If sync establishment is in progress node_rx_sync_estab is not NULL.
	 * - sync is already established, node_rx_sync_estab is NULL.
	 */
	uint16_t volatile timeout_reload;
	uint16_t timeout_expire;

	/* Member to store periodic advertising sync prepare.
	 * Also serves as a flag to inform if sync established was
	 * already generated.
	 */
	void (*lll_sync_prepare)(void *param);

#if defined(CONFIG_BT_CTLR_CHECK_SAME_PEER_SYNC) || \
	defined(CONFIG_BT_CTLR_SYNC_PERIODIC_ADI_SUPPORT)
	uint8_t peer_id_addr[6];
	uint8_t peer_id_addr_type:1;
#endif /* CONFIG_BT_CTLR_CHECK_SAME_PEER_SYNC ||
	* CONFIG_BT_CTLR_SYNC_PERIODIC_ADI_SUPPORT
	*/
       uint8_t peer_addr_resolved:1;
	uint8_t rx_enable:1;

#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC_ADI_SUPPORT)
	uint8_t nodups:1;
#endif

#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC_CTE_TYPE_FILTERING) && \
	!defined(CONFIG_BT_CTLR_CTEINLINE_SUPPORT)
	/* Member used to notify event done handler to terminate sync scanning.
	 * Used only when no HW support for parsing PDU for CTEInfo.
	 */
	uint8_t is_term:1;
#endif /* CONFIG_BT_CTLR_SYNC_PERIODIC_CTE_TYPE_FILTERING && !CONFIG_BT_CTLR_CTEINLINE_SUPPORT */

	uint8_t is_stop:1; /* sync terminate or cancel requested */
	uint8_t sync_expire:3; /* countdown of 6 before fail to establish */

#if defined(CONFIG_BT_CTLR_SYNC_ISO)
	uint8_t enc : 1;
	uint8_t num_bis : 5;
#endif /* CONFIG_BT_CTLR_SYNC_ISO */

//#if defined(CONFIG_BT_CTLR_CHECK_SAME_PEER_SYNC)
	uint8_t sid;
//#endif /* CONFIG_BT_CTLR_CHECK_SAME_PEER_SYNC */

	/* node rx type with memory aligned storage for sync lost reason.
	 * HCI will reference the value using the pdu member of
	 * struct node_rx_pdu.
	 */
	struct {
		struct node_rx_pdu rx;
		/* Dummy declaration to ensure space allocated to hold one pdu bytes */
		uint8_t dummy;
	} node_rx_lost;

	/* Not-Null when sync was setup and Controller is waiting for first AUX_SYNC_IND PDU.
	 * It means the sync was not estalished yet.
	 */
	struct node_rx_pdu *node_rx_sync_estab;

#if defined(CONFIG_BT_CTLR_SYNC_ISO)
	struct {
		struct node_rx_pdu *node_rx_estab;

		/* Non-Null when creating sync, reset in ISR context on
		 * synchronisation state and checked in Thread context when
		 * cancelling sync create, hence the volatile keyword.
		 */
		struct ll_sync_iso_set *volatile sync_iso;
	} iso;
#endif /* CONFIG_BT_CTLR_SYNC_ISO */


	uint16_t data_len;

#if defined(CONFIG_BT_CTLR_SYNC_TRANSFER_SENDER)
	uint16_t interval;
#endif /* CONFIG_BT_CTLR_SYNC_TRANSFER_SENDER */

    bool       is_pawr;
#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC_RSP)
	void (*lll_sync_wr_prepare)(void *param);
    LE_PER_ADV_RSP_TIMING_STRUCT    pawr_timing;
    LE_PER_ADV_SYNC_SUBEVENT_STRUCT pawr_sync_subevent;
    LE_PER_ADV_RSP_PARAM_STRUCT     pawr_sync_rsp_param;
#endif
};

struct node_rx_sync {
	uint8_t status;
	uint8_t  phy;
	uint16_t interval;
	uint8_t  sca;
//#ifdef PAWR
    uint8_t    num_subevent;
    uint8_t    subevent_interval;
    uint8_t    rsp_slot_delay;
    uint8_t    rsp_slot_spacing;
//#endif

};
struct node_rx_past_received {
	struct node_rx_sync rx_sync;
	uint16_t conn_handle;
	uint16_t service_data;
};

#if defined(CONFIG_BT_CTLR_SYNC_ISO)
struct ll_sync_iso_set {
	struct ull_hdr ull;
	struct lll_sync_iso lll;

	/* Periodic Advertising Sync that contained the BIGInfo */
	struct ll_sync_set *sync;

	/* Periodic Advertising Sync timeout */
	uint16_t timeout;
	uint16_t volatile timeout_reload; /* Non-zero when sync established */
	uint16_t timeout_expire; /* timeout countdown */
	uint8_t big_handle;

	/* Encryption */
	uint8_t gltk[16];

	/* node rx type with memory aligned storage for sync lost reason.
	 * HCI will reference the value using the pdu member of
	 * struct node_rx_pdu.
	 */
	struct {
		struct node_rx_pdu rx;
		/* Dummy declaration to ensure space allocated to hold two pdu bytes */
		uint8_t dummy[2];
	} node_rx_lost;
};

struct node_rx_sync_iso {
	uint8_t status;
	uint16_t interval;
};
#endif /* CONFIG_BT_CTLR_SYNC_ISO */
