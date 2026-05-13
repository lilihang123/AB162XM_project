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

#ifndef _SYSLOG_H_
#define _SYSLOG_H_

#if defined(AIR_LOGGING_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdarg.h"

/* Public define -------------------------------------------------------------*/
#define ATTR_LOG_STRING                                 __attribute__ ((__section__(".log_string"))) static const char
#define ATTR_LOG_STRING_LIB                             __attribute__ ((__section__(".log_string"))) const char
#define ATTR_LOG_FILTER(module)                         __attribute__ ((__section__(".log_filter." #module)))
#define ATTR_LOG_FILTER_MIRROR(module)                  __attribute__ ((__section__(".log_filter_mirror." #module))) __attribute__((used)) const
#define ATTR_LOG_VERSION                                __attribute__ ((__section__(".log_version"))) __attribute__((used)) static const char
#define ATTR_LOG_TIMESTAMP                              __attribute__ ((__section__(".log_timestamp"))) __attribute__((used)) static const char

/* Public typedef ------------------------------------------------------------*/
typedef enum {
    DEBUG_LOG_ON,   /**<  log on */
    DEBUG_LOG_OFF   /**<  log off */
} log_switch_t;

/** @brief Print level definition. */
typedef enum {
    PRINT_LEVEL_DEBUG,   /**<  log level with debugging */
    PRINT_LEVEL_INFO,    /**<  log level with info */
    PRINT_LEVEL_WARNING, /**<  log level with a warning */
    PRINT_LEVEL_ERROR    /**<  log level with an error */
} print_level_t;


typedef enum {
    LOG_TYPE_INTERNAL_COMMAND = 0x01,     /**<  Internal data used to communicated with the PC logging tool. */
    LOG_TYPE_INTERNAL_LOG_END = 0x0f,     /**<  The maximum number of log types used for internal usage. */

    LOG_TYPE_TEXTURE_LOG = 0x10,          /**<  Transmit log with its string content. */
    LOG_TYPE_MSG_ID_LOG = 0x11,           /**<  Transmit log with the address only. */
    LOG_TYPE_EXCEPTION_STRING_LOG = 0x12, /**<  Exception string log. */
    LOG_TYPE_EXCEPTION_BINARY_LOG = 0x13, /**<  Exception binary log. */
    LOG_TYPE_EXCEPTION_MSGID_LOG  = 0x1A, /**<  Exception msgid  log. */
    LOG_TYPE_COMMON_LOG_END = 0x2f,       /**<  The maximum number of log types used for internal and common logs. */

    LOG_TYPE_HCI_DATA = 0x30,             /**<  HCI specific log data. */
    LOG_TYPE_AUDIO_DATA = 0x31,           /**<  Audio specific log data. */
    LOG_TYPE_BT_LMP_LLCP_DATA = 0x32,     /**<  BT LMP and LLCP log data */
    LOG_TYPE_MODULE_LOG_DATA = 0x33,      /**<  Auto Sanity log data     */
    LOG_TYPE_AUDIO_V2_DATA = 0x34,        /**<  Audio V2 specific log data. */
    LOG_TYPE_SYSTEM_INFO = 0x35,          /**<  system information log data. */
    LOG_TYPE_SPECIAL_LOG_END = 0x3f,      /**<  The maximum number of log types used for customized data. */
} log_type_t;

typedef void (*f_print_t)(void *handle, const char *func, int line, print_level_t level, const char *message, ...);
typedef void (*f_dump_buffer_t)(void *handle, const char *func, int line, print_level_t level, const void *data, int length, const char *message, ...);
typedef void (*f_msg_id_t)(void *handle, print_level_t level, const char *message, uint32_t arg_cnt, ...);
typedef uint32_t (*f_tlv_dump_t)(void *handle, print_level_t level, log_type_t type, const void **p_data, uint32_t *p_length);

typedef struct {
    const char *module_name;
    uint32_t log_switch;
    uint32_t print_level;
    f_print_t print_handle;
    f_dump_buffer_t dump_handle;
    f_tlv_dump_t tlv_dump_handle;
    f_msg_id_t msg_id_handle;
} log_control_block_t;

/* Public macro --------------------------------------------------------------*/
#define __COUNT_ARGS(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_n,X...) _n
#define COUNT_ARGS(X...) __COUNT_ARGS(, ##X,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

/** @brief This macro defines an instance of the log control module.
 * @param[in] module is the name of the log control module.
 * @param[in] level is the log level of the log control module.
 * @par Example
 * @code
 *      log_create_module(common, PRINT_LEVEL_INFO);
 * @endcode
*/
#define log_create_module(module, level) \
ATTR_LOG_FILTER(module) log_control_block_t log_control_block_##module = \
{ \
    #module, \
    (DEBUG_LOG_ON), \
    (level), \
    NULL, \
    NULL, \
    NULL, \
    print_module_msgid_log \
}; \
ATTR_LOG_FILTER_MIRROR(module) char log_control_block_mirror_##module[] = #module

