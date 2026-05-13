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
import traceback

from enum import Enum
from collections import namedtuple

class ActionBuildErrorHandle(Enum):
    return_error_code = 1
    exit_error_code = 2

# add . into search path for RDs use ABSOLUTE path of build.py
airoha_build_service = os.path.join(os.path.dirname(__file__))
sys.path.insert(0, os.path.abspath(airoha_build_service))

# add ./airoha/mcu/scripts/build into search path for RDs when they copy build.py to the root of codebase
airoha_build_service = os.path.join(
    os.path.dirname(__file__),
    'airoha',
    'mcu',
    'scripts',
    'build',
)
sys.path.insert(0, os.path.abspath(airoha_build_service))

import airoha_build_service_common

def show_scripts_usage(notice = None):
    '''
    Refer to the man page of the command line to display the help information of the script.
    '''

    if notice:
        print(notice, file = sys.stderr)

    print('NAME\n\tbuild.py - read the configuration files( project_*.yaml ), convert it into a reasonable build command for the Zephyr build system and then call it.')
    print('')
    print('SYNOPSIS')
    print('\tpython3 ./airoha/mcu/scripts/build/build.py <BOARD> <PROJECT> [clean|rebuild]')
    print('\tpython3 ./airoha/mcu/scripts/build/build.py [clean|all|list]')
    print('')
    print('OPTIONS')
    print('\tIf there is only one parameter, the allowed parameters are "clean" and "all".')
    print('\t  clean: delete all project build-related files')
    print('\t  all: delete all project build-related files firstly, and then rebuild all projects listed in project_list*.yaml')
    print('\t  list: list all projects and their parameters')
    print('\t  <BOARD>: which board your would like to choose')
    print('\t  <PROJECT>: which project your would like to choose')
    print('')
    print('\tIf there are two or more parameters, then')
    print('\t  the first parameter is considered the BOARD corresponding to the project to be built')
    print('\t  the second parameter is considered the PROJECT NAME corresponding to the project to be built')
    print('\t  the third parameter can be "clean" or "rebuild". Clean means to delete the project\'s build directory and rebuild means to delete the project\'s build directory and then start a new build.')
    print('')
    print('EXAMPLE')
    print('\tbuild multi_thread project with ab1623m_evk board')
    print('\t  ./build.py ab1623m_evk multi_thread')
    print('')
    print('\tclean out folder of multi_thread project with ab1623m_evk board, and then build multi_thread project with ab1623m_evk board')
    print('\t  ./build.py ab1623m_evk multi_thread rebuild')
    print('')
    print('\tbuild all projects')
    print('\t  ./build.py all')
    print('')
    print('\tlist all projects with board ab1623m_evk')
    print('\t  ./build.py list | grep \'^ab1623m_evk\'')
    print('')
    print('\tbuild all projects with board ab1623m_evk')
    print('\t  ./build.py ab1623m_evk \'.*\' (NOTE: this \' symbol is mandatory)')
    print('')
    print('\tbuild all projects with board ab1623m_evk and project name ends with \'thread\'')
    print('\t  ./build.py ab1623m_evk \'.*thread$\'')
    print('')
    print('\tbuild all projects with board ab1623m_evk and project name contains \'thread\' or contains \'mouse\'')
    print('\t  ./build.py ab1623m_evk \'(.*mouse|.*thread)\'')
    print('')
    print('\tbuild all projects whose board name contains \'ab162\' and project name contains \'thread\' or contains \'mouse\'')
    print('\t  ./build.py \'ab162.*\' \'(.*mouse|.*thread)\'')
    print('')
    print('\tbuild all projects whose board name starts with \'ab162\' and ends with \'evk\' and project name doest not contains \'dvt\', \'hqa\', \'slt\', \'tcm_boot\', \'dbg\', \'demo\', \'debug\', \'heavy\', \'prebuilt\', \'log\', \'basic\', \'test\', and \'performance\'')
    print('\t  ./build.py \'ab162.*evk\' \'(?!.*(?:dvt|hqa|slt|tcm_boot|dbg|demo|debug|heavy|prebuilt|log|basic|test|performance)).*\'')
    print('')
    sys.exit(3)



def action__clean_all():
    print('rm -rf out')
    os.system('rm -rf out')



