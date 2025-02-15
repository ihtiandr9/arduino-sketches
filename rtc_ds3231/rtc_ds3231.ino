#include <iarduino_RTC.h>
#include <TM1638.h>

#define pDisp (&module)

//Объекты
iarduino_RTC time(RTC_DS3231);

// define a regular module and a inverted module
TM1638 module(4 ,5, 6);

long start_cnt;
//int cnt;
int buttons;
byte mode;
byte leds;
byte ldir;
byte button1_tic;
byte button2_tic;

void setup() {
  Serial.begin(9600);
  pDisp->setupDisplay(true, 7);  
  start_cnt = millis();
  time.begin();
  mode = 1;
  leds = 1;
}

void loop() {  
  
  time.gettime();
  
  if(millis()-start_cnt>1000){
    update_display();
    start_cnt = millis();
    if(leds & 0b10000000){
      ldir = 0;   
     }else{
      ldir = 1;
      }
  }
    //prepare next iteration;   
  
   leds = (leds << 1) + ldir;
   
//   cnt= cnt + 1;
   
  
  buttons = pDisp -> getButtons();
  
  if(buttons & 0b10000000) {
      button1_tic++;
    }else{
        button1_tic =0;
    }
    if(button1_tic>30){ 
      mode = mode xor 0b00000001;
      button1_tic =0;
    }
  if(buttons & 0b01000000) {
      button2_tic++;
    }else{
        button2_tic =0;
    }
    if(button2_tic>30){ 
      mode = mode xor 0b00000010;
      button2_tic =0;
    }
    //Serial.println(mode);
   pDisp->setLEDs(leds);   
  }
 
     
void update_display(){
  char s[9];    
  switch(mode){
    case 0:
    sprintf(s, time.gettime("dmY"));
    pDisp->setDisplayToString(s, 1<<6 | 1<<4);
    break;     
    case 1:
    sprintf(s, "%02dh%02dm%02d",time.hours,time.minutes,time.seconds);
    pDisp->setDisplayToString(s, ldir<<5); 
    break;
    default:
    sprintf(s, "defi %03d",mode);
    pDisp->setDisplayToString(s);
    Serial.println(s);
    
  }
}
