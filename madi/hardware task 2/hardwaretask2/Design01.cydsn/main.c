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
#include <stdio.h>

#define BUFFER_SIZE 500u
volatile uint8 speedReady;
volatile uint16 speed;


CY_ISR(ISR_QUAD)
{
    double k;
    k = 0.001;
    
    uint16 quadValue;
    quadValue = QuadDec_1_GetCounter();
    QuadDec_1_SetCounter(0);
   
    speed = quadValue/k;
    
    speedReady = 1u;
}

int main(void)

{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Clock_PWM_Start();
    PWM_1_Start();
    PWM_2_Start();
    Timer_1_Start();
    QuadDec_1_Start();
    
    ISR_QUAD_StartEx(ISR_QUAD);

    for(;;)
    {
        if (speedReady)
    {
        char usbText[20];

        speedReady = 0u;

        sprintf(usbText, "%u\r\n", speed);

        USBUART_1_PutString(usbText);
    }
    }
}

/* [] END OF FILE */