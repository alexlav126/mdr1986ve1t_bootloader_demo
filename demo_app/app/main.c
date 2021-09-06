#include "main.h"
#include "inits.h"
#include "gpio_def.h"
#include "uart_prog.h"
#include <string.h>
#include "MDR32F9Qx_eeprom.h"

volatile bool __attribute__((section(".boot_shared"))) is_main_app;

static volatile uint32_t system_time_ms;
static volatile uint8_t flag_1ms;
static volatile uint8_t flag_100ms;
static volatile uint8_t flag_1000ms;

static void ReadButtons(void)
{
    if (!GET_PIN(BUT_U))
        TGL_LED(0);
    if (!GET_PIN(BUT_D))
        TGL_LED(1);
    if (!GET_PIN(BUT_L))
        TGL_LED(2);
    if (!GET_PIN(BUT_R))
        TGL_LED(3);
    if (!GET_PIN(BUT_S))
        TGL_LED(4);
}

int main(void)
{
    is_main_app = true;
    HW_Init();

    for (;;)
    {
        UartProg_Handler();

        if (flag_1ms)
        {
            flag_1ms = 0;
        }

        if (flag_100ms)
        {
            flag_100ms = 0;
            // TGL_LED(6);
            ReadButtons();
        }

        if (flag_1000ms)
        {

            if (!GET_PIN(BUT_L))
            {
                // TestFlash(0);
                MDR_UART1->DR = 'l';
            }
            if (!GET_PIN(BUT_R))
            {
                // TestFlash(1);
                MDR_UART1->DR = 'r';
            }

            flag_1000ms = 0;
            TGL_LED(6);
        }
    }
}

uint32_t GetSysTime_ms(void)
{
    return system_time_ms;
}

void SysTick_1ms(void)
{
    static uint16_t counter_ms = 0;

    system_time_ms++;

    counter_ms++;
    flag_1ms = 1;
    if (counter_ms % 100 == 0)
    {
        flag_100ms = 1;
    }
    if (counter_ms >= 1000)
    {
        flag_1000ms = 1;
        counter_ms = 0;
    }
    UartProg_Systick_1ms();
}
