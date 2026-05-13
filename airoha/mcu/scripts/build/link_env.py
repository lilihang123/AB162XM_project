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


def link_env_toolchain():
    # Define the correct required directories
    required_env_dir = "/mtkoss/git/airoha/btd/.environment"
    required_riscv_tool_dir = "/mtkoss/git/airoha/btd/xpack-riscv-none-elf-gcc-13.2.0-2"

    # Path to the script in airoha/mcu/scripts/build
    script_path = os.path.join("airoha", "mcu", "scripts", "build", "link_env_toolchain.sh")

    # Check if both required directories exist
    if not (os.path.isdir(required_env_dir) and os.path.isdir(required_riscv_tool_dir)):
        print(f"Notice: One or both required directories do not exist:")
        print(f"- Environment directory: {required_env_dir} - {'Exists' if os.path.isdir(required_env_dir) else 'Missing'}")
        print(f"- RISC-V toolchain directory: {required_riscv_tool_dir} - {'Exists' if os.path.isdir(required_riscv_tool_dir) else 'Missing'}")
        print("This does not appear to be an Airoha internal codebase.")
        print("Environment toolchain linking will be skipped.")
        # Continue with other build tasks
    else:
        # Execute the link_env_toolchain.sh script
        if os.path.exists(script_path):
            print(f"Setting up environment links using {script_path}...")
            try:
                # Make sure the script is executable
                os.chmod(script_path, 0o755)  # rwxr-xr-x

                # Execute the script using os.system
                exit_code = os.system(f"bash {script_path}")

                if exit_code == 0:
                    print("Environment links setup completed successfully.")
                else:
                    print(f"Warning: Environment links setup exited with code {exit_code}")
            except Exception as e:
                print(f"Error setting up environment links: {e}")
        else:
            print(f"Warning: Link environment script not found at {script_path}")

    # ... continue with the rest of the build process ...


if __name__ == "__main__":
    import os
    link_env_toolchain()

