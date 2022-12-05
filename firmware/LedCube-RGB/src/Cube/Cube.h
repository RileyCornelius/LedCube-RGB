#pragma once

#include <FastLED.h>
#include "config.h"

/*---------------------------------------------------------------------------------------
 * POINT STRUCT - 3D Point in Cube
 *-------------------------------------------------------------------------------------*/
struct Point
{
    uint8_t x;
    uint8_t y;
    uint8_t z;
    Point() : x(0), y(0), z(0) {}
    Point(uint8_t X, uint8_t Y, uint8_t Z) : x(X), y(Y), z(Z) {}
};

/*---------------------------------------------------------------------------------------
 * CUBE CLASS - 3D RGB LED Cube
 *-------------------------------------------------------------------------------------*/
class RGBLedCube
{
private:
    uint16_t getIndex(uint8_t x, uint8_t y, uint8_t z);
    Point getPoint(uint16_t index);

public:
    RGBLedCube();
    CRGB leds[LED_COUNT];
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