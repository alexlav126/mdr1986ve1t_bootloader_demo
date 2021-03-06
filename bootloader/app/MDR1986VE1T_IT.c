/**
  ******************************************************************************
  * @file    MDR1986VE1T_IT.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    03/04/2013
  * @brief   Main Interrupt Service Routines.
  *
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include "MDR1986VE1T_IT.h"

#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Extern variables ----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Hard_fault_handler_c(unsigned int *hardfault_args);
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->NMI_Handler();
    }
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->HardFault_Handler();
    }
    else
    {
        unsigned int contr_reg;
        contr_reg = __get_CONTROL();
        if (contr_reg & 2)
        {
#if defined(__CMCARM__)
            __ASM MRS R0, PSP;
#else
            __ASM("MRS R0, PSP");
#endif
        }
        else
        {
#if defined(__CMCARM__)
            __ASM MRS R0, MSP;
#else
            __ASM("MRS R0, MSP");
#endif
        }
        //top of stack is in R0. It is passed to C-function.
#if defined(__CMCARM__)
        __ASM BL(Hard_fault_handler_c);
#else
        __ASM("BL (Hard_fault_handler_c)");
#endif

        /* Go to infinite loop when Hard Fault exception occurs */
        while (1)
            ;
    }
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->SVC_Handler();
    }
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles Debug PendSV exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->PendSV_Handler();
    }
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->SysTick_Handler();
    }
}

/*******************************************************************************
* Function Name  : MIL_STD_1553B2_IRQHandler
* Description    : This function handles MIL_STD_1553B2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MIL_STD_1553B2_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->MIL_STD_1553B2_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : MIL_STD_1553B1_IRQHandler
* Description    : This function handles MIL_STD_1553B1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MIL_STD_1553B1_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->MIL_STD_1553B1_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void USB_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->USB_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : CAN1_IRQHandler
* Description    : This function handles CAN1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->CAN1_IRQHandler();
    }
}

/*******************************************************************************

* Function Name  : CAN2_IRQHandler
* Description    : This function handles CAN2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN2_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->CAN2_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : DMA_IRQHandler
* Description    : This function handles DMA global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->DMA_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : UART1_IRQHandler
* Description    : This function handles UART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART1_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->UART1_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : UART2_IRQHandler
* Description    : This function handles UART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART2_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->UART2_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : SSP1_IRQHandler
* Description    : This function handles SSP1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP1_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->SSP1_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : BUSY_IRQHandler
* Description    : This function handles BUSY global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BUSY_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->BUSY_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : ARINC429R_IRQHandler
* Description    : This function handles ARINC429R global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429R_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->ARINC429R_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : POWER_IRQHandler
* Description    : This function handles POWER global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void POWER_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->POWER_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->WWDG_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : Timer4_IRQHandler
* Description    : This function handles TIMER4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer4_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->Timer4_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : Timer1_IRQHandler
* Description    : This function handles Timer1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void Timer1_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->Timer1_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : Timer2_IRQHandler
* Description    : This function handles Timer2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer2_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->Timer2_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : Timer3_IRQHandler
* Description    : This function handles Timer3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->Timer3_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : ADC_IRQHandler
* Description    : This function handles ADC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->ADC_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : ETHERNET_IRQHandler
* Description    : This function handles ETHERNET global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ETHERNET_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->ETHERNET_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : SSP3_IRQHandler
* Description    : This function handles SSP3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP3_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->SSP3_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : SSP2_IRQHandler
* Description    : This function handles SSP2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP2_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->SSP2_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : ARINC429T1_IRQHandler
* Description    : This function handles ARINC429T1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429T1_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->ARINC429T1_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : ARINC429T2_IRQHandler
* Description    : This function handles ARINC429T2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429T2_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->ARINC429T2_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : ARINC429T3_IRQHandler
* Description    : This function handles ARINC429T3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429T3_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->ARINC429T3_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : ARINC429T4_IRQHandler
* Description    : This function handles ARINC429T3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ARINC429T4_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->ARINC429T4_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : BKP_IRQHandler
* Description    : This function handles BKP global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->BKP_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : EXT_INT1_IRQHandler
* Description    : This function handles EXT_INT1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT1_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->EXT_INT1_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : EXT_INT2_IRQHandler
* Description    : This function handles EXT_INT2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT2_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->EXT_INT2_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : EXT_INT3_IRQHandler
* Description    : This function handles EXT_INT3 global interrupt request.
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT3_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->EXT_INT3_IRQHandler();
    }
}

/*******************************************************************************
* Function Name  : EXT_INT4_IRQHandler
* Description    : This function handles EXT_INT4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXT_INT4_IRQHandler(void)
{
    if (is_main_app)
    {
        MAIN_APP_VTABLE_P->EXT_INT4_IRQHandler();
    }
}

/**
  * @brief
  * @param
  * @retval
  */
void Hard_fault_handler_c(unsigned int *hardfault_args)
{
    volatile unsigned int stacked_r0;
    volatile unsigned int stacked_r1;
    volatile unsigned int stacked_r2;
    volatile unsigned int stacked_r3;
    volatile unsigned int stacked_r12;
    volatile unsigned int stacked_lr;
    volatile unsigned int stacked_pc;
    volatile unsigned int stacked_psr;

    stacked_r0 = ((unsigned long)hardfault_args[0]);
    stacked_r1 = ((unsigned long)hardfault_args[1]);
    stacked_r2 = ((unsigned long)hardfault_args[2]);
    stacked_r3 = ((unsigned long)hardfault_args[3]);

    stacked_r12 = ((unsigned long)hardfault_args[4]);
    stacked_lr = ((unsigned long)hardfault_args[5]);
    stacked_pc = ((unsigned long)hardfault_args[6]);
    stacked_psr = ((unsigned long)hardfault_args[7]);

    (void)stacked_r0;
    (void)stacked_r1;
    (void)stacked_r2;
    (void)stacked_r3;
    (void)stacked_r12;
    (void)stacked_lr;
    (void)stacked_pc;
    (void)stacked_psr;

    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
        ;
}
/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE MDR1986VE1T_IT.c */
