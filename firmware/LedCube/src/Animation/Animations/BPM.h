#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class BPM : public Animation
{
public:
    BPM()
    {
        name = __FUNCTION__;
        setDelay(15);
    };

    const uint8_t BeatsPerMinute = 62;
    const CRGBPalette16 palette = PartyColors_p;

    void drawFrame() override
    {
        uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
        uint8_t hue = 0;
        for (int i = 0; i < LED_COUNT; i++)
        {
            Cube.setLed(i, ColorFromPalette(palette, hue + (i * 2), beat + (i * 10)));
            hue += 2;
        }
    }
};
