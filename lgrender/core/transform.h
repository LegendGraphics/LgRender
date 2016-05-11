#ifndef LGRENDER_CORE_TRANSFORM_H
#define LGRENDER_CORE_TRANSFORM_H

#include "lgrender/math/matrix.h"
#include "lgrender/core/geometry.h"

class Transform
{
public:
    Transform();
    Transform(const Matrix4x4 &mat);
    Transform(const Matrix4x4 &mat, const Matrix4x4 &mat_inv);

    bool operator==(const Transform& t) const;
    bool operator!=(const Transform& t) const;

    Transform operator*(const Transform &t) const;

    inline Point operator()(const Point& p) const;
    inline Vector operator()(const Vector& v) const;
    inline Normal operator()(const Normal& n) const;
    inline Ray operator()(const Ray& r) const;

    Transform inverse() const;
    Transform transpose() const;
    Transform translate(const Vector &delta) const;
    Transform scale(float x, float y, float z) const;
    Transform rotateX(float angle) const;
    Transform rotateY(float angle) const;
    Transform rotateZ(float angle) const;
    Transform rotate(float angle, const Vector &axis) const;
    Transform lookAt(const Point &pos, const Point &look, const Vector &up) const;
    Transform orthographic(float znear, float zfar) const;
    Transform perspective(float fov, float znear, float zfar) const;
    

private:
    Matrix4x4 m_, m_inv_;
};


#endif // LGRENDER_CORE_TRANSFORM_H