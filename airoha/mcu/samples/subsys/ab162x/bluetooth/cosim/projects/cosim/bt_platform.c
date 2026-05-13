/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */
/* MediaTek restricted information */

#include "bt_platform_internal.h"

/* Kernel includes. */
//#include "bt_memory.h"
#include "bt_type_def.h"
//#include <bt_hci.h>

//#include "syslog.h"
#include "bt_debug.h"
#include "bt_sm_math.h"
#include "bt_system.h"
#include "bt_timer.h"
#include "bt_hci_internal.h"
#include "bt_gap_le_internal.h"
#include "bt_hci_log.h"

#ifdef BT_USE_SW_ECC
#include "p_256_ecc_pp.h"
#endif

#define BT_OS_TIMER_EXPIRED 0x01
#define BT_OS_RX_EVENT      0x02
#define BT_OS_TX_EVENT      0x04
#define BT_POWER_OFF_EVENT  0x10
#define BT_OS_MODULE_HANDLE 0x20
#define BT_OS_RX_OOM_EVENT  0x40

static uint32_t bt_task_events = 0;
static bool bt_task_running = false;
static uint32_t bt_os_stack_mutex;
#ifdef __BT_HB_DUO__
extern uint8_t bt_gap_DUT_mode;
#endif
void bt_driver_recv(void);
bt_status_t bt_driver_power_on(void);

extern bt_status_t bt_driver_power_off(void);

extern int32_t hci_log_cmd(unsigned char *buf, int32_t length);

extern char *bt_driver_lib_verno(void);
extern uint8_t *bt_driver_get_n9_build_date(uint8_t *len);
extern char *bt_stack_lib_verno(void);
extern char *bt_hfp_get_lib_verno(void);
extern char *bt_hsp_get_lib_verno(void);
extern char *bt_a2dp_get_lib_verno(void);
extern char *bt_avrcp_get_lib_verno(void);
extern char *bt_avrcp_eh_get_lib_verno(void);
extern char *bt_spp_get_lib_verno(void);
extern char *bt_pbapc_get_lib_verno(void);
extern char *bt_aws_get_lib_verno(void);
extern char *bt_aws_mce_get_lib_verno(void);

extern char *bt_airupdate_get_lib_verno(void);

extern char *bt_driver_lib_lastest_commit(void);
extern uint8_t *bt_driver_get_n9_git_version(uint8_t *len);
extern char *bt_stack_lib_lastest_commit(void);
extern char *bt_hfp_get_lib_lastest_commit(void);
extern char *bt_hsp_get_lib_lastest_commit(void);
extern char *bt_a2dp_get_lib_lastest_commit(void);
extern char *bt_avrcp_get_lib_lastest_commit(void);
extern char *bt_avrcp_eh_get_lib_lastest_commit(void);
extern char *bt_spp_get_lib_lastest_commit(void);
extern char *bt_pbapc_get_lib_lastest_commit(void);
extern char *bt_aws_get_lib_lastest_commit(void);
extern char *bt_aws_mce_get_lib_lastest_commit(void);
extern char *bt_airupdate_get_lib_lastest_commit(void);
extern void bt_hci_process_rx_oom(void);

extern char *bt_hid_get_lib_verno(void);
extern char *bt_hid_get_lib_lastest_commit(void);
extern uint8_t bt_driver_firmware_type_set(bt_firmware_type_t type);
extern bt_firmware_type_t bt_driver_firmware_type_get(void);

void bt_driver_trigger_controller_codedump(void);
void default_bt_driver_trigger_controller_codedump(void);
uint8_t default_bt_driver_firmware_type_set(bt_firmware_type_t type);
bt_firmware_type_t default_bt_driver_firmware_type_get(void);

