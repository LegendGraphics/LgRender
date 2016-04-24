
#include "sphere.h"

Sphere::Sphere(const Transform *o2w, const Transform *w2o, bool ro,
               float rad, float z_min, float z_max, float phi_max)
    :Shape(o2w, w2o, ro) 
{
    radius_ = rad;
    z_min_ = Clamp(min(z_min, z_max), -radius_, radius_);
    z_max_ = Clamp(max(z_min, z_max), -radius_, radius_);
    theta_min_ = acosf(Clamp(z_min / radius_, -1.f, 1.f));
    theta_max_ = acosf(Clamp(z_max / radius_, -1.f, 1.f));
    phi_max_ = Radians(Clamp(phi_max, 0.0f, 360.0f));
}


BoundingBox Sphere::object_bound() const {
    return BoundingBox(Point(-radius_, -radius_, z_min_),
                Point(radius_, radius_, z_max_));
}


//bool Sphere::Intersect(const Ray &r, float *tHit, float *rayEpsilon,
//                       DifferentialGeometry *dg) const {
//    float phi;
//    Point phit;
//    // Transform _Ray_ to object space
//    Ray ray;
//    (*WorldToObject)(r, &ray);
//
//    // Compute quadratic sphere coefficients
//    float A = ray.d.x*ray.d.x + ray.d.y*ray.d.y + ray.d.z*ray.d.z;
//    float B = 2 * (ray.d.x*ray.o.x + ray.d.y*ray.o.y + ray.d.z*ray.o.z);
//    float C = ray.o.x*ray.o.x + ray.o.y*ray.o.y +
//              ray.o.z*ray.o.z - radius*radius;
//
//    // Solve quadratic equation for _t_ values
//    float t0, t1;
//    if (!Quadratic(A, B, C, &t0, &t1))
//        return false;
//
//    // Compute intersection distance along ray
//    if (t0 > ray.maxt || t1 < ray.mint)
//        return false;
//    float thit = t0;
//    if (t0 < ray.mint) {
//        thit = t1;
//        if (thit > ray.maxt) return false;
//    }
//
//    // Compute sphere hit position and $\phi$
//    phit = ray(thit);
//    if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * radius;
//    phi = atan2f(phit.y, phit.x);
//    if (phi < 0.) phi += 2.f*M_PI;
//
//    // Test sphere intersection against clipping parameters
//    if ((zmin > -radius && phit.z < zmin) ||
//        (zmax <  radius && phit.z > zmax) || phi > phiMax) {
//        if (thit == t1) return false;
//        if (t1 > ray.maxt) return false;
//        thit = t1;
//        // Compute sphere hit position and $\phi$
//        phit = ray(thit);
//        if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * radius;
//        phi = atan2f(phit.y, phit.x);
//        if (phi < 0.) phi += 2.f*M_PI;
//        if ((zmin > -radius && phit.z < zmin) ||
//            (zmax <  radius && phit.z > zmax) || phi > phiMax)
//            return false;
//    }
//
//    // Find parametric representation of sphere hit
//    float u = phi / phiMax;
//    float theta = acosf(Clamp(phit.z / radius, -1.f, 1.f));
//    float v = (theta - thetaMin) / (thetaMax - thetaMin);
//
//    // Compute sphere $\dpdu$ and $\dpdv$
//    float zradius = sqrtf(phit.x*phit.x + phit.y*phit.y);
//    float invzradius = 1.f / zradius;
//    float cosphi = phit.x * invzradius;
//    float sinphi = phit.y * invzradius;
//    Vector dpdu(-phiMax * phit.y, phiMax * phit.x, 0);
//    Vector dpdv = (thetaMax-thetaMin) *
//        Vector(phit.z * cosphi, phit.z * sinphi,
//               -radius * sinf(theta));
//
//    // Compute sphere $\dndu$ and $\dndv$
//    Vector d2Pduu = -phiMax * phiMax * Vector(phit.x, phit.y, 0);
//    Vector d2Pduv = (thetaMax - thetaMin) * phit.z * phiMax *
//                    Vector(-sinphi, cosphi, 0.);
//    Vector d2Pdvv = -(thetaMax - thetaMin) * (thetaMax - thetaMin) *
//                    Vector(phit.x, phit.y, phit.z);
//
//    // Compute coefficients for fundamental forms
//    float E = Dot(dpdu, dpdu);
//    float F = Dot(dpdu, dpdv);
//    float G = Dot(dpdv, dpdv);
//    Vector N = Normalize(Cross(dpdu, dpdv));
//    float e = Dot(N, d2Pduu);
//    float f = Dot(N, d2Pduv);
//    float g = Dot(N, d2Pdvv);
//
//    // Compute $\dndu$ and $\dndv$ from fundamental form coefficients
//    float invEGF2 = 1.f / (E*G - F*F);
//    Normal dndu = Normal((f*F - e*G) * invEGF2 * dpdu +
//                         (e*F - f*E) * invEGF2 * dpdv);
//    Normal dndv = Normal((g*F - f*G) * invEGF2 * dpdu +
//                         (f*F - g*E) * invEGF2 * dpdv);
//
//    // Initialize _DifferentialGeometry_ from parametric information
//    const Transform &o2w = *ObjectToWorld;
//    *dg = DifferentialGeometry(o2w(phit), o2w(dpdu), o2w(dpdv),
//                               o2w(dndu), o2w(dndv), u, v, this);
//
//    // Update _tHit_ for quadric intersection
//    *tHit = thit;
//
//    // Compute _rayEpsilon_ for quadric intersection
//    *rayEpsilon = 5e-4f * *tHit;
//    return true;
//}


