/*
    Each encoder count is ~0.9mm
    Each cell is ~18.5cm
    
    one cell = 205 ecoder counts
*/

#include "astar.h"

#define CELL_LENGTH 205

uint8_t travelled = 0;

Command nextCommand;

void LED_1_Write();
void LED_2_Write();
void LED_3_Write();

static void MoveForwardOneCell(Command nextCommand) {
    LED_1_Write(1);
    if (nextCommand == CMD_FORWARD) {
        while (travelled < CELL_LENGTH) {
            PWM_1_WriteCompare(20);
            PWM_2_WriteCompare(20);
        }
    }
    LED_1_Write(0);
    PWM_1_WriteCompare(45);
    PWM_2_WriteCompare(45);
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