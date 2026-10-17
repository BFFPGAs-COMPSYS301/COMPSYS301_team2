/*
    Each encoder count is ~0.9mm
    Each cell is ~9cm
    
    one cell = 100 ecoder counts
*/
#include "project.h"
#include "astar.h"

#define CELL_LENGTH 75
#define CELL_LENGTH_SHORT 55
#define INTERSECTION_TIMEOUT 5000

#define PERIOD 90
#define FORWARD_SPEED 22 // 45 is stopped, go lower to drive forward, stay below 25 to ensure movement

static uint16_t offLineCount = 0;

static void goForwardSlow(void);
static void rampingLeftBack();

static void forwardFollowing() {
    if (FrontSensor_Read() == 0) {
        PWM_1_WriteCompare(FORWARD_SPEED - 1);
        PWM_2_WriteCompare(FORWARD_SPEED); // Drive right motor slightly slower so it gradually turns to the right
    } else {
        rampingLeftBack();
    }
}

static void findCorner() {
    if (FrontSensor_Read() == 0) { // Front sensor is on the line
        offLineCount = 0;
        PWM_1_WriteCompare(FORWARD_SPEED - 1);
        PWM_2_WriteCompare(FORWARD_SPEED); // Drive right motor slightly slower so it gradually turns to the right
    } else {
        if (offLineCount < 0) {
            rampingLeftBack();
        } else {
            goForwardSlow();
        }
        offLineCount++;
    }
}

static void rampingLeftBack(){
        PWM_2_WriteCompare(45);
        PWM_1_WriteCompare(PERIOD - 25); // Drive left wheel backard to quickly pivot right
        CyDelay(15);
        PWM_1_WriteCompare(PERIOD - 23); // Drive left wheel backard to quickly pivot right
        CyDelay(15);
        PWM_1_WriteCompare(PERIOD - 21); // Drive left wheel backard to quickly pivot right
        CyDelay(15);
        PWM_1_WriteCompare(PERIOD - 20); // Drive left wheel backard to quickly pivot right
        CyDelay(15);
        PWM_1_WriteCompare(PERIOD - 18); // Drive left wheel backard to quickly pivot right
        CyDelay(40);
        PWM_1_WriteCompare(PERIOD - 20); // Drive left wheel backard to quickly pivot right
        CyDelay(15);
        PWM_1_WriteCompare(PERIOD - 21); // Drive left wheel backard to quickly pivot right
        CyDelay(15);
        PWM_1_WriteCompare(PERIOD - 23); // Drive left wheel backard to quickly pivot right
        CyDelay(15);
        PWM_1_WriteCompare(PERIOD - 25); // Drive left wheel backard to quickly pivot right
        CyDelay(15);
}

static void goForwardSlow() {
    PWM_1_WriteCompare(22);
    PWM_2_WriteCompare(22);
}

static void stopMoving() {
    PWM_1_WriteCompare(45);
    PWM_2_WriteCompare(45);
}

static void MoveForwardOneCell(Command nextCommand)
{
    int16 travelled = 0;
    int16 timeout = 0;

    LED_1_Write(1);
    QuadDec_1_SetCounter(0);

    // Drive forward for one complete cell if going straight.
    if (nextCommand == CMD_FORWARD)
    {
        while (travelled < CELL_LENGTH)
        {
            forwardFollowing();
            CyDelay(1);
            travelled = QuadDec_1_GetCounter();
        }
        
       // stopMoving(); //Stop at end of cell for debugging, remove for final version
        
    } else {  // If turning next, approach the intersection first.
        // Continue until the sensors detect the intersection.
        if (nextCommand == CMD_LEFT) {
            while (FrontLSensor_Read() && timeout < INTERSECTION_TIMEOUT)
            {
                findCorner();
                CyDelay(1);
                timeout++;
            }
        } else if (nextCommand == CMD_RIGHT) {
            while (FrontRSensor_Read() && timeout < INTERSECTION_TIMEOUT)
            {
                findCorner();
                CyDelay(1);
                timeout++;
            }
        }
    }

    // Stop the motors.
    PWM_1_WriteCompare(45);
    PWM_2_WriteCompare(45);

    LED_1_Write(0);

    //CyDelay(1000);
}

