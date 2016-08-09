#ifndef LGRENDER_CORE_PRIMITIVE_H
#define LGRENDER_CORE_PRIMITIVE_H

// core/primitive.h*

#include "lgrender/core/lgrender.h"
#include "lgrender/core/geometry.h"
#include "lgrender/core/diff_geometry.h"
#include "lgrender/core/shape.h"

// Primitive Declarations
class Primitive : public ReferenceCounted {
public:
    // Primitive Interface
    Primitive() : primitive_id_(next_primitive_id_++) { }
    virtual ~Primitive();
    virtual BoundingBox world_bound() const = 0;
    virtual bool canIntersect() const;
    virtual bool intersect(const Ray &r, Intersection *in) const = 0;
    virtual bool intersectP(const Ray &r) const = 0;
    virtual void refine(std::vector<Reference<Primitive> > &refined) const;
    void refineFully(std::vector<Reference<Primitive> > &refined) const;

    /*virtual const AreaLight *GetAreaLight() const = 0;
    virtual BSDF *GetBSDF(const DifferentialGeometry &dg,
        const Transform &ObjectToWorld, MemoryArena &arena) const = 0;
    virtual BSSRDF *GetBSSRDF(const DifferentialGeometry &dg,
        const Transform &ObjectToWorld, MemoryArena &arena) const = 0;*/

    // Primitive Public Data
    const uint32_t primitive_id_;
protected:
    // Primitive Protected Data
    static uint32_t next_primitive_id_;
};



// GeometricPrimitive Declarations
class GeometricPrimitive : public Primitive {
public:
    /*GeometricPrimitive(const Reference<Shape> &s,
        const Reference<Material> &m, AreaLight *a);*/

    // GeometricPrimitive Public Methods
    bool canIntersect() const;
    void refine(std::vector<Reference<Primitive> > &refined) const;
    virtual BoundingBox world_bound() const;
    virtual bool intersect(const Ray &r, Intersection *isect) const;
    virtual bool intersectP(const Ray &r) const;

    /*const AreaLight *GetAreaLight() const;
    BSDF *GetBSDF(const DifferentialGeometry &dg,
                  const Transform &ObjectToWorld, MemoryArena &arena) const;
    BSSRDF *GetBSSRDF(const DifferentialGeometry &dg,
                      const Transform &ObjectToWorld, MemoryArena &arena) const;*/
private:
    // GeometricPrimitive Private Data
    Reference<Shape> shape;
    /*Reference<Material> material;
    AreaLight *areaLight;*/
};



// TransformedPrimitive Declarations
class TransformedPrimitive : public Primitive {
public:
    // TransformedPrimitive Public Methods
    TransformedPrimitive(Reference<Primitive> &prim,
                         const AnimatedTransform &w2p)
        : primitive(prim), WorldToPrimitive(w2p) { }
    bool intersect(const Ray &r, Intersection *in) const;
    bool intersectP(const Ray &r) const;
   
    BoundingBox world_bound() const {
        return WorldToPrimitive.MotionBounds(primitive->world_bound(), true);

        /*const AreaLight *GetAreaLight() const { return NULL; }
        BSDF *GetBSDF(const DifferentialGeometry &dg,
            const Transform &ObjectToWorld, MemoryArena &arena) const {
            return NULL;
        }
        BSSRDF *GetBSSRDF(const DifferentialGeometry &dg,
            const Transform &ObjectToWorld, MemoryArena &arena) const {
            return NULL;
        }*/
    }
private:
    // TransformedPrimitive Private Data
    Reference<Primitive> primitive;
    const AnimatedTransform WorldToPrimitive;
};



// Aggregate Declarations
class Aggregate : public Primitive {
public:
    // Aggregate Public Methods
    /*const AreaLight *GetAreaLight() const;
    BSDF *GetBSDF(const DifferentialGeometry &dg,
                  const Transform &, MemoryArena &) const;
    BSSRDF *GetBSSRDF(const DifferentialGeometry &dg,
                  const Transform &, MemoryArena &) const;*/
};



#endif // LGRENDER_CORE_PRIMITIVE_H
