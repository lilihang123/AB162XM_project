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

#include <zephyr/sys/printk.h>

#include "airoha_clock_control.h"

#ifdef CONFIG_AIR_DVFS
#include "hal_dvfs_internal.h"
#endif

#define DT_DRV_COMPAT airoha_air_clock_controller

#define air_clk_log_info(msg, cnt, ...)    printk("[AIR_CLK] "msg"\r\n", ##__VA_ARGS__)

/* clock_control_subsys_t sys: hal_clock_cg_id * */
static int airoha_clock_control_on(const struct device *dev, clock_control_subsys_t sys)
{
    ARG_UNUSED(dev);
#if 0
    hal_clock_cg_id *p_cg_id = (hal_clock_cg_id *)sys;
    air_clk_log_info("airoha_clock_control_on(%d)", 1, *p_cg_id);
    hal_clock_status_t status = hal_clock_enable(*p_cg_id);
#else
    hal_clock_status_t status = hal_clock_enable(*(hal_clock_cg_id *)sys);
#endif
    return status==HAL_CLOCK_STATUS_OK? 0:-EINVAL;
}

/* clock_control_subsys_t sys: hal_clock_cg_id * */
static int airoha_clock_control_off(const struct device *dev, clock_control_subsys_t sys)
{
    ARG_UNUSED(dev);
#if 0
    hal_clock_cg_id *p_cg_id = (hal_clock_cg_id *)sys;
    air_clk_log_info("airoha_clock_control_off(%d)", 1, *p_cg_id);
    hal_clock_status_t status = hal_clock_disable(*p_cg_id);
#else
    hal_clock_status_t status = hal_clock_disable(*(hal_clock_cg_id *)sys);
#endif
    return status==HAL_CLOCK_STATUS_OK? 0:-EINVAL;
}

/* clock_control_subsys_t sys: hal_clock_cg_id * */
static enum clock_control_status airoha_clock_control_get_status(const struct device *dev, clock_control_subsys_t sys)
{
    ARG_UNUSED(dev);
#if 0
    hal_clock_cg_id *p_cg_id = (hal_clock_cg_id *)sys;
    air_clk_log_info("airoha_clock_control_get_status(%d)", 1, *p_cg_id);
    return hal_clock_is_enabled(*p_cg_id)? CLOCK_CONTROL_STATUS_ON:CLOCK_CONTROL_STATUS_OFF;
#else
    return hal_clock_is_enabled(*(hal_clock_cg_id *)sys)? CLOCK_CONTROL_STATUS_ON:CLOCK_CONTROL_STATUS_OFF;
#endif
}

#if defined(CONFIG_MCUBOOT) || defined(AIR_DOWNLOAD_AGENT) || defined(CONFIG_AIR_FPGA_ENV_ENABLE)
static int airoha_clock_control_get_rate(const struct device *dev, clock_control_subsys_t sys, uint32_t *rate)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(sys);
    ARG_UNUSED(rate);
    return -EOPNOTSUPP;
}

static int airoha_clock_control_set_rate(const struct device *dev, clock_control_subsys_t sys, clock_control_subsys_rate_t rate)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(sys);
    ARG_UNUSED(rate);
    return -EOPNOTSUPP;
}

static int airoha_clock_control_configure(const struct device *dev, clock_control_subsys_t sys, void *data)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(data);
    return -EOPNOTSUPP;
}

