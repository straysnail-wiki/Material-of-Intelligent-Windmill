#define buzPin 11  //Set the pin of the buzzer
void setup(){
  pinMode(buzPin, OUTPUT); //Set to output state
}

void loop(){
  tone(buzPin,262);  //do
  delay(500);
  tone(buzPin,294);  //re
  delay(500);
  tone(buzPin,330);  //mi
  delay(500);
  tone(buzPin,349);  //fa
  delay(500);
  tone(buzPin,392);  //so
  delay(500);
  tone(buzPin,440);  //la
  delay(500);
  tone(buzPin,494);  //si
  delay(500);
  tone(buzPin,532);  //do
  delay(500);
  noTone(buzPin);     //Stop making sound
  delay(1000);
}
