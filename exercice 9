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
    Serial.println("écran non fonctionel.");
    while (1);
  }

  tft.fillScreen(ILI9341_BLACK); // Clear screen

  // Draw a red square with "0" in the middle
  drawRedSquareWithNumber();

  // Draw the keyboard
  drawKeyboard();
}

void loop() {
  // Detect key presses
  detectKeyPress();
}

void drawRedSquareWithNumber() {
  int squareSize = 50;
  int centerX = (screenWidth - squareSize) / 2;
  int centerY = (screenHeight - squareSize) / 2;

  // Draw red square
  tft.fillRect(centerX, centerY, squareSize, squareSize, ILI9341_RED);

  // Draw "0" in the center
  tft.setCursor(centerX + squareSize / 4, centerY + squareSize / 4);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK);
  tft.println("0");
}

void drawKeyboard() {
  int buttonWidth = screenWidth / 3;  // Width of each button
  int buttonHeight = screenHeight / 4; // Height of each button

  const char *keys[] = {
    "1", "2", "3",
    "4", "5", "6",
    "7", "8", "9",
    "*", "0", "#"
  };

  // Draw each button
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 3; col++) {
      int x = col * buttonWidth;
      int y = row * buttonHeight;

      // Draw button rectangle
      tft.fillRect(x, y, buttonWidth, buttonHeight, ILI9341_WHITE);
      tft.drawRect(x, y, buttonWidth, buttonHeight, ILI9341_BLACK);

      // Add button label
      tft.setCursor(x + buttonWidth / 3, y + buttonHeight / 3);
      tft.setTextSize(2);
      tft.setTextColor(ILI9341_BLACK);
      tft.println(keys[row * 3 + col]);
    }
  }
}

void detectKeyPress() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();

    // Map touch coordinates to screen coordinates
    int x = map(p.x, TS_MINX, TS_MAXX, 0, screenWidth);
    int y = map(p.y, TS_MINY, TS_MAXY, 0, screenHeight);

    // Calculate button pressed
    int buttonWidth = screenWidth / 3;
    int buttonHeight = screenHeight / 4;

    int col = x / buttonWidth;
    int row = y / buttonHeight;

    if (row >= 0 && row < 4 && col >= 0 && col < 3) {
      const char *keys[] = {
        "1", "2", "3",
        "4", "5", "6",
        "7", "8", "9",
        "*", "0", "#"
      };
      Serial.println(keys[row * 3 + col]); // Print the key pressed
    }
  }
}

