//
// Copyright (c) 2013-2021 Winlin
//
// SPDX-License-Identifier: MIT
//

#ifndef SRS_CORE_HPP
#define SRS_CORE_HPP

// The version config.
#include <srs_core_version4.hpp>

// The macros generated by configure script.
#include <srs_auto_headers.hpp>

// To convert macro values to string.
// @see https://gcc.gnu.org/onlinedocs/cpp/Stringification.html#Stringification
#define SRS_INTERNAL_STR(v) #v
#define SRS_XSTR(v) SRS_INTERNAL_STR(v)

// The project informations, may sent to client in HTTP header or RTMP metadata.
#define RTMP_SIG_SRS_KEY "SigmaRTMPServer"
#define RTMP_SIG_SRS_CODE "Anhlv"
#define RTMP_SIG_SRS_URL "https://github.com"
#define RTMP_SIG_SRS_LICENSE "MIT"
#define RTMP_SIG_SRS_AUTHORS "https://github.com/ossrs/srs/blob/4.0release/trunk/AUTHORS.txt"
#define RTMP_SIG_SRS_VERSION SRS_XSTR(VERSION_MAJOR) "." SRS_XSTR(VERSION_MINOR) "." SRS_XSTR(VERSION_REVISION)
#define RTMP_SIG_SRS_SERVER RTMP_SIG_SRS_KEY "/" RTMP_SIG_SRS_VERSION "(" RTMP_SIG_SRS_CODE ")"
#define RTMP_SIG_SRS_DOMAIN "ossrs.net"

// The current stable release.
#define VERSION_STABLE 2
#define VERSION_STABLE_BRANCH SRS_XSTR(VERSION_STABLE)".0release"

// For 32bit os, 2G big file limit for unistd io,
// ie. read/write/lseek to use 64bits size for huge file.
#ifndef _FILE_OFFSET_BITS
    #define _FILE_OFFSET_BITS 64
#endif

// For int64_t print using PRId64 format.
#ifndef __STDC_FORMAT_MACROS
    #define __STDC_FORMAT_MACROS
#endif

// For RTC/FFMPEG build.
#if defined(SRS_RTC) && !defined(__STDC_CONSTANT_MACROS)
    #define __STDC_CONSTANT_MACROS
#endif

// For srs-librtmp, @see https://github.com/ossrs/srs/issues/213
#ifndef _WIN32
#include <inttypes.h>
#endif

#include <assert.h>
#define srs_assert(expression) assert(expression)

#include <stddef.h>
#include <sys/types.h>

// The time unit for timeout, interval or duration.
#include <srs_core_time.hpp>

// Some important performance options.
#include <srs_core_performance.hpp>

// To free the p and set to NULL.
// @remark The p must be a pointer T*.
#define srs_freep(p) \
    if (p) { \
        delete p; \
        p = NULL; \
    } \
    (void)0
// Please use the freepa(T[]) to free an array, otherwise the behavior is undefined.
#define srs_freepa(pa) \
    if (pa) { \
        delete[] pa; \
        pa = NULL; \
    } \
    (void)0

// Checking for st(state-threads), only support the following cpus: i386/amd64/x86_64/arm
// @reamrk To patch ST for arm, read https://github.com/ossrs/state-threads/issues/1
#if !defined(__amd64__) && !defined(__x86_64__) && !defined(__i386__) && !defined(__arm__) && !defined(__aarch64__)
    #error "only support i386/amd64/x86_64/arm cpu"
#endif

// Error predefined for all modules.
class SrsCplxError;
typedef SrsCplxError* srs_error_t;

#include <string>
// The context ID, it default to a string object, we can also use other objects.
// @remark User can directly user string as SrsContextId, we user struct to ensure the context is an object.
#if 1
class _SrsContextId
{
private:
    std::string v_;
public:
    _SrsContextId();
    _SrsContextId(const _SrsContextId& cp);
    _SrsContextId& operator=(const _SrsContextId& cp);
    virtual ~_SrsContextId();
public:
    const char* c_str() const;
    bool empty() const;
    // Compare the two context id. @see http://www.cplusplus.com/reference/string/string/compare/
    //      0	They compare equal
    //      <0	Either the value of the first character that does not match is lower in the compared string, or all compared characters match but the compared string is shorter.
    //      >0	Either the value of the first character that does not match is greater in the compared string, or all compared characters match but the compared string is longer.
    int compare(const _SrsContextId& to) const;
    // Set the value of context id.
    _SrsContextId& set_value(const std::string& v);
};
typedef _SrsContextId SrsContextId;
#else
// Actually, we can directly user string as SrsContextId.
typedef std::string SrsContextId;
#endif

#endif
