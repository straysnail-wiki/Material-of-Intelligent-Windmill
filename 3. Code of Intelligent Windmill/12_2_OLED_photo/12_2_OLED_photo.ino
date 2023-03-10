#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 'cat', 128x64px
const unsigned char cat [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xeb, 
  0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x4b, 
  0xec, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0x9b, 
  0xcf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xc3, 
  0xd9, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0xff, 0xb7, 
  0xd9, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe2, 0xff, 0x7f, 
  0xd9, 0x70, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x7e, 0xff, 
  0xde, 0x7f, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01, 0xff, 
  0xdf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xcf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xef, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xf3, 0xe0, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xf8, 0x0e, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xdf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xce, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0x7f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xfc, 0x9f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xff, 0xfb, 0xdf, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd2, 0xff, 0xe6, 0x1f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd0, 0x40, 0x68, 0x1f, 0xff, 
  0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd0, 0x3f, 0x10, 0x1f, 0xff, 
  0xff, 0xff, 0xff, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd0, 0xff, 0xe0, 0x5f, 0xff, 
  0xf0, 0xff, 0xff, 0xbb, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xf8, 0x5f, 0xff, 
  0xf6, 0x7f, 0xff, 0x7b, 0xff, 0xff, 0xf9, 0x9c, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xfe, 0x5f, 0xff, 
  0xf4, 0x7f, 0xff, 0x63, 0xff, 0xff, 0xf2, 0x06, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xdf, 0xff, 
  0xec, 0xbf, 0xff, 0x4b, 0x9f, 0xff, 0xe8, 0x02, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xcf, 0xff, 
  0xec, 0x3f, 0xfe, 0xcb, 0x6f, 0xff, 0xd0, 0x06, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xef, 0xff, 
  0xe8, 0x5f, 0xfe, 0x83, 0x77, 0xf0, 0x00, 0x21, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xef, 0xff, 
  0xe8, 0x5f, 0xfe, 0x86, 0xfb, 0xc7, 0xe0, 0x8f, 0xff, 0xff, 0xff, 0xef, 0xff, 0x07, 0xe7, 0xff, 
  0xe8, 0x1f, 0xfe, 0x86, 0xfb, 0xbf, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x7e, 0xfb, 0xf7, 0xff, 
  0xe0, 0x2c, 0x00, 0x06, 0xfc, 0x7f, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x3d, 0xfd, 0xf7, 0xff, 
  0xf0, 0x21, 0xff, 0x06, 0x78, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xbb, 0xfc, 0xf7, 0xff, 
  0xf0, 0x6f, 0xff, 0xd7, 0x7b, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xd9, 0x9b, 0xde, 0xf7, 0xff, 
  0xf4, 0xff, 0xff, 0xe7, 0x7b, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xd0, 0xd3, 0x8e, 0xf7, 0xff, 
  0xf5, 0xff, 0xff, 0xf7, 0x7b, 0xff, 0xfd, 0xff, 0xc7, 0xff, 0xcf, 0xd0, 0xd7, 0x06, 0xf7, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0x7b, 0xff, 0xc1, 0xff, 0xa2, 0x00, 0x97, 0xd0, 0xc7, 0x0e, 0x13, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0x93, 0x1f, 0xd9, 0xff, 0x81, 0xfe, 0x07, 0xd1, 0x83, 0x8f, 0xeb, 0xff, 
  0xfb, 0xcf, 0xf0, 0xf7, 0xc3, 0x6f, 0xc1, 0xff, 0x4f, 0xff, 0xc7, 0x9f, 0x83, 0x9f, 0xf3, 0xff, 
  0xfb, 0x93, 0xec, 0xf7, 0xfa, 0x0f, 0xc1, 0xff, 0x1f, 0xff, 0xe3, 0xbf, 0xef, 0xff, 0xf1, 0xff, 
  0xfb, 0x35, 0xe8, 0xf7, 0xfd, 0x0f, 0xf5, 0xff, 0x3f, 0xff, 0xf3, 0x3f, 0xef, 0xff, 0xf9, 0xff, 
  0xfb, 0x75, 0xf6, 0xf7, 0xfd, 0x9e, 0x3d, 0xff, 0x7f, 0xff, 0xfb, 0x7f, 0xe7, 0xff, 0xfb, 0xff, 
  0xfb, 0xbb, 0xf9, 0xf7, 0xfd, 0xfc, 0x3d, 0xfe, 0x61, 0xfe, 0x7b, 0x3f, 0xe3, 0xff, 0xf3, 0xff, 
  0xfb, 0x93, 0xff, 0xf7, 0xfd, 0xfe, 0x40, 0x3e, 0xe8, 0xfc, 0x3b, 0xbf, 0xff, 0xff, 0xf3, 0xff, 
  0xfb, 0xce, 0x00, 0x00, 0x3d, 0x87, 0x70, 0xce, 0xea, 0xfc, 0x3b, 0x9f, 0xff, 0xff, 0xf7, 0xff, 
  0xfb, 0xc0, 0x1c, 0x03, 0xfc, 0x07, 0x7c, 0x0e, 0xe1, 0xc4, 0x7b, 0xcf, 0xff, 0xff, 0xe7, 0xff, 
  0xf8, 0x02, 0x1f, 0xc0, 0x72, 0x1f, 0x7d, 0xbc, 0xff, 0xb7, 0xf9, 0xf3, 0xff, 0xff, 0xe7, 0xff, 
  0xc2, 0x27, 0xbf, 0xf0, 0x3c, 0x3f, 0x7c, 0xfd, 0xff, 0xa7, 0xf9, 0xfb, 0xff, 0xff, 0xe7, 0xff, 
  0xf1, 0x9f, 0xbf, 0xf3, 0xfe, 0xfe, 0x7c, 0xfd, 0x80, 0xcc, 0x3d, 0xf9, 0xff, 0xff, 0xf7, 0xff, 
  0xea, 0x7f, 0xbf, 0xf3, 0xf8, 0xfe, 0x7c, 0xf0, 0x7f, 0xce, 0x05, 0xfd, 0xff, 0xff, 0xf7, 0xff, 
  0xf1, 0xff, 0x9f, 0xf7, 0xfe, 0xfe, 0x7d, 0xfd, 0xc1, 0xdc, 0x98, 0xfd, 0xff, 0xff, 0xf7, 0xff, 
  0xe3, 0xff, 0x9f, 0xf7, 0xfe, 0xff, 0xfd, 0xf8, 0x1d, 0xde, 0x65, 0x7d, 0xff, 0xff, 0xf7, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0xfe, 0xff, 0xfd, 0xf5, 0xe3, 0xff, 0x99, 0xfc, 0xff, 0xff, 0xf3, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0xfe, 0xff, 0xfd, 0xfd, 0x1f, 0xff, 0xcd, 0xfe, 0xff, 0xff, 0xf3, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0xfe, 0xff, 0xfd, 0xf8, 0xff, 0xff, 0xf1, 0xfe, 0xff, 0xff, 0xfb, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0xfe, 0xff, 0xfd, 0xfd, 0xff, 0xff, 0xf9, 0xfe, 0xff, 0xff, 0xfb, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0xfd, 0xff, 0xfd, 0xfd, 0xff, 0xff, 0xfc, 0xfe, 0xff, 0xff, 0xfb, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0xfd, 0xff, 0xfd, 0xfd, 0xff, 0xff, 0xfd, 0xfe, 0xff, 0xff, 0xfb, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0xfd, 0xff, 0xfd, 0xfd, 0xff, 0xff, 0xfd, 0xfe, 0x7f, 0xff, 0xfb, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0xfd, 0xff, 0xfd, 0xfd, 0xff, 0xff, 0xfd, 0xff, 0x7f, 0xff, 0xf9, 0xff, 
  0xfb, 0xff, 0xff, 0xf7, 0xfd, 0xff, 0xfd, 0xfd, 0xff, 0xff, 0xfd, 0xff, 0x7f, 0xff, 0xf9, 0xff, 
  0xfb, 0xff, 0xff, 0xe7, 0xfd, 0xff, 0xfd, 0xfd, 0xff, 0xff, 0xfd, 0xff, 0x7f, 0xff, 0xf9, 0xff, 
  0xfb, 0xff, 0xff, 0xef, 0xfd, 0xff, 0xfd, 0xfd, 0xff, 0xff, 0xfd, 0xff, 0x3f, 0xff, 0xfd, 0xff
};

void setup() {
  Serial.begin(115200);
 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000); // Pause for 2 seconds
 
  // Clear the buffer.
  display.clearDisplay();
  display.drawBitmap(0, 0, cat, 128, 64, 1);
  display.display();
  delay(200);
}
 
void loop() {

}
