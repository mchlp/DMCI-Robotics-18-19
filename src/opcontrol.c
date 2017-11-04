/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {

	/*
	Programming Notes:
	INVERT ON CODE, NOT THE ROBOT!
	*/

	unsigned long prevWakeupTime = millis();

	int move, rotate, baseUp, baseDown, liftUp, liftDown, clawGrab, clawRelease;
	int leftWheel, rightWheel, base, lift, claw;

	while (1) {

		// Controller Input
		rotate = joystickGetAnalog(JOYSTICK_PRIMARY, JOY_RX);
		move = joystickGetAnalog(JOYSTICK_PRIMARY, JOY_LY);
		baseDown = joystickGetDigital(JOYSTICK_PRIMARY, JOY_LBUM, JOY_UP);
		baseUp = joystickGetDigital(JOYSTICK_PRIMARY, JOY_LBUM, JOY_DOWN);
		liftUp = joystickGetDigital(JOYSTICK_PRIMARY, JOY_RBUM, JOY_UP);
		liftDown = joystickGetDigital(JOYSTICK_PRIMARY, JOY_RBUM, JOY_DOWN);
		clawGrab = joystickGetDigital(JOYSTICK_PRIMARY, JOY_RPAD, JOY_LEFT);
		clawRelease = joystickGetDigital(JOYSTICK_PRIMARY, JOY_RPAD, JOY_RIGHT);

		// Calculate Movement
		leftWheel = move + rotate;
		rightWheel = -(move - rotate);
		base = baseDown ? SPD_BASE_DOWN : baseUp ? SPD_BASE_UP : 0;
		lift = liftUp ? SPD_LIFT : liftDown ? -SPD_LIFT : 0;
		claw = clawGrab ? SPD_CLAW : clawRelease ? -SPD_CLAW : 0;

		// Motor Output
		motorSet(MC_WHEEL_L, leftWheel);
		motorSet(MC_WHEEL_R, rightWheel);
		motorSet(MC_BASE_L, base);
		motorSet(MC_BASE_R, -base);
		motorSet(MC_LIFT_L_1, lift);
		motorSet(MC_LIFT_L_2, lift);
		motorSet(MC_LIFT_R_1, -lift);
		motorSet(MC_LIFT_R_2, -lift);
		motorSet(MC_CLAW_1, claw);
		motorSet(MC_CLAW_2, claw);

		taskDelayUntil(&prevWakeupTime, 20);
	}
}
