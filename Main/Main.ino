#include <SPI.h>
#include <Wire.h>
#include <SabertoothSimplified.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <RH_NRF24.h>
#include <L298N.h>
#include <DFRobotDFPlayerMini.h>

int CurrentServo = 0;
int CurrentServoPulse = 150;

/* R2 Modes */
byte Mode = 2;
byte ModeSwitchChecks = 0;

/* DOME Servos */
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
Adafruit_PWMServoDriver DomeServos = Adafruit_PWMServoDriver();

/* Wireless */
RH_NRF24 Wireless;
unsigned long WirelessWait = 0;

/* DOME LEDs */
byte DomeLEDBrightness = 100;
Adafruit_NeoPixel DomeLEDS = Adafruit_NeoPixel(32, 2, NEO_GRB + NEO_KHZ800);

/* Basic LED Colors */
const uint32_t LEDWhite = Adafruit_NeoPixel::Color(195, 255, 255);
const uint32_t LEDBlack = Adafruit_NeoPixel::Color(0, 0, 0);

/* Front DOME LED Colors */
const uint32_t LEDBlue = Adafruit_NeoPixel::Color(0, 0, 255);
const uint32_t LEDRed = Adafruit_NeoPixel::Color(255, 0, 0);

/* Back DOME LED Colors */
const uint32_t LEDGreen = Adafruit_NeoPixel::Color(45, 235, 235);
const uint32_t LEDGold = Adafruit_NeoPixel::Color(245, 190, 35);


unsigned long LEDDiffuseWait = millis();
unsigned long LEDLogicWait = millis();
unsigned long LEDHoloWait = millis();

int LEDDiffusePause = random(1000, 10000);
int LEDLogicPause = random(1000, 4000);
int LEDHoloPause = random(100, 500);

byte FrontLEDState = 0;
byte BackLEDState = 0;

/* MP3 variables */
SoftwareSerial AudioVirtualSerial(9, 7);
DFRobotDFPlayerMini AudioPlayer;

/* DOME Drive Motor */
L298N DomeMotor(5, 4, 3);

/* Feet motors */
SabertoothSimplified FeetMotors; // We'll name the Sabertooth object FeetMotors.

/* Audio folder mapping */
byte Beeps[2] = {1, 34};
byte Frightened[2] = {35, 38};
byte Charging[2] = {39, 40};
byte No[2] = {41, 42};
byte Yes[2] = {43, 43};
byte Mad[2] = {44, 46};
byte Happy[2] = {47, 50};
byte Sad[2] = {51, 56};
byte Music[2] = {57, 65};

const unsigned long MusicLengths[10] = {
  420000,
  385800,
  192000,
  256200,
  128400,
  256800,
  300600,
  121200,
  193200
};
unsigned long PlayingAudioWait = 0;
int CurrentlyPlayingMusic = -1;

void setup()
{
  /* Virtual Serial Must Begin before actual nano Serial */
  AudioVirtualSerial.begin(9600);

  /* We next connect our audio player object to the audio virtual serial. */
  AudioPlayer.begin(AudioVirtualSerial);
  AudioPlayer.volume(30);  //Set volume value. From 0 to 30
  //PlayRandomMP3(Music);
 
  /* Dome LEDS Setup */
  DomeLEDS.begin();
  DomeLEDS.setBrightness(DomeLEDBrightness);
  DomeLEDS.show();
  

  /* Dome Servos Setup */
  DomeServos.begin();
  DomeServos.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  /* Dome Motor Setup */
  DomeMotor.setSpeed(0); // an integer between 0 and 255

  /* Feet Motors Setup */
  SabertoothTXPinSerial.begin(9600); // This is the baud rate you chose with the DIP switches.
  //FeetMotors.autobaud();
  FeetMotors.drive(0);
  FeetMotors.turn(0); 

  /* Wireless Setup */
  Wireless.init();
  Wireless.setChannel(1);
  Wireless.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm);
}

