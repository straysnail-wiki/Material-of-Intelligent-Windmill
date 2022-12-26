/*
create by straysnail
2022/11/14
*/
#define PIR_pin  A3   //Define the pin of pyroelectric sensor
boolean PIR_Val;  //Define a variable of bool type

void setup() {
  Serial.begin(9600);  //Set the baud rate of serial port communication as 9600
  pinMode(PIR_pin, INPUT); //Set the pin of the button to input
}

void loop() {
  PIR_Val = digitalRead(PIR_pin); //Read the button value and assign to PIR_Val
  Serial.print("PIR_Val = ");
  Serial.println(PIR_Val);
  delay(200);  //The delay is used to adjust the printing speed of the serial port
}
