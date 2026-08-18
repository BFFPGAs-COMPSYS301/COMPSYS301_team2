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

#define SAMPLE_SIZE     10
#define THRESHOLD       2448u

int main(void)
{
    uint8 i;
    int16 adcResult;
    int32 total;
    int32 average;
    char uartBuffer[64];

    CyGlobalIntEnable;

    /* Start USB UART */
    USBUART_1_Start(0, USBUART_1_5V_OPERATION);

    /* Start ADC */
    ADC_1_Start();

    for(;;)
    {
        total = 0;

        /* Take 10 samples */
        for(i = 0; i < SAMPLE_SIZE; i++)
        {
            /* Start one conversion */
            ADC_1_StartConvert();

            /* Wait for conversion to finish */
            ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);

            /* Read ADC result */
            adcResult = ADC_1_GetResult16();

            /* Add to total */
            total += adcResult;
        }

        /* Calculate average */
        average = total / SAMPLE_SIZE;

        /* Software comparator */
        if(average > THRESHOLD)
        {
            LED_Write(1);
        }
        else
        {
            LED_Write(0);
        }

        /* Send average over USB */
        if(USBUART_1_GetConfiguration())
        {
            if(USBUART_1_CDCIsReady())
            {
                sprintf(uartBuffer,
                        "ADC Average: %ld\r\n",
                        average);

                USBUART_1_PutString(uartBuffer);
            }
        }

        /* Wait before next group of samples */
        CyDelay(200);
    }
}