static void default_bt_memory_info_notify(void *p);
/* Weak symbol declaration */
#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_driver_trigger_controller_codedump=_default_bt_driver_trigger_controller_codedump")
#pragma comment(linker, "/alternatename:_bt_memory_info_notify=_default_bt_memory_info_notify")
#pragma comment(linker, "/alternatename:_bt_driver_firmware_type_set=_default_bt_driver_firmware_type_set")
#pragma comment(linker, "/alternatename:_bt_driver_firmware_type_get=_default_bt_driver_firmware_type_get")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_driver_trigger_controller_codedump = default_bt_driver_trigger_controller_codedump
#pragma weak bt_memory_info_notify = default_bt_memory_info_notify
#pragma weak bt_driver_firmware_type_set = default_bt_driver_firmware_type_set
#pragma weak bt_driver_firmware_type_get = default_bt_driver_firmware_type_get
#else
#error "Unsupported Platform"
#endif

static void default_bt_memory_info_notify(void *p)
{
}

void default_bt_driver_trigger_controller_codedump(void)
{

}

uint8_t default_bt_driver_firmware_type_set(bt_firmware_type_t type)
{
    return 0;
}

bt_firmware_type_t default_bt_driver_firmware_type_get(void)
{
    return 0;
}

char *bt_hfp_get_lib_verno_ext(void)
{
    return NULL;
}
char *bt_hsp_get_lib_verno_ext(void)
{
    return NULL;
}
char *bt_a2dp_get_lib_verno_ext(void)
{
    return NULL;
}

char *bt_avrcp_get_lib_verno_ext(void)
{
    return NULL;
}

char *bt_avrcp_eh_get_lib_verno_ext(void)
{
    return NULL;
}

char *bt_spp_get_lib_verno_ext(void)
{
    return NULL;
}

extern char *bt_pbapc_get_lib_verno_ext(void)
{
    return NULL;
}

extern char *bt_aws_get_lib_verno_ext(void)
{
    return NULL;
}

extern char *bt_aws_mce_get_lib_verno_ext(void)
{
    return NULL;
}

extern char *bt_hid_get_lib_verno_ext(void)
{
    return NULL;
}

char *bt_driver_lib_lastest_commit_ext(void)
{
    return NULL;
}

uint8_t *bt_driver_get_n9_build_date_ext(uint8_t *len)
{
    return NULL;
}

uint8_t *bt_driver_get_n9_git_version_ext(uint8_t *len)
{
    return NULL;
}

char *bt_hfp_get_lib_lastest_commit_ext(void)
{
    return NULL;
}
char *bt_hsp_get_lib_lastest_commit_ext(void)
{
    return NULL;
}
char *bt_a2dp_get_lib_lastest_commit_ext(void)
{
    return NULL;
}

char *bt_avrcp_get_lib_lastest_commit_ext(void)
{
    return NULL;
}

char *bt_avrcp_eh_get_lib_lastest_commit_ext(void)
{
    return NULL;
}

char *bt_spp_get_lib_lastest_commit_ext(void)
{
    return NULL;
}

char *bt_pbapc_get_lib_lastest_commit_ext(void)
{
    return NULL;
}

char *bt_aws_get_lib_lastest_commit_ext(void)
{
    return NULL;
}

char *bt_aws_mce_get_lib_lastest_commit_ext(void)
{
    return NULL;
}

extern char *bt_airupdate_get_lib_verno_ext(void)
{
    return NULL;
}

char *bt_airupdate_get_lib_lastest_commit_ext(void)
{
    return NULL;
}

