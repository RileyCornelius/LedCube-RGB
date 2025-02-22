#include "Animator/Animator.h"
#include "AnimatorState.h"
#include "Cube/Cube.h"
#include "Communication/Display.h"

static const char *TAG = "[Animator]";

Animator::Animator(Animation *animations[], uint16_t length)
{
    this->animations = animations;
    animationCount = length - 1;
}

void Animator::init()
{
    AnimatorState::set(Beginning);
    WRITE_DISPLAY_MESSAGE(MessageAnimation, animations[currentIndex]->name);
    WRITE_DISPLAY_MESSAGE(MessageFps, String(animations[currentIndex]->getFps()));
}

void Animator::first()
{
    AnimatorState::set(Ending);
    nextIndex = 0;
}

void Animator::last()
{
    AnimatorState::set(Ending);
    nextIndex = animationCount;
}

void Animator::play()
{
    AnimatorState::set(Running);
    WRITE_DISPLAY_COMMAND(CommandPlay);
}

void Animator::pause()
{
    AnimatorState::set(Idle);
    WRITE_DISPLAY_COMMAND(CommandPause);
}

void Animator::stop()
{
    AnimatorState::set(Idle);
    animations[currentIndex]->clear();
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

void Animator::togglePlay()
{
    if (AnimatorState::is(Idle))
        play();
    else
        pause();
}

void Animator::toggleRotating()
{
    rotating = !rotating;
}

void Animator::setRotationTime(uint32_t time)
{
    rotationTimer.setPeriod(time);
}

void Animator::setRotating(bool set)
{
    rotating = set;
}

bool Animator::isRotating()
{
    return rotating;
}

String Animator::getCurrentAnimationName()
{
    return animations[currentIndex]->name;
}

void Animator::loop()
{
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
            WRITE_DISPLAY_MESSAGE(MessageFps, String(animations[currentIndex]->getFps()));
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
        if (rotating && rotationTimer.ready())
            next();

        animations[currentIndex]->animate();
        break;
    }
}
