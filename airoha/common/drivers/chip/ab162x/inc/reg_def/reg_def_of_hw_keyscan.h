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

/* Register definitions for HW keyscan */
typedef struct
{
  union
  {
    struct
    {
      __IO uint8_t SFR_ROW_NUM; /* keyscan col number */
      __IO uint8_t SFR_COL_NUM; /* keyscan row number */
      __I uint8_t RESERVED[2];
    } MATRIX_SIZE_CELLS;
    __IO uint32_t MATRIX_SIZE; /*00:keyscan matrix size */
  } MATRIX_SIZE_UNION;

  __IO uint32_t SFR_SCAN_MODE;            /*04: keyscan mode */
  __IO uint32_t SFR_IO_SW_TIME_SEL;       /*08: gpio switch time selection */
  __IO uint32_t SFR_KEYSCAN_RATE_DLY_SEL; /*0c: keyscan rate selection */
  __IO uint32_t SFR_DEB_EN;               /*10: debounce enable */
  __IO uint32_t SFR_RLS_DEB_TIME;         /*14: release debounce time */
  __IO uint32_t SFR_PRS_DEB_TIME;         /*18: press debounce time */

  __IO uint32_t SFR_COL_MAP[18]; /*1c: col0 input from gpiox */
  __IO uint32_t SFR_ROW_MAP[8];  /*80: row7 input from gpiox */

  __IO uint32_t SFR_KB_TYPE;        /*84: keyboard type selection */
  __IO uint32_t SFR_COL_IN_SETTING; /*88: keyboard column input setting */
  __IO uint32_t SFR_KEYSCAN_IO_EN;  /*8c: keyscan gpio enable */
  __IO uint32_t SFR_KEYSCAN_EN;     /*90: keyscan enable */
  __IO uint32_t AFIFO_DOUT;         /*94: keyscan data out register */

  union
  {
    struct
    {
      __IO uint8_t AFIFO_DNUM;      /* afifo num flag */
      __IO uint8_t AFIFO_EMPTY;     /* afifo empty flag */
      __IO uint8_t AFIFO_FULL_SYNC; /* afifo full flag */
      __IO uint8_t FIFO_STOP_FLAG;  /*fifo full , stop flag*/
    } AFIFO_STATUS_CELLS;
    __IO uint32_t AFIFO_STATUS; /*98:afifo status */
  } AFIFO_STATUS_UNION;

  __IO uint32_t RESERVED[25];  /*9c-fc: reserved */
  __IO uint32_t GHOST_KEY;     /*104: ghost key register */
  __IO uint32_t SFR_IRQ_CLEAR; /*108: keyscan irq clear */
  __IO uint32_t SOFT_RST;      /*10c: keyscan soft reset */

  union
  {
    struct
    {
      __IO uint8_t DEB_DONE_SYNC;     /* debounce done flag */
      __IO uint8_t KEYSCAN_READ_SYNC; /* keyscan read status flag */
      __IO uint8_t RESERVED[2];
    } STATUS_CELLS;
    __IO uint32_t STATUS; /*110:keyscan status register */
  } STATUS_UNION;
} HW_KEYSCAN_REGISTER_T;

// #define  HW_KEYSCAN   ((UART_REGISTER_T *)(HW_KEYSCAN_BASE))

/*SFR_KEYSCAN_IO_EN register*/
#define SFR_KEYSCAN_IO_DISENABLE (0X00)
#define SFR_KEYSCAN_IO_ENBLE (0X01)

/*SFR_KEYSCAN_EN register*/
#define SFR_KEYSCAN_DISENABLE (0X00)
#define SFR_KEYSCAN_ENBLE (0X01)