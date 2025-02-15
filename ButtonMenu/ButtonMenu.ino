

/*

*/
#include <LiquidCrystal.h>
#include "MenuSystem.h"

//actions
#define actionFileNew  100
#define actionEdit  101
#define actionAbout 102
#define actionTop   200

//buttons pins
#define mode  8
#define setting  9
#define buzzer 13 //or signal led
#define LCD_Power 7

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
long mil;

pMenuSystem mainMenu;
MenuIterator currentlevel;
//String menu[3] = {"\n[0]-File \n[1]- Edit \n[2]-exit", "\n[0]-Save \n[1]-Print \n[2]-exit", "\n[0]-Copy \n[1]-Paste \n[2]-exit"};
byte mode_pressed;
byte setting_pressed;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(mode, INPUT_PULLUP);
  pinMode(setting, INPUT_PULLUP);
  pinMode(LCD_Power, INPUT_PULLUP);
  digitalWrite(LCD_Power,HIGH);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  setupMenu();
  currentlevel.GoInto(mainMenu);
  currentlevel.Print();
  currentlevel.connectActions(onMenuSelect);
  mil = millis();
}

void loop() {
    monitor_pins();
    if (millis() - mil > 10000) {
    }
}

void monitor_pins(){
  byte temp;
  
  temp = digitalRead(mode);
  if (mode_pressed & temp){ 
  currentlevel.MoveDown();
  tone(buzzer, 880, 1000/64);
  delay(250);
  }
  mode_pressed =!temp;

  temp = digitalRead(setting); 
  if (setting_pressed & temp){ 
  currentlevel.Select();
  tone(buzzer, 880, 1000/64);
  delay(250);
  }
   setting_pressed =!temp;
}

void setupMenu(){

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