char *bt_hid_get_lib_lastest_commit_ext(void)
{
    return NULL;
}
#if 0
#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_driver_lib_verno=_bt_driver_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_driver_lib_verno = bt_driver_lib_verno_ext
#else
#error "Unsupported Platform"
#endif
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_driver_lib_lastest_commit=_bt_driver_lib_lastest_commit_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_driver_lib_lastest_commit = bt_driver_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_driver_get_n9_build_date=_bt_driver_get_n9_build_date_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_driver_get_n9_build_date = bt_driver_get_n9_build_date_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_driver_get_n9_git_version=_bt_driver_get_n9_git_version_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_driver_get_n9_git_version = bt_driver_get_n9_git_version_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_hfp_get_lib_verno=_bt_hfp_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_hfp_get_lib_verno = bt_hfp_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_hfp_get_lib_lastest_commit=_bt_hfp_get_lib_lastest_commit")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_hfp_get_lib_lastest_commit = bt_hfp_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_hsp_get_lib_verno=_bt_hsp_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_hsp_get_lib_verno = bt_hsp_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_hsp_get_lib_lastest_commit=_bt_hsp_get_lib_lastest_commit")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_hsp_get_lib_lastest_commit = bt_hsp_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_a2dp_get_lib_verno=_bt_a2dp_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_a2dp_get_lib_verno = bt_a2dp_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_a2dp_get_lib_lastest_commit=_bt_a2dp_get_lib_lastest_commit")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_a2dp_get_lib_lastest_commit = bt_a2dp_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_avrcp_get_lib_verno=_bt_avrcp_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_avrcp_get_lib_verno = bt_avrcp_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_avrcp_get_lib_lastest_commit=_bt_avrcp_get_lib_lastest_commit_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_avrcp_get_lib_lastest_commit = bt_avrcp_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_avrcp_eh_get_lib_verno=_bt_avrcp_eh_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_avrcp_eh_get_lib_verno = bt_avrcp_eh_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_avrcp_eh_get_lib_lastest_commit=_bt_avrcp_eh_get_lib_lastest_commit_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_avrcp_eh_get_lib_lastest_commit = bt_avrcp_eh_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif


#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_spp_get_lib_verno=_bt_spp_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_spp_get_lib_verno = bt_spp_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_spp_get_lib_lastest_commit=_bt_spp_get_lib_lastest_commit_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_spp_get_lib_lastest_commit = bt_spp_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_pbapc_get_lib_verno=_bt_pbapc_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_pbapc_get_lib_verno = bt_pbapc_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_pbapc_get_lib_lastest_commit=_bt_pbapc_get_lib_lastest_commit_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_pbapc_get_lib_lastest_commit = bt_pbapc_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_aws_get_lib_verno=_bt_aws_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_aws_get_lib_verno = bt_aws_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_aws_get_lib_lastest_commit=_bt_aws_get_lib_lastest_commit_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_aws_get_lib_lastest_commit = bt_aws_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_aws_mce_get_lib_verno=_bt_aws_mce_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_aws_mce_get_lib_verno = bt_aws_mce_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_aws_mce_get_lib_lastest_commit=_bt_aws_mce_get_lib_lastest_commit_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_aws_mce_get_lib_lastest_commit = bt_aws_mce_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_airupdate_get_lib_verno=_bt_airupdate_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_airupdate_get_lib_verno = bt_airupdate_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_airupdate_get_lib_lastest_commit=_bt_airupdate_get_lib_lastest_commit_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_airupdate_get_lib_lastest_commit = bt_airupdate_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_hid_get_lib_verno=_bt_hid_get_lib_verno_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_hid_get_lib_verno = bt_hid_get_lib_verno_ext
#else
#error "Unsupported Platform"
#endif

#if _MSC_VER >= 1500
#pragma comment(linker, "/alternatename:_bt_hid_get_lib_lastest_commit=_bt_hid_get_lib_lastest_commit_ext")
#elif defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM)
#pragma weak bt_hid_get_lib_lastest_commit = bt_hid_get_lib_lastest_commit_ext
#else
#error "Unsupported Platform"
#endif


//log_create_module(bt_hb, PRINT_LEVEL_INFO);

uint32_t bt_os_get_stack_mutex(void)
{
    return bt_os_stack_mutex;
}

void bt_os_take_stack_mutex(void)
{
    if (bt_os_stack_mutex) {
        bt_os_layer_take_mutex(bt_os_stack_mutex);
    }
}

void bt_os_give_stack_mutex(void)
{
    if (bt_os_stack_mutex) {
        bt_os_layer_give_mutex(bt_os_stack_mutex);
    }
}

int32_t bt_timer_start_timer(uint32_t ms)
{
    bt_os_layer_start_timer(ms);
    return 0;
}

int32_t bt_timer_stop_timer()
{
    bt_os_layer_stop_timer();
    return 0;
}

static void bt_timer_os_expire(void)
{
    uint32_t mask;
    bt_os_layer_disable_interrupt(&mask);
    bt_task_events |= BT_OS_TIMER_EXPIRED;
    bt_os_layer_enable_interrupt(mask);
    bt_trigger_interrupt(1);
}

