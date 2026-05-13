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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#ifdef SOUNDMAKR_MODULE_ENABLED

#include "sound_maker.h"
#include "hal_gpio.h"
#include "hal_gpio_internal.h"

#include "hal_gpt.h"
#include "hal_gpt_internal.h"

#include "hal_pwm.h"
#include "hal_pinmux_define.h"

#define SOUND_MAKER_REPEAT_TIMES_INFINITE   (0) /* Set the repeat_times to it means the repeat will not stop until called sound_maker_stop. */

static bool sound_marker_repeat_play_always_flag= false;

static uint8_t special_count_times=0;
static uint8_t sound_marker_special_repeat_times=0;
static const sound_maker_buzz_map_t *special_buzz_runing_type;
static uint8_t buzz_runing_volume;
static uint32_t handler;
static hal_gpio_pin_t g_buzzer_gpio;
static hal_pwm_channel_t g_buzzer_pwm;

/*special ->buzzer music map*/
const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_SUCCESS_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),BASS5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE1},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_SUCCESS = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_SUCCESS_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FAIL_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE1},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FAIL = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FAIL_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_GFM_RING_ARRAY[] = {
        {(2*NOTE_LENGTH_16_TH),MIDRANGE6},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE7},

        {(6*NOTE_LENGTH_16_TH),TREBLE1},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE7},
        {(4*NOTE_LENGTH_16_TH),TREBLE1},
        {(4*NOTE_LENGTH_16_TH),TREBLE3},

        {(12*NOTE_LENGTH_16_TH),MIDRANGE7},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE3},

        //2
        {(6*NOTE_LENGTH_16_TH),MIDRANGE6},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
        {(4*NOTE_LENGTH_16_TH),MIDRANGE6},
        {(4*NOTE_LENGTH_16_TH),TREBLE1},

        {(12*NOTE_LENGTH_16_TH),MIDRANGE5},
        {(4*NOTE_LENGTH_16_TH),MIDRANGE3},

        {(6*NOTE_LENGTH_16_TH),MIDRANGE4},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE3},

        /*!!!!!*/
        {(4*NOTE_LENGTH_16_TH),MIDRANGE4},
        
        {(4*NOTE_LENGTH_16_TH),TREBLE1},

        //3
        {(8*NOTE_LENGTH_16_TH),MIDRANGE3},
        // {(2*NOTE_LENGTH_16_TH),PAUSE},
        {(2*NOTE_LENGTH_16_TH),TREBLE1},
        {(2*NOTE_LENGTH_16_TH),TREBLE1},
        {(2*NOTE_LENGTH_16_TH),TREBLE1},

        {(6*NOTE_LENGTH_16_TH),MIDRANGE7},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE4},
        {(4*NOTE_LENGTH_16_TH),MIDRANGE4},
        {(4*NOTE_LENGTH_16_TH),MIDRANGE7},

        {(8*NOTE_LENGTH_16_TH),MIDRANGE7},
        // {(4*NOTE_LENGTH_16_TH),PAUSE},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE6},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE7},

        //4
        {(6*NOTE_LENGTH_16_TH),TREBLE1},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE7},
        {(4*NOTE_LENGTH_16_TH),TREBLE1},
        {(4*NOTE_LENGTH_16_TH),TREBLE3},
        {(4*NOTE_LENGTH_16_TH),TREBLE1},

        {(4*NOTE_LENGTH_16_TH),PAUSE},
        {(4*NOTE_LENGTH_16_TH),PAUSE},
        {(4*NOTE_LENGTH_16_TH),PAUSE},
        {(4*NOTE_LENGTH_16_TH),PAUSE},
        {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_GFM_RING = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_GFM_RING_ARRAY,
    .repeat_times = SOUND_MAKER_REPEAT_TIMES_INFINITE
};


const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FMNA_NORMAL_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FMNA_NORMAL = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FMNA_NORMAL_ARRAY,
    .repeat_times = SOUND_MAKER_REPEAT_TIMES_INFINITE
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FMNA_UT_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FMNA_UT = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FMNA_UT_ARRAY,
    .repeat_times = 1
};


