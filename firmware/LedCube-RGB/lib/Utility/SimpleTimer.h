#pragma once

#include <Arduino.h>

class Timer
{
private:
    uint32_t prevTrigger;
    uint32_t period;

public:
    Timer(){};
    Timer(uint32_t periodMilliseconds)
    {
        reset();
        setPeriod(periodMilliseconds);
    }

    uint32_t getTime() { return millis(); }
    uint32_t getPeriod() { return period; }
    uint32_t getElapsed() { return getTime() - prevTrigger; }
    uint32_t getRemaining() { return period - getElapsed(); }
    void setPeriod(uint32_t periodMilliseconds) { period = periodMilliseconds; }
    void reset() { prevTrigger = getTime(); }
    bool ready()
    {
        bool isReady = (getElapsed() >= period);
        if (isReady)
        {
            reset();
        }
        return isReady;
    }

    operator bool() { return ready(); }
};
