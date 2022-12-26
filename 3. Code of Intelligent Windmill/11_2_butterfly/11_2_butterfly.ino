/*
 * create by straysnail
 * 2022/11/24
 */
#define INA 7  //Define pin 7 to control the direction
#define ENA 6  //Define pin 6 to control the speed
#define PIR_pin  A3   //Define the pin of pyroelectric sensor
boolean PIR_Val;  //Define a variable of bool type

void setup() {
  pinMode(INA, OUTPUT);//Set the pin of controlling the motor to output
  pinMode(ENA, OUTPUT);
  pinMode(PIR_pin, INPUT); //Set the pin to input
}

void loop() {
  PIR_Val = digitalRead(PIR_pin); //Read the value detected by the human body infrared pyroelectric sensor and assign it to PIR _Val
  if(PIR_Val == 1) {  //Person detected
    butterfly();  //The butterfly flutters
    delay(2000);  //Flutters for 2s
  } else {   //No person detected
    Stop();  //Stop
  }
}

//Rotate anticlockwise
void butterfly()
{
  digitalWrite(INA, HIGH);  //Control the direction
  analogWrite(ENA, 200);    //Control the speed whose range is 50-255
}
void Stop()
{
  digitalWrite(INA, LOW);
  analogWrite(ENA, 0);
}
