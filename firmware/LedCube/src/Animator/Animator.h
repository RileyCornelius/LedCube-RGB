#pragma once

#include <SimpleTimer.h>
#include "Animation/Animation.h"

#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0])) // return length of an array

class Animator
{
private:
    Animation **animations;
    Timer rotationTimer;
    uint8_t state;
    uint16_t animationCount, currentIndex, nextIndex;
    bool isRotating;

public:
    Animator(Animation *animations[], uint16_t length);
    void loop();
    void setRotation(uint32_t time);
    void rotating();
    void first();
    void next();
    void previous();
    void pause();
    void stop();
    void getUartData();
};