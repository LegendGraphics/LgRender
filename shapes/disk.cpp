
#include "disk.h"

Disk::Disk(const Transform *o2w, const Transform *w2o, bool ro,
    float height_, float radius_, float inner_radius, float phi_max)
    : Shape(o2w, w2o, ro) 
{
    height_ = height_;
    radius_ = radius_;
    inner_radius_ = inner_radius;
    phi_max_ = radians(clamp(phi_max, 0.0f, 360.0f));
}


BoundingBox Disk::object_bound() const 
{
    return BoundingBox(Point(-radius_, -radius_, height_),
        Point(radius_, radius_, height_));
}


bool Disk::intersect(const Ray &r, float *t_hit, float *ray_epsilon,
    DifferentialGeometry *dg) const {
    // Transform _Ray_ to object space
    Ray ray;
    (*world2object_)(r, &ray);

    // Compute plane intersection for disk
    if (fabsf(ray._d.z()) < 1e-7) return false;
    float thit = (height_ - ray._o.z()) / ray._d.z();
    if (thit < ray._tmin || thit > ray._tmax)
        return false;

    // See if hit point is inside disk radii and $\phimax$
    Point phit = ray(thit);
    float dist2 = phit.x() * phit.x() + phit.y() * phit.y();
    if (dist2 > radius_ * radius_ || dist2 < inner_radius_ * inner_radius_)
        return false;

    // Test disk $\phi$ value against $\phimax$
    float phi = atan2f(phit.y(), phit.x());
    if (phi < 0) phi += 2. * M_PI;
    if (phi > phi_max_)
        return false;

    // Find parametric representation of disk hit
    float u = phi / phi_max_;
    float R = sqrtf(dist2);
    float oneMinusV = ((R - inner_radius_) /
        (radius_ - inner_radius_));
    float v = 1.f - oneMinusV;
    Vector dpdu(-phi_max_ * phit.y(), phi_max_ * phit.x(), 0.);
    Vector dpdv(phit.x(), phit.y(), 0.);
    dpdv *= (inner_radius_ - radius_) / R;
    Normal dndu(0, 0, 0), dndv(0, 0, 0);

    // Initialize _DifferentialGeometry_ from parametric information
    const Transform &o2w = *object2world_;
    *dg = DifferentialGeometry(o2w(phit), o2w(dpdu), o2w(dpdv),
        o2w(dndu), o2w(dndv), u, v, this);

    // Update _tHit_ for quadric intersection
    *t_hit = thit;

    // Compute _rayEpsilon_ for quadric intersection
    *ray_epsilon = 5e-4f * *t_hit;
    return true;
}


bool Disk::intersectP(const Ray &r) const {
    // Transform _Ray_ to object space
    Ray ray;
    (*world2object_)(r, &ray);

    // Compute plane intersection for disk
    if (fabsf(ray._d.z()) < 1e-7) return false;
    float thit = (height_ - ray._o.z()) / ray._d.z();
    if (thit < ray._tmin || thit > ray._tmax)
        return false;

    // See if hit point is inside disk radii and $\phimax$
    Point phit = ray(thit);
    float dist2 = phit.x() * phit.x() + phit.y() * phit.y();
    if (dist2 > radius_ * radius_ || dist2 < inner_radius_ * inner_radius_)
        return false;

    // Test disk $\phi$ value against $\phimax$
    float phi = atan2f(phit.y(), phit.x());
    if (phi < 0) phi += 2. * M_PI;
    if (phi > phi_max_)
        return false;
    return true;
}


float Disk::area() const {
    return phi_max_ * 0.5f *
        (radius_ * radius_ - inner_radius_ * inner_radius_);
}


//Disk *CreateDiskShape(const Transform *o2w, const Transform *w2o,
//    bool reverseOrientation, const ParamSet &params) {
//    float height_ = params.FindOneFloat("height_", 0.);
//    float radius_ = params.FindOneFloat("radius_", 1);
//    float inner_radius = params.FindOneFloat("innerradius", 0);
//    float phimax = params.FindOneFloat("phimax", 360);
//    return new Disk(o2w, w2o, reverseOrientation, height_, radius_, inner_radius, phimax);
//}


//Point Disk::Sample(float u1, float u2, Normal *Ns) const {
//    Point p;
//    ConcentricSampleDisk(u1, u2, &p.x(), &p.y());
//    p.x() *= radius_;
//    p.y() *= radius_;
//    p.z() = height_;
//    *Ns = Normalize((*ObjectToWorld)(Normal(0, 0, 1)));
//    if (ReverseOrientation) *Ns *= -1.f;
//    return (*ObjectToWorld)(p);
//}


