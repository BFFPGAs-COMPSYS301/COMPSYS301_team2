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

#define THRESHOLD   3000

CY_ISR(ADC_ISR)
{
    uint8 adcValue;
    adcValue = ADC_SAR_1_GetResult8();
    
    VDAC8_1_SetValue(adcValue);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ADC_SAR_1_Start();
    Timer_1_Start();

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
