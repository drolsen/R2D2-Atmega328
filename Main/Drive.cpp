#include "Globals.h"
#include "Drive.h"

/* DOME Motor Driver */
CytronMD DomeMotor(PWM_DIR, 46, 47);  // PWM = Pin 3, DIR = Pin 4.

/* Feet Motor Driver */
HardwareSerial &FootMotorsSerial = Serial3; // RX on no pin (unused), TX on pin 11 (to S1).
SabertoothSimplified FeetMotors(FootMotorsSerial); // SabertoothSimplified FeetMotors(FootMotorsSerial)

void TurnDomeMotor(int speed) {
  speed = map(speed, 0, 255, 255, -255);
  // an integer between -255 (fullreverse) and 255 (full forward)
  if (speed > 100 || speed < -100) {
    DomeMotor.setSpeed(speed);
  } else {
    DomeMotor.setSpeed(0);
  }
}

void DriveFeetMotors(int speed, int turn, int limit) {
  limit = map(limit, 0, 255, 0, 127);

  int maxForwordSpeed = -limit;
  int maxBackwardSpeed = limit;

  speed = map(speed, 0, 255, maxForwordSpeed, maxBackwardSpeed);
  turn = map(turn, 0, 255, maxBackwardSpeed, maxForwordSpeed);

  if (speed <= 10 && speed >= -10) {
    speed = 0;
  }

  if (turn <= 10 && turn >= -10) {
    turn = 0;
  }

  FeetMotors.drive(speed); // 127 === forwards (full power) | -127 === backwards (full power)
  FeetMotors.turn(turn);   // -127 === turns left | 127 === turns right
}

void DriveSetup() {
  /* Dome Motor Setup */
  DomeMotor.setSpeed(0); // an integer between -255 (fullreverse) and 255 (full forward)

  /* Feet Motors Setup */
  FootMotorsSerial.begin(9600); // This is the baud rate you chose with the DIP switches.
  FeetMotors.drive(0);
  FeetMotors.turn(0);
}
