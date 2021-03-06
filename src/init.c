/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
    pinMode(pneuGrip.pin, OUTPUT);
    pinMode(pneuLift.pin, OUTPUT);
    pinMode(motorControlArm.pidPoten.poten.port, INPUT_ANALOG);
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
}

/**
 * Initialize variables from 'util.h'
 **/
struct MotorDrive motorDrive = {
    {5, 0, -1, 1, 1},
    {2, 0, -1, 1, -1},
    {4, 0, -1, 1, 1},
    {3, 0, -1, 1, -1}};
struct MotorRack motorRack = {
    {6, 0, -1, 1, 1},
    {7, 0, -1, 1, 1}};
struct MotorControlArm motorControlArm = {
    {{1, 0},
     {1, 0, 3500, 1, 0, 0, 0, 0, 0, 0}},
    {8, 0, -1, 1, 1},
    {9, 0, -1, 1, 1}};
struct Joystick joystick = {
    1,
    {4, 0},
    {3, 0},
    {1, 0},
    {2, 0},
    {7, 0, 0},
    {8, 0, 0},
    {5, 0, 0},
    {6, 0, 0}};
struct Pneumatics pneuGrip = {
    1,
    false};
struct Pneumatics pneuLift = {
    2,
    false};
