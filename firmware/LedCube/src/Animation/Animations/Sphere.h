#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Sphere : public Animation
{
public:
    Sphere()
    {
        name = __FUNCTION__;
        setDelay(60);
    };

    const uint8_t radius = 5;
    const uint8_t beatsPerMinute = 5;
    uint8_t hue = 0;
    uint8_t deltaHue = 1;

    CRGB white = CRGB(255, 255, 255);
    LedCube tempCube = LedCube();

    void fillCubeRainbow()
    {
        // fill_rainbow(Cube.leds, LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 2], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 3], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 4], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 5], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 6], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 7], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 8], LED_BRANCH_COUNT, hue, deltaHue);

        Cube.fadeAll(beatsin8(beatsPerMinute, 0, 130));
        hue++;
    }

    void drawFrame() override
    {
        fillCubeRainbow();
        tempCube.sphere(Point(CUBE_CENTER, CUBE_CENTER, CUBE_CENTER), radius, white);

        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                    if (tempCube.getLed(x, y, z) != white)
                    {
                        Cube.setLed(x, y, z, CRGB::Black);
                    }
    }
};