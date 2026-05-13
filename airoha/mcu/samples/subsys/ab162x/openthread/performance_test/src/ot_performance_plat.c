/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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
#include "ot_performance_plat.h"
#include "ot_performance_led.h"

LOG_MODULE_REGISTER(OT_PREFORMANCE);

#define OT_PLAT_LOG_TAG "[OT_PREFORMANCE] "

/* Definitions for error constants. */
#define AIR_OK          0
#define AIR_FAIL        -1

#define AIR_RETURN_ON_FALSE(a, err_code, log_tag, format, ...) do {                                        \
        if (!(a)) {                                                                              \
            LOG_ERR(log_tag format "\n", ##__VA_ARGS__);        \
            return err_code;                                                                               \
        }                                                                                                  \
    } while(0)

static int hex_digit_to_int(char hex)
{
    if ('A' <= hex && hex <= 'F')
    {
        return 10 + hex - 'A';
    }
    if ('a' <= hex && hex <= 'f')
    {
        return 10 + hex - 'a';
    }
    if ('0' <= hex && hex <= '9')
    {
        return hex - '0';
    }
    return -1;
}

static uint8_t hex_string_to_binary(const char * hex_string, uint8_t * buf, uint8_t buf_size)
{
    int num_char = strlen(hex_string);
    if (num_char != buf_size * 2)
    {
        return 0;
    }
    for (uint8_t i = 0; i < num_char; i += 2)
    {
        int digit0 = hex_digit_to_int(hex_string[i]);
        int digit1 = hex_digit_to_int(hex_string[i + 1]);

        if (digit0 < 0 || digit1 < 0)
        {
            return 0;
        }
        buf[i / 2] = (digit0 << 4) + digit1;
    }

    return buf_size;
}

void ot_performance_set_router_selection_jitter(uint8_t aRouterJitter)
{
    otInstance *instance = openthread_get_default_instance();
    otThreadSetRouterSelectionJitter(instance, aRouterJitter);
}

void ot_performace_set_device_mode(otLinkModeConfig *OT_LinkMode)
{
    otInstance *instance = openthread_get_default_instance();
    if ( !OT_LinkMode->mDeviceType ) {
        otLinkSetPollPeriod(instance, 5000);
    }
    uint32_t poll_period = otLinkGetPollPeriod(instance);
    LOG_INF(OT_PLAT_LOG_TAG"device mode: rx_on_when_idle: %d, device_type: %d, network_data: %d, poll_period: %d", \
        OT_LinkMode->mRxOnWhenIdle, OT_LinkMode->mDeviceType, OT_LinkMode->mNetworkData, poll_period);
    otThreadSetLinkMode(instance, *OT_LinkMode);
}

void ot_performance_factory_reset()
{
    LOG_INF(OT_PLAT_LOG_TAG"ot_performance_factory_reset");
    otInstance *instance = openthread_get_default_instance();
    otInstanceFactoryReset(instance);
}

static void ot_indicator_change_callback(otChangedFlags changed_flags, void* ctx)
{
    otInstance *instance = openthread_get_default_instance();
    otDeviceRole role = otThreadGetDeviceRole(instance);
    LOG_INF(OT_PLAT_LOG_TAG"ot_indicator_change_callback: changed_flags = %d, role = %d", changed_flags, role);
    if (role == OT_DEVICE_ROLE_DISABLED) {
        /* Clear LED */
        ot_performance_led_rgbw(0, 0, 0, 1);
    } else if (role == OT_DEVICE_ROLE_DETACHED) {
        /* White LED */
        ot_performance_led_rgbw(0, 0, 0, 1);
    } else if (role == OT_DEVICE_ROLE_LEADER) {
        /* Red LED  */
        ot_performance_led_rgbw(1, 0, 0, 0);
    } else if (role == OT_DEVICE_ROLE_ROUTER) {
        /* Blue LED  */
        ot_performance_led_rgbw(0, 0, 1, 0);
    } else if (role == OT_DEVICE_ROLE_CHILD) {
        otLinkModeConfig link_mode;
        link_mode = otThreadGetLinkMode(instance);
        /*  FTD: Red LED, MTD: Green LED*/
        if (link_mode.mDeviceType) {
            ot_performance_led_rgbw(1, 0, 0, 0);
        } else {
            ot_performance_led_rgbw(0, 1, 0, 0);
        }
    }
}

otError ot_performace_state_event_init(void)
{
    otInstance *instance = openthread_get_default_instance();
    otError error = otSetStateChangedCallback(instance, ot_indicator_change_callback, NULL);
    return error;
}

