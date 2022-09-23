#pragma once

#include "Animations.h"

// Defines
#define ARRAY_LENGTH(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0])) // return length of an array

/*---------------------------------------------------------------------------------------
 * ANIMATOR CLASS
 *-------------------------------------------------------------------------------------*/
class Animator
{
private:
    bool _isRotating;
    uint16_t _count;
    TimerMillis _timer;
    Animation *_pCurrent;
    Animation *_pHead;
    void addAnimation(Animation *animation);
    void addAnimationArray(Animation *animation[], uint16_t length);

public:
    Animator(Animation *animations[], uint16_t length);
    void rotateBegin(uint32_t time);
    void rotateEnd();
    void choose(String name);
    void first();
    void next();
    void previous();
    void random();
    void update();
};