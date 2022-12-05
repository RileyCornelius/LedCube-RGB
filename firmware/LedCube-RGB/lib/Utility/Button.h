#pragma once

#include <Arduino.h>

#if defined(ARDUINO_ARCH_AVR)
class Button
{
private:
    bool _prevState;
    bool _state;
    uint32_t _prevTime; // Milliseconds
    uint8_t _pin;

public:
    uint32_t holdTime; // Milliseconds

    Button()
    {
        holdTime = 50;
    }

    Button(uint8_t pin) : Button()
    {
        setPin(pin);
    }

    /**
     * \param pin The pin number of the button
     * \param isActiveHigh The state that triggers the button
     */
    void setPin(uint8_t pin)
    {
        _pin = pin;
        pinMode(_pin, INPUT_PULLUP);
    }

    /**
     * \return True if button is held for 'holdTime' default is 50 milliseconds
     */
    bool debounce()
    {
        uint8_t reading = digitalRead(_pin);

        if (reading != _prevState)
            _prevTime = millis();

        if ((millis() - _prevTime) > holdTime && reading != _state)
        {
            _state = reading;
            if (_state == LOW)
            {
                return true;
            }
        }
        _prevState = reading;

        return false;
    }

    operator bool() { return debounce(); }
};
#elif defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_ESP32)
class Button
{
private:
    bool _prevState;
    bool _state;
    bool _activeState;
    uint32_t _prevTime; // Milliseconds
    uint8_t _pin;

public:
    uint32_t holdTime; // Milliseconds

    Button()
    {
        holdTime = 50;
    }

    Button(uint8_t pin) : Button()
    {
        setPin(pin);
    }

    Button(uint8_t pin, bool isActiveHigh) : Button()
    {
        setPin(pin, isActiveHigh);
    }

    /**
     * \param pin The pin number of the button
     * \param isActiveHigh The state that triggers the button
     */
    void setPin(uint8_t pin, bool isActiveHigh = 0)
    {
        _pin = pin;
        _activeState = isActiveHigh;
        pinMode(_pin, isActiveHigh ? INPUT_PULLDOWN : INPUT_PULLUP); // supports pulldown and pullup resistors
    }

    /**
     * \return True if button is held for 'holdTime' default is 50 milliseconds
     */
    bool debounce()
    {
        uint8_t reading = digitalRead(_pin);

        if (reading != _prevState)
            _prevTime = millis();

        if ((millis() - _prevTime) > holdTime && reading != _state)
        {
            _state = reading;
            if (_state == _activeState)
            {
                return true;
            }
        }
        _prevState = reading;

        return false;
    }

    operator bool() { return debounce(); }
};
#endif