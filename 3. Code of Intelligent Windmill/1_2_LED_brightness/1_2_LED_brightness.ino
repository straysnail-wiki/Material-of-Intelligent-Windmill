/*
create by straysnail
2022/11/11
*/
void setup() {
  pinMode(3,OUTPUT); //Set pin 3 to output state
}

void loop() {
  analogWrite(3,50); //Analog output function with output value of 50 
  delay(300); //Delay 300ms
  analogWrite(3,120); //Analog output function with output value of 120
  delay(300);
  analogWrite(3,200); //Analog output function with output value of 200 
  delay(300);
  analogWrite(3,255); //Analog output function with output value of 255
  delay(300);
}
