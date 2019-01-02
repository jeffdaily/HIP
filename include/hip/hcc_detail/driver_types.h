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

#ifndef HIP_INCLUDE_HIP_HCC_DETAIL_DRIVER_TYPES_H
#define HIP_INCLUDE_HIP_HCC_DETAIL_DRIVER_TYPES_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

#if HIP_USE_ORIGINAL_TYPES

#include "runtime_types.h"

typedef void* hipDeviceptr_t;

#define HIP_TRSF_NORMALIZED_COORDINATES 0x01
#define HIP_TRSF_READ_AS_INTEGER 0x00
#define HIP_TRSA_OVERRIDE_FORMAT 0x01

typedef enum hipArray_Format {
    HIP_AD_FORMAT_UNSIGNED_INT8 = 0x01,
    HIP_AD_FORMAT_UNSIGNED_INT16 = 0x02,
    HIP_AD_FORMAT_UNSIGNED_INT32 = 0x03,
    HIP_AD_FORMAT_SIGNED_INT8 = 0x08,
    HIP_AD_FORMAT_SIGNED_INT16 = 0x09,
    HIP_AD_FORMAT_SIGNED_INT32 = 0x0a,
    HIP_AD_FORMAT_HALF = 0x10,
    HIP_AD_FORMAT_FLOAT = 0x20
}hipArray_Format;

typedef struct HIP_ARRAY_DESCRIPTOR_st_orig {
    hipArray_Format Format;
    unsigned int NumChannels;
    size_t Width;
    size_t Height;
    unsigned int Flags;
    size_t Depth;
}HIP_ARRAY_DESCRIPTOR_orig;
#define HIP_ARRAY_DESCRIPTOR HIP_ARRAY_DESCRIPTOR_orig
#define HIP_ARRAY3D_DESCRIPTOR HIP_ARRAY_DESCRIPTOR_orig

typedef struct hipArray {
    void* data;  // FIXME: generalize this
    struct hipChannelFormatDesc desc;
    unsigned int type;
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    HIP_ARRAY_DESCRIPTOR drvDesc;
    bool isDrv;
    unsigned int textureType;
}hipArray;

typedef struct hipArray* hipArray_t;

typedef const struct hipArray* hipArray_const_t;

typedef struct hip_Memcpy2D {
    size_t Height;
    size_t WidthInBytes;
    hipArray_t dstArray;
    hipDeviceptr_t dstDevice;
    void* dstHost;
    hipMemoryType dstMemoryType;
    size_t dstPitch;
    size_t dstXInBytes;
    size_t dstY;
    hipArray_t srcArray;
    hipDeviceptr_t srcDevice;
    const void* srcHost;
    hipMemoryType srcMemoryType;
    size_t srcPitch;
    size_t srcXInBytes;
    size_t srcY;
} hip_Memcpy2D;


// TODO: It needs to be modified since it was just copied from hipArray.
struct hipMipmappedArray {
    void* data;  // FIXME: generalize this
    struct hipChannelFormatDesc desc;
    unsigned int width;
    unsigned int height;
    unsigned int depth;
};

typedef struct hipMipmappedArray* hipMipmappedArray_t;

typedef const struct hipMipmappedArray* hipMipmappedArray_const_t;

/**
 * hip resource types
 */
typedef enum hipResourceType {
    hipResourceTypeArray = 0x00,
    hipResourceTypeMipmappedArray = 0x01,
    hipResourceTypeLinear = 0x02,
    hipResourceTypePitch2D = 0x03
}hipResourceType;

/**
 * hip texture resource view formats
 */
typedef enum hipResourceViewFormat {
    hipResViewFormatNone = 0x00,
    hipResViewFormatUnsignedChar1 = 0x01,
    hipResViewFormatUnsignedChar2 = 0x02,
    hipResViewFormatUnsignedChar4 = 0x03,
    hipResViewFormatSignedChar1 = 0x04,
    hipResViewFormatSignedChar2 = 0x05,
    hipResViewFormatSignedChar4 = 0x06,
    hipResViewFormatUnsignedShort1 = 0x07,
    hipResViewFormatUnsignedShort2 = 0x08,
    hipResViewFormatUnsignedShort4 = 0x09,
    hipResViewFormatSignedShort1 = 0x0a,
    hipResViewFormatSignedShort2 = 0x0b,
    hipResViewFormatSignedShort4 = 0x0c,
    hipResViewFormatUnsignedInt1 = 0x0d,
    hipResViewFormatUnsignedInt2 = 0x0e,
    hipResViewFormatUnsignedInt4 = 0x0f,
    hipResViewFormatSignedInt1 = 0x10,
    hipResViewFormatSignedInt2 = 0x11,
    hipResViewFormatSignedInt4 = 0x12,
    hipResViewFormatHalf1 = 0x13,
    hipResViewFormatHalf2 = 0x14,
    hipResViewFormatHalf4 = 0x15,
    hipResViewFormatFloat1 = 0x16,
    hipResViewFormatFloat2 = 0x17,
    hipResViewFormatFloat4 = 0x18,
    hipResViewFormatUnsignedBlockCompressed1 = 0x19,
    hipResViewFormatUnsignedBlockCompressed2 = 0x1a,
    hipResViewFormatUnsignedBlockCompressed3 = 0x1b,
    hipResViewFormatUnsignedBlockCompressed4 = 0x1c,
    hipResViewFormatSignedBlockCompressed4 = 0x1d,
    hipResViewFormatUnsignedBlockCompressed5 = 0x1e,
    hipResViewFormatSignedBlockCompressed5 = 0x1f,
    hipResViewFormatUnsignedBlockCompressed6H = 0x20,
    hipResViewFormatSignedBlockCompressed6H = 0x21,
    hipResViewFormatUnsignedBlockCompressed7 = 0x22
}hipResourceViewFormat;

