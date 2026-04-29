#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

class BreathingEffect: public LEDEffect {
    public:
        BreathingEffect() : LEDEffect({
            {"default", breathingEffect}
        }, "default") {}
    private:
        // TODO
        static void breathingEffect(LEDInfo info) {}
}

// brightness
// speed
// randomOrder
// colors
// perEarColors
// gradientColorWidth
// strip0
// strip0_len
// strip1
// strip1_len