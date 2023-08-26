#include "Quaternion.h"
#include "Math3D.h"

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
    Vector3 n = v_.normalize();
    // Angle is in degree and is converted to radian by 2PI/360 * angle
    // Angles are divided by 2 when using quaternions so back to PI/360
    a = radians(a) / 2.0f;
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
 * @param vec: Vector3 to rotate
 * @param center: Vector3 to rotate around (default: center of cube)
 * @return Rotated Vector3
 */
Vector3 Quaternion::rotate(const Vector3 &vec, const Vector3 &center /*= Vector3(4, 4, 4)*/)
{
    Vector3 shifted = vec - center;
    Vector3 vcv = v.cross(shifted);

    return (shifted + vcv * (2 * w) + v.cross(vcv) * 2) + center;
}