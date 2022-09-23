#include "Animation/Animation.h"

class Linear : public Animation
{
public:
    Linear() : Animation()
    {
        _name = __FUNCTION__;
        setDelay(75);
    };

    uint8_t hue = 0;
    uint16_t index = 0;

    void reset()
    {
        index = 0;
        Cube.clear();
    }

    bool drawFrame()
    {
        // set led hue and increment
        CRGB color = CHSV(hue++, 255, 255);
        Cube.setVoxel(index++, color);

        return (index >= PIXEL_COUNT);
    }
};

class Sparkles : public Animation
{
public:
    Sparkles()
    {
        _name = __FUNCTION__;
        setDelay(150);
    };
    int index = 0;

    const int fade_time = 230;
    const int numberOfSparkles = beatsin16(15, 1, 3); // bpm, min, max
    CRGB color = CRGB::White;

    void reset()
    {
    }

    bool drawFrame()
    {

        for (int i = 0; i < numberOfSparkles; i++)
        {
            index = random16(PIXEL_COUNT);
            Cube.setVoxel(index, color);
        }
        Cube.fadeAll(fade_time);

        return false; // never repeat
    }
};

class Solid : public Animation
{
public:
    Solid() : Animation()
    {
        _name = __FUNCTION__;
        setDelay(70);
    };

    uint8_t hue = 0;

    void reset()
    {
    }

    bool drawFrame()
    {
        CRGB color = CHSV(hue++, 255, 255); // hue will overflow
        Cube.fill(color);

        return false; // never repeat
    }
};

class Wave : public Animation
{
public:
    Wave()
    {
        _name = __FUNCTION__;
        setDelay(100);
    };
    int32_t yHueDelta32;
    int32_t xHueDelta32;
    int8_t yHueDelta8;
    int8_t xHueDelta8;

    void reset()
    {
    }

    bool drawFrame()
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

        return false; // never repeat
    }
};