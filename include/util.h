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
    struct Motor mml;
    struct Motor mmr;
    struct Motor mbl;
    struct Motor mbr;
};

struct JoystickInputAnalog {
    unsigned char axis;
    bool enabled;
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

static inline void write_motor_all(struct MotorDrive *motorDrive, double forward, double right) {
    write_motor(&motorDrive->mfl, forward+right);
    write_motor(&motorDrive->mfr, forward-right);
    write_motor(&motorDrive->mml, forward+right);
    write_motor(&motorDrive->mmr, forward-right);
    write_motor(&motorDrive->mbl, forward+right);
    write_motor(&motorDrive->mbr, forward-right);
}

static inline void write_motor(struct Motor *motor, double value) {
    if (motor->channel == 0) {
        return;
    }
    double output = clamp(motor->mul * value + motor->off, motor->min, motor->max);
    motorSet(motor->channel, clamp(output * MAX_ABS_MOTOR, -MAX_ABS_MOTOR, MAX_ABS_MOTOR));
}

static inline void get_joystick_all(struct Joystick *joystick) {
    get_joystick_analog(&joystick->lx, joystick->number);
    get_joystick_analog(&joystick->ly, joystick->number);
    get_joystick_analog(&joystick->rx, joystick->number);
    get_joystick_analog(&joystick->ly, joystick->number);
}

static inline int get_joystick_analog(struct JoystickInputAnalog *inputAnalog, unsigned char joystick) {
    if (inputAnalog->enabled) {
        inputAnalog->value = joystickGetAnalog(inputAnalog->axis, joystick) / MAX_ABS_JOYSTICK_ANALOG;
    }
}

#endif