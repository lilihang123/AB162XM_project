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

#include "bt_linknode.h"
#include <zephyr/kernel.h>


#include <zephyr/logging/log.h>
#define thisMODULE bt_node
LOG_MODULE_REGISTER(thisMODULE);


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
    if (NULL == ff_node) {
        return NULL;
    }
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

