/*
 * create by straysnail
 * 2022/11/24
 */
#define INA 7  //Define pin 7 to control the direction
#define ENA 6  //Define pin 6 to control the speed


void setup() {
  pinMode(INA, OUTPUT);//Set the pin of controlling the motor to output
  pinMode(ENA, OUTPUT);
}

void loop() {
  butterfly();
}

//Rotate anticlockwise
void butterfly()
{
  digitalWrite(INA, HIGH);  //Control the direction
  analogWrite(ENA, 100);    //Control the speed whose range is 50-255
}
