#include "MotorControls.h"


Servo srvFrontRightBrake = {
	GPIOA,
	0,
	&PWMD5,
	0,
	600,
	2400
};

Servo srvFrontLeftBrake = {
	GPIOA,
	1,
	&PWMD5,
	1,
	600,
	2400
};

Servo srvRearRightBrake = {
	GPIOA,
	2,
	&PWMD5,
	2,
	600,
	2400
};

Servo srvRearLeftBrake = {
	GPIOA,
	3,
	&PWMD5,
	3,
	600,
	2400
};

void initBrakeServos()
{

	  /*
	   * Initializes Servos
	   */

	  servoInit(&srvFrontLeftBrake);
	  servoInit(&srvFrontRightBrake);
	  servoInit(&srvRearLeftBrake);
	  servoInit(&srvRearRightBrake);
}

void initMotors()
{
	initBrakeServos();
}
