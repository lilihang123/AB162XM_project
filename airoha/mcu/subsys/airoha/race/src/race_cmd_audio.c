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
#ifdef AIR_BTD_IC_PREMIUM_G1
#include "race_cmd_feature.h"
#include "race_cmd.h"
#include "race_xport.h"
#include "race_util.h"

#ifdef RACE_AUDIO_RACE_CMD_ENABLE
#include "race_cmd_audio.h"
#include "hal_spm.h"

#ifdef AIR_AUDIO_SLT_TEST
#include "audio_slt_test.h"
#endif


// #define RACE_AUDIO_DESENSE_TEST

uint32_t u4SamplingRateConvert[17] = {0/*8K*/, 1/*11.25K*/, 2/*12K*/, 4/*16K*/, 5/*22.05K*/, 6/*24K*/, 8/*32K*/, 9/*44.1K*/, 10/*48K*/, 11/*88.2K*/, 12/*96K*/, 13/*176K*/, 14/*192K*/, 15/*260K*/, 10/*48KHD*/, 3/*384K*/, 7/*130K*/};
uint32_t u4SamplingRateHz[17] = {8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000, 88200, 96000, 176400, 192000, 260000, 48000, 384000, 130000};

const UL_VOICE_MODE_T eSampleRate2VoiceMode[] = {
    UL_VOICE_MODE_16k,   //AFE_8000HZ
    UL_VOICE_MODE_16k,   //AFE_11025HZ
    UL_VOICE_MODE_16k,   //AFE_12000HZ
    UL_VOICE_MODE_16k,  //AFE_16000HZ
    UL_VOICE_MODE_24k,  //AFE_22050HZ
    UL_VOICE_MODE_24k,  //AFE_24000HZ
    UL_VOICE_MODE_32k,  //AFE_32000HZ
    UL_VOICE_MODE_32k,  //AFE_44100HZ
    UL_VOICE_MODE_48k,  //AFE_48000HZ
    UL_VOICE_MODE_48k,  //AFE_88200HZ
    UL_VOICE_MODE_48k,  //AFE_96000HZ
    UL_VOICE_MODE_48k,  //AFE_176400HZ
    UL_VOICE_MODE_48k,  //AFE_192000HZ
    UL_VOICE_MODE_48k,  //AFE_260000HZ
    UL_VOICE_MODE_48k,  //AFE_48000HZHD
    UL_VOICE_MODE_48k,  //AFE_384000HZ
    UL_VOICE_MODE_48k,  //AFE_130000HZ
};

const int32_t IntrConOutReg[OUT_MAX] = {AFE_CONN0, AFE_CONN1, AFE_CONN2, AFE_CONN3, AFE_CONN4,
                                      AFE_CONN5, AFE_CONN6, AFE_CONN7, AFE_CONN8, AFE_CONN9,
                                      AFE_CONN10, AFE_CONN11, AFE_CONN12, AFE_CONN13, AFE_CONN14,
                                      AFE_CONN15, AFE_CONN16, AFE_CONN17, AFE_CONN18, AFE_CONN19,
                                      AFE_CONN20, AFE_CONN21, AFE_CONN22, AFE_CONN23, AFE_CONN24,
                                      AFE_CONN25, AFE_CONN26, AFE_CONN27, AFE_CONN28, AFE_CONN29,
                                      AFE_CONN30, AFE_CONN31, AFE_CONN32, AFE_CONN33, AFE_CONN34,
                                      AFE_CONN35, AFE_CONN36, AFE_CONN37, AFE_CONN38, AFE_CONN39,
                                      AFE_CONN40, AFE_CONN41, AFE_CONN42, AFE_CONN43
                                     };//KEN add
// AFE_CONNXX_1 is for IYY connect to OXX, 32 <= YY
//KH mark

const int32_t IntrConOutReg_1[OUT_MAX] = {AFE_CONN0_1, AFE_CONN1_1, AFE_CONN2_1, AFE_CONN3_1, AFE_CONN4_1,
                                        AFE_CONN5_1, AFE_CONN6_1, AFE_CONN7_1, AFE_CONN8_1, AFE_CONN9_1,
                                        AFE_CONN10_1, AFE_CONN11_1, AFE_CONN12_1, AFE_CONN13_1, AFE_CONN14_1,
                                        AFE_CONN15_1, AFE_CONN16_1, AFE_CONN17_1, AFE_CONN18_1, AFE_CONN19_1,
                                        AFE_CONN20_1, AFE_CONN21_1, AFE_CONN22_1, AFE_CONN23_1, AFE_CONN24_1,
                                        AFE_CONN25_1, AFE_CONN26_1, AFE_CONN27_1, AFE_CONN28_1, AFE_CONN29_1,
                                        AFE_CONN30_1, AFE_CONN31_1, AFE_CONN32_1, AFE_CONN33_1, AFE_CONN34_1,
                                        AFE_CONN35_1, AFE_CONN36_1, AFE_CONN37_1, AFE_CONN38_1, AFE_CONN39_1,
                                        AFE_CONN40_1, AFE_CONN41_1, AFE_CONN42_1, AFE_CONN43_1
                                       };//KEN add

void hal_aduio_set_register_32bit(uint32_t addr, uint32_t val, uint32_t msk)
{
    AFE_WRITE((addr), ((AFE_READ(addr) & (~(msk))) | ((val) & (msk))));
    //printf("32bitaddr:0x%x,val:0x%x\r\n",addr,AFE_READ(addr));
}

void hal_aduio_set_register_16bit(uint32_t addr, uint32_t val, uint32_t msk)
{
    ANA_WRITE((addr), ((ANA_READ(addr) & (~(msk))) | ((val) & (msk))));
    //printf("16bitaddr:0x%x,val:0x%x\r\n",addr,ANA_READ(addr));
}

/******************************************************************************
* Function      : vSetRegBit
* Description   : Set one bit
* Parameter     :
* Return        : None
******************************************************************************/
//void vRegSetBit(int32_t addr, int32_t bit)
void vRegSetBit(int32_t addr, int32_t bit)
{
    uint32_t u4CurrValue, u4Mask;
    u4Mask = 1 << bit;
    u4CurrValue = AFE_READ(addr);
    AFE_WRITE(addr, (u4CurrValue | u4Mask));
    return;
}


/******************************************************************************
* Function      : vResetRegBit
* Description   : Reset one bit
* Parameter     :
* Return        : None
******************************************************************************/
//void vRegResetBit(int32_t addr, int32_t bit)
void vRegResetBit(int32_t addr, int32_t bit)
{
    uint32_t u4CurrValue, u4Mask;
    u4Mask = 1 << bit;
    u4CurrValue = AFE_READ(addr);
    AFE_WRITE(addr, (u4CurrValue & (~u4Mask)));
    return;
}

