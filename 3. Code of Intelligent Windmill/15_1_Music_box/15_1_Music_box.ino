/*
 * create by straysnail
 * 2022/11/24
 */
//Define frequency values for some tones
#define NTF0 -1
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AE4 455
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

#define buzzer_pin 11  //buzzer PIN

int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define btn2 4  //button2 PIN

boolean state1 = 1;
boolean state2 = 1;
boolean state3 = 1;

int mode_count = 0;  //Used for counting
boolean btnVal; 
boolean flag = 0;
int time_data = 0;  //Used to calculate the time a key is pressed
int mode = 0;  //Used to determine whether key 2 is pressed quickly or long

void setup() {
  Serial.begin(9600);
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
  display.println(F("birthday"));
  display.println(F(""));
  display.println(F("star_war_tone"));
  display.println(F(""));
  display.println(F("Little_Star"));
  display.display(); //display

  /*
   * External interrupt functions, the external interrupt pins of UNO are 2 and 3
   * When key 1 is clicked, 
   * an external interrupt is triggered and the StopMusic() function is executed
   */
  attachInterrupt(digitalPinToInterrupt(2), StopMusic, CHANGE);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(btn2, INPUT);
}

void loop() {
  btnVal = digitalRead(btn2);  //Read the button value and assign it to btnVal
  if(btnVal == 0)  //Judge if the button is pressed
  {
    delay(20);
    btnVal = digitalRead(btn2); //Check the status of the button again
    if(btnVal == 0)  //Then judge if the button is pressed
    {
      flag = 1;
      while(flag == 1) //The while loop does not exit until the key is released and flag == 1.
      {
        delay(30);
        time_data = time_data + 1;  //Calculate how long key 2 is pressed
        if(time_data > 60)  //If >60, it indicates that key 2 is being held down
        {
          mode = 1;  //Mode 1, play the tune
          flag = 0;  //flag = 0, exit the while loop
        }
        else  //Button 2 is short press
        {
          btnVal = digitalRead(btn2); //Check the status of the button again
          if(btnVal == 1)  //Judge if the button is released
          {
            mode_count = mode_count + 1; //Keep track of the number of times a button is clicked
            Serial.println(mode_count); 
            if(mode_count > 3)
            {
              mode_count = 1;
            }
            time_data = 0;
            mode = 2;  //
            flag = 0; //Exit the while loop
          }   
        }
      }
      Serial.print("time_data = ");
      Serial.println(time_data);
      //According to the number of times key 2 is clicked, 
      //the OLED displays the selected status of the corresponding tune
      switch(mode_count)
      {
        case 1:  birthday_select(); break;
        case 2:  star_select(); break;
        case 3:  little_Star_select(); break;
      }
    }
  }
  if(mode == 1) //Play a tune
  {
    switch(mode_count)
    {
      case 1:  birthday();time_data = 0; break;
      case 2:  star_war_tone();time_data = 0; break;
      case 3:  little_Star();time_data = 0; break;
    }
    mode = 0;
  }
  if(mode == 2)
  {
    Serial.println("select music");
    mode = 0;
  }
}

void(* resetFunc) (void) = 0;  //Software reset

//The interrupt function that is triggered
void StopMusic() {
  noTone(11);
  resetFunc(); //Execute reset function
}

void birthday_select() {
  while(state1 == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("^birthday"));
    display.println(F(""));
    display.println(F("star_war_tone"));
    display.println(F(""));
    display.println(F("little_star"));
    display.display(); //display
    state1 = 0;
    state2 = 1;
    state3 = 1;
  }
}

void star_select() {
  while(state2 == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("birthday"));
    display.println(F(""));
    display.println(F("^star_war_tone"));
    display.println(F(""));
    display.println(F("little_star"));
    display.display(); //display
    state1 = 1;
    state2 = 0;
    state3 = 1;
  }
}
void little_Star_select() {
  while(state3 == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("birthday"));
    display.println(F(""));
    display.println(F("star_war_tone"));
    display.println(F(""));
    display.println(F("^little_star"));
    display.display(); //display
    state1 = 1;
    state2 = 1;
    state3 = 0;
  }
}

//Little star
void little_Star()
{
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
  
    // pause between notes
    delay(tempo / 2); 
  }
}
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(tone);
  }
}
  
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

//Happy Birthday
void birthday()
{
  tone(buzzer_pin,294);
  delay(250);
  tone(buzzer_pin,440);
  delay(250);
  tone(buzzer_pin,392);
  delay(250);
  tone(buzzer_pin,532);
  delay(250);
  tone(buzzer_pin,494);
  delay(500);
  tone(buzzer_pin,392);
  delay(250);
  tone(buzzer_pin,440);
  delay(250);
  tone(buzzer_pin,392);
  delay(250);
  tone(buzzer_pin,587);
  delay(250);
  tone(buzzer_pin,532);
  delay(500);
  tone(buzzer_pin,392);
  delay(250);
  tone(buzzer_pin,784);
  delay(250);
  tone(buzzer_pin,659);
  delay(250);
  tone(buzzer_pin,532);
  delay(250);
  tone(buzzer_pin,494);
  delay(250);
  tone(buzzer_pin,440);
  delay(250);
  tone(buzzer_pin,698);
  delay(375);
  tone(buzzer_pin,659);
  delay(250);
  tone(buzzer_pin,532);
  delay(250);
  tone(buzzer_pin,587);
  delay(250);
  tone(buzzer_pin,532);
  delay(500);
  noTone(buzzer_pin);
}

