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

void ADC_SAR_1_Start();
void ISR_1_Start(void);

CY_ISR(MyISR)
{
    LED_Write(!LED_Read());
    Timer_1_ReadStatusRegister();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Timer_1_Start();
    ADC_SAR_1_Start();
    
    isr_1_StartEx(MyISR);

    for(;;)
    {
        /* Place your application code here. */
    }
}
/* [] END OF FILE */
