/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.SPM_TOP_AUDIO_MEMIF_CONTROL_1
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

#include "hal_spm.h"
#include "hal_gpt.h"
#include "hal_nvic.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"
#include "hal_platform.h"
#include "hal_clock.h"
#include "hal_gpio.h"

#if defined(AIR_PD_DOMAIN_CONTROL_ENABLE)
#include "pd_domain_control.h"
#endif /* AIR_PD_DOMAIN_CONTROL_ENABLE */

#ifdef HAL_SLEEP_MANAGER_ENABLED

/* SPM Code Rev : 20260323_CONN_SLEEP_CHECK.spm */
const unsigned int pcm_event_vector_parameter[8] = {0x33,0x560035,0x5d0034,0x1130032,0x1690030,0x0,0x0,0x0};

#define PCM_IM_MAX_LENGTH 1993

static const unsigned int spm_im[PCM_IM_MAX_LENGTH] = {
0x18c0001f,0x42120184,0xe0e0004e,0x1a40001f,0x00270000,0x1900001f,0x42108008,0xe1000009,0x1a40001f,
0x0000fdff,0x1990001f,0x4210800c,0x81802406,0x1a40001f,0x01270000,0xa2402406,0xe1000009,0x1980001f,
0x42108008,0x1a80001f,0x0138abcd,0xe180000a,0x1980001f,0x42108070,0x1900001f,0x00040001,0xe1800004,
0x1910001f,0x4210806c,0x1a40001f,0xfff8ffff,0x1a80001f,0x00020000,0x82c02404,0x1a40001f,0x4210806c,
0xa100280b,0xe2400004,0x1910001f,0x42108074,0x1990001f,0x42108000,0x1a40001f,0xc0ffffff,0x81402404,
0x1a80001f,0x0000003f,0x81002806,0x1980001f,0x42108074,0xa25c1005,0xe1800009,0x1980001f,0x42108008,
0x1a40001f,0x01390002,0xe1800009,0x1a40001f,0x42108008,0x1980001f,0x01380000,0xe2400006,0x18c0001f,
0x42060000,0xe0e00001,0x18c0001f,0x42120184,0xe0e0004f,0x1940001f,0x42120188,0xe1600003,0x1940001f,
0x42130034,0xe1600000,0xe8208000,0x42120014,0x0b16ff08,0x80308400,0x1b80001f,0x200005a7,0x1b80001f,
0x2000001a,0x1b00001f,0x00250001,0xf0000000,0x17c07c1f,0x18c0001f,0x42120184,0xe0e0003e,0x1b00001f,
0x00400001,0xf0000000,0x17c07c1f,0x18c0001f,0x42120184,0xe0e00031,0x1910001f,0x421300b0,0x81081001,
0x1990001f,0x42120058,0x81841801,0xa1001804,0xc8c00da4,0x17c07c1f,0xc8e00ec4,0x17c07c1f,0xf0000000,
0x17c07c1f,0x18c0001f,0x42120184,0xe0e00035,0x1900001f,0x00000001,0x1b00001f,0x00200001,0xf0000000,
0x17c07c1f,0x18c0001f,0x42120184,0xe0e00032,0x1940001f,0x00000000,0x1a50001f,0x42040004,0x82442401,
0xd8001249,0x17c07c1f,0x18c0001f,0x42120194,0x1980001f,0x00040000,0xe0c00006,0x1990001f,0x42120110,
0x1940001f,0x00000000,0x1910001f,0x42120194,0x810d1001,0xc9201cc6,0x17c07c1f,0x81a01801,0xa1001804,
0xd82010a4,0x17c07c1f,0x1a50001f,0x42040004,0x8243a401,0xd8001529,0x17c07c1f,0x18c0001f,0x42120194,
0x1980001f,0x00020000,0xe0c00006,0x1990001f,0x42120110,0x1940001f,0x00000000,0x1910001f,0x42120194,
0x810c9001,0xc9201cc6,0x17c07c1f,0x81a01801,0xa1001804,0xd8201384,0x17c07c1f,0x1a50001f,0x42040004,
0x824ea401,0xd8001809,0x17c07c1f,0x18c0001f,0x42120194,0x1980001f,0x00010000,0xe0c00006,0x1990001f,
0x42120110,0x1940001f,0x00000000,0x1910001f,0x42120194,0x810c1001,0xc9201cc6,0x17c07c1f,0x81a01801,
0xa1001804,0xd8201664,0x17c07c1f,0x17c07c1f,0xd8000da5,0x17c07c1f,0x18c0001f,0x42120194,0xe0e00000,
0x18d0001f,0x4213006c,0x17c07c1f,0x1950001f,0x42130070,0x81400c05,0x17c07c1f,0x1990001f,0x42130074,
0x81401406,0x18d0001f,0x42120174,0x81810c01,0x80c08c01,0x81600c05,0x81601805,0x17c07c1f,0x18c0001f,
0x4212017c,0xe0c00005,0x1950001f,0x421201b4,0x1990001f,0x42120110,0xd8200da6,0x17c07c1f,0xd8201b45,
0x17c07c1f,0x1b00001f,0x00250001,0xf0000000,0x17c07c1f,0x1980001f,0x00000000,0x1a10001f,0x4213017c,
0x18c0001f,0x42120160,0xe0c00006,0x18c0001f,0x42130134,0xe0c00006,0x1a10001f,0x42130158,0x18c0001f,
0x4212015c,0xe0c00006,0x18c0001f,0x4213012c,0xe0c00006,0x1a10001f,0x42130164,0x18c0001f,0x42120164,
0xe0c00006,0x18c0001f,0x42130130,0xe0c00006,0x1a10001f,0x42130170,0x18c0001f,0x42120168,0xe0c00006,
0x18c0001f,0x42130138,0xe0c00006,0x1900001f,0x42120194,0xe1200000,0x1b00001f,0x00200001,0x1940001f,
0x00000001,0x1980001f,0x00000000,0xf0000000,0x17c07c1f,0x18c0001f,0x42120184,0xe0e00041,0x1980001f,
0x42108008,0x1a80001f,0x0138abcd,0xe180000a,0x1a40001f,0x01390003,0xe1800009,0x1910001f,0x42108074,
0x1990001f,0x42108000,0x1a40001f,0xc0ffffff,0x81402404,0x1a80001f,0x00003f00,0x81002806,0x1980001f,
0x42108074,0xa2581005,0xe1800009,0x1910001f,0x4210806c,0x1a40001f,0xfff8ffff,0x82c02404,0x1a40001f,
0x4210806c,0xe240000b,0x1a90001f,0x42107040,0x1900001f,0x42108070,0x8241a801,0xd8202809,0x17c07c1f,
0x1980001f,0x00040001,0xe1000006,0xd8002909,0x17c07c1f,0x1980001f,0x00040000,0xe1000006,0x1a40001f,
0x42108008,0x1980001f,0x01380000,0xe2400006,0x1a40001f,0x00270000,0x1900001f,0x42108008,0xe1000009,
0x1a40001f,0x00000200,0x1990001f,0x4210800c,0xa1802406,0x1a40001f,0x01270000,0xa2402406,0xe1000009,
0x1b80001f,0x2000000e,0x1910001f,0x42120114,0x91201001,0xa0108400,0x1940001f,0x42130034,0xe1600001,
0x1b00001f,0x00080001,0xe8208000,0x42120014,0x0b16ff0c,0xe8208000,0x42120014,0x0b16ff08,0xf0000000,
0x17c07c1f,0x18c0001f,0x42120184,0xe0e00061,0x1910001f,0x42130120,0x1980001f,0x42120078,0xe1800004,
0x1910001f,0x42104100,0x1980001f,0x42104030,0xe1800004,0x1910001f,0x4210410c,0x1980001f,0x42104034,
0xe1800004,0x1940001f,0x42107004,0x1990001f,0x42107004,0xa19c0406,0xe1400006,0x1a10001f,0x42107004,
0x1900001f,0x42040b54,0xe1200001,0x1940001f,0x42230074,0xe1600001,0x1a40001f,0x42230114,0x1980001f,
0x00080203,0xe2400006,0x1a90001f,0x42107030,0x1a00001f,0x42120170,0xe200000a,0x1910001f,0x2e2e2e2e,
0x1980001f,0x0000dead,0x02201804,0xd8003888,0x17c07c1f,0x0291040a,0x1a00001f,0x42120170,0xe200000a,
0x1910001f,0x2e2e2e2e,0x1980001f,0xdeadbeef,0x02601804,0xd8203889,0x17c07c1f,0x18d0001f,0x42230000,
0xd80034a3,0x17c07c1f,0x1980001f,0x42230118,0xe1a00000,0x1158101f,0x1980001f,0x42230100,0xe1800005,
0x0211040a,0x1a40001f,0x42230104,0xe2400008,0x1192101f,0x114a181f,0x1980001f,0x42230110,0xe1800005,
0x124e101f,0xd8203829,0x17c07c1f,0x1980001f,0x42230118,0x1a40001f,0x00008000,0xe1800009,0x0291140a,
0xd0003340,0x17c07c1f,0x18d0001f,0x42230000,0xd8003883,0x17c07c1f,0x1980001f,0x42230118,0xe1a00000,
0x1980001f,0x42230078,0xe1a00001,0x1a40001f,0x42040b44,0xe2600001,0xd0005b20,0x17c07c1f,0x1a50001f,
0x421300b4,0x82442401,0x82602401,0x1990001f,0x42120110,0x81802406,0xc9203c06,0x17c07c1f,0xc9003ce6,
0x17c07c1f,0xf0000000,0x17c07c1f,0x18c0001f,0x42120184,0xe0e0006f,0x1b00001f,0x00080001,0xf0000000,
0x17c07c1f,0x1990001f,0x42107028,0x1940001f,0x42107028,0x1a40001f,0x00000100,0xa1802406,0xe1400006,
0x18c0001f,0x42120184,0xe0e00062,0x1a40001f,0x42104110,0xe2600000,0x1a40001f,0x42104104,0xe2600000,
0x1900001f,0x4210410c,0x1990001f,0x4210410c,0x1a40001f,0x80000000,0xa2801809,0xe100000a,0x1a40001f,
0xc0000000,0xa2801809,0xe100000a,0x1a40001f,0xe0000000,0xa2801809,0xe100000a,0x1a40001f,0xf0000000,
0xa2801809,0xe100000a,0x1a40001f,0xf8000000,0xa2801809,0xe100000a,0x1a40001f,0xfc000000,0xa2801809,
0xe100000a,0x1a40001f,0xfe000000,0xa2801809,0xe100000a,0x1a40001f,0xff000000,0xa2801809,0xe100000a,
0x1a40001f,0xff800000,0xa2801809,0xe100000a,0x1a40001f,0xffc00000,0xa2801809,0xe100000a,0x1a40001f,
0xffe00000,0xa2801809,0xe100000a,0x1a40001f,0xfff00000,0xa2801809,0xe100000a,0x1a40001f,0xfff80000,
0xa2801809,0xe100000a,0x1a40001f,0xfffc0000,0xa2801809,0xe100000a,0x1a40001f,0xfffe0000,0xa2801809,
0xe100000a,0x1a40001f,0xffff0000,0xa2801809,0xe100000a,0x1900001f,0x42104100,0x1990001f,0x42104100,
0x1a40001f,0x00080000,0xa2801809,0xe100000a,0x1a40001f,0x000c0000,0xa2801809,0xe100000a,0x1a40001f,
0x000e0000,0xa2801809,0xe100000a,0x1a40001f,0x000f0000,0xa2801809,0xe100000a,0x1980001f,0x4210411c,
0xe1a00000,0xe1a00001,0x1a40001f,0x42104134,0xe2600000,0xe2600002,0xe2600003,0x18c0001f,0x42060000,
0xe0e00001,0x1a40001f,0x00270000,0x1900001f,0x42108008,0xe1000009,0x1a40001f,0x00008000,0x1990001f,
0x4210800c,0xa1802406,0x1a40001f,0x01270000,0xa2402406,0xe1000009,0x1940001f,0x42130034,0xe1600001,
0x1b00001f,0x00080001,0x1950001f,0x42107040,0x18c0001f,0x00000080,0xa1401403,0x18c0001f,0x42107040,
0xe0c00005,0xe8208000,0x42120014,0x0b16ff0c,0xe8208000,0x42120014,0x0b16ff08,0xf0000000,0x17c07c1f,
0xe0e00016,0x1b80001f,0x20000003,0xe0e0001e,0x1b80001f,0x20000003,0x81809401,0xd8005206,0x17c07c1f,
0xe0e0000e,0x1b80001f,0x20000004,0xe0e0001e,0xe0e0001c,0xe0e0001d,0xd0005600,0x17c07c1f,0x1980001f,
0x42130088,0x1a00001f,0x42130090,0x1a40001f,0x42130098,0x1a80001f,0x42130080,0xe1a00000,0x1b80001f,
0x20000004,0xe2200000,0x1b80001f,0x20000004,0xe2600000,0xe2a00000,0xe0e0000e,0x1b80001f,0x20000004,
0xe0e0001e,0xe0e0001c,0xe0e0001d,0x1900001f,0x01000000,0xe1800004,0xe2000004,0xe2400004,0x1900001f,
0x00030000,0xe2800004,0xd0005600,0x17c07c1f,0xe0e0000d,0xf0000000,0x17c07c1f,0xe0e0001d,0xe0e0001f,
0x81809401,0xd8005746,0x17c07c1f,0xd0005a00,0x17c07c1f,0x1980001f,0x42130088,0x1a00001f,0x42130090,
0x1a40001f,0x42130098,0x1a80001f,0x42130080,0xe1a00000,0xe2200000,0xe2600000,0xe2a00000,0xe1a00001,
0x1b80001f,0x20000004,0xe2200001,0x1b80001f,0x20000004,0xe2600001,0xe2a00003,0xd0005a00,0x17c07c1f,
0xe0e0001e,0xe0e0001a,0x1b80001f,0x20000003,0xe0e00012,0x1b80001f,0x20000003,0xf0000000,0x17c07c1f,
0x1900001f,0x42108008,0x1a40001f,0x0138abcd,0xe1000009,0x1980001f,0x01390003,0xe1000006,0x1990001f,
0x42107044,0x1a00001f,0x0000f7ff,0x82802006,0x1a00001f,0x010a0000,0xa180200a,0xe1000006,0x1a90001f,
0x42107040,0x8240040a,0xd8005e89,0x17c07c1f,0x1980001f,0x012c0006,0xe1000006,0xd0005ee0,0x17c07c1f,
0x1980001f,0x012c0007,0xe1000006,0x8240a801,0xd82063a9,0x17c07c1f,0x81812801,0xd8206106,0x17c07c1f,
0x1a90001f,0x42108030,0x1980001f,0xff00ffff,0x82402806,0x1900001f,0x00690000,0xa2801009,0x1980001f,
0x42108030,0xe180000a,0x1a90001f,0x42108030,0x1980001f,0xfffffcff,0x82402806,0x1900001f,0x00000300,
0xa2801009,0x1980001f,0x42108030,0xe180000a,0x1b80001f,0x20002bc0,0x1a90001f,0x42108030,0x1980001f,
0xfffffcff,0x82402806,0x1980001f,0x42108030,0xe1800009,0x1990001f,0x421300e0,0x1a40001f,0x420c00e0,
0xe2400006,0x1a90001f,0x421300e4,0x1a40001f,0x420d00f0,0xe240000a,0x1980001f,0x42108008,0x1a40001f,
0x01230008,0x1a80001f,0x01220010,0xe1800009,0xe180000a,0x1910001f,0x42108074,0x1990001f,0x42108000,
0x1a40001f,0xc0ffffff,0x81402404,0x1a80001f,0x00003f00,0x81002806,0x1980001f,0x42108074,0xa2581005,
0xe1800009,0x1910001f,0x4210806c,0x1a40001f,0xfff8ffff,0x82c02404,0x1a40001f,0x4210806c,0xe240000b,
0x1980001f,0x42108008,0x1a40001f,0x01380000,0xe1800009,0x1a90001f,0x42107040,0x1900001f,0x42108070,
0x8241a801,0xd8206ac9,0x17c07c1f,0x1980001f,0x00040001,0xe1000006,0xd8006b29,0x17c07c1f,0x1980001f,
0x00040000,0xe1000006,0x1a50001f,0x42107040,0x1a80001f,0x0000000f,0x8184240a,0x1a80001f,0x00000f00,
0x82c2240a,0xa240180b,0x1a80001f,0x011f1010,0xa2c02809,0x1980001f,0x42108008,0xe180000b,0x1a80001f,
0x42108008,0x1a40001f,0x01380000,0xe2800009,0xd0003a60,0x17c07c1f,0x1980001f,0x42108070,0x1900001f,
0x00040001,0xe1800004,0x1900001f,0x42108008,0x1a40001f,0x01390003,0xe1000009,0x1900001f,0x42108008,
0x1a40001f,0x0138abcd,0xe1000009,0x1910001f,0x4210806c,0x1a40001f,0xfff8ffff,0x1a80001f,0x00020000,
0x82c02404,0x1a40001f,0x4210806c,0xa100280b,0xe2400004,0x1910001f,0x42108074,0x1990001f,0x42108000,
0x1a40001f,0xc0ffffff,0x81402404,0x1a80001f,0x0000003f,0x81002806,0x1980001f,0x42108074,0xa25c1005,
0xe1800009,0x1a90001f,0x42107040,0x82412801,0xd82074e9,0x17c07c1f,0x1a90001f,0x42108030,0x1980001f,
0xff00ffff,0x82402806,0x1900001f,0x00960000,0xa2801009,0x1980001f,0x42108030,0xe180000a,0x1900001f,
0x42108008,0x1980001f,0x012c0007,0xe1000006,0x1980001f,0x00230000,0xe1000006,0x1980001f,0x00240000,
0x1a90001f,0x4210800c,0xe1000006,0x1a50001f,0x4210800c,0xa198240a,0x1900001f,0x42140470,0xe1000006,
0x1a40001f,0x42108008,0x1980001f,0x00250000,0xe2400006,0x1a40001f,0x42140474,0x1a90001f,0x4210800c,
0xe240000a,0x1900001f,0x42108008,0x1980001f,0x01210010,0xe1000006,0x1990001f,0x42104038,0x1a40001f,
0x420c00e0,0x1900001f,0x00000003,0x82001006,0xe2400008,0x1a80001f,0x420d00f0,0x82021804,0xe2800008,
0x1900001f,0x42108008,0x1990001f,0x42107044,0x1a00001f,0x0000ffff,0x82802006,0x1a00001f,0x010a0000,
0xa180200a,0xe1000006,0x1980001f,0x01390002,0x1a40001f,0x01380000,0x1900001f,0x42108008,0xe1000006,
0xe1000009,0xf0000000,0x17c07c1f,0xe8208000,0x42120188,0x00000003,0x1b80001f,0x2000001a,0xe8208000,
0x42120188,0x00000103,0xf0000000,0x17c07c1f,0x17c07c1f,0x17c07c1f,0x17c07c1f,0x17c07c1f,0x17c07c1f,
0x17c07c1f,0x17c07c1f,0x17c07c1f,0x17c07c1f,0x17c07c1f,0x17c07c1f,0x17c07c1f,0x1840001f,0x00000001,
0x1800001f,0x00000001,0x18c0001f,0x4212016c,0xe0e00000,0x18c0001f,0x42120184,0xe0e00001,0x81f08407,
0xa1d00407,0x18c0001f,0x4212005c,0xe0e00000,0xe8208000,0x42120014,0x0b16ff03,0xe8208000,0x42120188,
0x00000003,0x1b80001f,0x2000001a,0x1b00001f,0x01000001,0x18d0001f,0x4212014c,0x80cc0c01,0xd8004063,
0x17c07c1f,0x18c0001f,0x42120184,0xe0e00017,0x1b00001f,0x1e800001,0x18d0001f,0x4212014c,0x80ce0c01,
0xd8001203,0x17c07c1f,0x1b00001f,0x1e800001,0x18d0001f,0x4212014c,0x80cc8c01,0xd8001ec3,0x17c07c1f,
0x1b00001f,0x1e800001,0x18d0001f,0x4212014c,0x80cd8c01,0xd8003b83,0x17c07c1f,0x1b00001f,0x1e800001,
0x1950001f,0x42106010,0x18d0001f,0x42120084,0xa1401403,0x18d0001f,0x42106018,0x80e00c01,0xa1401403,
0x18d0001f,0x4212014c,0x80cd0c01,0x81601401,0xa0c01403,0xd8002783,0x17c07c1f,0x1b00001f,0x1e800001,
0x18c0001f,0x42120184,0xe0e00017,0x1b00001f,0x1e800001,0x18d0001f,0x4212014c,0x80cb8c01,0x1910001f,
0x421300b0,0x81a01001,0x80c01803,0x17c07c1f,0xc8e07d43,0x17c07c1f,0x1b80001f,0xd0100001,0x1b80001f,
0x90100001,0x17c07c1f,0x1980001f,0x42120188,0xe1a00003,0xd82003c3,0x17c07c1f,0x1b00001f,0x00d00001,
0x18c0001f,0x42120184,0xe0e00021,0x1910001f,0x421300b0,0x80c41001,0xd8000f63,0x17c07c1f,0x1b80001f,
0xd0100001,0x1b80001f,0x90100001,0x18d0001f,0x42120174,0x1900001f,0x00000001,0x1950001f,0x421301a4,
0x814b1401,0x81801404,0xd8200da6,0x17c07c1f,0x1b00001f,0x00c00001,0x1910001f,0x421300b0,0x80c41001,
0x1950001f,0x421301a4,0x814b1401,0x80f01403,0xd8000f63,0x17c07c1f,0x18c0001f,0x42120184,0xe0e0002f,
0x17c07c1f,0xd00003c0,0x17c07c1f,0x18c0001f,0x42120184,0xe0e000ff,0xf0000000,0x1940001f,0x42120188,
0xe1600003,0x18c0001f,0x42120184,0xe0e00013,0x18c0001f,0x4212000c,0x1940001f,0x00000001,0x1910001f,
0x42120080,0xd8201924,0x17c07c1f,0x1910001f,0x42130110,0x81041001,0xd8000504,0x17c07c1f,0x1910001f,
0x421201b8,0x1990001f,0x42130164,0xd8200506,0x17c07c1f,0xd8201464,0x17c07c1f,0x1980001f,0x422f0070,
0xe1a00001,0x1910001f,0x422f0074,0xd82015c4,0x17c07c1f,0x1980001f,0x42120080,0xe1a00000,0xe0e0001d,
0xe0e0001f,0x1980001f,0x421300a0,0xe1a00000,0xe1a00001,0xe0e0001e,0x1910001f,0x42120174,0x81029001,
0xd80018e4,0x17c07c1f,0xe0e0001a,0x1b80001f,0x20000003,0xe0e00012,0x1b80001f,0x20000003,0xd0000500,
0x17c07c1f,0x1910001f,0x42120174,0x81029001,0xd8001a84,0x17c07c1f,0xe0e00016,0x1b80001f,0x20000003,
0xe0e0001e,0x1b80001f,0x20000003,0x1980001f,0x421300a0,0xe1a00000,0xe0e0000e,0x1b80001f,0x20000004,
0xe0e0001e,0xe0e0001c,0xe0e0001d,0x1900001f,0x01000000,0xe1800004,0xe0e0000d,0x1900001f,0x42130064,
0xe1200000,0x1980001f,0x422f0070,0xe1a00000,0x18c0001f,0x42120080,0xe0e00001,0x1900001f,0x42130104,
0xe1200000,0x1910001f,0x422f0074,0xd8001da4,0x17c07c1f,0x1a00001f,0x42120164,0xe2200001,0xd0000500,
0x17c07c1f,0x1940001f,0x42120188,0xe1600003,0x18c0001f,0x42120184,0xe0e00011,0x18c0001f,0x42120008,
0x1940001f,0x00000002,0x1910001f,0x42120174,0x81001001,0xd82022c4,0x17c07c1f,0x1910001f,0x42130110,
0x81000404,0xd80005e4,0x17c07c1f,0x81f10407,0x1980001f,0x422f0040,0xe1a00001,0x1910001f,0x422f0044,
0xd82021c4,0x17c07c1f,0xc0c05660,0x17c07c1f,0xd00005e0,0x17c07c1f,0x1a50001f,0x42107040,0x1a80001f,
0x0000000f,0x8184240a,0x1a80001f,0x00000f00,0x82c2240a,0xa240180b,0x1a80001f,0x011f0000,0xa2c02809,
0x1980001f,0x42108008,0xe180000b,0x1a00001f,0x4212015c,0xe2200001,0xc8e04fe4,0x17c07c1f,0xa1d10407,
0x1980001f,0x42130100,0xe1a00000,0x1940001f,0x422f0040,0xe1600000,0x1990001f,0x42120174,0x81108406,
0xd8202744,0x17c07c1f,0x1910001f,0x422f0044,0xd80026c4,0x17c07c1f,0xd00005e0,0x17c07c1f,0x1940001f,
0x42120188,0xe1600003,0x18c0001f,0x42120184,0xe0e00012,0x18c0001f,0x42120010,0x1940001f,0x00000004,
0x1910001f,0x42120084,0xd82033a4,0x17c07c1f,0x1910001f,0x4213017c,0x1990001f,0x42130194,0x81800406,
0x81001804,0xd8200904,0x17c07c1f,0x1a50001f,0x42106010,0x82602401,0x1990001f,0x42130110,0x818c1801,
0xa1802406,0xd8000906,0x17c07c1f,0x1980001f,0x42120084,0xe1a00000,0x1910001f,0x42130194,0x81081001,
0xd8206bc4,0x17c07c1f,0x1a50001f,0xa0010000,0x1980001f,0x42120088,0xe1800009,0x1a50001f,0xa0010004,
0x1980001f,0x42120090,0xe1800009,0x1a00001f,0x0000ca00,0x1a40001f,0x42000000,0x02a02408,0xd8002f0a,
0x17c07c1f,0x1990001f,0x42106010,0xd8200906,0x17c07c1f,0x1990001f,0xa0010008,0x1a50001f,0xa0010480,
0xe2400006,0x1a10001f,0xa001000c,0x02510409,0xe2400008,0x1980001f,0x422f0050,0xe1a00001,0x1910001f,
0x422f0054,0xd8203084,0x17c07c1f,0xc0c05660,0x17c07c1f,0x1990001f,0x4212008c,0xd82032a6,0x17c07c1f,
0x1980001f,0x422f0058,0xe1a00001,0x1910001f,0x422f005c,0xd8203224,0x17c07c1f,0x18c0001f,0x42130154,
0x1940001f,0x00000004,0xc0c05660,0x17c07c1f,0xd0000900,0x17c07c1f,0x1910001f,0x421300ac,0x18c0001f,
0x4212008c,0xe0c00004,0x1910001f,0x42120174,0x81011001,0xd8006de4,0x17c07c1f,0x18c0001f,0x42120010,
0x1940001f,0x00000004,0xc0c04fe0,0x17c07c1f,0x18c0001f,0x42130154,0x1940001f,0x00000004,0xc0c04fe0,
0x17c07c1f,0x1990001f,0x4212008c,0xd82037c6,0x17c07c1f,0x1980001f,0x422f0058,0xe1a00000,0x1910001f,
0x422f005c,0xd8003744,0x17c07c1f,0x18c0001f,0x42120084,0xe0e00001,0x1980001f,0x422f0050,0xe1a00000,
0x1910001f,0x422f0054,0xd8003884,0x17c07c1f,0x1a00001f,0x42120160,0xe2200001,0x1b80001f,0x2000062a,
0x1990001f,0x42120088,0x1a40001f,0xa0010000,0xe2400006,0x1990001f,0x42120090,0x1a00001f,0x00800000,
0xa1801808,0x1a40001f,0xa0010004,0xe2400006,0xd0000900,0x17c07c1f,0x1940001f,0x42120188,0xe1600003,
0x18c0001f,0x42120184,0xe0e00014,0x18d0001f,0x421300d4,0xd8203dc3,0x17c07c1f,0x18c0001f,0x421300d4,
0xe0e00000,0x18c0001f,0x42090064,0xe0e0011b,0xd00006c0,0x17c07c1f,0x1990001f,0x422e0018,0x1940001f,
0xfffffeff,0x81801406,0x18c0001f,0x422e0018,0xe0c00006,0x1980001f,0x42130108,0xe1a00000,0x18c0001f,
0x421300d4,0xe0e00001,0x1b80001f,0x2000001a,0x18c0001f,0x42090064,0xe0e0001b,0xd00006c0,0x17c07c1f,
0x18c0001f,0x42120184,0xe0e00070,0x1a40001f,0x00270000,0x1900001f,0x42108008,0xe1000009,0x1a40001f,
0x00007fff,0x1990001f,0x4210800c,0x81802406,0x1a40001f,0x01270000,0xa2402406,0xe1000009,0x1900001f,
0x42104100,0x1990001f,0x42104030,0x1a40001f,0x000e0000,0xa2802406,0xe100000a,0x1a40001f,0x000c0000,
0xa2802406,0xe100000a,0x1a40001f,0x00080000,0xa2802406,0xe100000a,0x1a40001f,0x00000000,0xa2802406,
0xe100000a,0x1900001f,0x4210410c,0x1990001f,0x42104034,0x1a40001f,0xfffe0000,0xa2802406,0xe100000a,
0x1a40001f,0xfffc0000,0xa2802406,0xe100000a,0x1a40001f,0xfff80000,0xa2802406,0xe100000a,0x1a40001f,
0xfff00000,0xa2802406,0xe100000a,0x1a40001f,0xffe00000,0xa2802406,0xe100000a,0x1a40001f,0xffc00000,
0xa2802406,0xe100000a,0x1a40001f,0xff800000,0xa2802406,0xe100000a,0x1a40001f,0xff000000,0xa2802406,
0xe100000a,0x1a40001f,0xfe000000,0xa2802406,0xe100000a,0x1a40001f,0xfc000000,0xa2802406,0xe100000a,
0x1a40001f,0xf8000000,0xa2802406,0xe100000a,0x1a40001f,0xf0000000,0xa2802406,0xe100000a,0x1a40001f,
0xe0000000,0xa2802406,0xe100000a,0x1a40001f,0xc0000000,0xa2802406,0xe100000a,0x1a40001f,0x80000000,
0xa2802406,0xe100000a,0x1a40001f,0x00000000,0xa2802406,0xe100000a,0x1980001f,0x4210411c,0xe1a00000,
0x1a40001f,0x42104134,0xe2600001,0xe2600000,0x1980001f,0x0000ffff,0x1a40001f,0x42104110,0xe2400006,
0x1940001f,0x42104104,0x1980001f,0x000f0000,0xe1400006,0x1a40001f,0x4210411c,0xe2400006,0x1940001f,
0x42104134,0xe1400006,0x1940001f,0x42120180,0xe1600001,0x1900001f,0x42040b54,0xe1200001,0x1940001f,
0x42230074,0xe1600001,0x1a40001f,0x42230114,0x1980001f,0x00080203,0xe2400006,0x1a90001f,0x42107030,
0x1a00001f,0x42120170,0xe200000a,0x1910001f,0x2e2e2e2e,0x1980001f,0x0000dead,0x02201804,0xd80058e8,
0x17c07c1f,0x0291040a,0x1a00001f,0x42120170,0xe200000a,0x1910001f,0x2e2e2e2e,0x1980001f,0xdeadbeef,
0x02601804,0xd82058e9,0x17c07c1f,0x18d0001f,0x42230000,0xd8005503,0x17c07c1f,0x1980001f,0x42230118,
0xe1a00000,0x1158101f,0x0211040a,0x1980001f,0x42230100,0xe1800008,0x1a40001f,0x42230104,0xe2400005,
0x1192101f,0x114a181f,0x1980001f,0x42230110,0xe1800005,0x124e101f,0xd8205889,0x17c07c1f,0x1980001f,
0x42230118,0x1a40001f,0x00008000,0xe1800009,0x0291140a,0xd00053a0,0x17c07c1f,0x18d0001f,0x42230000,
0xd80058e3,0x17c07c1f,0x1980001f,0x42230118,0xe1a00000,0x1980001f,0x42230078,0xe1a00001,0x1a40001f,
0x42040b44,0xe2600001,0x18c0001f,0x42120184,0xe0e0007f,0x1940001f,0x42107004,0x1990001f,0x42107004,
0x18c0001f,0xfeffffff,0x81800c06,0xe1400006,0x1910001f,0x42120078,0x1980001f,0x42130120,0xe1800004,
0xc8c06de1,0x17c07c1f,0x1990001f,0x42107040,0x18c0001f,0x00070000,0x81961803,0x1950001f,0x42108014,
0x18c0001f,0xfff8ffff,0x81400c05,0xa1801805,0x18c0001f,0x42108014,0xe0c00006,0x1990001f,0x421300d8,
0x18c0001f,0x00000100,0xa1800c06,0x1940001f,0x421300d8,0xe1400006,0x1990001f,0x421300d8,0x81800406,
0xd82060e6,0x17c07c1f,0x1940001f,0x42010108,0xe1600013,0x1980001f,0x422f0030,0xe1a00000,0x1940001f,
0x42120180,0xe1600000,0x1980001f,0x4212017c,0x1254041f,0xe1800009,0x1980001f,0x4212017c,0x1254041f,
0xe1800009,0x1a50001f,0x421300b4,0x82482401,0xd8006249,0x17c07c1f,0x1940001f,0x00000063,0x1990001f,
0x42120110,0xd8206446,0x17c07c1f,0x1b80001f,0x200066cb,0x01600405,0xd8006325,0x17c07c1f,0x1950001f,
0x42107040,0x18c0001f,0xffffff7f,0x81401403,0x18c0001f,0x42107040,0xe0c00005,0x1980001f,0x4212017c,
0xe1a00000,0x1b80001f,0x20000003,0xd00070c0,0x17c07c1f,0x1980001f,0x01010101,0x1940001f,0x42030044,
0x18c0001f,0x42030034,0xe1400006,0xe0c00006,0x1940001f,0x42030048,0x18c0001f,0x42030038,0xe1400006,
0xe0c00006,0x1940001f,0x4203004c,0x18c0001f,0x4203003c,0xe1400006,0xe0c00006,0x1940001f,0x42030050,
0x18c0001f,0x42030040,0xe1400006,0xe0c00006,0x1b80001f,0x20000034,0x1940001f,0x42030044,0xe1600000,
0x1940001f,0x42030048,0xe1600000,0x1940001f,0x4203004c,0xe1600000,0x1940001f,0x42030050,0xe1600000,
0x18c0001f,0x4212016c,0xe0e00001,0xd00003c0,0x17c07c1f,0x1980001f,0x422f0050,0xe1a00001,0x1910001f,
0x422f0054,0xd8206c24,0x17c07c1f,0x18c0001f,0x42120010,0xe0e0001d,0x1980001f,0x42040b70,0x18c0001f,
0x00000040,0xe1800003,0xd0000900,0x17c07c1f,0x18c0001f,0x42120010,0xe0e0000d,0x1980001f,0x42040b80,
0x18c0001f,0x00000040,0xe1800003,0x1980001f,0x422f0050,0xe1a00000,0x18c0001f,0x42120084,0xe0e00001,
0x1910001f,0x422f0054,0xd8006fa4,0x17c07c1f,0x1a00001f,0x42120160,0xe2200001,0xd0000900,0x17c07c1f,
0x18c0001f,0x4212000c,0xe0e00016,0x1b80001f,0x20000003,0xe0e0001e,0x1b80001f,0x20000003,0xe0e0000e,
0x1b80001f,0x20000004,0xe0e0001e,0xe0e0001c,0xe0e0001d,0xe0e0000d,0x1980001f,0x422f0070,0xe1a00000,
0x1910001f,0x422f0074,0xd8007304,0x17c07c1f,0x1950001f,0x42105018,0x1980001f,0x400c0134,0xe1800005,
0x18c0001f,0x400c012c,0xe0e00001,0x1990001f,0x42105014,0x18c0001f,0x400c012c,0xe0c00006,0x81481401,
0x1990001f,0x42107028,0x18c0001f,0xfffffeff,0x81801803,0xa1541406,0x18c0001f,0x42107028,0xe0c00005,
0x1b80001f,0x2000001a,0x1980001f,0x422f0070,0xe1a00001,0x1910001f,0x422f0074,0xd8207704,0x17c07c1f,
0x18c0001f,0x4212000c,0xe0e0001d,0xe0e0001f,0xe0e0001e,0xe0e0001a,0x1b80001f,0x20000003,0xe0e00012,
0x1b80001f,0x20000003,0xd0006620,0x17c07c1f};


