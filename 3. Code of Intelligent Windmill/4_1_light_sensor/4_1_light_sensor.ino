/*
 * create by straysnail
 * 2022/11/14
 */
#define lightPin A1  //Define the pin of photosensitive sensor
int light_val;

void setup() {
  Serial.begin(9600);
  pinMode(lightPin, INPUT);  //Set to input state
}

void loop() {
  light_val = analogRead(lightPin);  //Read the analog value
  Serial.print("light_val = ");
  Serial.println(light_val);
  delay(100);
}
