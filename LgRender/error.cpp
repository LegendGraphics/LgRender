
// Error Reporting Includes
#include <cstdarg>
#include <cctype>
#include <string>

// Error Reporting Definitions
#define LGRENDER_ERROR_IGNORE 0
#define LGRENDER_ERROR_CONTINUE 1
#define LGRENDER_ERROR_ABORT 2

// for test
#define LGRENDER_IS_WINDOWS

// Error Reporting Functions
static void processError(const char *format, va_list args,
    const char *errorType, int disposition) {
    // Report error
    if (disposition == LGRENDER_ERROR_IGNORE)
        return;

    std::string errorString(errorType);
    errorString += ": ";

#if !defined(LGRENDER_IS_WINDOWS)
    char *errorBuf;
    if (vasprintf(&errorBuf, format, args) == -1) {
        fprintf(stderr, "vasprintf() unable to allocate memory!\n");
        abort();
    }
#else
    char errorBuf[2048];
    vsnprintf_s(errorBuf, sizeof(errorBuf), _TRUNCATE, format, args);
#endif

    errorString += errorBuf;
    fprintf(stderr, "%s\n", errorString.c_str());

    if (disposition == LGRENDER_ERROR_ABORT) {
#if defined(LGRENDER_IS_WINDOWS)
        __debugbreak();
#else
        abort();
#endif
    }
#if !defined(LGRENDER_IS_WINDOWS)
    free(errorBuf);
#endif
}


void Info(const char *format, ...) {
    va_list args;
    va_start(args, format);
    processError(format, args, "Notice", LGRENDER_ERROR_CONTINUE);
    va_end(args);
}


void Warning(const char *format, ...) {
    va_list args;
    va_start(args, format);
    processError(format, args, "Warning", LGRENDER_ERROR_CONTINUE);
    va_end(args);
}


void Error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    processError(format, args, "Error", LGRENDER_ERROR_CONTINUE);
    va_end(args);
}


void Severe(const char *format, ...) {
    va_list args;
    va_start(args, format);
    processError(format, args, "Fatal Error", LGRENDER_ERROR_ABORT);
    va_end(args);
}


