#ifndef LGRENDER_MATH_UTILS_H
#define LGRENDER_MATH_UTILS_H

#define     LG_PI       3.1415926

#include <cmath>

// Global Inline Functions
template <typename T>
inline T min(T t1, T t2)
{
    return t1 < t2 ? t1 : t2;
}

template <typename T>
inline T max(T t1, T t2)
{
    return t1 > t2 ? t1 : t2;
}

inline float lerp(float t, float v1, float v2) 
{
    return (1.f - t) * v1 + t * v2;
}


inline float clamp(float val, float low, float high)
{
    if (val < low) return low;
    else if (val > high) return high;
    else return val;
}


inline int clamp(int val, int low, int high)
{
    if (val < low) return low;
    else if (val > high) return high;
    else return val;
}


inline int mod(int a, int b) 
{
    int n = int(a / b);
    a -= n*b;
    if (a < 0) a += b;
    return a;
}


inline float radians(float degree) 
{
    return ((float)LG_PI / 180.f) * degree;
}


inline float degrees(float rad) 
{
    return (180.f / (float)LG_PI) * rad;
}


inline float log2(float x) 
{
    static float invLog2 = 1.f / logf(2.f);
    return logf(x) * invLog2;
}

inline bool isPowerOf2(int v) 
{
    return v && !(v & (v - 1));
}


inline int floor2int(float val) 
{
    return (int)floorf(val);
}


inline int log2int(float v)
{
    return floor2int(log2(v));
}



inline int round2int(float val) 
{
    return floor2int(val + 0.5f);
}


inline int float2int(float val) 
{
    return (int)val;
}


inline int ceil2int(float val)
{
    return (int)ceilf(val);
}

inline bool quadratic(float A, float B, float C, float *t0, float *t1) {
    // Find quadratic discriminant
    float discrim = B * B - 4.f * A * C;
    if (discrim < 0.) return false;
    float rootDiscrim = sqrtf(discrim);

    // Compute quadratic _t_ values
    float q;
    if (B < 0) q = -.5f * (B - rootDiscrim);
    else       q = -.5f * (B + rootDiscrim);
    *t0 = q / A;
    *t1 = C / q;
    if (*t0 > *t1) std::swap(*t0, *t1);
    return true;
}



#endif //LGRENDER_MATH_UTILS_H

