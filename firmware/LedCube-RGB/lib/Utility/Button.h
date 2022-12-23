#pragma once

#include <Arduino.h>

#if defined(ARDUINO_ARCH_AVR)
class Button
{
private:
    bool prevState;
    bool state;
    uint32_t prevTime; // Milliseconds
    uint8_t pin;

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
        pin = pin;
        pinMode(pin, INPUT_PULLUP);
    }

    /**
     * \return True if button is held for 'holdTime' default is 50 milliseconds
     */
    bool debounce()
    {
        uint8_t reading = digitalRead(pin);

        if (reading != prevState)
            prevTime = millis();

        if ((millis() - prevTime) > holdTime && reading != state)
        {
            state = reading;
            if (state == LOW)
            {
                return true;
            }
        }
        prevState = reading;

        return false;
    }

    operator bool() { return debounce(); }
};
#else
class Button
{
private:
    bool prevState;
    bool state;
    bool activeState;
    uint32_t prevTime; // Milliseconds
    uint8_t pin;

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
        int psin = pin;

        this->pin = pin;
        activeState = isActiveHigh;
        pinMode(pin, isActiveHigh ? INPUT_PULLDOWN : INPUT_PULLUP); // supports pulldown and pullup resistors
    }

    void func(uint8_t sfds)
    {
        int xsgds = sfds;
    }

    /**
     * \return True if button is held for 'holdTime' default is 50 milliseconds
     */
    bool debounce()
    {
        uint8_t reading = digitalRead(pin);

        if (reading != prevState)
            prevTime = millis();

        if ((millis() - prevTime) > holdTime && reading != state)
        {
            state = reading;
            if (state == activeState)
            {
                return true;
            }
        }
        prevState = reading;

        return false;
    }

    operator bool() { return debounce(); }
};
#endif