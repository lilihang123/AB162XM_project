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
import socket

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

def show_scripts_usage():
    '''
    Refer to the man page of the command line to display the help information of the script.
    '''

    print('Name\n\tconfig - read the configuration file, convert it into a reasonable menuconfig command for the Zephyr airoha_build_service_common system and then call it.\n')
    print('SYNOPSIS\n\tpython3 config.py <board> <project> [sub_project]\n')
    print('DESCRIPTION')
    print('OPTIONS')
    print('NOTE')
    print('EXAMPLE')


if __name__ == '__main__':
    # The first parameter is the name of the script, which needs to be filtered out.
    argv_number = len(sys.argv)
    if (argv_number < 3) or (argv_number > 4):
        show_scripts_usage()
        exit(1)

    board, project, sub_project = None, None, None
    if argv_number == 3:
        board, project, = sys.argv[1:3]
    else:
        board, project, sub_project = sys.argv[1:4]
        if project == sub_project:
            sub_project = None

    if airoha_build_service_common.validity_board_project(board, project, sub_project):
        projs, dockerq_image = airoha_build_service_common.find_project_list()
        proj_cfg_cmd_template = '\
%s west -v build -p auto -d %s \
-b %s --sysbuild %s -t %s \
-- \
%s %s'
        key = '%s__%s'%(board, project)
        proj_param = projs[key]
        output_dir = 'out/%s/%s' %(board, project)
        cfg_target = sub_project+'_menuconfig' if sub_project is not None else 'menuconfig'
        sysbuild_conf = airoha_build_service_common.extract_sysbuild_conf(proj_param)
        sysbuild_conf_cmd = ('-DSB_CONF_FILE=%s' % sysbuild_conf) if sysbuild_conf is not None else str()

        if airoha_build_service_common.allow_dockerq():
            export_dockerq_image_cmd = 'export DOCKERQ_IMAGE=\'%s\'; dockerq' %dockerq_image if dockerq_image is not None else str()
        else:
            export_dockerq_image_cmd = ''

        config_cmd = proj_cfg_cmd_template %(
            export_dockerq_image_cmd,
            output_dir,
            board,
            proj_param['proj'],
            cfg_target,
            sysbuild_conf_cmd,
            airoha_build_service_common.extract_extra_cmake_params(proj_param)
        )
        print(config_cmd)

        build_template_sh_path = airoha_build_service_common.find_template_build_sh()
        config_script = './menuconfig_%s_%s.sh'%(board, project)
        os.system('cp %s %s && chmod u+x %s' %(build_template_sh_path, config_script, config_script))
        with open(config_script, 'r+', encoding = 'utf-8') as config_sh:
            config_sh_context = config_sh.read()

            config_sh_context = config_sh_context.replace('__BUILD_COMMAND_PATTERN__', config_cmd, 1)
            config_sh_context = config_sh_context.replace('__OUTPUT_FOLDER_PATTERN__', output_dir, 1)

            config_sh.seek(0)
            config_sh.write(config_sh_context)
        os.system('%s'%(config_script))
        os.system('mv %s %s/config.sh'%(config_script, output_dir))
    else:
        print('Error: invalid parameter.', file = sys.stderr)
        exit(2)