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

/* Register definitions for qdec*/
typedef struct
{
  union
  {
    struct
    {
      __IO uint8_t RAMBOZ_DIRECTION; /* directin seetting */
      __IO uint8_t RAMBOZ_5CNT_MODE; /* z count mode setting */
      __IO uint8_t IRQ_ENABLE;       /* irq enable setting */
      __IO uint8_t WKUP_ENABLE;      /*wake up event enable setting */
    } RAMBOZ_CFG_CELLS;
    __IO uint32_t RAMBOZ_CFG; /*0x42102000:ramboz config register */
  } RAMBOZ_CFG_UNION;

  __IO uint32_t FILTER_PERIOD;      /*0x42102004: filter period setting */
  __IO uint32_t FAST_SAMPLE_PERIOD; /*0x42102008: fast sample period setting */
  __IO uint32_t SLOW_SAMPLE_PERIOD; /*0x4210200c: slow sample period setting */
  __IO uint32_t FAST_ROLL_PERIOD;   /*0x42102010: fast roll period setting */

  union
  {
    struct
    {
      __O uint8_t SW_FORCE_FAST_SAMPLE; /* sw force fast sample */
      __O uint8_t SW_FORCE_SLOW_SAMPLE; /* sw force slow sample */
      __O uint8_t SAMPLE_RATE_CHANGE;   /* sample rate change */
      __I uint8_t RESERVE;
    } SAMPLE_RATE_CONTROL_CELLS;
    __O uint32_t SAMPLE_RATE_CONTROL;
  } SAMPLE_RATE_CONTROL_UNION;

  __I uint32_t RESERVE1[2]; /*0x42102018/1C:  */

  __IO uint32_t RAMBOZ_IRQ_MASK; /*0x42102020: select debug group number */

  union
  {
    struct
    {
      __IO uint8_t IRQ_NOTIFY_CLR; /* clear irq notify */
      __O uint8_t IRQ_EVENT_CLR;   /* clear wake up event*/
      __I uint8_t RESERVE[2];
    } RAMBOZ_IRQ_CLR_CELLS;
    __O uint32_t RAMBOZ_IRQ_CLR;
  } RAMBOZ_IRQ_CLR_UNION; /*0x42102024: ramboz irq clear */

  __IO uint32_t RAMBOZ_WKUP_MASK; /*0x42102028: ramboz wake up mask */

  union
  {
    struct
    {
      __IO uint8_t WKUP_NOTIFY_CLR; /* wake up notify clear */
      __O uint8_t WKUP_EVENT_CLR;   /* wake up event clear */
      __I uint8_t RESERVE[2];
    } RAMBOZ_WKUP_CLR_CELLS;
    __O uint32_t RAMBOZ_WKUP_CLR; /*0x4210202c:ramboz wakeup clear register */
  } RAMBOZ_WKUP_CLR_UNION;

  __IO uint32_t RAMBOZ_ENABLE; /*0x42102030: enable ramboz function */
  __I uint32_t RESERVE2[3];    /*0x42102034/38/3c:  */

  __IO uint32_t RAMBOZ_CNT; /*0x42102040: ramboz count register */

  union
  {
    struct
    {
      __I uint8_t Z_CNT; /* z cnt */
      __I uint8_t RESERVE1;
      __O uint8_t Z_CNT_LATCH_N_CLR; /* z cnt latch and clear */
      __I uint8_t RESERVE2;
    } RAMBOZ_Z_CNT_CELLS;
    __O uint32_t RAMBOZ_Z_CNT; /*0x42102044:z count register */
  } RAMBOZ_Z_CNT_UNION;

  __I uint32_t RAMBOZ_IRQ_STATE; /*0x42102048:irq enable*/

  __I uint32_t RAMBOZ_WKUP_STATE; /*0x4210204c: wake up enable */

  union
  {
    struct
    {
      __I uint8_t DEBUG_MON; /* debug mon */
      __I uint8_t RESERVE1;
      __IO uint8_t DEBUG_SEL; /* debug sel */
      __I uint8_t RESERVE2;
    } RAMBOZ_DEBUG_MON_CELLS;
    __O uint32_t RAMBOZ_DEBUG_MON; /*0x42102050:debug reg */
  } RAMBOZ_DEBUG_MON_UNION;

  union
  {
    struct
    {
      __I uint8_t LED_STATE;   /* led state */
      __I uint8_t SLEEP_STATE; /* sleep state */
      __I uint16_t LEDOFF_PERIOD_MUX;
    } RAMBOZ_DEBUG_INFO_0_CELLS;
    __I uint32_t RAMBOZ_DEBUG_INFO_0; /*0x42102054:debug reg */
  } RAMBOZ_DEBUG_INFO_0_UNION;

  union
  {
    struct
    {
      __I uint8_t IRQ_CLR_LEVEL_32K;    /* irq clear level of 32k */
      __I uint8_t WKUP_CLR_LEVEL_32K;   /* wake up clear level of 32k */
      __I uint8_t FORCE_FAST_LEVEL_32K; /* force fast level of 32k */
      __I uint8_t FORCE_SLOW_LEVEL_32K; /* force slow level of 32k  */
    } RAMBOZ_DEBUG_INFO_1_CELLS;
    __I uint32_t RAMBOZ_DEBUG_INFO_1; /*0x42102058:debug reg */
  } RAMBOZ_DEBUG_INFO_1_UNION;

} HW_RAMBZ_REGISTER_T;

/*irq status register*/
#define RAMBOZ_IRQ_STATUS_RAMBO_CNT_OFFSET      (0) /* RAMBO_CNT */
#define RAMBOZ_IRQ_STATUS_RAMBO_CNT_MASK        (0x1 << RAMBOZ_IRQ_STATUS_RAMBO_CNT_OFFSET)
#define RAMBOZ_IRQ_STATUS_Z_CNT_OFFSET          (1) /* Z_CNT */
#define RAMBOZ_IRQ_STATUS_Z_CNT_MASK            (0x1 << RAMBOZ_IRQ_STATUS_Z_CNT_OFFSET)
#define RAMBOZ_IRQ_STATUS_DATA_READY_OFFSET     (2) /* DATA READY */
#define RAMBOZ_IRQ_STATUS_DATA_READY_MASK       (0x1 << RAMBOZ_IRQ_STATUS_DATA_READY_OFFSET)
