#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Ripple : public Animation
{
public:
    Ripple()
    {
        name = __FUNCTION__;
        setDelay(60);
    };

    const float amplitude = (float)(CUBE_SIZE - 1) / 2.0f;
    const float zOffset = (float)(CUBE_SIZE - 1) / 2.0f;
    const float waveScale = 0.55f;
    const uint8_t maxCounter = 100;

    uint8_t hue = 0;
    uint16_t index = 0;
    CRGB color = CRGB::Blue;

    uint8_t counter = 0;
    // uint8_t x = 0, y = 0, z = 0;

    CRGB gradientCube[LED_COUNT];

    void drawFrame() override
    {
        fill_gradient(gradientCube, LED_COUNT, CHSV(hue, 200, 255), CHSV(hue + 50, 255, 200));
        hue++;

        Cube.fadeAll(170);
        for (uint8_t x = 0; x < CUBE_SIZE / 2 + 1; x++)
        {
            for (uint8_t y = 0; y < CUBE_SIZE / 2 + 1; y++)
            {
                float phaseShift = (float)counter * 2.0 * PI / maxCounter;
                float insideSine = (waveScale * sqrt((x * x) + (y * y))) + phaseShift;
                float sineFunction = (amplitude * sin(insideSine)) + zOffset;
                float z = round(sineFunction);

                uint16_t index = (y * CUBE_SIZE * CUBE_SIZE) + (x * CUBE_SIZE) + z;
                CRGB color = gradientCube[index];
                Cube.setLed(x, y, z, color);
                Cube.setLed(x, CUBE_SIZE - y - 1, z, color);
                Cube.setLed(CUBE_SIZE - x - 1, y, z, color);
                Cube.setLed(CUBE_SIZE - x - 1, CUBE_SIZE - y - 1, z, color);
            }
            counter++;
            if (counter > maxCounter)
            {
                counter = 0;
            }
        }
    }
};