
#ifndef ROBOT_CONTROL_H
#define ROBOT_CONTROL_H

#include "project.h"
#include <stdbool.h>

/* Initialize controller variables */
void RobotControl_Init(void);

/* Execute one iteration of benchmark navigation */
void RobotControl_Update(void);

/* Motor control functions */
void Robot_Stop(void);
void Robot_Forward(void);
void Robot_ForwardSlow(void);

/* Line following */
void Robot_LineForward(void);
void Robot_LineCorrect(void);

/* Corner turning */
void Robot_TurnLeft(void);
void Robot_TurnRight(void);

#endif
