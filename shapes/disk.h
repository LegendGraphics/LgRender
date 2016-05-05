
#ifndef LGRENDER_SHAPES_DISK_H
#define LGRENDER_SHAPES_DISK_H

#include "shape.h"

class Disk : public Shape 
{
public:

    Disk(const Transform *o2w, const Transform *w2o, bool ro, float height,
        float radius, float inner_radius, float phi_max);
    BoundingBox object_bound() const;
    bool intersect(const Ray &ray, float *t_hit, float *ray_epsilon,
        DifferentialGeometry *dg) const;
    bool intersectP(const Ray &ray) const;
    float area() const;
  //  Point Sample(float u1, float u2, Normal *Ns) const;

private:
    float height_, radius_, inner_radius_, phi_max_;
};


//Disk *CreateDiskShape(const Transform *o2w, const Transform *w2o,
//    bool reverseOrientation, const ParamSet &params);

#endif // LGRENDER_SHAPES_DISK_H