void bt_hummingbird_deinit(void)
{
    bt_timer_stop_all_timer();
}

/* For util/timer use, get current system tick */
uint32_t bt_timer_get_current_tick(void)
{
    return bt_os_layer_get_system_tick();
}

#define ARRAY_TO_STREAM(p, a, len) {register int ijk; for (ijk = 0; ijk < len;        ijk++) *(p)++ = (uint8_t) a[ijk];}
#define REVERSE_ARRAY_TO_STREAM(p, a, len)  {register int ijk; for (ijk = 0; ijk < len; ijk++) *(p)++ = (uint8_t) a[len - 1 - ijk];}

/*static void bt_reverse_array_to_steam(uint8_t *p, const uint8_t *array, uint32_t length)
{
    uint32_t i;
    for (i=0; i<length; i++) {
        p[i] = array[length-i-1];
    }
}*/

void bt_sm_encrypt(bt_smp_key_t output, const bt_smp_key_t key, const bt_smp_key_t data)
{
    bt_os_layer_aes_buffer_t encrypted_data, plain_text, key_struct;
    uint8_t buffer[32] = {0};

    key_struct.buffer = (void *)key;
    key_struct.length = sizeof(bt_smp_key_t);

    plain_text.buffer = (void *)data;
    plain_text.length = sizeof(bt_smp_key_t);

    encrypted_data.buffer = buffer;
    encrypted_data.length = 32;//check size

    bt_os_layer_aes_encrypt(&encrypted_data, &plain_text, &key_struct);

    bt_memcpy(output, buffer, sizeof(bt_smp_key_t));

}

void bt_sm_random(bt_smp_key_t output)
{
    uint8_t i;
    for (i = 0; i < sizeof(bt_smp_key_t); i += 2) {
        uint16_t r =  bt_os_layer_generate_random();
        bt_memcpy(output + i, &r, 2);
    }
}

#ifdef BT_USE_SW_ECC
const uint8_t bt_private_key[32] =  {0xbd, 0x1a, 0x3c, 0xcd, 0xa6, 0xb8, 0x99, 0x58, 0x99, 0xb7, 0x40, 0xeb, 0x7b, 0x60, 0xff, 0x4a,
                                     0x50, 0x3f, 0x10, 0xd2, 0xe3, 0xb3, 0xc9, 0x74, 0x38, 0x5f, 0xc5, 0xa3, 0xd4, 0xf6, 0x49, 0x3f
                                    };

void bt_sm_read_public_key(bt_smp_public_key_t *public_key)
{
    Point   local_publ_key;
    uint8_t private_key[32];

    p_256_init_curve(8);

    bt_memcpy(private_key, bt_private_key, 32);
    ECC_PointMult(&local_publ_key, &(curve_p256.G), (BT_DWORD *)private_key, 8);
    bt_memcpy(public_key->x, local_publ_key.x, 32);
    bt_memcpy(public_key->y, local_publ_key.y, 32);
}

void bt_sm_compute_dhkey(uint8_t *dhkey, const bt_smp_public_key_t *public_key)
{
    Point       peer_publ_key, new_publ_key;
    uint8_t     private_key[32];

    bt_memcpy(private_key, bt_private_key, 32);
    bt_memcpy(peer_publ_key.x, public_key->x, 32);
    bt_memcpy(peer_publ_key.y, public_key->y, 32);

    ECC_PointMult(&new_publ_key, &peer_publ_key, (BT_DWORD *) private_key, 8);

    bt_memcpy(dhkey, new_publ_key.x, 32);
}
#endif

void bt_hci_notify(void)
{
    uint32_t mask;
    bt_os_layer_disable_interrupt(&mask);
    bt_task_events |= BT_OS_RX_EVENT;
    bt_os_layer_enable_interrupt(mask);
    bt_trigger_interrupt(1);
}

void bt_hci_notify_from_task(void)
{
    uint32_t mask;
    bt_os_layer_disable_interrupt(&mask);
    bt_task_events |= BT_OS_RX_EVENT;
    bt_os_layer_enable_interrupt(mask);
    bt_trigger_interrupt(0);
}

