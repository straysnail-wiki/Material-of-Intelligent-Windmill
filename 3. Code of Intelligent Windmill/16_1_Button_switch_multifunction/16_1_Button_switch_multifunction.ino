#include<NewTone.h> 
#include<Adafruit_NeoPixel.h>
#define Neo_PIN  A0 
#define NUMPIXELS  11 //Define the number of beads
Adafruit_NeoPixel pixels(NUMPIXELS, Neo_PIN, NEO_GRB + NEO_KHZ800);

#include<Wire.h>

#include <dht11.h>
dht11 DHT11;
#define DHT11PIN 12

#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int tunnel_count;

#include<OneButton.h>
// Setup a new OneButton on pin 2
OneButton button1(2, true);
// Setup a new OneButton on pin 4
OneButton button2(4, true);

#define door_servo 9  //door PIN
#define window_servo 10  //window PIN
int count1 = 0;
int count2 = 0;
int pulsewidth = 0;

#define LED_pin 3
#define btn_pin1 2
#define btn_pin2 4

int mode_count = 0;
boolean OLED_LED = 1;  //The first mode is LED, so its display variable is 1
boolean OLED_servo = 0;
boolean OLED_tunnel = 0;
boolean OLED_music = 0;
boolean OLED_windmill = 0;
boolean OLED_butterfly = 0;
boolean OLED_laser = 0;
boolean OLED_dht11 = 0;

#define lightPin A1  //Light sensor pin A1
//The motor that controls the butterfly
#define INA 7 
#define ENA 6 
//The motor that controls the windmill
#define INB 8 
#define ENB 5 

#define buzzerPin 11   //buzzer PIN
#define laserPin 13    //laser PIN

void setup() {
  Serial.begin(9600);
  pinMode(door_servo, OUTPUT);
  procedure(door_servo, 50); //close the door
  delay(500);
  pinMode(window_servo, OUTPUT);
  procedure(window_servo, 130); //close the window
  delay(500);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Clear the buffer
  display.clearDisplay();
  display.display();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("LED"));
  display.println(F("Door and window"));
  display.println(F("Tunnel light"));
  display.println(F("Windmill"));
  display.println(F("Butterfly"));
  display.println(F("Laser"));
  display.println(F("DHT11"));
  display.println(F("Music"));
  display.display();
  delay(1000);
  
  // link the button 1 functions.
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,10);             // Start at top-left corner

  pixels.begin(); // init NeoPixel
  pixels.clear(); //clear
  pixels.show();//display

  pinMode(INA, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(ENB, OUTPUT);

}

void loop() {
  // keep watching the push buttons:
  button1.tick();
  button2.tick();
}

// ----- button 1 callback functions

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  mode_count++;
  if(mode_count >= 9)
  {
    mode_count = 0;
  }
  Serial.println(mode_count);
  switch(mode_count)
  {
    case 1: select_LED_mode(); break;
    case 2: select_Door_and_window_mode(); break;
    case 3: select_Tunnel_light_mode(); break;
    case 4: select_windmill_mode(); break;
    case 5: select_butterfly_mode(); break;
    case 6: select_laser_mode(); break;
    case 7: select_dht11_mode(); break;
    case 8: select_Music_mode(); break;

  }
} // click1


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
  Serial.println(mode_count);
  switch(mode_count)
  {
    case 1: LED_mode(); break;
    case 2: Door_and_window_mode(); break;
    case 3: Tunnel_light_mode(); break;
    case 4: windmill_mode(); break;
    case 5: butterfly_mode(); break;
    case 6: laser_mode(); break;
    case 7: dht11_mode(); break;
    case 8: Music_mode(); break;

  }
} // doubleclick1

