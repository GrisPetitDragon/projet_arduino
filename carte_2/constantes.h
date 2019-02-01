#include <SoftwareSerial.h>

const int RX = 11; // Broche RX du module bluetooth
const int TX = 10;    // Broche TX du module bluetooth

/* Constantes pour les broches */
const int TRIGGER_PIN = 12; // Broche TRIGGER du module ultrasons
const int ECHO_PIN = 13;    // Broche ECHO du module ultrasons

const int PIN_VERT = 2;    // Broche VERT
const int PIN_ORANGE = 3;    // Broche ORANGE
const int PIN_ROUGE = 4;    // Broche ROUGE
const int PIN_LOW = 5;    // Broche des cathodes à LOW

/* Seuil pour l'allumage des LED en millimètres */
const int SEUIL_VERT = 3000;
const int SEUIL_ORANGE = 500;
const int SEUIL_ROUGE = 200;

int ETAT; // Pin de la dernière led allumee

int ACTIF; // 0 si le radar est désactivé, 1 sinon


/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;
