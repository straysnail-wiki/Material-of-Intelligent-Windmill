/*
 * create by straysnail
 * 2022/2/26
 */
#include <Adafruit_NeoPixel.h>
#define Neo_PIN  A0  //Define the pin
#define NUMPIXELS  11 //Define the LED number
//Declare our NeoPixel strip object
Adafruit_NeoPixel pixels(NUMPIXELS, Neo_PIN, NEO_GRB + NEO_KHZ800);

#define btnPin 2  //Define the button pin
#define btnPin2 4
boolean btnVal1;   //The variable is used to receive the value detected by the button
boolean btnVal2;
int count = 0; //The variable is used to record the click times of the button
boolean flag1 = 0; //Used to switch the state of button press and release
boolean flag2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(btnPin,INPUT);  //Set the pin to input
  pixels.begin(); // Initialize NeoPixel
  pixels.clear(); //Clean up
  pixels.show();//Display
}

void loop() {
  btnVal1 = digitalRead(btnPin);  //Read the button value and assign it to btnVal1
  while(btnVal1 == 0)  //Judge if the button is pressed
  {
    delay(10);
    flag1 = 1;
    while(flag1 == 1) //When the button is pressed
    {
      btnVal1 = digitalRead(btnPin); //Detect the button state again
      if(btnVal1 == 1)  //Judge if the button is released
      {
        count = count + 1; //Record the click times of the button
        Serial.println(count);  //Print the click times of the button
        flag1 = 0; //Exit the pressed state
        if(count >= 6)
        {
          count = 6;
        }
        switch(count)
        {
          case 0: displayPiexls(NUMPIXELS, 200, 0, 0); pixels.show(); break;
          case 1: displayPiexls(NUMPIXELS, 0, 200, 0); pixels.show(); break;
          case 2: displayPiexls(NUMPIXELS, 0, 0, 200); pixels.show(); break;
          case 3: displayPiexls(NUMPIXELS, 200, 200, 0); pixels.show(); break;
          case 4: displayPiexls(NUMPIXELS, 0, 200, 200); pixels.show(); break;
          case 5: displayPiexls(NUMPIXELS, 200, 200, 200); pixels.show(); break;
          case 6: displayPiexls(NUMPIXELS, 0, 0, 0); pixels.show(); break;
        }
      }
    }
  }
  btnVal2 = digitalRead(btnPin2);  //Read the button value and assign it to btnVal1
  while(btnVal2 == 0)  //Judge if the button is pressed
  {
    delay(10);
    flag2 = 1;
    while(flag2 == 1) //When the button is pressed
    {
      btnVal2 = digitalRead(btnPin2); //Detect the button state again
      if(btnVal2 == 1)  //Judge if the button is released
      {
        count = count - 1; //Record the click times of the button
        Serial.println(count);  //Print the click times of the button
        flag2 = 0; //Exit the pressed state
        if(count <= 0)
        {
          count = 0;
        }
        switch(count)
        {
          case 0: displayPiexls(NUMPIXELS, 200, 0, 0); pixels.show(); break;
          case 1: displayPiexls(NUMPIXELS, 0, 200, 0); pixels.show(); break;
          case 2: displayPiexls(NUMPIXELS, 0, 0, 200); pixels.show(); break;
          case 3: displayPiexls(NUMPIXELS, 200, 200, 0); pixels.show(); break;
          case 4: displayPiexls(NUMPIXELS, 0, 200, 200); pixels.show(); break;
          case 5: displayPiexls(NUMPIXELS, 200, 200, 200); pixels.show(); break;
          case 6: displayPiexls(NUMPIXELS, 0, 0, 0); pixels.show(); break;
        }
      }
    }
  }
}

//Define a function to control all the LED and their brightness
int displayPiexls(int num, int redVal, int greenVal, int blueVal)
{
  //Use for loop statement to make all LED on
  for(int i=0; i<num; i++) {
    pixels.setPixelColor(i, pixels.Color(redVal, greenVal, blueVal));//Set the pin of the LED and RGB color 
  }
}