#else /* !CONFIG_MCUBOOT && !AIR_DOWNLOAD_AGENT && !CONFIG_AIR_FPGA_ENV_ENABLE */
/* clock_control_subsys_t sys: air_clk_get_rate_t * */
static int airoha_clock_control_get_rate(const struct device *dev, clock_control_subsys_t sys, uint32_t *rate)
{
    ARG_UNUSED(dev);

    air_clk_get_rate_t *pt_clk_get_rate = (air_clk_get_rate_t *)sys;
    ref_clock_t   _ref_clock = 0;
    hal_src_clock _src_clock = 0;
    uint32_t      _ref_clk_hz = 0, _winset = 0, _fqmtr_data = 0;

    switch(pt_clk_get_rate->operation) {
        case AIR_CLK_GET_RATE__MCU_KHZ_FROM_MUX:
            *rate = hal_clock_get_curr_cpu_freq_hz();
            air_clk_log_info("airoha_clock_control_get_rate(MCU_KHZ_FROM_MUX) %d", 1, *rate);
            break;
        case AIR_CLK_GET_RATE__MUX_IDX:
            *rate = hal_clock_mux_cur_sel(pt_clk_get_rate->t_para.mux_idx.mux_id);
            air_clk_log_info("airoha_clock_control_get_rate(MUX_IDX) %d", 1, *rate);
            break;
        case AIR_CLK_GET_RATE__FQMTR_HZ_REF_XO:
            _ref_clock = XO_CK;
            _src_clock = pt_clk_get_rate->t_para.fqmtr_hz_ref_xo.src_clk;
            _ref_clk_hz = DCXO_HZ;
            _winset = hal_clock_fqmtr_winset_estimate(_ref_clk_hz, pt_clk_get_rate->t_para.fqmtr_hz_ref_xo.src_clk_hz);
            break;
        case AIR_CLK_GET_RATE__FQMTR_HZ_REF_XO_WINSET:
            _ref_clock = XO_CK;
            _src_clock = pt_clk_get_rate->t_para.fqmtr_hz_ref_xo_windset.src_clk;
            _ref_clk_hz = DCXO_HZ;
            _winset = pt_clk_get_rate->t_para.fqmtr_hz_ref_xo_windset.winset;
            break;
        case AIR_CLK_GET_RATE__FQMTR_HZ:
            _ref_clock = pt_clk_get_rate->t_para.fqmtr_hz.ref_clk;
            _src_clock = pt_clk_get_rate->t_para.fqmtr_hz.src_clk;
            _ref_clk_hz = pt_clk_get_rate->t_para.fqmtr_hz.ref_clk_hz;
            _winset = hal_clock_fqmtr_winset_estimate(_ref_clk_hz, pt_clk_get_rate->t_para.fqmtr_hz.src_clk_hz);
            break;
        case AIR_CLK_GET_RATE__FQMTR_HZ_WINSET:
            _ref_clock = pt_clk_get_rate->t_para.fqmtr_hz_winset.ref_clk;
            _src_clock = pt_clk_get_rate->t_para.fqmtr_hz_winset.src_clk;
            _ref_clk_hz = pt_clk_get_rate->t_para.fqmtr_hz_winset.ref_clk_hz;
            _winset = pt_clk_get_rate->t_para.fqmtr_hz_winset.winset;
            break;

#ifdef CONFIG_AIR_DVFS
        case AIR_CLK_GET_RATE__DVFS_VCORE:
            *rate = hal_dvfs_get_cur_vcore();
            air_clk_log_info("airoha_clock_control_get_rate(DVFS_VCORE) %d", 1, *rate);
            break;
        case AIR_CLK_GET_RATE__DVFS_FRQ:
            *rate = hal_dvfs_get_cur_frq();
            air_clk_log_info("airoha_clock_control_get_rate(DVFS_FRQ) %d", 1, *rate);
            break;
#endif
        default:
            return -EINVAL;
    }

    if((pt_clk_get_rate->operation >= AIR_CLK_GET_RATE__FQMTR_HZ_REF_XO) && (pt_clk_get_rate->operation <= AIR_CLK_GET_RATE__FQMTR_HZ_WINSET)) {
        _fqmtr_data = hal_clock_freq_meter_data(_ref_clock, _src_clock, _winset);
        if(_fqmtr_data) {
            *rate = hal_clock_get_freq_from_fqmtr_data(_ref_clk_hz, _fqmtr_data, _winset);
        }
        else {
            *rate = 0;
        }
        air_clk_log_info("airoha_clock_control_get_rate(FQMTR) ref(%d) %d, src(%d) %d, winset %d, data %d", 6, _ref_clock, _ref_clk_hz, _src_clock, *rate, _winset, _fqmtr_data);
    }

    return 0;
}

