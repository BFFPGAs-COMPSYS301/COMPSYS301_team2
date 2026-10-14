#include "movement.h"

uint16_t offLineCount = 0;
uint16_t onLineCount = 0;
uint8_t turnsComplete = 0;
bool turnDetected = 0;
bool onLine = 0;

void MotorL_Forward() {
  PWM_1_WriteCompare(FORWARD_COMPARE);
}

void MotorR_Forward() {
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

void stopMoving(){
    PWM_1_WriteCompare(45);
    PWM_2_WriteCompare(45);
}

void MoveForwardOneCell(void) {
    PWM_1_WriteCompare(FORWARD_COMPARE - 1);
    PWM_2_WriteCompare(FORWARD_COMPARE);
    stopMoving();
}

void oneSensorCorrect() {
    PWM_1_WriteCompare(period - 20);
    PWM_2_WriteCompare(20);
}

void TurnLeft(void) {
    MotorL_Back();
    MotorR_Forward();
    CyDelay(500);
    stopMoving();
}

void TurnRight(void) {
    MotorL_Forward();
    MotorR_Back();
    CyDelay(500);
    stopMoving();
}