#include <Arduino.h>

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

    // negative (operator -)
    Point operator-() const { return Point(-x, -y, -z); }
};