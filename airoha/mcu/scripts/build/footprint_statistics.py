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
import glob
import shutil
import argparse

from pathlib import Path

from os import sep as os_sep
from csv import writer as csv_writer
from dataclasses import dataclass


def show_parser_scripts_usage():
    '''
    Refer to the man page of the command line to display the help information of the script.
    '''


def get_parameters_from_command_line_args(argv, logger = None):
    '''
    A help function for obtaining command line parameter information.
    '''
    def show_all_input_parameter():
        for idx, item in enumerate(argv):
            print('  argv[%d]:' % idx, item, file=sys.stderr)
        print('', file=sys.stderr)

    out_args = None
    parser = argparse.ArgumentParser(add_help = False)
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


def copy_files(src_dir, dest_dir, file_extensions = tuple()):
    for file_extension in file_extensions:
        # copy normal files
        pattern = os.path.join(src_dir, '*' + file_extension)
        source_files = glob.glob(pattern)
        for src_file in source_files:
            dest_file = os.path.join(dest_dir, os.path.basename(src_file))
            shutil.copy(src_file, dest_file)

        # copy hidden files
        pattern = os.path.join(src_dir, file_extension)
        source_files = glob.glob(pattern)
        for src_file in source_files:
            dest_file = os.path.join(dest_dir, os.path.basename(src_file))
            shutil.copy(src_file, dest_file)


def find_footprint_source_files(target_path):
    fp_src_symbols_files = list()
    for file in Path(target_path).rglob('*'):
        if file.is_file():
            name, ext = file.stem, file.suffix
            dir = str(file.parent)
            if ext == '.symbols':
                fp_src_symbols_files.append(Path(dir + os_sep + name + ext))
    return fp_src_symbols_files


@dataclass
class FootprintStatisticsEntry:
    memory_type: str = ''
    total: int = -1
    used: int = -1
    free: int = -1

    @staticmethod
    def readable_attr_list():
        allowed_fields = (
            "{:<30}".format("Item"),
            "{:<30}".format("Total"),
            "{:<30}".format("Used"),
            "{:<30}".format("Free")
        )
        return allowed_fields

    def __iter__(self):
        tmp_tuple = (
            self.memory_type,
            self.total,
            self.used,
            self.free
        )
        formatted_tutple = (f'{item:<30}' for item in tmp_tuple)
        return iter(formatted_tutple)

    def check_validity(self):
        return True if (self.total == (self.used + self.free)) else False
    
    def print(self):
        print(f'{self.memory_type}:')
        print(f'    total: {self.total}')
        print(f'    used: {self.used}')
        print(f'    free: {self.free}')


if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    # args = get_parameters_from_command_line_args(sys.argv[1:])
    args = get_parameters_from_command_line_args(sys.argv[1:])

    print(f'[Airoha][Footprint][Statistics] processing {Path(args.output).resolve()}')
    script_path = Path(sys.executable).parent
    proj_out_path = Path(args.output)
    debug_path = proj_out_path / 'debug'
    assert(debug_path.exists())

    footprint_out_path = debug_path / 'footprint'
    if not footprint_out_path.exists():
        print(f'[Airoha][Footprint][Statistics] create directory {footprint_out_path.resolve()}')
        footprint_out_path.mkdir(parents = True, exist_ok = True)

    for item in find_footprint_source_files(debug_path):
        # print(f'[Airoha][Footprint][Statistics] find symbols file: {item}')
        target_statistics_file = footprint_out_path / f'{os.path.basename(item)}.csv'
        if 'riscv' in str(item):
            new_file_name = 'riscv_' + str(item.stem) + '.csv'
            target_statistics_file = footprint_out_path / new_file_name
        elif 'zephyr' in str(item):
            new_file_name = item.parent.name + '.csv'
            target_statistics_file = footprint_out_path / new_file_name
        else:
            new_file_name = item.name + '.csv'
            target_statistics_file = footprint_out_path / new_file_name

        # print(f'[Airoha][Footprint][Statistics] target statistics file: {target_statistics_file}')

        src_content = None
        with open(item, "r") as src_file:
            src_content = src_file.readlines()
        dst_content = None

        fp_statistics_entries = list()
        def find_target_entry(condition):
            for entry in fp_statistics_entries:
                if condition(entry):
                    return entry
            return None

        symbols_pattern = r"([0-9a-fA-F]+) (\w+) __fp_pattern_(\w+)_(total|used|free)$"
        for line in src_content:
            match = re.match(symbols_pattern, line)
            if match:
                hex_size = match.group(1)
                attribute = match.group(2)
                memory_type = match.group(3)
                property_name = match.group(4)
                # print(f'[Airoha][Footprint][Statistics] {hex_size} {memory_type} {property_name}')
                if memory_type not in [item.memory_type for item in fp_statistics_entries]:
                    tmp_entry = FootprintStatisticsEntry()
                    tmp_entry.memory_type = memory_type
                    setattr(tmp_entry, property_name, int(hex_size, 16))
                    fp_statistics_entries.append(tmp_entry)
                    # print(f'[Airoha][Footprint][Statistics] append {memory_type}')
                else:
                    target_entry = find_target_entry(lambda entry: (entry.memory_type == memory_type))
                    setattr(target_entry, property_name, int(hex_size, 16))
                    # print(f'[Airoha][Footprint][Statistics] set {property_name} as {int(hex_size, 16)} for {memory_type}')
        if len(fp_statistics_entries):
            with open(target_statistics_file, "w", newline = '') as dst_file:
                _writer = csv_writer(dst_file)
                sym_attr = FootprintStatisticsEntry.readable_attr_list()
                _writer.writerow(sym_attr)
                _writer.writerows(fp_statistics_entries)
                # for item in fp_statistics_entries:
                #     item.print()