#pragma once

#include <SimpleTimer.h>
#include "Animation/Animation.h"

#define ARRAY_LENGTH(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0])) // return length of an array

class Animator
{
private:
    Timer rotationTimer;
    Animation *transition;
    Animation *current;
    Animation *head;
    uint8_t state;
    uint16_t count;
    bool isRotating;
    void animate();
    void transitionState(Animation *nextAnimation);
    bool transitioning();
    bool fadeIn();
    bool fadeOut();
    void addAnimation(Animation *animation);
    void addAnimationArray(Animation *animation[], uint16_t length);

public:
    Animator(Animation *animations[], uint16_t length);
    void stateMachine();
    void setupFastLED(uint8_t scale = 255);
    void rotateBegin(uint32_t time);
    void rotateEnd();
    void first();
    void next();
    void previous();
    void pause();
};