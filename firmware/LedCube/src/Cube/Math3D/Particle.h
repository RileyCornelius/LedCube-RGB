#pragma once

#include "Math3D.h"
#include <FastLED.h>

class Particle
{

public:
    Vector3 position = Vector3(0, 0, 0);
    Vector3 velocity = Vector3(0, 0, 0);
    CRGB color = CRGB(0, 0, 0);
    uint8_t hue = 0;
    uint8_t brightness = 255;
    float seconds = 0;
    float elapsed = 0;

    Particle() {}
    // Particle(Vector3 position = Vector3(0, 0, 0), Vector3 velocity = Vector3(0, 0, 0), CRGB color = CRGB(0, 0, 0), uint32_t seconds = 0)
    //     : position(position), velocity(velocity), color(color), seconds(seconds) {}
    Particle(Vector3 position, Vector3 velocity, CRGB color = CRGB(0, 0, 0), uint32_t seconds = 0)
        : position(position), velocity(velocity), color(color), seconds(seconds) {}
    Particle(Vector3 position, Vector3 velocity, uint8_t hue = 0, float seconds = 0)
        : position(position), velocity(velocity), hue(hue), color(color), seconds(seconds) {}

    Particle &move(const float dt);
    Particle &move(const float dt, const Vector3 gravity);
};