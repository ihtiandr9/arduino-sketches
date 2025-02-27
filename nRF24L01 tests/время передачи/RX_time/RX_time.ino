/* В данном скетче с передающей части (ТХ) отправляется значение переменной counter,
 * переменная эта с каждым шагом увеличивается на единицу. Приёмник (RX) принимает
 * сигнал, и отправляет обратно то, что получил, используя функцию radio.writeAckPayload
 * То есть наш приёмник на одно мгновение становится передатчиком! Если наш передатчик (TX)
 * принимает ответный сигнал, он выдаёт то, что принял, и пишет посчитанное вермя между 
 * отправкой и приёмом сигнала в микросекундах. Данный скетч можно использовать для теста
 * модулей на качество связи, а также для понимания работы функции radio.writeAckPayload
 * by AlexGyver 2016
 */
 
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include  "printf.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей
RF24 radio(9,10); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

uint64_t address[3] = { 0xABCDABCD00LL, 0x544d52687CLL, 0xABCDABCD71LL};
bool justrecv=true;

void nrf24ini(){
  radio.begin(); //активировать модуль
  
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0,15);     //(время между попыткой достучаться, число попыток)
 // radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах
  radio.setCRCLength(RF24_CRC_16);
  radio.setChannel(0x4c);  //выбираем канал (в котором нет шумов!)
  radio.openWritingPipe(address[1]);      //труба трансмиттер
  radio.openReadingPipe(1,address[0]);      //на трубе 1 повешаем базовый адрес
  radio.openReadingPipe(4,address[2]);      //на трубе 4 слушаем
    
 // radio.setPALevel (RF24_PA_MIN); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  // ВНИМАНИЕ!!! enableAckPayload НЕ РАБОТАЕТ НА СКОРОСТИ 250 kbps!
  radio.powerUp(); //начать работу
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль 
  radio.printDetails();  
  }
  void lcdini(){
      lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("iarduino.ru");
  lcd.setCursor(8, 1);
  lcd.print("LCD 1602");
    }
void setup(){
  Serial.begin(57600); //открываем порт для связи с ПК
  printf_begin();
  nrf24ini();
  lcdini();
}

long tic=millis();
void loop(void) {    
    byte pipeNo, gotByte;                          
    char str1[16];
    while( radio.available(&pipeNo)){    // слушаем эфир со всех труб
     radio.read( &gotByte, 1 );         // чиатем входящий сигнал
     radio.writeAckPayload(pipeNo,&gotByte, 1 );  // отправляем обратно то что приняли
     sprintf(str1,"Recv:%d pipeNO:%d", gotByte,pipeNo);
     lcd.setCursor(0, 1);  lcd.print(str1); tic=millis();
   }
   if(millis()-tic>3000){lcd.setCursor(0, 1);  lcd.print("Nothing recieved");}
}
