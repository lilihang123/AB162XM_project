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

import re
import sys
import argparse

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
    parser.add_argument('-m', '--map')
    parser.add_argument('-c', '--config')
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


def extract_symbols_from_map(file_path, symbols):
    symbol_value_dict = {}

    content = ''
    with open(file_path, 'r') as file:
        content = file.read()

    for symbol in symbols:
        pattern = rf"^\s*(0x[0-9a-fA-F]+)\s+{symbol}\s*="
        matches = re.findall(pattern, content, re.MULTILINE)

        if matches:
            symbol_value_dict[symbol] = matches[0]
            print(f'[Airoha][Prepare Cross Core Params] found {symbol} equals {matches[0]}')
        else:
            print(f'[Airoha][Prepare Cross Core Params] not found symbol {symbol}')

    return symbol_value_dict


def extract_symbols_from_config(file_path, symbols):
    feature_value_dict = {}
    with open(file_path, encoding = 'utf-8', mode = 'r') as f:
        content = f.readlines()
        print(f'[Airoha][Prepare Cross Core Params] need to match {symbols}')
        for line in content:
            line = line.strip()
            if line.startswith('#define'):
                kconfig_feature, value = line.split(' ')[1], ' '.join(line.split(' ')[2:])
                feature = kconfig_feature.split('CONFIG_')[1]
                for symbol in symbols:
                    if symbol == feature:
                        print(f'[Airoha][Prepare Cross Core Params] found feature {feature} with value {value}')
                        feature_value_dict[feature] = 'y' if value == '1' else 'n'

    return feature_value_dict



if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    # args = get_parameters_from_command_line_args(sys.argv[1:])
    args = get_parameters_from_command_line_args(sys.argv[1:])

    input_map_file = args.map
    autoconf_h_file = args.config
    output_feature_mk = args.output

    link_params_dict = extract_symbols_from_map(input_map_file, ('_cross_core_mem_zi_data_start', '_cross_core_mem_size'))
    config_params_dict = extract_symbols_from_config(autoconf_h_file, ('AIR_FPGA_ENV_ENABLE',))

    with open(output_feature_mk, 'w') as file:
        for key, value in link_params_dict.items():
            print(f'[Airoha][Prepare Cross Core Params] write LINKER_SCRIPT_OPTION += -D{key}={value}')
            file.write(f'LINKER_SCRIPT_OPTION += -D{key}={value}\n')

        for key, value in config_params_dict.items():
            print(f'[Airoha][Prepare Cross Core Params] {key}={value}')
            file.write(f'{key}={value}\n')