const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FACTORY_RESET_ARRAY[]  = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE6},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE4},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FACTORY_RESET = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FACTORY_RESET_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_POWER_ON_ARRAY[]  = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE1},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE4},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_POWER_ON = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_POWER_ON_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PRESS_PAIRING_KEY_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE1},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE6},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE1},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PRESS_PAIRING_KEY = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PRESS_PAIRING_KEY_ARRAY,
    .repeat_times = 1
};


const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PAIRING_TIMEOUT_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PAIRING_TIMEOUT = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PAIRING_TIMEOUT_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PAIRED_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {(2*NOTE_LENGTH_16_TH),BASS6},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PAIRED = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PAIRED_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_UNPAIRED_ARRAY[] = {
        {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE6},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
        {(2*NOTE_LENGTH_16_TH),MIDRANGE4},
        {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_UNPAIRED = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_UNPAIRED_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_READ_IDENTIFIER_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE6},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_READ_IDENTIFIER = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_READ_IDENTIFIER_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PREPARE_POWER_OFF_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE3},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PREPARE_POWER_OFF = {
    .buzz_para=SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PREPARE_POWER_OFF_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_KEY_POWER_OFF_ARRAY[] = {
    {(2*NOTE_LENGTH_16_TH),MIDRANGE2},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE1},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE6},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE1},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE5},
    {(2*NOTE_LENGTH_16_TH),MIDRANGE1},
    {BUZZ_END,PAUSE}
};
const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_KEY_POWER_OFF = {
    .buzz_para = SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_KEY_POWER_OFF_ARRAY,
    .repeat_times = 1
};

const static buzz_para_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_SPECIAL_RING_ARRAY[] = {
    {(1000),1000},
    /*0*/
    {(200),100},
    {(200),200},
    {(200),300},
    {(200),400},
    {(200),500},
    {(200),600},
    {(200),700},
    {(200),800},
    {(200),900},
    {(200),1000},
    /*1*/
    {(200),1100},
    {(200),1200},
    {(200),1300},
    {(200),1400},
    {(200),1500},
    {(200),1600},
    {(200),1700},
    {(200),1800},
    {(200),1900},
    {(200),2000},
    /*2*/
    {(200),2100},
    {(200),2200},
    {(200),2300},
    {(200),2400},
    {(200),2500},
    {(200),2600},
    {(200),2700},
    {(200),2800},
    {(200),2900},
    {(200),3000},
    /*3*/
    {(200),3100},
    {(200),3200},
    {(200),3300},
    {(200),3400},
    {(200),3500},
    {(200),3600},
    {(200),3700},
    {(200),3800},
    {(200),3900},
    {(200),4000},
    /*4*/
    {(200),4100},
    {(200),4200},
    {(200),4300},
    {(200),4400},
    {(200),4500},
    {(200),4600},
    {(200),4700},
    {(200),4800},
    {(200),4900},
    {(200),5000},
    /*5*/
    {(200),5100},
    {(200),5200},
    {(200),5300},
    {(200),5400},
    {(200),5500},
    {(200),5600},
    {(200),5700},
    {(200),5800},
    {(200),5900},
    {(200),6000},
    /*6*/
    {(200),6100},
    {(200),6200},
    {(200),6300},
    {(200),6400},
    {(200),6500},
    {(200),6600},
    {(200),6700},
    {(200),6800},
    {(200),6900},
    {(200),7000},
    /*7*/
    {(200),7100},
    {(200),7200},
    {(200),7300},
    {(200),7400},
    {(200),7500},
    {(200),7600},
    {(200),7700},
    {(200),7800},
    {(200),7900},
    {(200),8000},
    /*8*/
    {(200),8100},
    {(200),8200},
    {(200),8300},
    {(200),8400},
    {(200),8500},
    {(200),8600},
    {(200),8700},
    {(200),8800},
    {(200),8900},
    {(200),9000},
    /*9*/
    {(200),9100},
    {(200),9200},
    {(200),9300},
    {(200),9400},
    {(200),9500},
    {(200),9600},
    {(200),9700},
    {(200),9800},
    {(200),9900},
    {(200),10000},
    /*10*/
    {(200),10100},
    {(200),10200},
    {(200),10300},
    {(200),10400},
    {(200),10500},
    {(200),10600},
    {(200),10700},
    {(200),10800},
    {(200),10900},
    {(200),11000},
    /*11*/
    {(200),11100},
    {(200),11200},
    {(200),11300},
    {(200),11400},
    {(200),11500},
    {(200),11600},
    {(200),11700},
    {(200),11800},
    {(200),11900},
    {(200),12000},
    /*12*/
    {(200),12100},
    {(200),12200},
    {(200),12300},
    {(200),12400},
    {(200),12500},
    {(200),12600},
    {(200),12700},
    {(200),12800},
    {(200),12900},
    {(200),13000},
    /*13*/
    {(200),13100},
    {(200),13200},
    {(200),13300},
    {(200),13400},
    {(200),13500},
    {(200),13600},
    {(200),13700},
    {(200),13800},
    {(200),13900},
    {(200),14000},
    /*14*/
    {(200),14100},
    {(200),14200},
    {(200),14300},
    {(200),14400},
    {(200),14500},
    {(200),14600},
    {(200),14700},
    {(200),14800},
    {(200),14900},
    {(200),15000},
    {BUZZ_END,PAUSE}
};

