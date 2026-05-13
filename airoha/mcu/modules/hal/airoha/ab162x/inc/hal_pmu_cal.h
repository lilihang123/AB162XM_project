/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
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
#ifndef __HAL_PMU_CAL_LP_H__
#define __HAL_PMU_CAL_LP_H__
#ifdef HAL_PMU_MODULE_ENABLED

#define OTP_OK                           (1)
#define NO_OTP                           (0xFF)
#define OTP_FT_ID_ADDR                   (0)
#define OTP_DDIE_VER_ADDR                (1)
#define OTP_BASE_ADDR                    (256)
#define OTP_BUCK_RF_BIAS_ADDR            (OTP_BASE_ADDR + 0)
#define OTP_BUCK_RF_VOUT_ADDR            (OTP_BASE_ADDR + 2)
#define OTP_BUCK_RF_TIMER_ADDR           (OTP_BASE_ADDR + 7)
#define OTP_BUCK_RF_OC_ADDR              (OTP_BASE_ADDR + 12)
#define OTP_BUCK_RF_ZC_ADDR              (OTP_BASE_ADDR + 14)
#define OTP_LPO32_FREQK_ADDR             (OTP_BASE_ADDR + 17)
#define OTP_CAPLESS_LDO_VOUT_ADDR        (OTP_BASE_ADDR + 20)
#define OTP_CAPLESS_LDO_VOUT_RSV_ADDR    (OTP_BASE_ADDR + 22)
#define OTP_OVP_VIO_ADDR                 (OTP_BASE_ADDR + 24)
#define OTP_OVP_NOCLDO_ADDR              (OTP_BASE_ADDR + 28)
#define OTP_VCORE_LDO_ADDR               (OTP_BASE_ADDR + 31)
#define OTP_VCORE_LDO_DUMMY_LOAD_ADDR    (OTP_BASE_ADDR + 33)
#define OTP_LPBG_TCTRIM_ADDR             (OTP_BASE_ADDR + 36)
#define OTP_LPBG_IBTRIM_ADDR             (OTP_BASE_ADDR + 38)
#define OTP_LPBG_VREF_ADDR               (OTP_BASE_ADDR + 40)
#define OTP_HPBG_TCTRIM_ADDR             (OTP_BASE_ADDR + 45)
#define OTP_HPBG_VREF_ADDR               (OTP_BASE_ADDR + 47)
#define OTP_VIO18_VOUT_ADDR              (OTP_BASE_ADDR + 49)
#define OTP_VIO18_RET_VOUT_ADDR          (OTP_BASE_ADDR + 52)
#define OTP_VIO18_OC_ADDR                (OTP_BASE_ADDR + 55)
#define OTP_BUCK_RF_ULP_TRIM_ADDR        (OTP_BASE_ADDR + 57)


#ifndef PACKED
#define PACKED  __attribute__((packed))
#endif


typedef enum {
    FT_ID_AB1620D         = 1,
    FT_ID_AB1620DM        = 2,
    FT_ID_AB1623          = 3,
    FT_ID_AB1623M         = 4,
    FT_ID_AB1625M         = 5,
} pmu_ft_id_t;

typedef enum {
    FT_DDIE_VER_E1        = 1,
    FT_DDIE_VER_E2        = 2,
    FT_DDIE_VER_E3        = 3,
    FT_DDIE_VER_E4        = 4,
    FT_DDIE_VER_E5        = 5,
} pmu_ddie_ver_t;

/****************************** OTP stru ******************************/
typedef struct {
    uint8_t kflag;
    uint8_t VRF_IBIAS_TRIM;
} PACKED buck_rf_bias_t;

typedef struct {
    uint8_t kflag;
    uint8_t VRF_VOTRIM_NM;
    uint8_t VRF_VOTRIM_LPM;
    uint8_t VRF_VOTRIM_ULPM;
    uint8_t VRF_IODUM_TRIM;
} PACKED buck_rf_vout_t;

