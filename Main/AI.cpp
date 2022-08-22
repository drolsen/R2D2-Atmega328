#include "AI.h";
#include "Audio.h";
#include "Relay.h";
#include "Drive.h";

int AIStream;
String AIInterpreter = "";
HardwareSerial &AI = Serial2; // Use hardware serial 2 configuration for AVR or
//AltSoftSerial AI(10, 11); // if possible use default pin configuration for AVR (optional: you can rewire and change pins here)

/* Modes */
byte TranslationMode = 1; // 0 = droid (beeps), 1 = english (synth)

/* Mood */
byte CurrentMoods[5] = {0, 0, 0, 100, 0}; // angry, frightend, sad, happy, excited (all range 0-100)

String GetCurrentMood() {
  int Mood = 0;
  String Status = "";
  for (int i = 0; i < 4; i++) {
    if (Mood >= CurrentMoods[i]) {
      Mood = CurrentMoods[i];
      if (i == 0) {
        Status = "angry";
      }
      if (i == 1) {
        Status = "frightened";
      }
      if (i == 2) {
        Status = "sad";
      }
      if (i == 3) {
        Status = "happy";
      }
      if (i == 4) {
        Status = "excited";
      }
    }
  }

  return Status;
}

// angry, frightend, sad, happy, excited (all range 0-100)
void AdjustPersonality(byte TargetMood, byte AdjustValue) {
  // Adjust target mood
  if ((CurrentMoods[TargetMood] + AdjustValue) < 100) {
    CurrentMoods[TargetMood] = (CurrentMoods[TargetMood] - AdjustValue);
  } else {
    CurrentMoods[TargetMood] = 100;
  }
  // Adjust non-target moods
  if (TargetMood > 2) { // we are increasing up moods and decreasing down moods
    if ((CurrentMoods[0] - AdjustValue) > 0) { // angry
      CurrentMoods[0] = (CurrentMoods[0] - AdjustValue);
    } else {
      CurrentMoods[0] = 0;
    }

    if ((CurrentMoods[1] - AdjustValue) > 0) { // frightend
      CurrentMoods[1] = (CurrentMoods[1] - AdjustValue);
    } else {
      CurrentMoods[1] = 0;
    }

    if ((CurrentMoods[2] - AdjustValue) > 0) { // sad
      CurrentMoods[2] = (CurrentMoods[1] - AdjustValue);
    } else {
      CurrentMoods[2] = 0;
    }
  } else { // we are increasing down moods and decreasing up moods
    if ((CurrentMoods[3] - AdjustValue) > 0) { // happy
      CurrentMoods[3] = (CurrentMoods[0] - AdjustValue);
    } else {
      CurrentMoods[3] = 0;
    }

    if ((CurrentMoods[4] - AdjustValue) > 0) { // excited
      CurrentMoods[4] = (CurrentMoods[1] - AdjustValue);
    } else {
      CurrentMoods[4] = 0;
    }
  }
}

void AISetup() {
  //AI.begin(9600);
  //AI.println("SYSTEMMESSAGES OFF"); // removes boot message
  //AI.println("THRESHOLD 2");
  //AI.println("VOLUME 84"); // removes the vocal the startup status
  //AI.println("RESPONSES OFF"); // removes "there is a lot of noise" & "sorry, but I couldn't understand that"
}

