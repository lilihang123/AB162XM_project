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


#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>


#include "app_state.h"
#include "app_power_manager.h"
#include "app_scenario.h"
#include "app_usb_port.h"

#include "hal_riscv_ctl.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"
#include "hal_clock_internal.h"

#if defined(CONFIG_AIR_RAM_BLOCKS_CONTROL_ENABLE)
#include "ram_blocks_control.h"
#endif
#include "pd_domain_control.h"
#include "hal_sleep_manager_internal.h"
#include "hal_clock_internal.h"
#include "hal_spm.h"
#include "app_button.h"
#include "hal_wdt.h"
#include "hal_gpt.h"
#include "hal_dvfs.h"
#include "nvkey.h"
#include "hid_scenario_report_rate.h"
#include "hid_power_mgr.h"
#include "app_joystick_and_trigger.h"

#define thisMODULE power_mgr
#define thisMOD    "power_mgr"
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
static void app_power_mgr_lock_dvfs(dvfs_frequency_t freq_idx);
static void app_power_mgr_unlock_dvfs(dvfs_frequency_t freq_idx);

static void app_power_mgr_unlock_sleep();
static void app_power_mgr_lock_sleep();

static void app_power_mgr_unlock_extslp();
static void app_power_mgr_lock_extslp();

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
uint8_t  app_power_mgr_state = APP_POWER_MGR_NORMAL_MODE;
bool app_power_mgr_lock_extslp_status = false;
bool app_power_mgr_lock_sleepp_status = false;
bool app_power_mgr_lock_dvfs_status = false;

