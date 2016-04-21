#ifndef LGRENDER_CORE_GEOMETRY_H
#define LGRENDER_CORE_GEOMETRY_H

#include <cmath>
#include "types.h"

class Triple {
public:
    // Triple Public Methods
    Triple();
    Triple(float x, float y, float z);
    Triple(const Triple &t);

    float& x();
    float& y();
    float& z();

    const float& x() const;
    const float& y() const;
    const float& z() const;

    bool hasNaNs() const;
    //explicit Triple(const Point &p);

    Triple operator+(const Triple &t) const;   
    Triple operator-(const Triple &t) const;   
    Triple operator*(float f) const;   
    Triple operator/(float f) const;
    
    void operator+=(const Triple &t);
    void operator-=(const Triple &t);
    void operator*=(float f);
    void operator/=(float f);

    Triple operator-() const;

    void operator=(const Triple &t);
    bool operator==(const Triple &t) const;
    bool operator!=(const Triple &t) const;

    float operator[](int i) const;
    float &operator[](int i);

    float length_squared() const;
    float length() const;
    //explicit Triple(const Normal &n);

private:
    // Triple Public Data
    float _x, _y, _z;
};





class Point {
public:
    // Point Public Methods
    Point() { x = y = z = 0.f; }
    Point(float xx, float yy, float zz)
        : x(xx), y(yy), z(zz) {
        LG_ASSERT(!HasNaNs());
    }
#ifndef NDEBUG
    Point(const Point &p) {
        LG_ASSERT(!p.HasNaNs());
        x = p.x; y = p.y; z = p.z;
    }

    Point &operator=(const Point &p) {
        LG_ASSERT(!p.HasNaNs());
        x = p.x; y = p.y; z = p.z;
        return *this;
    }
#endif // !NDEBUG
    Point operator+(const Triple &v) const {
        LG_ASSERT(!v.HasNaNs());
        return Point(x + v.x, y + v.y, z + v.z);
    }

