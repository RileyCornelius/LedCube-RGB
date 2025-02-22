#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Rainbow : public Animation
{
public:
    Rainbow()
    {
        name = __FUNCTION__;
        setDelay(40);
    };

    uint8_t hue = 0;
    uint8_t deltaHue = 1;

    void drawFrame() override
    {
        fill_rainbow(Cube.leds, LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 2], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 3], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 4], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 5], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 6], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 7], LED_BRANCH_COUNT, hue, deltaHue);
        fill_rainbow(&Cube.leds[LED_BRANCH_COUNT * 8], LED_BRANCH_COUNT, hue, deltaHue);
        hue++;
    }
};