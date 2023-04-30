#include "Animator.h"
#include "AnimatorState.h"
#include "Cube/Cube.h"
#include "Config.h"

static const char *TAG = "[Animator]";

Animator::Animator(Animation *animations[], uint16_t length)
{
    AnimatorState::set(Beginning);
    this->animations = animations;
    animationCount = length;
    isRotating = false;
    rotationTimer.setPeriod(15000);
}

void Animator::pause()
{
    if (AnimatorState::is(Idle))
        AnimatorState::set(Running);
    else
        AnimatorState::set(Idle);
}

void Animator::stop()
{
    AnimatorState::set(Idle);
    animations[currentIndex]->stop();
}

void Animator::first()
{
    AnimatorState::set(Ending);
    nextIndex = 0;
}

void Animator::next()
{
    AnimatorState::set(Ending);
    if (nextIndex < animationCount - 1)
        nextIndex++;
    else
        nextIndex = 0;
}

void Animator::previous()
{
    AnimatorState::set(Ending);
    if (nextIndex > 0)
        nextIndex--;
    else
        nextIndex = animationCount;
}

void Animator::setRotation(uint32_t time)
{
    rotationTimer.setPeriod(time);
}

void Animator::rotating()
{
    isRotating = !isRotating;
}

void Animator::readDisplay()
{
#if DISPLAY_ENABLE
    while (SerialDisplay.available())
    {
        String data = SerialDisplay.readStringUntil('\n');
        data.trim();

        if (data == "next")
            next();
        else if (data == "prev")
            previous();
        else if (data == "stop")
            stop();
        else if (data == "play" || data == "pause")
            pause();
    }
#endif
}

void Animator::run()
{
    readDisplay();

    if (isRotating && rotationTimer.ready())
        next();

    switch (AnimatorState::get())
    {
    case Idle:
        break;

    case Ending:
        if (animations[currentIndex]->ending())
        {
            AnimatorState::set(Beginning);
            currentIndex = nextIndex;
        }
        break;

    case Beginning:
        DISPLAY_PRINTLN(animations[currentIndex]->name);
        if (animations[currentIndex]->beginning())
        {
            AnimatorState::set(Running);
            LOG_INFO(TAG, "Animation: %s", animations[currentIndex]->name);
        }
        break;

    case Running:
        animations[currentIndex]->animate();
        break;
    }
}
