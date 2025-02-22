#pragma once

#include <SimpleTimer.h>

/**--------------------------------------------------------------------------------------
 * Animation class (Abstract) - Base class for all animations
 *
 * Ensure name and setDelay() are called in the constructor
 *-------------------------------------------------------------------------------------*/

class Animation
{
protected:
    Timer updateTimer;
    Timer transitionTimer = Timer(3);
    float deltaTime = 0;

    void setFps(uint16_t fps);
    void setDelay(uint32_t millis);
    float getDeltaTime() { return deltaTime; } // time since last update in seconds
    virtual void drawFrame() = 0;              // pure virtual, needs to be overridden

public:
    String name;

    Animation();
    uint16_t getFps(bool actual = true);
    void animate();
    void clear();
    virtual bool beginning(); // virtual, optional override
    virtual bool ending();    // virtual, optional override
};