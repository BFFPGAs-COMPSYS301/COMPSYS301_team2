
#include "robot_controls.h"

#define FORWARD_COMPARE 23
#define PWM_PERIOD 90
#define PWM_STOP 45

/* Maximum time allowed to find the new line */
#define TURN_TIMEOUT_MS 2000u

static uint16 offLineCount = 0;
static uint16 onLineCount = 0;
static uint8 turnsComplete = 0;

static bool turnDetected = false;
static bool onLine = false;
static bool controlFault = false;

/* ========================================
 * INITIALIZATION
 * ======================================== */

void RobotControl_Init(void)
{
    offLineCount = 0;
    onLineCount = 0;
    turnsComplete = 0;

    turnDetected = false;
    onLine = false;
    controlFault = false;

    Robot_Stop();
}

/* ========================================
 * MOTOR CONTROL
 * ======================================== */

void Robot_Stop(void)
{
    PWM_1_WriteCompare(PWM_STOP);
    PWM_2_WriteCompare(PWM_STOP);
}

void Robot_Forward(void)
{
    PWM_1_WriteCompare(FORWARD_COMPARE);
    PWM_2_WriteCompare(FORWARD_COMPARE);
}

void Robot_ForwardSlow(void)
{
    PWM_1_WriteCompare(23);
    PWM_2_WriteCompare(23);
}

void Robot_LineForward(void)
{
    PWM_1_WriteCompare(FORWARD_COMPARE - 2);
    PWM_2_WriteCompare(FORWARD_COMPARE);
}

void Robot_LineCorrect(void)
{
    PWM_1_WriteCompare(PWM_PERIOD - 20);
    PWM_2_WriteCompare(20);
}

/* ========================================
 * LEFT TURN
 * ======================================== */

void Robot_TurnLeft(void)
{
    uint16 elapsed = 0;

    onLineCount = 0;
    onLine = false;
    turnDetected = true;

    Robot_ForwardSlow();
    CyDelay(142);

    Robot_Stop();

    while (LED1_Read() == 1)
    {
        PWM_1_WriteCompare(PWM_PERIOD - 25);
        PWM_2_WriteCompare(25);

        CyDelay(1);
        elapsed++;

        if (elapsed >= TURN_TIMEOUT_MS)
        {
            Robot_Stop();
            controlFault = true;
            return;
        }
    }

    Robot_ForwardSlow();
    CyDelay(10);

    PWM_1_WriteCompare(25);
    PWM_2_WriteCompare(PWM_PERIOD - 25);
    CyDelay(50);
}

/* ========================================
 * RIGHT TURN
 * ======================================== */

void Robot_TurnRight(void)
{
    uint16 elapsed = 0;

    onLineCount = 0;
    onLine = false;
    turnDetected = true;

    Robot_ForwardSlow();
    CyDelay(146);

    Robot_Stop();

    while (LED1_Read() == 1)
    {
        PWM_1_WriteCompare(25);
        PWM_2_WriteCompare(PWM_PERIOD - 25);

        CyDelay(1);
        elapsed++;

        if (elapsed >= TURN_TIMEOUT_MS)
        {
            Robot_Stop();
            controlFault = true;
            return;
        }
    }

    Robot_ForwardSlow();
    CyDelay(30);
}

/* ========================================
 * BENCHMARK LINE FOLLOWING
 * ======================================== */

void RobotControl_Update(void)
{
    if (controlFault)
    {
        Robot_Stop();
        return;
    }

    uint8 front = LED1_Read();
    uint8 rearLeft = LED2_Read();
    uint8 rearRight = LED3_Read();
    uint8 frontRight = LED4_Read();
    uint8 frontLeft = LED5_Read();

    if (front == 1)
    {
        /* Front sensor has lost the line */

        if (offLineCount < 15)
        {
            Robot_LineCorrect();
        }
        else if (offLineCount > 80)
        {
            Robot_Stop();
            controlFault = true;
            return;
        }
        else
        {
            Robot_ForwardSlow();
            CyDelay(12);

            if (frontLeft == 0)
            {
                Robot_TurnLeft();
            }
            else if (frontRight == 0)
            {
                Robot_TurnRight();
            }
            else
            {
                Robot_Stop();
            }
        }

        offLineCount++;
    }
    else
    {
        /* Front sensor is on the line */

        Robot_LineForward();
        offLineCount = 0;

        if (onLineCount > 100 && !onLine)
        {
            turnDetected = false;
        }

        if (rearLeft == 0 || rearRight == 0)
        {
            onLine = true;
        }

        onLineCount++;
    }

    if (turnDetected && onLine)
    {
        turnsComplete++;
        turnDetected = false;
    }
}
