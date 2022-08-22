#include "Globals.h";
#include "Servos.h";
#include "Radio.h";
#include "AI.h";
#include "Relay.h";
#include "Audio.h";
#include "LEDs.h";
#include "Drive.h";
#include "Body.h";

/* WiFi */
HardwareSerial &WiFi = Serial1;

/* Relays */

/* Servos */

/* Radio communication */
RadioPackage RadioData; // Create a variable with the above structure

/* MP3 Player */

void setup()
{
  /* Dome & Body Servos Setup */
  ServosSetup();
  
  /* Setup MP3 Player (MUST BE RAN BEFORE THE MAIN Serial.begin() BELOW!)*/
  AudioSetup();

  /* Main Serial Setup (DO NOT REMOVE, RADIO COMMUNICATION NEEDS THIS STARTED) */
  Serial.begin(9600);

  /* Setup AI (Speech recoignition and text to speech) */
  AISetup();
  
  /* Radio communication Setup */
  RadioSetup();
  
  /* Relays Setup */
  // RelaySetup();

  /* Dome and Foot Drive Setup */
  DriveSetup();

  /*Audio.h Plays random beeps array */
  PlayRandomBeep(Beeps, false);

  /* Body and Dome LED setup */
  LEDSetup();  
}

//String readString;

void loop()
{   
  // ToggleArmLights((leftFrontLargeDoorStatus == 1 || leftFrontLargeDoorStatus == 1) ? 1 : 0);
  // TogglePanelLights((dataFrontDoorStatus == 1 || chargebayFrontDoorStatus == 1) ? 1 : 0);
  // ToggleGroundLights(groundLightsStatus);

  if (millis() > (AudioWait + random(9000, 21000))) {
    if (random(0, 2) == 0) {
      PlayRandomBeep(Beeps, false);
    } else {
      PlayRandomBeep(Happy, false);
    }
    AudioWait = millis();
  }
  
  // Radio Transiver Pulse
  RadioPing();
  
  // Voice Interface Pulses
  // AIPing();

  //  if (millis() > (dataFrontDoorWait + 5000)) {
  //    digitalWrite(Relay5VA, HIGH);
  //    digitalWrite(Relay5VB, HIGH);
  //    digitalWrite(Relay12VA, HIGH);
  //    digitalWrite(Relay12VB, HIGH);
  //    
  //    dataFrontDoorWait = millis();
  //  } else {
  //    digitalWrite(Relay5VA, LOW);
  //    digitalWrite(Relay5VB, LOW);
  //    digitalWrite(Relay12VA, LOW);
  //    digitalWrite(Relay12VB, LOW);
  //  }   
}

