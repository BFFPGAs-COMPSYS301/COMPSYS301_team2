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
#include <stdio.h>

#define FORWARD_COMPARE 20
#define period 90

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

static void turnLeft() {
    MotorL_Back();
    MotorR_Forward();
}    

static void turnRight() {
    MotorR_Back();
    MotorL_Forward();
}    

static void correctLeft() {
    PWM_2_WriteCompare(FORWARD_COMPARE - 2);
    PWM_1_WriteCompare(90 - FORWARD_COMPARE + 2);
    
}    

static void correctRight() {
    PWM_1_WriteCompare(FORWARD_COMPARE - 2);
    PWM_2_WriteCompare(90 - FORWARD_COMPARE + 2);
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

static void doSomething() {
    uint8 led_1 = LED1_Read();
    uint8 led_2 = LED2_Read();
    uint8 led_3 = LED3_Read();
    uint8 led_4 = LED4_Read();
    uint8 led_5 = LED5_Read();
    
    if (led_1 == 0 && led_2 == 1 && led_3 == 1) {
        goBack();  
    }
    
    else if (led_1 == 0 && led_2 == 1 && led_3 == 0) {
            correctLeft();
    }
    
    else if (led_1 == 0 && led_2 == 0 && led_3 == 1) {
            correctRight();
    }
    
    else {
        stopMoving();
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