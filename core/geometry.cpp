
#include <cmath>

#include "geometry.h"

Triple::Triple()
{
    _x = _y = _z = 0.f;
}

Triple::Triple(float x, float y, float z)
{
    _x = x; _y = y; _z = z;
}

Triple::Triple(const Triple &t)
{
    _x = t._x; _y = t._y; _z = t._z;
}

bool Triple::hasNaNs() const 
{
    return isnan(_x) || isnan(_y) || isnan(_z);
}

Triple Triple::operator+(const Triple &t) const
{
    LG_ASSERT(!t.hasNaNs());
    return Triple(_x + t._x, _y + t._y, _z + t._z);
}

Triple Triple::operator-(const Triple &t) const
{
    LG_ASSERT(!t.hasNaNs());
    return Triple(_x - t._x, _y - t._y, _z - t._z);
}
Triple Triple::operator*(float f) const
{
    return Triple(_x*f, _y*f, _z*f);
}
Triple Triple::operator/(float f) const
{
    return Triple(_x/f, _y/f, _z/f);
}

void Triple::operator+=(const Triple &t)
{
    LG_ASSERT(!t.hasNaNs());
    _x += t._x; _y += t._y; _z += t._z;
}

void Triple::operator-=(const Triple &t)
{
    LG_ASSERT(!t.hasNaNs());
    _x -= t._x; _y -= t._y; _z -= t._z;
}

void Triple::operator*=(float f)
{
    _x *= f; _y *= f; _z *= f;
}

void Triple::operator/=(float f)
{
    _x /= f; _y /= f; _z /= f;
}


Triple Triple::operator-() const
{
    return Triple(-_x, -_y, -_z);
}

void Triple::operator=(const Triple &t)
{
    LG_ASSERT(!t.hasNaNs());
    _x = t._x; _y = t._y; _z = t._z;
}

bool Triple::operator==(const Triple &t) const
{
    LG_ASSERT(!t.hasNaNs());
    return (_x == t._x) && (_y == t._y) && (_z == t._z);
}

bool Triple::operator!=(const Triple &t) const
{
    LG_ASSERT(!t.hasNaNs());
    return (_x != t._x) || (_y != t._y) || (_z != t._z);
}

float Triple::operator[](int i) const
{
    LG_ASSERT(i >= 0 && i <= 2);
    return (&_x)[i];
}

float& Triple::operator[](int i)
{
    LG_ASSERT(i >= 0 && i <= 2);
    return (&_x)[i];
}

float& Triple::x()
{
    return _x;
}

float& Triple::y()
{
    return _y;
}

float& Triple::z()
{
    return _z;
}

const float& Triple::x() const
{
    return _x;
}

const float& Triple::y() const
{
    return _y;
}

const float& Triple::z() const
{
    return _z;
}

float Triple::length_squared() const
{
    return _x*_x + _y*_y + _z*_z;
}

float Triple::length() const
{
    return sqrt(_x*_x + _y*_y + _z*_z);
}

float Triple::dot(const Triple& t) const
{
    LG_ASSERT(!t.hasNaNs());
    return (_x * t._x + _y * t._y + _z * t._z);
}

Triple Triple::cross(const Triple& t) const
{
    LG_ASSERT(!t.hasNaNs());
    return Triple((_y * t._z) - (_z * t._y),
        (_z * t._x) - (_x * t._z),
        (_x * t._y) - (_y * t._x));
}

Triple Triple::normalize() const
{
    float len = length();
    return Triple(_x / len, _y / len, _z / len);
}


Ray::Ray()
    : _tmin(0.f), _tmax(INFINITY), _time(0.f), _depth(0)
{}

Point Ray::operator()(float t) const
{
    return _o + _d * t;
}
bool Ray::hasNaNs() const
{
    return isnan(_tmin) || isnan(_tmax) || _o.hasNaNs() || _d.hasNaNs();
}


Point& Ray::o()
{
    return _o;
}

Vector& Ray::d()
{
    return _d;
}

const Point& Ray::o() const
{
    return _o;
}

const Vector& Ray::d() const
{
    return _d;
}


BoundingBox::BoundingBox()
{
    _pmax = Point(INFINITY, INFINITY, INFINITY);
    _pmin = Point(-INFINITY, -INFINITY, -INFINITY);
}

BoundingBox::BoundingBox(const Point &p)
    :_pmin(p), _pmax(p)
{}

BoundingBox::BoundingBox(const Point &p1, const Point &p2)
{
    _pmin = Point(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
    _pmax = Point(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
}
 
bool BoundingBox::operator==(const BoundingBox &bbox) const
{
    return (_pmin == bbox._pmin) && (_pmax == bbox._pmax);
}

bool BoundingBox::operator!=(const BoundingBox &bbox) const
{
    return (_pmin != bbox._pmin) || (_pmax != bbox._pmax);
}


