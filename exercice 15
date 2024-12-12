const int buzzerPin = 8; // Correspond à D4 sur la base shield

void setup() {
  // Configurer la broche du buzzer comme sortie
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Jouer la fréquence 440 Hz pendant 10 secondes
  tone(buzzerPin, 440); // Émettre un son à 435 Hz
  delay(3000); // Attendre 10 secondes
  noTone(buzzerPin); // Arrêter le son

  delay(1000); // Pause de 1 seconde entre les fréquences

  // Jouer la fréquence 523 Hz pendant 3 secondes
  tone(buzzerPin, 523); // Émettre un son à 488 Hz
  delay(3000); // Attendre 20 secondes
  noTone(buzzerPin); // Arrêter le son

  delay(1000); // Pause de 1 seconde avant de recommencer

 // Jouer la fréquence 523 Hz pendant 3 secondes
   tone(buzzerPin, 293); // Émettre un son à 293 Hz
  delay(3000); // Attendre 20 secondes
  noTone(buzzerPin); // Arrêter le son
  
  
  delay(500);
}


