#pragma once

#include <Arduino.h>

/**--------------------------------------------------------------------------------------
 * Millis Timer Class
 *-------------------------------------------------------------------------------------*/

class Timer
{
private:
    uint32_t lastTriggerTime;
    uint32_t period;

public:
    Timer()
    {
        reset();
        period = 1;
    };
    Timer(uint32_t period)
    {
        reset();
        setPeriod(period);
    }

    virtual uint32_t getTime() { return millis(); }
    uint32_t getPeriod() { return period; }
    uint32_t getElapsed() { return getTime() - lastTriggerTime; }
    uint32_t getRemaining() { return period - getElapsed(); }
    void setPeriod(uint32_t period) { this->period = period; }
    void reset() { lastTriggerTime = getTime(); }
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

/**--------------------------------------------------------------------------------------
 * Micros Timer Class
 *-------------------------------------------------------------------------------------*/

class TimerMicros : public Timer
{
    using Timer::Timer; // inherit constructor
public:
    uint32_t getTime() override { return micros(); };
};

/**--------------------------------------------------------------------------------------
 * Benchmark Macros
 *-------------------------------------------------------------------------------------*/

// Toggle debug benchmarking
#ifndef DEBUG_BENCHMARK
#define DEBUG_BENCHMARK 1
#endif

// Benchmarking macros
#if DEBUG_BENCHMARK
// Creates a static benchmark timer
// Use BENCHMARK_END or BENCHMARK_PRINT_END to get elapsed time
#define BENCHMARK_BEGIN()                           \
    static TimerMicros _benchmark_ = TimerMicros(); \
    _benchmark_.reset();
// Creates elapsed time variable
#define BENCHMARK_END() uint32_t _elapsed_ = _benchmark_.getElapsed();
// Prints elapsed time
#define BENCHMARK_PRINT_END() Serial.println(_benchmark_.getElapsed());
#else
#define BENCHMARK_BEGIN()
#define BENCHMARK_END()
#define BENCHMARK_PRINT_END()
#endif