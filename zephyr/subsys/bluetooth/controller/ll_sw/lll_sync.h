/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 * Copyright (c) 2026 Airoha Technology Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Modifications:
2026-03-05 by Airoha - Merge PAST from zephyr 4.0.0
2026-03-05 by Airoha - Add PAwR and Airoha PAwR proprietary implmentation.
*/

/* Periodic advertisements synchronization status. */
enum sync_status {
	SYNC_STAT_ALLOWED,
	SYNC_STAT_READY,
	SYNC_STAT_CONT_SCAN,
	SYNC_STAT_TERM
};

#define LLL_SYNC_SUBEVENT_NUM_MAX 0x2
#define LLL_SYNC_SUBEVENT_NUM_INVALID 0xFF

#define PAWR_NORMAL_MODE   0x00
#define PAWR_PROPRIETARY_MODE  0x01

#define PAWR_PROPRIETARY_PAYLOAD_COUNT_MAX 0x0F //TBD
//#define PAWR_PRO_UT_DEBUG

struct lll_sync_wr_subevent {
    uint8_t  subevent_idx;
    uint16_t skip_prepare;
	uint16_t skip_event;
	uint16_t event_counter;

    uint32_t window_widening_periodic_us;
    uint32_t window_widening_max_us;
    uint32_t window_widening_prepare_us;
    uint32_t window_widening_event_us;
    uint32_t window_size_event_us;
};

#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC_RSP_PRO)
struct lll_sync_pro {
	uint8_t  pawr_mode;// 0:Normal mode 1:Proprietary mode
	uint8_t  id;
	uint8_t  sse_start;//CR
	uint8_t  sse_end;
	uint8_t  sse_count;//The total sse count for update complete image
	uint8_t  last_rx_sse;
	uint8_t  last_rx_good_sse;
	uint8_t  cur_rx_sse;
	uint8_t  last_rx_seq;
	uint8_t  cur_rx_seq;
	uint8_t  polling_sse_start;
	uint8_t  polling_sse_end;
	//uint8_t  slot_offset_us;
	uint8_t  total_sse_count;
	uint8_t  rcvd_good_count;//CR
	uint8_t  rx_ch[10];//For Rx To Debug
#ifdef PAWR_PRO_UT_DEBUG
	uint8_t  access_addr[4];
	uint8_t  data_chan_map[5];
	uint8_t  data_chan_count:6;
	uint16_t data_chan_id;
	uint16_t event_counter;
#endif
	//uint8_t  sse_max_count;
	//uint8_t  bn_current;//burst number
	bool     new_packet;//true: update new image data   false: re-transmission old image data  CR
	//bool     ack_lost;//true: ack lost false: ack not lost
	bool	 rcvd_report;
	uint16_t mem_block_size;//must 4*N
	uint16_t ft;//Flush Point (PA EVT CNT)
	uint16_t sse_interval_us;
	uint16_t share_buf_length;
	uint32_t share_buf_start_addr;
	uint32_t rx_addr;
	uint32_t rx_map;
	uint32_t window_widening_us;
	uint32_t window_widening_max_us;
	//uint32_t payload_addr[PAWR_PROPRIETARY_PAYLOAD_COUNT_MAX];
	uint32_t payload_total_length;
	uint32_t slot_offset_us;
	struct node_rx_pdu *node_rx_tailored_data_recv;
};

//TBD:need modify
#if 0
struct lll_sync_pro_mem_ctrl {
	uint16_t buf_length;
	uint8_t  packet_count;//CR
	uint16_t block_size;
	uint32_t receive_data_total_length;
	uint8_t  write_state;/*0x00:Init, 0x01:write on-going, 0x02:write done, 0xFF:write error*/
	uint8_t  read_state; /*0x00:Init, 0x01:read on-going, 0x02:read done, 0xFF:read error*/
	uint8_t  reserved;
};
#endif

struct lll_sync_pro_mem_ctrl {
	uint8_t  packet_count;//CR
	uint8_t  write_state;/*0x00:Init, 0x01:write on-going, 0x02:write done, 0xFF:write error*/
	uint8_t  read_state; /*0x00:Init, 0x01:read on-going, 0x02:read done, 0xFF:read error*/
	uint8_t  reserved;
	uint16_t buf_length;
	uint16_t block_size;
	uint32_t receive_data_total_length;
}__packed;




struct lll_sync_pro_data_ext_hdr {
	uint8_t ext_seq_num:4;
	uint8_t rfu:4;
};
#endif