void RadioPing() {
  while (millis() > RadioWait + 50) {
    if (Radio.available()) {
      Radio.read(&RadioData, sizeof(RadioPackage));
      // MP3 and AI Volumes
      // time and value based volume debouncer

//      if (groundLightsStatus == 1) {
//        // scroll throught colors
//        byte red = groundLightsRGB[0];
//        byte green = groundLightsRGB[1];
//        byte blue = groundLightsRGB[2];
//        byte saturation = 255;
//        bool scrollDownRGB = (RadioData.angleY > (255 / 2)) ? true : false;
//        byte scrollSpeed = 17;
//
//        if (blue == 0 && red == 0 && green == 0) {
//          red = saturation;
//        } 
//        
//        // SCROLL DOWN COLORS
//        if (RadioData.angleY > 210) {         
//          // Add blue to red
//          if (blue != saturation && red == saturation && green == 0) {
//            blue = blue + scrollSpeed;
//            if (blue > saturation) { blue = saturation; }
//          }
//          // Remove red from blue
//          else if (blue == saturation && red != 0 && green == 0) {
//            red = red - scrollSpeed;
//            if (red < 0) { red = 0; }
//          }
//
//          // Add green to blue
//          else if (green != saturation && blue == saturation && red == 0) {
//            green = green + scrollSpeed;
//            if (green > saturation) { green = saturation; }
//          }
//
//          // Remove blue from green
//          else if (green == saturation && blue != 0 && red == 0) {
//            blue = blue - scrollSpeed;
//            if (blue < 0) { blue = 0; }
//          }
//
//          // Add red to green
//          else if (red != saturation && green == saturation && blue == 0) {
//            red = red + scrollSpeed;
//            if (red > saturation) { red = saturation; }
//          }
//
//          // Remove green from red
//          else if (red == saturation && green != 0 && blue == 0) {
//            green = green - scrollSpeed;
//            if (green < 0) { green = 0; }
//          }
//          
//        } 
//        // SCROLL UP COLORS
//        else if (RadioData.angleY < 30) {             
//          // Add green to red
//          if (blue == 0 && green != saturation && red == saturation) {
//            green = green + scrollSpeed;
//            if (green > saturation) { green = saturation; }
//          }
//          
//          // Remove red from green
//          else if (blue == 0 && red != 0 && green == saturation) {
//            red = red - scrollSpeed;
//            if (red < 0) { red = 0; }
//          }
//
//          // Add blue to green
//          else if (green == saturation && blue != saturation && red == 0) {
//            blue = blue + scrollSpeed;
//            if (blue > saturation) { blue = saturation; }
//          }
//
//          // Remove green from blue
//          else if (green != 0 && blue == saturation && red == 0) {
//            green = green - scrollSpeed;
//            if (green < 0) { green = saturation; }
//          }
//
//          // Add red to blue
//          else if (red != saturation && green == 0 && blue == saturation) {
//            red = red + scrollSpeed;
//            if (red > saturation) { red = saturation; }
//          }
//
//          // Remove blue from red
//          else if (red == saturation && green == 0 && blue > 0) {
//            blue = blue - scrollSpeed;
//            if (blue < 0) { blue = 0; }
//          }
//        }
//        
//        if (red > saturation) { red = saturation; }
//        if (green > saturation) { green = saturation; }
//        if (blue > saturation) { blue = saturation; }
//
//        groundLightsRGB[0] = red;
//        groundLightsRGB[1] = green;
//        groundLightsRGB[2] = blue;
// 
//        for(int i=0;i<120;i++) {
//          BodyLEDS.setPixelColor(i, BodyLEDS.Color(groundLightsRGB[0], groundLightsRGB[1], groundLightsRGB[2]));
//        }
//
//        if (RadioData.angleX >= 150) {
//          BodyLEDS.setBrightness(150);
//        }else if (RadioData.angleX <= 10) {
//          BodyLEDS.setBrightness(10);
//        } else {
//          BodyLEDS.setBrightness(RadioData.angleX);      
//        }
//        
//        BodyLEDS.show();
//      }


      if (millis() > VolumeWait + 1000) {
        if ((CurrentAudioVolume) != map(RadioData.pot1, 0, 255, 0, 30)) {
          CurrentAudioVolume = map(RadioData.pot1, 0, 255, 0, 30);
          AudioPlayer.volume(CurrentAudioVolume);
          // AI.println("VOLUME" + (char)CurrentAudioVolume);      
        }
        VolumeWait = millis();
      }

      // Toggle Switch Modes
      if (millis() > (tSwitchWait + 512)) {
        if (
          RadioData.tSwitch1 != tSwitch1State 
          || RadioData.tSwitch2 != tSwitch2State
        ) {
          // if (RadioData.tSwitch1 == 0 && RadioData.tSwitch2 == 0) { AI.println(F("SAY Voice Mode!")); }
          // if (RadioData.tSwitch1 == 0 && RadioData.tSwitch2 == 1) { AI.println(F("SAY Body Mode!")); }
          // if (RadioData.tSwitch1 == 1 && RadioData.tSwitch2 == 0) { AI.println(F("SAY Dome Mode!")); } 
          // if (RadioData.tSwitch1 == 1 && RadioData.tSwitch2 == 1) { AI.println(F("SAY Standard Mode!")); }
        }

        tSwitch1State = RadioData.tSwitch1;
        tSwitch2State = RadioData.tSwitch2;
        
        tSwitchWait = millis();
      }

      //Standard Mode
      if (RadioData.tSwitch1 == 1 && RadioData.tSwitch2 == 1) {
        // Driving Feet Motors
        DriveFeetMotors(
          RadioData.j1PotY,
          RadioData.j1PotX,
          RadioData.pot2
        );
        
        // Driving Dome Motors
        TurnDomeMotor(RadioData.j2PotX); 

        // Button1 states
        if (millis() > AudioWait + 256) {
          if (button1State != RadioData.button1) {
            // we have a changed state
            // button released
            if (button1State == 0 && RadioData.button1 == 1) {
              button1State = 1;
              PlayRandomBeep(GeneralMusic, false);
            } else if (button1State == 1 && RadioData.button1 == 0){
              button1State = 0;
            }
          }
    
          // Button2 states
          if (button2State != RadioData.button2) {
            // we have a changed state
            // button released
            if (button2State == 0 && RadioData.button2 == 1) {
              button2State = 1;
              PlayRandomBeep(Beeps, false);
            } else if (button2State == 1 && RadioData.button2 == 0){
              button2State = 0;
            }
          }      
    
          // Button3 states
          if (button3State != RadioData.button3) {
            // we have a changed state
            // button released
            if (button3State == 0 && RadioData.button3 == 1) {
              button3State = 1;
              PlayRandomMP3(FilmMusic);
            } else if (button3State == 1 && RadioData.button3 == 0){
              button3State = 0;
            }
          }
    
          // Button4 states
          if (button4State != RadioData.button4) {
            // we have a changed state
            // button released
            if (button4State == 0 && RadioData.button4 == 1) {
              button4State = 1;
              PlayRandomMP3(HalloweenMusic);
            } else if (button4State == 1 && RadioData.button4 == 0){
              button4State = 0;
            }
          }
  
          AudioWait = millis();
        }      
      }

      // Voice mode
      if (RadioData.tSwitch1 == 0 && RadioData.tSwitch2 == 0) {
        
      }
      
      // Body Mode
      if (RadioData.tSwitch1 == 0 && RadioData.tSwitch2 == 1) {
        // Open/Close Top Utility arm
        if (RadioData.j1Button == 0 && millis() > (UtilityArmTopWait + 250)) {
          if (UtilityArmStatus[0] == 0) {
            // Open
            ToggleBodyDoor(1, 170, 338);
            UtilityArmStatus[0] = 1;              
          } else if (UtilityArmStatus[0] == 1) {
            // Close            
            ToggleBodyDoor(1, 338, 170); 
            UtilityArmStatus[0] = 0;                
          }
          UtilityArmTopWait = millis();           
        }
        
        // Open/Close Bottom Utility arm
        if (RadioData.j2Button == 0 && millis() > (UtilityArmBottomWait + 250)) {
          if (UtilityArmStatus[1] == 0) {
            // Open
            ToggleBodyDoor(0, 250, 412);
            UtilityArmStatus[1] = 1; 
          } else if (UtilityArmStatus[1] == 1) {
            // Close
            ToggleBodyDoor(0, 412, 250); 
            UtilityArmStatus[1] = 0;
          }
          UtilityArmBottomWait = millis();
        }
        
        // Open Large Body Door One
        if (RadioData.j1PotY > 230) {
          if (leftFrontLargeDoorStatus == 0 && leftArmRotateStatus == 0 && leftArmActuateStatus == 0 && (millis() > (largeOneFrontDoorWait + 500))) {
            largeOneFrontDoorWait = millis();
            ToggleBodyDoor(5, 200, 130);
            leftFrontLargeDoorStatus = 1;
          }
          
          if (leftFrontLargeDoorStatus == 1 && leftArmRotateStatus == 0 && leftArmActuateStatus == 0 && (millis() > (largeOneFrontDoorWait + 500))) {
            largeOneFrontDoorWait = millis();
            ToggleBodyDoor(6, 250, 450);
            leftArmRotateStatus = 1;
          }
          
          if (leftFrontLargeDoorStatus == 1 && leftArmRotateStatus == 1 && leftArmActuateStatus == 0 && (millis() > (largeOneFrontDoorWait + 500))) {
            largeOneFrontDoorWait = millis();
            ToggleBodyDoor(7, 340, 220);
            leftArmActuateStatus = 1;             
          }
        }

        // Close Large Body Door One
        if (RadioData.j1PotY < 20) {   
          if (leftFrontLargeDoorStatus == 1 && leftArmRotateStatus == 1 && leftArmActuateStatus == 1 && (millis() > (largeOneFrontDoorWait + 500))) {
            largeOneFrontDoorWait = millis();
            ToggleBodyDoor(7, 220, 340);
            leftArmActuateStatus = 0;
          }
          
          if (leftFrontLargeDoorStatus == 1 && leftArmRotateStatus == 1 && leftArmActuateStatus == 0 && (millis() > (largeOneFrontDoorWait + 500))) {
            largeOneFrontDoorWait = millis();
            ToggleBodyDoor(6, 450, 250);
            leftArmRotateStatus = 0;            
          }
             
          if (leftFrontLargeDoorStatus == 1 && leftArmRotateStatus == 0 && leftArmActuateStatus == 0 && (millis() > (largeOneFrontDoorWait + 500))) {
            largeOneFrontDoorWait = millis();
            ToggleBodyDoor(5, 130, 200);
            leftFrontLargeDoorStatus = 0;
          }
        }

        // Open Large Body Door Two
        if (RadioData.j2PotY > 230) {
          if (rightFrontLargeDoorStatus == 0 && rightArmRotateStatus == 0 && rightArmActuateStatus == 0 && (millis() > (largeTwoFrontDoorWait + 500))) {
            largeTwoFrontDoorWait = millis();
            ToggleBodyDoor(8, 150, 350);
            rightFrontLargeDoorStatus = 1;
          }

          if (rightFrontLargeDoorStatus == 1 && rightArmRotateStatus == 0 && rightArmActuateStatus == 0 && (millis() > (largeTwoFrontDoorWait + 500))) {
            largeTwoFrontDoorWait = millis();   
            ToggleBodyDoor(9, 410, 170);
            rightArmRotateStatus = 1;
          } 

          if (rightFrontLargeDoorStatus == 1 && rightArmRotateStatus == 1 && rightArmActuateStatus == 0 && (millis() > (largeTwoFrontDoorWait + 500))) {
            largeTwoFrontDoorWait = millis();          
            ToggleBodyDoor(10, 200, 490);
            rightArmActuateStatus = 1;        
          } 
        }

        // Close Large Body Door Two
        if (RadioData.j2PotY < 20) { 
          if (rightFrontLargeDoorStatus == 1 && rightArmRotateStatus == 1 && rightArmActuateStatus == 1 && (millis() > (largeTwoFrontDoorWait + 500))) {
            largeTwoFrontDoorWait = millis();             
            ToggleBodyDoor(10, 490, 200);
            rightArmActuateStatus = 0;            
          }       

          if (rightFrontLargeDoorStatus == 1 && rightArmRotateStatus == 1 && rightArmActuateStatus == 0 && (millis() > (largeTwoFrontDoorWait + 500))) {
            largeTwoFrontDoorWait = millis();             
            ToggleBodyDoor(9, 170, 410);
            rightArmRotateStatus = 0;               
          } 
                         
          if (rightFrontLargeDoorStatus == 1 && rightArmRotateStatus == 0 && rightArmActuateStatus == 0 && (millis() > (largeTwoFrontDoorWait + 500))) {
            largeTwoFrontDoorWait = millis();             
            ToggleBodyDoor(8, 350, 150);
            rightFrontLargeDoorStatus = 0; 
          }        
        }          

        // Open / Close Data panel
        if (RadioData.button1 == 0 && millis() > (dataPanelFrontDoorWait + 250)) {
          if (dataFrontDoorStatus == 0) {
            ToggleBodyDoor(2, 420, 570);
            dataFrontDoorStatus = 1;
          } else {
            ToggleBodyDoor(2, 570, 420);
            dataFrontDoorStatus = 0;
          }
          
          dataPanelFrontDoorWait = millis();
        }
        
        // Open / Close Charge Bay
        if (RadioData.button2 == 0 && millis() > (chargebayFrontDoorWait + 250)) {
          if (chargebayFrontDoorStatus == 0) {
            ToggleBodyDoor(3, 370, 250);
            chargebayFrontDoorStatus = 1;
          } else {
            ToggleBodyDoor(3, 250, 370);
            chargebayFrontDoorStatus = 0;
          }
          
          chargebayFrontDoorWait = millis();
        }

        // Open / Close Small Front Door
        if (RadioData.button3 == 0 && millis() > (smallTallFrontDoorWait + 250)) {
          if (verticalSwitchFrontDoorStatus == 0) {
            ToggleBodyDoor(4, 100, 320);
            verticalSwitchFrontDoorStatus = 1;
          } else {
            ToggleBodyDoor(4, 320, 100);
            verticalSwitchFrontDoorStatus = 0;
          }
          
          smallTallFrontDoorWait = millis();
        }

        // Open / Close Back Doors
        if (RadioData.button4 == 0) {
          if (backLargeDoorsStatus == 0 && (millis() > (largeBackDoorsWait + 500))) {
            largeBackDoorsWait = millis(); 
            ToggleBodyDoor(13, 400, 475);
            ToggleBodyDoor(11, 475, 400);
            backLargeDoorsStatus = 1;
          } else if (backLargeDoorsStatus == 1 && (millis() > (largeBackDoorsWait + 500))) {
            largeBackDoorsWait = millis();
            ToggleBodyDoor(13, 475, 400);
            ToggleBodyDoor(11, 400, 475);
            backLargeDoorsStatus = 0;
          }
        }                
        
        // Toggle on / configure / off ground lights
        if (RadioData.button4 == 0 && RadioData.button1 == 0 && millis() > (groundLightsWait + 150)) {
          if (groundLightsStatus == 0) {
            groundLightsStatus = 1;
          } else if (groundLightsStatus == 1) {
            groundLightsStatus = 2;
          } else {
            groundLightsStatus = 0;
          }
          groundLightsWait = millis();
        }
      }

      // Dome Mode
      if (RadioData.tSwitch1 == 1 && RadioData.tSwitch2 == 0) {
        
      }   
    } else {
      // DO NOT REMOVE THIS!
      DomeMotor.setSpeed(0);
      FeetMotors.drive(0);
      FeetMotors.turn(0);
    }

    RadioWait = millis();

    if (millis() > (ServoSleepWait + 1000)) {
      BodyServos.sleep();
    }
  }
}

