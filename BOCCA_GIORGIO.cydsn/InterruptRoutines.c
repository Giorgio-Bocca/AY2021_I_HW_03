/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "InterruptRoutines.h"
#include "RGBLedDriver.h"
#include "VariabiliGlobali.h"

#include "UART.h"
#include "stdio.h"

int flag=0; 

 CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
          flag = 1; 

    }
}

/* [] END OF FILE */