void LED_mode()
{
  boolean LED_flag = 1;
  boolean i = 1;
  while(LED_flag == 1)
  {
    while(i == 1)
    {
      display.clearDisplay();
      display.display();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("LED mode"));
      display.setTextSize(1);
      display.println(F("Btn1 turn off the LED"));
      display.println(F("Btn2 turn on the LED"));
      display.display();
      i = 0;
    }
    pinMode(btn_pin1,INPUT);
    pinMode(btn_pin2,INPUT);
    boolean btn1_val = digitalRead(btn_pin1);
    boolean btn2_val = digitalRead(btn_pin2);
    if(btn1_val == 0)
    {
      digitalWrite(LED_pin, LOW);
    }
    if(btn2_val == 0)
    {
      digitalWrite(LED_pin, HIGH);
    }
    if((btn1_val == 0) && (btn2_val == 0))
    {
      Serial.println("Exit the mode");
      boolean L = 1;
      while(L == 1)
      {
        display.clearDisplay();
        display.display();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("^  LED"));
        display.println(F("Door and window"));
        display.println(F("Tunnel light"));
        display.println(F("Windmill"));
        display.println(F("Butterfly"));
        display.println(F("Laser"));
        display.println(F("DHT11"));
        display.println(F("Music"));
        display.display();
        L = 0;
      }
      digitalWrite(LED_pin, LOW);
      LED_flag = 0;
      mode_count = 0;
      OLED_LED = 1;
    }
  }
  
}

//根据舵机原理控制舵机角度的函数
void procedure(int serPin, int myangle)   //函数有两个参数，serPin是舵机的引脚，myangle是舵机的角度
{
  int i=0;
  while(i<15)
  {
    //计算脉冲值，也就是高电平的时间，myangle值范围是0~180，对应得到pulsewidth的范围是500~2480
    pulsewidth = myangle * 11 + 600;  
    digitalWrite(serPin,HIGH);
    delayMicroseconds(pulsewidth);  //延时计算好的高电平时间
    digitalWrite(serPin,LOW); //设置为低电平
    delay((20 - pulsewidth / 1000));  //延时剩余的低电平时间
    i++;
  }
}
void Door_and_window_mode()
{
  boolean servo_flag = 1;
  boolean i = 1;
  while(servo_flag == 1)
  {
    while(i == 1)
    {
      pinMode(door_servo, OUTPUT);
      pinMode(window_servo, OUTPUT);
      display.clearDisplay();
      display.display();
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("door_window mode"));
      display.println(F(""));
      display.println(F("Btn2 open and close the door"));
      display.display();
      i = 0;
    }
    pinMode(btn_pin1,INPUT);
    pinMode(btn_pin2,INPUT);
    boolean btn1_val = digitalRead(btn_pin1);
    boolean btn2_val = digitalRead(btn_pin2);
   
    if((btn1_val == 0) && (btn2_val == 0))
    {
      Serial.println("Exit the mode");
      boolean L = 1;
      while(L == 1)
      {
        display.clearDisplay();
        display.display();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("LED"));
        display.println(F("^  Door and window"));
        display.println(F("Tunnel light"));
        display.println(F("Windmill"));
        display.println(F("Butterfly"));
        display.println(F("Laser"));
        display.println(F("DHT11"));
        display.println(F("Music"));
        display.display();
        L = 0;
      }
      procedure(door_servo, 46);  //关门
      procedure(window_servo, 110);  //关窗
      delay(200);
      servo_flag = 0;
      mode_count = 1;
      OLED_servo = 1;
    }
    else
    {
      if(btn2_val == 0)
      {
        delay(10);
        boolean ser2 = 1;
        while(ser2 == 1)
        {
          boolean btn2_val = digitalRead(btn_pin2);
          if(btn2_val == 1)
          {
            count2++;
            Serial.print("button2 = ");
            Serial.println(count2);
            ser2 = 0;
          }
          boolean val = count2 % 2;
          if(val == 1)
          {
            procedure(door_servo, 140);
            procedure(window_servo, 50);
            delay(200);
          }
          else
          {
            procedure(door_servo, 46);
            procedure(window_servo, 110);
            delay(200);
          }
        }
      }
    }
  }
}