struct lll_sync {
	struct lll_hdr hdr;
#if defined(CONFIG_BT_PERIPHERAL)
    //struct lll_conn *conn; /*for PAwR Connection*/
#endif
	uint8_t access_addr[4];
	uint8_t crc_init[3];

	uint8_t phy:3;
	/* Bitmask providing not allowed types of CTE. */
	uint8_t cte_type:5;
	/* The member is required for filtering by CTE type. If filtering policy is disabled then
	 * synchronization is terminated for periodic advertisements with wrong CTE type.
	 */
	uint8_t filter_policy:1;
	uint8_t is_rx_enabled:1;
	uint8_t is_aux_sched:1;

#if defined(CONFIG_BT_CTLR_SYNC_ISO) || \
	defined(CONFIG_BT_CTLR_SYNC_TRANSFER_RECEIVER) || \
	defined(CONFIG_BT_CTLR_SYNC_TRANSFER_SENDER)
	uint8_t sca:3;
#endif /* CONFIG_BT_CTLR_SYNC_ISO || CONFIG_BT_CTLR_SYNC_TRANSFER_RECEIVER/SENDER */

#if defined(CONFIG_BT_CTLR_SCAN_AUX_SYNC_RESERVE_MIN)
	/* Counter used by LLL abort of event when in unreserved time space to
	 * provide near fair scheduling of overlapping multiple Periodic
	 * Sync sets.
	 */
	uint8_t abort_count;
#endif /* CONFIG_BT_CTLR_SCAN_AUX_SYNC_RESERVE_MIN */

	uint16_t skip_prepare;
	uint16_t skip_event;
	uint16_t event_counter;

	uint16_t data_chan_id;
	struct {
		uint8_t data_chan_map[5];
		uint8_t data_chan_count:6;
	} chm[2];
	uint8_t  chm_first;
	uint8_t  chm_last;
	uint16_t chm_instant;

	uint32_t window_widening_periodic_us;
	uint32_t window_widening_max_us;
	uint32_t window_widening_prepare_us;
	uint32_t window_widening_event_us;
	uint32_t window_size_event_us;

	/* used to store lll_aux when chain is being scanned */
	struct lll_scan_aux *volatile lll_aux;

#if defined(CONFIG_BT_CTLR_DF_SCAN_CTE_RX)
	struct lll_df_sync df_cfg;
	/* Member stores one additional IQ report rx node for notification of insufficient
	 * resources to sample all CTEs in currently pending synchronization event.
	 * The member is temporary storage used between prepare of an event and IQ data report
	 * generation.
	 */
	struct node_rx_iq_report *node_cte_incomplete;
	/* Member stores information if there were insufficient IQ report rx nodes for all CTEs
	 * in pending synchronization event.
	 */
	bool is_cte_incomplete;
#endif /* CONFIG_BT_CTLR_DF_SCAN_CTE_RX */

    bool is_pawr;
//#if defined(CONFIG_BT_CTLR_ADV_PERIODIC_SYNC_RSP)
#if (1)
    uint8_t current_subevent;
    //struct lll_adv_pdu rsp_data; //for PAwR Sync Rsp use
    struct lll_sync_wr_subevent lll_subevent_ctx[LLL_SYNC_SUBEVENT_NUM_MAX]; //Each subevent has its own independent context.
    uint8_t  rsp_data[251];
    uint8_t  rsp_data_len;
	uint8_t  cur_subevent_channel;
    uint8_t  rsp_aa[4];
	bool     recv_conn_req;
	struct lll_conn *conn; /*for PAwR Connection*/
#endif
#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC_RSP_PRO)
	struct lll_sync_pro sync_pro;
#endif
};

int lll_sync_init(void);
int lll_sync_reset(void);
void lll_sync_create_prepare(void *param);
void lll_sync_prepare(void *param);
enum sync_status lll_sync_cte_is_allowed(uint8_t cte_type_mask, uint8_t filter_policy,
					 uint8_t rx_cte_time, uint8_t rx_cte_type);
extern uint16_t ull_sync_lll_handle_get(struct lll_sync *lll);
extern struct lll_sync *ull_sync_lll_is_valid_get(struct lll_sync *lll);

void lll_sync_wr_prepare(void *param);
void lll_sync_wr_send_response_prepare(void *param);
struct pdu_adv *lll_sync_wr_init_rsp_data(struct lll_sync *lll);

#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC_RSP_PRO)
void lll_sync_rsp_pro_prepare(void *param);
#ifdef PAWR_PRO_UT_DEBUG
void* lll_sync_pro_get_share_buf_addr(void);
#endif
#endif

