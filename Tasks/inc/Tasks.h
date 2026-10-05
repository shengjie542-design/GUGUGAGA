/**
 * @file    Tasks.h
 * @brief   电控第一次作业 - 业务代码统一入口 (Tasks 模块对外接口)
 *
 * 约定:
 *   - 业务代码只写在 Tasks/src 里, 头文件放 Tasks/inc;
 *   - main.c 只在 USER CODE 中包含本头文件并调用 TasksInit(), while(1) 保持为空;
 *   - 全工程唯一的定时器更新回调 HAL_TIM_PeriodElapsedCallback 放在 Tasks.cpp 中。
 */
#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 全局 tick: 定时器更新中断里每 1ms 自增 1。
 * 第2题(喂狗) 持续增长; 第3题(不喂狗) 涨到约 2000 后被看门狗复位归零。
 * 必须是全局 volatile uint32_t, 供 Ozone 监视。 */
extern volatile uint32_t tick;

/* Tasks 初始化: 在 main.c 中所有 MX_XXX_Init() 执行完后调用一次。
 * 完成: 第1题 GPIO 点灯 + 第2题启动 1ms 定时器中断 (看门狗由 CubeMX 的 MX_IWDG_Init 启动)。 */
void TasksInit(void);

#ifdef __cplusplus
}
#endif

#endif /* TASKS_H */