def action__build(i_board, i_proj_abbr, i_more_param_array = list(), error_action = ActionBuildErrorHandle.exit_error_code):
    projs, dockerq_image = airoha_build_service_common.find_project_list()
    build_template_sh_path = airoha_build_service_common.find_template_build_sh()

    board_name = i_board.replace('/', '_')
    proj_abbr_name = i_proj_abbr.replace('/', '_')

    output_dir = 'out/%s/%s' %(board_name, proj_abbr_name)
    key = '%s__%s'%(board_name, proj_abbr_name)
    if key not in projs.keys():
        print('Error: project %s not found in project list file.' %key, file = sys.stderr)
        print('Notice: use list command to view all supported projects', file = sys.stderr)
        if error_action == ActionBuildErrorHandle.exit_error_code:
            output_log_dir = output_dir + '/log'
            os.makedirs(output_log_dir, exist_ok = True)
            err_log_file = output_log_dir + '/err.log'
            with open(err_log_file, 'w', encoding = 'utf-8') as file:
                file.write('error: project definition is invalid')
            build_status_file = output_log_dir + '/build_status'
            with open(build_status_file, 'w', encoding = 'utf-8') as file:
                file.write('fail')
            try:
                airoha_build_service_common.build_error_analysis(i_proj_abbr, output_log_dir, err_log_file)
            except Exception as e:
                with open(err_log_path, 'a', encoding = 'utf-8') as err_log_file:
                    print('Exception in build_error_analysis:', file = err_log_file)
                    traceback.print_exc(file = err_log_file)
            sys.exit(22) # EINVAL
        else:
            return 22
    else:
        proj_param = projs[key]
        build_log_name = 'build_%s_%s.log'%(board_name, proj_abbr_name)
        proj_build_cmd_template_w_sysbuild = '{DOCKER_CMD} west build -p auto -d {OUTPUT_DIR} -b {BOARD} --sysbuild {PROJ_RELATIVE_PATH} -- {SYS_BUILD_CFG} {PROJS_PARAMETER} 2>&1 | tee {BUILD_LOG}'
        proj_build_cmd_template = '{DOCKER_CMD} west build -p auto -d {OUTPUT_DIR} -b {BOARD} {PROJ_RELATIVE_PATH} {PROJS_PARAMETER} {PREBUILT_TARGET} 2>&1 | tee {BUILD_LOG}'
        if (len(i_more_param_array) == 1):
            if i_more_param_array[0] == 'clean':
                print('rm -rf %s' %(output_dir))
                os.system('rm -rf %s' %(output_dir))
                if error_action == ActionBuildErrorHandle.exit_error_code:
                    sys.exit(0)
                else:
                    return 0
            elif i_more_param_array[0] == 'rebuild':
                print('rm -rf %s' %(output_dir))
                os.system('rm -rf %s' %(output_dir))
                # Recursive call, but can definitely be terminated.
                return action__build(i_board, i_proj_abbr, error_action = error_action)
            else:
                show_scripts_usage('Error: unsupported parameter: %s' %(i_more_param_array[0]))
                if error_action == ActionBuildErrorHandle.exit_error_code:
                    sys.exit(134) # ENOTSUP
                else:
                    return 134
        elif len(i_more_param_array) == 0:
            sysbuild_conf = airoha_build_service_common.extract_sysbuild_conf(proj_param)
            sysbuild_conf_cmd = ('-DSB_CONF_FILE=%s' % sysbuild_conf) if sysbuild_conf is not None else str()
            cfg_sysbuild = True if len(sysbuild_conf_cmd) > 0 else False

            if airoha_build_service_common.allow_dockerq():
                export_dockerq_image_cmd = 'export DOCKERQ_IMAGE=\'%s\'; dockerq' %dockerq_image if dockerq_image is not None else str()
            else:
                export_dockerq_image_cmd = ''

            # generate build.sh from build_template.sh
            if cfg_sysbuild is True:
                build_cmd = proj_build_cmd_template_w_sysbuild.format(
                    DOCKER_CMD = export_dockerq_image_cmd,
                    OUTPUT_DIR = output_dir,
                    BOARD = i_board,
                    PROJ_RELATIVE_PATH = proj_param['proj'],
                    SYS_BUILD_CFG = sysbuild_conf_cmd,
                    PROJS_PARAMETER = airoha_build_service_common.extract_extra_cmake_params(proj_param, True),
                    BUILD_LOG = build_log_name
                )
            else:
                prebuilt_target = airoha_build_service_common.extrace_prebuilt(proj_param)
                prebuilt_target_str = ('-t %s' % prebuilt_target) if prebuilt_target is not None else str()
                build_cmd = proj_build_cmd_template.format(
                    DOCKER_CMD = export_dockerq_image_cmd,
                    OUTPUT_DIR = output_dir,
                    BOARD = i_board,
                    PROJ_RELATIVE_PATH = proj_param['proj'],
                    PROJS_PARAMETER = airoha_build_service_common.extract_extra_cmake_params(proj_param, False),
                    PREBUILT_TARGET = prebuilt_target_str,
                    BUILD_LOG = build_log_name
                )
            print(build_cmd)
            build_script = './build_%s_%s.sh'%(board_name, proj_abbr_name)
            os.system('cp %s %s' %(build_template_sh_path, build_script))
            with open(build_script, 'r+', encoding = 'utf-8') as build_sh:
                build_sh_context = build_sh.read()

                build_sh_context = build_sh_context.replace('__BUILD_COMMAND_PATTERN__', build_cmd, 1)
                build_sh_context = build_sh_context.replace('__OUTPUT_FOLDER_PATTERN__', output_dir, 1)
                build_sh_context = build_sh_context.replace('__BUILD_LOG_PATTERN__', build_log_name, 1)

                build_sh.seek(0)
                build_sh.write(build_sh_context)
            exit_status = os.system('chmod u+x %s && %s'%(build_script, build_script))
            # The build.sh cannot move itself to the specified output directory, so we need to move it manually.
            # In other words, we need to avoid undefined behavior.
            os.system('mv %s %s/build.sh'%(build_script, output_dir))
            log_out_dir = output_dir + os.sep + "log"
            if not os.path.exists(log_out_dir):
                os.makedirs(log_out_dir)
            err_log_path = log_out_dir + os.sep + 'err.log'
            build_status_path = log_out_dir + os.sep + 'build_status'
            build_status = 'FAIL'
            if os.path.exists(build_status_path):
                with open(build_status_path, 'rt') as build_status_file:
                    build_status = build_status_file.read().strip().upper()
            if build_status != 'PASS':
                try:
                    airoha_build_service_common.build_error_analysis(i_proj_abbr, log_out_dir, err_log_path)
                except Exception as e:
                    with open(err_log_path, 'a', encoding = 'utf-8') as err_log_file:
                        print('Exception in build_error_analysis:', file = err_log_file)
                        traceback.print_exc(file = err_log_file)

                if error_action == ActionBuildErrorHandle.exit_error_code:
                    sys.exit(1) # EPERM
                else:
                    return 1
            else:
                if error_action == ActionBuildErrorHandle.exit_error_code:
                    sys.exit(0)
                else:
                    return 0
        else:
            show_scripts_usage('Error: unsupported parameter: %s' %(' '.join(i_more_param_array)))
            if error_action == ActionBuildErrorHandle.exit_error_code:
                sys.exit(134) # ENOTSUP
            else:
                return 134


