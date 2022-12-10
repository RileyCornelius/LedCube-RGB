#include "Cube.h"

// Globl cube object for Animation sub classes
RGBLedCube Cube = RGBLedCube();

// Enables safe voxel guard
#define SAFE_VOXEL_ON 1

// Checks if invalid index is trying to be accessed and stops the program if so
#if SAFE_VOXEL_ON
#define SAFE_VOXEL_GUARD(index) \
    if (index >= LED_COUNT)     \
        while (1)               \
            ;
#else
#define SAFE_VOXEL_GUARD(index)
#endif

RGBLedCube::RGBLedCube()
{
}

void RGBLedCube::setVoxel(Point p, CRGB col)
{
    setVoxel(p.x, p.y, p.z, col);
}

void RGBLedCube::setVoxel(uint8_t x, uint8_t y, uint8_t z, CRGB col)
{
    setVoxel(getIndex(x, y, z), col);
}

void RGBLedCube::setVoxel(uint16_t index, CRGB col)
{
    SAFE_VOXEL_GUARD(index)
    leds[index] = col;
}

CRGB RGBLedCube::getVoxel(Point p)
{
    return getVoxel(p.x, p.y, p.z);
}

CRGB RGBLedCube::getVoxel(uint8_t x, uint8_t y, uint8_t z)
{
    return getVoxel(getIndex(x, y, z));
}

CRGB RGBLedCube::getVoxel(uint16_t index)
{
    SAFE_VOXEL_GUARD(index)
    return CRGB(leds[index].r, leds[index].g, leds[index].b);
}

void RGBLedCube::fadeVoxel(Point p, uint8_t scale)
{
    fadeVoxel(p.x, p.y, p.z, scale);
}

void RGBLedCube::fadeVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t scale)
{
    fadeVoxel(getIndex(x, y, z), scale);
}

void RGBLedCube::fadeVoxel(uint16_t index, uint8_t scale)
{
    SAFE_VOXEL_GUARD(index)
    leds[index].nscale8(scale);
}

void RGBLedCube::fadeAll(uint8_t scale) // scale / 256 * color
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        fadeVoxel(i, scale);
}

void RGBLedCube::fill(CRGB col)
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        setVoxel(i, col);
}

void RGBLedCube::clear()
{
    fill(CRGB::Black);
}

/*--------------------------- PRIVATE FUNCTIONS --------------------------*/
uint16_t RGBLedCube::getIndex(uint8_t x, uint8_t y, uint8_t z)
{
    return (z * CUBE_SIZE * CUBE_SIZE) + (x * CUBE_SIZE) + y;
}

Point RGBLedCube::getPoint(uint16_t index)
{
    uint8_t z = index / (CUBE_SIZE * CUBE_SIZE);              // get layer
    uint8_t layerIndex = index - (z * CUBE_SIZE * CUBE_SIZE); // get 2D index of layer
    uint8_t y = layerIndex / CUBE_SIZE;                       // get y on layer
    uint8_t x = layerIndex % CUBE_SIZE;                       // get x on layer

    return Point(x, y, z);
}