    Point &operator+=(const Triple &v) {
        LG_ASSERT(!v.HasNaNs());
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    Triple operator-(const Point &p) const {
        LG_ASSERT(!p.HasNaNs());
        return Triple(x - p.x, y - p.y, z - p.z);
    }

    Point operator-(const Triple &v) const {
        LG_ASSERT(!v.HasNaNs());
        return Point(x - v.x, y - v.y, z - v.z);
    }

    Point &operator-=(const Triple &v) {
        LG_ASSERT(!v.HasNaNs());
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    Point &operator+=(const Point &p) {
        LG_ASSERT(!p.HasNaNs());
        x += p.x; y += p.y; z += p.z;
        return *this;
    }
    Point operator+(const Point &p) const {
        LG_ASSERT(!p.HasNaNs());
        return Point(x + p.x, y + p.y, z + p.z);
    }
    Point operator* (float f) const {
        return Point(f*x, f*y, f*z);
    }
    Point &operator*=(float f) {
        x *= f; y *= f; z *= f;
        return *this;
    }
    Point operator/ (float f) const {
        float inv = 1.f / f;
        return Point(inv*x, inv*y, inv*z);
    }
    Point &operator/=(float f) {
        float inv = 1.f / f;
        x *= inv; y *= inv; z *= inv;
        return *this;
    }
    float operator[](int i) const {
        LG_ASSERT(i >= 0 && i <= 2);
        return (&x)[i];
    }

    float &operator[](int i) {
        LG_ASSERT(i >= 0 && i <= 2);
        return (&x)[i];
    }
    bool HasNaNs() const {
        return isnan(x) || isnan(y) || isnan(z);
    }

    bool operator==(const Point &p) const {
        return x == p.x && y == p.y && z == p.z;
    }
    bool operator!=(const Point &p) const {
        return x != p.x || y != p.y || z != p.z;
    }

    // Point Public Data
    float x, y, z;
};


class Normal {
public:
    // Normal Public Methods
    Normal() { x = y = z = 0.f; }
    Normal(float xx, float yy, float zz)
        : x(xx), y(yy), z(zz) {
        LG_ASSERT(!HasNaNs());
    }
    Normal operator-() const {
        return Normal(-x, -y, -z);
    }
    Normal operator+ (const Normal &n) const {
        LG_ASSERT(!n.HasNaNs());
        return Normal(x + n.x, y + n.y, z + n.z);
    }

    Normal& operator+=(const Normal &n) {
        LG_ASSERT(!n.HasNaNs());
        x += n.x; y += n.y; z += n.z;
        return *this;
    }
    Normal operator- (const Normal &n) const {
        LG_ASSERT(!n.HasNaNs());
        return Normal(x - n.x, y - n.y, z - n.z);
    }

    Normal& operator-=(const Normal &n) {
        LG_ASSERT(!n.HasNaNs());
        x -= n.x; y -= n.y; z -= n.z;
        return *this;
    }
    bool HasNaNs() const {
        return isnan(x) || isnan(y) || isnan(z);
    }
    Normal operator*(float f) const {
        return Normal(f*x, f*y, f*z);
    }

    Normal &operator*=(float f) {
        x *= f; y *= f; z *= f;
        return *this;
    }
    Normal operator/(float f) const {
        LG_ASSERT(f != 0);
        float inv = 1.f / f;
        return Normal(x * inv, y * inv, z * inv);
    }

    Normal &operator/=(float f) {
        LG_ASSERT(f != 0);
        float inv = 1.f / f;
        x *= inv; y *= inv; z *= inv;
        return *this;
    }
    float LengthSquared() const { return x*x + y*y + z*z; }
    float Length() const { return sqrtf(LengthSquared()); }

#ifndef NDEBUG
    Normal(const Normal &n) {
        LG_ASSERT(!n.HasNaNs());
        x = n.x; y = n.y; z = n.z;
    }

    Normal &operator=(const Normal &n) {
        LG_ASSERT(!n.HasNaNs());
        x = n.x; y = n.y; z = n.z;
        return *this;
    }
#endif // !NDEBUG
    explicit Normal(const Triple &v)
        : x(v.x), y(v.y), z(v.z) {
        LG_ASSERT(!v.HasNaNs());
    }
    float operator[](int i) const {
        LG_ASSERT(i >= 0 && i <= 2);
        return (&x)[i];
    }

    float &operator[](int i) {
        LG_ASSERT(i >= 0 && i <= 2);
        return (&x)[i];
    }

    bool operator==(const Normal &n) const {
        return x == n.x && y == n.y && z == n.z;
    }
    bool operator!=(const Normal &n) const {
        return x != n.x || y != n.y || z != n.z;
    }

    // Normal Public Data
    float x, y, z;
};


class Ray {
public:
    // Ray Public Methods
    Ray() : mint(0.f), maxt(INFINITY), time(0.f), depth(0) { }
    Ray(const Point &origin, const Triple &direction,
        float start, float end = INFINITY, float t = 0.f, int d = 0)
        : o(origin), d(direction), mint(start), maxt(end), time(t), depth(d) { }
    Ray(const Point &origin, const Triple &direction, const Ray &parent,
        float start, float end = INFINITY)
        : o(origin), d(direction), mint(start), maxt(end),
        time(parent.time), depth(parent.depth + 1) { }
    Point operator()(float t) const { return o + d * t; }
    bool HasNaNs() const {
        return (o.HasNaNs() || d.HasNaNs() ||
            isnan(mint) || isnan(maxt));
    }

    // Ray Public Data
    Point o;
    Triple d;
    mutable float mint, maxt;
    float time;
    int depth;
};


class RayDifferential : public Ray {
public:
    // RayDifferential Public Methods
    RayDifferential() { hasDifferentials = false; }
    RayDifferential(const Point &org, const Triple &dir, float start,
        float end = INFINITY, float t = 0.f, int d = 0)
        : Ray(org, dir, start, end, t, d) {
        hasDifferentials = false;
    }
    RayDifferential(const Point &org, const Triple &dir, const Ray &parent,
        float start, float end = INFINITY)
        : Ray(org, dir, start, end, parent.time, parent.depth + 1) {
        hasDifferentials = false;
    }
    explicit RayDifferential(const Ray &ray) : Ray(ray) {
        hasDifferentials = false;
    }
    bool HasNaNs() const {
        return Ray::HasNaNs() ||
            (hasDifferentials && (rxOrigin.HasNaNs() || ryOrigin.HasNaNs() ||
                rxDirection.HasNaNs() || ryDirection.HasNaNs()));
    }
    void ScaleDifferentials(float s) {
        rxOrigin = o + (rxOrigin - o) * s;
        ryOrigin = o + (ryOrigin - o) * s;
        rxDirection = d + (rxDirection - d) * s;
        ryDirection = d + (ryDirection - d) * s;
    }

    // RayDifferential Public Data
    bool hasDifferentials;
    Point rxOrigin, ryOrigin;
    Triple rxDirection, ryDirection;
};


class BBox {
public:
    // BBox Public Methods
    BBox() {
        pMin = Point(INFINITY, INFINITY, INFINITY);
        pMax = Point(-INFINITY, -INFINITY, -INFINITY);
    }
    BBox(const Point &p) : pMin(p), pMax(p) { }
    BBox(const Point &p1, const Point &p2) {
        pMin = Point(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
        pMax = Point(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
    }
    friend BBox Union(const BBox &b, const Point &p);
    friend BBox Union(const BBox &b, const BBox &b2);
    bool Overlaps(const BBox &b) const {
        bool x = (pMax.x >= b.pMin.x) && (pMin.x <= b.pMax.x);
        bool y = (pMax.y >= b.pMin.y) && (pMin.y <= b.pMax.y);
        bool z = (pMax.z >= b.pMin.z) && (pMin.z <= b.pMax.z);
        return (x && y && z);
    }
    bool Inside(const Point &pt) const {
        return (pt.x >= pMin.x && pt.x <= pMax.x &&
            pt.y >= pMin.y && pt.y <= pMax.y &&
            pt.z >= pMin.z && pt.z <= pMax.z);
    }
    void Expand(float delta) {
        pMin -= Triple(delta, delta, delta);
        pMax += Triple(delta, delta, delta);
    }
    float SurfaceArea() const {
        Triple d = pMax - pMin;
        return 2.f * (d.x * d.y + d.x * d.z + d.y * d.z);
    }
    float Volume() const {
        Triple d = pMax - pMin;
        return d.x * d.y * d.z;
    }
    int MaximumExtent() const {
        Triple diag = pMax - pMin;
        if (diag.x > diag.y && diag.x > diag.z)
            return 0;
        else if (diag.y > diag.z)
            return 1;
        else
            return 2;
    }
    const Point &operator[](int i) const;
    Point &operator[](int i);
    Point Lerp(float tx, float ty, float tz) const {
        return Point(::Lerp(tx, pMin.x, pMax.x), ::Lerp(ty, pMin.y, pMax.y),
            ::Lerp(tz, pMin.z, pMax.z));
    }
    Triple Offset(const Point &p) const {
        return Triple((p.x - pMin.x) / (pMax.x - pMin.x),
            (p.y - pMin.y) / (pMax.y - pMin.y),
            (p.z - pMin.z) / (pMax.z - pMin.z));
    }
    void BoundingSphere(Point *c, float *rad) const;
    bool IntersectP(const Ray &ray, float *hitt0 = NULL, float *hitt1 = NULL) const;

    bool operator==(const BBox &b) const {
        return b.pMin == pMin && b.pMax == pMax;
    }
    bool operator!=(const BBox &b) const {
        return b.pMin != pMin || b.pMax != pMax;
    }

    // BBox Public Data
    Point pMin, pMax;
};



// Geometry Inline Functions
inline Triple::Triple(const Point &p)
    : x(p.x), y(p.y), z(p.z) {
    LG_ASSERT(!HasNaNs());
}


inline Triple operator*(float f, const Triple &v) { return v*f; }
inline float Dot(const Triple &v1, const Triple &v2) {
    LG_ASSERT(!v1.HasNaNs() && !v2.HasNaNs());
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


inline float AbsDot(const Triple &v1, const Triple &v2) {
    LG_ASSERT(!v1.HasNaNs() && !v2.HasNaNs());
    return fabsf(Dot(v1, v2));
}


inline Triple Cross(const Triple &v1, const Triple &v2) {
    LG_ASSERT(!v1.HasNaNs() && !v2.HasNaNs());
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Triple((v1y * v2z) - (v1z * v2y),
        (v1z * v2x) - (v1x * v2z),
        (v1x * v2y) - (v1y * v2x));
}


inline Triple Cross(const Triple &v1, const Normal &v2) {
    LG_ASSERT(!v1.HasNaNs() && !v2.HasNaNs());
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Triple((v1y * v2z) - (v1z * v2y),
        (v1z * v2x) - (v1x * v2z),
        (v1x * v2y) - (v1y * v2x));
}


inline Triple Cross(const Normal &v1, const Triple &v2) {
    LG_ASSERT(!v1.HasNaNs() && !v2.HasNaNs());
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Triple((v1y * v2z) - (v1z * v2y),
        (v1z * v2x) - (v1x * v2z),
        (v1x * v2y) - (v1y * v2x));
}


inline Triple Normalize(const Triple &v) { return v / v.Length(); }
inline void CoordinateSystem(const Triple &v1, Triple *v2, Triple *v3) {
    if (fabsf(v1.x) > fabsf(v1.y)) {
        float invLen = 1.f / sqrtf(v1.x*v1.x + v1.z*v1.z);
        *v2 = Triple(-v1.z * invLen, 0.f, v1.x * invLen);
    }
    else {
        float invLen = 1.f / sqrtf(v1.y*v1.y + v1.z*v1.z);
        *v2 = Triple(0.f, v1.z * invLen, -v1.y * invLen);
    }
    *v3 = Cross(v1, *v2);
}


inline float Distance(const Point &p1, const Point &p2) {
    return (p1 - p2).Length();
}


inline float DistanceSquared(const Point &p1, const Point &p2) {
    return (p1 - p2).LengthSquared();
}


inline Point operator*(float f, const Point &p) {
    LG_ASSERT(!p.HasNaNs());
    return p*f;
}


inline Normal operator*(float f, const Normal &n) {
    return Normal(f*n.x, f*n.y, f*n.z);
}


inline Normal Normalize(const Normal &n) {
    return n / n.Length();
}


inline Triple::Triple(const Normal &n)
    : x(n.x), y(n.y), z(n.z) {
    LG_ASSERT(!n.HasNaNs());
}


inline float Dot(const Normal &n1, const Triple &v2) {
    LG_ASSERT(!n1.HasNaNs() && !v2.HasNaNs());
    return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
}


inline float Dot(const Triple &v1, const Normal &n2) {
    LG_ASSERT(!v1.HasNaNs() && !n2.HasNaNs());
    return v1.x * n2.x + v1.y * n2.y + v1.z * n2.z;
}


inline float Dot(const Normal &n1, const Normal &n2) {
    LG_ASSERT(!n1.HasNaNs() && !n2.HasNaNs());
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}


inline float AbsDot(const Normal &n1, const Triple &v2) {
    LG_ASSERT(!n1.HasNaNs() && !v2.HasNaNs());
    return fabsf(n1.x * v2.x + n1.y * v2.y + n1.z * v2.z);
}


inline float AbsDot(const Triple &v1, const Normal &n2) {
    LG_ASSERT(!v1.HasNaNs() && !n2.HasNaNs());
    return fabsf(v1.x * n2.x + v1.y * n2.y + v1.z * n2.z);
}


inline float AbsDot(const Normal &n1, const Normal &n2) {
    LG_ASSERT(!n1.HasNaNs() && !n2.HasNaNs());
    return fabsf(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
}


inline Normal Faceforward(const Normal &n, const Triple &v) {
    return (Dot(n, v) < 0.f) ? -n : n;
}


inline Normal Faceforward(const Normal &n, const Normal &n2) {
    return (Dot(n, n2) < 0.f) ? -n : n;
}



inline Triple Faceforward(const Triple &v, const Triple &v2) {
    return (Dot(v, v2) < 0.f) ? -v : v;
}



inline Triple Faceforward(const Triple &v, const Normal &n2) {
    return (Dot(v, n2) < 0.f) ? -v : v;
}


inline const Point &BBox::operator[](int i) const {
    LG_ASSERT(i == 0 || i == 1);
    return (&pMin)[i];
}



inline Point &BBox::operator[](int i) {
    LG_ASSERT(i == 0 || i == 1);
    return (&pMin)[i];
}


inline Triple SphericalDirection(float sintheta,
    float costheta, float phi) {
    return Triple(sintheta * cosf(phi),
        sintheta * sinf(phi),
        costheta);
}


inline Triple SphericalDirection(float sintheta, float costheta,
    float phi, const Triple &x,
    const Triple &y, const Triple &z) {
    return sintheta * cosf(phi) * x +
        sintheta * sinf(phi) * y + costheta * z;
}


inline float SphericalTheta(const Triple &v) {
    return acosf(Clamp(v.z, -1.f, 1.f));
}


inline float SphericalPhi(const Triple &v) {
    float p = atan2f(v.y, v.x);
    return (p < 0.f) ? p + 2.f*M_PI : p;
}



#endif // LGRENDER_CORE_GEOMETRY_H
