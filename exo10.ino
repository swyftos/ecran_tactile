#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>

// Calibration data for touch screen
#define TS_MINX 0
#define TS_MINY 0
#define TS_MAXX 3800
#define TS_MAXY 4000

// TFT and Touchscreen pin definitions
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int screenWidth = 240; // TFT width
int screenHeight = 320; // TFT height

void setup() {
  Serial.begin(9600);

  // Initialize TFT and touch screen
  tft.begin();
  if (!ts.begin()) {
    Serial.println("Unable to start touchscreen.");
    while (1);
  }

  tft.fillScreen(ILI9341_BLACK); // Clear screen

  // Draw the keyboard
  drawKeyboard();
}

void loop() {
  detectAndChangeKeyColor();
}

void drawKeyboard() {
  int buttonWidth = screenWidth / 3;  // Width of each button
  int buttonHeight = screenHeight / 4; // Height of each button

  // Draw each button
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 3; col++) {
      int x = col * buttonWidth;
      int y = row * buttonHeight;

      // Draw button rectangle
      tft.fillRect(x, y, buttonWidth, buttonHeight, ILI9341_YELLOW);
      tft.drawRect(x, y, buttonWidth, buttonHeight, ILI9341_BLACK);
    }
  }
}

void detectAndChangeKeyColor() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();

    // Convert raw touch to screen coordinates and reduce by a factor of 10
    int x = map(p.x, TS_MINX, TS_MAXX, 0, screenWidth) / 10;
    int y = map(p.y, TS_MINY, TS_MAXY, 0, screenHeight) / 10;

    // Calculate which button is touched
    int buttonWidth = screenWidth / 3;
    int buttonHeight = screenHeight / 4;

    int col = x / (buttonWidth / 10);  // Use scaled-down x
    int row = y / (buttonHeight / 10); // Use scaled-down y

    if (row >= 0 && row < 4 && col >= 0 && col < 3) {
      int xmin = col * buttonWidth;
      int xmax = xmin + buttonWidth;
      int ymin = row * buttonHeight;
      int ymax = ymin + buttonHeight;

      // Check if touch is within the button bounds
      if (x * 10 >= xmin && x * 10 <= xmax && y * 10 >= ymin && y * 10 <= ymax) {
        // Change button to blue
        tft.fillRect(xmin, ymin, buttonWidth, buttonHeight, ILI9341_BLUE);
        delay(200); // Wait 200 ms

        // Change button back to yellow
        tft.fillRect(xmin, ymin, buttonWidth, buttonHeight, ILI9341_YELLOW);
        tft.drawRect(xmin, ymin, buttonWidth, buttonHeight, ILI9341_BLACK);
      }
    }
  }
}
