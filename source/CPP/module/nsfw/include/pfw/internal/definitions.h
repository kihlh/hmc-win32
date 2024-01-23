#ifndef PFW_DEFINITIONS_H
#define PFW_DEFINITIONS_H

/**
 * Figure out which platform we are compiling on.
 * Afterwards one (or more) of the following constants will be defined:
 *      * PFW_WINDOWS         - any kind of windows platform
 *        * PFW_WIN32         - 32bit windows
 *        * PFW_WIN64         - 64bit windows
 *      * PFW_POSIX           - POSIX compliant operating system
 *        * PFW_UNIX          - Unix
 *          * PFW_APPLE       - macOS
 *        * PFW_LINUX         - Linux
 */
#ifdef _WIN32
#define PFW_WINDOWS 1
#ifdef _WIN64
#define PFW_WIN64 1
#else
#define PFW_WIN32 1
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
#define PFW_APPLE 1
#define PFW_UNIX 1
#define PFW_POSIX 1
#else
#error "unknown or unsupported Apple platform"
#endif
#elif __linux__
#define PFW_UNIX 1
#define PFW_LINUX 1
#define PFW_POSIX 1
#elif __unix__
#define PFW_UNIX 1
#define PFW_POSIX 1
#elif defined(_POSIX_VERSION)
#define PFW_POSIX 1
#else
#error "unknown or unsupported platform"
#endif

#ifdef __clang__
#define PFW_CLANG 1
#elif __GNUC__
#define PFW_GCC 1
#elif _MSC_VER
#define PFW_MSVC 1
#else
#error "unknown or unsupported compiler"
#endif

#endif /* PFW_DEFINITIONS_H */
