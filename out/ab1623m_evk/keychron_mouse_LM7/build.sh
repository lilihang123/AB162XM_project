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
# set -e

# With this prompt, the exit status of the pipeline will be the exit status of
# the first command that fails (if any).
set -o pipefail

CURR_DIR=$(pwd)

# zephyr mirror mechanism which allows airoha to optimize code
# but not contribute to the open source community.
# Note: For incremental build requirements, we need to update files
# when the target file does not exist or the source file was modified more recently.
# cp -ru ${CURR_DIR}/airoha/zephyr_mirror/* ${CURR_DIR}
AIROHA_MIRROR_SRC_DIR="${CURR_DIR}/airoha/zephyr_mirror"
AIROHA_MIRROR_DEST_DIR="${CURR_DIR}"
find "${AIROHA_MIRROR_SRC_DIR}" -type f ! -path '*/.*/*' | while IFS= read -r SRC_FILE; do
    RELATIVE_PATH="${SRC_FILE#${AIROHA_MIRROR_SRC_DIR}/}"
    DEST_FILE="${AIROHA_MIRROR_DEST_DIR}/${RELATIVE_PATH}"
    mkdir -p "$(dirname "${DEST_FILE}")"
    if [ ! -f "${DEST_FILE}" ] || ! cmp -s "${SRC_FILE}" "${DEST_FILE}"; then
        cp "${SRC_FILE}" "${DEST_FILE}"
        echo "copy ${SRC_FILE} to ${DEST_FILE}"
    fi
done

# cp Airoha mbedtls folder content to modules/crypto/mbedtls
AIROHA_MBEDTLS_SRC_DIR="${CURR_DIR}/airoha/mcu/subsys/airoha/mbedtls"
AIROHA_MBEDTLS_DEST_DIR="${CURR_DIR}/modules/crypto/mbedtls"
find "${AIROHA_MBEDTLS_SRC_DIR}" -type f ! -path '*/.*/*' | while IFS= read -r SRC_FILE; do
    RELATIVE_PATH="${SRC_FILE#${AIROHA_MBEDTLS_SRC_DIR}/}"
    DEST_FILE="${AIROHA_MBEDTLS_DEST_DIR}/${RELATIVE_PATH}"
    mkdir -p "$(dirname "${DEST_FILE}")"
    if [ ! -f "${DEST_FILE}" ] || ! cmp -s "${SRC_FILE}" "${DEST_FILE}"; then
        cp "${SRC_FILE}" "${DEST_FILE}"
        echo "copy ${SRC_FILE} to ${DEST_FILE}"
    fi
done


AIROHA_ZEPHYR_MODULE="${CURR_DIR}/airoha/mcu"
AIROHA_MCUBOOT_MODULE="${CURR_DIR}/airoha/mcu/applications/mcuboot"
if [ -e "${CURR_DIR}/modules/lib/matter/config/airoha/chip-module" ]; then
    THIRD_PARTY_MATTER_MODULE=${CURR_DIR}/modules/lib/matter/config/airoha/chip-module
    export ZEPHYR_EXTRA_MODULES="${AIROHA_ZEPHYR_MODULE};${AIROHA_MCUBOOT_MODULE};${THIRD_PARTY_MATTER_MODULE}"
else
    export ZEPHYR_EXTRA_MODULES="${AIROHA_ZEPHYR_MODULE};${AIROHA_MCUBOOT_MODULE}"
fi

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

OUTPUT_FOLDER=out/ab1623m_evk/keychron_mouse_LM7
OUTPUT_LOG_FOLDER=${OUTPUT_FOLDER}/log
BUILD_LOG=build_ab1623m_evk_keychron_mouse_LM7.log

START_TIME_IN_SEC=$(TZ=UTC date +%s)

 west build -p auto -d out/ab1623m_evk/keychron_mouse_LM7 -b ab1623m_evk --sysbuild airoha/mcu/applications/Keychron_LM7_design_mouse -- -DSB_CONF_FILE=config/ab1623m_evk/sysbuild_with_mcuboot.conf -Dmcuboot_DTC_OVERLAY_FILE=config/ab162x_evb/mcuboot.overlay -Dmcuboot_CONF_FILE=config/ab162x_evb/air_mcuboot.conf -DKeychron_LM7_design_mouse_DTC_OVERLAY_FILE=config/ab1623m_evk/hid_device_ref_design_mouse_m20_pro.overlay -DKeychron_LM7_design_mouse_CONF_FILE=config/ab1623m_evk/hid_device_ref_design_mouse_m20_pro.conf 2>&1 | tee build_ab1623m_evk_keychron_mouse_LM7.log
BUILD_RESULT=$?

END_TIME_IN_SEC=$(TZ=UTC date +%s)
TIME_ELAPSED_IN_SEC=$((END_TIME_IN_SEC - START_TIME_IN_SEC))

TIME_ELAPSED_MINUTE_PART=$((TIME_ELAPSED_IN_SEC / 60))
TIME_ELAPSED_SEC_PART=$((TIME_ELAPSED_IN_SEC % 60))

if [ -f "${BUILD_LOG}" ]; then
    echo -e "[Airoha][Build] Total Build Time: ${TIME_ELAPSED_MINUTE_PART} min ${TIME_ELAPSED_SEC_PART} s"
    echo -e "[Airoha][Build] Total Build Time: ${TIME_ELAPSED_MINUTE_PART} min ${TIME_ELAPSED_SEC_PART} s" >> "${BUILD_LOG}"
    if [ ${BUILD_RESULT} -eq 0 ]; then
        echo -e "Build Result: ${GREEN}PASS${COLOR_OFF}"
        BUILD_RESULT="pass"
    else
        echo -e "Build Result: ${RED}FAIL${COLOR_OFF}(${BUILD_RESULT})"
        BUILD_RESULT="fail"
    fi

    if [ ! -d "${OUTPUT_FOLDER}" ]; then
        mkdir -p "${OUTPUT_FOLDER}"
        # In some cases, build directory has not yet been create because of project build failed.
        sleep 1
    fi

    if [ ! -d "${OUTPUT_LOG_FOLDER}" ]; then
        mkdir -p "${OUTPUT_LOG_FOLDER}"
        echo ${BUILD_RESULT} > "${OUTPUT_LOG_FOLDER}"/build_status
    fi

    mv ${BUILD_LOG} "${OUTPUT_FOLDER}"/build.log
    cp "${OUTPUT_FOLDER}"/build.log "${OUTPUT_LOG_FOLDER}"/err.log
fi
