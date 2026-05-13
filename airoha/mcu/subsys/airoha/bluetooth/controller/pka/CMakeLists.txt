# Copyright Statement:
#
# (C) 2025  Airoha Technology Corp. All rights reserved.
#
# This software/firmware and related documentation ("Airoha Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
# Without the prior written permission of Airoha and/or its licensors,
# any reproduction, modification, use or disclosure of Airoha Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.
# You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
# if you have agreed to and been bound by the applicable license agreement with
# Airoha ("License Agreement") and been granted explicit permission to do so within
# the License Agreement ("Permitted User").  If you are not a Permitted User,
# please cease any access or use of Airoha Software immediately.
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
# ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
# WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
# CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
# AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.


include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)

set(PKA_PROTECT_ROOT ${AIR_ROOT_DIR}/subsys/airoha/pka_protected)
set(PKA_ROOT ${PKA_PROTECT_ROOT}/pikachu/btcon)
set(PKA_PLUGIN_ROOT ${PKA_PROTECT_ROOT}/pikachu_plugin/btcon)
set(PKA_802154_PLUGIN_ROOT ${PKA_PROTECT_ROOT}/pikachu_plugin/ieee802154)
set(PKA_TARGET_BOARD_PATH ${PKA_PLUGIN_ROOT}/board/${PKA_TARGET_BOARD})
set(PKA_802154_TARGET_BOARD_PATH ${PKA_802154_PLUGIN_ROOT}/board/${PKA_TARGET_BOARD})
set(PKA_TOOLS_ROOT ${PKA_PROTECT_ROOT}/pikachu_tools)
zephyr_library_named(pka_${PKA_TARGET_LIB})

zephyr_include_directories(../)
zephyr_include_directories(${PKA_TARGET_BOARD_PATH}/lib/${PKA_TARGET_LIB})
zephyr_include_directories(${PKA_TARGET_BOARD_PATH}/inc)
zephyr_include_directories(${PKA_802154_TARGET_BOARD_PATH}/inc)
zephyr_include_directories(${AIR_SUBSYS_PKA_ROOT}/inc)

# generate hwmac instruction table
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/src/LC/tsvr/frame)
#execute_process(
#    COMMAND ${PYTHON_EXECUTABLE} ${PKA_TOOLS_ROOT}/tool/hwmac_common_converter.py ${PKA_PLUGIN_ROOT}/
#    )
if(CONFIG_BT_PKA_INST_TEST)
    message("${PYTHON_EXECUTABLE} ${PKA_TOOLS_ROOT}/tool/convert.py ${PKA_PLUGIN_ROOT}/test/cases/case${CONFIG_BT_PKA_INST_TEST_CASE} ${PKA_PLUGIN_ROOT}/test/LC_HwmacInstTable.c")
    execute_process(
        COMMAND ${PYTHON_EXECUTABLE} ${PKA_TOOLS_ROOT}/tool/convert.py ${PKA_PLUGIN_ROOT}/test/cases/case${CONFIG_BT_PKA_INST_TEST_CASE} ${PKA_PLUGIN_ROOT}/test/LC_HwmacInstTableTestCases.c
        )
    message("${PKA_PLUGIN_ROOT}/gen_hwmac_inst_table.sh testhdr ${PKA_PLUGIN_ROOT}/test/cases/case${CONFIG_BT_PKA_INST_TEST_CASE}/HwmacInstTbl_Case.c ${PKA_PLUGIN_ROOT}/test/LC_HwmacInstTableTestCases.c")
    execute_process(
        COMMAND /bin/bash ${PKA_PLUGIN_ROOT}/gen_hwmac_inst_table.sh testhdr ${PKA_PLUGIN_ROOT}/test/cases/case${CONFIG_BT_PKA_INST_TEST_CASE}/HwmacInstTbl_Case.c ${PKA_PLUGIN_ROOT}/test/LC_HwmacInstTableTestCases.c
        )
