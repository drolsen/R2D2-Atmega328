#include "Body.h"
#include "Servos.h"

void ToggleBodyDoor(byte servoNumber, int from, int to) {
  // BodyServos.wakeup();
  BodyServos.wakeup();
  ServoSleepWait = millis();
  
  if (from > to) {
    for (uint16_t pulselen = from; pulselen > to; pulselen--) {
      BodyServos.setPWM(servoNumber, 0, pulselen);         
    }
  } else if (from < to) {
    for (uint16_t pulselen = from; pulselen < to; pulselen++) {
      BodyServos.setPWM(servoNumber, 0, pulselen);           
    }    
  }
}

void ToggleCPUArm(byte state) {
  if (state == 0) {
    //BodyServos.setPWM(0, 0, int(float(1500) / 1000000 * SERVOFREQUENCY * 4096));
  }

  if (state == 1) {
    //BodyServos.setPWM(0, 0, int(float(400) / 1000000 * SERVOFREQUENCY * 4096));
  }
}

void ToggleGripperArm(byte state) {
  if (state == 0) {
    //BodyServos.setPWM(1, 0, int(float(700) / 1000000 * SERVOFREQUENCY * 4096));
  }

  if (state == 1) {
    //BodyServos.setPWM(1, 0, int(float(2000) / 1000000 * SERVOFREQUENCY * 4096));
  }
}

void ToggleUtilityArmTop(byte state) {
  if (state == 0) {
    //BodyServos.setPWM(2, 0, int(float(500) / 1000000 * SERVOFREQUENCY * 4096));
  }

  if (state == 1) {
    //BodyServos.setPWM(2, 0, int(float(3000) / 1000000 * SERVOFREQUENCY * 4096));
  }
}

void ToggleUtilityArmBottom(byte state) {
  if (state == 0) {
    //BodyServos.setPWM(2, 0, int(float(500) / 1000000 * SERVOFREQUENCY * 4096));
  }

  if (state == 1) {
    //BodyServos.setPWM(2, 0, int(float(3000) / 1000000 * SERVOFREQUENCY * 4096));
  }
}
