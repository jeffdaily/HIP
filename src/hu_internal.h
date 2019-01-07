/*
Copyright (c) 2015 - present Advanced Micro Devices, Inc. All rights reserved.

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

#include "hip_hcc_internal.h"
#include "hip/hip_runtime_api.h"

#if 0
std::ostream& operator<<(std::ostream& os, const HUstream_st& s);
std::ostream& operator<<(std::ostream& os, const HUipcEventHandle_st& s);
std::ostream& operator<<(std::ostream& os, const HUipcMemHandle_st& s);

// Helper functions to convert HU function arguments into strings.
// Handles POD data types as well as enumerations.
// The implementation uses C++11 variadic templates and template specialization.

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
#endif

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


// This macro should be called at the end of every HU API, and only at the end of top-level HU
// APIS (not internal HU). It prints the closing message when the debug trace is enabled.
//        printf("=%d\n", huStatus);
//        if (localHuStatus == HIP_ERROR_NOT_SUPPORTED) printf("FIX ME!!\n");
#define ihuLogStatus(huStatus)                                                                      \
    ({                                                                                              \
        HUresult localHuStatus = huStatus; /*local copy so huStatus only evaluated once*/          \
        if (_hu_trace) printf("=%d %s\n", localHuStatus, localHuStatus == HIP_ERROR_NOT_SUPPORTED ? "FIX ME!" : "OK"); \
        localHuStatus;                                                                             \
    })

// Just initialize the HIP runtime, but don't log any trace information.
#define HU_INIT()                               \
    std::call_once(hip_initialized, ihipInit);  \
    ihipCtxStackUpdate();

#define HU_API_TRACE(IS_CMD, ...)

//{ static bool done = false; if (!done) { printf("%s\n", #cid); done = true; } }
//{ printf("%s", #cid); }
#define HU_INIT_API(cid, ...) \
    static bool _hu_trace = getenv("HU_TRACE") != NULL; \
    if (_hu_trace) { printf("%s : %d : %s", __FILE__, __LINE__, #cid); } \
    HU_INIT() \
    HU_API_TRACE(0, __VA_ARGS__);

#endif /* HIP_SRC_HU_INTERNAL_H */

