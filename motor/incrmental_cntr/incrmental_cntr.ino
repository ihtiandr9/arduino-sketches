
#include <Stepper.h>
#include <Servo.h>

#define in1Pin  13
#define in2Pin  11
#define in3Pin  10
#define in4Pin  9
#define motorStep 5
#define StepsInRound 64
int motorSpeed = 10;
Stepper motor(StepsInRound, in1Pin, in2Pin, in3Pin, in4Pin);

void setup() {
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  
}

void loop() {
  motor.setSpeed(motorSpeed);
  motor.step(10);delay(160/motorSpeed);
}     