const static sound_maker_buzz_map_t SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_SPECIAL_RING = {
    .buzz_para = SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_SPECIAL_RING_ARRAY,
    .repeat_times = SOUND_MAKER_REPEAT_TIMES_INFINITE
};

/*api*/
static void sound_marker_clear(void);
void sound_maker_handler_imp(const sound_maker_buzz_map_t *special_buzz_type,uint8_t input_volume);

void sound_maker_handler_imp_callbck(void *user_data)
{
    special_count_times++;
    uint32_t play_time = special_buzz_runing_type->buzz_para[special_count_times].play_time;
    uint32_t frequency = special_buzz_runing_type->buzz_para[special_count_times].frequency;
    uint8_t volume = buzz_runing_volume;

    printk(" sound_maker_handler_imp_callbck  special_count_times=%d,play_time=%d,frequency=%d,volume=%d\r\n", special_count_times,play_time,frequency,volume);

    if(play_time == BUZZ_END)
    {
        if (!sound_marker_repeat_play_always_flag) {
            sound_marker_special_repeat_times--;
        }
        printk(" sound_maker_handler_imp_callbck  sound_marker_special_repeat_times=%d\r\n" , sound_marker_special_repeat_times);

        if(sound_marker_special_repeat_times == 0 && !sound_marker_repeat_play_always_flag)
        {
            sound_maker_stop();
            return;
        }else{
            special_count_times = 0;
            uint32_t play_time = special_buzz_runing_type->buzz_para[special_count_times].play_time;
            uint32_t frequency = special_buzz_runing_type->buzz_para[special_count_times].frequency;

            uint8_t volume = buzz_runing_volume;
            uint32_t temp_frequency = frequency;
            uint32_t temp_total_duty = 0;
            hal_gpt_sw_stop_timer_ms(handler);
            // hal_pwm_stop(g_buzzer_pwm);
            // hal_pwm_deinit(g_buzzer_pwm);
            // hal_pwm_init(g_buzzer_pwm,HAL_PWM_CLOCK_32KHZ);
            uint32_t temp_duty;
            if(frequency != 0)
            {
                hal_pwm_set_frequency(g_buzzer_pwm, temp_frequency, &temp_total_duty);
                printk("sound_maker_handler_imp--duty=%d",temp_total_duty);
                temp_duty = (temp_total_duty * volume / TOTAL_DUTY_VOLUME);
                hal_pwm_set_duty_cycle(g_buzzer_pwm, temp_duty);
                // hal_pwm_start(g_buzzer_pwm);
            }else {
                temp_duty = (0);
                hal_pwm_set_duty_cycle(g_buzzer_pwm, temp_duty);            
            }
            hal_gpt_sw_start_timer_ms(handler, play_time, sound_maker_handler_imp_callbck, NULL);
            printk(" sound_maker_handler_imp_callbck  special_count_times=%d,play_time=%d,frequency=%d,volume=%d\r\n" , special_count_times,play_time,frequency,volume);
            return;
        }
    }

    uint32_t temp_frequency = frequency;
    uint32_t temp_total_duty = 0;
    hal_gpt_sw_stop_timer_ms(handler);
    // hal_pwm_stop(g_buzzer_pwm);
    // hal_pwm_deinit(g_buzzer_pwm);
    // hal_pwm_init(g_buzzer_pwm,HAL_PWM_CLOCK_32KHZ);
    uint32_t temp_duty;
    if(frequency != 0)
    {
        hal_pwm_set_frequency(g_buzzer_pwm, temp_frequency, &temp_total_duty);
        printk("sound_maker_handler_imp--duty=%d",temp_total_duty);
        temp_duty = (temp_total_duty * volume / TOTAL_DUTY_VOLUME);
        hal_pwm_set_duty_cycle(g_buzzer_pwm, temp_duty);
        // hal_pwm_start(g_buzzer_pwm);
    }else {
        temp_duty = (0);
        hal_pwm_set_duty_cycle(g_buzzer_pwm, temp_duty);            
    }
    hal_gpt_sw_start_timer_ms(handler, play_time, sound_maker_handler_imp_callbck, NULL);
}

