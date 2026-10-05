#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint32_t tick;

void TasksInit(void);

#ifdef __cplusplus
}
#endif

#endif
//咕咕嘎嘎
