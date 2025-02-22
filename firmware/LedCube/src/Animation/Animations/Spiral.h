#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Spiral : public Animation
{
public:
    Spiral()
    {
        name = __FUNCTION__;
        setDelay(75);
    };

    enum Side
    {
        FRONT,
        LEFT,
        BACK,
        RIGHT,
        RESETTING,
    };
    Side side = FRONT;

    uint8_t hue = 0;
    CRGB color = CHSV(hue, 255, 255);
    uint8_t x = 0, y = 0, z = 0;

    void drawFrame() override
    {
        switch (side)
        {
        case FRONT:
            Cube.line(Point(x, 0, 0), Point(CUBE_SIZE_M1 - x, CUBE_SIZE_M1, CUBE_SIZE_M1), color);
            Cube.line(Point(CUBE_SIZE_M1 - x, CUBE_SIZE_M1, 0), Point(x, 0, CUBE_SIZE_M1), CRGB::Black);
            x++;

            if (x == CUBE_SIZE_M1)
                side = LEFT;

            break;
        case LEFT:
            Cube.line(Point(CUBE_SIZE_M1, y, 0), Point(0, CUBE_SIZE_M1 - y, CUBE_SIZE_M1), color);
            Cube.line(Point(0, CUBE_SIZE_M1 - y, 0), Point(CUBE_SIZE_M1, y, CUBE_SIZE_M1), CRGB::Black);
            y++;

            if (y == CUBE_SIZE_M1)
                side = BACK;

            break;
        case BACK:
            Cube.line(Point(x, CUBE_SIZE_M1, 0), Point(8 - x, 0, CUBE_SIZE_M1), color);
            Cube.line(Point(CUBE_SIZE_M1 - x, 0, 0), Point(x, CUBE_SIZE_M1, CUBE_SIZE_M1), CRGB::Black);
            x--;

            if (x == 0)
                side = RIGHT;
            break;

        case RIGHT:
            Cube.line(Point(0, y, 0), Point(CUBE_SIZE_M1, CUBE_SIZE_M1 - y, CUBE_SIZE_M1), color);
            Cube.line(Point(CUBE_SIZE_M1, CUBE_SIZE_M1 - y, 0), Point(0, y, CUBE_SIZE_M1), CRGB::Black);
            y--;

            if (y == 0)
                side = FRONT;
            break;
        }
        color = CHSV(hue++, 255, 255);
        // Cube.fadeAll(35);
        Cube.setLed(4, 4, 4, color); // write to center as it keeps getting blanked out
    }
};