static struct {
    uint32_t audio;
    uint32_t conn_top_off;
    uint32_t conn_zigbee;
    uint32_t perisys;
    uint32_t rtcsys;
} mtcmos_resource;

typedef struct {
    uint32_t start_addr;
    void (*force_power_down)(void);
    void (*force_power_on)(void);
    void (*enter_non_retention)(void);
} spm_ram_block_ctrl_t;

const spm_ram_block_ctrl_t spm_ram_block_ctrl_table[] =
{
    {0x04000000,  sysram_0_0_force_power_down, sysram_0_0_force_power_on, sysram_0_0_enter_non_retention},
    {0x04004000,  sysram_0_1_force_power_down, sysram_0_1_force_power_on, sysram_0_1_enter_non_retention},
    {0x04008000,  sysram_0_2_force_power_down, sysram_0_2_force_power_on, sysram_0_2_enter_non_retention},
    {0x0400C000,  sysram_0_3_force_power_down, sysram_0_3_force_power_on, sysram_0_3_enter_non_retention},
    {0x04010000,  sysram_1_0_force_power_down, sysram_1_0_force_power_on, sysram_1_0_enter_non_retention},
    {0x04014000,  sysram_1_1_force_power_down, sysram_1_1_force_power_on, sysram_1_1_enter_non_retention},
    {0x04018000,  sysram_1_2_force_power_down, sysram_1_2_force_power_on, sysram_1_2_enter_non_retention},
    {0x0401C000,  sysram_1_3_force_power_down, sysram_1_3_force_power_on, sysram_1_3_enter_non_retention},
    {0x04020000,  sysram_2_0_force_power_down, sysram_2_0_force_power_on, sysram_2_0_enter_non_retention},
    {0x04024000,  sysram_2_1_force_power_down, sysram_2_1_force_power_on, sysram_2_1_enter_non_retention},
    {0x04028000, sysram_2_2_force_power_down, sysram_2_2_force_power_on, sysram_2_2_enter_non_retention},
    {0x0402C000, sysram_2_3_force_power_down, sysram_2_3_force_power_on, sysram_2_3_enter_non_retention},
    {0x04030000, sysram_3_0_force_power_down, sysram_3_0_force_power_on, sysram_3_0_enter_non_retention},
    {0x04034000, sysram_3_1_force_power_down, sysram_3_1_force_power_on, sysram_3_1_enter_non_retention},
    {0x04038000, sysram_3_2_force_power_down, sysram_3_2_force_power_on, sysram_3_2_enter_non_retention},
    {0x0403C000, sysram_3_3_force_power_down, sysram_3_3_force_power_on, sysram_3_3_enter_non_retention},
    {0x04040000, sysram_4_0_force_power_down, sysram_4_0_force_power_on, sysram_4_0_enter_non_retention},
    {0x04048000, sysram_4_1_force_power_down, sysram_4_1_force_power_on, sysram_4_1_enter_non_retention},
    {0x04050000, sysram_5_0_force_power_down, sysram_5_0_force_power_on, sysram_5_0_enter_non_retention},
    {0x04058000, sysram_5_1_force_power_down, sysram_5_1_force_power_on, sysram_5_1_enter_non_retention},
};


