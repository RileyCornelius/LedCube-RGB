
#include "Vector3.h"
#include "Math3D.h"

/*------------------------------------------------------------------------------
 * Vector3 CLASS
 *----------------------------------------------------------------------------*/

// Constructors
Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f){};
Vector3::Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_){};
Vector3::Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z){};

// add two vectors together
Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

// subtract two vectors
Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

// add to this vector
Vector3 &Vector3::operator+=(const Vector3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

// subtract from this vector
Vector3 &Vector3::operator-=(const Vector3 &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

// negative (operator -)
Vector3 Vector3::operator-() const { return Vector3(-x, -y, -z); }

// multiply a vector by a scalar
Vector3 Vector3::operator*(float s) const
{
    return Vector3(x * s, y * s, z * s);
}

// divide a vector by a scalar
Vector3 Vector3::operator/(float s) const
{
    return Vector3(x / s, y / s, z / s);
}

// multiply this vector by a scalar
Vector3 &Vector3::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

// divide this vector by a scalar
Vector3 &Vector3::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

// cross product
Vector3 Vector3::cross(const Vector3 &v) const
{
    return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

// dot product
float Vector3::dot(const Vector3 &v) const
{
    return x * v.x + y * v.y + z * v.z;
}

// Ensure vector is not greater than 1
Vector3 Vector3::normalize() const { return *this / magnitude(); }

// length from origin
float Vector3::magnitude() const
{
    return sqrt(x * x + y * y + z * z);
}

// Check if this vector is within a spherical radius of v inclusive
bool Vector3::inside(const Vector3 &v, float radius) const
{
    return ((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y) +
                (v.z - z) * (v.z - z) <=
            radius * radius);
}
// Check if this vector is inside a box, low inclusive, high exclusive
bool Vector3::inside(const Vector3 &l, const Vector3 &h) const
{
    return (x < h.x && x >= l.x) && (y < h.y && y >= l.y) &&
           (z < h.z && z >= l.z);
}

// Check if this vector is inside the led cube
bool Vector3::isValid() const
{
    return (x >= 0 && x < CUBE_LENGTH && y >= 0 && y < CUBE_LENGTH && z >= 0 && z < CUBE_LENGTH);
}

/**
 * Rotate this vector by an angle, with axis around the centroid using Rodrigues formula
 *
 * @param angle: angle in degrees
 * @param axis: axis of rotation (Axis::X, Axis::Y, Axis::Z)
 * @param center: point to rotate around (default: center of cube)
 * @return: this vector rotated
 */
Vector3 Vector3::rotate(float angle, const Vector3 &axis, const Vector3 &center /*= Vector3(4, 4, 4)*/)
{
    float rad = radians(angle);   // Convert angle to radians
    Vector3 a = axis.normalize(); // Insure axis is not greater than 1
    Vector3 v = *this - center;   // Translate vector to be relative to the origin in order to rotate

    // Rodrigues formula:  v * cos(0) + (a x v)sin(0) + a(a.v)(1 - cos(0))
    Vector3 rotated = v * cos(rad) + a.cross(v) * sin(rad) + a * a.dot(v) * (1 - cos(rad));
    return rotated + center; // Translate back
}

// Constants to used for rotations

const Vector3 Axis::X(1, 0, 0);
const Vector3 Axis::Y(0, 1, 0);
const Vector3 Axis::Z(0, 0, 1);