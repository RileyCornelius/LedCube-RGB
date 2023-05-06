#include "Animator.h"
#include "AnimatorState.h"
#include "Cube/Cube.h"
#include "Display/Display.h"
#include "Config.h"

static const char *TAG = "[Animator]";

Animator::Animator(Animation *animations[], uint16_t length)
{
    AnimatorState::set(Ending);
    this->animations = animations;
    animationCount = length;
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
    // DISPLAY_PRINTLN("pause");
}

void Animator::play()
{
    AnimatorState::set(Running);
    WRITE_DISPLAY_COMMAND(CommandPlay);
    // DISPLAY_PRINTLN("play");
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
            WRITE_DISPLAY_MESSAGE(MessageAnimation, animations[currentIndex]->name);
            // DISPLAY_PRINTLN(animations[currentIndex]->name);
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
