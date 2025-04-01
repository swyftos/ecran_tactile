#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

//tactile
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
//TFT
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

//variables du projet
boolean appui = true;
const int buzzerPin = 8; // Correspond à D4 sur la base shield
const int correctCode = 1111; // Code du digicode

int enteredCode = 0; // Code saisi
int currentMultiplier = 1000; // Multiplicateur initial (4 chiffres)

int buttonWidth = 80; // Largeur d'un bouton
int buttonHeight = 80; // Hauteur d'un bouton
bool isTouching = false; // Vérifie si une touche est en cours de maintien
int lastRow = -1; // Stocker la dernière ligne touchée
int lastCol = -1; // Stocker la dernière colonne touchée

void setup() {
  // Configurer la broche du buzzer comme sortie
  pinMode(buzzerPin, OUTPUT);

  // Gestion de la liaison série avec l'écran
  Serial.begin(9600);
  tft.begin();
  if (!ts.begin()) {
    Serial.println("Unable to start touchscreen.");
  } else {
    Serial.println("Touchscreen started.");
  }
  tft.fillScreen(ILI9341_BLACK);

  // Dessiner les boutons du digicode
  drawKeyboard();
}

void playNote(int frequency, int duration) {
  tone(buzzerPin, frequency);
  delay(duration);
  noTone(buzzerPin);
}

void drawKeyboard() {
  // Dessiner une matrice 3x4 pour les chiffres
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 3; col++) {
      int x = col * buttonWidth;
      int y = row * buttonHeight;
      tft.fillRect(x, y, buttonWidth, buttonHeight, ILI9341_YELLOW);
      tft.drawRect(x, y, buttonWidth, buttonHeight, ILI9341_BLACK);
      // Afficher les chiffres sur les boutons
      int number = row * 3 + col + 1;
      if (number <= 9 || (row == 3 && col == 1)) {
        tft.setCursor(x + buttonWidth / 2 - 10, y + buttonHeight / 2 - 10);
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(2);
        tft.print((row == 3 && col == 1) ? 0 : number);
      }
    }
  }
}

void highlightButton(int row, int col, uint16_t color) {
  int x = col * buttonWidth;
  int y = row * buttonHeight;
  tft.fillRect(x, y, buttonWidth, buttonHeight, color);
  tft.drawRect(x, y, buttonWidth, buttonHeight, ILI9341_BLACK);
  int number = row * 3 + col + 1;
  if (number <= 9 || (row == 3 && col == 1)) {
    tft.setCursor(x + buttonWidth / 2 - 10, y + buttonHeight / 2 - 10);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.print((row == 3 && col == 1) ? 0 : number);
  }
}

void loop() {

  // Détection du tactile
  if (ts.touched()) {
    TS_Point p = ts.getPoint();

    // Convertir les coordonnées tactiles en pixels de l'écran
    int x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    int y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    // Vérifier quelle touche a été pressée
    int col = x / buttonWidth;
    int row = y / buttonHeight;

    if (row >= 0 && row < 4 && col >= 0 && col < 3) {
      // Vérifier si la touche actuelle est différente de la dernière
      if (!isTouching || row != lastRow || col != lastCol) {
        // Calculer le numéro correspondant
        int number = row * 3 + col + 1;
        if (number == 11) number = 0; // Bouton "0"
        if (number >= 0 && number <= 9) {
          // Mettre à jour l'interface pour montrer l'appui
          highlightButton(row, col, ILI9341_BLUE); // Coloriser en bleu à l'appui
          playNote(220, 200); // LA3 pour chaque appui
          delay(200);
          highlightButton(row, col, ILI9341_YELLOW); // Revenir à la couleur d'origine

          // Mettre à jour le code saisi
          enteredCode += number * currentMultiplier;
          currentMultiplier /= 10;
        }

        // Vérifier si le code complet a été saisi
        if (currentMultiplier == 0) {
          if (enteredCode == correctCode) {
            playNote(261, 1000); // DO4 pour code correct
          } else {
            playNote(147, 1000); // RÉ3 pour code incorrect
          }
          // Réinitialiser pour une nouvelle tentative
          enteredCode = 0;
          currentMultiplier = 1000;
        }

        // Mettre à jour les dernières coordonnées de touche
        lastRow = row;
        lastCol = col;
        isTouching = true;
      }
    }
  } else {
    // Si aucune touche n'est pressée
    isTouching = false;
    lastRow = -1; // Réinitialiser la dernière ligne touchée
    lastCol = -1; // Réinitialiser la dernière colonne touchée
  }
}

