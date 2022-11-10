#ifndef SERVO_ANIMATIONS_H
#define SERVO_ANIMATIONS_H

#include "c_types.h"
#include <Adafruit_PWMServoDriver.h>
#include <MathUtils.h>

extern std::vector<void (*)(Adafruit_PWMServoDriver, uint8, unsigned long t, unsigned long delta)> SERVO_ANIMATIONS;

void setPWM(Adafruit_PWMServoDriver pwm, uint8 i, float factor);

void test(Adafruit_PWMServoDriver pwm, uint8 i, unsigned long t, unsigned long delta);

#endif

