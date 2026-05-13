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

#include <stdint.h>
#include <string.h>
#include "hal_gpio.h"
#include "hid_plc_common.h"
#include "zephyr/logging/log.h"


#define HID_PLC_COMMON_TAG     "[HID][PLC][COMMON] "
// #define PLC_DEBUG_LOG
// #define PLC_DEBUG_GPIO

#ifdef PLC_DEBUG_GPIO
#define PLC_DEBUG_GPIO_1 HAL_GPIO_6
#define PLC_DEBUG_GPIO_1_GPIO_1 HAL_GPIO_6_GPIO6
#define PLC_DEBUG_GPIO_2 HAL_GPIO_7
#define PLC_DEBUG_GPIO_2_GPIO_2 HAL_GPIO_7_GPIO7
#define PLC_DEBUG_GPIO_3 HAL_GPIO_9
#define PLC_DEBUG_GPIO_3_GPIO_3 HAL_GPIO_9_GPIO9
#endif

typedef struct{
    int32_t last_valid_x;
    int32_t last_valid_y;
    point data_in;
    point data_out;
} hid_plc_common_t;

static hid_plc_common_t hid_plc_common_ctx;

#ifdef PLC_DEBUG_GPIO
void plc_hid_debug_gpio_init(void)
{
    hal_gpio_init(PLC_DEBUG_GPIO_1);
    hal_pinmux_set_function(PLC_DEBUG_GPIO_1, PLC_DEBUG_GPIO_1_GPIO_1);
    hal_gpio_set_direction(PLC_DEBUG_GPIO_1, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_output(PLC_DEBUG_GPIO_1, HAL_GPIO_DATA_LOW);

    hal_gpio_init(PLC_DEBUG_GPIO_2);
    hal_pinmux_set_function(PLC_DEBUG_GPIO_2, PLC_DEBUG_GPIO_2_GPIO_2);
    hal_gpio_set_direction(PLC_DEBUG_GPIO_2, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_output(PLC_DEBUG_GPIO_2, HAL_GPIO_DATA_LOW);

    hal_gpio_init(PLC_DEBUG_GPIO_3);
    hal_pinmux_set_function(PLC_DEBUG_GPIO_3, PLC_DEBUG_GPIO_3_GPIO_3);
    hal_gpio_set_direction(PLC_DEBUG_GPIO_3, HAL_GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_output(PLC_DEBUG_GPIO_3, HAL_GPIO_DATA_LOW);
}
#endif

#ifdef CONFIG_AIR_HID_PLC
static point *hid_data0 = NULL;
#endif

static int32_t  last_variance_x, last_variance_y = 0;
ATTR_TEXT_IN_SYSRAM int8_t hid_plc_common_detect_big_drift(int32_t *x, int32_t *y)
{
    /*Get Statistics from history data*/
    int32_t mean_x, mean_y, variance_x, variance_y = 0;
    int32_t min_x, max_x, min_y, max_y = 0;
    int32_t weight_x, weight_y = 0;
    hid_plc_get_statistics(&mean_x, &mean_y, &variance_x, &variance_y);
    if (variance_x != 0) {
        last_variance_x = variance_x;
    } else {
        if (last_variance_x == 0) {
            return 0;
        }
    }
    if (variance_y != 0) {
        last_variance_y = variance_y;
    } else {
        if (last_variance_y == 0) {
            return 0;
        }
    }
    if (mean_x > 0) {
        if (mean_x > last_variance_x) {
            weight_x = mean_x;
        } else {
            weight_x = last_variance_x;
        }
    } else {
        if ((-mean_x) > last_variance_x) {
            weight_x = -mean_x;
        } else {
            weight_x = last_variance_x;
        }
    }
    min_x = mean_x - CONFIG_AIR_HID_PLC_BIG_DRIFT_THRESHOLD * weight_x;
    max_x = mean_x + CONFIG_AIR_HID_PLC_BIG_DRIFT_THRESHOLD * weight_x;
    if (mean_y > 0) {
        if (mean_y > last_variance_y) {
            weight_y = mean_y;
        } else {
            weight_y = last_variance_y;
        }
    } else {
        if ((-mean_y) > last_variance_y) {
            weight_y = -mean_y;
        } else {
            weight_y = last_variance_y;
        }
    }
    min_y = mean_y - CONFIG_AIR_HID_PLC_BIG_DRIFT_THRESHOLD * weight_y;
    max_y = mean_y + CONFIG_AIR_HID_PLC_BIG_DRIFT_THRESHOLD * weight_y;

    // LOG_INF(HID_PLC_COMMON_TAG"hid_plc_common_detect_big_drift: data_in(%d, %d), mean:(%d,%d), variance:(%d, %d), last:(%d, %d), x[%d, %d], y[%d, %d]",
    //         *x, *y, mean_x, mean_y, variance_x, variance_y,
    //         last_variance_x, last_variance_y,
    //         min_x, max_x, min_y, max_y);

    if (*x < min_x || *x > max_x || *y < min_y || *y > max_y) {
        return -1;
    }

    return 0;
}

ATTR_TEXT_IN_SYSRAM void hid_plc_common_get_character_data(int32_t *x, int32_t *y)
{
    hid_plc_get_character_data(x, y);
}

ATTR_TEXT_IN_SYSRAM hid_plc_common_status_t hid_plc_common_get_plc_data(hid_plc_param_t *hid_plc_param, int32_t *x, int32_t *y)
{
    hid_plc_common_status_t ret = HID_PLC_COMMON_SUCCESS;
    if (hid_plc_param == NULL || x == NULL || y == NULL) {
        return ret;
    }
/* update raw hid data */
    hid_plc_common_ctx.data_in.x = hid_plc_param->x;
    hid_plc_common_ctx.data_in.y = hid_plc_param->y;
    hid_plc_common_ctx.data_in.correct = hid_plc_param->correct;
    /* fake data means data_in.fake = true; real data means data_in.fake = false; */
    if (hid_plc_param->reason) {
        hid_plc_common_ctx.data_in.fake = true;
    } else {
        hid_plc_common_ctx.data_in.fake = false;
    }

/* Rx failed & Correct data process */
    hid_plc_update_data(&hid_plc_common_ctx.data_in);
#ifdef CONFIG_AIR_HID_PLC
    hid_plc_little_window();
    hid_plc_status status = hid_plc_begin(hid_plc_param, &hid_plc_common_ctx.data_out);
#else
/* Normal data process */
    hid_plc_common_ctx.data_out.x =  hid_plc_param->x;
    hid_plc_common_ctx.data_out.y =  hid_plc_param->y;
/* Way1: Duplicate will deduct the last valid data */
    // /* Duplicate data process if without PLC */
    // if (!hid_plc_param->reason){
    //     hid_plc_common_ctx.last_valid_x = hid_plc_param->x;
    //     hid_plc_common_ctx.last_valid_y = hid_plc_param->y;
    // }
    // if (hid_plc_param->reason == HID_PLC_REASON_DUP_PKT){
    //     hid_plc_common_ctx.data_out.x -= hid_plc_common_ctx.last_valid_x;
    //     hid_plc_common_ctx.data_out.y -= hid_plc_common_ctx.last_valid_y;
    //     hid_plc_common_ctx.last_valid_x =  hid_plc_param->x;
    //     hid_plc_common_ctx.last_valid_y =  hid_plc_param->y;
    // }
/* Way2: Discard duplicate data */
    if (hid_plc_param->reason == HID_PLC_REASON_DUP_PKT) {
        hid_plc_common_ctx.data_out.x =  0;
        hid_plc_common_ctx.data_out.y =  0;
    }
#endif

/* Out data process*/
    /* int32 -> int16 */
    if (hid_plc_common_ctx.data_out.x > 32767)
    {
        hid_plc_common_ctx.data_out.x = 32767;
    }
    else if (hid_plc_common_ctx.data_out.x < -32768)
    {
        hid_plc_common_ctx.data_out.x = -32768;
    }
    if (hid_plc_common_ctx.data_out.y > 32767)
    {
        hid_plc_common_ctx.data_out.y = 32767;
    }
    else if (hid_plc_common_ctx.data_out.y < -32768)
    {
        hid_plc_common_ctx.data_out.y = -32768;
    }
#ifdef CONFIG_AIR_HID_PLC
    /* get hid_data0 */
    hid_plc_t *hid_plc_ctx = hid_plc_get_ctx();
    hid_data0 = hid_plc_load_data_from_ring(hid_plc_ctx, 1);
    if(status == APP_HID_PLC_CORRECT){
        hid_data0->x = hid_plc_common_ctx.data_out.x;
        hid_data0->y = hid_plc_common_ctx.data_out.y;
    } else if(status == APP_HID_PLC_CORRECT_ZERO) {
        ret = HID_PLC_COMMON_REVISED_ZERO;
    }
#endif

    *x = hid_plc_common_ctx.data_out.x;
    *y = hid_plc_common_ctx.data_out.y;
#ifdef PLC_DEBUG_LOG
if (hid_plc_param->report_rate <= BT_ULL_LE_HID_SRV_REPORT_RATE_LEVEL_7) {
#ifdef CONFIG_AIR_HID_PLC
    LOG_INF(HID_PLC_COMMON_TAG "hid_plc_common_get_plc_data, data_in:(%04d,%04d), data_out:(%04d,%04d), accum:%d, pre(%d,%d), zero:%d; lose:%d, reason: %d", 
                                            hid_plc_param->x, hid_plc_param->y, hid_plc_common_ctx.data_out.x, hid_plc_common_ctx.data_out.y,
                                            hid_data0->accumulate, hid_plc_ctx->predict_x, hid_plc_ctx->predict_y,
                                            hid_data0->hid_data_char.zero_num,
                                            hid_data0->hid_data_char.lose_point_num,
                                            hid_plc_param->reason);
#else
    LOG_INF(HID_PLC_COMMON_TAG "hid_plc_common_get_plc_data, data_in:(%04d,%04d), data_out:(%04d,%04d), reason: %d, last_valid(%04d,%04d)", 
                                            hid_plc_param->x, hid_plc_param->y, hid_plc_common_ctx.data_out.x, 
                                            hid_plc_common_ctx.data_out.y, hid_plc_param->reason,
                                            hid_plc_common_ctx.last_valid_x, hid_plc_common_ctx.last_valid_y);
#endif
}
#endif
    return ret;
}

ATTR_TEXT_IN_SYSRAM void hid_plc_common_handler(hid_plc_param_t *hid_plc_param)
{
#ifdef CONFIG_AIR_HID_PLC_CALCULATE
    hid_plc_window();
    /* calculate the predicted plc data*/
    hid_plc_preprocess_data();
#endif
}

void hid_plc_common_clear(void)
{
    // LOG_INF(HID_PLC_COMMON_TAG "hid_plc_common_clear");
    last_variance_x = 0;
    last_variance_y = 0;
    memset(&hid_plc_common_ctx, 0, sizeof(hid_plc_common_ctx));
#ifdef CONFIG_AIR_HID_PLC_CALCULATE
    hid_plc_clear();
#endif
}

void hid_plc_common_init(void)
{
    LOG_INF(HID_PLC_COMMON_TAG "hid_plc_common_init");
#ifdef PLC_DEBUG_GPIO
	plc_hid_debug_gpio_init();
#endif
    memset(&hid_plc_common_ctx, 0, sizeof(hid_plc_common_ctx));
#ifdef CONFIG_AIR_HID_PLC_CALCULATE
    hid_plc_init();
#endif
}
