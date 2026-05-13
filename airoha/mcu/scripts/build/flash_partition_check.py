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
import argparse
import dataclasses

##########################################################################
####    Add the library provided by zephyr to operate dts file.    #######
##########################################################################
python_devicetree_src = os.path.join(
    os.path.dirname(__file__),
    '..',    # scripts
    '..',    # mcu
    '..',    # airoha
    '..',    # codebase
    'zephyr',
    'scripts',
    'dts',
    'python-devicetree',
    'src'
)
sys.path.insert(0, os.path.abspath(python_devicetree_src))
from devicetree import dtlib
##########################################################################


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
    parser.add_argument('-f', '--folder')
    parser.add_argument('-h', '--help', action = 'store_true')

    try:
        out_args = parser.parse_args(argv)
    except argparse.ArgumentError:
        print('Error input parameter:', file=sys.stderr)
        show_all_input_parameter()
        show_parser_scripts_usage()
        sys.exit(1)
    return out_args


def find_dts_files(i_dir):
    dts_files = list()
    for root, dirs, files in os.walk(i_dir):
        for file in files:
            if file.endswith('.dts'):
                dts_files.append(os.path.join(root, file))
    return dts_files


def extract_flash_partition_symbols_from_dts_file(i_dts_file_path):
    device_tree = dtlib.DT(i_dts_file_path)
    flash_partitions = device_tree.get_node('main-flash-partitions')
    symbols_dict = dict()
    for node in flash_partitions.node_iter():
        if node is not flash_partitions:
            addr, length = node._get_prop('reg').to_nums(signed = False)
            node_label = node.labels[0]
            symbols_dict[node_label] = (addr, length)
    return symbols_dict


def all_dicts_equal(dict_list):
    if not dict_list:
        return True
    first_dict = dict_list[0]
    first_dict_keys = first_dict.keys()
    return all(d.keys() == first_dict_keys and all(d.get(k) == first_dict[k] for k in first_dict_keys) for d in dict_list)


def boot_partition_equal(dict_list):
    if not dict_list:
        return True
    first_dict = dict_list[0]
    first_dict_keys = ['boot_partition']
    return all(all(d.get(k) == first_dict[k] for k in first_dict_keys) for d in dict_list)


def show_dicts_diff(dict_name_list, dict_value_list):
    value_list_len = len(dict_value_list)
    assert(value_list_len == len(dict_name_list))

    for idx, item in enumerate(dict_name_list):
        print('[Airoha][FlashPartition Check] dts[%d]: %s' %(idx, item))

    for i in range(value_list_len):
        for j in range(i + 1, value_list_len):
            key_set = set(dict_value_list[i].keys()) | set(dict_value_list[j].keys())
            for key in key_set:
                value_i = dict_value_list[i].get(key, 'N/A')
                if isinstance(value_i, tuple):
                    value_i = " ".join(("0x%08X" % value for value in value_i))
                value_j = dict_value_list[j].get(key, 'N/A')
                if isinstance(value_j, tuple):
                    value_j = " ".join(("0x%08X" % value for value in value_j))
                if value_i != value_j:
                    text = '[Airoha][FlashPartition Check] value(%s(%d, %s) <=> %s(%d, %s)) of key(%s) are different, please check !!!'%(
                        value_i, i, os.path.basename(dict_name_list[i]),
                        value_j, j, os.path.basename(dict_name_list[j]),
                        key)
                    print(text)



if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    # args = get_parameters_from_command_line_args(sys.argv[1:])
    args = get_parameters_from_command_line_args(sys.argv[1:])

    start_time = time.time()
    dts_files = find_dts_files(args.folder)
    compare_dts_files = list()
    dts_flash_partition_symbol_list = list()
    for dts in dts_files:
        symbols_dict = extract_flash_partition_symbols_from_dts_file(dts)
        if len(symbols_dict) != 0:
            dts_flash_partition_symbol_list.append(symbols_dict)
            compare_dts_files.append(dts)

    if True != boot_partition_equal(dts_flash_partition_symbol_list):
        print('[Airoha][FlashPartition Check] Flash Partitions Not Match', file=sys.stderr)
        print('[Airoha][FlashPartition Check] not boot_partition symbol are equal', file=sys.stderr)
        show_dicts_diff(compare_dts_files, dts_flash_partition_symbol_list)
        sys.exit(1)

    end_time = time.time()
    print('[Airoha][FlashPartition Check] time: %d min %d seconds' %(
            round((end_time - start_time)/60.0),
            round((end_time - start_time)%60.0)
        )
    )