bool bConnect_bitWidth(ITRCON_OUT_T rOut, HD_AUDIO_MEM_TYPE bitWidth)
{
    int32_t address = 0;
    int32_t sbit;

    if (rOut >= OUT_MAX) {
        LOG_INF("[%s]rOut %d[max %d] \r\n", __FUNCTION__, rOut, OUT_MAX);
        return FALSE;
    }

    if (rOut<32) {
        sbit = rOut;
        address = AFE_CONN_24BIT;
    } else {
        sbit = rOut - I32;
        address = AFE_CONN_24BIT_1;
    }
    if (address == 0) {
        LOG_INF("[%s] set rOut:%d width, register address:0x%x error!!!!! \r\n", __FUNCTION__, rOut, address);
        assert(0);
    }
    if (bitWidth == HD_AUDIO_WLEN_16_BIT){
        vRegResetBit(address, sbit);
    } else {
        vRegSetBit(address, sbit);
    }
    LOG_INF("[%s] set out[%d] width[%d] Set bit[%d], [0x%x] = %x \r\n", __FUNCTION__, rOut, bitWidth, sbit, address, AFE_READ(address));

    return TRUE;
}


bool bConnect(ITRCON_IN_T rIn, ITRCON_OUT_T rOut, bool bRShift)
{
    int32_t address;
    int32_t sbit;
    // INT32 rbit;

    if (rIn >= IN_MAX || rOut >= OUT_MAX) {
        LOG_INF("rIn %d [max %d], rOut %d[max %d] \r\n", rIn, IN_MAX, rOut, OUT_MAX);
        return FALSE;
    }

    //assert(rIn<32); //KH:add
    if (rIn<32) {
        sbit = rIn;
        LOG_INF("IntrConOutReg 0x%x \r\n", (unsigned int)IntrConOutReg);
        address = IntrConOutReg[rOut];
    } else {
        sbit = rIn - I32;
        LOG_INF("IntrConOutReg_1 0x%x \r\n", (unsigned int)IntrConOutReg_1);
        address = IntrConOutReg_1[rOut];
    }
    if (address == 0) {
        LOG_INF("rIn %d [max %d], rOut %d[max %d] \r\n", rIn, IN_MAX, rOut, OUT_MAX);
        return FALSE;
    }
    vRegSetBit(address, sbit);
    LOG_INF("bConnect in[%d], out[%d] Set bit[%d], [0x%x] = %x \r\n", rIn, rOut, sbit, address, AFE_READ(address));

    //Set R bit
    if (bRShift) {
        if (rOut < 32) {
            vRegSetBit(AFE_CONN_RS, rOut);
        } else {
            vRegSetBit(AFE_CONN_RS_1, rOut - 32);
//GZ            assert(0); //KH
        }
    }

    return TRUE;
}




void vEnableADDAInterface(bool eControl)
{
    AFE_SET_REG(AFE_ADDA_UL_DL_CON0, eControl << 0, 1<<0); //{0,1}
}

void vEnableUpLinkSrc(UPLINK_PATH_T UplinkPath, bool eControl)
{
    if (UP_LINK_1 == UplinkPath) {
        AFE_SET_REG(AFE_ADDA_UL_SRC_CON1, (eControl ? 3 : 0) << 0, 3 << 0);
    }
}

void set_dmic_clk(UPLINK_PATH_T UplinkPath, Dmic_Input_Mode_T Dmic_InMode)
{
    if (UplinkPath == UP_LINK_1) {
        /* ADDA 1 */
        AFE_SET_REG(AFE_ADDA_UL_SRC_CON0, Dmic_InMode << 14, 3 << 14);
        AFE_SET_REG(AFE_ADDA_UL_SRC_CON1, Dmic_InMode << 18, 3 << 18);
    }
}

void vSetupUplinkParameters(SAMPLINGRATE_T eUplinkSamplingRate, UPLINK_PATH_T UplinkPath)
{
    if ( UP_LINK_1 == UplinkPath){
        AFE_SET_REG(AFE_ADDA_UL_SRC_CON1, eSampleRate2VoiceMode[eUplinkSamplingRate] << 8, 3 << 8);
    }
}

#if 1
void hal_audio_afe_set_enable(bool enable)
{
    if (enable) {
            //Default clock setting
            // AFE_WRITE(AUDIO_TOP_CON0, AUDIO_TOP_CON0_PDN_ALL_MASK);
            // AFE_WRITE(AUDIO_TOP_CON1, AUDIO_TOP_CON1_PDN_ALL_MASK);
            //Enable clock
            // hal_audio_clock_enable_afe(enable);
            AFE_SET_REG(AUDIO_TOP_CON0, 0 << 2, 1<<2);

            AFE_SET_REG(AFE_DAC_CON0, 1 << 0, 1<<0);
    } else {
            AFE_SET_REG(AFE_DAC_CON0, 0 << 0, 1<<0);
            //Disable clock
            // hal_audio_clock_enable_afe(enable);
            AFE_SET_REG(AUDIO_TOP_CON0, 1 << 2, 1<<2);

    }
    LOG_INF("DSP - Hal Audio AFE control:%d", enable);
}

bool hal_audio_ul_set_dmic_clock(uint32_t clock_rate)
{
    // uint32_t reg = afe_samplerate_get_ul_device_register(device_agent);
    uint32_t reg = AFE_ADDA_UL_SRC_CON0;

    AFE_SET_REG(reg, (clock_rate << 14), 3<<14);
    AFE_SET_REG(AFE_ADDA_UL_SRC_CON1, clock_rate << 18, 3 << 18);

    LOG_INF("[DMIC Driver] DMIC clock rate: %d\r\n", clock_rate);
    return false;
}

bool hal_audio_ul_set_dmic_phase(uint32_t phase_ch1, uint32_t phase_ch2)
{
    // uint32_t reg = afe_samplerate_get_ul_device_register(device_agent);
    uint32_t reg = AFE_ADDA_UL_SRC_CON0;

    AFE_SET_REG(reg, (phase_ch1 << 27) | (phase_ch2 << 24), (7 << 27) | (7 << 24));
    return false;
}

bool hal_audio_ul_set_dmic_selection(void)
{
    // Dmic0 clk & data setting
    AFE_SET_REG(TOP_DMIC_CK_SEL, 0 << 0, 3 << 0); //00: audio_dmic0_ck
    return false;
}

