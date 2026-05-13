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

#include "app_links.h"

#if KERNELVERSION == 0x3030000
#include <zephyr/random/rand32.h>
#else
#include <zephyr/random/random.h>
#endif

#include <zephyr/bluetooth/hci.h>
#include "air_version.h"
#include "nvkey.h"

#include "app_slide_switch.h"



#define BT_HCI_OP_VS_SET_DEVICE_ADDR		BT_OP(BT_OGF_VS, 0x001A)

#define thisMODULE links
#define thisMOD    "links"

LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
void app_links__scenario_links_init();
void app_links__get_ss_in_which_scenario_link();

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
uint8_t scenario_link_idx = 0;
uint8_t scenario_gaming_link_idx = 0;
uint8_t scenario_bt_link_idx = 0;

#if defined(AIROHA_DEFAULT_LINK_IS_PROPRIERTARY_2_4G)
uint8_t app_link_type = LINKT_TYPE_2_4G;
#else
uint8_t app_link_type = LINKT_TYPE_BT;
#endif

/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
static bool app_links_restore_handler(const struct af_evt_header *evt_header)
{
    struct evt_restore* event = (struct evt_restore*)evt_header;
    APP_LOGI(thisMOD,"app_links_restore_handler , event->restore_mask = %d \n ", event->restore_mask);
    return AF_TRAVERSE_NEXT;
}


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
#if 0
static int bt_le_set_device_addr(uint8_t* bd_addr)
{
    #define BD_ADDR_SIZE  6

    struct net_buf *buf;

    int err;

    buf = bt_hci_cmd_create(BT_HCI_OP_VS_SET_DEVICE_ADDR, BD_ADDR_SIZE);
    if (!buf) {
        return -ENOBUFS;
    }

    net_buf_add_mem(buf, bd_addr, BD_ADDR_SIZE );

    err = bt_hci_cmd_send_sync(BT_HCI_OP_VS_SET_DEVICE_ADDR, buf, NULL);
    if (err) {
        return err;
    }

    return 0;
}
#endif

static void app_links_save()
{
    nvkey_status_t ret;

    ret = nvkey_write_data(NVID_LINK_IDX , (const uint8_t*)&scenario_link_idx , sizeof(scenario_link_idx));
    APP_LOGI(thisMOD,"nvkey write data id = 0x%08X , ret = %d, link = %d", NVID_LINK_IDX, ret, scenario_link_idx);
}
/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/
void app_links_init()
{
    app_links_read();
    app_links__scenario_links_init();

#if 0
    uint8_t bd_addr[6];

    sys_rand_get(bd_addr, 6);
    bd_addr[5] &= 0x3F;

    // usging data and time for device address
    #if 1
    bd_addr[4] = ((build_date_time_str[5]-0x30)<<4)| ((build_date_time_str[6]-0x30));
    bd_addr[3] = ((build_date_time_str[8]-0x30)<<4)| ((build_date_time_str[9]-0x30));
    bd_addr[2] = ((build_date_time_str[11]-0x30)<<4)| ((build_date_time_str[12]-0x30));
    bd_addr[1] = ((build_date_time_str[14]-0x30)<<4)| ((build_date_time_str[15]-0x30));
    bd_addr[0] = ((build_date_time_str[17]-0x30)<<4)| ((build_date_time_str[18]-0x30));
    #endif

    APP_LOGI(thisMOD,"BD_ADDR = 0x%02X-%02X-%02X-%02X-%02X-%02X"
        ,bd_addr[5]
        ,bd_addr[4]
        ,bd_addr[3]
        ,bd_addr[2]
        ,bd_addr[1]
        ,bd_addr[0]
        );
    APP_LOGI(thisMOD,"===========");

    bt_le_set_device_addr(bd_addr);
#endif
}

bool app_links_read_link_type()
{
    return ((LINK_MASK & (0x01<<scenario_link_idx))? 1: 0);
}

bool app_links_read_bond_status()
{
    return BONDING_STATUS_NO;
}

void app_links__increase_scenario_link_idx()
{
    scenario_link_idx++;
    if (scenario_link_idx >= LINK_NUM) {
        scenario_link_idx = 0;
    }
    APP_LOGI(thisMOD,"app_links__increase_scenario_link_idx, scenario_link_idx +1 = %d", scenario_link_idx);
}

