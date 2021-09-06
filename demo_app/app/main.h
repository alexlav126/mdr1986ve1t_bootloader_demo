#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdint.h>
#include <stdbool.h>
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_can.h"

uint32_t GetSysTime_ms(void);
void SysTick_1ms(void);

#endif // __MAIN_H__
