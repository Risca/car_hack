/*
    ChibiOS - Copyright (C) 2006-2014 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "carconf.h"
#include "servo.h"


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


/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
	static pwmcnt_t x = 600;
  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
	  servoSetValue(&srvFrontLeftBrake,x);
	  servoSetValue(&srvFrontRightBrake,x);
	  servoSetValue(&srvRearLeftBrake,x);
	  servoSetValue(&srvRearRightBrake,x);
	  x++;
	  if (x>2400)
	  {
		  x=600;
	  }

  }
  return 5;
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Activates the serial driver 2 using the driver default configuration.
   * PA2(TX) and PA3(RX) are routed to USART2.
   */
  sdStart(&SD2, NULL);
  palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
  palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));

  /*
   * Initializes Servos
   */

  servoInit(&srvFrontLeftBrake);
  servoInit(&srvFrontRightBrake);
  servoInit(&srvRearLeftBrake);
  servoInit(&srvRearRightBrake);
  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it just performs
   * a shell respawn upon its termination.
   */
  while (TRUE) {
    if (palReadPad(GPIOA, GPIOA_BUTTON))
      TestThread(&SD2);
    chThdSleepMilliseconds(500);
  }
  return 5;//lol
}