void bt_hci_tx_notify(void)
{
    uint32_t mask;
    bt_os_layer_disable_interrupt(&mask);
    bt_task_events |= BT_OS_TX_EVENT;
    bt_os_layer_enable_interrupt(mask);
    bt_trigger_interrupt(0);
}

void bt_power_off_notify(void)
{
    uint32_t mask;
    bt_os_layer_disable_interrupt(&mask);
    bt_task_events |= BT_POWER_OFF_EVENT;
    bt_os_layer_enable_interrupt(mask);
    bt_trigger_interrupt(0);
}

void bt_module_handle_notify(void)
{
    uint32_t mask;
    bt_os_layer_disable_interrupt(&mask);
    bt_task_events |= BT_OS_MODULE_HANDLE;
    bt_os_layer_enable_interrupt(mask);
    bt_trigger_interrupt(0);
}

void bt_hci_rx_oom_notify(void)
{
    uint32_t mask;
    //BT_LOG_MSGID_W("BT", BT_001, 0);
    bt_os_layer_disable_interrupt(&mask);
    bt_task_events |= BT_OS_RX_OOM_EVENT;
    bt_os_layer_enable_interrupt(mask);
    bt_trigger_interrupt(0);
}

int32_t hci_log_util_info(unsigned char *buf, int32_t length)
{
    uint8_t info[256];
    if (length > 252) {
        /* Out of memory */
        //BT_LOG_MSGID_E("BT", BT_002, 0);
        return -1;
    }
    info[0] = 0;
    info[1] = 0x1a;
    info[2] = 0xfc;
    info[3] = 0;
    memcpy(info + 4, buf, length);

    bt_hci_log(0, info, length + 4);

    return 0;
}

