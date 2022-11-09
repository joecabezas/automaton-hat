#ifndef LED_ANIMATIONS_H
#define LED_ANIMATIONS_H

#include "c_types.h"
#include <FastLED.h>

void swipe_x(CRGB* leds, uint8 i, unsigned long t, unsigned long delta);
void swipe_y(CRGB* leds, uint8 i, unsigned long t, unsigned long delta);
void wave_y(CRGB* leds, uint8 i, unsigned long t, unsigned long delta);
void sparks(CRGB* leds, uint8 i, unsigned long t, unsigned long delta);

extern std::vector<void (*)(CRGB*, uint8, unsigned long t, unsigned long delta)> LED_ANIMATIONS;

#endif
