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
#include <zephyr/logging/log.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/sys/util.h>
#include <zephyr/settings/settings.h>

#include "air_chip.h"

#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "hid_scenario_adv.h"

#define thisMODULE adv
#define thisMOD    "adv"
LOG_MODULE_REGISTER(thisMODULE);
/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/
void hid_scenario_adv_switch_advertising(struct k_work *work);
void hid_scenario_adv_switch_ad_timeout(struct k_timer *timer);
/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/
#define GET_ADDRESS_ERROR 0
#define MAX_REPAIR_COUNT CONFIG_BT_MAX_PAIRED - 1
#define BT_ADV_START_INTERVAL_MAX  0x0040
#define BT_ADV_START_INTERVAL_MIN  0x0020

#define BT_FILTER_ADV_START_INTERVAL_MAX  0x0040
#define BT_FILTER_ADV_START_INTERVAL_MIN  0x0020
static const uint8_t zero_address[6] = {0}; 
uint8_t used_id[MAX_REPAIR_COUNT];

#if defined(CONFIG_AIR_MUTIPLE_ADV_SUPPORT)
#define DEFAULT_ADV_CHANGE_INTERVAL 100
K_WORK_DEFINE(switch_advertising_work, hid_scenario_adv_switch_advertising);
K_TIMER_DEFINE(advertising_timer, hid_scenario_adv_switch_ad_timeout, NULL);
#endif
/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/
#if defined (CONFIG_AIR_MICROSOFT_SWIFT_PAIR)
#define SWIFT_PAIR "\x06\x00\x03\x00\x80"
const uint8_t microsoft_swift[] = SWIFT_PAIR;
#endif

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
uint16_t ad_appearance = CONFIG_BT_DEVICE_APPEARANCE;

#if defined(CONFIG_AIR_MUTIPLE_ADV_SUPPORT)
typedef struct{
    uint8_t adv_group_num;
    uint8_t address_id;
}T_ADV_CTRL_S;

struct ad_group_info {
    const struct bt_data *data;
    size_t len;
};

T_ADV_CTRL_S adv_ctrl = {0};

static const struct bt_data ad_group1[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
		      BT_UUID_16_ENCODE(BT_UUID_HIDS_VAL)),
    BT_DATA(BT_DATA_GAP_APPEARANCE, &ad_appearance, sizeof(ad_appearance) ),
    BT_DATA(BT_DATA_NAME_SHORTENED, CONFIG_AIR_SHORTEN_DEVICE_NAME, (sizeof(CONFIG_AIR_SHORTEN_DEVICE_NAME) - 1)),
};

static const struct bt_data ad_group2[] = {
    BT_DATA(BT_DATA_GAP_APPEARANCE, &ad_appearance, sizeof(ad_appearance) ),
    BT_DATA(BT_DATA_NAME_SHORTENED, CONFIG_AIR_SHORTEN_DEVICE_NAME, (sizeof(CONFIG_AIR_SHORTEN_DEVICE_NAME) - 1)),
    #if defined (CONFIG_AIR_MICROSOFT_SWIFT_PAIR)
    BT_DATA(BT_DATA_MANUFACTURER_DATA , microsoft_swift, sizeof(microsoft_swift) ),
    #endif
};

static const struct ad_group_info ad_groups[] = {
    {ad_group1, ARRAY_SIZE(ad_group1)},
    {ad_group2, ARRAY_SIZE(ad_group2)},
};

_Static_assert(!(CONFIG_AIR_ADV_CONTENT_CHANGE_INTERVAL == 0 && ARRAY_SIZE(ad_groups) > 1), "config interval or array size error");
#else
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
		      BT_UUID_16_ENCODE(BT_UUID_HIDS_VAL),
		      BT_UUID_16_ENCODE(BT_UUID_BAS_VAL)),

    BT_DATA(BT_DATA_GAP_APPEARANCE, &ad_appearance, sizeof(ad_appearance) ),
    BT_DATA(BT_DATA_NAME_SHORTENED, CONFIG_AIR_SHORTEN_DEVICE_NAME, (sizeof(CONFIG_AIR_SHORTEN_DEVICE_NAME) - 1)),
    #if defined (CONFIG_AIR_MICROSOFT_SWIFT_PAIR)
    BT_DATA(BT_DATA_MANUFACTURER_DATA , microsoft_swift, (sizeof(microsoft_swift) - 1)),
    #endif
};
#endif

static const struct bt_data sd[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, (sizeof(CONFIG_BT_DEVICE_NAME) - 1)),
};

