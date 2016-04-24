
#ifndef LGRENDER_CORE_SHAPE_H
#define LGRENDER_CORE_SHAPE_H

#include <vector>

#include "lgrender.h"
#include "geometry.h"
#include "transform.h"
#include "memory.h"

class Shape : public ReferenceCounted 
{
public:
    Shape(const Transform *o2w, const Transform *w2o, bool ro);
    virtual ~Shape();
    virtual BoundingBox ObjectBound() const = 0;
    virtual BoundingBox WorldBound() const;
    virtual bool CanIntersect() const;
    virtual void Refine(std::vector<Reference<Shape> > &refined) const;
    virtual bool Intersect(const Ray &ray, float *tHit,
                           float *rayEpsilon, DifferentialGeometry *dg) const;
    virtual bool IntersectP(const Ray &ray) const;
    virtual void GetShadingGeometry(const Transform &obj2world,
            const DifferentialGeometry &dg,
            DifferentialGeometry *dgShading) const {
        *dgShading = dg;
    }
    virtual float Area() const;
    virtual Point Sample(float u1, float u2, Normal *Ns) const {
        Severe("Unimplemented Shape::Sample() method called");
        return Point();
    }
    virtual float Pdf(const Point &Pshape) const {
        return 1.f / Area();
    }
    virtual Point Sample(const Point &P, float u1, float u2,
                         Normal *Ns) const {
        return Sample(u1, u2, Ns);
    }
    virtual float Pdf(const Point &p, const Vector &wi) const;

    // Shape Public Data
    const Transform *ObjectToWorld, *WorldToObject;
    const bool ReverseOrientation, TransformSwapsHandedness;
    const unsigned int shapeId;
    static unsigned int nextshapeId;
};



#endif // LGRENDER_CORE_SHAPE_H
