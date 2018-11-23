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

void operatorControl() {
    unsigned long prevWakeupTime = millis();
    while (1) {
        get_joystick_all(&joystick);
        // printf("%f %f %f %f\n", joystick.lx.value, joystick.ly.value, joystick.rx.value, joystick.ry.value);
        // printf("%d %d %d %d\n", joystickGetAnalog(1, 1),  joystickGetAnalog(1, 2),  joystickGetAnalog(1, 3),
        // joystickGetAnalog(1, 4));
        // printf("%f %f %f %f %f %f %f %f %f %f\n", joystick.lx.value, joystick.ly.value, joystick.rx.value, joystick.ry.value,
        //       joystick.ld4.valueX, joystick.ld4.valueY, joystick.rd4.valueX, joystick.rd4.valueY, joystick.ld2.valueY,
        //       joystick.rd2.valueY);
        write_motor_drive(&motorDrive, joystick.ry.value, joystick.rx.value);
        write_motor_rack(&motorRack, joystick.ld4.valueY);
        write_motor_arm(&motorArm, joystick.ly.value);
        set_pneumatics(&pneuGrip, -joystick.ld2.valueY);
        set_pneumatics(&pneuLift, -joystick.rd2.valueY);

        if (joystick.rd4.valueX != 0) {
            // write_motor_arm(&motorArm, 1);
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
        }

        write_pneumatics(&pneuGrip);
        write_pneumatics(&pneuLift);
        taskDelayUntil(&prevWakeupTime, 20);
    }
}
