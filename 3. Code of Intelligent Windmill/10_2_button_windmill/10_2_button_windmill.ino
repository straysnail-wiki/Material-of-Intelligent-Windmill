/*
 * create by straysnail
 * 2022/11/24
 */
#define INB 8  //Define pin 8 to control the direction
#define ENB 5  //Define pin 5 to control the speed
#define btnPin 2  //Define the button pin
boolean btnVal;   //The variable is used to receive the values detected by the button
int count = 0; //The variable is used to record the click times of the button
boolean flag = 0; //Used to switch the state of button press and release
int data;

void setup() {
  Serial.begin(9600);
  pinMode(INB, OUTPUT);//Set the pin of controlling the motor to output
  pinMode(ENB, OUTPUT);
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
      while(flag == 1) //While loop function, it will not exit the loop until the button is released and flag == 0
      {
        btnVal = digitalRead(btnPin); //Detect the button state again
        if(btnVal == 0)  //Judge if the button is released
        {
          count = count + 1; //Record the click times of the button
          Serial.println(count);  //Print the click times of the button
          flag = 0; //Exit the state of button press
        }
      }
      data = count % 2;  //Calculate the remainder. If it is singular, the value is equal to 1, and if it is even, the value is equal to 0
      if(data == 1) //If it is singular
      {
        anticlockwise();  //Rotate anticlockwise
      }
      else
      {
        Stop(); //Stop
      }
    }
  }
}

//Rotate anticlockwise
void anticlockwise()
{
  digitalWrite(INB, HIGH);  //Control the direction
  analogWrite(ENB, 50);    //Control the speed whose range is 10-255
}
//Stop
void Stop()
{
  digitalWrite(INB, HIGH);
  analogWrite(ENB, 0);
}