bool hal_audio_ul_set_dmic_enable(bool enable)
{
    // uint32_t reg = afe_samplerate_get_ul_device_register(device_agent);
    uint32_t reg = AFE_ADDA_UL_SRC_CON0;

    AFE_SET_REG(reg, enable << 1, 1<<1);
    return false;
}

/*              UL sample rate              */
static afe_samplerate_adda_ul_t afe_samplerate_adda_ul_convert_samplerate_to_register_value(uint32_t samplerate)
{
    switch (samplerate) {
        case 16000:
            return AFE_ADDA_UL_SAMPLERATE_16K;
        case 24000:
            return AFE_ADDA_UL_SAMPLERATE_24K;
        case 32000:
            return AFE_ADDA_UL_SAMPLERATE_32K;
        case 48000:
            return AFE_ADDA_UL_SAMPLERATE_48K;
        default:
            return AFE_ADDA_UL_SAMPLERATE_16K;
    }
}

void afe_samplerate_set_ul_samplerate(uint32_t samplerate)
{
    uint32_t register_value = 0;
    // uint32_t reg = afe_samplerate_get_ul_register(agent);
    uint32_t reg = AFE_ADDA_UL_SRC_CON1;
    register_value = afe_samplerate_adda_ul_convert_samplerate_to_register_value(samplerate);
    AFE_SET_REG(reg, register_value << 8, 3 << 8);
}

bool hal_audio_adda_set_ul_clock(bool enable)
{
    //Workaround:Prevent state machine is unfinished
    hal_gpt_delay_us(5);

    AFE_SET_REG(AUDIO_TOP_CON0, 0 << 24, 1 << 24);
    //Workaround:Prevent state machine is unfinished
    hal_gpt_delay_us(5);

    return false;
}

bool hal_audio_ul_reset_fifo(bool enable)
{
    AFE_SET_REG(AFE_ADDA_UL_DL_CON0, (enable << 29), (1 << 29));
    return false;
}

void hal_audio_adda_set_enable(bool enable)
{
    // hal_audio_adda_set_enable_register(enable);
    AFE_SET_REG(AFE_ADDA_UL_DL_CON0, enable << 0, 1 << 0);

}

bool hal_audio_ul_set_enable(bool enable)
{
    // uint32_t reg = afe_samplerate_get_ul_device_register(device_agent);
    //Workaround : Toggle enable to reset filter
    AFE_SET_REG(AFE_ADDA_UL_SRC_CON1, (enable ? 3 : 0) << 0, 3 << 0);
    return false;
}

bool hal_audio_adda_set_ul_amic(bool enable)
{
    AFE_SET_REG(AFE_ADDA_UL_SRC_CON1, (enable << 21) | (enable << 12), (1 << 21) | (1 << 12));
    return false;
}

bool hal_audio_adda_set_ul_dmic(bool enable)
{
    AFE_SET_REG(AFE_ADDA_UL_SRC_CON1, (0 << 21) | (enable << 16), (1 << 21) | (1 << 16));
    return false;
}

bool hal_audio_adda_set_ul(uint32_t samplerate, bool control)
{
    LOG_INF("[hal_audio_adda_set_ul], on/off %d, samplerate %d", control, samplerate);
    if (control) {
        afe_samplerate_set_ul_samplerate(samplerate);

        hal_audio_adda_set_ul_clock(true);

        hal_audio_ul_reset_fifo(false);

        // hal_audio_ul_set_iir(device_agent, iir_filter, true);
        // hal_audio_ul_set_hires(device_agent, true);
        hal_audio_adda_set_enable(true);

        hal_audio_ul_set_enable(true);
    } else {
        hal_audio_ul_set_enable(false);

        hal_audio_adda_set_enable(false);
        // hal_audio_ul_set_hires(device_agent, false);
        // hal_audio_ul_set_iir(device_agent, iir_filter, false);

        hal_audio_ul_reset_fifo(true);

        hal_audio_adda_set_ul_clock(false);
    }
    LOG_INF("[hal_audio_adda_set_ul] set done, AFE_ADDA_UL_SRC_CON0(0x%x): 0x%x, AFE_ADDA_UL_SRC_CON1(0x%x): 0x%x, AFE_ADDA_UL_DL_CON0(0x%x): 0x%x",
             AFE_ADDA_UL_SRC_CON0, AFE_READ(AFE_ADDA_UL_SRC_CON0),
             AFE_ADDA_UL_SRC_CON1, AFE_READ(AFE_ADDA_UL_SRC_CON1),
             AFE_ADDA_UL_DL_CON0, AFE_READ(AFE_ADDA_UL_DL_CON0));

    return false;
}

bool hal_audio_device_set_digital_mic(uint32_t samplerate, uint32_t dmic_clock_rate, bool control)
{
    LOG_INF("hal_audio_device_set_digital_mic, samplerate: %d, dmic_clock_rate:%d, control:%d", samplerate, dmic_clock_rate, control);
#if 1
    if (control) {
        // if (!handle->with_external_bias) {
            // hal_audio_adda_set_bias_enable( handle->bias_select, (hal_audio_bias_voltage_t *)&(handle->bias_voltage), handle->with_bias_lowpower, true, control);
            // hal_audio_adda_set_bias_enable(handle->bias_select, (hal_audio_bias_voltage_t *)&(handle->bias_voltage), handle->with_bias_lowpower,handle->bias1_2_with_LDO0, control);
            // hal_audio_ul_set_dmic_bias(device_agent, true);
        // }

        // hal_audio_ana_set_dmic_enable(handle->dmic_selection, true);
        hal_audio_ul_set_dmic_clock(dmic_clock_rate);
        hal_audio_ul_set_dmic_phase(3, 7);
        hal_audio_ul_set_dmic_selection();
        hal_audio_ul_set_dmic_enable(true);

        hal_audio_adda_set_ul_dmic(true);
        hal_audio_adda_set_ul(samplerate, true);
    } else {
        hal_audio_adda_set_ul(samplerate, false);

        hal_audio_ul_set_dmic_enable(false);
        // hal_audio_ana_set_dmic_enable(handle->dmic_selection, false);

        // if (!handle->with_external_bias) {
            // hal_audio_adda_set_bias_enable( handle->bias_select, (hal_audio_bias_voltage_t *)&(handle->bias_voltage), handle->with_bias_lowpower, true, control);
            // hal_audio_adda_set_bias_enable(handle->bias_select, (hal_audio_bias_voltage_t *)&(handle->bias_voltage), handle->with_bias_lowpower,handle->bias1_2_with_LDO0, control);
            // hal_audio_ul_set_dmic_bias(false);
        // }
    }
#else

    AFE_SET_REG(AFE_ADDA_UL_DL_CON0, 0 << 29, 1 << 29); // 1 -> debug mode, 0 -> normal mode

    // Open Dmic
    vRegSetBit(AFE_ADDA_UL_SRC_CON0, 1); //MC: select Dmic/Amic

    AFE_SET_REG(AFE_ADDA_UL_SRC_CON0, 1 << 23, 1 << 23); // 1 wire or 2 wire //MC : not defined in CODA

    AFE_SET_REG(AFE_ADDA_UL_SRC_CON0, (nWire == 1 ? 0 : 1) << 23, 1 << 23); // 1 wire or 2 wire //MC : not defined in CODA

    AFE_SET_REG(AFE_ADDA_UL_SRC_CON1, (0  << 21) | (1 << 16), (1 << 21) | (1 << 16)); // UL1 Dmic, dmic enable

    // Dmic0 clk & data setting
    AFE_SET_REG(TOP_DMIC_CK_SEL, 0 << 0, 3 << 0); //00: audio_dmic0_ck

    uint32_t temp_reg = 0;

    temp_reg = AFE_READ(AFE_ADDA_UL_SRC_CON0);
    temp_reg &= ~(0x3F000000); //MC: bit29-27=> ul_dmic_phase_sel_ch1,   bit26-24: =>ul_dmic_phase_sel_ch2
    temp_reg |= ((3 << 27) | (7 << 24));
    WriteREG(AFE_ADDA_UL_SRC_CON0, temp_reg);
    LOG_INF("\r\n\r\nch1 phase = %d, ch2 phase = %d\r\n\r\n", phase_table[nPhase].ch1_phase, phase_table[nPhase].ch2_phase);

    /* ADDA 1 */
    set_dmic_clk(UP_LINK_1, dmic_clock_rate);

    // vSetupUplinkParameters(samplerate, UP_LINK_1);
    afe_samplerate_set_ul_samplerate(samplerate);

    vEnableUpLinkSrc(UP_LINK_1, true);
    vEnableADDAInterface(true);
    vAfeTurnOn();

#endif
    return false;
}

