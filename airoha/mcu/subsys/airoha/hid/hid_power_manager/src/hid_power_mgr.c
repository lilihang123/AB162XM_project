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

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "hid_power_mgr.h"
#include "hal_clock_internal.h"
#include "hal_dvfs.h"
/******************************************************************************/
/*  macro                                                                     */
/******************************************************************************/

#define thisMOD    "pwmgr"
#define thisMODULE pwmgr
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  typedef                                                                   */
/******************************************************************************/
#if !defined(CONFIG_AIR_DISABLE_LC_SLEEP)
#define LC_SLEEP_UNLOCK_DELAY_SEC   1
#endif

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
#if !defined(CONFIG_AIR_DISABLE_LC_SLEEP)
static void hid_power_mgr__unlock_sleep_delay_timeout(struct k_timer *timer_id);
#endif

static void hid_power_mgr_system_low_clock_execution(struct k_timer *timer_id);

/******************************************************************************/
/* callback function                                                        */
/******************************************************************************/


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#if !defined(CONFIG_AIR_DISABLE_LC_SLEEP)
static uint8_t lc_slp_policy_ctrl = LC_SLP_POLICY_CTR_UNDEFINED;
static uint8_t lc_slp_policy = LC_SLP_POLICY_DISABLE;

K_TIMER_DEFINE(hid_power_mgr__delay_timer_hdl, hid_power_mgr__unlock_sleep_delay_timeout, NULL);
#endif

K_TIMER_DEFINE(hid_power_mgr__low_clock_timer_hdl, hid_power_mgr_system_low_clock_execution, NULL);

bool hid_power_mgr_low_clock_status = false;
clk_mux_sel_idx_t hid_power_mgr_sys_clock_id;

/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/

/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
#if !defined(CONFIG_AIR_DISABLE_LC_SLEEP)
static void hid_power_mgr__unlock_sleep_delay_timeout(struct k_timer *timer_id)
{
    DBG_LOGI(thisMOD,"hid_power_mgr__unlock_sleep_delay_timeout");
    hid_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_SHORT_SLEEP);
}

static void hid_power_mgr__start_LC_sleep_timers()
{
    k_timer_start(&hid_power_mgr__delay_timer_hdl, K_SECONDS(LC_SLEEP_UNLOCK_DELAY_SEC), K_NO_WAIT);
}

void hid_power_mgr__stop_LC_sleep_timers()
{
    DBG_LOGI(thisMOD,"hid_power_mgr__stop_LC_sleep_timers");
    k_timer_stop(&hid_power_mgr__delay_timer_hdl);
}


void hid_power_mgr__set_LC_sleep_pollicy(uint8_t policyctrl, uint8_t policy)
{
    #define BT_HCI_OP_VS_SET_LC_SLP_POLICY		BT_OP(BT_OGF_VS, 0x00C2)
    #define LC_SLEEP_POLICY_CTRL_MASK_PARA_SIZE 2

    int err = 0;

    DBG_LOGI(thisMOD,"app_power_mgr__set_LC_sleep_pollicy  policy = (%d->%d),  policyctrl(%d->%d)"
        , lc_slp_policy
        , policy
        , lc_slp_policy_ctrl
        , policyctrl
        );

    struct net_buf *buf;
    uint8_t policy_para[LC_SLEEP_POLICY_CTRL_MASK_PARA_SIZE];
    policy_para[0] = policyctrl;
    policy_para[1] = policy;

    buf = bt_hci_cmd_create(BT_HCI_OP_VS_SET_LC_SLP_POLICY, LC_SLEEP_POLICY_CTRL_MASK_PARA_SIZE);
    if (!buf) {
        return;
    }

    net_buf_add_mem(buf, policy_para, LC_SLEEP_POLICY_CTRL_MASK_PARA_SIZE );
    err = bt_hci_cmd_send(BT_HCI_OP_VS_SET_LC_SLP_POLICY, buf);
}
#endif

