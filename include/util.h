#ifndef util_c
#define util_c

#include <main.h>

#define MAX_ABS_MOTOR 127
#define MAX_ABS_JOYSTICK_ANALOG 127.0

struct Motor {
    unsigned char channel;
    double off;
    double min;
    double max;
    double mul;
};

struct MotorDrive {
    struct Motor mfl;
    struct Motor mfr;
    struct Motor mbl;
    struct Motor mbr;
};

struct MotorRack {
    struct Motor ml;
    struct Motor mr;
};

struct MotorArm {
    struct Motor ml;
    struct Motor mr;
};

struct JoystickInputAnalog {
    unsigned char axis;
    double value;
};

struct Joystick {
    unsigned char number;
    struct JoystickInputAnalog lx;
    struct JoystickInputAnalog ly;
    struct JoystickInputAnalog rx;
    struct JoystickInputAnalog ry;
};

static inline double clamp(double val, double min, double max) { return val < min ? min : (val > max ? max : val); }

static inline void write_motor(struct Motor *motor, double value) {
    if (motor->channel == 0) {
        return;
    }
    double output = clamp(motor->mul * value + motor->off, motor->min, motor->max);
    motorSet(motor->channel, clamp(output * MAX_ABS_MOTOR, -MAX_ABS_MOTOR, MAX_ABS_MOTOR));
}

static inline void write_motor_drive(struct MotorDrive *motorDrive, double forward, double right) {
    write_motor(&motorDrive->mfl, forward + right);
    write_motor(&motorDrive->mfr, forward - right);
    write_motor(&motorDrive->mbl, forward + right);
    write_motor(&motorDrive->mbr, forward - right);
}

static inline void write_motor_rack(struct MotorRack *motorRack, double value) {
    write_motor(&motorRack->ml, value);
    write_motor(&motorRack->mr, value);
}

static inline void write_motor_arm(struct MotorArm *motorArm, double value) {
    write_motor(&motorArm->ml, value);
    write_motor(&motorArm->mr, value);
}

static inline int get_joystick_analog(struct JoystickInputAnalog *inputAnalog, unsigned char joystick) {
    inputAnalog->value = joystickGetAnalog(joystick, inputAnalog->axis) / MAX_ABS_JOYSTICK_ANALOG;
}

static inline void get_joystick_all(struct Joystick *joystick) {
    get_joystick_analog(&joystick->lx, joystick->number);
    get_joystick_analog(&joystick->ly, joystick->number);
    get_joystick_analog(&joystick->rx, joystick->number);
    get_joystick_analog(&joystick->ry, joystick->number);
}

#endif