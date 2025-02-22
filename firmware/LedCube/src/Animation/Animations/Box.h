#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Box : public Animation
{
public:
    Box()
    {
        name = __FUNCTION__;
        setDelay(80);
    };

    const uint8_t low = 0;
    const uint8_t high = CUBE_SIZE_M1;
    uint8_t hue = 0;

    void drawFrame() override
    {
        Cube.box(Point(low, low, low), Point(high, high, high), CHSV(hue + 10, 255, 255));
        Cube.box(Point(low + 1, low + 1, low + 1), Point(high - 1, high - 1, high - 1), CHSV(hue + 30, 255, 255));
        Cube.box(Point(low + 2, low + 2, low + 2), Point(high - 2, high - 2, high - 2), CHSV(hue + 50, 255, 255));
        Cube.sphere(CUBE_CENTER, CUBE_CENTER, CUBE_CENTER, 1.0, CHSV(hue + 70, 255, 255));

        hue += 1;
    }
};
