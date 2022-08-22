#ifndef _DRIVE_h
#define _DRIVE_h
#include "Globals.h"
#include <SabertoothSimplified.h>
#include <CytronMotorDriver.h>

// eg: extern String variable; will make a .cpp file's variable public
// eg: extern void thing(); will make a .cpp file's function public

/* DOME Motor Driver */
extern CytronMD DomeMotor;  // PWM = Pin 3, DIR = Pin 4.
extern SabertoothSimplified FeetMotors; // SabertoothSimplified FeetMotors(FootMotorsSerial)

extern void TurnDomeMotor(int speed);
extern void DriveFeetMotors(int speed, int turn, int limit);
extern void DriveSetup();

#endif
