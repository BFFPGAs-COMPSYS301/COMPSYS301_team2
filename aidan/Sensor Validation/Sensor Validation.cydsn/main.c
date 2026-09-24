#include "project.h"
#include <stdio.h>

#define FORWARD_COMPARE 15
#define period 90

uint16 overCount = 0;

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

static void doSomething() {
    uint8 led_1 = LED1_Read();  // Front sensor
    uint8 led_2 = LED2_Read();  // Back left sensor
    uint8 led_3 = LED3_Read();  // Back right sensor
    uint8 led_4 = LED4_Read();  // Front right sensor
    uint8 led_5 = LED5_Read();  // Front left sensor
    
    if (led_1 == 1) {
        oneSensorCorrect();
    } else {
        oneSensorForward();
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

    for(;;)
    {
        doSomething();
        CyDelay(5);
    }
}

/* [] END OF FILE */
