#pragma once

#include <Arduino.h>

/**-----------------------------------------------------------------------------
 * DEBOUNCE BUTTON CLASS
 *----------------------------------------------------------------------------*/
class Button
{
private:
    bool _prevState;
    bool state;
    uint32_t _prevTime;
    uint32_t _holdTime;
    uint8_t pin;

public:
    Button()
    {
        state = 0;
        _holdTime = 50;
    }

    Button(uint8_t pin) : Button()
    {
        begin(pin);
    }

    void begin(uint8_t pin)
    {
        pin = pin;
        pinMode(pin, INPUT_PULLUP);
    }

    bool debounce()
    {
        auto reading = digitalRead(pin);
        if (reading != _prevState)
            _prevTime = millis();

        if ((millis() - _prevTime) > _holdTime)
        {
            if (reading != state)
            {
                state = reading;
                if (state == LOW)
                {
                    state = reading;
                    return true;
                }
            }
        }
        _prevState = reading;

        return false;
    }
};