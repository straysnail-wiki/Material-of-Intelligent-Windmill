#include <Servo.h>  //Import the library files of steering gear
Servo window_servo;  //Create a steering gear instance to control the window steering gear
#define waterPin A2  //Define the IO port of the raindrop sensor as A2
int waterVal = 0;

void setup() {
  Serial.begin(9600);  //Set the baud rate of serial communication to 9600
  pinMode(10, OUTPUT);
  pinMode(waterPin,INPUT);  //Set the pin to input
  window_servo.attach(10,500,2500);  //Set the pin of the steering gear as 10, and the pulse range is 500-2500ms

  window_servo.write(130);
  delay(300);
}

void loop() {
  waterVal = analogRead(waterPin);  //Read the analog value detected by the raindrop sensor
  Serial.print("waterVal = ");
  Serial.println(waterVal);  //Print the value detected by the raindrop sensor with new line
  //delay(200); //Delay to adjust the printing speed of serial port
  if(waterVal > 100)  //Greater than the set value, that is, when it rains
  {
    window_servo.write(130); //Close the window
    delay(300);
  }
  else
  {
    window_servo.write(50); //Open the window
    delay(300);
  }
}
