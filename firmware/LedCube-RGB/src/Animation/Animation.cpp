#include "Animation.h"

Animation::Animation()
{
    setDelay(50);
}

void Animation::setFps(uint16_t fps)
{
    setDelay(1000 / fps);
}

void Animation::setDelay(uint32_t delay)
{
    _timer.setPeriod(delay);
}

bool Animation::animate()
{
    bool updated = false;
    if (_timer.ready())
    {
        if (drawFrame())
            reset();

        updated = true;
    }

    return updated;
}
