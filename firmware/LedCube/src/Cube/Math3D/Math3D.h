#pragma once

#include <Arduino.h>
#include <math.h>

#include "Point.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Particle.h"

float mapf(float x, float in_min, float in_max, float out_min, float out_max);
float randomFloat(float max);
float randomFloat(float min, float max);
Vector3 randomVector(const Vector3 &max = Vector3(CUBE_SIZE_M1, CUBE_SIZE_M1, CUBE_SIZE_M1));
Vector3 randomVector(const Vector3 &min, const Vector3 &max);
Vector3 randomVector(const Vector3 &center, float radius);

