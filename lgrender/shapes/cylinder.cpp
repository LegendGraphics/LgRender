
#include "lgrender/shapes/cylinder.h"
#include "lgrender/math/math_utils.h"

// Cylinder Method Definitions
Cylinder::Cylinder(const Transform *o2w, const Transform *w2o, bool ro,
    float rad, float z_min, float z_max, float phi_max_)
    : Shape(o2w, w2o, ro) 
{
    radius_ = rad;
    z_min_ = min(z_min, z_max);
    z_max_ = max(z_min, z_max);
    phi_max_ = radians(clamp(phi_max_, 0.0f, 360.0f));
}


BoundingBox Cylinder::object_bound() const {
    Point p1 = Point(-radius_, -radius_, z_min_);
    Point p2 = Point(radius_, radius_, z_max_);
    return BoundingBox(p1, p2);
}


bool Cylinder::intersect(const Ray &r, float *t_hit, float *ray_epsilon,
    DifferentialGeometry *dg) const 
{
    float phi;
    Point phit;
    // Transform _Ray_ to object space
    Ray ray = (*world2object_)(r);

    // Compute quadratic cylinder coefficients
    float A = ray._d.x()*ray._d.x() + ray._d.y()*ray._d.y();
    float B = 2 * (ray._d.x()*ray._o.x() + ray._d.y()*ray._o.y());
    float C = ray._o.x()*ray._o.x() + ray._o.y()*ray._o.y() - radius_*radius_;

    // Solve quadratic equation for _t_ values
    float t0, t1;
    if (!quadratic(A, B, C, &t0, &t1))
        return false;

    // Compute intersection distance along ray
    if (t0 > ray._tmax || t1 < ray._tmin)
        return false;
    float thit = t0;
    if (t0 < ray._tmin) {
        thit = t1;
        if (thit > ray._tmax) return false;
    }

    // Compute cylinder hit point and $\phi$
    phit = ray(thit);
    phi = atan2f(phit.y(), phit.x());
    if (phi < 0.) phi += 2.f*LG_PI;

    // Test cylinder intersection against clipping parameters
    if (phit.z() < z_min_ || phit.z() > z_max_ || phi > phi_max_) {
        if (thit == t1) return false;
        thit = t1;
        if (t1 > ray._tmax) return false;
        // Compute cylinder hit point and $\phi$
        phit = ray(thit);
        phi = atan2f(phit.y(), phit.x());
        if (phi < 0.) phi += 2.f*LG_PI;
        if (phit.z() < z_min_ || phit.z() > z_max_ || phi > phi_max_)
            return false;
    }

    // Find parametric representation of cylinder hit
    float u = phi / phi_max_;
    float v = (phit.z() - z_min_) / (z_max_ - z_min_);

    // Compute cylinder $\dpdu$ and $\dpdv$
    Vector dpdu(-phi_max_ * phit.y(), phi_max_ * phit.x(), 0);
    Vector dpdv(0, 0, z_max_ - z_min_);

    // Compute cylinder $\dndu$ and $\dndv$
    Vector d2Pduu = -phi_max_ * phi_max_ * Vector(phit.x(), phit.y(), 0);
    Vector d2Pduv(0, 0, 0), d2Pdvv(0, 0, 0);

    // Compute coefficients for fundamental forms
    float E = dpdu.dot(dpdu);
    float F = dpdu.dot(dpdv);
    float G = dpdv.dot(dpdv);
    Vector N = (dpdu.cross(dpdv)).normalize();
    float e = N.dot(d2Pduu);
    float f = N.dot(d2Pduv);
    float g = N.dot(d2Pdvv);
     
    // Compute $\dndu$ and $\dndv$ from fundamental form coefficients
    float invEGF2 = 1.f / (E*G - F*F);
    Normal dndu = Normal((f*F - e*G) * invEGF2 * dpdu +
        (e*F - f*E) * invEGF2 * dpdv);
    Normal dndv = Normal((g*F - f*G) * invEGF2 * dpdu +
        (f*F - g*E) * invEGF2 * dpdv);

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


bool Cylinder::intersectP(const Ray &r) const {
    float phi;
    Point phit;
    // Transform _Ray_ to object space
    Ray ray = (*world2object_)(r);

    // Compute quadratic cylinder coefficients
    float A = ray._d.x()*ray._d.x() + ray._d.y()*ray._d.y();
    float B = 2 * (ray._d.x()*ray._o.x() + ray._d.y()*ray._o.y());
    float C = ray._o.x()*ray._o.x() + ray._o.y()*ray._o.y() - radius_*radius_;

    // Solve quadratic equation for _t_ values
    float t0, t1;
    if (!quadratic(A, B, C, &t0, &t1))
        return false;

    // Compute intersection distance along ray
    if (t0 > ray._tmax || t1 < ray._tmin)
        return false;
    float thit = t0;
    if (t0 < ray._tmin) {
        thit = t1;
        if (thit > ray._tmax) return false;
    }

    // Compute cylinder hit point and $\phi$
    phit = ray(thit);
    phi = atan2f(phit.y(), phit.x());
    if (phi < 0.) phi += 2.f*LG_PI;

    // Test cylinder intersection against clipping parameters
    if (phit.z() < z_min_ || phit.z() > z_max_ || phi > phi_max_) {
        if (thit == t1) return false;
        thit = t1;
        if (t1 > ray._tmax) return false;
        // Compute cylinder hit point and $\phi$
        phit = ray(thit);
        phi = atan2f(phit.y(), phit.x());
        if (phi < 0.) phi += 2.f*LG_PI;
        if (phit.z() < z_min_ || phit.z() > z_max_ || phi > phi_max_)
            return false;
    }
    return true;
}


float Cylinder::area() const 
{
    return (z_max_ - z_min_) * phi_max_ * radius_;
}


//Cylinder *CreateCylinderShape(const Transform *o2w, const Transform *w2o,
//    bool reverseOrientation, const ParamSet &params) {
//    float radius_ = params.FindOneFloat("radius_", 1);
//    float z_min_ = params.FindOneFloat("z_min_", -1);
//    float z_max_ = params.FindOneFloat("z_max_", 1);
//    float phimax = params.FindOneFloat("phimax", 360);
//    return new Cylinder(o2w, w2o, reverseOrientation, radius_, z_min_, z_max_, phimax);
//}


//Point Cylinder::Sample(float u1, float u2, Normal *Ns) const {
//    float z = Lerp(u1, z_min_, z_max_);
//    float t = u2 * phi_max_;
//    Point p = Point(radius_ * cosf(t), radius_ * sinf(t), z);
//    *Ns = Normalize((*ObjectToWorld)(Normal(p.x, p.y, 0.)));
//    if (ReverseOrientation) *Ns *= -1.f;
//    return (*ObjectToWorld)(p);
//}


