#ifndef LGRENDER_CORE_TRANSFORM_H
#define LGRENDER_CORE_TRANSFORM_H

#include "matrix.h"

class Transform
{
public:
    Transform(){}
    Transform(const Matrix4x4 &mat);

    bool operator==(const Transform& t) const;
    bool operator!=(const Transform& t) const;
    /*Matrix operator*(const Transform& t) const;
    void operator*=(const Matrix<OtherR, OtherC>& mat);*/

    Transform inverse() const;
    Transform transpose() const;

    inline Point operator()(const Point &pt) const;
    inline void operator()(const Point &pt, Point *ptrans) const;
    inline Vector operator()(const Vector &v) const;
    inline void operator()(const Vector &v, Vector *vt) const;
    inline Normal operator()(const Normal &) const;
    inline void operator()(const Normal &, Normal *nt) const;
    inline Ray operator()(const Ray &r) const;
    inline void operator()(const Ray &r, Ray *rt) const;
    inline RayDifferential operator()(const RayDifferential &r) const;
    inline void operator()(const RayDifferential &r, RayDifferential *rt) const;
    BBox operator()(const BBox &b) const;
    Transform operator*(const Transform &t2) const;

private:
    Matrix4x4 m_, m_inv_;
};


#endif // LGRENDER_CORE_TRANSFORM_H