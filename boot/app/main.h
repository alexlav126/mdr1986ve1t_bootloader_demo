#ifndef __MAIN_H__
#define __MAIN_H__
#include <stdint.h>
#include <stdbool.h>
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_can.h"

extern volatile bool is_main_app;

typedef void (*func_ptr_t)(void);
typedef struct
{
    uint32_t *__StackTop;
    func_ptr_t Reset_Handler;
    func_ptr_t NMI_Handler;
    func_ptr_t HardFault_Handler;
    func_ptr_t Reserved_0;
    func_ptr_t Reserved_1;
    func_ptr_t Reserved_2;
    func_ptr_t Reserved_3;
    func_ptr_t Reserved_4;
    func_ptr_t Reserved_5;
    func_ptr_t Reserved_6;
    func_ptr_t SVC_Handler;
    func_ptr_t Reserved_7;
    func_ptr_t Reserved_8;
    func_ptr_t PendSV_Handler;
    func_ptr_t SysTick_Handler;

    // External interrupts
    func_ptr_t MIL_STD_1553B2_IRQHandler;
    func_ptr_t MIL_STD_1553B1_IRQHandler;
    func_ptr_t USB_IRQHandler;
    func_ptr_t CAN1_IRQHandler;
    func_ptr_t CAN2_IRQHandler;
    func_ptr_t DMA_IRQHandler;
    func_ptr_t UART1_IRQHandler;
    func_ptr_t UART2_IRQHandler;
    func_ptr_t SSP1_IRQHandler;
    func_ptr_t BUSY_IRQHandler;
    func_ptr_t ARINC429R_IRQHandler;
    func_ptr_t POWER_IRQHandler;
    func_ptr_t WWDG_IRQHandler;
    func_ptr_t Timer4_IRQHandler;
    func_ptr_t Timer1_IRQHandler;
    func_ptr_t Timer2_IRQHandler;
    func_ptr_t Timer3_IRQHandler;
    func_ptr_t ADC_IRQHandler;
    func_ptr_t ETHERNET_IRQHandler;
    func_ptr_t SSP3_IRQHandler;
    func_ptr_t SSP2_IRQHandler;
    func_ptr_t ARINC429T1_IRQHandler;
    func_ptr_t ARINC429T2_IRQHandler;
    func_ptr_t ARINC429T3_IRQHandler;
    func_ptr_t ARINC429T4_IRQHandler;
    func_ptr_t IRQ_Reserve_25;
    func_ptr_t IRQ_Reserve_26;
    func_ptr_t BKP_IRQHandler;
    func_ptr_t EXT_INT1_IRQHandler;
    func_ptr_t EXT_INT2_IRQHandler;
    func_ptr_t EXT_INT3_IRQHandler;
    func_ptr_t EXT_INT4_IRQHandler;
} v_table_t;

#define FLASH_MAIN_APP_START_PAGE 2
#define FLASH_MAIN_APP_LAST_PAGE 14
#define MAIN_APP_FLASH_ADDR (FLASH_MAIN_APP_START_PAGE * EEPROM_PAGE_SIZE)
#define MAIN_APP_VTABLE_P ((v_table_t *)MAIN_APP_FLASH_ADDR)

#endif // __MAIN_H__
