# 电控第一次作业

电控组第一次作业的 STM32 工程：**GPIO 点灯 / 1ms 定时器 / 独立看门狗** 三题，芯片 **STM32F103C8T6**。

## 题目

| 题 | 内容 | 关键现象 |
|---|---|---|
| 1 | GPIO | 板载灯 PC13 低电平点亮 |
| 2 | 定时器 | TIM2 产生 1ms 更新中断，全局 `tick` 每秒 +1000，回调里喂狗 |
| 3 | 看门狗 | 去掉喂狗，IWDG 约 2s 超时复位，`tick` 涨到约 2000 后归零 |

## 环境

- STM32CubeMX 6.18，Toolchain/IDE = CMake，Generate Under Root
- VS Code + CMake（构建类型 Debug）
- SEGGER Ozone（打开 `build/electro_hw1.elf`）

## 目录结构

- `Core/` — CubeMX 生成的初始化代码
- `Drivers/` — STM32 HAL 库与 CMSIS
- `Tasks/inc`、`Tasks/src` — 业务代码
- `CMakeLists.txt` — 发放的模板

## 关键参数

- 主频 72 MHz（HSE 8 MHz × 9）
- TIM2：PSC=71、ARR=999 → `(71+1)×(999+1)/72MHz = 1ms`（定时器时钟 72 MHz，APB1 分频≠1 时翻倍）
- IWDG：64 分频、Reload=1249 → `(1249+1)×64/40000 = 2s`（LSI ≈ 40 kHz）

## 构建

1. 打开工程目录
2. VS Code：`CMake: Delete Cache and Reconfigure` → `Build`
3. 产物：`build/electro_hw1.elf`（`.hex` / `.bin` 由 post-build 自动生成）

## 说明

业务代码集中在 `Tasks/src/Tasks.cpp`（约 106 行），第 2 题 / 第 3 题通过宏 `FEED_WATCHDOG_IN_TIMER_CALLBACK` 切换（`1` = 喂狗，`0` = 不喂狗），分两次编译下载。
