#include "Point.h"
#include "config.h"

/*---------------------------------------------------------------------------------------
 * POINT STRUCT - 3D Point in Cube
 *-------------------------------------------------------------------------------------*/

// Constructors
Point::Point() : x(0), y(0), z(0) {}
Point::Point(uint8_t X, uint8_t Y, uint8_t Z) : x(X), y(Y), z(Z) {}
Point::Point(const Point &p) : x(p.x), y(p.y), z(p.z) {}
Point::Point(const Vector3 &v)
{
    x = round(v.x);
    y = round(v.y);
    z = round(v.z);
}

// set this point equal to another
Point Point::operator=(const Point &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}

// compare two points
bool Point::operator==(const Point &p)
{
    return (x == p.x && y == p.y && z == p.z);
}

// add two points together
Point Point::operator+(const Point &p) const
{
    return Point(x + p.x, y + p.y, z + p.z);
}

// subtract two points
Point Point::operator-(const Point &p) const
{
    return Point(x - p.x, y - p.y, z - p.z);
}

// add to this point
Point &Point::operator+=(const Point &p)
{
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
}

// subtract from this point
Point &Point::operator-=(const Point &p)
{
    x -= p.x;
    y -= p.y;
    z -= p.z;
    return *this;
}

// multiply a point by a scalar
Point Point::operator*(const float &s) const
{
    return Point(x * s, y * s, z * s);
}

// divide a point by a scalar
Point Point::operator/(const float &s) const
{
    return Point(x / s, y / s, z / s);
}

// multiply this point by a scalar
Point &Point::operator*=(const float &s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

// divide this point by a scalar
Point &Point::operator/=(const float &s)
{
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

// negative (operator -)
Point Point::operator-() const
{
    return Point(-x, -y, -z);
}

bool Point::isValid()
{
    return (x >= 0 && x < CUBE_LENGTH && y >= 0 && y < CUBE_LENGTH && z >= 0 && z < CUBE_LENGTH);
}

/**
 * @brief Rotate a point around a center point with angles
 *
 * @param c Point center
 * @param a Angles to rotate
 * @return Point rotated
 */
Point Point::rotate(const Point &c, Angles a)
{
    Point p = *this;
    float dx = p.x - c.x, dy = p.y - c.y, dz = p.z - c.z;

    return Point(
        round(
            ((cos(a.y) * cos(a.z)) * dx +
             (-cos(a.x) * sin(a.z) + sin(a.x) * sin(a.y) * cos(a.z)) * dy +
             (sin(a.x) * sin(a.z) + cos(a.x) * sin(a.y) * cos(a.z)) * dz) +
            c.x),
        round(
            ((cos(a.y) * sin(a.z)) * dx +
             (cos(a.x) * cos(a.z) + sin(a.x) * sin(a.y) * sin(a.z)) * dy +
             (-sin(a.x) * cos(a.z) + cos(a.x) * sin(a.y) * sin(a.z)) * dz) +
            c.y),
        round(((-sin(a.y)) * dx + (sin(a.x) * cos(a.y)) * dy +
               (cos(a.x) * cos(a.y)) * dz) +
              c.z));
}

/*---------------------------------------------------------------------------------------
 * Angles STRUCT - Rotate in 3D
 *-------------------------------------------------------------------------------------*/

Angles::Angles(float degreeX, float degreeY, float degreeZ)
{
    x = deg2rad(degreeX);
    y = deg2rad(degreeY);
    z = deg2rad(degreeZ);
}