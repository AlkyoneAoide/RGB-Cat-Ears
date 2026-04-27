#include <Adafruit_NeoPixel.h>

// set strip to single color, identified by ColorHSV
void showColor(uint32_t color, Adafruit_NeoPixel strip) {
    strip.fill(strip.gamma32(strip.ColorHSV(h, s, v)));
    strip.show();
}

// set every pixel in a strip to a defined color, assumes the list length = strip length
void showColors(uint32_t colors[], Adafruit_NeoPixel strip) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.gamma32(colors[i]));
    }
    strip.show();
}

// set color of an edge pixel, move other colors through the strip one step
void pushColor(uint32_t color, bool forward = true, Adafruit_NeoPixel strip) {
    if (forward) {
        for (uint16_t i = 0; i < strip.numPixels() - 1; i++) {
            strip.setPixelColor(i, strip.getPixelColor(i + 1));
        }
        strip.setPixelColor(strip.numPixels() - 1, strip.gamma32(color));
    } else {
        for (uint16_t i = strip.numPixels() - 1; i > 0; i--) {
            strip.setPixelColor(i, strip.getPixelColor(i - 1));
        }
        strip.setPixelColor(0, strip.gamma32(color));
    }
    strip.show();
}

/**
 * @brief Increase the saturation of the color passed in by the factor.
 *
 * @param r The amount of red in [0, 255]
 * @param g The amount of green in [0, 255]
 * @param b The amount of blue in [0, 255]
 * @param factor The factor to multiply the saturation by
 * @return The resulting color in a packed HSV.
 */
uint32_t increaseSaturation(uint8_t r, uint8_t g, uint8_t b, float factor) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float maxC = max(rf, max(gf, bf));
    float minC = min(rf, min(gf, bf));
    float delta = maxC - minC;

    float v = maxC;                            // value
    float s = (maxC == 0) ? 0 : delta / maxC;  // saturation

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

    return Adafruit_NeoPixel::ColorHSV(h * 65535, s * 255, v * 255);
}

// should be able to register for effects through effects.h, also keeps a list of known effects with string aliases
effect
gyroFallback
gyroFallbackStyle
gyroTimeout