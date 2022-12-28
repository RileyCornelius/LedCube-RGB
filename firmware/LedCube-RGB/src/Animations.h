#pragma once

#include "Animation/Animation.h"
#include "Cube/Cube.h"
#include <Logger.h>

class Linear : public Animation
{
public:
    Linear()
    {
        name = __FUNCTION__;
        setDelay(75);
    };

    uint8_t hue = 0;
    uint16_t index = 0;

    void reset()
    {
        index = 0;
        Cube.clear();
    }

    void drawFrame()
    {
        if (index >= LED_COUNT)
        {
            index = 0;
            Cube.clear();
        }

        // set led hue and increment
        CRGB color = CHSV(hue++, 255, 255);
        Cube.setVoxel(index++, color);
    }
};

class Sparkles : public Animation
{
public:
    Sparkles()
    {
        name = __FUNCTION__;
        setDelay(30);
    };
    int index = 0;
    const int fade_time = 230;
    const int numberOfSparkles = beatsin16(15, 1, 1); // bpm, min, max
    CRGB color = CRGB::White;

    void drawFrame()
    {
        for (int i = 0; i < numberOfSparkles; i++)
        {
            index = random16(LED_COUNT);
            Cube.setVoxel(index, color);
        }
        Cube.fadeAll(fade_time);
    }
};

class Solid : public Animation
{
public:
    Solid()
    {
        name = __FUNCTION__;
        setDelay(30);
    };

    uint8_t hue = 0;

    void drawFrame()
    {
        CRGB color = CHSV(hue++, 255, 255); // hue will overflow
        Cube.fill(color);
    }
};

class SolidColor : public Animation
{
public:
    SolidColor(CRGB color)
    {
        name = __FUNCTION__;
        this->color = color;
        setDelay(30);
    };
    CRGB color;

    void drawFrame()
    {
        Cube.fill(color);
    }
};

class Wave : public Animation
{
public:
    Wave()
    {
        name = __FUNCTION__;
        setDelay(100);
    };

    int32_t yHueDelta32;
    int32_t xHueDelta32;
    int8_t yHueDelta8;
    int8_t xHueDelta8;

    void drawFrame()
    {
        uint32_t ms = millis();
        yHueDelta32 = ((int32_t)cos16(ms * 27) * (350 / CUBE_SIZE));
        xHueDelta32 = ((int32_t)cos16(ms * 39) * (310 / CUBE_SIZE));
        yHueDelta8 = yHueDelta32 / 32768;
        xHueDelta8 = xHueDelta32 / 32768;

        byte lineStartHue = ms / 65536;
        for (byte z = 0; z < CUBE_SIZE; z++)
        {
            for (byte y = 0; y < CUBE_SIZE; y++)
            {
                lineStartHue += yHueDelta8;
                byte pixelHue = lineStartHue;
                for (byte x = 0; x < CUBE_SIZE; x++)
                {
                    pixelHue += xHueDelta8;
                    Cube.setVoxel(x, y, z, CHSV(pixelHue, 255, 255));
                }
            }
        }
    }
};

class Fire : public Animation
{
public:
    Fire()
    {
        name = __FUNCTION__;
        setDelay(100);
    };

    CRGBPalette16 palette;
    bool gReverseDirection = false;
    uint8_t heat[LED_COUNT]; // Array of temperature readings at each simulation cell

    // Less cooling = taller flames.  More cooling = shorter flames.
    // Default 55, suggested range 20-100
    const uint8_t cooling = 55;
    // Higher chance = more roaring fire.  Lower chance = more flickery fire.
    // Default 120, suggested range 50-200.
    const uint8_t sparking = 120;

    void drawFrame()
    {
        // Step 1.  Cool down every cell a little
        for (int i = 0; i < LED_COUNT; i++)
        {
            heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / LED_COUNT) + 2));
        }
        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for (int k = LED_COUNT - 1; k >= 2; k--)
        {
            heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
        }

        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if (random8() < sparking)
        {
            int y = random8(7);
            heat[y] = qadd8(heat[y], random8(160, 255));
        }

        // Step 4.  Map from heat cells to LED colors
        for (int j = 0; j < LED_COUNT; j++)
        {
            // Scale the heat value from 0-255 down to 0-240
            // for best results with color palettes.
            uint8_t colorindex = scale8(heat[j], 240);
            CRGB color = ColorFromPalette(palette, colorindex);
            int pixelnumber;
            if (gReverseDirection)
            {
                pixelnumber = (LED_COUNT - 1) - j;
            }
            else
            {
                pixelnumber = j;
            }
            Cube.setVoxel(pixelnumber, color);
        }
    }
};