//Star Wars
void star_war_tone()
{
  //Play first section
  tone(buzzer_pin, NOTE_A4);
  delay(500);
  noTone(buzzer_pin);
  delay(50);
  tone(buzzer_pin, NOTE_A4);
  delay(500);  
  noTone(buzzer_pin);
  delay(50);
  tone(buzzer_pin, NOTE_A4);
  delay(500);
  noTone(buzzer_pin);
  delay(50);
  tone(buzzer_pin, NOTE_F4);
  delay(350);
  noTone(buzzer_pin);
  delay(50);
  tone(buzzer_pin, NOTE_C5);
  delay(150);
  noTone(buzzer_pin);
  delay(50);  
  tone(buzzer_pin, NOTE_A4);
  delay(500);
  noTone(buzzer_pin);
  delay(50);
  tone(buzzer_pin, NOTE_F4);
  delay(350);
  noTone(buzzer_pin);
  delay(50);
  tone(buzzer_pin, NOTE_C5);
  delay(150);
  noTone(buzzer_pin);
  delay(50);
  tone(buzzer_pin, NOTE_A4);
  delay(650);
  noTone(buzzer_pin);
  delay(500);

  tone(buzzer_pin, NOTE_E5);
  delay(500);
  tone(buzzer_pin, NOTE_E5);
  delay(500);
  tone(buzzer_pin, NOTE_E5);
  delay(500);
  tone(buzzer_pin, NOTE_F5);
  delay(350);
  tone(buzzer_pin, NOTE_C5);
  delay(150);
  tone(buzzer_pin, NOTE_GS4);
  delay(500);
  tone(buzzer_pin, NOTE_F4);
  delay(350);
  tone(buzzer_pin, NOTE_C5);
  delay(150);
  tone(buzzer_pin, NOTE_A4);
  delay(650);
  noTone(buzzer_pin);
  delay(500);

  //second
  tone(buzzer_pin, NOTE_A5);
  delay(500);
  tone(buzzer_pin, NOTE_A4);
  delay(300);
  tone(buzzer_pin, NOTE_A4);
  delay(150);
  tone(buzzer_pin, NOTE_A5);
  delay(500);
  tone(buzzer_pin, NOTE_GS5);
  delay(325);
  tone(buzzer_pin, NOTE_G5);
  delay(175);
  tone(buzzer_pin, NOTE_FS5);
  delay(125);
  tone(buzzer_pin, NOTE_F5);
  delay(125);
  tone(buzzer_pin, NOTE_FS5);
  delay(250);
  noTone(buzzer_pin);
  delay(325);
  tone(buzzer_pin, NOTE_AE4);
  delay(250);
  tone(buzzer_pin, NOTE_DS5);
  delay(500);
  tone(buzzer_pin, NOTE_D5);
  delay(325);
  tone(buzzer_pin, NOTE_CS5);
  delay(175);
  tone(buzzer_pin, NOTE_C5);
  delay(125);
  tone(buzzer_pin, NOTE_AS4);
  delay(125);
  tone(buzzer_pin, NOTE_C5);
  delay(250);
  noTone(buzzer_pin);
  delay(350);
  
  tone(buzzer_pin, NOTE_F4);
  delay(250);
  tone(buzzer_pin, NOTE_GS4);
  delay(500);
  tone(buzzer_pin, NOTE_F4);
  delay(350);
  tone(buzzer_pin, NOTE_A4);
  delay(125);
  tone(buzzer_pin, NOTE_C5);
  delay(500);
  tone(buzzer_pin, NOTE_A4);
  delay(375);
  tone(buzzer_pin, NOTE_C5);
  delay(125);
  tone(buzzer_pin, NOTE_E5);
  delay(650);
  noTone(buzzer_pin);
  delay(500);

  //second
  tone(buzzer_pin, NOTE_A5);
  delay(500);
  tone(buzzer_pin, NOTE_A4);
  delay(300);
  tone(buzzer_pin, NOTE_A4);
  delay(150);
  tone(buzzer_pin, NOTE_A5);
  delay(500);
  tone(buzzer_pin, NOTE_GS5);
  delay(325);
  tone(buzzer_pin, NOTE_G5);
  delay(175);
  tone(buzzer_pin, NOTE_FS5);
  delay(125);
  tone(buzzer_pin, NOTE_F5);
  delay(125);
  tone(buzzer_pin, NOTE_FS5);
  delay(250);
  noTone(buzzer_pin);
  delay(325);
  tone(buzzer_pin, NOTE_AE4);
  delay(250);
  tone(buzzer_pin, NOTE_DS5);
  delay(500);
  tone(buzzer_pin, NOTE_D5);
  delay(325);
  tone(buzzer_pin, NOTE_CS5);
  delay(175);
  tone(buzzer_pin, NOTE_C5);
  delay(125);
  tone(buzzer_pin, NOTE_AS4);
  delay(125);
  tone(buzzer_pin, NOTE_C5);
  delay(250);
  noTone(buzzer_pin);
  delay(350);

  tone(buzzer_pin, NOTE_F4);
  delay(250);
  tone(buzzer_pin, NOTE_GS4);
  delay(500);
  tone(buzzer_pin, NOTE_F4);
  delay(375);
  tone(buzzer_pin, NOTE_C5);
  delay(125);
  tone(buzzer_pin, NOTE_A4);
  delay(500);
  tone(buzzer_pin, NOTE_F4);
  delay(375);
  tone(buzzer_pin, NOTE_C5);
  delay(125);
  tone(buzzer_pin, NOTE_A4);
  delay(650);
  noTone(buzzer_pin);
}
