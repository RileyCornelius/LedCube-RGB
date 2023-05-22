#pragma once

#include <SimpleTimer.h>

/**--------------------------------------------------------------------------------------
 * Animation class (Abstract) - Base class for all animations
 *-------------------------------------------------------------------------------------*/

class Animation
{
protected:
    Timer timer;
    Timer transitionTimer = Timer(3);
    void setFps(uint16_t fps);
    void setDelay(uint32_t millis);

public:
    String name;
    Animation();
    uint16_t getFps();
    void animate();
    void clear();
    virtual void drawFrame() = 0; // pure virtual, needs to be overridden
    virtual bool beginning();     // virtual, optional override
    virtual bool ending();        // virtual, optional override
};