else()
    message("${PYTHON_EXECUTABLE} ${PKA_TOOLS_ROOT}/tool/convert.py -d ${PKA_PLUGIN_ROOT}/src/LC/tsvr/frame/hwmac ${PROJECT_BINARY_DIR}/src/LC/tsvr/frame/LC_HwmacInstTable.c ${PKA_TARGET_LIB}")
    execute_process(
        #COMMAND ${PYTHON_EXECUTABLE} ${PKA_TOOLS_ROOT}/tool/convert.py ${PKA_PLUGIN_ROOT}/src/LC/tsvr/frame/hwmac ${PKA_PLUGIN_ROOT}/src/LC/tsvr/frame/LC_HwmacInstTable.c
        COMMAND ${PYTHON_EXECUTABLE} ${PKA_TOOLS_ROOT}/tool/convert.py -d ${PKA_PLUGIN_ROOT}/src/LC/tsvr/frame/hwmac ${PROJECT_BINARY_DIR}/src/LC/tsvr/frame/LC_HwmacInstTable.c ${PKA_TARGET_LIB}
        )
    execute_process(
        COMMAND /bin/bash ${PKA_PLUGIN_ROOT}/gen_hwmac_inst_table.sh hdr ${PROJECT_BINARY_DIR}/src/LC/tsvr/frame/LC_HwmacInstTable.c
        )
endif()


# generate verno
set(PKAP_LAST_COMMIT "TempVer")
set(PKA_LAST_COMMIT "TempVer")
string(TIMESTAMP PKA_BUILD_TIME "%Y%m%d%H%M%S")
find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --always --dirty
        WORKING_DIRECTORY ${PKA_ROOT}
        OUTPUT_VARIABLE PKA_LAST_COMMIT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        )
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --always --dirty
        WORKING_DIRECTORY ${PKA_PLUGIN_ROOT}
        OUTPUT_VARIABLE PKAP_LAST_COMMIT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        )
endif()
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/bt_pikachu_lib_verno.h.in
    ${PROJECT_BINARY_DIR}/include/generated/zephyr/bt_pikachu_lib_verno.h
    @ONLY
    )
zephyr_library_sources(bt_pikachu_lib_verno.c)
message(STATUS "pka ${ZEPHYR_CURRENT_LIBRARY} git version ${PKAP_LAST_COMMIT}, ${PKA_LAST_COMMIT} build time ${PKA_BUILD_TIME}")


#zephyr_include_directories(prebuilt/subsys/nvkey)

#include proprietary pka source
include(${PKA_TARGET_BOARD_PATH}/lib/${PKA_TARGET_LIB}/CMakeLists.txt)

#execute_process(
#    COMMAND ${CMAKE_COMMAND} -E compare_files
#        ${AIR_MODULE_OUT_PATH}/subsys/bluetooth/controller/pka/lib${ZEPHYR_CURRENT_LIBRARY}.a
#        ${AIR_PREBUILT_LIB_ROOT}/bluetooth/controller/lib${ZEPHYR_CURRENT_LIBRARY}.a
#    RESULT_VARIABLE compare_result
#    )
#if(compare_result EQUAL 0)
#    message(STATUS "libpka_${PKA_TARGET_LIB}.a no changed")
#elseif(compare_result EQUAL 1)
#    message(STATUS "libpka_${PKA_TARGET_LIB}.a coppied to ${AIR_PREBUILT_LIB_ROOT}/bluetooth/controller/")
#else()
#    message(STATUS "Error while comparing the files")
#endif()

# copy lib to prebuilt folder
#add_custom_command(
#    TARGET ${ZEPHYR_CURRENT_LIBRARY}
#    POST_BUILD
#    COMMAND
#    ${CMAKE_COMMAND} -E copy
#    ${AIR_MODULE_OUT_PATH}/subsys/airoha/bluetooth/controller/pka/lib${ZEPHYR_CURRENT_LIBRARY}.a
#    ${AIR_PREBUILT_LIB_ROOT}/middleware/airoha/bluetooth/${SOC_SERIES}/controller/lib${ZEPHYR_CURRENT_LIBRARY}.a
#    )

# copy lib to prebuilt folder
airoha_copy_file_with_lock_and_rename(
    lib${ZEPHYR_CURRENT_LIBRARY}.a
    ${AIR_MODULE_OUT_PATH}/subsys/airoha/bluetooth/controller/pka
    ${AIR_PREBUILT_LIB_ROOT}/middleware/airoha/bluetooth/${SOC_SERIES}/controller
    lib${ZEPHYR_CURRENT_LIBRARY}${PKA_TARGET_LIB_POST_STR}.a
)

# gen zi_region.txt for cosim
if(CONFIG_BT_PKA_LIB_COSIM)
    add_custom_target(genzi ALL
        COMMAND
        /bin/bash ${PKA_TOOLS_ROOT}/build_script/genzi.sh ${APPLICATION_BINARY_DIR}/zephyr/zephyr.map ${APPLICATION_BINARY_DIR}/zi_region.txt
        DEPENDS ${APPLICATION_BINARY_DIR}/zephyr/zephyr.map
        )
endif()