void sound_maker_handler_imp(const sound_maker_buzz_map_t *special_buzz_type,uint8_t input_volume)
{
    uint32_t total_duty = 0;
    special_count_times = 0;
    sound_marker_clear();
    special_buzz_runing_type = special_buzz_type;
    sound_marker_special_repeat_times = special_buzz_type->repeat_times;
    uint32_t play_time = special_buzz_runing_type->buzz_para[special_count_times].play_time;
    uint32_t frequency = special_buzz_runing_type->buzz_para[special_count_times].frequency;
    uint8_t volume = input_volume;
    buzz_runing_volume = volume;

    /**/
    hal_pinmux_set_function((g_buzzer_gpio), 8);

    if(sound_marker_special_repeat_times == SOUND_MAKER_REPEAT_TIMES_INFINITE)
    {
        sound_marker_repeat_play_always_flag = true;
    }

    hal_gpt_sw_stop_timer_ms(handler);
    hal_pwm_stop(g_buzzer_pwm);
    hal_pwm_deinit(g_buzzer_pwm);
    if(frequency != 0)
    {
        hal_pwm_init(g_buzzer_pwm,HAL_PWM_CLOCK_32KHZ);
        hal_pwm_set_frequency(g_buzzer_pwm, frequency, &total_duty);
        printk("sound_maker_handler_imp--duty=%d",total_duty);
        uint32_t temp_duty;
        temp_duty = (total_duty * volume / TOTAL_DUTY_VOLUME);
        hal_pwm_set_duty_cycle(g_buzzer_pwm, temp_duty);
        hal_pwm_start(g_buzzer_pwm);  
    }else{
        printk("first frequency is 0, can not play sound\r\n");
        return;
    }
    hal_gpt_sw_start_timer_ms(handler, play_time, sound_maker_handler_imp_callbck, NULL);
    printk(" sound_maker_handler_imp  special_count_times=%d,play_time=%d,frequency=%d,volume=%d\r\n", special_count_times,play_time,frequency,volume);
}

static void sound_marker_clear(void)
{
    /*repeat para*/
    sound_marker_repeat_play_always_flag = false;
    /*special para*/
    special_count_times=0;
    sound_marker_special_repeat_times=0;
    special_buzz_runing_type = NULL;
    buzz_runing_volume = 0;
}

void sound_maker_stop(void)
{
    printk("sound_maker_stop\r\n");
    sound_marker_clear();
    hal_gpt_sw_stop_timer_ms(handler);
    hal_pwm_stop(g_buzzer_pwm);
    hal_pwm_deinit(g_buzzer_pwm);

    /*buzzer_pwm*/
    hal_pinmux_set_function((g_buzzer_gpio), 0);
    hal_gpio_pull_down(g_buzzer_gpio);
    hal_gpio_set_direction(g_buzzer_gpio, HAL_GPIO_DIRECTION_INPUT);
}

