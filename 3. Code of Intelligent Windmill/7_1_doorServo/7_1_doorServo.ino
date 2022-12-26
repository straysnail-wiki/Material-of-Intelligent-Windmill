/*
 * create by straysnail
 * 2022/11/24
 */
#define door_servoPin 9  //Set the pin of the steering gear
int pulsewidth = 0; //Variable: used to calculate the pulse value of the steering gear

void setup() {
  pinMode(door_servoPin,OUTPUT); //Set the pin to output state
}

void loop() {
  procedure(door_servoPin, 130);  //Turn the steering gear to 130 degrees and open the door
  delay(500);      //Time for the steering gear to turn
  procedure(door_servoPin, 50);  //Turn the steering gear to 50 degrees and close the door
  delay(500);
}

//Function to control the angle of steering gear according to the principle of steering fear
void procedure(int serPin, int myangle)   //There are 2 parameters of the function, serPin is the pin of the steering gear, and myangle is the angle of the steering gear
{
  for(int i=0; i<10; i++)
  {
    //Calculate the pulse value, that is, the high level time. The range of myangle is 0-180, and the corresponding pulse width range is 500-2480
    pulsewidth = myangle * 11 + 500;  
    digitalWrite(serPin,HIGH);
    delayMicroseconds(pulsewidth);  //Delay calculated high level time
    digitalWrite(serPin,LOW); //Set to low level
    delay((20 - pulsewidth / 1000));  //Delay the remaining low level time
  }
}