void windmill_mode()
{
  boolean windmill_flag = 1;
  boolean i = 1;
  while(windmill_flag == 1)
  {
    while(i == 1)
    {
      display.clearDisplay();
      display.display();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("windmill mode"));
      display.setTextSize(1);
      display.println(F("Btn1 turn off the windmill"));
      display.println(F("Btn2 turn on the windmill"));
      display.display();
      i = 0;
    }
    pinMode(btn_pin1,INPUT);
    pinMode(btn_pin2,INPUT);
    boolean btn1_val = digitalRead(btn_pin1);
    boolean btn2_val = digitalRead(btn_pin2);
    if(btn1_val == 0) //点击按键1，风车停止
    {
      digitalWrite(INB, HIGH);
      analogWrite(ENB, 0);
    }
    if(btn2_val == 0) //点击按键2，风车转动
    {
      digitalWrite(INB, HIGH);
      analogWrite(ENB, 50);
    }
    if((btn1_val == 0) && (btn2_val == 0))
    {
      Serial.println("Exit the mode");
      boolean L = 1;
      while(L == 1)
      {
        display.clearDisplay();
        display.display();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("LED"));
        display.println(F("Door and window"));
        display.println(F("Tunnel light"));
        display.println(F("^  Windmill"));
        display.println(F("Butterfly"));
        display.println(F("Laser"));
        display.println(F("DHT11"));
        display.println(F("Music"));
        display.display();
        L = 0;
      }
      analogWrite(ENB, 0);  
      windmill_flag = 0;
      mode_count = 3;
      OLED_windmill = 0;
    }
  }
  
}

void butterfly_mode()
{
  boolean butterfly_flag = 1;
  boolean i = 1;
  while(butterfly_flag == 1)
  {
    while(i == 1)
    {
      display.clearDisplay();
      display.display();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("butterfly mode"));
      display.setTextSize(1);
      display.println(F("Btn1 turn off the butterfly"));
      display.println(F("Btn2 turn on the butterfly"));
      display.display();
      i = 0;
    }
    pinMode(btn_pin1,INPUT);
    pinMode(btn_pin2,INPUT);
    boolean btn1_val = digitalRead(btn_pin1);
    boolean btn2_val = digitalRead(btn_pin2);
    if(btn1_val == 0) //点击按键1，蝴蝶不动
    {
      digitalWrite(INA, HIGH);
      analogWrite(ENA, 0);
    }
    if(btn2_val == 0) //点击按键2，蝴蝶翅膀扇动
    {
      digitalWrite(INA, HIGH);
      analogWrite(ENA, 50);
    }
    if((btn1_val == 0) && (btn2_val == 0))
    {
      Serial.println("Exit the mode");
      boolean L = 1;
      while(L == 1)
      {
        display.clearDisplay();
        display.display();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("LED"));
        display.println(F("Door and window"));
        display.println(F("Tunnel light"));
        display.println(F("Windmill"));
        display.println(F("^  Butterfly"));
        display.println(F("Laser"));
        display.println(F("DHT11"));
        display.println(F("Music"));
        display.display();
        L = 0;
      }
      analogWrite(ENA, 0);  
      butterfly_flag = 0;
      mode_count = 4;
      OLED_butterfly = 0;
    }
  }
  
}

void laser_mode()
{
  boolean laser_flag = 1;
  boolean i = 1;
  while(laser_flag == 1)
  {
    while(i == 1)
    {
      display.clearDisplay();
      display.display();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("laser mode"));
      display.setTextSize(1);
      display.println(F("Btn1 turn off the laser"));
      display.println(F("Btn2 turn on the laser"));
      display.display();
      i = 0;
    }
    pinMode(btn_pin1,INPUT);
    pinMode(btn_pin2,INPUT);
    boolean btn1_val = digitalRead(btn_pin1);
    boolean btn2_val = digitalRead(btn_pin2);
    if(btn1_val == 0) //点击按键1，关闭激光
    {
      digitalWrite(laserPin, LOW);
    }
    if(btn2_val == 0) //点击按键2，打开激光
    {
      digitalWrite(laserPin, HIGH);
    }
    if((btn1_val == 0) && (btn2_val == 0))
    {
      Serial.println("Exit the mode");
      boolean L = 1;
      while(L == 1)
      {
        display.clearDisplay();
        display.display();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("LED"));
        display.println(F("Door and window"));
        display.println(F("Tunnel light"));
        display.println(F("Windmill"));
        display.println(F("Butterfly"));
        display.println(F("^  Laser"));
        display.println(F("DHT11"));
        display.println(F("Music"));
        display.display();
        L = 0;
      }
      analogWrite(laserPin, 0);  
      laser_flag = 0;
      mode_count = 5;
      OLED_laser = 0;
    }
  }
}

