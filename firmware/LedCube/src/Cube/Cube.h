#pragma once

#if defined(ESP32)
// Changes data transfer from RMT to I2S which can handle up to 24 parallel branches
#define FASTLED_ESP32_I2S true // This must be defined before including FastLED.h
#endif
#include <FastLED.h>
#include "Point.h"
#include "Cube/Math3D/Math3D.h"
#include "config.h"

/*---------------------------------------------------------------------------------------
 * CUBE CLASS - 3D RGB LED Cube
 *-------------------------------------------------------------------------------------*/

/**
 * Helper class to create 3d rgb animations for the FastLED library
 */
class LedCube
{
private:
    uint16_t getIndex(uint16_t index);
    uint16_t getIndex(uint8_t x, uint8_t y, uint8_t z);
    uint16_t getIndex(Point p);
    Point getPoint(uint16_t index);

public:
    LedCube();
    CRGB leds[LED_COUNT];
    void setVoxel(uint8_t x, uint8_t y, uint8_t z, CRGB col);
    void setVoxel(uint16_t index, CRGB col);
    void setVoxel(Point p, CRGB col);
    void setVoxel(Vector3 p, CRGB col);
    CRGB getVoxel(uint8_t x, uint8_t y, uint8_t z);
    CRGB getVoxel(uint16_t index);
    CRGB getVoxel(Point p);
    void fadeVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t scale);
    void fadeVoxel(Point p, uint8_t scale);
    void fadeVoxel(uint16_t index, uint8_t scale);
    void fadeXLayer(uint8_t x, uint8_t scale);
    void fadeYLayer(uint8_t y, uint8_t scale);
    void fadeZLayer(uint8_t z, uint8_t scale);
    void fadeAll(uint8_t scale);
    void fill(CRGB col);
    void clear();
    void line(int x1, int y1, int z1, int x2, int y2, int z2, CRGB col);
    void line(Point p1, Point p2, CRGB col);
    void triangle(Point p1, Point p2, Point p3, CRGB col);
    void square(Point p1, Point p2, Point p3, Point p4, CRGB col);
    void sphere(int x, int y, int z, int radius, CRGB col);
    void sphere(Point p, int radius, CRGB col);
    void shell(float x, float y, float z, float r, CRGB col, float thickness = 0.1);
    void shell(Point p, float r, CRGB col, float thickness = 0.1);
    void ascii(char ascii, uint8_t y, CRGB color);
    void asciiThin(char ascii, uint8_t y, CRGB color);
};

extern LedCube Cube;
