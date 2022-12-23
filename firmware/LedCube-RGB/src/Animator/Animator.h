#pragma once

#include <SimpleTimer.h>
#include "Animation/Animation.h"

#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0])) // return length of an array

class Animator
{
private:
    Timer rotationTimer;
    Animation **animations;
    uint16_t animationCount;
    uint16_t currentIndex;
    bool isRotating;

public:
    Animator(Animation *animations[], uint16_t length);
    void animate();
    void rotateBegin(uint32_t time);
    void rotateEnd();
    void first();
    void next();
    void previous();
    void pause();
};