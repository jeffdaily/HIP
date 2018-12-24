/*
Copyright (c) 2018 - present Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef HIP_SRC_HU_INTERNAL_H
#define HIP_SRC_HU_INTERNAL_H

#include <hc.hpp>

#include "hip/hip_common.h"
#include "hip/hip_driver.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

std::ostream& operator<<(std::ostream& os, const HUstream_st& s);
std::ostream& operator<<(std::ostream& os, const HUipcEventHandle_st& s);
std::ostream& operator<<(std::ostream& os, const HUipcMemHandle_st& s);

// Helper functions to convert HU function arguments into strings.
// Handles POD data types as well as enumerations (ie hipMemcpyKind).
// The implementation uses C++11 variadic templates and template specialization.
// The hipMemcpyKind example below is a good example that shows how to implement conversion for a
// new HSA type.

// Handy macro to convert an enumeration to a stringified version of same:
#define CASE_STR(x)                                                                                \
    case x:                                                                                        \
        return #x;

// Building block functions:
template <typename T>
inline std::string ToHexString(T v) {
    std::ostringstream ss;
    ss << "0x" << std::hex << v;
    return ss.str();
};

// This is the default which works for most types:
template <typename T>
inline std::string ToString(T v) {
    std::ostringstream ss;
    ss << v;
    return ss.str();
};

//  HUevent specialization
template <>
inline std::string ToString(HUevent v) {
    std::ostringstream ss;
    ss << v;
    return ss.str();
};

//  HUstream
template <>
inline std::string ToString(HUstream v) {
    std::ostringstream ss;
    if (v == NULL) {
        ss << "stream:<null>";
    } else {
        ss << *v;
    }

    return ss.str();
};

template <>
inline std::string ToString(HUresult v) {
    const char *e;
    huGetErrorString(v, &e);
    return e;
};

inline const char* ToChar(HUresult v) {
    const char *e;
    huGetErrorString(v, &e);
    return e;
};

// Catch empty arguments case
inline std::string ToString() { return (""); }

// C++11 variadic template - peels off first argument, converts to string, and calls itself again to
// peel the next arg. Strings are automatically separated by comma+space.
template <typename T, typename... Args>
inline std::string ToString(T first, Args... args) {
    return ToString(first) + ", " + ToString(args...);
}

#define HU_INIT()
#define HU_TRACE_API 1

static inline uint64_t getTicks() { return hc::get_system_ticks(); }
extern uint64_t recordApiTrace(std::string* fullStr, const std::string& apiStr);

// Color defs for debug messages:
#define KRED "\x1B[31m"

extern const char* API_COLOR;
extern const char* API_COLOR_END;
#if 1
#define HU_API_TRACE(forceTrace, ...)                                                              \
    uint64_t hipApiStartTick = 0;                                                                  \
    {                                                                                              \
        if (forceTrace || HU_TRACE_API) {                                                          \
            std::string apiStr = std::string(__func__) + " (" + ToString(__VA_ARGS__) + ')';       \
            std::string fullStr;                                                                   \
            hipApiStartTick = recordApiTrace(&fullStr, apiStr);                                    \
        }                                                                                          \
    }
#else
// Swallow HU_API_TRACE
#define HU_API_TRACE(IS_CMD, ...)
#endif

// This macro should be called at the end of every HU API, and only at the end of top-level HU
// APIS (not internal HU). It prints the closing message when the debug trace is enabled.
#define ihuLogStatus(huStatus)                                                                      \
    ({                                                                                              \
        HUresult localHipStatus = huStatus; /*local copy so huStatus only evaluated once*/          \
        if (HU_TRACE_API) {                                                                         \
            auto ticks = getTicks() - hipApiStartTick;                                              \
            fprintf(stderr, "  %shu-api %-30s ret=%2d (%s)>> +%lu ns%s\n",                          \
                    (localHipStatus == 0) ? API_COLOR : KRED, __func__, localHipStatus,             \
                    ToChar(localHipStatus), ticks, API_COLOR_END);                                  \
        }                                                                                           \
        localHipStatus;                                                                             \
    })

#define HU_INIT_API(cid, ...) \
    HU_INIT() \
    HU_API_TRACE(0, __VA_ARGS__);

#endif /* HIP_SRC_HU_INTERNAL_H */

