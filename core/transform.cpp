#include "transform.h"

Transform::Transform()
    :m_(),
    m_inv_() // Identity
{}

Transform::Transform(const Matrix4x4 &mat)
    :m_(mat),
    m_inv_(mat.inverse())
{
}

Transform::Transform(const Matrix4x4 &mat, const Matrix4x4 &mat_inv)
    :m_(mat),
    m_inv_(mat_inv)
{}

bool Transform::operator==(const Transform& t) const
{
    return (m_ == t.m_);
}

bool Transform::operator!=(const Transform& t) const
{
    return (m_ != t.m_);
}

Transform Transform::operator*(const Transform &t) const
{
    return Transform(m_ * t.m_, t.m_inv_ * m_inv_);
}

Transform Transform::inverse() const
{
    return Transform(m_inv_, m_);
}

Transform Transform::transpose() const
{
    return Transform(m_.transpose(), m_inv_.transpose());
}

inline Point Transform::operator()(const Point& p) const
{
    float x = p.x, y = p.y, z = p.z;
    float xp = m_[0][0] * x + m_[0][1] * y + m_[0][2] * z + m_[0][3];
    float yp = m_[1][0] * x + m_[1][1] * y + m_[1][2] * z + m_[1][3];
    float zp = m_[2][0] * x + m_[2][1] * y + m_[2][2] * z + m_[2][3];
    float wp = m_[3][0] * x + m_[3][1] * y + m_[3][2] * z + m_[3][3];

    LG_ASSERT(wp != 0);

    return Point(xp, yp, zp) / wp;
}


inline Vector Transform::operator()(const Vector &v) const 
{
    float x = v.x(), y = v.y(), z = v.z();
    return Vector(m_[0][0] * x + m_[0][1] * y + m_[0][2] * z,
        m_[1][0] * x + m_[1][1] * y + m_[1][2] * z,
        m_[2][0] * x + m_[2][1] * y + m_[2][2] * z);
}

inline Normal Transform::operator()(const Normal &n) const 
{
    float x = n.x, y = n.y, z = n.z;
    return Normal(m_inv_[0][0] * x + m_inv_[1][0] * y + m_inv_[2][0] * z,
        m_inv_[0][1] * x + m_inv_[1][1] * y + m_inv_[2][1] * z,
        m_inv_[0][2] * x + m_inv_[1][2] * y + m_inv_[2][2] * z);
}


inline Ray Transform::operator()(const Ray &r) const 
{
    Ray ret = r;
    ret.o() = (*this)(r.o());
    ret.d() = (*this)(r.d());
 
    return ret;
}

Transform Transform::translate(const Vector &delta) const
{
    Matrix4x4 m(1, 0, 0, delta.x,
        0, 1, 0, delta.y,
        0, 0, 1, delta.z,
        0, 0, 0, 1);
    Matrix4x4 minv(1, 0, 0, -delta.x,
        0, 1, 0, -delta.y,
        0, 0, 1, -delta.z,
        0, 0, 0, 1);
    return Transform(m, minv);
}

Transform Transform::scale(float x, float y, float z) const
{
    Matrix4x4 m(x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1);
    Matrix4x4 minv(1.f / x, 0, 0, 0,
        0, 1.f / y, 0, 0,
        0, 0, 1.f / z, 0,
        0, 0, 0, 1);
    return Transform(m, minv);
}

Transform Transform::rotateX(float angle) const
{
    float sin_t = sinf(Radians(angle));
    float cos_t = cosf(Radians(angle));
    Matrix4x4 m(1, 0, 0, 0,
        0, cos_t, -sin_t, 0,
        0, sin_t, cos_t, 0,
        0, 0, 0, 1);
    return Transform(m, m.transpose());
}

Transform Transform::rotateY(float angle) const
{
    float sin_t = sinf(Radians(angle));
    float cos_t = cosf(Radians(angle));
    Matrix4x4 m(cos_t, 0, sin_t, 0,
        0, 1, 0, 0,
        -sin_t, 0, cos_t, 0,
        0, 0, 0, 1);
    return Transform(m, m.transpose());
}

Transform Transform::rotateZ(float angle) const
{
    float sin_t = sinf(Radians(angle));
    float cos_t = cosf(Radians(angle));
    Matrix4x4 m(cos_t, -sin_t, 0, 0,
        sin_t, cos_t, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
    return Transform(m, m.transpose());
}

Transform Transform::rotate(float angle, const Vector &axis) const
{
    Vector a = axis.normalize();
    float s = sinf(Radians(angle));
    float c = cosf(Radians(angle));
    float m[4][4];

    m[0][0] = a.x * a.x + (1.f - a.x * a.x) * c;
    m[0][1] = a.x * a.y * (1.f - c) - a.z * s;
    m[0][2] = a.x * a.z * (1.f - c) + a.y * s;
    m[0][3] = 0;

    m[1][0] = a.x * a.y * (1.f - c) + a.z * s;
    m[1][1] = a.y * a.y + (1.f - a.y * a.y) * c;
    m[1][2] = a.y * a.z * (1.f - c) - a.x * s;
    m[1][3] = 0;

    m[2][0] = a.x * a.z * (1.f - c) - a.y * s;
    m[2][1] = a.y * a.z * (1.f - c) + a.x * s;
    m[2][2] = a.z * a.z + (1.f - a.z * a.z) * c;
    m[2][3] = 0;

    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;

    Matrix4x4 mat(m);
    return Transform(mat, mat.transpose());
}

//Transform Transform::lookAt(const Point &pos, const Point &look, const Vector &up) const
//{
//    float m[4][4];
//    // Initialize fourth column of viewing matrix
//    m[0][3] = pos.x;
//    m[1][3] = pos.y;
//    m[2][3] = pos.z;
//    m[3][3] = 1;
//
//    // Initialize first three columns of viewing matrix
//    Vector dir = (look - pos).normalize();
//    /*if (Cross(Normalize(up), dir).Length() == 0) {
//        Error("\"up\" vector (%f, %f, %f) and viewing direction (%f, %f, %f) "
//            "passed to LookAt are pointing in the same direction.  Using "
//            "the identity transformation.", up.x, up.y, up.z, dir.x, dir.y,
//            dir.z);
//        return Transform();
//    }*/
//    Vector left = Normalize(Cross(Normalize(up), dir));
//    Vector newUp = Cross(dir, left);
//    m[0][0] = left.x;
//    m[1][0] = left.y;
//    m[2][0] = left.z;
//    m[3][0] = 0.;
//    m[0][1] = newUp.x;
//    m[1][1] = newUp.y;
//    m[2][1] = newUp.z;
//    m[3][1] = 0.;
//    m[0][2] = dir.x;
//    m[1][2] = dir.y;
//    m[2][2] = dir.z;
//    m[3][2] = 0.;
//    Matrix4x4 camToWorld(m);
//    return Transform(Inverse(camToWorld), camToWorld);
//}
//
//Transform Transform::orthographic(float znear, float zfar) const
//{
//    return Scale(1.f, 1.f, 1.f / (zfar - znear)) *
//        Translate(Vector(0.f, 0.f, -znear));
//}
//
//Transform Transform::perspective(float fov, float znear, float zfar) const
//{
//    // Perform projective divide
//    Matrix4x4 persp = Matrix4x4(1, 0, 0, 0,
//        0, 1, 0, 0,
//        0, 0, f / (f - n), -f*n / (f - n),
//        0, 0, 1, 0);
//
//    // Scale to canonical viewing volume
//    float invTanAng = 1.f / tanf(Radians(fov) / 2.f);
//    return Scale(invTanAng, invTanAng, 1) * Transform(persp);
//}


