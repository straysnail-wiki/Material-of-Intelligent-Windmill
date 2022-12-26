/*
 * create by straysnail
 * 2022/11/11
 */
 
#include <NewTone.h> //Import a library file of sound frequencies
#define buzzerPin 11   //buzzer PIN
#define btnPin 2  //button PIN

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop() {
  boolean val = digitalRead(btnPin);
  if(val == 0)
  {
    play_music(buzzerPin);  //Execute the subfunction and play the tune
  }
  else
  {
    NewNoTone(buzzerPin);  //stop
  }
}

void play_music(int buzzer_pin)
{
  //NewTone Three parameters: PIN , frequency, duration
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
