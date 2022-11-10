// based on:
// https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/examples/servo/servo.ino

// #define FASTLED_ALLOW_INTERRUPTS 0
// #define FASTLED_INTERRUPT_RETRY_COUNT 0
#include <FastLED.h>

#include <Adafruit_PWMServoDriver.h>

#include "configuration.h"

#include <MathUtils.h>
#include <LedAnimations.h>
#include <LedCartesianCoordinates.h>
#include <ServoAnimations.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

CRGB leds[LED_COUNT];
uint8 led_animations_index = 0;
uint8 servo_animations_index = 0;
unsigned long last_millis = 0;

void setup() {
  // Serial.begin(115200);

  FastLED.addLeds<LED_TYPE, LEDS_DATA_PIN, COLOR_ORDER>(leds, LED_COUNT);
  FastLED.setBrightness(BRIGHTNESS);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  // delay(10);
}

void count(uint8_t i, unsigned long t){
  if ((int)(t / 100) % 50 == i) {
    leds[i].setHSV(255, 255, 255);
  }
}

void loop_leds(){
  FastLED.clear();
  unsigned long t = millis();
  // if (t % 2 != 0) return;
  unsigned long delta = t - last_millis;
  for(uint8 i = 0; i<LED_COUNT; i++){
    LED_ANIMATIONS[led_animations_index](leds, i, t, delta);
  }
  FastLED.show();
}

void loop_servos(){
  unsigned long t = millis();
  // if (t % 5 != 0) return;
  unsigned long delta = t - last_millis;
  for(uint8 i = 0; i<SERVO_COUNT; i++){
    SERVO_ANIMATIONS[servo_animations_index](pwm, i, t, delta);
  }
}

void simulate_button(){
  unsigned long t = millis();
  uint16 period = 7000;

  if(t > last_millis + period){
    led_animations_index = led_animations_index % LED_ANIMATIONS.size();
    servo_animations_index = servo_animations_index % SERVO_ANIMATIONS.size();
    last_millis = t;
  }
}

int servonum = 0;
int pulse_delta = 100;
void loop() {
  simulate_button();
  loop_servos();
  loop_leds();

  // for (uint16 pulselen = 103.0f; pulselen < 512.0f; pulselen += pulse_delta) {
  //   pwm.setPWM(servonum, 0, pulselen);
  //   Serial.println(pulselen);
  // }
  // pwm.setPWM(servonum, 0, 103);
  // pwm.setPWM(servonum, 0, 203);
  // pwm.setPWM(servonum, 0, 303);
  // pwm.setPWM(servonum, 0, 403);

  // pwm.setPWM(servonum, 0, 510);

  // delay(500);
  // for (uint16 pulselen = 512.0f; pulselen > 103.0f; pulselen -= pulse_delta) {
  //   pwm.setPWM(servonum, 0, pulselen);
  // }
  // pwm.setPWM(servonum, 0, 512);

  // pwm.setPWM(servonum, 0, 103);

  // delay(500);

  // servonum++;
  // if (servonum > SERVO_COUNT - 1) servonum = 0;
}
