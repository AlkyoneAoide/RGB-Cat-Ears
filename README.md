The **RGB Cat Ears** is a 3D-printed, motion-reactive cat ear headband. Each ear has a strip of **WS2812B LEDs**. The LEDs are controlled by a **Seeed Studio XIAO ESP32C3**, which uses an **Adafruit MPU-6050** as a sensor. The headband is powered via a USB-C cable. This repository contains the Arduino code for the ESP32C3.

## Hardware

The full CAD model and design are available on [Onshape](https://cad.onshape.com/documents/aee8694863dfed44766b44b6/w/e9796f69ad3ce933161dcc72/e/a92e5c633d0d9e836d9ece51?renderMode=0&uiState=68f36529a2913f7217212281).

**Main Components**:
- Seed Studio XIAO ESP32-C3
- Adafruit MPU-6050 (I²C accelerometer + gyroscope)  
- WS2812B (22 LEDs per ear)  
- USB-C power input  
- 3D-printed TPU headband and PETG ears

## Development

1. Clone the repository.
2. Open the Arduino IDE.
3. Install the following libraries:
    1. Adafruit MPU6050
    2. Adafruit NeoPixel
    3. ArduinoJson
4. Select the XIAO_ESP32C3 as the board in Arduino IDE.

### Relevant Documentation  
- [ESP32-C3](https://docs.espressif.com/projects/arduino-esp32/en/latest/index.html)  
- [MPU-6050](https://github.com/adafruit/Adafruit_MPU6050)  
- NeoPixel LEDs [guide](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use) and [library](https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.h)  

## Adding LED Effects

1. Create a new header file under `effects`, containing a class for your effect
2. Extend LEDEffect and define possible styles (and their corresponding functions) in its constructor call
3. Add your new class (and its alias) to the map in `effect_utilities.h`
