#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST -1  // Set TFT_RST to -1 if the display doesn't have a reset pin

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  tft.begin();

  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(3);  // Adjust the rotation as needed
  
  drawStar();
}

void drawStar() {
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  
  int star_size = 480; // Changeable, preferably from 100 to what your screen dimensions allow
  int star_points = 19; // Changeable but always an ODD number
  float interior_angle_at_star_point = 360.0 / star_points / 2;
  float angle = 90 - interior_angle_at_star_point / 2;

  int x = tft.width() / 2;
  int y = tft.height() / 2 - star_size / 2;

  uint16_t colors[] = {ILI9341_YELLOW, ILI9341_ORANGE, ILI9341_CYAN};

  for (int i = 0; i < star_points; ++i) {
    for (int j = 0; j < 3; ++j) {
      tft.drawLine(x, y, x + cos(angle * PI / 180) * (star_size / 3),
                   y + sin(angle * PI / 180) * (star_size / 3), colors[j]);
      x = x + cos(angle * PI / 180) * (star_size / 3);
      y = y + sin(angle * PI / 180) * (star_size / 3);
      angle += interior_angle_at_star_point;
    }
    angle += 180 - interior_angle_at_star_point;
  }
}

void loop() {
  // Your loop code here
}
