#pragma once

#include <Arduino.h>

/**--------------------------------------------------------------------------------------
 * Millis Timer Class
 *-------------------------------------------------------------------------------------*/

class Timer
{
protected:
    uint32_t prevTrigger;
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
    uint32_t getElapsed() { return getTime() - prevTrigger; }
    uint32_t getRemaining() { return period - getElapsed(); }
    void setPeriod(uint32_t period) { this->period = period; }
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

/**--------------------------------------------------------------------------------------
 * Micros Timer Class
 *-------------------------------------------------------------------------------------*/

class TimerMicros : public Timer
{
    using Timer::Timer; // inherit constructor
public:
    uint32_t getTime() override { return micros(); };
};

/*------------------------------------------------------------------------------
 * Timer Macros
 *----------------------------------------------------------------------------*/

#ifndef EVERY_N_MILLIS
// EVERY_N_MILLIS(1000)
// {
// do something every 1000 miliseconds
// }
#define EVERY_N_MILLIS(n) I_EVERY_N_MILLIS(CONCAT(_timer_, __COUNTER__), n)
#define I_EVERY_N_MILLIS(name, n) \
    static Timer name = Timer(n); \
    if (name.ready())

// EVERY_N_MICROS(1000)
// {
// do something every 1000 microseconds
// }
#define EVERY_N_MICROS(n) I_EVERY_N_MICROS(CONCAT(_timer_, __COUNTER__), n)
#define I_EVERY_N_MICROS(name, n)             \
    static TimerMicros name = TimerMicros(n); \
    if (name.ready())

// Join two symbols together
#define CONCAT(x, y) I_CONCAT(x, y)
#define I_CONCAT(x, y) x##y
#endif

/**--------------------------------------------------------------------------------------
 * Benchmark Macros
 *-------------------------------------------------------------------------------------*/

// Toggle debug benchmarking
#ifndef DEBUG_BENCHMARK
#define DEBUG_BENCHMARK 0
#endif

// Benchmarking macros
#if DEBUG_BENCHMARK
// Creates a static benchmark timer
// Use BENCHMARK_END or BENCHMARK_PRINT_END to get elapsed time
#define BENCHMARK_BEGIN() static Timer _benchmark_ = Timer();
// Creates elapsed time variable
#define BENCHMARK_END() uint32_t _elapsed_ = _benchmark_.getElapsed();
// Prints elapsed time
#define BENCHMARK_PRINT_END(message)               \
    uint32_t _elapsed_ = _benchmark_.getElapsed(); \
    Serial.println(String(message) + _elapsed_);
#else
#define BENCHMARK_BEGIN()
#define BENCHMARK_END()
#define BENCHMARK_PRINT_END(message)
#endif