/*
 * create by straysnail
 * 2022/11/11
 */
#define ledPin 3  //Define the pin of LED lamp
#define btnPin1 2  //Define the button pin
#define btnPin2 4  //Define the button pin
//The variable is used to receive the value of the button
boolean btnVal1;
boolean  btnVal2;   

void setup() {
  Serial.begin(9600);
  pinMode(btnPin1,INPUT);  //Set the pin to input state
  pinMode(btnPin2,INPUT);  //Set the pin to input state
  pinMode(ledPin, OUTPUT);
}

void loop() {
  btnVal1 = digitalRead(btnPin1);  //Read the value of the button and assign it to btnVal1
  btnVal2 = digitalRead(btnPin2);  //Read the value of the button and assign it to btnVal2
  Serial.println(btnVal2);
  if(btnVal1 == 0)  //If function, and it means that if button 1 is pressed.
  {
    digitalWrite(ledPin, HIGH);  //LED is on
  }
  if(btnVal2 == 0)  //If button 2 is pressed
  { 
    digitalWrite(ledPin, LOW);  //LED is off
  }
}
