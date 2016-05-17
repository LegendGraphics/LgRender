
#ifndef LGRENDER_SHAPES_SPHERE_H
#define LGRENDER_SHAPES_SPHERE_H

#include "lgrender/core/shape.h"

class Sphere : public Shape 
{
public:
    Sphere(const Transform *o2w, const Transform *w2o, bool ro, float rad,
           float z_min, float z_max, float phi_max);
    BoundingBox object_bound() const;
    bool intersect(const Ray &ray, float *t_hit, float *ray_epsilon,
        DifferentialGeometry *dg) const;
    bool intersectP(const Ray &ray) const;
    float area() const;
    /*Point Sample(float u1, float u2, Normal *ns) const;
    Point Sample(const Point &p, float u1, float u2, Normal *ns) const;
    float Pdf(const Point &p, const Vector &wi) const;*/

private:
    float radius_;
    float phi_max_;
    float z_min_, z_max_;
    float theta_min_, theta_max_;
};


//Sphere *CreateSphereShape(const Transform *o2w, const Transform *w2o,
//        bool reverseOrientation, const ParamSet &params);

#endif // LGRENDER_SHAPES_SPHERE_H