otError ot_performace_get_active_tlvs(otOperationalDatasetTlvs *aDataset)
{
    LOG_INF(OT_PLAT_LOG_TAG"ot_performace_get_active_tlvs: aDataset: 0x%x", aDataset);
    otInstance *instance = openthread_get_default_instance();
    otError error = otDatasetGetActiveTlvs(instance, aDataset);
    return error;
}

otError ot_performace_start_openthread(otOperationalDatasetTlvs *datasetTlvs)
{
    otError err = OT_ERROR_NONE;
    otInstance *instance = openthread_get_default_instance();
    LOG_INF(OT_PLAT_LOG_TAG"ot_performace_start_openthread datasetTlvs: 0x%x", datasetTlvs);
    if (datasetTlvs) {
        otDatasetSetActiveTlvs(instance, datasetTlvs);
    } else {
        otOperationalDataset dataset;
        uint8_t len = 0;
#if CONFIG_OPENTHREAD_FTD
        otDatasetCreateNewNetwork(instance, &dataset);
#else
        memset(&dataset, 0, sizeof(otOperationalDataset));
#endif
        // Active timestamp
        dataset.mActiveTimestamp.mSeconds = 1;
        dataset.mActiveTimestamp.mTicks = 0;
        dataset.mActiveTimestamp.mAuthoritative = false;
        dataset.mComponents.mIsActiveTimestampPresent = true;

        // Channel, Pan ID, Network Name
        dataset.mChannel = CONFIG_OPENTHREAD_CHANNEL;
        dataset.mComponents.mIsChannelPresent = true;
        dataset.mPanId = CONFIG_OPENTHREAD_NETWORK_PANID;
        dataset.mComponents.mIsPanIdPresent = true;
        len = strlen(CONFIG_OPENTHREAD_NETWORK_NAME);
        assert(len <= OT_NETWORK_NAME_MAX_SIZE);
        memcpy(dataset.mNetworkName.m8, CONFIG_OPENTHREAD_NETWORK_NAME, len + 1);
        dataset.mComponents.mIsNetworkNamePresent = true;

        // Extended Pan ID
        len = hex_string_to_binary(CONFIG_OPENTHREAD_NETWORK_EXTPANID, dataset.mExtendedPanId.m8,
                                   sizeof(dataset.mExtendedPanId.m8));
        AIR_RETURN_ON_FALSE(len == sizeof(dataset.mExtendedPanId.m8), AIR_FAIL, OT_PLAT_LOG_TAG,
                            "Cannot convert OpenThread extended pan id");
        dataset.mComponents.mIsExtendedPanIdPresent = true;

        // Mesh Local Prefix
        otIp6Prefix prefix;
        memset(&prefix, 0, sizeof(otIp6Prefix));
        if (otIp6PrefixFromString(CONFIG_OPENTHREAD_MESH_LOCAL_PREFIX, &prefix) == OT_ERROR_NONE) {
            memcpy(dataset.mMeshLocalPrefix.m8, prefix.mPrefix.mFields.m8, sizeof(dataset.mMeshLocalPrefix.m8));
            dataset.mComponents.mIsMeshLocalPrefixPresent = true;
        } else {
            LOG_ERR("Failed to parse mesh local prefix", CONFIG_OPENTHREAD_MESH_LOCAL_PREFIX);
        }

        // Network Key
        len = hex_string_to_binary(CONFIG_OPENTHREAD_NETWORK_MASTERKEY, dataset.mNetworkKey.m8,
                                   sizeof(dataset.mNetworkKey.m8));
        AIR_RETURN_ON_FALSE(len == sizeof(dataset.mNetworkKey.m8), AIR_FAIL, OT_PLAT_LOG_TAG,
                            "Cannot convert OpenThread master key");
        dataset.mComponents.mIsNetworkKeyPresent = true;

        // PSKc
        len = hex_string_to_binary(CONFIG_OPENTHREAD_NETWORK_PSKC, dataset.mPskc.m8, sizeof(dataset.mPskc.m8));
        AIR_RETURN_ON_FALSE(len == sizeof(dataset.mPskc.m8), AIR_FAIL, OT_PLAT_LOG_TAG,
                            "Cannot convert OpenThread pre-shared commissioner key");
        dataset.mComponents.mIsPskcPresent = true;

        AIR_RETURN_ON_FALSE(otDatasetSetActive(instance, &dataset) == OT_ERROR_NONE, AIR_FAIL, OT_PLAT_LOG_TAG,
                            "Failed to set OpenThread active dataset");
    }
    otIp6SetEnabled(instance, true);
    if ((err = otThreadSetEnabled(instance, true)) != OT_ERROR_NONE) {
        LOG_ERR(OT_PLAT_LOG_TAG" Failed to enable Thread network: %d", err);
    }

    return err;    
}