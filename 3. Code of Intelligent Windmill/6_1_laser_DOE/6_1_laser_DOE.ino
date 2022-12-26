/*
 * create by straysil
 * 2022/11/25
 */
#define laserPin 13 //Define the pin of the laser
#define btnPin 2  //Define the pin fo the button
boolean btnVal;   //The variable is used to receive the value detected by the button
int count = 0; //The variable is used to record the number of times the butotn is clicked
boolean flag = 0; //The variable is used to switch the state of button press and release
int data;

void setup() {
  Serial.begin(9600);
  pinMode(btnPin,INPUT);  //Set the pin of the button to input
}

void loop() {
  btnVal = digitalRead(btnPin);  //Read the button value and assign it to btnVal
  if(btnVal == 1)  //Judge if the button is pressed
  {
    delay(10); //Delay to eliminate the shake of the button
    if(btnVal == 1)  //Judge if the button is pressed
    {
      flag = 1;
      while(flag == 1) //While cyclic function. The cycle will not exit until the button is released and flag==0
      {
        btnVal = digitalRead(btnPin); //Detect state of the button again
        if(btnVal == 0)  //Judge If the button is released
        {
          count = count + 1; //Record the number of times the button is clicked
          Serial.println(count);  //Print the number of times the button is clicked
          flag = 0; //Exit the state of button pressing
        }
      }
  
      data = count % 2;  //Calculate the remainder of the number of clicks on the button to 2. If it is singular, data is equal to 1. If it is even, data is equal to 0
      if(data == 1) //If it is singular
      {
        digitalWrite(laserPin, HIGH);  //The laser turns on
      }
      else
      {
        digitalWrite(laserPin, LOW);  //The laser turns off
      }
    }
  }
}
