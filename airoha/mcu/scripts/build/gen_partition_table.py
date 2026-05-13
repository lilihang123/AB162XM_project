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
    parser.add_argument('-h', '--help', action = 'store_true')

    try:
        out_args = parser.parse_args(argv)
    except argparse.ArgumentError:
        print('[Airoha] Error input parameter:', file=sys.stderr)
        show_all_input_parameter()
        show_parser_scripts_usage()
        sys.exit(1)
    return out_args


def construct_partition_table_item(id, attribute, address, length, name, custom_data):
    item_bytes = bytes()
    name = name.encode('utf-8')[:16] if name is not None else b'\x00'*16
    empty_padding = b'\x00'*(16 - len(name))
    item_bytes += name + empty_padding

    item_bytes += struct.pack('I', id)

    attr_value = 0
    for attr in attribute:
        if attr == 'read-only':
            attr_value |= 1 << 0

    item_bytes += struct.pack('I', attr_value)
    item_bytes += struct.pack('I', address)
    item_bytes += struct.pack('I', length)

    custom_data = [0xFFFFFFFF]*8 if custom_data is None else custom_data
    custom_data = b''.join([struct.pack('I', item) for item in custom_data])
    empty_padding = b'\x00'*(32 - len(custom_data))
    item_bytes += custom_data + empty_padding

    return item_bytes


def dummy_end_partition():
    return construct_partition_table_item(0xDEADBEEF, set(), 0xDEADBEEF, 0xDEADBEEF, 'DUMMYEND', None)


def process_specified_memory(memory_name, region_name, device_tree):
    flash_memory = device_tree.get_node(memory_name)
    phy_addr, capacity = flash_memory._get_prop('reg').to_nums(signed = False)
    # print('0x%08X, 0x%08X' %(phy_addr, capacity))

    context = bytes()
    id_set = set()

    flash_partitions = device_tree.get_node('%s-flash-partitions' %(region_name.lower()))
    for node in flash_partitions.node_iter():
        if node is not flash_partitions:
            addr, length = node._get_prop('reg').to_nums(signed = False)
            id = node._get_prop('id').to_num(signed = False)

            id_set_num = len(id_set)
            id_set.add(id)
            id_set_num_new = len(id_set)
            assert id_set_num < id_set_num_new, 'id 0x%08X is duplicated' % id

            attr_set = set()
            if 'read-only' in node.props:
                attr_set.add('read-only')

            label = node._get_prop('label').to_string()
            display_name = node._get_prop('display_name').to_string() if 'display_name' in node.props else None
            custom_data = node._get_prop('customized_data').to_string() if 'customized_data' in node.props else None
            context += construct_partition_table_item(\
                            id, attr_set, \
                            phy_addr + addr, length, \
                            display_name if display_name is not None else label, \
                            custom_data)

    return context


def padding_bytes(data, target_len, padding_value = 0xFF):
    padding_len = target_len - len(data)
    assert(padding_len >= 0)
    return data + bytes([padding_value] * padding_len)


def calc_checksum(context, calc_range = -1):
    # Special Airoha Algorithm
    assert(len(context) % 2 == 0)
    checksum = 0
    calc_range = len(context) if calc_range == -1 else calc_range
    for i in range(0, calc_range, 2):
        # print(f'[Airoha] checksum calc offset: {i}~{i+2} 0x{i:X}~0x{i+2:X}', file=sys.stdout)
        # print(f'[Airoha] checksum before ^: {checksum} 0x{checksum:X}', file=sys.stdout)
        half_word_value = struct.unpack('H', context[i:i+2])[0]
        # print(f'[Airoha] half_word_value is {half_word_value} 0x{half_word_value:X}', file=sys.stdout)
        checksum ^= half_word_value
        # print(f'[Airoha] checksum after ^: {checksum} 0x{checksum:X}', file=sys.stdout)
        # print('', file=sys.stdout)
    # print(f'[Airoha] checksum final in calc_checksum: {checksum} 0x{checksum:X}', file=sys.stdout)
    return struct.pack('<H', checksum)


if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    args = get_parameters_from_command_line_args(sys.argv[1:])
    if args.help == True:
        show_scripts_usage()
    else:
        partition_table_context = bytes()

        # parse device tree file
        device_tree = dtlib.DT(args.file)

        # add main flash partitions( default flash device controlled by SFC )
        partition_table_context += process_specified_memory('flash-memory', 'Main', device_tree)

        # add external flash partitions( external flash device controlled by ESC )
        flash_memory_ext = device_tree.get_node('flash-memory-ext') if device_tree.has_node('flash-memory-ext') else None
        if flash_memory_ext:
            partition_table_context += process_specified_memory('flash-memory-ext', 'External', device_tree)

        partition_table_context += dummy_end_partition()
        # print('[Airoha] Current partition table size: %d' % len(partition_table_context), file=sys.stdout)
        checksum_str = calc_checksum(partition_table_context).hex()
        # print(f'[Airoha] Current partition table checksum: {checksum_str}', file=sys.stdout)

        # with 2 bytes checksum
        assert(len(partition_table_context) <= 4094)
        partition_table_context = padding_bytes(partition_table_context, 4094)

        partition_table_context += calc_checksum(partition_table_context)
        assert(len(partition_table_context) == 4096)

        with open(args.output + os.sep + 'partition_table.bin', 'wb') as mbr:
            mbr.write(partition_table_context)