//AMIC
bool hal_audio_device_analog_set_input(bool control)
{
    if (control) {
        //Here Set Analog - Top
        AFE_WRITE(0x42080048, 0x00004401);
        AFE_WRITE(0x4208004C, 0x0000070F);
        AFE_WRITE(0x42080050, 0x0000050F);
        AFE_WRITE(0x4208005C, 0x00000041);
        AFE_WRITE(0x4208007C, 0x00000011);
        AFE_WRITE(0x4208000C, 0x00000010);
        hal_gpt_delay_us(100);//delay 100us

        //Here Set Analog - Capless LDO
        AFE_WRITE(0x42080024, 0x00000001);
        AFE_WRITE(0x42080024, 0x00000001);
        AFE_WRITE(0x42080024, 0x00000005);
        AFE_WRITE(0x42080024, 0x00000005);
        AFE_WRITE(0x42080024, 0x00000005);

        //Analog_ADC01_BIAS_AMIC
        AFE_WRITE(0x42080008, 0x00000001);
        AFE_WRITE(0x42080008, 0x00000001);
        AFE_WRITE(0x42080008, 0x00000005);
        AFE_WRITE(0x4208000C, 0x00000010);
        AFE_WRITE(0x4208000C, 0x00000010);
        AFE_WRITE(0x4208000C, 0x00000010);
        AFE_WRITE(0x42080008, 0x00000005);
        AFE_WRITE(0x42080008, 0x00000005);
        AFE_WRITE(0x42080008, 0x00000005);

        //Here Set Analog - PGA0
        AFE_WRITE(0x42080004, 0x00000000);
        AFE_WRITE(0x42080004, 0x00000002);
        AFE_WRITE(0x42080004, 0x00000002);
        AFE_WRITE(0x42080004, 0x00000002);
        AFE_WRITE(0x42080004, 0x00000042);
        AFE_WRITE(0x4208003C, 0x00000000);
        AFE_WRITE(0x4208003C, 0x00000005);
        AFE_WRITE(0x42080040, 0x00000008);
        AFE_WRITE(0x42080004, 0x00000043);
        AFE_WRITE(0x4208000C, 0x00001810);
        AFE_WRITE(0x42080010, 0x0000F200);
        AFE_WRITE(0x4208000C, 0x00001850);
        hal_gpt_delay_us(1000);//delay 1000us
        AFE_WRITE(0x4208000C, 0x00001810);

        //Here Set Analog - ADC0
        AFE_WRITE(0x4208000C, 0x00001810);
        AFE_WRITE(0x4208000C, 0x00001810);
        AFE_WRITE(0x4208001C, 0x00000000);
        AFE_WRITE(0x4208000C, 0x00001810);
        AFE_WRITE(0x42080018, 0x00000015);
        AFE_WRITE(0x4208001C, 0x00000002);
        AFE_WRITE(0x42080004, 0x00001043);
        AFE_WRITE(0x42080004, 0x00005043);
    } else {
        //Here Set Analog - ADC01
        AFE_WRITE(0x42080004, 0x00001043);
        AFE_WRITE(0x42080004, 0x00000043);
        AFE_WRITE(0x4208000C, 0x00000010);
        AFE_WRITE(0x4208000C, 0x00000010);
        AFE_WRITE(0x4208000C, 0x00000010);
        AFE_WRITE(0x42080018, 0x00000015);
        AFE_WRITE(0x4208001C, 0x00000010);
        AFE_WRITE(0x4208001C, 0x00000001);

        //Here Set Analog - PGA01
        AFE_WRITE(0x42080004, 0x00000042);
        AFE_WRITE(0x42080004, 0x00000002);
        AFE_WRITE(0x42080004, 0x00000000);

        //Here Set Analog - Capless LDO
        AFE_WRITE(0x42080024, 0x00000004);
        AFE_WRITE(0x42080024, 0x00000000);

        //Here Set Analog - Top
        AFE_WRITE(0x4208000C, 0x00000000);
    }
    return false;
}



