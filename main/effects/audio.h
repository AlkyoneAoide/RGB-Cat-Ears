#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

class AudioEffect: public LEDEffect {
	public:
		AudioEffect() : LEDEffect({
			{"volume", audioEffectVolume},
			{"frequency", audioEffectFrequency}
		}, "frequency") {}
	private:
		// TODO
		static void audioEffectVolume(LEDInfo info) {}
		// TODO
		static void audioEffectFrequency(LEDInfo info) {}
}

// brightness
// randomOrder
// colors
// perEarColors
// audioHalfEar
// gradientColorWidth
// style
// strip0
// strip0_len
// strip1
// strip1_len