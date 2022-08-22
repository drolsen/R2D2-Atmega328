#include "Servos.h";

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  312 // this is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVOFREQUENCY 50 // this is the 'frequency' of each pulse

Adafruit_PWMServoDriver BodyServos = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver DomeServos = Adafruit_PWMServoDriver(0x41);

void ServosSetup(){
  /* Dome Servos Setup */
  BodyServos.begin();
  BodyServos.setPWMFreq(SERVOFREQUENCY);  // Analog servos run at ~50 Hz updates
  //BodyServos.setOscillatorFrequency(27000000);

  DomeServos.begin();
  DomeServos.setPWMFreq(SERVOFREQUENCY);  // Analog servos run at ~50 Hz updates  
  //DomeServos.setOscillatorFrequency(27000000);  
}
