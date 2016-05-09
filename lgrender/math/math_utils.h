#ifndef LGRENDER_MATH_UTILS_H
#define LGRENDER_MATH_UTILS_H

#include <cmath>

// Global Inline Functions
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
    return ((float)M_PI / 180.f) * degree;
}


inline float degrees(float rad) 
{
    return (180.f / (float)M_PI) * rad;
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


inline int floor2int(float val) {
    return (int)floorf(val);
}


inline int log2int(float v)
{
    return floor2int(log2(v));
}



inline int round2int(float val) {
    return floor2int(val + 0.5f);
}


inline int float2int(float val) {
    return (int)val;
}


inline int ceil2int(float val) {
    return (int)ceilf(val);
}


#endif //LGRENDER_MATH_UTILS_H

