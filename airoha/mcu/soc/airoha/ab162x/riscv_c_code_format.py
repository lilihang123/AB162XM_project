#!/usr/bin/python3
# -*- coding: UTF-8 -*-
#
# * Copyright Statement:
# *
# * (C) 2024  Airoha Technology Corp. All rights reserved.
# *
# * This software/firmware and related documentation ("Airoha Software") are
# * protected under relevant copyright laws. The information contained herein
# * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
# * Without the prior written permission of Airoha and/or its licensors,
# * any reproduction, modification, use or disclosure of Airoha Software,
# * and information contained herein, in whole or in part, shall be strictly prohibited.
# * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
# * if you have agreed to and been bound by the applicable license agreement with
# * Airoha ("License Agreement") and been granted explicit permission to do so within
# * the License Agreement ("Permitted User").  If you are not a Permitted User,
# * please cease any access or use of Airoha Software immediately.
# * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
# * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
# * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
# * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
# * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
# * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
# * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
# *
# * Airoha restricted information */

import sys
from codecs import encode, decode


def riscv_load_converter(proj_abbr, feature_abbr, proj_idx):
    bin_content = bytes()
    with open(f"{proj_abbr}.bin", "rb") as f:
        bin_content = f.read()
    array_size = len(bin_content)

    file_content = list()
    file_content.append('#include <stdio.h>')
    file_content.append('#include "hal_riscv_ctl.h"')
    file_content.append('#include "memory_attribute.h"')
    file_content.append('')
    file_content.append(f'ATTR_ALIGN(4) static const uint8_t riscv_firmware[{array_size}] =')
    file_content.append('{')
    for idx in range(0, array_size, 16):
        end = (idx + 16) if (idx + 16) < array_size else array_size
        chunk = bin_content[idx: end]
        file_content.append('    ' + \
            ', '.join(f'0x{byte:02X}' for byte in chunk) + \
            f', /* {idx} ~ {end-1} */')
    file_content.append('};')
    file_content.append('')
    file_content.append(f'__attribute__((section(".riscv_scenario" "." "{proj_idx}" "." "{proj_abbr}" "." "{feature_abbr}")))')
    file_content.append(f'const riscv_scenario_info_t riscv_firmware_{proj_idx}_{proj_abbr}_{feature_abbr} =')
    file_content.append('{')
    file_content.append('    .firmware_load_addr = (uint32_t)(&riscv_firmware[0]),')
    file_content.append(f'    .firmware_len = {array_size},')
    file_content.append('};')

    with open(f"{proj_abbr}.c", 'wt') as f:
        f.write('\n'.join(file_content))


if __name__ == '__main__':
    riscv_load_converter(sys.argv[1], sys.argv[2], sys.argv[3])