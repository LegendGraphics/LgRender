#include "matrix.h"

#include <cstring>

template <int R, int C>
Matrix<R, C>::Matrix()
{
    LG_ASSERT((R > 0 && C > 0));
    memset(&_m, 0, sizeof(float)*R*C);
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
float& Matrix<R, C>::operator()(int i, int j) const
{
    LG_ASSERT((i >= 0 && i < R) && (j >= 0 && j < C));
    return _m[i][j];
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

