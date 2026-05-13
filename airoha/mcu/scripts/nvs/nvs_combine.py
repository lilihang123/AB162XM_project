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
import subprocess

from lxml import etree
from copy import deepcopy

def show_scripts_usage():
    '''
    Refer to the man page of the command line to display the help information of the script.
    '''

    print('Name\n\tnvs_combine - According to the strategy, combine the input nvkey.xml files into one file.\n')
    print('SYNOPSIS\n\tpython3 nvs_combine.py [-h] [-f FILE [FILE ...]] [-s STRATEGY] [-o OUTPUT]\n')
    print('OPTIONS')
    print('\t-f: XML files containing nvs item\n')
    print('\t-s: The strategy to take when merging data items.')
    print('\t    ERROR: disable NVS ID duplication and prompt by build errors')
    print('\t    USE_FIRST: enable NVS ID duplication and use the value at the first occurrence\n')
    print('\t    USE_LAST: enable NVS ID duplication and use the value at the last occurrence\n')
    print('\t-o: output file path\n')


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
    parser.add_argument('-f', '--file', nargs = '+')
    parser.add_argument('-s', '--strategy')
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

def confirm_no_repeat(root):
    # Note:
    # Commented items will not appear in the results of findall,
    # but they will be traversed during iteration.
    # number_of_items = len([item for item in root])
    # number_of_items_with_unique_id = len(set(item.get('KeyID') for item in root.findall('NVKey')))

    data_items = [item.get('KeyID') for item in root.findall('NVKey')]
    number_of_items = len(data_items)
    number_of_items_with_unique_id = len(set(data_items))

    assert(number_of_items == number_of_items_with_unique_id)


if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    args = get_parameters_from_command_line_args(sys.argv[1:])
    if args.help == True:
        show_scripts_usage()
    else:
        available_strategy = ['ERROR', 'USE_FIRST', 'USE_LAST']
        if args.strategy not in available_strategy:
            show_scripts_usage()
            sys.exit(1)

        assert(len(args.file) >= 1)
        tree = etree.parse(args.file[0])
        root = tree.getroot()

        # duplicates are not allowed within a single file
        confirm_no_repeat(root)

        for xml in args.file[1:]:
            _tmp_tree = etree.parse(xml)
            # duplicates are not allowed within a single file
            confirm_no_repeat(_tmp_tree.getroot())

            for element in _tmp_tree.getroot():
                if isinstance(element, etree._Comment):
                    continue
                # print(f"tag: {element.tag}\nattributes: {element.attrib}\ntext: {element.text}")
                match args.strategy:
                    case 'ERROR':
                        print('ERROR: Duplicate KeyID are not allowed.', file = sys.stderr)
                        sys.exit(1)
                    case 'USE_FIRST':
                        if len(root.findall(f"NVKey[@KeyID='{element.attrib['KeyID']}']")) == 0:
                            root.append(element)
                    case 'USE_LAST':
                        # print(element.attrib['KeyID'])
                        # print(f"NVKey[@KeyID='{element.attrib['KeyID']}']")
                        for item in root.findall(f"NVKey[@KeyID='{element.attrib['KeyID']}']"):
                            # print(f"delete elements of tag: {element.tag}\nattributes: {element.attrib}\ntext: {element.text}")
                            root.remove(item)
                        root.append(element)

        if not os.path.isfile(args.output):
            open(args.output, 'w').close()

        tree.write(args.output, pretty_print = True)