/* clock_control_subsys_t sys: hal_dvfs_lock_parameter_t * */
/* clock_control_subsys_rate_t rate: dvfs_frequency_t * */
static int airoha_clock_control_set_rate(const struct device *dev, clock_control_subsys_t sys, clock_control_subsys_rate_t rate)
{
    ARG_UNUSED(dev);

#ifdef CONFIG_AIR_DVFS
    air_clk_log_info("airoha_clock_control_set_rate(lock_ctrl %d, opp %d)", 2, *(hal_dvfs_lock_parameter_t *)sys, *(dvfs_frequency_t *)rate);
    hal_dvfs_status_t status = hal_dvfs_lock_control(*(dvfs_frequency_t *)rate, *(hal_dvfs_lock_parameter_t *)sys);
    return status==HAL_DVFS_STATUS_OK? 0:-EINVAL;
#else
    ARG_UNUSED(sys);
    ARG_UNUSED(rate);
    return -ENOSYS;
#endif
}

/* clock_control_subsys_t sys: air_clk_cfg_t * */
static int airoha_clock_control_configure(const struct device *dev, clock_control_subsys_t sys, void *data)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(data);

    air_clk_cfg_t *pt_clk_cfg = (air_clk_cfg_t *)sys;

    switch(pt_clk_cfg->operation) {
        case AIR_CLK_CFG__SET_MUX_IDX:
            air_clk_log_info("airoha_clock_control_configure(SET_MUX_IDX) %d %d", 2, pt_clk_cfg->t_para.set_mux_idx.mux_id, pt_clk_cfg->t_para.set_mux_idx.mux_sel);
            if(hal_clock_mux_sel(pt_clk_cfg->t_para.set_mux_idx.mux_id, pt_clk_cfg->t_para.set_mux_idx.mux_sel) != HAL_CLOCK_STATUS_OK) {
                return -EINVAL;
            }
            break;

#ifdef CONFIG_MULTITHREADING
        case AIR_CLK_CFG__SET_LPOSC_KHZ:
            air_clk_log_info("airoha_clock_control_configure(SET_LPOSC_KHZ) %d", 1, pt_clk_cfg->t_para.set_lposc_khz.khz);
            if(hal_clock_set_lposc_khz(pt_clk_cfg->t_para.set_lposc_khz.khz) != HAL_CLOCK_STATUS_OK) {
                return -EOPNOTSUPP;
            }
            break;
#endif

        case AIR_CLK_CFG__DCM_CTRL:
            air_clk_log_info("airoha_clock_control_configure(DCM_CTRL) %d", 1, pt_clk_cfg->t_para.dcm_ctrl.val);
            hal_clock_dcm_ctrl_all(pt_clk_cfg->t_para.dcm_ctrl.val);
            break;

#ifdef CONFIG_AIR_DCXO
        case AIR_CLK_CFG__DCXO_32K_CTRL:
            air_clk_log_info("airoha_clock_control_configure(DCXO_32K_CTRL) %d", 1, pt_clk_cfg->t_para.dcxo_32k_ctrl.val);
            hal_dcxo_32k_ctrl(pt_clk_cfg->t_para.dcxo_32k_ctrl.val);
            break;
        case AIR_CLK_CFG__DCXO_PM_CTRL:
            air_clk_log_info("airoha_clock_control_configure(DCXO_PM_CTRL) %d", 1, pt_clk_cfg->t_para.dcxo_pm_ctrl.mode);
            hal_dcxo_set_pwr_mode(pt_clk_cfg->t_para.dcxo_pm_ctrl.mode);
            break;
#endif
        default:
            return -EINVAL;
    }

    return 0;
}
#endif /* !CONFIG_MCUBOOT && !AIR_DOWNLOAD_AGENT && !CONFIG_AIR_FPGA_ENV_ENABLE */

