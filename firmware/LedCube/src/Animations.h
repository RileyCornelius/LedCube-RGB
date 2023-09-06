#pragma once

#include <Logger.h>
#include "Animation.h"
#include "Cube.h"

// class Fire : public Animation
// {
// public:
//     Fire()
//     {
//         name = __FUNCTION__;
//         setDelay(40);
//     };

//     CRGBPalette16 firePalette = HeatColors_p;
//     ;
//     const uint8_t cooling = 55;
//     const uint8_t sparking = 120;
//     CHSV color = CHSV(0, 255, 255);

//     uint8_t heat[LED_COUNT];

//     uint8_t speed = 20;
//     uint8_t radii[LED_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

//     uint8_t hue = 0;

//     void drawFrame() override
//     {

//         static uint16_t sPseudotime = 0;
//         static uint16_t sLastMillis = 0;
//         static uint16_t sHue16 = 0;

//         // uint8_t sat8 = beatsin88( 87, 220, 250);
//         uint8_t brightdepth = beatsin88(341, 96, 224);
//         uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
//         uint8_t msmultiplier = beatsin88(147, 23, 60);

//         uint16_t hue16 = sHue16; // gHue * 256;
//         uint16_t hueinc16 = beatsin88(113, 300, 1500);

//         uint16_t ms = millis();
//         uint16_t deltams = ms - sLastMillis;
//         sLastMillis = ms;
//         sPseudotime += deltams * msmultiplier;
//         sHue16 += deltams * beatsin88(400, 5, 9);
//         uint16_t brightnesstheta16 = sPseudotime;

//         for (uint16_t i = 0; i < LED_COUNT; i++)
//         {
//             hue16 += hueinc16;
//             uint8_t hue8 = hue16 / 256;
//             uint16_t h16_128 = hue16 >> 7;
//             if (h16_128 & 0x100)
//             {
//                 hue8 = 255 - (h16_128 >> 1);
//             }
//             else
//             {
//                 hue8 = h16_128 >> 1;
//             }

//             brightnesstheta16 += brightnessthetainc16;
//             uint16_t b16 = sin16(brightnesstheta16) + 32768;

//             uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
//             uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
//             bri8 += (255 - brightdepth);

//             uint8_t index = hue8;
//             index = scale8(index, 240);

//             CRGB newcolor = ColorFromPalette(firePalette, index, bri8);

//             uint16_t pixelnumber = i;
//             pixelnumber = (LED_COUNT - 1) - pixelnumber;

//             nblend(Cube.leds[pixelnumber], newcolor, 128);
//         }

//         // void drawFrame() override
//         // {
//         //     for (uint8_t x = 0; x < CUBE_SIZE; x++)
//         //     {
//         //         for (uint8_t y = 0; y < CUBE_SIZE; y++)
//         //         {
//         //             // Step 1.  Cool down every cell a little
//         //             heat[x][y][0] = qsub8(heat[x][y][0], random8(0, ((cooling * 10) / CUBE_SIZE) + 2));

//         //             // Step 2.  Heat from each cell drifts 'up' and diffuses a little
//         //             for (uint8_t z = CUBE_SIZE - 1; z > 0; z--)
//         //             {
//         //                 heat[x][y][z] = (heat[x][y][z - 1] + heat[x][y][z - 2] + heat[x][y][z - 2]) / 3;
//         //             }

//         //             // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
//         //             if (random8() < sparking)
//         //             {
//         //                 uint8_t z = random8(2);
//         //                 heat[x][y][z] = qadd8(heat[x][y][z], random8(160, 255));
//         //             }

//         //             // Step 4.  Map from heat cells to LED colors
//         //             for (uint8_t z = 0; z < CUBE_SIZE; z++)
//         //             {
//         //                 // Scale the heat value from 0-255 down to 0-240
//         //                 // for best results with color palettes.
//         //                 uint8_t colorindex = scale8(heat[x][y][z], 240);
//         //                 CRGB color = ColorFromPalette(firePalette, colorindex);
//         //                 Cube.setLed(x, y, z, color);
//         //             }
//         //         }
//         //     }
//         // }
//     }
// };

// class Plasma : public Animation
// {
// public:
//     Plasma()
//     {
//         name = __FUNCTION__;
//         setDelay(100);
//     };

//     uint16_t xRandom = random16();
//     uint16_t yRandom = random16();
//     uint16_t zRandom = random16();

//     uint16_t noise[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
//     uint8_t ihue = 0;

//     uint16_t speed = 20;
//     uint16_t scale = 311;

//     void fillNoise8()
//     {
//         for (int x = 0; x < CUBE_SIZE; x++)
//         {
//             int xOffset = scale * x;
//             for (int y = 0; y < CUBE_SIZE; y++)
//             {
//                 int yOffset = scale * y;
//                 for (int z = 0; z < CUBE_SIZE; z++)
//                 {
//                     int zOffset = scale * z;
//                     noise[x][y][z] = inoise8(xRandom + xOffset, yRandom + yOffset, zRandom + zOffset);
//                 }
//             }
//         }

