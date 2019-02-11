#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
// pin 10 pour arduino RX --> TxD de la carte Bluetooth
#define RxD 10
// pin 11 pour arduino TX- -> RxD de la carte Bluetooth
#define TxD 11
// pin 9 pour renommage de la carte Bluetooth
#define Key 9

// simulation liaison Série pour le Bluetooth
SoftwareSerial BTSerie(RxD,TxD);

String ans = String("");
int i = 0;

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temperature :");
  
  // Initialisation de la communication Série
  InitCommunicationSerie();

  // Configuration du Bluetooth
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  // Configuration du renommage
  pinMode(Key, OUTPUT);
  
  // Initialisation de la communication Bluetooth
  InitCommunicationBluetooth();
  
  // Renommmage du périphérique Bluetooth 
  digitalWrite(Key,HIGH);

  /*
  BTSerie.print("AT+ORGL\r\n");
  Serial.println("AT+ORGL");
  ans = BTSerie.readString();
  Serial.println(BTSerie.readString());
  */
  
  BTSerie.print("AT+NAME=BT-Carte3\r\n");
  Serial.println("AT+NAME=BT-Carte3");
  ans = BTSerie.readString();
  Serial.println(BTSerie.readString());

  BTSerie.print("AT+NAME?\r\n");
  Serial.println("AT+NAME?");
  ans = BTSerie.readString();
  Serial.println(ans);

  BTSerie.print("AT+RMAAD\r\n");
  Serial.println("AT+RMAAD");
  ans = BTSerie.readString();
  Serial.println(ans);

  BTSerie.print("AT+PSWD=1234\r\n");
  Serial.println("AT+PSWD=1234");
  ans = BTSerie.readString();
  Serial.println(ans);

  BTSerie.print("AT+ROLE=1\r\n");
  Serial.println("AT+ROLE=1");
  ans = BTSerie.readString();
  Serial.println(ans);
  
  BTSerie.print("AT+CMODE=0\r\n");
  Serial.println("AT+CMODE=0");
  ans = BTSerie.readString();
  Serial.println(ans);
  
  BTSerie.print("AT+INIT\r\n");
  Serial.println("AT+INIT");
  ans = BTSerie.readString();
  Serial.println(ans);

  BTSerie.print("AT+INQ\r\n");
  Serial.println("AT+INQ");
  ans = BTSerie.readString();
  Serial.println(ans);

  BTSerie.print("AT+LINK=98D3,31,F51BC7\r\n");
  Serial.println("AT+LINK=98D3,31,F51BC7");
  ans = BTSerie.readString();
  Serial.println(ans);
  
  digitalWrite(Key,LOW);

  // Début de la transmission sur la liaison Série
  //Serial.begin(38400);
}

void loop()
{
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerie.available()){
    Serial.write(BTSerie.read());
    if(i<5){
      lcd.setCursor(i,1);
      lcd.print(BTSerie.read());
    }
    else if(i>=7){
      lcd.setCursor(0,1);
      lcd.print("        ");
    }
    i++;
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerie.write(Serial.read());

  // Attente d'une seconde pour la prochaine exécution
  delay(250);
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
  BTSerie.begin(38400); //38400 //57600 //38400
  while(!BTSerie){}
}
