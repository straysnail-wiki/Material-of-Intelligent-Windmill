/*
create by straysnail
2022/11/14
*/
#define lightPin A1
#define LEDPin 3
#define PIR_pin  A3   //Define the pin of pyroelectric sensor
boolean PIR_Val;  //Define a variable of bool type
int light_val;

void setup() {
  Serial.begin(9600);  //Set the baud rate of serial port communication as 9600
  pinMode(PIR_pin, INPUT); //Set the pin of the button to input
  pinMode(lightPin, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  light_val = analogRead(lightPin);
//  Serial.print("light_val = ");
//  Serial.println(light_val);
  if(light_val < 500) {   //When it is dark
    PIR_Val = digitalRead(PIR_pin); //Read the button value and assign to PIR_Val
    Serial.println("evening");
    if(PIR_Val == 1) {  //Person detected
      digitalWrite(LEDPin, HIGH);  //The LED lights up
      Serial.println("someone");
    } else {   //No person detected
      digitalWrite(LEDPin, LOW);  //The LED turns off
      Serial.println("nobody");
    }
  }
  else {  //When it is daytime
    digitalWrite(LEDPin, LOW);  //The LED turns off
    Serial.println("morning");
  }
}
