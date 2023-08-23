#include "Math3D.h"

#include <math.h>
#include <stdint.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

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

/*------------------------------------------------------------------------------
 * Quaternion CLASS
 *----------------------------------------------------------------------------*/
Quaternion::Quaternion() : w(0.0f), v(Vector3(0.0, 0.0, 0.0)) {}
Quaternion::Quaternion(const Quaternion &q) : w(q.w), v(q.v) {}
// Make a unit quaternion from an axis as a vector and an angle
// Theoretically the magnitude of v_ can be used to specify the rotation
// Using an angle makes things more convenient
Quaternion::Quaternion(float a, const Vector3 &v_)
{
  // normalize v to get n hat (unit vector with length = 1)
  Vector3 n = v_.normalized();
  // Angle is in degree and is converted to radian by 2PI/360 * angle
  // Angles are divided by 2 when using quaternions so back to PI/360
  a = a * M_PI / 360;
  // Multiply n hat by sin(0) (scale n, but no directional change)
  // So v still represents the axis of rotation, but changed magnitude
  v = n * sinf(a);
  // Store cos(0) in the scalar part of the quaternion, results in a
  // unit quaternion => w^2+x^2+y^2+z^2=1, since sin(x)^2+cos(x)^2=1
  // Magnitude is always one. To stack rotations multiply unit
  // quaternions together and keep magnitude 1. So multiple rotations
  // without changing size of an object
  w = cosf(a);
}

// add, subtract (operator +, -, +=, -=)
Quaternion Quaternion::operator+(const Quaternion &q) const
{
  return Quaternion(w + q.w, v + q.v);
}
Quaternion Quaternion::operator-(const Quaternion &q) const
{
  return Quaternion(w - q.w, v - q.v);
}
Quaternion &Quaternion::operator+=(const Quaternion &q)
{
  w += q.w;
  v += q.v;
  return *this;
}
Quaternion &Quaternion::operator-=(const Quaternion &q)
{
  w -= q.w;
  v -= q.v;
  return *this;
}

// multiply, divide by scalar (operator *, /, *=, /=)
Quaternion Quaternion::operator*(float s) const
{
  return Quaternion(w * s, v * s);
}
Quaternion Quaternion::operator/(float s) const
{
  return Quaternion(w / s, v / s);
}
Quaternion &Quaternion::operator*=(float s)
{
  w *= s;
  v *= s;
  return *this;
}
Quaternion &Quaternion::operator/=(float s)
{
  w /= s;
  v /= s;
  return *this;
}

// multiply quaternions (operator *, /, *=)
Quaternion Quaternion::operator*(const Quaternion &q) const
{
  Quaternion r;
  r.w = w * q.w - v.dot(q.v);
  r.v = v * q.w + q.v * w + v.cross(q.v);
  return r;
}
Quaternion Quaternion::operator/(const Quaternion &q) const
{
  return *this * q.inversed();
}
Quaternion &Quaternion::operator*=(const Quaternion &q)
{
  return *this = operator*(q);
}

// dot product (operator %)
float Quaternion::dot(const Quaternion &q) const
{
  return w * q.w + v.dot(q.v);
}
float Quaternion::operator%(const Quaternion &q) const { return dot(q); }

// inverse
Quaternion &Quaternion::inverse()
{
  conjugate();
  return *this *= 1 / norm();
}
Quaternion Quaternion::inversed() const { return conjugated() * (1 / norm()); }
// conjugate
Quaternion &Quaternion::conjugate()
{
  v = -v;
  return *this;
}
Quaternion Quaternion::conjugated() const { return Quaternion(w, -v); }
// normalize
Quaternion &Quaternion::normalize() { return *this /= magnitude(); }
Quaternion Quaternion::normalized() const { return *this / magnitude(); }
// magnitude
float Quaternion::magnitude() const { return sqrt(norm()); }
float Quaternion::norm() const { return w * w + v.dot(v); }

/**
 * Rotate vec by this quaternion holding an angle and axis around the center
 * parm vec: Vector3 to rotate
 * parm center: Vector3 to rotate around (default: center of cube)
 * return: Vector3 rotated
 */
Vector3 Quaternion::rotate(const Vector3 &vec, const Vector3 &center /*= Vector3(4, 4, 4)*/)
{
  Vector3 shifted = vec - center;
  Vector3 vcv = v.cross(shifted);

  return (shifted + vcv * (2 * w) + v.cross(vcv) * 2) + center;
}