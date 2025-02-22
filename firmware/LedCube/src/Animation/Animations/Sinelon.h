#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Sinelon : public Animation
{
public:
    Sinelon()
    {
        name = __FUNCTION__;
        setDelay(5);
    };

    const CRGBPalette16 palette = PartyColors_p;
    const uint8_t beatsPerMinute = 6;
    uint8_t hue = 0;
    Timer timer = Timer(50);
    Timer timer2 = Timer(10);

    void drawFrame() override
    {
        int pos = beatsin16(beatsPerMinute, 0, LED_COUNT - 1);
        Cube.setLed(pos, ColorFromPalette(palette, hue));

        if (timer2.ready())
            Cube.fadeAll(2);

        if (timer.ready())
            hue++;
    }
};