void loop()
{
  //serial_commands_.ReadSerial();
  DomeLEDsUpdate();
  WirelessPing();
}

void WirelessPing() {
  while (millis() > WirelessWait + 100) {
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    // Should be a reply message for us now 
    if (Wireless.recv(buf, sizeof(&buf)))
    {
      //Serial.println("Speed: ");
      //Serial.print(buf[1]); 
      if (buf[2] == 1) {
        // Click to play random beep
        PlayRandomBeep(Beeps, false);
  
        if (ModeSwitchChecks <= 3) {
          // If found to be holding joystick click for three checks
          ModeSwitchChecks++;
        } else {
          Mode++;
          if (Mode > 3) {
            Mode = 0;
          }  
          ModeSwitchChecks = 0;
        }
      } else {
        ModeSwitchChecks = 0;
      }
      
      // Driving Feet Motors
      if (Mode == 0) {
        DriveFeetMotors(buf[1], buf[0]);      
      }

      // Turning Dome Motor
      if (Mode == 1) {
        TurnDomeMotor(buf[0]);
      }

      // Turning Dome Servos
      if (Mode == 2) {
        DriveDomeServos(buf[0], buf[1]);
      }

      //Serial.println(ModeSwitchChecks);   
    } else {
      //DriveFeetMotors(0, 0);
      //TurnDomeMotor(0);  
    }

    WirelessWait = millis();
  }
}

void DriveFeetMotors(int speed, int turn) {
  int maxSpeed = 127;
  speed = map(speed, 127, 0, maxSpeed, -maxSpeed);
  turn = map(turn, 127, 0, -maxSpeed, maxSpeed);
  AudioPlayer.volume(map(abs(speed), 0, 127, 0, 15));
  PlayRandomMP3(Music);

  if (speed <= 10 && speed >= -10) {
    speed = 0;
  }

  if (turn <= 10 && turn >= -10) { 
    turn = 0; 
  }

  FeetMotors.drive(speed); // 127 === forwards (full power) | -127 === backwards (full power)
  FeetMotors.turn(turn);   // -127 === turns left | 127 === turns right
}

void TurnDomeMotor(int x) {
  // due to poor joystick percision due to battery, we have limit this method to values over 20.
  int maxSpeed = 255;
  int Input = map(x, 127, 0, 127, -127);
  if (Input <= 10 && Input >= -10) {
    Input = 0;
    DomeMotor.stop();
    return;
  }

  int Direction = abs(Input); 
  int Speed = map(Direction, 0, 127, 0, maxSpeed);

  if (Speed >= 10) {
    DomeMotor.setSpeed(Speed); // 127 === forwards (full power) | -127 === backwards (full power)
  }

  if (Input >= 10) {
    DomeMotor.forward();
  }
  
  if (Input <= -10){
    DomeMotor.backward();
  }
}

byte DomeServoCount = 5;
void DriveDomeServos(int x, int y) {
  // Drive each servo one at a time
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    DomeServos.setPWM(DomeServoCount, 0, pulselen);
    delay(20);
  }
  delay(500);

  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    DomeServos.setPWM(DomeServoCount, 0, pulselen);
    delay(20);
  }
  delay(500);

  DomeServoCount++;
  if (DomeServoCount == 5) DomeServoCount = 16;
}

void PlayRandomBeep(byte audioRange[2], bool asAdvertisment) {
  if (asAdvertisment == true) {
    AudioPlayer.advertise(random(audioRange[0], audioRange[1]));
  } else {
    AudioPlayer.play(random(audioRange[0], audioRange[1]));  
  }
}

void PlayRandomMP3(byte audioRange[2]) {
  int randomId = random(audioRange[0], audioRange[1]);

  if (CurrentlyPlayingMusic == -1) {
    AudioPlayer.play(randomId);
    CurrentlyPlayingMusic = randomId - 57;
    PlayingAudioWait = millis();
    return;
  }

  while (millis() > PlayingAudioWait + MusicLengths[CurrentlyPlayingMusic]) {
    AudioPlayer.play(randomId);    
    CurrentlyPlayingMusic = randomId - 57;
    PlayingAudioWait = millis();
  }
}

