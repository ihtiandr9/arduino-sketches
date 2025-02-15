
#define POT A0
#define STEP 3

void setup() {
  Serial.begin(9600);
  pinMode(STEP, OUTPUT);
  pinMode(POT, INPUT);
}

void loop() {
int motorSpeed = analogRead(POT);

    motorSpeed = map(motorSpeed,1,1023,1,255);    
    analogWrite(STEP,motorSpeed);
    Serial.println(motorSpeed);
}     

            
