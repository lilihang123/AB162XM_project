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
      __IO uint8_t LED_POL;       /* polarity setting of led */
      __IO uint8_t LED_FORCE_OFF; /* force led lights-off */
      __I uint8_t RESERVED[2];
    } QDEC_LED_CON_CELLS;
    __IO uint32_t QDEC_LEED_CON; /*0x42101000:led control setting */
  } QDEC_LED_CON_UNION;

  union
  {
    struct
    {
      __IO uint16_t Z_SUM_THR;  /* setting z_sum threshold to trigger interrupt */
      __IO uint8_t Z_COUNT_THR; /* setting z_count threshold to trigger interrupt */
      __IO uint8_t Z_DIV;       /* choose divider for z_count:0 set z_count = z_sum/2, 1 set z_count = z_sum/4 */
    } QDEC_SAMPLE_THR_CELLS;
    __IO uint32_t QDEC_SAMPLE_THR; /*0x42101004:sample control setting */
  } QDEC_SAMPLE_THR_UNION;

  union
  {
    struct
    {
      __IO uint16_t SMP_PERIOD_A; /* sample period setting:(n+1)*31.25us */
      __IO uint8_t LED_PERIOD_A;  /* led lights-on period setting:(n+1)*31.25us */
      __IO uint8_t DBC_COUNT_A;   /* setting debounce count */
    } QDEC_SAMPLE_CON_A_CELLS;
    __IO uint32_t QDEC_SAMPLE_CON_A; /*0x42101008:sample,debounce time,led period setting */
  } QDEC_SAMPLE_CON_A_UNION;

  union
  {
    struct
    {
      __IO uint16_t SMP_PERIOD_B; /* sample period setting:(n+1)*31.25us */
      __IO uint8_t LED_PERIOD_B;  /* led lights-on period setting:(n+1)*31.25us */
      __IO uint8_t DBC_COUNT_B;   /* setting debounce count */
    } QDEC_SAMPLE_CON_B_CELLS;
    __IO uint32_t QDEC_SAMPLE_CON_B; /*0x4210100c:sample,debounce time,led period setting */
  } QDEC_SAMPLE_CON_B_UNION;

  union
  {
    struct
    {
      __O uint8_t SW_RELOAD;   /* reload a/b reg group setting */
      __O uint8_t QDEC_ENABLE; /* enable qdec  */
      __I uint8_t RESERVED;    /* reserved*/
      __O uint8_t SW_RSTB;     /* reset  qdec to default */
    } QDEC_CON_CELLS;
    __O uint32_t QDEC_CON; /*0x421010010:qdec start or reload register */
  } QDEC_CON_UNION;

  union
  {
    struct
    {
      __IO uint8_t SEL_GROUP;    /*reg group select :using a/b reg group */
      __IO uint8_t HW_SEL_EN; /* enable hw reload when qdec detect z-axis change */
      __IO uint8_t HW_SEL_GROUP;  /* select :using a/b reg group  */
      __I uint8_t RESERVED;      /* reserved */
    } QDEC_SEL_GROUP_CELLS;
    __O uint32_t QDEC_SEL_GROUP; /*0x421010014:qdecd select group a/b reg*/
  } QDEC_SEL_GROUP_UNION;

  __IO uint32_t RESERVED1[2]; /*0x42101018/0x4210101C: reserved  */

  union
  {
    struct
    {
      __IO uint8_t IRQ_ENABLE_Z_SUM;    /* enable irq of z value >= z sum event */
      __IO uint8_t IRQ_ENABLE_Z_CNT;    /* enable irq of z value >= z cnt event */
      __IO uint8_t IRQ_ENABLE_DATA_RDY; /* enable irq of data ready event */
      __I uint8_t RESERVED;
    } QDEC_IRQ_ENABLE_CELLS;
    __IO uint32_t QDEC_IRQ_ENABLE; /*0x42101020:enable interrupt event */
  } QDEC_IRQ_ENABLE_UNION;

  union
  {
    struct
    {
      __IO uint8_t WKUP_ENABLE_Z_SUM; /* enable event of z value >= z sum event */
      __IO uint8_t WKUP_ENABLE_Z_CNT; /* enable event of z value >= z cnt event */
      __I uint8_t RESERVED[2];
    } QDEC_WKUP_ENABLE_CELLS;
    __IO uint32_t QDEC_WKUP_ENABLE; /*0x42101024:enable wake up event */
  } QDEC_WKUP_ENABLE_UNION;

  union
  {
    struct
    {
      __IO uint8_t LATCH_N_CLR;  /* trigger latch & clear */
      __I uint8_t LATCH_STATUS; /* status of latch & cleara action */
      __I uint8_t RESERVED[2];
    } QDEC_LATCH_N_CLR_CELLS;
    __IO uint32_t QDEC_LATCH_N_CLR; /*0x42101028:latch and clear */
  } QDEC_LATCH_N_CLR_UNION;

  union
  {
    struct
    {
      __O uint8_t IRQ_CLR_Z_THR_NOTIFY; /* clear irq notify*/
      __O uint8_t IRQ_CLR_Z_THR_EVENT;  /* clear irq event  */
      __O uint8_t IRQ_CLR_DATA_RDY;     /* clear data ready status */
      __I uint8_t RESERVED;             /* reserved*/
    } QDEC_IRQ_LCR_CELLS;
    __O uint32_t QDEC_IRQ_LCR; /*0x42101002C:qdec start or reload register */
  } QDEC_IRQ_LCR_UNION;

  union
  {
    struct
    {
      __O uint8_t WKUP_LCR_Z_THR_NOTIFY; /* clear wkup notify */
      __O uint8_t WKUP_LCR_Z_THR_EVENT;  /* clear wkup event  */
      __I uint8_t RESERVED[2];           /* reserved */
    } QDEC_WKUP_LCR_CELLS;
    __O uint32_t QDEC_WKUP_LCR; /*0x421010030:clear wake up event register */
  } QDEC_WKUP_LCR_UNION;

  union
  {
    struct
    {
      __I uint16_t Z_SUM; /* value of z_sum */
      __I uint16_t Z_CNT; /* value of z_sum/z_div */
    } QDEC_Z_INFO_CELLS;
    __I uint32_t QDEC_Z_INFO; /*0x42101034:sum of moving direction error result */
  } QDEC_Z_INFO_UNION;

  union
  {
    struct
    {
      __I uint16_t SMP_CNT;     /* value of invalid z-axis */
      __I uint16_t INVALID_CNT; /* value of sample times */
    } QDEC_SAMPLE_INFO_CELLS;
    __I uint32_t QDEC_SAMPLE_INFO; /*0x42101038:sample times and invalid times */
  } QDEC_SAMPLE_INFO_UNION;

  __IO uint32_t RESERVED2[2]; /*0x4210103C: reserved  */

  union
  {
    struct
    {
      __O uint8_t SW_RELOAD_CLR;    /* clear sw reload status */
      __I uint8_t SW_RELOAD_STATUS; /* sw reload finished status */
      __I uint8_t RESERVED[2];
    } QDEC_SW_RELOAD_CLR_CELLS;
    __IO uint32_t QDEC_SW_RELOAD_CLR; /*0x42101044:sw reload clear & status */
  } QDEC_SW_RELOAD_CLR_UNION;

  union
  {
    struct
    {
      __I uint8_t QDEC_STATE;     /* value of qdec sample state */
      __I uint8_t QDEC_SEL_GROUP; /* value of qdec using group */
      __I uint8_t RESERVED[2];
    } QDEC_INFO_CELLS;
    __IO uint32_t QDEC_INFO; /*0x42101048:engine and 32k domain reg status */
  } QDEC_INFO_UNION;

  union
  {
    struct
    {
      __I uint8_t IRQ_STATUS_Z_SUM;    /* interrupt is trigger by z value >= z sum event */
      __I uint8_t IRQ_STATUS_Z_CNT;    /* interrupt is trigger by z value >= z cnt event */
      __I uint8_t IRQ_STATUS_DATA_RDY; /* interrupt is trigger by data ready event */
      __I uint8_t RESERVED[1];
    } QDEC_IRQ_STATUS_CELLS;
    __I uint32_t QDEC_IRQ_STATUS; /*0x4210104C:status of interrupt event */
  } QDEC_IRQ_STATUS_UNION;

  union
  {
    struct
    {
      __I uint8_t WKUP_STATUS_Z_SUM; /* wake up event is trigger by z value >= z sum event */
      __I uint8_t WKUP_STATUS_Z_CNT; /* wake up event is trigger by z value >= z cnt event */
      __I uint8_t RESERVED[2];
    } QDEC_WKUP_STATUS_CELLS;
    __IO uint32_t QDEC_WKUP_STATUS; /*0x42101050:status of interrupt event */
  } QDEC_WKUP_STATUS_UNION;

  union
  {
    struct
    {
      __I uint8_t IRQ_EVENT_STATUS_Z_SUM; /* irq event is trigger by z value >= z sum event */
      __I uint8_t IRQ_EVENT_STATUS_Z_CNT; /* irq event is trigger by z value >= z cnt event */
      __I uint8_t RESERVED[2];
    } QDEC_IRQ_EVENT_STATUS_CELLS;
    __IO uint32_t QDEC_IRQ_EVENT_STATUS; /*0x42101054:status of interrupt event */
  } QDEC_IRQ_EVENT_STATUS_UNION;

  union
  {
    struct
    {
      __I uint8_t WKUP_EVENT_STATUS_Z_SUM; /* wakeup event is trigger by z value >= z sum event */
      __I uint8_t WKUP_EVENT_STATUS_Z_CNT; /* wakeup event is trigger by z value >= z cnt event */
      __I uint8_t RESERVED[2];
    } QDEC_WKUP_EVENT_STATUS_CELLS;
    __IO uint32_t QDEC_WKUP_EVENT_STATUS; /*0x42101058:status of  event */
  } QDEC_WKUP_EVENT_STATUS_UNION;

  __IO uint32_t RESERVED3; /*0x42101005c: reserved  */

  __IO uint32_t QDEC_DEBUG_SEL; /*0x42101060: select debug group number */
  __I uint32_t QDEC_DEBUG_ADDR; /*0x42101064: value of debug group number */

} HW_QDEC_REGISTER_T;

/* qdec status of interrupt event Register */
#define QDEC_IRQ_DATAREADY_OFFSEET        (16)
#define QDEC_IRQ_DATAREADY_MASK           (0x1<<QDEC_IRQ_DATAREADY_OFFSEET)
#define QDEC_IRQ_Z_CNT_OFFSET             (8)
#define QDEC_IRQ_Z_CNT_MASK               (0x1<<QDEC_IRQ_Z_CNT_OFFSET)
#define QDEC_IRQ_Z_SUM_OFFSET             (0)
#define QDEC_IRQ_Z_SUM_MASK               (0x1<<QDEC_IRQ_Z_SUM_OFFSET)

