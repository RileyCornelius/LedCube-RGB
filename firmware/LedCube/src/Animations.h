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
        setDelay(15);
    };

    uint8_t hue = 0;
    uint16_t index = 0;
    CRGB color = CRGB::White;

    void drawFrame() override
    {
        if (index >= LED_COUNT)
        {
            index = 0;
            Cube.clear();
        }

        // set led hue and increment
        if (index % CUBE_SIZE < CUBE_SIZE)
            color = CHSV(hue++, 255, 255);

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
    const int fade_time = 500;
    const int numberOfSparkles = beatsin16(30, 5, 5); // bpm, min, max
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

        // fill_rainbow(Cube.leds, LED_COUNT, hue, 1);
        // fill_rainbow(Cube.leds, LED_COUNT, hue, 1);
        // fill_rainbow(Cube.leds, LED_COUNT, hue, 1);

        // fill_noise8(Cube.leds, LED_COUNT, 20, 10, 10, 255, 20, hue, 50);
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
        Cube.fadeAll(1);
        EVERY_N_MILLIS(100)
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

class Spiral : public Animation
{
public:
    Spiral()
    {
        name = __FUNCTION__;
        setDelay(75);
    };

    enum Side
    {
        FRONT,
        LEFT,
        BACK,
        RIGHT,
        RESET,
    };
    Side side = FRONT;

    uint8_t hue = 0;
    CRGB color = CHSV(hue, 255, 255);
    uint8_t x = 0, y = 0, z = 0;

    void drawFrame() override
    {
        switch (side)
        {
        case FRONT:
            Cube.line(Point(x, 0, 0), Point(CUBE_LENGTH - x, CUBE_LENGTH, CUBE_LENGTH), color);
            Cube.line(Point(CUBE_LENGTH - x, CUBE_LENGTH, 0), Point(x, 0, CUBE_LENGTH), CRGB::Black);
            x++;

            if (x == CUBE_LENGTH)
                side = LEFT;

            break;
        case LEFT:
            Cube.line(Point(CUBE_LENGTH, y, 0), Point(0, CUBE_LENGTH - y, CUBE_LENGTH), color);
            Cube.line(Point(0, CUBE_LENGTH - y, 0), Point(CUBE_LENGTH, y, CUBE_LENGTH), CRGB::Black);
            y++;

            if (y == CUBE_LENGTH)
                side = BACK;

            break;
        case BACK:
            Cube.line(Point(x, CUBE_LENGTH, 0), Point(8 - x, 0, CUBE_LENGTH), color);
            Cube.line(Point(CUBE_LENGTH - x, 0, 0), Point(x, CUBE_LENGTH, CUBE_LENGTH), CRGB::Black);
            x--;

            if (x == 0)
                side = RIGHT;
            break;

        case RIGHT:
            Cube.line(Point(0, y, 0), Point(CUBE_LENGTH, CUBE_LENGTH - y, CUBE_LENGTH), color);
            Cube.line(Point(CUBE_LENGTH, CUBE_LENGTH - y, 0), Point(0, y, CUBE_LENGTH), CRGB::Black);
            y--;

            if (y == 0)
                side = FRONT;
            break;
        }
        color = CHSV(hue++, 255, 255);
        // Cube.fadeAll(35);
        Cube.setVoxel(4, 4, 4, color); // write to center as it keeps getting blanked out
    }
};

class Sphere : public Animation
{
public:
    Sphere()
    {
        name = __FUNCTION__;
        setDelay(60);
    };
    bool expanding = true;

    uint8_t index = 0;
    uint8_t hue = 0;
    CRGB color = CHSV(hue, 255, 255);
    uint8_t x = 0, y = 0, z = 0;

    void drawFrame() override
    {
        Cube.clear();
        Cube.sphere(Point(4, 4, 4), index, color);
        index = expanding ? index + 1 : index - 1;

        if (index == 6 || index == 0)
            expanding = !expanding;

        color = CHSV(hue += 2, 255, 255);
    }
};

class Shell : public Animation
{
public:
    Shell()
    {
        name = __FUNCTION__;
        setDelay(75);
    };
    bool expanding = true;

    uint8_t index = 0;
    uint8_t hue = 0;
    CRGB color = CHSV(hue, 255, 255);
    uint8_t x = 0, y = 0, z = 0;

    void drawFrame() override
    {
        Cube.clear();
        Cube.shell(Point(4, 4, 4), index, 0.2, color);
        index = expanding ? index + 1 : index - 1;

        if (index == 6 || index == 0)
            expanding = !expanding;

        color = CHSV(hue += 2, 255, 255);
    }
};

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
    const float waveScale = 0.75f;
    const uint8_t maxCounter = 100;

    uint8_t hue = 0;
    uint16_t index = 0;
    CRGB color = CRGB::Blue;

    uint8_t counter = 0;
    uint8_t x = 0, y = 0, z = 0;

    void drawFrame() override
    {
        Cube.fadeAll(170);
        // Cube.clear();
        color = CHSV(hue++, 255, 255);
        for (uint8_t x = 0; x < CUBE_SIZE / 2 + 1; x++)
        {
            for (uint8_t y = 0; y < CUBE_SIZE / 2 + 1; y++)
            {
                float phaseShift = (float)counter * 2.0 * PI / maxCounter;
                float insideSine = (waveScale * sqrt((x * x) + (y * y))) + phaseShift;
                float sineFunction = (amplitude * sin(insideSine)) + zOffset;
                float z = round(sineFunction);

                Cube.setVoxel(x, y, z, color);
                Cube.setVoxel(x, CUBE_SIZE - y - 1, z, color);
                Cube.setVoxel(CUBE_SIZE - x - 1, y, z, color);
                Cube.setVoxel(CUBE_SIZE - x - 1, CUBE_SIZE - y - 1, z, color);
            }
            counter++;
            if (counter > maxCounter)
            {
                counter = 0;
            }
        }
    }
};

