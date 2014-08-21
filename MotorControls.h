#ifndef __MOTOR_CONTROLS_H__
#define __MOTOR_CONTROLS_H__
#include "servo.h"

//High-level functions
void initMotors();


//Brake Servos
extern Servo srvFrontRightBrake;
extern Servo srvFrontLeftBrake;
extern Servo srvRearRightBrake;
extern Servo srvRearLeftBrake;
void initBrakeServos();

//Motor Control


#endif
