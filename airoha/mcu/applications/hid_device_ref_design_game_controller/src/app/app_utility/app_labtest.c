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

#include "app_labtest.h"
#include "app_button.h"
#include "app_state.h"

#include "hal_wdt.h"
#include "hal_nvic.h"
#include "hal_nvic_internal.h"
#include "relay_client.h"
#include "hid_labtest_service.h"

#define thisMODULE lab_test
#define thisMOD    "lab_test"
LOG_MODULE_REGISTER(thisMODULE);

/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
void app_labtest__relay_status_notify_cb(bt_relay_status_t status);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
static uint8_t app_lab_type = APP_LABTEST_TYPE_NONE;
#if 0
static uint8_t rf_mode = LABTEST_MODE_DC_TONE;
static uint8_t rf_channel = LABTEST_RF_FREQ_L;
static bool modem_phy = LABTEST_MODEM_PHY_1M;
#endif

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
#if 0
static bool app_labtest_evt_key_event(const struct af_evt_header *evt_header)
{
    struct evt_key_event* event = (struct evt_key_event*)evt_header;
    APP_LOGI(thisMOD,"app_labtest_evt_key_event , key_id = %d, event = %x", event->key_id, event->key_evt);

    switch (event->key_evt)
    {
        case AK_PRESS:
        {
            uint32_t state = app_state_current_state();
            if(state == APP_STATE_TEST)
            {
                #if 0
                switch(event->key_id)
                {
                    case M_KEY_L:
                    {
                        uint8_t temp = rf_mode;
                        rf_mode++;
                        if(rf_mode >= LABTEST_MODE_MAX_NUM){
                            rf_mode = LABTEST_MODE_DC_TONE;
                        }
                        APP_LOGI(thisMOD,"L key: RF mode setting, mode = %d->%d", temp, rf_mode);
                        hid_labtest__change_action_by_key_press(event->key_id, rf_mode);
                        break;
                    }
                    case M_KEY_M:
                    {
                        bool temp = modem_phy;
                        modem_phy = !modem_phy;
                        APP_LOGI(thisMOD,"M key: modem phy setting, phy = %d->%d", temp, modem_phy);
                        hid_labtest__change_action_by_key_press(event->key_id, modem_phy);
                        break;
                    }
                    case M_KEY_R:
                    {
                        bool temp = rf_channel;
                        rf_channel++;
                        if(rf_channel >= LABTEST_RF_FREQ_MAX_NUM){
                            rf_channel = LABTEST_RF_FREQ_L;
                        }
                        APP_LOGI(thisMOD,"R key: RF channel setting, channel = %d->%d", temp, rf_channel);
                        hid_labtest__change_action_by_key_press(event->key_id, rf_channel);
                        break;
                    }
                    default:{
                        break;
                    }
                }
                #endif
            }
        }
        break;

        default:
            break;
    }
    return AF_TRAVERSE_NEXT;
}
#endif

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
static bool app_labtest_evt_usb_status(const struct af_evt_header *evt_header)
{
    struct evt_usb_status* event = (struct evt_usb_status*)evt_header;
    APP_LOGI(thisMOD,"app_labtest_evt_usb_status, status = %d", event->status);
    switch(event->status)
    {
        case USB_STATUS_PLUGGED_OUT:  //0
        {
            uint32_t state = app_state_current_state();
            if(state == APP_STATE_TEST){
                APP_LOGI(thisMOD,"Exit test mode!!!");
                hal_wdt_software_reset();
                break;
            }
            break;
        }
        default:{
            break;
        }
    }

    return AF_TRAVERSE_NEXT;
}
#endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_ */

/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
void app_labtest__enter_test_mode()
{
    uint8_t type = (app_lab_type == APP_LABTEST_TYPE_RELAY_MODE) ? TEST_TYPE_RELAY_MODE : TEST_TYPE_LAB_TEST;

    struct evt_enter_test* event = create_evt_enter_test();
    if(event)
    {
        event->type = type;
        AF_EVT_SUBMIT(event);
    }
}

void app_labtest__relay_status_notify_cb(bt_relay_status_t status)
{
    APP_LOGI(thisMOD,"app_labtest__relay_status_notify_cb, status = %d", status);
    if (status == bt_relay_status_enable)
    {
        app_lab_type = APP_LABTEST_TYPE_RELAY_MODE;
        app_labtest__enter_test_mode();
        hal_nvic_set_priority(BT_IRQn, BT_IRQ_PRIORITY);
        hal_nvic_set_priority(OS_GPT_IRQn, OS_GPT_IRQ_PRIORITY);
    }
    else if (status == bt_relay_status_disable)
    {
        // app_state_in_processing_action = ACTION_SWITCH_TO_LAB_TEST
        app_lab_type = APP_LABTEST_TYPE_NONE;
    }
}


/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_labtest_init(uint32_t key_status)
{
    #if 0
    if(key_status == (M_KEY_L_PRESSED | M_KEY_FW_PRESSED | M_KEY_BW_PRESSED)){
        app_lab_type = APP_LABTEST_TYPE_LAB_TEST;
        app_labtest__enter_test_mode();
    }
    #endif
    relay_status_notify_register(app_labtest__relay_status_notify_cb);
    return;
}

app_labtest_type_t app_labtest_get_type()
{
    return app_lab_type;
}



/*============================Application Framework============================*/
// AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_key_event, app_labtest_evt_key_event);
#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_usb_status, app_labtest_evt_usb_status);
#endif /* _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_ */

/*=============================================================================*/

