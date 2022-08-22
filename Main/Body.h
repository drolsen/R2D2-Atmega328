#ifndef _BODY_h
#define _BODY_h
#include "Globals.h"


// eg: extern String variable; will make a .cpp file's variable public
// eg: extern void thing(); will make a .cpp file's function public

extern void ToggleCPUArm(byte state);
extern void ToggleGripperArm(byte state);
extern void ToggleUtilityArmTop(byte state);
extern void ToggleUtilityArmBottom(byte state);

extern void ToggleBodyDoor(byte servoNumber, int from, int);
#endif
