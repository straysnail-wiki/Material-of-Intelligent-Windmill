/*
create by straysnail
2022/11/11
*/
void setup() {  //Initial function, the program will only run once
  pinMode(3,OUTPUT); //Set pin 3 to output state
}

void loop() {  //Cyclic function, the program will run circularly all the time
  digitalWrite(3,HIGH); //Digital output function, controlling pin 3 output high level
  delay(300); //Delay 300ms
  digitalWrite(3,LOW);  //controlling pin 3 output low level
  delay(300);
}
