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

//#define PAWR_PRO_UT_DEBUG
int ull_sync_init(void);
int ull_sync_reset(void);
uint16_t ull_sync_handle_get(struct ll_sync_set *sync);
struct ll_sync_set *ull_sync_is_enabled_get(uint16_t handle);
void ull_sync_release(struct ll_sync_set *sync);
void ull_sync_setup_addr_check(struct ll_scan_set *scan, uint8_t addr_type,
			       uint8_t *addr, uint8_t rl_idx);
bool ull_sync_setup_sid_match(struct ll_scan_set *scan, uint8_t sid);
void ull_sync_setup(struct ll_scan_set *scan, struct ll_scan_aux_set *aux,
		    struct node_rx_pdu *node_rx, struct pdu_adv_sync_info *si);
void ull_sync_setup_reset(struct ll_scan_set *scan);
void ull_sync_established_report(memq_link_t *link, struct node_rx_pdu *rx);
void ull_sync_done(struct node_rx_event_done *done);
void ull_sync_chm_update(uint8_t sync_handle, uint8_t *acad, uint8_t acad_len);
int ull_sync_slot_update(struct ll_sync_set *sync, uint32_t slot_plus_us,
			 uint32_t slot_minus_us);
struct ll_sync_set *ull_sync_is_valid_get(struct ll_sync_set *sync);
void ull_sync_transfer_received(struct ll_conn *conn, uint16_t service_data,
				struct pdu_adv_sync_info *si, uint16_t conn_event_count,
				uint16_t last_pa_event_counter, uint8_t sid,
				uint8_t addr_type, uint8_t sca, uint8_t phy,
				uint8_t *adv_addr, uint16_t sync_conn_event_count,
				uint8_t addr_resolved);
#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC_RSP)
void ull_sync_rsp_transfer_received(struct ll_conn *conn, uint16_t service_data,
				struct pdu_adv_sync_info *si, uint16_t conn_event_count,
				uint16_t last_pa_event_counter, uint8_t sid,
				uint8_t addr_type, uint8_t sca, uint8_t phy,
				uint8_t *adv_addr, uint16_t sync_conn_event_count,
				uint8_t addr_resolved, uint8_t *rsp_aa, uint8_t num_subevent,
				uint8_t subevent_interval, uint8_t rsp_slot_delay,
				uint8_t rsp_slot_spacing);
struct ll_sync_set *ull_sync_create(uint8_t sid, uint16_t timeout, uint16_t skip,
					   uint8_t cte_type, uint8_t rx_enable, uint8_t nodups);

uint32_t ull_sync_rsp_data_time_get(struct pdu_adv *pdu, uint8_t phy);
uint32_t ull_sync_rsp_start(struct ll_sync_set *sync, uint32_t ref_ticks_anchor);
uint8_t ull_sync_rsp_data_set(uint16_t handle, uint8_t data_len, uint8_t const *const data);
bool ull_sync_rsp_check_sync_subevent(struct ll_sync_set *sync, uint8_t cur_subevent);
uint8_t ull_sync_rsp_get_sync_subevent_index(struct ll_sync_set *sync, uint8_t cur_subevent);
void ull_sync_rsp_switch_prepare_cb_func(struct ll_sync_set *sync);
void ull_sync_rsp_update(struct ll_sync_set *sync, uint32_t ticks_drift_minus, uint32_t ticks_drift_plus, uint16_t lazy, uint8_t force);
void ull_sync_rsp_clean_up(struct ll_sync_set *sync, void *stop_op_cb);
void ull_sync_rsp_scan_aux_update_timing(struct node_rx_pdu *rx, struct node_rx_pdu **rx_incomplete, uint8_t *yield_handle);
uint8_t ull_sync_rsp_terminate(uint16_t handle);
void ull_sync_rsp_record_anchor(struct ll_sync_set *sync, uint32_t ticks_anchor);
void ull_sync_rsp_conn_init(struct lll_sync *lll);
void ull_sync_rsp_init_subevent_ctx(struct lll_sync *lll);
struct lll_sync_wr_subevent* ull_sync_rsp_malloc_subevent_ctx(struct lll_sync *lll, uint8_t subevent);
struct lll_sync_wr_subevent *ull_sync_rsp_get_subevent_ctx(struct lll_sync *lll, uint8_t subevent);
uint8_t ull_sync_rsp_delete_subevent_ctx(struct lll_sync *lll, uint8_t subevent) ;

#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC_RSP_PRO)
void ull_sync_pro_check_acad(struct node_rx_pdu *rx);
uint8_t ull_sync_rsp_pro_set_param(uint16_t handle, uint8_t id, uint32_t start_addr, uint16_t length, uint16_t block_size);
#endif

#endif

