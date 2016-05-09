

#ifndef LGRENDER_SHAPES_CYLINDER_H
#define LGRENDER_SHAPES_CYLINDER_H

#include "shape.h"

class Cylinder : public Shape
{
public:
    Cylinder(const Transform *o2w, const Transform *w2o, bool ro, float rad,
        float z_min, float z_max, float phi_max);
    BoundingBox object_bound() const;
    bool intersect(const Ray &ray, float *t_hit, float *ray_epsilon,
        DifferentialGeometry *dg) const;
    bool intersectP(const Ray &ray) const;
    float area() const;

    //Point Sample(float u1, float u2, Normal *Ns) const;
protected:
    float radius_, z_min_, z_max_, phi_max_;
};


//Cylinder *CreateCylinderShape(const Transform *o2w, const Transform *w2o,
//    bool reverseOrientation, const ParamSet &params);

#endif // LGRENDER_SHAPES_CYLINDER_H
