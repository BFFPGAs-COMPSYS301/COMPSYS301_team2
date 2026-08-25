#include "project.h"
#include <stdio.h>

volatile uint8 speedReady = 0u;
volatile int32 speed = 0;

CY_ISR(MyISR)
{
    int32 quadValue;

    quadValue = QuadDec_1_GetCounter();
    QuadDec_1_SetCounter(0);

    speed = quadValue / 0.001;
    speedReady = 1u;

    Timer_1_ReadStatusRegister();
}

int main(void)
{
    char usbText[20];

    CyGlobalIntEnable;

    Clock_PWM_Start();
    PWM_1_Start();
    PWM_2_Start();
    QuadDec_1_Start();

    USBUART_1_Start(0u, USBUART_1_5V_OPERATION);

    while (USBUART_1_GetConfiguration() == 0u)
    {
    }

    USBUART_1_CDC_Init();

    ISR_QUAD_StartEx(MyISR);
    Timer_1_Start();

    for (;;)
    {
        if (speedReady == 1u)
        {
            speedReady = 0u;

            sprintf(usbText, "%ld\r\n", (long)speed);

            while (USBUART_1_CDCIsReady() == 0u)
            {
            }

            USBUART_1_PutString(usbText);
        }
    }
}