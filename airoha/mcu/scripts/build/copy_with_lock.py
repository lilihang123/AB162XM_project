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
import time
import fcntl
import shutil

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Usage: python copy_with_lock.py <file_name> <src_dir> <dest_dir> <target_file_name>")
        sys.exit(1)

    file_name = sys.argv[1]
    src_dir = sys.argv[2]
    dest_dir = sys.argv[3]
    target_file_name = sys.argv[4]

    src_file = os.sep.join([src_dir, file_name])
    dest_file = os.sep.join([dest_dir, target_file_name])

    start_time = time.time()
    locked_file = open(dest_file, 'w')
    locked = False

    try:
        while True:
            try:
                fcntl.flock(locked_file, fcntl.LOCK_EX | fcntl.LOCK_NB)
                locked = True
                print(f"File {dest_file} is locked.")
                break
            except BlockingIOError:
                if time.time() - start_time >= 3:
                    print(f"Timeout: Could not lock file {dest_file} within 3 seconds")
                    break
                time.sleep(0.5)
                print(f"try lock file {dest_file} again...")
    finally:
        if locked:
            print(f"copy {src_file} to {dest_file}")
            shutil.copy(src_file, dest_file)
            fcntl.flock(locked_file, fcntl.LOCK_UN)
            print(f"File {dest_file} is unlocked.")
        locked_file.close()