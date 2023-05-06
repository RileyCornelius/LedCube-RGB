#pragma once

#include <Logger.h>
#include "Animation.h"
#include "Cube.h"

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

    void drawFrame() override
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

    void drawFrame() override
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

    void drawFrame() override
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

    void drawFrame() override
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

    void drawFrame() override
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

class Sinelon : public Animation
{
public:
    Sinelon()
    {
        name = __FUNCTION__;
        setDelay(10);
    };

    const CRGBPalette16 palette = PartyColors_p;
    const uint8_t beatsPerMinute = 15;
    uint8_t hue = 0;

    void drawFrame() override
    {
        Cube.fadeAll(20);
        int pos = beatsin16(beatsPerMinute, 0, LED_COUNT - 1);
        Cube.leds[pos] = ColorFromPalette(palette, hue);
        hue++;
    }
};

class Gradient : public Animation
{
public:
    Gradient()
    {
        name = __FUNCTION__;
        setDelay(40);
    };
    uint8_t hue = 0;

    void drawFrame() override
    {
        fill_gradient(Cube.leds, LED_COUNT, CHSV(hue, 200, 255), CHSV(hue + 50, 255, 200));
        hue++;
    }
};

class Rainbow : public Animation
{
public:
    Rainbow()
    {
        name = __FUNCTION__;
        setDelay(40);
    };

    uint8_t hue = 0;

    void drawFrame() override
    {
        fill_rainbow(Cube.leds, LED_COUNT, hue, 7);
        hue++;
    }
};

class Confetti : public Animation
{
public:
    Confetti()
    {
        name = __FUNCTION__;
        setDelay(10);
    };

    uint8_t hue = 0;

    void drawFrame() override
    {
        Cube.fadeAll(20);
        EVERY_N_MILLIS(200)
        {
            int pos = random16(LED_COUNT);
            Cube.leds[pos] += CHSV(hue + random8(64), 200, 255);
            hue++;
        }
    }
};

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
            Cube.setVoxel(i, ColorFromPalette(palette, hue + (i * 2), beat + (i * 10)));
            hue += 2;
        }
    }
};

class Plasma : public Animation
{
public:
    Plasma()
    {
        name = __FUNCTION__;
        setDelay(10);
    };

    uint16_t xRandom = random16();
    uint16_t yRandom = random16();
    uint16_t zRandom = random16();

    uint16_t noise[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
    uint8_t ihue = 0;

    uint16_t speed = 20;
    uint16_t scale = 311;

    void fillNoise8()
    {
        for (int x = 0; x < CUBE_SIZE; x++)
        {
            int xOffset = scale * x;
            for (int y = 0; y < CUBE_SIZE; y++)
            {
                int yOffset = scale * y;
                for (int z = 0; z < CUBE_SIZE; z++)
                {
                    int zOffset = scale * z;
                    noise[x][y][z] = inoise8(xRandom + xOffset, yRandom + yOffset, zRandom + zOffset);
                }
            }
        }

        zRandom += speed;
    }

    void drawFrame() override
    {
        fillNoise8();
        for (int x = 0; x < CUBE_SIZE; x++)
        {
            for (int y = 0; y < CUBE_SIZE; y++)
            {
                for (int z = 0; z < CUBE_SIZE; z++)
                {
                    Cube.setVoxel(x, y, z, CHSV(noise[x][y][z], 255, noise[x][y][z]));
                    // Cube.setVoxel(x, y, z, CHSV(ihue + noise[x][y][z] >> 2, 255, noise[x][y][z]));
                }
            }
        }
        ihue += 1;
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

    void drawFrame() override
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
