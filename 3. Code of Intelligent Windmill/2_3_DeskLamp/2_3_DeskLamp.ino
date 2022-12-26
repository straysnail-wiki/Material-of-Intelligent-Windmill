/*
 * create by straysnail
 * 2022/11/26
 */
#define ledPin 3 //Define the pin of LED as 3
#define btnPin 2  //Define the button pin as 2
boolean btnVal;   //Variable, used to receive the value detected by the button
int count = 0; //Variable, used to record the number of times the button is clicked
boolean flag = 0; //Used to switch the state of button press and release
int data;

void setup() {
  Serial.begin(9600);
  pinMode(btnPin,INPUT);  //Set the button pin to input state
}

void loop() {
  btnVal = digitalRead(btnPin);  //Read the value of the button and assign it to btnVal
  if(btnVal == 0)  //If function, and it means that if the button is pressed
  {
    delay(20); //Delay to eliminate the shake of the button
    btnVal = digitalRead(btnPin);
    if(btnVal == 0)
    {
      flag = 1;
      while(flag == 1) //While cyclic function. The cycle will not exit until the button is released and flag==0
      {
        btnVal = digitalRead(btnPin); //Detect state of the button again
        if(btnVal == 1)  //Judge. If the button is released
        {
          count = count + 1; //Record the number of times the button is clicked
          Serial.println(count);  //Print the number of times the button is clicked
          flag = 0; //Exit the state of button pressing
        }
      }
  
      data = count % 2;  //Calculate the remainder of the number of clicks on the button to 2. If it is singular, data is equal to 1. If it is even, data is equal to 0
      if(data == 1) //If it is singular
      {
        digitalWrite(ledPin, HIGH);  //LED is on 
      }
      else
      {
        digitalWrite(ledPin, LOW);  //LED is off
      }
    }
    
  }
}
