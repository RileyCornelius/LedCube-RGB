#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

class Sparkles : public Animation
{
public:
    Sparkles()
    {
        name = __FUNCTION__;
        setDelay(40);
    };
    // int index = 0;
    // const int fade_time = 500;
    const int numberOfSparkles = beatsin16(30, 5, 5); // bpm, min, max

    const uint32_t fadeInTime = 1000;
    const uint32_t fadeOutTime = 2000;

    uint8_t sparkleChance = 150;
    uint8_t beatsPerMinute = 5;
    uint8_t hue = 0;
    CRGB color = CRGB::White;
    uint32_t time[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
    CRGB colors[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
    Timer timer;

    void drawFrame() override
    {
        // fade in and out
        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                    if (colors[x][y][z] != CRGB(CRGB::Black))
                    {
                        if (time[x][y][z] < fadeInTime)
                        {
                            time[x][y][z] += timer.getElapsed();
                            float scale = (float)time[x][y][z] / (float)fadeInTime;
                            scale = min(scale, 1.0f);
                            Cube.setLed(x, y, z, colors[x][y][z].scale8(scale * 255));
                        }
                        else if (time[x][y][z] < fadeInTime + fadeOutTime)
                        {
                            time[x][y][z] += timer.getElapsed();
                            float scale = ((float)time[x][y][z] - (float)fadeInTime) / (float)fadeOutTime;
                            scale = min(scale, 1.0f);
                            Cube.setLed(x, y, z, colors[x][y][z].scale8(255 - (scale * 255)));
                        }
                        else
                        {
                            time[x][y][z] = 0;
                            colors[x][y][z] = CRGB(CRGB::Black);
                            Cube.setLed(x, y, z, CRGB::Black);
                            // sparklesCount--;
                        }
                    }

        timer.reset();

        // add sparkle
        if (random8() < sparkleChance)
        {
            Point p;
            uint8_t x;
            uint8_t y;
            uint8_t z;
            do // Ensure the same sparkle isn't overwritten
            {
                x = random8(0, CUBE_SIZE);
                y = random8(0, CUBE_SIZE);
                z = random8(0, CUBE_SIZE);
                p = Point(x, y, z);
            } while (Cube.getLed(p) != CRGB(CRGB::Black));

            colors[x][y][z] = color.setHue(hue++);
        }

        // change amount of sparkles
        EVERY_N_MILLIS(5000)
        {
            beatsPerMinute = random8(3, 20);
        }
        sparkleChance = beatsin8(beatsPerMinute, 50, 255); // bpm, min, max
    }
};