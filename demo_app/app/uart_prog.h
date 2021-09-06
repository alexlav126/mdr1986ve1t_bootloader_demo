#ifndef __UART_DEBUG_H__
#define __UART_DEBUG_H__

#include <stdint.h>

void UartProg_InterruptRxByte(void);
void UartProg_InterruptTxByte(void);
void UartProg_Handler(void);
void UartProg_Systick_1ms(void);

#endif // __UART_DEBUG_H__
