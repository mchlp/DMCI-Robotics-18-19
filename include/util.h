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

struct Joystick {
    unsigned char number;
    bool enabled[4];
    double values[4];
};

static inline double clamp(double val, double min, double max) { return val < min ? min : (val > max ? max : val); }

static inline void write_motor(struct Motor *motor, double value) {
    if (motor->channel == 0) {
        return;
    }
    double output = clamp(motor->mul * value + motor->off, motor->min, motor->max);
    motorSet(motor->channel, clamp(output * MAX_ABS_MOTOR, -MAX_ABS_MOTOR, MAX_ABS_MOTOR));
}

static inline int get_joystick_all(struct Joystick *joystick) {
    for (int i = 0; i < 4; i++) {
        if (joystick->enabled[i]) {
            joystick->values[i] = get_joystick_analog(joystick->number, i);
        }
    }
}

static inline int get_joystick_analog(unsigned char joystick, unsigned char axis) {
    return joystickGetAnalog(joystick, axis) / MAX_ABS_JOYSTICK_ANALOG;
}

#endif