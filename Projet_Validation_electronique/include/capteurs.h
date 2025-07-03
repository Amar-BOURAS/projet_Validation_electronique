#ifndef CAPTEURS_H
#define CAPTEURS_H

#include <Arduino.h>
#include <Adafruit_INA237.h>
#include <SPI.h>
#include <math.h>

// === Broches ===
#define LED_GREEN 14
#define LED_RED   15
#define BUZZER    13
#define CTN1_PIN  26
#define CTN2_PIN  25

#define TMP126_CS   5
#define TMP126_SCK  18
#define TMP126_MOSI 23
#define TMP126_MISO 19

// === Constantes CTN ===
const float VCC = 3.3;
const float R_FIXED = 10000.0;
const float BETA = 3950.0;
const float T0_KELVIN = 298.15;
const float R0 = 10000.0;

// === Objets globaux ===
extern Adafruit_INA237 ina237;
extern SPISettings tmp126SPISettings;

// === Fonctions ===
float readTemperatureCTN(int pin);
float readTemperatureTMP126();
void bipSimple();
void testINA237(Adafruit_INA237* ina237 );

#endif