/**
 * HIP resource descriptor
 */
typedef struct hipResourceDesc {
    enum hipResourceType resType;

    union {
        struct {
            hipArray_t hArray;
        } array;
        struct {
            hipMipmappedArray_t hMipmappedArray;
        } mipmap;
        struct {
            void* devPtr;
            struct hipChannelFormatDesc desc;
            size_t sizeInBytes;
        } linear;
        struct {
            void* devPtr;
            struct hipChannelFormatDesc desc;
            size_t width;
            size_t height;
            size_t pitchInBytes;
        } pitch2D;
    } res;
}hipResourceDesc;

/**
 * hip resource view descriptor
 */
struct hipResourceViewDesc {
    enum hipResourceViewFormat format;
    size_t width;
    size_t height;
    size_t depth;
    unsigned int firstMipmapLevel;
    unsigned int lastMipmapLevel;
    unsigned int firstLayer;
    unsigned int lastLayer;
};

typedef struct hipMemcpy3DParms {
    hipArray_t srcArray;
    struct hipPos srcPos;
    struct hipPitchedPtr srcPtr;

    hipArray_t dstArray;
    struct hipPos dstPos;
    struct hipPitchedPtr dstPtr;

    struct hipExtent extent;
    int kind;

    size_t Depth;
    size_t Height;
    size_t WidthInBytes;
    hipDeviceptr_t dstDevice;
    size_t dstHeight;
    void* dstHost;
    size_t dstLOD;
    hipMemoryType dstMemoryType;
    size_t dstPitch;
    size_t dstXInBytes;
    size_t dstY;
    size_t dstZ;
    void* reserved0;
    void* reserved1;
    hipDeviceptr_t srcDevice;
    size_t srcHeight;
    const void* srcHost;
    size_t srcLOD;
    hipMemoryType srcMemoryType;
    size_t srcPitch;
    size_t srcXInBytes;
    size_t srcY;
    size_t srcZ;
}hipMemcpy3DParms;

#else

#include "hip_driver.h"

#include "runtime_types.h"

typedef HUdeviceptr hipDeviceptr_t;

#define HIP_AD_FORMAT_UNSIGNED_INT8   HU_AD_FORMAT_UNSIGNED_INT8
#define HIP_AD_FORMAT_UNSIGNED_INT16  HU_AD_FORMAT_UNSIGNED_INT16
#define HIP_AD_FORMAT_UNSIGNED_INT32  HU_AD_FORMAT_UNSIGNED_INT32
#define HIP_AD_FORMAT_SIGNED_INT8     HU_AD_FORMAT_SIGNED_INT8
#define HIP_AD_FORMAT_SIGNED_INT16    HU_AD_FORMAT_SIGNED_INT16
#define HIP_AD_FORMAT_SIGNED_INT32    HU_AD_FORMAT_SIGNED_INT32
#define HIP_AD_FORMAT_HALF            HU_AD_FORMAT_HALF
#define HIP_AD_FORMAT_FLOAT           HU_AD_FORMAT_FLOAT
typedef HUarray_format hipArray_Format;

typedef struct HUarray_st {
    void* data;  // FIXME: generalize this
    struct hipChannelFormatDesc desc;
    unsigned int type;
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    HIP_ARRAY3D_DESCRIPTOR drvDesc;
    bool isDrv;
    unsigned int textureType;
} HUarray_st;

typedef HUarray_st hipArray;
typedef HUarray_st* hipArray_t;
typedef const HUarray_st* hipArray_const_t;

typedef struct HUmipmappedArray_st {
    void* data;  // FIXME: generalize this
    struct hipChannelFormatDesc desc;
    unsigned int width;
    unsigned int height;
    unsigned int depth;
} HUmipmappedArray_st;

typedef HUmipmappedArray_st* hipMipmappedArray_t;
typedef const HUmipmappedArray_st* hipMipmappedArray_const_t;

