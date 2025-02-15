
#include <LiquidCrystal_I2C.h>
#include <TM1638.h>
#include <InvertedTM1638.h>
#include <IRremote.h>
#include <Stepper.h>

#define VEL A0
#define STEP 3
#define NO_MODULES  1
#define IR_Recv_Pin    8
#define in1Pin  12
#define in2Pin  11
#define in3Pin  10
#define in4Pin  9
#define motorStep 5
#define StepsInRound 160


decode_results results;
//Counter - переменная для хранения значения счетчика
volatile unsigned int motorSpeed;

//Временные переменные для хранения уровней сигналов энкодера
volatile unsigned char encoder_A, encoder_B, encoder_A_prev;

byte modes[NO_MODULES];

int IRKey;
int direkt;
int cntRead;
//Объекты

// define a regular module and a inverted module
TM1638 module1(4 ,5, 6);
TM1638* modules[NO_MODULES] = {
  &module1
  //, &module2
};
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

IRrecv irrecv(IR_Recv_Pin); // указываем вывод, к которому подключен приемник

Stepper motor(StepsInRound, in1Pin, in2Pin, in3Pin, in4Pin);

void setup() {
  Serial.begin(9600);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(VEL, INPUT);

  motorSpeed = 25;
  for (int i = 0; i < NO_MODULES; i++) {
    modules[i]->setupDisplay(true, 7);
    modes[i] = 0;
  }
  lcd.init();
  lcd.backlight();
  irrecv.enableIRIn(); // запускаем прием
  cntRead = 100;
  direkt=motorSpeed;
}

void loop() {
  char s[8];  
  motor.setSpeed(motorSpeed);
  sprintf(s, "cntr%04d", motorSpeed);
  modules[0]->setDisplayToString(s);
  if ( irrecv.decode( &results )) { // если данные пришли
    IRKey = results.value;
    Serial.println( IRKey, HEX ); // печатаем данные
    lcd.setCursor(0,0);  lcd.print("IR key:");
    
    sprintf(s, "  %0xh", results.value);
    //lcd.setCursor(0,1);  lcd.print(s);
    irrecv.resume(); // принимаем следующую команду
    switch(IRKey){
      case 0x18e7:
            SetMotor(motorStep);            
            break;
      case 0x4ab5:
            SetMotor(-motorStep);
            break; 
      case 0x6897:
            SetMotor(0);            
            break;                       
      case 0xB04f:
            motorSpeed = 25;
            break;                       
      case 0x5aa5:
            motorSpeed ++;                       
            break;
      case 0x10EF:
            motorSpeed --;                       
    }  
    if(motorSpeed <= 2){
        motorSpeed = 1;
    }
  } 
 // if(cntRead <= 0){
    motorSpeed = analogRead(VEL);
    motorSpeed = map(motorSpeed/4,1,1023,25,500);
    
    cntRead = 100;
    motor.step(direkt);   
    Serial.println( motorSpeed); // печатаем данные
  //}  
  cntRead--;
}     

 void SetMotor(int _step){
  direkt = _step;
}           
