#ifndef _RELAY_h
#define _RELAY_h
#include "Globals.h"

#define Relay5VA 4
#define Relay5VB 5
#define Relay12VA 44
#define Relay12VB 45

// eg: extern String variable; will make a .cpp file's variable public
// eg: extern void thing(); will make a .cpp file's function public

extern byte RelayDialogPortDecision;
extern byte RelayDialogVoltageDecision;

#endif
