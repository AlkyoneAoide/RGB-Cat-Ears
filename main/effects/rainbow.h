#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

class RainbowEffect: public LEDEffect {
	public:
		RainbowEffect() : LEDEffect({
			{"static", rainbowEffectStatic},
			{"moving", rainbowEffectMoving},
			{"wipe", rainbowEffectWipe},
			{"gyro", rainbowEffectGyro}
		}, "static") {}
	private:
		// TODO
		static void rainbowEffectStatic(LEDInfo info) {}

		// TODO: brightness setting maybe?
		static void rainbowEffectMoving(LEDInfo info) {
			float hue = (millis() % 5000) / 5000.0f;
			uint32_t color = Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::ColorHSV(hue * 65535, 255, 255));

			pushColor(color, true, ledsLeft);
			pushColor(color, false, ledsRight);
			delay(100);
		}

		// TODO
		static void rainbowEffectWipe(LEDInfo info) {}

		static void rainbowEffectGyro(LEDInfo info) {
			if (gyro == NULL) {
				rainbowEffectStatic(info);
				return;
			}
			
			const float maxRate = 30.0;
			float rotMag =
			sqrt(
				gyro.gyro.x * gyro.gyro.x + gyro.gyro.y * gyro.gyro.y + gyro.gyro.z * gyro.gyro.z)
			* 57.2958;
			rotMag = constrain(rotMag, 0, maxRate);

			// Brightness depends on rotation rate (for fun).
			float brightness = fmap(rotMag, 0, maxRate, 0.5f, 1.0f);
			// Smooth out brightness to stop spikes.
			float smoothedBrightness = 0.0f;
			float target = brightness;
			float alpha = 0.1f;
			smoothedBrightness = smoothedBrightness * (1 - alpha) + target * alpha;
			brightness = smoothedBrightness;

			float hue = (millis() % 5000) / 5000.0f;
			uint32_t color = Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::ColorHSV(hue * 65535, 255, brightness * 255));

			pushColor(color, true, strip0);
			pushColor(color, false, strip1);
			delay(100);
		}

		//TODO: consider moving this to led_effect.h?
		/**
		 * @brief Map input float from the input range to the output range
		 *
		 * @param x The input to map
		 * @param in_min The minimum of the mapping range, but lesser values are mapped
		 * anyways
		 * @param in_max The maximum of the mapping range, but greater values are 
		 * mapped anyways
		 * @param out_min The minimum of the output range, lesser outputs are possible
		 * when the input is less than in_min
		 * @param out_max The maximum of the output range, greater outputs are possible
		 * when the input is greater than in_max
		 * @return The mapped to value
		 */
		static float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
			return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
		}
}

// brightness
// speed
// direction
// style
// strip0
// strip0_len
// strip1
// strip1_len