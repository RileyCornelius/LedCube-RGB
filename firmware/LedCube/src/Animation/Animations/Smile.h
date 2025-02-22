#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"
#include "Cube/Bitmaps/smile.h"

class Smile : public Animation
{
public:
    Smile()
    {
        name = __FUNCTION__;
        setDelay(60);

        uint8_t y = 1;
        tempCube.clear();
        for (int8_t z = 0; z < 9; z++)
            for (int8_t x = 0; x < 9; x++)
            {
                bool set = false;
                uint32_t data = smile_data[z * 9 + x];
                CRGB c;
                if (data >> 24 & 0xFF) // if not transparent
                {
                    set = true;
                }
                tempCube.setLed(CUBE_SIZE_M1 - x, y, CUBE_SIZE_M1 - z, set ? CRGB::White : CRGB::Black);
            }
    };

    float angle = 0;
    LedCube tempCube;
    uint8_t hue = 0;

    void drawFrame() override
    {
        CRGB color = CHSV(hue++, 255, 255);

        // Rotate and draw
        Cube.clear();
        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                {
                    Vector3 v = Vector3(x, y, z);
                    if (tempCube.getLed(v) != CRGB(0, 0, 0))
                    {
                        v = v.rotate(angle, Axis::Z);
                        Cube.setLed(v, color);
                    }
                }

        // Increase angle and go to next letter after full rotation
        angle += 10;
        if (angle >= 360)
        {
            angle = 0;
        }
    }
};