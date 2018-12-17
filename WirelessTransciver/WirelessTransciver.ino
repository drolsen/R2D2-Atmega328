// nrf24_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_NRF24 class. RH_NRF24 class does not provide for addressing or
// reliability, so you should only use RH_NRF24 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example nrf24_server.
// Tested on Uno with Sparkfun NRF25L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <SPI.h>
#include <RH_NRF24.h>

#define JoyStick_X_PIN A1 
#define JoyStick_Y_PIN A2
#define JoyStick_Z_PIN A3
int8_t joystick[3];

// Singleton instance of the radio driver
RH_NRF24 nrf24(8, 10);
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
    delay(1000); // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
}

void loop()
{
  // Send a message to nrf24_server
  joystick[0] = map(constrain(analogRead(JoyStick_X_PIN), 0, 640), 0, 640, 127, 0);
  joystick[1] = map(constrain(analogRead(JoyStick_Y_PIN), 0, 640), 640, 0, 127, 0);
  joystick[2] = map(constrain(analogRead(JoyStick_Z_PIN), 0, 640), 0, 640, 1, 0);
  
  nrf24.send(joystick, sizeof(joystick));
}

