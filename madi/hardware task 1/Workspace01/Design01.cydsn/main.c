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

CY_ISR(ADC_ISR)

{
    uint8 adcValue;
    
    adcValue = ADC_SAR_1_GetResult8();
    
    VDAC8_1_SetValue(adcValue);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_SAR_1_Start();
    VDAC8_1_Start();
    Timer_1_Start();
    USBFS_1_Start(0,USBFS_1_5V_OPERATION);
    
    ADC_ISR_StartEx(ADC_ISR);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