static const struct bt_data reconn_ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
		      BT_UUID_16_ENCODE(BT_UUID_HIDS_VAL),
		      BT_UUID_16_ENCODE(BT_UUID_BAS_VAL)),

    BT_DATA(BT_DATA_NAME_SHORTENED, CONFIG_AIR_SHORTEN_DEVICE_NAME, (sizeof(CONFIG_AIR_SHORTEN_DEVICE_NAME) - 1)),
    BT_DATA(BT_DATA_GAP_APPEARANCE, &ad_appearance, sizeof(ad_appearance)),
};
#endif

uint16_t ad_appearance_2_4G_mouse = CONFIG_AIR_2_4G_DEVICE_APPEARANCE;

static const struct bt_data ad_proprietary_2_4G_link[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_GAP_APPEARANCE, &ad_appearance_2_4G_mouse, sizeof(ad_appearance_2_4G_mouse) ),
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, (sizeof(CONFIG_BT_DEVICE_NAME) - 1)),    
};


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/
#if defined(CONFIG_AIR_MUTIPLE_ADV_SUPPORT)
void hid_scenario_adv_switch_timer_start()
{
    // make sure the connection is not established
    uint8_t state = hid_scenario_get_state();

    if((state & (MODE_OPEN_SPECIFIED)) || (state == MODE_CLOSED)){
        uint16_t switch_time = CONFIG_AIR_ADV_CONTENT_CHANGE_INTERVAL;
        if(switch_time < DEFAULT_ADV_CHANGE_INTERVAL)
        {
            switch_time = DEFAULT_ADV_CHANGE_INTERVAL;
        }

        k_timer_start(&advertising_timer, K_MSEC(switch_time), K_NO_WAIT);
    }
}

void hid_scenario_adv_switch_advertising(struct k_work *work)
{
    struct bt_le_adv_param adv_param;
    adv_param = *BT_LE_ADV_CONN_ONE_TIME;
    adv_param.interval_max = BT_ADV_START_INTERVAL_MAX;
    adv_param.interval_min = BT_ADV_START_INTERVAL_MIN;
    adv_param.id = adv_ctrl.address_id;
    if(adv_ctrl.adv_group_num < (ARRAY_SIZE(ad_groups) - 1))
    {
        adv_ctrl.adv_group_num++;
    }
    else {
        adv_ctrl.adv_group_num = 0;
    }

    bt_le_adv_stop();
    DBG_LOGI(thisMOD, "hid_scenario_adv_switch_advertising adv_group_num = %d len= %d", adv_ctrl.adv_group_num, ad_groups[adv_ctrl.adv_group_num].len);
    int err = bt_le_adv_start(&adv_param, ad_groups[adv_ctrl.adv_group_num].data, ad_groups[adv_ctrl.adv_group_num].len, sd, ARRAY_SIZE(sd) );

    if (err)
    {
        DBG_LOGI(thisMOD,"Bluetooth undir adv failed (err %d)\n", err);
    }
    else
    {
        DBG_LOGI(thisMOD,"hid_scenario_undir_adv_start successed\n");
    }
    hid_scenario_adv_switch_timer_start();
}

void hid_scenario_adv_switch_ad_timeout(struct k_timer *timer)
{
    k_work_submit(&switch_advertising_work);
}
#endif


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/
static uint8_t adv_set_static_random_address(uint8_t id)
{
    int err;
    bt_addr_le_t static_random_addr;
    struct bt_le_oob oob;

    err = bt_le_oob_get_local(id, &oob);
    if (err) 
    {
        DBG_LOGI(thisMOD,"Failed to get OOB data (err %d) id = %d\n", err, id);
        return 0;
    }

    if(memcmp(zero_address, &oob.addr.a.val[0], 6) == 0)
    {
        err = bt_addr_le_create_static(&static_random_addr);
        if (err) 
        {
            DBG_LOGI(thisMOD,"bt_addr_le_create_static failed (err %d)\n", err);
            return GET_ADDRESS_ERROR;
        }   
        static_random_addr.type = BT_ADDR_LE_RANDOM;
        err = bt_id_create(&static_random_addr, NULL);
        if (err < 0)
        {
            DBG_LOGI(thisMOD,"bt_id_create failed with error code %d\n", err);
            return GET_ADDRESS_ERROR;
        }

        DBG_LOGI(thisMOD,"Random static address set successfully for id %d\n", err);
        return err;
    }

    return GET_ADDRESS_ERROR;
}

void hid_scenario_adv_print_local_address(uint8_t id)
{
    int err;
    struct bt_le_oob oob;

    err = bt_le_oob_get_local(id, &oob);
    if (err) 
    {
        DBG_LOGI(thisMOD,"Failed to get OOB data (err %d) id = %d\n", err, id);
        return;
    }
    DBG_LOGI(thisMOD,"bt_le_oob_get_local with 0x%02X-%02X-%02X-%02X-%02X-%02X, type = %d"
            , oob.addr.a.val[0]
            , oob.addr.a.val[1]
            , oob.addr.a.val[2]
            , oob.addr.a.val[3]
            , oob.addr.a.val[4]
            , oob.addr.a.val[5]
            , oob.addr.type
    );
}
/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/

