#include "Animator.h"
#include "Cube/Cube.h"
#include "Config.h"

enum State : uint8_t
{
    Idle,
    Stop,
    Beginning,
    Running,
    Ending,
};

Animator::Animator(Animation *animations[], uint16_t length)
{
    state = Running;
    this->animations = animations;
    animationCount = length;
    isRotating = false;
    rotationTimer.setPeriod(15000);
}

void Animator::pause()
{
    if (state == Idle)
        state = Running;
    else
        state = Idle;
}

void Animator::stop()
{
    if (state == Idle)
        state = Running;
    else
        state = Stop;
}

void Animator::first()
{
    state = Ending;
    nextIndex = 0;
}

void Animator::next()
{
    state = Ending;
    if (nextIndex < animationCount - 1)
        nextIndex++;
    else
        nextIndex = 0;
}

void Animator::previous()
{
    state = Ending;
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

void Animator::getUartData()
{
    while (DisplaySerial.available())
    {
        String data = DisplaySerial.readStringUntil('\n');
        data.trim();

        if (data == "next")
            next();
        else if (data == "prev")
            previous();
        else if (data == "play" || data == "pause")
            pause();
    }
}

void Animator::loop()
{
    getUartData();

    if (isRotating && rotationTimer.ready())
        next();

    switch (state)
    {
    case Stop:
        animations[currentIndex]->stop();
        state = Idle;
        break;

    case Idle:
        DisplaySerial.println("paused");
        break;

    case Ending:
        if (animations[currentIndex]->ending())
        {
            state = Beginning;
            currentIndex = nextIndex;
        }
        break;

    case Beginning:
        if (animations[currentIndex]->beginning())
        {
            state = Running;
            DisplaySerial.println(animations[currentIndex]->name);
        }
        break;

    case Running:
        animations[currentIndex]->animate();
        break;
    }
}
