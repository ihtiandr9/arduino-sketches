/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialEvent
*/

#include "MenuSystem.h"
#define actionFileNew  100
#define actionEdit  101
#define actionAbout 102
#define actionTop   200

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

pMenuSystem mainMenu;
MenuIterator currentlevel;
//String menu[3] = {"\n[0]-File \n[1]- Edit \n[2]-exit", "\n[0]-Save \n[1]-Print \n[2]-exit", "\n[0]-Copy \n[1]-Paste \n[2]-exit"};


void setupMenu(){
// Serial.print(menu[inputString.toInt()]);
mainMenu = new MenuSystem;
mainMenu->items = new MenuItem[3];;
mainMenu->count = 3;
mainMenu->items[0].text = "File";
mainMenu->items[0].action = 0;
mainMenu->items[1].text = "Edit";
mainMenu->items[1].action = actionEdit;
mainMenu->items[2].text = "About";
mainMenu->items[2].action = actionAbout;

pMenuSystem fileMenu = new MenuSystem;
fileMenu->items = new MenuItem[2];
fileMenu->count = 2;
fileMenu->parentMenu = mainMenu;
fileMenu->items[0].text = "New";
fileMenu->items[0].action = actionFileNew;
fileMenu->items[1].text = "Top";
fileMenu->items[1].action = actionTop;
mainMenu->items[0].childMenu = fileMenu;
}

void onMenuSelect(MenuSystem* level, int selected){
 if(level->items[selected].childMenu){
        currentlevel.GoInto(level->items[selected].childMenu);
        currentlevel.Print();
      }else{  
  lcd.clear();
  //lcd.autoscroll();
  lcd.print("Selected action ");
  lcd.setCursor(0, 1);
  lcd.print(level->items[selected].text);
  //lcd.noAutoscroll();
  //lcd.println(selected);
  }
  if(level->items[selected].action == actionTop){
    currentlevel.GoInto(level->parentMenu);
    currentlevel.currentItem = 0;
    currentlevel.Print();
  }  
}
  
void setup() {
  // initialize serial:
  Serial.begin(9600);
  lcd.begin(16, 2);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  setupMenu();
  currentlevel.GoInto(mainMenu);
  currentlevel.Print();
  currentlevel.connectActions(onMenuSelect);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    if(inputString== String("s")) {
      currentlevel.Select();
    } else {
      currentlevel.MoveDown();
    }
    //printMenu();
    //lcd.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;    
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    //Serial.print(inChar);    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n'|inChar == '\r') {
      stringComplete = true;
    }else{inputString += inChar;}
  }
}
