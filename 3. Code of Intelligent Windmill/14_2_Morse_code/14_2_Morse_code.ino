#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#include "OneButton.h"
// Setup a new OneButton on pin 2
OneButton button1(2, true);
// Setup a new OneButton on pin 4
OneButton button2(4, true);

int count1;
int count2;
String passward = ".._.";  //password
String E_passward = "";  //Store the entered password

#define door_servo 9  //door PIN
int pulsewidth = 0; //

void setup() {
  Serial.begin(9600);
  pinMode(door_servo, OUTPUT);
  procedure(door_servo, 50); //close the door
  delay(500);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Clear the buffer
  display.clearDisplay();
  display.display();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Enter the password"));
  display.display();
  delay(1000);
  
  // link the button 1 functions.
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);
  button1.attachDuringLongPress(longPress1);

  // link the button 2 functions.
  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
  button2.attachLongPressStop(longPressStop2);
  button2.attachDuringLongPress(longPress2);
  
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,10);             // Start at top-left corner
}

void loop() {
  // keep watching the push buttons:
  button1.tick();
  button2.tick();
}

// ----- button 1 callback functions

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  Serial.print(".");
  E_passward = E_passward + ".";  //input . 
  display.setTextSize(2);             // Normal 1:2 pixel scale
  display.print(F("."));
  display.display();
} // click1


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
} // doubleclick1


// This function will be called once, when the button1 is pressed for a long time.
void longPressStart1() {
  //Serial.println("Button 1 longPress start");
} // longPressStart1


// This function will be called often, while the button1 is pressed for a long time.
void longPress1() {
  //Serial.println("Button 1 longPress...");
} // longPress1


// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop1() {
  Serial.print("_");
  E_passward = E_passward + "_";  //input _
  display.setTextSize(2);             // Normal 1:2 pixel scale
  display.print(F("_"));
  display.display();
} // longPressStop1


// ... and the same for button 2:

void click2() {
  Serial.println("Determine the password");
  Serial.println(E_passward);
  //door_servo.write(120);
  delay(100);
  if(E_passward == passward)
  {
    procedure(door_servo, 140); //open the door
    delay(500);
    display.clearDisplay();
    display.display();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("successful"));
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.println(F("Long press button 2 to close the door"));
    display.display();
  }
  else
  {
    Serial.println("Wrong password. Please re-enter it");
    display.clearDisplay();
    display.display();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("Error"));
    display.display();
    delay(1000);

    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("Enter the password"));
    display.display();
  }
  E_passward = ""; //clear the password
} // click2


void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
} // doubleclick2


void longPressStart2() {
  Serial.println("Button 2 longPress start");
} // longPressStart2


void longPress2() {
  Serial.println("Button 2 longPress...");
} // longPress2

void longPressStop2() {
  Serial.println("close the door");
  procedure(door_servo, 56); //close the door 
  E_passward = ""; //claer the password
  display.clearDisplay();
  display.display();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Enter the password"));
  display.display();
} // longPressStop2

//control the servo
void procedure(int serPin, int myangle)
{
  int i = 0;
  while(i<10)
  {
    pulsewidth = myangle * 11 + 500;  
    digitalWrite(serPin,HIGH);
    delayMicroseconds(pulsewidth); 
    digitalWrite(serPin,LOW);
    delay((20 - pulsewidth / 1000));
    i++;
  }
}