//         zRandom += speed;
//     }

//     void drawFrame() override
//     {
//         fillNoise8();
//         for (int x = 0; x < CUBE_SIZE; x++)
//         {
//             for (int y = 0; y < CUBE_SIZE; y++)
//             {
//                 for (int z = 0; z < CUBE_SIZE; z++)
//                 {
//                     // Cube.setLed(x, y, z, CHSV(noise[x][y][z], 255, noise[x][y][z]));
//                     Cube.setLed(x, y, z, CHSV(ihue + noise[x][y][z] >> 2, 255, noise[x][y][z]));
//                 }
//             }
//         }
//         ihue += 1;
//     }
// };

// class Square : public Animation
// {
// public:
//     Square()
//     {
//         name = __FUNCTION__;
//         setDelay(100);
//     };

//     uint8_t hue = 0;
//     uint8_t rotation = 0;

//     enum Side
//     {
//         FRONT,
//         LEFT,
//         BACK,
//         RIGHT,
//         RESETTING,
//     };
//     Side side = FRONT;

//     CRGB color = CHSV(hue, 255, 255);
//     uint8_t x = 0, y = 0, z = 0;

//     uint8_t MIDDLE = CUBE_SIZE / 2;

//     void drawFrame() override
//     {
//         Cube.clear();
//         switch (side)
//         {
//         case FRONT:
//             Cube.line(Point(MIDDLE, MIDDLE, 0), Point(CUBE_SIZE_M1, CUBE_SIZE_M1 - x, MIDDLE), color);
//             // Cube.line(Point(4, 4, 4), Point(CUBE_SIZE_M1 - x, CUBE_SIZE_M1, CUBE_SIZE_M1), color);
//             // Cube.line(Point(CUBE_SIZE_M1 - x, CUBE_SIZE_M1, 0), Point(x, 0, CUBE_SIZE_M1), CRGB::Black);
//             x++;

//             if (x == CUBE_SIZE_M1)
//                 side = LEFT;

//             break;
//         case LEFT:
//             Cube.line(Point(MIDDLE, MIDDLE, 0), Point(CUBE_SIZE_M1 - y, CUBE_SIZE_M1, MIDDLE), color);

//             // Cube.line(Point(CUBE_SIZE_M1, y, 0), Point(0, CUBE_SIZE_M1 - y, CUBE_SIZE_M1), color);
//             // Cube.line(Point(0, CUBE_SIZE_M1 - y, 0), Point(CUBE_SIZE_M1, y, CUBE_SIZE_M1), CRGB::Black);
//             y++;

//             if (y == CUBE_SIZE_M1)
//                 side = BACK;

//             break;
//         case BACK:
//             Cube.line(Point(MIDDLE, MIDDLE, 0), Point(CUBE_SIZE_M1 - x, CUBE_SIZE_M1, MIDDLE), color);

//             // Cube.line(Point(x, CUBE_SIZE_M1, 0), Point(8 - x, 0, CUBE_SIZE_M1), color);
//             // Cube.line(Point(CUBE_SIZE_M1 - x, 0, 0), Point(x, CUBE_SIZE_M1, CUBE_SIZE_M1), CRGB::Black);
//             x--;

//             if (x == 0)
//                 side = RIGHT;
//             break;

//         case RIGHT:
//             Cube.line(Point(MIDDLE, MIDDLE, 0), Point(CUBE_SIZE_M1, CUBE_SIZE_M1 - y, MIDDLE), color);

//             // Cube.line(Point(0, y, 0), Point(CUBE_SIZE_M1, CUBE_SIZE_M1 - y, CUBE_SIZE_M1), color);
//             // Cube.line(Point(CUBE_SIZE_M1, CUBE_SIZE_M1 - y, 0), Point(0, y, CUBE_SIZE_M1), CRGB::Black);
//             y--;

//             if (y == 0)
//                 side = FRONT;
//             break;
//         }
//         color = CHSV(hue++, 255, 255);
//         // Cube.fadeAll(35);
//         Cube.setLed(MIDDLE, MIDDLE, MIDDLE, color); // write to center as it keeps getting blanked out
//     }
// };

class Arrow : public Animation
{
public:
    Arrow()
    {
        name = __FUNCTION__;
        setDelay(70);

        tempCube.clear();
        int8_t y = 1;
        for (int8_t z = 0; z < 9; z++)
            for (int8_t x = 0; x < 9; x++)
            {
                if (upArrow[z] & 1 << x)
                {
                    Vector3 v = Vector3(CUBE_SIZE_M1 - x, 1, CUBE_SIZE_M1 - z);
                    tempCube.setLed(v, CRGB::Blue);
                }

                if (downArrow[z] & 1 << x)
                {
                    Vector3 v = Vector3(CUBE_SIZE_M1 - x, CUBE_SIZE_M1 - 1, CUBE_SIZE_M1 - z);
                    tempCube.setLed(v, CRGB::Red);
                }
            }
    };

