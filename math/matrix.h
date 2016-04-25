#ifndef LGRENDER_CORE_MATRIX_H
#define LGRENDER_CORE_MATRIX_H

#include "types.h"

template <int R, int C>
class Matrix
{
public:
    Matrix();
    Matrix(float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);
    Matrix(const float m[R][C]);
    Matrix(const Matrix& mat);

    bool operator==(const Matrix& mat) const;
    bool operator!=(const Matrix& mat) const;
    Matrix operator+(const Matrix& mat) const;
    Matrix operator-(const Matrix& mat) const;
    void operator+=(const Matrix& mat);
    void operator-=(const Matrix& mat);

    template <int OtherR, int OtherC>
    Matrix operator*(const Matrix<OtherR, OtherC>& mat) const;
    template <int OtherR, int OtherC>
    void operator*=(const Matrix<OtherR, OtherC>& mat);

    float& operator()(int i, int j);
    float* const operator[](int k);
    const float& operator()(int i, int j) const;
    const float* const operator[](int k) const;

    Matrix transpose() const;
    Matrix inverse() const;

private:
    float _m[R][C];
};


typedef Matrix<4, 4> Matrix4x4;


#endif // LGRENDER_CORE_MATRIX_H