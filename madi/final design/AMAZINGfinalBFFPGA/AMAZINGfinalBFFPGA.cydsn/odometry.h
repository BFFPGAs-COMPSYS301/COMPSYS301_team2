#ifndef ODOMETRY_H
#define ODOMETRY_H
#include "robot_io.h"
typedef struct { float x_mm,y_mm,theta_rad; } Pose2D;
typedef struct {
    Pose2D pose;
    EncoderPair previous;
    float leftMmPerCount,rightMmPerCount,wheelbaseMm;
    float travelledMm;
    bool ready;
} Odometry;
bool Odom_Init(Odometry *o, Pose2D start, EncoderPair initial,
               float leftMmPerCount, float rightMmPerCount, float wheelbaseMm);
void Odom_Update(Odometry *o, EncoderPair current);
#endif
