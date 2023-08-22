#include <Point.h>

Point rotateUsingAxis(const Point &c, const Point &p, const Angles &a)
{
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