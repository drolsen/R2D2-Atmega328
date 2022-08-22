#include "Globals.h";
#include "Audio.h";
#include <DFRobotDFPlayerMini.h>

SoftwareSerial AudioVirtualSerial(68, 69); // RX A14, TX A15
DFRobotDFPlayerMini AudioPlayer;

byte CurrentAudioVolume = 15;
byte PreviousAudioVolume = 15;
byte CurrentAudioNumber = 0;
byte PreviousAudioNumber = 0;

// Audio file mappings due to DFPlayer requirements of all files living in single MP3 folder.
int Beeps[2] = {1, 34};
int Frightened[2] = {35, 38};
int Charging[2] = {39, 40};
int No[2] = {41, 42};
int Yes[2] = {43, 43};
int Mad[2] = {44, 46};
int Angry[2] = {44, 46};
int Excited[2] = {47, 50};
int Happy[2] = {47, 50};
int Sad[2] = {51, 56};
int FilmMusic[2] = {57, 65};
int GeneralMusic[2] = {66, 100};
int HalloweenMusic[2] = {101, 110};
int NarratedTrilogy[2] = {111, 113};

void PlayRandomBeep(int audioRange[2], bool asAdvertisment) {
  AudioPlayer.pause();

  int randomNumber = random(audioRange[0], audioRange[1]);

  if (asAdvertisment == true) {
    AudioPlayer.advertise(random(audioRange[0], audioRange[1]));
  } else {
    AudioPlayer.playMp3Folder(random(audioRange[0], audioRange[1]));
  }
}

void PlayRandomMP3(int audioRange[2]) {
  AudioPlayer.pause();
  int randomId = random(audioRange[0], audioRange[1]);
  if (PreviousAudioNumber == 0) {
    PreviousAudioNumber = randomId;
  } else {
    PreviousAudioNumber = CurrentAudioNumber;
  }

  CurrentAudioNumber = randomId;
  AudioPlayer.playMp3Folder(randomId);
}

void PlayMP3(int audioFile) {
  AudioPlayer.pause();
  if (PreviousAudioNumber == 0) {
    PreviousAudioNumber = audioFile;
  } else {
    PreviousAudioNumber = CurrentAudioNumber;
  }

  CurrentAudioNumber = audioFile;
  AudioPlayer.playMp3Folder(audioFile);
}

void AudioSetup() {
  AudioVirtualSerial.begin(9600);
  AudioPlayer.begin(AudioVirtualSerial);
  AudioPlayer.volume(15);  //Set default volume value. (0 to 30)
  AudioPlayer.EQ(DFPLAYER_EQ_BASS); // Set EQ type (DFPLAYER_EQ_POP, DFPLAYER_EQ_ROCK, DFPLAYER_EQ_JAZZ, DFPLAYER_EQ_CLASSIC, DFPLAYER_EQ_BASS)
  // PlayMP3(83); // Startup audio
}
