#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>

// Calibration data for touch screen
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// Touch screen and TFT pin definitions
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  Serial.begin(9600);
  tft.begin();
  
  if (!ts.begin()) {
    Serial.println("Unable to start touchscreen.");
  } else {
    Serial.println("Touchscreen started.");
  }

  tft.fillScreen(ILI9341_BLACK); // Clear screen
  delay(1000);

  // Test each function
  testTFTFunctions();
}

void loop() {
  // No loop actions; the setup demonstrates the commands
}

void testTFTFunctions() {
  // Fill screen with a color
  tft.fillScreen(ILI9341_BLUE);
  delay(1000);

  // Draw a single pixel
  tft.drawPixel(50, 50, ILI9341_RED);
  delay(500);

  // Draw a vertical line
  tft.drawFastVLine(100, 20, 100, ILI9341_GREEN);
  delay(500);

  // Draw a horizontal line
  tft.drawFastHLine(50, 150, 100, ILI9341_YELLOW);
  delay(500);

  // Draw a filled rectangle
  tft.fillRect(120, 60, 50, 80, ILI9341_CYAN);
  delay(500);

  // Rotate screen
  for (int i = 0; i < 4; i++) {
    tft.setRotation(i);
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(10, 10);
    tft.setTextSize(2);
    tft.println("Rotation: " + String(i));
    delay(1000);
  }

  // Invert display colors
  tft.invertDisplay(true);
  delay(1000);
  tft.invertDisplay(false);
  delay(1000);

  // Display text
  tft.setRotation(0); // Reset rotation
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.println("Hello, TFT!");
  delay(1000);

  // Display larger text
  tft.setCursor(10, 50);
  tft.setTextSize(3);
  tft.println("Text Size: 3");
  delay(1000);

  // Draw shapes based on touch
  tft.fillScreen(ILI9341_BLACK);
  tft.println("Touch to draw!");

  while (true) {
    if (ts.touched()) {
      TS_Point p = ts.getPoint();
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

      tft.fillRect(p.x - 10, p.y - 10, 20, 20, ILI9341_RED);
      delay(100);
    }
  }
}

