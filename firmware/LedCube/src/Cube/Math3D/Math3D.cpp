#include "Math3D.h"

float randomFloat(float max)
{
    return randomFloat(0, max);
}

float randomFloat(float min, float max)
{
    return min + (max - min) * (float)random() / RAND_MAX;
}

Vector3 randomVector(const Vector3 &max /*= Vector3(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH)*/)
{
    return randomVector(Vector3(0, 0, 0), max);
}

Vector3 randomVector(const Vector3 &min, const Vector3 &max)
{
    float x = random(min.x * 1000, max.x * 1000) / 1000.0;
    float y = random(min.y * 1000, max.y * 1000) / 1000.0;
    float z = random(min.z * 1000, max.z * 1000) / 1000.0;
    return Vector3(x, y, z);
}

Vector3 randomVector(const Vector3 &center, float radius)
{
    Vector3 sphere;
    do
    {
        sphere = randomVector(center - Vector3(radius, radius, radius), center + Vector3(radius, radius, radius));
    } while (sphere.inside(center, radius));

    return sphere;
}
