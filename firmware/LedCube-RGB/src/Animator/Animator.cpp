#include "Animator.h"

/*--------------------------- PUBLIC FUNCTIONS ---------------------------*/
Animator::Animator(Animation *pAnimations[], uint16_t length)
{
    _count = 0;
    _pHead = NULL;
    _isRotating = false;
    addAnimationArray(pAnimations, length);
}

void Animator::update()
{
    if (_isRotating && _timer.ready())
        next();

    _pCurrent->animate();
}

void Animator::first()
{
    _pCurrent = _pHead;
    _pCurrent->reset();
}

void Animator::next()
{
    _pCurrent = _pCurrent->pNext;
    _pCurrent->reset();
}

void Animator::previous()
{
    for (uint16_t i = 0; i < _count - 1; i++)
    {
        _pCurrent = _pCurrent->pNext;
    }

    _pCurrent->reset();
}

void Animator::random()
{
    // for (uint16_t i = 0; i < random8(_count); i++)
    //     _pCurrent = _pCurrent->next;

    // _pCurrent->reset();
}

void Animator::choose(String name)
{
    for (uint16_t i = 0; i < _count; i++)
    {
        _pCurrent = _pCurrent->pNext;
        if (_pCurrent->getName() == name)
            break;
    }

    _pCurrent->reset();
}

void Animator::rotateBegin(uint32_t time)
{
    _isRotating = true;
    _timer.setPeriod(time);
}

void Animator::rotateEnd()
{
    _isRotating = false;
}

/*--------------------------- PRIVATE FUNCTIONS --------------------------*/
void Animator::addAnimationArray(Animation *pAnimations[], uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
        addAnimation(pAnimations[i]);
}

void Animator::addAnimation(Animation *pAnimation)
{
    // Circular linked list
    _count++;                // Increase total animations count
    if (_pHead == NULL)      // will only run once
        _pHead = pAnimation; // set first animation as head
    else
        _pCurrent->pNext = pAnimation; // change current to point at new animation

    pAnimation->pNext = _pHead; // set new animation to point to first animation
    _pCurrent = pAnimation;     // set new animation as current
}