static int hw_latency_time_32k;
ATTR_ZIDATA_IN_TCM volatile static uint32_t infra_pd_force_on_resource_table[SPM_FORCE_ON_REQUEST_MAX];
ATTR_ZIDATA_IN_TCM volatile uint32_t infra_pd_force_on_status;

void manual_spm_write_im(uint32_t addr, uint32_t data);
uint32_t manual_spm_read_im(uint32_t addr);
static void spm_mtcmos_audio_sys_on(void);
static void spm_mtcmos_audio_sys_off(void);
static void spm_mtcmos_conn_top_off_on(void);
static void spm_mtcmos_conn_top_off_off(void);
static void spm_mtcmos_conn_zigbee_on(void);
#ifdef CONFIG_AIR_SPM_STANDBY_MODE_ENABLE
static void spm_mtcmos_conn_zigbee_off(void);
#endif
static void spm_mtcmos_perisys_on(void);
static void spm_mtcmos_perisys_off(void);
static void spm_mtcmos_rtcsys_on(void);
static void spm_mtcmos_rtcsys_off(void);

void manual_spm_write_im(uint32_t addr, uint32_t data)
{
    *SPM_TOP_PCM_IM_HOST_RW_PTR = 0x01010000 | addr;
    *SPM_TOP_PCM_IM_HOST_RW_DAT = data;

    //printk("Load IM *SPM_TOP_PCM_IM_HOST_RW_PTR=0x%x\r\n", *SPM_TOP_PCM_IM_HOST_RW_PTR);
    //printk("Load IM *SPM_TOP_PCM_IM_HOST_RW_DAT=0x%x\r\n", *SPM_TOP_PCM_IM_HOST_RW_DAT);
    //printk("Load IM data=0x%x\r\n", data);
    return;
}

uint32_t manual_spm_read_im(uint32_t addr)
{
    uint32_t data;
    *SPM_TOP_PCM_IM_HOST_RW_PTR = 0x01000000 | addr;
    data = *SPM_TOP_PCM_IM_HOST_RW_DAT;

    //printk("Read IM *SPM_TOP_PCM_IM_HOST_RW_PTR=0x%x\r\n", *SPM_TOP_PCM_IM_HOST_RW_PTR);
    //printk("Read IM *SPM_TOP_PCM_IM_HOST_RW_DAT=0x%x\r\n", data);

    *SPM_TOP_PCM_IM_HOST_RW_PTR = 0;
    return (data);
}

int spm_init(void)
{
    //printk("hal_spm_init start\n", 0);
    uint32_t status;
    int result = 0, i;

    // init spm setting
    *SPM_TOP_PCM_CON0 = 0x0B160000 | 0x10; // pcm sw_rst
    hal_gpt_delay_us(10);
    *SPM_TOP_PCM_CON0 = 0x0B160000; // release pcm sw_rst
    hal_gpt_delay_us(10);
    // SET_PCM_EVENT_VEC
    // [6]: immediate mode, immediate jump to the vector while event occurred <= give 0
    // [5]: resume mode, after finishing vector, pcm(the processor) jump to sleep state again <= give 1
    // [4:0]: event number

    /* Load PCM_EVENT_VECTOR[0-7] */
    *SPM_TOP_PCM_EVENT_VECTOR0 = pcm_event_vector_parameter[0];
    *SPM_TOP_PCM_EVENT_VECTOR1 = pcm_event_vector_parameter[1];
    *SPM_TOP_PCM_EVENT_VECTOR2 = pcm_event_vector_parameter[2];
    *SPM_TOP_PCM_EVENT_VECTOR3 = pcm_event_vector_parameter[3];
    *SPM_TOP_PCM_EVENT_VECTOR4 = pcm_event_vector_parameter[4];
    *SPM_TOP_PCM_EVENT_VECTOR5 = pcm_event_vector_parameter[5];
    *SPM_TOP_PCM_EVENT_VECTOR6 = pcm_event_vector_parameter[6];
    *SPM_TOP_PCM_EVENT_VECTOR7 = pcm_event_vector_parameter[7];

    //PCM KICK
    *SPM_TOP_POWER_ON_VAL0 = 0x0;
    *SPM_TOP_POWER_ON_VAL1 = 0x84;
    *SPM_TOP_PCM_REG_DATA_INI = *SPM_TOP_POWER_ON_VAL0 | 0x1; // [0]: sc_xo_cg_en default =1
    *SPM_TOP_PCM_PWR_IO_EN = 0x00010000; // for R0
    *SPM_TOP_PCM_PWR_IO_EN = 0x00000000;
    *SPM_TOP_PCM_REG_DATA_INI = *SPM_TOP_POWER_ON_VAL1;
    *SPM_TOP_PCM_PWR_IO_EN = 0x00800000; // for R7
    *SPM_TOP_PCM_PWR_IO_EN = 0x00000000;
    *SPM_TOP_CLK_SETTLE =0x3; /*TBD*/
    *SPM_TOP_PCM_PWR_IO_EN = 0x1;
    *SPM_TOP_SLEEP_WAKEUP_EVENT_MASK = 0x0;           // unmask all AP wakeup event

    /* Init IM Length and pointer */
    *SPM_TOP_PCM_IM_LEN = PCM_IM_MAX_LENGTH;
    *SPM_TOP_PCM_IM_PTR = (uint32_t)spm_im;
    /* Manual load spm code */
    for (i = 0; i < PCM_IM_MAX_LENGTH; i++) {
        manual_spm_write_im(i, spm_im[i]);
    }

    *SPM_TOP_PCM_CON1 = 0x0B169C49; // (if code had already manual filled into instruction memory)
    *SPM_TOP_PCM_CON0 = 0x0B160000 | 0x2; // [1]: kick IM process; kick(load) IM first, kick PCM before WFI

    /* Wait ready state */
    do {
          status = (*SPM_CFG_PCM_FSM_STA >> 9) & 0x1;
    } while (status != 0x01);

    *SPM_TOP_PCM_PWR_IO_EN = 0x1; // enable R0 & R7 output

    *SPM_CFG_SEQUENCER_26M_REG_1 = 0x1B;    /* 27 * 38ns > 1us */
    *SPM_CFG_SEQUENCER_32K_REG_1 = 0x32;    /* rg_active_guard_time = 50 * 30.52us > 1500us */
    *SPM_CFG_SEQUENCER_32K_REG_2 = 0x1A;    /* rg_sleep_guard_time = 26 * 30.52us > 780us */
    *SPM_CFG_SEQUENCER_32K_REG_3 = 0x0;     /* pmu_en_delay = 0,osc_en_delay = 0,xo_en_delay = 0 */
    *SPM_CFG_SEQUENCER_32K_REG_4 = 0x32;    /* vcore/xo settle_time > 1500us/780us */

    hw_latency_time_32k = spm_latency_time_checking(); /* SPM Latency Time */

    spm_unmask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_ZB_TIMER);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_AURX);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_AUTX);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_ZB_INT);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_BT_PLAYEN);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_I3C0);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_TIMER);

    spm_unmask_wakeup_source(SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, HAL_SPM_INFRA_WAKEUP_SOURCE_SPM_SW_WAKEUP);

#if 0
    //turn off usb sram
    *USB_SRAM_CONTROL = 0x100; //iso_b = 1
    *USB_SRAM_CONTROL = 0x101; //reten 2 mode
#endif

#if 0
    /* Set AO_BACKUP_BASE_ADDR to SPM & register AO bakcup format */
#endif

#if 0
    /* Default SPM IRQ disable */
#endif


    for (i = 0; i < PCM_IM_MAX_LENGTH; i++) {
        /* Check SPM Code */
        if (manual_spm_read_im(i) != spm_im[i]) {
            printk("SPM Code loading Fail\r\n");
            return (result++);
        }
    }

    // Disable request DCXO in sleep mode , set 0x1 when audio is not sleep at sleep mode *CONN_AUDIO_ABB_XO_SIDEBAND = 0x0;
    *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0;

    /* SPM Kick Start */
    *SPM_TOP_PCM_CON0 = 0x0B160103;

    printk("hal_spm_init finish\n");
    return (result);
}

bool spm_get_clock_ready(spm_clk_rdy_t spm_clk_rdy)
{
    return (0x1 & (*SPM_CFG_CLOCK_RDY >> (spm_clk_rdy * 8)));
}

void spm_force_sleep_state(spm_request_t user, spm_sleep_state_t state, spm_ctrl_t enable)
{
    uint32_t mask;
    uint32_t spm_state_control_bit;
    volatile uint32_t *state_control_rg;
    static uint8_t resource_control[SPM_STATE_MAX];

    spm_state_control_bit = 0x1 << ((state % 4) * 8);
    state_control_rg = (state % 4) ? SPM_CFG_SPM_STATE_CONTROL_1 : SPM_CFG_SPM_STATE_CONTROL_0;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (enable == SPM_ENABLE) {
        resource_control[state] |= (1 << user);
    } else {
        resource_control[state] &= ~(1 << user);
    }

    if (resource_control[state] == 0) {
        *state_control_rg &= ~spm_state_control_bit;
    } else {
        *state_control_rg |= spm_state_control_bit;
    }

    hal_nvic_restore_interrupt_mask(mask);
    return;
}

int spm_latency_time_checking(void)
{
    int latency_time_32k = 0;
    float hw_buffer_time_ms = 1;
    float hw_buffer_time_32k = 0;
    float hw_buffer_time_freq = 32.768;

    float latency_time_max_ms = 10 - 2 - 1; /* MaximumIdleTime - DEEP_SLEEP_SW_BACKUP_RESTORE_TIME - 1, due to hw_latency_time_ms is rounded up in port_tick.c */
    float latency_time_min_ms = 2; /* Minimun of Sleep/Wakeup time */
    float latency_time_max_32k;
    float latency_time_min_32k;

    uint32_t xo_en_delay, osc_en_delay, pmu_en_delay, en_delay_max;

    uint32_t latency_time_check;

    printk("[spm_latency_time_checking] SPM_CFG_SEQUENCER_32K_REG_1 is 0x%08x", *SPM_CFG_SEQUENCER_32K_REG_1);
    printk("[spm_latency_time_checking] SPM_CFG_SEQUENCER_32K_REG_2 is 0x%08x", *SPM_CFG_SEQUENCER_32K_REG_2);
    printk("[spm_latency_time_checking] SPM_CFG_SEQUENCER_32K_REG_3 is 0x%08x", *SPM_CFG_SEQUENCER_32K_REG_3);
    printk("[spm_latency_time_checking] SPM_CFG_SEQUENCER_32K_REG_4 is 0x%08x", *SPM_CFG_SEQUENCER_32K_REG_4);

    osc_en_delay = ((*SPM_CFG_SEQUENCER_32K_REG_3 >> 0) & 0xFF);
    pmu_en_delay = ((*SPM_CFG_SEQUENCER_32K_REG_3 >> 8) & 0xFF);
    xo_en_delay = ((*SPM_CFG_SEQUENCER_32K_REG_3 >> 16) & 0xFF);
    en_delay_max = osc_en_delay;

    if (pmu_en_delay >= en_delay_max) {
        en_delay_max = pmu_en_delay;
    } else if (xo_en_delay >= en_delay_max) {
        en_delay_max = xo_en_delay;
    }

    hw_buffer_time_32k = (hw_buffer_time_ms / (1 / (hw_buffer_time_freq)));
    latency_time_max_32k = (latency_time_max_ms / (1 / (hw_buffer_time_freq)));
    latency_time_min_32k = (latency_time_min_ms / (1 / (hw_buffer_time_freq)));

    latency_time_check = (*SPM_CFG_SEQUENCER_32K_REG_2 + en_delay_max + *SPM_CFG_SEQUENCER_32K_REG_4);

    if ((float)(latency_time_check) + hw_buffer_time_32k < latency_time_min_32k || (float)(latency_time_check) + hw_buffer_time_32k > latency_time_max_32k) {
        // printk("spm_latency_time_checking is error, max of latency time is %d in 32k", (int)latency_time_max_32k);
        assert(0);
    } else {
        latency_time_32k = (int)(latency_time_check) + (int)(hw_buffer_time_32k);
    }

    printk("[spm_latency_time_checking] latency_time_32k is %d", latency_time_32k);

    return latency_time_32k;
}

void spm_debug_io(unsigned int debug_bus)
{
    printk("enter spm_debug_io\r\n");
    /* SPM Clock Force to 26M bar, *SPM_CLK_SW_CON &= ~(1 << 0) */
    //*SPM_CLK_SW_CON &= ~(1 << 0);
    //Set GPIO
#if 0
    hal_pinmux_set_function(32, 13);
    hal_pinmux_set_function(30, 13);
    hal_pinmux_set_function(31, 13);
    hal_pinmux_set_function(26, 13);

    hal_pinmux_set_function(27, 13);
    hal_pinmux_set_function(5, 13);
    hal_pinmux_set_function(6, 13);
    hal_pinmux_set_function(7, 13);

    hal_pinmux_set_function(8, 13);
    hal_pinmux_set_function(9, 13);
    hal_pinmux_set_function(10, 13);
    hal_pinmux_set_function(11, 13);

    hal_pinmux_set_function(12, 13);
    hal_pinmux_set_function(13, 13);
    hal_pinmux_set_function(14, 13);
    hal_pinmux_set_function(15, 13);
#endif

    //*TOP_DEBUG(0xA2010008) = 0x14;
    *(volatile uint32_t *)(0x42010108) = 0x13;
    //*INFRA_CFG_DBGMON__AO_DBGMON_SEL(0xA2200030)  = 0x0
    *(volatile uint32_t *)(0x422F0030) = 0x0;
    //*SPM_DEBUG_CON(0xA21103D4)=0x1;
    *SPM_CFG_SPM_DEBUG_CON = 0x1;
    //*SPM_SPM_DEBUG_SELECT = debug_bus;
    *SPM_CFG_SPM_DEBUG_SELECT = debug_bus;

    /* Debug bus restore */
    *SPM_CFG_SPM_CFG_DUMMY_REG_A |= 0x1;
    printk("[SLP] SPM_CFG_SPM_CFG_DUMMY_REG_A=0x%08x\r\n", *SPM_CFG_SPM_CFG_DUMMY_REG_A);

    printk("spm_debug_io SPM_CFG_SPM_DEBUG_SELECT=0x%x\r\n\r\n", *SPM_CFG_SPM_DEBUG_SELECT);

}

ATTR_TEXT_IN_TCM_RETENTION void spm_control_mtcmos_internal(spm_mtcmos_type_t mtcmos, spm_mtcmos_ctrl_t ctrl)
{
    bool clock_old_status;

    if( mtcmos == SPM_MTCMOS_AUDIO_SYS ){
        clock_old_status = hal_clock_is_enabled(HAL_CLOCK_CG_AUD_INTBUS);
        if (clock_old_status == false) {
            hal_clock_enable(HAL_CLOCK_CG_AUD_INTBUS);
        }

        if( ctrl == SPM_MTCMOS_PWR_ENABLE ){
            /* MTCMOS AUDIO PWR ON */
            spm_mtcmos_audio_sys_on();
        }else if( ctrl == SPM_MTCMOS_PWR_DISABLE ){
            /* MTCMOS AUDIO PWR OFF */
            spm_mtcmos_audio_sys_off();
        }

        if (clock_old_status == false) {
            hal_clock_disable(HAL_CLOCK_CG_AUD_INTBUS);
        }
        return;
    }

    if( mtcmos == SPM_MTCMOS_CONN_TOP_OFF ){
        clock_old_status = hal_clock_is_enabled(HAL_CLOCK_CG_BT_MAC);
        if (clock_old_status == false) {
            hal_clock_enable(HAL_CLOCK_CG_BT_MAC);
        }

        if( ctrl == SPM_MTCMOS_PWR_ENABLE ){
            /* MTCMOS CONN_TOP_OFF PWR ON */
            spm_mtcmos_conn_top_off_on();
        }else if(ctrl == SPM_MTCMOS_PWR_DISABLE){
            /* MTCMOS CONN_TOP_OFF PWR OFF */
            spm_mtcmos_conn_top_off_off();
        }

        if (clock_old_status == false) {
            hal_clock_disable(HAL_CLOCK_CG_BT_MAC);
        }
        return;
    }

    if( mtcmos == SPM_MTCMOS_CONN_ZIGBEE ){
        clock_old_status = hal_clock_is_enabled(HAL_CLOCK_CG_BT_MAC);
        if (clock_old_status == false) {
            hal_clock_enable(HAL_CLOCK_CG_BT_MAC);
        }

        if( ctrl == SPM_MTCMOS_PWR_ENABLE ){
            /* MTCMOS CONN_ZIGBEE PWR ON */
            spm_mtcmos_conn_zigbee_on();
            *SPM_CFG_CONN_MTCMOS_ENABLE |= 0x2;

        }else if( ctrl == SPM_MTCMOS_PWR_DISABLE ){
            /* MTCMOS CONN_ZIGBEE PWR OFF */
        #ifdef CONFIG_AIR_SPM_STANDBY_MODE_ENABLE
            spm_mtcmos_conn_zigbee_off();
        #endif
            *SPM_CFG_CONN_MTCMOS_ENABLE &= 0xFFFFFFFD;

        }

        if (clock_old_status == false) {
            hal_clock_disable(HAL_CLOCK_CG_BT_MAC);
        }
        return;
    }


    if( mtcmos == SPM_MTCMOS_PERISYS ){

        if( ctrl == SPM_MTCMOS_PWR_ENABLE ){
            /* MTCMOS PERISYS PWR ON */
            spm_mtcmos_perisys_on();
        }else if( ctrl == SPM_MTCMOS_PWR_DISABLE ){
            /* MTCMOS PERISYS PWR OFF */
            spm_mtcmos_perisys_off();
        }

        return;
    }

    if( mtcmos == SPM_MTCMOS_RTCSYS ){

        if( ctrl == SPM_MTCMOS_PWR_ENABLE ){
            /* MTCMOS RTCSYS PWR ON */
            spm_mtcmos_rtcsys_on();
        }else if( ctrl == SPM_MTCMOS_PWR_DISABLE ){
            /* MTCMOS RTCSYS PWR OFF */
            spm_mtcmos_rtcsys_off();
        }

        return;
    }
}

