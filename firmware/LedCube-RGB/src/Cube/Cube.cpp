#include "Cube.h"

// Global cube helper object for Animation sub classes
RGBLedCube Cube = RGBLedCube();

// Enables safe voxel guard
#define SAFE_VOXEL_ON 1

#if SAFE_VOXEL_ON
// Checks if invalid index is trying to be accessed and stops the program if so
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

#define SERPENT_LAYOUT false

// Set 'SERPENT_LAYOUT' to true if leds are like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//                         |
//     9 <  8 <  7 <  6 <  5
//     |
//     |
//    10 > 11 > 12 > 13 > 14
//
// Set 'SERPENT_LAYOUT' to false if leds are like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//     .----<----<----<----'
//     |
//     5 >  6 >  7 >  8 >  9
//                         |
//     .----<----<----<----'
//     |
//    10 > 11 > 12 > 13 > 14
//

/*--------------------------- PRIVATE FUNCTIONS --------------------------*/
uint16_t RGBLedCube::getIndex(uint8_t x, uint8_t y, uint8_t z)
{
#if SERPENT_LAYOUT

    uint16_t xy = 0;
    if (y & 0x01) // Odd rows run backwards
    {
        uint8_t reverseX = (CUBE_SIZE - 1) - x;
        xy = (y * CUBE_SIZE) + reverseX;
    }
    else // Even rows run forwards
    {
        xy = (y * CUBE_SIZE) + x;
    }
    return (z * CUBE_SIZE * CUBE_SIZE) + xy;
#else
    return (z * CUBE_SIZE * CUBE_SIZE) + (x * CUBE_SIZE) + y;
#endif
}

Point RGBLedCube::getPoint(uint16_t index)
{
    uint8_t z = index / (CUBE_SIZE * CUBE_SIZE);              // get layer
    uint8_t layerIndex = index - (z * CUBE_SIZE * CUBE_SIZE); // get 2D index of layer
    uint8_t y = layerIndex / CUBE_SIZE;                       // get y on layer
    uint8_t x = layerIndex % CUBE_SIZE;                       // get x on layer

    return Point(x, y, z);
}
