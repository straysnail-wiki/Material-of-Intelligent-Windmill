#define lightPin A1
#define LEDPin 3

int light_val;

void setup() {
  Serial.begin(9600);
  pinMode(lightPin, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  light_val = analogRead(lightPin);
  Serial.print("light_val = ");
  Serial.println(light_val);
  delay(100);
  if(light_val < 500)  //When it is lower than the set value, the LED will light up.
  {
    digitalWrite(LEDPin, HIGH);
  }
  else
  {
    digitalWrite(LEDPin, LOW);
  }
}
