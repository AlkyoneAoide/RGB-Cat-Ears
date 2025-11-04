#pragma once

namespace led_effect {
  static const String DEFAULT_STATIC_JSON = R"jsonliteral(
    {
      "effect": "static",
      "colors": [["blue", "off"], ["orange", "off"]],
      "style": "alternating" 
    }
  )jsonliteral";

  static const String DEFAULT_GYRO_JSON = R"jsonliteral(
    {
      "effect": "gyro",
      "gyroFallback": "rainbow",
      "style": "map"
    }
  )jsonliteral";

  class LEDEffect {
    public:
      uint8_t brightness;
      uint8_t speed;
      int16_t direction;
      bool randomOrder;
      uint8_t numColorsLeft;
      String* colorsLeft;
      uint8_t numColorsRight;
      String* colorsRight;
      bool audioHalfEar;
      String* gradientColorWidthLeft;
      String* gradientColorWidthRight;
      String gyroFallback;
      String gyroFallbackStyle;
      uint8_t gyroSensitivity;
      uint16_t gyroTimeout;
      String style;

      LEDEffect(uint8_t brightness = 255, uint8_t speed = 128, int16_t direction = 0,
          bool randomOrder = false, uint8_t numColorsLeft = 1, String* colorsLeft = NULL, uint8_t numColorsRight = 1, String* colorsRight = NULL,
          bool audioHalfEar = false, String* gradientColorWidthLeft = NULL, String* gradientColorWidthRight = NULL,
          String gyroFallback = "rainbow", String gyroFallbackStyle = "static", uint8_t gyroSensitivity = 10,
          uint16_t gyroTimeout = 5000, String style = "static") {
        this->brightness = brightness;
        this->speed = speed;
        this->direction = (-360 <= direction <= 360) ? direction : 0;
        this->randomOrder = randomOrder;
        this->numColorsLeft = numColorsLeft;
        this->colorsLeft = (colorsLeft != NULL) ? colorsLeft : {"blue"}; //TODO: figure out other way to deal w memory
        this->numColorsRight = numColorsRight;
        this->colorsRight = (colorsRight != NULL) ? colorsRight : {"orange"}; //TODO: same
        this->audioHalfEar = audioHalfEar;

        this->gradientColorWidthLeft = gradientColorWidthLeft; //TODO: validate and default
        this->gradientColorWidthRight = gradientColorWidthRight; //TODO: validate
        
        this->gyroFallback = gyroFallback; //TODO: check if effect is valid
        this->gyroFallbackStyle = gyroFallbackStyle; //TODO: check if style is valid
        this->gyroSensitivity = gyroSensitivity;
        this->gyroTimeout = gyroTimeout;
        this->style = style; //TODO: check if in list
      }
  };
}
