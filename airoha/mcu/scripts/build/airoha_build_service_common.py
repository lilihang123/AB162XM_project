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
import re
import sys
import json
import socket
import subprocess

from enum import Enum
from yaml import safe_load
from collections import OrderedDict

from csv import reader as csv_reader

class BuildErrorType(Enum):
    ERR_SOURCE_FILE = "Source File Error"
    ERR_KCONFIG = "Kconfig Error"
    ERR_DEVICE_TREE = "Device Tree Error"
    ERR_PYTHON = "Python Error"
    ERR_CMAKE = "CMake Error"
    ERR_MAKEFILE = "Makefile Error"
    ERR_BT_SRAM_OVERSIZE = "BT RAM Oversize Error"
    ERR_LINK = "Link Error"
    ERR_PROJ_DEFINE = "Project Define Error"
    ERR_FLASH_PARTITION_NOT_MATCH = "Flash Partition Not Match Error"
    ERR_RAM_USAGE_OVERSIZE = "RAM Usage Oversize Error"
    ERR_ROM_USAGE_OVERSIZE = "ROM Usage Oversize Error"
    ERR_UNKNOWN_TARGET = "Unknown Target"
    ERR_UNKNOWN = "Unknown Error"


def find_project_list():
    _proj_cfg_dict = dict()
    target_folder = 'airoha/mcu/tools/mapping_proj'
    target_file = 'project_list*.yaml'
    dockerq_image = None

    def find_project_list_file_path():
        cmd = 'find %s -name %s -type f'%(target_folder, target_file)
        if not os.path.exists(target_folder):
            print('Error: directory %s not exist.' %(target_folder), file = sys.stderr)
            exit(1)
        return subprocess.check_output(cmd, shell = True).decode().splitlines()
    projs_yaml = find_project_list_file_path()
    error = True
    for item in projs_yaml:
        yaml_content = dict()
        with open(item, encoding = 'utf-8') as f:
            yaml_content = safe_load(f)
        for key, value in yaml_content.items():
            if key in _proj_cfg_dict.keys():
                raise ValueError("project %s is already duplicated" %(key))
            if (key.find('__') != -1) and \
               ('proj' in value.keys()):
                # need to check more
                # 1. project path is not exist
                # 2. project name and sub project don't match
                # for example:
                #     ab1620_fpga__test:
                #     proj: airoha/mcu/samples/templates/multi_thread
                #     xxxx(!!!ERROR HERE!!!):
                #         DTC_OVERLAY_FILE: config/ab1620_fpga/app.overlay
                #         CONF_FILE: config/ab1620_fpga/multi_thread.conf
                # ...
                if not os.path.exists(value['proj']):
                    # print('Error: project path %s is invalid.' %(value['proj']), file = sys.stderr)
                    continue

                proj_path = value['proj']
                proj_abbr = proj_path.split(os.sep)[-1]
                if proj_abbr not in value.keys():
                    print('Error: project name( %s ) and sub project name description do not match.' %(proj_abbr), file = sys.stderr)
                    if 1 >= len(value.keys()):
                        print('Error: no available sub project description.', file = sys.stderr)
                    else:
                        print('Error: available sub project name are:', file = sys.stderr)
                        for sub_proj in value.keys():
                            if sub_proj != 'proj':
                                print('\t%s' %(sub_proj), file = sys.stderr)
                    continue

                _proj_cfg_dict[key] = yaml_content[key]
                error = False
            _tmp_docker_image = str(yaml_content['dockerq_image']) if 'dockerq_image' in yaml_content.keys() else None
            if dockerq_image is None:
                dockerq_image = _tmp_docker_image
            else:
                # Check if the dockerq_image is consistent across all project configuration files
                assert _tmp_docker_image == dockerq_image
    if error:
        print('Warning: project configuration files: ', end = '', file = sys.stderr)
        print(projs_yaml, file = sys.stderr)
        print('Error: no projects were found in any %s files in the %s' %(target_file, target_folder), file = sys.stderr)
        exit(3)

    return _proj_cfg_dict, dockerq_image