void bt_lib_version_hci()
{
    unsigned char *ver_str = NULL;

    //driver version log
    ver_str = (unsigned char *)bt_driver_lib_verno();
    if (ver_str != NULL) {
        //BT_LOG_MSGID_I("BT", BT_003, 0);
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_driver_lib_lastest_commit();
    if (ver_str != NULL) {
        //BT_LOG_MSGID_I("BT", BT_004, 0);
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    //controller version log
    uint8_t len;
    ver_str = (unsigned char *)bt_driver_get_n9_build_date(&len);
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_driver_get_n9_git_version(&len);
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    //stack version log
    //BT_LOG_MSGID_I("BT", BT_005, 0);
    ver_str = (unsigned char *)bt_stack_lib_verno();
    if (ver_str != NULL) {
        //BT_LOG_MSGID_I("BT", BT_006, 0);
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_stack_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
#ifdef __BT_HB_DUO__
    //hfp version log
    ver_str = (unsigned char *)bt_hfp_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_hfp_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //hsp version log
    ver_str = (unsigned char *)bt_hsp_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_hsp_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //a2dp version log
    ver_str = (unsigned char *)bt_a2dp_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_a2dp_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //avrcp version log
    ver_str = (unsigned char *)bt_avrcp_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_avrcp_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //avrcp_eh version log
    ver_str = (unsigned char *)bt_avrcp_eh_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_avrcp_eh_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //spp version log
    ver_str = (unsigned char *)bt_spp_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_spp_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //pbap version log
    ver_str = (unsigned char *)bt_pbapc_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_pbapc_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //aws version log
    ver_str = (unsigned char *)bt_aws_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_aws_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //aws mce version log
    ver_str = (unsigned char *)bt_aws_mce_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_aws_mce_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //airupdate version log
    ver_str = (unsigned char *)bt_airupdate_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_airupdate_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }

    //hid version log
    ver_str = (unsigned char *)bt_hid_get_lib_verno();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
    ver_str = (unsigned char *)bt_hid_get_lib_lastest_commit();
    if (ver_str != NULL) {
        hci_log_util_info(ver_str, strlen((const char *)ver_str));
    }
#endif
}


bool bt_is_bt_task_running(void)
{
    return bt_task_running;
}

void bt_init(void)
{
    /* mutex init */
    if (bt_os_stack_mutex == 0) {
        bt_os_stack_mutex = bt_os_layer_create_mutex();
    }

    /* OS timer init */
    bt_os_layer_init_timer();
    bt_os_layer_register_timer_callback(bt_timer_os_expire);

    /* print lib version */
    bt_lib_version_hci();
}
/**
 * @brief     This function handle the bt events.
 * @return    #BT_STATUS_SUCCESS means the operation was successful, otherwise failed.
 */
bt_status_t bt_handle_interrupt(void)
{
    uint32_t current_events, mask;
    BT_MUTEX_LOCK();
    bt_task_running = true;
    bt_os_layer_disable_interrupt(&mask);
    current_events = bt_task_events;
    bt_task_events = 0;
    bt_os_layer_enable_interrupt(mask);

    if (current_events & BT_OS_RX_OOM_EVENT) {
        bt_hci_process_rx_oom();
    }

    if (current_events & BT_OS_TIMER_EXPIRED) {
        bt_timer_check_timeout_handler();
    }

    if (current_events & BT_OS_RX_EVENT) {
        bt_driver_recv();
        bt_hci_process_packet();
    }

    if (current_events & BT_OS_TX_EVENT) {
        bt_hci_process_packet();
    }

    if (current_events & BT_POWER_OFF_EVENT) {
        bt_status_t st = BT_STATUS_SUCCESS;
        if (BT_POWER_RESET_SW != bt_power_reset_type) {
            st = bt_driver_power_off();
            //BT_LOG_MSGID_I("BT", BT_007, 1, st);
        }
        bt_app_event_callback_wrap(BT_POWER_OFF_CNF, st, NULL);
        if (0 != bt_power_reset_type) {
            bt_power_on(NULL, NULL);
        }
    }
    if (current_events & BT_OS_MODULE_HANDLE) {
        //bt_module_handle_process();
    }

    bt_task_running = false;
    bt_app_event_callback(BT_MEMORY_FREE_GARBAGE_IND, BT_STATUS_SUCCESS, NULL);
    BT_MUTEX_UNLOCK();
    return BT_STATUS_SUCCESS;
}

void *bt_memcpy(void *dest, const void *src, uint32_t size)
{
    return memcpy(dest, src, size);
}

int bt_memcmp(const void *buf1, const void *buf2, uint32_t size)
{
    return memcmp(buf1, buf2, size);
}

void *bt_memset(void *buf, uint8_t ch, uint32_t size)
{
    return memset(buf, ch, size);
}

void *bt_memmove(void *dest, const void *src, uint32_t size)
{
    return memmove(dest, src, size);
}

void bt_md5_init(bt_md5_context *ctx)
{
    bt_os_layer_md5_init((bt_os_md5_context *)ctx);
}

void bt_md5_free(bt_md5_context *ctx)
{
    bt_os_layer_md5_free((bt_os_md5_context *)ctx);
}

void bt_md5_clone(bt_md5_context *dst,  const bt_md5_context *src)
{
    bt_os_layer_md5_clone((bt_os_md5_context *)dst, (const bt_os_md5_context *)src);
}

void bt_md5_starts(bt_md5_context *ctx)
{
    bt_os_layer_md5_starts((bt_os_md5_context *)ctx);
}

void bt_md5_process(bt_md5_context *ctx, const unsigned char data[64])
{
    bt_os_layer_md5_process((bt_os_md5_context *)ctx, data);
}

void bt_md5_update(bt_md5_context *ctx, const unsigned char *input, unsigned int ilen)
{
    bt_os_layer_md5_update((bt_os_md5_context *)ctx, input, ilen);
}

void bt_md5_finish(bt_md5_context *ctx, unsigned char output[16])
{
    bt_os_layer_md5_finish((bt_os_md5_context *)ctx, output);
}

uint8_t bt_firmware_type_set(bt_firmware_type_t type)
{
    return bt_driver_firmware_type_set(type);
}

bt_firmware_type_t bt_firmware_type_get(void)
{
    return bt_driver_firmware_type_get();
}
