#include <NewTone.h>
#include<Adafruit_NeoPixel.h>
#define Neo_PIN  A0 
#define NUMPIXELS  11 
Adafruit_NeoPixel pixels(NUMPIXELS, Neo_PIN, NEO_GRB + NEO_KHZ800);
#include<Wire.h>

#define INA 7  
#define ENA 6 
#define INB 8 
#define ENB 5 
#define door_servo 9
#define window_servo 10
#define LED_pin 3
#define laser_pin 13
#define buzzerPin 11
#define lightPin A1

int seek_r,seek_g,seek_b;
int seek_ml = 150;
int seek_mr = 150;

char bleVal;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(door_servo, OUTPUT);
  procedure(door_servo, 50); //close the door
  delay(200);
  pinMode(window_servo, OUTPUT);
  procedure(window_servo, 130); //close the window
  delay(200);
  pinMode(INA, OUTPUT); 
  pinMode(ENA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(lightPin, INPUT);
  pinMode(Neo_PIN, OUTPUT);
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));//Set the pin and RGB color of the lamp
  }
  pixels.show();
  delay(300);
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
  } 
  pixels.show();
  delay(300);
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
  } 
  pixels.show();
  delay(1000);
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  } 
  pixels.show();
}

void loop() {
  SerialRead();
  parseData();
}

void(* resetFunc) (void) = 0;  //Software reset

void SerialRead()
{
  if(Serial.available() > 0)
  {
    String bleVal1 = Serial.readStringUntil('*');
    if(bleVal1[0] == '$')
    {
      bleVal = bleVal1[1];
      Serial.println(bleVal);
      //Control the red brightness of tunnel lights
      if(bleVal1[1] == 'F')
      {
        //The second beginning of the string converts the following characters to an integer, 
        //assigned to the variable seek_r
        seek_r = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        Serial.println(seek_r);
        displayPiexls(NUMPIXELS, seek_r, seek_g, seek_b);pixels.show();
      }
      //Control the green brightness of tunnel lights
      if(bleVal1[1] == 'G')
      {
        seek_g = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        Serial.println(seek_g);
        displayPiexls(NUMPIXELS, seek_r, seek_g, seek_b);pixels.show();
      }
      //Control the blue brightness of tunnel lights
      if(bleVal1[1] == 'H')
      {
        seek_b = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        Serial.println(seek_b);
        displayPiexls(NUMPIXELS, seek_r, seek_g, seek_b);pixels.show();
      }
      //Control windmill speed
      if(bleVal1[1] == 'm')
      {
        seek_ml = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        Serial.print("windmill");
        Serial.println(seek_ml);
        digitalWrite(INB, HIGH);
        analogWrite(ENB, seek_ml);
      }
      //Control butterfly speed
      if(bleVal1[1] == 'n')
      {
        seek_mr = String(String(bleVal1).substring(2,String(bleVal1).length())).toInt();
        Serial.print("butterfly");
        Serial.println(seek_mr);
        digitalWrite(INA, HIGH); 
        analogWrite(ENA, seek_mr); 
      }
    }
    
  }
}

