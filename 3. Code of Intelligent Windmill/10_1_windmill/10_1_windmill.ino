/*
 * create by straysnail
 * 2022/11/24
 */
#define INB 8  //Define pin 8 to control the direction
#define ENB 5  //Define pin 5 to control the speed

void setup() {
  pinMode(INB, OUTPUT);//Set the pin of controlling the motor to output
  pinMode(ENB, OUTPUT);
}

void loop() {
  anticlockwise();  //Rotate anticlockwise
  delay(2000);
  Stop();           //Stop
  delay(200);
  clockwise();      //Rotate clockwise
  delay(2000);
  Stop();           //Stop
  delay(200);
}

//Rotate anticlockwise
void anticlockwise()
{
  digitalWrite(INB, HIGH);  //Control the direction
  analogWrite(ENB, 50);    //Control the speed which range is 10-255
}
//Rotate clockwise
void clockwise()
{
  digitalWrite(INB, LOW);
  analogWrite(ENB, 100);
}
//Stop
void Stop()
{
  digitalWrite(INB, HIGH);
  analogWrite(ENB, 0);
}
