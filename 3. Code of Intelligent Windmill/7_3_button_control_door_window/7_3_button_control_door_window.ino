/*
 * create by straysnail
 * 2022/2/26
 */
#include <Servo.h>  //Import the library files of steering gear
Servo door_servo;  //Create a steering gear instance to control the door steering gear
Servo window_servo;  //Create a steering gear instance to control the window steering gear
#define btnPin1 2 //IO port of the button
#define btnPin2 4
boolean btnVal1 = 0; //Used to receive the button value
boolean btnVal2 = 0;
int count1 = 0;  //Calculate the click times of the button
int count2 = 0;
boolean door_state = 0; //Control the door state
boolean window_state = 0; //Control the window state

void setup() {
  Serial.begin(9600);
  pinMode(btnPin1,INPUT);
  pinMode(btnPin2,INPUT);
  door_servo.attach(9,500,2500);  //Set the pin of the steering gear as 9, and the pulse range is 500-2500ms
  window_servo.attach(10,500,2500);  //Set the pin of the steering gear as 10, and the pulse range is 500-2500ms
  door_servo.write(50); //Close the door
  delay(300);
  door_servo.write(130);   //Open the door
  delay(500);   //Delay for the steering gear to turn
  window_servo.write(130); //Close the window
  delay(300);
  window_servo.write(50);  //Open the window
  delay(500);
  door_servo.write(50); //Close the door
  delay(300);
  window_servo.write(130); //Close the window
  delay(300);
}

void loop() {
  btnVal1 = digitalRead(btnPin1);  //Read the value of the button
  btnVal2 = digitalRead(btnPin2);
  if(btnVal1 == 0)  //If button 1 is pressed
  {
    delay(10); //Eliminate wrong judgement caused by the shake of the button
    if(btnVal1 == 0)
    {
      boolean i1 = 1;
      while(i1 == 1)
      {
        btnVal1 = digitalRead(btnPin1);
        if(btnVal1 == 1)  //Button 1 is released
        {
          count1 = count1 + 1; //Record the click times
          Serial.print("button1 = ");
          Serial.println(count1);
          door_state = count1 % 2; //Calculate the remainder. If it is singular, the value is equal to 1, and if it is even, the value is equal to 0
          if(door_state == 1)
          {
            door_servo.write(130); //Open the door
            delay(300);
          }
          else
          {
            door_servo.write(50); //Close the door
            delay(300);
          }
          i1 = 0; //Exit the cycle with i = 0
        }
      }
    }
  }
  
  if(btnVal2 == 0)  //If button 2 is pressed
  {
    delay(10);
    if(btnVal2 == 0)
    {
      boolean i2 = 1;
      while(i2 == 1)
      {
        btnVal2 = digitalRead(btnPin2);
        if(btnVal2 == 1)  //Button 2 is released
        {
          count2 = count2 + 1; //Record the click times
          Serial.print("button2 = ");
          Serial.println(count2);
          window_state = count2 % 2; //Calculate the remainder. If it is singular, the value is equal to 1, and if it is even, the value is equal to 0
          if(window_state == 1)
          {
            window_servo.write(50); //Open the window
            delay(300);
          }
          else
          {
            window_servo.write(130); //Close the window
            delay(300);
          }
          i2 = 0; //Exit the cycle with i = 0
        }
      }
    }
  }
}
