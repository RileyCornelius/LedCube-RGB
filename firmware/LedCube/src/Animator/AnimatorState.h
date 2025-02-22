#pragma once

#include <Logger.h>

enum State
{
    Idle,
    Beginning,
    Running,
    Ending,

    MAX_VALUE
};

#if LOG_LEVEL_MIN > 0
static const char *stateNames[MAX_VALUE] = {
    "Idle",
    "Beginning",
    "Running",
    "Ending"};
#endif

namespace AnimatorState
{
    State state = Idle;

    State get() { return state; }
    bool is(State isState) { return (state == isState); }
    void set(State newState)
    {
        if (state != newState)
        {
            LOG_DEBUG("[State]", "%s => %s", stateNames[state], stateNames[newState]);
            state = newState;
        }
    }
};