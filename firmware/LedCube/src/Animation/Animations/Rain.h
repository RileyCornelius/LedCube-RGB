#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Rain : public Animation
{
public:
    Rain()
    {
        name = __FUNCTION__;
        setDelay(30);
    };

    const uint8_t rainAmount = 150;
    const uint8_t fadeTailScale = 170;
    const uint8_t fadeBottomScale = 30;

    const CRGBPalette16 rainColor_p =
        {
            CRGB(0, 0, 255),
            CRGB(0, 80, 245),
            CRGB(0, 0, 235),
            CRGB(20, 0, 225),
            CRGB(0, 0, 215),
            CRGB(0, 120, 190),
            CRGB(20, 20, 245),
            CRGB(0, 10, 235),
            CRGB(20, 30, 225),
            CRGB(30, 90, 180),
            CRGB(10, 20, 245),
            CRGB(30, 40, 235),
            CRGB(20, 80, 225),
            CRGB(10, 70, 180),
            CRGB(10, 60, 205),
            CRGB(20, 50, 160),
        };

    void drawFrame() override
    {
        // Move raindrops down
        EVERY_N_MILLISECONDS(60)
        {
            for (int x = 0; x < CUBE_SIZE; x++)
                for (int y = 0; y < CUBE_SIZE; y++)
                    for (int z = 0; z < CUBE_SIZE; z++)
                    {
                        CRGB rainColor = Cube.getLed(x, y, z);
                        if (rainColor != CRGB(0, 0, 0))
                        {
                            if (z >= 1) // move rain down
                            {
                                if (rainColor.getAverageLight() > 80)
                                    Cube.setLed(x, y, z - 1, rainColor);
                                Cube.fadeLed(x, y, z, fadeTailScale);
                            }
                            else // fade rain on the ground
                            {
                                Cube.fadeLed(x, y, z, fadeBottomScale);
                            }
                        }
                    }
        }

        // Create new raindrops
        if (random8() < rainAmount)
        {
            static Point prevPoint;
            Point point;
            do // Ensure the same point doesnt get set twice in a row
            {
                point = Point(random8(0, CUBE_SIZE), random8(0, CUBE_SIZE), CUBE_SIZE - 1);
            } while (point == prevPoint);
            prevPoint = point;

            Cube.setLed(point, ColorFromPalette(rainColor_p, random8(0, 255)));
        }
    }
};