#include "Radio.h";

RF24 Radio(42, 43); // CE, CSN
const byte address[6] = "R2D2";

void RadioSetup() {
  Radio.begin();
  Radio.setPALevel(RF24_PA_LOW);
  Radio.openReadingPipe(0, address);
  Radio.startListening();
}
