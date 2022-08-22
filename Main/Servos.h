#ifndef _SERVOS_h
#define _SERVOS_h
#include "Globals.h"
#include <Adafruit_PWMServoDriver.h>

// eg: extern String variable; will make a .cpp file's variable public
// eg: extern void thing(); will make a .cpp file's function public

extern Adafruit_PWMServoDriver BodyServos;
extern Adafruit_PWMServoDriver DomeServos;

extern void ServosSetup();

#endif