    const uint8_t upArrow[CUBE_SIZE] = {
        0b00000000, // 0
        0b00010000, // 1
        0b00111000, // 2
        0b01111100, // 3
        0b11111110, // 4
        0b00111000, // 5
        0b00111000, // 6
        0b00111000, // 7
        0b00000000, // 8
    };

    const uint8_t downArrow[CUBE_SIZE] = {
        0b00000000, // 8
        0b00111000, // 7
        0b00111000, // 6
        0b00111000, // 5
        0b11111110, // 4
        0b01111100, // 3
        0b00111000, // 2
        0b00010000, // 1
        0b00000000, // 0
    };

    float angleX = 360;
    float angleY = 0;

    LedCube tempCube;
    uint8_t hue = 0;

    void drawFrame() override
    {
        // Rotate and draw
        Cube.clear();
        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                {
                    Vector3 v = Vector3(x, y, z);
                    CRGB color = tempCube.getLed(v);
                    if (color != CRGB(0, 0, 0))
                    {
                        v = v.rotate(angleX, Axis::X);
                        v = v.rotate(angleY, Axis::Y);
                        Cube.setLed(v, color + CHSV(hue, 255, 255));
                    }
                }

        // line in the middle
        // Cube.radiate(Point(4, 4, 4), 1.5, CRGB::Green + CHSV(hue, 255, 255), 3);
        // Cube.line(Point(1, 4, 4), Point(7, 4, 4), CRGB::Green + CHSV(hue, 255, 255));

        // Increase angle and hue
        hue++;
        angleX -= 15;
        if (angleX <= 0)
        {
            angleX = 360;
            angleY += 15;
            if (angleY >= 360)
                angleY = 0;
        }
    }
};

#include "Cube/Bitmaps/smile.h"

class Smile : public Animation
{
public:
    Smile()
    {
        name = __FUNCTION__;
        setDelay(60);

        uint8_t y = 1;
        tempCube.clear();
        for (int8_t z = 0; z < 9; z++)
            for (int8_t x = 0; x < 9; x++)
            {
                bool set = false;
                uint32_t data = smile_data[z * 9 + x];
                CRGB c;
                if (data >> 24 & 0xFF) // if not transparent
                {
                    set = true;
                }
                tempCube.setLed(CUBE_SIZE_M1 - x, y, CUBE_SIZE_M1 - z, set ? CRGB::White : CRGB::Black);
            }
    };

    float angle = 0;
    LedCube tempCube;
    uint8_t hue = 0;

    void drawFrame() override
    {
        CRGB color = CHSV(hue++, 255, 255);

        // Rotate and draw
        Cube.clear();
        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                {
                    Vector3 v = Vector3(x, y, z);
                    if (tempCube.getLed(v) != CRGB(0, 0, 0))
                    {
                        v = v.rotate(angle, Axis::Z);
                        Cube.setLed(v, color);
                    }
                }

        // Increase angle and go to next letter after full rotation
        angle += 10;
        if (angle >= 360)
        {
            angle = 0;
        }
    }
};

#include "Cube/Bitmaps/pacman.h"
#include "Cube/Bitmaps/pacman_ghost.h"

class Pacman : public Animation
{
public:
    Pacman()
    {
        name = __FUNCTION__;
        setDelay(150);

        uint8_t y = 1;

        updateBitmap();
    };

    float angle = 0;
    CRGB tempCube[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE] = {0};
    uint8_t hue = 0;
    const uint16_t pacmanRereshRate = 200;
    const uint16_t ghostRereshRate = 500;
    uint8_t pacmanFrame = 0;
    uint8_t ghostFrame = 0;

    int8_t moveX = 0;

    void clearTempCube()
    {
        for (int8_t x = 0; x < CUBE_SIZE; x++)
            for (int8_t y = 0; y < CUBE_SIZE; y++)
                for (int8_t z = 0; z < CUBE_SIZE; z++)
                {
                    tempCube[x][y][z] = CRGB::Black;
                }
    }

    void updateBitmap()
    {
        clearTempCube();
        for (int8_t z = 0; z < CUBE_SIZE; z++)
            for (int8_t x = 0; x < CUBE_SIZE; x++)
            {
                // pacman on the front
                uint32_t frame = pacman_data[pacmanFrame][z * CUBE_SIZE + x];
                CRGB col = CRGB::Black;
                if (frame >> 24 & 0xFF) // if not transparent
                {
                    col = CRGB((frame & 0xff), (frame >> 8) & 0xff, (frame >> 16 & 0xff)); // get rgb from data
                }
                tempCube[CUBE_SIZE_M1 - x][1][CUBE_SIZE_M1 - z] = col;

                // ghost on the back
                frame = ghost_data[ghostFrame][z * CUBE_SIZE + x];
                col = CRGB::Black;
                if (frame >> 24 & 0xFF) // if not transparent
                {
                    col = CRGB((frame & 0xff), (frame >> 8) & 0xff, (frame >> 16 & 0xff)); // get rgb from data
                }
                tempCube[CUBE_SIZE_M1 - x][CUBE_SIZE_M1 - 1][CUBE_SIZE_M1 - z] = col;
            }
    }

