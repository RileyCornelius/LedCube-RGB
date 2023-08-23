
#include "Vector3.h"
#include "Math3D.h"

/*------------------------------------------------------------------------------
 * Vector3 CLASS
 *----------------------------------------------------------------------------*/
const Vector3 Vector3::Y(0, 1, 0);
const Vector3 Vector3::X(1, 0, 0);
const Vector3 Vector3::Z(0, 0, 1);

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f){};
Vector3::Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_){};
Vector3::Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z){};

// add, subtract (operator +, -, +=, -=)
Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}
Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}
Vector3 &Vector3::operator+=(const Vector3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
Vector3 &Vector3::operator-=(const Vector3 &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}
// negative (operator -)
Vector3 Vector3::operator-() const { return Vector3(-x, -y, -z); }

// multiply, divide by scalar (operator *, /, *=, /=)
Vector3 Vector3::operator*(float s) const
{
    return Vector3(x * s, y * s, z * s);
}
Vector3 Vector3::operator/(float s) const
{
    return Vector3(x / s, y / s, z / s);
}
Vector3 &Vector3::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}
Vector3 &Vector3::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

// cross product (operator *, *=)
Vector3 Vector3::cross(const Vector3 &v) const
{
    return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}
Vector3 Vector3::operator*(const Vector3 &v) const { return cross(v); }
Vector3 &Vector3::operator*=(const Vector3 &v) { return *this = cross(v); }

// dot product (operator %)
float Vector3::dot(const Vector3 &v) const
{
    return x * v.x + y * v.y + z * v.z;
}
float Vector3::operator%(const Vector3 &v) const { return dot(v); }

// normalize
Vector3 &Vector3::normalize() { return *this /= magnitude(); }
Vector3 Vector3::normalized() const { return *this / magnitude(); }
// magnitude
float Vector3::magnitude() const { return sqrt(norm()); }
float Vector3::norm() const { return x * x + y * y + z * z; }

// Test if this vector (point) is within a spherical radius of v inclusive
bool Vector3::inside(const Vector3 &v, float radius) const
{
    return ((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y) +
                (v.z - z) * (v.z - z) <=
            radius * radius);
}
// Test if this vector (point) is inside a box, low inclusive, high exclusive
bool Vector3::inside(const Vector3 &l, const Vector3 &h) const
{
    return (x < h.x && x >= l.x) && (y < h.y && y >= l.y) &&
           (z < h.z && z >= l.z);
}

/**
 * Rotate this vector by an angle, with axis around the centroid using Rodrigues formula
 *
 * @param angle: angle in degrees
 * @param axis: axis of rotation
 * @param center: point to rotate around (default: center of cube)
 * @return: this vector rotated
 */
Vector3 Vector3::rotate(float angle, const Vector3 &axis, const Vector3 &center /*= Vector3(4, 4, 4)*/)
{
    // Angle is in degree and is converted to radian by multiplying by PI/180
    float rad = angle * M_PI / 180;
    // shift the vector to rotate around the center instead of the origin
    Vector3 shifted = *this - center;
    // normalize this axis to get n hat
    Vector3 n = axis.normalized();
    // (1-cos(0))(v.n)n + cos(0)v + sin(0)(n x v) + c
    return (n * shifted.dot(n) * (1 - cosf(rad)) + shifted * cosf(rad) + n.cross(shifted) * sinf(rad)) + center;
}
