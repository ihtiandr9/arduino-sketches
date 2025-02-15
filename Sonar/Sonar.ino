#include <NewPing.h>
#include <TM1638.h>

#define TRIGGER_PIN 3

#define ECHO_PIN 2

#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Настройка пинов и максимального расстояния.

// define a module on data pin 8, clock pin 9 and strobe pin 7
TM1638 module(8, 9, 7);

void setup() {
  // display a hexadecimal number and set the left 4 dots
  module.setDisplayToHexNumber(0x1234ABCD, 0xF0);
}

void loop() {
  byte keys = module.getButtons();

  // light the first 4 red LEDs and the last 4 green LEDs as the buttons are pressed
  module.setLEDs(((keys & 0xF0) << 8) | (keys & 0xF));
  delay(250);
  unsigned int uS = sonar.ping_cm();
  
  module.setDisplayToDecNumber(uS,0);
  Serial.print(uS);
  Serial.println("cm");

}
//-----------------


