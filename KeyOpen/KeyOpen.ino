/*
 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * Released into the public domain.
 *
 * Sample program showing how to read data from a PICC using a MFRC522 reader on the Arduino SPI interface.
 *----------------------------------------------------------------------------- empty_skull 
 * Aggiunti pin per arduino Mega
 * add pin configuration for arduino mega
 * http://mac86project.altervista.org/
 ----------------------------------------------------------------------------- Nicola Coppola
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     10               53                SDA
 * SPI MOSI   11               51                MOSI
 * SPI MISO   12               50                MISO
 * SPI SCK    13               52                SCK
 *
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 
 */

#include <SPI.h>
#include <MFRC522.h>
#include "pitches.h"

#define SS_PIN 10
#define RST_PIN 9
#define buzzer 8
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.

void sirena(){
  for (int thisNote = 200; thisNote < 2000; thisNote++) {
    tone(buzzer, thisNote, 32);
    //delay(5);
    }
    for (int thisNote = 2000; thisNote > 200; thisNote--) {
      tone(buzzer, thisNote, 32);
      //delay(5);
      }
}

int melody[] = {
  NOTE_G5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_F5, NOTE_E5,NOTE_D5, NOTE_C5, 0,
  NOTE_A4, NOTE_C5, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_F4, NOTE_E4,NOTE_D4, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 8,
  4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4
};

void elochka(){
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 23; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
  }
}

void setup() {
	Serial.begin(9600);	// Initialize serial communications with the PC
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();	// Init MFRC522 card
	Serial.println("Scan PICC to see UID and type...");
}

void loop() {
	// Look for new cards
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
 Serial.print("Alarm!!!   ");Serial.print("UID: "); Serial.println(mfrc522.uid.uidByte[0], HEX);
if (mfrc522.uid.uidByte[0]==0x50)  sirena();
if (mfrc522.uid.uidByte[0]==0xBB)  elochka();
 
}