void DomeLEDsUpdate() {
  while (millis() >  LEDHoloWait + LEDHoloPause) {
    for (uint16_t i = 0; i <= 3; i++) {
      int rand = random(20, 100);
      DomeLEDS.setPixelColor(i, rand, rand, rand);
    }

    for (uint16_t j = 22; j <= 25; j++) {
      int rand = random(20, 100);
      DomeLEDS.setPixelColor(j, rand, rand, rand);
    }

    for (uint16_t k = 29; k <= 32; k++) {
      int rand = random(20, 100);
      DomeLEDS.setPixelColor(k, rand, rand, rand);
    }    
    
    DomeLEDS.show();
    LEDHoloWait = millis();
    LEDHoloPause = random(50, 100);
    return;  
  }
  
  while (millis() >  LEDLogicWait + LEDLogicPause) {
    // small logic lights have random two colors across all pixels
    for (uint16_t l = 7; l <= 12; l++) {
      DomeLEDS.setPixelColor(l, (random(1, 3) == 1) ? LEDBlue : LEDWhite);
    }

    // large logic lights have two random colors (and off state) per pixel
    int rand = random(1, 5);
    DomeLEDS.setPixelColor(13, (rand == 3) ? LEDRed : (rand == 2) ? LEDBlack : (rand == 1) ? LEDRed : LEDRed); //red / red / black / red
    DomeLEDS.setPixelColor(14, (rand == 1) ? LEDGold : (rand == 2) ? LEDGreen : (rand == 3) ? LEDBlack : LEDGold); //gold / green / black
    DomeLEDS.setPixelColor(15, (rand == 3) ? LEDGold : (rand == 1) ? LEDGold : (rand == 2) ? LEDBlack : LEDBlack); // gold / gold / black
    DomeLEDS.setPixelColor(16, (rand == 2) ? LEDGreen : (rand == 3) ? LEDGreen : (rand == 1) ? LEDBlack : LEDGreen); // green / black / black
    DomeLEDS.setPixelColor(17, (rand == 3) ? LEDGreen : (rand == 1) ? LEDGold : (rand == 2) ? LEDGold : LEDBlack); // green / gold / black
    DomeLEDS.setPixelColor(18, (rand == 1) ? LEDRed : (rand == 2) ? LEDRed : (rand == 3) ? LEDBlack : LEDBlack); // red / red / black
    DomeLEDS.setPixelColor(19, (rand == 2) ? LEDGreen : (rand == 3) ? LEDGreen : (rand == 1) ? LEDBlack : LEDGreen); // green / green / black
    DomeLEDS.setPixelColor(20, (rand == 1) ? LEDGold : (rand == 2) ? LEDGold : (rand == 3) ? LEDGreen : LEDBlack); // gold / gold / green
    DomeLEDS.setPixelColor(21, (rand == 3) ? LEDRed : (rand == 2) ? LEDBlack : (rand == 1) ? LEDRed : LEDBlack); // red / black / black
    
    DomeLEDS.show();
    LEDLogicWait = millis();
    LEDLogicPause = random(100, 500);
    return;  
  }

  while (millis() >  LEDDiffuseWait + LEDDiffusePause) {
    BackLEDState = (BackLEDState == 0) ? 1 : 0;
    FrontLEDState = (FrontLEDState == 0) ? 1 : 0;

    for (uint16_t m = 4; m <= 6; m++) {
      DomeLEDS.setPixelColor(m, (FrontLEDState == 0)? LEDBlue : LEDRed);
    }

    for (uint16_t n = 26; n <= 28; n++) {
      DomeLEDS.setPixelColor(n, (BackLEDState == 0)? LEDGreen: LEDGold);
    }

    DomeLEDS.show();
    LEDDiffuseWait = millis();
    LEDDiffusePause = random(10000, 20000);
    return;   
  }
}


