#pragma once

#include <Arduino.h>

class Timer
{
private:
    uint32_t _prevTrigger;
    uint32_t _period;

public:
    Timer(){};
    Timer(uint32_t period)
    {
        reset();
        setPeriod(period);
    }

    uint32_t getTime() { return millis(); }
    uint32_t getPeriod() { return _period; }
    uint32_t getElapsed() { return getTime() - _prevTrigger; }
    uint32_t getRemaining() { return _period - getElapsed(); }
    void setPeriod(uint32_t period) { _period = period; }
    void reset() { _prevTrigger = getTime(); }
    bool ready()
    {
        bool isReady = (getElapsed() >= _period);
        if (isReady)
        {
            reset();
        }
        return isReady;
    }

    operator bool() { return ready(); }
};
