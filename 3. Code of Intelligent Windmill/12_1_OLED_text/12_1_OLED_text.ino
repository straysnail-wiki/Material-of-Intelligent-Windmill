#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // The display is 128 pixels long
#define SCREEN_HEIGHT 64 // The screen is 64 pixels wide
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C //OLED   IIC address of the screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10

void setup() {
  Serial.begin(9600);
  //Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
   // Clear screen
  display.clearDisplay();
  display.display();
}

void loop() {
  display.setTextSize(2);             // Set font size
  display.setTextColor(SSD1306_WHITE);        // Font color, there's only one color here
  // The starting position coordinates of the display, 0,0 is the top left corner
  display.setCursor(0,0);             
  //display.print(F("Windmill"));           //Display character
  display.println(F("Windmill"));           //Line feed display character
  display.println(F("Snail man"));
  display.display(); //display
  display.clearDisplay();    //clear screen
  delay(200);
}
