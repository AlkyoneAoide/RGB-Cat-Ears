#pragma once

#include <unordered_map>

struct {
    LEDDefinition effectInfo;
    Adafruit_NeoPixel ledsLeft;
    Adafruit_NeoPixel ledsRight;
    sensors_event_t gyro;
} LEDInfo;

typedef void (*EffectFunction)(LEDInfo info);

static class LEDEffect {
    public:
        LEDEffect(initializer_list<string, EffectFunction> stylesMap, string defaultStyle) {
            this->stylesMap = stylesMap;
            this->defaultStyle = defaultStyle;
        }

        static void show(LEDInfo info) {
            EffectFunction fun = getStyleFunction(info.effectInfo.style);
            fun(info);
        }

        static bool hasStyle(string style) {
            return styles.count(style);
        }
    private:
        unordered_map<string, EffectFunction> styles;
        string defaultStyle;

        static void (*)(LEDDefinition, Adafruit_NeoPixel,
	    Adafruit_NeoPixel, sensors_event_t) getStyleFunction(string style) {
            if (styles.count(style) == 1) {
                return styles[style];
            } else {
                return styles[defaultStyle];
            }
        }
}
