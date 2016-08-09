

#include "lgrender/core/primitive.h"


// Primitive Method Definitions
uint32_t Primitive::next_primitive_id_ = 1;
Primitive::~Primitive() { }

bool Primitive::canIntersect() const 
{
    return true;
}



void Primitive::refine(std::vector<Reference<Primitive> > &refined) const 
{
    Severe("Unimplemented Primitive::refine() method called!");
}


void Primitive::refineFully(std::vector<Reference<Primitive> > &refined) const 
{
    std::vector<Reference<Primitive> > todo;
    todo.push_back(const_cast<Primitive *>(this));
    while (todo.size()) {
        // refine last primitive in todo list
        Reference<Primitive> prim = todo.back();
        todo.pop_back();
        if (prim->canIntersect())
            refined.push_back(prim);
        else
            prim->refine(todo);
    }
}


//const AreaLight *Aggregate::GetAreaLight() const {
//    Severe("Aggregate::GetAreaLight() method"
//         "called; should have gone to GeometricPrimitive");
//    return NULL;
//}
//
//
//BSDF *Aggregate::GetBSDF(const DifferentialGeometry &,
//        const Transform &, MemoryArena &) const {
//    Severe("Aggregate::GetBSDF() method"
//        "called; should have gone to GeometricPrimitive");
//    return NULL;
//}
//
//
//BSSRDF *Aggregate::GetBSSRDF(const DifferentialGeometry &,
//        const Transform &, MemoryArena &) const {
//    Severe("Aggregate::GetBSSRDF() method"
//        "called; should have gone to GeometricPrimitive");
//    return NULL;
//}



// TransformedPrimitive Method Definitions
bool TransformedPrimitive::intersect(const Ray &r,
                                     Intersection *isect) const {
    Transform w2p;
    WorldToPrimitive.Interpolate(r._time, &w2p);
    Ray ray = w2p(r);
    if (!primitive->intersect(ray, isect))
        return false;
    r._tmax = ray._tmax;
    isect->primitive_id_ = primitive_id_;
    if (!w2p.IsIdentity()) {
        // Compute world-to-object transformation for instance
        isect->WorldToObject = isect->WorldToObject * w2p;
        isect->ObjectToWorld = Inverse(isect->WorldToObject);

        // Transform instance's differential geometry to world space
        Transform PrimitiveToWorld = Inverse(w2p);
        isect->dg.p = PrimitiveToWorld(isect->dg.p);
        isect->dg.nn = Normalize(PrimitiveToWorld(isect->dg.nn));
        isect->dg.dpdu = PrimitiveToWorld(isect->dg.dpdu);
        isect->dg.dpdv = PrimitiveToWorld(isect->dg.dpdv);
        isect->dg.dndu = PrimitiveToWorld(isect->dg.dndu);
        isect->dg.dndv = PrimitiveToWorld(isect->dg.dndv);
    }
    return true;
}


bool TransformedPrimitive::intersectP(const Ray &r) const {
    return primitive->intersectP(WorldToPrimitive(r));
}



// GeometricPrimitive Method Definitions
BoundingBox GeometricPrimitive::world_bound() const {
    return shape->world_bound();
}


bool GeometricPrimitive::intersectP(const Ray &r) const {
    return shape->intersectP(r);
}


bool GeometricPrimitive::canIntersect() const {
    return shape->canIntersect();
}


void GeometricPrimitive::
        refine(std::vector<Reference<Primitive> > &refined)
        const {
    std::vector<Reference<Shape> > r;
    shape->refine(r);
    for (uint32_t i = 0; i < r.size(); ++i) {
        /*GeometricPrimitive *gp = new GeometricPrimitive(r[i],
               material, areaLight);
        refined.push_back(gp);*/
    }
}


GeometricPrimitive::GeometricPrimitive(const Reference<Shape> &s,
        const Reference<Material> &m, AreaLight *a)
    : shape(s), material(m), areaLight(a) {
}


bool GeometricPrimitive::intersect(const Ray &r,
                                   Intersection *isect) const {
    float thit, rayEpsilon;
    if (!shape->intersect(r, &thit, &rayEpsilon, &isect->dg))
        return false;
    isect->primitive = this;
    isect->WorldToObject = *shape->WorldToObject;
    isect->ObjectToWorld = *shape->ObjectToWorld;
    isect->shapeId = shape->shapeId;
    isect->primitive_id_ = primitive_id_;
    isect->rayEpsilon = rayEpsilon;
    r._tmax = thit;
    return true;
}


//const AreaLight *GeometricPrimitive::GetAreaLight() const {
//    return areaLight;
//}
//
//
//BSDF *GeometricPrimitive::GetBSDF(const DifferentialGeometry &dg,
//                                  const Transform &ObjectToWorld,
//                                  MemoryArena &arena) const {
//    DifferentialGeometry dgs;
//    shape->GetShadingGeometry(ObjectToWorld, dg, &dgs);
//    return material->GetBSDF(dg, dgs, arena);
//}
//
//
//BSSRDF *GeometricPrimitive::GetBSSRDF(const DifferentialGeometry &dg,
//                                  const Transform &ObjectToWorld,
//                                  MemoryArena &arena) const {
//    DifferentialGeometry dgs;
//    shape->GetShadingGeometry(ObjectToWorld, dg, &dgs);
//    return material->GetBSSRDF(dg, dgs, arena);
//}
//

