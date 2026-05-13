#/*
# * Copyright Statement:
# *
# * This software/firmware and related documentation ("MediaTek Software") are
# * protected under relevant copyright laws. The information contained herein
# * is confidential and proprietary to MediaTek Inc. and/or its licensors.
# * Without the prior written permission of MediaTek inc. and/or its licensors,
# * any reproduction, modification, use or disclosure of MediaTek Software,
# * and information contained herein, in whole or in part, shall be strictly
# * prohibited.
# *
# * MediaTek Inc. (C) 2015. All rights reserved.
# *
# * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
# * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
# * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND
# * ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
# * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
# * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
# * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
# * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
# * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
# * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
# * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
# * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBT FOR ANY MEDIATEK SOFTWARE
# * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
# * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
# * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE
# * THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR
# * SERVICE CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE
# * AT ISSUE.
# *
# * The following software/firmware and/or related documentation
# * ("MediaTek Software") have been modified by MediaTek Inc.
# * All revisions are subject to any receiver's applicable license agreements
# * with MediaTek Inc.
# */
#/* MediaTek restricted information */

cmake_minimum_required(VERSION 3.20.0)

#LIST(APPEND QEMU_EXTRA_FLAGS -serial unix:/tmp/bt-stack-tester)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(auto_bqb)

#zephyr_library_include_directories(${ZEPHYR_BASE}/samples/bluetooth)
#zephyr_library_include_directories(${ZEPHYR_BASE}/subsys/bluetooth/mesh)
#zephyr_library_include_directories(${ZEPHYR_BASE}/subsys/bluetooth/host)
include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)
include(${AIR_ROOT_DIR}/cmake/common/download_cfg.cmake)

#if(CONFIG_BT_L2CAP_DYNAMIC_CHANNEL)
#target_sources(app PRIVATE src/btp_l2cap.c)
#endif()

#if(CONFIG_BT_MESH)
#target_sources(app PRIVATE src/btp_mesh.c)
#endif()

#if(CONFIG_BT_IAS OR CONFIG_BT_IAS_CLIENT)
#target_sources(app PRIVATE src/btp_ias.c)
#endif()

#if(CONFIG_BT_OTS)
#    target_sources(app PRIVATE src/btp_ots.c)
#endif()

#zephyr_library_include_directories(src src/btp src/audio/btp)
#add_subdirectory_ifdef(CONFIG_BT_AUDIO src/audio)

#target_sources(app PRIVATE
#    src/main.c  ../../../../../zephyr/tests/bluetooth/tester/src/main.c
#    src/btp.c
#    src/btp_core.c
#    src/btp_gap.c
#    src/btp_gatt.c
#    )

target_sources(app PRIVATE
#   ../../../../../../../zephyr/tests/bluetooth/tester/src/main.c
    ../../../../../../../zephyr/tests/bluetooth/tester/src/btp.c
    ../../../../../../../zephyr/tests/bluetooth/tester/src/btp_core.c
    ../../../../../../../zephyr/tests/bluetooth/tester/src/btp_gap.c
    ../../../../../../../zephyr/tests/bluetooth/tester/src/btp_gatt.c
    src/main.c
    src/btp_vendor.c
    )
if(CONFIG_BT_L2CAP_DYNAMIC_CHANNEL)
target_sources(app PRIVATE ../../../../../../../zephyr/tests/bluetooth/tester/src/btp_l2cap.c)
endif()

if(CONFIG_BT_MESH)
target_sources(app PRIVATE ../../../../../../../zephyr/tests/bluetooth/tester/src/btp_mesh.c)
endif()

if(CONFIG_BT_IAS OR CONFIG_BT_IAS_CLIENT)
target_sources(app PRIVATE ../../../../../../../zephyr/tests/bluetooth/tester/src/btp_ias.c)
endif()

if(CONFIG_BT_OTS)
    target_sources(app PRIVATE ../../../../../../../zephyr/tests/bluetooth/tester/src/btp_ots.c)
endif()

zephyr_library_include_directories(../../../../../../../zephyr/tests/bluetooth/tester/src ../../../../../../../zephyr/tests/bluetooth/tester/src/btp ../../../../../../../zephyr/tests/bluetooth/tester/src/audio/btp)
zephyr_include_directories(./inc)
add_subdirectory_ifdef(CONFIG_BT_AUDIO ../../../../zephyr/tests/bluetooth/tester/src/audio)
include(${AIR_ROOT_DIR}/cmake/common/gen_nvs.cmake)
