#pragma once

#include <unordered_map>
#include <Adafruit_NeoPixel.h>

static const unordered_map<string, void (*)(LEDEffect, Adafruit_NeoPixel,
	Adafruit_NeoPixel, sensors_event_t)> gyroEffectStyles = {
	{"static", gyroEffectStatic},
	{"map", gyroEffectMap}
	"strength"
}

static void ledGyro(LEDEffect chosenEffect, Adafruit_NeoPixel ledsLeft,
    Adafruit_NeoPixel ledsRight, sensors_event_t _) {
    // get func from map like in effects.h
}

//sets rgb based on gyro (copy of original implementation)
static void gyroEffectMap(sensors_event_t &gyro) {
	float rollRate = gyro.gyro.x * 57.2958f;
	float pitchRate = gyro.gyro.y * 57.2958f;
	float yawRate = gyro.gyro.z * 57.2958f;

	const float maxRate = 180.0f;
	float rotMag = sqrt(gyro.gyro.x * gyro.gyro.x + gyro.gyro.y * gyro.gyro.y + gyro.gyro.z * gyro.gyro.z) * 57.2958f;
	rotMag = constrain(rotMag, 0, maxRate);
	uint8_t speed = map(rotMag, 0, maxRate, 100, 50);

	const float maxAxisRate = 180.0f;
	auto signedMap = [&](float rate) -> uint8_t {
		rate = constrain(rate, -maxAxisRate, maxAxisRate);
		return (uint8_t)map(rate, -maxAxisRate, maxAxisRate, 0, 255);
	};

	uint8_t r = signedMap(rollRate);
	uint8_t g = signedMap(pitchRate);
	uint8_t b = signedMap(yawRate);

	uint32_t packedColor = Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::Color(r, g, b));
	// uint32_t color = increaseSaturation(r, g, b, 1.5f);

	pushColor(packedColor, true, strip0);
	pushColor(packedColor, false, strip1);
	delay(speed);
}

brightness
speed (sensitivity of effect, as opposed to sensitivity of gyro sensor)
randomOrder
colors
perEarColors
gradientColorWidth
gyroSensitivity
style
gyro
strip0
strip0_len
strip1
strip1_len