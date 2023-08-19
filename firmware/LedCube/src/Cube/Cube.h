#pragma once

#if defined(ESP32)
// Changes data transfer from RMT to I2S which can handle up to 24 parallel branches
#define FASTLED_ESP32_I2S true // This must be defined before including FastLED.h
#endif
#include <FastLED.h>
#include "config.h"

enum Font
{
    IBM_BIOS,
    IBM_CGA,
    IBM_CGA_LIGHT,
    IBM_VGA,
};

/*---------------------------------------------------------------------------------------
 * POINT STRUCT - 3D Point in Cube
 *-------------------------------------------------------------------------------------*/

/**
 * x, y, z location
 */
struct Point
{
    uint8_t x;
    uint8_t y;
    uint8_t z;
    Point() : x(0), y(0), z(0) {}
    Point(uint8_t X, uint8_t Y, uint8_t Z) : x(X), y(Y), z(Z) {}
    Point(const Point &p) : x(p.x), y(p.y), z(p.z) {}

    // set this point equal to another
    Point operator=(const Point &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }

    // compare two points
    bool operator==(const Point &p)
    {
        return (x == p.x && y == p.y && z == p.z);
    }

    // add two points together
    Point operator+(const Point &p)
    {
        return Point(x + p.x, y + p.y, z + p.z);
    }

    // subtract two points
    Point operator-(const Point &p)
    {
        return Point(x - p.x, y - p.y, z - p.z);
    }

    // add to this point
    Point operator+=(const Point &p)
    {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    // subtract from this point
    Point operator-=(const Point &p)
    {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }

    // multiply a point by a scalar
    Point operator*(const int &s)
    {
        return Point(x * s, y * s, z * s);
    }

    // divide a point by a scalar
    Point operator/(const int &s)
    {
        return Point(x / s, y / s, z / s);
    }

    // multiply this point by a scalar
    Point operator*=(const int &s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // divide this point by a scalar
    Point operator/=(const int &s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }
};

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
    void shell(float x, float y, float z, float r, CRGB col);
    void shell(float x, float y, float z, float r, float thickness, CRGB col);
    void shell(Point p, float r, CRGB col);
    void shell(Point p, float r, float thickness, CRGB col);
    void ascii_1(Font font, char ascii, uint8_t y, CRGB color);
    void ascii(char ascii, uint8_t y, CRGB color);
    void asciiThin(char ascii, uint8_t y, CRGB color);
};

extern LedCube Cube;
