/*------------------------------------------------------------------------------
 * DEBOUNCE BUTTON CLASS
 *----------------------------------------------------------------------------*/
class Button
{
private:
    bool _prevState;
    bool _state;
    uint32_t _prevTime;
    uint32_t _holdTime;
    uint8_t _pin;

public:
    Button()
    {
        _state = 0;
        _holdTime = 50;
    }

    Button(uint8_t pin) : Button()
    {
        begin(pin);
    }

    void begin(uint8_t pin)
    {
        _pin = pin;
        pinMode(_pin, INPUT_PULLUP);
    }

    bool debounce()
    {
        auto reading = digitalRead(_pin);
        if (reading != _prevState)
            _prevTime = millis();

        if ((millis() - _prevTime) > _holdTime)
        {
            if (reading != _state)
            {
                _state = reading;
                if (_state == LOW)
                {
                    _state = reading;
                    return true;
                }
            }
        }
        _prevState = reading;

        return false;
    }
};