#include <Arduino.h>
#include "capteurs.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

//=== UUIDs BLE ===
#define SERVICE_UUID        "abcd1234-5678-1234-5678-123456789abb" // Custom service UUID (replace if needed)
#define CHARACTERISTIC_UUID_RX "abcd1234-5678-1234-5678-123456789abc" // Write
#define CHARACTERISTIC_UUID_TX "abcd1234-5678-1234-5678-123456789abd" // Notify
 
Adafruit_INA237 ina237 = Adafruit_INA237();

// === Objets BLE ===
BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic = NULL;
bool deviceConnected = false;

// === Callbacks BLE ===
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Client BLE connecté");
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Client BLE déconnecté");
    BLEDevice::startAdvertising();
  }
};

class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0) {
      String command = String(rxValue.c_str());
      Serial.println("Reçu via BLE : " + command);

      if (command.equalsIgnoreCase("LED")) {
        digitalWrite(LED_GREEN, HIGH);
        delay(500);
        digitalWrite(LED_RED, HIGH);
        delay(500);
        digitalWrite(LED_RED, LOW);
        pTxCharacteristic->setValue("LED TESTED");
        pTxCharacteristic->notify();
      } else if (command.equalsIgnoreCase("BUZZER")) {
        bipSimple() ;
        delay(500);
        bipSimple() ;
        delay(500);
        bipSimple() ;
      } else if (command.equalsIgnoreCase("SPI")) {
        Serial.println("==== Température TMP126 ====");
        float tempTMP126 = readTemperatureTMP126();
        Serial.printf("TMP126 : %.2f °C\n", tempTMP126);
      }
      else if ((command.equalsIgnoreCase("I2C"))||(command.equalsIgnoreCase("INA"))) {
        // Serial.println("INA");
          
        Serial.printf("Current: %.2f mA, Bus Voltage: %.2f V, Shunt Voltage: %.0f uV, Power: %.2f mW, Temp: %.2f C\n",
              ina237.getCurrent_mA(),
              ina237.getBusVoltage_V(),
              ina237.getShuntVoltage_mV() * 1000.0, // Convert mV to μV
              ina237.getPower_mW(),
              ina237.readDieTemp());
        
      }
        else if (command.equalsIgnoreCase("CTN")) {
          Serial.println("==== Température CTN ====");
          float temp1 = readTemperatureCTN(CTN1_PIN);
          float temp2 = readTemperatureCTN(CTN2_PIN);
          Serial.printf("CTN1 : %.2f °C | CTN2 : %.2f °C\n", temp1, temp2);

         }
        
    

      
    }
  }
};

void setup() {
  // === Serial ===
  Serial.begin(115200);
  delay(1000);
  
  //=== CTN ===
  analogReadResolution(12);
  
  // === LED & BUZZER ===
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  digitalWrite(LED_GREEN, LOW);
  // === TMP126 ===
  pinMode(TMP126_CS, OUTPUT);
  digitalWrite(TMP126_CS, HIGH);
  SPI.begin(TMP126_SCK, TMP126_MISO, TMP126_MOSI);

  // === INA237 ===
  Serial.println("=== Initialisation INA237 ===");
  if (!ina237.begin()) {
    Serial.println("INA237 non détecté !");
  } else {
    Serial.println("INA237 détecté !");
    ina237.setShunt(0.0005, 10.0);
    ina237.setAveragingCount(INA2XX_COUNT_16);
    ina237.setVoltageConversionTime(INA2XX_TIME_150_us);
    ina237.setCurrentConversionTime(INA2XX_TIME_280_us);
  }

  //=== Initialisation BLE ===
  BLEDevice::init("ESP32_BLE_");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  // TX : notifications vers client
  pTxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_TX,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  pTxCharacteristic->addDescriptor(new BLE2902());

  // RX : commandes depuis client
  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_RX,
    BLECharacteristic::PROPERTY_WRITE
  );
  pRxCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  BLEDevice::startAdvertising();

  Serial.println("BLE prêt : ESP32_BLE_. En attente de connexion...");
}

void loop() {
  
  delay(2000);
}
