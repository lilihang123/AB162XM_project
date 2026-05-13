#!/bin/bash
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

# When execution result of any statement is not true, exit the script immediately to
# prevent the script from continuing to execute subsequent commands that may depend on
# the successful execution of the previous command after an error occures.
set -e
# set -o pipefail



CURR_DIR=$(pwd)
AIROHA_ZEPHYR_MODULE=${CURR_DIR}/airoha/mcu
AIROHA_MCUBOOT_MODULE=${CURR_DIR}/airoha/mcu/applications/mcuboot
export ZEPHYR_EXTRA_MODULES="${AIROHA_ZEPHYR_MODULE};${AIROHA_MCUBOOT_MODULE}"

# Reset
COLOR_OFF='\033[0m'       # Text Reset
# Regular Colors
BLACK='\033[0;30m'        # Black
RED='\033[0;31m'          # Red
GREEN='\033[0;32m'        # Green
YELLOW='\033[0;33m'       # Yellow
BLUE='\033[0;34m'         # Blue
PURPLE='\033[0;35m'       # Purple
CYAN='\033[0;36m'         # Cyan
WHITE='\033[0;37m'        # White

show_available_proj () {
    echo "==============================================================="
    echo "Available Build Projects:"
    echo "==============================================================="
    for var in ${!map_@}
    do
        board=$(echo ${var} | sed 's/__/:/g' | cut -d':' -f2)
        project=$(echo ${var} | sed 's/__/:/g' | cut -d':' -f3)
        echo "${board}"
        echo "  ${project}"
        eval proj_map_key=( \${!$var[@]} )
        eval proj_map_value=( \${$var[@]} )
        for key in ${proj_map_key[@]}
        do
            displayName=""
            case ${key} in
                0)
                 displayName="project path"
                    ;;
                1)
                 displayName="sysbuild_conf"
                    ;;
                2)
                 displayName="mcuboot__DTC_OVERLAY_FILE"
                    ;;
                3)
                 displayName="mcuboot__CONF_FILE"
                    ;;
                4)
                 displayName="${project}__DTC_OVERLAY_FILE"
                    ;;
                5)
                 displayName="${project}__CONF_FILE"
                    ;;
            esac
            eval echo \"\ \ \ \ \ \ ${displayName}: \${${var}[\"${key}\"]}\"
        done
    done
}

#source mapping_proj.cfg
for d in $(cd airoha/mcu/tools/mapping_proj/; find . -name mapping_proj.cfg);
do
    echo "d : ${d:2}"
    if [ -f airoha/mcu/tools/mapping_proj/${d:2} ]; then
        source airoha/mcu/tools/mapping_proj/${d:2}
    fi
done

declare -a argv=($0)
for i in $@
do
    case ${i} in
        list)
            if [ "${#argv[@]}" == "1" ]; then
                show_available_proj
                exit 0
            else
                #echo "args : ${#argv[@]}"
                echo "Error: wrong usage!!"
                exit 1
            fi
            ;;
        *)
            argv+=($i)
            ;;
    esac
done

board=${argv[1]}
project=${argv[2]}
mapping_var="map__${board}__${project}"
eval proj_path=\${$mapping_var[0]}
eval sysbuild_conf=\${$mapping_var[1]}
eval mcuboot_DTC_OVERLAY_FILE=\${$mapping_var[2]}
eval mcuboot_CONF_FILE=\${$mapping_var[3]}
eval project_DTC_OVERLAY_FILE=\${$mapping_var[4]}
eval project_CONF_FILE=\${$mapping_var[5]}

OUTPUT_FOLDER=out/${board}/${project}
BUILD_LOG=build_${board}_${project}.log
OUTPUT_LOG_FOLDER=${OUTPUT_FOLDER}/log

user=$(whoami)
if [[ "${user}" =~ "ar700" ]]; then
    dockerq="export DOCKERQ_IMAGE='mtkdocker01:5000/srv_airoha/ubuntu.22.04:latest' ; dockerq"
else
    dockerq=""
fi

DSB_CONFIG_FILE=""
project_DTC_OVERLAY_FILE_OPTION=""
project_CONF_FILE_OPTION=""
mcuboot_CONF_FILE_OPTION=""
mcuboot_DTC_OVERLAY_FILE_OPTION=""

if [ ! -z "${sysbuild_conf}" ]; then
    DSB_CONFIG_FILE="-DSB_CONF_FILE=${sysbuild_conf}"
fi

if [ ! -z "${project_DTC_OVERLAY_FILE}" ]; then
    prefix_DTC_OVERLAY_FILE=$(basename ${proj_path})
    project_DTC_OVERLAY_FILE_OPTION="-D${prefix_DTC_OVERLAY_FILE}_DTC_OVERLAY_FILE=${project_DTC_OVERLAY_FILE}"
fi

if [ ! -z "${project_CONF_FILE}" ]; then
    prefix_CONF_FILE=$(basename ${proj_path})
    #echo "\${prefix_CONF_FILE} : ${prefix_CONF_FILE}"
    project_CONF_FILE_OPTION="-D${prefix_CONF_FILE}_CONF_FILE=${project_CONF_FILE}"
fi

if [ ! -z "${mcuboot_CONF_FILE}" ]; then
    mcuboot_CONF_FILE_OPTION="-Dmcuboot_CONF_FILE=${mcuboot_CONF_FILE}"
fi

if [ ! -z "${mcuboot_DTC_OVERLAY_FILE}" ]; then
    mcuboot_DTC_OVERLAY_FILE_OPTION="-Dmcuboot_DTC_OVERLAY_FILE=${mcuboot_DTC_OVERLAY_FILE}"
fi

build_command="${dockerq} west -v build -p auto -d ${OUTPUT_FOLDER} -b ${board} --sysbuild ${proj_path} -- ${DSB_CONF_FILE} ${project_DTC_OVERLAY_FILE_OPTION} ${project_CONF_FILE_OPTION} ${mcuboot_CONF_FILE_OPTION} ${mcuboot_DTC_OVERLAY_FILE_OPTION} 2>&1 | tee ${BUILD_LOG}"
echo "${build_command}"
if [ ! -d "${OUTPUT_LOG_FOLDER}" ]; then
    mkdir -p "${OUTPUT_LOG_FOLDER}"
fi

eval ${build_command}
BUILD_RET=$?

if [ -f "${BUILD_LOG}" ]; then
    echo 'PIPESTATUS:' ${PIPESTATUS[0]}
    echo 'Error number:' $(grep -i "error:" "${BUILD_LOG}" | wc -l)
    echo 'Build return:' ${BUILD_RET}

    if [ ${PIPESTATUS[0]} -eq 0 ] && [ $? -eq 0 ] && [ $(grep -i "error:" "${BUILD_LOG}" | wc -l) -eq 0 ]; then
        echo -e "Build Result: ${GREEN}PASS${COLOR_OFF}"
        echo 'pass' > "${OUTPUT_LOG_FOLDER}"/build_status
    else
        echo -e "Build Result: ${RED}FAIL${COLOR_OFF}"
        echo 'fail' > "${OUTPUT_LOG_FOLDER}"/build_status
    fi

    if [ ! -d "${OUTPUT_FOLDER}" ]; then
        mkdir -p "${OUTPUT_FOLDER}"
        # In some cases, build directory has not yet been create because of project build failed.
        sleep 1
    fi
    mv ${BUILD_LOG} "${OUTPUT_FOLDER}"/build.log
    cp "${OUTPUT_FOLDER}"/build.log "${OUTPUT_LOG_FOLDER}"/err.log
fi