static struct clock_control_driver_api airoha_clock_control_api = {
    .on = airoha_clock_control_on,
    .off = airoha_clock_control_off,
    .get_status = airoha_clock_control_get_status,
    .get_rate = airoha_clock_control_get_rate,
    .set_rate = airoha_clock_control_set_rate,
    .configure = airoha_clock_control_configure,
};

/*
void airoha_clock_control_dump_rg_module_info(void)
{
    if(DT_NODE_HAS_PROP(AIROHA_CLOCK_NODE_ID, module_str)) {
        air_clk_log_info("Ttl RG modules: %d", 1, DT_NUM_REGS(AIROHA_CLOCK_NODE_ID));
        air_clk_log_info("%s 0x%08X", 2, DT_PROP_BY_IDX(AIROHA_CLOCK_NODE_ID, module_str, 0), DT_REG_ADDR_BY_IDX(AIROHA_CLOCK_NODE_ID, 0));
        air_clk_log_info("%s 0x%08X", 2, DT_PROP_BY_IDX(AIROHA_CLOCK_NODE_ID, module_str, 1), DT_REG_ADDR_BY_IDX(AIROHA_CLOCK_NODE_ID, 1));
        air_clk_log_info("%s 0x%08X", 2, DT_PROP_BY_IDX(AIROHA_CLOCK_NODE_ID, module_str, 2), DT_REG_ADDR_BY_IDX(AIROHA_CLOCK_NODE_ID, 2));
        air_clk_log_info("%s 0x%08X", 2, DT_PROP_BY_IDX(AIROHA_CLOCK_NODE_ID, module_str, 3), DT_REG_ADDR_BY_IDX(AIROHA_CLOCK_NODE_ID, 3));
        air_clk_log_info("%s 0x%08X", 2, DT_PROP_BY_IDX(AIROHA_CLOCK_NODE_ID, module_str, 4), DT_REG_ADDR_BY_IDX(AIROHA_CLOCK_NODE_ID, 4));
        air_clk_log_info("%s 0x%08X", 2, DT_PROP_BY_IDX(AIROHA_CLOCK_NODE_ID, module_str, 5), DT_REG_ADDR_BY_IDX(AIROHA_CLOCK_NODE_ID, 5));
        air_clk_log_info("%s 0x%08X", 2, DT_PROP_BY_IDX(AIROHA_CLOCK_NODE_ID, module_str, 6), DT_REG_ADDR_BY_IDX(AIROHA_CLOCK_NODE_ID, 6));
    }
}
*/