ATTR_TEXT_IN_TCM_RETENTION uint32_t spm_control_mtcmos(spm_mtcmos_type_t mtcmos, spm_mtcmos_ctrl_t ctrl)
{
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    if(mtcmos == SPM_MTCMOS_AUDIO_SYS){
        if(ctrl == SPM_MTCMOS_PWR_ENABLE){
            mtcmos_resource.audio++;
            if(mtcmos_resource.audio == 1){
                spm_control_mtcmos_internal(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_ENABLE);
            }
        }else{
            if(mtcmos_resource.audio == 0){
                spm_control_mtcmos_internal(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
                hal_nvic_restore_interrupt_mask(mask);
                return (mtcmos_resource.audio);
            }
            mtcmos_resource.audio--;
            if(mtcmos_resource.audio == 0){
                spm_control_mtcmos_internal(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
            }
        }
        hal_nvic_restore_interrupt_mask(mask);
        if(mtcmos_resource.audio == 0xFF ){
            printk("[SLP] AUDIO pwr on count is overflow.\r\n");
            //assert(0);
        }
        return (mtcmos_resource.audio);
    }

    if(mtcmos == SPM_MTCMOS_CONN_TOP_OFF){
        if(ctrl == SPM_MTCMOS_PWR_ENABLE){
            mtcmos_resource.conn_top_off++;
            if(mtcmos_resource.conn_top_off == 1){
                spm_control_mtcmos_internal(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_ENABLE);
            }
        }else{
            if(mtcmos_resource.conn_top_off == 0){
                printk("[SLP] CONN_TOP_OFF pwr off controlled by SPM.\r\n");
                spm_control_mtcmos_internal(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_DISABLE);
                hal_nvic_restore_interrupt_mask(mask);
                return (mtcmos_resource.conn_top_off);
            }
            mtcmos_resource.conn_top_off--;
            if(mtcmos_resource.conn_top_off == 0){
                printk("[SLP] CONN_TOP_OFF pwr off controlled by SPM.\r\n");
                spm_control_mtcmos_internal(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_DISABLE);
            }
        }
        hal_nvic_restore_interrupt_mask(mask);
        if(mtcmos_resource.conn_top_off == 0xFF ){
            printk("[SLP] CONN_TOP_OFF pwr on count is overflow.\r\n");
            //assert(0);
        }
        return (mtcmos_resource.conn_top_off);
    }

    if(mtcmos == SPM_MTCMOS_CONN_ZIGBEE){
        if(ctrl == SPM_MTCMOS_PWR_ENABLE){
            /* Status of Conn MTCMOS is always on when cmsys pwr on ZB MTCMOS. (Already confirmed with BT)  */
            mtcmos_resource.conn_zigbee++;
            if(mtcmos_resource.conn_zigbee == 1){
                spm_control_mtcmos_internal(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_ENABLE);
            }
        }else{
            if(mtcmos_resource.conn_zigbee == 0){
                spm_control_mtcmos_internal(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_DISABLE);
                hal_nvic_restore_interrupt_mask(mask);
                return (mtcmos_resource.conn_zigbee);
            }
            mtcmos_resource.conn_zigbee--;
            if(mtcmos_resource.conn_zigbee == 0){
                spm_control_mtcmos_internal(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_DISABLE);
            }
        }
        hal_nvic_restore_interrupt_mask(mask);
        if(mtcmos_resource.conn_zigbee == 0xFF ){
            printk("[SLP] CONN_ZIGBEE pwr on count is overflow.\r\n");
            //assert(0);
        }
        return (mtcmos_resource.conn_zigbee);
    }

    if(mtcmos == SPM_MTCMOS_PERISYS){
        if(ctrl == SPM_MTCMOS_PWR_ENABLE){
            mtcmos_resource.perisys++;
            if(mtcmos_resource.perisys == 1){
                spm_control_mtcmos_internal(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_ENABLE);
            }
        }else{
            if(mtcmos_resource.perisys == 0){
                spm_control_mtcmos_internal(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
                hal_nvic_restore_interrupt_mask(mask);
                return (mtcmos_resource.perisys);
            }
            mtcmos_resource.perisys--;
            if(mtcmos_resource.perisys == 0){
                spm_control_mtcmos_internal(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
            }
        }
        hal_nvic_restore_interrupt_mask(mask);
        if(mtcmos_resource.perisys == 0xFF ){
            printk("[SLP] PERISYS pwr on count is overflow.\r\n");
            //assert(0);
        }
        return (mtcmos_resource.perisys);
    }

    if(mtcmos == SPM_MTCMOS_RTCSYS){
        if(ctrl == SPM_MTCMOS_PWR_ENABLE){
            mtcmos_resource.rtcsys++;
            if(mtcmos_resource.rtcsys == 1){
                spm_control_mtcmos_internal(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_ENABLE);
            }
        }else{
            if(mtcmos_resource.rtcsys == 0){
                spm_control_mtcmos_internal(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_DISABLE);
                hal_nvic_restore_interrupt_mask(mask);
                return (mtcmos_resource.rtcsys);
            }
            mtcmos_resource.rtcsys--;
            if(mtcmos_resource.rtcsys == 0){
                spm_control_mtcmos_internal(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_DISABLE);
            }
        }
        hal_nvic_restore_interrupt_mask(mask);
        if(mtcmos_resource.rtcsys == 0xFF ){
            printk("[SLP] RTCSYS pwr on count is overflow.\r\n");
            //assert(0);
        }
        return (mtcmos_resource.rtcsys);
    }

    hal_nvic_restore_interrupt_mask(mask);
    return SPM_MTCMOS_PWR_ERROR;

}

void spm_mask_wakeup_source(volatile uint32_t *wakeup_source_mask_rg, uint32_t wakeup_source)
{
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (wakeup_source == HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL) {
        *wakeup_source_mask_rg = 0xFFFFFFFF;
    } else {
        *wakeup_source_mask_rg |= (0x1 << wakeup_source);
    }

    hal_nvic_restore_interrupt_mask(mask);
}

void spm_unmask_wakeup_source(volatile uint32_t *wakeup_source_mask_rg, uint32_t wakeup_source)
{
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (wakeup_source == HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL) {
        *wakeup_source_mask_rg = 0x0;
    } else {
        *wakeup_source_mask_rg &= ~(0x1 << wakeup_source);
    }

    hal_nvic_restore_interrupt_mask(mask);
}

void spm_enter_usb_suspend(void)
{
    /* Lock extend sleep */
    hal_sleep_manager_lock_extslp(SLEEP_LOCK_EXTEND_USB);

    /* Request INFRA_PD off */
#if defined(AIR_PD_DOMAIN_CONTROL_ENABLE)
    pd_domain_control_enter_sleep(INFRA_PD_MODULE_USB);
#endif /* AIR_PD_DOMAIN_CONTROL_ENABLE */

    /* Unmask USB wakeup source for INFRA_PD */
    spm_unmask_wakeup_source(SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, HAL_SPM_INFRA_WAKEUP_SOURCE_USB_32K_RES);
}

void spm_leave_usb_suspend(void)
{
    /* Mask USB wakeup source for INFRA_PD */
    spm_mask_wakeup_source(SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, HAL_SPM_INFRA_WAKEUP_SOURCE_USB_32K_RES);

    /* Unlock extend sleep */
    hal_sleep_manager_unlock_extslp(SLEEP_LOCK_EXTEND_USB);
}

void spm_bt_enter_standby_stage(void)
{
    /* Mask BT_TIMER wakeup source for Conn
     * Mask HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_BT_TIMER & HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_TIMER for CMSYS
     */
    spm_mask_wakeup_source(SPM_CFG_CONN_WAKEUP_SOURCE_MASK, HAL_SPM_CONN_WAKEUP_SOURCE_BT_TIMER);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_BT_TIMER);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_TIMER);

    /* Mask SW_WAKEUP wakeup source for Conn */
    spm_mask_wakeup_source(SPM_CFG_CONN_WAKEUP_SOURCE_MASK, HAL_SPM_CONN_WAKEUP_SOURCE_SPM_SW_WAKEUP);

    *SPM_CFG_CONN_WAKEUP_EVENT = 0x0;

    /* Ignore CONN Active */
    *SPM_CFG_IGNORE_CPU_ACTIVE |= (0x1 << 24);

    /* Conn MTCMOS pwr off */
    #ifdef CONFIG_AIR_SPM_STANDBY_MODE_ENABLE
    spm_control_mtcmos(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_DISABLE);
    #endif
    spm_control_mtcmos(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_DISABLE);

    /* PWR Down Sysram6 whne entering SLP or ExtSLP mode */
    spm_bt_sram_16k_power_down();
}

void spm_bt_leave_standby_stage(void)
{
    /* Ignore CONN Active */
    *SPM_CFG_IGNORE_CPU_ACTIVE &= (~(0x1 << 24));

    *SPM_CFG_CONN_WAKEUP_EVENT = 0x1;

    /* Unmask BT_TIMER wakeup source for Conn
     * Unmask HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_BT_TIMER for CMSYS
     */
    spm_unmask_wakeup_source(SPM_CFG_CONN_WAKEUP_SOURCE_MASK, HAL_SPM_CONN_WAKEUP_SOURCE_BT_TIMER);
    spm_unmask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_CONNSYS_BT_TIMER);
    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_TIMER);

    /* Mask SW_WAKEUP wakeup source for Conn */
    spm_unmask_wakeup_source(SPM_CFG_CONN_WAKEUP_SOURCE_MASK, HAL_SPM_CONN_WAKEUP_SOURCE_SPM_SW_WAKEUP);

    /* PWR On Sysram6 whne entering SLP or ExtSLP mode */
    spm_bt_sram_16k_power_on();

    /* Conn MTCMOS pwr on */
    spm_control_mtcmos(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_ENABLE);

    /* IF need Zigbee, Pwr on by IP owner. */
}

void spm_mtcmos_force_on(spm_mtcmos_force_on_t processor, spm_ctrl_t enable){

    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);

    if(enable){
        *SPM_CFG_RESOURCE_CONTROL_0 |= (1 << processor);
        *SPM_CFG_IGNORE_CPU_ACTIVE |= (1 << processor);
    }else{
        *SPM_CFG_RESOURCE_CONTROL_0 &= ~(1 << processor);
        *SPM_CFG_IGNORE_CPU_ACTIVE &= ~(1 << processor);
    }

    hal_nvic_restore_interrupt_mask(mask);

    printk("[SLP][Force On] Force On Status: 0x%08x\r\n", *SPM_CFG_RESOURCE_CONTROL_0);
}

void spm_mtcmos_force_on_infra_pd(spm_mtcmos_force_on_request_t request_handle, spm_ctrl_t enable){

    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);

    if(enable == SPM_ENABLE){

        if((infra_pd_force_on_resource_table[request_handle] != 0) && (!infra_pd_force_on_status)){
            printk("[SLP][Force On PD][RG(0x%08x)] Force Status(0x%08x) is not equal to Handle(%d) Request(%d)\r\n"
                , *SPM_CFG_RESOURCE_CONTROL_0
                , infra_pd_force_on_status
                , request_handle
                , infra_pd_force_on_resource_table[request_handle]
            );
            hal_nvic_restore_interrupt_mask(mask);
            assert(0);
            return;
        }

        if( ((infra_pd_force_on_resource_table[request_handle] == 0) && (!infra_pd_force_on_status)) ){

            infra_pd_force_on_resource_table[request_handle]++;
            infra_pd_force_on_status |= (1 << request_handle);
            spm_mtcmos_force_on(INFRA_PD_FORCE_ON, SPM_ENABLE);
            hal_nvic_restore_interrupt_mask(mask);

            printk("[SLP][Force On PD] Handle:%d, Request:%d, Force Status:0x%08x, RG:0x%08x\r\n"
                , request_handle
                , infra_pd_force_on_resource_table[request_handle]
                , infra_pd_force_on_status
                , *SPM_CFG_RESOURCE_CONTROL_0
            );

            return;
        }

        infra_pd_force_on_resource_table[request_handle]++;
        infra_pd_force_on_status |= (1 << request_handle);

        if(infra_pd_force_on_resource_table[request_handle] >= 0xFF){
            printk("[SLP][Force On PD][Force Status(0x%08x)][RG(0x%08x)] Handle(%d) Request(%d) is overflow.\r\n"
                , infra_pd_force_on_status
                , *SPM_CFG_RESOURCE_CONTROL_0
                , request_handle
                , infra_pd_force_on_resource_table[request_handle]
            );
            hal_nvic_restore_interrupt_mask(mask);
            assert(0);

            return;
        }

    }else if (enable == SPM_DISABLE){

        if(infra_pd_force_on_resource_table[request_handle] <= 0 || (!infra_pd_force_on_status) ){
            printk("[SLP][Force On PD][RG(0x%08x)][Force Status(0x%08x)][Handle(%d)][Request(%d)] Disable force_on is not paired.\r\n"
                , *SPM_CFG_RESOURCE_CONTROL_0
                , infra_pd_force_on_status
                , request_handle
                , infra_pd_force_on_resource_table[request_handle]
            );

            hal_nvic_restore_interrupt_mask(mask);
            assert(0);
            return;
        }

        if((--infra_pd_force_on_resource_table[request_handle]) == 0){
            infra_pd_force_on_status &= ~(1 << request_handle);
        }

        if(infra_pd_force_on_status == 0){
            spm_mtcmos_force_on(INFRA_PD_FORCE_ON, SPM_DISABLE);
        }

    }else{
        printk("[SLP][Force On PD][RG(0x%08x)][Force Status(0x%08x)][Handle(%d)][Request(%d)] Parameter is error.\r\n"
            , *SPM_CFG_RESOURCE_CONTROL_0
            , infra_pd_force_on_status
            , request_handle
            , infra_pd_force_on_resource_table[request_handle]
        );
        assert(0);
    }
    hal_nvic_restore_interrupt_mask(mask);

    printk("[SLP][Force On PD] Handle:%d, Request:%d, Force Status:0x%08x, RG:0x%08x\r\n"
    , request_handle
    , infra_pd_force_on_resource_table[request_handle]
    , infra_pd_force_on_status
    , *SPM_CFG_RESOURCE_CONTROL_0
    );

}

void spm_check_debug_bus(void)
{
    printk("enter spm_check_debug_bus\r\n");
    spm_debug_io(0x43424342);

    unsigned int i = 0, delay = 0;

    /* SPM Clock Force to 26M bar, *SPM_CLK_SW_CON &= ~(1 << 0) */
    //*SPM_CLK_SW_CON &= ~(1 << 0);
    printk("Check SPM_TOP_STATE_STATUS\r\n");
    while (1) {
        *SPM_TOP_STATE_STATUS = i;
        for (delay = 0; delay < 512; delay++);
        if (i++ >= 512) {
            i = 0;
        }
    }
}

