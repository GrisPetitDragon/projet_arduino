#include <SoftwareSerial.h>

#define RxD 10 // pin 10 pour arduino RX-->vers TxD de la carte Bluetooth
#define TxD 11 // pin 11 pour arduino TX-->vers RxD de la carte Bluetooth
#define Key 9  // pin 9 pour Le renommage de la carte bluetooth
#define led 2  // pin 2 pour commander la led

// Simulation d'une liaison série pour le bluetooth
SoftwareSerial BTSerie(RxD,TxD);

// Définition des variables type String
String cmd = String("");
String ans = String("");
String msg[] = {"AT+LED+ON","AT+LED+OFF","AT","AT+VERSION?","AT+NAME?","AT+NAME="};

void setup()
{
  // Initialisation de la communication serie avec l'ordinateur
  InitCommunicationSerie();
  Serial.println("Initialisation carte: Ok");
  
  // Configuration du bluetooth
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(Key, OUTPUT);
  
  // Configuration de la led
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);

  // Initialisation de la communication bluetooth
  InitCommunicationBluetoothSerie();
  
  // Renommmage du périphérique bluetooth 
  digitalWrite(Key,HIGH); 
  BTSerie.print("AT+NAME=BTSaliouGuigui\r\n");
  digitalWrite(Key,LOW);

  // Début de la transmission sur la liaison Serie
  Serial.begin(9600);
}

void loop()
{
  // Si communication bluetooth disponible
  if(BTSerie.available())
  {
    Serial.print("REQUEST: ");
    BTSerie.print("REQUEST: ");
    cmd=BTSerie.readString();
    Serial.print(cmd);
    BTSerie.print(cmd);
    
    if(cmd.indexOf(msg[2]) != -1) // Si message contient AT
    {
      if(cmd.indexOf(msg[0]) != -1) // Si message contient AT+LED+ON
      {
        digitalWrite(led,HIGH);
        Serial.println("ANSWER: LED ON");
        BTSerie.println("ANSWER: LED ON");
      }
      else if(cmd.indexOf(msg[1]) != -1) // Si message contient AT+LED+OFF
      {
        digitalWrite(led,LOW);
        Serial.println("ANSWER: LED OFF");
        BTSerie.println("ANSWER: LED OFF");
      }
      else if((cmd.indexOf(msg[2]) != -1) || // Si message contient juste AT
              (cmd.indexOf(msg[3]) != -1) || // Si message contient AT+VERSION?
              (cmd.indexOf(msg[4]) != -1) || // Si message contient AT+NAME?
              (cmd.indexOf(msg[5]) != -1))   // Si message contient AT+NAME=
      {
        Serial.print("ANSWER: ");
        BTSerie.print("ANSWER: ");
        digitalWrite(Key,HIGH);    // passage en mode AT
        delay(250);
        BTSerie.print(cmd);        // envoie de la commande
        ans=BTSerie.readString();  // réception de la réponse
        delay(250);
        digitalWrite(Key,LOW);     // quitter le mode AT
        Serial.print(ans+"\n");
        BTSerie.print(ans+"\n");
      }
    }
  }

  // Si communication série disponible
  if(Serial.available())
  {
    Serial.print("Envoi vers Bluetooth : ");
    BTSerie.print("Envoi vers Bluetooth : ");
    cmd=Serial.readString();
    Serial.println(cmd);
    BTSerie.println(cmd);
  }
  
  // Récupération et affichage de la température
  int temp = analogRead(A0);
  float temp_c = temp*(5.0/1023.0*100.0);
  Serial.println("TEMP: "+String(temp_c));
  BTSerie.println("TEMP: "+String(temp_c));

  // Attente d'une seconde pour la prochaine exécution
  delay(1000);
}

// Initialisation communication serie
void InitCommunicationSerie()
{
  Serial.begin(9600);
  while(!Serial){}
  Serial.println("Demarrage connexion serie : Ok");
  BTSerie.println("Demarrage connexion serie : Ok");
}

// Initialisation communication bluetooth
void InitCommunicationBluetoothSerie()
{
  BTSerie.begin(9600); //38400 /57600 / 38400
  while (!BTSerie)
  {
    Serial.println("Attente reponse Bluetooth");
  }
  Serial.println("Demarrage connexion bluetooth : Ok");
  BTSerie.println("Demarrage connexion bluetooth : Ok");
}
