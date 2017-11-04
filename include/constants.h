/*  Directional Rules:
 * 	Motors:
 * 	 1. Holding the motor screw holes up
 * 	 2. Axle away from you
 * 	  A. Clockwise is positive
 * 	  B. Counter Clockwise is negative
 * 	Cortex:
 * 	 1. Ports side up
 * 	 2. Power facing towards you
 * 	 3. USB port facing away from you
 * 	  A. Forward is pointing in the same direction as the USB port
 *
 * Build Rules:
 *  1. Connect same color to wires
 *  2. On two size ports, the black is on the left
 *  3. On three size ports, the black is on the right
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// Set Teamname string
#define TEAMNAME "2505"

// Robot Constants
#define SPD_BASE_UP 127
#define SPD_BASE_DOWN -64
#define SPD_LIFT -127
#define SPD_CLAW 127

// Joystick Constants
#define JOYSTICK_PRIMARY 1
#define JOYSTICK_PARTNER 2
#define JOY_RX 1
#define JOY_RY 2
#define JOY_LX 4
#define JOY_LY 3
#define JOY_LBUM 5
#define JOY_RBUM 6
#define JOY_LPAD 7
#define JOY_RPAD 8

// Motor Constants
#define MC_WHEEL_L 2
#define MC_WHEEL_R 9
#define MC_BASE_L 3
#define MC_BASE_R 8
#define MC_LIFT_L_1 4
#define MC_LIFT_L_2 5
#define MC_LIFT_R_1 6
#define MC_LIFT_R_2 7
#define MC_CLAW_1 1
#define MC_CLAW_2 10

#endif // CONSTANTS_H_
