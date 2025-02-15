
char cur_pin;
unsigned int ms;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);  
  cur_pin=2;
}

// the loop function runs over and over again forever
void loop() {
  ms = analogRead(A0);
  Serial.println(ms);
  digitalWrite(cur_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(ms);                       // wait for a second
  cur_pin ++;
  if (cur_pin>4){
  cur_pin = 2;
   digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
   digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
   digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
   delay(ms);                       // wait for a second
  }
}
