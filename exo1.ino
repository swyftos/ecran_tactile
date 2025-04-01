//Gestion d'un écran tactile
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

void carre()
{
    // Remplir un carré sur l'écran
    tft.fillRect(50, 50, 100, 100, ILI9341_RED); // Position (50, 50), taille 100x100, couleur rouge
}

// la fonction setup est activée lors d'un reset ou lorsque la carte est alimentée
void setup() 
{
    // gestion de la liaison série avec l'écran
    Serial.begin(9600);
    tft.begin();
    if (!ts.begin()) {
        Serial.println("Unable to start touchscreen.");
    } else {
        Serial.println("Touchscreen started.");
    }
    tft.fillScreen(ILI9341_BLACK);
    carre(); // Dessine un carré au démarrage
}

// la fonction loop est une boucle permanente
void loop()
{
    // Vérification de l'état tactile
    if (ts.touched()) {
        // Obtenir les coordonnées tactiles
        TS_Point p = ts.getPoint();
        // Conversion des coordonnées brutes en coordonnées écran
        p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

        // Affiche les coordonnées
        Serial.print("Touch at: ");
        Serial.print(p.x);
        Serial.print(", ");
        Serial.println(p.y);

        // Dessine un carré rouge où le contact est détecté
        tft.fillRect(p.x - 10, p.y - 10, 20, 20, ILI9341_RED);
    }
}


//crée un objet appelé ts à partir de la classe Adafruit_STMPE610. Cet objet permet de gérer le contrôleur tactile STMPE610, souvent utilisé avec des écrans tactiles résistifs.

Le paramètre STMPE_CS, qui vaut 8 (défini plus haut dans le code par #define STMPE_CS 8), spécifie que la broche numéro 8 de la carte Arduino sera utilisée comme broche de sélection de circuit (Chip Select) pour la communication avec le contrôleur. Cette broche est nécessaire pour établir une communication via le protocole SPI.

En résumé, cette ligne initialise l'objet ts, qui permet ensuite d'utiliser les fonctionnalités offertes par la bibliothèque Adafruit_STMPE610. Par exemple, vous pourrez détecter si l'écran est touché ou obtenir les coordonnées du point de contact.
