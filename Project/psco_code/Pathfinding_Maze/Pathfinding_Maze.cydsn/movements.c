/*
    Each encoder count is ~0.9mm
    Each cell is ~9cm
    
    one cell = 100 ecoder counts
*/
#include "project.h"
#include "astar.h"

#define CELL_LENGTH 100
#define CELL_LENGTH_SHORT 75
#define INTERSECTION_TIMEOUT 5000

static void MoveForwardOneCell(Command nextCommand)
{
    int16 travelled = 0;
    int16 timeout = 0;

    LED_1_Write(1);
    QuadDec_1_SetCounter(0);

    // Drive forward for one complete cell if going straight.
    if (nextCommand == CMD_FORWARD)
    {
        PWM_1_WriteCompare(20);
        PWM_2_WriteCompare(20);

        while (travelled < CELL_LENGTH)
        {
            travelled = QuadDec_1_GetCounter();
        }
    }
    // If turning next, approach the intersection first.
    else
    {
        PWM_1_WriteCompare(20);
        PWM_2_WriteCompare(20);

        while (travelled < CELL_LENGTH_SHORT)
        {
            travelled = QuadDec_1_GetCounter();
        }

        // Continue until the sensors detect the intersection.
        while (LED_5_Read())
        {
            CyDelay(1);
            timeout++;
        }
    }

    // Stop the motors.
    PWM_1_WriteCompare(45);
    PWM_2_WriteCompare(45);

    LED_1_Write(0);

    CyDelay(1000);
}

static void TurnLeft(Command nextCommand) {
    LED_2_Write(1);
    CyDelay(1000);
    LED_2_Write(0);
    CyDelay(1000);
}

static void TurnRight(Command nextCommand) {
    LED_3_Write(1);
    CyDelay(1000);
    LED_3_Write(0);
    CyDelay(1000);
}