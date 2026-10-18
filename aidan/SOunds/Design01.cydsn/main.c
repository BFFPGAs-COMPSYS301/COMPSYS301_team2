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

/*
403Hz - Period=4960, Compare=2480

604Hz - Period=3300, Compare=1650

538Hz - Period=3716, Compare=1858

*/
#include "project.h"

void tone1(){
    PWM_1_WritePeriod(4960);
    PWM_2_WritePeriod(4960);
    PWM_1_WriteCompare(2480);
    PWM_2_WriteCompare(2480);
}

void tone2(){
    PWM_1_WritePeriod(3300);
    PWM_2_WritePeriod(3300);
    PWM_1_WriteCompare(1650);
    PWM_2_WriteCompare(1650);
}

void tone3(){
    PWM_1_WritePeriod(3716);
    PWM_2_WritePeriod(3716);
    PWM_1_WriteCompare(1858);
    PWM_2_WriteCompare(1858);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    PWM_1_Start();
    PWM_2_Start();


    for(;;)
    {
        tone1();
        CyDelay(320);
        tone2();
        CyDelay(120);
        tone2();
        CyDelay(170);
        tone3();
        CyDelay(220);
        tone3();
        CyDelay(120);
        tone3();
        CyDelay(190);
        tone3();
        CyDelay(90);
        tone3();
        CyDelay(80);
        tone2();
        CyDelay(330);
        tone2();
        CyDelay(330);
        tone1();
        CyDelay(330);
        
    }
}

/* [] END OF FILE */
