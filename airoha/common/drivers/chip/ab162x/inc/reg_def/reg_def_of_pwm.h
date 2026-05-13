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

#ifndef __PWM_REG_DEFINITION_H__
#define __PWM_REG_DEFINITION_H__


 /* *************************pwm hardware definition start line**********************************
*/

/*pwm register structure definition*/
typedef struct {
    __IO uint32_t PWM_CTRL;         /*!<  PWM control register Address offset: 0x00 */
    __IO uint32_t PWM_COUNT;        /*!< PWM counter register Address offset: 0x04 */
    __IO uint32_t PWM_THRESH;      /*!<  pwm thresh up registerAddress offset:   0x08 */
    __IO uint32_t PWM_THRESH_DOWN;      /*!<  pwm thresh down registerAddress offset:   0x0c */
    __IO uint32_t PWM_POL; 
} PWM_REGISTER_T;


/*the bit value in PWM  control  register*/
#define PWM_CLK_SEL_OFFSET            (2)
#define PWM_CLK_SEL_MASK              (0x3<< PWM_CLK_SEL_OFFSET)

#define PWM_CLK_SEL_13M_MASK          (0x0<< PWM_CLK_SEL_OFFSET)

#define PWM_CLK_SEL_32K_MASK          (0x1<< PWM_CLK_SEL_OFFSET)

#define PWM_CLK_SEL_40M_MASK          (0x2<< PWM_CLK_SEL_OFFSET)

/*the bit mask definition in  PWM control  register */
#define PWM_CLK_DIV_OFFSET            (0)
#define PWM_CLK_DIV_MASK                   (0x3<< PWM_CLK_DIV_OFFSET)



/* *************************pwm hardware definition end line**********************************/
#endif /*__PWM_2_REG_DEFINITION_H__*/
