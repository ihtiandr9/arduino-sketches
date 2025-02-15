/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#define buzzer 8

#include "pitches.h"


void setup() {
for (int thisNote = 0; thisNote < 1000; thisNote++) {
    tone(buzzer, thisNote, 32);
    //delay(5);
  }
 for (int thisNote = 1000; thisNote > 0; thisNote--) {
    tone(buzzer, thisNote, 32);
    //delay(5);
  }
}

void loop() {
  
}
