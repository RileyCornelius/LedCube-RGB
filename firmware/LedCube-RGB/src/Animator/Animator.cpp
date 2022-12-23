#include "Animator.h"
#include "Cube/Cube.h"
#include "Config.h"

/*--------------------------- PUBLIC FUNCTIONS ---------------------------*/
Animator::Animator(Animation *animations[], uint16_t length)
{
    this->animations = animations;
    animationCount = length;
    isRotating = false;
    isPaused = false;
}

void Animator::pause()
{
    isPaused = !isPaused;
}

void Animator::first()
{
    currentIndex = 0;
}

void Animator::next()
{
    if (currentIndex < animationCount - 1)
        currentIndex++;
    else
        currentIndex = 0;
}

void Animator::previous()
{
    if (currentIndex > 0)
        currentIndex--;
    else
        currentIndex = animationCount;
}

void Animator::rotateBegin(uint32_t time)
{
    isRotating = true;
    rotationTimer.setPeriod(time);
}

void Animator::rotateEnd()
{
    isRotating = false;
}

void Animator::animate()
{
    if (isPaused)
        return;

    if (isRotating && rotationTimer.ready())
        next();

    if (animations[currentIndex]->animate())
    {
        BENCHMARK_BEGIN();
        FastLED.show();
        BENCHMARK_PRINT_END("Animate: ");
    }
}
