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
#include "project.h"
#include "RGBLedDriver.h"
#include "InterruptRoutines.h"
#include "VariabiliGlobali.h"
#include "stdio.h"

Color pattern = {0, 0, 0};

static char message[30] = {'\0'};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    UART_Start(); 
    
    isr_UART_StartEx(Custom_UART_RX_ISR);
    
    UART_PutString("Scrivi un valore:\r\n");

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    RGBLed_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        if(flag==1)
        {
            pattern.red = UART_GetByte();
            //sprintf(message,"Valore ricevuto: %d\r\n", pattern.red);
            //UART_PutString(message);
            RGBLed_WriteColor(pattern);
            flag=0;
        }
    }
}

/* [] END OF FILE */
