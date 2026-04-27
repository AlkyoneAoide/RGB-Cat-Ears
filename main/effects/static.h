#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

class StaticEffect: public LEDEffect {
    public:
        StaticEffect() : LEDEffect({
            {"together", staticEffectTogether},
            {"alternating", staticEffectAlternating}
        }, "together") {}
    private:
        static void staticEffectTogether(LEDInfo info) {
            // extract required information from `info`
            uint8_t speed;
            bool randomOrder;
            uint8_t numColors;
            uint32_t* colorsLeft;
            uint32_t* colorsRight;
            bool perEarColors;
            string style;

            // divide provided colors among length

            if (randomOrder) {
                // randomize colors list
            }

            // set strip0
            if (perEarColors) {
                //set strip1
            }
        }

        static void staticEffectAlternating(LEDInfo info) {
            // extract info

            // switch between provided colors

            // color = next in list
            if (randomOrder) {
                // color = random
            }

            // set strip0
            if (perEarColors) {
                // do the same as above
            }
        }
}