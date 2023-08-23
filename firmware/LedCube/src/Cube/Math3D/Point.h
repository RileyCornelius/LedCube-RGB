#pragma once

#include "Math3D.h"

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
struct Point
{
    int8_t x;
    int8_t y;
    int8_t z;

    Point();
    Point(uint8_t X, uint8_t Y, uint8_t Z);
    Point(const Point &p);
    Point(const Vector3 &v);

    Point operator=(const Point &p);
    bool operator==(const Point &p);
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
    Point rotate(const Point &c, Angles a);
};