bool hal_audio_device_set_analog_mic(uint32_t samplerate, bool control)
{
    LOG_INF("hal_audio_device_set_analog_mic, samplerate: %d, control:%d", samplerate, control);

    AFE_WRITE(0x420D0038, 0x00000060);//set AIO for AMIC,GPIO28/29

    if (control) {
        // if (!handle->with_external_bias) {
            // hal_audio_adda_set_bias_enable( handle->bias_select, (hal_audio_bias_voltage_t *)&(handle->bias_voltage), handle->with_bias_lowpower, true, control);
            // hal_audio_adda_set_bias_enable( handle->bias_select, (hal_audio_bias_voltage_t *)&(handle->bias_voltage), handle->with_bias_lowpower, handle->bias1_2_with_LDO0, control);
        // }
        hal_audio_device_analog_set_input(control);
        hal_audio_adda_set_ul_amic(control);

        hal_audio_adda_set_ul(samplerate, control);
    } else {
        hal_audio_adda_set_ul(samplerate, control);
        hal_audio_device_analog_set_input(control);
        // if (!handle->with_external_bias) {
            // hal_audio_adda_set_bias_enable( handle->bias_select, (hal_audio_bias_voltage_t *)&(handle->bias_voltage), handle->with_bias_lowpower, true, control);
            // hal_audio_adda_set_bias_enable(handle->bias_select, (hal_audio_bias_voltage_t *)&(handle->bias_voltage), handle->with_bias_lowpower,handle->bias1_2_with_LDO0, control);
        // }
    }
    return false;
}

#endif

//=================================I2S config============================================//
void I2SMasterConfig(I2S_CONFIG_T* i2s_config, bool control)
{
    uint32_t eSamplingRateConvert = u4SamplingRateConvert[i2s_config->sampling_rate];
    uint32_t reg_con = AFE_I2S0_CON;
    uint32_t reg_top_con = AFE_I2S_TOP_CON;

    switch(i2s_config->i2s_device) {
        case I2S_0://I2S0
        default:
            reg_con = AFE_I2S0_CON;
            LOG_INF("[%s]I2S master:%d config, reg_RG: 0x%x \r\n", __FUNCTION__, i2s_config->i2s_device, reg_con);
            break;
    }

    if (control) {

        //word length
        AFE_SET_REG(reg_con, i2s_config->word_length << 1, 1 << 1);
        //format
        switch(i2s_config->i2s_format) {
            case I2S_EIAJ:
            case I2S_I2S:
                AFE_SET_REG(reg_con, i2s_config->i2s_format << 3, 1 << 3); //0: EIAJ   1: I2S
                break;

            case I2S_LJ:
                AFE_SET_REG(reg_con, I2S_I2S << 3, 1 << 3); //0: EIAJ   1: I2S
                //inverse WS
                AFE_SET_REG(reg_con, 1 << 5, 1 << 5); //0: LJ   1: RJ
                if (i2s_config->word_length == I2S_32BIT) {
                    AFE_SET_REG(reg_con, 8 << 16, 0x1F << 16); //out shift
                    AFE_SET_REG(reg_con, 8 << 24, 0x1F << 24); //in shift
                } else {
                    AFE_SET_REG(reg_con, 0 << 16, 0x1F << 16); //out shift
                    AFE_SET_REG(reg_con, 0 << 24, 0x1F << 24); //in shift
                }
                //I2S out LJ mode
                AFE_SET_REG(reg_con, 0 << 22, 1 << 22); //0: LJ   1: RJ
                //I2S in LJ mode
                AFE_SET_REG(reg_con, 0 << 30, 1 << 30); //0: LJ   1: RJ
                break;

            case I2S_RJ:
                AFE_SET_REG(reg_con, I2S_I2S << 3, 1 << 3); //0: EIAJ   1: I2S
                //inverse WS
                AFE_SET_REG(reg_con, 1 << 5, 1 << 5); //0: LJ   1: RJ
                AFE_SET_REG(reg_con, 8 << 16, 0x1F << 16); //out shift
                AFE_SET_REG(reg_con, 8 << 24, 0x1F << 24); //in shift
                //I2S out LJ mode
                AFE_SET_REG(reg_con, 1 << 22, 1 << 22); //0: LJ   1: RJ
                //I2S in lsb align
                AFE_SET_REG(reg_con, 1 << 29, 1 << 29);
                break;
            default:
                LOG_INF("[%s]I2S master format:%d error!!! \r\n", __FUNCTION__, i2s_config->i2s_format);
                assert(0);
                break;

        }

        switch(i2s_config->sampling_rate) {
            case AFE_16000HZ:
            case AFE_24000HZ:
            case AFE_32000HZ:
            case AFE_48000HZ:
                //sample rate
                AFE_SET_REG(reg_con, eSamplingRateConvert << 8, 0xf << 8);
                break;
            default:
                LOG_INF("[%s]I2S master sampling rate:%d not support!!! \r\n", __FUNCTION__, u4SamplingRateHz[i2s_config->sampling_rate]);
                assert(0);
                break;
        }
        //swap
        AFE_SET_REG(reg_top_con, (i2s_config->is_internal_loopback <<0), 1 << 0);

        //swap
        AFE_SET_REG(reg_con, (i2s_config->is_tx_swap << 13) | (i2s_config->is_rx_swap << 14), 1 << 13 | 1 << 14);
    }
    //enable I2S
    AFE_SET_REG(AUDIO_TOP_CON1, (control ? 0 : 1) << 1, 1 << 1);
    AFE_SET_REG(reg_con, control << 0, 1 << 0); //0: diable, 1: enable

    LOG_INF("[%s]I2S master:%d control:%d \r\n", __FUNCTION__, i2s_config->i2s_device,  control);
    LOG_INF("[%s]format:%d, word_length:%d, sample rate:%d \r\n", __FUNCTION__, i2s_config->i2s_format, i2s_config->word_length, u4SamplingRateHz[i2s_config->sampling_rate]);
    LOG_INF("[%s]reg_con(addr = 0x%x): 0x%x, reg_top_con(addr = 0x%x): 0x%x \r\n", __FUNCTION__, reg_con, AFE_READ(reg_con), reg_top_con, AFE_READ(reg_top_con));
}
//==============================================================================================================//
bool loopback_running = false;
uint8_t loopback_in_device = 0xff;
uint8_t loopback_out_device = 0xff;
uint8_t loopback_samplerate = 0xff;

#ifdef RACE_AUDIO_DESENSE_TEST

#define DUMP_BUFFER_SIZE  1*1024
#define AUDIO_LOOPBAKC_GPT_TIMER_TIMEOUT  500 //ms

uint8_t audio_dump_buffer[DUMP_BUFFER_SIZE] = {0};
uint32_t audio_loopback_gpt_timer = 0;
uint32_t gpt_timer_timeout_cnt = 0;
uint32_t vul_base_addr = 0, vul_end_addr = 0;

