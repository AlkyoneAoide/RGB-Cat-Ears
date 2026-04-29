#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

class GyroEffect: public LEDEffect {
	public:
		GyroEffect() : LEDEffect({
			{"static", gyroEffectStatic},
			{"map", gyroEffectMap},
			{"strength", gyroEffectStrength}
		}, "strength") {}
	private:
		// TODO
		static void gyroEffectStatic(LEDInfo info) {}

		static void gyroEffectMap(LEDInfo info) {
			float rollRate = gyro.gyro.x * 57.2958f;
			float pitchRate = gyro.gyro.y * 57.2958f;
			float yawRate = gyro.gyro.z * 57.2958f;

			const float maxRate = 180.0f;
			float rotMag = sqrt(gyro.gyro.x * gyro.gyro.x + gyro.gyro.y * gyro.gyro.y + gyro.gyro.z * gyro.gyro.z) * 57.2958f;
			rotMag = constrain(rotMag, 0, maxRate);
			uint8_t speed = map(rotMag, 0, maxRate, 100, 50);

			const float maxAxisRate = 180.0f;
			auto signedMap = [&](float rate) -> uint8_t {
				rate = constrain(rate, -maxAxisRate, maxAxisRate);
				return (uint8_t)map(rate, -maxAxisRate, maxAxisRate, 0, 255);
			};

			uint8_t r = signedMap(rollRate);
			uint8_t g = signedMap(pitchRate);
			uint8_t b = signedMap(yawRate);

			uint32_t packedColor = Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::Color(r, g, b));
			// uint32_t color = increaseSaturation(r, g, b, 1.5f);

			pushColor(packedColor, true, strip0);
			pushColor(packedColor, false, strip1);
			delay(speed);
		}

		// TODO
		static void gyroEffectStrength(LEDInfo info) {}

		// TODO consider moving to effect_utilities.h
		/**
		 * @brief Increase the saturation of the color passed in by the factor.
		 *
		 * @param r The amount of red in [0, 255]
		 * @param g The amount of green in [0, 255]
		 * @param b The amount of blue in [0, 255]
		 * @param factor The factor to multiply the saturation by
		 * @return The resulting color in a packed HSV.
		 */
		static uint32_t increaseSaturation(uint8_t r, uint8_t g, uint8_t b, float factor) {
			float rf = r / 255.0f;
			float gf = g / 255.0f;
			float bf = b / 255.0f;

			float maxC = max(rf, max(gf, bf));
			float minC = min(rf, min(gf, bf));
			float delta = maxC - minC;

			float v = maxC; // value
			float s = (maxC == 0) ? 0 : delta / maxC; // saturation

			// Compute Hue.
			float h = 0.0f;
			if (delta != 0) {
				if (maxC == rf) h = fmod((gf - bf) / delta, 6.0f);
				else if (maxC == gf) h = ((bf - rf) / delta) + 2.0f;
				else h = ((rf - gf) / delta) + 4.0f;
				h /= 6.0f;
				if (h < 0) h += 1.0f;
			}

			// Adjust saturation.
			s = constrain(s * factor, 0.0f, 1.0f);

			//no gamma32, on purpose
			return Adafruit_NeoPixel::ColorHSV(h * 65535, s * 255, v * 255);
		}
}

// brightness
// speed (sensitivity of effect, as opposed to sensitivity of gyro sensor)
// randomOrder
// colors
// perEarColors
// gradientColorWidth
// gyroSensitivity
// style
// gyro
// strip0
// strip0_len
// strip1
// strip1_len