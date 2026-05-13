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

#ifndef _RACE_CMD_CLOCK_H_
#define _RACE_CMD_CLOCK_H_

#include "race_cmd.h"

#ifdef RACE_CLOCK_CMD_ENABLE
#include <zephyr/sys/printk.h>

#define RACE_CLOCK_CMD_LOG_ENABLE
#ifdef RACE_CLOCK_CMD_LOG_ENABLE
//#define race_clk_log_info(fmt, cnt, ...)   LOG_MSGID_I(race, "[RACE_CLK] "fmt, cnt, ##__VA_ARGS__)
//#define race_clk_log_warn(fmt, cnt, ...)   LOG_MSGID_W(race, "[RACE_CLK] "fmt, cnt, ##__VA_ARGS__)
//#define race_clk_log_err(fmt, cnt, ...)    LOG_MSGID_E(race, "[RACE_CLK] "fmt, cnt, ##__VA_ARGS__)
#define race_clk_log_info(msg, cnt, ...)   printk("[RACE_CLK] "msg, ##__VA_ARGS__)
#define race_clk_log_warn(msg, cnt, ...)   printk("[RACE_CLK] "msg, ##__VA_ARGS__)
#define race_clk_log_err(msg, cnt, ...)    printk("[RACE_CLK] "msg, ##__VA_ARGS__)
#else
#define race_clk_log_info(fmt, cnt, ...)
#define race_clk_log_warn(fmt, cnt, ...)
//#define race_clk_log_err(fmt, cnt, ...)    LOG_MSGID_E(race, "[RACE_CLK] "fmt, cnt, ##__VA_ARGS__)
#define race_clk_log_err(msg, cnt, ...)    printk("[RACE_CLK] "msg, ##__VA_ARGS__)
#endif

/*****************************************************************************
 * CONSTANT DEFINITIONS
 *****************************************************************************/
#define _RACE_ID_CLOCK_BEGIN   0x02C0
#define _RACE_ID_CLOCK_END     0x02C7  /* Include reserved RACE ID */

/* RACE ID */
enum {
    RACE_ID_CAPID = _RACE_ID_CLOCK_BEGIN,
    RACE_ID_DCXO,
    RACE_ID_DVFS,
    RACE_ID_CLOCK
};

#ifndef CAPID_VAL_MAX
#define CAPID_VAL_MAX          511
#endif

/*****************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************/
typedef struct {
    uint8_t  sub_cmd;
    uint8_t  val;
} PACKED race_clk_common_uint8_val_only_t;

typedef struct {
    uint8_t  sub_cmd;
    uint16_t val;
} PACKED race_clk_common_uint16_val_only_t;

typedef struct {
    uint8_t  sub_cmd;
    uint32_t val;
} PACKED race_clk_common_uint32_val_only_t;

/*****************************************************************************
 * FUNCTION DECLARATIONS
 *****************************************************************************/
/*!
  @brief Process clock related RACE commands.

  @param pRaceHeaderCmd This parameter represents the raw data such as "05 5A...".
  @param Lenth Total bytes of this RACE command.
  @param channel_id Channel identifier
*/
void *RACE_CmdHandler_clock(ptr_race_pkt_t pRaceHeaderCmd, uint16_t Length, uint8_t channel_id);

#endif /* RACE_CLOCK_CMD_ENABLE */
#endif /* _RACE_CMD_CLOCK_H_ */

