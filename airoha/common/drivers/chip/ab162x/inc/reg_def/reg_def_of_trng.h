/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

#ifndef __TRNG_REG_DEFINITION_H__
#define __TRNG_REG_DEFINITION_H__


#include <stdint.h>

/* *************************trng hardware definition start line**********************************
*/

typedef struct {
    __IO uint32_t TRNG_CTRL;         /*!<  trng control register address offset: 0x00 */
    __IO uint32_t TRNG_TIME;         /*!<  trng time register address offset: 0x04 */
    __I  uint32_t TRNG_DATA;         /*!<  trng data register address offset: 0x08 */
    __IO uint32_t TRNG_CONF;         /*!<  trng configure register address offset: 0x0C */
    __I  uint32_t TRNG_INT_SET;      /*!<  trng interrupt setting register address offset: 0x10 */
    __O  uint32_t TRNG_INT_CLR;      /*!<  trng interrupt clean  register address offset: 0x14 */
} TRNG_REGISTER_T;


#define  TRNG                           ((TRNG_REGISTER_T *) (TRNG_BASE))

/* the bit value in TRNG  CONTROL register */
#define  TRNG_START_OFFSET              (0)
#define  TRNG_START_MASK                (0x1UL<< TRNG_START_OFFSET)

#define  TRNG_STOP_OFFSET               (0)
#define  TRNG_STOP_MASK                 (0x1UL<< TRNG_STOP_OFFSET)

/* the bit value in TRNG INT_SET register */
#define  TRNG_RDY_OFFSET                (0)
#define  TRNG_RDY_MASK                  (0x1UL<< TRNG_RDY_OFFSET)

/* the bit value in TRNG INT_SET register */
#define  TRNG_TIMEOUT_OFFSET            (1)
#define  TRNG_TIMEOUT_MASK              (0x1UL<< TRNG_TIMEOUT_OFFSET)

/* the bit value in TRNG INT_CLR register */
#define  TRNG_INT_CLR_OFFSET            (0)
#define  TRNG_INT_CLR_MASK              (0x3UL<< TRNG_INT_CLR_OFFSET)

/* the bit value in TRNG  CONF register */
#define  TRNG_H_FIRO_OFFSET             (8)
#define  TRNG_H_FIRO_EN_MASK            (0x1UL<< TRNG_H_FIRO_OFFSET)

#define  TRNG_H_RO_EN_OFFSET            (9)
#define  TRNG_H_RO_EN_MASK              (0x1UL<< TRNG_H_RO_EN_OFFSET)

#define  TRNG_H_GARO_OFFSET             (10)
#define  TRNG_H_GARO_EN_MASK            (0x1UL<< TRNG_H_GARO_OFFSET)

#define  TRNG_H_GARO2_OFFSET            (11)
#define  TRNG_H_GARO2_EN_MASK           (0x1UL<< TRNG_H_GARO_OFFSET)

#define  TRNG_H_GARO3_OFFSET            (12)
#define  TRNG_H_GARO3_EN_MASK           (0x1UL<< TRNG_H_GARO_OFFSET)

#define  TRNG_H_GARO4_OFFSET            (13)
#define  TRNG_H_GARO4_EN_MASK           (0x1UL<< TRNG_H_GARO_OFFSET)

#define  TRNG_H_GARO5_OFFSET            (14)
#define  TRNG_H_GARO5_EN_MASK           (0x1UL<< TRNG_H_GARO_OFFSET)

#define  TRNG_VON_EN_OFFSET             (28)
#define  TRNG_VON_EN_MASK               (0x1UL<< TRNG_VON_EN_OFFSET)


/* *************************trng hardware definition end line**********************************
*/


#endif /* __TRNG_REG_DEFINITION_H__ */