    bool changeFrame()
    {
        bool changed = false;
        EVERY_N_MILLIS(70)
        {
            pacmanFrame++;
            if (pacmanFrame >= PACMAN_FRAME_COUNT)
                pacmanFrame = 0;

            changed = true;
        }
        EVERY_N_MILLIS(500)
        {
            ghostFrame++;
            if (ghostFrame >= GHOST_FRAME_COUNT)
                ghostFrame = 0;

            changed = true;
        }

        return changed;
    }

    void rotatePacman()
    {
        Cube.clear();
        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                {
                    CRGB color = tempCube[x][y][z];
                    if (color != CRGB(0, 0, 0))
                    {
                        Vector3 v = Vector3(x, y, z).rotate(angle, Axis::Z);
                        Cube.setLed(v, color);
                    }
                }

        // Increase angle
        angle += 10;
        if (angle >= 360)
        {
            angle = 0;
        }
    }

    void movePacman()
    {
        Cube.clear();
        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                {
                    CRGB color = tempCube[x][y][z];
                    if (color != CRGB(0, 0, 0))
                    {
                        Vector3 v = Vector3(x, y, z);
                        // v = v.rotate(180.0, Axis::X);
                        v += Vector3(moveX, 0, 0);
                        Cube.setLed(v, color);
                    }
                }

        // // Move through the cube forward
        // moveX++;
        // if (moveX > CUBE_SIZE)
        //     moveX = -CUBE_SIZE;

        // Move through the cube backwards
        moveX--;
        if (moveX < -CUBE_SIZE)
            moveX = CUBE_SIZE;
    }

    void drawFrame() override
    {
        // Update bitmap
        if (changeFrame())
        {
            updateBitmap();
        }

        // rotatePacman();
        movePacman();
    }
};

class Sinus : public Animation
{
public:
    Sinus()
    {
        name = __FUNCTION__;
        setDelay(40);
    };

    CRGBPalette16 firePalette = CRGBPalette16(
        CRGB::Black, CRGB::Black, CRGB::Black, CHSV(0, 255, 4),
        CHSV(0, 255, 8), CRGB::Red, CRGB::Red, CRGB::Red,
        CRGB::DarkOrange, CRGB::Orange, CRGB::Orange, CRGB::Orange,
        CRGB::Yellow, CRGB::Yellow, CRGB::Gray, CRGB::Gray);

    uint32_t xscale = 100; // How far apart they are
    uint32_t yscale = 50;  // How fast they move
    uint32_t zscale = 50;  // How fast they move

    float x_min = -2;
    float x_max = 2;
    float z_min = -2;
    float z_max = 2;

    int16_t hue16;
    int16_t hue16_speed;
    float phase_speed = PI;
    float resolution = 30;
    float radius = 7.5f;
    int8_t hue_speed = -50 * 255;
    uint8_t brightness = 200;

    float phase = 0;

