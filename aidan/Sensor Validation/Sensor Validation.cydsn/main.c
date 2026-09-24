#include "project.h"
#include <stdio.h>

#define FORWARD_COMPARE 23
#define period 90

uint16 offLineCount = 0;

static void MotorL_Forward() {
  PWM_1_WriteCompare(FORWARD_COMPARE);
}

static void MotorR_Forward() {
   PWM_2_WriteCompare(FORWARD_COMPARE);
}

static void MotorL_Back() {
  PWM_1_WriteCompare(period - FORWARD_COMPARE);
}

static void MotorR_Back() {
    PWM_2_WriteCompare(period - FORWARD_COMPARE);
}   

static void goForward() {
    MotorR_Forward();
    MotorL_Forward();
}

static void goBack() {
    MotorR_Back();
    MotorL_Back();
}   

static void stopMoving(){
    PWM_1_WriteCompare(45);
    PWM_2_WriteCompare(45);
}

static void oneSensorForward() {
    PWM_1_WriteCompare(FORWARD_COMPARE - 2);
    PWM_2_WriteCompare(FORWARD_COMPARE);
}

static void oneSensorCorrect() {
    PWM_1_WriteCompare(period - 20);
    PWM_2_WriteCompare(20);
}

static void goForwardSlow() {
    PWM_1_WriteCompare(23);
    PWM_2_WriteCompare(23);
}

static void turnLeft() {
    goForwardSlow();
    CyDelay(142);
    stopMoving();
    while (LED1_Read() == 1) {
        PWM_1_WriteCompare(period - 25);
        PWM_2_WriteCompare(25);
    }
    goForwardSlow();
    CyDelay(30);
}

static void turnRight() {
    uint8 led_1 = LED1_Read();
    goForwardSlow();
    CyDelay(146);
    stopMoving();
    while (LED1_Read() == 1) {
        PWM_1_WriteCompare(25);
        PWM_2_WriteCompare(period - 25);
    }
    goForwardSlow();
    CyDelay(30);
}

static void Dance() { // Shaking movement used to debug
    PWM_1_WriteCompare(period - 20);
    PWM_2_WriteCompare(20);
    CyDelay(50);
    PWM_2_WriteCompare(period - 20);
    PWM_1_WriteCompare(20);
    CyDelay(50);
}

static void doSomething() {
    uint8 led_1 = LED1_Read();  // Front sensor
    uint8 led_2 = LED2_Read();  // Back left sensor
    uint8 led_3 = LED3_Read();  // Back right sensor
    uint8 led_4 = LED4_Read();  // Front right sensor
    uint8 led_5 = LED5_Read();  // Front left sensor

    if (led_1 == 1) { // Front sensor is off the line
        if (offLineCount < 15) {
            oneSensorCorrect();
        } else {
            goForwardSlow();
            CyDelay(12);
            
            if (led_5 == 0) { //Front left on line (Junction going left)
                turnLeft();
            } else if (led_4 == 0) { //Front right on line (Junction going right)
                turnRight();
            } else {
                stopMoving();
            }
        }
        offLineCount++; // Count to know how long front sensor has been off for
    } else { // Front sensor is on the line
        oneSensorForward();
        offLineCount = 0; // Reset the off-line counter
    }

}


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
        CyDelay(5);
    }
}

/* [] END OF FILE */
