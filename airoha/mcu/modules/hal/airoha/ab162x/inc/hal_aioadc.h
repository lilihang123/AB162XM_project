/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#ifndef __HAL_AIOADC_H__
#define __HAL_AIOADC_H__

typedef enum
{
    HAL_AIOADC_CH_0 = 0, /*GPIO 25 */
    HAL_AIOADC_CH_1 = 1, /*GPIO 26 */
    HAL_AIOADC_CH_2 = 2, /*GPIO 27 */
    HAL_AIOADC_CH_3 = 3, /*GPIO 28 */
    HAL_AIOADC_CH_4 = 4, /*GPIO 29 */
    HAL_AIOADC_CH_5 = 5, /*GPIO 30 */
    HAL_AIOADC_CH_6 = 6, /*GPIO 31 */
    HAL_AIOADC_CH_7 = 7, /*GPIO 32 */
    HAL_AIOADC_CH_8 = 8, /*GPIO 33 */
    HAL_AIOADC_CH_9 = 9, /*GPIO 34 */
    HAL_AIOADC_CH_MAX = 10,
} hal_aioadc_ch_en_t;

typedef enum
{
    HAL_AIOADC_MODE_SE_0 = 0,//max 3.0v
    HAL_AIOADC_MODE_SE_1 = 1,//max 1.8v
    HAL_AIOADC_MODE_SE_2 = 2,//max 0.9v
    HAL_AIOADC_MODE_SE_3 = 3,//max 0.6v
    HAL_AIOADC_MODE_SE_4 = 4,//max 0.45v
    /*diff mode only support gpio26(v+)/27(v-),gpio28(v+)/29(v-)*/
    HAL_AIOADC_MODE_DIFF_0 = 5,//max 3.0v
    HAL_AIOADC_MODE_DIFF_1 = 6,//max 1.8v
    HAL_AIOADC_MODE_DIFF_2 = 7,//max 0.9v
    HAL_AIOADC_MODE_DIFF_3 = 8,//max 0.6v
    HAL_AIOADC_MODE_DIFF_4 = 9,//max 0.45v
    HAL_AIOADC_MODE_VBAT = 10,//internal channel ,ONLY CH 0 READ DATA
    // HAL_AIOADC_MODE_RFCAL = 11,//internal channel ,ONLY CH 0 READ DATA
    // HAL_AIOADC_MODE_PMU_ATST = 12,//internal channel ,ONLY CH 0 READ DATA
    HAL_AIOADC_MODE_TEMP_SENSOR = 13,//internal channel ,ONLY CH 0 READ DATA
    HAL_AIOADC_MODE_MAX = 14,
} hal_aioadc_mode_sel_t;

typedef enum
{
    HAL_AIOADC_SW_CH_DLY_0T = 0,
    HAL_AIOADC_SW_CH_DLY_1T = 1,
    HAL_AIOADC_SW_CH_DLY_2T = 2,
    HAL_AIOADC_SW_CH_DLY_4T = 3,
    HAL_AIOADC_SW_CH_DLY_8T = 4,
    HAL_AIOADC_SW_CH_DLY_16T = 5,
    HAL_AIOADC_SW_CH_DLY_32T = 6,
    HAL_AIOADC_SW_CH_DLY_64T = 7,
    HAL_AIOADC_SW_CH_DLY_MAX = 8,
} hal_aioadc_sw_ch_dly_t;

typedef enum
{
    HAL_AIOADC_RST_DLY_0T = 0,
    HAL_AIOADC_RST_DLY_4T = 1,
    HAL_AIOADC_RST_DLY_8T = 2,
    HAL_AIOADC_RST_DLY_16T = 3,
    HAL_AIOADC_RST_DLY_32T = 4,
    HAL_AIOADC_RST_DLY_40T = 5,
    HAL_AIOADC_RST_DLY_48T = 6,
    HAL_AIOADC_RST_DLY_56T = 7,
    HAL_AIOADC_RST_DLY_64T = 8,
    HAL_AIOADC_RST_DLY_72T = 9,
    HAL_AIOADC_RST_DLY_80T = 10,
    HAL_AIOADC_RST_DLY_128T = 11,
    HAL_AIOADC_RST_DLY_144T = 12,
    HAL_AIOADC_RST_DLY_160T = 13,
    HAL_AIOADC_RST_DLY_200T = 14,
    HAL_AIOADC_RST_DLY_256T = 15,
    HAL_AIOADC_RST_DLY_MAX = 16,
} hal_aioadc_rst_dly_t;

