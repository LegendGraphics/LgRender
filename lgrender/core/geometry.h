#ifndef LGRENDER_CORE_GEOMETRY_H
#define LGRENDER_CORE_GEOMETRY_H

#include <cmath>
#include "types.h"

class Triple {
public:
    // Triple Public Methods
    Triple();
    Triple(float x, float y, float z);
    Triple(const Triple &t);

    float& x();
    float& y();
    float& z();

    const float& x() const;
    const float& y() const;
    const float& z() const;

    bool hasNaNs() const;

    Triple operator+(const Triple &t) const;   
    Triple operator-(const Triple &t) const;   
    Triple operator*(float f) const;   
    Triple operator/(float f) const;
    
    void operator+=(const Triple &t);
    void operator-=(const Triple &t);
    void operator*=(float f);
    void operator/=(float f);

    Triple operator-() const;

    void operator=(const Triple &t);
    bool operator==(const Triple &t) const;
    bool operator!=(const Triple &t) const;

    float operator[](int i) const;
    float &operator[](int i);

    float length_squared() const;
    float length() const;
    
    float dot(const Triple& t) const;
    Triple cross(const Triple& t) const;
    Triple normalize() const;

private:
    // Triple Public Data
    float _x, _y, _z;
};


typedef Triple Vector;
typedef Triple Point;
typedef Triple Normal;


struct Ray
{
    Ray();
    // other constructors
    Point operator()(float t) const;
    bool hasNaNs() const;

    Point   _o;
    Vector  _d;
    float   _tmin, _tmax;
    float   _time;
    int     _depth;
};


class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(const Point &p);
    BoundingBox(const Point &p1, const Point &p2);

    bool operator==(const BoundingBox &bbox) const;
    bool operator!=(const BoundingBox &bbox) const;

    // other operations
private:
    Point _pmin, _pmax;
};


#endif // LGRENDER_CORE_GEOMETRY_H
