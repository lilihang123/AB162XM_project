/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 */

#ifndef __APP_ARGB_TEST_H__
#define __APP_ARGB_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start the ARGB LED demo (red breathing + green constant).
 * @return 0 on success, negative error code on failure.
 */
int app_argb_demo_start(void);

/**
 * @brief Stop the ARGB LED demo and turn off all LEDs.
 * @return 0 on success, negative error code on failure.
 */
int app_argb_demo_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_ARGB_TEST_H__ */
