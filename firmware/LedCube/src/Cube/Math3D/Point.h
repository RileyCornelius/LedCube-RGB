#pragma once

#include <Arduino.h>
#include "Vector3.h"
#include "config.h"

/*---------------------------------------------------------------------------------------
 * Angles STRUCT - Rotate in 3D
 *-------------------------------------------------------------------------------------*/

/**
 * Angles for rotation on point
 */
struct Angles
{
    float x; // rad
    float y; // rad
    float z; // rad

    Angles(float degreeX, float degreeY, float degreeZ);
};

/*---------------------------------------------------------------------------------------
 * POINT STRUCT - 3D Point in Cube
 *-------------------------------------------------------------------------------------*/

/**
 * x, y, z location
 */
class Point
{
public:
    int8_t x;
    int8_t y;
    int8_t z;

public:
    Point();
    Point(int8_t X, int8_t Y, int8_t Z);
    Point(const Point &p);
    Point(const Vector3 &v);

    bool operator==(const Point &p) const;
    Point operator=(const Point &p);
    Point operator+(const Point &p) const;
    Point operator-(const Point &p) const;
    Point &operator+=(const Point &p);
    Point &operator-=(const Point &p);
    Point operator*(const float &s) const;
    Point operator/(const float &s) const;
    Point &operator*=(const float &s);
    Point &operator/=(const float &s);
    Point operator-() const;

    bool isValid();
    Point rotate(Angles a, const Point &c = Point(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH));
};
