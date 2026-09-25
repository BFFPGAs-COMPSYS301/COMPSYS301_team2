#include "project.h"
#include <stdio.h>
#include <stdbool.h>

#define FORWARD_COMPARE 23
#define period 90

uint16 offLineCount = 0;
uint16 onLineCount = 0;
uint8 turnsComplete = 0;
bool turnDetected = 0;
bool onLine = 0;

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
    onLineCount = 0;
    onLine = 0;
    turnDetected = 1;
    goForwardSlow();
    CyDelay(142);
    stopMoving();
    while (LED1_Read() == 1) {
        PWM_1_WriteCompare(period - 25);
        PWM_2_WriteCompare(25);
    }
    goForwardSlow();
    CyDelay(10);
    PWM_1_WriteCompare(25);
    PWM_2_WriteCompare(period - 25);
    CyDelay(50);
}

static void turnRight() {
    onLineCount = 0;
    onLine = 0;
    turnDetected = 1;
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
        if (turnsComplete == 11 && offLineCount > 20) {
            while(1) {
                stopMoving();
            }
        }
        if (offLineCount < 15) {
            oneSensorCorrect();
        } else if (offLineCount > 80) {
            while (1) {
                stopMoving();
            }
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
        if (onLineCount > 100 && onLine == 0) {
            turnDetected = 0;
        }
        if (led_2 == 0 || led_3 == 0) {
            onLine = 1;
        }
        onLineCount++;
    }

    if (turnDetected == 1 && onLine == 1) {
        turnsComplete++;
        turnDetected = 0;
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