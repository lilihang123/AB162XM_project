#!/usr/bin/python3
# -*- coding: UTF-8 -*-
#
# * Copyright Statement:
# *
# * (C) 2023  Airoha Technology Corp. All rights reserved.
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
import sys
import struct
import argparse

from copy import deepcopy
from yaml import safe_load


def get_parameters_from_command_line_args(argv):
    '''
    A help function for obtaining command line parameter information.
    '''

    def show_all_input_parameter():
        for idx, item in enumerate(argv):
            print('  argv[%d]:' % idx, item, file=sys.stderr)
        print('', file=sys.stderr)

    out_args = None
    parser = argparse.ArgumentParser(add_help = False)
    parser.add_argument('-f', '--file')
    parser.add_argument('-o', '--output')
    parser.add_argument('-h', '--help', action = 'store_true')

    try:
        out_args = parser.parse_args(argv)
    except argparse.ArgumentError:
        print('Error input parameter:', file=sys.stderr)
        show_all_input_parameter()
        show_parser_scripts_usage()
        sys.exit(1)
    return out_args


def gen_init_files(init_cfg_file, output_dir):
    init_cfg_content = ''
    with open(init_cfg_file, encoding = 'utf-8') as f:
        init_cfg_content = safe_load(f)

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    macro_value_dict = dict()

    init_level_c_hdr_file = output_dir + os.sep + 'air_sys_init_level.h'
    with open(init_level_c_hdr_file, encoding = 'utf-8', mode = 'w') as f:
        for level, module_prio in init_cfg_content.items():
            for module, priority in module_prio.items():
                macro_value_dict['CONFIG_{}_INIT_LEVEL'.format(module.upper())] = level.upper()
                macro_value_dict['CONFIG_{}_INIT_PRIORITY'.format(module.upper())] = priority
        for key, value in macro_value_dict.items():
            if key.find('INIT_PRIORITY') == -1:
                f.write('#define {} {}\n'.format(key, value))

    init_priority_kconfig_file = output_dir + os.sep + 'Kconfig.init_priority'
    with open(init_priority_kconfig_file, encoding = 'utf-8', mode = 'w') as f:
        for key,value in macro_value_dict.items():
            if key.find('INIT_PRIORITY') != -1:
                f.write('config {}\n'.format(key))
                f.write('\tint\n')
                f.write('\tdefault {}\n'.format(value))
                f.write('\n')


if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    args = get_parameters_from_command_line_args(sys.argv[1:])
    if args.help == True:
        show_scripts_usage()
    else:
        gen_init_files(args.file, args.output)