uint8_t power_mgr_last_app_state;

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_power_mgr__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    uint8_t curr_state = app_state_current_state();
    APP_LOGI(thisMOD,"app_power_mgr__evt_app_state, event->app_state = %02X, curr_state = %02X ", event->app_state, curr_state);

    switch (event->app_state)
    {
        case APP_STATE_INITIALIZED:
        {
            hal_dvfs_lock_control(HAL_DVFS_OPP_NV, HAL_DVFS_LOCK);
        }
        break;

        case APP_STATE_STANDBY:
        {
            if (curr_state == APP_STATE_STANDBY){
                #if defined (CONFIG_AIR_APP_STANDBY_WITH_ADAPTOR_RGB)
                if(app_usb_port__get_usb_plug_status() != APP_USB_PLUG_OUT){

                }
                else
                #endif
                {
                    app_power_mgr_enter_low_power_mode();
                }
            }
        }
        break;

        case APP_STATE_DISCONNECTED:
        {
            app_power_mgr_lock_sleep();
            #if defined(ENABLE_LC_SLEEP_POLICY_CTR)
            app_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_DISABLE);
            #endif

            #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
            app_power_mgr__lock_LC_sleep_control(true);
            #endif

            app_power_mgr_system_low_clock_disable();
        }
        break;

        case APP_STATE_CONNECT_PREPARING:
        {
            app_power_mgr_system_low_clock_disable();

            #if defined(ENABLE_LC_SLEEP_POLICY_CTR)
            uint8_t usb_plugged_status = APP_USB_PLUG_OUT;

            #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
            usb_plugged_status = app_usb_port__get_usb_plug_status();
            #endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

            if(usb_plugged_status != APP_USB_CONFIGURED)
            {
                app_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_DISABLE);
            }
            #endif
        }
        break;

        case APP_STATE_BT_PAIRING:
        case APP_STATE_2_4G_PAIRING:
        case APP_STATE_BT_RECONNECT:
        case APP_STATE_2_4G_RECONNECT:
        case APP_STATE_2_4G_QUICK_CONNECT:
        case APP_STATE_CONNECT_CANCEL:
        case APP_STATE_CONNECT_CANCEL_CHECK:
            break;
        case APP_STATE_2_4G_RECONNECT_RESUME_WAIT:
        {
            #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
            hid_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_DEEP_SLEEP);
            #endif
            app_power_mgr_enter_low_power_mode_exclude_bt();
        }
        break;
        case APP_STATE_2_4G_CONNECTED:
        case APP_STATE_BT_CONNECTED:
        case APP_STATE_USB_CONNECTED:
        case APP_STATE_USB_DISCONNECTING:
        {
            app_power_mgr_system_low_clock_disable();
        }
        break;

        case APP_STATE_USB_ACTIVE:
        case APP_STATE_USB_SUSPEND:
        case APP_STATE_USB_ENTERING_ACTIVE:
            break;

        case APP_STATE_BT_CONNECTED_ACTIVE:
        {
            // app_power_mgr_unlock_sleep();
            #if defined(ENABLE_LC_SLEEP_POLICY_CTR)
            app_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_DEEP_SLEEP);
            #endif
        }
        break;

        case APP_STATE_BT_CONNECTED_IDLE_1:
        case APP_STATE_BT_CONNECTED_IDLE_2:
        case APP_STATE_BT_CONNECTED_IDLE_3:
        case APP_STATE_BT_CONNECTED_ENTERING_ACTIVE:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_1:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_2:
        case APP_STATE_BT_CONNECTED_ENTERING_IDLE_3:
            break;

        case APP_STATE_BT_DISCONNECTING:
        {
            #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
            app_power_mgr__lock_LC_sleep_control(true);
            #endif
            app_power_mgr_system_low_clock_disable();
        }
        break;

        case APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE:
        {
        }
        break;

        case APP_STATE_2_4G_CONNECTED_ACTIVE:
        {
            #if !defined(CONFIG_AIR_PRINT_HID_REPORT_LOG)
            // app_power_mgr_system_low_clock_enable();
            // app_power_mgr_unlock_sleep();
            #endif

            #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
            app_power_mgr__lock_LC_sleep_control(false);
            #endif
        }
        break;

        case APP_STATE_2_4G_DISCONNECTING:
        {
            app_power_mgr_system_low_clock_disable();

            #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
            app_power_mgr__lock_LC_sleep_control(true);
            #endif
        }
        break;

        case APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1:
        {
        }
        break;

        case APP_STATE_2_4G_CONNECTED_IDLE_1:
        {
        }
        break;

        case APP_STATE_TEST:
        {
            APP_LOGI(thisMOD,"app_power_mgr, mgr_state = %d, lock_extslp = %d, lock_sleep = %d", 
                            app_power_mgr_state, app_power_mgr_lock_extslp_status, app_power_mgr_lock_sleepp_status);
            break;
        }
    }

    power_mgr_last_app_state = event->app_state;

    return AF_TRAVERSE_NEXT;
}

static bool app_power_mgr_evt_scenario_status(const struct af_evt_header *evt_header)
{
    struct evt_scenario_status* event = (struct evt_scenario_status*)evt_header;
    APP_LOGI(thisMOD,"evt_scenario_status = 0x%02X, reason = 0x%02X"
        , event->status
        , event->reason
        );

    switch(event->status)
    {
        case MODE_OPEN_CONNECTED:
        {
            if(app_power_mgr_state == APP_POWER_MGR_LOW_POWER_MODE_EXCLUDE_BT){
                #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
                hid_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_DISABLE);
                #endif
                app_power_mgr_exit_low_power_mode_exclude_bt();
            }
        }
        break;
    }
    return AF_TRAVERSE_NEXT;
}

