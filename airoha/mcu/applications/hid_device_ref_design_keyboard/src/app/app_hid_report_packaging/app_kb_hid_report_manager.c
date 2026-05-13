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


#include "app_kb_hid_report_manager.h"

#ifdef CONFIG_AIR_HID_EXPRESS_SERVICE
#include "riscv_hid_express.h"
#include "riscv_hid_express_bt_mode.h"
#endif/*CONFIG_AIR_HID_EXPRESS_SERVICE*/
#include "hid_common.h"

#define thisMOD    "app_kb"
#define thisMODULE  app_kb
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
void app_kb__init();

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#if defined (CONFIG_AIR_HID_EXPRESS_SERVICE) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
static bool app_kb__evt_hogp_attr(const struct af_evt_header *evt_header)
{
    struct evt_hogp_attr* event = (struct evt_hogp_attr*)evt_header;

    hid_experss_bt_set_attr_handle(event->ms, event->kb_std, event->kb_consumer, event->kb_nkey);
    return AF_TRAVERSE_NEXT;
}
#endif

static bool app_kb__evt_app_state(const struct af_evt_header *evt_header)
{
    struct evt_app_state* event = (struct evt_app_state*)evt_header;
    APP_LOGI(thisMOD,"app_kb__evt_app_state, app_state = 0x%02X", event->app_state);

    switch(event->app_state)
    {
        case APP_STATE_NONE:
        case APP_STATE_INITIALIZED:
        case APP_STATE_STANDBY:
        case APP_STATE_TEST:
            break;

        case APP_STATE_DISCONNECTED:
            #if defined (CONFIG_AIR_HID_EXPRESS_SERVICE) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
            hid_experss_bt_clear_queue();
            #endif

        case APP_STATE_CONNECT_PREPARING:
            app_kb__init();
            break;

        default:
            break;
    }


    return AF_TRAVERSE_NEXT;
}

#ifdef CONFIG_AIR_HID_EXPRESS_SERVICE
void app_kb__report_handler(T_PS_CB_TYPE_E ps_cb_type, T_OUTGOING_VALUES_S* outgoing_data)
{
    // APP_LOGI(thisMOD,"app_kb__report_handler ");

    switch(ps_cb_type)
    {
        case HID_EXP_1ST_CB:
        {

        }
        break;

        case HID_EXP_2ND_CB:
        {
            // assert( outgoing_data &&   "Error : outgoing_data is NULL at HID_EXP_2ND_CB");
            if(FORCE_RELEASE_KEY_ENABLE(hid_flags))
            {
                // Pairing check
            }
        }
        break;

        case HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL:
        {
            // assert( outgoing_data &&   "Error : outgoing_data is NULL at HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL");

            if(FORCE_RELEASE_KEY_ENABLE(hid_flags))
            {

            }
            else
            {
                // Get key status

            }
        }
        break;

        case HID_EXP_4TH_CB_POST_PROCESS:
        {
            // assert( outgoing_data &&   "Error : outgoing_data is NULL at HID_EXP_4TH_CB_POST_PROCESS");

        }
        break;

        case HID_EXP_NO_REPORT_PROCESS:
        {
           // Traffic is stopped.
           // Do pheripheral control if needed
        }
        break;
    }
}
#endif/*CONFIG_AIR_HID_EXPRESS_SERVICE*/

void app_kb__init()
{
    APP_LOGI(thisMOD,"app_kb__init ");
#ifdef CONFIG_AIR_HID_EXPRESS_SERVICE
    // hid_express_init(app_kb__report_handler);
#endif/*CONFIG_AIR_HID_EXPRESS_SERVICE*/

}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_app_state, app_kb__evt_app_state);
#if defined (CONFIG_AIR_HID_EXPRESS_SERVICE) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_hogp_attr, app_kb__evt_hogp_attr);
#endif
/*=============================================================================*/
