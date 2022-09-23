// #pragma once

#include <Arduino.h>

typedef void (*func_t)(void);

/*------------------------------------------------------------------------------
 * SIMPLE TIMER CLASS (Abstract) - Base class for timers
 *----------------------------------------------------------------------------*/
class SimpleTimer
{
private:
    uint32_t _prevTrigger;
    uint32_t _period;
    func_t _pFuncCallback;

    void callFunction()
    {
        if (_pFuncCallback != NULL)
            _pFuncCallback();
    }

public:
    SimpleTimer()
    {
        _period = 1;
        _pFuncCallback = NULL;
        reset();
    };
    SimpleTimer(uint32_t period) : SimpleTimer()
    {
        setPeriod(period);
    };

    SimpleTimer(uint32_t period, func_t funcCallback) : SimpleTimer(period)
    {
        setCallback(funcCallback);
    };

    virtual uint32_t getTime() { return millis(); }; // default to millis()
    uint32_t getPeriod() { return _period; };
    uint32_t getElapsed() { return getTime() - _prevTrigger; }
    uint32_t getRemaining() { return _period - getElapsed(); }
    void setPeriod(uint32_t period) { _period = period; };
    void setCallback(func_t funcCallback) { _pFuncCallback = funcCallback; }
    void reset() { _prevTrigger = getTime(); };
    bool ready()
    {
        bool isReady = (getElapsed() >= _period);
        if (isReady)
        {
            reset();
            callFunction();
        }
        return isReady;
    }

    operator bool() { return ready(); }
};

/*------------------------------------------------------------------------------
 * TIMER MILLIS CLASS - using millis()
 *----------------------------------------------------------------------------*/
class TimerMillis : public SimpleTimer
{
    using SimpleTimer::SimpleTimer; // inherit constructors

public:
    uint32_t getTime() { return millis(); }; // override time getter
};

/*------------------------------------------------------------------------------
 * TIMER MILLIS CLASS - using micro()
 *----------------------------------------------------------------------------*/
class TimerMicros : public SimpleTimer
{
    using SimpleTimer::SimpleTimer; // inherit constructors

public:
    uint32_t getTime() { return micros(); }; // override time getter
};

#ifdef __HAL_UNLOCK // only available in STM32 HAL framework
/*------------------------------------------------------------------------------
 * TIMER TICK CLASS - using HAL_GetTick()
 *----------------------------------------------------------------------------*/
class TimerTick : public SimpleTimer
{
    using SimpleTimer::SimpleTimer; // inherit constructors

public:
    uint32_t getTime() { return HAL_GetTick(); }; // override time getter
};
#endif

/*------------------------------------------------------------------------------
 * MACROS
 *----------------------------------------------------------------------------*/
#ifndef EVERY_N_MILLIS
// EVERY_N_MILLIS(1000)
// {
// do something every 1000
// }
#define EVERY_N_MILLIS(N) EVERY_N_MILLIS_I(CONCAT(__timer, __COUNTER__), N)
#define EVERY_N_MILLIS_I(NAME, N)             \
    static TimerMillis NAME = TimerMillis(N); \
    if (NAME)

// FUNC_EVERY_N_MILLIS(1000, function);
// call function every 1000
#define FUNC_EVERY_N_MILLIS(N, FUNC) FUNC_EVERY_N_MILLIS_I(CONCAT(__func_timer, __COUNTER__), N, FUNC)
#define FUNC_EVERY_N_MILLIS_I(NAME, N, FUNC)        \
    static TimerMillis NAME = TimerMillis(N, FUNC); \
    NAME.ready()

// EVERY_N_MICROS(1000)
// {
// do something every 1000
// }
#define EVERY_N_MICROS(N) EVERY_N_MICROS_I(CONCAT(__timer, __COUNTER__), N)
#define EVERY_N_MICROS_I(NAME, N)             \
    static TimerMicros NAME = TimerMicros(N); \
    if (NAME)

// FUNC_EVERY_N_MICROS(1000, function);
// call function every 1000
#define FUNC_EVERY_N_MICROS(N, FUNC) FUNC_EVERY_N_MICROS_I(CONCAT(__func_timer, __COUNTER__), N, FUNC)
#define FUNC_EVERY_N_MICROS_I(NAME, N, FUNC)        \
    static TimerMicros NAME = TimerMicros(N, FUNC); \
    NAME.ready()

// Join two symbols together
#define CONCAT(x, y) CONCAT_HELPER(x, y)
#define CONCAT_HELPER(x, y) x##y

#endif
