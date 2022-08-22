#ifndef _GLOBALS_h
#define _GLOBALS_h
#include "Globals.h"

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>

// This file is used as a single location to include all needed libs and variables


// eg: extern String variable; will make a .cpp file's variable public
// eg: extern void thing(); will make a .cpp file's function public

extern unsigned long groundLightsWait; 
extern unsigned long ServoSleepWait;
extern unsigned long tSwitchWait;
extern unsigned long UtilityArmTopWait;
extern unsigned long UtilityArmBottomWait;
extern unsigned long largeOneFrontDoorWait;
extern unsigned long largeTwoFrontDoorWait;
extern unsigned long largeBackDoorsWait;
extern unsigned long chargebayFrontDoorWait;
extern unsigned long smallTallFrontDoorWait;
extern unsigned long dataPanelFrontDoorWait;
extern unsigned long AudioWait;
extern unsigned long VolumeWait;
extern unsigned long BeepWait;
extern unsigned long DomeWait;
extern unsigned long RadioWait;
extern unsigned long ButtonWait;
extern unsigned long ActionWait;

/* Remote button status */
extern byte button1State;
extern byte button2State;
extern byte button3State;
extern byte button4State;

extern byte tSwitch1State;
extern byte tSwitch2State;

/* Door & Arm Status (0 = close | 1 = open) */
extern byte UtilityArmStatus[2];

extern byte leftFrontLargeDoorStatus;
extern byte rightFrontLargeDoorStatus;

extern byte dataFrontDoorStatus;
extern byte chargebayFrontDoorStatus;
extern byte verticalSwitchFrontDoorStatus;

extern byte backLargeDoorsStatus;

extern byte leftArmRotateStatus;
extern byte leftArmActuateStatus;

extern byte rightArmRotateStatus;
extern byte rightArmActuateStatus;

#endif
