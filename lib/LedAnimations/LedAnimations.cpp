#include "c_types.h"
#include <FastLED.h>

#include <LedAnimations.h>
#include <LedCartesianCoordinates.h>
#include <MathUtils.h>

uint8 MAX_LED_X = 110;
uint8 MAX_LED_Y = 120;

std::vector<void (*)(CRGB*, uint8, unsigned long t, unsigned long delta)> LED_ANIMATIONS = {
  sparks,
  // wave_y,
  // swipe_y,
  // swipe_x,
};

void swipe_x(CRGB* leds, uint8 i, unsigned long t, unsigned long delta){
  uint16 period = 1500;
  uint16 cycle = t % period;
  uint8 offset = 20;
  float x = LED_CARTESIAN_COORDINATES[i][0];
  float pos = map_generic((float)cycle, 0.0f, (float)period, (float)- MAX_LED_X, (float)MAX_LED_X);
  pos *= 1.05f;
  if(x < pos + offset && x > pos - offset){
    int v = t * 0.1;
    leds[i].setHSV(v%255, 255, 255);
  }
}

void swipe_y(CRGB* leds, uint8 i, unsigned long t, unsigned long delta){
  uint16 period = 1000;
  uint16 cycle = t % period;
  uint8 offset = 20;
  float y = LED_CARTESIAN_COORDINATES[i][1];
  float pos = map_generic((float)cycle, 0.0f, (float)period, (float)MAX_LED_Y, (float)-MAX_LED_Y);
  pos *= 1.25f;
  if(y < pos + offset && y > pos - offset){
    int v = t * 0.1;
    leds[i].setHSV(v%255, 255, 255);
  }
}

void wave_y(CRGB* leds, uint8 i, unsigned long t, unsigned long delta){
  float x = LED_CARTESIAN_COORDINATES[i][0];
  float y = LED_CARTESIAN_COORDINATES[i][1];
  float xx = x*x;
  float yy = pow(y - 130, 2);
  float amplitude = 255;
  float out = amplitude/2 + amplitude/2 * sin(t * 0.0025 - sqrt((xx+yy)/3000));
  leds[i].setHSV(int(t*0.05)%255, 255, out);
}

void sparksv1(CRGB* leds, uint8 i, unsigned long t, unsigned long delta){
  float x = LED_CARTESIAN_COORDINATES[i][0];
  float y = LED_CARTESIAN_COORDINATES[i][1];
  float xx = x*x;
  float yy = pow(y - 130, 2);
  float amplitude = 255;
  float value = amplitude * sin(delta * 0.01 - sqrt(xx+yy));
  float decay = pow(1 - delta / 3000.0f, 3);
  decay = constrain(decay, 0.0f, 1.0f);
  if (i == 0) Serial.println(value * decay);
  leds[i].setHSV(45, 50, value * decay);
}

void sparks(CRGB* leds, uint8 i, unsigned long t, unsigned long delta){
  float decay = pow(1.0f - (delta - 2000.0f) / 3000.0f, 3.0f);
  decay = constrain(decay, 0.0f, 1.0f);
  float value = random8() < 10 * decay ? 255 : 0;
  leds[i].setHSV(45, 50, value);
}