void app_links__scenario_links_init()
{
    uint8_t temp_link_idx = scenario_link_idx;
    bool link_type = app_links_read_link_type();  // 1: gaming, 0: bt
    uint8_t link_count = 1;

    //get link 0 type
    if(link_type){
        scenario_gaming_link_idx = scenario_link_idx;
    }
    else{
        scenario_bt_link_idx = scenario_link_idx;
    }
    APP_LOGI(thisMOD,"app_links__scenario_links_init, link_type = %d, bt_link_idx = %d, gaming_link_idx = %d",
                link_type,
                scenario_bt_link_idx,
                scenario_gaming_link_idx);

    //if LINK_NUM = 1, then we only have one link
    if((uint8_t)LINK_NUM > 1)
    {
        //find another link type which first link idx
        while(app_links_read_link_type() == link_type && link_count < (uint8_t)LINK_NUM)
        {
            app_links__increase_scenario_link_idx();
            link_count += 1;
        }

        if(link_type){
            scenario_bt_link_idx = scenario_link_idx;
        }
        else{
            scenario_gaming_link_idx = scenario_link_idx;
        }
        APP_LOGI(thisMOD,"app_links__scenario_links_init, bt_link_idx = %d, gaming_link_idx = %d", scenario_bt_link_idx, scenario_gaming_link_idx);
    }

    scenario_link_idx = (temp_link_idx == 0) ?
                        ((app_link_type == LINKT_TYPE_2_4G) ? scenario_gaming_link_idx : scenario_bt_link_idx) :
                        temp_link_idx;

    APP_LOGI(thisMOD,"app_links__scenario_links_init, scenario_link_idx = %d", scenario_link_idx);
}

void app_links__get_ss_in_which_scenario_link()
{
    uint8_t ss_type = 0;
    GET_SLIDE_SWITCH_MODE(&ss_type);

    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
    if(ss_type == SS_MODE_BT)
    {
        while(app_links_read_link_type())  //until change to bt link:0
        {
            app_links__increase_scenario_link_idx();
        }
        scenario_bt_link_idx = scenario_link_idx;
    }
    else
    #endif
    if(ss_type == SS_MODE_2_4G)
    {
        while(!app_links_read_link_type())  //until change to glink:1
        {
            app_links__increase_scenario_link_idx();
        }
        scenario_gaming_link_idx = scenario_link_idx;
    }
    else if(ss_type == SS_MODE_OFF)
    {
        if(app_links_read_link_type()){
            scenario_gaming_link_idx = scenario_link_idx;
        }
        else{
            scenario_bt_link_idx = scenario_link_idx;
        }
    }

    APP_LOGI(thisMOD,"app_links__get_ss_in_which_scenario_link, ss_type = %d, scenario_link_idx = %d, bt_link_idx = %d, gaming_link_idx = %d",
                    ss_type,
                    scenario_link_idx,
                    scenario_bt_link_idx,
                    scenario_gaming_link_idx);

    return;
}

void app_links_change_to_next_link_idx()
{
    uint8_t last_link_idx = scenario_link_idx;

    app_links__increase_scenario_link_idx();
    app_links__get_ss_in_which_scenario_link();
    if(scenario_link_idx != last_link_idx){
        app_links_save();
    }

    APP_LOGI(thisMOD,"app_links_change_to_next_link_idx  %d => %d", last_link_idx, scenario_link_idx);
}

uint8_t app_links_get_link_idx()
{
    uint8_t ss_type = 0;
    GET_SLIDE_SWITCH_MODE(&ss_type);

    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
    if(ss_type == SS_MODE_BT){
        scenario_link_idx = scenario_bt_link_idx;
    }
    else
    #endif
    if(ss_type == SS_MODE_2_4G){
        scenario_link_idx = scenario_gaming_link_idx;
    }
    #if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
    APP_LOGI(thisMOD,"app_links_get_link_idx, ss_type = %d, scenario_link_idx = %d, bt_link_idx = %d, gaming_link_idx = %d",
                    ss_type,
                    scenario_link_idx,
                    scenario_bt_link_idx,
                    scenario_gaming_link_idx);
    #else
    APP_LOGI(thisMOD,"app_links_get_link_idx, ss_type = %d, scenario_link_idx = %d, gaming_link_idx = %d",
                    ss_type,
                    scenario_link_idx,
                    scenario_gaming_link_idx);
    #endif

    return scenario_link_idx;
}

void app_links_read()
{
    uint8_t temp_link = scenario_link_idx;
    app_nvkey_read_data((uint16_t) NVID_LINK_IDX, (void*)&temp_link, sizeof(temp_link));
    scenario_link_idx = temp_link;
    APP_LOGI(thisMOD,"Now link = %d", scenario_link_idx);
}

/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_restore, app_links_restore_handler);
/*=============================================================================*/
