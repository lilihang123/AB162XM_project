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

#include "hal_flash.h"
#ifdef HAL_FLASH_MODULE_ENABLED
#include "memory_attribute.h"
#include "hal_flash_custom_memorydevice.h"
#include "hal_flash_opt.h"
#include "hal_flash_combo_init.h"
#include "hal_flash_combo_defs.h"
#include "hal_flash_mtd.h"
#include "hal_flash_mtd_internal.h"
#if defined(__SERIAL_FLASH__)
#include "hal_flash_sf.h"
#endif
#include "hal_nvic.h"


//#include "br_GFH_cmem_id_info.h"
typedef struct {
    GFH_Header            m_gfh_hdr;
    CMEMEntryIDList       m_data;
} GFH_CMEM_ID_INFO_v1;


//-----------------------------------------------------------------------------
// MCP ID Table
//-----------------------------------------------------------------------------
#define COMBO_MEM_STRUCT_HEAD  COMBO_MEM_ID_GFH_HEADER, { COMBO_MEM_ID_VER, COMBO_MEM_DEVICE_COUNT, {
#define COMBO_MEM_STRUCT_FOOT  } }

const GFH_CMEM_ID_INFO_v1 combo_mem_id_list = {
    COMBO_MEM_STRUCT_HEAD
    {
        //1, W25Q16JW WB 16Mbit
        CMEM_TYPE_SERIAL_NOR_FLASH,
        3,  // Valid ID length
        {0xEF, 0x60, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00}  // Flash ID
    },
    {
        //2, GD25LE16E GD 16Mbit
        CMEM_TYPE_SERIAL_NOR_FLASH,
        3,  // Valid ID length
        {0xC8, 0x60, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00}  // Flash ID
    },
    {
        //10, XMC 16
        CMEM_TYPE_SERIAL_NOR_FLASH,
        3,  // Valid ID length
        {0x20, 0x50, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00}  // Flash ID
    },
    COMBO_MEM_STRUCT_FOOT
};


int32_t CMEM_EMIINIT_Index(void);

void CMEM_EMIINIT_ReadID(const uint16_t CS, void *BaseAddr, uint16_t *flashid);


static signed short int cmem_emiinit_index = -1;
//static signed short int cmem_index = -1;

uint8_t nor_id[4];

bool CMEM_CheckValidDeviceID(uint8_t *id)
{
    int32_t i, j;
    const CMEMEntryID *id_list = NULL;

    id_list = combo_mem_id_list.m_data.List;

    for (i = 0; i < COMBO_MEM_DEVICE_COUNT; i++) {
        /*Compare ID*/
        for (j = 0; j < id_list[i].IDLength; j++) {
            if (id_list[i].ID[j] != id[j]) {
                break;
            }
        }

        if (j == id_list[i].IDLength)   {
            return true;
        }
    }

    return false;
}

ATTR_TEXT_IN_TCM_RETENTION void NOR_ReadID(const uint16_t CS, volatile uint16_t *BaseAddr, uint16_t *flashid)
{
    uint32_t savedMask;
    uint8_t cmd, id[SF_FLASH_ID_LENGTH], i;

    cmd = SF_CMD_READ_ID;
    hal_nvic_save_and_set_interrupt_mask(&savedMask);
    SFI_Dev_Command_Ext(CS, &cmd, id, 1, SF_FLASH_ID_LENGTH);
    hal_nvic_restore_interrupt_mask(savedMask);

    for (i = 0; i < SF_FLASH_ID_LENGTH; i++) {
        flashid[i] = id[i];
    }
}

#define UID_MAX_LENGH   (16)
ATTR_TEXT_IN_TCM_RETENTION void NOR_Get_UID(uint8_t *uid, uint8_t uid_length)
{
    uint32_t savedMask;
    uint8_t cmd[5];

    if (UID_MAX_LENGH > 16) {
        return;
    }

    /* Read Flash UID */
    cmd[0] = 0x4B;
    cmd[1] = 0x0;
    cmd[2] = 0x0;
    cmd[3] = 0x0;
    cmd[4] = 0x0;
    hal_nvic_save_and_set_interrupt_mask(&savedMask);
    SFI_Dev_Command_Ext (0, (uint8_t *)&cmd, uid, 5, uid_length);
    hal_nvic_restore_interrupt_mask(savedMask);
}

uint8_t NOR_Get_Customer_UID(void)
{
    //customer UID is the first byte of UID data
    uint8_t uid_4byte[4];
    NOR_Get_UID(uid_4byte, 4);
    return uid_4byte[0];
}

const CMEMEntryID *CMEM_GetIDEntry(uint32_t index)
{
    return &combo_mem_id_list.m_data.List[index];
}

void NOR_ReadUID(const uint16_t CS, uint8_t *flashuid, uint32_t uid_length)
{
    (void)CS;
    NOR_Get_UID(flashuid, uid_length);
}


ATTR_TEXT_IN_TCM_RETENTION int32_t CMEM_EMIINIT_Index()
{
    int32_t i, j;
    CMEMFlashID id;
    const CMEMEntryID *id_list = NULL;

    if (cmem_emiinit_index >= 0) {
        return cmem_emiinit_index;
    }

    NOR_ReadID(0, (void *)NOR_FLASH_BASE_ADDRESS, id.NOR);
    // seach CMEM list for specific Flash ID
    id_list = combo_mem_id_list.m_data.List;
    nor_id[0] = id.NOR[0];
    nor_id[1] = id.NOR[1];
    nor_id[2] = id.NOR[2];
    nor_id[3] = id.NOR[3];
    for (i = 0; i < COMBO_MEM_DEVICE_COUNT; i++) {
        // Check 1: Compare ID
        for (j = 0; j < id_list[i].IDLength; j++) {
            if (id_list[i].ID[j] != id.NOR[j]) {
                break;
            }
        }
        // Check 2: Compare RegionInfo
        if (j == id_list[i].IDLength) {
            cmem_emiinit_index = i;
            break;
        }
    }
    return cmem_emiinit_index;  // entry not found
}

ATTR_TEXT_IN_TCM_RETENTION uint32_t protect_flash_last_1mb()
{
    uint8_t cmd[2];
    uint8_t srp0, srp1;

    cmd[0] = 0x5;
    SFI_Dev_Command_Ext(0, cmd, &srp0, 1, 1);
#if 0
    if ((srp0 & 0x80) == 0) {
        //WEN
        cmd[0] = 0x6;
        SFI_Dev_Command_Ext(0, cmd, NULL, 1, 0);
        cmd[0] = 0x1;
        //set 1 to srp0 and bp0/1/2
        cmd[1] = (0x94 | srp0);
        SFI_Dev_Command_Ext(0, cmd, NULL, 2, 0);
    }
#endif
    cmd[0] = 0x35;
    SFI_Dev_Command_Ext(0, cmd, &srp1, 1, 1);
#if 0
    if ((srp1 & 0x1) == 0) {
        //WEN
        cmd[0] = 0x6;
        SFI_Dev_Command_Ext(0, cmd, NULL, 1, 0);
        cmd[0] = 0x31;
        ////set 1 to srp1 and QE
        cmd[1] = (0x3 | srp1);
        SFI_Dev_Command_Ext(0, cmd, NULL, 2, 0);
    }
#endif
    return (srp0 | (srp1 << 8));
}


#endif // HAL_FLASH_MODULE_ENABLED


