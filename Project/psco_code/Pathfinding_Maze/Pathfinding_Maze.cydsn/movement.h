#ifndef MOVEMENT

#include <stdint.h>
    
#include <stdio.h>
#include <stdbool.h>
    
    #define FORWARD_COMPARE 23
    #define period 90
    
    void MotorL_Forward(void);
    void MotorR_Forward(void);
    
    void MoveForwardOneCell(void);
    void TurnLeft(void);
    void TurnRight(void);
    
    void CyDelay();
    
#endif