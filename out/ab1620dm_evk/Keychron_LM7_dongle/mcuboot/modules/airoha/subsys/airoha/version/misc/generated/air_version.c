#include "version.h"

#include "air_chip.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/util_macro.h>

#define AIROHA_SDK_VERSION "IoT_SDK_for_BT_Data_V0.0.1.AB1620_Alpha"

#if defined(CONFIG_FIRMWARE_VERSION_STR)
    #define AIROHA_FIRMWARE_VERSION CONFIG_FIRMWARE_VERSION_STR
#else
    #define AIROHA_FIRMWARE_VERSION ""
#endif

const char build_date_time_str[] = "BuildTime: 2026/05/29 07:21:49 UTC";
const char sw_verno_str[] = "Version: " AIROHA_FIRMWARE_VERSION;

#ifdef CONFIG_AIR_LOGGING_ENABLE
/* save the same information to logging binary */
#include "memory_attribute.h"
ATTR_LOG_TIMESTAMP log_bin_build_date_time_str[] = "BuildTime: 2026/05/29 07:21:49 UTC";
ATTR_LOG_VERSION log_bin_sw_verno_str[] = "Version: " AIROHA_FIRMWARE_VERSION;
extern void airoha_printk(const char *fmt, uint32_t arg_cnt, ...);
#endif

#if KERNELVERSION == 0x3030000
static int build_info_print(const struct device *dev)
{
    ARG_UNUSED(dev);
#elif KERNELVERSION >= 0x3070000
static int build_info_print(void)
{
#else
#error "Unkown supported kernel version"
#endif
#ifdef CONFIG_AIR_LOGGING_ENABLE
    airoha_printk(log_bin_sw_verno_str, 0);
    airoha_printk(log_bin_build_date_time_str, 0);
    print_module_log(NULL, NULL, 0, PRINT_LEVEL_INFO, sw_verno_str);
    print_module_log(NULL, NULL, 0, PRINT_LEVEL_INFO, build_date_time_str);
    printk("addr of build_date_time_str: 0x%08X\r\n", (unsigned int)build_date_time_str);
    printk("addr of sw_verno_str: 0x%08X\r\n", (unsigned int)sw_verno_str);
#else
    printk(sw_verno_str);
    printk(build_date_time_str);
#endif
    return 0;
}

SYS_INIT(build_info_print, CONFIG_BUILD_INFO_INIT_LEVEL, CONFIG_BUILD_INFO_INIT_PRIORITY);
