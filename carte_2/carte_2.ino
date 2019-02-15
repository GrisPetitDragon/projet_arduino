#include "constantes.h"

float TEMPERATURE; // dernière température mesurée

SoftwareSerial BTSerie(TX,RX);

void setup() {
  ACTIF = 0;
  InitCommunicationSerie();
  Serial.println("Initalisation de la carte: OK");
  //On configure les broches d'entrée et de sorties de la carte (voir le fichier constantes.h pour les valeurs de TX et RX)
  pinMode(TX, INPUT);
  pinMode(RX, OUTPUT);

  pinMode(PIN_LOW, OUTPUT);
  digitalWrite(PIN_LOW, LOW); // Low sur la patte courte des LED
  
  InitCommunicationBluetoothSerie();
  configModuleBT();

}
//Cette fonction intialise la connextion série
void InitCommunicationSerie() {
  Serial.begin(9600);
  Serial.println("Demarrage connexion serie : OK");
}

// Cette fonction initialise la connextion série avec le module Bluetooth
void InitCommunicationBluetoothSerie() {
  BTSerie.begin(9600); //38400 / 57600 / 38400
  while (!BTSerie) {
    Serial.println("Attente réponse bluetooth");
  }
  Serial.println("Démarrage connexion bluetooth serie : OK");
}

//Cette fonction demande sa version au module bluetooth
void configModuleBT() {
  char c;
  BTSerie.print("AT+VERSION?");
  BTSerie.print("\r\n");
  Serial.println("Demande version ?");
  //lecture caractère par caractère de la réponse
  while (BTSerie.available()) {
    c = BTSerie.read();
    Serial.print(c);
  }
}
//fonction qui s'exécute lorsque l'on envoie le code '1' au radar (voir fonction loop plus bas) pour l'activer
void hello() {
  //on passe cette constante à 1 : cela veut dire que le dispositif est activé et qu'un terminal Bluetooth peut l'interroger, pour lui demander la distance mesurée notamment.
  ACTIF = 1;
  //TODO : dire bonjour
}

//fonction qui affiche la dernière distance mesurée par le capteur à US - cela ne marche que si le radar est actif c'est à dire que l'on a axécuté la fonction hello auparavant
void temperature() {
  if (ACTIF == 1) {
    // Demander la température au modèle
    BTSerie.print(F("La température est de : "));
    BTSerie.print(TEMPERATURE);
  } else {
    BTSerie.println("Le thermomètre est inactif\r\n");
  }
}

//Eteint le dispositif et envoie un signal avec les LED pour saluer l'utilisateur et lui indiquer qu'il a désacttivé le dispositif
void goodbye() {
  // on désactive le dispositif
  ACTIF = 0;

  
}

/*Cette fonction vérifie en permanence:
- si un utilisateur a saisi quelque chose depuis le terminal Bluetooth, et si cette saisie peut être interprétée, le système active la bonne fonction
- si un utilisateur a saisi quelque chose depuis la console (envoi sur le port série), auquel cas il l'envoie au terminal Bluetooth
*/
void loop() {
  char c;

  if (BTSerie.available()) {
    Serial.print("\nRéception de : ");
    
    while (BTSerie.available()) {
      c = BTSerie.read();
      Serial.print(c);
      switch(c){
        case '1' : hello();
        break;
        case '2' : temperature();
        break;
        case '0' : goodbye();
        break;
      }
      Serial.print(c);
    }
  }

  if (Serial.available()) {
    Serial.print("Envoi vers Bluetooth : ");
    while (Serial.available()) {
      c = Serial.read();
      Serial.print(c);
      BTSerie.print(c);
    }
  }
  delay(200);
}