class Rain : public Animation
{
public:
    Rain()
    {
        name = __FUNCTION__;
        setDelay(60);
    };

    const uint8_t scaleAmount = 1;
    uint8_t tempZ[CUBE_SIZE * CUBE_SIZE] = {0};
    uint16_t previousLed = 0;

    Timer timer = Timer(40);
    Timer fadeTimer = Timer(150);

    uint8_t hue = 0;
    uint16_t index = 0;
    CRGB color = CRGB::Blue;

    uint8_t counter = 0;
    uint8_t x = 0, y = 0, z = 0;

    void drawFrame() override
    {
        uint16_t newLed = 0;
        do
        {
            newLed = (rand() % CUBE_SIZE * CUBE_SIZE) + ((CUBE_SIZE - 1) * CUBE_SIZE * CUBE_SIZE);
        } while (newLed == previousLed);

        previousLed = newLed; // Ensure the same LED cannot be set twice in a row

        Cube.setVoxel(newLed, color);

        // if (timer.ready())
        // {

        //     ledCube.copyZLayer(0, tempZ);
        //     ledCube.setZLayer(0, 0);
        //     ledCube.shiftZ(-1);
        //     for (uint8_t i = 0; i < CUBE_SIZE * CUBE_SIZE; i++)
        //         if (ledCube.getLedBrightness(i) != 0)
        //             tempZ[i] = ledCube.getLedBrightness(i);
        //     ledCube.setZLayerWithArray(0, tempZ);
        // }

        // if (fadeTimer.ready())
        // {
        //     ledCube.scaleZLayer(0, -scaleAmount);
        // }
    }
};

class Bounce : public Animation
{
public:
    Bounce()
    {
        name = __FUNCTION__;
        setDelay(75);

        updateBall(ball1, v1init);
        updateBall(ball2, v2init);
        updateBall(ball3, v3init);
    };
    static const uint8_t ballSize = 8;

    CRGB color = CRGB::Blue;

    int8_t v1init[3] = {2, 3, 0};
    int8_t v1[3] = {1, 1, 1};
    Point ball1[ballSize] = {Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0), Point(1, 1, 0),
                             Point(0, 0, 1), Point(1, 0, 1), Point(0, 1, 1), Point(1, 1, 1)};

    int8_t v2init[3] = {5, 6, 0};
    int8_t v2[3] = {-1, 1, 1};
    Point ball2[ballSize] = {Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0), Point(1, 1, 0),
                             Point(0, 0, 1), Point(1, 0, 1), Point(0, 1, 1), Point(1, 1, 1)};

    int8_t v3init[3] = {1, 2, 3};
    int8_t v3[3] = {-1, -1, 1};
    Point ball3[ballSize] = {Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0), Point(1, 1, 0),
                             Point(0, 0, 1), Point(1, 0, 1), Point(0, 1, 1), Point(1, 1, 1)};

    void setBallVoxel(Point *ball, CRGB color)
    {
        for (size_t i = 0; i < ballSize; i++)
        {
            Cube.setVoxel(ball[i], color);
        }
    }

    void updateBall(Point *ball, int8_t *v)
    {
        for (size_t i = 0; i < ballSize; i++)
        {
            ball[i].x += v[0];
            ball[i].y += v[1];
            ball[i].z += v[2];
        }

        for (size_t i = 0; i < ballSize; i++)
        {
            if (ball[i].x == CUBE_LENGTH || ball[i].x == 0)
            {
                v[0] = -v[0];
                break;
            }
        }
        for (size_t i = 0; i < ballSize; i++)
        {
            if (ball[i].y == CUBE_LENGTH || ball[i].y == 0)
            {
                v[1] = -v[1];
                break;
            }
        }
        for (size_t i = 0; i < ballSize; i++)
        {
            if (ball[i].z == CUBE_LENGTH || ball[i].z == 0)
            {
                v[2] = -v[2];
                break;
            }
        }
    }

    // void moveBall(Point &ball, int8_t v[3])
    // {
    //     ball.x += v[0];
    //     ball.y += v[1];
    //     ball.z += v[2];

    //     if (ball.x == CUBE_LENGTH || ball.x == 0)
    //         v[0] = -v[0];

    //     if (ball.y == CUBE_LENGTH || ball.y == 0)
    //         v[1] = -v[1];

    //     if (ball.z == CUBE_LENGTH || ball.z == 0)
    //         v[2] = -v[2];
    // }

    void drawFrame() override
    {
        Cube.fadeAll(150);

        setBallVoxel(ball1, CRGB::Blue);
        updateBall(ball1, v1);

        setBallVoxel(ball2, CRGB::Green);
        updateBall(ball2, v2);

        setBallVoxel(ball3, CRGB::Red);
        updateBall(ball3, v3);
    }
};