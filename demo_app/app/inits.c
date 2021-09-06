#include "inits.h"
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_uart.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_can.h"
#include "main.h"
#include "gpio_def.h"

/*
* HSE_Value must be 16MHz!!!
* in MDR32F9Qx_config.h
* #define HSE_Value                  ((uint32_t)16000000)
*/

/* Frequencies setup */
static void Setup_CPU_Clock(void)
{
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    while (!(MDR_RST_CLK->CLOCK_STATUS & (1 << 2)))
        ; // wait HSE

    // ethernet
    // MDR_RST_CLK->HS_CONTROL = RST_CLK_HSE2_ON; // HSE2 ON (crystall freq = 25 MHz)
    RST_CLK_HSE2config(RST_CLK_HSE2_ON);
    while (!(MDR_RST_CLK->CLOCK_STATUS & (1 << 3)))
        ; // wait HSE2

    // MDR_EEPROM->CMD = (4 << 3); // Flash delay = 4 cycle (default value) F < 125 MHz
    MDR_EEPROM->CMD = (5 << 3); // Flash delay = 5 cycle F < 150 MHz
    /*
    MDR_RST_CLK->HS_CONTROL = RST_CLK_HSE_ON; // HSE ON (crystall freq = 16 MHz)
    while(!(MDR_RST_CLK->CLOCK_STATUS & (1 << 2))); // wait HSE
    */
    MDR_RST_CLK->CPU_CLOCK = ((2 << 0));                                    // CPU_C1 = HSE (on PLL)
    MDR_RST_CLK->PLL_CONTROL = ((1 << 0) | (1 << 2) | (2 << 4) | (7 << 8)); // PLL_USB=ON, PLL_CPU=ON, PLL_USB_MUL=(2+1), PLL_CPU_MUL=(7+1)
    // PLL_USBo = 16 * 3 = 48 MHz
    // PLL_CPUo = 16 * 8 = 128 MHz
    while (!(MDR_RST_CLK->CLOCK_STATUS & (1 << 1)))
        ; // wait PLL_CPU
    while (!(MDR_RST_CLK->CLOCK_STATUS & (1 << 0)))
        ; // wait PLL_USB

    MDR_RST_CLK->CPU_CLOCK = ((2 << 0) | (1 << 2) | (0 << 4) | (1 << 8)); // CPU_C1=HSE, CPU_C2=PLL_CPUo, CPU_C3=CPU_C2, HCLK=CPU_C3
    // HCLK = 128 MHz
    // ETH_CLOCK (HCLK) >= 50 MHz

    MDR_RST_CLK->ETH_CLOCK = (3 << 28) | (1 << 27) | (1 << 24); // PHY_CLOCK = HSE2, PHY_CLOCK_EN = ON, ETH_CLOCK_EN = ON

    SystemCoreClock = 128000000;
}

static void InitPorts(void)
{
    // config inputs:
    PIN_CONFIG_IN(PIN_PORT_BUT_U, PIN_BIT_BUT_U);
    PIN_CONFIG_IN(PIN_PORT_BUT_D, PIN_BIT_BUT_D);
    PIN_CONFIG_IN(PIN_PORT_BUT_L, PIN_BIT_BUT_L);
    PIN_CONFIG_IN(PIN_PORT_BUT_R, PIN_BIT_BUT_R);
    PIN_CONFIG_IN(PIN_PORT_BUT_S, PIN_BIT_BUT_S);

    // config outputs:
    PIN_CONFIG_OUT_LO(PIN_PORT_LED0, PIN_BIT_LED0);
    PIN_CONFIG_OUT_LO(PIN_PORT_LED1, PIN_BIT_LED1);
    PIN_CONFIG_OUT_LO(PIN_PORT_LED2, PIN_BIT_LED2);
    PIN_CONFIG_OUT_LO(PIN_PORT_LED3, PIN_BIT_LED3);
    PIN_CONFIG_OUT_LO(PIN_PORT_LED4, PIN_BIT_LED4);
    PIN_CONFIG_OUT_LO(PIN_PORT_LED5, PIN_BIT_LED5);
    PIN_CONFIG_OUT_LO(PIN_PORT_LED6, PIN_BIT_LED6);
    PIN_CONFIG_OUT_LO(PIN_PORT_LED7, PIN_BIT_LED7);
}