def action__build_all(projs = None):
    RED='\033[31m'
    GREEN='\033[32m'
    BOLD='\033[1m'
    RESET='\033[0m'

    all_proj = False
    if projs is None:
        action__clean_all()         # clean all here
        projs, _ = airoha_build_service_common.find_project_list()
        all_proj = True

    target_pattern = r"(\w+)__(\w+)"
    collected_build_info = []
    total_proj_num = len(projs.keys())
    pass_proj_count = 0
    for porj_idx, proj_descriptor in enumerate(projs.keys(), start = 1):
        board, proj_abbr = re.findall(target_pattern, proj_descriptor)[0]
        if all_proj:
            result = action__build(board, proj_abbr, error_action = ActionBuildErrorHandle.return_error_code)
        else:
            result = action__build(board, proj_abbr, ('rebuild', ), error_action = ActionBuildErrorHandle.return_error_code)
        BuildInfo = namedtuple('BuildInfo', ['board', 'proj_abbr', 'result'])
        tmp_build_info = BuildInfo(board, proj_abbr, 'PASS' if result == 0 else 'FAIL')

        # keep the list in order to make it easier to compare compilation result
        collected_build_info.append(tmp_build_info)
        collected_build_info.sort(key = (lambda info: (info.result, info.board, info.proj_abbr)))
        pass_proj_count = pass_proj_count + (1 if result == 0 else 0)

        print(BOLD + 'Build Result List(Progress: %.2f%%( %d/%d ), PASS Rate: %.2f%%):' \
            %(porj_idx*100/total_proj_num,\
              porj_idx,\
              total_proj_num,\
              pass_proj_count*100/porj_idx)\
            + RESET)

        max_board_length = max([len(board) for board, _, _ in collected_build_info])
        for i_board, i_proj_abbr, build_result in collected_build_info:
            text = '\t%s <=> "%s"%s "%s"' %(build_result, i_board, ' '*(max_board_length - len(i_board)), i_proj_abbr)
            color = RED if build_result != 'PASS' else GREEN
            print(color + text + RESET)


