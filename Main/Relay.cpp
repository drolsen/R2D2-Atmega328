#include "Relay.h"

byte RelayDialogPortDecision;
byte RelayDialogVoltageDecision;

void RelaySetup() {
  pinMode(Relay5VA, OUTPUT); // 5V A
  pinMode(Relay5VB, OUTPUT); // 5V B
  pinMode(Relay12VA, OUTPUT);// 12V A
  pinMode(Relay12VB, OUTPUT);// 12V B
  
  digitalWrite(Relay5VA, LOW);
  digitalWrite(Relay5VB, LOW);
  digitalWrite(Relay12VA, LOW);
  digitalWrite(Relay12VB, LOW);  
};