def find_template_build_sh():
    target_folder = 'airoha/mcu/tools/mapping_proj'
    target_file = 'build_template.sh'

    cmd = 'find %s -name %s -type f'%(target_folder, target_file)
    if not os.path.exists(target_folder):
        print('Error: directory %s not exist.' %(target_folder), file = sys.stderr)
        exit(1)
    template_path_list = subprocess.check_output(cmd, shell = True).decode().splitlines()
    if len(template_path_list) != 1:
        print('Error: find %d template build script.' %(len(template_path_list)), file = sys.stderr)
        exit(1)
    return template_path_list[0]


def validity_board_project(board, project, sub_project = None):
    projs, _ = find_project_list()
    key = '%s__%s'%(board, project)
    if key not in projs.keys():
        return False
    if (sub_project is not None) and (sub_project not in projs[key].keys()):
        return False
    return True


def extract_extra_cmake_params(proj_param, cfg_sysbuild = True):
    extra_cmake_params = list()
    # namespace + variable name + variable value
    cmake_param_fmt_sysbuild = '-D%s_%s=%s'
    cmake_param_fmt = '-D%s=%s'
    for key, value in proj_param.items():
        if isinstance(value, dict):
            # sub project can specified parameters in the target_key_set
            target_key_set = {'DTC_OVERLAY_FILE', 'CONF_FILE', 'BOARD'}
            for sub_key, sub_value in value.items():
                if (sub_key in target_key_set) and (sub_value is not None):
                    if cfg_sysbuild:
                        extra_cmake_params.append(cmake_param_fmt_sysbuild%(key, sub_key, sub_value))
                    else:
                        extra_cmake_params.append(cmake_param_fmt%(sub_key, sub_value))
    return ' '.join(extra_cmake_params)


def print_dict_recursive(d, indent = 0):
    for key, value in d.items():
        print(' '*indent + str(key), end = ': ')
        if isinstance(value, dict):
            print()
            print_dict_recursive(value, indent + 4)
        else:
            print(value)
        if indent == 0:
            print()



def extract_sysbuild_conf(proj_param: dict):
    if ('sysbuild_conf' in proj_param.keys()) and (proj_param['sysbuild_conf'] is not None):
        return proj_param['sysbuild_conf']
    else:
        return None


def extrace_prebuilt(proj_param: dict):
    if ('target' in proj_param.keys()) and (proj_param['target'] is not None):
        assert 'library' in proj_param.keys() and (proj_param['library'] is not None)
        assert 'compatible' in proj_param.keys() and (proj_param['compatible'] is not None)
        assert 'repo_path' in proj_param.keys() and (proj_param['repo_path'] is not None)
        if isinstance(proj_param['repo_path'], str):
            assert os.path.exists(proj_param['repo_path'])
        elif isinstance(proj_param['repo_path'], list):
            for temp_path in proj_param['repo_path']:
                assert os.path.exists(temp_path), "%s not exist, please check configuration" %(temp_path)
        else:
            assert False, "unsupported data type(%s) for repo_path" %(type(proj_param['repo_path']))
        compatible_attr_allow_set = {'bt_data', 'smart_home', 'esl'}
        assert all(item in compatible_attr_allow_set for item in proj_param['compatible'])
        return proj_param['target']
    else:
        return None


def allow_dockerq():
    host_name = socket.gethostname()
    who_am_i = os.popen('whoami').read().strip()

    air_staff_ids = ('ar7', 'vd0')
    air_staff = any(item in who_am_i for item in air_staff_ids)
    print('whoami: %s' %(who_am_i))
    if (not air_staff) or (host_name.startswith('mcdalx')) or (host_name.startswith('arhtscf')):
        return False
    else:
        return True


