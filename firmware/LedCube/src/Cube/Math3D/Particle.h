#pragma once

#include "Math3D.h"

class Particle
{
public:
    Vector3 position = Vector3(0, 0, 0);
    Vector3 velocity = Vector3(0, 0, 0);

    uint8_t hue;
    float brightness;
    float seconds;

public:
    Particle(Vector3 position = Vector3(0, 0, 0), Vector3 velocity = Vector3(0, 0, 0),
             uint8_t hue = 0, float brightness = 1.0f, float seconds = 0)
        : position(position), velocity(velocity), hue(hue), brightness(brightness), seconds(seconds) {}

    Particle &move(const float dt);
    Particle &move(const float dt, const Vector3 gravity);
};