static bool app_power_mgr__evt_active_status(const struct af_evt_header *evt_header)
{
    struct evt_active_status* event = (struct evt_active_status*)evt_header;
    APP_LOGI(thisMOD,"app_power_mgr__evt_active_status , active = %d, type = %d", event->active, event->type);

    if (event->active){
        app_power_mgr_exit_low_power_mode();
    }
    if(app_power_mgr_state == APP_POWER_MGR_LOW_POWER_MODE_EXCLUDE_BT){
        #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
        hid_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_DISABLE);
        #endif
        app_power_mgr_exit_low_power_mode_exclude_bt();
    }

    return AF_TRAVERSE_NEXT;
}

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
static bool app_power_mgr__evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status* event = (struct evt_usb_status*)evt_header;
    APP_LOGI(thisMOD,"app_power_mgr__evt_usb_status , status = %d", event->status);
    app_power_mgr_lock_sleep();
    app_power_mgr_exit_low_power_mode();
    if(app_power_mgr_state == APP_POWER_MGR_LOW_POWER_MODE_EXCLUDE_BT){
        #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
        hid_power_mgr__set_LC_sleep_pollicy(LC_SLP_POLICY_CTR_CHANGE, LC_SLP_POLICY_DISABLE);
        #endif
        app_power_mgr_exit_low_power_mode_exclude_bt();
    }
    return AF_TRAVERSE_NEXT;
}
#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

static bool app_power_mgr__evt_slide_switch_status(const struct af_evt_header *evt_header)
{
    struct evt_slide_switch_status* event = (struct evt_slide_switch_status*)evt_header;
    APP_LOGI(thisMOD,"app_power_mgr__evt_slide_switch_status , position = %d \n ", event->position);
    app_power_mgr_exit_low_power_mode();
    return AF_TRAVERSE_NEXT;
}