    void drawFrame() override
    {
        uint8_t brightness = 255;
        phase += getDeltaTime() * phase_speed;
        hue16 += getDeltaTime() * hue16_speed;

        for (uint16_t x = 0; x <= resolution; x++)
        {
            // convert cube x to floating point coordinate between x_min and x_max
            float xprime = mapf(x, 0, resolution, x_min, x_max);
            for (uint16_t z = 0; z <= resolution; z++)
            {
                // convert cube z to floating point coordinate between z_min and z_max
                float zprime = mapf(z, 0, resolution, z_min, z_max);
                // determine y floating point coordinate
                float y = sinf(phase + sqrtf(xprime * xprime + zprime * zprime));
                // display voxel on the cube scaled back to radius fitting the cube
                Vector3 point =
                    Vector3(2 * (x / resolution) - 1, 2 * (z / resolution) - 1, y);
                point = point.rotate(phase * 10.0f, Axis::Z);
                // point = q.rotate(point) * radius;
                // Color c =
                //     Color((hue16 >> 8) + (int8_t)(y * 64), RainbowGradientPalette);
                // radiate(point, c.scale(brightness), 1.0f);
                Cube.setLed(point, CHSV(hue16 >> 8, 255, 255));
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
        setDelay(40);
    };

    CRGBPalette16 firePalette = CRGBPalette16(
        CRGB::Black, CRGB::Black, CRGB::Black, CHSV(0, 255, 4),
        CHSV(0, 255, 8), CRGB::Red, CRGB::Red, CRGB::Red,
        CRGB::DarkOrange, CRGB::Orange, CRGB::Orange, CRGB::Orange,
        CRGB::Yellow, CRGB::Yellow, CRGB::Gray, CRGB::Gray);

    uint32_t xscale = 100; // How far apart they are
    uint32_t yscale = 50;  // How fast they move
    uint32_t zscale = 50;  // How fast they move

    void drawFrame() override
    {
        for (int i = 0; i < LED_COUNT; i++)
        {
            // 16 bit resoloution
            uint8_t index = inoise16(i * xscale, i * zscale, millis() * yscale * LED_COUNT / 65535);                  // X location is constant, but we move along the Y at the rate of millis()
            CRGB color = ColorFromPalette(firePalette, min(i * (index) >> 6, 255), i * 255 / LED_COUNT, LINEARBLEND); // With that value, look up the 8 bit colour palette value and assign it to the current LED.
            Cube.setLed(i, color);                                                                                    // Set the i'th led's color
        }
    }
};

class FireWorks : public Animation
{
public:
    FireWorks()
    {
        name = "Fire Works";
        setDelay(40);
    };

    Timer preMissileTimer;
    const Vector3 gravity = Vector3(0, 0, -1.0);

    uint8_t missileHue = 0;
    uint8_t explosionHue;
    float radius;
    Vector3 temp;
    Vector3 source;
    Vector3 target;
    Vector3 velocity;
    Particle missile;
    float explosionRadius = 0;
    float explosionMaxRadius;

    enum State
    {
        PREPARE_MISSILE,
        LAUNCHING,
        EXPLODING,
        RESET,
    };

    State state = PREPARE_MISSILE;

    void drawFrame() override
    {
        Cube.fadeAll(65);

        switch (state)
        {
        case PREPARE_MISSILE:

            if (preMissileTimer.ready())
            {
                source = Vector3(randomFloat(3, 5), randomFloat(3, 5), 0);
                target = Vector3(randomFloat(3, 6), randomFloat(3, 6), randomFloat(4.5, 6.5));
                float timeToTarget = randomFloat(1.2, 2.0);
                velocity = (target - source) / timeToTarget;
                missileHue = random8(0, 255);
                missile = Particle(source, velocity, missileHue, timeToTarget);
                Cube.setLed(missile.position, CHSV(missileHue, 255, 255));
                state = LAUNCHING;
            }
            break;
        case LAUNCHING:
            temp = missile.position;
            missile.move(getDeltaTime(), gravity);
            Cube.setLed(missile.position, CHSV(missileHue, 255, 255));

            if (temp.z > missile.position.z || missile.position.z > target.z)
            {
                explosionMaxRadius = randomFloat(2.5, 4.5);
                explosionHue = missileHue + random8(5, 15);
                state = EXPLODING;
            }
            break;

        case EXPLODING:
            explosionRadius += 0.5f;
            Cube.shell(missile.position, explosionRadius, CHSV(explosionHue++, 255, 255), randomFloat(0.1, 0.5));

            if (explosionRadius > explosionMaxRadius)
            {
                state = RESET;
            }
            break;

        case RESET:
            explosionRadius = 0;
            preMissileTimer.reset();
            preMissileTimer.setPeriod(random16(300, 800));
            state = PREPARE_MISSILE;
            break;
        }
    }
};

class Draw : public Animation
{
public:
    Draw()
    {
        name = __FUNCTION__;
        setDelay(500);
    };

    uint8_t hue = 0;
    CRGB color = CRGB(0, 255, 0);

    float angle = 45.0f;

    float radius = 0.0f;

    uint8_t power = 1;

    void drawFrame() override
    {
        // Quaternion q = Quaternion(angle, Vector3(0, 0, 1));
        // Vector3 v = Vector3(6, 6, 4) - Vector3(4, 4, 4);
        // v = q.rotate(v) + Vector3(4, 4, 4);

        // Quaternion q = Quaternion(angle, Axis::Z);
        // Quaternion q2 = Quaternion(90, Axis::Y);
        // Quaternion q3 = q * q2;
        // Vector3 v = Vector3(7, 7, 4);
        // v = q.rotate(v);

        // Vector3 v = Vector3(6, 6, 5);
        // v = v.rotate(angle, Axis::Z);
        // v = v.rotate(90.0f, Axis::Y);

        Cube.clear();
        Cube.radiate(Vector3(4, 4, 4), 4.1, color, 3);
        // Cube.s(Vector3(4, 4, 4), radius, color);

        if (power < 5)
            power++;
        else
            power = 2;

        if (radius < 4.0f)
            radius += 0.1f;
        else
            radius = 1.0f;

        // Cube.shell(v, 1, color);

        //         Vector3 v = Vector3(0, 0, 1);
        // v = v.rotate(angle, Vector3(5, 5, 5) - Vector3(4, 4, 4)) + Vector3(4, 4, 4);

        // Cube.setLed(Point(5, 5, 4), color);
        // Cube.setLed(Point(6, 6, 4), color);

        // clear colors
        // Cube.fadeAll(200);
        // Cube.setLed(v, color);

        // Point p = Point(4, 7, 4);
        // p = p.rotate(Point(4, 4, 4), Angles(angle, 0, 90));
        // Cube.fadeAll(200);
        // Cube.setLed(p, color);

        angle += 90;
        if (angle >= 360)
            angle = 0;
    }
};

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

        Cube.setLed(index++, color);
    }
};

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

