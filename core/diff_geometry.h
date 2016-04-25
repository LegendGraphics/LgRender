
#ifndef LGRENDER_CORE_DIFF_GEOMETRY_H
#define LGRENDER_CORE_DIFF_GEOMETRY_H

#include "geometry.h"


struct DifferentialGeometry 
{
    DifferentialGeometry() 
    {
        _u = _v = _dudx = _dvdx = _dudy = _dvdy = 0.f;
        _shape = nullptr;
    }

    DifferentialGeometry(const Point &p, const Vector &dpdu,
        const Vector &dpdv, const Normal &dndu,
        const Normal &dndv, float u, float v,
        const Shape *shape);
   // void ComputeDifferentials(const RayDifferential &r) const;


    Point _p;
    Normal _nn;
    float _u, _v;
    const Shape* _shape;
    Vector _dpdu, _dpdv;
    Normal _dndu, _dndv;
    mutable Vector _dpdx, _dpdy;
    mutable float _dudx, _dvdx, _dudy, _dvdy;
};



#endif // LGRENDER_CORE_DIFF_GEOMETRY_H