void hid_power_mgr__lock_LC_sleep_control(bool enable_lock)
{
    #if !defined(CONFIG_AIR_DISABLE_LC_SLEEP)
    bool skip = false;
    uint8_t  device_type = hid_scenario_get();
    uint16_t report_rate = hid_scenario_read_now_report_rate(device_type);
    uint8_t sceario_state = hid_scenario_get_state();

    hid_power_mgr__stop_LC_sleep_timers();

    if(sceario_state & (MODE_OPEN_SPECIFIED | MODE_OPEN_CONNECTED))
    {
        if (enable_lock)
        {
            switch(device_type)
            {
                case HID_SCENARIO_GAMING_MODE:
                {
                    hid_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_DISABLE);
                    break;
                }
            }
        }
        else {
            switch(device_type)
            {
                case HID_SCENARIO_USB_MODE:
                {
                }
                break;

                case HID_SCENARIO_GAMING_MODE:
                {
                    if ( report_rate == RR_IDX_TO_REPORT_RATE(HID_REPORT_RATE_1K_HZ))
                    {
                        hid_power_mgr__start_LC_sleep_timers();
                    }
                    else {
                        skip = true;
                    }
                }
                break;

                // case HID_SCENARIO_BT_MODE:
                // {
                // }
                // break;
            }
        }

        DBG_LOGI(thisMOD,"hid_power_mgr__lock_LC_sleep_control  unlock sleep request,  enable_lock = %d  device_type = %d  report_rate = %d, skip = %d  "
            , enable_lock
            , device_type
            , report_rate
            , skip
        );
    }
    #endif
}




// this function is executed in timer irq
static void hid_power_mgr_system_low_clock_execution(struct k_timer *timer_id)
{
    DBG_LOGI(thisMOD,"hid_power_mgr__low_clock_execution,  hid_power_mgr_low_clock_status = %d ", hid_power_mgr_low_clock_status);
    if (!hid_power_mgr_low_clock_status && (hal_dvfs_get_cur_frq() == HAL_DVFS_FRQ_MID))
    {
        hid_power_mgr_low_clock_status = true;
        hid_power_mgr_sys_clock_id = clock_mux_cur_sel(CLK_SYS_SEL);
        hal_dvfs_lock_control(HAL_DVFS_OPP_NV, HAL_DVFS_UNLOCK);

        DBG_LOGI(thisMOD,"Done, old id = %d ", hid_power_mgr_sys_clock_id);
    }
}

void hid_power_mgr_system_low_clock_enable()
{
    #if defined (DISABLE_LOW_CLOCK)
    DBG_LOGI(thisMOD,"hid_power_mgr_system_low_clock_enable skipped");
    #else

    // uint32_t app_state_stable = app_state_check(TYPE_IN_GAMING_CONNECTED_STABLE);
    uint8_t  device_type = hid_scenario_get();
    uint16_t report_rate = hid_scenario_read_now_report_rate(device_type);

    if((report_rate <= RR_IDX_TO_REPORT_RATE(HID_REPORT_RATE_1K_HZ)))
    {
        DBG_LOGI(thisMOD,"hid_power_mgr_system_low_clock_enable, report_rate = %d", report_rate);
        k_timer_start(&hid_power_mgr__low_clock_timer_hdl, K_SECONDS(1), K_NO_WAIT);
    }
    else {
        // Disable low clock and stop timer if needed
        // report rate change request will not be announced in application layer if sync report rate from USB mode to 2.4g mode (2.4G = 1K, USB = 8K)
        // low clock timer must be stop in this case
        hid_power_mgr_system_low_clock_disable();
    }
    #endif
}

void hid_power_mgr_system_low_clock_disable()
{
    #if defined (DISABLE_LOW_CLOCK)
    DBG_LOGI(thisMOD,"hid_power_mgr_system_low_clock_disable skipped");
    #else

    // stop the timer to avoid unexpected changing of clock
    k_timer_stop(&hid_power_mgr__low_clock_timer_hdl);

    if (hid_power_mgr_low_clock_status && (hal_dvfs_get_cur_frq() != HAL_DVFS_FRQ_MID))
    {
        hid_power_mgr_low_clock_status = false;
        hal_dvfs_lock_control(HAL_DVFS_OPP_NV, HAL_DVFS_LOCK);
        DBG_LOGI(thisMOD,"hid_power_mgr_system_low_clock_disable done, current id = %d ", hid_power_mgr_sys_clock_id);
    }
    else
    {
        DBG_LOGI(thisMOD,"skip hid_power_mgr_system_low_clock_disable, current id = %d ", hid_power_mgr_sys_clock_id);
    }
    #endif
}