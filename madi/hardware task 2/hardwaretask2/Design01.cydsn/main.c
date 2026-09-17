#include "project.h"
#include <stdio.h>

volatile uint8 speedReady = 0u;
volatile int32 speedL = 0;
volatile int32 speedR = 0;

#define MOTOR_PWM_PERIOD 91
#define MOTOR_MIDPOINT 45


static void MotorL_Forward() {
  PWM_1_WriteCompare(5);
}

static void MotorR_Forward() {
    PWM_2_WriteCompare(5);
}

static void MotorL_Back() {
  PWM_1_WriteCompare(85);
}

static void MotorR_Back() {
    PWM_2_WriteCompare(85);
}

static void turnLeft() {
    MotorL_Back();
    MotorR_Forward();
}    

static void turnRight() {
    MotorR_Back();
    MotorL_Forward();
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

CY_ISR(MyISR)
{
    char usbText[20];
    int32 countL;
    int32 countR;

    countL = QuadDec_1_GetCounter();
    QuadDec_1_SetCounter(0);

    speedL = countL * 1000;
    
    countR = QuadDec_2_GetCounter();
    QuadDec_2_SetCounter(0);

    speedR = countR * 1000;
    
    speedReady = 1u;
    speedReady = 0u;

    sprintf(usbText, "%ld,%ld\r\n", (long)speedL,(long)speedR);

    while (USBUART_1_CDCIsReady() == 0u)
    {
    }

    USBUART_1_PutString(usbText);

    Timer_1_ReadStatusRegister();
}

int main(void)
{
    

    CyGlobalIntEnable;

    Clock_PWM_Start();
    Clock_1_Start();
    PWM_1_Start();
    PWM_2_Start();
    QuadDec_1_Start();
    QuadDec_2_Start();
    goBack();

    USBUART_1_Start(0u, USBUART_1_5V_OPERATION);

    while (USBUART_1_GetConfiguration() == 0u)
    {
    }

    USBUART_1_CDC_Init();

    ISR_QUAD_StartEx(MyISR);
    Timer_1_Start();

    for (;;)
    {
        if (speedReady == 1u)
        {
            
        }
        CyDelay(250);
    }
}