// class Wave : public Animation
// {
// public:
//     Wave()
//     {
//         name = __FUNCTION__;
//         setDelay(100);
//     };

//     int32_t yHueDelta32;
//     int32_t xHueDelta32;
//     int8_t yHueDelta8;
//     int8_t xHueDelta8;

//     void drawFrame() override
//     {
//         uint32_t ms = millis();
//         yHueDelta32 = ((int32_t)cos16(ms * 27) * (350 / CUBE_SIZE));
//         xHueDelta32 = ((int32_t)cos16(ms * 39) * (310 / CUBE_SIZE));
//         yHueDelta8 = yHueDelta32 / 32768;
//         xHueDelta8 = xHueDelta32 / 32768;

//         byte lineStartHue = ms / 65536;
//         for (byte z = 0; z < CUBE_SIZE; z++)
//         {
//             for (byte y = 0; y < CUBE_SIZE; y++)
//             {
//                 lineStartHue += yHueDelta8;
//                 byte pixelHue = lineStartHue;
//                 for (byte x = 0; x < CUBE_SIZE; x++)
//                 {
//                     pixelHue += xHueDelta8;
//                     Cube.setLed(x, y, z, CHSV(pixelHue, 255, 255));
//                 }
//             }
//         }
//     }
// };

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
        Cube.leds.fill_gradient(CHSV(hue, 200, 255), CHSV(hue + 50, 255, 200));
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

        hue++;
    }
};

// class Confetti : public Animation
// {
// public:
//     Confetti()
//     {
//         name = __FUNCTION__;
//         setDelay(10);
//     };

//     uint8_t hue = 0;

