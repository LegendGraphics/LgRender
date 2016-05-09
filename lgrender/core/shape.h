
#ifndef LGRENDER_CORE_SHAPE_H
#define LGRENDER_CORE_SHAPE_H

#include <vector>

#include "lgrender.h"
#include "geometry.h"
#include "diff_geometry.h"
#include "transform.h"
#include "memory.h"

class Shape : public ReferenceCounted 
{
public:
    Shape(const Transform *o2w, const Transform *w2o, bool ro = false);
    virtual ~Shape();
    virtual BoundingBox object_bound() const = 0;
    virtual BoundingBox world_bound() const;
    virtual bool canIntersect() const;
    virtual void refine(std::vector<Reference<Shape> > &refined) const;
    virtual bool intersect(const Ray &ray, float *t_hit,
                           float *ray_epsilon, DifferentialGeometry *dg) const;
    virtual bool intersectP(const Ray &ray) const;
    virtual float area() const;


    /*virtual void GetShadingGeometry(const Transform &obj2world,
            const DifferentialGeometry &dg,
            DifferentialGeometry *dgShading) const {
        *dgShading = dg;
    }*/
    
    /*virtual Point Sample(float u1, float u2, Normal *Ns) const {
        Severe("Unimplemented Shape::Sample() method called");
        return Point();
    }*/

    /*virtual float Pdf(const Point &Pshape) const {
        return 1.f / Area();
    }
    virtual Point Sample(const Point &P, float u1, float u2,
                         Normal *Ns) const {
        return Sample(u1, u2, Ns);
    }
    virtual float Pdf(const Point &p, const Vector &wi) const;*/

private:
    const Transform *object2world_, *world2object_;
    //const bool ReverseOrientation, TransformSwapsHandedness;
    const unsigned int shape_id_;
    static unsigned int next_shape_id_;
};



#endif // LGRENDER_CORE_SHAPE_H
