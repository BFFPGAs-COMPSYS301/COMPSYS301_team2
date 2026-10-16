
#include "project.h"
#include <stdio.h>
#include <stdbool.h>
#include "robotcontrols.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    PWM_1_Start();
    PWM_2_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    VDAC8_1_Start();
    Timeout_1_Start();
    Timeout_2_Start();
    Timeout_3_Start();
    Timeout_4_Start();
    Timeout_5_Start();

    //turnRight();
    for(;;)
    {
        doSomething();
        CyDelay(2);
    }
}

/* [] END OF FILE */
