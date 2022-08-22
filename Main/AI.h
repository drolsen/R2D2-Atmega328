#ifndef _AI_h
#define _AI_h
#include "Globals.h"

#include "HardwareSerial.h"
#include <AltSoftSerial.h>

// eg: extern String variable; will make a .cpp file's variable public
// eg: extern void thing(); will make a .cpp file's function public

extern int AIStream;
extern String AIInterpreter;
extern HardwareSerial &AI; // Use hardware serial 2 configuration for AVR or
//AltSoftSerial AI(10, 11); // if possible use default pin configuration for AVR (optional: you can rewire and change pins here)

extern void AISetup();
extern void AIPing();
extern void AIAsk();

/* Modes */
extern byte TranslationMode; // 0 = droid (beeps), 1 = english (synth)

/* Mood */
extern byte CurrentMoods[5]; // angry, frightend, sad, happy, excited (all range 0-100)
extern String GetCurrentMood();

// angry, frightend, sad, happy, excited (all range 0-100)
extern void AdjustPersonality(byte TargetMood, byte AdjustValue);

#endif
