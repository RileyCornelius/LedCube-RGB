#pragma once

#include "Arduino.h"

class Potentiometer
{
private:
    uint8_t _pin;
    uint16_t sectors;
    uint16_t _lastValue;
    uint16_t threshold;

    uint16_t read()
    {
        uint16_t average = 0;
        uint16_t filter = 10;
        for (size_t i = 0; i < filter; i++)
        {
            average += analogRead(_pin);
        }

        return average / filter;
    }

public:
    Potentiometer(uint8_t pin)
    {
        _pin = pin;
        pinMode(_pin, INPUT);
        sectors = 1;
        threshold = 10;
    }

    Potentiometer(byte potPin, uint16_t sectors)
    {
        _pin = potPin;
        pinMode(_pin, INPUT);
        this->sectors = sectors;
        threshold = 10;
    }

    bool changed()
    {
        bool changed = false;
        uint16_t value = read();
        if (value >= _lastValue + this->threshold || value <= _lastValue - this->threshold)
        {
            _lastValue = value;
            changed = true;
        }

        return changed;
    }

    uint16_t get()
    {
        return read();
    }

    uint8_t get8()
    {
        return map(read(), 0, 1023, 0, 255);
    }

    float getRatio()
    {
        return read() / 1023.0;
    }

    uint16_t getSector()
    {
        return read() / (1024 / sectors);
    }

    void setSectors(uint16_t sectors)
    {
        if (sectors < 1024 && sectors > 0)
            sectors = 1;

        this->sectors = sectors;
    }

    void setThreshold(uint16_t threshold)
    {
        this->threshold = threshold;
    }
};