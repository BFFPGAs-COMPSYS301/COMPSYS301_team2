#include "project.h"
#include <stdio.h>

volatile uint8 sendFlag = 0u;
int32 speedL = 0;

CY_ISR(MyISR)
{
    char usbText[20];

    speedL++;
    sprintf(usbText, "%ld\r\n", (long)speedL);

    while (USBUART_1_CDCIsReady() == 0u)
    {
    }
    USBUART_1_PutString(usbText);

    Timer_1_ReadStatusRegister();   /* clear the interrupt source */
}

int main(void)
{
    CyGlobalIntEnable;

    USBUART_1_Start(0u, USBUART_1_5V_OPERATION);

    /* wait for the host to enumerate us */
    while (USBUART_1_GetConfiguration() == 0u)
    {
    }
    USBUART_1_CDC_Init();

    Timer_1_Start();
    ISR_1_StartEx(MyISR);

    for(;;)
    {
        /* host re-configured the device (e.g. terminal reopened) */
        if (USBUART_1_IsConfigurationChanged() != 0u)
        {
            if (USBUART_1_GetConfiguration() != 0u)
            {
                USBUART_1_CDC_Init();
            }
        }

        CyDelay(250);
    }
}