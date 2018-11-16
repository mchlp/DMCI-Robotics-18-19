/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
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

unsigned char channel;
double off;
double min;
double max;
double mul;

static struct MotorDrive motorDrive = {{5, 0, -1, 1, 1}, {2, 0, -1, 1, -1}, {4, 0, -1, 1, 1}, {3, 0, -1, 1, -1}};
static struct MotorRack motorRack = {{6, 0, -1, 1, 1}, {7, 0, -1, 1, 1}};
static struct MotorArm motorArm = {{8, 0, -1, 1, 1}, {9, 0, -1, 1, -1}};
static struct Joystick joystick = {1, {4, 0}, {3, 0}, {1, 0}, {2, 0}, {7, 0, 0}, {8, 0, 0}, {5, 0, 0}, {6, 0, 0}};
static struct Pneumatics pneuGrip = {1, false};
static struct Pneumatics pneuLift = {2, false};

void operatorControl() {
    unsigned long prevWakeupTime = millis();

    pinMode(pneuGrip.pin, OUTPUT);
    pinMode(pneuLift.pin, OUTPUT);

    while (1) {
        get_joystick_all(&joystick);
        // printf("%f %f %f %f\n", joystick.lx.value, joystick.ly.value, joystick.rx.value, joystick.ry.value);
        // printf("%d %d %d %d\n", joystickGetAnalog(1, 1),  joystickGetAnalog(1, 2),  joystickGetAnalog(1, 3),
        // joystickGetAnalog(1, 4));
        //printf("%f %f %f %f %f %f %f %f %f %f\n", joystick.lx.value, joystick.ly.value, joystick.rx.value, joystick.ry.value,
        //       joystick.ld4.valueX, joystick.ld4.valueY, joystick.rd4.valueX, joystick.rd4.valueY, joystick.ld2.valueY,
        //       joystick.rd2.valueY);
        write_motor_drive(&motorDrive, joystick.ry.value, joystick.rx.value);
        write_motor_rack(&motorRack, joystick.rd2.valueY);
        write_motor_arm(&motorArm, joystick.ld2.valueY);
        set_pneumatics(&pneuGrip, joystick.ld4.valueX);
        set_pneumatics(&pneuLift, joystick.ld4.valueY);
        write_pneumatics(&pneuGrip);
        write_pneumatics(&pneuLift);
        printf("%d\n", pneuLift.opened);
        taskDelayUntil(&prevWakeupTime, 20);
    }
}
