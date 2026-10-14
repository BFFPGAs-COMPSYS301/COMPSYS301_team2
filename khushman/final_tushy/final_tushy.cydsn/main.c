
#include "project.h"
#include "robot_controls.h"
int main(void)
{
    CyGlobalIntEnable;

    /* Start motor PWM components */
    PWM_1_Start();
    PWM_2_Start();

    /* Start sensor hardware */
    VDAC8_1_Start();

    Timeout_1_Start();
    Timeout_2_Start();
    Timeout_3_Start();
    Timeout_4_Start();
    Timeout_5_Start();

    /* Initialize robot controller */
    RobotControl_Init();

    /* Main control loop */
    for (;;)
    {
        RobotControl_Update();

        CyDelay(5);
    }
}