static int airoha_clock_control_init(const struct device *dev)
{
    ARG_UNUSED(dev);

#ifdef CONFIG_MCUBOOT
    air_clk_log_info("airoha_clock_control_init, PRE_KERNEL_1, INIT_PRIORITY %d", 1, CONFIG_CLOCK_INIT_PRIORITY);
#endif

    //airoha_clock_control_dump_rg_module_info();

    hal_clk_cfg_t tCfg;
    memset(&tCfg, 0, sizeof(tCfg));

#ifdef CONFIG_AIR_CLK_CTRL_LPOSC_KHZ
    tCfg.lposc_khz = CONFIG_AIR_CLK_CTRL_LPOSC_KHZ;
#endif

#ifdef CONFIG_AIR_CLK_CTRL_LPOSC_HS_DIV
    tCfg.lposc_hs_div = CONFIG_AIR_CLK_CTRL_LPOSC_HS_DIV;
#else
    tCfg.lposc_hs_div = 2;  // fixed
#endif

#ifdef CONFIG_AIR_CLK_CTRL_LPOSC_LS_DIV
    tCfg.lposc_ls_div = CONFIG_AIR_CLK_CTRL_LPOSC_LS_DIV;
#else
    tCfg.lposc_ls_div = 6;  // fixed
#endif

#ifdef CONFIG_MCUBOOT
#ifdef CONFIG_AIR_CLK_CTRL_LPOSC_HOPPING_ENABLE
    tCfg.lposc_hopping_enable = TRUE;
#endif

#ifdef CONFIG_AIR_CLK_CTRL_LPOSC_HOPPING_RANGE_X10000
    tCfg.lposc_hopping_range_x10000 = CONFIG_AIR_CLK_CTRL_LPOSC_HOPPING_RANGE_X10000;
#endif

#ifdef CONFIG_AIR_CLK_CTRL_LPOSC_HOPPING_TIMER_US_ONCE
    tCfg.lposc_hopping_timer_us_once = CONFIG_AIR_CLK_CTRL_LPOSC_HOPPING_TIMER_US_ONCE;
#endif

#ifdef CONFIG_AIR_CLK_CTRL_LPOSC_HOPPING_JUMP_CODE_ONCE
    tCfg.lposc_hopping_jump_code_once = CONFIG_AIR_CLK_CTRL_LPOSC_HOPPING_JUMP_CODE_ONCE;
#endif
#endif /* CONFIG_MCUBOOT */

#ifdef CONFIG_AIR_CLK_CTRL_LPOSC_RE_K_PERIODICALLY_ENABLE
    tCfg.lposc_re_k_periodically_enable = TRUE;
#endif

#ifdef CONFIG_AIR_CLK_CTRL_LPOSC_RE_K_PERIOD_MS
    tCfg.lposc_re_k_period_ms = CONFIG_AIR_CLK_CTRL_LPOSC_RE_K_PERIOD_MS;
#endif

#ifdef CONFIG_AIR_CLK_CTRL_DCM_ENABLE
    tCfg.dcm_enable = TRUE;
#endif

#ifdef CONFIG_AIR_DVFS_SYS_CFG
    if(!strcmp(CONFIG_AIR_DVFS_SYS_CFG, "BASE_MID")) {
        tCfg.dvfs_sys_cfg = AIR_DVFS_SYS_CFG_BASE_MID;
    }
    else if(!strcmp(CONFIG_AIR_DVFS_SYS_CFG, "FIX_HIGH")) {
        tCfg.dvfs_sys_cfg = AIR_DVFS_SYS_CFG_FIX_HIGH;
    }
    else {
        tCfg.dvfs_sys_cfg = AIR_DVFS_SYS_CFG_NORMAL;
    }
#endif

#ifdef CONFIG_MCUBOOT
    air_clk_log_info("osc_hopping: enable=%d, range_x10000=%d, timer_us_once=%d, jump_code_once=%d", 4,
                      tCfg.lposc_hopping_enable, tCfg.lposc_hopping_range_x10000, tCfg.lposc_hopping_timer_us_once, tCfg.lposc_hopping_jump_code_once);
#endif

#if 0
    air_clk_log_info("osc_khz=%d, osc_hs_div=%d, osc_ls_div=%d, osc_hopping_enable=%d, osc_hopping_range_x10000=%d", 5,
                      tCfg.lposc_khz, tCfg.lposc_hs_div, tCfg.lposc_ls_div, tCfg.lposc_hopping_enable, tCfg.lposc_hopping_range_x10000);
    air_clk_log_info("osc_hopping_timer_us_once=%d, osc_hopping_jump_code_once=%d, osc_re_k_periodically_enable=%d, osc_re_k_period_ms=%d, dcm_enable=%d, dvfs_sys_cfg=%d", 6,
                      tCfg.lposc_hopping_timer_us_once, tCfg.lposc_hopping_jump_code_once, tCfg.lposc_re_k_periodically_enable, tCfg.lposc_re_k_period_ms, tCfg.dcm_enable, tCfg.dvfs_sys_cfg);
#endif

    hal_clock_init_cfg(&tCfg);

    return 0;
}

DEVICE_DT_DEFINE(
            AIROHA_CLOCK_NODE_ID,
            &airoha_clock_control_init,
            NULL,
            NULL,
            NULL,
            CONFIG_CLOCK_INIT_LEVEL,
            CONFIG_CLOCK_INIT_PRIORITY,
            &airoha_clock_control_api);

