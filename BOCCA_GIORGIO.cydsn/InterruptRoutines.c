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

int flag=0; 
int count=0;
int i;

 CY_ISR(Custom_UART_RX_ISR)
{     
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        flag = 1; //Aggiorno il flag quando ricevo un dato  
    }
}

CY_ISR(Custom_Timer_ISR)
{
    if(i==1 || i==2 || i==3 || i==4) //Se mi trovo in uno stato intermedio...
    {
        if(flag==1 && count<5) //Se ho ricevuto il byte prima dei 5 secondi resetto il contatore
        {
            count=0;
        }
        else if(flag==0 && count>=5) //Se non ho ricevuto il byte prima dei 5 secondi 
        {                            //stampo a video il Timeout, azzero il contatore e torno nello stato di IDLE
            UART_PutString("\nTimeout! Torno nella IDLE\n");
            i=0;
            count=0;
        }
        else if(flag==0 && count<5)
        {
            count++;
        }
    }
    
    Timeout_Timer_ReadStatusRegister();
}

/* [] END OF FILE */
