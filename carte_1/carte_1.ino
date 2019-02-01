#include <SoftwareSerial.h>

// pin 10 pour arduino RX --> TxD de la carte Bluetooth
#define RxD 10
// pin 11 pour arduino TX- -> RxD de la carte Bluetooth
#define TxD 11
// pin 9 pour renommage de la carte Bluetooth
#define Key 9

// simulation liaison Série pour le Bluetooth
SoftwareSerial BTSerie(RxD,TxD);

void setup()
{
  // Initialisation de la communication Série
  InitCommunicationSerie();
  
  // Initialisation de la communication Bluetooth
  InitCommunicationBluetooth();
  
  // Configuration du Bluetooth
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  
  // Configuration du renommage
  pinMode(Key, OUTPUT);
  
  // Renommmage du périphérique Bluetooth 
  digitalWrite(Key,HIGH); 
  BTSerie.print("AT+NAME=BT-Carte1\r\n");
  BTSerie.print("AT+ROLE=0\r\n");
  digitalWrite(Key,LOW);

  // Début de la transmission sur la liaison Série
  Serial.begin(9600);
}

void loop()
{
  // Si communication Bluetooth disponible
  if(BTSerie.available())
  {
    // Récupération et affichage de la température
    int temp = analogRead(A0);
    float temp_c = temp*(5.0/1023.0*100.0); // conversion celcius en degré
    BTSerie.println("T1:"+String(temp_c));
  }

  // Si communication Série disponible
  if(Serial.available())
  {
    // Récupération et affichage de la température
    int temp = analogRead(A0);
    float temp_c = temp*(5.0/1023.0*100.0); // conversion celcius en degré
    Serial.println("T1:"+String(temp_c));
  }

  // Attente d'une seconde pour la prochaine exécution
  delay(1000);
}

// Initialisation communication Série
void InitCommunicationSerie()
{
  Serial.begin(9600);
  while(!Serial){}
  Serial.println("Connexion Série : Ok");
}

// Initialisation communication bluetooth
void InitCommunicationBluetooth()
{
  BTSerie.begin(9600); //38400 //57600 //38400
  while(!BTSerie){}
  BTSerie.println("Connexion Bluetooth : Ok");
}
