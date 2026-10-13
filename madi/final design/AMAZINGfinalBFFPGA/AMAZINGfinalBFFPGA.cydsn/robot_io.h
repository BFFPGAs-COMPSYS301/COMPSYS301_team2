#ifndef ROBOT_IO_H
#define ROBOT_IO_H
#include <stdint.h>
#include <stdbool.h>
typedef struct { bool fc, fl, fr, rl, rr; } Sensors;
typedef struct { int32_t left, right; } EncoderPair;
Sensors IO_Sensors(void);
/* Returns false if both independent encoders are not available. */
bool IO_Encoders(EncoderPair *result);
void IO_Stop(void);
void IO_Forward(void);
void IO_SpinLeft(void);
void IO_SpinRight(void);
void IO_Init(void);
#endif
