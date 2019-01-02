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

#ifndef HIP_INCLUDE_HIP_HCC_DETAIL_RUNTIME_TYPES_H
#define HIP_INCLUDE_HIP_HCC_DETAIL_RUNTIME_TYPES_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

typedef enum hipChannelFormatKind {
    hipChannelFormatKindSigned = 0,
    hipChannelFormatKindUnsigned = 1,
    hipChannelFormatKindFloat = 2,
    hipChannelFormatKindNone = 3
}hipChannelFormatKind;

typedef struct hipChannelFormatDesc {
    int x;
    int y;
    int z;
    int w;
    enum hipChannelFormatKind f;
}hipChannelFormatDesc;

/**
 * Memory copy types
 *
 */
typedef enum hipMemcpyKind {
    hipMemcpyHostToHost = 0,      ///< Host-to-Host Copy
    hipMemcpyHostToDevice = 1,    ///< Host-to-Device Copy
    hipMemcpyDeviceToHost = 2,    ///< Device-to-Host Copy
    hipMemcpyDeviceToDevice = 3,  ///< Device-to-Device Copy
    hipMemcpyDefault =
        4  ///< Runtime will automatically determine copy-kind based on virtual addresses.
} hipMemcpyKind;

typedef struct hipPitchedPtr {
    void* ptr;
    size_t pitch;
    size_t xsize;
    size_t ysize;
}hipPitchedPtr;

typedef struct hipExtent {
    size_t width;  // Width in elements when referring to array memory, in bytes when referring to
                   // linear memory
    size_t height;
    size_t depth;
}hipExtent;

typedef struct hipPos {
    size_t x;
    size_t y;
    size_t z;
}hipPos;

static __inline__ struct hipPitchedPtr make_hipPitchedPtr(void* d, size_t p, size_t xsz,
                                                          size_t ysz) {
    struct hipPitchedPtr s;

    s.ptr = d;
    s.pitch = p;
    s.xsize = xsz;
    s.ysize = ysz;

    return s;
}

static __inline__ struct hipPos make_hipPos(size_t x, size_t y, size_t z) {
    struct hipPos p;

    p.x = x;
    p.y = y;
    p.z = z;

    return p;
}

static __inline__ struct hipExtent make_hipExtent(size_t w, size_t h, size_t d) {
    struct hipExtent e;

    e.width = w;
    e.height = h;
    e.depth = d;

    return e;
}

#endif /* HIP_INCLUDE_HIP_HCC_DETAIL_RUNTIME_TYPES_H */

