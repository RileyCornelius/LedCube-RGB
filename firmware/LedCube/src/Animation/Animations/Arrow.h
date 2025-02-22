#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Arrow : public Animation
{
public:
    Arrow()
    {
        name = __FUNCTION__;
        setDelay(70);

        tempCube.clear();
        int8_t y = 1;
        for (int8_t z = 0; z < 9; z++)
            for (int8_t x = 0; x < 9; x++)
            {
                if (upArrow[z] & 1 << x)
                {
                    Vector3 v = Vector3(CUBE_SIZE_M1 - x, 1, CUBE_SIZE_M1 - z);
                    tempCube.setLed(v, CRGB::Blue);
                }

                if (downArrow[z] & 1 << x)
                {
                    Vector3 v = Vector3(CUBE_SIZE_M1 - x, CUBE_SIZE_M1 - 1, CUBE_SIZE_M1 - z);
                    tempCube.setLed(v, CRGB::Red);
                }
            }
    };

    const uint8_t upArrow[CUBE_SIZE] = {
        0b00000000, // 0
        0b00010000, // 1
        0b00111000, // 2
        0b01111100, // 3
        0b11111110, // 4
        0b00111000, // 5
        0b00111000, // 6
        0b00111000, // 7
        0b00000000, // 8
    };

    const uint8_t downArrow[CUBE_SIZE] = {
        0b00000000, // 8
        0b00111000, // 7
        0b00111000, // 6
        0b00111000, // 5
        0b11111110, // 4
        0b01111100, // 3
        0b00111000, // 2
        0b00010000, // 1
        0b00000000, // 0
    };

    float angleX = 360;
    float angleY = 0;

    LedCube tempCube;
    uint8_t hue = 0;

    void drawFrame() override
    {
        // Rotate and draw
        Cube.clear();
        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                {
                    Vector3 v = Vector3(x, y, z);
                    CRGB color = tempCube.getLed(v);
                    if (color != CRGB(0, 0, 0))
                    {
                        v = v.rotate(angleX, Axis::X);
                        v = v.rotate(angleY, Axis::Y);
                        Cube.setLed(v, color + CHSV(hue, 255, 255));
                    }
                }

        // Increase angle and hue
        hue++;
        angleX -= 15;
        if (angleX <= 0)
        {
            angleX = 360;
            angleY += 15;
            if (angleY >= 360)
                angleY = 0;
        }
    }
};