#include "capteurs.h"

// === Initialisation objets ===

SPISettings tmp126SPISettings(1000000, MSBFIRST, SPI_MODE0);

float readTemperatureCTN(int pin) {
  int adc = analogRead(pin);
  float voltage = (adc / 4095.0) * VCC;
  float r_ntc = (R_FIXED * voltage) / (VCC - voltage);
  float tempK = 1.0 / (1.0 / T0_KELVIN + (1.0 / BETA) * log(r_ntc / R0));
  return tempK - 273.15;
}

float readTemperatureTMP126() {
  uint16_t tempRaw;
  float temperature;
  uint16_t command = (1 << 8) | 0x00;

  SPI.beginTransaction(tmp126SPISettings);
  digitalWrite(TMP126_CS, LOW);

  SPI.transfer16(command);
  tempRaw = SPI.transfer16(0x0000);

  digitalWrite(TMP126_CS, HIGH);
  SPI.endTransaction();
  delayMicroseconds(1);

  int16_t tempSigned = (int16_t)(tempRaw & 0xFFFC);
  tempSigned >>= 2;
  temperature = tempSigned * 0.03125;

  return temperature;
}

void bipSimple() {
  tone(BUZZER, 1000);
  delay(200);
  noTone(BUZZER);
}

void testINA237(Adafruit_INA237* ina237) {
  Serial.println("==== INA237 ====");
  Serial.print("Courant : ");
  Serial.print(ina237->getCurrent_mA());
  Serial.println(" mA");

  Serial.print("Tension bus : ");
  Serial.print(ina237->getBusVoltage_V());
  Serial.println(" V");

  Serial.print("Tension shunt : ");
  Serial.print(ina237->getShuntVoltage_mV() * 1000.0);
  Serial.println(" uV");

  Serial.print("Puissance : ");
  Serial.print(ina237->getPower_mW());
  Serial.println(" mW");

  Serial.print("Température interne : ");
  Serial.print(ina237->readDieTemp());
  Serial.println(" °C");
  Serial.println();
}