static void TurnLeft() {
    LED_2_Write(1);
    goForwardSlow();
    CyDelay(250);
    stopMoving();
    PWM_1_WriteCompare(PERIOD - 20);
    PWM_2_WriteCompare(20);
    CyDelay(500);
    while (FrontSensor_Read() == 1) {
        PWM_1_WriteCompare(PERIOD - 21);
        PWM_2_WriteCompare(21);
    }
    goForwardSlow();
    CyDelay(10);
    PWM_1_WriteCompare(20);
    PWM_2_WriteCompare(PERIOD - 20);
    CyDelay(82);
    stopMoving();
    LED_2_Write(0);
    CyDelay(1000);
}

static void TurnRight() {
    LED_3_Write(1);
    uint8 led_1 = FrontSensor_Read();
    goForwardSlow();
    CyDelay(220);
    stopMoving();
    PWM_1_WriteCompare(20);
    PWM_2_WriteCompare(PERIOD - 20);
    CyDelay(500);
    while (FrontSensor_Read() == 1) {
        PWM_1_WriteCompare(21);
        PWM_2_WriteCompare(PERIOD - 21);
    }
    goForwardSlow();
    CyDelay(10);
    PWM_1_WriteCompare(PERIOD - 20);
    PWM_2_WriteCompare(20);
    CyDelay(100);
    stopMoving();
    LED_3_Write(0);
    CyDelay(1000);
}

static void UTurn(void)
{
    LED_3_Write(1);
    uint8 led_1 = FrontSensor_Read();
    goForwardSlow();
    CyDelay(500);
    stopMoving();
    PWM_2_WriteCompare(20);
    PWM_1_WriteCompare(PERIOD - 18);
    CyDelay(700);
    while (FrontSensor_Read() == 1) {
        PWM_2_WriteCompare(21);
        PWM_1_WriteCompare(PERIOD - 19);
    }
    goForwardSlow();
    CyDelay(10);
    PWM_2_WriteCompare(PERIOD - 20);
    PWM_1_WriteCompare(18);
    CyDelay(100);
    stopMoving();
    PWM_1_WriteCompare(PERIOD - 20);
    PWM_2_WriteCompare(PERIOD - 20);
    CyDelay(200);
    stopMoving();
    LED_3_Write(0);
    CyDelay(1000);
}

static void LittleLeft(void)
{/*
    goForwardSlow();
    CyDelay(100);
    stopMoving();
    PWM_1_WriteCompare(PERIOD - 20);
    PWM_2_WriteCompare(20);
    CyDelay(500);
    while (FrontSensor_Read() == 1) {
        PWM_1_WriteCompare(PERIOD - 21);
        PWM_2_WriteCompare(21);
    }
    goForwardSlow();
    CyDelay(10);
    PWM_1_WriteCompare(20);
    PWM_2_WriteCompare(PERIOD - 20);
    CyDelay(82);*/
    stopMoving();
    LED_2_Write(0);
    CyDelay(1000);
}

static void LittleRight(void)
{ /*
    uint8 led_1 = FrontSensor_Read();
    goForwardSlow();
    CyDelay(100);
    stopMoving();
    PWM_1_WriteCompare(20);
    PWM_2_WriteCompare(PERIOD - 20);
    CyDelay(500);
    while (FrontSensor_Read() == 1) {
        PWM_1_WriteCompare(21);
        PWM_2_WriteCompare(PERIOD - 21);
    }
    goForwardSlow();
    CyDelay(10);
    PWM_1_WriteCompare(PERIOD - 20);
    PWM_2_WriteCompare(20);
    CyDelay(100);*/
    stopMoving();
    LED_3_Write(0);
    CyDelay(1000);
}