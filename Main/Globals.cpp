#include "Globals.h"

/* Debounce waits */
unsigned long groundLightsWait = millis();
unsigned long ServoSleepWait = millis();
unsigned long tSwitchWait = millis();
unsigned long UtilityArmTopWait = millis();
unsigned long UtilityArmBottomWait = millis();
unsigned long largeOneFrontDoorWait = millis();
unsigned long largeTwoFrontDoorWait = millis();
unsigned long largeBackDoorsWait = millis();
unsigned long chargebayFrontDoorWait = millis();
unsigned long smallTallFrontDoorWait = millis();
unsigned long dataPanelFrontDoorWait = millis();
unsigned long AudioWait = millis();
unsigned long VolumeWait = millis();
unsigned long BeepWait = millis();
unsigned long DomeWait = millis();
unsigned long RadioWait = millis();
unsigned long ButtonWait = millis();
unsigned long ActionWait = millis();

/* Remote button status */
byte button1State = 0;
byte button2State = 0;
byte button3State = 0;
byte button4State = 0;

byte tSwitch1State = 0;
byte tSwitch2State = 0;

/* Door & Arm Status (0 = close | 1 = open) */
byte UtilityArmStatus[2] = {0, 0};

byte leftFrontLargeDoorStatus = 0;
byte rightFrontLargeDoorStatus = 0;

byte dataFrontDoorStatus = 0;
byte chargebayFrontDoorStatus = 0;
byte verticalSwitchFrontDoorStatus = 0;

byte backLargeDoorsStatus = 0;

byte leftArmRotateStatus = 0;
byte leftArmActuateStatus = 0;

byte rightArmRotateStatus = 0;
byte rightArmActuateStatus = 0;
