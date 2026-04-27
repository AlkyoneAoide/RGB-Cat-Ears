//sets rgb based on gyro (copy of original implementation)
void gyro(sensors_event_t &gyro) {
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

    // uint32_t color = increaseSaturation(r, g, b, 1.5f);
    // unpack
    // r = (color >> 16) & 0xFF;
    // g = (color >> 8) & 0xFF;
    // b = color & 0xFF;

    // Default to orange when not moving to be more interesting than being white.
    // const float deadband = 10.0;
    // if (fabs(rollRate) < deadband && fabs(pitchRate) < deadband && fabs(yawRate) < deadband) {
    //   r  = 255;
    //   g  = 128;
    //   b  = 0;
    //   r1 = 255;
    //   g1 = 128;
    //   b1 = 0;
    // }

    pushColor(strip0.Color(r, g, b), true, strip0);
    pushColor(strip1.Color(r, g, b), false, strip1);
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