def build_error_analysis(i_proj_abbr, out_dir, err_log_path):
    build_context = []
    with open(err_log_path, 'r', encoding = 'utf-8') as err_log:
        build_context = err_log.readlines()

    proj_start_build_pattern = r"Performing build step for '(.*)'"
    proj_finish_build_pattern = r"Completed '(.*)'"

    source_file_err_pattern = r"(.*): (error|fatal error): (.*?)"
    source_file_err_detail_pattern = r"(.*): (error|fatal error): (.*?): (.*)"

    kconfig_err_pattern = r"error: Aborting due to Kconfig warnings"
    kconfig_file_pattern = r"(.*): warning:"

    devicetree_err_pattern = r"devicetree error: (.*?) "
    application_pattern = r"-- Application: (.*)"

    cmake_err_pattern = r"CMake Error at (.*?):"
    make_err_pattern = r"^make:"

    python_err_pattern = r" File \"(.*)\", line ([0-9]*)"

    link_oversize_pattern = r"region `(.*)\' overflowed by"
    undefined_ref_err_pattern = r"(.*): undefined reference to "
    multiple_definition_err_pattern = r"(.*): multiple definition of "

    project_define_err_pattern = r"project definition is invalid"

    flash_partition_not_match_err_pattern = r"Flash Partitions Not Match"

    ram_usage_oversize_err_pattern = r"RAM usage oversize"
    rom_usage_oversize_err_pattern = r"flash memory usage oversize"

    unknown_target_err_pattern = r"ninja: error: unknown target"

    projects = []
    error_files = []
    error_types = []
    error_owners = []
    for ctx_idx, line in enumerate(build_context):
        matched = re.search(unknown_target_err_pattern, line)
        if matched:
            error_types.append(BuildErrorType.ERR_UNKNOWN_TARGET)

        matched = re.search(ram_usage_oversize_err_pattern, line)
        if matched:
            error_types.append(BuildErrorType.ERR_RAM_USAGE_OVERSIZE)

        matched = re.search(rom_usage_oversize_err_pattern, line)
        if matched:
            error_types.append(BuildErrorType.ERR_ROM_USAGE_OVERSIZE)

        matched = re.search(flash_partition_not_match_err_pattern, line)
        if matched:
            error_types.append(BuildErrorType.ERR_FLASH_PARTITION_NOT_MATCH)

        matched = re.search(project_define_err_pattern, line)
        if matched:
            error_types.append(BuildErrorType.ERR_PROJ_DEFINE)

        matched = re.search(proj_start_build_pattern, line)
        if matched:
            projects.append(matched.group(1))
        matched = re.search(proj_finish_build_pattern, line)
        if matched:
            projects.remove(matched.group(1))

        matched = re.search(source_file_err_pattern, line)
        if matched:
            context = matched.group(1)
            c_cpp_files_suffix = ('.c', '.cpp', '.cc', '.cxx', '.c++', '.h', '.hpp')
            if any(context.find(suffix) != -1 for suffix in c_cpp_files_suffix): #context.find('.c') != -1 or context.find('.cpp') != -1:
                error_files.append(matched.group(1))
                error_types.append(BuildErrorType.ERR_SOURCE_FILE)
            if context.find('.ld') != -1 or context.find('.cmd') != -1:
                error_files.append(matched.group(1))
                error_types.append(BuildErrorType.ERR_LINK)
            if context.find('collect') != -1:
                region_matched = re.search(link_oversize_pattern, build_context[ctx_idx - 1])
                if region_matched:
                    region = region_matched.group(1)
                    if region.find('BT') != -1:
                        error_types.append(BuildErrorType.ERR_BT_SRAM_OVERSIZE)

                for rev_idx, line_context in enumerate(build_context[ctx_idx - 1: 0: -1]):
                    file_matched = re.search(undefined_ref_err_pattern, line_context)
                    # print(rev_idx, line_context)
                    if file_matched:
                        error_file = file_matched.group(1)
                        if error_file.count(':') >= 2:
                            print(error_file.split(':'))
                            error_file = ':'.join(error_file.split(':')[1:]).strip()
                        error_files.append(error_file)
                        error_types.append(BuildErrorType.ERR_LINK)
                        break

                    file_matched = re.search(multiple_definition_err_pattern, line_context)
                    if file_matched:
                        error_file = file_matched.group(1)
                        if error_file.count(':') >= 2:
                            print(error_file.split(':'))
                            error_file = ':'.join(error_file.split(':')[1:]).strip()
                        error_files.append(error_file)
                        error_types.append(BuildErrorType.ERR_LINK)
                        break

            if matched.group(1).find('command-line') != -1:
                matched = re.search(source_file_err_detail_pattern, line)
                err_file = matched.group(3)
                err_info = matched.group(4)

                name, extension = os.path.splitext(err_file)
                if extension.find('.overlay') != -1:
                    error_types.append(BuildErrorType.ERR_DEVICE_TREE)

                # print(err_file)
                # print(err_info)
                if err_info.find('No such file') != -1:
                    error_files.append(err_file)
                else:
                    if os.path.exists(err_file):
                        error_files.append(err_file)
                    else:
                        for rev_idx, line_context in enumerate(build_context[ctx_idx - 1: 0: -1]):
                            app_matched = re.search(application_pattern, line_context)
                            if app_matched:
                                app = app_matched.group(1)
                                app_sth = app + os.sep + err_file
                                if os.path.exists(app_sth):
                                    error_files.append(app + os.sep + sth)
                                break

        matched = re.search(kconfig_err_pattern, line)
        if matched:
            for rev_idx, line_context in enumerate(build_context[ctx_idx - 1: 0: -1]):
                file_matched = re.search(kconfig_file_pattern, line_context)
                if file_matched:
                    error_files.append(file_matched.group(1))
                    error_types.append(BuildErrorType.ERR_KCONFIG)

        matched = re.search(devicetree_err_pattern, line)
        if matched:
            error_types.append(BuildErrorType.ERR_DEVICE_TREE)

            sth = matched.group(1)
            if sth.startswith('./'):
                sth = sth[2:]
            sth_wo_line = sth
            last_colon_idx = sth.rfind(':')
            if last_colon_idx != -1:
                sth_wo_line = sth[:last_colon_idx]
            # print(sth_wo_line)
            if os.path.exists(sth_wo_line):
                error_files.append(sth)
            else:
                for rev_idx, line_context in enumerate(build_context[ctx_idx - 1: 0: -1]):
                    app_matched = re.search(application_pattern, line_context)
                    if app_matched:
                        app = app_matched.group(1)
                        app_sth = app + os.sep + sth_wo_line
                        # print(app_sth)
                        if os.path.exists(app_sth):
                            error_files.append(app + os.sep + sth)
                        break


        matched = re.search(cmake_err_pattern, line)
        if matched:
            cmake_err_file = matched.group(1)
            if (len(build_context) > ctx_idx + 2) and \
               (cmake_err_file.find('kconfig.cmake') != -1) and \
               (build_context[ctx_idx + 1].find('File not found') != -1):
               error_files.append(build_context[ctx_idx + 2].strip())
               error_types.append(BuildErrorType.ERR_KCONFIG)
            error_files.append(cmake_err_file)
            error_types.append(BuildErrorType.ERR_CMAKE)

        matched = re.search(make_err_pattern, line)
        if matched:
            make_file_pattern = r"^(.*?): "
            error_files.append(re.search(make_file_pattern, build_context[ctx_idx-1]).group(1))
            error_types.append(BuildErrorType.ERR_MAKEFILE)

        matched = re.search(python_err_pattern, line)
        if matched:
            error_types.append(BuildErrorType.ERR_PYTHON)
            error_files.append('%s:%s' %(matched.group(1), matched.group(2)))

    if len(error_types) == 0:
        error_types.append(BuildErrorType.ERR_UNKNOWN)

    curr_script_path = os.path.join(os.path.dirname(__file__))
    if len(error_files) == 0:
        # Read the CSV file to get the owner of different @BuildErrorType
        err_type_window_file = curr_script_path + os.sep + 'err_type_window.csv'
        assert os.path.exists(err_type_window_file)
        with open(err_type_window_file, 'r', encoding = 'utf-8') as csv_file:
            reader = csv_reader(csv_file)
            next(reader)
            for err_type, err_window in reader:
                if (err_type in [item.name for item in error_types]) and (len(err_window) != 0):
                    error_owners.append(err_window)

    else:
        if any(os.path.exists(build_error_file.split(':')[0]) for build_error_file in error_files) and \
            any(build_error_file.split(':')[0].find('/airoha/') != -1 for build_error_file in error_files):
                # based on the information in BUILD_ERROR_FILES,
                # as well as the information of result of git blame and git show,
                # we can get the owner of the error
                for build_error_file in error_files:
                    info_list = build_error_file.split(':')
                    error_file = info_list[0]
                    error_file_dir = os.path.dirname(error_file)
                    error_file_name = os.path.basename(error_file)
                    error_line = 0xDEADBEEF
                    if len(info_list) >= 2:
                        error_line = info_list[1]
                    if os.path.exists(error_file) and error_file.find('/airoha/') != -1:
                        # get the owner of the file
                        if error_line != 0xDEADBEEF:
                            git_blame_cmd = 'cd %s && git blame -L %s,%s %s && cd -' %(error_file_dir, error_line, error_line, error_file_name)
                            git_blame_result = subprocess.check_output(git_blame_cmd, shell = True).decode().splitlines()
                            assert len(git_blame_result) >= 1, 'Failed to get git blame result'
                            commit_hash = git_blame_result[0].split(' ')[0]

                            git_show_cmd = 'cd %s && git show --no-patch %s && cd -' % (error_file_dir, commit_hash)
                            try:
                                git_show_result = subprocess.check_output(git_show_cmd, shell = True).decode().splitlines()
                                for result_idx, result_line in enumerate(git_show_result):
                                    if result_line.find('Author') != -1:
                                        git_owner_info_patter = r'Author: (.*) <(.*)>'
                                        git_owner_info_matched = re.search(git_owner_info_patter, result_line)
                                        assert git_owner_info_matched is not None, 'Failed to parse git owner info'
                                        assert len(git_owner_info_matched.groups()) >= 2, 'Failed to parse git owner info'
                                        file_owner = git_owner_info_matched.group(2)
                                        error_owners.append(file_owner)
                            except:
                                print("find build error fail, assign to project owner")

    if len(error_owners) == 0:
        # need to assign build error issue by checking project owner
        # Read the CSV file to get the owner of the project
        proj_owner_file = curr_script_path + os.sep + 'proj_owner.csv'
        assert os.path.exists(proj_owner_file)
        with open(proj_owner_file, 'r', encoding = 'utf-8') as csv_file:
            reader = csv_reader(csv_file)
            next(reader)
            for proj_re_expr, proj_owner in reader:
                matched = re.search(proj_re_expr, i_proj_abbr)
                if matched:
                    error_owners.append(proj_owner)
                    break

    for idx, error_file in enumerate(error_files):
        if error_file.count(':') == 2:
            last_colon_idx = error_file.rfind(':')
            error_files[idx] = error_file[:last_colon_idx]

    report_path = out_dir + os.sep + 'build_error_analysis_report'
    with open(report_path, 'w', encoding = 'utf-8') as report:
        def write_error_info(title, value):
            if len(value) > 1:
                report.write('%s=(\n' %(title))
                for var in value:
                    report.write('    "%s"\n' %(var))
                report.write(')\n')
            else:
                if len(value):
                    report.write('%s="%s"\n' %(title, value[0]))
        write_error_info('BUILD_ERROR_TYPE', list(OrderedDict.fromkeys([item.value for item in error_types])))
        write_error_info('BUILD_ERROR_PROJECT', projects)
        write_error_info('BUILD_ERROR_FILES', error_files)
        write_error_info('BUILD_ERROR_OWNER', list(OrderedDict.fromkeys([item for item in error_owners])))


    # Store the analysis report using the JSON standard file format.
    report_path = out_dir + os.sep + 'build_error_analysis_report.json'
    with open(report_path, 'w', encoding = 'utf-8') as report:
        report_data = {
            'BUILD_ERROR_TYPE': list(OrderedDict.fromkeys([item.value for item in error_types])),
            'BUILD_ERROR_PROJECT': projects,
            'BUILD_ERROR_FILES': error_files,
            'BUILD_ERROR_OWNER': list(OrderedDict.fromkeys([item for item in error_owners]))
        }
        json.dump(report_data, report, indent = 4, ensure_ascii = False)