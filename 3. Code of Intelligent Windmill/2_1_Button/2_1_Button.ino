/*
create by straysnail
2022/11/11
*/
#define btnPin1  2   //Macro define the pin name of button 1 as btnPin1, and the corresponding IO port is 2
boolean btnVal1;  //Define a bool type variable to receive the value of button 1
#define btnPin2  4   //Define the pin of button 2 as 4
boolean btnVal2;  //Define a bool type variable to receive the value of button 2

void setup() {
  Serial.begin(9600);  //Set the baud rate of serial communication to 9600
  pinMode(btnPin1, INPUT); //Set button pin as input type
  pinMode(btnPin2, INPUT);
}

void loop() {
  btnVal1 = digitalRead(btnPin1); //Read the value of the button and assign it to btnVal1
  btnVal2 = digitalRead(btnPin2); //Read the value of the button and assign it to btnVal2
  Serial.print("button1 = "); //Serial.print(); function is serial port printing
  Serial.print(btnVal1); //Print the value of button 1
  Serial.print("  ");
  Serial.print("button2 = ");
  Serial.println(btnVal2);  //Serial.println(); function is serial port newline printing
  delay(200);  //The delay is used to adjust the printing speed of the serial port
}
