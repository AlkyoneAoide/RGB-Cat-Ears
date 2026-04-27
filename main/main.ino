#include <Adafruit_NeoPixel.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Wire.h>

#include "led_effect.h"

#define LED_PIN_0 D0
#define LED_PIN_1 D1
#define LED_COUNT_0 22
#define LED_COUNT_1 22
#define GYRO_SDA 6
#define GYRO_SCL 7

#define BLE_SERVICE_UUID "49991c1e-9300-46d0-9981-f43b07781010"
#define BLE_CHARACTERISTIC_UUID "a538cf14-2e71-4089-a2c4-ca0506b5f1fb"

Adafruit_NeoPixel strip0(LED_COUNT_0, LED_PIN_0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);

Adafruit_MPU6050 gyro;
bool gyroFound = false;

JsonDocument effectJson;

unsigned long lastMoveTime = 0;
const unsigned long idleDelay = 5000;  // ms before entering idle

class BLECallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* newCharacteristic) {
    String newValue = newCharacteristic->getValue();

    if (newValue.length() > 0) {
      Serial.println("Got new value:");
      for (int i = 0; i < newValue.length(); i++)
        Serial.print(newValue[i]);
      Serial.println();
      Serial.println("Done.");
    }
  }
};

void setup() {
  Serial.begin(115200);

  Wire.begin(GYRO_SDA, GYRO_SCL);
  if (!gyro.begin()) {
    Serial.println("MPU6050 not found!");
    gyroFound = false;
    deserializeJson(effectJson, led_effect::DEFAULT_STATIC_JSON);
  } else {
    gyroFound = true;
    deserializeJson(effectJson, led_effect::DEFAULT_GYRO_JSON);
  }

  if (gyroFound) {
    Serial.println("Setting up MPU6050.");
    gyro.setAccelerometerRange(MPU6050_RANGE_8_G);
    gyro.setGyroRange(MPU6050_RANGE_500_DEG);
    gyro.setFilterBandwidth(MPU6050_BAND_21_HZ);

    // Setup motion detection
    gyro.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
    gyro.setMotionDetectionThreshold(10);  // threshold in milli gs
    gyro.setMotionDetectionDuration(20);   // duration above threshold in ms
    gyro.setMotionInterrupt(true);
  }

  strip0.begin();
  strip0.setBrightness(255);
  strip0.show();
  strip1.begin();
  strip1.setBrightness(255);
  strip1.show();

  // Setup device as BLE server
  BLEDevice::init("RGB Cat Ears");
  BLEServer* btServer = BLEDevice::createServer();
  BLEService* btService = btServer->createService(BLE_SERVICE_UUID);

  BLECharacteristic* btCharacteristic = btService->createCharacteristic(BLE_CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  btCharacteristic->setCallbacks(new BLECallbacks());
  btCharacteristic->setValue("JSON stuff goes here...");
  
  btService->start();

  BLEAdvertising* btAdvertising = btServer->getAdvertising();
  btAdvertising->start();
}

// TODO: handle switching to new effect, including defaults if not provided
void updateEffect(String effectJson) {}

void loop() {
  if (gyroFound) {
    sensors_event_t a, g, t;
    gyro.getEvent(&a, &g, &t);

    if (gyro.getMotionInterruptStatus()) {
      lastMoveTime = millis();
    }

    bool isIdle = (millis() - lastMoveTime) > idleDelay;  // must not move for idle delay to trigger idle
    if (isIdle) rainbowBreathing(g);
    else gyroReactive(g);
  }
}
