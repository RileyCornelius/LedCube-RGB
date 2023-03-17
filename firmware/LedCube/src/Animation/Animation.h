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
    uint16_t getFps();
    void setFps(uint16_t fps);
    void setDelay(uint32_t millis);

public:
    String name;
    Animation();
    void animate();
    void stop();
    virtual void drawFrame() = 0; // pure virtual, needs to be overridden
    virtual bool beginning();     // virtual, optional override
    virtual bool ending();        // virtual, optional override
};