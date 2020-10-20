/* ========================================
 * \file main.c
 * \brief Main file for project ASSIGNMENT 03: RGB LED CONTROL THROUGH SERIAL PORT COMMUNICATION
 * 
 *  This project shows how to configure a RGB Led through a series of packets 
 *  of bytes send with a serial port communication. A timeout happens
 *  if the system doesn't receive a byte within 5 seconds and returns in the IDLE state.
 *   
 * \author Giorgio Bocca
 * ========================================
*/
#include "project.h"
#include "RGBLedDriver.h"
#include "InterruptRoutines.h"
#include "VariabiliGlobali.h"
#include "stdio.h"

Color pattern = {0, 0, 0};

int i=55; //Variabile utilizzata per tenere traccia dello stato del programma,
          //prima per l'invio del carattere 'v', poi per i vari byte che compongono un pacchetto dati
uint8_t val=0; //Varibile utilizzata per salvare il valore del byte ricevuto da seriale
int count; //Variabile utilizzata per contare i secondi per il Timeout e aggiornata nella ISR
char car; //Variabile utilizzata per salvare il carattere 'v'

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //Inizializzo Timer e ISR ad esso relativa
    Timeout_Timer_Start();
    isr_TIMER_StartEx(Custom_Timer_ISR);
    //Inizializzo UART e ISR ad essa relativa
    UART_Start(); 
    isr_UART_StartEx(Custom_UART_RX_ISR);
    
    RGBLed_Start();
    
    UART_PutString("Digita il carattere 'v':\r\n");
    
    for(;;)
    {
        /* Place your application code here. */
        
        if(i==55) //Fino a che non invio il carattere 'v' per mostrare
        {         //l'interfaccia RGB Led Control non esco dal ciclo
            if(flag==1)
            {
                car=UART_GetChar();
                if(car=='v')
                {
                    UART_PutString("\n");
                    UART_PutString("RGB LED Program $$$"); //Invio la stringa alla porta seriale per attivare l'interfaccia
                    UART_PutString("\nStringa inviata!\r\n");
                    i=0;
                }
                flag=0;
            }
        }  
        
        else if(i==0)
        { 
            if(flag==1)
            {
                val=UART_GetChar();
                if(val==160) //Corrisponde alla codifica esadecimale 0xA0
                {
                    i++;
                }
                else
                {
                    UART_PutString("\nByte iniziale errato! Torno nella IDLE\r\n"); //Se il primo byte ricevuto del pacchetto non è uguale a
                }                                                                   //0xA0, stampo a video e rimango nello stato di IDLE
                flag=0;
            }
        }
        
        else if(i==1)
        {
            if(flag==1)
            {
                pattern.red = UART_GetChar();
                RGBLed_WriteColor(pattern); //Configuro il Led rosso
                i++;
                flag=0; 
                count=0;
            }
        }
        
        else if(i==2)
        {
            if(flag==1)
            {
                pattern.green = UART_GetChar();
                RGBLed_WriteColor(pattern); //Configuro il Led verde
                i++;
                flag=0;
                count=0;
            }
        }
        
        else if(i==3)
        {
            if(flag==1)
            {
                pattern.blu = UART_GetChar();
                RGBLed_WriteColor(pattern); //Configuro il Led blu
                i++;
                flag=0;
                count=0;
            }
        }
        
        else if(i==4)
        { 
            if(flag==1)
            {
                val=UART_GetChar();
                if(val==192) //Corrisponde alla codifica esadecimale 0xC0
                {
                    UART_PutString("\nConfigurazione corretta!\r\n"); //Se il pacchetto ricevuto è nel formato corretto,
                    UART_PutString("Pacchetto inviato! Torno nella IDLE"); //stampo a video e torno nello stato di IDLE
                }
                else
                {
                    UART_PutString("\nByte finale errato!\r\n"); //Se l'ultimo byte ricevuto del pacchetto non è uguale a
                    UART_PutString("Pacchetto inviato! Torno nella IDLE"); //0xC0, stampo a video e torno nello stato di IDLE
                }
                i=0;
                flag=0;
                count=0;
            }
        }
    }
}
/* [] END OF FILE */
