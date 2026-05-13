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
import enum
import glob
import yaml
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
    parser.add_argument('-f', '--file')
    parser.add_argument('-v', '--version')
    parser.add_argument('-h', '--help', action = 'store_true')

    try:
        out_args = parser.parse_args(argv)
    except argparse.ArgumentError:
        print('Error input parameter:', file=sys.stderr)
        show_all_input_parameter()
        show_parser_scripts_usage()
        sys.exit(1)
    return out_args


def obtain_zephyr_version(version_file):
    assert(os.path.exists(version_file))
    version = 0
    digit_num_max = 4
    with open(version_file, 'r') as f:
        _content = f.read().splitlines()
        for line in _content:
            digit_str = line.split('=')[-1].strip()
            if digit_str != '':
                digit = int(digit_str)
                # The operator precedence is different from that in C language,
                # so we need to use parentheses to make it work correctly.
                version = (version << 8) + digit
                digit_num_max -= 1
            if digit_num_max == 0:
                break
    return version



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


@dataclasses.dataclass
class FirmwareProcRule:
    origin: str = str()
    new: str = None
    optional: bool = False
    kconfig: str = None


if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    # args = get_parameters_from_command_line_args(sys.argv[1:])
    args = get_parameters_from_command_line_args(sys.argv[1:])
    zephyr_version = obtain_zephyr_version(args.version)
    print(f'[Airoha][Collect Firmware] obtain zephyr version: 0x{zephyr_version:0{8}X}')

    with open(args.file, 'r') as f:
        domains_yaml_content = yaml.safe_load(f)

        default_proj = domains_yaml_content['default']
        default_proj_bin = str()

        bootloader_proj = str()
        bootloader_proj_bin = str()

        system_build_config = os.path.dirname(os.path.realpath(__file__)) + os.sep + 'build_config.yaml'

        work_dir = domains_yaml_content['build_dir']
        top_download_dir = work_dir + os.sep + 'download'
        os.makedirs(top_download_dir, exist_ok=True)
        print(f'[Airoha][Collect Firmware] create directory {top_download_dir}')

        top_debug_dir = work_dir + os.sep + 'debug'
        os.makedirs(top_debug_dir, exist_ok=True)
        print(f'[Airoha][Collect Firmware] create directory {top_debug_dir}')

        # copy firmware files to download directory and other needed files to debug directory
        for domain in domains_yaml_content['domains']:
            name, build_dir = domain['name'], domain['build_dir']
            dest_dir = top_debug_dir + os.sep + domain['name']
            os.makedirs(dest_dir, exist_ok=True)
            print(f'[Airoha][Collect Firmware] create directory {dest_dir}')

            # copy debug files to dest_dir to have enough information to decode the exception dump
            src_dir = build_dir + os.sep + 'zephyr'
            debug_file_ext_tuple = ('.dts', '.elf', '.map', '.bin', '.hex', '.yaml', '.config', '.cmd', '.lst', '.json', '.symbols', '.stat')
            copy_files(src_dir, dest_dir, debug_file_ext_tuple)
            print(f'[Airoha][Collect Firmware] copy debug files which file extension match {debug_file_ext_tuple} from {src_dir} to {dest_dir}')

            runner_file = os.sep.join([build_dir, 'zephyr', 'runners.yaml'])
            with open(runner_file, 'r') as runner:
                runner_content = yaml.safe_load(runner)
                bin_file = runner_content['config']['bin_file']

                if bin_file.find('zephyr') != -1:
                    dest_file = os.path.join(top_download_dir, os.path.basename(bin_file.replace('zephyr', domain['name'])))
                else:
                    dest_file = os.path.join(top_download_dir, os.path.basename(bin_file))

                if bin_file.find(os.sep) == -1:
                    src_file = os.path.join(build_dir, 'zephyr', bin_file)
                else:
                    src_file = bin_file
                print(f'[Airoha][Collect Firmware] copy firmware file from {src_file} to {dest_file}')
                shutil.copy(src_file, dest_file)

            if name == default_proj:
                default_proj_bin = os.path.basename(dest_file)
                src_dir = build_dir + os.sep + 'download'
                print(f'[Airoha][Collect Firmware] copy all other download binary files from {src_dir} to {top_download_dir}')
                copy_files(src_dir, top_download_dir, ('*'))

                riscv_src_top_dir =  build_dir + os.sep + 'riscv'
                if os.path.exists(riscv_src_top_dir):
                    riscv_out_projs = [d for d in os.listdir(riscv_src_top_dir) if os.path.isdir(os.path.join(riscv_src_top_dir, d))]
                    for proj in riscv_out_projs:
                        riscv_out_proj_dir = riscv_src_top_dir + os.sep + proj
                        riscv_out_features = [d for d in os.listdir(riscv_out_proj_dir) if os.path.isdir(os.path.join(riscv_out_proj_dir, d))]
                        for feature in riscv_out_features:
                            riscv_out_feature_dir = riscv_out_proj_dir + os.sep + feature
                            riscv_dest_dir = top_debug_dir + os.sep + 'riscv' + os.sep + proj + os.sep + feature
                            os.makedirs(riscv_dest_dir, exist_ok=True)
                            riscv_debug_file_ext_tuple = ('.dis', '.bin', '.map', '.elf', '.c', '.ld', '.symbols')
                            copy_files(riscv_out_feature_dir, riscv_dest_dir, riscv_debug_file_ext_tuple)
                            print(f'[Airoha][Collect Firmware] copy debug files which file extension match {riscv_debug_file_ext_tuple} from {riscv_out_feature_dir} to {riscv_dest_dir}')

            if (name != default_proj) and (name.find('boot') != -1):
                bootloader_proj = domain['name']
                bootloader_proj_bin = os.path.basename(dest_file)

        # change firmware naming in flash_download.cfg
        build_dir_tuple = tuple([domain['build_dir'] for domain in domains_yaml_content['domains']])
        print(f'[Airoha][Collect Firmware] build dirs: {build_dir_tuple}')
        print(f'[Airoha][Collect Firmware] default project: {default_proj}')
        print(f'[Airoha][Collect Firmware] firmware of default project: {default_proj_bin}')
        print(f'[Airoha][Collect Firmware] bootloader project: {bootloader_proj}')
        print(f'[Airoha][Collect Firmware] firmware of bootloader project: {bootloader_proj_bin}')

        download_cfg_path = top_download_dir + os.sep + 'flash_download.cfg'
        if os.path.exists(download_cfg_path):
            download_cfg_content = str()
            with open(download_cfg_path, 'r+') as f:
                download_cfg_content = yaml.safe_load(f)
                regions_name = [region for region in download_cfg_content.keys() if region.find('region') != -1]

                firmware_proc_rules = (
                    FirmwareProcRule(
                        origin = 'image-0.bin',
                        new = default_proj_bin,
                    ),
                    FirmwareProcRule(
                        origin = 'bootloader.bin',
                        new = bootloader_proj_bin,
                        optional = True,
                        kconfig = 'SB_CONFIG_BOOTLOADER_MCUBOOT=y'
                    ),
                    FirmwareProcRule(
                        origin = 'storage.bin',
                        optional = True,
                        kconfig = 'CONFIG_GEN_DEFAULT_NVS_BIN=y'
                    ),
                    FirmwareProcRule(
                        origin = 'storage_ota.bin',
                        optional = True,
                        kconfig = 'CONFIG_GEN_DEFAULT_NVS_BIN=y'
                    ),
                    FirmwareProcRule(
                        origin = 'partition_table.bin',
                        optional = True,
                        kconfig = 'CONFIG_AIR_PARTITION_GEN_TABLE_ENABLE=y'
                    ),
                    FirmwareProcRule(
                        origin = 'secure_hdr0.bin',
                        optional = True,
                        kconfig = 'CONFIG_AIR_SECURITY_SECURE_BOOT_ENABLE=y'
                    ),
                    FirmwareProcRule(
                        origin = 'secure_hdr1.bin',
                        optional = True,
                        kconfig = 'CONFIG_AIR_SECURITY_SECURE_BOOT_ENABLE=y'
                    ),
                )

                mark_firmwares = set()
                for rule in firmware_proc_rules:
                    for region in regions_name:
                        region_cfg = download_cfg_content[region]
                        for dl_entry in region_cfg['rom_list']:
                            if (rule.new is not None) and (len(rule.new) != 0) and (dl_entry['rom']['file'] == rule.origin):
                                print(f'[Airoha][Collect Firmware] replace {rule.origin} => {rule.new} in flash_download.cfg')
                                dl_entry['rom']['file'] = rule.new

                        if (rule.optional == True) and (rule.kconfig is not None):
                            match_result = os.popen(
                                f'find {work_dir} -iname ".config" -type f | xargs grep "{rule.kconfig}" | wc -l'
                            ).read().strip()
                            kconfig_match = bool(int(match_result))
                            if kconfig_match == False:
                                print(f'[Airoha][Collect Firmware] remove download entry of {rule.origin} due to {rule.kconfig} not matched')
                                mark_firmwares.add(rule.origin)
                                if rule.new is not None:
                                    mark_firmwares.add(rule.new)

                for region in regions_name:
                    dl_entries = download_cfg_content[region]['rom_list']
                    download_cfg_content[region]['rom_list'] = [x for x in dl_entries if x['rom']['file'] not in mark_firmwares]

            def repr_int2hex(dumper, data):
                return dumper.represent_scalar('tag:yaml.org,2002:int', f'0x{data:0{8}X}')
            print(f'[Airoha][Collect Firmware] represent as hex format')
            result = yaml.add_representer(int, repr_int2hex)

            with open(download_cfg_path, 'w') as f:
                print(f'[Airoha][Collect Firmware] generate {download_cfg_path}')
                yaml.dump(download_cfg_content, f, sort_keys = False, default_flow_style = False)
                print(f'[Airoha][Collect Firmware] generate {download_cfg_path} done!')
        else:
            print(f'[Airoha][Collect Firmware] warning: file {download_cfg_path} is not exist.')