void dht11_mode()
{
  boolean dht11_flag = 1;
  boolean i = 1;
  while(dht11_flag == 1)
  {
    int chk = DHT11.read(DHT11PIN); //读取DHT11传感器测到的值
//    while(i == 1)
//    {
//      display.clearDisplay();
//      display.display();
//      display.setTextSize(2);             // Normal 1:1 pixel scale
//      display.setTextColor(SSD1306_WHITE);        // Draw white text
//      display.setCursor(0,0);             // Start at top-left corner
//      display.println(F("DHT11 mode"));
//      display.setTextSize(1);
//      display.println(F("Btn1 turn off the DHT11"));
//      display.println(F("Btn2 turn on the DHT11"));
//      display.display();
//      i = 0;
//    }
    pinMode(btn_pin1,INPUT);
    pinMode(btn_pin2,INPUT);
    boolean btn1_val = digitalRead(btn_pin1);
    boolean btn2_val = digitalRead(btn_pin2);

    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.print(F("T : "));
    display.print(DHT11.temperature);
    display.println(F(" C"));
    display.println(F(""));
    display.print(F("H : "));
    display.print(DHT11.humidity);
    display.println(F(" %"));
    display.display(); //显示
    display.clearDisplay();
    delay(20);
    
    if((btn1_val == 0) && (btn2_val == 0))
    {
      Serial.println("Exit the mode");
      boolean L = 1;
      while(L == 1)
      {
        display.clearDisplay();
        display.display();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("LED"));
        display.println(F("Door and window"));
        display.println(F("Tunnel light"));
        display.println(F("Windmill"));
        display.println(F("Butterfly"));
        display.println(F("Laser"));
        display.println(F("^  DHT11"));
        display.println(F("Music"));
        display.display();
        L = 0;
      }
      dht11_flag = 0;
      mode_count = 6;
      OLED_dht11 = 0;
    }
  }
}