void CB_AUDIO_LOOPBACK_GPT_CALLBACK(void *user_data)
{
    UNUSED(user_data);
    // LOG_ERR("loopback, CB_AUDIO_LOOPBACK_GPT_CALLBACK\r\n");
    if (HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(audio_loopback_gpt_timer, AUDIO_LOOPBAKC_GPT_TIMER_TIMEOUT, CB_AUDIO_LOOPBACK_GPT_CALLBACK, NULL)) {
        /* err step 3 */
        LOG_ERR("loopback open error! GPT timer start fail!!!\r\n");
    }
    if (loopback_in_device == 3) {
        LOG_INF("loopback timer, DMIC in, AFE_ADDA_DEBUG_MON0: 0x%x", AFE_READ(AFE_ADDA_DEBUG_MON0));
    } else if (loopback_in_device == 1) {
        LOG_INF("loopback timer, I2S master in, AFE_I2S_BCOUNT_MON: 0x%x", AFE_READ(AFE_I2S_BCOUNT_MON));
    }
    if (loopback_out_device == 2) {//for desense
        uint32_t *addr = (uint32_t *)vul_base_addr;
        for (uint32_t i = 0; i < 5; i++) {
            LOG_INF("loopback timer, audio_dump_buffer[%d~%d]: 0x%08x, 0x%08x, 0x%08x, 0x%08x", i*16, (i+1) * 16 -1, *addr, *(addr + 1), *(addr + 2), *(addr + 3));
            addr += 4;
        }
    }
    gpt_timer_timeout_cnt++;
    if (gpt_timer_timeout_cnt == 10) {
        // assert(0);
    }
}

#endif

