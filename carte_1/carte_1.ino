#include <SoftwareSerial.h> // Import de la librairie SoftwareSerial

#define RxD 10 // Pin 10 (arduino RX --> carte Bluetooth TxD)
#define TxD 11 // Pin 11 (arduino TX- -> carte Bluetooth RxD)
#define Key 9 // Pin 9 (renommage carte Bluetooth)

SoftwareSerial BTSerie(RxD,TxD); // Simulation liaison Bluetooth

String ans = String(""); // Variable pour enregistrer des chaines de caractères

void setup()
{
  Serial.begin(38400); // Initialisation de la communication Série
  
  pinMode(RxD, INPUT); // Configuration RxD Bluetooth
  pinMode(TxD, OUTPUT); // Configuration TxD Bluetooth
  pinMode(Key, OUTPUT); // Configuration mode AT

  BTSerie.begin(38400); // Initialisation communication bluetooth
  
  digitalWrite(Key,HIGH);  // Activer le mode AT

  BTSerie.print("AT+ORGL\r\n"); // Configuration par défaut du périphérique Bluetooth
  BTSerie.print("AT+NAME?\r\n"); // Récupérer le nom du périphérique Bluetooth (vérification de la configuration par défaut)
  BTSerie.print("AT+NAME=BT-Carte1\r\n"); // Configurer le nom du périphérique Bluetooth
  BTSerie.print("AT+NAME?\r\n"); // Récupérer le nom du périphérique Bluetooth (vérification du renommage du périphérique)
  BTSerie.print("AT+STATE?\r\n"); // Récupération de l'état du périphérique Bluetooth

  // Serial.println("Command AT"); // affichage sur la liaison Série de chaque commande AT exécutée sur la liaison Bluetooth
  // ans = BTSerie.readString(); // récupération de la valeur de retour sur la liaison Bluetooth
  // Serial.println(ans); // affichage de la valeur de retour sur sur la liaison Série

  digitalWrite(Key,LOW); // Désactiver le mode AT
}

void loop()
{
  int temp = analogRead(A0); // Récupération et affichage de la température (pin A0)
  float temp_c = temp*(5.0/1023.0*100.0); // conversion en degré Celsius
  
  BTSerie.println(String(temp_c)); // Affichage de la température sur liaison Bluetooth
  Serial.println(String(temp_c)); // Affichage de la température sur liaison Serie
  
  delay(2500); // Attente pour la prochaine exécution
}
