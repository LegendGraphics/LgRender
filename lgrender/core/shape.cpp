
#include "shape.h"


unsigned int Shape::next_shape_id_ = 1;

Shape::~Shape() 
{
}


Shape::Shape(const Transform *o2w, const Transform *w2o, bool ro)
    : object2world_(o2w), world2object_(w2o),
      shape_id_(next_shape_id_++) 
{
    // Update shape creation statistics
   // LGRENDER_CREATED_SHAPE(this);
}




BoundingBox Shape::world_bound() const 
{
    return (*object2world_)(object_bound());
}


bool Shape::canIntersect() const 
{
    return true;
}


void Shape::refine(std::vector<Reference<Shape> > &refined) const 
{
    Severe("Unimplemented Shape::Refine() method called");
}


bool Shape::intersect(const Ray &ray, float *t_hit, float *ray_epsilon,
                      DifferentialGeometry *dg) const 
{
    Severe("Unimplemented Shape::Intersect() method called");
    return false;
}


bool Shape::intersectP(const Ray &ray) const 
{
    Severe("Unimplemented Shape::IntersectP() method called");
    return false;
}


float Shape::area() const 
{
    Severe("Unimplemented Shape::Area() method called");
    return 0.f;
}


//float Shape::Pdf(const Point &p, const Vector &wi) const {
//    // Intersect sample ray with area light geometry
//    DifferentialGeometry dgLight;
//    Ray ray(p, wi, 1e-3f);
//    ray.depth = -1; // temporary hack to ignore alpha mask
//    float thit, rayEpsilon;
//    if (!Intersect(ray, &thit, &rayEpsilon, &dgLight)) return 0.;
//
//    // Convert light sample weight to solid angle measure
//    float pdf = DistanceSquared(p, ray(thit)) /
//                (AbsDot(dgLight.nn, -wi) * Area());
//    if (isinf(pdf)) pdf = 0.f;
//    return pdf;
//}


