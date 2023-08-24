#pragma once

#include <Arduino.h>
#include "Vector3.h"

/*------------------------------------------------------------------------------
 * Quaternion CLASS
 *------------------------------------------------------------------------------
 * A Quaternion is a complex number in the form  w + xi + yj + zk, where w, x,
 *y, z are real numbers and i, j, k are imaginary.
 *
 * In the implementation i,j and k are ignored, w is a scalar and x,y,z is a
 *vector
 *----------------------------------------------------------------------------*/
class Quaternion
{
public:
    float w;
    Vector3 v;

public:
    // constructors
    Quaternion();
    Quaternion(const Quaternion &q);
    Quaternion(float w, const Vector3 &v);

    // moving (add subtract)
    Quaternion operator+(const Quaternion &q) const;
    Quaternion operator-(const Quaternion &q) const;
    Quaternion &operator+=(const Quaternion &q);
    Quaternion &operator-=(const Quaternion &q);

    // scaling (multiply divide by scalar)
    Quaternion operator*(float s) const;
    Quaternion operator/(float s) const;
    Quaternion &operator*=(float s);
    Quaternion &operator/=(float s);

    // multiply quaternions
    Quaternion operator*(const Quaternion &q) const;
    Quaternion operator/(const Quaternion &q) const;
    Quaternion &operator*=(const Quaternion &q);

    // dot product
    float dot(const Quaternion &q) const;
    float operator%(const Quaternion &q) const;

    // inverse
    Quaternion &inverse();
    Quaternion inversed() const;
    // get conjugate (negative imaginary part)
    Quaternion &conjugate();
    Quaternion conjugated() const;
    // unit quaternion
    Quaternion &normalize();
    Quaternion normalized() const;
    // magnitude or length of the quaternion
    float magnitude() const;
    float norm() const;
    // rotate v by quaternion
    Vector3 rotate(const Vector3 &v, const Vector3 &c = Vector3(4, 4, 4));
};