bool race_audio_loopback_open(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;

        uint8_t sample_rate; //3: 16k, 5:24k, 6:32k, 8:48k
        uint8_t in_device;  // 0:sinegen 1:I2S master, 2:amic, 3:dicm
        uint8_t interface;  // 1:(only)
        uint8_t mic_mode;  //adc_mode or dmic pin
        uint8_t mic_performance; //amic: performance level;  dicm: clk
        uint8_t out_device;  //1:I2S master(only)
    } PACKED CMD;

    // typedef struct {
    //     uint8_t status;
    // } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    // RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
    //                                   RACE_TYPE_RESPONSE,
    //                                   RACE_CRYSTAL_TRIM_TRIGGER,
    //                                   sizeof(RSP),
    //                                   channel_id);

    if (loopback_running) {
        LOG_ERR("loopback open error! loopback is running");
        return true;
    }
    LOG_INF("loopback open, sample_rate:%d, in_device: %d, interface:%d, mic_mode: %d, mic_performance:%d, out_device:%d",
                    pCmd->sample_rate,
                    pCmd->in_device,
                    pCmd->interface,
                    pCmd->mic_mode,
                    pCmd->mic_performance,
                    pCmd->out_device);

    if (pCmd->in_device > 3) {
        LOG_ERR("loopback open error! in_device: %d not support!!! \r\n", pCmd->in_device);
        return true;
    }

    if (pCmd->out_device >= 3) {
        LOG_ERR("loopback open error! out_device: %d not support!!! \r\n", pCmd->out_device);
        return true;
    }

    if ((pCmd->sample_rate != AFE_16000HZ)
         && (pCmd->sample_rate != AFE_24000HZ)
         && (pCmd->sample_rate != AFE_32000HZ)
         && (pCmd->sample_rate != AFE_48000HZ)) {
        LOG_ERR("loopback open error! sample_rate[index = %d]: %d not support!!! \r\n", pCmd->sample_rate, u4SamplingRateHz[pCmd->sample_rate]);
        return true;
    }
    spm_control_mtcmos(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_ENABLE);

    // LOG_INF("loopback open, INFRA_CFG_AUDIO_SYS_TOP_PORT_RDY: 0x%x \r\n",*INFRA_CFG_AUDIO_SYS_TOP_PORT_RDY);
    // if( (*INFRA_CFG_AUDIO_SYS_TOP_PORT_RDY) == 1){
    //     *INFRA_CFG_AUDIO_SYS_TOP_PORT_EN = 0;
    //     while (*INFRA_CFG_AUDIO_SYS_TOP_PORT_RDY != 0x0);
    // }

    hal_clock_enable(HAL_CLOCK_CG_AUD_INTBUS);
    hal_clock_enable(HAL_CLOCK_CG_AUD_ENGINE);

    hal_audio_afe_set_enable(true);

    /**I2S config**/
    I2S_CONFIG_T i2s_master_config;

    memset(&i2s_master_config, 0, sizeof(I2S_CONFIG_T));
    if (pCmd->out_device == 1) {
        //I2S out
        switch(pCmd->interface) {
            case 1:
                i2s_master_config.i2s_device = I2S_0;
                break;
            default:
                LOG_ERR("loopback open error! interface: 0x%x  not support!!!\r\n", pCmd->interface);
                return true;
        }
    } else if (pCmd->out_device == 2) { //for desense
        if (pCmd->in_device == 1) {
            i2s_master_config.i2s_device = I2S_0;
        }
#ifdef RACE_AUDIO_DESENSE_TEST

        memset((void *)audio_dump_buffer, 0, DUMP_BUFFER_SIZE);

        //memory agent
        // VarWriteBits(gAfeInfo.reg_AFE_DAC_CON1, u4SamplingRateConvert[pCmd->sample_rate], b_AFE_DAC_CON1.mVUL_MODE);
        AFE_SET_REG(AFE_DAC_CON1, u4SamplingRateConvert[pCmd->sample_rate] << 16, 0x0F << 16);

        // VarWriteBits(gAfeInfo.reg_AFE_DAC_CON1, memif_config->eChannelConfig, b_AFE_DAC_CON1.mVUL_DATA);
        AFE_SET_REG(AFE_DAC_CON1, 0 << 27, 1 << 27);

        // if (memif_config->eChannelConfig == AFE_MONO) {
        //     // Set MONO select
        //     VarWriteBits(gAfeInfo.reg_AFE_DAC_CON1, memif_config->eMonoSelect, b_AFE_DAC_CON1.mVUL_R_MONO);
        // }

        // MEMIF setting
        // vRegWriteBits(AFE_MEMIF_HDALIGN, isNormal, b_AFE_MEMIF_HDALIGN.mVUL_NORMAL_MODE);
        // vRegWriteBits(AFE_MEMIF_HDALIGN, isAlign, b_AFE_MEMIF_HDALIGN.mVUL_HD_ALIGN);
        AFE_SET_REG(AFE_MEMIF_HDALIGN, (1 << 21) | (0 << 5), (1 << 21) | (1 << 5));

        // vRegWriteBits(AFE_MEMIF_HD_MODE, isHD, b_AFE_MEMIF_HD_MODE.mVUL_HD);
        AFE_SET_REG(AFE_MEMIF_HD_MODE, (0 << 10), (1 << 10)); //16bit

        // vRegWriteBits(AFE_MEMIF_MSB, isSigned, b_AFE_MEMIF_MSB.mVUL_AXI_WR_SIGN);
        // vRegWriteBits(AFE_MEMIF_CONN, isTinyConn, VUL_USE_TINY_POS, MEMIF_USE_TINY_LEN);

        // Buffer setting
        // WriteREG(AFE_VUL_BASE, memif_config->rBufferSetting.u4AFE_MEMIF_BUF_BASE);
        // WriteREG(AFE_VUL_END, memif_config->rBufferSetting.u4AFE_MEMIF_BUF_END);
        vul_base_addr = (uint32_t)&audio_dump_buffer[0];
        vul_base_addr = (vul_base_addr + 0xf) & 0xfffffff0; //16byte align
        vul_end_addr = (uint32_t)&audio_dump_buffer[DUMP_BUFFER_SIZE - 1];
        vul_end_addr = (vul_end_addr - 0xf) & 0xfffffff0; //16byte align
        AFE_WRITE(AFE_VUL_BASE, vul_base_addr);
        AFE_WRITE(AFE_VUL_END, vul_end_addr);

        LOG_INF("loopback open, VUL base_addr: 0x%x,  end_addr: 0x%x; &audio_dump_buffer[0]:0x%x, &audio_dump_buffer[DUMP_BUFFER_SIZE - 1]: 0x%x\r\n",
                vul_base_addr, vul_end_addr, (uint32_t)&audio_dump_buffer[0], (uint32_t)&audio_dump_buffer[DUMP_BUFFER_SIZE - 1]);

        // connection setting
        // vRegWriteBits(AFE_CONN_24BIT, (memif_config->eHdAudioMemType > 0) ? 0x1 : 0x0, b_AFE_CONN_24BIT.mO16_24BIT);
        // vRegWriteBits(AFE_CONN_24BIT, (memif_config->eHdAudioMemType > 0) ? 0x1 : 0x0, b_AFE_CONN_24BIT.mO17_24BIT);
        AFE_SET_REG(AFE_CONN_24BIT, (1 << 16) | (1 << 17), (1 << 16) | (1 << 17));

        // IRQ
        // vRegWriteBits(AFE_IRQ_MCU_CON1, eSamplingRateConvert, b_AFE_IRQ_MCU_CON1.mIRQ4_MCU_MODE);
        AFE_SET_REG(AFE_IRQ_MCU_CON1, u4SamplingRateConvert[pCmd->sample_rate] << 16, (0xf << 16));

        // vRegSetBit(AFE_IRQ_MCU_CON0, b_AFE_IRQ_MCU_CON0.mIRQ4_MCU_ON.pos);
        AFE_SET_REG(AFE_IRQ_MCU_CON0, 1 << 4, (0x1 << 4));

        AFE_SET_REG(AFE_DAC_CON0, 1 << 3, (0x1 << 3));// turn on VUL
#else
        LOG_ERR("loopback open error! desense mode not enable!!!\r\n");
#endif

    }
    i2s_master_config.i2s_format = I2S_I2S;
    i2s_master_config.word_length = I2S_32BIT;
    i2s_master_config.is_rx_swap = false;
    i2s_master_config.is_tx_swap = false;
    i2s_master_config.is_internal_loopback = false;
    i2s_master_config.sampling_rate = pCmd->sample_rate;

    uint32_t RegSamplingRate = 0;
    RegSamplingRate = u4SamplingRateConvert[i2s_master_config.sampling_rate];

    loopback_in_device = pCmd->in_device;
    loopback_out_device = pCmd->out_device;
    loopback_samplerate = pCmd->sample_rate;

    // hal_audio_afe_set_enable(true);

    if (pCmd->in_device == 0) {//sinegen
        //enable sinegen to I2S out
        LOG_INF("loopback open, sinegen to I2S master:%d output. \r\n", __FUNCTION__, i2s_master_config.i2s_device);
        //set I2S intercon bit width
        bConnect_bitWidth(O00, HD_AUDIO_WLEN_24_BIT);
        bConnect_bitWidth(O01, HD_AUDIO_WLEN_24_BIT);

        //sinegen to I2S master0 out
        AFE_WRITE(AFE_SGEN_CON2, 0x20);
        AFE_WRITE(AFE_SGEN_CON0, 0x40e20e2 | (RegSamplingRate << 20) | (RegSamplingRate << 8));
    } else {
        //set intercon
        if (pCmd->out_device == 1) {
            switch(i2s_master_config.i2s_device) {
                case I2S_0://I2S0
                default:
                    //set I2S intercon bit width
                    // bConnect_bitWidth(O00, AgentMemType);
                    // bConnect_bitWidth(O01, AgentMemType);
                    bConnect_bitWidth(O00, HD_AUDIO_WLEN_24_BIT);
                    bConnect_bitWidth(O01, HD_AUDIO_WLEN_24_BIT);

                    if (pCmd->in_device == 1) {
                        //I2S0 in -> I2S0 out
                        bConnect(I00, O00, false);
                        bConnect(I01, O01, false);
                    } else {
                        //UL -> I2S0 out
                        bConnect(I08, O00, false);
                        bConnect(I09, O01, false);
                    }
                    break;
            }
        } else if (pCmd->out_device == 2) {//desense mode, to VUL1
            if (pCmd->in_device == 1) {
                LOG_INF("loopback open, sinegen to I2S master:%d output, I2S master:%d input to VUL1 \r\n", __FUNCTION__, i2s_master_config.i2s_device);
                //set I2S intercon bit width
                bConnect_bitWidth(O00, HD_AUDIO_WLEN_24_BIT);
                bConnect_bitWidth(O01, HD_AUDIO_WLEN_24_BIT);

                //sinegen to I2S master0 out
                AFE_WRITE(AFE_SGEN_CON2, 0x20);
                AFE_WRITE(AFE_SGEN_CON0, 0x40e20e2 | (RegSamplingRate << 20) | (RegSamplingRate << 8));

                //I2S0 in -> VUL1
                bConnect(I00, O16, false);
                bConnect(I01, O17, false);
            } else {
                //UL -> VUL1
                bConnect(I08, O16, false);
                bConnect(I09, O17, false);
            }
        }
    }


    // turn on
    // vAfeTurnOn();
    // AFE_WRITE(AUDIO_TOP_CON1, 0x0);
    // AFE_SET_REG(AFE_DAC_CON0, 1<<0, 1<<0);

    // vEnableADDAInterface(true);

    if ((pCmd->out_device == 1)  || (pCmd->in_device == 1)) {
    //config I2S
    AFE_WRITE(0x420B0038, 0xD4444CC0);//set Pinmux GPIO19/20/21/22
    I2SMasterConfig(&i2s_master_config, true);
    }

    if (pCmd->in_device == 2) {//AMIC
        hal_audio_device_set_analog_mic(u4SamplingRateHz[pCmd->sample_rate], true);
    } else if (pCmd->in_device == 3) { //DMIC
        hal_pinmux_set_function(28, 5);
        hal_pinmux_set_function(29, 5);
        hal_audio_device_set_digital_mic(u4SamplingRateHz[pCmd->sample_rate], pCmd->mic_performance, true);

    }
    if (pCmd->out_device == 2) {
#ifdef RACE_AUDIO_DESENSE_TEST
        hal_gpt_status_t gpt_status = hal_gpt_sw_get_timer(&audio_loopback_gpt_timer);
        if (HAL_GPT_STATUS_OK != gpt_status) {
            LOG_ERR("loopback open error! GPT timer get fail!!!\r\n");
        }
        gpt_status = hal_gpt_sw_start_timer_ms(audio_loopback_gpt_timer, AUDIO_LOOPBAKC_GPT_TIMER_TIMEOUT, CB_AUDIO_LOOPBACK_GPT_CALLBACK, NULL);
        if (HAL_GPT_STATUS_OK != gpt_status) {
            /* err step 3 */
            LOG_ERR("loopback open error! GPT timer start fail!!!\r\n");
        }
#endif
    }
    loopback_running = true;
    // send_pattern_char(pCmd->port, pCmd->baudrate, pCmd->timeout_ms);

    return false;
}

