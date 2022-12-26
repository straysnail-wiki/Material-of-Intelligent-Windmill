/*
create by straysnail
2022/11/11
*/
void setup() {
  pinMode(3,OUTPUT); //Set pin 3 to output state
}

void loop() {
  //Control LED to light up gradually
  for(int i=0; i<255; i++) {
    analogWrite(3,i); //Analog output function
    delay(10);
  }
  //Control LED to darken gradually
  for(int i=255; i>0; i--) {
    analogWrite(3,i); //Analog output function
    delay(10);
  }
}
