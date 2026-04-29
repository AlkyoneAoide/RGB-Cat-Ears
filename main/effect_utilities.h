#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

static const unordered_map<string, LEDEffect> effectList = {
	//TODO: make these classes
	{"audio", AudioEffect},
	{"breathing", BreathingEffect},
	{"gradient", GradientEffect},
	{"gyro", GyroEffect},
	{"rainbow", RainbowEffect},
	{"stars", StarsEffect},
	{"static", StaticEffect},
}

// given deserialised JSON, leds, gyro (nullable), and last move time,
// select correct function and pass required info
// TODO: update to use class methods now
static void run(LEDDefinition effectInfo, Adafruit_NeoPixel ledsLeft,
Adafruit_NeoPixel ledsRight, sensors_event_t gyro, uint32_t lastMoveTime) {
	LEDEffect primaryEffect = effectList[effectInfo.effect];

	// only care abt idling if primary effect is "gyro"
	if (gyro != NULL && primaryEffect == effectList["gyro"]) {
		bool isIdle = (millis() - lastMoveTime) > effectInfo.gyroTimeout; // must not move for idle delay to trigger idle
		if (isIdle) {
			LEDEffect idleEffect = effectList[effectInfo.gyroIdle];
			// TODO: make a copy of effectInfo, assign gyro idle stuff over the defaults they replace
			idleEffect.show({effectInfo, ledsLeft, ledsRight, gyro});
		} else {
			primaryEffect.show({effectInfo, ledsLeft, ledsRight, gyro});
		}
	} else {
		primaryEffect.show({effectInfo, ledsLeft, ledsRight, gyro});
	}
}

// set strip to single color, identified by ColorHSV
static void showColor(uint32_t color, Adafruit_NeoPixel strip) {
	strip.fill(color);
	strip.show();
}

// set every pixel in a strip to a defined color, assumes the list length = strip length
static void showColors(uint32_t* colors, Adafruit_NeoPixel strip) {
	for (uint16_t i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, colors[i]);
	}
	strip.show();
}

// set color of an edge pixel, move other colors through the strip one step
static void pushColor(uint32_t color, bool forward = true, Adafruit_NeoPixel strip) {
	if (forward) {
		for (uint16_t i = 0; i < strip.numPixels() - 1; i++) {
			strip.setPixelColor(i, strip.getPixelColor(i + 1));
		}
		strip.setPixelColor(strip.numPixels() - 1, color);
	} else {
		for (uint16_t i = strip.numPixels() - 1; i > 0; i--) {
			strip.setPixelColor(i, strip.getPixelColor(i - 1));
		}
		strip.setPixelColor(0, color);
	}
	strip.show();
}
