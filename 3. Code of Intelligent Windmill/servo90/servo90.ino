#include <Servo.h>
Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myservo.write(90);  // tell servo to go to position in variable 'pos'
}
