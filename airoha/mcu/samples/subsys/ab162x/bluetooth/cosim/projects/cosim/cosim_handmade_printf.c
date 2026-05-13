/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#include <stdarg.h>
#include <stdint.h>

#define HM_MAX_FRACT     10000
#define HM_NUM_FRACT     4
#define HM_LEN           20

#define HM_SLIM_UDIV_R(N, D, R) (((R)=(N)%(D)), ((N)/(D)))

static void bl_itoa(char **buf, uint32_t i, uint32_t base)
{
    char *s;
    uint32_t rem;
    static char rev[HM_LEN + 1];

    rev[HM_LEN] = 0;
    if (i == 0) {
        (*buf)[0] = '0';
        ++(*buf);
        return;
    }
    s = &rev[HM_LEN];
    while (i) {
        i = HM_SLIM_UDIV_R(i, base, rem);
        if (rem < 10) {
            *--s = rem + '0';
        } else if (base == 16) {
            *--s = "abcdef"[rem - 10];
        }
    }
    while (*s) {
        (*buf)[0] = *s++;
        ++(*buf);
    }
}

static void bl_itof(char **buf, int32_t i)
{
    char *s;
    int32_t rem, j;
    static char rev[HM_LEN + 1];

    rev[HM_LEN] = 0;
    s = &rev[HM_LEN];
    for (j = 0 ; j < HM_NUM_FRACT ; j++) {
        i = HM_SLIM_UDIV_R(i, 10, rem);
        *--s = rem + '0';
    }
    while (*s) {
        (*buf)[0] = *s++;
        ++(*buf);
    }
}

void handmade_printf(char *buf, const char *fmt, va_list ap)
{
    const char *cp;

    int32_t   ival;
    char     *sval;
    char     *bp, cval;
    int64_t   dval;
    int32_t   fract;
    uint32_t  uxval;
    uint32_t  uival, uival1, uival2;
    char     *bp_old;
    int32_t   i, j;

    bp = buf;
    *bp = 0;

    for (cp = fmt; *cp; cp++) {
        if (*cp != '%') {
            *bp++ = *cp;
            continue;
        }
        while(*(cp + 1) <= '9' && *(cp + 1) >= '0') {
            ++cp;
        }
        switch (*++cp) {
            case 'D':
            case 'd':
                ival = va_arg(ap, int32_t);
                if (ival < 0) {
                    *bp++ = '-';
                    ival = -ival;
                }
                bl_itoa(&bp, ival, 10);
                break;

            case 'O':
            case 'o':
                ival = va_arg(ap, int32_t);
                if (ival < 0) {
                    *bp++ = '-';
                    ival = -ival;
                }
                *bp++ = '0';
                bl_itoa(&bp, ival, 8);
                break;

            case 'X':
            case 'x':
                *bp++ = '0';
                *bp++ = 'x';
                uxval = va_arg(ap, uint32_t);
                bl_itoa(&bp, uxval, 16);
                break;

            case 'U':
            case 'u':
                uival = va_arg(ap, unsigned int);
                *bp++ = '0';
                *bp++ = 'x';
                bp_old = bp;
                uival1 = uival >> 16;
                uival2 = uival & 0x0000ffff;
                bl_itoa(&bp, uival1, 16);
                i = (unsigned int)bp - (unsigned int)bp_old;
                if (i < 4) {
                    for (j = 3; j > (3 - i); j--) {
                        bp_old[j] = bp_old[j - (3 - i) - 1];
                    }
                    for (j = 0; j <= (3 - i); j++) {
                        bp_old[j] = '0';
                    }
                }
                bp = bp_old + 4;
                bp_old = bp;
                bl_itoa(&bp, uival2, 16);
                i = (unsigned int)bp - (unsigned int)bp_old;
                if (i < 4) {
                    for (j = 3; j > (3 - i); j--) {
                        bp_old[j] = bp_old[j - (3 - i) - 1];
                    }
                    for (j = 0; j <= (3 - i); j++) {
                        bp_old[j] = '0';
                    }
                }
                bp = bp_old + 4;
                break;

            case 'P':
            case 'p':
                ival = va_arg(ap, int32_t);
                *bp++ = '0';
                *bp++ = 'x';
                bl_itoa(&bp, ival, 16);
                break;

            case 'c':
            case 'C':
                cval = va_arg(ap, int32_t);
                *bp++ = cval;
                break;

            case 'f':
            case 'F':
                dval = va_arg(ap, int64_t);
                if (dval < 0) {
                    *bp++ = '-';
                    dval = -dval;
                }
                if (dval >= 1.0) {
                    bl_itoa(&bp, (int32_t)dval, 10);
                } else {
                    *bp++ = '0';
                }
                *bp++ = '.';
                fract = (int32_t)((dval - (int64_t)(int32_t)dval) * (int64_t)(HM_MAX_FRACT));
                bl_itof(&bp, fract);
                break;

            case 's':
            case 'S':
                for (sval = va_arg(ap, char *) ; *sval ; sval++) {
                    *bp++ = *sval;
                }
                break;
        }
    }

    *bp = 0;
}

