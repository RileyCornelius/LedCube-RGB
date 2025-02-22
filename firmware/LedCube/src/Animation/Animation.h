#pragma once

#include <SimpleTimer.h>

/**--------------------------------------------------------------------------------------
 * Animation class (Abstract) - Base class for all animations
 *-------------------------------------------------------------------------------------*/

class Animation
{
protected:
    Timer updateTimer; // * Ensure updateTimer is set in the constructor
    Timer transitionTimer = Timer(3);
    float deltaTime = 0;

    void setFps(uint16_t fps);
    void setDelay(uint32_t millis);
    float getDeltaTime() { return deltaTime; }
    virtual void drawFrame() = 0; // * pure virtual, needs to be overridden

public:
    String name; // * Ensure name is set in the constructor

    Animation();
    uint16_t getFps(bool actual = true);
    void animate();
    void clear();
    virtual bool beginning(); // virtual, optional override
    virtual bool ending();    // virtual, optional override
};