void spm_mtcmos_default_init(void){
    uint32_t rtctemp;
    rtctemp = ((*RTCSYS_PWR_CTRL >> 16) & 0x1);
    printk("[SLP][HW Default] PWR_STATUS is 0x%08X. RTC PWR STATUS = 0x%x, value = 0x%x\r\n"
        , *SPM_CFG_PWR_STATUS_2ND
        , rtctemp
        , *RTCSYS_PWR_CTRL
    );
    // spm_control_mtcmos(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_ENABLE);
    infra_irtx_sram_power_down();
    audio_memif_sram_power_down();
    cmsys_rom_0_sram_power_down();
    cmsys_rom_1_sram_power_down();
    perisys_usb_sram_power_down();
    spm_control_mtcmos(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos(SPM_MTCMOS_RTCSYS, SPM_MTCMOS_PWR_DISABLE);

    rtctemp = ((*RTCSYS_PWR_CTRL >> 16) & 0x1);
    printk("[SLP][SW Default Status] RTC PWR STATUS = 0x%x, value = 0x%x\r\n"
        , rtctemp
        , *RTCSYS_PWR_CTRL
    );
}

#ifdef SPM_DVT_TEST
void spm_fpga_mtcmos_all_on(void){

    printk("[SPM] PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);
    printk("[SPM] MTCMOS default on\r\n");
    spm_mtcmos_conn_zigbee_on();
    printk("[SPM] SPM_MTCMOS_CONN_ZIGBEE ON, PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);
    //spm_control_mtcmos(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_ENABLE);
    spm_mtcmos_perisys_on();
    printk("[SPM] SPM_MTCMOS_PERISYS ON, PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);

}
#endif

#if 0
void infra_control_dvt(){

    uint32_t mask, spm_irq = *SPM_CFG_PCM_SW_INT_STATE;

   // spm_debug_io(0x43424544);

    //SPM->CM4_WAKEUP_SOURCE_MASK = 0xFFFFFFFE;
    //SPM->DSP_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK = 0xFFFFFFFE;
    *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;
    *SPM_CFG_CONN_WAKEUP_SOURCE_MASK = 0xFFFFFFFF;

    //SPM->SPM_STATE_CONTROL_0_b.LOCK_ON_S1 = 1;
    //SPM->SPM_STATE_CONTROL_0_b.LOCK_ON_S3 = 1;
    //SPM->SPM_STATE_CONTROL_0 = 0;
    //SPM->RESOURCE_CONTROL_0_b.INFRA_FORCE_ON = 1;

    //spm_mtcmos_perisys_off();
    //printk("[SLP] SPM_MTCMOS_PERISYS OFF, PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);

    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x1010000;    //IGNORE RISCV/INFRA/CONN ACTIVE
    //*SPM_CFG_IGNORE_CPU_ACTIVE = 0x0;    //IGNORE RISCV/INFRA/CONN ACTIVE
    printk("*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);
    *RISCV_DEEP_SLEEP = 0xFFFFFFFF;
    printk("*RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);

    spm_mtcmos_perisys_off();

    printk("[SLP] Default Status, PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);

    printk("Enter deep sleep\r\n");

    /* Lock S1 */
    //*SPM_CFG_SPM_STATE_CONTROL_0 = 0x1;
    /* Lock S3 */
    //*SPM_CFG_SPM_STATE_CONTROL_0 = 0x10000;
    printk("*SPM_CFG_SPM_STATE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_0, *SPM_CFG_SPM_STATE_CONTROL_0);
    hal_sleep_manager_set_sleep_time( 5000000);

while(1){

        printk("[1]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        printk("[1]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
        printk("[1]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
        printk("[1]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);

        *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
        /* INFRA pwr off requested by SW, flag cleared by SPM */
        *SPM_CFG_INFRA_DEEP_SLEEP = 0x1;             // INFRA_DEEP_SLEEP=1
        //printk("[1]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //hal_gpt_delay_ms(1000);
        printk("[2]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        printk("[2]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
        printk("[2]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
        printk("[2]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);


        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0;        //for sleep test, need BT or Audio Control.
        *SPM_TOP_STATE_STATUS = 0xE2;
        //printk("SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND(0x%08x)=0x%x \r\n", (uint32_t)SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND, *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND);
        hal_nvic_save_and_set_interrupt_mask(&mask);

        //for (int i = 0; i < 53; i++) {
        //    if (hal_nvic_get_pending_irq(i) == 1) {
        //        //printk("pending_irq:%d\r\n", i);
        //        printk("pending_irq:%d\r\n", i);
        //        *SPM_TOP_STATE_STATUS = i;
        //        hal_nvic_clear_pending_irq(i);
        //    }
        //}



        *SPM_TOP_STATE_STATUS = 0xE3;

        //hal_nvic_clear_pending_irq(22); //GPT_TIMER

        sleep_management_enter_deep_sleep(0);
        *SPM_TOP_STATE_STATUS = 0xEE;

        //printk("[1]*(volatile uint32_t*)(0x4215031C)=0x%08x\r\n", *(volatile uint32_t*)(0x4215031C));
        //printk("[1]*(volatile uint32_t*)(0x42150318)=0x%08x\r\n", *(volatile uint32_t*)(0x42150318));
        //printk("[1]*(volatile uint32_t*)(0x42150310)=0x%08x\r\n", *(volatile uint32_t*)(0x42150310));
        //printk("[1]*(volatile uint32_t*)(0x42150308)=0x%08x\r\n", *(volatile uint32_t*)(0x42150308));
        //printk("[1]*(volatile uint32_t*)(0x42150300)=0x%08x\r\n", *(volatile uint32_t*)(0x42150300));
        //printk("[1]*(volatile uint32_t*)(0x4215030C)=0x%08x\r\n", *(volatile uint32_t*)(0x4215030C));
        //printk("[1]*(volatile uint32_t*)(0x42150C00)=0x%08x\r\n", *(volatile uint32_t*)(0x42150C00));
        //printk("[1]*(volatile uint32_t*)(0x42150C04)=0x%08x\r\n", *(volatile uint32_t*)(0x42150C04));
        //printk("[1]*(volatile uint32_t*)(0x42150C0C)=0x%08x\r\n", *(volatile uint32_t*)(0x42150C0C));
        *SPM_TOP_STATE_STATUS = 0xEE;
        hal_nvic_restore_interrupt_mask(mask);
        *SPM_TOP_STATE_STATUS = 0xED;
        //printk("[2]*(volatile uint32_t*)(0x4215031C)=0x%08x\r\n", *(volatile uint32_t*)(0x4215031C));
        //printk("[2]*(volatile uint32_t*)(0x42150318)=0x%08x\r\n", *(volatile uint32_t*)(0x42150318));
        //printk("[2]*(volatile uint32_t*)(0x42150310)=0x%08x\r\n", *(volatile uint32_t*)(0x42150310));
        //printk("[2]*(volatile uint32_t*)(0x42150308)=0x%08x\r\n", *(volatile uint32_t*)(0x42150308));
        //printk("[2]*(volatile uint32_t*)(0x42150300)=0x%08x\r\n", *(volatile uint32_t*)(0x42150300));
        //printk("[2]*(volatile uint32_t*)(0x4215030C)=0x%08x\r\n", *(volatile uint32_t*)(0x4215030C));
        //printk("[2]*(volatile uint32_t*)(0x42150C00)=0x%08x\r\n", *(volatile uint32_t*)(0x42150C00));
        //printk("[2]*(volatile uint32_t*)(0x42150C04)=0x%08x\r\n", *(volatile uint32_t*)(0x42150C04));
        //printk("[2]*(volatile uint32_t*)(0x42150C0C)=0x%08x\r\n", *(volatile uint32_t*)(0x42150C0C));

        /* INFRA pwr on requested by SW, flag cleared by SPM */
        *SPM_CFG_INFRA_WAKEUP_EVENT = 0x1;
        //printk("[2]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
       // printk("[2]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //hal_gpt_delay_ms(500);
        spm_irq = *SPM_CFG_PCM_SW_INT_STATE;
        if((spm_irq & 0x100) != 0){
            printk("[spm_irq]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
            printk("[spm_irq]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
            printk("[spm_irq]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
            printk("[spm_irq]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);
            *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
        }

        *SPM_TOP_STATE_STATUS = 0xEF;
        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0x101;    //for sleep test, need BT or Audio Control.
        *SPM_TOP_STATE_STATUS = 0xE1;
    }

}
ATTR_ZIDATA_IN_TCM uint32_t mask;
ATTR_TEXT_IN_TCM_RETENTION void sleep_control_enter_slp(void)
{
    uint32_t i;
    uint32_t spm_irq;

    // __asm volatile("cpsid i");

    spm_debug_io(0x42444345);

    //spm_check_debug_bus();
    printk("Enter Sleep !!!");

    for (i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }

    for (i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }

    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x01000000;    //IGNORE RISCV/INFRA/CONN ACTIVE
    printk("*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);
    // ao_backup_restore_regitster_dvt();

    // hal_rtc_switch_32k_source(HAL_RTC_OSC32K_EOSC_MODE);
    printk("[SLP][32K] CLK Source=0x%08x\r\n",*(volatile uint32_t*)(0x42105008));

    //hal_nvic_disable_irq(12);

    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL);
    // spm_unmask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_RTC_TIMER);
    spm_mask_wakeup_source(SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, HAL_SPM_INFRA_WAKEUP_SOURCE_ALL);
    // spm_unmask_wakeup_source(SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, HAL_SPM_INFRA_WAKEUP_SOURCE_SPM_SW_WAKEUP);
    spm_mask_wakeup_source(SPM_CFG_CONN_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL);

    printk("*SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_INFRA_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_RISCV_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_WAKEUP_SOURCE_MASK, *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_CONN_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_WAKEUP_SOURCE_MASK, *SPM_CFG_CONN_WAKEUP_SOURCE_MASK);

    // if(*SPM_CFG_SPM_CFG_DUMMY_REG_C == 0x1){
    //     printk("[SLP] subsys_sram_all_power_down \r\n");
    //     subsys_sram_all_power_down();
    // }
    spm_control_mtcmos_internal(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_DISABLE);
    printk("[SPM] PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);
    *SPM_TOP_CONN_FAKE_PWR = 0x0;

    /* RISCV/CMSYS/CONN Ext SLP Flag */
    *SPM_CFG_CMSYS_REQ_EXT_SLP = 0x0;
    *SPM_CFG_RISCV_REQ_EXT_SLP = 0x0;
    *SPM_CFG_CONN_REQ_EXT_SLP = 0x0;
    printk("*SPM_CFG_CMSYS_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_REQ_EXT_SLP, *SPM_CFG_CMSYS_REQ_EXT_SLP);
    printk("*SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);
    printk("*SPM_CFG_CONN_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_REQ_EXT_SLP, *SPM_CFG_CONN_REQ_EXT_SLP);

    /* Lock S1 */
    // *SPM_CFG_SPM_STATE_CONTROL_0 = 0x1;
    /* Lock S3 */
    // *SPM_CFG_SPM_STATE_CONTROL_0 = 0x10000;
    printk("*SPM_CFG_SPM_STATE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_0, *SPM_CFG_SPM_STATE_CONTROL_0);

    /* Debug bus restore */
    *SPM_CFG_SPM_CFG_DUMMY_REG_A = 0x1;
    // printk("*SPM_CFG_SPM_CFG_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_CFG_DUMMY_REG_A, *SPM_CFG_SPM_CFG_DUMMY_REG_A);

    /* CMSYS force on */
    // *SPM_CFG_RESOURCE_CONTROL_0 = 0x100;
    printk("*SPM_CFG_RESOURCE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RESOURCE_CONTROL_0, *SPM_CFG_RESOURCE_CONTROL_0);

    /* IBEX DEEP SLEEP */
    // *RISCV_DEEP_SLEEP = 0xFFFFFFFF;
    printk("*RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);

    /* Lock S6 */
    //*SPM_CFG_SPM_STATE_CONTROL_1 = 0x100;
    //*SPM_CFG_SPM_STATE_CONTROL_1 = 0x10000;
    // printk("*SPM_CFG_SPM_STATE_CONTROL_1(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_1, *SPM_CFG_SPM_STATE_CONTROL_1);

    //*SPM_CFG_SEQUENCER_32K_REG_0 = 0x300; //PMU force on
    // printk("*SPM_CFG_SEQUENCER_32K_REG_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SEQUENCER_32K_REG_0, *SPM_CFG_SEQUENCER_32K_REG_0);

    //hal_sleep_manager_set_sleep_time(5000000); //5s
    // hal_sleep_manager_set_sleep_time_rtc(5000); //5s
    while(1){
        *SPM_TOP_STATE_STATUS = 0xE1;
        hal_sleep_manager_set_sleep_time_rtc(5000); //5s

        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0;        //for sleep test, need BT or Audio Control.
        *SPM_TOP_STATE_STATUS = 0xE2;
        printk("SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND(0x%08x)=0x%x \r\n", (uint32_t)SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND, *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND);
        hal_nvic_save_and_set_interrupt_mask(&mask);
        *SPM_TOP_STATE_STATUS = 0xE3;

        //hal_nvic_clear_pending_irq(22); //GPT_TIMER

        __asm volatile("cpsid i");
        // printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_2);
        // printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_0);
        // printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_2);
        // printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_0);
        // printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_2);
        // printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_0);

        // clock_dump_info();
        // pmu_rg_dump();

        sleep_management_enter_deep_sleep(HAL_SLEEP_MODE_SLEEP);
         *SPM_TOP_STATE_STATUS = 0xE4;
        __asm volatile("cpsie i");
        hal_nvic_restore_interrupt_mask(mask);
        *SPM_TOP_STATE_STATUS = 0xE5;

        /* INFRA pwr on requested by SW, flag cleared by SPM */
        //*SPM_CFG_INFRA_WAKEUP_EVENT = 0x1;
        //printk("[2]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
       // printk("[2]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
        //hal_gpt_delay_ms(500);
        spm_irq = *SPM_CFG_PCM_SW_INT_STATE;
        *SPM_TOP_STATE_STATUS = 0xE6;
        if((spm_irq & 0x100) != 0){
            // printk("[spm_irq]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
            // printk("[spm_irq]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
            // printk("[spm_irq]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
            // printk("[spm_irq]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);
            *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
        }
        *SPM_TOP_STATE_STATUS = 0xE7;

        //*SPM_TOP_STATE_STATUS = 0xEF;
        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0x101;    //for sleep test, need BT or Audio Control.
        //*SPM_TOP_STATE_STATUS = 0xE1;
         *SPM_TOP_STATE_STATUS = 0xE8;
    }
}

void sleep_control_enter_ext_slp(void)
{
    uint32_t mask, i;
    uint32_t spm_irq;

    spm_debug_io(0x45424344);
    //spm_check_debug_bus();

    printk("Enter Ext Sleep !!!");

    for (i = 0; i < IRQ_NUMBER_MAX; i++) {
        //hal_nvic_disable_irq(i);
        if (hal_nvic_get_pending_irq(i) == 1) {
            // printf("pending_irq:%d\r\n", i);
            hal_nvic_clear_pending_irq(i);
        }
    }

    // hal_rtc_switch_32k_source(HAL_RTC_OSC32K_XOSC_MODE);
    printk("[SLP][32K] CLK Source=0x%08x\r\n",*(volatile uint32_t*)(0x42105008));

    *SPM_CFG_IGNORE_CPU_ACTIVE = 0x01000000;    //IGNORE RISCV/INFRA/CONN ACTIVE
    printk("*SPM_CFG_IGNORE_CPU_ACTIVE(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_IGNORE_CPU_ACTIVE, *SPM_CFG_IGNORE_CPU_ACTIVE);
    // ao_backup_restore_regitster_dvt();

    spm_mask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL);
    spm_unmask_wakeup_source(SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_RTC_TIMER);
    spm_mask_wakeup_source(SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, HAL_SPM_INFRA_WAKEUP_SOURCE_ALL);
    spm_unmask_wakeup_source(SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, HAL_SPM_INFRA_WAKEUP_SOURCE_SPM_SW_WAKEUP);
    spm_mask_wakeup_source(SPM_CFG_CONN_WAKEUP_SOURCE_MASK, HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL);

    printk("*SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK, *SPM_CFG_CMSYS_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_INFRA_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_INFRA_WAKEUP_SOURCE_MASK, *SPM_CFG_INFRA_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_RISCV_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_WAKEUP_SOURCE_MASK, *SPM_CFG_RISCV_WAKEUP_SOURCE_MASK);
    printk("*SPM_CFG_CONN_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_WAKEUP_SOURCE_MASK, *SPM_CFG_CONN_WAKEUP_SOURCE_MASK);

    // if(*SPM_CFG_SPM_CFG_DUMMY_REG_C == 0x1){
    //     printk("[SLP] subsys_sram_all_power_down \r\n");
    //     subsys_sram_all_power_down();
    // }
    spm_control_mtcmos_internal(SPM_MTCMOS_AUDIO_SYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_PERISYS, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_ZIGBEE, SPM_MTCMOS_PWR_DISABLE);
    spm_control_mtcmos_internal(SPM_MTCMOS_CONN_TOP_OFF, SPM_MTCMOS_PWR_DISABLE);
    *SPM_TOP_CONN_FAKE_PWR = 0x0;
    printk("[SPM] PWR_STATUS is 0x%08X\r\n", *SPM_CFG_PWR_STATUS_2ND);

    /* RISCV/CMSYS/CONN Ext SLP Flag */
    *SPM_CFG_CMSYS_REQ_EXT_SLP = 0xF;
    *SPM_CFG_RISCV_REQ_EXT_SLP = 0xF;
    *SPM_CFG_CONN_REQ_EXT_SLP = 0xF;
    printk("*SPM_CFG_CMSYS_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CMSYS_REQ_EXT_SLP, *SPM_CFG_CMSYS_REQ_EXT_SLP);
    printk("*SPM_CFG_RISCV_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_RISCV_REQ_EXT_SLP, *SPM_CFG_RISCV_REQ_EXT_SLP);
    printk("*SPM_CFG_CONN_REQ_EXT_SLP(0x%08x)=0x%08x\r\n",(uint32_t)SPM_CFG_CONN_REQ_EXT_SLP, *SPM_CFG_CONN_REQ_EXT_SLP);

    /* Lock S1 */
    //*SPM_CFG_SPM_STATE_CONTROL_0 = 0x1;
    /* Lock S3 */
    *SPM_CFG_SPM_STATE_CONTROL_0 = 0x0;
    // printk("*SPM_CFG_SPM_STATE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_0, *SPM_CFG_SPM_STATE_CONTROL_0);

    /* Debug bus restore */
    *SPM_CFG_SPM_CFG_DUMMY_REG_A = 0x1;
    // printk("*SPM_CFG_SPM_CFG_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_CFG_DUMMY_REG_A, *SPM_CFG_SPM_CFG_DUMMY_REG_A);

    /* CMSYS force on */
    //*SPM_CFG_RESOURCE_CONTROL_0 = 0x1;
    // printk("*SPM_CFG_RESOURCE_CONTROL_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_RESOURCE_CONTROL_0, *SPM_CFG_RESOURCE_CONTROL_0);

    /* INFRA DEEP SLEEP */
    // *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
    // /* INFRA pwr off requested by SW, flag cleared by SPM */
    // *SPM_CFG_INFRA_DEEP_SLEEP = 0x1;

    /* IBEX DEEP SLEEP */
    // *RISCV_DEEP_SLEEP = 0xFFFFFFFF;
    printk("*RISCV_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)RISCV_DEEP_SLEEP, *RISCV_DEEP_SLEEP);

    /* Lock S6 */
    //*SPM_CFG_SPM_STATE_CONTROL_1 = 0x100;
    //*SPM_CFG_SPM_STATE_CONTROL_1 = 0x10000;
    // printk("*SPM_CFG_SPM_STATE_CONTROL_1(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SPM_STATE_CONTROL_1, *SPM_CFG_SPM_STATE_CONTROL_1);

    //*SPM_CFG_SEQUENCER_32K_REG_0 = 0x300; //PMU force on
    // printk("*SPM_CFG_SEQUENCER_32K_REG_0(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_SEQUENCER_32K_REG_0, *SPM_CFG_SEQUENCER_32K_REG_0);

    //hal_sleep_manager_set_sleep_time(5000000); //5s
    hal_sleep_manager_set_sleep_time_rtc(5000); //5s
    // while(1){

        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0;        //for sleep test, need BT or Audio Control.
        // *SPM_TOP_STATE_STATUS = 0xE2;
        printk("SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND(0x%08x)=0x%x \r\n", (uint32_t)SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND, *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND);
        hal_nvic_save_and_set_interrupt_mask(&mask);
        // *SPM_TOP_STATE_STATUS = 0xE3;
        //hal_nvic_clear_pending_irq(22); //GPT_TIMER

        __asm volatile("cpsid i");
        printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_2);
        printk("[SLP] SPM_CFG_INFRA_IRTX_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_INFRA_IRTX_CONTROL_0);
        printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_2);
        printk("[SLP] SPM_CFG_PERISYS_USB_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_PERISYS_USB_CONTROL_0);
        printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_2[PRDYN][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_2);
        printk("[SLP] SPM_CFG_AUDIO_MEMIF_CONTROL_0[RET2N][0]= 0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_0);

        // clock_dump_info();
        // pmu_rg_dump();

        sleep_management_enter_deep_sleep(HAL_SLEEP_MODE_SLEEP);
        __asm volatile("cpsie i");
        //*SPM_TOP_STATE_STATUS = 0xEE;
        hal_nvic_restore_interrupt_mask(mask);
        //*SPM_TOP_STATE_STATUS = 0xED;

        spm_irq = *SPM_CFG_PCM_SW_INT_STATE;
        if((spm_irq & 0x100) != 0){
            // printk("[spm_irq]*SPM_CFG_INFRA_WAKEUP_EVENT(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_WAKEUP_EVENT, *SPM_CFG_INFRA_WAKEUP_EVENT);
            // printk("[spm_irq]*SPM_TOP_DUMMY_REG_A(0x%08x)=0x%08x\r\n", (uint32_t)SPM_TOP_DUMMY_REG_A, *SPM_TOP_DUMMY_REG_A);
            // printk("[spm_irq]*SPM_CFG_INFRA_DEEP_SLEEP(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_INFRA_DEEP_SLEEP, *SPM_CFG_INFRA_DEEP_SLEEP);
            // printk("[spm_irq]*SPM_CFG_PCM_SW_INT_STATE(0x%08x)=0x%08x\r\n", (uint32_t)SPM_CFG_PCM_SW_INT_STATE, *SPM_CFG_PCM_SW_INT_STATE);
            *SPM_CFG_PCM_SW_INT_CLEAR_INFRA = 0x1;
        }

        //*SPM_TOP_STATE_STATUS = 0xEF;
        *SPM_CFG_CONN_AUDIO_ABB_XO_SIDEBAND = 0x101;    //for sleep test, need BT or Audio Control.
        //*SPM_TOP_STATE_STATUS = 0xE1;

    // }
}
#endif

/*---------------------------------- MTCMOS POWER CONTROL ------------------------------------------*/
ATTR_TEXT_IN_TCM_RETENTION static void spm_mtcmos_audio_sys_on(void){

    if ((*SPM_CFG_PWR_STATUS_2ND & 0x10) != 0) {
        printk("[SLP] spm_mtcmos_audio_sys is already on\r\n");
        return;
    }

    /*TINFO = "---AUDIO power on by CMSYS API"*/
    //*AUDIO_PWR_CON = 0x12 sleep
    *SPM_CFG_AUDIO_PWR_CON = 0x16;     // [2]:pwr_on = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*SPM_TOP_MDM_TM_WAIT_US!=0);
    *SPM_CFG_AUDIO_PWR_CON = 0x1E;     // [3]:pwr_on_2nd = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*SPM_TOP_MDM_TM_WAIT_US!=0);

    //pgen = 0
    *SPM_CFG_AUDIO_MEMIF_CONTROL_1 = 0x00000000; //[24]:MEM_ISO_EN [0]:PGEN

    *SPM_CFG_AUDIO_PWR_CON = 0xE;      // [4]:clk_dis = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*SPM_TOP_MDM_TM_WAIT_US!=0);
    *SPM_CFG_AUDIO_PWR_CON = 0x1E;     // [4]:clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*SPM_TOP_MDM_TM_WAIT_US!=0);
    *SPM_CFG_AUDIO_PWR_CON = 0x1C;     // [1]:iso = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*SPM_TOP_MDM_TM_WAIT_US!=0);
    *SPM_CFG_AUDIO_PWR_CON = 0x1D;      // [0]:rstb = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*SPM_TOP_MDM_TM_WAIT_US!=0);

    //mem_iso_en_b = 1
    *SPM_CFG_AUDIO_MEMIF_CONTROL_1 = 0x01000000; //[24]:MEM_ISO_EN [0]:PGEN

    *SPM_CFG_AUDIO_PWR_CON = 0xD;      // [4]:clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*SPM_TOP_MDM_TM_WAIT_US!=0);

    //turn AUDIO protect_en = 0
    *AUDIO_SYS_TOP_PROT_EN = 0x0;
    //wait AUDIO protect ready = 0
    while(*AUDIO_SYS_TOP_PROT_RDY!=0x0);

}

ATTR_TEXT_IN_TCM_RETENTION static void spm_mtcmos_audio_sys_off(void){

    if ((*SPM_CFG_PWR_STATUS_2ND & 0x10) == 0) {
        printk("[SLP] spm_mtcmos_audio_sys is already off\r\n");
        return;
    }

    /*TINFO = "---AUDIO power off by CMSYS API"*/
    //turn AUDIO protect_en = 0
    *AUDIO_SYS_TOP_PROT_EN = 0x1;
    //wait AUDIO protect ready = 0
    while(*AUDIO_SYS_TOP_PROT_RDY!=0x1);
    //*AUDIO_PWR_CON = 0xD on
    *SPM_CFG_AUDIO_PWR_CON = 0x1D;     // [4]:clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_AUDIO_PWR_CON = 0x1F;     // [1]:iso = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

#ifdef AUDIO_SRAM_RET2N_MODE //SPM TBD
    *SPM_CFG_AUDIO_MEMIF_CONTROL_0 = *SPM_CFG_AUDIO_MEMIF_CONTROL_0 | 0x00000001; //[16]:FORCE_OFF [0]:RET2N
    hal_gpt_delay_us(1);     // 500ns
    //while(*MDM_TM_WAIT_NS!=0);
#elif AUDIO_SRAM_PD_MODE //SPM TBD
    *SPM_CFG_AUDIO_MEMIF_CONTROL_0 = *SPM_CFG_AUDIO_MEMIF_CONTROL_0 & 0xFFFF0000; //[16]:FORCE_OFF [0]:RET2N
     hal_gpt_delay_us(1);;     // 500ns
    //while(*MDM_TM_WAIT_NS!=0);
#endif
    //mem_iso_en_b = 0
    *SPM_CFG_AUDIO_MEMIF_CONTROL_1 = 0x00000000; //[24]:MEM_ISO_EN [0]:PGEN
    //pgen = 1
    *SPM_CFG_AUDIO_MEMIF_CONTROL_1 = 0x00000001; //[24]:MEM_ISO_EN [0]:PGEN

    *SPM_CFG_AUDIO_PWR_CON = 0x1E;     // [0]:rstb = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_AUDIO_PWR_CON = 0x1A;     // [2]:pwr_on = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_AUDIO_PWR_CON = 0x12;     // [3]:pwr_on_2nd = 0
    hal_gpt_delay_us(1);       // 1us

}

ATTR_TEXT_IN_TCM_RETENTION static void spm_mtcmos_conn_top_off_on(void){

    if ((*SPM_CFG_PWR_STATUS_2ND & 0x4) != 0) {
        printk("[SLP] spm_mtcmos_conn_top_off is already on\r\n");
        return;
    }

    /*TINFO = "---CONN_TOP_OFF power on by CMSYS API"*/
    //*CONN_TOP_OFF_PWR_CON = 0x12 sleep
    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x16;     // [2]:pwr_on = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x1E;     // [3]:pwr_on_2nd = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0xE;      // [4]:clk_dis = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x1E;     // [4]:clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x1C;     // [1]:iso = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x1D;      // [0]:rstb = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0xD;      // [4]:clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    //turn CONN_M_MODEM protect_en = 0
    *CONNSYS_OFF_PROT_EN = 0x0;
    //wait CONN_M_MODEM protect ready = 0
    while(*CONNSYS_OFF_PROT_RDY!=0x0);

    *SPM_TOP_CONN_FAKE_PWR = 0x1;
}

ATTR_TEXT_IN_TCM_RETENTION static void spm_mtcmos_conn_top_off_off(void){

    if ((*SPM_CFG_PWR_STATUS_2ND & 0x4) == 0) {
        printk("[SLP] spm_mtcmos_conn_top_off is already off\r\n");
        return;
    }

    /*TINFO = "---CONN_M_MODEM power off by CMSYS API"*/
    //turn CONN_M_MODEM protect_en = 0
    *CONNSYS_OFF_PROT_EN = 0x1;
    //wait CONN_M_MODEM protect ready = 0
    // while(*CONNSYS_OFF_PROT_RDY!=0x1);
    //*CONN_TOP_OFF_PWR_CON = 0xD on
    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x1D;     // [4]:clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x1F;     // [1]:iso = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x1E;     // [0]:rstb = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x1A;     // [2]:pwr_on = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_TOP_CONN_TOP_OFF_PWR_CON = 0x12;     // [3]:pwr_on_2nd = 0
    hal_gpt_delay_us(1);       // 1us

    *SPM_TOP_CONN_FAKE_PWR = 0x0;
}

ATTR_TEXT_IN_TCM_RETENTION static void spm_mtcmos_conn_zigbee_on(void){
    //SPM TBD
    int tmp,tmp1;
    *SPM_CFG_CONN_MTCMOS_ENABLE = *SPM_CFG_CONN_MTCMOS_ENABLE | 0x2;
    tmp = 0x1;
    while(tmp){
    tmp1 = *SPM_CFG_CONN_MTCMOS_FLOW_FW;
    tmp1 = tmp1 >> 1;
    tmp = tmp1 & 0x1;
    }

    if ((*SPM_CFG_PWR_STATUS_2ND & 0x8) != 0) {
        printk("[SLP] spm_mtcmos_conn_zigbee is already on\r\n");
        return;
    }

    /*TINFO = "---CONN_ZIGBEE power on by CMSYS API"*/
    *SPM_CFG_CONN_MTCMOS_FLOW_SW = *SPM_CFG_CONN_MTCMOS_FLOW_SW | 0x00000002;
    *SPM_TOP_CONN_MTCMOS_ENABLE_FW = *SPM_TOP_CONN_MTCMOS_ENABLE_FW | 0x2;
    //*CONN_ZIGBEE_PWR_CON = 0x12 sleep
    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x16;     // [2]:pwr_on = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x1E;     // [3]:pwr_on_2nd = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0xE;      // [4]:clk_dis = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x1E;     // [4]:clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x1C;     // [1]:iso = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x1D;      // [0]:rstb = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0xD;      // [4]:clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_CONN_MTCMOS_FLOW_SW = *SPM_CFG_CONN_MTCMOS_FLOW_SW & 0xFFFFFFFD;

    *ZB_TOP_PROT_EN = 0x0;
    while(*ZB_TOP_PROT_RDY != 0x0);

}

#ifdef CONFIG_AIR_SPM_STANDBY_MODE_ENABLE
ATTR_TEXT_IN_TCM_RETENTION static void spm_mtcmos_conn_zigbee_off(void){
    //SPM TBD
    int tmp, tmp1;
    *SPM_CFG_CONN_MTCMOS_ENABLE = *SPM_CFG_CONN_MTCMOS_ENABLE & 0xFFFFFFFD;
    tmp = 0x1;
    while(tmp){
    tmp1 = *SPM_CFG_CONN_MTCMOS_FLOW_FW;
    tmp1 = tmp1 >> 1;
    tmp = tmp1 & 0x1;
    }

    if ((*SPM_CFG_PWR_STATUS_2ND & 0x8) == 0) {
        printk("[SLP] spm_mtcmos_conn_zigbee is already off\r\n");
        return;
    }

    *ZB_TOP_PROT_EN = 0x1;
    while(*ZB_TOP_PROT_RDY != 0x1);

    /*TINFO = "---CONN_ZIGBEE power off by CMSYS API"*/
    *SPM_CFG_CONN_MTCMOS_FLOW_SW = *SPM_CFG_CONN_MTCMOS_FLOW_SW | 0x00000002;
    //*CONN_ZIGBEE_PWR_CON = 0xD on
    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x1D;     // [4]:clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x1F;     // [1]:iso = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x1E;     // [0]:rstb = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x1A;     // [2]:pwr_on = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_CONN_ZIGBEE_PWR_CON = 0x12;     // [3]:pwr_on_2nd = 0
    hal_gpt_delay_us(1);       // 1us
    *SPM_CFG_CONN_MTCMOS_FLOW_SW = *SPM_CFG_CONN_MTCMOS_FLOW_SW & 0xFFFFFFFD;
    *SPM_TOP_CONN_MTCMOS_ENABLE_FW = *SPM_TOP_CONN_MTCMOS_ENABLE_FW & 0xFFFFFFFD;

}
#endif

ATTR_TEXT_IN_TCM_RETENTION static void spm_mtcmos_perisys_on(void)
{
    if ((*SPM_CFG_PWR_STATUS_2ND & 0x20) != 0) {
        printk("[SLP] spm_mtcmos_perisys is already on\r\n");
        return;
    }

    /*TINFO = " --- PERISYS power on by PERISYS API "*/
    //*PERISYS_PWR_CON = 0x12; sleep
    *SPM_CFG_PERISYS_PWR_CON = 0x16; // [2]: pwr_on = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_PERISYS_PWR_CON = 0x1E; // [3]: pwr_on_2nd = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    // --- PERISYS SRAM begin ------
//    *USB_SRAM_CONTROL_1 = 0x01000100;//[24]:MEM_ISO_EN [16]:ISOINTB [8]:SLEEPB [0]:PD
      //hal_gpt_delay_us(2); // wait sleepb to isointb  > 2us
      //while(*MDM_TM_WAIT_US!=0);
//    *USB_SRAM_CONTROL_1 = 0x01010100;//[24]:MEM_ISO_EN [16]:ISOINTB [8]:SLEEPB [0]:PD

    // --- PERISYS SRAM end ------
    *SPM_CFG_PERISYS_PWR_CON = 0xE;   // [4]: clk_dis = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_PERISYS_PWR_CON = 0x1E;  // [4]: clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_PERISYS_PWR_CON = 0x1C;  // [4]: clk_dis = 1, iso = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_PERISYS_PWR_CON = 0x1D;  // [0]: rstb = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    // --- PERISYS SRAM MEM_ISO_EN begin ------
//    *USB_SRAM_CONTROL_1 = 0x00010100;//[24]:MEM_ISO_EN [16]:ISOINTB [8]:SLEEPB [0]:PD

    *SPM_CFG_PERISYS_PWR_CON = 0xD;   // [4]: clk_dis = 0
      //*TM_CTRL |= 0x200;
    hal_gpt_delay_us(1);       // 1us
      //while(*MDM_TM_WAIT_US!=0);

    //turn PERISYS protect_en=0
    *PERISYS_PROT_EN = 0x0;
    //wait PERISYS protect ready=0
    while(*PERISYS_PROT_RDY!=0x0);

    // *SPM_CFG_RESOURCE_CONTROL_0 = *SPM_CFG_RESOURCE_CONTROL_0 | 0x100; //infra_force_on set 1

}

ATTR_TEXT_IN_TCM_RETENTION static void spm_mtcmos_perisys_off(void)
{
    if ((*SPM_CFG_PWR_STATUS_2ND & 0x20) == 0) {
        printk("[SLP] spm_mtcmos_perisys is already off\r\n");
        return;
    }

      /*TINFO = " --- USB, SPISLV, I3C CG power off "*/
      //*TM_CTRL &= 0xFFFFFDFF;

    /*TINFO = " --- PERISYS power down by PERISYS API "*/
    *SPM_CFG_PERISYS_PWR_CON = 0x1D; // [4]: clk_dis = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_PERISYS_PWR_CON = 0x1F; // [1]: iso = 1
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);

    //// --- PERISYS SRAM Power Down begin ------

//    *USB_SRAM_CONTROL_1 = 0x01010100;//[24]:MEM_ISO_EN=1

//    *USB_SRAM_CONTROL_1 = 0x01000100;//[16]:ISOINTB=0
      //*MDM_TM_WAIT_US = 1; // wait isointb to sleepb  > 1us
      //while(*MDM_TM_WAIT_US!=0);
//    *USB_SRAM_CONTROL_1 = 0x01000001;//[8]:SLEEPB=0 [0]:PD=1

    //// --- PERISYS SRAM end Power Down------
    *SPM_CFG_PERISYS_PWR_CON = 0x1E; // [0]: rstb = 0
    hal_gpt_delay_us(1);       // 1us
    //while(*MDM_TM_WAIT_US!=0);
    *SPM_CFG_PERISYS_PWR_CON = 0x1A; // [2]: pwr_on = 0
    hal_gpt_delay_us(1);       // 1us

    *SPM_CFG_PERISYS_PWR_CON = 0x12; // [3]: pwr_on_2nd = 0
    hal_gpt_delay_us(1);       // 1us

    //turn PERISYS protect_en=1
    *PERISYS_PROT_EN = 0x1;
    //wait PERISYS protect ready=1
    while(*PERISYS_PROT_RDY!=0x1);

    // *SPM_CFG_RESOURCE_CONTROL_0 = *SPM_CFG_RESOURCE_CONTROL_0 & 0xFFFFFEFF; //infra_force_on set 0

}

static void spm_mtcmos_rtcsys_on(void)
{
    if ((*RTCSYS_PWR_CTRL & 0x10000) != 0) {
        printk("[SLP] spm_mtcmos_rtcsys is already on\r\n");
        return;
    }

    *RTCSYS_PWR_CTRL = 0x7EF;
    hal_gpt_delay_us(300);
    *RTCSYS_PWR_CTRL = 0x7EE;
    hal_gpt_delay_us(300);
    *RTCSYS_PWR_CTRL = 0x7FE;
    hal_gpt_delay_us(300);
    *RTCSYS_PWR_CTRL = 0x7F6;
    hal_gpt_delay_us(300);
}

static void spm_mtcmos_rtcsys_off(void)
{
    if ((*RTCSYS_PWR_CTRL & 0x10000) == 0) {
        printk("[SLP] spm_mtcmos_rtcsys is already off\r\n");
        return;
    }

    *RTCSYS_PWR_CTRL = 0x7FE;
    hal_gpt_delay_us(300);
    *RTCSYS_PWR_CTRL = 0x7EE;
    hal_gpt_delay_us(300);
    *RTCSYS_PWR_CTRL = 0x7EF;
    hal_gpt_delay_us(300);
    *RTCSYS_PWR_CTRL = 0x7ED;
    hal_gpt_delay_us(300);
}

ATTR_TEXT_IN_TCM_RETENTION void infra_irtx_sram_power_down(void)
{
    *SPM_CFG_INFRA_IRTX_CONTROL_0 |= (1 << 0); /* RET2N=1 */
    *SPM_CFG_INFRA_IRTX_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_INFRA_IRTX_CONTROL_0 |= (1 << 16); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void infra_irtx_sram_retention(void)
{
    *SPM_CFG_INFRA_IRTX_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 0)); /* RET2N=0 */
    *SPM_CFG_INFRA_IRTX_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_INFRA_IRTX_CONTROL_0 |= (1 << 16); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void infra_irtx_sram_power_on(void)
{
    *SPM_CFG_INFRA_IRTX_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 16)); /* force_off=0 */
    *SPM_CFG_INFRA_IRTX_CONTROL_1 |= (1 << 24); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void perisys_usb_sram_power_down(void)
{
    *SPM_CFG_PERISYS_USB_CONTROL_0 |= (1 << 0); /* RET2N=1 */
    *SPM_CFG_PERISYS_USB_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_PERISYS_USB_CONTROL_0 |= (1 << 16); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_PERISYS_USB_CONTROL_0=0x%x", *SPM_CFG_PERISYS_USB_CONTROL_0);
    printk("[SLP][PD] SPM_CFG_PERISYS_USB_CONTROL_1=0x%x", *SPM_CFG_PERISYS_USB_CONTROL_1);
}

ATTR_TEXT_IN_TCM_RETENTION void perisys_usb_sram_retention(void)
{
    *SPM_CFG_PERISYS_USB_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 0)); /* RET2N=0 */
    *SPM_CFG_PERISYS_USB_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_PERISYS_USB_CONTROL_0 |= (1 << 16); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void perisys_usb_sram_power_on(void)
{
    *SPM_CFG_PERISYS_USB_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 16)); /* force_off=0 */
    *SPM_CFG_PERISYS_USB_CONTROL_1 |= (1 << 24); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void audio_memif_sram_power_down(void)
{
    *SPM_CFG_AUDIO_MEMIF_CONTROL_0 |= (1 << 0); /* RET2N=1 */
    *SPM_CFG_AUDIO_MEMIF_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_AUDIO_MEMIF_CONTROL_0 |= (1 << 16); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_AUDIO_MEMIF_CONTROL_0=0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_0);
    printk("[SLP][PD] SPM_CFG_AUDIO_MEMIF_CONTROL_1=0x%x", *SPM_CFG_AUDIO_MEMIF_CONTROL_1);
}

ATTR_TEXT_IN_TCM_RETENTION void audio_memif_sram_retention(void)
{
    *SPM_CFG_AUDIO_MEMIF_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 0)); /* RET2N=0 */
    *SPM_CFG_AUDIO_MEMIF_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_AUDIO_MEMIF_CONTROL_0 |= (1 << 16); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void audio_memif_sram_power_on(void)
{
    *SPM_CFG_AUDIO_MEMIF_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 16)); /* force_off=0 */
    *SPM_CFG_AUDIO_MEMIF_CONTROL_1 |= (1 << 24); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_rom_0_sram_power_down(void)
{
    *SPM_CFG_CMSYS_ROM_CONTROL &= (0xFFFFFFFF & ~(1 << 16)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_ROM_CONTROL |= (1 << 0); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_CMSYS_ROM_CONTROL=0x%x", *SPM_CFG_CMSYS_ROM_CONTROL);
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_rom_0_sram_power_on(void)
{
    *SPM_CFG_CMSYS_ROM_CONTROL &= (0xFFFFFFFF & ~(1 << 0)); /* force_off=0 */
    *SPM_CFG_CMSYS_ROM_CONTROL |= (1 << 16); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_rom_1_sram_power_down(void)
{
    *SPM_CFG_CMSYS_ROM_CONTROL &= (0xFFFFFFFF & ~(1 << 17)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_ROM_CONTROL |= (1 << 1); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_CMSYS_ROM_CONTROL=0x%x", *SPM_CFG_CMSYS_ROM_CONTROL);
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_rom_1_sram_power_on(void)
{
    *SPM_CFG_CMSYS_ROM_CONTROL &= (0xFFFFFFFF & ~(1 << 1)); /* force_off=0 */
    *SPM_CFG_CMSYS_ROM_CONTROL |= (1 << 17); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_0_sram_power_down(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 0); /* RET2N=1 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 16); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_CMSYS_TCM2K_CONTROL_0=0x%x", *SPM_CFG_CMSYS_TCM2K_CONTROL_0);
    printk("[SLP][PD] SPM_CFG_CMSYS_TCM2K_CONTROL_1=0x%x", *SPM_CFG_CMSYS_TCM2K_CONTROL_1);

}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_0_sram_retention(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 0)); /* RET2N=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 16); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_0_sram_power_on(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 16)); /* force_off=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 |= (1 << 24); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_1_sram_power_down(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 1); /* RET2N=1 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 17); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_CMSYS_TCM2K_CONTROL_0=0x%x", *SPM_CFG_CMSYS_TCM2K_CONTROL_0);
    printk("[SLP][PD] SPM_CFG_CMSYS_TCM2K_CONTROL_1=0x%x", *SPM_CFG_CMSYS_TCM2K_CONTROL_1);
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_1_sram_retention(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 1)); /* RET2N=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 17); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_1_sram_power_on(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 17)); /* force_off=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 |= (1 << 24); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_2_sram_power_down(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 2); /* RET2N=1 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 18); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_CMSYS_TCM2K_CONTROL_0=0x%x", *SPM_CFG_CMSYS_TCM2K_CONTROL_0);
    printk("[SLP][PD] SPM_CFG_CMSYS_TCM2K_CONTROL_1=0x%x", *SPM_CFG_CMSYS_TCM2K_CONTROL_1);
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_2_sram_retention(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 2)); /* RET2N=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 18); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_2_sram_power_on(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 18)); /* force_off=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 |= (1 << 24); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_3_sram_power_down(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 3); /* RET2N=1 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 19); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_CMSYS_TCM2K_CONTROL_0=0x%x", *SPM_CFG_CMSYS_TCM2K_CONTROL_0);
    printk("[SLP][PD] SPM_CFG_CMSYS_TCM2K_CONTROL_1=0x%x", *SPM_CFG_CMSYS_TCM2K_CONTROL_1);
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_3_sram_retention(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 3)); /* RET2N=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 |= (1 << 19); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm2k_3_sram_power_on(void)
{
    *SPM_CFG_CMSYS_TCM2K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 19)); /* force_off=0 */
    *SPM_CFG_CMSYS_TCM2K_CONTROL_1 |= (1 << 24); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm4k_0_sram_power_down(void)
{
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 |= (1 << 0); /* RET2N=1 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 |= (1 << 16); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_CMSYS_TCM4K_CONTROL_0=0x%x", *SPM_CFG_CMSYS_TCM4K_CONTROL_0);
    printk("[SLP][PD] SPM_CFG_CMSYS_TCM4K_CONTROL_1=0x%x", *SPM_CFG_CMSYS_TCM4K_CONTROL_1);
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm4k_0_sram_retention(void)
{
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 0)); /* RET2N=0 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 |= (1 << 16); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm4k_0_sram_power_on(void)
{
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 16)); /* force_off=0 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_1 |= (1 << 24); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm4k_1_sram_power_down(void)
{
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 |= (1 << 1); /* RET2N=1 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 |= (1 << 17); /* force_off=1 */

    printk("[SLP][PD] SPM_CFG_CMSYS_TCM4K_CONTROL_0=0x%x", *SPM_CFG_CMSYS_TCM4K_CONTROL_0);
    printk("[SLP][PD] SPM_CFG_CMSYS_TCM4K_CONTROL_1=0x%x", *SPM_CFG_CMSYS_TCM4K_CONTROL_1);
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm4k_1_sram_retention(void)
{
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 1)); /* RET2N=0 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_1 &= (0xFFFFFFFF & ~(1 << 24)); /* mem_iso_en_b=0 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 |= (1 << 17); /* force_off=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void cmsys_tcm4k_1_sram_power_on(void)
{
    *SPM_CFG_CMSYS_TCM4K_CONTROL_0 &= (0xFFFFFFFF & ~(1 << 17)); /* force_off=0 */
    *SPM_CFG_CMSYS_TCM4K_CONTROL_1 |= (1 << 24); /* mem_iso_en_b=1 */
}

ATTR_TEXT_IN_TCM_RETENTION void subsys_sram_all_power_down(void)
{
    // infra_irtx_sram_power_down();
    perisys_usb_sram_power_down();
    audio_memif_sram_power_down();
    cmsys_rom_0_sram_power_down();
    cmsys_rom_1_sram_power_down();
    // cmsys_tcm2k_0_sram_power_down(void);
    // cmsys_tcm2k_1_sram_power_down(void);
    // cmsys_tcm2k_2_sram_power_down(void);
    // cmsys_tcm2k_3_sram_power_down(void);
    // cmsys_tcm4k_0_sram_power_down(void);
    // cmsys_tcm4k_1_sram_power_down(void);
}

ATTR_TEXT_IN_TCM_RETENTION void subsys_sram_all_power_on(void)
{
    infra_irtx_sram_power_on();
    perisys_usb_sram_power_on();
    audio_memif_sram_power_on();
    // cmsys_tcm2k_0_sram_power_on(void);
    // cmsys_tcm2k_1_sram_power_on(void);
    // cmsys_tcm2k_2_sram_power_on(void);
    // cmsys_tcm2k_3_sram_power_on(void);
    // cmsys_tcm4k_0_sram_power_on(void);
    // cmsys_tcm4k_1_sram_power_on(void);

}

ATTR_TEXT_IN_TCM_RETENTION void subsys_sram_all_retention(void)
{

    infra_irtx_sram_retention();
    perisys_usb_sram_retention();
    audio_memif_sram_retention();
    // cmsys_tcm2k_0_sram_retention(void);
    // cmsys_tcm2k_1_sram_retention(void);
    // cmsys_tcm2k_2_sram_retention(void);
    // cmsys_tcm2k_3_sram_retention(void);
    // cmsys_tcm4k_0_sram_retention(void);
    // cmsys_tcm4k_1_sram_retention(void);

}

void sysram_0_0_power_down(void){
    uint32_t mask = 0;

    *SYSRAM0_PWR_CON |= (0x7 << mask);    /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);

}

void sysram_0_0_force_off(void){
    uint32_t mask = 16;

    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM0_CONTROL_0__F_MEMORY_SYSRAM0_FORCE_OFF = 0x0001; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM0_CONTROL_0 |= 0xFFFF0000; /* *MEMORY_SYSRAM0_CONTROL_0__F_MEMORY_SYSRAM0_FORCE_OFF = 0x000F; */
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFFF0000;

}

void sysram_0_0_power_on(void){
    uint32_t temp = *SYSRAM0_PWR_CON;
    uint32_t mask = 0;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM0_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 0));
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON |= (1 << (mask + 1));
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0)));
    hal_gpt_delay_us(1);

}

void sysram_0_0_force_on(void){
    *MEMORY_SYSRAM0_CONTROL_0 &= 0xFFFEFFFF;
}

void sysram_0_1_power_down(void){
    uint32_t mask = 8;

    *SYSRAM0_PWR_CON |= (0x7 << mask);    /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_0_1_force_off(void){
    uint32_t mask = 17;

    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM0_CONTROL_0__F_MEMORY_SYSRAM0_FORCE_OFF = 0x0001; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM0_CONTROL_0 |= 0xFFFE0000; /* *MEMORY_SYSRAM0_CONTROL_0__F_MEMORY_SYSRAM0_FORCE_OFF = 0x000E; */
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFFF0000;
}

void sysram_0_1_power_on(void){
    uint32_t temp = *SYSRAM0_PWR_CON;
    uint32_t mask = 8;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM0_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 8));
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON |= (1 << (mask + 1));
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0)));
    hal_gpt_delay_us(1);
}

void sysram_0_1_force_on(void){
    *MEMORY_SYSRAM0_CONTROL_0 &= 0xFFFCFFFF;
}

void sysram_0_2_power_down(void){
    uint32_t mask = 16;

    *SYSRAM0_PWR_CON |= (0x7 << mask);    /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_0_2_force_off(void){
    uint32_t mask = 18;

    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM0_CONTROL_0__F_MEMORY_SYSRAM0_FORCE_OFF = 0x0001; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM0_CONTROL_0 |= 0xFFFC0000; /* *MEMORY_SYSRAM0_CONTROL_0__F_MEMORY_SYSRAM0_FORCE_OFF = 0x000C; */
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFFF0000;
}

void sysram_0_2_power_on(void){
    uint32_t temp = *SYSRAM0_PWR_CON;
    uint32_t mask = 16;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM0_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 16));
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON |= (1 << (mask + 1));
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0)));
    hal_gpt_delay_us(1);
}

void sysram_0_2_force_on(void){
    *MEMORY_SYSRAM0_CONTROL_0 &= 0xFFF8FFFF;
}

void sysram_0_3_power_down(void){
    uint32_t mask = 24;

    *SYSRAM0_PWR_CON |= (0x7 << mask);    /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM0_PWR_CON__F_SYSRAM_0_0_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_0_3_force_off(void){
    uint32_t mask = 19;

    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM0_CONTROL_0__F_MEMORY_SYSRAM0_FORCE_OFF = 0x0001; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM0_CONTROL_0 |= 0xFFF80000; /* *MEMORY_SYSRAM0_CONTROL_0__F_MEMORY_SYSRAM0_FORCE_OFF = 0x000F; */
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFFF0000;
}

void sysram_0_3_power_on(void){
    uint32_t temp = *SYSRAM0_PWR_CON;
    uint32_t mask = 24;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM0_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 24));
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON |= (1 << (mask + 1));
    hal_gpt_delay_us(1);
    *SYSRAM0_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0)));
    hal_gpt_delay_us(1);
}

void sysram_0_3_force_on(void){
    *MEMORY_SYSRAM0_CONTROL_0 &= 0xFFF0FFFF;
}

void sysram_5_0_power_down(void){
    uint32_t mask = 16;

    *SYSRAM4_5_PWR_CON |= (0x7 << mask);    /* *SYSRAM4_5_PWR_CON__F_SYSRAM_5_0_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_5_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_5_0_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_5_0_force_off(void){
    uint32_t mask = 30;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x4000; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xC0000000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xC000; */

}

void sysram_5_0_power_on(void){
    uint32_t temp = *SYSRAM4_5_PWR_CON;
    uint32_t mask = 16;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM4_5_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 16));
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON |= (1 << (mask + 1));
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0)));
    hal_gpt_delay_us(1);

}

void sysram_5_0_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0x8000FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x8000; */
    //sysram1-0~5_0 force on
}

void sysram_5_1_power_down(void){
    uint32_t mask = 24;

    *SYSRAM4_5_PWR_CON |= (0x7 << mask);    /* *SYSRAM4_5_PWR_CON__F_SYSRAM_5_1_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_5_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_5_1_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);

}

void sysram_5_1_force_off(void){
    uint32_t mask = 31;
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x8000; */
}

void sysram_5_1_power_on(void){

    uint32_t temp = *SYSRAM4_5_PWR_CON;
    uint32_t mask = 24;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM4_5_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 24)); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_5_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_5_1_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_5_1_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);

}

void sysram_5_1_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0x0000FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0000; */
}

void sysram_4_0_power_down(void){

    uint32_t mask = 0;

    *SYSRAM4_5_PWR_CON |= (0x7 << mask);    /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_0_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_0_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);

}

void sysram_4_0_force_off(void){

    uint32_t mask = 28;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x1000; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xF0000000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xF000; */
}

void sysram_4_0_power_on(void){

    uint32_t temp = *SYSRAM4_5_PWR_CON;
    uint32_t mask = 0;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM4_5_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 0)); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_0_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_0_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);

}

