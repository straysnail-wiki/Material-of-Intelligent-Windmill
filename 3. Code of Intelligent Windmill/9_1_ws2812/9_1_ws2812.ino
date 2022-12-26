#include <Adafruit_NeoPixel.h>
#define Neo_PIN  A0  //Define the pin
#define NUMPIXELS  11 //Define the LED number
//Declare our NeoPixel strip object
Adafruit_NeoPixel pixels(NUMPIXELS, Neo_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(A0, OUTPUT);
  pixels.begin(); // Initialize NeoPixel
}

void loop() {
  //Use the for statement to make all LED on
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));//Set the pin of the LED and RGB color
  }
  pixels.show();//Set the pin of the LED and RGB color
  delay(500);
  pixels.clear(); //Clean up
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 0, 0)); 
  }
  pixels.show();
  delay(500);
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
  }
  pixels.show();
  delay(500);
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 150, 0));
  }
  pixels.show();
  delay(500);
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 150));
  }
  pixels.show();
  delay(500);
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 150, 150));
  }
  pixels.show();
  delay(500);
  pixels.clear();
}