def action__list_build_result():
    RED='\033[31m'
    GREEN='\033[32m'
    BOLD='\033[1m'
    RESET='\033[0m'

    def find_build_result(target_dir = 'out'):
        for board in os.listdir(target_dir):
            board_path = os.path.join(target_dir, board)
            if not os.path.isdir(board_path):
                continue
            for proj in os.listdir(board_path):
                project_path = os.path.join(board_path, proj)
                if not os.path.isdir(project_path):
                    continue
                build_status_path = os.path.join(project_path, 'log', 'build_status')
                if os.path.exists(build_status_path) and os.path.isfile(build_status_path):
                    yield (board, proj, build_status_path)

    proj_idx = 0
    for board, proj, file_path in find_build_result():
        # board = board.strip()
        # proj = proj.strip()
        if proj_idx == 0:
            print(BOLD + 'Build Result List:' + RESET)
        build_result = 'FAIL'
        with open(file_path, "r") as build_result_file:
            build_result = build_result_file.readlines()[0].upper().strip()
        text = '\t%s <=> "%s" "%s"' %(build_result, board, proj)
        color = RED if build_result != 'PASS' else GREEN
        print(color + text + RESET)
        proj_idx += 1








if __name__ == '__main__':
    #link env toolchain for airoha internal codebase
    link_env_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), 
                           "airoha", "mcu", "scripts", "build")
    sys.path.append(link_env_dir)

    # Now you can import link_env
    try:
        import link_env
    
        
        # ... existing main function code ...
        
        # Call the main function from link_env
        link_env.link_env_toolchain()
        
        # ... continue with the rest of the build process ...
    except ImportError:
        print("Warning: Could not import link_env module. Environment setup will be skipped.")
#link env toolchain for airoha internal codebase

    # The first parameter is the name of the script, which needs to be filtered out.
    if len(sys.argv) == 2:
        if sys.argv[1] == 'clean':
            action__clean_all()
        elif sys.argv[1] == 'list':
            projs, _ = airoha_build_service_common.find_project_list()
            airoha_build_service_common.print_dict_recursive(projs)
        elif sys.argv[1] == 'all':
            action__build_all()
        elif sys.argv[1] == 'result':
            action__list_build_result()
        else:
            print(sys.argv[1:])
            show_scripts_usage('Error: unsupported parameter: %s' %(sys.argv[1]))
            sys.exit(134) # ENOTSUP
    else:
        if (len(sys.argv) >= 3):
            i_board, i_proj_abbr, *args = sys.argv[1:]
            if (i_board.find('*') != -1) or (i_proj_abbr.find('*') != -1):
                # print(i_board, i_proj_abbr)
                assert(len(sys.argv) == 3)
                projs, _ = airoha_build_service_common.find_project_list()
                input_pattern = '__'.join(sys.argv[1:])
                print('input pattern: %s' %(input_pattern))
                re_pattern =  re.compile(input_pattern)
                matched_projs = { key:'' for key, value in projs.items() if re_pattern.match(key) }
                if len(matched_projs):
                    print('all matched %d projects are as follows:' %(len(matched_projs)))
                    for key in matched_projs.keys():
                        print('  %s' %(key))
                    time.sleep(3)
                    action__build_all(matched_projs)
                else:
                    print('Warning: there is no matched projects to be build')
                    sys.exit(0)
            else:
                action__build(i_board, i_proj_abbr, args)
        else:
            print(sys.argv[1:])
            show_scripts_usage('Error: need more parameter')
            sys.exit(22) # EINVAL