void sysram_4_0_force_on(void){

    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xE000FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xE000; */
}

void sysram_4_1_power_down(void){

    uint32_t mask = 8;

    *SYSRAM4_5_PWR_CON |= (0x7 << mask);    /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_1_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_1_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);

}

void sysram_4_1_force_off(void){

    uint32_t mask = 29;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x1000; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xE0000000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xE000; */
}

void sysram_4_1_power_on(void){

    uint32_t temp = *SYSRAM4_5_PWR_CON;
    uint32_t mask = 8;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM4_5_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 8)); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_1_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM4_5_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM4_5_PWR_CON__F_SYSRAM_4_1_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);

}

void sysram_4_1_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xC000FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xC000; */
}

void sysram_3_0_power_down(void){

    uint32_t mask = 0;

    *SYSRAM3_PWR_CON |= (0x7 << mask);    /* *SYSRAM3_PWR_CON__F_SYSRAM_3_0_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_0_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);

}

void sysram_3_0_force_off(void){

    uint32_t mask = 24;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0100; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFF000000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFE00; */
}

void sysram_3_0_power_on(void){

    uint32_t temp = *SYSRAM3_PWR_CON;
    uint32_t mask = 0;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM3_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 0)); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_0_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_0_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);

}

void sysram_3_0_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFE00FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFE00; */
}

