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
import argparse

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
    parser.add_argument('-f', '--file')
    parser.add_argument('-o', '--output')
    parser.add_argument('-b', '--board')
    parser.add_argument('-p', '--product')
    parser.add_argument('-h', '--help', action = 'store_true')

    try:
        out_args = parser.parse_args(argv)
    except argparse.ArgumentError:
        print('Error input parameter:', file=sys.stderr)
        show_all_input_parameter()
        show_parser_scripts_usage()
        sys.exit(1)
    return out_args


def add_general_setting(file, platform, product_category, cfg_ver):
    print('###############################################################################################',file = file)
    print('#  General Setting',file = file)
    print('###############################################################################################',file = file)
    print('general:',file = file)
    print('    platform: %s' %platform ,file = file)
    print('    product_category: %s' %product_category ,file = file)
    print('    config_version: %s' %cfg_ver,file = file)
    print('',file = file)


def add_main_region_setting(file, region_name):
    print('###############################################################################################', file = file)
    print('#  %s Region Setting' %(region_name), file = file)
    print('###############################################################################################', file = file)
    print('%s_region:' %(region_name.lower()), file = file)
    print('    address_type: physical', file = file)
    print('    rom_list:', file = file)


def append_download_entry(file, start_address, end_address, label, display):
    print('        - rom:', file = file)
    print('            file: %s.bin' %label, file = file)
    print('            name: %s' %display, file = file)
    print('            begin_address: 0x%08X' %start_address, file = file)
    print('            end_address: 0x%08X' %end_address, file = file)


def process_specified_memory(file, memory_name, region_name, device_tree):
    flash_memory = device_tree.get_node(memory_name)
    phy_addr, capacity = flash_memory._get_prop('reg').to_nums(signed = False)
    # print('0x%08X, 0x%08X' %(phy_addr, capacity))
    add_main_region_setting(download_cfg, region_name)

    flash_partitions = device_tree.get_node('%s-flash-partitions' %(region_name.lower()))
    for node in flash_partitions.node_iter():
        if node is not flash_partitions:
            label = node._get_prop('label').to_string()
            begin, length = node._get_prop('reg').to_nums(signed = False)
            download = True if 'download' in node.props else False
            display_name = node._get_prop('display_name').to_string() if 'display_name' in node.props else None
            assert(((download == True) and (display_name is not None))
                or ((download == False) and (display_name is None)))
            # print(label, begin, length, download, display_name)
            if download == True:
                append_download_entry(
                    download_cfg,
                    phy_addr + begin,
                    phy_addr + begin + length,
                    label,
                    display_name
                )


if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    args = get_parameters_from_command_line_args(sys.argv[1:])
    if args.help == True:
        show_scripts_usage()
    else:
        with open(args.output + os.sep + 'flash_download.cfg', 'wt', encoding = 'utf-8') as download_cfg:
            add_general_setting(download_cfg, args.board, args.product, 'v2.0')

            # parse device tree file
            device_tree = dtlib.DT(args.file)

            # add main_region( default flash device controlled by SFC )
            process_specified_memory(download_cfg, 'flash-memory', 'Main', device_tree)

            # add external_region( external flash device controlled by ESC )
            flash_memory_ext = device_tree.get_node('flash-memory-ext') if device_tree.has_node('flash-memory-ext') else None
            if flash_memory_ext:
                process_specified_memory(download_cfg, 'flash-memory-ext', 'External', device_tree)