void parseData()
{
  switch(bleVal)   //Each data control corresponding function
  {
    case 'a': digitalWrite(LED_pin, HIGH); break;
    case 'b': digitalWrite(LED_pin, LOW); break;
    case 'c': digitalWrite(laser_pin, HIGH); break;
    case 'd': digitalWrite(laser_pin, LOW); break;
    case 'e': procedure(door_servo, 130);break;
    case 'f': procedure(door_servo, 50); break;
    case 'g': procedure(window_servo, 50);break;
    case 'h': procedure(window_servo, 130);break;
    case 'i': NewTone(buzzerPin,532,250); break;
    case 'j': NewNoTone(buzzerPin); break;
    case 'k': play_music(buzzerPin); break;
    case 'l': NewNoTone(buzzerPin); resetFunc(); break;
    case '1': displayPiexls(NUMPIXELS, 150, 0, 0);pixels.show(); break;
    case '2': displayPiexls(NUMPIXELS, 255, 128, 0);pixels.show(); break;
    case '3': displayPiexls(NUMPIXELS, 255, 255, 0);pixels.show(); break;
    case '4': displayPiexls(NUMPIXELS, 0, 150, 0);pixels.show(); break;
    case '5': displayPiexls(NUMPIXELS, 0, 255, 255);pixels.show(); break;
    case '6': displayPiexls(NUMPIXELS, 0, 0, 150);pixels.show(); break;
    case '7': displayPiexls(NUMPIXELS, 138, 43, 226);pixels.show(); break;
    case '8': displayPiexls(NUMPIXELS, 150, 150, 150);pixels.show(); break;
    case '0': displayPiexls(NUMPIXELS, 0, 0, 0);pixels.show(); break;
    case 'A': breath_rgb(); break;
    case 'B': colorWipe(pixels.Color(255,0,0),100); colorWipe(pixels.Color(0,255,0),100);colorWipe(pixels.Color(0,0,255),100);break;
    case 'C': theaterChase(pixels.Color(127,127,127),50);theaterChase(pixels.Color(127,0,0),50);theaterChase(pixels.Color(0,0,127),50);break;
    case 'D': rainbow(10);break;
    case 'E': theaterChaseRainbow(50); break;                      
  }
}

void play_music(int buzzer_pin)
{
  NewTone(buzzer_pin,294,250);
  NewTone(buzzer_pin,440,250);
  NewTone(buzzer_pin,392,250);
  NewTone(buzzer_pin,532,250);
  NewTone(buzzer_pin,494,500);
  NewTone(buzzer_pin,392,250);
  NewTone(buzzer_pin,440,250);
  NewTone(buzzer_pin,392,250);
  NewTone(buzzer_pin,587,250);
  NewTone(buzzer_pin,532,500);
  NewTone(buzzer_pin,392,250);
  NewTone(buzzer_pin,784,250);
  NewTone(buzzer_pin,659,250);
  NewTone(buzzer_pin,532,250);
  NewTone(buzzer_pin,494,250);
  NewTone(buzzer_pin,440,250);
  NewTone(buzzer_pin,698,375);
  NewTone(buzzer_pin,659,250);
  NewTone(buzzer_pin,532,250);
  NewTone(buzzer_pin,587,250);
  NewTone(buzzer_pin,532,500);
  NewNoTone(buzzer_pin);
}

int displayPiexls(int num, int redVal, int greenVal, int blueVal)
{
  for(int i=0; i<num; i++) {
    pixels.setPixelColor(i, pixels.Color(redVal, greenVal, blueVal));
  }
}

//Breathing lamp
void breath_rgb()
{
  for(int bright_val=0;bright_val<256;bright_val++)
  {
    displayPiexls(NUMPIXELS, 0, bright_val, bright_val);
    pixels.show();
    delay(10);
  }
  for(int bright_val=255;bright_val>0;bright_val--)
  {
    displayPiexls(NUMPIXELS, 0, bright_val, bright_val);
    pixels.show();
    delay(10);
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) { // For each pixel in strip...
    pixels.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    pixels.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      pixels.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<pixels.numPixels(); c += 3) {
        pixels.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      pixels.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<pixels.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      pixels.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<pixels.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / pixels.numPixels();
        uint32_t color = pixels.gamma32(pixels.ColorHSV(hue)); // hue -> RGB
        pixels.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      pixels.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

//The function that controls the steering gear
void procedure(int serPin, int myangle)
{
  int i=0;
  while(i<15)
  {
    int pulsewidth = myangle * 11 + 600;  
    digitalWrite(serPin,HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(serPin,LOW);
    delay((20 - pulsewidth / 1000));
    i++;
  }
}