bool Sphere::intersectP(const Ray &r) const {
    float phi;
    Point phit;
    // Transform _Ray_ to object space
    Ray ray;
    (*WorldToObject)(r, &ray);

    // Compute quadratic sphere coefficients
    float A = ray.d.x*ray.d.x + ray.d.y*ray.d.y + ray.d.z*ray.d.z;
    float B = 2 * (ray.d.x*ray.o.x + ray.d.y*ray.o.y + ray.d.z*ray.o.z);
    float C = ray.o.x*ray.o.x + ray.o.y*ray.o.y +
              ray.o.z*ray.o.z - radius*radius;

    // Solve quadratic equation for _t_ values
    float t0, t1;
    if (!Quadratic(A, B, C, &t0, &t1))
        return false;

    // Compute intersection distance along ray
    if (t0 > ray.maxt || t1 < ray.mint)
        return false;
    float thit = t0;
    if (t0 < ray.mint) {
        thit = t1;
        if (thit > ray.maxt) return false;
    }

    // Compute sphere hit position and $\phi$
    phit = ray(thit);
    if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * radius;
    phi = atan2f(phit.y, phit.x);
    if (phi < 0.) phi += 2.f*M_PI;

    // Test sphere intersection against clipping parameters
    if ((zmin > -radius && phit.z < zmin) ||
        (zmax <  radius && phit.z > zmax) || phi > phiMax) {
        if (thit == t1) return false;
        if (t1 > ray.maxt) return false;
        thit = t1;
        // Compute sphere hit position and $\phi$
        phit = ray(thit);
        if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * radius;
        phi = atan2f(phit.y, phit.x);
        if (phi < 0.) phi += 2.f*M_PI;
        if ((zmin > -radius && phit.z < zmin) ||
            (zmax <  radius && phit.z > zmax) || phi > phiMax)
            return false;
    }
    return true;
}


float Sphere::area() const {
    return phi_max_ * radius_ * (z_max_-z_min_);
}


//Sphere *CreateSphereShape(const Transform *o2w, const Transform *w2o,
//        bool reverseOrientation, const ParamSet &params) {
//    float radius = params.FindOneFloat("radius", 1.f);
//    float zmin = params.FindOneFloat("zmin", -radius);
//    float zmax = params.FindOneFloat("zmax", radius);
//    float phimax = params.FindOneFloat("phimax", 360.f);
//    return new Sphere(o2w, w2o, reverseOrientation, radius,
//                      zmin, zmax, phimax);
//}


//Point Sphere::Sample(float u1, float u2, Normal *ns) const {
//    Point p = Point(0,0,0) + radius * UniformSampleSphere(u1, u2);
//    *ns = Normalize((*ObjectToWorld)(Normal(p.x, p.y, p.z)));
//    if (ReverseOrientation) *ns *= -1.f;
//    return (*ObjectToWorld)(p);
//}
//
//
//Point Sphere::Sample(const Point &p, float u1, float u2,
//                     Normal *ns) const {
//    // Compute coordinate system for sphere sampling
//    Point Pcenter = (*ObjectToWorld)(Point(0,0,0));
//    Vector wc = Normalize(Pcenter - p);
//    Vector wcX, wcY;
//    CoordinateSystem(wc, &wcX, &wcY);
//
//    // Sample uniformly on sphere if $\pt{}$ is inside it
//    if (DistanceSquared(p, Pcenter) - radius*radius < 1e-4f)
//        return Sample(u1, u2, ns);
//
//    // Sample sphere uniformly inside subtended cone
//    float sinThetaMax2 = radius*radius / DistanceSquared(p, Pcenter);
//    float cosThetaMax = sqrtf(max(0.f, 1.f - sinThetaMax2));
//    DifferentialGeometry dgSphere;
//    float thit, rayEpsilon;
//    Point ps;
//    Ray r(p, UniformSampleCone(u1, u2, cosThetaMax, wcX, wcY, wc), 1e-3f);
//    if (!Intersect(r, &thit, &rayEpsilon, &dgSphere))
//        thit = Dot(Pcenter - p, Normalize(r.d));
//    ps = r(thit);
//    *ns = Normal(Normalize(ps - Pcenter));
//    if (ReverseOrientation) *ns *= -1.f;
//    return ps;
//}
//
//
//float Sphere::Pdf(const Point &p, const Vector &wi) const {
//    Point Pcenter = (*ObjectToWorld)(Point(0,0,0));
//    // Return uniform weight if point inside sphere
//    if (DistanceSquared(p, Pcenter) - radius*radius < 1e-4f)
//        return Shape::Pdf(p, wi);
//
//    // Compute general sphere weight
//    float sinThetaMax2 = radius*radius / DistanceSquared(p, Pcenter);
//    float cosThetaMax = sqrtf(max(0.f, 1.f - sinThetaMax2));
//    return UniformConePdf(cosThetaMax);
//}

