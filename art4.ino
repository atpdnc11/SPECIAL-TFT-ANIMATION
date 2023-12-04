#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  -1  // RST can be left unconnected
#define TFT_LED  7

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);

  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);

  // Display color square grid and triangles
  displayColorSquareGrid();
  delay(2000);
  tft.fillScreen(ILI9341_BLACK);

  displayColorTriangles();
  delay(2000);
  tft.fillScreen(ILI9341_BLACK);

  animateTriangle(); // Call the function from Code 2

  // Write "Arvind" in yellow color
  writeArvindYellow();
}

void loop() {
  // Your main code (if any) goes here
}

void displayColorSquareGrid() {
  int side = 150;
  int spacing = 10;

  for (int i = 0; i < 10; ++i) {
    uint16_t color = tft.color565(i * 20, i * 10, 255 - i * 15);
    tft.fillRect(10 + i * spacing, 10 + i * spacing, side, side, color);
    side -= 5;
  }
}

void displayColorTriangles() {
  int side = 150;
  int spacing = 10;

  for (int i = 0; i < 10; ++i) {
    uint16_t color = tft.color565(i * 20, 255 - i * 10, i * 15);
    int x0 = 80 + i * spacing;
    int y0 = 30 + i * spacing;
    int x1 = 140 + i * spacing;
    int y1 = 70 + i * spacing;
    int x2 = 40 + i * spacing;
    int y2 = 70 + i * spacing;
    tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
    side -= 5;
  }
}

void animateTriangle() {
  int x1 = 120;
  int y1 = 30;
  int x2 = 30;
  int y2 = 200;
  int x3 = 210;
  int y3 = 200;

  int size = 200;
  int colorStep = 5;

  while (size > 0) {
    for (int i = 0; i < size; i++) {
      int currX1 = x1 + (x2 - x1) * i / size;
      int currY1 = y1 + (y2 - y1) * i / size;
      int currX2 = x1 + (x3 - x1) * i / size;
      int currY2 = y1 + (y3 - y1) * i / size;

      uint16_t color = tft.color565(
        255 * (1 + sin(colorStep * i * PI / 180.0)) / 2,
        255 * (1 + sin(colorStep * (i + 120) * PI / 180.0)) / 2,
        255 * (1 + sin(colorStep * (i + 240) * PI / 180.0)) / 2
      );

      tft.drawLine(currX1, currY1, currX2, currY2, color);
    }

    size -= 10;
    delay(100);
    tft.fillScreen(ILI9341_BLACK);
  }

  writeArvind();
}

void writeArvind() {
  tft.setCursor(80, 120);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Arvind");
}

void writeArvindYellow() {
  tft.setCursor(10, 290);
  tft.setTextColor(ILI9341_YELLOW);
  tft.print("Arvind");
}
