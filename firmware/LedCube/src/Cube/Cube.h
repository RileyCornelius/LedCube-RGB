#pragma once

#if defined(ESP32)
// Changes data transfer from RMT to I2S which can handle up to 24 parallel branches
#define FASTLED_ESP32_I2S true // This must be defined before including FastLED.h
#endif

#include <FastLED.h>
#include "Cube/Math3D/Math3D.h"
#include "Cube/Math3D/Point.h"
#include "Cube/Math3D/Vector3.h"
#include "Cube/Math3D/Quaternion.h"
#include "config.h"

/*---------------------------------------------------------------------------------------
 * CUBE CLASS - 3D RGB LED Cube
 *-------------------------------------------------------------------------------------*/

/**
 * Helper class to create 3d rgb animations for the FastLED library
 */
class LedCube
{
public:
    CRGB leds[LED_COUNT];

public:
    LedCube();

    void setLed(int8_t x, int8_t y, int8_t z, const CRGB &col);
    void setLed(uint16_t index, const CRGB &col);
    void setLed(const Point &p, const CRGB &col);
    CRGB getLed(int8_t x, int8_t y, int8_t z);
    CRGB getLed(uint16_t index);
    CRGB getLed(const Point &p);
    void fadeLed(int8_t x, int8_t y, int8_t z, int8_t scale);
    void fadeLed(const Point &p, int8_t scale);
    void fadeLed(uint16_t index, int8_t scale);
    void fadeAll(int8_t scale);
    void fill(const CRGB &col);
    void clear();
    void line(int x1, int y1, int z1, int x2, int y2, int z2, const CRGB &col);
    void line(const Point &p1, const Point &p2, const CRGB &col);
    void triangle(const Point &p1, const Point &p2, const Point &p3, const CRGB &col);
    void square(const Point &p1, const Point &p2, const Point &p3, const Point &p4, const CRGB &col);
    void sphere(int x, int y, int z, int radius, const CRGB &col);
    void sphere(const Point &p, int radius, const CRGB &col);
    void shell(float x, float y, float z, float r, const CRGB &col, float thickness = 0.1);
    void shell(const Point &p, float r, const CRGB &col, float thickness = 0.1);
    void ascii(char ascii, int8_t y, const CRGB &color);
    void asciiThin(char ascii, int8_t y, const CRGB &color);

private:
    uint16_t getIndex(uint16_t index);
    uint16_t getIndex(int8_t x, int8_t y, int8_t z);
    uint16_t getIndex(const Point &p);
    Point getPoint(uint16_t index);
};

extern LedCube Cube;