//     void drawFrame() override
//     {
//         Cube.fadeAll(1);
//         EVERY_N_MILLIS(100)
//         {
//             int pos = random16(LED_COUNT);
//             Cube.leds[pos] += CHSV(hue + random8(64), 200, 255);
//             hue++;
//         }
//     }
// };

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
        RESETTING,
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
            Cube.line(Point(x, 0, 0), Point(CUBE_SIZE_M1 - x, CUBE_SIZE_M1, CUBE_SIZE_M1), color);
            Cube.line(Point(CUBE_SIZE_M1 - x, CUBE_SIZE_M1, 0), Point(x, 0, CUBE_SIZE_M1), CRGB::Black);
            x++;

            if (x == CUBE_SIZE_M1)
                side = LEFT;

            break;
        case LEFT:
            Cube.line(Point(CUBE_SIZE_M1, y, 0), Point(0, CUBE_SIZE_M1 - y, CUBE_SIZE_M1), color);
            Cube.line(Point(0, CUBE_SIZE_M1 - y, 0), Point(CUBE_SIZE_M1, y, CUBE_SIZE_M1), CRGB::Black);
            y++;

            if (y == CUBE_SIZE_M1)
                side = BACK;

            break;
        case BACK:
            Cube.line(Point(x, CUBE_SIZE_M1, 0), Point(8 - x, 0, CUBE_SIZE_M1), color);
            Cube.line(Point(CUBE_SIZE_M1 - x, 0, 0), Point(x, CUBE_SIZE_M1, CUBE_SIZE_M1), CRGB::Black);
            x--;

            if (x == 0)
                side = RIGHT;
            break;

        case RIGHT:
            Cube.line(Point(0, y, 0), Point(CUBE_SIZE_M1, CUBE_SIZE_M1 - y, CUBE_SIZE_M1), color);
            Cube.line(Point(CUBE_SIZE_M1, CUBE_SIZE_M1 - y, 0), Point(0, y, CUBE_SIZE_M1), CRGB::Black);
            y--;

            if (y == 0)
                side = FRONT;
            break;
        }
        color = CHSV(hue++, 255, 255);
        // Cube.fadeAll(35);
        Cube.setLed(4, 4, 4, color); // write to center as it keeps getting blanked out
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

    const uint8_t radius = 4;
    const uint8_t beatsPerMinute = 5;
    // bool expanding = true;
    // uint8_t index = 0;
    // uint8_t x = 0, y = 0, z = 0;
    // CRGB color = CHSV(hue, 255, 255);
    uint8_t hue = 0;
    uint8_t deltaHue = 1;

    CRGB white = CRGB(255, 255, 255);
    LedCube tempCube = LedCube();

    void fillCubeRainbow()
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

        // index = expanding ? index + 1 : index - 1;

        // if (index == 6 || index == 0)
        //     expanding = !expanding;

        // color = CHSV(hue += 2, 255, 255);
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
    const float waveScale = 0.55f;
    const uint8_t maxCounter = 100;

    uint8_t hue = 0;
    uint16_t index = 0;
    CRGB color = CRGB::Blue;

    uint8_t counter = 0;
    // uint8_t x = 0, y = 0, z = 0;

    CRGB gradientCube[LED_COUNT];

    void drawFrame() override
    {
        fill_gradient(gradientCube, LED_COUNT, CHSV(hue, 200, 255), CHSV(hue + 50, 255, 200));
        hue++;

        Cube.fadeAll(170);
        for (uint8_t x = 0; x < CUBE_SIZE / 2 + 1; x++)
        {
            for (uint8_t y = 0; y < CUBE_SIZE / 2 + 1; y++)
            {
                float phaseShift = (float)counter * 2.0 * PI / maxCounter;
                float insideSine = (waveScale * sqrt((x * x) + (y * y))) + phaseShift;
                float sineFunction = (amplitude * sin(insideSine)) + zOffset;
                float z = round(sineFunction);

                uint16_t index = (y * CUBE_SIZE * CUBE_SIZE) + (x * CUBE_SIZE) + z;
                CRGB color = gradientCube[index];
                Cube.setLed(x, y, z, color);
                Cube.setLed(x, CUBE_SIZE - y - 1, z, color);
                Cube.setLed(CUBE_SIZE - x - 1, y, z, color);
                Cube.setLed(CUBE_SIZE - x - 1, CUBE_SIZE - y - 1, z, color);
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

// class MatrixRain : public Animation
// {
// public:
//     MatrixRain()
//     {
//         name = __FUNCTION__;
//         setDelay(30);
//     };

//     const uint8_t rainAmount = 200;
//     const uint8_t fadeTailScale = 55;
//     const uint8_t fadeBottomScale = 30;

//     const CRGBPalette16 rainColor_p =
//         {
//             CRGB(0, 255, 0),
//             CRGB(0, 245, 10),
//             CRGB(30, 255, 10),
//             CRGB(20, 230, 20),
//             CRGB(0, 220, 0),
//             CRGB(0, 200, 30),
//             CRGB(20, 230, 10),
//             CRGB(0, 240, 0),
//             CRGB(20, 225, 10),
//             CRGB(30, 180, 20),
//             CRGB(10, 245, 10),
//             CRGB(30, 235, 5),
//             CRGB(20, 225, 20),
//             CRGB(10, 180, 20),
//             CRGB(10, 205, 40),
//             CRGB(20, 160, 20),
//         };

//     Particle lines[CUBE_SIZE][CUBE_SIZE];

//     void drawFrame() override
//     {

//         // Create new raindrops
//         if (random8() < rainAmount)
//         {
//             static Point prevPoint;
//             Point point;
//             do // Ensure the same point doesnt get set twice in a row
//             {
//                 point = Point(random8(0, CUBE_SIZE), random8(0, CUBE_SIZE), CUBE_SIZE - 1);
//             } while (point == prevPoint);
//             prevPoint = point;

//             lines[point.x][point.y].position = Vector3(point.x, point.y, point.z);
//             lines[point.x][point.y].velocity = Vector3(0, 0, randomFloat(0.7f, 1.3f));

//             Cube.setLed(point, ColorFromPalette(rainColor_p, random8(0, 255)));
//         }
//     }

//     // void drawFrame() override
//     // {
//     //     // Move raindrops down
//     //     EVERY_N_MILLISECONDS(70)
//     //     {
//     //         // Cube.fadeAll(fadeTailScale);
//     //         for (int x = 0; x < CUBE_SIZE; x++)
//     //             for (int y = 0; y < CUBE_SIZE; y++)
//     //                 for (int z = 0; z < CUBE_SIZE; z++)
//     //                 {
//     //                     CRGB rainColor = Cube.getLed(x, y, z);
//     //                     if (rainColor != CRGB(0, 0, 0))
//     //                     {
//     //                         if (z >= 1) // move rain down
//     //                         {
//     //                             if (rainColor.getAverageLight() > 80)
//     //                                 Cube.setLed(x, y, z - 1, rainColor);
//     //                         }
//     //                         Cube.fadeLed(x, y, z, fadeTailScale);
//     //                     }
//     //                 }
//     //     }

//     //     // Create new raindrops
//     //     if (random8() < rainAmount)
//     //     {
//     //         static Point prevPoint;
//     //         Point point;
//     //         do // Ensure the same point doesnt get set twice in a row
//     //         {
//     //             point = Point(random8(0, CUBE_SIZE), random8(0, CUBE_SIZE), CUBE_SIZE - 1);
//     //         } while (point == prevPoint);
//     //         prevPoint = point;

//     //         Cube.setLed(point, ColorFromPalette(rainColor_p, random8(0, 255)));
//     //     }
//     // }
// };

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
            Cube.setLed(ball[i], color);
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
            if (ball[i].x == CUBE_SIZE_M1 || ball[i].x == 0)
            {
                v[0] = -v[0];
                break;
            }
        }
        for (size_t i = 0; i < ballSize; i++)
        {
            if (ball[i].y == CUBE_SIZE_M1 || ball[i].y == 0)
            {
                v[1] = -v[1];
                break;
            }
        }
        for (size_t i = 0; i < ballSize; i++)
        {
            if (ball[i].z == CUBE_SIZE_M1 || ball[i].z == 0)
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

    //     if (ball.x == CUBE_SIZE_M1 || ball.x == 0)
    //         v[0] = -v[0];

    //     if (ball.y == CUBE_SIZE_M1 || ball.y == 0)
    //         v[1] = -v[1];

    //     if (ball.z == CUBE_SIZE_M1 || ball.z == 0)
    //         v[2] = -v[2];
    // }

    void drawFrame() override
    {
        Cube.fadeAll(170);

        setBallVoxel(ball1, CRGB::Blue);
        updateBall(ball1, v1);

        setBallVoxel(ball2, CRGB::Green);
        updateBall(ball2, v2);

        setBallVoxel(ball3, CRGB::Red);
        updateBall(ball3, v3);
    }
};

class Text : public Animation
{
public:
    Text(const char *text)
    {
        name = text;
        ascii = text;
        setDelay(100);
    };

    const char *ascii;
    CRGB color = CRGB::Blue;
    int8_t y = CUBE_SIZE_M1;
    uint8_t index = 0;
    bool thin = false;

    void drawFrame() override
    {
        if (y < 0)
        {
            color = CHSV(random8(), 255, 255);
            y = CUBE_SIZE_M1;
            index++;
            if (ascii[index] == '\0')
            {
                thin = !thin;
                index = 0;
            }
            if (ascii[index] == ' ')
                Cube.fadeAll(200);
        }

        Cube.fadeAll(180);
        thin ? Cube.asciiThin(ascii[index], y, color) : Cube.ascii(ascii[index], y, color);
        y--;
    }
};

class TextRotate : public Animation
{
public:
    TextRotate(const char *text)
    {
        name = text;
        ascii = text;
        setDelay(80);
    };

    const char *ascii;
    CRGB color = CRGB::Blue;
    uint8_t index = 0;
    float angle = 0.0f;
    LedCube tempCube = LedCube();

    void drawFrame() override
    {
        // Motion blur
        Cube.fadeAll(150);

        // Draw text on temp cube
        tempCube.clear();
        tempCube.asciiThin(ascii[index], CUBE_CENTER, color);

        // Rotate text
        for (int x = 0; x < CUBE_SIZE; x++)
            for (int y = 0; y < CUBE_SIZE; y++)
                for (int z = 0; z < CUBE_SIZE; z++)
                    if (tempCube.getLed(x, y, z) != CRGB(CRGB::Black))
                    {
                        // Quaternion q = Quaternion(angle, Axis::Z);
                        // Vector3 v = q.rotate(Vector3(x, y, z));
                        // Cube.setLed(v, color);

                        Vector3 v = Vector3(x, y, z).rotate(angle, Axis::Z);
                        Cube.setLed(v, color);

                        // Point p = Point(x, y, z).rotate(Angles(0, 0, angle));
                        // Cube.setLed(p, color);
                    }

        // fade in and out
        if (angle > 300)
            Cube.fadeAll(map(angle, 300, 360, 0, 255));
        else if (angle < 60)
            Cube.fadeAll(map(angle, 60, 0, 0, 255));

        // Increase angle and go to next letter after full rotation
        angle += 10;
        if (angle >= 360)
        {
            angle = 0;
            index++;
            if (ascii[index] == '\0')
            {
                index = 0;
            }
        }
    }
};

class Box : public Animation
{
public:
    Box()
    {
        name = __FUNCTION__;
        setDelay(80);
    };

    const uint8_t low = 0;
    const uint8_t high = CUBE_SIZE_M1;
    uint8_t hue = 0;

    void drawFrame() override
    {
        Cube.box(Point(low, low, low), Point(high, high, high), CHSV(hue + 10, 255, 255));
        Cube.box(Point(low + 1, low + 1, low + 1), Point(high - 1, high - 1, high - 1), CHSV(hue + 30, 255, 255));
        Cube.box(Point(low + 2, low + 2, low + 2), Point(high - 2, high - 2, high - 2), CHSV(hue + 50, 255, 255));
        // Cube.box(Point(low + 3, low + 3, low + 3), Point(high - 3, high - 3, high - 3), CHSV(hue + 70, 255, 255));
        Cube.sphere(CUBE_CENTER, CUBE_CENTER, CUBE_CENTER, 1.0, CHSV(hue + 70, 255, 255));

        hue += 1;
    }
};