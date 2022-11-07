// based on:
// https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/examples/servo/servo.ino

#include <Adafruit_PWMServoDriver.h>

#include "servo_cell_indexes.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  103 // 0.5ms
#define SERVOMAX  512 // 2.5ms
#define SERVO_FREQ 50
#define SERVO_COUNT 1

uint8_t servonum = 0;

void setup() {
  //Serial.begin(115200);
  //Serial.println("SETUP");

  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10);
}

void loop() {
  //Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(500);

  servonum++;
  if (servonum > SERVO_COUNT - 1) servonum = 0;
}
