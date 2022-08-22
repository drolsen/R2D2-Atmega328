#ifndef _AUDIO_h
#define _AUDIO_h
#include "Globals.h"
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// eg: extern String variable; will make a .cpp file's variable public
// eg: extern void thing(); will make a .cpp file's function public

extern DFRobotDFPlayerMini AudioPlayer;
extern byte CurrentAudioVolume;
extern byte PreviousAudioVolume;
extern byte CurrentAudioNumber;
extern byte PreviousAudioNumber;


// Audio file mappings due to DFPlayer requirements of all files living in single MP3 folder.
extern int Beeps[2];
extern int Frightened[2];
extern int Charging[2];
extern int No[2];
extern int Yes[2];
extern int Mad[2];
extern int Angry[2];
extern int Excited[2];
extern int Happy[2];
extern int Sad[2];
extern int FilmMusic[2];
extern int GeneralMusic[2];
extern int HalloweenMusic[2];
extern int NarratedTrilogy[2];

extern void AudioSetup();
extern void PlayRandomBeep(int audioRange[2], bool asAdvertisment);
extern void PlayRandomMP3(int audioRange[2]);
extern void PlayMP3(int audioFile);

#endif
