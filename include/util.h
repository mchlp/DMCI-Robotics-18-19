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

struct PID {
    double setMin;
    double setMax;
    double pGain;
    double iGain;
    double dGain;
    double errSum;
    double errLast;
    double setPoint;
};

struct MotorControlWithPoten {
    unsigned char potenChannel;
    struct Motor motor;
    struct PID pid;
};

struct Pneumatics {
    unsigned char pin;
    bool opened;
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

struct JoystickInputDigital {
    unsigned char group;
    double valueX;
    double valueY;
};

struct Joystick {
    unsigned char number;
    struct JoystickInputAnalog lx;
    struct JoystickInputAnalog ly;
    struct JoystickInputAnalog rx;
    struct JoystickInputAnalog ry;
    struct JoystickInputDigital ld4;
    struct JoystickInputDigital rd4;
    struct JoystickInputDigital ld2;
    struct JoystickInputDigital rd2;
};

static inline double clamp(double val, double min, double max) { return val < min ? min : (val > max ? max : val); }

static inline void set_pid(struct PID *pid, double value) { pid->setPoint = value; }

static inline double get_new_value_pid(struct PID *pid, double curValue) {
    double error = pid->setPoint - curValue;
    pid->errSum += error;
    double errDelta = error - pid->errLast;
    pid->errLast = error;
    double correction = (error * pid->pGain + pid->errSum * pid->iGain + errDelta * pid->dGain);
    printf("%f\n", correction);
    return correction;
}

static inline void update_pid(struct PID *pid, double value) {}

static inline void write_motor(struct Motor *motor, double value) {
    if (motor->channel == 0) {
        return;
    }
    double output = clamp(motor->mul * value + motor->off, motor->min, motor->max);
    motorSet(motor->channel, clamp(output * MAX_ABS_MOTOR, -MAX_ABS_MOTOR, MAX_ABS_MOTOR));
}

static inline void set_motor_control_with_poten(struct MotorControlWithPoten *motorControlWithPoten, double change) {
    set_pid(&motorControlWithPoten->pid, clamp(motorControlWithPoten->pid.setPoint + change, motorControlWithPoten->pid.setMin,
                                               motorControlWithPoten->pid.setMax));
}

static inline void refresh_motor_control_with_poten(struct MotorControlWithPoten *motorControlWithPoten) {
    write_motor(&motorControlWithPoten->motor, get_new_value_pid(&motorControlWithPoten->pid, 0));
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

static inline void write_pneumatics(struct Pneumatics *pneumatics) {
    if (pneumatics->opened) {
        digitalWrite(pneumatics->pin, HIGH);
    } else {
        digitalWrite(pneumatics->pin, LOW);
    }
}

static inline void set_pneumatics(struct Pneumatics *pneumatics, double value) {
    if (value > 0) {
        pneumatics->opened = true;
    } else if (value < 0) {
        pneumatics->opened = false;
    }
}

static inline int get_joystick_analog(struct JoystickInputAnalog *inputAnalog, unsigned char joystick) {
    inputAnalog->value = joystickGetAnalog(joystick, inputAnalog->axis) / MAX_ABS_JOYSTICK_ANALOG;
}

static inline int get_joystick_digital(struct JoystickInputDigital *inputDigital, unsigned char joystick) {
    int left = joystickGetDigital(joystick, inputDigital->group, JOY_LEFT) ? -1 : 0;
    int right = joystickGetDigital(joystick, inputDigital->group, JOY_RIGHT) ? 1 : 0;
    inputDigital->valueX = left + right;

    int up = joystickGetDigital(joystick, inputDigital->group, JOY_DOWN) ? -1 : 0;
    int down = joystickGetDigital(joystick, inputDigital->group, JOY_UP) ? 1 : 0;
    inputDigital->valueY = up + down;
}

static inline void get_joystick_all(struct Joystick *joystick) {
    get_joystick_analog(&(joystick->lx), joystick->number);
    get_joystick_analog(&(joystick->ly), joystick->number);
    get_joystick_analog(&(joystick->rx), joystick->number);
    get_joystick_analog(&(joystick->ry), joystick->number);
    get_joystick_digital(&joystick->ld4, joystick->number);
    get_joystick_digital(&joystick->rd4, joystick->number);
    get_joystick_digital(&joystick->ld2, joystick->number);
    get_joystick_digital(&joystick->rd2, joystick->number);
}

#endif