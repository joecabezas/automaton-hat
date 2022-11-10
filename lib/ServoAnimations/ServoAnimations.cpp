#include <ServoAnimations.h>

uint16 SERVOMIN = 103; // 0.5ms
uint16 SERVOMAX = 510; // 2.5ms
float MAX_FACTOR = 1.0f;
float FULL_TIME = 330.0f; // in millis: 0.11s/60deg => 0.33s/180deg

extern std::vector<void (*)(Adafruit_PWMServoDriver, uint8, unsigned long t, unsigned long delta)> SERVO_ANIMATIONS = {
    test,
};

void setPWM(Adafruit_PWMServoDriver pwm, uint8 i, float factor){
  float value = map_generic(factor, 0.0f, 1.0f, SERVOMIN, SERVOMAX);
//   Serial.println(value);
  pwm.setPWM(i, 0, (uint16_t)value);
}



void test(Adafruit_PWMServoDriver pwm, uint8 i, unsigned long t, unsigned long delta) {
  if (i < 0 || i > 14 ) return;
  // if(t%15 != i) return;
  float factor = MAX_FACTOR * (0.5f + 0.5f * sin(t / 400.0f));
  if (i > 7) factor = 1.0f - factor;
  setPWM(pwm, i, factor);

  // setPWM(pwm, i, 0);
  // delay(500);
  // setPWM(pwm, i, 1);
  // delay(500);
}