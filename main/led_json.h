#pragma once

namespace led_json {
	static const String DEFAULT_STATIC_JSON = R"jsonliteral(
		{
			"effect": "static",
			"perEarColors": true,
			"colors": [[1, hsv(210, 100, 100)], [1, hsv(30, 100, 100)]],
			"style": "together" 
		}
	)jsonliteral";

	static const String DEFAULT_GYRO_JSON = R"jsonliteral(
		{
			"effect": "gyro",
			"style": "map",
			"gyroIdle": "rainbow",
			"gyroIdleStyle": "gyro",
		}
	)jsonliteral";

	class LEDDefinition {
		public:
			String effect;
			uint8_t speed;
			int16_t direction;
			bool randomOrder;
			uint8_t numColorsLeft;
			uint32_t* colorsLeft;
			uint8_t numColorsRight;
			uint32_t* colorsRight;
			bool audioHalfEar;
			String gyroIdle;
			String gyroIdleStyle;
			uint8_t gyroSensitivity;
			uint16_t gyroTimeout;
			String style;

			LEDDefinition(String effect = "static", uint8_t speed = 128, int16_t direction = 0,
					bool randomOrder = false, uint8_t numColorsLeft = 1, uint32_t* colorsLeft = NULL,
					uint8_t numColorsRight = 1, uint32_t* colorsRight = NULL, bool audioHalfEar = false,
					String gyroIdle = "rainbow", String gyroIdleStyle = "static", uint8_t gyroSensitivity = 10,
					uint16_t gyroTimeout = 5000, String style = "static") {
				this->effect = effect; // TODO: validate
				this->speed = speed;
				this->direction = (-360 <= direction <= 360) ? direction : 0;
				this->randomOrder = randomOrder;

				// TODO: convert colors lists to packed hsv lists, remember to gamma32 them
				this->numColorsLeft = numColorsLeft;
				this->colorsLeft = (colorsLeft != NULL) ? colorsLeft : {"blue"};
				this->numColorsRight = numColorsRight;
				this->colorsRight = (colorsRight != NULL) ? colorsRight : {"orange"};
				
				this->audioHalfEar = audioHalfEar;

				this->gyroIdle = gyroIdle; //TODO: check if effect is valid (if not in effects.h's map's list of keys)
				this->gyroIdleStyle = gyroIdleStyle; //TODO: check if style is valid
				this->gyroSensitivity = gyroSensitivity;
				this->gyroTimeout = gyroTimeout;
				this->style = style; //TODO: validate
			}
	};
}
