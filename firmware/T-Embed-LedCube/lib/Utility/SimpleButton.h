#pragma once

#include <Arduino.h>

class Button
{
private:
    bool lastState;
    bool heldState;
    bool activeState;

    uint8_t pin;
    uint32_t lastTime;
    uint32_t debounceDelay = 20; // Milliseconds

public:
    Button()
    {
    }

    Button(uint8_t pinNumber, uint8_t inputMode = INPUT_PULLUP, uint8_t activeState = LOW)
    {
        init(pinNumber, inputMode, activeState);
    }

    /**
     * Default inputMode: INPUT_PULLUP - Default activeState: LOW
     * \param pin The pin number of the button
     * \param inputMode The type of input - INPUT, INPUT_PULLUP, INPUT_PULLDOWN
     * \param buttonActiveState The state that triggers the button
     */
    void init(uint8_t pinNumber, uint8_t inputMode = INPUT_PULLUP, uint8_t buttonActiveState = LOW)
    {
        pinMode(pinNumber, inputMode);
        pin = pinNumber;
        activeState = buttonActiveState;
    }

    /**
     * \return True only once when the button is pressed
     */
    bool pressed()
    {
        bool currentState = digitalRead(pin);
        uint32_t now = millis();

        if (currentState != lastState) // Update lastTime if the state changed
            lastTime = now;

        if (now - lastTime > debounceDelay && currentState != heldState)
        {
            heldState = currentState; // Prevents entering this block again on the same press
            if (currentState == activeState)
            {
                return true;
            }
        }
        lastState = currentState;

        return false;
    }
};