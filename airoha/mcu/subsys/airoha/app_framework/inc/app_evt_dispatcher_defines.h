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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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
 

#ifndef __APP_EVT_DISPATCHER_DEFINE_H__
#define __APP_EVT_DISPATCHER_DEFINE_H__


#if defined(CONFIG_AIR_APP_FRAMEWORK)
struct af_evt_header {
    void *fifo_reserved;
    const struct af_evt_type  *cb_list;
};

struct af_evt_dispatch_cb {
    bool (*cb)(const struct af_evt_header *evt_header); 
};

struct af_evt_type {
    const struct af_evt_dispatch_cb *dummy_00; 
    const struct af_evt_dispatch_cb *dummy_99;
    const char *event_name;  // debug log 
};

void app_evt_apply(struct af_evt_header *evt_header);

#if defined(CONFIG_AIR_APP_FRAMEWORK_DELAYABLE)
struct delayable_work_item{
    struct k_work_delayable dwork;
    struct af_evt_header *evt_header;
};

struct delayable_work_item * app_delayable_evt_apply(struct af_evt_header *evt_header, k_timeout_t delay);
int app_delayable_evt_cancel(struct delayable_work_item * dwork);
#endif


#define APP_DISPATCH_EVT_CB_DEFINE_DUMMY_00           _0_
#define APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_1         _1_
#define APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_2         _2_
#define APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_3         _3_
#define APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_4         _4_
#define APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_5         _5_
#define APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_6         _6_
#define APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_7         _7_
#define APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_8         _8_
#define APP_DISPATCH_EVT_CB_DEFINE_DUMMY_99           _9_


#define _DO_COMBINE_3(x, y, z) x ## y ## z
#define _COMBINE_3(x, y, z) _DO_COMBINE_3(x, y, z)


#define _DO_COMBINE_4(w, x, y, z) w ## x ## y ## z
#define _COMBINE_4(w, x, y, z) _DO_COMBINE_4(w, x, y, z)

#define SORT_KEY           _app_evt_dispatcher_


#define _APP_EVT_DECLARE(evt_name)                                                                                                              \
    const struct {} _COMBINE_4(SORT_KEY, evt_name, APP_DISPATCH_EVT_CB_DEFINE_DUMMY_00, _label)                                                 \
    __used __aligned(__alignof(struct af_evt_dispatch_cb))                                                                                      \
    __attribute__((__section__(STRINGIFY(_COMBINE_3(SORT_KEY, evt_name, APP_DISPATCH_EVT_CB_DEFINE_DUMMY_00))))) = {};                          \
                                                                                                                                                \
    const struct {} _COMBINE_4(SORT_KEY, evt_name, APP_DISPATCH_EVT_CB_DEFINE_DUMMY_99, _label)                                                 \
    __used __aligned(__alignof(struct af_evt_dispatch_cb))                                                                                      \
    __attribute__((__section__(STRINGIFY(_COMBINE_3(SORT_KEY, evt_name, APP_DISPATCH_EVT_CB_DEFINE_DUMMY_99))))) = {};                          \
                                                                                                                                                \
    STRUCT_SECTION_ITERABLE(af_evt_type, _CONCAT(__af_evt_type_, evt_name)) = {                                                                 \
        .dummy_00 = ((const struct af_evt_dispatch_cb *) &_COMBINE_4(SORT_KEY, evt_name, APP_DISPATCH_EVT_CB_DEFINE_DUMMY_00, _label)),         \
        .dummy_99 = ((const struct af_evt_dispatch_cb *) &_COMBINE_4(SORT_KEY, evt_name, APP_DISPATCH_EVT_CB_DEFINE_DUMMY_99, _label)),         \
        .event_name   = STRINGIFY(evt_name)                                                                                                     \
    }


#define _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, prio) \
    __used __aligned(__alignof(struct af_evt_dispatch_cb))\
    __attribute__((__section__(STRINGIFY(_COMBINE_3(SORT_KEY, evt_name, _COMBINE_3(prio, _by_, mod_name))))))\
    const struct af_evt_dispatch_cb _COMBINE_4(_app_evt_dispatch_cb_, evt_name, _by_, mod_name ) = {\
        .cb = (hdl_fun),\
    }

#define _APP_EVT_EXTERN(evt_name)                                                                   \
    extern Z_DECL_ALIGN(struct af_evt_type) _CONCAT(__af_evt_type_, evt_name);                      \
                                                                                                    \
    static inline struct evt_name *_DO_COMBINE_3(create_, evt_name, _ex)(int extend_len)            \
    {                                                                                               \
        struct evt_name *event =  (struct evt_name *)k_malloc(sizeof(*event)+extend_len);           \
        if (event) {                                                                                \
            event->header.cb_list = &_CONCAT(__af_evt_type_, evt_name);                            \
        }                                                                                           \
        return event;                                                                               \
    }                                                                                               \
                                                                                                    \
    static inline struct evt_name *_CONCAT(create_, evt_name)(void)                                 \
    {                                                                                               \
        return _DO_COMBINE_3(create_, evt_name, _ex)(0);                                            \
    }                                                                                               



#endif //CONFIG_AIR_APP_FRAMEWORK
#endif //__APP_EVT_DISPATCHER_DEFINE_H__
