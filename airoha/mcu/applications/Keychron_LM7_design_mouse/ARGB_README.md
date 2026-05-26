# Airoha AB162x ARGB LED 控制指南

## 概述

Airoha AB162x 芯片内置了专用的 ARGB (Addressable RGB) LED 控制器，支持单线控制多个 LED，支持 8 位 PWM 调光（256 级），工作在 32kHz 时钟频率下。

## 硬件连接

- **控制引脚**: GPIO34 (已配置为 ARGB 模式)
- **LED 条供电**: 5V (建议使用外部电源)
- **通信协议**: 单线协议，类似于 WS2812

## 配置步骤

### 1. 启用 ARGB 功能

在 `prj.conf` 中添加：
```
CONFIG_AIR_ARGB_ENABLE=y
```

### 2. 设备树配置

在 overlay 文件中已配置：
```dts
&argb {
    argb_channel = <34>;        /* GPIO34 */
    one_h_value = <800>;        /* 逻辑 1 高电平时间: 800ns */
    one_l_value = <450>;        /* 逻辑 1 低电平时间: 450ns */
    zero_h_value = <400>;       /* 逻辑 0 高电平时间: 400ns */
    zero_l_value = <850>;       /* 逻辑 0 低电平时间: 850ns */
    reset_value = <50000>;      /* 复位时间: 50us */
    pat_cnt = <16>;             /* LED 数量: 16 个 */
    bit_nonrev = <1>;           /* MSB 先发 */
    ed_big = <1>;               /* 大端模式 */
    nonalign = <1>;             /* 非对齐模式 */
    status = "okay";
};
```

## API 使用示例

### 初始化
```c
#include "bsp_argb.h"

// 在 main() 中初始化
bsp_argb_status_t status = bsp_argb_enable();
if (status == BSP_ARGB_STATUS_OK) {
    // 初始化成功
}
```

### 设置单色
```c
// 设置红色
argb_set_color(255, 0, 0);

// 设置绿色
argb_set_color(0, 255, 0);

// 设置蓝色
argb_set_color(0, 0, 255);

// 设置白色
argb_set_color(255, 255, 255);
```

### 运行演示模式
```c
// 循环演示不同颜色
argb_led_demo();
```

### 高级控制
```c
argb_style_config_t config;

// 配置彩虹模式
config.repeat = 0;  // 连续重复
config.type = ARGB_TYPE_RGB;
uint8_t rainbow_data[48];  // 16 个 LED * 3 色
// 填充彩虹数据...
config.argb_data = rainbow_data;

bsp_argb_realtime_config(&config);
bsp_argb_realtime_start();
```

## 时序参数说明

- **逻辑 1**: 高电平 800ns + 低电平 450ns
- **逻辑 0**: 高电平 400ns + 低电平 850ns
- **复位**: 至少 50us 低电平
- **数据格式**: GRB (Green-Red-Blue)，每个颜色 8 位

## 功耗优化

- 使用 32kHz 时钟，适合低功耗应用
- 支持中断控制，可在需要时唤醒
- DMA 传输减少 CPU 占用

## 注意事项

1. 确保 LED 条有足够的电源供应
2. 控制线需要合适的上下拉电阻
3. 长 LED 条可能需要信号放大器
4. 调试时注意时序参数的准确性

## 故障排除

- 检查 GPIO34 是否正确配置为 ARGB 模式
- 验证电源电压和电流是否足够
- 使用示波器检查信号时序
- 查看日志中的错误码进行调试</content>
<parameter name="filePath">/home/leo/IoT_SDK_for_BT_Data_V1.1.1.AB162x_HID_exe_V1.1.1.AB162x_HID/ARGB_README.md