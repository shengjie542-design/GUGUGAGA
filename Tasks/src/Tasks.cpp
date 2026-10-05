#include "Tasks.h"
#include "main.h"
#include <cstdint>
/* htim2/hiwdg 定义在 main.c，这里声明 */
extern "C" {
extern TIM_HandleTypeDef  htim2;   /* 1ms 定时器句柄 */
extern IWDG_HandleTypeDef hiwdg;   /* 看门狗句柄 */
}


/* 1 = 第2题(喂) 0 = 第3题(不喂)*/
#define FEED_WATCHDOG_IN_TIMER_CALLBACK   1

/* 第1题*/
#define LED_GPIO_Port   GPIOC
#define LED_Pin         GPIO_PIN_13
#define LED_ON_LEVEL    GPIO_PIN_RESET

/* APB1 分频 !=1 时, 定时器时钟 = 2×36 = 72MHz
* PSC = 71, APR = 999 -> (71+1)*(999+1)/72MHz = 1ms */
#define TICK_TIMER_HANDLE     htim2
#define TICK_TIMER_INSTANCE   TIM2

volatile uint32_t tick = 0;

/* Tasks 初始化 */
extern "C" void TasksInit(void)
{
    /* 第1题 GPIO */
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LED_ON_LEVEL);

    /* 第2题 定时器 */
    HAL_TIM_Base_Start_IT(&TICK_TIMER_HANDLE);
}

/* 定时器更新回调 */
extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TICK_TIMER_INSTANCE) {
        tick++;

#if (FEED_WATCHDOG_IN_TIMER_CALLBACK == 1)
        /* 第2题喂狗 */
        HAL_IWDG_Refresh(&hiwdg);
#endif
    }
}
//咕咕嘎嘎