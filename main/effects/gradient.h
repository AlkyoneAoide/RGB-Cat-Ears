#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

class GradientEffect: public LEDEffect {
	public:
		GradientEffect() : LEDEffect({
			{"static", gradientEffectStatic},
			{"moving", gradientEffectMoving}
		}, "static") {}
	private:
		// TODO
		static void gradientEffectStatic(LEDInfo info) {}
		// TODO
		static void gradientEffectMoving(LEDInfo info) {}
}

// brightness
// speed
// direction
// randomOrder
// colors
// perEarColors
// gradientColorWidth
// style
// strip0
// strip0_len
// strip1
// strip1_len