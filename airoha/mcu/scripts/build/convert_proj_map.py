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

import os
import re
import sys
import time
from collections import namedtuple


# add . into search path for RDs use ABSOLUTE path of build.py
airoha_build_service = os.path.join(os.path.dirname(__file__))
sys.path.insert(0, os.path.abspath(airoha_build_service))

# add ./airoha/mcu/scripts/build into search path for RDs when they copy build.py to the root of codebase
airoha_build_service = os.path.join(
    os.path.dirname(__file__),
    'airoha',
    'mcu',
    'scripts',
    'build',
)
sys.path.insert(0, os.path.abspath(airoha_build_service))

import airoha_build_service_common




if __name__ == '__main__':
    projs, dockerq_image = airoha_build_service_common.find_project_list()
    bash_proj_map_template = 'map__%s__%s=( \\\n\
[0]="%s" \\\n\
[1]="%s" \\\n\
[2]="%s" \\\n\
[3]="%s" \\\n\
[4]="%s" \\\n\
[5]="%s" \\\n\
)\n'
    for proj, proj_dict in projs.items():
        board, proj_name = proj.split('__')
        proj_path = proj_dict['proj']
        sysbuild_conf = proj_dict['sysbuild_conf'] if 'sysbuild_conf' in proj_dict.keys() else ''
        mcuboot_dtc_overlay = proj_dict['mcuboot']['DTC_OVERLAY_FILE'] if 'mcuboot' in proj_dict.keys() else ''
        mcuboot_conf = proj_dict['mcuboot']['CONF_FILE'] if 'mcuboot' in proj_dict.keys() else ''

        all_proj_keys = set(proj_dict.keys())
        not_main_proj_keys = set(['proj', 'sysbuild_conf', 'mcuboot'])
        main_proj_key_set = all_proj_keys - not_main_proj_keys
        assert(len(main_proj_key_set)==1)
        main_proj_key = next(iter(main_proj_key_set))

        main_proj_dtc_overlay = proj_dict[main_proj_key]['DTC_OVERLAY_FILE'] if 'DTC_OVERLAY_FILE' in proj_dict[main_proj_key].keys() else ''
        main_proj_conf = proj_dict[main_proj_key]['CONF_FILE'] if 'CONF_FILE' in proj_dict[main_proj_key].keys() else ''
        _bash_proj = bash_proj_map_template%(
            board,
            proj_name,
            proj_path,
            sysbuild_conf,
            mcuboot_dtc_overlay,
            mcuboot_conf,
            main_proj_dtc_overlay,
            main_proj_conf
        )
        print(_bash_proj)

    build_cmd_temp = './build.sh %s %s'
    for proj, proj_dict in projs.items():
        board, proj_name = proj.split('__')
        print(build_cmd_temp%(board, proj_name))