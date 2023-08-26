#pragma once

#include "config.h"

/*------------------------------------------------------------------------------
 * Vector3 CLASS
 *------------------------------------------------------------------------------
 * A vector V in physics is an (angel, magnitude) magnitude is length and the
 * angle is usually represented by Greek letter theta.
 *
 * In game development a vector is stored as (x,y,z) representing a movement
 * in the Cartesian plane across the x, y and z axis.
 *
 * A point or the position of an object can also be represented by a vector by
 * moving from the origin to the coordinates (x,y,z)
 *
 * The length = sqrt(x*x + y*y + z*z)
 *----------------------------------------------------------------------------*/
class Vector3
{
public:
    float x, y, z;

public:
    // constructors
    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3 &v);

    Vector3 operator+(const Vector3 &v) const;
    Vector3 operator-(const Vector3 &v) const;
    Vector3 &operator+=(const Vector3 &v);
    Vector3 &operator-=(const Vector3 &v);
    Vector3 operator*(float s) const;
    Vector3 operator/(float s) const;
    Vector3 &operator*=(float s);
    Vector3 &operator/=(float s);
    Vector3 operator-() const;

    Vector3 cross(const Vector3 &v) const;
    float dot(const Vector3 &v) const;
    Vector3 normalize() const;
    float magnitude() const;

    bool inside(const Vector3 &v, float radius) const;
    bool inside(const Vector3 &l, const Vector3 &h) const;
    bool isValid() const;

    Vector3 rotate(float angle, const Vector3 &v, const Vector3 &c = Vector3(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH));
};

// Axis of rotation constants
struct Axis
{
    static const Vector3 X;
    static const Vector3 Y;
    static const Vector3 Z;
};