uint8_t hid_scenario_undir_adv_start(T_HID_SCENARIO_DEVICE_TYPE_E mode, uint8_t address_id)
{
    int err = 0;
    struct bt_le_adv_param adv_param;
    adv_param = *BT_LE_ADV_CONN_ONE_TIME;
    adv_param.interval_max = BT_ADV_START_INTERVAL_MAX;
    adv_param.interval_min = BT_ADV_START_INTERVAL_MIN;
    adv_param.id = address_id;

    DBG_LOGI(thisMOD, "hid_scenario_undir_adv_start, mode = %d, link_idx = %d", mode , adv_param.id);

    #if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
    if (mode == HID_SCENARIO_BT_MODE){
        #if defined(CONFIG_AIR_MUTIPLE_ADV_SUPPORT)
        DBG_LOGI(thisMOD,"hid_scenario_undir_adv_start, ad len = %d, sd len %d", ad_groups[adv_ctrl.adv_group_num].len, ARRAY_SIZE(sd));
        adv_ctrl.adv_group_num = 0;
        adv_ctrl.address_id = address_id;
        err = bt_le_adv_start(&adv_param, ad_groups[adv_ctrl.adv_group_num].data, ad_groups[adv_ctrl.adv_group_num].len, sd, ARRAY_SIZE(sd) );
        if(ARRAY_SIZE(ad_groups) > 1 && (CONFIG_AIR_ADV_CONTENT_CHANGE_INTERVAL != 0))
        {
            hid_scenario_adv_switch_timer_start();
        }
        #else
        DBG_LOGI(thisMOD,"hid_scenario_undir_adv_start, ad len = %d, sd len %d", ARRAY_SIZE(ad), ARRAY_SIZE(sd));  
        err = bt_le_adv_start(&adv_param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd) );
        #endif
    }
    else 
    #endif
    if (mode == HID_SCENARIO_GAMING_MODE){
        DBG_LOGI(thisMOD,"hid_scenario_undir_adv_start, ad_proprietary_2_4G_link = %d", ARRAY_SIZE(ad_proprietary_2_4G_link) );  
        err = bt_le_adv_start(&adv_param, ad_proprietary_2_4G_link, ARRAY_SIZE(ad_proprietary_2_4G_link), NULL, 0 );
    }
    else {
        DBG_LOGI(thisMOD,"Error");  
    }

    if (err)
    {      
        DBG_LOGI(thisMOD,"Bluetooth undir adv failed (err %d)", err);      
    }
    else
    {
        DBG_LOGI(thisMOD,"app_undir_adv_start successed");
    }

    //app_adv_announce_status(ADV_STATUS_UNDIRECT_ADV);

    return err;
}

uint8_t hid_scenario_adv_stop()
{
    DBG_LOGI(thisMOD,"hid_scenario_adv_stop\n");
    return bt_le_adv_stop();
}

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
uint8_t hid_scenario_dir_adv_start(T_HID_SCENARIO_DEVICE_TYPE_E mode, const bt_addr_le_t* bond_addr, uint8_t address_id)
{
    int err = true;
    struct bt_le_adv_param adv_param;
    adv_param = *BT_LE_ADV_CONN_DIR(bond_addr);
    adv_param.id = address_id;

    if (mode == HID_SCENARIO_BT_MODE){
        DBG_LOGI(thisMOD,"hid_scenario_dir_adv_start, ad len = %d, sd len %d,  LINKT_TYPE_BT", ARRAY_SIZE(reconn_ad), ARRAY_SIZE(sd));
        err = bt_le_adv_start(&adv_param, reconn_ad, ARRAY_SIZE(reconn_ad), NULL, 0);
    }
    else {
        DBG_LOGI(thisMOD,"Error");
    }

    if (err)
    {
        DBG_LOGI(thisMOD,"Bluetooth dir adv failed (err %d)", err);
    }
    else
    {
        DBG_LOGI(thisMOD,"hid_scenario_dir_adv_start successed");
    }

    //app_adv_announce_status(ADV_STATUS_DIRECT_ADV);

    return err;
}

