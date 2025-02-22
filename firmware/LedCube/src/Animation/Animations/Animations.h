#pragma once

#include <Logger.h>
#include "Animation/Animation.h"
#include "Cube/Cube.h"

#include "Animation/Animations/Arrow.h"
#include "Animation/Animations/Bounce.h"
#include "Animation/Animations/Box.h"
#include "Animation/Animations/BPM.h"
#include "Animation/Animations/FireWorks.h"
#include "Animation/Animations/Gradient.h"
#include "Animation/Animations/Pacman.h"
#include "Animation/Animations/Rain.h"
#include "Animation/Animations/Rainbow.h"
#include "Animation/Animations/Ripple.h"
#include "Animation/Animations/Sinelon.h"
#include "Animation/Animations/Smile.h"
#include "Animation/Animations/Sparkles.h"
#include "Animation/Animations/Sphere.h"
#include "Animation/Animations/Spiral.h"
#include "Animation/Animations/Text.h"

// class Fire : public Animation
// {
// public:
//     Fire()
//     {
//         name = __FUNCTION__;
//         setDelay(40);s
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

// class Sinus : public Animation
// {
// public:
//     Sinus()
//     {
//         name = __FUNCTION__;
//         setDelay(40);
//     };

//     CRGBPalette16 firePalette = CRGBPalette16(
//         CRGB::Black, CRGB::Black, CRGB::Black, CHSV(0, 255, 4),
//         CHSV(0, 255, 8), CRGB::Red, CRGB::Red, CRGB::Red,
//         CRGB::DarkOrange, CRGB::Orange, CRGB::Orange, CRGB::Orange,
//         CRGB::Yellow, CRGB::Yellow, CRGB::Gray, CRGB::Gray);

//     uint32_t xscale = 100; // How far apart they are
//     uint32_t yscale = 50;  // How fast they move
//     uint32_t zscale = 50;  // How fast they move

//     float x_min = -2;
//     float x_max = 2;
//     float z_min = -2;
//     float z_max = 2;

//     int16_t hue16;
//     int16_t hue16_speed;
//     float phase_speed = PI;
//     float resolution = 30;
//     float radius = 7.5f;
//     int8_t hue_speed = -50 * 255;
//     uint8_t brightness = 200;

//     float phase = 0;

//     void drawFrame() override
//     {
//         uint8_t brightness = 255;
//         phase += getDeltaTime() * phase_speed;
//         hue16 += getDeltaTime() * hue16_speed;

//         for (uint16_t x = 0; x <= resolution; x++)
//         {
//             // convert cube x to floating point coordinate between x_min and x_max
//             float xprime = mapf(x, 0, resolution, x_min, x_max);
//             for (uint16_t z = 0; z <= resolution; z++)
//             {
//                 // convert cube z to floating point coordinate between z_min and z_max
//                 float zprime = mapf(z, 0, resolution, z_min, z_max);
//                 // determine y floating point coordinate
//                 float y = sinf(phase + sqrtf(xprime * xprime + zprime * zprime));
//                 // display voxel on the cube scaled back to radius fitting the cube
//                 Vector3 point =
//                     Vector3(2 * (x / resolution) - 1, 2 * (z / resolution) - 1, y);
//                 point = point.rotate(phase * 10.0f, Axis::Z);
//                 // point = q.rotate(point) * radius;
//                 // Color c =
//                 //     Color((hue16 >> 8) + (int8_t)(y * 64), RainbowGradientPalette);
//                 // radiate(point, c.scale(brightness), 1.0f);
//                 Cube.setLed(point, CHSV(hue16 >> 8, 255, 255));
//             }
//         }
//     }
// };

// class Fire : public Animation
// {
// public:
//     Fire()
//     {
//         name = __FUNCTION__;
//         setDelay(40);
//     };

//     CRGBPalette16 firePalette = CRGBPalette16(
//         CRGB::Black, CRGB::Black, CRGB::Black, CHSV(0, 255, 4),
//         CHSV(0, 255, 8), CRGB::Red, CRGB::Red, CRGB::Red,
//         CRGB::DarkOrange, CRGB::Orange, CRGB::Orange, CRGB::Orange,
//         CRGB::Yellow, CRGB::Yellow, CRGB::Gray, CRGB::Gray);

