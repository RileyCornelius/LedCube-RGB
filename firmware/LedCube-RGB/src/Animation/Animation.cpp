#include "Animation.h"

Animation::Animation()
{
    setDelay(50);
}

void Animation::begin()
{
}

void Animation::end()
{
}

void Animation::setFps(uint16_t fps)
{
    setDelay(1000 / fps);
}

void Animation::setDelay(uint32_t delay)
{
    _timer.setPeriod(delay);
}

void Animation::animate()
{
    if (_timer.ready())
    {
        if (drawFrame())
            reset();
    }
}
