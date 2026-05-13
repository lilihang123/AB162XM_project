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

#ifndef __FG_NAFG_H__
#define __FG_NAFG_H__

#include <stdint.h>
#include "fg_sim.h"
#ifndef FG_SIM
#include "bm_cust.h"
#endif

#ifdef AIR_SDK_ZCV_TABLE_ENABLE
#include "fg_nafg_sdk.h"
#else
#include "fg_nafg_cust.h"
#endif

#ifndef PACKED
#define PACKED  __attribute__((packed))
#endif


typedef struct {
    uint32_t time_dur;                            //nafg times duration
    uint16_t idx;                                 //nafg calculation times
    uint16_t sd_bat;                              //shutdown battery voltage
    int16_t  temp;                                //the current temperature
    int16_t  temp_old;                            //the previous temperature
    int16_t  chg_sta;                             //record the current charger state to check charger complete(end of charge, EOC)
    int16_t  chg_sta_old;                         //record the previous charger state to check charger state change
    int16_t  is_charging;                         //is charging state flag, 0:w/o charging, 1: w/i charging
    int16_t  charging_sta;                        //record charging state to check state change
    uint16_t zcv_qmax;                            //estimated ZCV table battery capacity
    uint16_t qmax;                                //estimated current battery capacity
    uint16_t init_qmax;                           //estimated initial battery capacity
    uint16_t pnzcv;                               //power on zcv(ocv when system boot)
    uint16_t vbat;                                //current battery voltage
    double   ocv;                                 //current ocv
    double   vm_total_car;                        //the cumulative charge or discharge capacity(mAh) with V mode
    double   cm_total_car;                        //the cumulative charge or discharge capacity(mAh) with C mode
    double   soc;                                 //the status of battery capacity(SOC)

    //aging
    double   aging_vector;                        //if real_qmax < zcv_qmax, aging_vector = real_qmax/zcv_qmax, read from nvkey

    //get_cv_point
    uint16_t vbat_arr_idx;                        //the current index of vbat array : 0 ~ (FG_VBAT_ARR_SIZE - 1)
    uint16_t vbat_arr_num;                        //the number of the vbat array
    uint16_t vbat_arr[FG_VBAT_ARR_SIZE];          //the vbat array to get average battery voltage
    uint16_t cv_thrd;                             //cc to cv battery voltage threshold
    uint16_t cv_rsv_thrd;                         //vbat < cv_thrd means chg state change to cc state from cv state
    uint16_t cv_cnt;                              //cc to cv count, count++ when vbat_avg >= cv_thrd
    uint16_t cv_cnt_thrd;                         //cv_cnt >= cv_cnt_thrd means chg state change to cv state

    //cv process
    uint8_t  cv_flag;                             //check charger state by SW, 0:cc, 1:cv(charger current start to decrease)
    uint8_t  pt_i_comp_flag;                      //current compensation when CV state (current too small for 0C), 1:enable, 0:disable
    uint8_t  v_tune_flag;                         //v_tune calibration for IR drop, 0:not yet, 1:done
    uint8_t  i_tune_flag;                         //i_tune calibration for PT current too small, 0:not yet, 1:done
    double   i_max_thrd;                          //maximum charger current in CC state
    double   pt_dlt_vbat;                         //(ocv - vbat) when CC to CV
    double   pt_r;                                //resistance from ZCV table when CC to CV
    double   pt_ocv;                              //current OCV when CC to CV
    double   pt_vbat;                             //current vbat when CC to CV
    double   v_tune;                              //v_tune for IR drop during charge state
    double   i_tune;                              //i_tune for charger current too small with 0C
    double   i_coef_conv;                         //i_coef_conv is the coefficient that fg current convert to real cueernt
} nafg_stru;

typedef struct {
    uint16_t sm_arr_idx;                          //the current index of smooth array : 0 ~ (sm_arr_act_num - 1)
    uint32_t sm_arr_num;                          //the current number that smooth array used
    double   sm_soc;                              //smooth soc
    double   sm_soc_old;                          //record the previous SOC value that avoid soc value will backdate
    double   sm_soc_arr[FG_SM_MAX_ARR_SIZE];      //the SOC smooth array
} sm_stru;

typedef struct {
    uint16_t pre_ocv;
    uint8_t  pre_soc;
    uint8_t  rsv1;
    uint32_t aging_coef_conv;
    uint32_t chg_total_car;
    uint32_t bat_cycle;
} PACKED nv_data_stru;

typedef struct {
    uint32_t rsv1;
    uint8_t  rsv2;
    uint8_t  rsv3;
    uint8_t  dlt_temp_thrd;
    uint8_t  sm_act_arr_size;
    uint8_t  cv_cnt_thrd;
    uint8_t  i_coef_conv;

    uint32_t rsv4;
    uint32_t rsv5;
    uint32_t rsv6;

    uint16_t car_tune_in;
    uint16_t car_tune_out;
    uint16_t cv_offset;
    uint16_t cv_rev_offset;

    uint8_t  soc_gap_thrd;
    uint8_t  soc_comp_en;
    uint8_t  soc_100_comp_start;
    uint8_t  soc_100_comp_end;
    uint8_t  soc_0_comp_start;
    uint8_t  soc_0_comp_end;

    uint32_t rsv[8];
} PACKED nv_cfg_stru;

extern nafg_stru nafg;
extern nv_data_stru fg_nv;
extern nv_cfg_stru fg_cfg;
extern sm_stru fg_sm;

void fg_set_nvkey(void);
void fg_proc(uint16_t vbat);
void fg_init(void);
void fg_sim(void);
int32_t fg_get_temp(void);
uint32_t fg_get_soc(void);
uint32_t fg_get_bat_cycle(void);
void fg_clean_bat_cycle(void);
#endif //__FG_NAFG_H__

