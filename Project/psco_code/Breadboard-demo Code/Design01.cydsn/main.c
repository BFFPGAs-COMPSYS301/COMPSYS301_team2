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
#define THRESHOLD       400

int main(void)
{
    uint8 i;
    int16 adcResult;
    int16 adc_mV;
    int32 total;
    int32 average_mV;
    
    int16 adcResult_1;
    int16 adc_mV_1;
    int32 total_1;
    int32 average_mV_1;

    CyGlobalIntEnable;

    /* Start ADC */
    ADC_1_Start();
    ADC_2_Start();

    for(;;)
    {
        total = 0;
        total_1 = 0;

        /* Take 10 samples */
        for(i = 0; i < SAMPLE_SIZE; i++)
        {
            /* Start one conversion */
            ADC_1_StartConvert();
            

            /* Wait for conversion to finish */
            ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
            ADC_2_StartConvert();
            ADC_2_IsEndConversion(ADC_2_WAIT_FOR_RESULT);

            /* Read ADC result */
            adcResult = ADC_1_GetResult16();
            adc_mV = ADC_1_CountsTo_mVolts(adcResult);

            /* Add to total */
            total += adc_mV;
            
            /* Read ADC result */
            adcResult_1 = ADC_2_GetResult16();
            adc_mV_1 = ADC_2_CountsTo_mVolts(adcResult_1);

            /* Add to total */
            total_1 += adc_mV_1;
        }

        /* Calculate average */
        average_mV = total / SAMPLE_SIZE;
        average_mV_1 = total_1 / SAMPLE_SIZE;

        /* Software comparator */
        if(average_mV > THRESHOLD)
        {
            LED_Write(1);
        }
        else
        {
            LED_Write(0);
        }
        
        /* Software comparator */
        if(average_mV_1 > THRESHOLD)
        {
            LED_1_Write(1);
        }
        else
        {
            LED_1_Write(0);
        }
    }
}
