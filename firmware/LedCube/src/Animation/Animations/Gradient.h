#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Gradient : public Animation
{
public:
    Gradient()
    {
        name = __FUNCTION__;
        setDelay(40);
    };
    uint8_t hue = 0;

    void drawFrame() override
    {
        Cube.leds.fill_gradient(CHSV(hue, 200, 255), CHSV(hue + 50, 255, 200));
        hue++;
    }
};
