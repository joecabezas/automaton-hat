// based on:
// https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/examples/servo/servo.ino

#include <Adafruit_PWMServoDriver.h>
#include <FastLED.h>

#include "configuration.h"

#include <MathUtils.h>
#include <LedAnimations.h>
#include <LedCartesianCoordinates.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

CRGB leds[LED_COUNT];
uint8 animation_index = 0;
unsigned long last_millis = 0;

void setup() {
  Serial.begin(115200);

  FastLED.addLeds<LED_TYPE, LEDS_DATA_PIN, COLOR_ORDER>(leds, LED_COUNT);
  FastLED.setBrightness(BRIGHTNESS);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10);
}

void count(uint8_t i, unsigned long t){
  if ((int)(t / 100) % 50 == i) {
    leds[i].setHSV(255, 255, 255);
  }
}

void loop_leds(){
  FastLED.clear();
  unsigned long t = millis();
  unsigned long delta = t - last_millis;
  for(uint8 i = 0; i<LED_COUNT; i++){
    LED_ANIMATIONS[animation_index](leds, i, t, delta);
  }
  FastLED.show();
}

void simulate_button(){
  unsigned long t = millis();
  uint16 period = 7000;

  if(t > last_millis + period){
    animation_index = animation_index % LED_ANIMATIONS.size();
    last_millis = t;
  }
}

void loop() {
  simulate_button();
  loop_leds();

  // for (uint16 pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
  //   pwm.setPWM(servonum, 0, pulselen);
  // }

  // delay(500);
  // for (uint16 pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
  //   pwm.setPWM(servonum, 0, pulselen);
  // }

  // delay(500);

  // servonum++;
  // if (servonum > SERVO_COUNT - 1) servonum = 0;
}
