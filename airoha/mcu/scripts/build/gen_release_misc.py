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
import sys
import shutil
import argparse
import dataclasses

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
    parser.add_argument('-o', '--output')
    parser.add_argument('-h', '--help', action = 'store_true')

    try:
        out_args = parser.parse_args(argv)
    except argparse.ArgumentError:
        print('Error input parameter:', file=sys.stderr)
        show_all_input_parameter()
        sys.exit(1)
    return out_args


@dataclasses.dataclass
class FirmwareProcRule:
    origin: str = str()
    new: str = None
    optional: bool = False
    kconfig: str = None



def replace_pattern_in_file(file_path, pattern):
    content = None
    with open(file_path, "r") as file:
        content = file.readlines()

    for rule in pattern:
        for idx, line in enumerate(content):
            if rule.origin in line:
                content[idx] = line.replace(rule.origin, rule.new)

    with open(file_path, "w") as file:
        file.write(''.join(content))


def debug_release_in_one_folder(output_dir):
    src_file = output_dir + os.sep + 'flash_download.cfg'
    debug_file = output_dir + os.sep + 'flash_download_debug.cfg'
    release_file = output_dir + os.sep + 'flash_download_release.cfg'

    assert os.path.exists(src_file)
    shutil.copy(src_file, release_file)

    shutil.move(src_file, debug_file)
    if os.path.exists(output_dir + os.sep + 'storage.bin'):
        proc_rules = (
            FirmwareProcRule(
                origin = 'storage.bin',
                new = 'storage_release.bin',
            ),
        )
        replace_pattern_in_file(release_file, proc_rules)


        shutil.move(output_dir + os.sep + 'storage.bin',  output_dir + os.sep + 'storage_debug.bin')
        shutil.move(output_dir + os.sep + 'nvkey.xml',  output_dir + os.sep + 'nvkey_debug.xml')
        proc_dbg_rules = (
            FirmwareProcRule(
                origin = 'storage.bin',
                new = 'storage_debug.bin',
            ),
        )
        replace_pattern_in_file(debug_file, proc_dbg_rules)


def debug_release_in_separate_folder(output_dir):
    src_cfg_file = output_dir + os.sep + 'flash_download.cfg'
    assert os.path.exists(src_cfg_file)

    debug_dir = output_dir + os.sep + 'debug'
    release_dir = output_dir + os.sep + 'release'

    os.makedirs(debug_dir, exist_ok = True)
    os.makedirs(release_dir, exist_ok = True)

    src_files = [file for file in os.listdir(output_dir) if os.path.isfile(os.path.join(output_dir, file))]

    for item in src_files:
        file_name, file_ext = os.path.splitext(item)
        # print(file_name, file_ext)
        release_file_name = file_name + '_release' + file_ext
        src_file = output_dir + os.sep + item
        if release_file_name in src_files:
            shutil.copy(src_file, debug_dir)
            os.remove(src_file)
            continue
        if '_release' in file_name:
            shutil.copy(src_file, release_dir + os.sep + file_name.replace('_release', '') + file_ext)
            os.remove(src_file)
            continue
        shutil.copy(src_file, debug_dir)
        shutil.copy(src_file, release_dir)
        os.remove(src_file)


if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    # args = get_parameters_from_command_line_args(sys.argv[1:])
    args = get_parameters_from_command_line_args(sys.argv[1:])

    # debug_release_in_one_folder(args.output)
    debug_release_in_separate_folder(args.output)