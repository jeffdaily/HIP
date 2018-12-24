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
#include <hsa/hsa.h>
#include <hsa/hsa_ext_amd.h>

#include "hip/hip_common.h"
#include "hip/hip_driver.h"
#include "env.h"

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

//---
// Environment variables:

// Intended to distinguish whether an environment variable should be visible only in debug mode, or
// in debug+release.
// static const int debug = 0;
extern const int release;

// TODO - this blocks both kernels and memory ops.  Perhaps should have separate env var for
// kernels?
extern int HIP_LAUNCH_BLOCKING;
extern int HIP_API_BLOCKING;

extern int HIP_PRINT_ENV;
extern int HIP_PROFILE_API;
// extern int HIP_TRACE_API;
extern int HIP_ATP;
extern int HIP_DB;
extern int HIP_STAGING_SIZE;    /* size of staging buffers, in KB */
extern int HIP_STREAM_SIGNALS;  /* number of signals to allocate at stream creation */
extern int HIP_VISIBLE_DEVICES; /* Contains a comma-separated sequence of GPU identifiers */
extern int HIP_FORCE_P2P_HOST;

extern int HIP_HOST_COHERENT;

extern int HIP_HIDDEN_FREE_MEM;
//---
// Chicken bits for disabling functionality to work around potential issues:
extern int HIP_SYNC_HOST_ALLOC;
extern int HIP_SYNC_STREAM_WAIT;

extern int HIP_SYNC_NULL_STREAM;
extern int HIP_INIT_ALLOC;
extern int HIP_FORCE_NULL_STREAM;

extern int HIP_DUMP_CODE_OBJECT;

// TODO - remove when this is standard behavior.
extern int HCC_OPT_FLUSH;

// Class to assign a short TID to each new thread, for HIP debugging purposes.
class TidInfo {
   public:
    TidInfo();

    int tid() const { return _shortTid; };
    pid_t pid() const { return _pid; };
    uint64_t incApiSeqNum() { return ++_apiSeqNum; };
    uint64_t apiSeqNum() const { return _apiSeqNum; };

   private:
    int _shortTid;
    pid_t _pid;

    // monotonically increasing API sequence number for this threa.
    uint64_t _apiSeqNum;
};

struct ThreadLocalData {
    TidInfo tid;
};

struct ThreadLocalData* get_tls();

#define HU_TLS() struct ThreadLocalData* tls = get_tls()

// A macro to disallow the copy constructor and operator= functions
// This is usually placed in the private: declarations for a class.
#define HU_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;         \
  void operator=(const TypeName&) = delete

#ifdef _MSC_VER
#define __thread __declspec(thread)
#else
#define __thread thread_local
#endif

// For POD types in TLS mode, s_obj_VAR is the thread-local variable.
#define HU_STATIC_THREAD_LOCAL_POD(_Type_, _var_)               \
  static __thread _Type_ s_obj_##_var_;                         \
  namespace {                                                   \
  class ThreadLocal_##_var_ {                                   \
  public:                                                       \
    ThreadLocal_##_var_() {}                                    \
    void Init() {}                                              \
    inline _Type_ *pointer() const {                            \
      return &s_obj_##_var_;                                    \
    }                                                           \
    inline _Type_ *safe_pointer() const {                       \
      return &s_obj_##_var_;                                    \
    }                                                           \
    _Type_ &get() const {                                       \
      return s_obj_##_var_;                                     \
    }                                                           \
    bool is_native_tls() const { return true; }                 \
  private:                                                      \
    HU_DISALLOW_COPY_AND_ASSIGN(ThreadLocal_##_var_);           \
  } _var_;                                                      \
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