void sysram_3_1_power_down(void){
    uint32_t mask = 8;

    *SYSRAM3_PWR_CON |= (0x7 << mask);    /* *SYSRAM3_PWR_CON__F_SYSRAM_3_1_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_1_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);

}

void sysram_3_1_force_off(void){
    uint32_t mask = 25;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0100; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFE000000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFE00; */
}

void sysram_3_1_power_on(void){
    uint32_t temp = *SYSRAM3_PWR_CON;
    uint32_t mask = 8;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM3_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 8)); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_1_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_1_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);

}

void sysram_3_1_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFC00FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFC00; */
}

void sysram_3_2_power_down(void){
    uint32_t mask = 16;

    *SYSRAM3_PWR_CON |= (0x7 << mask);    /* *SYSRAM3_PWR_CON__F_SYSRAM_3_2_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_2_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_2_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_3_2_force_off(void){
    uint32_t mask = 26;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0400; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFC000000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFC00; */
}

void sysram_3_2_power_on(void){
    uint32_t temp = *SYSRAM3_PWR_CON;
    uint32_t mask = 16;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM3_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 16)); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_2_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_2_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_2_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_3_2_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xF800FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xF800; */
}

void sysram_3_3_power_down(void){
    uint32_t mask = 24;

    *SYSRAM3_PWR_CON |= (0x7 << mask);    /* *SYSRAM3_PWR_CON__F_SYSRAM_3_3_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_3_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_3_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_3_3_force_off(void){
    uint32_t mask = 27;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0800; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xF8000000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xF800; */
}

void sysram_3_3_power_on(void){
    uint32_t temp = *SYSRAM3_PWR_CON;
    uint32_t mask = 24;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM3_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 24)); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_3_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_3_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM3_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM3_PWR_CON__F_SYSRAM_3_3_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_3_3_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xF000FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xF000; */
}

void sysram_2_0_power_down(void){
    uint32_t mask = 0;

    *SYSRAM2_PWR_CON |= (0x7 << mask);    /* *SYSRAM2_PWR_CON__F_SYSRAM_2_0_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_0_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_2_0_force_off(void){
    uint32_t mask = 20;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0010; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFF00000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFF0; */
}

void sysram_2_0_power_on(void){
    uint32_t temp = *SYSRAM2_PWR_CON;
    uint32_t mask = 0;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM2_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 0)); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_0_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_0_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_2_0_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFFE0FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFE0; */
}

void sysram_2_1_power_down(void){
    uint32_t mask = 8;

    *SYSRAM2_PWR_CON |= (0x7 << mask);    /* *SYSRAM2_PWR_CON__F_SYSRAM_2_1_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_1_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_2_1_force_off(void){
    uint32_t mask = 21;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0020; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFE00000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFE0; */
}

void sysram_2_1_power_on(void){
    uint32_t temp = *SYSRAM2_PWR_CON;
    uint32_t mask = 8;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM2_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 8)); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_1_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_1_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_2_1_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFFC0FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFC0; */
}

void sysram_2_2_power_down(void){
    uint32_t mask = 16;

    *SYSRAM2_PWR_CON |= (0x7 << mask);    /* *SYSRAM2_PWR_CON__F_SYSRAM_2_2_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_2_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_2_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_2_2_force_off(void){
    uint32_t mask = 22;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0040; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFC00000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFC0; */
}

void sysram_2_2_power_on(void){
    uint32_t temp = *SYSRAM2_PWR_CON;
    uint32_t mask = 16;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM2_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 16)); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_1_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_1_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_2_2_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFF80FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFF80; */
}

void sysram_2_3_power_down(void){
    uint32_t mask = 24;

    *SYSRAM2_PWR_CON |= (0x7 << mask);    /* *SYSRAM2_PWR_CON__F_SYSRAM_2_3_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_3_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_3_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_2_3_force_off(void){
    uint32_t mask = 23;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0080; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFF800000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFF80; */
}

void sysram_2_3_power_on(void){
    uint32_t temp = *SYSRAM2_PWR_CON;
    uint32_t mask = 24;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM2_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 24)); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_3_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_3_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM2_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM2_PWR_CON__F_SYSRAM_2_3_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_2_3_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFF00FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFF00; */
}

void sysram_1_0_power_down(void){
    uint32_t mask = 0;

    *SYSRAM1_PWR_CON |= (0x7 << mask);    /* *SYSRAM1_PWR_CON__F_SYSRAM_1_0_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_0_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_1_0_force_off(void){
    uint32_t mask = 16;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0001; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFFF0000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFFF; */
}

void sysram_1_0_power_on(void){
    uint32_t temp = *SYSRAM1_PWR_CON;
    uint32_t mask = 0;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM1_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 0)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_0_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_0_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_0_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_1_0_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFFFEFFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFFE; */
}

void sysram_1_1_power_down(void){
    uint32_t mask = 8;

    *SYSRAM1_PWR_CON |= (0x7 << mask);    /* *SYSRAM1_PWR_CON__F_SYSRAM_1_1_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_1_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_1_1_force_off(void){
    uint32_t mask = 17;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0002; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFFE0000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFFE; */
}

void sysram_1_1_power_on(void){
    uint32_t temp = *SYSRAM1_PWR_CON;
    uint32_t mask = 8;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM1_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 8)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_1_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_1_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_1_1_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFFFCFFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFFC; */
}

void sysram_1_2_power_down(void){
    uint32_t mask = 16;

    *SYSRAM1_PWR_CON |= (0x7 << mask);    /* *SYSRAM1_PWR_CON__F_SYSRAM_1_2_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_2_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_2_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_1_2_force_off(void){
    uint32_t mask = 18;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0004; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFFC0000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFFC; */
}