static bool app_power_mgr__evt_conn_req(const struct af_evt_header *evt_header)
{
    struct evt_conn_req* event = (struct evt_conn_req*)evt_header;

    APP_LOGI(thisMOD,"app_power_mgr__evt_conn_req , cmd = %d "
        , event->cmd
        );

    switch(event->cmd)
    {
        case CONN_REQ_CONN_NEXT_LINK:
        case CONN_REQ_DISC:
        {
            #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
            // In these cases, it is expected that disconnect process will be triggered
            app_power_mgr__lock_LC_sleep_control(true);
            #endif

            // disable low clock before executing disconnect process
            app_power_mgr_system_low_clock_disable();
        }
        break;

        default:
        break;
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_power_mgr__evt_rr_change_req(const struct af_evt_header *evt_header)
{
    struct evt_rr_change_req* event = (struct evt_rr_change_req*)evt_header;
    APP_LOGI(thisMOD,"app_power_mgr__evt_rr_change_req, change_type = %d,  RR = %d\n ", event->change_type, event->RR);

    if (app_state_check(TYPE_IN_GAMING_STATES)){
        #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
        app_power_mgr__lock_LC_sleep_control(true);
        #endif
    }

    app_power_mgr_system_low_clock_disable();

    return AF_TRAVERSE_NEXT;
}

static bool app_power_mgr__evt_rr_status(const struct af_evt_header *evt_header)
{
    struct evt_rr_status* event = (struct evt_rr_status*)evt_header;
    APP_LOGI(thisMOD,"app_power_mgr__evt_rr_status , category = %d, RR = %d", event->category, event->RR);

    if ((event->category == MODE_TYPE_GAMING) && app_state_check(TYPE_IN_GAMING_STATES)){

        #if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
        // update LC sleep lock after report rate is changed in 2.4G scenario
        if (event->RR == RR_IDX_TO_REPORT_RATE(HID_REPORT_RATE_1K_HZ)  && app_state_check(TYPE_IN_GAMING_CONNECTED_STABLE)  ){
            app_power_mgr__lock_LC_sleep_control(false);
        }
        else {
            app_power_mgr__lock_LC_sleep_control(true);
        }
        #endif

        #if !defined(CONFIG_AIR_PRINT_HID_REPORT_LOG)
        app_power_mgr_system_low_clock_enable();
        #endif
    }
    else
    {
        app_power_mgr_system_low_clock_disable();
    }

    return AF_TRAVERSE_NEXT;
}


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/

/* Just support one freq_idx now */
static void app_power_mgr_lock_dvfs(dvfs_frequency_t freq_idx)
{
    if (app_power_mgr_lock_dvfs_status == false)
    {
        app_power_mgr_lock_dvfs_status = true;
        hal_dvfs_lock_control(freq_idx, HAL_DVFS_LOCK);
        APP_LOGI(thisMOD,"app_power_mgr_lock_dvfs, idx = %d", freq_idx);
    }
}

static void app_power_mgr_unlock_dvfs(dvfs_frequency_t freq_idx)
{
    if (app_power_mgr_lock_dvfs_status)
    {
        app_power_mgr_lock_dvfs_status = false;
        hal_dvfs_lock_control(freq_idx, HAL_DVFS_UNLOCK);
        APP_LOGI(thisMOD,"app_power_mgr_unlock_dvfs, idx = %d", freq_idx);
    }
}

static void app_power_mgr_unlock_sleep()
{
    if(app_power_mgr_lock_sleepp_status)
    {
        hal_sleep_manager_status_t ret = hal_sleep_manager_unlock_sleep(SLEEP_LOCK_APP_PURE);
        app_power_mgr_lock_sleepp_status = false;
        APP_LOGI(thisMOD,"app_power_mgr_unlock_sleep, status = %d, ret = %d", app_power_mgr_lock_sleepp_status, ret);
    }
}

static void app_power_mgr_lock_sleep()
{
    if(app_power_mgr_lock_sleepp_status == false)
    {
        hal_sleep_manager_status_t ret = hal_sleep_manager_lock_sleep(SLEEP_LOCK_APP_PURE);
        app_power_mgr_lock_sleepp_status = true;
        APP_LOGI(thisMOD,"app_power_mgr_lock_sleep, status = %d, ret = %d", app_power_mgr_lock_sleepp_status, ret);
    }
}

static void app_power_mgr_unlock_extslp()
{
    #if defined (DISABLE_EXT_SLEEP_UNLOCK)
    APP_LOGI(thisMOD,"app_power_mgr_unlock_extslp skipped");
    #else
    if(app_power_mgr_lock_extslp_status)
    {
        hal_sleep_manager_status_t ret = hal_sleep_manager_unlock_extslp(SLEEP_LOCK_EXTEND_APP);
        app_power_mgr_lock_extslp_status = false;
        APP_LOGI(thisMOD,"app_power_mgr_unlock_extslp, status = %d, ret = %d", app_power_mgr_lock_extslp_status, ret);
    }
    #endif
}

static void app_power_mgr_lock_extslp()
{
    if(app_power_mgr_lock_extslp_status == false)
    {
        hal_sleep_manager_status_t ret = hal_sleep_manager_lock_extslp(SLEEP_LOCK_EXTEND_APP);
        app_power_mgr_lock_extslp_status = true;
        APP_LOGI(thisMOD,"app_power_mgr_lock_extslp, status = %d, ret = %d", app_power_mgr_lock_extslp_status, ret);
    }
}

#if defined(ENABLE_LC_SLEEP_POLICY_CTR_2_4G)
void app_power_mgr__lock_LC_sleep_control(bool lock)
{
    hid_power_mgr__lock_LC_sleep_control(lock);
}
#endif

/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool app_power_mgr_init()
{
    app_power_mgr_lock_extslp();
    app_power_mgr_lock_sleep();
    /* lock 78M, no need unlock */
    hal_dvfs_lock_control(HAL_DVFS_OPP_MID, HAL_DVFS_LOCK);
    /* lock  156M */
    app_power_mgr_lock_dvfs(HAL_DVFS_OPP_HIGH);
    /* prohibit flash enter DPD till enter standby stage */
    pd_domain_control_sfc_dpd_disable();
    /* prohibit peripharl backup restire till enter standby stage */
    sleep_management_backup_restore_ctrl(false);
    return true;
}

bool app_power_mgr_execute_shutdown()
{
    return true;
}

void app_power_mgr_system_low_clock_enable()
{
    if(app_state_check(TYPE_IN_GAMING_CONNECTED_STABLE))
    {
        hid_power_mgr_system_low_clock_enable();
    }
}

void app_power_mgr_system_low_clock_disable()
{
    hid_power_mgr_system_low_clock_disable();
}

void app_power_mgr_enter_low_power_mode_exclude_bt()
{
    APP_LOGI(thisMOD,"app_power_mgr_enter_low_power_mode_exclude_bt");
    app_power_mgr_unlock_extslp();
    app_power_mgr_unlock_sleep();
    /* unlock 156M */
    app_power_mgr_unlock_dvfs(HAL_DVFS_OPP_HIGH);
    /* allow peripharl backup restire till enter standby stage */
    sleep_management_backup_restore_ctrl(true);
    hal_riscv_stop();
    hal_clock_lposc_recali_ctrl(false);
    app_power_mgr_state = APP_POWER_MGR_LOW_POWER_MODE_EXCLUDE_BT;
}

void app_power_mgr_enter_low_power_mode()
{
    if (app_power_mgr_state != APP_POWER_MGR_LOW_POWER_MODE)
    {
        APP_LOGI(thisMOD,"app_power_mgr_enter_low_power_mode");
        app_power_mgr_unlock_extslp();
        app_power_mgr_unlock_sleep();
        /* unlock 156M */
        app_power_mgr_unlock_dvfs(HAL_DVFS_OPP_HIGH);

#if !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
        /* allow flash enter DPD till enter standby stage */
        pd_domain_control_sfc_dpd_enable();
#endif /* !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE) */

        /* allow peripharl backup restire till enter standby stage */
        sleep_management_backup_restore_ctrl(true);

#if !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
#if defined(CONFIG_AIR_RAM_BLOCKS_CONTROL_ENABLE)
        ram_blocks_control_non_retention_blocks_extend_sleep_off_allow();
#endif
#endif /* !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE) */

        hal_riscv_stop();
        hal_clock_lposc_recali_ctrl(false);

        extern void bt_driver_direct_power_off(void);
        bt_driver_direct_power_off();

#if !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
        /* disable rtcsys for better low power */
        spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_DISABLE);
#endif /* !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE) */

        // extern void spm_debug_io(unsigned int debug_bus);
        // spm_debug_io(0x7f595d48);

        app_power_mgr_state = APP_POWER_MGR_LOW_POWER_MODE;
        APP_LOGI(thisMOD,"app_power_mgr_enter_low_power_mode done, %d", app_power_mgr_state);
    }
}

#define RISCV_START_WITH_DMA_COPY

#if defined(RISCV_START_WITH_DMA_COPY)
uint32_t riscv_start_complete;
void riscv_start_async_cb(void)
{
    riscv_start_complete = true;
    DBG_IDX(3, DBG_SIGNAL_MAIN_LOOP)
}
#endif

void app_power_mgr_exit_low_power_mode_exclude_bt()
{
    APP_LOGI(thisMOD,"app_power_mgr_exit_low_power_mode_exclude_bt, cpu_freq = %d,  ", hal_clock_get_curr_cpu_freq_hz());
    app_power_mgr_lock_extslp();
    app_power_mgr_lock_sleep();
    /* lock 156M */
    app_power_mgr_lock_dvfs(HAL_DVFS_OPP_HIGH);
    /* prohibit peripharl backup restire till enter standby stage */
    sleep_management_backup_restore_ctrl(false);
    hal_riscv_start(0);
    hal_clock_lposc_recali_ctrl(true);
    app_power_mgr_state = APP_POWER_MGR_NORMAL_MODE;
}

void app_power_mgr_exit_low_power_mode()
{
    if (app_power_mgr_state == APP_POWER_MGR_LOW_POWER_MODE){
        APP_LOGI(thisMOD,"app_power_mgr_exit_low_power_mode, cpu_freq = %d,  ", hal_clock_get_curr_cpu_freq_hz());
        DBG_PING_H(DBG_SIGNAL_SPI_CB);

        // extern hal_gpio_status_t hal_gpio_wakeup_extend_sleep_clear(hal_gpio_pin_t gpio_pin);
#if !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
        /* enable rtcsys and restore peripherals */
        spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_ENABLE);
#endif /* !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE) */

        app_power_mgr_lock_extslp();
        app_power_mgr_lock_sleep();
        /* unlock 156M */
        app_power_mgr_lock_dvfs(HAL_DVFS_OPP_HIGH);

#if !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
        /* prohibit flash enter DPD till enter standby stage */
        pd_domain_control_sfc_dpd_disable();
#endif /* !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE) */

        /* prohibit peripharl backup restire till enter standby stage */
        sleep_management_backup_restore_ctrl(false);
        DBG_PING_L(DBG_SIGNAL_SPI_CB);


        DBG_PING_H(DBG_SIGNAL_SPI_CB);
        #if defined(RISCV_START_WITH_DMA_COPY)
        hal_riscv_start_async(0, riscv_start_async_cb);
        #else
        hal_riscv_start(0);
        #endif
        DBG_PING_L(DBG_SIGNAL_SPI_CB);


        DBG_PING_H(DBG_SIGNAL_SPI_CB);
        extern void bt_driver_direct_power_on(void);
        bt_driver_direct_power_on();
        DBG_PING_L(DBG_SIGNAL_SPI_CB);


        DBG_PING_H(DBG_SIGNAL_SPI_CB);
        hal_clock_lposc_recali_ctrl(true);

#if !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE)
#if defined(CONFIG_AIR_RAM_BLOCKS_CONTROL_ENABLE)
        ram_blocks_control_non_retention_blocks_extend_sleep_off_prohibit();
#endif
#endif /* !defined(CONFIG_AIR_JOYSTICK_AND_TRIGGER_WAKEUP_ENABLE) */

        #if defined(RISCV_START_WITH_DMA_COPY)
        #define RELEASE_CNT 100
        uint16_t protect_cnt = 0;
        while(riscv_start_complete == false && protect_cnt < RELEASE_CNT){
            DBG_PING_H(DBG_SIGNAL_LATCH_REPORT);
            DBG_PING_L(DBG_SIGNAL_LATCH_REPORT);
            protect_cnt++;
            assert(protect_cnt < RELEASE_CNT);
        };
        #endif

        DBG_PING_L(DBG_SIGNAL_SPI_CB);
        app_power_mgr_state = APP_POWER_MGR_NORMAL_MODE;
        APP_LOGI(thisMOD,"app_power_mgr_exit_low_power_mode done, %d", app_power_mgr_state);
    }
}

