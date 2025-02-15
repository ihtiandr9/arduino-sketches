
#define period 5000 //ms
#define positivePin 12
#define negativePin 11
#define motorEnPin 9

long int cnt;
bool dir;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  cnt = 0;
  dir = 0;
}

void loop() {
  int powMotor;
  cnt = 512 - analogRead(A0);
  dir = cnt>0;
  if (dir){
    powMotor = cnt/2;
  }else{
    powMotor = cnt / (-2);
  }
  
    digitalWrite(positivePin, dir);
    digitalWrite(negativePin, !dir);
    analogWrite(motorEnPin, powMotor);
    Serial.println(powMotor);
  }
