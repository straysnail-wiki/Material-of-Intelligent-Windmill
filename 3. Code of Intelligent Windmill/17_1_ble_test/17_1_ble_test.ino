char bleStr = "";

void setup() {
  Serial.begin(9600);

}

void loop() {
  while(Serial.available() > 0)  //Judge whether the serial port area receives value
  {
    bleStr = Serial.read();  //Read the value of serial port area
    Serial.println(bleStr);
    delay(10);
  }
}