/*============================Application Framework============================*/
// WARNING : the following event SHALL be handled after other scbscribers
// Enter low power mode shall be the last process
AF_EVT_SUBSCRIBE_FUN_LAST(thisMODULE, evt_app_state, app_power_mgr__evt_app_state);

// WARNING : the following event SHALL be handle before other scbscribers
// Exit low power mode shall be the first process
AF_EVT_SUBSCRIBE_FUN_FIRST(thisMODULE, evt_active_status, app_power_mgr__evt_active_status);
#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_SUBSCRIBE_FUN_FIRST(thisMODULE, evt_usb_status, app_power_mgr__evt_usb_status);
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE */
AF_EVT_SUBSCRIBE_FUN_FIRST(thisMODULE, evt_slide_switch_status, app_power_mgr__evt_slide_switch_status);
AF_EVT_SUBSCRIBE_FUN_FIRST(thisMODULE, evt_conn_req, app_power_mgr__evt_conn_req);
AF_EVT_SUBSCRIBE_FUN_FIRST(thisMODULE, evt_rr_change_req, app_power_mgr__evt_rr_change_req);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_rr_status, app_power_mgr__evt_rr_status);
AF_EVT_SUBSCRIBE_FUN_HIGH(thisMODULE, evt_scenario_status, app_power_mgr_evt_scenario_status);
/*=============================================================================*/
