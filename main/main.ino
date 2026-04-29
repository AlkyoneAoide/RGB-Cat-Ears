#include <Adafruit_NeoPixel.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLESecurity.h>
#include <Wire.h>

#include "led_json.h"

#define LED_PIN_0 D0
#define LED_PIN_1 D1
#define LED_COUNT_0 22
#define LED_COUNT_1 22
#define GYRO_SDA 6
#define GYRO_SCL 7

#define BT_SERVICE_UUID "49991c1e-9300-46d0-9981-f43b07781010"
#define BT_CHARACTERISTIC_UUID "a538cf14-2e71-4089-a2c4-ca0506b5f1fb"
#define BT_PASSKEY 123456

Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(LED_COUNT_0, LED_PIN_0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);

Adafruit_MPU6050 gyro = NULL;
sensors_event_t accel = NULL, gyro = NULL, temp = NULL;
bool gyroFound = false;
uint32_t lastMoveTime = 0;

JsonDocument effectJson = NULL;
LEDDefinition effectInfo = NULL;

class BLECallbacks: public BLECharacteristicCallbacks {
	void onWrite(BLECharacteristic* newCharacteristic) {
		String newValue = newCharacteristic->getValue();

		if (newValue.length() > 0) {
			Serial.println("Got new value:");
			Serial.printf("New value:\n%s\n", newValue);
			Serial.println("Done.");
			// deserializeJson(effectJson, newValue);
		}
	}
};

class SecurityCallbacks: public BLESecurityCallbacks {
	void onAuthenticationComplete(esp_ble_auth_cmpl_t param) override {
		if (param.success) {
			Serial.println("Pairing success");
		} else {
			Serial.printf("Pairing failed: %d\n", param.fail_reason);
		}
	}
}

void setup() {
	Serial.begin(115200);

	Wire.begin(GYRO_SDA, GYRO_SCL);
	if (!gyro.begin()) {
		Serial.println("MPU6050 not found!");
		gyroFound = false;
		deserializeJson(effectJson, led_json::DEFAULT_STATIC_JSON);
	} else {
		gyroFound = true;
		deserializeJson(effectJson, led_json::DEFAULT_GYRO_JSON);
	}
	updateEffect(effectJson)

	if (gyroFound) {
		Serial.println("Setting up MPU6050.");
		gyro.setAccelerometerRange(MPU6050_RANGE_8_G);
		gyro.setGyroRange(MPU6050_RANGE_500_DEG);
		gyro.setFilterBandwidth(MPU6050_BAND_21_HZ);

		// Setup motion detection
		gyro.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
		gyro.setMotionDetectionThreshold(10); // threshold in milli gs
		gyro.setMotionDetectionDuration(20); // duration above threshold in ms
		gyro.setMotionInterrupt(true);
	}

	// Setup device as BLE server
	// TODO: see if these need to be attached to the server or smth
	// TODO: is new required here?
	BLEDevice::init("RGB Cat Ears");
	BLEDevice::setSecurityCallbacks(new SecurityCallbacks());

	BLESecurity *btSecurity = new BLESecurity();
	btSecurity->setCapability(ESP_IO_CAP_NONE);
	btSecurity->setPassKey(true, BT_PASSKEY);

	BLEServer* btServer = BLEDevice::createServer();
	BLEService* btService = btServer->createService(BT_SERVICE_UUID);

	BLECharacteristic* btCharacteristic = btService->createCharacteristic(BT_CHARACTERISTIC_UUID,
		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE |
		BLECharacteristic::PROPERTY_READ_AUTHEN | BLECharacteristic::PROPERTY_WRITE_AUTHEN
	);
	btCharacteristic->setAccessPermissions(ESP_GATT_PERM_READ_ENC_MITM | ESP_GATT_PERM_WRITE_ENC_MITM);
	btCharacteristic->setCallbacks(new BLECallbacks());
	btCharacteristic->setValue("JSON stuff goes here...");

	btService->start();

	BLEAdvertising* btAdvertising = btServer->getAdvertising();
	btAdvertising->start();

	strip0.begin();
	strip0.setBrightness(255);
	strip0.show();
	strip1.begin();
	strip1.setBrightness(255);
	strip1.show();
}

// TODO: handle switching to new effect
// **including defaults if not provided**
void updateEffect(String newEffect) {
	effectInfo = LEDDefinition(
		newEffect["effect"],
		newEffect["speed"]
	);
}

void loop() {
	if (gyroFound) {
		gyro.getEvent(&accel, &gyro, &temp);

		if (gyro.getMotionInterruptStatus()) {
			lastMoveTime = millis();
		}
	}

	run(effectInfo, strip0, strip1, gyro, lastMoveTime)
}