//定义一个函数，控制全部灯珠和其亮度
int displayPiexls(int num, int redVal, int greenVal, int blueVal)
{
  //使用for循环语句，让所有灯珠都亮起
  for(int i=0; i<num; i++) {
    pixels.setPixelColor(i, pixels.Color(redVal, greenVal, blueVal));//设置灯的引脚和RGB颜色
  }
}
void Tunnel_light_mode()
{
  boolean tunnel_flag = 1;
  boolean i = 1;
  while(tunnel_flag == 1)
  {
    while(i == 1)
    {
      display.clearDisplay();
      display.display();
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("Tunnel mode"));
      display.println(F("Btn1 turn off tunnel"));
      display.println(F("Btn2 turn on tunnel"));
      display.display();
      i = 0;
    }
    pinMode(btn_pin1,INPUT);
    pinMode(btn_pin2,INPUT);
    boolean btn1_val = digitalRead(btn_pin1);
    boolean btn2_val = digitalRead(btn_pin2);
    if(btn1_val == 0)
    {
      displayPiexls(NUMPIXELS, 0, 0, 0);  //关闭 隧道灯
      pixels.show();
    }
    if(btn2_val == 0)
    {
      delay(10);
      boolean i=1;
      while(i == 1)
      {
        boolean btn2_val = digitalRead(btn_pin2);
        if(btn2_val == 1)
        {
          tunnel_count++;
          if(tunnel_count >= 6)
          {
            tunnel_count = 0;
          }
          Serial.print("tunnel_count = ");
          Serial.println(tunnel_count);
          i= 0;
        }
        switch(tunnel_count)
        {
          case 0: displayPiexls(NUMPIXELS, 200, 0, 0); pixels.show(); break;
          case 1: displayPiexls(NUMPIXELS, 0, 200, 0); pixels.show(); break;
          case 2: displayPiexls(NUMPIXELS, 0, 0, 200); pixels.show(); break;
          case 3: displayPiexls(NUMPIXELS, 200, 200, 0); pixels.show(); break;
          case 4: displayPiexls(NUMPIXELS, 0, 200, 200); pixels.show(); break;
          case 5: displayPiexls(NUMPIXELS, 200, 200, 200); pixels.show(); break;
          case 6: displayPiexls(NUMPIXELS, 0, 0, 0); pixels.show(); break;
        }
      }
    }
    if((btn1_val == 0) && (btn2_val == 0))
    {
      Serial.println("Exit the mode");
      boolean L = 1;
      while(L == 1)
      {
        display.clearDisplay();
        display.display();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("LED"));
        display.println(F("Door and window"));
        display.println(F("^  Tunnel light"));
        display.println(F("Windmill"));
        display.println(F("Butterfly"));
        display.println(F("Laser"));
        display.println(F("DHT11"));
        display.println(F("Music"));
        display.display();
        L = 0;
      }
      tunnel_flag = 0;
      mode_count = 2;
      OLED_tunnel = 1;
      displayPiexls(NUMPIXELS, 0, 0, 0); 
      pixels.show();
    }
  }
}
void Music_mode()
{
  boolean music_flag = 1;
  boolean i = 1;
  while(music_flag == 1)
  {
    while(i == 1)
    {
      display.clearDisplay();
      display.display();
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("music mode"));
      display.setTextSize(1);
      display.println(F("Play Happy Birthday"));
      display.display();
      i = 0;
    }
    pinMode(btn_pin1,INPUT);
    pinMode(btn_pin2,INPUT);
    boolean btn1_val = digitalRead(btn_pin1);
    boolean btn2_val = digitalRead(btn_pin2);
    if((btn1_val == 0) && (btn2_val == 0))
    {
      Serial.println("Exit the mode");
      boolean L = 1;
      while(L == 1)
      {
        display.clearDisplay();
        display.display();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("LED"));
        display.println(F("Door and window"));
        display.println(F("Tunnel light"));
        display.println(F("Windmill"));
        display.println(F("Butterfly"));
        display.println(F("Laser"));
        display.println(F("DHT11"));
        display.println(F("^  Music"));
        display.display();
        L = 0;
      }
      music_flag = 0;
      mode_count = 7;
      OLED_music = 1;
      break;
    }
    if(btn2_val == 0)
    {
      pinMode(buzzerPin, OUTPUT);
      play_music(buzzerPin);
    }
  }
  
}

void select_windmill_mode()
{
  while(OLED_windmill == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("LED"));
    display.println(F("Door and window"));
    display.println(F("Tunnel light"));
    display.println(F("^  Windmill"));
    display.println(F("Butterfly"));
    display.println(F("Laser"));
    display.println(F("DHT11"));
    display.println(F("Music"));
    display.display();
    OLED_LED = 1;
    OLED_servo = 1;
    OLED_tunnel = 1;
    OLED_music = 1;
    OLED_windmill = 0;
    OLED_butterfly = 1;
    OLED_laser = 1;
    OLED_dht11 = 1;
  }
}

