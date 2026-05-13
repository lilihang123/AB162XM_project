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

#ifndef __FIND_MY_DEVICE_SOUND_MAKER_HH__
#define __FIND_MY_DEVICE_SOUND_MAKER_HH__

#include "hal_platform.h"

#define TOTAL_DUTY_VOLUME 10
#define SOUND_MAKER_PLAY_DURATION_INFINITE            0xFFFFFFFF
#define BUZZ_END 0xFFFFFFFF

typedef enum {
    SOUND_MARKER_TYPE_SUCCESS                             = 0,
    SOUND_MARKER_TYPE_FAIL,
    SOUND_MARKER_TYPE_GFM_RING,
    SOUND_MARKER_TYPE_FMNA_NORMAL,
    SOUND_MARKER_TYPE_FMNA_UT,
    SOUND_MARKER_TYPE_FACTORY_RESET,
    SOUND_MARKER_TYPE_POWER_ON,
    SOUND_MARKER_TYPE_PRESS_PAIRING_KEY,
    SOUND_MARKER_TYPE_PAIRING_TIMEOUT,
    SOUND_MARKER_TYPE_PAIRED,
    SOUND_MARKER_TYPE_UNPAIRED,
    SOUND_MARKER_TYPE_READ_IDENTIFIER,
    SOUND_MARKER_TYPE_PREPARE_POWER_OFF,
    SOUND_MARKER_TYPE_KEY_POWER_OFF,
    SOUND_MARKER_TYPE_MAX,
    SOUND_MARKER_TYPE_SPECIAL_RING,
}sound_maker_type_t;

typedef enum {
    SOUND_MARKER_VOLUME_0                             = 0,
    SOUND_MARKER_VOLUME_1 = 1,
    SOUND_MARKER_VOLUME_2 = 2,
    SOUND_MARKER_VOLUME_3 = 3,
    SOUND_MARKER_VOLUME_4 = 4,
    SOUND_MARKER_VOLUME_5 = 5,
    SOUND_MARKER_VOLUME_MAX                           = SOUND_MARKER_VOLUME_5,
}sound_maker_volume_t;

typedef struct
{
    uint32_t        play_time;              // sound play duration unit:ms
    uint32_t        frequency;
} buzz_para_t;

typedef struct
{
    const buzz_para_t     *buzz_para;
    uint8_t         repeat_times;           // sound play repeat times
} sound_maker_buzz_map_t;

typedef enum {
    SOUNDMAKER_STATUS_INVALID_PARAMETER  = -1,     /* pmu error invalid parameter */
    SOUNDMAKER_STATUS_ERROR              = 0,      /* pmu undefined error */
    SOUNDMAKER_STATUS_SUCCESS            = 1       /* pmu function ok */
}sound_maker_status_t;

sound_maker_status_t sound_maker_gpio_init(hal_gpio_pin_t buzz_gpio,hal_pwm_channel_t g_buzzer_pwm);
void sound_maker_gpio_deinit(void);
void sound_maker_handler_imp(const sound_maker_buzz_map_t *special_buzz_type,uint8_t input_volume);
void sound_maker_stop(void);
sound_maker_status_t sound_maker_handler_config_default(uint8_t type,uint8_t input_volume);
/*C key notes and frequency comparisozn table*/
#define PAUSE 0

#define BASS1   262
#define BASS1_SEMITONE   277
#define BASS2 294 
#define BASS2_SEMITONE 311
#define BASS3 330 
#define BASS4 349
#define BASS4_SEMITONE 370
#define BASS5   392
#define BASS5_SEMITONE 415
#define BASS6   440
#define BASS6_SEMITONE  466
#define BASS7   494

#define MIDRANGE1   523
#define MIDRANGE1_SEMITONE   554
#define MIDRANGE2 587 
#define MIDRANGE2_SEMITONE 622
#define MIDRANGE3 659 
#define MIDRANGE4 698
#define MIDRANGE4_SEMITONE 740
#define MIDRANGE5   784
#define MIDRANGE5_SEMITONE 831
#define MIDRANGE6   880
#define MIDRANGE6_SEMITONE  932
#define MIDRANGE7   988

#define TREBLE1   1046
#define TREBLE1_SEMITONE   1109
#define TREBLE2 1175 
#define TREBLE2_SEMITONE 1245
#define TREBLE3 1318
#define TREBLE4 1397
#define TREBLE4_SEMITONE 1480
#define TREBLE5   1568
#define TREBLE5_SEMITONE 1661
#define TREBLE6   1760
#define TREBLE6_SEMITONE  1865
#define TREBLE7   1976


/*music time*/
#define NOTE_LENGTH_16_TH 125



#endif /*__FIND_MY_DEVICE_SOUND_MAKER_HH__*/
