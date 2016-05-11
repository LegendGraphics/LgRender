#include "matrix.h"

#include <cstring>

template <int R, int C>
Matrix<R, C>::Matrix()
{
    LG_ASSERT((R > 0 && C > 0));
    memset(&_m, 0, sizeof(float)*R*C);
}

template <int R, int C>
Matrix<R, C>::Matrix(float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
{
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

template <int R, int C>
Matrix<R, C>::Matrix(const float m[R][C])
{
    LG_ASSERT((R > 0 && C > 0));
    memcpy(&_m, &m, sizeof(float)*R*C);
}

template <int R, int C>
Matrix<R, C>::Matrix(const Matrix<R, C>& mat)
{
    LG_ASSERT((R > 0 && C > 0));
    memcpy(&_m, &mat._m, sizeof(float)*R*C);
}

template <int R, int C>
bool Matrix<R, C>::operator==(const Matrix& mat) const
{
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (_m[i][j] != mat._m[i][j]) return false;
    return true;
}

template <int R, int C>
bool Matrix<R, C>::operator!=(const Matrix& mat) const
{
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (_m[i][j] != mat._m[i][j]) return true;
    return false;
}

template <int R, int C>
void Matrix<R, C>::operator+=(const Matrix& mat)
{
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            _m[i][j] += mat._m[i][j];
}

template <int R, int C>
void Matrix<R, C>::operator-=(const Matrix& mat)
{
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            _m[i][j] -= mat._m[i][j];
}

template <int R, int C>
Matrix<R, C> Matrix<R, C>::operator+(const Matrix& mat) const
{
    Matrix nm;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            nm[i][j] = _m[i][j] + mat._m[i][j];
    return nm;
}

template <int R, int C>
Matrix<R, C> Matrix<R, C>::operator-(const Matrix& mat) const
{
    Matrix nm;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            nm[i][j] = _m[i][j] - mat._m[i][j];
    return nm;
}

template <int R, int C>
template <int OtherR, int OtherC>
Matrix<R, C> Matrix<R, C>::operator*(const Matrix<OtherR, OtherC>& mat) const
{
    LG_ASSERT(C == OtherR);
    Matrix nm;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < OtherC; ++j)
            for (int k = 0; k < C; ++k)
                nm[i][j] += _m[i][k] * mat._m[k][j];
    return nm;
}

template <int R, int C>
template <int OtherR, int OtherC>
void Matrix<R, C>::operator*=(const Matrix<OtherR, OtherC>& mat)
{
    LG_ASSERT(C == OtherR);
    Matrix nm;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < OtherC; ++j)
            for (int k = 0; k < C; ++k)
                nm[i][j] += _m[i][k] * mat._m[k][j];
    *this = nm;
}

template <int R, int C>
float& Matrix<R, C>::operator()(int i, int j)
{
    LG_ASSERT((i >= 0 && i < R) && (j >= 0 && j < C));
    return _m[i][j];
}

template <int R, int C>
float* const Matrix<R, C>::operator[](int k)
{
    LG_ASSERT( k < R );
    return &_m[k];
}

template <int R, int C>
const float& Matrix<R, C>::operator()(int i, int j) const
{
    LG_ASSERT((i >= 0 && i < R) && (j >= 0 && j < C));
    return _m[i][j];
}

template <int R, int C>
const float* const Matrix<R, C>::operator[](int k) const
{
    LG_ASSERT(k < R);
    return &_m[k];
}

template <int R, int C>
Matrix<R, C> Matrix<R, C>::transpose() const
{
    Matrix tm;
    for (int i = 0; i < R; ++i)
        for (int j = i + 1; j < C; ++j)
        {
            float tval = _m[i][j];
            _m[i][j] = _m[j][i];
            _m[j][i] = tval;
        }
    return tm;
}

template <int R, int C>
Matrix<R, C> Matrix<R, C>::inverse() const
{

}

template <int R, int C>
static const Matrix<R, C> Matrix<R, C>::identity()
{
    LG_ASSERT(R == C);
    Matrix im;
    for (int k = 0; k < R; ++k)
        im[k][k] = 1;
    return im;
}

template <int R, int C>
static const Matrix<R, C> Matrix<R, C>::zero()
{
    return Matrix();
}

