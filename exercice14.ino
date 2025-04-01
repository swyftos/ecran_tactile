const int buzzerPin = 8; // Correspond à D4 sur la base shield

void setup() {
  // Configurer la broche du buzzer comme sortie
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Jouer la fréquence 435 Hz pendant 10 secondes
  tone(buzzerPin, 435); // Émettre un son à 435 Hz
  delay(800); // Attendre 10 secondes
  noTone(buzzerPin); // Arrêter le son

  delay(500); // Pause de 1 seconde entre les fréquences

  // Jouer la fréquence 488 Hz pendant 20 secondes
  tone(buzzerPin, 488); // Émettre un son à 488 Hz
  delay(1000); // Attendre 20 secondes
  noTone(buzzerPin); // Arrêter le son

  delay(500); // Pause de 1 seconde avant de recommencer
}

//Dans ce code :

La fonction tone() génère une onde carrée à la fréquence spécifiée (en Hz) sur la broche du buzzer.
La fonction noTone() arrête le son émis par le buzzer.
Les délais (delay()) contrôlent la durée pendant laquelle chaque fréquence est jouée (10 secondes pour 435 Hz et 20 secondes pour 488 Hz).
Une pause d'1 seconde est ajoutée entre les deux fréquences pour une meilleure distinction.
Le programme recommence indéfiniment grâce à la boucle loop().
