#include <Servo.h>  //Import the library files of steering gear
Servo windowServo;  //Create a steering gear instance to control a steering gear

void setup() {
  windowServo.attach(10,500,2500);  //Set the pin of the steering gear as 10, and the pulse range is 500-2500ms
}

void loop() {
  windowServo.write(50);   //Turn the steering gear to 50 degrees and open the window
  delay(500);   //Delay for the steering gear to turn
  windowServo.write(130);  //Turn the steering gear to 130 degrees and close the window
  delay(700);
}
