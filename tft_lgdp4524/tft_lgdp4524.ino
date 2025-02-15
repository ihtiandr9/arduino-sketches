
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made for modules with a screen resolution
// of 176X220 pixels.
//
// This program requires the UTFT library.

//Demo for
//by Open-Smart Team and Catalex Team
//catalex_inc@163.com
//Store: open-smart.aliexpress.com
//      http://dx.com
//Demo Function:


#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
//***********************************************//
// If you use OPEN-SMART TFT breakout board                 //
// You need to add 5V-3.3V level converting circuit.
// Of course you can use OPEN-SMART UNO Black version with 5V/3.3V power switch,
// you just need switch to 3.3V.
// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
//----------------------------------------|
// TFT Breakout  -- OPEN-SMART UNO Black /Red
// GND              -- GND
// 3V3               -- 3.3V
// CS                 -- A3
// RS                 -- A2
// WR                -- A1
// RD                 -- 3.3V
// RST                -- A0
// LED                -- GND
// DB0                -- 8
// DB1                -- 9
// DB2                -- 10
// DB3                -- 11
// DB4                -- 4
// DB5                -- 13
// DB6                -- 6
// DB7                -- 7

//
// Remember to change the model parameter to suit your display module!
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_RS A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RST A0 // 

//  Пример считывания текущего времени                      //
//
//  Раскомментируйте для программной реализации шины I2C:   //
//  #define pin_SW_SDA 3                                    // Назначение любого вывода Arduino для работы в качестве линии SDA программной шины I2C.
//  #define pin_SW_SCL 9                                    // Назначение любого вывода Arduino для работы в качестве линии SCL программной шины I2C.
//  Раскомментируйте для совместимости с большинством плат: //
//  #include <Wire.h>                                       // Библиотека iarduino_RTC будет использовать методы и функции библиотеки Wire.
//  Ссылки для ознакомления:                                //
//  Подробная информация о подключении модуля к шине I2C:   // http://wiki.iarduino.ru/page/i2c_connection/
//  Подробная информация о функциях и методах библиотеки:   // http://wiki.iarduino.ru/page/chasy-realnogo-vremeni-rtc-trema-modul/
//


UTFT tft(0x9225, LCD_RS, LCD_WR, LCD_CS, LCD_RST);

void setup()
{
  randomSeed(analogRead(0));
  delay(300);                                             // Ждем готовности модуля отвечать на запросы
  Serial.begin(9600);                                     // Инициируем передачу данных в монитор последовательного порта на скорости 9600 бод.
  // Setup the LCD
  tft.InitLCD();
  tft.setFont(SmallFont);
  tft.clrScr();

  tft.setColor(255, 0, 0);
  tft.fillRect(0, 0, 219, 13);
  tft.setColor(64, 64, 64);
  tft.fillRect(0, 162, 219, 175);
  tft.setColor(255, 255, 255);
  tft.setBackColor(255, 0, 0);
  tft.print("** Universal TFT Library **", CENTER, 1);
  tft.setBackColor(64, 64, 64);
  tft.setColor(255, 255, 0);
  tft.print("My clock projekt (ihtiandr9)", CENTER, 163);

  tft.setColor(0, 0, 255);
  tft.drawRect(0, 14, 219, 161);
}

void loop()
{
  int buf[218];
  int x, x2;
  int y, y2;
  int r;

  // Clear the screen and draw the frame
  if (millis() % 1000 == 0) {                             // Если прошла 1 секунда.


    Serial.println("in loop \r\n");      // Выводим время.
    tft.print("in loop", CENTER, 63);
    delay(1);                                             // Приостанавливаем скетч на 1 мс, чтоб не выводить время несколько раз за 1мс.
  }
}
