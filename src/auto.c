/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {

    unsigned long prevWakeupTime = millis();
    write_motor_arm(&motorArm, 1);
    taskDelayUntil(&prevWakeupTime, 200);
    write_motor_arm(&motorArm, 0);

    write_motor_drive(&motorDrive, -0.8, 0.5);
    taskDelayUntil(&prevWakeupTime, 660);
    write_motor_drive(&motorDrive, 0, 0);

    write_motor_drive(&motorDrive, 0, 0.6);
    taskDelayUntil(&prevWakeupTime, 300);
    write_motor_drive(&motorDrive, 0, 0);

    write_motor_drive(&motorDrive, -1, 0);
    taskDelayUntil(&prevWakeupTime, 500);
    write_motor_drive(&motorDrive, 0, 0);

    write_motor_rack(&motorRack, -1);
    taskDelayUntil(&prevWakeupTime, 500);
    write_motor_rack(&motorRack, 0);

    write_motor_drive(&motorDrive, 1, 0);
    taskDelayUntil(&prevWakeupTime, 100);
    write_motor_drive(&motorDrive, 0, 0);

    write_motor_drive(&motorDrive, -1, 0);
    taskDelayUntil(&prevWakeupTime, 2000);
    write_motor_drive(&motorDrive, 0, 0);

    write_motor_rack(&motorRack, 1);
    taskDelayUntil(&prevWakeupTime, 1000);
    write_motor_rack(&motorRack, 0);

    write_motor_drive(&motorDrive, -1, 0);
    taskDelayUntil(&prevWakeupTime, 1000);
    write_motor_drive(&motorDrive, 0, 0);

    write_motor_rack(&motorRack, -1);
    taskDelayUntil(&prevWakeupTime, 500);
    write_motor_rack(&motorRack, 0);

    write_motor_drive(&motorDrive, -1, 0);
    taskDelayUntil(&prevWakeupTime, 300);
    write_motor_drive(&motorDrive, 0, 0);
    return;
}