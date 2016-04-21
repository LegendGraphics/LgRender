#ifndef LGRENDER_CORE_TYPES_H
#define LGRENDER_CORE_TYPES_H


#ifdef NDEBUG
#define LG_ASSERT(expr) ((void)0)
#else
#define LG_ASSERT(expr) \
    ((expr) ? (void)0 : \
    Severe("Assertion \"%s\" failed in %s, line %d", \
    #expr, __FILE__, __LINE__))
#endif // NDEBUG

#endif // LGRENDER_CORE_TYPES_H