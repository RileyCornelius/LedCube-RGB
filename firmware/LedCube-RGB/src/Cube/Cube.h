#pragma once

#include <FastLED.h>

// Cube Defines
#define CUBE_SIZE 3
#define PIXEL_COUNT (CUBE_SIZE * CUBE_SIZE * CUBE_SIZE)
#define PIXEL_PIN 3
#define PIXEL_TYPE WS2812B
#define COLOR_ORDER RGB

/*---------------------------------------------------------------------------------------
 * POINT CLASS - 3D Point on Cube
 *-------------------------------------------------------------------------------------*/
struct Point
{
    uint8_t x;
    uint8_t y;
    uint8_t z;
    Point() : x(0), y(0), z(0) {}
    Point(uint8_t _x, uint8_t _y, uint8_t _z) : x(_x), y(_y), z(_z) {}
};

/*---------------------------------------------------------------------------------------
 * CUBE CLASS - 3D LED Cube
 *-------------------------------------------------------------------------------------*/
class RGBLedCube
{
private:
    uint16_t getIndex(uint8_t x, uint8_t y, uint8_t z);
    Point getPoint(uint16_t index);

public:
    RGBLedCube();
    CRGB leds[PIXEL_COUNT];
    void setVoxel(uint8_t x, uint8_t y, uint8_t z, CRGB col);
    void setVoxel(uint16_t index, CRGB col);
    void setVoxel(Point p, CRGB col);
    CRGB getVoxel(uint8_t x, uint8_t y, uint8_t z);
    CRGB getVoxel(uint16_t index);
    CRGB getVoxel(Point p);
    void fadeVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t scale);
    void fadeVoxel(Point p, uint8_t scale);
    void fadeVoxel(uint16_t index, uint8_t scale);
    void fadeAll(uint8_t scale);
    void fill(CRGB col);
    void clear();
};

extern RGBLedCube Cube;

// MACROS
#define SAFE_VOXEL_ON 1

#if SAFE_VOXEL_ON
#define SAFE_VOXEL_GUARD(index) \
    if (index >= PIXEL_COUNT)   \
        while (1)               \
            ;
#else
#define SAFE_VOXEL(index)
#endif