typedef struct {
    uint8_t kflag;
    uint8_t VRF_COT_TRIM;
    uint8_t VRF_PREON;
    uint8_t VRF_IQDN;
    uint8_t VRF_HIZ_TRIM;
} PACKED buck_rf_timer_t;

typedef struct {
    uint8_t kflag;
    uint8_t VRF_OCOS_TRIM;
} PACKED buck_rf_oc_t;

typedef struct {
    uint8_t kflag;
    uint8_t VRF_ZCOS_TRIM;
    uint8_t VRF_CCM_ZCOS_TRIM;
} PACKED buck_rf_zc_t;

typedef struct {
    uint8_t kflag;
    uint8_t Ftune;
    uint8_t Ctune;
} PACKED lpo32_freqk_t;

typedef struct {
    uint8_t kflag;
    uint8_t VOTRIM;
} PACKED capless_ldo_vout_t;

typedef struct {
    uint8_t kflag;
    uint8_t NOCLDO_RSV;
} PACKED capless_ldo_vout_rsv_t;

typedef struct {
    uint8_t kflag;
    uint8_t OVP_VIO_VTH;
    uint8_t OVP_VIO_IBIAS;
    uint8_t OVP_VIO_VTH_LP;
} PACKED ovp_vio_t;

typedef struct {
    uint8_t kflag;
    uint8_t OVP_NOCLDO_VTH;
    uint8_t OVP_NOCLDO_IBIAS;
} PACKED ovp_nocldo_t;

typedef struct {
    uint8_t kflag;
    uint8_t VCORE_VOTRIM;
} PACKED vcore_ldo_t;

typedef struct {
    uint8_t kflag;
    uint16_t VCORE_DL;
} PACKED vcore_ldo_dummy_load_t;

typedef struct {
    uint8_t kflag;
    uint8_t LPBG_TCTRIM;
} PACKED lpbg_tctrim_t;

typedef struct {
    uint8_t kflag;
    uint8_t LPBG_IBTRIM;
} PACKED lpbg_ibtrim_t;

typedef struct {
    uint8_t kflag;
    uint8_t LPBG_VREF1P0TRIM;
    uint8_t LPBG_VREF0P5TRIM;
    uint8_t LPBG_VREF0P5_UVLO_TRIM1;
    uint8_t LPBG_VREF0P5_UVLO_TRIM2;
} PACKED lpbg_vref_t;

typedef struct {
    uint8_t kflag;
    uint8_t HPBG_TCTRIM;
} PACKED hpbg_tctrim_t;

typedef struct {
    uint8_t kflag;
    uint8_t HPBG_VREF0P5TRIM;
} PACKED hpbg_vref_t;

typedef struct {
    uint8_t kflag;
    uint8_t NM_VOTRIM_1p8;
    uint8_t NM_VOTRIM_1p5;
} PACKED vio18_vout_t;

typedef struct {
    uint8_t kflag;
    uint8_t RET_VOTRIM_1p8;
    uint8_t RET_VOTRIM_1p5;
} PACKED vio18_ret_vout_t;

typedef struct {
    uint8_t kflag;
    uint8_t OCTRIM;
} PACKED vio18_oc_t;

typedef struct {
    uint8_t kflag;
    uint8_t BUCK_VRF_R1;
    uint8_t BUCK_VRF_R2;
    uint8_t BUCK_VRF_COMP_MIS;
    uint8_t BUCK_VRF_VOCAL_LP_IQDN_TRIM;
    uint8_t BUCK_VRF_LP_TRIM_STEP;
} PACKED buck_rf_ulp_trim_t;

/* extern API & veriable */
extern uint8_t otp_ft_id;
extern uint8_t otp_ddie_ver;

pmu_status_t pmu_get_otp(uint16_t addr, uint8_t *ptr, uint32_t size);
void pmu_get_otp_ft_id();
void pmu_get_ddie_ver();
void pmu_buck_rf_ulp_trim(uint16_t vrf_extslp2, int16_t rg_vrf_extslp2);
void pmu_cal_init(void);

#endif  /* HAL_PMU_MODULE_ENABLED */
#endif  /* __HAL_PMU_CAL_LP_H__ */
