#pragma once

#include <SimpleTimer.h>
#include "Animation/Animation.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

class Animator
{
private:
    Animation **animations;
    uint16_t animationCount;
    Timer rotationTimer = Timer(30000);
    uint16_t currentIndex = 0, nextIndex = 0;
    bool rotating = false;

public:
    Animator(Animation *animations[], uint16_t length);
    void loop();
    void first();
    void last();
    void next();
    void previous();
    void play();
    void pause();
    void stop();
    void togglePlay();
    void toggleRotation();
    void setRotationTime(uint32_t time);
    void setRotating(bool set);
    bool isRotating();
    String getCurrentAnimationName();
};