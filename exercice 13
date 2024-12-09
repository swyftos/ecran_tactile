const int buzzerPin = 8; // Correspond à D4 sur la base shield
int tempo=50;

void setup() {
  // Configurer la broche du buzzer comme sortie
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Activer le buzzer (émettre un son)
  digitalWrite(buzzerPin, HIGH);
  delayMicroseconds(tempo); // Attendre 1 seconde

  // Désactiver le buzzer (arrêter le son)
  digitalWrite(buzzerPin, LOW);
  delayMicroseconds(tempo); // Attendre 1 seconde
  //tempo=tempo+20;
}

