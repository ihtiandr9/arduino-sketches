 /*
   Пример вывода на дисплей с регистром TM1637
   показывает все возможности библиотеки GyverTM1637
   AlexGyver Technologies http://alexgyver.ru/
*/

#define CLK 2
#define DIO 3

#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);

uint32_t Now, clocktimer;
boolean flag;

void setup() {
  Serial.begin(115200);
  disp.clear();
  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  Now = millis();
  clocktimer = 1;
}

void loop() {
twistClock();
test();
}

void test(){
  byte hrs, mins;
  hrs  = clocktimer / 100;
  mins = clocktimer % 512;
  if (millis() - Now > 1000){    
    disp.displayByte(3, mins);    // выводим время
    clocktimer *= 2;
    Now = millis();
    Serial.println(hrs);
    Serial.println(mins);
    Serial.println(clocktimer);
  }  
  
}

void twistClock() {
  byte hrs = 21, mins = 55;
  uint32_t tmr;
  Now = millis();
  while (millis () - Now < 10000) {   // каждые 10 секунд
    if (millis() - tmr > 500) {       // каждые полсекунды
      tmr = millis();
      flag = !flag;
      disp.point(flag);   // выкл/выкл точки

      if (flag) {
        // ***** часы! ****
        mins ++;
        if (mins > 59) {
          mins = 0;
          hrs++;
          if (hrs > 24) hrs = 0;
        }
        // ***** часы! ****
        disp.displayClock(hrs, mins);    // выводим время
      }
    }
  }
  disp.point(0);   // выкл точки
}