static void InitTim3(void)
{
    TIMER_CntInitTypeDef sTIMER;

    // timer3 period = 1 ms
    //RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER3, ENABLE);
    TIMER_BRGInit(MDR_TIMER3, TIMER_HCLKdiv1);
    TIMER_DeInit(MDR_TIMER3);
    TIMER_CntStructInit(&sTIMER);
    sTIMER.TIMER_Period = 0x001F3FF; // div = 128000 (ARR)
    TIMER_CntInit(MDR_TIMER3, &sTIMER);
    TIMER_ITConfig(MDR_TIMER3, TIMER_STATUS_CNT_ARR, ENABLE); // (CNT == ARR)
    TIMER_Cmd(MDR_TIMER3, ENABLE);
    NVIC_EnableIRQ(TIMER3_IRQn);
}

void InitUart1(void)
{
    PORT_InitTypeDef PORT_InitStruct = {0};
    PORT_StructInit(&PORT_InitStruct);

    // Set the HCLK division factor = 1 for UART1
    UART_BRGInit(MDR_UART1, UART_HCLKdiv1);

    // UART1 (uart)
    PORT_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
    PORT_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
    PORT_InitStruct.PORT_PD_SHM = PORT_PD_SHM_OFF;
    PORT_InitStruct.PORT_PD = PORT_PD_DRIVER;
    PORT_InitStruct.PORT_GFEN = PORT_GFEN_OFF;
    PORT_InitStruct.PORT_FUNC = PORT_FUNC_MAIN;
    PORT_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStruct.PORT_MODE = PORT_MODE_DIGITAL;

    // Configure PORTC pins 3 (UART1_TX) as output
    PORT_InitStruct.PORT_OE = PORT_OE_OUT;
    PORT_InitStruct.PORT_Pin = PORT_Pin_3;
    PORT_Init(MDR_PORTC, &PORT_InitStruct);

    // Configure PORTC pins 4 (UART1_RX) as input
    PORT_InitStruct.PORT_OE = PORT_OE_IN;
    PORT_InitStruct.PORT_Pin = PORT_Pin_4;
    PORT_Init(MDR_PORTC, &PORT_InitStruct);

    UART_InitTypeDef UART_InitStructure = {0};

    // Initialize UART_InitStructure
    UART_InitStructure.UART_BaudRate = 115200;
    UART_InitStructure.UART_WordLength = UART_WordLength8b;
    UART_InitStructure.UART_StopBits = UART_StopBits1;
    UART_InitStructure.UART_Parity = UART_Parity_No;
    UART_InitStructure.UART_FIFOMode = UART_FIFO_OFF;
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE;
    UART_Init(MDR_UART1, &UART_InitStructure);

    UART_ITConfig(MDR_UART1, UART_IT_RX, ENABLE); // Receiver interrupt (UARTRXINTR)
    UART_ITConfig(MDR_UART1, UART_IT_TX, ENABLE); // Transmitter interrupt (UARTTXINTR)

    NVIC_SetPriority(UART1_IRQn, 1);
    NVIC_EnableIRQ(UART1_IRQn);

    // Enables UART1 peripheral
    UART_Cmd(MDR_UART1, ENABLE);
}

void HW_Init(void)
{
    // MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF; // enable clock to all periph
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_RST_CLK;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_TIMER3;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_PORTA;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_PORTB;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_PORTC;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_PORTD;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_PORTE;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_PORTF;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_EEPROM_CNTRL;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PER_CLOCK_PCLK_EN_UART1;

    Setup_CPU_Clock();

    InitPorts();
    InitTim3();
    InitUart1();
}