void AIPing() {
  // Cognative Polling
  if (AI.available()) {
    AIStream = AI.read();
    if (AIStream == '\n') {   
      /* Excited Standalones */
      if (AIInterpreter.indexOf("#19") >= 0) { // I love you
        AdjustPersonality(4, 15);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY I love you too!"));
        }
      }
      if (AIInterpreter.indexOf("#20") >= 0) { // you are awesome
        AdjustPersonality(4, 10);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Thank you!"));
        }
      }
      if (AIInterpreter.indexOf("#21") >= 0) { // you are so cool
        AdjustPersonality(4, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Thanks!"));
        }
      }
      if (AIInterpreter.indexOf("#22") >= 0) { // you are the best
        AdjustPersonality(4, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY You are most welcome!"));
        }
      }
      if (AIInterpreter.indexOf("#23") >= 0) { // you rock
        AdjustPersonality(4, 10);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Why thank you!"));
        }
      }

      /* Happy Standalones */
      if (AIInterpreter.indexOf("#24") >= 0) { // cheers
        AdjustPersonality(3, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Cheers mate!"));
        }
      }
      if (AIInterpreter.indexOf("#25") >= 0) { // good droid
        AdjustPersonality(3, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY woof woof bark"));
        }
      }
      if (AIInterpreter.indexOf("#26") >= 0) { // good robot
        AdjustPersonality(3, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Thank you, but I am a droid"));
        }
      }
      if (AIInterpreter.indexOf("#27") >= 0) { // you are awesome
        AdjustPersonality(3, 10);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY No, you are in fact more awesome"));
        }
      }
      if (AIInterpreter.indexOf("#28") >= 0) { // you are so cool
        AdjustPersonality(3, 10);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("Thank you, I try"));
        }
      }
      if (AIInterpreter.indexOf("#29") >= 0 || AIInterpreter.indexOf("#30") >= 0) { // darth sucks
        AdjustPersonality(3, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY He has his moments, but mostly I agree."));
        }
      }

      if (AIInterpreter.indexOf("#31") >= 0 || AIInterpreter.indexOf("#32") >= 0) { // kylo ren sucks
        AdjustPersonality(3, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Kylo ren has lost all hope, so I agree."));
        }
      }

      /* Sad standalones */
      if (AIInterpreter.indexOf("#33") >= 0) { // go away
        AdjustPersonality(2, 10);
      }
      if (AIInterpreter.indexOf("#34") >= 0) { // get away
        AdjustPersonality(2, 10);
      }
      if (AIInterpreter.indexOf("#35") >= 0) { // too loud
        AdjustPersonality(2, 5);
      }
      if (AIInterpreter.indexOf("#36") >= 0) { // no one likes you
        AdjustPersonality(2, 10);
      }
      if (AIInterpreter.indexOf("#37") >= 0) { // leave me alone
        AdjustPersonality(2, 10);
      }
      if (AIInterpreter.indexOf("#38") >= 0) { // quiet
        AdjustPersonality(2, 5);
      }
      if (AIInterpreter.indexOf("#39") >= 0) { // be quiet
        AdjustPersonality(2, 5);
      }
      if (AIInterpreter.indexOf("#40") >= 0) { // out of the way
        AdjustPersonality(2, 5);
      }
      if (AIInterpreter.indexOf("#41") >= 0) { // star wars sucks
        AdjustPersonality(2, 10);
      }
      if (AIInterpreter.indexOf("#42") >= 0) { // you suck
        AdjustPersonality(2, 10);
      }
      if (AIInterpreter.indexOf("#43") >= 0) { // you stink
        AdjustPersonality(2, 5);
      }

      /* Frightend standlones */
      if (AIInterpreter.indexOf("#44") >= 0) { // i dont like you
        AdjustPersonality(1, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY You are frightening me."));
        }
      }
      if (AIInterpreter.indexOf("#45") >= 0) { // i hate you
        AdjustPersonality(1, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Please don't hurt me"));
        }
      }
      if (AIInterpreter.indexOf("#46") >= 0) { // i hate star wars
        AdjustPersonality(1, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY That is a scarry thought!"));
        }
      }
      if (AIInterpreter.indexOf("#47") >= 0 || AIInterpreter.indexOf("#48") >= 0) { // i hate luke
        AdjustPersonality(1, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Luke is a friend of mine. You are frightening me."));
        }
      }
      if (AIInterpreter.indexOf("#49") >= 0 || AIInterpreter.indexOf("#50") >= 0) { // i hate han
        AdjustPersonality(1, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Han solo was a dear friend of mine. You are starting to frighten me."));
        }
      }

      if (AIInterpreter.indexOf("#51") >= 0 || AIInterpreter.indexOf("#52") >= 0) { // i hate chewie
        AdjustPersonality(1, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY That wookie is a close friend of mine. You are starting to frighten me."));
        }
      }

      if (AIInterpreter.indexOf("#53") >= 0 || AIInterpreter.indexOf("#54") >= 0) { // i hate leah
        AdjustPersonality(1, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY She is a true friend of mine. Please stop, you frighten me."));
        }
      }

      if (AIInterpreter.indexOf("#55") >= 0 || AIInterpreter.indexOf("#56") >= 0) { // i hate yoda
        AdjustPersonality(1, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Master yoda was a close friend of mine. Please stop, this talk frightens me."));
        }
      }

      /* Angry standlones */
      if (AIInterpreter.indexOf("#57") >= 0) { // Pile of junk
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Bag of bones"));
        }
      }
      if (AIInterpreter.indexOf("#58") >= 0) { // You suck
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Not nice! I'm getting angry"));
        }
      }
      if (AIInterpreter.indexOf("#59") >= 0) { // Droids suck
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Hoo-mans suck!"));
        }
      }
      if (AIInterpreter.indexOf("#60") >= 0) { // R2D2 sucks
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY You are staring to make me very angry."));
        }
      }
      if (AIInterpreter.indexOf("#61") >= 0) { // C3P0 sucks
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY That is my friend you are talking about. You are making me angry!"));
        }
      }
      if (AIInterpreter.indexOf("#62") >= 0 || AIInterpreter.indexOf("#63") >= 0) { // luke sucks
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY That is my master you are talking about. You are making me very angry!"));
        }
      }
      if (AIInterpreter.indexOf("#64") >= 0 || AIInterpreter.indexOf("#65") >= 0) { // han sucks
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY That was my friend you are talking about. I'm angry now!"));
        }
      }
      if (AIInterpreter.indexOf("#66") >= 0 || AIInterpreter.indexOf("#67") >= 0) { // chewbacca sucks
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY That is my wookie friend you are talking about. Please stop, I am getting angry with you."));
        }
      }
      if (AIInterpreter.indexOf("#68") >= 0 || AIInterpreter.indexOf("#69") >= 0) { // leah sucks
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY She is my friend, how dare you! Please stop, I am getting angry."));
        }
      }
      if (AIInterpreter.indexOf("#70") >= 0 || AIInterpreter.indexOf("#71") >= 0) { // yoda sucks
        AdjustPersonality(0, 5);
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY He was my friend, how dare speak about him like that! I am getting angry."));
        }
      }

      if (AIInterpreter.indexOf("#72") >= 0) { // Hi!
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Hello!"));
        }
      }
      if (AIInterpreter.indexOf("#73") >= 0) { // Hello
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Hi!"));
        }
      }
      if (AIInterpreter.indexOf("#74") >= 0) { // Howdy
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Howdy!"));
        }
      }
      if (AIInterpreter.indexOf("#75") >= 0 || AIInterpreter.indexOf("#78") >= 0) { // Whats up
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Not much"));
        }
      }
      if (AIInterpreter.indexOf("#76") >= 0 || AIInterpreter.indexOf("#77") >= 0) { // How are you?
        if (GetCurrentMood() == "excited") {
          if (TranslationMode == 0) {
            PlayRandomMP3(Beeps);
          } else {
            AI.println(F("SAY I am pretty excited right now!"));
          }
        }
        if (GetCurrentMood() == "happy") {
          if (TranslationMode == 0) {
            PlayRandomMP3(Beeps);
          } else {
            AI.println(F("SAY I am pretty happy right now!"));
          }
        }
        if (GetCurrentMood() == "sad") {
          if (TranslationMode == 0) {
            PlayRandomMP3(Beeps);
          } else {
            AI.println(F("SAY I am awfully sad right now!"));
          }
        }
        if (GetCurrentMood() == "frightend") {
          if (TranslationMode == 0) {
            PlayRandomMP3(Beeps);
          } else {
            AI.println(F("SAY I am very frightend right now!"));
          }
        }
        if (GetCurrentMood() == "angry") {
          if (TranslationMode == 0) {
            PlayRandomMP3(Beeps);
          } else {
            AI.println(F("SAY I am so angry right now!"));
          }
        }
      }

      if (AIInterpreter.indexOf("#79") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY No thank you"));
        }
      }
      if (AIInterpreter.indexOf("#80") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY May the force be with us all!"));
        }
      }
      if (AIInterpreter.indexOf("#81") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY At home, dunking himself into a  hot  oil  bath."));
        }
      }
      if (AIInterpreter.indexOf("#82") >= 0 || AIInterpreter.indexOf("#83") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Darth vader, died fighting to hold onto what little humanity he had left, while saving his son luke\'s life."));
        }
      }
      if (AIInterpreter.indexOf("#84") >= 0 || AIInterpreter.indexOf("#85") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Sadly, Luke has now become one with the force and is physically no more."));
        }
      }

      if (AIInterpreter.indexOf("#86") >= 0 || AIInterpreter.indexOf("#87") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Unfortunatly, han died at the hands of his own son; Kylo Ren."));
        }
      }

      if (AIInterpreter.indexOf("#88") >= 0 || AIInterpreter.indexOf("#89") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Out Cross-bow training, and living life as a new found vegan"));
        }
      }

      if (AIInterpreter.indexOf("#90") >= 0 || AIInterpreter.indexOf("#91") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY She is somewhere out there, in a galaxy far far away."));
        }
      }

      if (AIInterpreter.indexOf("#92") >= 0 || AIInterpreter.indexOf("#93") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Sadly, Master yoda has now become one with the force and is physically no more."));
        }
      }

      if (AIInterpreter.indexOf("#94") >= 0 || AIInterpreter.indexOf("#95") >= 0) { // Where are you from? || Where did you come from?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY I was one of several droids stationed on the Na-boo Royal Starship during the invasion the Trade Federation. The ship was used by Queen Ami-dala and her entourage in an attempt to escape the planet."));
        }
      }
      if (AIInterpreter.indexOf("#96") >= 0) { // who made you
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY My master and builder's name is, Dev-in Olsen"));
        }
      }
      if (AIInterpreter.indexOf("#97") >= 0) { // where is c3p0 from?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY A junk heap on Tat-too-een long  long  ago"));
        }
      }
      if (AIInterpreter.indexOf("#98") >= 0) { // who made c3p0
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY C-3PO was built by a young Annie-kin Skywalker out of parts found in a junk heap on Tat-too-een"));
        }
      }

      if (AIInterpreter.indexOf("#99") >= 0 || AIInterpreter.indexOf("#100") >= 0) { // where did darth come from?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Darth Vader, formerly knowen as Anakin Skywalker was raised on the planet Tat-too-een"));
        }
      }

      if (AIInterpreter.indexOf("#101") >= 0 || AIInterpreter.indexOf("#102") >= 0) { // where did luke skywalker come from?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Luke Skywalker was born on Po-lis Mas-sa. After the death of their mother, Luke and his twin sister Lay-ah were separated to protect them from their father."));
        }
      }

      if (AIInterpreter.indexOf("#103") >= 0 || AIInterpreter.indexOf("#104") >= 0) { // where did han solo come from?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Han Solo was born on Corellia, and was orphaned not long after that. Turning to illicit means of obtaining money, han was born both a thief and a smuggler"));
        }
      }

      if (AIInterpreter.indexOf("#105") >= 0 || AIInterpreter.indexOf("#106") >= 0) { // where Chewbacca come from?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Chewbacca hailed from Kashyyyk, a peaceful planet where he was born in the city of Rwookrrorro one hundred and eighty years before the Clone Wars"));
        }
      }

      if (AIInterpreter.indexOf("#107") >= 0 || AIInterpreter.indexOf("#108") >= 0) { // where Leia from?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Princess Lay-ah was born on Polis Massa. After the death of their mother, Lay-ah and her twin brother Luke were separated to protect them from their father."));
        }
      }

      if (AIInterpreter.indexOf("#109") >= 0 || AIInterpreter.indexOf("#110") >= 0) { // where Yoda from?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY A member of an unknown species, Yoda was born on an unknown planet.He was discovered and trained by the Jedi Master N\'Kata Del Gormo"));
        }
      }

      if (AIInterpreter.indexOf("#111") >= 0) { // how old are you?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY sixty six earth years"));
        }
      }

      if (AIInterpreter.indexOf("#112") >= 0 || AIInterpreter.indexOf("#113") >= 0) { // how old was darth vader?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Darth Vader died at the age of 45"));
        }
      }

      if (AIInterpreter.indexOf("#114") >= 0 || AIInterpreter.indexOf("#115") >= 0) { // how old was luke skywalker?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Luke was sixty six earth years old when finally becoming one with the force forever."));
        }
      }

      if (AIInterpreter.indexOf("#116") >= 0 || AIInterpreter.indexOf("#117") >= 0) { // how old was han solo?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Han solo was seventy six earth years old when he was slayed by his own son Kylo ren."));
        }
      }

      if (AIInterpreter.indexOf("#118") >= 0 || AIInterpreter.indexOf("#119") >= 0) { // how old is chewbacca?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Chewbacca is around two hundred and thirty four earth years old."));
        }
      }

      if (AIInterpreter.indexOf("#120") >= 0 || AIInterpreter.indexOf("#121") >= 0) { // how old is chewbacca?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Lay-ah is sixty six earth years old."));
        }
      }

      if (AIInterpreter.indexOf("#122") >= 0 || AIInterpreter.indexOf("#123") >= 0) { // how old is yoda?
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Yoda lived to the young age of nine hundred earth years."));
        }
      }

      if (AIInterpreter.indexOf("#124") >= 0 || AIInterpreter.indexOf("#125") >= 0 || AIInterpreter.indexOf("#126") >= 0 || AIInterpreter.indexOf("#127") >= 0) { // Time to dance / boogie. Dance time / lets boogie
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Time to boogie."));
        }
        PlayMP3(71);
      }

      if (AIInterpreter.indexOf("#128") >= 0) { // how much wood could a wood chuck
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY A wood-chuck would chuck as much wood as a wood-chuck could chuck, if a wood-chuck could chuck wood"));
        }
      }

      if (AIInterpreter.indexOf("#129") >= 0) { // Play narrated version of A New Hope
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          PlayMP3(84);
        }
      }
      if (AIInterpreter.indexOf("#130") >= 0) { // Play narrated version of Empire Strikes Back
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          PlayMP3(85);
        }
      }
      if (AIInterpreter.indexOf("#131") >= 0) { // Player narrated version Return of Jedi
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          PlayMP3(86);
        }
      }
      if (AIInterpreter.indexOf("#132") >= 0) { // Cancel dialog!
        AudioPlayer.stop();
        DomeMotor.setSpeed(0);
        FeetMotors.drive(0);
        FeetMotors.turn(0);
      }
      if (AIInterpreter.indexOf("#133") >= 0) { // Stop everything!
        AudioPlayer.stop();
      }
      if (AIInterpreter.indexOf("#134") >= 0) { // Translate to English
        TranslationMode = 1;
        AI.println(F("SAY Now translating to english."));
      }
      if (AIInterpreter.indexOf("#135") >= 0) { // Translate to Droid
        TranslationMode = 0;
        PlayRandomBeep(Happy, false);
      }

      if (AIInterpreter.indexOf("#136") >= 0 || AIInterpreter.indexOf("#137") >= 0) { // Play general song / music
        PlayRandomMP3(GeneralMusic);
      }
      if (AIInterpreter.indexOf("#138") >= 0 || AIInterpreter.indexOf("#139") >= 0) { // Play films song / music
        PlayRandomMP3(FilmMusic);
      }

      if (AIInterpreter.indexOf("#152") >= 0) { // Play previous song
        if (PreviousAudioNumber != 0) {
          PlayMP3(PreviousAudioNumber);
        } else if (CurrentAudioNumber != 0) {
          PlayMP3(CurrentAudioNumber);
        } else {
          PlayRandomMP3(GeneralMusic);
        }
      }
      if (AIInterpreter.indexOf("#153") >= 0) { // Repeat song
        PlayMP3(CurrentAudioNumber);
      }

      if (AIInterpreter.indexOf("#154") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel One."));
        }
      }
      if (AIInterpreter.indexOf("#155") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Two."));
        }
      }
      if (AIInterpreter.indexOf("#156") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Three."));
        }
      }
      if (AIInterpreter.indexOf("#157") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Four."));
        }
      }
      if (AIInterpreter.indexOf("#158") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Five."));
        }
      }
      if (AIInterpreter.indexOf("#159") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Six."));
        }
      }
      if (AIInterpreter.indexOf("#160") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Seven."));
        }
      }
      if (AIInterpreter.indexOf("#161") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Eight."));
        }
      }
      if (AIInterpreter.indexOf("#162") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Nine."));
        }
      }
      if (AIInterpreter.indexOf("#163") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Ten."));
        }
      }
      if (AIInterpreter.indexOf("#164") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Eleven."));
        }
      }
      if (AIInterpreter.indexOf("#165") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Twelve."));
        }
      }
      if (AIInterpreter.indexOf("#166") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Pie Panel Thirteen."));
        }
      }
      if (AIInterpreter.indexOf("#167") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Data pane."));
        }
      }
      if (AIInterpreter.indexOf("#168") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening utility arms"));
        }
      }
      if (AIInterpreter.indexOf("#169") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Left Panel"));
        }
      }
      if (AIInterpreter.indexOf("#170") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Opening Right Panel"));
        }
      }
      if (AIInterpreter.indexOf("#171") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Closing my pie holes"));
        }
      }
      if (AIInterpreter.indexOf("#172") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Closing my left panel"));
        }
      }
      if (AIInterpreter.indexOf("#173") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Closing my right panel"));
        }
      }
      if (AIInterpreter.indexOf("#174") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Closing my data panel"));
        }
      }
      if (AIInterpreter.indexOf("#175") >= 0) {
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Closing all panels"));
        }
      }

      if (AIInterpreter.indexOf("#176") >= 0) {
        AI.println(F("SAY Scanning for available networks"));
        // WiFi.flush();
        // WiFi.println("Scan");
        delay(5000);
        AI.println(Serial2.read());
      }

      if (AIInterpreter.indexOf("#177") >= 0) {
        AI.println(F("SAY Which network woud you like to join?"));
      }

      if (AIInterpreter.indexOf("#178") >= 0) {
        AI.println(F("SAY Disconnecting"));
        // WiFi.flush();
        // WiFi.println(F("Disconnect"));
      }

      /* Audio EQ Dialog */
      if (AIInterpreter.indexOf("#179") >= 0 || AIInterpreter.indexOf("#180") >= 0) {
        AI.println(F("Which EQ preset? You can say pop, rock, jazz, bass or classical"));
        AI.println(F("ASK"));
      }
      if (AIInterpreter.indexOf("#181") >= 0) {
        AudioPlayer.EQ(DFPLAYER_EQ_POP);
        AI.println(F("SAY EQ Levels now set to pop preset"));
      }
      if (AIInterpreter.indexOf("#182") >= 0) {
        AudioPlayer.EQ(DFPLAYER_EQ_ROCK);
        AI.println(F("SAY EQ Levels now set to rock preset"));
      }
      if (AIInterpreter.indexOf("#183") >= 0) {
        AudioPlayer.EQ(DFPLAYER_EQ_JAZZ);
        AI.println(F("SAY EQ Levels now set to jazz preset"));
      }
      if (AIInterpreter.indexOf("#184") >= 0) {
        AudioPlayer.EQ(DFPLAYER_EQ_CLASSIC);
        AI.println(F("SAY EQ Levels now set to classical preset"));
      }
      if (AIInterpreter.indexOf("#185") >= 0) {
        AudioPlayer.EQ(DFPLAYER_EQ_BASS);
        AI.println(F("SAY EQ Levels now set to bass preset"));
      }

      /* 5v & 12v Power Relays */
      if (AIInterpreter.indexOf("#186") >= 0 || AIInterpreter.indexOf("#187") >= 0) {
        AI.println(F("Which relay? You can say five volts, or twelve volts"));
        AI.println(F("ASK"));
      }
      if (AIInterpreter.indexOf("#188") >= 0) {
        RelayDialogVoltageDecision = 5;
        AI.println(F("Which five volt relay port? You can say relay a, or relay b"));
        AI.println(F("ASK"));
      }
      if (AIInterpreter.indexOf("#189") >= 0) {
        RelayDialogVoltageDecision = 12;
        AI.println(F("Which twelve volt relay port? You can say relay a, or relay b"));
        AI.println(F("ASK"));
      }

      if (AIInterpreter.indexOf("#190") >= 0) {
        if (RelayDialogVoltageDecision == 5) {
          if (digitalRead(Relay5VA) == LOW) {
            digitalWrite(Relay5VA, HIGH);
          } else {
            digitalWrite(Relay5VA, LOW);
          }
        }
        if (RelayDialogVoltageDecision == 12) {
          if (digitalRead(Relay12VA) == LOW) {
            digitalWrite(Relay12VA, HIGH);
          } else {
            digitalWrite(Relay12VA, LOW);
          }
        }
      }
      if (AIInterpreter.indexOf("#191") >= 0) {
        if (RelayDialogVoltageDecision == 5) {
          //if (digitalRead(Relay5VB) == LOW) {
          //  digitalWrite(Relay5VB, HIGH);
          //} else {
          //  digitalWrite(Relay5VB, LOW);
          //}
        }
        if (RelayDialogVoltageDecision == 12) {
          //if (digitalRead(Relay12VB) == LOW) {
          //  digitalWrite(Relay12VB, HIGH);
          //} else {
          //  digitalWrite(Relay12VB, LOW);
          //}
        }
      }

      // Dome directional commands

      // MOVI hardware commands
      if (AIInterpreter.indexOf("#199") >= 0) { // MOVI Threshold
        AI.println(F("To what threshold level?"));
        AI.println(F("ASK"));
      }
      if (AIInterpreter.indexOf("#200") >= 0) { // MOVI Volume
        AI.println(F("To what threshold level?"));
        AI.println(F("ASK"));
      }
      if (AIInterpreter.indexOf("#201") >= 0) { // MOVI Responses on
        AI.println(F("RESPONSES ON"));
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Responses Enabled"));
        }
      }
      if (AIInterpreter.indexOf("#202") >= 0) { // MOVI Responses off
        AI.println(F("RESPONSES OFF"));
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Responses Disabled"));
        }
      }
      if (AIInterpreter.indexOf("#203") >= 0) { // MOVI Welcome message on
        AI.println(F("WELCOMEMESSAGE ON"));
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("Welcome message enabled"));
        }
      }
      if (AIInterpreter.indexOf("#204") >= 0) { // MOVI Welcome message off
        AI.println(F("WELCOMEMESSAGE OFF"));
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Welcome message disabled"));
        }
      }
      if (AIInterpreter.indexOf("#205") >= 0) { // MOVI Promt beeps on
        AI.println(F("BEEPS ON"));
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("Feedback beeps enabled"));
        }
      }
      if (AIInterpreter.indexOf("#206") >= 0) { // MOVI Promt beeps off
        AI.println(F("BEEPS OFF"));
        if (TranslationMode == 0) {
          PlayRandomMP3(Beeps);
        } else {
          AI.println(F("SAY Feedback beeps disabled"));
        }
      }

      /* Dome Periscope Controls */
      if (AIInterpreter.indexOf("#207") >= 0 || AIInterpreter.indexOf("#208") >= 0) { // Open / Extend

      }
      if (AIInterpreter.indexOf("#209") >= 0 || AIInterpreter.indexOf("#210") >= 0) { // Close / Retract

      }

      /* Life Form Controls */
      if (AIInterpreter.indexOf("#211") >= 0 || AIInterpreter.indexOf("#212") >= 0) { // Open / Extend

      }
      if (AIInterpreter.indexOf("#213") >= 0 || AIInterpreter.indexOf("#214") >= 0) { // Close / Retract

      }

      if (AIInterpreter.indexOf("#215") >= 0 || AIInterpreter.indexOf("#216") >= 0 || AIInterpreter.indexOf("#217") >= 0) { // Start scanning

      }

      if (AIInterpreter.indexOf("#218") >= 0) { // Stop scanning

      }

      /* Dome Zapper */
      if (AIInterpreter.indexOf("#219") >= 0 || AIInterpreter.indexOf("#220") >= 0) { // Open / Extend

      }

      if (AIInterpreter.indexOf("#221") >= 0 || AIInterpreter.indexOf("#222") >= 0) { // Close / Retract

      }

      /* Fire Extinguisher */
      if (AIInterpreter.indexOf("#223") >= 0) { // Open

      }

      if (AIInterpreter.indexOf("#224") >= 0) { // Close

      }

      if (AIInterpreter.indexOf("#225") >= 0 || AIInterpreter.indexOf("#226") >= 0) { // Shoot / Spray

      }

      /* Light Saber Launcher */
      if (AIInterpreter.indexOf("#227") >= 0) { // Open

      }

      if (AIInterpreter.indexOf("#228") >= 0) { // Close

      }

      if (AIInterpreter.indexOf("#229") >= 0 || AIInterpreter.indexOf("#230") >= 0) { // Shoot / Launch

      }

      /* Arc Zapper */
      if (AIInterpreter.indexOf("#231") >= 0 || AIInterpreter.indexOf("#232") >= 0) { // Open / Extend

      }

      if (AIInterpreter.indexOf("#233") >= 0 || AIInterpreter.indexOf("#234") >= 0) { // Close / Retract

      }

      /* Computer Interface Arm */
      if (AIInterpreter.indexOf("#235") >= 0 || AIInterpreter.indexOf("#236") >= 0) { // Open / Extend

      }

      if (AIInterpreter.indexOf("#237") >= 0 || AIInterpreter.indexOf("#238") >= 0) { // Close / Retract

      }

      /* Gripper Arm */
      if (AIInterpreter.indexOf("#239") >= 0 || AIInterpreter.indexOf("#240") >= 0  || AIInterpreter.indexOf("#241") >= 0) { // Open / Extend / Lift

      }

      if (AIInterpreter.indexOf("#242") >= 0 || AIInterpreter.indexOf("#243") >= 0 || AIInterpreter.indexOf("#244") >= 0) { // Close / Retract / Lower

      }

      /* Hyperdrive Arm */
      if (AIInterpreter.indexOf("#245") >= 0 || AIInterpreter.indexOf("#246") >= 0) { // Open / Extend

      }

      if (AIInterpreter.indexOf("#247") >= 0 || AIInterpreter.indexOf("#248") >= 0) { // Close / Retract

      }

      /* Magnetic Grabber Arm */
      if (AIInterpreter.indexOf("#249") >= 0 || AIInterpreter.indexOf("#250") >= 0) { // Open / Extend

      }

      if (AIInterpreter.indexOf("#251") >= 0 || AIInterpreter.indexOf("#252") >= 0) { // Close / Retract

      }

      /* Booster rockets */
      if (AIInterpreter.indexOf("#253") >= 0 || AIInterpreter.indexOf("#254") >= 0 || AIInterpreter.indexOf("#255") >= 0 || AIInterpreter.indexOf("#256") >= 0) { // Open / Extend

      }

      if (AIInterpreter.indexOf("#257") >= 0 || AIInterpreter.indexOf("#258") >= 0 || AIInterpreter.indexOf("#259") >= 0 || AIInterpreter.indexOf("#260") >= 0) { // Close / Retract

      }

      AIInterpreter = "";
    } else {
      AIInterpreter += (char) AIStream;
    }
  }
}

void AIAsk(char text) {
  AI.println("ASK" + text);
}
