#include <SoftwareSerial.h>

// pin 10 pour arduino RX --> TxD de la carte Bluetooth
#define RxD 10
// pin 11 pour arduino TX- -> RxD de la carte Bluetooth
#define TxD 11
// pin 9 pour renommage de la carte Bluetooth
#define Key 9

// simulation liaison Série pour le Bluetooth
SoftwareSerial BTSerie(RxD,TxD);

String ans = String("");

void setup()
{
  // Initialisation de la communication Série
  InitCommunicationSerie();
  
  // Configuration du Bluetooth
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  // Configuration du renommage
  pinMode(Key, OUTPUT);

  // Initialisation de la communication Bluetooth
  InitCommunicationBluetooth();
  
  // Configuration du périphérique Bluetooth
  digitalWrite(Key,HIGH);
  
  BTSerie.print("AT+NAME=BT-Carte1\r\n");
  Serial.println("AT+NAME=BT-Carte1");
  ans = BTSerie.readString();
  Serial.println(ans);

  BTSerie.print("AT+NAME?\r\n");
  Serial.println("AT+NAME?");
  ans = BTSerie.readString();
  Serial.println(ans);
  
  /*
  BTSerie.print("AT+RMAAD\r\n");
  Serial.println("AT+RMAAD");
  ans = BTSerie.readString();
  Serial.println(ans);
  
  BTSerie.print("AT+ROLE=0\r\n");
  Serial.println("AT+ROLE=0");
  ans = BTSerie.readString();
  Serial.println(ans);
  
  BTSerie.print("AT+UART=38400\r\n");
  Serial.println("AT+UART=38400");
  ans = BTSerie.readString();
  Serial.println(ans);
  */
  
  digitalWrite(Key,LOW);

  // Début de la transmission sur la liaison Série
  //Serial.begin(38400);
}

void loop()
{
  // Récupération et affichage de la température
  int temp = analogRead(A0);
  float temp_c = temp*(5.0/1023.0*100.0); // conversion celcius en degré
  // Affichage de la température sur liaison Serie
  BTSerie.println(String(temp_c));
  // Affichage de la température sur liaison Bluetooth
  Serial.println(String(temp_c));
  
  // Si communication Bluetooth disponible
  if(BTSerie.available()){}

  // Si communication Série disponible
  if(Serial.available()){}
  
  // Attente d'une seconde pour la prochaine exécution
  delay(2000);
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
