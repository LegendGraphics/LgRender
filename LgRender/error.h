#ifndef LGRENDER_CORE_ERROR_H
#define LGRENDER_CORE_ERROR_H

// Setup printf format
#ifdef __GNUG__
#define PRINTF_FUNC __attribute__ \
    ((__format__ (__printf__, 1, 2)))
#else
#define PRINTF_FUNC
#endif // __GNUG__
void Info(const char *, ...) PRINTF_FUNC;
void Warning(const char *, ...) PRINTF_FUNC;
void Error(const char *, ...) PRINTF_FUNC;
void Severe(const char *, ...) PRINTF_FUNC;

#endif // PBRT_CORE_ERROR_H
