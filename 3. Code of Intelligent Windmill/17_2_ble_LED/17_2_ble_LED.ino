char bleVal = "";
#define ledPin 3

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop() {
  while(Serial.available() > 0)  //Judge whether the serial port area receives value
  {
    String bleVal1 = Serial.readStringUntil('*'); //Read the string received by the Bluetooth until “*” is received
    if(bleVal1[0] == '$')  //If the first character of the string is “$”
    {
      bleVal = bleVal1[1]; //The second character of the string is the command we need and assign it to bleVal
      Serial.println(bleVal);
      if(bleVal == 'a')  //If the command received is “a”
      {
        digitalWrite(ledPin, HIGH); //Turn on the LED
      }
      if(bleVal == 'b')  //If the command received is “b”
      {
        digitalWrite(ledPin, LOW); //Turn off the LED
      }
    }
  }
}