void sysram_1_2_power_on(void){
    uint32_t temp = *SYSRAM1_PWR_CON;
    uint32_t mask = 16;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM1_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 16)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_2_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_2_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_2_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_1_2_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFFF8FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFF8; */
}

void sysram_1_3_power_down(void){
    uint32_t mask = 24;

    *SYSRAM1_PWR_CON |= (0x7 << mask);    /* *SYSRAM1_PWR_CON__F_SYSRAM_1_3_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_3_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_3_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_1_3_force_off(void){
    uint32_t mask = 19;

    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << mask); /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0x0004; */
    hal_gpt_delay_us(1);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= 0xFFF80000; /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFFC; */
}

void sysram_1_3_power_on(void){
    uint32_t temp = *SYSRAM1_PWR_CON;
    uint32_t mask = 24;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM1_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 24)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_3_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_3_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM1_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_3_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_1_3_force_on(void){
    *MEMORY_SYSRAM1_5_CONTROL_0 &= 0xFFF0FFFF;   /* *MEMORY_SYSRAM1_5_CONTROL_0__F_MEMORY_SYSRAM1_5_FORCE_OFF = 0xFFF0; */
}

void sysram_force_off_unused_ram(uint32_t used_ram_start_addr, uint32_t used_ram_end_addr)
{
    uint32_t i;
    for (i = 0; i < sizeof(spm_ram_block_ctrl_table)/sizeof(spm_ram_block_ctrl_table[0]); i++)
    {
        if (spm_ram_block_ctrl_table[i].start_addr > used_ram_end_addr)
        {
            break;
        }
    }
    for (; i < sizeof(spm_ram_block_ctrl_table)/sizeof(spm_ram_block_ctrl_table[0]); i++)
    {
        spm_ram_block_ctrl_table[i].force_power_down();
    }
}

void sysram_power_down_ram(uint32_t start_addr, uint32_t end_addr)
{
    uint32_t i;
    for (i = 0; i < sizeof(spm_ram_block_ctrl_table)/sizeof(spm_ram_block_ctrl_table[0]); i++)
    {
        if (((spm_ram_block_ctrl_table[i].start_addr) >= start_addr) && ((spm_ram_block_ctrl_table[i].start_addr) <= end_addr))
        {
            spm_ram_block_ctrl_table[i].force_power_down();
        }
    }
}

void sysram_power_on_ram(uint32_t start_addr, uint32_t end_addr)
{
    uint32_t i;
    for (i = 0; i < sizeof(spm_ram_block_ctrl_table)/sizeof(spm_ram_block_ctrl_table[0]); i++)
    {
        if (((spm_ram_block_ctrl_table[i].start_addr) >= start_addr) && ((spm_ram_block_ctrl_table[i].start_addr) <= end_addr))
        {
            spm_ram_block_ctrl_table[i].force_power_on();
        }
    }
}

void sysram_bt_sram_power_down(void){
    *SYSRAM6_PWR_CON |= (0x7 << 0);    /* *SYSRAM6_PWR_CON__F_SYSRAM_6_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM6_PWR_CON &= (0xFFFFFFFF & ~(1 << (1))); /* *SYSRAM6_PWR_CON__F_SYSRAM_6_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM6_PWR_CON &= (0xFFFFFFFF & ~(1 << (2))); /* *SYSRAM6_PWR_CON__F_SYSRAM_6_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_bt_sram_force_off(void){
    *MEMORY_SYSRAM6_CONTROL_0 |= (1 << 16); /* *MEMORY_SYSRAM6_CONTROL_0__F_MEMORY_SYSRAM6_FORCE_OFF = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_bt_sram_power_on(void){
    uint32_t temp = *SYSRAM6_PWR_CON;

    temp &= (0xFFFFFFFF & ~(0x7 << (0)));
    *SYSRAM6_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 0)); /* *SYSRAM6_PWR_CON__F_SYSRAM_6_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM6_PWR_CON |= (1 << (1)); /* *SYSRAM6_PWR_CON__F_SYSRAM_6_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM6_PWR_CON &= (0xFFFFFFFF & ~(1 << (0))); /* *SYSRAM6_PWR_CON__F_SYSRAM_6_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_bt_sram_force_on(void){
    *MEMORY_SYSRAM6_CONTROL_0 &= 0x0000FFFF;   /* *MEMORY_SYSRAM6_CONTROL_0__F_MEMORY_SYSRAM6_FORCE_OFF = 0x0; */
}

void sysram_riscv_0_sram_power_down(void){
    uint32_t mask = 0;

    *SYSRAM8_PWR_CON |= (0x7 << mask);    /* *SYSRAM8_PWR_CON__F_SYSRAM_8_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM8_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM8_PWR_CON__F_SYSRAM_8_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM8_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM8_PWR_CON__F_SYSRAM_8_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_riscv_0_sram_force_off(void){
    uint32_t mask = 16;

    *MEMORY_RISCV_CONTROL_0 |= (1 << mask); /* *MEMORY_RISCV_CONTROL_0__F_MEMORY_RISCV_FORCE_OFF |= (1 << mask) */
    hal_gpt_delay_us(1);
    *MEMORY_RISCV_CONTROL_0 |= 0xFFFF0000; /* *MEMORY_RISCV_CONTROL_0__F_MEMORY_RISCV_FORCE_OFF |= 0xFFFF0000 */
}

void sysram_riscv_0_sram_power_on(void){
    uint32_t temp = *SYSRAM8_PWR_CON;
    uint32_t mask = 0;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM8_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 0)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_3_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM8_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_3_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM8_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM1_PWR_CON__F_SYSRAM_1_3_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_riscv_0_sram_force_on(void){
    *MEMORY_RISCV_CONTROL_0 &= 0xFFFEFFFF;   /* *MEMORY_RISCV_CONTROL_0__F_MEMORY_RISCV_FORCE_OFF = 0xFFFEFFFF; */
}

void sysram_riscv_1_sram_power_down(void){
    uint32_t mask = 8;

    *SYSRAM8_PWR_CON |= (0x7 << mask);    /* *SYSRAM8_PWR_CON__F_SYSRAM_8_1_PWR_CON = 0x7 */
    hal_gpt_delay_us(1);
    *SYSRAM8_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 1))); /* *SYSRAM8_PWR_CON__F_SYSRAM_8_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM8_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 2))); /* *SYSRAM8_PWR_CON__F_SYSRAM_8_1_PWR_CON = 0x1; */
    hal_gpt_delay_us(1);
}

void sysram_riscv_1_sram_power_on(void){
    uint32_t temp = *SYSRAM8_PWR_CON;
    uint32_t mask = 8;

    temp &= (0xFFFFFFFF & ~(0x7 << (mask)));
    *SYSRAM8_PWR_CON = (temp | (((uint32_t) (0x00000101)) << 8)); /* *SYSRAM8_PWR_CON__F_SYSRAM_8_1_PWR_CON = 0x5; */
    hal_gpt_delay_us(1);
    *SYSRAM8_PWR_CON |= (1 << (mask + 1)); /* *SYSRAM8_PWR_CON__F_SYSRAM_8_1_PWR_CON = 0x7; */
    hal_gpt_delay_us(1);
    *SYSRAM8_PWR_CON &= (0xFFFFFFFF & ~(1 << (mask + 0))); /* *SYSRAM8_PWR_CON__F_SYSRAM_8_1_PWR_CON = 0x6; */
    hal_gpt_delay_us(1);
}

void sysram_riscv_1_sram_force_off(void){
    uint32_t mask = 17;

    *MEMORY_RISCV_CONTROL_0 |= (1 << mask); /* *MEMORY_RISCV_CONTROL_0__F_MEMORY_RISCV_FORCE_OFF |= (1 << mask) */
    hal_gpt_delay_us(1);
    *MEMORY_RISCV_CONTROL_0 |= 0xFFFE0000; /* *MEMORY_RISCV_CONTROL_0__F_MEMORY_RISCV_FORCE_OFF |= 0xFFFE0000 */
}

void sysram_riscv_1_sram_force_on(void){
    *MEMORY_RISCV_CONTROL_0 &= 0xFFFCFFFF;   /* *MEMORY_RISCV_CONTROL_0__F_MEMORY_RISCV_FORCE_OFF = 0xFFFCFFFF; */
}

void sysram_5_0_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 14); //RET2N=1, power down on
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (14))); //mem_iso_en_b=0
    sysram_5_0_force_off();
    sysram_5_0_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_5_0_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_5_0_power_on();
    sysram_5_0_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (14)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 14); //RET2N=0, retention on
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_5_0_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 14); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_5_1_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 15); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (15))); //mem_iso_en_b=0
    sysram_5_1_force_off();
    sysram_5_1_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_5_1_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_5_1_power_on();
    sysram_5_1_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (15)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 15); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_5_1_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 15); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_4_0_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 12); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (12))); //mem_iso_en_b=0
    sysram_4_0_force_off();
    sysram_4_0_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_4_0_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_4_0_power_on();
    sysram_4_0_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (12)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 12); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_4_0_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 12); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_4_1_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 13); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (13))); //mem_iso_en_b=0
    sysram_4_1_force_off();
    sysram_4_1_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_4_1_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_4_1_power_on();
    sysram_4_1_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (13)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 13); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_4_1_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 13); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_3_0_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 8); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (8))); //mem_iso_en_b=0
    sysram_3_0_force_off();
    sysram_3_0_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_3_0_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_3_0_power_on();
    sysram_3_0_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (8)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 8); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_3_0_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 8); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_3_1_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 9); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (9))); //mem_iso_en_b=0
    sysram_3_1_force_off();
    sysram_3_1_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_3_1_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_3_1_power_on();
    sysram_3_1_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (9)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 9); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_3_1_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 9); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_3_2_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 10); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (10))); //mem_iso_en_b=0
    sysram_3_2_force_off();
    sysram_3_2_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_3_2_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_3_2_power_on();
    sysram_3_2_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (10)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 10); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_3_2_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 10); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_3_3_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 11); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (11))); //mem_iso_en_b=0
    sysram_3_3_force_off();
    sysram_3_3_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_3_3_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_3_3_power_on();
    sysram_3_3_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (11)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 11); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_3_3_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 11); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_2_0_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 4); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (4))); //mem_iso_en_b=0
    sysram_2_0_force_off();
    sysram_2_0_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_2_0_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_2_0_power_on();
    sysram_2_0_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (4)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 4); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_2_0_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 4); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_2_1_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 5); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (5))); //mem_iso_en_b=0
    sysram_2_1_force_off();
    sysram_2_1_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_2_1_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_2_1_power_on();
    sysram_2_1_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (5)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 5); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_2_1_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 5); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_2_2_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 6); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (6))); //mem_iso_en_b=0
    sysram_2_2_force_off();
    sysram_2_2_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_2_2_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_2_2_power_on();
    sysram_2_2_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (6)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 6); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_2_2_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 6); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_2_3_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 7); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (7))); //mem_iso_en_b=0
    sysram_2_3_force_off();
    sysram_2_3_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_2_3_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_2_3_power_on();
    sysram_2_3_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (7)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 7); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_2_3_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 7); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_1_0_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 0); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (0))); //mem_iso_en_b=0
    sysram_1_0_force_off();
    sysram_1_0_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_1_0_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_1_0_power_on();
    sysram_1_0_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (0)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 0); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_1_0_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 0); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_1_1_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 1); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (1))); //mem_iso_en_b=0
    sysram_1_1_force_off();
    sysram_1_1_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_1_1_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_1_1_power_on();
    sysram_1_1_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (1)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 1); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_1_1_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 1); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_1_2_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 2); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (2))); //mem_iso_en_b=0
    sysram_1_2_force_off();
    sysram_1_2_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_1_2_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_1_2_power_on();
    sysram_1_2_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (2)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 2); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_1_2_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 2); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_1_3_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 3); //RET2N=1
    *MEMORY_SYSRAM1_5_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (3))); //mem_iso_en_b=0
    sysram_1_3_force_off();
    sysram_1_3_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_1_3_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_1_3_power_on();
    sysram_1_3_force_on();
    *MEMORY_SYSRAM1_5_CONTROL_1 |= (1 << (3)); //mem_iso_en_b=1
    *MEMORY_SYSRAM1_5_CONTROL_0 &= ~(1 << 3); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_1_3_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);   
    *MEMORY_SYSRAM1_5_CONTROL_0 |= (1 << 3); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM1_5_CONTROL_2=0x%x", *MEMORY_SYSRAM1_5_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM1_5_CONTROL_0=0x%x", *MEMORY_SYSRAM1_5_CONTROL_0);
}

void sysram_0_0_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << 0); //RET2N=1
    *MEMORY_SYSRAM0_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (16))); //mem_iso_en_b=0
    sysram_0_0_force_off();
    sysram_0_0_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void sysram_0_0_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_0_0_power_on();
    sysram_0_0_force_on();
    *MEMORY_SYSRAM0_CONTROL_1 |= (1 << (16)); //mem_iso_en_b=1
    *MEMORY_SYSRAM0_CONTROL_0 &= ~(1 << 0);//RET2N=0
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void sysram_0_0_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << 0); //RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void sysram_0_1_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << 1);//RET2N=1
    *MEMORY_SYSRAM0_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (17))); //mem_iso_en_b=0
    sysram_0_1_force_off();
    sysram_0_1_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void sysram_0_1_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_0_1_power_on();
    sysram_0_1_force_on();
    *MEMORY_SYSRAM0_CONTROL_1 |= (1 << (17)); //mem_iso_en_b=1
    *MEMORY_SYSRAM0_CONTROL_0 &= ~(1 << 1);//RET2N=0
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void sysram_0_1_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << 1);//RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void sysram_0_2_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << 2);//RET2N=1
    *MEMORY_SYSRAM0_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (18))); //mem_iso_en_b=0
    sysram_0_2_force_off();
    sysram_0_2_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void sysram_0_2_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_0_2_power_on();
    sysram_0_2_force_on();
    *MEMORY_SYSRAM0_CONTROL_1 |= (1 << (18)); //mem_iso_en_b=1
    *MEMORY_SYSRAM0_CONTROL_0 &= ~(1 << 2);//RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_0_2_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << 2);//RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void sysram_0_3_force_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << 3);//RET2N=1
    *MEMORY_SYSRAM0_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (19))); //mem_iso_en_b=0
    sysram_0_3_force_off();
    sysram_0_3_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void sysram_0_3_force_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_0_3_power_on();
    sysram_0_3_force_on();
    *MEMORY_SYSRAM0_CONTROL_1 |= (1 << (19)); //mem_iso_en_b=1
    *MEMORY_SYSRAM0_CONTROL_0 &= ~(1 << 3);//RET2N=0
    hal_nvic_restore_interrupt_mask(mask);
}

void sysram_0_3_enter_non_retention(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM0_CONTROL_0 |= (1 << 3);//RET2N=1
    hal_nvic_restore_interrupt_mask(mask);

    // printk("[SLP][PD][PRDYN] MEMORY_SYSRAM0_CONTROL_2=0x%x", *MEMORY_SYSRAM0_CONTROL_2);
    // printk("[SLP][PD][RET2N] MEMORY_SYSRAM0_CONTROL_0=0x%x", *MEMORY_SYSRAM0_CONTROL_0);
}

void riscv_sram_all_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_RISCV_CONTROL_0 |= (1 << 1); //RET2N=1
    *MEMORY_RISCV_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (17))); //mem_iso_en_b=0
    sysram_riscv_1_sram_force_off();
    sysram_riscv_1_sram_power_down();


    *MEMORY_RISCV_CONTROL_0 |= (1 << 0); //RET2N=1
    *MEMORY_RISCV_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (16))); //mem_iso_en_b=0
    sysram_riscv_0_sram_force_off();
    sysram_riscv_0_sram_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    printk("[SLP][PD][PRDYN] MEMORY_RISCV_CONTROL_2=0x%x", *MEMORY_RISCV_CONTROL_2);
    printk("[SLP][PD][RET2N] MEMORY_RISCV_CONTROL_0=0x%x", *MEMORY_RISCV_CONTROL_0);
}

void riscv_sram_all_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_riscv_0_sram_power_on();
    sysram_riscv_0_sram_force_on();
    *MEMORY_RISCV_CONTROL_1 |= (1 << 16); //mem_iso_en_b=1
    *MEMORY_RISCV_CONTROL_0 &= ~(1 << 0); //RET2N=0

    sysram_riscv_1_sram_power_on();
    sysram_riscv_1_sram_force_on();
    *MEMORY_RISCV_CONTROL_1 |= (1 << 17); //mem_iso_en_b=1=
    *MEMORY_RISCV_CONTROL_0 &= ~(1 << 1); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);

    printk("[SLP][PD][PRDYN] MEMORY_RISCV_CONTROL_2=0x%x", *MEMORY_RISCV_CONTROL_2);
    printk("[SLP][PD][RET2N] MEMORY_RISCV_CONTROL_0=0x%x", *MEMORY_RISCV_CONTROL_0);
}

void bt_sram_all_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    // *MEMORY_SYSRAM6_CONTROL_0 |= (1 << 0); //RET2N=1
    // *MEMORY_SYSRAM6_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (16))); //mem_iso_en_b=0
    // sysram_bt_sram_force_off();
    // sysram_bt_sram_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    printk("[SLP][PD][PRDYN] MEMORY_SYSRAM6_CONTROL_2=0x%x", *MEMORY_SYSRAM6_CONTROL_2);
    printk("[SLP][PD][RET2N] MEMORY_SYSRAM6_CONTROL_0=0x%x", *MEMORY_SYSRAM6_CONTROL_0);

}

void spm_bt_sram_16k_power_down(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    *MEMORY_SYSRAM6_CONTROL_0 |= (1 << 0); //RET2N=1
    *MEMORY_SYSRAM6_CONTROL_1 &= (0xFFFFFFFF & ~(1 << (16))); //mem_iso_en_b=0
    sysram_bt_sram_force_off();
    sysram_bt_sram_power_down();
    hal_nvic_restore_interrupt_mask(mask);

    printk("[SLP][BT][Enter Standby] MEMORY_SYSRAM6_CONTROL_2=0x%x", *MEMORY_SYSRAM6_CONTROL_2);
    printk("[SLP][BT][Enter Standby] MEMORY_SYSRAM6_CONTROL_0=0x%x", *MEMORY_SYSRAM6_CONTROL_0);
}

void spm_bt_sram_16k_power_on(void){
    uint32_t mask;

    hal_nvic_save_and_set_interrupt_mask(&mask);
    sysram_bt_sram_power_on();
    sysram_bt_sram_force_on();
    *MEMORY_SYSRAM6_CONTROL_1 |= (1 << 16); //mem_iso_en_b=1
    *MEMORY_SYSRAM6_CONTROL_0 &= ~(1 << 0); //RET2N=0
    hal_nvic_restore_interrupt_mask(mask);

    printk("[SLP][BT][Leave Standby] MEMORY_SYSRAM6_CONTROL_2=0x%x", *MEMORY_SYSRAM6_CONTROL_2);
    printk("[SLP][BT][Leave Standby] MEMORY_SYSRAM6_CONTROL_0=0x%x", *MEMORY_SYSRAM6_CONTROL_0);
}

#endif
