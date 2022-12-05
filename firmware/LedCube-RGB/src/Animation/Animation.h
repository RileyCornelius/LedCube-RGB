#pragma once

#include <SimpleTimer.h>

/*---------------------------------------------------------------------------------------
 * ANIMATION BASE CLASS (Abstract) - Base class for all animations
 *-------------------------------------------------------------------------------------*/
class Animation
{
protected:
    Timer _timer;
    void setFps(uint16_t fps);
    void setDelay(uint32_t millis);

public:
    String name;
    Animation *pNext;
    Animation();
    bool animate();
    virtual void reset() = 0;     // pure virtual, needs to be overridden
    virtual bool drawFrame() = 0; // pure virtual, needs to be overridden
};