#pragma once

#include "Math3D.h"

class Particle
{
public:
    Vector3 position = Vector3(0, 0, 0);
    Vector3 velocity = Vector3(0, 0, 0);

    uint8_t hue;
    uint8_t scale;
    float seconds;

public:
    Particle(Vector3 position = Vector3(0, 0, 0), Vector3 velocity = Vector3(0, 0, 0),
             uint8_t hue = 0, uint8_t scale = 1.0f, float sec = 255)
        : position(position), velocity(velocity), hue(hue), scale(scale), seconds(sec) {}

    Particle &move(const float dt);
    Particle &move(const float dt, const Vector3 gravity);
};