#define LOG_MSGID_E(module, message, arg_cnt, ...) \
do { \
    extern log_control_block_t log_control_block_##module; \
    ATTR_LOG_STRING msg_id_string[] = "[M:" #module " C:info F: L: ]: " message; \
    print_module_msgid_log(&log_control_block_##module, \
                            (PRINT_LEVEL_ERROR), \
                            (msg_id_string), \
                            (arg_cnt),  \
                            ##__VA_ARGS__); \
} while (0)

#define LOG_MSGID_W(module, message, arg_cnt, ...) \
do { \
    extern log_control_block_t log_control_block_##module; \
    ATTR_LOG_STRING msg_id_string[] = "[M:" #module " C:info F: L: ]: " message; \
    print_module_msgid_log(&log_control_block_##module, \
                            (PRINT_LEVEL_WARNING), \
                            (msg_id_string), \
                            (arg_cnt),  \
                            ##__VA_ARGS__); \
} while (0)

#define LOG_MSGID_I(module, message, arg_cnt, ...) \
do { \
    extern log_control_block_t log_control_block_##module; \
    ATTR_LOG_STRING msg_id_string[] = "[M:" #module " C:info F: L: ]: " message; \
    print_module_msgid_log(&log_control_block_##module, \
                            (PRINT_LEVEL_INFO), \
                            (msg_id_string), \
                            (arg_cnt),  \
                            ##__VA_ARGS__); \
} while (0)

#define LOG_MSGID_D(module, message, arg_cnt, ...) \
do { \
    extern log_control_block_t log_control_block_##module; \
    ATTR_LOG_STRING msg_id_string[] = "[M:" #module " C:info F: L: ]: " message; \
    print_module_msgid_log(&log_control_block_##module, \
                            (PRINT_LEVEL_DEBUG), \
                            (msg_id_string), \
                            (arg_cnt),  \
                            ##__VA_ARGS__); \
} while (0)

/** @brief This macro calls the SYSLOG internal function to print the user's customized data with a debugging level.
 *         Therefore, the user's data cannot be sent if the module's log level is higher.
 *         This data must be managed with a specific method on the PC side.
 *         Therefore, the type must be decided here so that the PC logging tool can split them for specific post processing.
 *         The user must check the return value to see whether all data is sent.
 *         If not, the user must try to send the remaining data by calling this API again.
 * @param[in] module is the name of the log control module.
 * @param[in] type is a uniform value of #log_type_t used to tell the difference between the user's different logs and data.
 * @param[in] p_data is the address of the data buffer array. It must be end with NULL.
 * @param[in] p_len is the array of data buffer length.
 * @param[out] ret_len is the size actually sent.
 * @note   The user must check the return value to see whether all data is sent.
 * @par Example
 * @code
 *      uint8_t *audio_buffer_array[] = {audio_buffer_1, audio_buffer_2, NULL};
 *      uint32_t audio_buffer_length_array[] = {0x10, 0x200};
 *      LOG_TLVDUMP_D(common, LOG_TYPE_HCI_DATA, audio_buffer_array, audio_buffer_length_array, ret_len);
 * @endcode
 * @sa #LOG_TLVDUMP_I()/#LOG_TLVDUMP_W()/#LOG_TLVDUMP_E()
 */
#define LOG_TLVDUMP_D(module, type, p_data, p_len, ret_len) \
do { \
    extern log_control_block_t log_control_block_##module; \
    ret_len = dump_module_tlv_buffer(&log_control_block_##module, \
                                            PRINT_LEVEL_DEBUG, \
                                            (type), \
                                            (const void **)(p_data), \
                                            (p_len)); \
} while (0)

/** @brief This macro calls the SYSLOG internal function to print the user's customized data with an information level.
 *         Therefore, the user's data cannot be sent if the module's log level is higher.
 *         This data must be managed with a specific method on the PC side.
 *         Therefore, the type must be set here so that the PC logging tool can split it for specific post processing.
 *         The user must check the return value to see whether all data is sent.
 *         If not, the user must call this API again to send the remaining data.
 * @param[in] module is the name of the log control module.
 * @param[in] type is a uniform value of #log_type_t used to tell the difference between the user's different logs and data.
 * @param[in] p_data is the address of the data buffer array. It must be end with NULL.
 * @param[in] p_len is the array of data buffer length.
 * @param[out] ret_len is the size actually sent.
 * @note   The user must check the return value to see whether all data is sent.
 * @par Example
 * @code
 *      uint8_t *audio_buffer_array[] = {audio_buffer_1, audio_buffer_2, NULL};
 *      uint32_t audio_buffer_length_array[] = {0x10, 0x200};
 *      LOG_TLVDUMP_I(common, LOG_TYPE_HCI_DATA, audio_buffer_array, audio_buffer_length_array, ret_len);
 * @endcode
 * @sa #LOG_TLVDUMP_D()/#LOG_TLVDUMP_W()/#LOG_TLVDUMP_E()
 */
#define LOG_TLVDUMP_I(module, type, p_data, p_len, ret_len) \
do { \
    extern log_control_block_t log_control_block_##module; \
    ret_len = dump_module_tlv_buffer(&log_control_block_##module, \
                                            PRINT_LEVEL_INFO, \
                                            (type), \
                                            (const void **)(p_data), \
                                            (p_len)); \
} while (0)

/** @brief This macro calls the SYSLOG internal function to print the user's customized data with a warning level.
 *         Therefore, the user's log cannot be sent if the module's log level setting is higher.
 *         This data must be managed using a specific method on the PC side.
 *         Therefore, the type must be set here so that the PC logging tool can split it for specific post proccessing.
 *         The user must check the return value to see whether all data is sent.
 *         If not, the user must call this API again to send the remaining data.
 * @param[in] module is the name of the log control module.
 * @param[in] type is a uniform value of #log_type_t used to tell the difference between the user's different logs and the data.
 * @param[in] p_data is the address of the data buffer array. It must be end with NULL.
 * @param[in] p_len is the array of data buffer length.
 * @param[out] ret_len is the size actually be sent out.
 * @note   The user must check the return value to see whether all data is sent.
 * @return
 *         The size of data that is actually sent.
 * @par Example
 * @code
 *      uint8_t *audio_buffer_array[] = {audio_buffer_1, audio_buffer_2, NULL};
 *      uint32_t audio_buffer_length_array[] = {0x10, 0x200};
 *      LOG_TLVDUMP_W(common, LOG_TYPE_HCI_DATA, audio_buffer_array, audio_buffer_length_array, ret_len);
 * @endcode
 * @sa #LOG_TLVDUMP_D()/#LOG_TLVDUMP_I()/#LOG_TLVDUMP_E()
 */
#define LOG_TLVDUMP_W(module, type, p_data, p_len, ret_len) \
do { \
    extern log_control_block_t log_control_block_##module; \
    ret_len = dump_module_tlv_buffer(&log_control_block_##module, \
                                            PRINT_LEVEL_WARNING, \
                                            (type), \
                                            (const void **)(p_data), \
                                            (p_len)); \
} while (0)

/** @brief This macro calls the SYSLOG internal function to print the user's customized data with an error level.
 *         Therefore, the user's log cannot be sent if the module's log level setting is higher.
 *         This data must be managed with a specific method on the PC side.
 *         Therefore, the type must be set here so that the PC logging tool can split it for specific post processing.
 *         The user must check the return value to see whether all data is sent.
 *         If not, the user must call this API again to send the remaining data.
 * @param[in] module is the name of the log control module.
 * @param[in] type is a uniform value of #log_type_t used to tell the difference between the user's different logs and data.
 * @param[in] p_data is the address of the data buffer array. It must be end with NULL.
 * @param[in] p_len is the array of data buffer length.
 * @param[out] ret_len is the size actually sent.
 * @note   The user must check the return value to see whether all data is sent.
 * @par Example
 * @code
 *      uint8_t *audio_buffer_array[] = {audio_buffer_1, audio_buffer_2, NULL};
 *      uint32_t audio_buffer_length_array[] = {0x10, 0x200};
 *      LOG_TLVDUMP_E(common, LOG_TYPE_HCI_DATA, audio_buffer_array, audio_buffer_length_array, ret_len);
 * @endcode
 * @sa #LOG_TLVDUMP_D()/#LOG_TLVDUMP_I()/#LOG_TLVDUMP_W()
 */
#define LOG_TLVDUMP_E(module, type, p_data, p_len, ret_len) \
do { \
    extern log_control_block_t log_control_block_##module; \
    ret_len = dump_module_tlv_buffer(&log_control_block_##module, \
                                            PRINT_LEVEL_ERROR, \
                                            (type), \
                                            (const void **)(p_data), \
                                            (p_len)); \
} while (0)

/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern void print_module_msgid_log(void *handle,
                            print_level_t level,
                            const char *message,
                            uint32_t arg_cnt, ...);

extern uint32_t dump_module_tlv_buffer(void *handle,
                                print_level_t level,
                                log_type_t type,
                                const void **p_data,
                                uint32_t *p_length);

extern int log_init(void);

#else

/* ref zephyr/include/zephyr/logging/log.h, define empty macro for projects without AIR_LOGGING_ENABLE */
#define log_create_module(module, level)
#define LOG_MSGID_E(module, message, arg_cnt, ...)
#define LOG_MSGID_W(module, message, arg_cnt, ...)
#define LOG_MSGID_I(module, message, arg_cnt, ...)
#define LOG_MSGID_D(module, message, arg_cnt, ...)
#define LOG_TLVDUMP_D(module, type, p_data, p_len, ret_len)
#define LOG_TLVDUMP_I(module, type, p_data, p_len, ret_len)
#define LOG_TLVDUMP_W(module, type, p_data, p_len, ret_len)
#define LOG_TLVDUMP_E(module, type, p_data, p_len, ret_len)

#endif /* AIR_LOGGING_ENABLE */

#endif /* _SYSLOG_H_ */