sound_maker_status_t sound_maker_gpio_init(hal_gpio_pin_t buzz_gpio,hal_pwm_channel_t buzzer_pwm)
{
    if(buzz_gpio > HAL_GPIO_MAX)
    {
        return SOUNDMAKER_STATUS_INVALID_PARAMETER;
    }

    if(buzzer_pwm > HAL_PWM_MAX_CHANNEL)
    {
        return SOUNDMAKER_STATUS_INVALID_PARAMETER;
    }

    g_buzzer_gpio = buzz_gpio;
    g_buzzer_pwm = buzzer_pwm;

    printk("sound_maker g_buzzer_gpio=%d",g_buzzer_gpio);
    printk("sound_maker g_buzzer_pwm=%d",g_buzzer_pwm);

    hal_gpt_sw_get_timer(&handler);
    return SOUNDMAKER_STATUS_SUCCESS;
}

void sound_maker_gpio_deinit()
{
    printk("sound_maker_deinit\r\n");
    sound_marker_clear();

    hal_pwm_stop(g_buzzer_pwm);
    hal_pwm_deinit(g_buzzer_pwm);

    hal_pinmux_set_function((g_buzzer_gpio), 0);
    hal_gpio_pull_down(g_buzzer_gpio);
    hal_gpio_set_direction(g_buzzer_gpio, HAL_GPIO_DIRECTION_INPUT);
    hal_gpio_deinit(g_buzzer_gpio); 
}

sound_maker_status_t sound_maker_handler_config_default(uint8_t type,uint8_t input_volume)
{
    printk(" sound_maker_handler_config_default-type%d,input_volume=%d\r\n", type,input_volume);
    switch(type)
    {
        case SOUND_MARKER_TYPE_SUCCESS:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_SUCCESS,input_volume);
            break;
        case SOUND_MARKER_TYPE_FAIL:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FAIL,input_volume);
            break;
        case SOUND_MARKER_TYPE_GFM_RING:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_GFM_RING,input_volume);
            break;
        case SOUND_MARKER_TYPE_FMNA_NORMAL:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FMNA_NORMAL,input_volume);
            break;
        case SOUND_MARKER_TYPE_FMNA_UT:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FMNA_UT,input_volume);
            break;
        case SOUND_MARKER_TYPE_FACTORY_RESET:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_FACTORY_RESET,input_volume);
            break;
        case SOUND_MARKER_TYPE_POWER_ON:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_POWER_ON,input_volume);
            break;
        case SOUND_MARKER_TYPE_PRESS_PAIRING_KEY:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PRESS_PAIRING_KEY,input_volume);
            break;
        case SOUND_MARKER_TYPE_PAIRING_TIMEOUT:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PAIRING_TIMEOUT,input_volume);
            break;
        case SOUND_MARKER_TYPE_PAIRED:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PAIRED,input_volume);
            break;
        case SOUND_MARKER_TYPE_UNPAIRED:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_UNPAIRED,input_volume);
            break;
        case SOUND_MARKER_TYPE_READ_IDENTIFIER:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_READ_IDENTIFIER,input_volume);
            break;
        case SOUND_MARKER_TYPE_PREPARE_POWER_OFF:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_PREPARE_POWER_OFF,input_volume);
            break;
        case SOUND_MARKER_TYPE_KEY_POWER_OFF:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_KEY_POWER_OFF,input_volume);
            break;
        case SOUND_MARKER_TYPE_SPECIAL_RING:
            sound_maker_handler_imp(&SPECIAL_BUZZER_TYPE_SOUND_MARKER_TYPE_SPECIAL_RING,input_volume);
            break;
        default:
            return SOUNDMAKER_STATUS_INVALID_PARAMETER;
    }
    return SOUNDMAKER_STATUS_SUCCESS;
}
#endif /*   SOUNDMAKR_MODULE_ENABLED   */