bool race_audio_loopback_close(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    if (loopback_running == false) {
        LOG_ERR("loopback close error! loopback was already closed");
        return true;
    }
#ifdef RACE_AUDIO_DESENSE_TEST
    if (audio_loopback_gpt_timer != 0) {
        hal_gpt_status_t gpt_status = hal_gpt_sw_stop_timer_ms(audio_loopback_gpt_timer);
        if (HAL_GPT_STATUS_OK != gpt_status) {
            LOG_ERR("loopback close error! GPT timer stop fail!!!\r\n");
        }

        gpt_status = hal_gpt_sw_free_timer(audio_loopback_gpt_timer);
        if (HAL_GPT_STATUS_OK != gpt_status) {
            LOG_ERR("loopback close error! GPT timer free fail!!!\r\n");
        }
        audio_loopback_gpt_timer = 0;
    }
    vul_base_addr = 0;
    vul_end_addr = 0;
    gpt_timer_timeout_cnt = 0;
#endif

    I2S_CONFIG_T i2s_master_config;

    memset(&i2s_master_config, 0, sizeof(I2S_CONFIG_T));
    i2s_master_config.i2s_device = I2S_0;
    i2s_master_config.i2s_format = I2S_I2S;
    i2s_master_config.word_length = I2S_32BIT;
    i2s_master_config.is_rx_swap = false;
    i2s_master_config.is_tx_swap = false;
    i2s_master_config.is_internal_loopback = false;
    i2s_master_config.sampling_rate = loopback_samplerate;

    I2SMasterConfig(&i2s_master_config, false);

    if ((loopback_in_device == 0) || ((loopback_in_device == 1) && (loopback_out_device == 2))) {//sinegen
        //disable sinegen
        // AFE_WRITE(AFE_SGEN_CON2, 0x00);
        AFE_SET_REG(AFE_SGEN_CON0, 0 << 24, 1 << 24);
    } else if (loopback_in_device == 2) {//AMIC
        hal_audio_device_set_analog_mic(u4SamplingRateHz[loopback_samplerate], false);
    } else if (loopback_in_device == 3) { //DMIC
        hal_audio_device_set_digital_mic(u4SamplingRateHz[loopback_samplerate], 0, false);
    }
    loopback_running = false;
    hal_clock_disable(HAL_CLOCK_CG_AUD_INTBUS);
    hal_clock_disable(HAL_CLOCK_CG_AUD_ENGINE);
    spm_control_mtcmos(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
    return false;
}

bool race_audio_common(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;

        uint8_t sub_id;
        uint8_t reserv1;
        uint8_t reserv2;
        uint8_t reserv3;
        uint8_t reserv4;
        uint8_t reserv5;
        uint8_t reserv6;
        uint8_t reserv7;
    } PACKED CMD;

    CMD *pCmd = (CMD *)pCmdMsg;

    LOG_INF("Audio Common RACE, sub id: %d", pCmd->sub_id);

    switch (pCmd->sub_id) {
        case RACE_AUDIO_COMMON_SLT_TEST:
#ifdef AIR_AUDIO_SLT_TEST
            audio_slt_test_case_1620();
#else
            LOG_ERR("Audio Common RACE, not support Audio SLT test, please config AIR_AUDIO_SLT_TEST = y");
#endif
            break;
        default:
            LOG_WRN("Audio Common RACE, not support sub id: %d", pCmd->sub_id);
            break;
    }
    return false;
}

void *RACE_CmdHandler_audio(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    (void)length;
    uint16_t    id;
    bool        ret = true;
    LOG_INF("RACE_CmdHandler_audio, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pCmdMsg->hdr.type, pCmdMsg->hdr.id, channel_id);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND) {
        id = pCmdMsg->hdr.id;
        switch (pCmdMsg->hdr.id) {
            case RACE_AUDIO_HQA_LOOPBACK_OPEN: //0x3113
                ret = race_audio_loopback_open((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
                break;
            case RACE_AUDIO_HQA_LOOPBACK_CLOSE: //0x3114
                ret = race_audio_loopback_close((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
                break;
            case RACE_AUDIO_COMMON_CMD: //0x3115
                ret = race_audio_common((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), channel_id);
                break;
            default:
                LOG_ERR("RACE_CmdHandler_audio race_id[0x%X] not support!!!!", pCmdMsg->hdr.id);
                break;
        }
    }

    typedef struct {
        uint8_t status;
    } PACKED RACE_AUDIO_EVT_RES_STRU;

    RACE_AUDIO_EVT_RES_STRU *pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE,
                                                     (uint16_t)pCmdMsg->hdr.id,
                                                     (uint16_t)sizeof(RACE_AUDIO_EVT_RES_STRU),
                                                     channel_id);
    if (pEvt) {
        if (ret) {
            pEvt->status = (uint8_t)RACE_ERRCODE_FAIL;
        } else {
            pEvt->status = (uint8_t)RACE_ERRCODE_SUCCESS;
        }
    }
    return pEvt;
}


#endif  /* RACE_AUDIO_RACE_CMD_ENABLE */
#endif
