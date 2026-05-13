/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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
#include <stdio.h>
#include <string.h>
#include "cosim_script_parser.h"
#include "cosim_mdm.h"
//#include "hal_clock_1577_simple.h"

enum enumeration_script_id {
    SCRIPT_ID_START = 0,
    SCRIPT_ID_CMD,
    SCRIPT_ID_EVT,
    SCRIPT_ID_PEER_WAIT,
    SCRIPT_ID_PEER_SET,
    SCRIPT_ID_WAIT,
    SCRIPT_ID_END,
    
} SCRIPT_ID;

U32 gScriptOffset = 0;
U8 *gScriptWaitPktPtr = 0;
U16 gScriptWaitPktLen = 0;
U16 gScriptTotalLine = 0;
U8 gScriptWait = 0;
U8 gScriptPeerWait = 0;

U8 gScriptCmpBuf[1024];
U16 gScriptCmpOffset = 0;
U16 gScriptCopyOffset = 0;
U16 gScriptCmpTotalLen = 0;

uint8_t *cosim_script_parser_get_rx_ptr(void)
{
    return (uint8_t*)COSIM_SCRIPT_MEMORY_BASE;
}

VOID ScriptParseEvtBufCmp(VOID)
{
    if (gScriptWait && (gScriptCmpTotalLen != 0)) {
        MDM_TM_PRINTF("[SPEvt] Cmp pkt size %d", gScriptWaitPktLen);
        MDM_TM_DUMP((char *)&gScriptCmpBuf[gScriptCmpOffset], gScriptWaitPktLen);
        if (memcmp(gScriptCmpBuf + gScriptCmpOffset, gScriptWaitPktPtr, gScriptWaitPktLen) == 0)
        {
            MDM_TM_PRINTF("[SPEvt] Cmp PASS");
            gScriptWait = 0;
            gScriptCmpTotalLen -= gScriptWaitPktLen;
            gScriptCmpOffset = (gScriptCmpOffset + gScriptWaitPktLen) % 1024;;
        }
        else
        {
            MDM_TM_PRINTF("[SPEvt] Cmp FAIL");
            MDM_TM_ENDFAIL;
        }
    }
}

VOID ScriptParseEvtBufBackup(U8* buf, U16 len)
{
    memcpy(gScriptCmpBuf + gScriptCopyOffset, buf, len);
    gScriptCopyOffset = (gScriptCopyOffset + len) % 1024;;
    gScriptCmpTotalLen += len;
    ScriptParseEvtBufCmp();
}

U16 ScriptParseStart(U8 *buf)
{
    U16 length = buf[0] | (buf[1] << 4);
    // length: 2 byte
    gScriptTotalLine = length;
    MDM_TM_PRINTF("[SP][Start] total line: %d", gScriptTotalLine);
    return 1;
}

U16 ScriptParseCmd(U8 *buf)
{
    U16 length = buf[0] | (buf[1] << 4);
    // length: 2 byte
    MDM_TM_PRINTF("[SP][Cmd] length %d", length);
    MDM_TM_DUMP((char *)&buf[2], length);
    //ScriptHciCmdSend(&buf[2], length);
    return length;
}

U16 ScriptParseEvt(U8 *buf)
{
    U16 length = buf[0] | (buf[1] << 4);
    // length: 2 byte
    //ScriptHciEvtWait(&buf[2], length);
    gScriptWaitPktPtr = buf + 2; 
    gScriptWaitPktLen = length;
    MDM_TM_PRINTF("[SP][Evt] buf %x len %d", gScriptWaitPktPtr, gScriptWaitPktLen);
    gScriptWait = 1;
    ScriptParseEvtBufCmp();
    return length;
}

U16 ScriptParsePeerWait(U8 *buf)
{
    U16 length = buf[0] | (buf[1] << 4);
    // length: 2 byte
    gScriptPeerWait = buf[2];
    MDM_TM_PRINTF("[SP][WaitP] length %d, peer_wait %x", length, gScriptPeerWait);
    return length;
}

U16 ScriptParsePeerSet(U8 *buf)
{
    U16 length = buf[0] | (buf[1] << 4);
    // length: 2 byte
    MDM_TM_SET_PEER_WAIT(buf[2]);
    MDM_TM_PRINTF("[SP][SetP] length %d peer_wait %x", length, buf[2]);
    return length;
}

U16 ScriptParseWait(U8 *buf)
{
    U16 length = buf[0] | (buf[1] << 4);
    // length: 2 byte
    MDM_TM_PRINTF("[SP][Wait] length %d, wait %d ms", length, buf[2]);
	//clock_top_mux_ctrl(CLK_SYS_SEL, MUX_SYS_IDX_XO);
	//clock_top_mux_ctrl(CLK_BT_HOP_SEL, MUX_BT_HOP_IDX_XO);
    MDM_TM_WAIT_MS(buf[2]);
    return length;
}

U8 ScriptParse(U8 *buf)
{
    U32 i = 0;
    //MDM_TM_PRINTF("[SP] %x, offset %d, addr %x", buf[i], i, &buf[i]);
    
    //while (1)
    {
        switch (buf[i])
        {
            case SCRIPT_ID_START:
                i += ScriptParseStart(&buf[i + 1]);
                break;
            case SCRIPT_ID_CMD:
                i+= ScriptParseCmd(&buf[i + 1]);
                break;
            case SCRIPT_ID_EVT:
                i += ScriptParseEvt(&buf[i + 1]);
                break;
            case SCRIPT_ID_PEER_WAIT:
                i += ScriptParsePeerWait(&buf[i + 1]);
                break;
            case SCRIPT_ID_PEER_SET:
                i += ScriptParsePeerSet(&buf[i + 1]);
                break;
            case SCRIPT_ID_WAIT:
                i += ScriptParseWait(&buf[i + 1]);
                break;
            case SCRIPT_ID_END:
                MDM_TM_ENDSIM;
                while(1){};
                break;
            default:
                MDM_TM_PRINTF("Parse buf[%d] 0x%x Error\n\n", i, buf[i]);
                MDM_TM_ENDFAIL;
                while(1){};
                return 0;
        }
    }
    return i;
}

