#ifndef _LEDS_h
#define _LEDS_h
#include "Globals.h"
#include <Adafruit_NeoPixel.h>

// eg: extern String variable; will make a .cpp file's variable public
// eg: extern void thing(); will make a .cpp file's function public

extern byte BodyLEDSCount; 
extern byte groundLightsStatus;
extern byte groundLightsRGB[3];

extern Adafruit_NeoPixel BodyLEDS;

extern void LEDSetup();

#endif
