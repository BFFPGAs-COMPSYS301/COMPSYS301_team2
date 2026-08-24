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
#define THRESHOLD       500

int main(void)
{
    uint8 i;
    int16 adcResult;
    int16 adc_mV;
    int32 total;
    int32 average_mV;
    char uartBuffer[64];

    CyGlobalIntEnable;

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
            adc_mV = ADC_1_CountsTo_mVolts(adcResult);

            /* Add to total */
            total += adc_mV;
        }

        /* Calculate average */
        average_mV = total / SAMPLE_SIZE;

        /* Software comparator */
        if(average_mV > THRESHOLD)
        {
            LED_Write(1);
        }
        else
        {
            LED_Write(0);
        }
    }
}