// Motor and Servo methods

void ToggleArmLights(byte onOff) {
  if (onOff == 0) {
    //for(int i=120;i<BodyLEDSCount;i++) {
    //  BodyLEDS.setPixelColor(i, BodyLEDS.Color(0,0,0));
    //  BodyLEDS.show();
    //}
  }
  
  if (onOff == 1) {
    //for(int i=120;i<BodyLEDSCount;i++) {
    //  BodyLEDS.setPixelColor(i, BodyLEDS.Color(52,0,223));
    //  BodyLEDS.show();
    //}
  }
}

void TogglePanelLights(byte onOff) {
  if (onOff == 0) {
    // digitalWrite(Relay5VA, LOW);
    // digitalWrite(Relay5VB, LOW);
  }
  
  if (onOff == 1) {
    // digitalWrite(Relay5VA, HIGH);
    // digitalWrite(Relay5VB, HIGH);
  }
}

void ToggleGroundLights(byte onOff) {  
  //if (onOff == 0) {
  //  for(int i=0;i<120;i++) {
  //    BodyLEDS.setPixelColor(i, BodyLEDS.Color(0,0,0));
  //  }
  //}
  
  //if (onOff == 2) {
  //  for(int i=0;i<120;i++) {
  //    BodyLEDS.setPixelColor(i, BodyLEDS.Color(groundLightsRGB[0],groundLightsRGB[1],groundLightsRGB[2])); 
  //  }
  //}

  //BodyLEDS.show();
}
