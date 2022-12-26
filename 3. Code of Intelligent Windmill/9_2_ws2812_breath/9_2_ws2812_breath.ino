#include <Adafruit_NeoPixel.h>
#define Neo_PIN  A0  //Define the pin
#define NUMPIXELS  11 //Define the LED number
//Declare our NeoPixel strip object
Adafruit_NeoPixel pixels(NUMPIXELS, Neo_PIN, NEO_GRB + NEO_KHZ800);
int brightness = 0; //The variable is used to set the lamp brightness, and the maximum brightness value is 255

void setup() {
  pixels.begin(); //Initialize NeoPixel
}

void loop() {
  //Realize the purple breathing lamp
  for(int bright_val=0;bright_val<256;bright_val++)
  {
    displayPiexls(NUMPIXELS, bright_val, 0, bright_val);
    pixels.show();//Display
    delay(10);
  }
  for(int bright_val=255;bright_val>0;bright_val--)
  {
    displayPiexls(NUMPIXELS, bright_val, 0, bright_val);
    pixels.show();//Display
    delay(10);
  }
}

//Set a function to control all the LED and their brightness
int displayPiexls(int num, int redVal, int greenVal, int blueVal)
{
  //Use for loop statement to make all LED on
  for(int i=0; i<num; i++) {
    pixels.setPixelColor(i, pixels.Color(redVal, greenVal, blueVal));//Set the pin of the LED and RGB color

  }
}
