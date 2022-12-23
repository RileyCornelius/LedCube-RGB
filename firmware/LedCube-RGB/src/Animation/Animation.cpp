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
    timer.setPeriod(delay);
}

bool Animation::beginning()
{
}

bool Animation::ending()
{
}

// Returns true if animation updates
bool Animation::animate()
{
    if (timer.ready())
    {
        if (drawFrame())
            reset();

        return true;
    }

    return false;
}
