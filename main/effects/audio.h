#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

static const unordered_map<string, void (*)(LEDEffect, Adafruit_NeoPixel,
	Adafruit_NeoPixel, sensors_event_t)> audioEffectStyles = {
	{"volume", audioEffectVolume},
	{"frequency", audioEffectFrequency}
}

static void ledAudio(LEDEffect chosenEffect, Adafruit_NeoPixel ledsLeft,
    Adafruit_NeoPixel ledsRight, sensors_event_t _) {
    // get func from map like in effects.h
}

brightness
randomOrder
colors
perEarColors
audioHalfEar
gradientColorWidth
style
strip0
strip0_len
strip1
strip1_len