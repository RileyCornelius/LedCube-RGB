#pragma once

#include "Cube/Cube.h"
#include "SimpleTimer.h"

/*---------------------------------------------------------------------------------------
 * ANIMATION BASE CLASS (Abstract) - Base class for all animations
 *-------------------------------------------------------------------------------------*/
class Animation
{
protected:
    TimerMillis _timer;
    String _name;
    void setFps(uint16_t fps);
    void setDelay(uint32_t millis);

public:
    Animation();
    Animation *pNext;
    String getName() { return _name; };
    void animate();
    virtual void reset() = 0;     // pure virtual, needs to be overridden
    virtual bool drawFrame() = 0; // pure virtual, needs to be overridden
    virtual void begin();
    virtual void end();
};

enum class state_t : uint8_t
{
    INACTIVE = 0,
    STARTING,
    RUNNING,
    ENDING
};