void select_LED_mode()
{
  while(OLED_LED == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("^  LED"));
    display.println(F("Door and window"));
    display.println(F("Tunnel light"));
    display.println(F("Windmill"));
    display.println(F("Butterfly"));
    display.println(F("Laser"));
    display.println(F("DHT11"));
    display.println(F("Music"));
    display.display();
    OLED_LED = 0;
    OLED_servo = 1;
    OLED_tunnel = 1;
    OLED_music = 1;
    OLED_windmill = 1;
    OLED_butterfly = 1;
    OLED_laser = 1;
    OLED_dht11 = 1;
  }
}
void select_Door_and_window_mode()
{
  while(OLED_servo == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("LED"));
    display.println(F("^  Door and window"));
    display.println(F("Tunnel light"));
    display.println(F("Windmill"));
    display.println(F("Butterfly"));
    display.println(F("Laser"));
    display.println(F("DHT11"));
    display.println(F("Music"));
    display.display();
    
    OLED_LED = 1;
    OLED_servo = 0;
    OLED_tunnel = 1;
    OLED_music = 1;
    OLED_windmill = 0;
    OLED_butterfly = 1;
    OLED_laser = 1;
    OLED_dht11 = 1;
  }
}
void select_Tunnel_light_mode()
{
  while(OLED_tunnel == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("LED"));
    display.println(F("Door and window"));
    display.println(F("^  Tunnel light"));
    display.println(F("Windmill"));
    display.println(F("Butterfly"));
    display.println(F("Laser"));
    display.println(F("DHT11"));
    display.println(F("Music"));
    display.display();
    
    OLED_LED = 1;
    OLED_servo = 1;
    OLED_tunnel = 0;
    OLED_music = 1;
    OLED_windmill = 1;
    OLED_butterfly = 1;
    OLED_laser = 1;
    OLED_dht11 = 1;
  }
}
void select_Music_mode()
{
  while(OLED_music == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("LED"));
    display.println(F("Door and window"));
    display.println(F("Tunnel light"));
    display.println(F("Windmill"));
    display.println(F("Butterfly"));
    display.println(F("Laser"));
    display.println(F("DHT11"));
    display.println(F("^  Music"));
    display.display();
    
    OLED_LED = 1;
    OLED_servo = 1;
    OLED_tunnel = 1;
    OLED_music = 0;
    OLED_windmill = 1;
    OLED_butterfly = 1;
    OLED_laser = 1;
    OLED_dht11 = 1;
  }
}
void select_butterfly_mode()
{
  while(OLED_butterfly == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("LED"));
    display.println(F("Door and window"));
    display.println(F("Tunnel light"));
    display.println(F("Windmill"));
    display.println(F("^  Butterfly"));
    display.println(F("Laser"));
    display.println(F("DHT11"));
    display.println(F("Music"));
    display.display();
    
    OLED_LED = 1;
    OLED_servo = 1;
    OLED_tunnel = 1;
    OLED_music = 1;
    OLED_windmill = 1;
    OLED_butterfly = 0;
    OLED_laser = 1;
    OLED_dht11 = 1;
  }
}
void select_laser_mode()
{
  while(OLED_laser == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("LED"));
    display.println(F("Door and window"));
    display.println(F("Tunnel light"));
    display.println(F("Windmill"));
    display.println(F("Butterfly"));
    display.println(F("^  Laser"));
    display.println(F("DHT11"));
    display.println(F("Music"));
    display.display();
    
    OLED_LED = 1;
    OLED_servo = 1;
    OLED_tunnel = 1;
    OLED_music = 1;
    OLED_windmill = 1;
    OLED_butterfly = 1;
    OLED_laser = 0;
    OLED_dht11 = 1;
  }
}
void select_dht11_mode()
{
  while(OLED_dht11 == 1)
  {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("LED"));
    display.println(F("Door and window"));
    display.println(F("Tunnel light"));
    display.println(F("Windmill"));
    display.println(F("Butterfly"));
    display.println(F("Laser"));
    display.println(F("^  DHT11"));
    display.println(F("Music"));
    display.display();
    
    OLED_LED = 1;
    OLED_servo = 1;
    OLED_tunnel = 1;
    OLED_music = 1;
    OLED_windmill = 1;
    OLED_butterfly = 1;
    OLED_laser = 1;
    OLED_dht11 = 0;
  }
}


void play_music(int buzzer_pin)
{
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
