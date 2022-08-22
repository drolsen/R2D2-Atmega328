#ifndef _RADIO_h
#define _RADIO_h
#include "Globals.h"
#include <RF24.h>

struct RadioPackage {
  byte j1PotX;
  byte j1PotY;
  byte j1Button;
  byte j2PotX;
  byte j2PotY;
  byte j2Button;
  byte pot1;
  byte pot2;
  byte tSwitch1;
  byte tSwitch2;
  byte button1;
  byte button2;
  byte button3;
  byte button4;
  byte angleX;
  byte angleY;
};

// eg: extern String variable; will make a .cpp file's variable public
// eg: extern void thing(); will make a .cpp file's function public

extern RF24 Radio;
extern void RadioSetup();

#endif
