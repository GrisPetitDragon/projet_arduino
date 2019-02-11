// Import de la librairie SoftwareSerial
#include <SoftwareSerial.h>
// Pin 10 (arduino RX --> carte Bluetooth TxD)
#define RxD 10
// Pin 11 (arduino TX- -> carte Bluetooth RxD)
#define TxD 11
// Pin 9 (renommage carte Bluetooth)
#define Key 9
// Simulation liaison Bluetooth
SoftwareSerial BTSerie(RxD,TxD);
// Variable pour enregistrer des chaines de caractères
String ans = String("");

void setup()
{
  // Initialisation de la communication Série
  InitCommunicationSerie();
  
  // Configuration du Bluetooth
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  // Configuration le mode admin (clé)
  pinMode(Key, OUTPUT);

  // Initialisation de la communication Bluetooth
  InitCommunicationBluetooth();
  
  // Activer le mode AT
  digitalWrite(Key,HIGH);

  // Configuration par défaut du périphérique Bluetooth
  BTSerie.print("AT+ORGL\r\n");
  Serial.println("AT+ORGL");
  ans = BTSerie.readString();
  Serial.println(ans);

  // Récupérer le nom du périphérique Bluetooth
  BTSerie.print("AT+NAME?\r\n");
  Serial.println("AT+NAME?");
  ans = BTSerie.readString();
  Serial.println(ans);

  // Configurer le nom du périphérique Bluetooth
  BTSerie.print("AT+NAME=BT-Carte1\r\n");
  Serial.println("AT+NAME=BT-Carte1");
  ans = BTSerie.readString();
  Serial.println(ans);

  // Récupérer le nom du périphérique Bluetooth
  BTSerie.print("AT+NAME?\r\n");
  Serial.println("AT+NAME?");
  ans = BTSerie.readString();
  Serial.println(ans);

  // Récupération de l'état du périphérique Bluetooth
  BTSerie.print("AT+STATE?\r\n");
  Serial.println("AT+STATE?");
  ans = BTSerie.readString();
  Serial.println(ans);

  // Désactiver le mode AT
  digitalWrite(Key,LOW);
}

void loop()
{
  // Récupération et affichage de la température
  int temp = analogRead(A0);
  float temp_c = temp*(5.0/1023.0*100.0); // conversion celcius en degré
  //int temp_c = temp*(5.0/1023.0*100.0);
  
  // Affichage de la température sur liaison Bluetooth
  BTSerie.println(String(temp_c));
  
  // Affichage de la température sur liaison Serie
  Serial.println(String(temp_c));

  // Affichage de l'état du périphérique Bluetooth
  displayState();
  
  // Attente pour la prochaine exécution
  delay(2500);
}

// Initialisation communication Série
void InitCommunicationSerie()
{
  Serial.begin(38400);
  while(!Serial){}
}

// Initialisation communication bluetooth
void InitCommunicationBluetooth()
{
  BTSerie.begin(38400); //57600 //38400 //9600
  while(!BTSerie){}
}

// Récupérer l'état du périphérique bluetooth
void displayState()
{
  // Configuration le mode admin (clé)
  pinMode(Key, OUTPUT);
  // Activer le mode AT
  digitalWrite(Key,HIGH);
  
  // Récupération de l'état du périphérique Bluetooth
  BTSerie.print("AT+STATE?\r\n");
  Serial.println("AT+STATE?");
  ans = BTSerie.readString();
  Serial.println(ans);

  // Désactiver le mode AT
  digitalWrite(Key,LOW);
}