#define hipResourceTypeArray            HU_RESOURCE_TYPE_ARRAY
#define hipResourceTypeMipmappedArray   HU_RESOURCE_TYPE_MIPMAPPED_ARRAY
#define hipResourceTypeLinear           HU_RESOURCE_TYPE_LINEAR
#define hipResourceTypePitch2D          HU_RESOURCE_TYPE_PITCH2D
typedef HUresourcetype hipResourceType;

#define hipResViewFormatNone                        HU_RES_VIEW_FORMAT_NONE
#define hipResViewFormatUnsignedChar1               HU_RES_VIEW_FORMAT_UINT_1X8
#define hipResViewFormatUnsignedChar2               HU_RES_VIEW_FORMAT_UINT_2X8
#define hipResViewFormatUnsignedChar4               HU_RES_VIEW_FORMAT_UINT_4X8
#define hipResViewFormatSignedChar1                 HU_RES_VIEW_FORMAT_SINT_1X8
#define hipResViewFormatSignedChar2                 HU_RES_VIEW_FORMAT_SINT_2X8
#define hipResViewFormatSignedChar4                 HU_RES_VIEW_FORMAT_SINT_4X8
#define hipResViewFormatUnsignedShort1              HU_RES_VIEW_FORMAT_UINT_1X16
#define hipResViewFormatUnsignedShort2              HU_RES_VIEW_FORMAT_UINT_2X16
#define hipResViewFormatUnsignedShort4              HU_RES_VIEW_FORMAT_UINT_4X16
#define hipResViewFormatSignedShort1                HU_RES_VIEW_FORMAT_SINT_1X16
#define hipResViewFormatSignedShort2                HU_RES_VIEW_FORMAT_SINT_2X16
#define hipResViewFormatSignedShort4                HU_RES_VIEW_FORMAT_SINT_4X16
#define hipResViewFormatUnsignedInt1                HU_RES_VIEW_FORMAT_UINT_1X32
#define hipResViewFormatUnsignedInt2                HU_RES_VIEW_FORMAT_UINT_2X32
#define hipResViewFormatUnsignedInt4                HU_RES_VIEW_FORMAT_UINT_4X32
#define hipResViewFormatSignedInt1                  HU_RES_VIEW_FORMAT_SINT_1X32
#define hipResViewFormatSignedInt2                  HU_RES_VIEW_FORMAT_SINT_2X32
#define hipResViewFormatSignedInt4                  HU_RES_VIEW_FORMAT_SINT_4X32
#define hipResViewFormatHalf1                       HU_RES_VIEW_FORMAT_FLOAT_1X16
#define hipResViewFormatHalf2                       HU_RES_VIEW_FORMAT_FLOAT_2X16
#define hipResViewFormatHalf4                       HU_RES_VIEW_FORMAT_FLOAT_4X16
#define hipResViewFormatFloat1                      HU_RES_VIEW_FORMAT_FLOAT_1X32
#define hipResViewFormatFloat2                      HU_RES_VIEW_FORMAT_FLOAT_2X32
#define hipResViewFormatFloat4                      HU_RES_VIEW_FORMAT_FLOAT_4X32
#define hipResViewFormatUnsignedBlockCompressed1    HU_RES_VIEW_FORMAT_UNSIGNED_BC1
#define hipResViewFormatUnsignedBlockCompressed2    HU_RES_VIEW_FORMAT_UNSIGNED_BC2
#define hipResViewFormatUnsignedBlockCompressed3    HU_RES_VIEW_FORMAT_UNSIGNED_BC3
#define hipResViewFormatUnsignedBlockCompressed4    HU_RES_VIEW_FORMAT_UNSIGNED_BC4
#define hipResViewFormatSignedBlockCompressed4      HU_RES_VIEW_FORMAT_SIGNED_BC4
#define hipResViewFormatUnsignedBlockCompressed5    HU_RES_VIEW_FORMAT_UNSIGNED_BC5
#define hipResViewFormatSignedBlockCompressed5      HU_RES_VIEW_FORMAT_SIGNED_BC5
#define hipResViewFormatUnsignedBlockCompressed6H   HU_RES_VIEW_FORMAT_UNSIGNED_BC6H
#define hipResViewFormatSignedBlockCompressed6H     HU_RES_VIEW_FORMAT_SIGNED_BC6H
#define hipResViewFormatUnsignedBlockCompressed7    HU_RES_VIEW_FORMAT_UNSIGNED_BC7
typedef HUresourceViewFormat hipResourceViewFormat;

typedef HIP_MEMCPY2D hip_Memcpy2D;
typedef HIP_MEMCPY3D hipMemcpy3DParms;
typedef HIP_RESOURCE_DESC hipResourceDesc;
typedef HIP_RESOURCE_VIEW_DESC hipResourceViewDesc;

#endif /* HIP_USE_ORIGINAL_TYPES */

#endif /* HIP_INCLUDE_HIP_HCC_DETAIL_DRIVER_TYPES_H */
