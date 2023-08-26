#pragma once

#include <Arduino.h>
#include <math.h>

#include "Point.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Particle.h"

float randomFloat(float max);
float randomFloat(float min, float max);
Vector3 randomVector(const Vector3 &max = Vector3(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH));
Vector3 randomVector(const Vector3 &min, const Vector3 &max);
Vector3 randomVector(const Vector3 &center, float radius);
