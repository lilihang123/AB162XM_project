/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */
/* MediaTek restricted information */

#include "bt_linknode.h"

/*               |front|                                 |back|
 *                  /                                      /
 * [Link_HEAD]-->[node1]-->[node2]-->[node3]-->[node4]-->[node5]-->NULL
 *    [des]
 * Insert [src] to [des] linked list.
 * #BT_NODE_FRONT : Insert [src] to front of [des] linked list.
 * #BT_NODE_BACK  : Insert [src] to back of [des linked list.
 */
void bt_linknode_insert_node(bt_linknode_t *des, bt_linknode_t *src, bt_linknode_position pos)
{
    bt_linknode_t *tmp = des;
    if (pos == BT_NODE_BACK) {
        while (tmp->front != NULL) {
            tmp = tmp->front;
        }
    }
    src->front = tmp->front;
    tmp->front = src;
}

/*               |front|                                 |back|
 *                  /                                      /
 * [Link_HEAD]-->[node1]-->[node2]-->[node3]-->[node4]-->[node5]-->NULL
 *    [src]
 * #BT_NODE_FRONT : Remove [node1] from [src] linked list.
 * #BT_NODE_BACK  : Remove [node5] from [src] linked list.
 * [f_node]-->[ff_node]
 */
bt_linknode_t *bt_linknode_remove_node(bt_linknode_t *src, bt_linknode_position pos)
{
    bt_linknode_t *f_node = src;
    bt_linknode_t *ff_node = src->front; /* #ff_node is removing node. */
    if (ff_node != NULL) {
        if (pos == BT_NODE_BACK) {
            while (ff_node->front != NULL) {
                f_node = ff_node;
                ff_node = ff_node->front;
            }
        }
        f_node->front = ff_node->front;
        ff_node->front = NULL;
    }
    return ff_node;
}


bool bt_linknode_cmp_current(const bt_linknode_t *node, const void *data)
{
    return (node == (const bt_linknode_t *)data);
}

bool bt_linknode_cmp_backward(const bt_linknode_t *node, const void *data)
{
    return (node->front == (const bt_linknode_t *)data);
}

bt_linknode_t *bt_linknode_travel_node(bt_linknode_t *head, bt_linknode_cmp_t func, const void *data)
{
    bt_linknode_t *tmp;
    tmp = head;
    while (tmp) {
        if (false != func(tmp, data)) {
            return tmp;
        }
        tmp = tmp->front;
        if (tmp == head) {
            return NULL;
        }
    }
    return NULL;
}
bt_linknode_t *bt_linknode_travel_and_remove_node(bt_linknode_t *head, bt_linknode_cmp_t func, const void* data)
{
    bt_linknode_t *f_node = head;
    bt_linknode_t *ff_node = head->front;
    while(1){
        if(false != func(f_node, data)){
            f_node->front = ff_node->front;
            ff_node->front = NULL;
            return ff_node;
        }
        if(ff_node != NULL){
            f_node = ff_node;
            ff_node = ff_node->front;
        }
        else{
            return NULL;
        }
        if(f_node == head){
            return NULL;
        }
    }
    return NULL;
}

