// Import de la librairie SoftwareSerial
#include <SoftwareSerial.h>
// Import de la librairie LiquidCrystal_I2C
#include <LiquidCrystal_I2C.h>

// Pin 10 (arduino RX --> carte Bluetooth TxD)
#define RxD 10
// Pin 11 (arduino TX- -> carte Bluetooth RxD)
#define TxD 11
// Pin 9 (renommage carte Bluetooth)
#define Key 9

// Simulation liaison Bluetooth
SoftwareSerial BTSerie(RxD,TxD);
// Simulation liaison LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Variable pour enregistrer des chaînes de caractères
String ans = String("");
// Variables pour récupérer la température
char bluetooth;
char tmp[5]; 
strcpy(tmp,"");

void setup()
{
  // Initialisation de l'écran LCD
  lcd.init();
  // Initialisation du fond de l'écran LCD
  lcd.backlight();
  // Affichage de "Température °C :"
  lcd.setCursor(0,0);
  lcd.print("Temperature :");

  // Initialisation de la communication Série
  Serial.begin(38400);  

  // Configuration RxD Bluetooth
  pinMode(RxD, INPUT);
  // Configuration TxD Bluetooth
  pinMode(TxD, OUTPUT);
  // Configuration mode AT
  pinMode(Key, OUTPUT);
  
  // Initialisation de la communication Bluetooth
  BTSerie.begin(38400);
  
  // Renommmage du périphérique Bluetooth 
  digitalWrite(Key,HIGH);

  // Configuration par défaut du périphérique Bluetooth
  BTSerie.print("AT+ORGL\r\n");
  // Récupérer le nom du périphérique Bluetooth
  // (vérification de la configuration par défaut)
  BTSerie.print("AT+NAME?\r\n");
  // Configurer le nom du périphérique Bluetooth
  BTSerie.print("AT+NAME=BT-Carte3\r\n");
  // Récupérer le nom du périphérique Bluetooth
  // (vérification du renommage du périphérique)
  BTSerie.print("AT+NAME?\r\n");
  // Supprimer les périphériques appareillés
  BTSerie.print("AT+RMAAD\r\n");
  // Configuration de mot de passe
  BTSerie.print("AT+PSWD=1234\r\n");
  // Configuration du rôle master
  BTSerie.print("AT+ROLE=1\r\n");
  // Configuration du mode d'adressage (fixe)
  BTSerie.print("AT+CMODE=0\r\n");
  // Activation du périphérique Bluetooth
  BTSerie.print("AT+INIT\r\n");
  // Récupération des périphériques actifs
  BTSerie.print("AT+INQ\r\n");
  // Connexion à la carte slave
  BTSerie.print("AT+LINK=98D3,31,F51BC7\r\n");
  
  // Affichage sur la liaison Série
  // de chaque commande AT exécutée sur la liaison Bluetooth
  // Serial.println("Command AT"); 
  // récupération de la valeur de retour sur la liaison Bluetooth
  // ans = BTSerie.readString();
  // affichage de la valeur de retour sur sur la liaison Série
  // Serial.println(ans);

  // Désactiver le mode AT
  digitalWrite(Key,LOW);
}

void loop()
{
  // Si liaison Bluetooth disponible
  if (BTSerie.available()){
    // Tant que des caractères sont reçus sur la liaison Bluetooth
    while(BTSerie.available()){
      // Récupération d'un caractère
      bluetooth=BTSerie.read();
      // Copie du caractère dans le tableau de température
      strcat(tmp,&bluetooth);
    }
    // Affichage de la température sur la liaison Série
    Serial.print(tmp);
    // Affichage de la température sur l'écran LCD
    lcd.setCursor(0,1);
    lcd.print(tmp);
    // Réinitialisation du tableau de température
    strcpy(tmp,"");
  }

  // Attente d'une seconde pour la prochaine exécution
  delay(250);
}
