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

int i=0;
uint8_t val=0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    UART_Start(); 
    
    isr_UART_StartEx(Custom_UART_RX_ISR);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    RGBLed_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        if(i==0){ 
            if(flag==1){
                val=UART_GetChar();
                if(val==160){
                    i++;
                }
                else{
                    UART_PutString("Formato errato!\r\n");
                }
                flag=0;
            }
        }
        
        else if(i==1)
        {
            if(flag==1)
            {
                pattern.red = UART_GetChar();
                RGBLed_WriteColor(pattern);
                i++;
                flag=0; 
            }
        }
        
        else if(i==2)
        {
            if(flag==1)
            {
                pattern.green = UART_GetChar();
                RGBLed_WriteColor(pattern);
                i++;
                flag=0; 
            }
        }
        
        else if(i==3)
        {
            if(flag==1)
            {
                pattern.blu = UART_GetChar();
                RGBLed_WriteColor(pattern);
                i++;
                flag=0;
            }
        }
        
        else if(i==4){ 
            if(flag==1){
                val=UART_GetChar();
                if(val==192){
                    UART_PutString("Config corretta!\r\n");
                }
                else{
                    UART_PutString("Config errata!\r\n");
                }
                i=0;
                flag=0;
            }
        }
    }
}

/* [] END OF FILE */