//     uint32_t xscale = 100; // How far apart they are
//     uint32_t yscale = 50;  // How fast they move
//     uint32_t zscale = 50;  // How fast they move

//     void drawFrame() override
//     {
//         for (int i = 0; i < LED_COUNT; i++)
//         {
//             // 16 bit resoloution
//             uint8_t index = inoise16(i * xscale, i * zscale, millis() * yscale * LED_COUNT / 65535);                  // X location is constant, but we move along the Y at the rate of millis()
//             CRGB color = ColorFromPalette(firePalette, min(i * (index) >> 6, 255), i * 255 / LED_COUNT, LINEARBLEND); // With that value, look up the 8 bit colour palette value and assign it to the current LED.
//             Cube.setLed(i, color);                                                                                    // Set the i'th led's color
//         }
//     }
// };

// class Draw : public Animation
// {
// public:
//     Draw()
//     {
//         name = __FUNCTION__;
//         setDelay(500);
//     };

//     uint8_t hue = 0;
//     CRGB color = CRGB(0, 255, 0);

//     float angle = 45.0f;

//     float radius = 0.0f;

//     uint8_t power = 1;

//     void drawFrame() override
//     {
//         // Quaternion q = Quaternion(angle, Vector3(0, 0, 1));
//         // Vector3 v = Vector3(6, 6, 4) - Vector3(4, 4, 4);
//         // v = q.rotate(v) + Vector3(4, 4, 4);

//         // Quaternion q = Quaternion(angle, Axis::Z);
//         // Quaternion q2 = Quaternion(90, Axis::Y);
//         // Quaternion q3 = q * q2;
//         // Vector3 v = Vector3(7, 7, 4);
//         // v = q.rotate(v);

//         // Vector3 v = Vector3(6, 6, 5);
//         // v = v.rotate(angle, Axis::Z);
//         // v = v.rotate(90.0f, Axis::Y);

//         Cube.clear();
//         Cube.radiate(Vector3(4, 4, 4), 4.1, color, 3);
//         // Cube.s(Vector3(4, 4, 4), radius, color);

//         if (power < 5)
//             power++;
//         else
//             power = 2;

//         if (radius < 4.0f)
//             radius += 0.1f;
//         else
//             radius = 1.0f;

//         // Cube.shell(v, 1, color);

//         //         Vector3 v = Vector3(0, 0, 1);
//         // v = v.rotate(angle, Vector3(5, 5, 5) - Vector3(4, 4, 4)) + Vector3(4, 4, 4);

//         // Cube.setLed(Point(5, 5, 4), color);
//         // Cube.setLed(Point(6, 6, 4), color);

//         // clear colors
//         // Cube.fadeAll(200);
//         // Cube.setLed(v, color);

//         // Point p = Point(4, 7, 4);
//         // p = p.rotate(Point(4, 4, 4), Angles(angle, 0, 90));
//         // Cube.fadeAll(200);
//         // Cube.setLed(p, color);

//         angle += 90;
//         if (angle >= 360)
//             angle = 0;
//     }
// };

// class SolidColor : public Animation
// {
// public:
//     SolidColor(CRGB color)
//     {
//         name = __FUNCTION__;
//         this->color = color;
//         setDelay(30);
//     };
//     CRGB color;

//     void drawFrame() override
//     {
//         Cube.fill(color);
//     }
// };

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

// class Shell : public Animation
// {
// public:
//     Shell()
//     {
//         name = __FUNCTION__;
//         setDelay(75);
//     };
//     bool expanding = true;

//     uint8_t index = 0;
//     uint8_t hue = 0;
//     CRGB color = CHSV(hue, 255, 255);
//     uint8_t x = 0, y = 0, z = 0;

//     void drawFrame() override
//     {
//         Cube.clear();
//         Cube.shell(Point(4, 4, 4), index, 0.2, color);
//         index = expanding ? index + 1 : index - 1;

//         if (index == 6 || index == 0)
//             expanding = !expanding;

//         color = CHSV(hue += 2, 255, 255);
//     }
// };

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