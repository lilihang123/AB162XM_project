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
#include <app_evt_dispatcher.h>
#include "af_events_declaration.h"
#include "air_daemon_work_q.h"
#include "assert.h"


#if defined (AIR_SWLA_ENABLE)
#include "swla.h"
#endif

#if defined(CONFIG_AIR_APP_FRAMEWORK)


#define thisMODULE evt_dispatch
#define thisMOD    "evt_dispatch"
LOG_MODULE_REGISTER(thisMODULE);

//#define DBG_EVT_DISPATCHER_LOG
//#define DBG_EVT_DISPATCHER_LA_SIGNAL

#ifdef DBG_EVT_DISPATCHER_LOG
#define EVT_DISPATCH_DBG_LOGI(module_name, format, ...)   LOG_INF("["module_name"]" format, ## __VA_ARGS__)
#else
#define EVT_DISPATCH_DBG_LOGI(module_name, format, ...) 
#endif

#if DBG_EVT_DISPATCHER_LA_SIGNAL
#include "hid_common_debug.h"
#define EVT_DISPATCH_DEB_DBG_L(x)       DBG_PING_L(x)
#define EVT_DISPATCH_DEB_DBG_H(x)       DBG_PING_H(x)
#else 
#define EVT_DISPATCH_DEB_DBG_L(x)
#define EVT_DISPATCH_DEB_DBG_H(x)
#endif


static void app_evt_dispatcher(struct k_work *work);
static K_WORK_DEFINE(app_evt_dispatch, app_evt_dispatcher);

K_FIFO_DEFINE(app_dispatcher_fifo);
static struct k_spinlock app_dispatcher_evt_q_lock;


static void app_evt_dispatching(struct af_evt_header *evt_header)
{
    const struct af_evt_type *cb_list = evt_header->cb_list;
    const struct af_evt_dispatch_cb *evt_cb;

    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_evt_dispatcher, SWLA_DIRECTION_START);
    #endif

    EVT_DISPATCH_DEB_DBG_H(DBG_SIGNAL_USB_SOF);
    EVT_DISPATCH_DBG_LOGI(thisMOD,"app_evt_dispatching [start]  event_name = 0x%08X--%08X--%08X", *(uint32_t*)&cb_list->event_name[8], *(uint32_t*)&cb_list->event_name[4], *(uint32_t*)&cb_list->event_name[0] );

    for (evt_cb = cb_list->dummy_00; evt_cb != cb_list->dummy_99; evt_cb++)
    {
        #if defined (AIR_SWLA_ENABLE)
        HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_evt_dispatcher, SWLA_DIRECTION_LABEL);
        #endif   

        EVT_DISPATCH_DEB_DBG_H(DBG_SIGNAL_USB_TX_DONE);
        if(evt_cb->cb(evt_header)){
            break;
        }
        EVT_DISPATCH_DEB_DBG_L(DBG_SIGNAL_USB_TX_DONE);
    }

    EVT_DISPATCH_DBG_LOGI(thisMOD,"app_evt_dispatching [end] (%u / %u )\n "
        , ((uint32_t)evt_cb - (uint32_t)cb_list->dummy_00) / sizeof(struct af_evt_dispatch_cb)
        , ((uint32_t)cb_list->dummy_99 - (uint32_t)cb_list->dummy_00) / sizeof(struct af_evt_dispatch_cb)
        );

    k_free(evt_header);
    EVT_DISPATCH_DEB_DBG_L(DBG_SIGNAL_USB_SOF);
	
    #if defined (AIR_SWLA_ENABLE)
    HCLA_RamLogging_V2(SWLA_TYPE_LABEL, label_app_evt_dispatcher, SWLA_DIRECTION_STOP);
    #endif	
}

static void app_evt_dispatcher(struct k_work *work)
{
    k_spinlock_key_t lock = k_spin_lock(&app_dispatcher_evt_q_lock);
    struct af_evt_header *this_evt_header = k_fifo_get(&app_dispatcher_fifo, K_NO_WAIT);
    k_spin_unlock(&app_dispatcher_evt_q_lock, lock);

    while (this_evt_header != NULL)
    {
        app_evt_dispatching(this_evt_header);

        k_spinlock_key_t lock = k_spin_lock(&app_dispatcher_evt_q_lock);
        this_evt_header = k_fifo_get(&app_dispatcher_fifo, K_NO_WAIT);
        k_spin_unlock(&app_dispatcher_evt_q_lock, lock);
    }
}



#if defined(CONFIG_AIR_APP_FRAMEWORK_DELAYABLE)
static void app_delayable_evt_dispatcher(struct k_work *work)
{
    struct k_work_delayable *dwork = CONTAINER_OF(work, struct k_work_delayable,   work);
    
    struct delayable_work_item *dwork_item = CONTAINER_OF(dwork, struct delayable_work_item,   dwork);
    app_evt_dispatching(dwork_item->evt_header);
    dwork_item->evt_header = NULL;

    k_free(dwork_item);
}

struct delayable_work_item * app_delayable_evt_apply(struct af_evt_header *evt_header, k_timeout_t delay)
{
    EVT_DISPATCH_DBG_LOGI(thisMOD,"app_delayable_evt_apply, event_name = 0x%08X--%08X--%08X", *(uint32_t*)&evt_header->cb_list->event_name[8],*(uint32_t*)&evt_header->cb_list->event_name[4], *(uint32_t*)&evt_header->cb_list->event_name[0]);

    struct delayable_work_item * new_dwork_item = k_malloc(sizeof(struct delayable_work_item));

    if (new_dwork_item){
        new_dwork_item->evt_header = evt_header;
        k_work_init_delayable(&new_dwork_item->dwork, app_delayable_evt_dispatcher);
        air_daemon_wq_work_schedule(&new_dwork_item->dwork, delay);
        return new_dwork_item;
    }
    else {
        return NULL;
    }
}

int app_delayable_evt_cancel(struct delayable_work_item * dwork_item)
{
    EVT_DISPATCH_DBG_LOGI(thisMOD,"app_delayable_evt_cancel, dwork = 0x%X", dwork_item);

    if (dwork_item) {
        int ret = k_work_cancel_delayable(&dwork_item->dwork);

        if ((ret == 0) && (dwork_item->evt_header)){
            k_free(dwork_item->evt_header);
            k_free(dwork_item);
            return 0;
        }
    }
    return 1;
}
#endif

void app_evt_apply(struct af_evt_header *evt_header)
{
    EVT_DISPATCH_DBG_LOGI(thisMOD,"app_evt_apply to fifo,   event_name = 0x%08X--%08X--%08X", *(uint32_t*)&evt_header->cb_list->event_name[8],*(uint32_t*)&evt_header->cb_list->event_name[4], *(uint32_t*)&evt_header->cb_list->event_name[0]);
    
    k_spinlock_key_t lock = k_spin_lock(&app_dispatcher_evt_q_lock);
    k_fifo_put(&app_dispatcher_fifo, evt_header);
    k_spin_unlock(&app_dispatcher_evt_q_lock, lock);

    int ret = air_daemon_wq_work_submit(&app_evt_dispatch);
    if(ret < 0){
        EVT_DISPATCH_DBG_LOGI(thisMOD, "app_evt_apply fail, ret = %d", ret);
    }
}






#endif