typedef enum
{
    HAL_AIOADC_AVG_SHIFT_2048 = 0,
    HAL_AIOADC_AVG_SHIFT_1024 = 1,
    HAL_AIOADC_AVG_SHIFT_512 = 2,
    HAL_AIOADC_AVG_SHIFT_256 = 3,
    HAL_AIOADC_AVG_SHIFT_128 = 4,
    HAL_AIOADC_AVG_SHIFT_64 = 5,
    HAL_AIOADC_AVG_SHIFT_32 = 6,
    HAL_AIOADC_AVG_SHIFT_16 = 7,
    HAL_AIOADC_AVG_SHIFT_8 = 8,
    HAL_AIOADC_AVG_SHIFT_4 = 9,
    HAL_AIOADC_AVG_SHIFT_2 = 10,
    HAL_AIOADC_AVG_SHIFT_1 = 11,
    HAL_AIOADC_AVG_SHIFT_1_2 = 12,
    HAL_AIOADC_AVG_SHIFT_1_4 = 13,
    HAL_AIOADC_AVG_SHIFT_1_8 = 14,
    HAL_AIOADC_AVG_SHIFT_1_16 = 15,
    HAL_AIOADC_AVG_SHIFT_MAX = 16,
} hal_aioadc_avg_shift_sel_t;

typedef enum
{
    HAL_AIOADC_AVG_1T = 0,
    HAL_AIOADC_AVG_2T = 1,
    HAL_AIOADC_AVG_4T = 2,
    HAL_AIOADC_AVG_8T = 3,
    HAL_AIOADC_AVG_16T = 4,
    HAL_AIOADC_AVG_32T = 5,
    HAL_AIOADC_AVG_64T = 6,
    HAL_AIOADC_AVG_128T = 7,
    HAL_AIOADC_AVG_256T = 8,
    HAL_AIOADC_AVG_512T = 9,
    HAL_AIOADC_AVG_1024T = 10,
    HAL_AIOADC_AVG_2048T = 11,
    HAL_AIOADC_AVG_4096T = 12,
    HAL_AIOADC_AVG_8192T = 13,
    HAL_AIOADC_AVG_16384T = 14,
    HAL_AIOADC_AVG_32768T = 15,
    HAL_AIOADC_AVG_MAX = 16,
} hal_aioadc_avg_sel_t;

typedef struct
{
  hal_aioadc_avg_sel_t adc_avg_sel;
  hal_aioadc_avg_shift_sel_t adc_avg_shift_sel;
  hal_aioadc_rst_dly_t adc_rst_dly;
  hal_aioadc_sw_ch_dly_t adc_sw_ch_dly;
} hal_aioadc_config_t;

typedef enum {
    HAL_AIOADC_STATUS_ERROR_PARAMETER = -2,      /**< Invalid user input parameter. */
    HAL_AIOADC_STATUS_ERROR = -1,                /**< AIOADC driver detected a common error. */
    HAL_AIOADC_STATUS_OK = 0                     /**< AIOADC function executed successfully. */
} hal_aioadc_status_t;

typedef void (*hal_aioadc_callback_t)(int16_t adc_data,int16_t v_bat);
uint32_t aioadc_get_ch_data_reg_mask(hal_aioadc_ch_en_t aioadc_ch);

hal_aioadc_status_t hal_aioadc_init(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_mode_sel_t aioadc_mode,hal_aioadc_config_t *aioadc_cfg);
void hal_aioadc_deinit(void);

int16_t hal_aioadc_read_data_polling(hal_aioadc_ch_en_t aioadc_ch);
hal_aioadc_status_t hal_aioadc_read_data_by_irq(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_callback_t callback);

int16_t hal_aioadc_get_voltage(hal_aioadc_ch_en_t aioadc_ch,hal_aioadc_mode_sel_t aioadc_mode);
hal_aioadc_status_t hal_aioadc_get_tempsensor(hal_aioadc_ch_en_t aioadc_ch,int16_t *output_adc_data,int16_t *output_opt_offset,int16_t *output_temp_data);
#endif/*__HAL_AIOADC_H__*/
