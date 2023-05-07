#include "Animator.h"
#include "AnimatorState.h"
#include "Cube.h"
#include "Display.h"

static const char *TAG = "[Animator]";

Animator::Animator(Animation *animations[], uint16_t length)
{
    AnimatorState::set(Ending);
    this->animations = animations;
    animationCount = length - 1;
    isRotating = false;
    rotationTimer.setPeriod(15000);
}

void Animator::togglePlay()
{
    if (AnimatorState::is(Idle))
        play();
    else
        pause();
}

void Animator::pause()
{
    AnimatorState::set(Idle);
    WRITE_DISPLAY_COMMAND(CommandPause);
}

void Animator::play()
{
    AnimatorState::set(Running);
    WRITE_DISPLAY_COMMAND(CommandPlay);
}

void Animator::clear()
{
    AnimatorState::set(Idle);
    animations[currentIndex]->clear();
}

void Animator::first()
{
    AnimatorState::set(Ending);
    nextIndex = 0;
}

void Animator::next()
{
    AnimatorState::set(Ending);
    if (nextIndex < animationCount)
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

void Animator::rotate()
{
    isRotating = !isRotating;
}

void Animator::run()
{
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
            animations[currentIndex]->clear();
            WRITE_DISPLAY_MESSAGE(MessageAnimation, animations[currentIndex]->name);
        }
        break;

    case Beginning:
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
