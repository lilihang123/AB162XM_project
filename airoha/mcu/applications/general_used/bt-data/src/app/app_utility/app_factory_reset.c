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

#include "app_factory_reset.h"
#include "factory_reset.h"

#define thisMODULE app_fctrst
#define thisMOD    "app_fctrst"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/

uint8_t factory_reset_res = false;
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_factory_reset_evt_handler(const struct af_evt_header *evt_header)
{
    struct evt_factory_reset* event = (struct evt_factory_reset*)evt_header;
    APP_LOGI(thisMOD,"app_factory_reset_evt_handler , status = %d", event->status);

    if(event->status)
    {
        k_sleep(K_MSEC(1));
        factory_reset_enable();
    }

    return AF_TRAVERSE_NEXT;
}

static bool app_factory_reset_evt_race_cmd_req(const struct af_evt_header *evt_header)
{
    struct evt_race_cmd_req* req_event = (struct evt_race_cmd_req*)evt_header;
    APP_LOGI(thisMOD,"evt_race_cmd_req , cmd = %x", req_event->cmd);

    switch(req_event->cmd)
    {
        case RACE_CMD_ENABLE_KEY_EVENT:
        {
            if(req_event->ENABLE_KEY_EVNET.event_id == 0x0095)
            {
                nvkey_status_t ret;
                uint32_t dump_mode;
                dump_mode = 0x0CE10CE1;
                ret = nvkey_write_data(NVID_SYS_EXP_DUMP_MODE , (const uint8_t*)&dump_mode , sizeof(dump_mode));
                APP_LOGI(thisMOD,"nvkey write data id = 0x%04X , ret = %d, value = 0x%x", NVID_SYS_EXP_DUMP_MODE, ret, dump_mode);
                struct evt_race_cmd_rsp* event = create_evt_race_cmd_rsp();
                if (event){
                    event->cmd = RACE_CMD_ENABLE_KEY_EVENT;
                    event->OTHERS.status = 0;
                    AF_EVT_SUBMIT(event);
                }

                struct evt_factory_reset* evt = create_evt_factory_reset();
                if (evt){
                    evt->status = true;
                    AF_EVT_SUBMIT(evt);
                }
            }
        }
        break;

        default:
          break;
    }

    return AF_TRAVERSE_NEXT;
}




/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/



/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
bool app_factory_reset_hdl(const uint16_t *nvkey_id_list, uint8_t size)
{
    uint32_t result = factory_reset_handler(nvkey_id_list, size);

    uint32_t dump_mode;
    app_nvkey_read_data((uint16_t) NVID_SYS_EXP_DUMP_MODE, (void*)&dump_mode, sizeof(dump_mode));
    APP_LOGI(thisMOD,"NVID_SYS_EXP_DUMP_MODE = 0x%x",  dump_mode);

    if(result == FACTORY_RESET_OK)
    {
        factory_reset_res = true;
        APP_LOGI(thisMOD,"app_factory_reset_init, FACTORY_RESET_OK");
    }
    else
    {
        APP_LOGI(thisMOD,"app_factory_reset_init, result = %d", result);
    }
    return result;
}
inline uint8_t app_factory_reset_get_status()
{
    return factory_reset_res;
}

inline void app_factory_reset_clear_status()
{
    factory_reset_res = false;
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_factory_reset, app_factory_reset_evt_handler);
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_race_cmd_req, app_factory_reset_evt_race_cmd_req);
/*=============================================================================*/