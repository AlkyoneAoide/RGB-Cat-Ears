#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

class StarsEffect: public LEDEffect {
    public:
        StarsEffect() : LEDEffect({
            {"default", starsEffect}
        }, "default") {}
    private:
        static void starsEffect(LEDInfo info) {
            //TODO: whole thing lmao
        }
}

// brightness
// speed
// randomOrder
// colors
// perEarColors
// strip0
// strip0_len
// strip1
// strip1_len