uint8_t hid_scenario_filter_undir_adv_start(T_HID_SCENARIO_DEVICE_TYPE_E mode, const bt_addr_le_t* bond_addr, uint8_t address_id)
{
    int err = true;
    struct bt_le_adv_param adv_param;
    adv_param = *BT_LE_ADV_CONN_ONE_TIME;
    adv_param.options |= BT_LE_ADV_OPT_FILTER_CONN;
    adv_param.interval_max = BT_FILTER_ADV_START_INTERVAL_MAX;
    adv_param.interval_min = BT_FILTER_ADV_START_INTERVAL_MIN;
    adv_param.id = address_id;

    DBG_LOGI(thisMOD, "hid_scenario_filter_undir_adv_start, mode = %d, link_idx = %d", mode , address_id);

    err = bt_le_filter_accept_list_add(bond_addr);
    if (err) {
        DBG_LOGI(thisMOD,"bt_le_filter_accept_list_add failed (err %d)", err);
    }
    else{
        DBG_LOGI(thisMOD,"bt_le_filter_accept_list_add successed");
    }

    if (mode == HID_SCENARIO_BT_MODE){
        DBG_LOGI(thisMOD,"hid_scenario_filter_undir_adv_start, ad len = %d, sd len %d,  LINKT_TYPE_BT", ARRAY_SIZE(reconn_ad), ARRAY_SIZE(sd));
        err = bt_le_adv_start(&adv_param, reconn_ad, ARRAY_SIZE(reconn_ad), NULL, 0 );
    }
    else {
        DBG_LOGI(thisMOD,"Error");
    }

    if (err)
    {
        DBG_LOGI(thisMOD,"Bluetooth filter undir adv failed (err %d)", err);
    }
    else
    {
        DBG_LOGI(thisMOD,"hid_scenario_filter_undir_adv_start successed"); 
    }

    //app_adv_announce_status(ADV_STATUS_DIRECT_ADV);

    return err; 
}
#endif

uint8_t hid_scenario_adv_local_address_id_read(uint8_t link_idx)
{
    uint8_t local_address_id = link_idx + 1;
    uint8_t ret = HID_SCENARIO_NVKEY_READ_DATA(NVID_LOCAL_DEVICES_ADDR_ID_0 + link_idx, (void*)&local_address_id, sizeof(local_address_id));

    if(ret)
    {
        DBG_LOGI(thisMOD,"nvkey read local_address_id = %d", local_address_id);
        return local_address_id;
    }
    else
    {
        for(uint32_t idx = 1; idx <= MAX_REPAIR_COUNT ; idx++)
        {
            uint32_t id = adv_set_static_random_address(idx);
            if(id != GET_ADDRESS_ERROR)
            {
                hid_scenario_adv_local_address_id_save(link_idx, id);
                return id;
            }
        }
    }

    return GET_ADDRESS_ERROR;
}

uint32_t hid_scenario_adv_get_unused_address_id()
{
    bool is_used[CONFIG_BT_MAX_PAIRED] = {false};
    for(uint32_t i = 0; i < MAX_REPAIR_COUNT - 1 ; i++){
        is_used[hid_scenario_adv_local_address_id_read(i)] = 1;
        // DBG_LOGI(thisMOD,"i =%d, used_id = %d", i, hid_scenario_adv_local_address_id_read(i));
    }

    for(uint32_t i = 1; i < CONFIG_BT_MAX_PAIRED ; i++){
        if(!is_used[i])
        {
            adv_set_static_random_address(i);
            DBG_LOGI(thisMOD,"hid_scenario_adv_get_unused_address_id = %d", i);
            return i;
        }
    }
    return GET_ADDRESS_ERROR;
}

void hid_scenario_adv_local_address_id_save(uint8_t link_idx, uint8_t address_id)
{
    nvkey_status_t ret;
    ret = nvkey_write_data(NVID_LOCAL_DEVICES_ADDR_ID_0 + link_idx, (const uint8_t*)&address_id , sizeof(address_id));
    DBG_LOGI(thisMOD,"nvkey write data id = 0x%08X , ret = %d, link = %d, address_id = %d", NVID_LOCAL_DEVICES_ADDR_ID_0 + link_idx, ret, link_idx, address_id);
}

void hid_scenario_adv_delete_id()
{
    int err;
    size_t count = CONFIG_BT_ID_MAX;

    bt_id_get(NULL, &count);
    DBG_LOGI(thisMOD,"bt_id_delete count = %d", count);

    for (uint32_t id = count-1 ; id >= 1; id--) 
    {
        err = bt_id_delete(id);
        if(err)
        {
            DBG_LOGI(thisMOD,"bt_id_delete err = %d", err);
        }
        else 
        {
            DBG_LOGI(thisMOD,"bt_id_delete id = %d", id);
        }
    }
}

#if defined(CONFIG_AIR_MUTIPLE_ADV_SUPPORT)
void hid_scenario_adv_stop_advertising_timer()
{
    k_timer_stop(&advertising_timer);
}
#endif