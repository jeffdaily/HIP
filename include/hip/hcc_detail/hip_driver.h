/*
 * Copyright 1993-2014 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO LICENSEE:
 *
 * This source code and/or documentation ("Licensed Deliverables") are
 * subject to NVIDIA intellectual property rights under U.S. and
 * international Copyright laws.
 *
 * These Licensed Deliverables contained herein is PROPRIETARY and
 * CONFIDENTIAL to NVIDIA and is being provided under the terms and
 * conditions of a form of NVIDIA software license agreement by and
 * between NVIDIA and Licensee ("License Agreement") or electronically
 * accepted by Licensee.  Notwithstanding any terms or conditions to
 * the contrary in the License Agreement, reproduction or disclosure
 * of the Licensed Deliverables to any third party without the express
 * written consent of NVIDIA is prohibited.
 *
 * NOTWITHSTANDING ANY TERMS OR CONDITIONS TO THE CONTRARY IN THE
 * LICENSE AGREEMENT, NVIDIA MAKES NO REPRESENTATION ABOUT THE
 * SUITABILITY OF THESE LICENSED DELIVERABLES FOR ANY PURPOSE.  IT IS
 * PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.
 * NVIDIA DISCLAIMS ALL WARRANTIES WITH REGARD TO THESE LICENSED
 * DELIVERABLES, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * NOTWITHSTANDING ANY TERMS OR CONDITIONS TO THE CONTRARY IN THE
 * LICENSE AGREEMENT, IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY
 * SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THESE LICENSED DELIVERABLES.
 *
 * U.S. Government End Users.  These Licensed Deliverables are a
 * "commercial item" as that term is defined at 48 C.F.R. 2.101 (OCT
 * 1995), consisting of "commercial computer software" and "commercial
 * computer software documentation" as such terms are used in 48
 * C.F.R. 12.212 (SEPT 1995) and is provided to the U.S. Government
 * only as a commercial end item.  Consistent with 48 C.F.R.12.212 and
 * 48 C.F.R. 227.7202-1 through 227.7202-4 (JUNE 1995), all
 * U.S. Government End Users acquire the Licensed Deliverables with
 * only those rights set forth herein.
 *
 * Any use of the Licensed Deliverables in individual and commercial
 * software must include, in the user documentation and internal
 * comments to the code, the above Disclaimer and U.S. Government End
 * Users Notice.
 */

#ifndef HIP_INCLUDE_HIP_HCC_DETAIL_HIP_DRIVER_H
#define HIP_INCLUDE_HIP_HCC_DETAIL_HIP_DRIVER_H

#include <stdlib.h>
#ifdef _MSC_VER
typedef unsigned __int32 huuint32_t;
typedef unsigned __int64 huuint64_t;
#else
#include <stdint.h>
typedef uint32_t huuint32_t;
typedef uint64_t huuint64_t;
#endif

// __TEMP_WAR__ 200338925 - define manually for ARM/AARCH64 to enable promotion
#if !defined(HIP_ENABLE_DEPRECATED) && (defined(__arm__) || defined(__aarch64__))
#define HIP_ENABLE_DEPRECATED
#endif

/**
 * HIP API versioning support
 */
#if defined(__HIP_API_VERSION_INTERNAL) || defined(__DOXYGEN_ONLY__) || defined(HIP_ENABLE_DEPRECATED)
#define __HIP_DEPRECATED
#elif defined(_MSC_VER)
#define __HIP_DEPRECATED __declspec(deprecated)
#elif defined(__GNUC__)
#define __HIP_DEPRECATED __attribute__((deprecated))
#else
#define __HIP_DEPRECATED
#endif

/**
 * \defgroup HIP_TYPES Data types used by HIP driver
 * @{
 */

/**
 * HIP API version number
 */
#define HIP_VERSION 2000

#ifdef __cplusplus
extern "C" {
#endif

#if 0
/**
 * HIP device pointer
 * HUdeviceptr is defined as an unsigned integer type whose size matches the size of a pointer on the target platform.
 */ 
#if defined(_WIN64) || defined(__LP64__)
typedef unsigned long long HUdeviceptr;
#else
typedef unsigned int HUdeviceptr;
#endif
#else
typedef void* HUdeviceptr;
#endif

typedef int HUdevice;                                     /**< HIP device */
typedef struct HUctx_st *HUcontext;                       /**< HIP context */
typedef struct HUmod_st *HUmodule;                        /**< HIP module */
typedef struct HUfunc_st *HUfunction;                     /**< HIP function */
typedef struct HUarray_st *HUarray;                       /**< HIP array */
typedef struct HUmipmappedArray_st *HUmipmappedArray;     /**< HIP mipmapped array */
typedef struct HUtexref_st *HUtexref;                     /**< HIP texture reference */
typedef struct HUsurfref_st *HUsurfref;                   /**< HIP surface reference */
typedef struct HUevent_st *HUevent;                       /**< HIP event */
typedef struct HUstream_st *HUstream;                     /**< HIP stream */
typedef struct HUgraphicsResource_st *HUgraphicsResource; /**< HIP graphics interop resource */
typedef unsigned long long HUtexObject;                   /**< An opaque value that represents a HIP texture object */
typedef unsigned long long HUsurfObject;                  /**< An opaque value that represents a HIP surface object */

typedef struct HUuuid_st {                                /**< HIP definition of UUID */
    char bytes[16];
} HUuuid;

/**
 * HIP IPC handle size 
 */
#define HU_IPC_HANDLE_SIZE 64

/**
 * HIP IPC event handle
 */
typedef struct HUipcEventHandle_st {
    char reserved[HU_IPC_HANDLE_SIZE];
} HUipcEventHandle;

/**
 * HIP IPC mem handle
 */
typedef struct HUipcMemHandle_st {
    char reserved[HU_IPC_HANDLE_SIZE];
} HUipcMemHandle;

/**
 * HIP Ipc Mem Flags
 */
typedef enum HUipcMem_flags_enum {
    HU_IPC_MEM_LAZY_ENABLE_PEER_ACCESS = 0x1 /**< Automatically enable peer access between remote devices as needed */
} HUipcMem_flags;

/**
 * HIP Mem Attach Flags
 */
typedef enum HUmemAttach_flags_enum {
    HU_MEM_ATTACH_GLOBAL = 0x1, /**< Memory can be accessed by any stream on any device */
    HU_MEM_ATTACH_HOST   = 0x2, /**< Memory cannot be accessed by any stream on any device */
    HU_MEM_ATTACH_SINGLE = 0x4  /**< Memory can only be accessed by a single stream on the associated device */
} HUmemAttach_flags;

/**
 * Context creation flags
 */
typedef enum HUctx_flags_enum {
    HU_CTX_SCHED_AUTO          = 0x00, /**< Automatic scheduling */
    HU_CTX_SCHED_SPIN          = 0x01, /**< Set spin as default scheduling */
    HU_CTX_SCHED_YIELD         = 0x02, /**< Set yield as default scheduling */
    HU_CTX_SCHED_BLOCKING_SYNC = 0x04, /**< Set blocking synchronization as default scheduling */
    HU_CTX_BLOCKING_SYNC       = 0x04, /**< Set blocking synchronization as default scheduling
                                         *  \deprecated This flag was deprecated as of HIP 4.0
                                         *  and was replaced with ::HU_CTX_SCHED_BLOCKING_SYNC. */
    HU_CTX_SCHED_MASK          = 0x07, 
    HU_CTX_MAP_HOST            = 0x08, /**< Support mapped pinned allocations */
    HU_CTX_LMEM_RESIZE_TO_MAX  = 0x10, /**< Keep local memory allocation after launch */
    HU_CTX_FLAGS_MASK          = 0x1f
} HUctx_flags;

/**
 * Stream creation flags
 */
typedef enum HUstream_flags_enum {
    HU_STREAM_DEFAULT      = 0x0, /**< Default stream flag */
    HU_STREAM_NON_BLOCKING = 0x1  /**< Stream does not synchronize with stream 0 (the NULL stream) */
} HUstream_flags;

/**
 * Legacy stream handle
 *
 * Stream handle that can be passed as a HUstream to use an implicit stream
 * with legacy synchronization behavior.
 *
 * See details of the \link_sync_behavior
 */
#define HU_STREAM_LEGACY     ((HUstream)0x1)

/**
 * Per-thread stream handle
 *
 * Stream handle that can be passed as a HUstream to use an implicit stream
 * with per-thread synchronization behavior.
 *
 * See details of the \link_sync_behavior
 */
#define HU_STREAM_PER_THREAD ((HUstream)0x2)

/**
 * Event creation flags
 */
typedef enum HUevent_flags_enum {
    HU_EVENT_DEFAULT        = 0x0, /**< Default event flag */
    HU_EVENT_BLOCKING_SYNC  = 0x1, /**< Event uses blocking synchronization */
    HU_EVENT_DISABLE_TIMING = 0x2, /**< Event will not record timing data */
    HU_EVENT_INTERPROCESS   = 0x4  /**< Event is suitable for interprocess use. HU_EVENT_DISABLE_TIMING must be set */
} HUevent_flags;

/**
 * Flags for ::huStreamWaitValue32 and ::huStreamWaitValue64
 */
typedef enum HUstreamWaitValue_flags_enum {
    HU_STREAM_WAIT_VALUE_GEQ   = 0x0,   /**< Wait until (int32_t)(*addr - value) >= 0 (or int64_t for 64 bit
                                             values). Note this is a cyclic comparison which ignores wraparound.
                                             (Default behavior.) */
    HU_STREAM_WAIT_VALUE_EQ    = 0x1,   /**< Wait until *addr == value. */
    HU_STREAM_WAIT_VALUE_AND   = 0x2,   /**< Wait until (*addr & value) != 0. */
    HU_STREAM_WAIT_VALUE_NOR   = 0x3,   /**< Wait until ~(*addr | value) != 0. Support for this operation can be
                                             queried with ::huDeviceGetAttribute() and
                                             ::HU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_WAIT_VALUE_NOR.*/
    HU_STREAM_WAIT_VALUE_FLUSH = 1<<30  /**< Follow the wait operation with a flush of outstanding remote writes. This
                                             means that, if a remote write operation is guaranteed to have reached the
                                             device before the wait can be satisfied, that write is guaranteed to be
                                             visible to downstream device work. The device is permitted to reorder
                                             remote writes internally. For example, this flag would be required if
                                             two remote writes arrive in a defined order, the wait is satisfied by the
                                             second write, and downstream work needs to observe the first write.
                                             Support for this operation is restricted to selected platforms and can be 
                                             queried with ::HU_DEVICE_ATTRIBUTE_CAN_USE_WAIT_VALUE_FLUSH.*/
} HUstreamWaitValue_flags;

/**
 * Flags for ::huStreamWriteValue32
 */
typedef enum HUstreamWriteValue_flags_enum {
    HU_STREAM_WRITE_VALUE_DEFAULT           = 0x0, /**< Default behavior */
    HU_STREAM_WRITE_VALUE_NO_MEMORY_BARRIER = 0x1  /**< Permits the write to be reordered with writes which were issued
                                                        before it, as a performance optimization. Normally,
                                                        ::huStreamWriteValue32 will provide a memory fence before the
                                                        write, which has similar semantics to
                                                        __threadfence_system() but is scoped to the stream
                                                        rather than a HIP thread. */
} HUstreamWriteValue_flags;

/**
 * Operations for ::huStreamBatchMemOp
 */
typedef enum HUstreamBatchMemOpType_enum {
    HU_STREAM_MEM_OP_WAIT_VALUE_32  = 1,     /**< Represents a ::huStreamWaitValue32 operation */
    HU_STREAM_MEM_OP_WRITE_VALUE_32 = 2,     /**< Represents a ::huStreamWriteValue32 operation */
    HU_STREAM_MEM_OP_WAIT_VALUE_64  = 4,     /**< Represents a ::huStreamWaitValue64 operation */
    HU_STREAM_MEM_OP_WRITE_VALUE_64 = 5,     /**< Represents a ::huStreamWriteValue64 operation */
    HU_STREAM_MEM_OP_FLUSH_REMOTE_WRITES = 3 /**< This has the same effect as ::HU_STREAM_WAIT_VALUE_FLUSH, but as a
                                                  standalone operation. */
} HUstreamBatchMemOpType;

/**
 * Per-operation parameters for ::huStreamBatchMemOp
 */
typedef union HUstreamBatchMemOpParams_union {
    HUstreamBatchMemOpType operation;
    struct HUstreamMemOpWaitValueParams_st {
        HUstreamBatchMemOpType operation;
        HUdeviceptr address;
        union {
            huuint32_t value;
            huuint64_t value64;
        };
        unsigned int flags;
        HUdeviceptr alias; /**< For driver internal use. Initial value is unimportant. */
    } waitValue;
    struct HUstreamMemOpWriteValueParams_st {
        HUstreamBatchMemOpType operation;
        HUdeviceptr address;
        union {
            huuint32_t value;
            huuint64_t value64;
        };
        unsigned int flags;
        HUdeviceptr alias; /**< For driver internal use. Initial value is unimportant. */
    } writeValue;
    struct HUstreamMemOpFlushRemoteWritesParams_st {
        HUstreamBatchMemOpType operation;
        unsigned int flags;
    } flushRemoteWrites;
    huuint64_t pad[6];
} HUstreamBatchMemOpParams;

/**
 * Occupancy calculator flag
 */
typedef enum HUoccupancy_flags_enum {
    HU_OCCUPANCY_DEFAULT                  = 0x0, /**< Default behavior */
    HU_OCCUPANCY_DISABLE_CACHING_OVERRIDE = 0x1  /**< Assume global caching is enabled and cannot be automatically turned off */
} HUoccupancy_flags;

/**
 * Array formats
 */
typedef enum HUarray_format_enum {
    HU_AD_FORMAT_UNSIGNED_INT8  = 0x01, /**< Unsigned 8-bit integers */
    HU_AD_FORMAT_UNSIGNED_INT16 = 0x02, /**< Unsigned 16-bit integers */
    HU_AD_FORMAT_UNSIGNED_INT32 = 0x03, /**< Unsigned 32-bit integers */
    HU_AD_FORMAT_SIGNED_INT8    = 0x08, /**< Signed 8-bit integers */
    HU_AD_FORMAT_SIGNED_INT16   = 0x09, /**< Signed 16-bit integers */
    HU_AD_FORMAT_SIGNED_INT32   = 0x0a, /**< Signed 32-bit integers */
    HU_AD_FORMAT_HALF           = 0x10, /**< 16-bit floating point */
    HU_AD_FORMAT_FLOAT          = 0x20  /**< 32-bit floating point */
} HUarray_format;

/**
 * Texture reference addressing modes
 */
typedef enum HUaddress_mode_enum {
    HU_TR_ADDRESS_MODE_WRAP   = 0, /**< Wrapping address mode */
    HU_TR_ADDRESS_MODE_CLAMP  = 1, /**< Clamp to edge address mode */
    HU_TR_ADDRESS_MODE_MIRROR = 2, /**< Mirror address mode */
    HU_TR_ADDRESS_MODE_BORDER = 3  /**< Border address mode */
} HUaddress_mode;

/**
 * Texture reference filtering modes
 */
typedef enum HUfilter_mode_enum {
    HU_TR_FILTER_MODE_POINT  = 0, /**< Point filter mode */
    HU_TR_FILTER_MODE_LINEAR = 1  /**< Linear filter mode */
} HUfilter_mode;

/**
 * Device properties
 */
typedef enum HUdevice_attribute_enum {
    HU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK = 1,              /**< Maximum number of threads per block */
    HU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X = 2,                    /**< Maximum block dimension X */
    HU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y = 3,                    /**< Maximum block dimension Y */
    HU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z = 4,                    /**< Maximum block dimension Z */
    HU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X = 5,                     /**< Maximum grid dimension X */
    HU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Y = 6,                     /**< Maximum grid dimension Y */
    HU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Z = 7,                     /**< Maximum grid dimension Z */
    HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK = 8,        /**< Maximum shared memory available per block in bytes */
    HU_DEVICE_ATTRIBUTE_SHARED_MEMORY_PER_BLOCK = 8,            /**< Deprecated, use HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK */
    HU_DEVICE_ATTRIBUTE_TOTAL_CONSTANT_MEMORY = 9,              /**< Memory available on device for __constant__ variables in a HIP C kernel in bytes */
    HU_DEVICE_ATTRIBUTE_WARP_SIZE = 10,                         /**< Warp size in threads */
    HU_DEVICE_ATTRIBUTE_MAX_PITCH = 11,                         /**< Maximum pitch in bytes allowed by memory copies */
    HU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_BLOCK = 12,           /**< Maximum number of 32-bit registers available per block */
    HU_DEVICE_ATTRIBUTE_REGISTERS_PER_BLOCK = 12,               /**< Deprecated, use HU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_BLOCK */
    HU_DEVICE_ATTRIBUTE_CLOCK_RATE = 13,                        /**< Typical clock frequency in kilohertz */
    HU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT = 14,                 /**< Alignment requirement for textures */
    HU_DEVICE_ATTRIBUTE_GPU_OVERLAP = 15,                       /**< Device can possibly copy memory and execute a kernel concurrently. Deprecated. Use instead HU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT. */
    HU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT = 16,              /**< Number of multiprocessors on device */
    HU_DEVICE_ATTRIBUTE_KERNEL_EXEC_TIMEOUT = 17,               /**< Specifies whether there is a run time limit on kernels */
    HU_DEVICE_ATTRIBUTE_INTEGRATED = 18,                        /**< Device is integrated with host memory */
    HU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY = 19,               /**< Device can map host memory into HIP address space */
    HU_DEVICE_ATTRIBUTE_COMPUTE_MODE = 20,                      /**< Compute mode (See ::HUcomputemode for details) */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_WIDTH = 21,           /**< Maximum 1D texture width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_WIDTH = 22,           /**< Maximum 2D texture width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_HEIGHT = 23,          /**< Maximum 2D texture height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH = 24,           /**< Maximum 3D texture width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT = 25,          /**< Maximum 3D texture height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH = 26,           /**< Maximum 3D texture depth */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_WIDTH = 27,   /**< Maximum 2D layered texture width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_HEIGHT = 28,  /**< Maximum 2D layered texture height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_LAYERS = 29,  /**< Maximum layers in a 2D layered texture */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_WIDTH = 27,     /**< Deprecated, use HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_WIDTH */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_HEIGHT = 28,    /**< Deprecated, use HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_HEIGHT */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_NUMSLICES = 29, /**< Deprecated, use HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_LAYERS */
    HU_DEVICE_ATTRIBUTE_SURFACE_ALIGNMENT = 30,                 /**< Alignment requirement for surfaces */
    HU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS = 31,                /**< Device can possibly execute multiple kernels concurrently */
    HU_DEVICE_ATTRIBUTE_ECC_ENABLED = 32,                       /**< Device has ECC support enabled */
    HU_DEVICE_ATTRIBUTE_PCI_BUS_ID = 33,                        /**< PCI bus ID of the device */
    HU_DEVICE_ATTRIBUTE_PCI_DEVICE_ID = 34,                     /**< PCI device ID of the device */
    HU_DEVICE_ATTRIBUTE_TCC_DRIVER = 35,                        /**< Device is using TCC driver model */
    HU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE = 36,                 /**< Peak memory clock frequency in kilohertz */
    HU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH = 37,           /**< Global memory bus width in bits */
    HU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE = 38,                     /**< Size of L2 cache in bytes */
    HU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR = 39,    /**< Maximum resident threads per multiprocessor */
    HU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT = 40,                /**< Number of asynchronous engines */
    HU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING = 41,                /**< Device shares a unified address space with the host */    
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_WIDTH = 42,   /**< Maximum 1D layered texture width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_LAYERS = 43,  /**< Maximum layers in a 1D layered texture */
    HU_DEVICE_ATTRIBUTE_CAN_TEX2D_GATHER = 44,                  /**< Deprecated, do not use. */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_WIDTH = 45,    /**< Maximum 2D texture width if HIP_ARRAY3D_TEXTURE_GATHER is set */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_HEIGHT = 46,   /**< Maximum 2D texture height if HIP_ARRAY3D_TEXTURE_GATHER is set */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH_ALTERNATE = 47, /**< Alternate maximum 3D texture width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT_ALTERNATE = 48,/**< Alternate maximum 3D texture height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH_ALTERNATE = 49, /**< Alternate maximum 3D texture depth */
    HU_DEVICE_ATTRIBUTE_PCI_DOMAIN_ID = 50,                     /**< PCI domain ID of the device */
    HU_DEVICE_ATTRIBUTE_TEXTURE_PITCH_ALIGNMENT = 51,           /**< Pitch alignment requirement for textures */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_WIDTH = 52,      /**< Maximum hubemap texture width/height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_WIDTH = 53,  /**< Maximum hubemap layered texture width/height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_LAYERS = 54, /**< Maximum layers in a hubemap layered texture */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_WIDTH = 55,           /**< Maximum 1D surface width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_WIDTH = 56,           /**< Maximum 2D surface width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_HEIGHT = 57,          /**< Maximum 2D surface height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_WIDTH = 58,           /**< Maximum 3D surface width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_HEIGHT = 59,          /**< Maximum 3D surface height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_DEPTH = 60,           /**< Maximum 3D surface depth */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_WIDTH = 61,   /**< Maximum 1D layered surface width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_LAYERS = 62,  /**< Maximum layers in a 1D layered surface */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_WIDTH = 63,   /**< Maximum 2D layered surface width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_HEIGHT = 64,  /**< Maximum 2D layered surface height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_LAYERS = 65,  /**< Maximum layers in a 2D layered surface */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_WIDTH = 66,      /**< Maximum hubemap surface width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_WIDTH = 67,  /**< Maximum hubemap layered surface width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_LAYERS = 68, /**< Maximum layers in a hubemap layered surface */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LINEAR_WIDTH = 69,    /**< Maximum 1D linear texture width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_WIDTH = 70,    /**< Maximum 2D linear texture width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_HEIGHT = 71,   /**< Maximum 2D linear texture height */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_PITCH = 72,    /**< Maximum 2D linear texture pitch in bytes */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_WIDTH = 73, /**< Maximum mipmapped 2D texture width */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_HEIGHT = 74,/**< Maximum mipmapped 2D texture height */
    HU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MAJOR = 75,          /**< Major compute capability version number */     
    HU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MINOR = 76,          /**< Minor compute capability version number */
    HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_MIPMAPPED_WIDTH = 77, /**< Maximum mipmapped 1D texture width */
    HU_DEVICE_ATTRIBUTE_STREAM_PRIORITIES_SUPPORTED = 78,       /**< Device supports stream priorities */
    HU_DEVICE_ATTRIBUTE_GLOBAL_L1_CACHE_SUPPORTED = 79,         /**< Device supports caching globals in L1 */
    HU_DEVICE_ATTRIBUTE_LOCAL_L1_CACHE_SUPPORTED = 80,          /**< Device supports caching locals in L1 */
    HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_MULTIPROCESSOR = 81,  /**< Maximum shared memory available per multiprocessor in bytes */
    HU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_MULTIPROCESSOR = 82,  /**< Maximum number of 32-bit registers available per multiprocessor */
    HU_DEVICE_ATTRIBUTE_MANAGED_MEMORY = 83,                    /**< Device can allocate managed memory on this system */
    HU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD = 84,                    /**< Device is on a multi-GPU board */ 
    HU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD_GROUP_ID = 85,           /**< Unique id for a group of devices on the same multi-GPU board */
    HU_DEVICE_ATTRIBUTE_HOST_NATIVE_ATOMIC_SUPPORTED = 86,       /**< Link between the device and the host supports native atomic operations (this is a placeholder attribute, and is not supported on any current hardware)*/
    HU_DEVICE_ATTRIBUTE_SINGLE_TO_DOUBLE_PRECISION_PERF_RATIO = 87,  /**< Ratio of single precision performance (in floating-point operations per second) to double precision performance */
    HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS = 88,            /**< Device supports coherently accessing pageable memory without calling hipHostRegister on it */
    HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS = 89,         /**< Device can coherently access managed memory concurrently with the CPU */
    HU_DEVICE_ATTRIBUTE_COMPUTE_PREEMPTION_SUPPORTED = 90,      /**< Device supports compute preemption. */
    HU_DEVICE_ATTRIBUTE_CAN_USE_HOST_POINTER_FOR_REGISTERED_MEM = 91, /**< Device can access host registered memory at the same virtual address as the CPU */
    HU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_MEM_OPS = 92,            /**< ::huStreamBatchMemOp and related APIs are supported. */
    HU_DEVICE_ATTRIBUTE_CAN_USE_64_BIT_STREAM_MEM_OPS = 93,     /**< 64-bit operations are supported in ::huStreamBatchMemOp and related APIs. */
    HU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_WAIT_VALUE_NOR = 94,     /**< ::HU_STREAM_WAIT_VALUE_NOR is supported. */
    HU_DEVICE_ATTRIBUTE_COOPERATIVE_LAUNCH = 95,                /**< Device supports launching cooperative kernels via ::huLaunchCooperativeKernel */
    HU_DEVICE_ATTRIBUTE_COOPERATIVE_MULTI_DEVICE_LAUNCH = 96,   /**< Device can participate in cooperative kernels launched via ::huLaunchCooperativeKernelMultiDevice */
    HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK_OPTIN = 97, /**< Maximum optin shared memory per block */
    HU_DEVICE_ATTRIBUTE_CAN_FLUSH_REMOTE_WRITES = 98,           /**< Both the ::HU_STREAM_WAIT_VALUE_FLUSH flag and the ::HU_STREAM_MEM_OP_FLUSH_REMOTE_WRITES MemOp are supported on the device. See \ref HIP_MEMOP for additional details. */
    HU_DEVICE_ATTRIBUTE_HOST_REGISTER_SUPPORTED = 99,           /**< Device supports host memory registration via ::hipHostRegister. */
    HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES = 100, /**< Device accesses pageable memory via the host's page tables. */
    HU_DEVICE_ATTRIBUTE_DIRECT_MANAGED_MEM_ACCESS_FROM_HOST = 101, /**< The host can directly access managed memory on the device without migration. */
    HU_DEVICE_ATTRIBUTE_MAX
} HUdevice_attribute;

/**
 * Legacy device properties
 */
typedef struct HUdevprop_st {
    int maxThreadsPerBlock;     /**< Maximum number of threads per block */
    int maxThreadsDim[3];       /**< Maximum size of each dimension of a block */
    int maxGridSize[3];         /**< Maximum size of each dimension of a grid */
    int sharedMemPerBlock;      /**< Shared memory available per block in bytes */
    int totalConstantMemory;    /**< Constant memory available on device in bytes */
    int SIMDWidth;              /**< Warp size in threads */
    int memPitch;               /**< Maximum pitch in bytes allowed by memory copies */
    int regsPerBlock;           /**< 32-bit registers available per block */
    int clockRate;              /**< Clock frequency in kilohertz */
    int textureAlign;           /**< Alignment requirement for textures */
} HUdevprop;

/**
 * Pointer information
 */
typedef enum HUpointer_attribute_enum {
    HU_POINTER_ATTRIBUTE_CONTEXT = 1,        /**< The ::HUcontext on which a pointer was allocated or registered */
    HU_POINTER_ATTRIBUTE_MEMORY_TYPE = 2,    /**< The ::HUmemorytype describing the physical location of a pointer */
    HU_POINTER_ATTRIBUTE_DEVICE_POINTER = 3, /**< The address at which a pointer's memory may be accessed on the device */
    HU_POINTER_ATTRIBUTE_HOST_POINTER = 4,   /**< The address at which a pointer's memory may be accessed on the host */
    HU_POINTER_ATTRIBUTE_P2P_TOKENS = 5,     /**< A pair of tokens for use with the nv-p2p.h Linux kernel interface */
    HU_POINTER_ATTRIBUTE_SYNC_MEMOPS = 6,    /**< Synchronize every synchronous memory operation initiated on this region */
    HU_POINTER_ATTRIBUTE_BUFFER_ID = 7,      /**< A process-wide unique ID for an allocated memory region*/
    HU_POINTER_ATTRIBUTE_IS_MANAGED = 8,     /**< Indicates if the pointer points to managed memory */
    HU_POINTER_ATTRIBUTE_DEVICE_ORDINAL = 9  /**< A device ordinal of a device on which a pointer was allocated or registered */
} HUpointer_attribute;

/**
 * Function properties
 */
typedef enum HUfunction_attribute_enum {
    /**
     * The maximum number of threads per block, beyond which a launch of the
     * function would fail. This number depends on both the function and the
     * device on which the function is currently loaded.
     */
    HU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK = 0,

    /**
     * The size in bytes of statically-allocated shared memory required by
     * this function. This does not include dynamically-allocated shared
     * memory requested by the user at runtime.
     */
    HU_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES = 1,

    /**
     * The size in bytes of user-allocated constant memory required by this
     * function.
     */
    HU_FUNC_ATTRIBUTE_CONST_SIZE_BYTES = 2,

    /**
     * The size in bytes of local memory used by each thread of this function.
     */
    HU_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES = 3,

    /**
     * The number of registers used by each thread of this function.
     */
    HU_FUNC_ATTRIBUTE_NUM_REGS = 4,

    /**
     * The PTX virtual architecture version for which the function was
     * compiled. This value is the major PTX version * 10 + the minor PTX
     * version, so a PTX version 1.3 function would return the value 13.
     * Note that this may return the undefined value of 0 for hubins
     * compiled prior to HIP 3.0.
     */
    HU_FUNC_ATTRIBUTE_PTX_VERSION = 5,

    /**
     * The binary architecture version for which the function was compiled.
     * This value is the major binary version * 10 + the minor binary version,
     * so a binary version 1.3 function would return the value 13. Note that
     * this will return a value of 10 for legacy hubins that do not have a
     * properly-encoded binary architecture version.
     */
    HU_FUNC_ATTRIBUTE_BINARY_VERSION = 6,

    /**
     * The attribute to indicate whether the function has been compiled with 
     * user specified option "-Xptxas --dlcm=ca" set .
     */
    HU_FUNC_ATTRIBUTE_CACHE_MODE_CA = 7,

    /**
     * The maximum size in bytes of dynamically-allocated shared memory that can be used by
     * this function. If the user-specified dynamic shared memory size is larger than this
     * value, the launch will fail.
     * See ::huFuncSetAttribute
     */
    HU_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES = 8,

    /**
     * On devices where the L1 cache and shared memory use the same hardware resources, 
     * this sets the shared memory carveout preference, in percent of the total shared memory.
     * Refer to ::HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_MULTIPROCESSOR.
     * This is only a hint, and the driver can choose a different ratio if required to execute the function.
     * See ::huFuncSetAttribute
     */
    HU_FUNC_ATTRIBUTE_PREFERRED_SHARED_MEMORY_CARVEOUT = 9,

    HU_FUNC_ATTRIBUTE_MAX
} HUfunction_attribute;

/**
 * Function cache configurations
 */
typedef enum HUfunc_cache_enum {
    HU_FUNC_CACHE_PREFER_NONE    = 0x00, /**< no preference for shared memory or L1 (default) */
    HU_FUNC_CACHE_PREFER_SHARED  = 0x01, /**< prefer larger shared memory and smaller L1 cache */
    HU_FUNC_CACHE_PREFER_L1      = 0x02, /**< prefer larger L1 cache and smaller shared memory */
    HU_FUNC_CACHE_PREFER_EQUAL   = 0x03  /**< prefer equal sized L1 cache and shared memory */
} HUfunc_cache;

/**
 * Shared memory configurations
 */
typedef enum HUsharedconfig_enum {
    HU_SHARED_MEM_CONFIG_DEFAULT_BANK_SIZE    = 0x00, /**< set default shared memory bank size */
    HU_SHARED_MEM_CONFIG_FOUR_BYTE_BANK_SIZE  = 0x01, /**< set shared memory bank width to four bytes */
    HU_SHARED_MEM_CONFIG_EIGHT_BYTE_BANK_SIZE = 0x02  /**< set shared memory bank width to eight bytes */
} HUsharedconfig;

/**
 * Shared memory carveout configurations. These may be passed to ::huFuncSetAttribute
 */
typedef enum HUshared_carveout_enum {
    HU_SHAREDMEM_CARVEOUT_DEFAULT       = -1,  /**< No preference for shared memory or L1 (default) */
    HU_SHAREDMEM_CARVEOUT_MAX_SHARED    = 100, /**< Prefer maximum available shared memory, minimum L1 cache */
    HU_SHAREDMEM_CARVEOUT_MAX_L1        = 0    /**< Prefer maximum available L1 cache, minimum shared memory */
} HUshared_carveout;

/**
 * Memory types
 */
typedef enum HUmemorytype_enum {
    HU_MEMORYTYPE_HOST    = 0x01,    /**< Host memory */
    HU_MEMORYTYPE_DEVICE  = 0x02,    /**< Device memory */
    HU_MEMORYTYPE_ARRAY   = 0x03,    /**< Array memory */
    HU_MEMORYTYPE_UNIFIED = 0x04     /**< Unified device or host memory */
} HUmemorytype;

/**
 * Compute Modes
 */
typedef enum HUcomputemode_enum {
    HU_COMPUTEMODE_DEFAULT           = 0, /**< Default compute mode (Multiple contexts allowed per device) */
    HU_COMPUTEMODE_PROHIBITED        = 2, /**< Compute-prohibited mode (No contexts can be created on this device at this time) */
    HU_COMPUTEMODE_EXCLUSIVE_PROCESS = 3  /**< Compute-exclusive-process mode (Only one context used by a single process can be present on this device at a time) */
} HUcomputemode;

/**
 * Memory advise values
 */
typedef enum HUmem_advise_enum {
    HU_MEM_ADVISE_SET_READ_MOSTLY          = 1, /**< Data will mostly be read and only occassionally be written to */
    HU_MEM_ADVISE_UNSET_READ_MOSTLY        = 2, /**< Undo the effect of ::HU_MEM_ADVISE_SET_READ_MOSTLY */
    HU_MEM_ADVISE_SET_PREFERRED_LOCATION   = 3, /**< Set the preferred location for the data as the specified device */
    HU_MEM_ADVISE_UNSET_PREFERRED_LOCATION = 4, /**< Clear the preferred location for the data */
    HU_MEM_ADVISE_SET_ACCESSED_BY          = 5, /**< Data will be accessed by the specified device, so prevent page faults as much as possible */
    HU_MEM_ADVISE_UNSET_ACCESSED_BY        = 6  /**< Let the Unified Memory subsystem decide on the page faulting policy for the specified device */
} HUmem_advise;

typedef enum HUmem_range_attribute_enum {
    HU_MEM_RANGE_ATTRIBUTE_READ_MOSTLY            = 1, /**< Whether the range will mostly be read and only occassionally be written to */
    HU_MEM_RANGE_ATTRIBUTE_PREFERRED_LOCATION     = 2, /**< The preferred location of the range */
    HU_MEM_RANGE_ATTRIBUTE_ACCESSED_BY            = 3, /**< Memory range has ::HU_MEM_ADVISE_SET_ACCESSED_BY set for specified device */
    HU_MEM_RANGE_ATTRIBUTE_LAST_PREFETCH_LOCATION = 4  /**< The last location to which the range was prefetched */
} HUmem_range_attribute;

/**
 * Online compiler and linker options
 */
typedef enum HUjit_option_enum
{
    /**
     * Max number of registers that a thread may use.\n
     * Option type: unsigned int\n
     * Applies to: compiler only
     */
    HU_JIT_MAX_REGISTERS = 0,

    /**
     * IN: Specifies minimum number of threads per block to target compilation
     * for\n
     * OUT: Returns the number of threads the compiler actually targeted.
     * This restricts the resource utilization fo the compiler (e.g. max
     * registers) such that a block with the given number of threads should be
     * able to launch based on register limitations. Note, this option does not
     * currently take into account any other resource limitations, such as
     * shared memory utilization.\n
     * Cannot be combined with ::HU_JIT_TARGET.\n
     * Option type: unsigned int\n
     * Applies to: compiler only
     */
    HU_JIT_THREADS_PER_BLOCK,

    /**
     * Overwrites the option value with the total wall clock time, in
     * milliseconds, spent in the compiler and linker\n
     * Option type: float\n
     * Applies to: compiler and linker
     */
    HU_JIT_WALL_TIME,

    /**
     * Pointer to a buffer in which to print any log messages
     * that are informational in nature (the buffer size is specified via
     * option ::HU_JIT_INFO_LOG_BUFFER_SIZE_BYTES)\n
     * Option type: char *\n
     * Applies to: compiler and linker
     */
    HU_JIT_INFO_LOG_BUFFER,

    /**
     * IN: Log buffer size in bytes.  Log messages will be capped at this size
     * (including null terminator)\n
     * OUT: Amount of log buffer filled with messages\n
     * Option type: unsigned int\n
     * Applies to: compiler and linker
     */
    HU_JIT_INFO_LOG_BUFFER_SIZE_BYTES,

    /**
     * Pointer to a buffer in which to print any log messages that
     * reflect errors (the buffer size is specified via option
     * ::HU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES)\n
     * Option type: char *\n
     * Applies to: compiler and linker
     */
    HU_JIT_ERROR_LOG_BUFFER,

    /**
     * IN: Log buffer size in bytes.  Log messages will be capped at this size
     * (including null terminator)\n
     * OUT: Amount of log buffer filled with messages\n
     * Option type: unsigned int\n
     * Applies to: compiler and linker
     */
    HU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES,

    /**
     * Level of optimizations to apply to generated code (0 - 4), with 4
     * being the default and highest level of optimizations.\n
     * Option type: unsigned int\n
     * Applies to: compiler only
     */
    HU_JIT_OPTIMIZATION_LEVEL,

    /**
     * No option value required. Determines the target based on the current
     * attached context (default)\n
     * Option type: No option value needed\n
     * Applies to: compiler and linker
     */
    HU_JIT_TARGET_FROM_HUCONTEXT,

    /**
     * Target is chosen based on supplied ::HUjit_target.  Cannot be
     * combined with ::HU_JIT_THREADS_PER_BLOCK.\n
     * Option type: unsigned int for enumerated type ::HUjit_target\n
     * Applies to: compiler and linker
     */
    HU_JIT_TARGET,

    /**
     * Specifies choice of fallback strategy if matching hubin is not found.
     * Choice is based on supplied ::HUjit_fallback.  This option cannot be
     * used with huLink* APIs as the linker requires exact matches.\n
     * Option type: unsigned int for enumerated type ::HUjit_fallback\n
     * Applies to: compiler only
     */
    HU_JIT_FALLBACK_STRATEGY,

    /**
     * Specifies whether to create debug information in output (-g)
     * (0: false, default)\n
     * Option type: int\n
     * Applies to: compiler and linker
     */
    HU_JIT_GENERATE_DEBUG_INFO,

    /**
     * Generate verbose log messages (0: false, default)\n
     * Option type: int\n
     * Applies to: compiler and linker
     */
    HU_JIT_LOG_VERBOSE,

    /**
     * Generate line number information (-lineinfo) (0: false, default)\n
     * Option type: int\n
     * Applies to: compiler only
     */
    HU_JIT_GENERATE_LINE_INFO,

    /**
     * Specifies whether to enable caching explicitly (-dlcm) \n
     * Choice is based on supplied ::HUjit_cacheMode_enum.\n
     * Option type: unsigned int for enumerated type ::HUjit_cacheMode_enum\n
     * Applies to: compiler only
     */
    HU_JIT_CACHE_MODE,

    /**
     * The below jit options are used for internal purposes only, in this version of HIP
     */
    HU_JIT_NEW_SM3X_OPT,
    HU_JIT_FAST_COMPILE,

    HU_JIT_NUM_OPTIONS

} HUjit_option;

/**
 * Online compilation targets
 */
typedef enum HUjit_target_enum
{
    HU_TARGET_COMPUTE_20 = 20,       /**< Compute device class 2.0 */
    HU_TARGET_COMPUTE_21 = 21,       /**< Compute device class 2.1 */
    HU_TARGET_COMPUTE_30 = 30,       /**< Compute device class 3.0 */
    HU_TARGET_COMPUTE_32 = 32,       /**< Compute device class 3.2 */
    HU_TARGET_COMPUTE_35 = 35,       /**< Compute device class 3.5 */
    HU_TARGET_COMPUTE_37 = 37,       /**< Compute device class 3.7 */
    HU_TARGET_COMPUTE_50 = 50,       /**< Compute device class 5.0 */
    HU_TARGET_COMPUTE_52 = 52,       /**< Compute device class 5.2 */
    HU_TARGET_COMPUTE_53 = 53,       /**< Compute device class 5.3 */
    HU_TARGET_COMPUTE_60 = 60,       /**< Compute device class 6.0.*/
    HU_TARGET_COMPUTE_61 = 61,       /**< Compute device class 6.1.*/
    HU_TARGET_COMPUTE_62 = 62,       /**< Compute device class 6.2.*/
    HU_TARGET_COMPUTE_70 = 70,       /**< Compute device class 7.0.*/
    HU_TARGET_COMPUTE_73 = 73,       /**< Compute device class 7.3.*/
    HU_TARGET_COMPUTE_75 = 75        /**< Compute device class 7.5.*/
} HUjit_target;

/**
 * Cubin matching fallback strategies
 */
typedef enum HUjit_fallback_enum
{
    HU_PREFER_PTX = 0,  /**< Prefer to compile ptx if exact binary match not found */

    HU_PREFER_BINARY    /**< Prefer to fall back to compatible binary code if exact match not found */

} HUjit_fallback;

/**
 * Caching modes for dlcm 
 */
typedef enum HUjit_cacheMode_enum
{
    HU_JIT_CACHE_OPTION_NONE = 0, /**< Compile with no -dlcm flag specified */
    HU_JIT_CACHE_OPTION_CG,       /**< Compile with L1 cache disabled */
    HU_JIT_CACHE_OPTION_CA        /**< Compile with L1 cache enabled */
} HUjit_cacheMode;

/**
 * Device code formats
 */
typedef enum HUjitInputType_enum
{
    /**
     * Compiled device-class-specific device code\n
     * Applicable options: none
     */
    HU_JIT_INPUT_HUBIN = 0,

    /**
     * PTX source code\n
     * Applicable options: PTX compiler options
     */
    HU_JIT_INPUT_PTX,

    /**
     * Bundle of multiple hubins and/or PTX of some device code\n
     * Applicable options: PTX compiler options, ::HU_JIT_FALLBACK_STRATEGY
     */
    HU_JIT_INPUT_FATBINARY,

    /**
     * Host object with embedded device code\n
     * Applicable options: PTX compiler options, ::HU_JIT_FALLBACK_STRATEGY
     */
    HU_JIT_INPUT_OBJECT,

    /**
     * Archive of host objects with embedded device code\n
     * Applicable options: PTX compiler options, ::HU_JIT_FALLBACK_STRATEGY
     */
    HU_JIT_INPUT_LIBRARY,

    HU_JIT_NUM_INPUT_TYPES
} HUjitInputType;

typedef struct HUlinkState_st *HUlinkState;

/**
 * Flags to register a graphics resource
 */
typedef enum HUgraphicsRegisterFlags_enum {
    HU_GRAPHICS_REGISTER_FLAGS_NONE           = 0x00,
    HU_GRAPHICS_REGISTER_FLAGS_READ_ONLY      = 0x01,
    HU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD  = 0x02,
    HU_GRAPHICS_REGISTER_FLAGS_SURFACE_LDST   = 0x04,
    HU_GRAPHICS_REGISTER_FLAGS_TEXTURE_GATHER = 0x08
} HUgraphicsRegisterFlags;

/**
 * Flags for mapping and unmapping interop resources
 */
typedef enum HUgraphicsMapResourceFlags_enum {
    HU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE          = 0x00,
    HU_GRAPHICS_MAP_RESOURCE_FLAGS_READ_ONLY     = 0x01,
    HU_GRAPHICS_MAP_RESOURCE_FLAGS_WRITE_DISCARD = 0x02
} HUgraphicsMapResourceFlags;

/**
 * Array indices for hube faces
 */
typedef enum HUarray_cubemap_face_enum {
    HU_CUBEMAP_FACE_POSITIVE_X  = 0x00, /**< Positive X face of hubemap */
    HU_CUBEMAP_FACE_NEGATIVE_X  = 0x01, /**< Negative X face of hubemap */
    HU_CUBEMAP_FACE_POSITIVE_Y  = 0x02, /**< Positive Y face of hubemap */
    HU_CUBEMAP_FACE_NEGATIVE_Y  = 0x03, /**< Negative Y face of hubemap */
    HU_CUBEMAP_FACE_POSITIVE_Z  = 0x04, /**< Positive Z face of hubemap */
    HU_CUBEMAP_FACE_NEGATIVE_Z  = 0x05  /**< Negative Z face of hubemap */
} HUarray_cubemap_face;

/**
 * Limits
 */
typedef enum HUlimit_enum {
    HU_LIMIT_STACK_SIZE                       = 0x00, /**< GPU thread stack size */
    HU_LIMIT_PRINTF_FIFO_SIZE                 = 0x01, /**< GPU printf FIFO size */
    HU_LIMIT_MALLOC_HEAP_SIZE                 = 0x02, /**< GPU malloc heap size */
    HU_LIMIT_DEV_RUNTIME_SYNC_DEPTH           = 0x03, /**< GPU device runtime launch synchronize depth */
    HU_LIMIT_DEV_RUNTIME_PENDING_LAUNCH_COUNT = 0x04, /**< GPU device runtime pending launch count */
    HU_LIMIT_MAX
} HUlimit;

/**
 * Resource types
 */
typedef enum HUresourcetype_enum {
    HU_RESOURCE_TYPE_ARRAY           = 0x00, /**< Array resoure */
    HU_RESOURCE_TYPE_MIPMAPPED_ARRAY = 0x01, /**< Mipmapped array resource */
    HU_RESOURCE_TYPE_LINEAR          = 0x02, /**< Linear resource */
    HU_RESOURCE_TYPE_PITCH2D         = 0x03  /**< Pitch 2D resource */
} HUresourcetype;

/**
 * Error codes
 */
typedef enum hipError_enum {
    /**
     * The API call returned with no errors. In the case of query calls, this
     * can also mean that the operation being queried is complete (see
     * ::huEventQuery() and ::huStreamQuery()).
     */
    HIP_SUCCESS                              = 0,

    /**
     * This indicates that one or more of the parameters passed to the API call
     * is not within an acceptable range of values.
     */
    HIP_ERROR_INVALID_VALUE                  = 1,

    /**
     * The API call failed because it was unable to allocate enough memory to
     * perform the requested operation.
     */
    HIP_ERROR_OUT_OF_MEMORY                  = 2,

    /**
     * This indicates that the HIP driver has not been initialized with
     * ::huInit() or that initialization has failed.
     */
    HIP_ERROR_NOT_INITIALIZED                = 3,

    /**
     * This indicates that the HIP driver is in the process of shutting down.
     */
    HIP_ERROR_DEINITIALIZED                  = 4,

    /**
     * This indicates profiler is not initialized for this run. This can
     * happen when the application is running with external profiling tools
     * like visual profiler.
     */
    HIP_ERROR_PROFILER_DISABLED              = 5,

    /**
     * \deprecated
     * This error return is deprecated as of HIP 5.0. It is no longer an error
     * to attempt to enable/disable the profiling via ::huProfilerStart or
     * ::huProfilerStop without initialization.
     */
    HIP_ERROR_PROFILER_NOT_INITIALIZED       = 6,

    /**
     * \deprecated
     * This error return is deprecated as of HIP 5.0. It is no longer an error
     * to call huProfilerStart() when profiling is already enabled.
     */
    HIP_ERROR_PROFILER_ALREADY_STARTED       = 7,

    /**
     * \deprecated
     * This error return is deprecated as of HIP 5.0. It is no longer an error
     * to call huProfilerStop() when profiling is already disabled.
     */
    HIP_ERROR_PROFILER_ALREADY_STOPPED       = 8,

    /**
     * This indicates that no HIP-capable devices were detected by the installed
     * HIP driver.
     */
    HIP_ERROR_NO_DEVICE                      = 100,

    /**
     * This indicates that the device ordinal supplied by the user does not
     * correspond to a valid HIP device.
     */
    HIP_ERROR_INVALID_DEVICE                 = 101,


    /**
     * This indicates that the device kernel image is invalid. This can also
     * indicate an invalid HIP module.
     */
    HIP_ERROR_INVALID_IMAGE                  = 200,

    /**
     * This most frequently indicates that there is no context bound to the
     * current thread. This can also be returned if the context passed to an
     * API call is not a valid handle (such as a context that has had
     * ::huCtxDestroy() invoked on it). This can also be returned if a user
     * mixes different API versions (i.e. 3010 context with 3020 API calls).
     * See ::huCtxGetApiVersion() for more details.
     */
    HIP_ERROR_INVALID_CONTEXT                = 201,

    /**
     * This indicated that the context being supplied as a parameter to the
     * API call was already the active context.
     * \deprecated
     * This error return is deprecated as of HIP 3.2. It is no longer an
     * error to attempt to push the active context via ::huCtxPushCurrent().
     */
    HIP_ERROR_CONTEXT_ALREADY_CURRENT        = 202,

    /**
     * This indicates that a map or register operation has failed.
     */
    HIP_ERROR_MAP_FAILED                     = 205,

    /**
     * This indicates that an unmap or unregister operation has failed.
     */
    HIP_ERROR_UNMAP_FAILED                   = 206,

    /**
     * This indicates that the specified array is currently mapped and thus
     * cannot be destroyed.
     */
    HIP_ERROR_ARRAY_IS_MAPPED                = 207,

    /**
     * This indicates that the resource is already mapped.
     */
    HIP_ERROR_ALREADY_MAPPED                 = 208,

    /**
     * This indicates that there is no kernel image available that is suitable
     * for the device. This can occur when a user specifies code generation
     * options for a particular HIP source file that do not include the
     * corresponding device configuration.
     */
    HIP_ERROR_NO_BINARY_FOR_GPU              = 209,

    /**
     * This indicates that a resource has already been acquired.
     */
    HIP_ERROR_ALREADY_ACQUIRED               = 210,

    /**
     * This indicates that a resource is not mapped.
     */
    HIP_ERROR_NOT_MAPPED                     = 211,

    /**
     * This indicates that a mapped resource is not available for access as an
     * array.
     */
    HIP_ERROR_NOT_MAPPED_AS_ARRAY            = 212,

    /**
     * This indicates that a mapped resource is not available for access as a
     * pointer.
     */
    HIP_ERROR_NOT_MAPPED_AS_POINTER          = 213,

    /**
     * This indicates that an uncorrectable ECC error was detected during
     * execution.
     */
    HIP_ERROR_ECC_UNCORRECTABLE              = 214,

    /**
     * This indicates that the ::HUlimit passed to the API call is not
     * supported by the active device.
     */
    HIP_ERROR_UNSUPPORTED_LIMIT              = 215,

    /**
     * This indicates that the ::HUcontext passed to the API call can
     * only be bound to a single CPU thread at a time but is already 
     * bound to a CPU thread.
     */
    HIP_ERROR_CONTEXT_ALREADY_IN_USE         = 216,

    /**
     * This indicates that peer access is not supported across the given
     * devices.
     */
    HIP_ERROR_PEER_ACCESS_UNSUPPORTED        = 217,

    /**
     * This indicates that a PTX JIT compilation failed.
     */
    HIP_ERROR_INVALID_PTX                    = 218,

    /**
     * This indicates an error with OpenGL or DirectX context.
     */
    HIP_ERROR_INVALID_GRAPHICS_CONTEXT       = 219,

    /**
    * This indicates that an uncorrectable NVLink error was detected during the
    * execution.
    */
    HIP_ERROR_NVLINK_UNCORRECTABLE           = 220,

    /**
    * This indicates that the PTX JIT compiler library was not found.
    */
    HIP_ERROR_JIT_COMPILER_NOT_FOUND         = 221,

    /**
     * This indicates that the device kernel source is invalid.
     */
    HIP_ERROR_INVALID_SOURCE                 = 300,

    /**
     * This indicates that the file specified was not found.
     */
    HIP_ERROR_FILE_NOT_FOUND                 = 301,

    /**
     * This indicates that a link to a shared object failed to resolve.
     */
    HIP_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND = 302,

    /**
     * This indicates that initialization of a shared object failed.
     */
    HIP_ERROR_SHARED_OBJECT_INIT_FAILED      = 303,

    /**
     * This indicates that an OS call failed.
     */
    HIP_ERROR_OPERATING_SYSTEM               = 304,

    /**
     * This indicates that a resource handle passed to the API call was not
     * valid. Resource handles are opaque types like ::HUstream and ::HUevent.
     */
    HIP_ERROR_INVALID_HANDLE                 = 400,

    /**
     * This indicates that a named symbol was not found. Examples of symbols
     * are global/constant variable names, texture names, and surface names.
     */
    HIP_ERROR_NOT_FOUND                      = 500,

    /**
     * This indicates that asynchronous operations issued previously have not
     * completed yet. This result is not actually an error, but must be indicated
     * differently than ::HIP_SUCCESS (which indicates completion). Calls that
     * may return this value include ::huEventQuery() and ::huStreamQuery().
     */
    HIP_ERROR_NOT_READY                      = 600,

    /**
     * While executing a kernel, the device encountered a
     * load or store instruction on an invalid memory address.
     * This leaves the process in an inconsistent state and any further HIP work
     * will return the same error. To continue using HIP, the process must be terminated
     * and relaunched.
     */
    HIP_ERROR_ILLEGAL_ADDRESS                = 700,

    /**
     * This indicates that a launch did not occur because it did not have
     * appropriate resources. This error usually indicates that the user has
     * attempted to pass too many arguments to the device kernel, or the
     * kernel launch specifies too many threads for the kernel's register
     * count. Passing arguments of the wrong size (i.e. a 64-bit pointer
     * when a 32-bit int is expected) is equivalent to passing too many
     * arguments and can also result in this error.
     */
    HIP_ERROR_LAUNCH_OUT_OF_RESOURCES        = 701,

    /**
     * This indicates that the device kernel took too long to execute. This can
     * only occur if timeouts are enabled - see the device attribute
     * ::HU_DEVICE_ATTRIBUTE_KERNEL_EXEC_TIMEOUT for more information.
     * This leaves the process in an inconsistent state and any further HIP work
     * will return the same error. To continue using HIP, the process must be terminated
     * and relaunched.
     */
    HIP_ERROR_LAUNCH_TIMEOUT                 = 702,

    /**
     * This error indicates a kernel launch that uses an incompatible texturing
     * mode.
     */
    HIP_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING  = 703,
    
    /**
     * This error indicates that a call to ::huCtxEnablePeerAccess() is
     * trying to re-enable peer access to a context which has already
     * had peer access to it enabled.
     */
    HIP_ERROR_PEER_ACCESS_ALREADY_ENABLED    = 704,

    /**
     * This error indicates that ::huCtxDisablePeerAccess() is 
     * trying to disable peer access which has not been enabled yet 
     * via ::huCtxEnablePeerAccess(). 
     */
    HIP_ERROR_PEER_ACCESS_NOT_ENABLED        = 705,

    /**
     * This error indicates that the primary context for the specified device
     * has already been initialized.
     */
    HIP_ERROR_PRIMARY_CONTEXT_ACTIVE         = 708,

    /**
     * This error indicates that the context current to the calling thread
     * has been destroyed using ::huCtxDestroy, or is a primary context which
     * has not yet been initialized.
     */
    HIP_ERROR_CONTEXT_IS_DESTROYED           = 709,

    /**
     * A device-side assert triggered during kernel execution. The context
     * cannot be used anymore, and must be destroyed. All existing device 
     * memory allocations from this context are invalid and must be 
     * reconstructed if the program is to continue using HIP.
     */
    HIP_ERROR_ASSERT                         = 710,

    /**
     * This error indicates that the hardware resources required to enable
     * peer access have been exhausted for one or more of the devices 
     * passed to ::huCtxEnablePeerAccess().
     */
    HIP_ERROR_TOO_MANY_PEERS                 = 711,

    /**
     * This error indicates that the memory range passed to ::huMemHostRegister()
     * has already been registered.
     */
    HIP_ERROR_HOST_MEMORY_ALREADY_REGISTERED = 712,

    /**
     * This error indicates that the pointer passed to ::huMemHostUnregister()
     * does not correspond to any currently registered memory region.
     */
    HIP_ERROR_HOST_MEMORY_NOT_REGISTERED     = 713,

    /**
     * While executing a kernel, the device encountered a stack error.
     * This can be due to stack corruption or exceeding the stack size limit.
     * This leaves the process in an inconsistent state and any further HIP work
     * will return the same error. To continue using HIP, the process must be terminated
     * and relaunched.
     */
    HIP_ERROR_HARDWARE_STACK_ERROR           = 714,

    /**
     * While executing a kernel, the device encountered an illegal instruction.
     * This leaves the process in an inconsistent state and any further HIP work
     * will return the same error. To continue using HIP, the process must be terminated
     * and relaunched.
     */
    HIP_ERROR_ILLEGAL_INSTRUCTION            = 715,

    /**
     * While executing a kernel, the device encountered a load or store instruction
     * on a memory address which is not aligned.
     * This leaves the process in an inconsistent state and any further HIP work
     * will return the same error. To continue using HIP, the process must be terminated
     * and relaunched.
     */
    HIP_ERROR_MISALIGNED_ADDRESS             = 716,

    /**
     * While executing a kernel, the device encountered an instruction
     * which can only operate on memory locations in certain address spaces
     * (global, shared, or local), but was supplied a memory address not
     * belonging to an allowed address space.
     * This leaves the process in an inconsistent state and any further HIP work
     * will return the same error. To continue using HIP, the process must be terminated
     * and relaunched.
     */
    HIP_ERROR_INVALID_ADDRESS_SPACE          = 717,

    /**
     * While executing a kernel, the device program counter wrapped its address space.
     * This leaves the process in an inconsistent state and any further HIP work
     * will return the same error. To continue using HIP, the process must be terminated
     * and relaunched.
     */
    HIP_ERROR_INVALID_PC                     = 718,

    /**
     * An exception occurred on the device while executing a kernel. Common
     * causes include dereferencing an invalid device pointer and accessing
     * out of bounds shared memory.
     * This leaves the process in an inconsistent state and any further HIP work
     * will return the same error. To continue using HIP, the process must be terminated
     * and relaunched.
     */
    HIP_ERROR_LAUNCH_FAILED                  = 719,

    /**
     * This error indicates that the number of blocks launched per grid for a kernel that was
     * launched via either ::huLaunchCooperativeKernel or ::huLaunchCooperativeKernelMultiDevice
     * exceeds the maximum number of blocks as allowed by ::huOccupancyMaxActiveBlocksPerMultiprocessor
     * or ::huOccupancyMaxActiveBlocksPerMultiprocessorWithFlags times the number of multiprocessors
     * as specified by the device attribute ::HU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT.
     */
    HIP_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE   = 720,

    /**
     * This error indicates that the attempted operation is not permitted.
     */
    HIP_ERROR_NOT_PERMITTED                  = 800,

    /**
     * This error indicates that the attempted operation is not supported
     * on the current system or device.
     */
    HIP_ERROR_NOT_SUPPORTED                  = 801,

    /**
     * This indicates that an unknown internal error has occurred.
     */
    HIP_ERROR_UNKNOWN                        = 999
} HUresult;

/**
 * P2P Attributes
 */
typedef enum HUdevice_P2PAttribute_enum {
    HU_DEVICE_P2P_ATTRIBUTE_PERFORMANCE_RANK              = 0x01, /**< A relative value indicating the performance of the link between two devices */
    HU_DEVICE_P2P_ATTRIBUTE_ACCESS_SUPPORTED              = 0x02, /**< P2P Access is enable */
    HU_DEVICE_P2P_ATTRIBUTE_NATIVE_ATOMIC_SUPPORTED       = 0x03,  /**< Atomic operation over the link supported */
    HU_DEVICE_P2P_ATTRIBUTE_ARRAY_ACCESS_ACCESS_SUPPORTED = 0x04   /**< Accessing HIP arrays over the link supported */
} HUdevice_P2PAttribute;

#ifdef _WIN32
#define HIP_CB __stdcall
#else
#define HIP_CB
#endif

/**
 * HIP stream callback
 * \param hStream The stream the callback was added to, as passed to ::huStreamAddCallback.  May be NULL.
 * \param status ::HIP_SUCCESS or any persistent error on the stream.
 * \param userData User parameter provided at registration.
 */
typedef void (HIP_CB *HUstreamCallback)(HUstream hStream, HUresult status, void *userData);

/**
 * Block size to per-block dynamic shared memory mapping for a certain
 * kernel \param blockSize Block size of the kernel.
 *
 * \return The dynamic shared memory needed by a block.
 */
typedef size_t (HIP_CB *HUoccupancyB2DSize)(int blockSize);

/**
 * If set, host memory is portable between HIP contexts.
 * Flag for ::huMemHostAlloc()
 */
#define HU_MEMHOSTALLOC_PORTABLE        0x01

/**
 * If set, host memory is mapped into HIP address space and
 * ::huMemHostGetDevicePointer() may be called on the host pointer.
 * Flag for ::huMemHostAlloc()
 */
#define HU_MEMHOSTALLOC_DEVICEMAP       0x02

/**
 * If set, host memory is allocated as write-combined - fast to write,
 * faster to DMA, slow to read except via SSE4 streaming load instruction
 * (MOVNTDQA).
 * Flag for ::huMemHostAlloc()
 */
#define HU_MEMHOSTALLOC_WRITECOMBINED   0x04

/**
 * If set, host memory is portable between HIP contexts.
 * Flag for ::huMemHostRegister()
 */
#define HU_MEMHOSTREGISTER_PORTABLE     0x01

/**
 * If set, host memory is mapped into HIP address space and
 * ::huMemHostGetDevicePointer() may be called on the host pointer.
 * Flag for ::huMemHostRegister()
 */
#define HU_MEMHOSTREGISTER_DEVICEMAP    0x02

/**
 * If set, the passed memory pointer is treated as pointing to some
 * memory-mapped I/O space, e.g. belonging to a third-party PCIe device.
 * On Windows the flag is a no-op.
 * On Linux that memory is marked as non cache-coherent for the GPU and
 * is expected to be physically contiguous. It may return
 * HIP_ERROR_NOT_PERMITTED if run as an unprivileged user,
 * HIP_ERROR_NOT_SUPPORTED on older Linux kernel versions.
 * On all other platforms, it is not supported and HIP_ERROR_NOT_SUPPORTED
 * is returned.
 * Flag for ::huMemHostRegister()
 */
#define HU_MEMHOSTREGISTER_IOMEMORY     0x04

/**
 * 2D memory copy parameters
 */
typedef struct HIP_MEMCPY2D_st {
    size_t srcXInBytes;         /**< Source X in bytes */
    size_t srcY;                /**< Source Y */

    HUmemorytype srcMemoryType; /**< Source memory type (host, device, array) */
    const void *srcHost;        /**< Source host pointer */
    HUdeviceptr srcDevice;      /**< Source device pointer */
    HUarray srcArray;           /**< Source array reference */
    size_t srcPitch;            /**< Source pitch (ignored when src is array) */

    size_t dstXInBytes;         /**< Destination X in bytes */
    size_t dstY;                /**< Destination Y */

    HUmemorytype dstMemoryType; /**< Destination memory type (host, device, array) */
    void *dstHost;              /**< Destination host pointer */
    HUdeviceptr dstDevice;      /**< Destination device pointer */
    HUarray dstArray;           /**< Destination array reference */
    size_t dstPitch;            /**< Destination pitch (ignored when dst is array) */

    size_t WidthInBytes;        /**< Width of 2D memory copy in bytes */
    size_t Height;              /**< Height of 2D memory copy */
} HIP_MEMCPY2D;

/**
 * 3D memory copy parameters
 */
typedef struct HIP_MEMCPY3D_st {
    size_t srcXInBytes;         /**< Source X in bytes */
    size_t srcY;                /**< Source Y */
    size_t srcZ;                /**< Source Z */
    size_t srcLOD;              /**< Source LOD */
    HUmemorytype srcMemoryType; /**< Source memory type (host, device, array) */
    const void *srcHost;        /**< Source host pointer */
    HUdeviceptr srcDevice;      /**< Source device pointer */
    HUarray srcArray;           /**< Source array reference */
    void *reserved0;            /**< Must be NULL */
    size_t srcPitch;            /**< Source pitch (ignored when src is array) */
    size_t srcHeight;           /**< Source height (ignored when src is array; may be 0 if Depth==1) */

    size_t dstXInBytes;         /**< Destination X in bytes */
    size_t dstY;                /**< Destination Y */
    size_t dstZ;                /**< Destination Z */
    size_t dstLOD;              /**< Destination LOD */
    HUmemorytype dstMemoryType; /**< Destination memory type (host, device, array) */
    void *dstHost;              /**< Destination host pointer */
    HUdeviceptr dstDevice;      /**< Destination device pointer */
    HUarray dstArray;           /**< Destination array reference */
    void *reserved1;            /**< Must be NULL */
    size_t dstPitch;            /**< Destination pitch (ignored when dst is array) */
    size_t dstHeight;           /**< Destination height (ignored when dst is array; may be 0 if Depth==1) */

    size_t WidthInBytes;        /**< Width of 3D memory copy in bytes */
    size_t Height;              /**< Height of 3D memory copy */
    size_t Depth;               /**< Depth of 3D memory copy */
} HIP_MEMCPY3D;

/**
 * 3D memory cross-context copy parameters
 */
typedef struct HIP_MEMCPY3D_PEER_st {
    size_t srcXInBytes;         /**< Source X in bytes */
    size_t srcY;                /**< Source Y */
    size_t srcZ;                /**< Source Z */
    size_t srcLOD;              /**< Source LOD */
    HUmemorytype srcMemoryType; /**< Source memory type (host, device, array) */
    const void *srcHost;        /**< Source host pointer */
    HUdeviceptr srcDevice;      /**< Source device pointer */
    HUarray srcArray;           /**< Source array reference */
    HUcontext srcContext;       /**< Source context (ignored with srcMemoryType is ::HU_MEMORYTYPE_ARRAY) */
    size_t srcPitch;            /**< Source pitch (ignored when src is array) */
    size_t srcHeight;           /**< Source height (ignored when src is array; may be 0 if Depth==1) */

    size_t dstXInBytes;         /**< Destination X in bytes */
    size_t dstY;                /**< Destination Y */
    size_t dstZ;                /**< Destination Z */
    size_t dstLOD;              /**< Destination LOD */
    HUmemorytype dstMemoryType; /**< Destination memory type (host, device, array) */
    void *dstHost;              /**< Destination host pointer */
    HUdeviceptr dstDevice;      /**< Destination device pointer */
    HUarray dstArray;           /**< Destination array reference */
    HUcontext dstContext;       /**< Destination context (ignored with dstMemoryType is ::HU_MEMORYTYPE_ARRAY) */
    size_t dstPitch;            /**< Destination pitch (ignored when dst is array) */
    size_t dstHeight;           /**< Destination height (ignored when dst is array; may be 0 if Depth==1) */

    size_t WidthInBytes;        /**< Width of 3D memory copy in bytes */
    size_t Height;              /**< Height of 3D memory copy */
    size_t Depth;               /**< Depth of 3D memory copy */
} HIP_MEMCPY3D_PEER;

/**
 * Array descriptor
 */
typedef struct HIP_ARRAY_DESCRIPTOR_st
{
    size_t Width;             /**< Width of array */
    size_t Height;            /**< Height of array */

    HUarray_format Format;    /**< Array format */
    unsigned int NumChannels; /**< Channels per array element */
} HIP_ARRAY_DESCRIPTOR;

/**
 * 3D array descriptor
 */
typedef struct HIP_ARRAY3D_DESCRIPTOR_st
{
    size_t Width;             /**< Width of 3D array */
    size_t Height;            /**< Height of 3D array */
    size_t Depth;             /**< Depth of 3D array */

    HUarray_format Format;    /**< Array format */
    unsigned int NumChannels; /**< Channels per array element */
    unsigned int Flags;       /**< Flags */
} HIP_ARRAY3D_DESCRIPTOR;

/**
 * HIP Resource descriptor
 */
typedef struct HIP_RESOURCE_DESC_st
{
    HUresourcetype resType;                   /**< Resource type */

    union {
        struct {
            HUarray hArray;                   /**< HIP array */
        } array;
        struct {
            HUmipmappedArray hMipmappedArray; /**< HIP mipmapped array */
        } mipmap;
        struct {
            HUdeviceptr devPtr;               /**< Device pointer */
            HUarray_format format;            /**< Array format */
            unsigned int numChannels;         /**< Channels per array element */
            size_t sizeInBytes;               /**< Size in bytes */
        } linear;
        struct {
            HUdeviceptr devPtr;               /**< Device pointer */
            HUarray_format format;            /**< Array format */
            unsigned int numChannels;         /**< Channels per array element */
            size_t width;                     /**< Width of the array in elements */
            size_t height;                    /**< Height of the array in elements */
            size_t pitchInBytes;              /**< Pitch between two rows in bytes */
        } pitch2D;
        struct {
            int reserved[32];
        } reserved;
    } res;

    unsigned int flags;                       /**< Flags (must be zero) */
} HIP_RESOURCE_DESC;

/**
 * Texture descriptor
 */
typedef struct HIP_TEXTURE_DESC_st {
    HUaddress_mode addressMode[3];  /**< Address modes */
    HUfilter_mode filterMode;       /**< Filter mode */
    unsigned int flags;             /**< Flags */
    unsigned int maxAnisotropy;     /**< Maximum anisotropy ratio */
    HUfilter_mode mipmapFilterMode; /**< Mipmap filter mode */
    float mipmapLevelBias;          /**< Mipmap level bias */
    float minMipmapLevelClamp;      /**< Mipmap minimum level clamp */
    float maxMipmapLevelClamp;      /**< Mipmap maximum level clamp */ 
    float borderColor[4];           /**< Border Color */
    int reserved[12];
} HIP_TEXTURE_DESC;

/**
 * Resource view format
 */
typedef enum HUresourceViewFormat_enum
{
    HU_RES_VIEW_FORMAT_NONE          = 0x00, /**< No resource view format (use underlying resource format) */
    HU_RES_VIEW_FORMAT_UINT_1X8      = 0x01, /**< 1 channel unsigned 8-bit integers */
    HU_RES_VIEW_FORMAT_UINT_2X8      = 0x02, /**< 2 channel unsigned 8-bit integers */
    HU_RES_VIEW_FORMAT_UINT_4X8      = 0x03, /**< 4 channel unsigned 8-bit integers */
    HU_RES_VIEW_FORMAT_SINT_1X8      = 0x04, /**< 1 channel signed 8-bit integers */
    HU_RES_VIEW_FORMAT_SINT_2X8      = 0x05, /**< 2 channel signed 8-bit integers */
    HU_RES_VIEW_FORMAT_SINT_4X8      = 0x06, /**< 4 channel signed 8-bit integers */
    HU_RES_VIEW_FORMAT_UINT_1X16     = 0x07, /**< 1 channel unsigned 16-bit integers */
    HU_RES_VIEW_FORMAT_UINT_2X16     = 0x08, /**< 2 channel unsigned 16-bit integers */
    HU_RES_VIEW_FORMAT_UINT_4X16     = 0x09, /**< 4 channel unsigned 16-bit integers */
    HU_RES_VIEW_FORMAT_SINT_1X16     = 0x0a, /**< 1 channel signed 16-bit integers */
    HU_RES_VIEW_FORMAT_SINT_2X16     = 0x0b, /**< 2 channel signed 16-bit integers */
    HU_RES_VIEW_FORMAT_SINT_4X16     = 0x0c, /**< 4 channel signed 16-bit integers */
    HU_RES_VIEW_FORMAT_UINT_1X32     = 0x0d, /**< 1 channel unsigned 32-bit integers */
    HU_RES_VIEW_FORMAT_UINT_2X32     = 0x0e, /**< 2 channel unsigned 32-bit integers */
    HU_RES_VIEW_FORMAT_UINT_4X32     = 0x0f, /**< 4 channel unsigned 32-bit integers */
    HU_RES_VIEW_FORMAT_SINT_1X32     = 0x10, /**< 1 channel signed 32-bit integers */
    HU_RES_VIEW_FORMAT_SINT_2X32     = 0x11, /**< 2 channel signed 32-bit integers */
    HU_RES_VIEW_FORMAT_SINT_4X32     = 0x12, /**< 4 channel signed 32-bit integers */
    HU_RES_VIEW_FORMAT_FLOAT_1X16    = 0x13, /**< 1 channel 16-bit floating point */
    HU_RES_VIEW_FORMAT_FLOAT_2X16    = 0x14, /**< 2 channel 16-bit floating point */
    HU_RES_VIEW_FORMAT_FLOAT_4X16    = 0x15, /**< 4 channel 16-bit floating point */
    HU_RES_VIEW_FORMAT_FLOAT_1X32    = 0x16, /**< 1 channel 32-bit floating point */
    HU_RES_VIEW_FORMAT_FLOAT_2X32    = 0x17, /**< 2 channel 32-bit floating point */
    HU_RES_VIEW_FORMAT_FLOAT_4X32    = 0x18, /**< 4 channel 32-bit floating point */
    HU_RES_VIEW_FORMAT_UNSIGNED_BC1  = 0x19, /**< Block compressed 1 */
    HU_RES_VIEW_FORMAT_UNSIGNED_BC2  = 0x1a, /**< Block compressed 2 */
    HU_RES_VIEW_FORMAT_UNSIGNED_BC3  = 0x1b, /**< Block compressed 3 */
    HU_RES_VIEW_FORMAT_UNSIGNED_BC4  = 0x1c, /**< Block compressed 4 unsigned */
    HU_RES_VIEW_FORMAT_SIGNED_BC4    = 0x1d, /**< Block compressed 4 signed */
    HU_RES_VIEW_FORMAT_UNSIGNED_BC5  = 0x1e, /**< Block compressed 5 unsigned */
    HU_RES_VIEW_FORMAT_SIGNED_BC5    = 0x1f, /**< Block compressed 5 signed */
    HU_RES_VIEW_FORMAT_UNSIGNED_BC6H = 0x20, /**< Block compressed 6 unsigned half-float */
    HU_RES_VIEW_FORMAT_SIGNED_BC6H   = 0x21, /**< Block compressed 6 signed half-float */
    HU_RES_VIEW_FORMAT_UNSIGNED_BC7  = 0x22  /**< Block compressed 7 */
} HUresourceViewFormat;

/**
 * Resource view descriptor
 */
typedef struct HIP_RESOURCE_VIEW_DESC_st
{
    HUresourceViewFormat format;   /**< Resource view format */
    size_t width;                  /**< Width of the resource view */
    size_t height;                 /**< Height of the resource view */
    size_t depth;                  /**< Depth of the resource view */
    unsigned int firstMipmapLevel; /**< First defined mipmap level */
    unsigned int lastMipmapLevel;  /**< Last defined mipmap level */
    unsigned int firstLayer;       /**< First layer index */
    unsigned int lastLayer;        /**< Last layer index */
    unsigned int reserved[16];
} HIP_RESOURCE_VIEW_DESC;

/**
 * GPU Direct v3 tokens
 */
typedef struct HIP_POINTER_ATTRIBUTE_P2P_TOKENS_st {
    unsigned long long p2pToken;
    unsigned int vaSpaceToken;
} HIP_POINTER_ATTRIBUTE_P2P_TOKENS;

/**
 * Kernel launch parameters
 */
typedef struct HIP_LAUNCH_PARAMS_st {
    HUfunction function;         /**< Kernel to launch */
    unsigned int gridDimX;       /**< Width of grid in blocks */
    unsigned int gridDimY;       /**< Height of grid in blocks */
    unsigned int gridDimZ;       /**< Depth of grid in blocks */
    unsigned int blockDimX;      /**< X dimension of each thread block */
    unsigned int blockDimY;      /**< Y dimension of each thread block */
    unsigned int blockDimZ;      /**< Z dimension of each thread block */
    unsigned int sharedMemBytes; /**< Dynamic shared-memory size per thread block in bytes */
    HUstream hStream;            /**< Stream identifier */
    void **kernelParams;         /**< Array of pointers to kernel parameters */
} HIP_LAUNCH_PARAMS;

/**
 * If set, each kernel launched as part of ::huLaunchCooperativeKernelMultiDevice only
 * waits for prior work in the stream corresponding to that GPU to complete before the
 * kernel begins execution.
 */
#define HIP_COOPERATIVE_LAUNCH_MULTI_DEVICE_NO_PRE_LAUNCH_SYNC   0x01

/**
 * If set, any subsequent work pushed in a stream that participated in a call to
 * ::huLaunchCooperativeKernelMultiDevice will only wait for the kernel launched on
 * the GPU corresponding to that stream to complete before it begins execution.
 */
#define HIP_COOPERATIVE_LAUNCH_MULTI_DEVICE_NO_POST_LAUNCH_SYNC  0x02

/**
 * If set, the HIP array is a collection of layers, where each layer is either a 1D
 * or a 2D array and the Depth member of HIP_ARRAY3D_DESCRIPTOR specifies the number 
 * of layers, not the depth of a 3D array.
 */
#define HIP_ARRAY3D_LAYERED        0x01

/**
 * Deprecated, use HIP_ARRAY3D_LAYERED
 */
#define HIP_ARRAY3D_2DARRAY        0x01

/**
 * This flag must be set in order to bind a surface reference
 * to the HIP array
 */
#define HIP_ARRAY3D_SURFACE_LDST   0x02

/**
 * If set, the HIP array is a collection of six 2D arrays, representing faces of a hube. The
 * width of such a HIP array must be equal to its height, and Depth must be six.
 * If ::HIP_ARRAY3D_LAYERED flag is also set, then the HIP array is a collection of hubemaps
 * and Depth must be a multiple of six.
 */
#define HIP_ARRAY3D_CUBEMAP        0x04

/**
 * This flag must be set in order to perform texture gather operations
 * on a HIP array.
 */
#define HIP_ARRAY3D_TEXTURE_GATHER 0x08

/**
 * This flag if set indicates that the HIP
 * array is a DEPTH_TEXTURE.
*/
#define HIP_ARRAY3D_DEPTH_TEXTURE 0x10

/**
 * Override the texref format with a format inferred from the array.
 * Flag for ::huTexRefSetArray()
 */
#define HU_TRSA_OVERRIDE_FORMAT 0x01

/**
 * Read the texture as integers rather than promoting the values to floats
 * in the range [0,1].
 * Flag for ::huTexRefSetFlags()
 */
#define HU_TRSF_READ_AS_INTEGER         0x01

/**
 * Use normalized texture coordinates in the range [0,1) instead of [0,dim).
 * Flag for ::huTexRefSetFlags()
 */
#define HU_TRSF_NORMALIZED_COORDINATES  0x02

/**
 * Perform sRGB->linear conversion during texture read.
 * Flag for ::huTexRefSetFlags()
 */
#define HU_TRSF_SRGB  0x10

/**
 * End of array terminator for the \p extra parameter to
 * ::huLaunchKernel
 */
#define HU_LAUNCH_PARAM_END            ((void*)0x00)

/**
 * Indicator that the next value in the \p extra parameter to
 * ::huLaunchKernel will be a pointer to a buffer containing all kernel
 * parameters used for launching kernel \p f.  This buffer needs to
 * honor all alignment/padding requirements of the individual parameters.
 * If ::HU_LAUNCH_PARAM_BUFFER_SIZE is not also specified in the
 * \p extra array, then ::HU_LAUNCH_PARAM_BUFFER_POINTER will have no
 * effect.
 */
#define HU_LAUNCH_PARAM_BUFFER_POINTER ((void*)0x01)

/**
 * Indicator that the next value in the \p extra parameter to
 * ::huLaunchKernel will be a pointer to a size_t which contains the
 * size of the buffer specified with ::HU_LAUNCH_PARAM_BUFFER_POINTER.
 * It is required that ::HU_LAUNCH_PARAM_BUFFER_POINTER also be specified
 * in the \p extra array if the value associated with
 * ::HU_LAUNCH_PARAM_BUFFER_SIZE is not zero.
 */
#define HU_LAUNCH_PARAM_BUFFER_SIZE    ((void*)0x02)

/**
 * For texture references loaded into the module, use default texunit from
 * texture reference.
 */
#define HU_PARAM_TR_DEFAULT -1

/**
 * Device that represents the CPU
 */
#define HU_DEVICE_CPU               ((HUdevice)-1)

/**
 * Device that represents an invalid device
 */
#define HU_DEVICE_INVALID           ((HUdevice)-2)

/** @} */ /* END HIP_TYPES */

#ifdef _WIN32
#define HIPAPI __stdcall
#else
#define HIPAPI
#endif

/**
 * \defgroup HIP_ERROR Error Handling
 *
 * ___MANBRIEF___ error handling functions of the low-level HIP driver API
 * (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the error handling functions of the low-level HIP
 * driver application programming interface.
 *
 * @{
 */

/**
 * \brief Gets the string description of an error code
 *
 * Sets \p *pStr to the address of a NULL-terminated string description
 * of the error code \p error.
 * If the error code is not recognized, ::HIP_ERROR_INVALID_VALUE
 * will be returned and \p *pStr will be set to the NULL address.
 *
 * \param error - Error code to convert to string
 * \param pStr - Address of the string pointer.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::HUresult,
 * ::hipGetErrorString
 */
HUresult HIPAPI huGetErrorString(HUresult error, const char **pStr);

/**
 * \brief Gets the string representation of an error code enum name
 *
 * Sets \p *pStr to the address of a NULL-terminated string representation
 * of the name of the enum error code \p error.
 * If the error code is not recognized, ::HIP_ERROR_INVALID_VALUE
 * will be returned and \p *pStr will be set to the NULL address.
 *
 * \param error - Error code to convert to string
 * \param pStr - Address of the string pointer.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::HUresult,
 * ::hipGetErrorName
 */
HUresult HIPAPI huGetErrorName(HUresult error, const char **pStr);

/** @} */ /* END HIP_ERROR */

/**
 * \defgroup HIP_INITIALIZE Initialization
 *
 * ___MANBRIEF___ initialization functions of the low-level HIP driver API
 * (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the initialization functions of the low-level HIP
 * driver application programming interface.
 *
 * @{
 */

/**
 * \brief Initialize the HIP driver API
 *
 * Initializes the driver API and must be called before any other function from
 * the driver API. Currently, the \p Flags parameter must be 0. If ::huInit()
 * has not been called, any function from the driver API will return
 * ::HIP_ERROR_NOT_INITIALIZED.
 *
 * \param Flags - Initialization flag for HIP.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 */
HUresult HIPAPI huInit(unsigned int Flags);

/** @} */ /* END HIP_INITIALIZE */

/**
 * \defgroup HIP_VERSION Version Management
 *
 * ___MANBRIEF___ version management functions of the low-level HIP driver
 * API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the version management functions of the low-level
 * HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Returns the HIP driver version
 *
 * Returns in \p *driverVersion the version number of the installed HIP
 * driver. This function automatically returns ::HIP_ERROR_INVALID_VALUE if
 * the \p driverVersion argument is NULL.
 *
 * \param driverVersion - Returns the HIP driver version
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa
 * ::hipDriverGetVersion,
 * ::hipRuntimeGetVersion
 */
HUresult HIPAPI huDriverGetVersion(int *driverVersion);

/** @} */ /* END HIP_VERSION */

/**
 * \defgroup HIP_DEVICE Device Management
 *
 * ___MANBRIEF___ device management functions of the low-level HIP driver API
 * (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the device management functions of the low-level
 * HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Returns a handle to a compute device
 *
 * Returns in \p *device a device handle given an ordinal in the range <b>[0,
 * ::huDeviceGetCount()-1]</b>.
 *
 * \param device  - Returned device handle
 * \param ordinal - Device number to get handle for
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGetAttribute,
 * ::huDeviceGetCount,
 * ::huDeviceGetName,
 * ::huDeviceGetUuid,
 * ::huDeviceTotalMem
 */
HUresult HIPAPI huDeviceGet(HUdevice *device, int ordinal);

/**
 * \brief Returns the number of compute-capable devices
 *
 * Returns in \p *count the number of devices with compute capability greater
 * than or equal to 2.0 that are available for execution. If there is no such
 * device, ::huDeviceGetCount() returns 0.
 *
 * \param count - Returned number of compute-capable devices
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGetAttribute,
 * ::huDeviceGetName,
 * ::huDeviceGetUuid,
 * ::huDeviceGet,
 * ::huDeviceTotalMem,
 * ::hipGetDeviceCount
 */
HUresult HIPAPI huDeviceGetCount(int *count);

/**
 * \brief Returns an identifer string for the device
 *
 * Returns an ASCII string identifying the device \p dev in the NULL-terminated
 * string pointed to by \p name. \p len specifies the maximum length of the
 * string that may be returned.
 *
 * \param name - Returned identifier string for the device
 * \param len  - Maximum length of string to store in \p name
 * \param dev  - Device to get identifier string for
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGetAttribute,
 * ::huDeviceGetCount,
 * ::huDeviceGet,
 * ::huDeviceTotalMem,
 * ::hipGetDeviceProperties
 */
HUresult HIPAPI huDeviceGetName(char *name, int len, HUdevice dev);

/**
 * \brief Return an UUID for the device
 *
 * Returns 16-octets identifing the device \p dev in the structure
 * pointed by the \p uuid.
 *
 * \param uuid - Returned UUID
 * \param dev  - Device to get identifier string for
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGetAttribute,
 * ::huDeviceGetCount,
 * ::huDeviceGetName,
 * ::huDeviceGet,
 * ::huDeviceTotalMem,
 * ::hipGetDeviceProperties
 */
HUresult HIPAPI huDeviceGetUuid(HUuuid *uuid, HUdevice dev);

/**
 * \brief Returns the total amount of memory on the device
 *
 * Returns in \p *bytes the total amount of memory available on the device
 * \p dev in bytes.
 *
 * \param bytes - Returned memory available on device in bytes
 * \param dev   - Device handle
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGetAttribute,
 * ::huDeviceGetCount,
 * ::huDeviceGetName,
 * ::huDeviceGetUuid,
 * ::huDeviceGet,
 * ::hipMemGetInfo
 */
HUresult HIPAPI huDeviceTotalMem(size_t *bytes, HUdevice dev);

/**
 * \brief Returns information about the device
 *
 * Returns in \p *pi the integer value of the attribute \p attrib on device
 * \p dev. The supported attributes are:
 * - ::HU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK: Maximum number of threads per
 *   block;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X: Maximum x-dimension of a block;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y: Maximum y-dimension of a block;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z: Maximum z-dimension of a block;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X: Maximum x-dimension of a grid;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Y: Maximum y-dimension of a grid;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Z: Maximum z-dimension of a grid;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK: Maximum amount of
 *   shared memory available to a thread block in bytes;
 * - ::HU_DEVICE_ATTRIBUTE_TOTAL_CONSTANT_MEMORY: Memory available on device for
 *   __constant__ variables in a HIP C kernel in bytes;
 * - ::HU_DEVICE_ATTRIBUTE_WARP_SIZE: Warp size in threads;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_PITCH: Maximum pitch in bytes allowed by the
 *   memory copy functions that involve memory regions allocated through
 *   ::huMemAllocPitch();
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_WIDTH: Maximum 1D 
 *  texture width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LINEAR_WIDTH: Maximum width
 *  for a 1D texture bound to linear memory;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_MIPMAPPED_WIDTH: Maximum 
 *  mipmapped 1D texture width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_WIDTH: Maximum 2D 
 *  texture width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_HEIGHT: Maximum 2D 
 *  texture height;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_WIDTH: Maximum width
 *  for a 2D texture bound to linear memory;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_HEIGHT: Maximum height
 *  for a 2D texture bound to linear memory;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_PITCH: Maximum pitch
 *  in bytes for a 2D texture bound to linear memory;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_WIDTH: Maximum 
 *  mipmapped 2D texture width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_HEIGHT: Maximum
 *  mipmapped 2D texture height;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH: Maximum 3D 
 *  texture width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT: Maximum 3D 
 *  texture height;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH: Maximum 3D 
 *  texture depth;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH_ALTERNATE: 
 *  Alternate maximum 3D texture width, 0 if no alternate
 *  maximum 3D texture size is supported;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT_ALTERNATE: 
 *  Alternate maximum 3D texture height, 0 if no alternate
 *  maximum 3D texture size is supported;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH_ALTERNATE: 
 *  Alternate maximum 3D texture depth, 0 if no alternate
 *  maximum 3D texture size is supported;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_WIDTH:
 *  Maximum hubemap texture width or height;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_WIDTH: 
 *  Maximum 1D layered texture width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_LAYERS: 
 *   Maximum layers in a 1D layered texture;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_WIDTH: 
 *  Maximum 2D layered texture width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_HEIGHT: 
 *   Maximum 2D layered texture height;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_LAYERS: 
 *   Maximum layers in a 2D layered texture;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_WIDTH: 
 *   Maximum hubemap layered texture width or height;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_LAYERS: 
 *   Maximum layers in a hubemap layered texture;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_WIDTH:
 *   Maximum 1D surface width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_WIDTH:
 *   Maximum 2D surface width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_HEIGHT:
 *   Maximum 2D surface height;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_WIDTH:
 *   Maximum 3D surface width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_HEIGHT:
 *   Maximum 3D surface height;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_DEPTH:
 *   Maximum 3D surface depth;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_WIDTH:
 *   Maximum 1D layered surface width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_LAYERS:
 *   Maximum layers in a 1D layered surface;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_WIDTH:
 *   Maximum 2D layered surface width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_HEIGHT:
 *   Maximum 2D layered surface height;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_LAYERS:
 *   Maximum layers in a 2D layered surface;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_WIDTH:
 *   Maximum hubemap surface width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_WIDTH:
 *   Maximum hubemap layered surface width;
 * - ::HU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_LAYERS:
 *   Maximum layers in a hubemap layered surface;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_BLOCK: Maximum number of 32-bit
 *   registers available to a thread block;
 * - ::HU_DEVICE_ATTRIBUTE_CLOCK_RATE: The typical clock frequency in kilohertz;
 * - ::HU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT: Alignment requirement; texture
 *   base addresses aligned to ::textureAlign bytes do not need an offset
 *   applied to texture fetches;
 * - ::HU_DEVICE_ATTRIBUTE_TEXTURE_PITCH_ALIGNMENT: Pitch alignment requirement
 *   for 2D texture references bound to pitched memory;
 * - ::HU_DEVICE_ATTRIBUTE_GPU_OVERLAP: 1 if the device can concurrently copy
 *   memory between host and device while executing a kernel, or 0 if not;
 * - ::HU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT: Number of multiprocessors on
 *   the device;
 * - ::HU_DEVICE_ATTRIBUTE_KERNEL_EXEC_TIMEOUT: 1 if there is a run time limit
 *   for kernels executed on the device, or 0 if not;
 * - ::HU_DEVICE_ATTRIBUTE_INTEGRATED: 1 if the device is integrated with the
 *   memory subsystem, or 0 if not;
 * - ::HU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY: 1 if the device can map host
 *   memory into the HIP address space, or 0 if not;
 * - ::HU_DEVICE_ATTRIBUTE_COMPUTE_MODE: Compute mode that device is currently
 *   in. Available modes are as follows:
 *   - ::HU_COMPUTEMODE_DEFAULT: Default mode - Device is not restricted and
 *     can have multiple HIP contexts present at a single time.
 *   - ::HU_COMPUTEMODE_PROHIBITED: Compute-prohibited mode - Device is
 *     prohibited from creating new HIP contexts.
 *   - ::HU_COMPUTEMODE_EXCLUSIVE_PROCESS:  Compute-exclusive-process mode - Device
 *     can have only one context used by a single process at a time.
 * - ::HU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS: 1 if the device supports
 *   executing multiple kernels within the same context simultaneously, or 0 if
 *   not. It is not guaranteed that multiple kernels will be resident
 *   on the device concurrently so this feature should not be relied upon for
 *   correctness;
 * - ::HU_DEVICE_ATTRIBUTE_ECC_ENABLED: 1 if error correction is enabled on the
 *    device, 0 if error correction is disabled or not supported by the device;
 * - ::HU_DEVICE_ATTRIBUTE_PCI_BUS_ID: PCI bus identifier of the device;
 * - ::HU_DEVICE_ATTRIBUTE_PCI_DEVICE_ID: PCI device (also known as slot) identifier
 *   of the device;
 * - ::HU_DEVICE_ATTRIBUTE_PCI_DOMAIN_ID: PCI domain identifier of the device
 * - ::HU_DEVICE_ATTRIBUTE_TCC_DRIVER: 1 if the device is using a TCC driver. TCC
 *    is only available on Tesla hardware running Windows Vista or later;
 * - ::HU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE: Peak memory clock frequency in kilohertz;
 * - ::HU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH: Global memory bus width in bits;
 * - ::HU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE: Size of L2 cache in bytes. 0 if the device doesn't have L2 cache;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR: Maximum resident threads per multiprocessor;
 * - ::HU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING: 1 if the device shares a unified address space with 
 *   the host, or 0 if not;
 * - ::HU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MAJOR: Major compute capability version number;
 * - ::HU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MINOR: Minor compute capability version number;
 * - ::HU_DEVICE_ATTRIBUTE_GLOBAL_L1_CACHE_SUPPORTED: 1 if device supports caching globals 
 *    in L1 cache, 0 if caching globals in L1 cache is not supported by the device;
 * - ::HU_DEVICE_ATTRIBUTE_LOCAL_L1_CACHE_SUPPORTED: 1 if device supports caching locals 
 *    in L1 cache, 0 if caching locals in L1 cache is not supported by the device;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_MULTIPROCESSOR: Maximum amount of
 *   shared memory available to a multiprocessor in bytes; this amount is shared
 *   by all thread blocks simultaneously resident on a multiprocessor;
 * - ::HU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_MULTIPROCESSOR: Maximum number of 32-bit
 *   registers available to a multiprocessor; this number is shared by all thread
 *   blocks simultaneously resident on a multiprocessor;
 * - ::HU_DEVICE_ATTRIBUTE_MANAGED_MEMORY: 1 if device supports allocating managed memory
 *   on this system, 0 if allocating managed memory is not supported by the device on this system.
 * - ::HU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD: 1 if device is on a multi-GPU board, 0 if not.
 * - ::HU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD_GROUP_ID: Unique identifier for a group of devices
 *   associated with the same board. Devices on the same multi-GPU board will share the same identifier.
 * - ::HU_DEVICE_ATTRIBUTE_HOST_NATIVE_ATOMIC_SUPPORTED: 1 if Link between the device and the host
 *   supports native atomic operations.
 * - ::HU_DEVICE_ATTRIBUTE_SINGLE_TO_DOUBLE_PRECISION_PERF_RATIO: Ratio of single precision performance
 *   (in floating-point operations per second) to double precision performance.
 * - ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS: Device suppports coherently accessing
 *   pageable memory without calling hipHostRegister on it.
 * - ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS: Device can coherently access managed memory
 *   concurrently with the CPU.
 * - ::HU_DEVICE_ATTRIBUTE_COMPUTE_PREEMPTION_SUPPORTED: Device supports Compute Preemption.
 * - ::HU_DEVICE_ATTRIBUTE_CAN_USE_HOST_POINTER_FOR_REGISTERED_MEM: Device can access host registered
 *   memory at the same virtual address as the CPU.
 * -  ::HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK_OPTIN: The maximum per block shared memory size
 *    suported on this device. This is the maximum value that can be opted into when using the huFuncSetAttribute() call.
 *    For more details see ::HU_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES
 * - ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES: Device accesses pageable memory via the host's
 *   page tables.
 * - ::HU_DEVICE_ATTRIBUTE_DIRECT_MANAGED_MEM_ACCESS_FROM_HOST: The host can directly access managed memory on the device without migration.
 *
 * \param pi     - Returned device attribute value
 * \param attrib - Device attribute to query
 * \param dev    - Device handle
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGetCount,
 * ::huDeviceGetName,
 * ::huDeviceGetUuid,
 * ::huDeviceGet,
 * ::huDeviceTotalMem,
 * ::hipDeviceGetAttribute,
 * ::hipGetDeviceProperties
 */
HUresult HIPAPI huDeviceGetAttribute(int *pi, HUdevice_attribute attrib, HUdevice dev);

/** @} */ /* END HIP_DEVICE */

/**
 * \defgroup HIP_DEVICE_DEPRECATED Device Management [DEPRECATED]
 *
 * ___MANBRIEF___ deprecated device management functions of the low-level HIP
 * driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the device management functions of the low-level
 * HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Returns properties for a selected device
 *
 * \deprecated
 *
 * This function was deprecated as of HIP 5.0 and replaced by ::huDeviceGetAttribute().
 *
 * Returns in \p *prop the properties of device \p dev. The ::HUdevprop
 * structure is defined as:
 *
 * \code
     typedef struct HUdevprop_st {
     int maxThreadsPerBlock;
     int maxThreadsDim[3];
     int maxGridSize[3];
     int sharedMemPerBlock;
     int totalConstantMemory;
     int SIMDWidth;
     int memPitch;
     int regsPerBlock;
     int clockRate;
     int textureAlign
  } HUdevprop;
 * \endcode
 * where:
 *
 * - ::maxThreadsPerBlock is the maximum number of threads per block;
 * - ::maxThreadsDim[3] is the maximum sizes of each dimension of a block;
 * - ::maxGridSize[3] is the maximum sizes of each dimension of a grid;
 * - ::sharedMemPerBlock is the total amount of shared memory available per
 *   block in bytes;
 * - ::totalConstantMemory is the total amount of constant memory available on
 *   the device in bytes;
 * - ::SIMDWidth is the warp size;
 * - ::memPitch is the maximum pitch allowed by the memory copy functions that
 *   involve memory regions allocated through ::huMemAllocPitch();
 * - ::regsPerBlock is the total number of registers available per block;
 * - ::clockRate is the clock frequency in kilohertz;
 * - ::textureAlign is the alignment requirement; texture base addresses that
 *   are aligned to ::textureAlign bytes do not need an offset applied to
 *   texture fetches.
 *
 * \param prop - Returned properties of device
 * \param dev  - Device to get properties for
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGetAttribute,
 * ::huDeviceGetCount,
 * ::huDeviceGetName,
 * ::huDeviceGetUuid,
 * ::huDeviceGet,
 * ::huDeviceTotalMem
 */
__HIP_DEPRECATED HUresult HIPAPI huDeviceGetProperties(HUdevprop *prop, HUdevice dev);

/**
 * \brief Returns the compute capability of the device
 *
 * \deprecated
 *
 * This function was deprecated as of HIP 5.0 and its functionality superceded
 * by ::huDeviceGetAttribute(). 
 *
 * Returns in \p *major and \p *minor the major and minor revision numbers that
 * define the compute capability of the device \p dev.
 *
 * \param major - Major revision number
 * \param minor - Minor revision number
 * \param dev   - Device handle
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGetAttribute,
 * ::huDeviceGetCount,
 * ::huDeviceGetName,
 * ::huDeviceGetUuid,
 * ::huDeviceGet,
 * ::huDeviceTotalMem
 */
__HIP_DEPRECATED HUresult HIPAPI huDeviceComputeCapability(int *major, int *minor, HUdevice dev);

/** @} */ /* END HIP_DEVICE_DEPRECATED */

/**
 * \defgroup HIP_PRIMARY_CTX Primary Context Management
 *
 * ___MANBRIEF___ primary context management functions of the low-level HIP driver
 * API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the primary context management functions of the low-level
 * HIP driver application programming interface.
 *
 * The primary context is unique per device and shared with the HIP runtime API.
 * These functions allow integration with other libraries using HIP.
 *
 * @{
 */

/**
 * \brief Retain the primary context on the GPU
 *
 * Retains the primary context on the device, creating it if necessary,
 * increasing its usage count. The caller must call
 * ::huDevicePrimaryCtxRelease() when done using the context.
 * Unlike ::huCtxCreate() the newly created context is not pushed onto the stack.
 *
 * Context creation will fail with ::HIP_ERROR_UNKNOWN if the compute mode of
 * the device is ::HU_COMPUTEMODE_PROHIBITED.  The function ::huDeviceGetAttribute() 
 * can be used with ::HU_DEVICE_ATTRIBUTE_COMPUTE_MODE to determine the compute mode 
 * of the device. 
 * The <i>nvidia-smi</i> tool can be used to set the compute mode for
 * devices. Documentation for <i>nvidia-smi</i> can be obtained by passing a
 * -h option to it.
 *
 * Please note that the primary context always supports pinned allocations. Other
 * flags can be specified by ::huDevicePrimaryCtxSetFlags().
 *
 * \param pctx  - Returned context handle of the new context
 * \param dev   - Device for which primary context is requested
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_DEVICE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa ::huDevicePrimaryCtxRelease,
 * ::huDevicePrimaryCtxSetFlags,
 * ::huCtxCreate,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize
 */
HUresult HIPAPI huDevicePrimaryCtxRetain(HUcontext *pctx, HUdevice dev);

/**
 * \brief Release the primary context on the GPU
 *
 * Releases the primary context interop on the device by decreasing the usage
 * count by 1. If the usage drops to 0 the primary context of device \p dev
 * will be destroyed regardless of how many threads it is current to.
 *
 * Please note that unlike ::huCtxDestroy() this method does not pop the context
 * from stack in any circumstances.
 *
 * \param dev - Device which primary context is released
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa ::huDevicePrimaryCtxRetain,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize
 */
HUresult HIPAPI huDevicePrimaryCtxRelease(HUdevice dev);

/**
 * \brief Set flags for the primary context
 *
 * Sets the flags for the primary context on the device overwriting perviously
 * set ones. If the primary context is already created
 * ::HIP_ERROR_PRIMARY_CONTEXT_ACTIVE is returned.
 *
 * The three LSBs of the \p flags parameter can be used to control how the OS
 * thread, which owns the HIP context at the time of an API call, interacts
 * with the OS scheduler when waiting for results from the GPU. Only one of
 * the scheduling flags can be set when creating a context.
 *
 * - ::HU_CTX_SCHED_SPIN: Instruct HIP to actively spin when waiting for
 * results from the GPU. This can decrease latency when waiting for the GPU,
 * but may lower the performance of CPU threads if they are performing work in
 * parallel with the HIP thread.
 *
 * - ::HU_CTX_SCHED_YIELD: Instruct HIP to yield its thread when waiting for
 * results from the GPU. This can increase latency when waiting for the GPU,
 * but can increase the performance of CPU threads performing work in parallel
 * with the GPU.
 *
 * - ::HU_CTX_SCHED_BLOCKING_SYNC: Instruct HIP to block the CPU thread on a
 * synchronization primitive when waiting for the GPU to finish work.
 *
 * - ::HU_CTX_BLOCKING_SYNC: Instruct HIP to block the CPU thread on a
 * synchronization primitive when waiting for the GPU to finish work. <br>
 * <b>Deprecated:</b> This flag was deprecated as of HIP 4.0 and was
 * replaced with ::HU_CTX_SCHED_BLOCKING_SYNC.
 *
 * - ::HU_CTX_SCHED_AUTO: The default value if the \p flags parameter is zero,
 * uses a heuristic based on the number of active HIP contexts in the
 * process \e C and the number of logical processors in the system \e P. If
 * \e C > \e P, then HIP will yield to other OS threads when waiting for
 * the GPU (::HU_CTX_SCHED_YIELD), otherwise HIP will not yield while
 * waiting for results and actively spin on the processor (::HU_CTX_SCHED_SPIN).
 * However, on low power devices like Tegra, it always defaults to
 * ::HU_CTX_SCHED_BLOCKING_SYNC.
 *
 * - ::HU_CTX_LMEM_RESIZE_TO_MAX: Instruct HIP to not reduce local memory
 * after resizing local memory for a kernel. This can prevent thrashing by
 * local memory allocations when launching many kernels with high local
 * memory usage at the cost of potentially increased memory usage.
 *
 * \param dev   - Device for which the primary context flags are set
 * \param flags - New flags for the device
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_DEVICE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_PRIMARY_CONTEXT_ACTIVE
 * \notefnerr
 *
 * \sa ::huDevicePrimaryCtxRetain,
 * ::huDevicePrimaryCtxGetState,
 * ::huCtxCreate,
 * ::huCtxGetFlags,
 * ::hipSetDeviceFlags
 */
HUresult HIPAPI huDevicePrimaryCtxSetFlags(HUdevice dev, unsigned int flags);

/**
 * \brief Get the state of the primary context
 *
 * Returns in \p *flags the flags for the primary context of \p dev, and in
 * \p *active whether it is active.  See ::huDevicePrimaryCtxSetFlags for flag
 * values.
 *
 * \param dev    - Device to get primary context flags for
 * \param flags  - Pointer to store flags
 * \param active - Pointer to store context state; 0 = inactive, 1 = active
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_DEVICE,
 * ::HIP_ERROR_INVALID_VALUE,
 * \notefnerr
 *
 * \sa
 * ::huDevicePrimaryCtxSetFlags,
 * ::huCtxGetFlags,
 * ::hipGetDeviceFlags
 */
HUresult HIPAPI huDevicePrimaryCtxGetState(HUdevice dev, unsigned int *flags, int *active);

/**
 * \brief Destroy all allocations and reset all state on the primary context
 *
 * Explicitly destroys and cleans up all resources associated with the current
 * device in the current process.
 *
 * Note that it is responsibility of the calling function to ensure that no
 * other module in the process is using the device any more. For that reason
 * it is recommended to use ::huDevicePrimaryCtxRelease() in most cases.
 * However it is safe for other modules to call ::huDevicePrimaryCtxRelease()
 * even after resetting the device.
 *
 * \param dev - Device for which primary context is destroyed
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_DEVICE,
 * ::HIP_ERROR_PRIMARY_CONTEXT_ACTIVE
 * \notefnerr
 *
 * \sa ::huDevicePrimaryCtxRetain,
 * ::huDevicePrimaryCtxRelease,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize,
 * ::hipDeviceReset
 */
HUresult HIPAPI huDevicePrimaryCtxReset(HUdevice dev);

/** @} */ /* END HIP_PRIMARY_CTX */


/**
 * \defgroup HIP_CTX Context Management
 *
 * ___MANBRIEF___ context management functions of the low-level HIP driver
 * API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the context management functions of the low-level
 * HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Create a HIP context
 *
 * Creates a new HIP context and associates it with the calling thread. The
 * \p flags parameter is described below. The context is created with a usage
 * count of 1 and the caller of ::huCtxCreate() must call ::huCtxDestroy() or
 * when done using the context. If a context is already current to the thread, 
 * it is supplanted by the newly created context and may be restored by a subsequent 
 * call to ::huCtxPopCurrent().
 *
 * The three LSBs of the \p flags parameter can be used to control how the OS
 * thread, which owns the HIP context at the time of an API call, interacts
 * with the OS scheduler when waiting for results from the GPU. Only one of
 * the scheduling flags can be set when creating a context.
 *
 * - ::HU_CTX_SCHED_SPIN: Instruct HIP to actively spin when waiting for
 * results from the GPU. This can decrease latency when waiting for the GPU,
 * but may lower the performance of CPU threads if they are performing work in
 * parallel with the HIP thread.
 *
 * - ::HU_CTX_SCHED_YIELD: Instruct HIP to yield its thread when waiting for
 * results from the GPU. This can increase latency when waiting for the GPU,
 * but can increase the performance of CPU threads performing work in parallel
 * with the GPU.
 * 
 * - ::HU_CTX_SCHED_BLOCKING_SYNC: Instruct HIP to block the CPU thread on a
 * synchronization primitive when waiting for the GPU to finish work.
 *
 * - ::HU_CTX_BLOCKING_SYNC: Instruct HIP to block the CPU thread on a
 * synchronization primitive when waiting for the GPU to finish work. <br>
 * <b>Deprecated:</b> This flag was deprecated as of HIP 4.0 and was
 * replaced with ::HU_CTX_SCHED_BLOCKING_SYNC. 
 *
 * - ::HU_CTX_SCHED_AUTO: The default value if the \p flags parameter is zero,
 * uses a heuristic based on the number of active HIP contexts in the
 * process \e C and the number of logical processors in the system \e P. If
 * \e C > \e P, then HIP will yield to other OS threads when waiting for 
 * the GPU (::HU_CTX_SCHED_YIELD), otherwise HIP will not yield while 
 * waiting for results and actively spin on the processor (::HU_CTX_SCHED_SPIN). 
 * However, on low power devices like Tegra, it always defaults to 
 * ::HU_CTX_SCHED_BLOCKING_SYNC.
 *
 * - ::HU_CTX_MAP_HOST: Instruct HIP to support mapped pinned allocations.
 * This flag must be set in order to allocate pinned host memory that is
 * accessible to the GPU.
 *
 * - ::HU_CTX_LMEM_RESIZE_TO_MAX: Instruct HIP to not reduce local memory
 * after resizing local memory for a kernel. This can prevent thrashing by
 * local memory allocations when launching many kernels with high local
 * memory usage at the cost of potentially increased memory usage.
 *
 * Context creation will fail with ::HIP_ERROR_UNKNOWN if the compute mode of
 * the device is ::HU_COMPUTEMODE_PROHIBITED. The function ::huDeviceGetAttribute() 
 * can be used with ::HU_DEVICE_ATTRIBUTE_COMPUTE_MODE to determine the 
 * compute mode of the device. The <i>nvidia-smi</i> tool can be used to set 
 * the compute mode for * devices. 
 * Documentation for <i>nvidia-smi</i> can be obtained by passing a
 * -h option to it.
 *
 * \param pctx  - Returned context handle of the new context
 * \param flags - Context creation flags
 * \param dev   - Device to create context on
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_DEVICE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize
 */
HUresult HIPAPI huCtxCreate(HUcontext *pctx, unsigned int flags, HUdevice dev);

/**
 * \brief Destroy a HIP context
 *
 * Destroys the HIP context specified by \p ctx.  The context \p ctx will be
 * destroyed regardless of how many threads it is current to.
 * It is the responsibility of the calling function to ensure that no API
 * call issues using \p ctx while ::huCtxDestroy() is executing.
 *
 * If \p ctx is current to the calling thread then \p ctx will also be 
 * popped from the current thread's context stack (as though ::huCtxPopCurrent()
 * were called).  If \p ctx is current to other threads, then \p ctx will
 * remain current to those threads, and attempting to access \p ctx from
 * those threads will result in the error ::HIP_ERROR_CONTEXT_IS_DESTROYED.
 *
 * \param ctx - Context to destroy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize
 */
HUresult HIPAPI huCtxDestroy(HUcontext ctx);

/**
 * \brief Pushes a context on the current CPU thread
 *
 * Pushes the given context \p ctx onto the CPU thread's stack of current
 * contexts. The specified context becomes the CPU thread's current context, so
 * all HIP functions that operate on the current context are affected.
 *
 * The previous current context may be made current again by calling
 * ::huCtxDestroy() or ::huCtxPopCurrent().
 *
 * \param ctx - Context to push
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize
 */
HUresult HIPAPI huCtxPushCurrent(HUcontext ctx);

/**
 * \brief Pops the current HIP context from the current CPU thread.
 *
 * Pops the current HIP context from the CPU thread and passes back the 
 * old context handle in \p *pctx. That context may then be made current 
 * to a different CPU thread by calling ::huCtxPushCurrent().
 *
 * If a context was current to the CPU thread before ::huCtxCreate() or
 * ::huCtxPushCurrent() was called, this function makes that context current to
 * the CPU thread again.
 *
 * \param pctx - Returned new context handle
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize
 */
HUresult HIPAPI huCtxPopCurrent(HUcontext *pctx);

/**
 * \brief Binds the specified HIP context to the calling CPU thread
 *
 * Binds the specified HIP context to the calling CPU thread.
 * If \p ctx is NULL then the HIP context previously bound to the
 * calling CPU thread is unbound and ::HIP_SUCCESS is returned.
 *
 * If there exists a HIP context stack on the calling CPU thread, this
 * will replace the top of that stack with \p ctx.  
 * If \p ctx is NULL then this will be equivalent to popping the top
 * of the calling CPU thread's HIP context stack (or a no-op if the
 * calling CPU thread's HIP context stack is empty).
 *
 * \param ctx - Context to bind to the calling CPU thread
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT
 * \notefnerr
 *
 * \sa
 * ::huCtxGetCurrent,
 * ::huCtxCreate,
 * ::huCtxDestroy,
 * ::hipSetDevice
 */
HUresult HIPAPI huCtxSetCurrent(HUcontext ctx);

/**
 * \brief Returns the HIP context bound to the calling CPU thread.
 *
 * Returns in \p *pctx the HIP context bound to the calling CPU thread.
 * If no context is bound to the calling CPU thread then \p *pctx is
 * set to NULL and ::HIP_SUCCESS is returned.
 *
 * \param pctx - Returned context handle
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * \notefnerr
 *
 * \sa
 * ::huCtxSetCurrent,
 * ::huCtxCreate,
 * ::huCtxDestroy,
 * ::hipGetDevice
 */
HUresult HIPAPI huCtxGetCurrent(HUcontext *pctx);

/**
 * \brief Returns the device ID for the current context
 *
 * Returns in \p *device the ordinal of the current context's device.
 *
 * \param device - Returned device ID for the current context
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize,
 * ::hipGetDevice
 */
HUresult HIPAPI huCtxGetDevice(HUdevice *device);

/**
 * \brief Returns the flags for the current context
 *
 * Returns in \p *flags the flags of the current context. See ::huCtxCreate
 * for flag values.
 *
 * \param flags - Pointer to store flags of current context
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetCurrent,
 * ::huCtxGetDevice
 * ::huCtxGetLimit,
 * ::huCtxGetSharedMemConfig,
 * ::huCtxGetStreamPriorityRange,
 * ::hipGetDeviceFlags
 */
HUresult HIPAPI huCtxGetFlags(unsigned int *flags);

/**
 * \brief Block for a context's tasks to complete
 *
 * Blocks until the device has completed all preceding requested tasks.
 * ::huCtxSynchronize() returns an error if one of the preceding tasks failed.
 * If the context was created with the ::HU_CTX_SCHED_BLOCKING_SYNC flag, the 
 * CPU thread will block until the GPU context has finished its work.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::hipDeviceSynchronize
 */
HUresult HIPAPI huCtxSynchronize(void);

/**
 * \brief Set resource limits
 *
 * Setting \p limit to \p value is a request by the application to update
 * the current limit maintained by the context. The driver is free to
 * modify the requested value to meet h/w requirements (this could be
 * clamping to minimum or maximum values, rounding up to nearest element
 * size, etc). The application can use ::huCtxGetLimit() to find out exactly
 * what the limit has been set to.
 *
 * Setting each ::HUlimit has its own specific restrictions, so each is
 * discussed here.
 *
 * - ::HU_LIMIT_STACK_SIZE controls the stack size in bytes of each GPU thread.
 *
 * - ::HU_LIMIT_PRINTF_FIFO_SIZE controls the size in bytes of the FIFO used
 *   by the ::printf() device system call. Setting ::HU_LIMIT_PRINTF_FIFO_SIZE
 *   must be performed before launching any kernel that uses the ::printf()
 *   device system call, otherwise ::HIP_ERROR_INVALID_VALUE will be returned.
 *
 * - ::HU_LIMIT_MALLOC_HEAP_SIZE controls the size in bytes of the heap used
 *   by the ::malloc() and ::free() device system calls. Setting
 *   ::HU_LIMIT_MALLOC_HEAP_SIZE must be performed before launching any kernel
 *   that uses the ::malloc() or ::free() device system calls, otherwise
 *   ::HIP_ERROR_INVALID_VALUE will be returned.
 *
 * - ::HU_LIMIT_DEV_RUNTIME_SYNC_DEPTH controls the maximum nesting depth of
 *   a grid at which a thread can safely call ::hipDeviceSynchronize(). Setting
 *   this limit must be performed before any launch of a kernel that uses the 
 *   device runtime and calls ::hipDeviceSynchronize() above the default sync
 *   depth, two levels of grids. Calls to ::hipDeviceSynchronize() will fail 
 *   with error code ::hipErrorSyncDepthExceeded if the limitation is 
 *   violated. This limit can be set smaller than the default or up the maximum
 *   launch depth of 24. When setting this limit, keep in mind that additional
 *   levels of sync depth require the driver to reserve large amounts of device
 *   memory which can no longer be used for user allocations. If these 
 *   reservations of device memory fail, ::huCtxSetLimit will return 
 *   ::HIP_ERROR_OUT_OF_MEMORY, and the limit can be reset to a lower value.
 *   This limit is only applicable to devices of compute capability 3.5 and
 *   higher. Attempting to set this limit on devices of compute capability less
 *   than 3.5 will result in the error ::HIP_ERROR_UNSUPPORTED_LIMIT being 
 *   returned.
 *
 * - ::HU_LIMIT_DEV_RUNTIME_PENDING_LAUNCH_COUNT controls the maximum number of
 *   outstanding device runtime launches that can be made from the current
 *   context. A grid is outstanding from the point of launch up until the grid
 *   is known to have been completed. Device runtime launches which violate 
 *   this limitation fail and return ::hipErrorLaunchPendingCountExceeded when
 *   ::hipGetLastError() is called after launch. If more pending launches than
 *   the default (2048 launches) are needed for a module using the device
 *   runtime, this limit can be increased. Keep in mind that being able to
 *   sustain additional pending launches will require the driver to reserve
 *   larger amounts of device memory upfront which can no longer be used for
 *   allocations. If these reservations fail, ::huCtxSetLimit will return
 *   ::HIP_ERROR_OUT_OF_MEMORY, and the limit can be reset to a lower value.
 *   This limit is only applicable to devices of compute capability 3.5 and
 *   higher. Attempting to set this limit on devices of compute capability less
 *   than 3.5 will result in the error ::HIP_ERROR_UNSUPPORTED_LIMIT being
 *   returned.
 *
 * \param limit - Limit to set
 * \param value - Size of limit
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_UNSUPPORTED_LIMIT,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSynchronize,
 * ::hipDeviceSetLimit
 */
HUresult HIPAPI huCtxSetLimit(HUlimit limit, size_t value);

/**
 * \brief Returns resource limits
 *
 * Returns in \p *pvalue the current size of \p limit.  The supported
 * ::HUlimit values are:
 * - ::HU_LIMIT_STACK_SIZE: stack size in bytes of each GPU thread.
 * - ::HU_LIMIT_PRINTF_FIFO_SIZE: size in bytes of the FIFO used by the
 *   ::printf() device system call.
 * - ::HU_LIMIT_MALLOC_HEAP_SIZE: size in bytes of the heap used by the
 *   ::malloc() and ::free() device system calls.
 * - ::HU_LIMIT_DEV_RUNTIME_SYNC_DEPTH: maximum grid depth at which a thread
 *   can issue the device runtime call ::hipDeviceSynchronize() to wait on
 *   child grid launches to complete.
 * - ::HU_LIMIT_DEV_RUNTIME_PENDING_LAUNCH_COUNT: maximum number of outstanding
 *   device runtime launches that can be made from this context.
 *
 * \param limit  - Limit to query
 * \param pvalue - Returned size of limit
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_UNSUPPORTED_LIMIT
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize,
 * ::hipDeviceGetLimit
 */
HUresult HIPAPI huCtxGetLimit(size_t *pvalue, HUlimit limit);

/**
 * \brief Returns the preferred cache configuration for the current context.
 *
 * On devices where the L1 cache and shared memory use the same hardware
 * resources, this function returns through \p pconfig the preferred cache configuration
 * for the current context. This is only a preference. The driver will use
 * the requested configuration if possible, but it is free to choose a different
 * configuration if required to execute functions.
 *
 * This will return a \p pconfig of ::HU_FUNC_CACHE_PREFER_NONE on devices
 * where the size of the L1 cache and shared memory are fixed.
 *
 * The supported cache configurations are:
 * - ::HU_FUNC_CACHE_PREFER_NONE: no preference for shared memory or L1 (default)
 * - ::HU_FUNC_CACHE_PREFER_SHARED: prefer larger shared memory and smaller L1 cache
 * - ::HU_FUNC_CACHE_PREFER_L1: prefer larger L1 cache and smaller shared memory
 * - ::HU_FUNC_CACHE_PREFER_EQUAL: prefer equal sized L1 cache and shared memory
 *
 * \param pconfig - Returned cache configuration
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize,
 * ::huFuncSetCacheConfig,
 * ::hipDeviceGetCacheConfig
 */
HUresult HIPAPI huCtxGetCacheConfig(HUfunc_cache *pconfig);

/**
 * \brief Sets the preferred cache configuration for the current context.
 *
 * On devices where the L1 cache and shared memory use the same hardware
 * resources, this sets through \p config the preferred cache configuration for
 * the current context. This is only a preference. The driver will use
 * the requested configuration if possible, but it is free to choose a different
 * configuration if required to execute the function. Any function preference
 * set via ::huFuncSetCacheConfig() will be preferred over this context-wide
 * setting. Setting the context-wide cache configuration to
 * ::HU_FUNC_CACHE_PREFER_NONE will cause subsequent kernel launches to prefer
 * to not change the cache configuration unless required to launch the kernel.
 *
 * This setting does nothing on devices where the size of the L1 cache and
 * shared memory are fixed.
 *
 * Launching a kernel with a different preference than the most recent
 * preference setting may insert a device-side synchronization point.
 *
 * The supported cache configurations are:
 * - ::HU_FUNC_CACHE_PREFER_NONE: no preference for shared memory or L1 (default)
 * - ::HU_FUNC_CACHE_PREFER_SHARED: prefer larger shared memory and smaller L1 cache
 * - ::HU_FUNC_CACHE_PREFER_L1: prefer larger L1 cache and smaller shared memory
 * - ::HU_FUNC_CACHE_PREFER_EQUAL: prefer equal sized L1 cache and shared memory
 *
 * \param config - Requested cache configuration
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize,
 * ::huFuncSetCacheConfig,
 * ::hipDeviceSetCacheConfig
 */
HUresult HIPAPI huCtxSetCacheConfig(HUfunc_cache config);

/**
 * \brief Returns the current shared memory configuration for the current context.
 *
 * This function will return in \p pConfig the current size of shared memory banks
 * in the current context. On devices with configurable shared memory banks, 
 * ::huCtxSetSharedMemConfig can be used to change this setting, so that all 
 * subsequent kernel launches will by default use the new bank size. When 
 * ::huCtxGetSharedMemConfig is called on devices without configurable shared 
 * memory, it will return the fixed bank size of the hardware.
 *
 * The returned bank configurations can be either:
 * - ::HU_SHARED_MEM_CONFIG_FOUR_BYTE_BANK_SIZE:  shared memory bank width is 
 *   four bytes.
 * - ::HU_SHARED_MEM_CONFIG_EIGHT_BYTE_BANK_SIZE: shared memory bank width will
 *   eight bytes.
 *
 * \param pConfig - returned shared memory configuration
 * \return 
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize,
 * ::huCtxGetSharedMemConfig,
 * ::huFuncSetCacheConfig,
 * ::hipDeviceGetSharedMemConfig
 */
HUresult HIPAPI huCtxGetSharedMemConfig(HUsharedconfig *pConfig);

/**
 * \brief Sets the shared memory configuration for the current context.
 *
 * On devices with configurable shared memory banks, this function will set
 * the context's shared memory bank size which is used for subsequent kernel 
 * launches. 
 *
 * Changed the shared memory configuration between launches may insert a device
 * side synchronization point between those launches.
 *
 * Changing the shared memory bank size will not increase shared memory usage
 * or affect occupancy of kernels, but may have major effects on performance. 
 * Larger bank sizes will allow for greater potential bandwidth to shared memory,
 * but will change what kinds of accesses to shared memory will result in bank 
 * conflicts.
 *
 * This function will do nothing on devices with fixed shared memory bank size.
 *
 * The supported bank configurations are:
 * - ::HU_SHARED_MEM_CONFIG_DEFAULT_BANK_SIZE: set bank width to the default initial
 *   setting (currently, four bytes).
 * - ::HU_SHARED_MEM_CONFIG_FOUR_BYTE_BANK_SIZE: set shared memory bank width to
 *   be natively four bytes.
 * - ::HU_SHARED_MEM_CONFIG_EIGHT_BYTE_BANK_SIZE: set shared memory bank width to
 *   be natively eight bytes.
 *
 * \param config - requested shared memory configuration
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize,
 * ::huCtxGetSharedMemConfig,
 * ::huFuncSetCacheConfig,
 * ::hipDeviceSetSharedMemConfig
 */
HUresult HIPAPI huCtxSetSharedMemConfig(HUsharedconfig config);

/**
 * \brief Gets the context's API version.
 *
 * Returns a version number in \p version corresponding to the capabilities of
 * the context (e.g. 3010 or 3020), which library developers can use to direct
 * callers to a specific API version. If \p ctx is NULL, returns the API version
 * used to create the currently bound context.
 *
 * Note that new API versions are only introduced when context capabilities are
 * changed that break binary compatibility, so the API version and driver version
 * may be different. For example, it is valid for the API version to be 3020 while
 * the driver version is 4020.
 *
 * \param ctx     - Context to check
 * \param version - Pointer to version
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize
 */
HUresult HIPAPI huCtxGetApiVersion(HUcontext ctx, unsigned int *version);

/**
 * \brief Returns numerical values that correspond to the least and
 * greatest stream priorities.
 *
 * Returns in \p *leastPriority and \p *greatestPriority the numerical values that correspond
 * to the least and greatest stream priorities respectively. Stream priorities
 * follow a convention where lower numbers imply greater priorities. The range of
 * meaningful stream priorities is given by [\p *greatestPriority, \p *leastPriority].
 * If the user attempts to create a stream with a priority value that is
 * outside the meaningful range as specified by this API, the priority is
 * automatically clamped down or up to either \p *leastPriority or \p *greatestPriority
 * respectively. See ::huStreamCreateWithPriority for details on creating a
 * priority stream.
 * A NULL may be passed in for \p *leastPriority or \p *greatestPriority if the value
 * is not desired.
 *
 * This function will return '0' in both \p *leastPriority and \p *greatestPriority if
 * the current context's device does not support stream priorities
 * (see ::huDeviceGetAttribute).
 *
 * \param leastPriority    - Pointer to an int in which the numerical value for least
 *                           stream priority is returned
 * \param greatestPriority - Pointer to an int in which the numerical value for greatest
 *                           stream priority is returned
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * \notefnerr
 *
 * \sa ::huStreamCreateWithPriority,
 * ::huStreamGetPriority,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize,
 * ::hipDeviceGetStreamPriorityRange
 */
HUresult HIPAPI huCtxGetStreamPriorityRange(int *leastPriority, int *greatestPriority);

/** @} */ /* END HIP_CTX */

/**
 * \defgroup HIP_CTX_DEPRECATED Context Management [DEPRECATED]
 *
 * ___MANBRIEF___ deprecated context management functions of the low-level HIP
 * driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the deprecated context management functions of the low-level
 * HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Increment a context's usage-count
 *
 * \deprecated
 *
 * Note that this function is deprecated and should not be used.
 *
 * Increments the usage count of the context and passes back a context handle
 * in \p *pctx that must be passed to ::huCtxDetach() when the application is
 * done with the context. ::huCtxAttach() fails if there is no context current
 * to the thread.
 *
 * Currently, the \p flags parameter must be 0.
 *
 * \param pctx  - Returned context handle of the current context
 * \param flags - Context attach flags (must be 0)
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxDetach,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize
 */
__HIP_DEPRECATED HUresult HIPAPI huCtxAttach(HUcontext *pctx, unsigned int flags);

/**
 * \brief Decrement a context's usage-count
 *
 * \deprecated
 *
 * Note that this function is deprecated and should not be used.
 *
 * Decrements the usage count of the context \p ctx, and destroys the context
 * if the usage count goes to 0. The context must be a handle that was passed
 * back by ::huCtxCreate() or ::huCtxAttach(), and must be current to the
 * calling thread.
 *
 * \param ctx - Context to destroy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT
 * \notefnerr
 *
 * \sa ::huCtxCreate,
 * ::huCtxDestroy,
 * ::huCtxGetApiVersion,
 * ::huCtxGetCacheConfig,
 * ::huCtxGetDevice,
 * ::huCtxGetFlags,
 * ::huCtxGetLimit,
 * ::huCtxPopCurrent,
 * ::huCtxPushCurrent,
 * ::huCtxSetCacheConfig,
 * ::huCtxSetLimit,
 * ::huCtxSynchronize
 */
__HIP_DEPRECATED HUresult HIPAPI huCtxDetach(HUcontext ctx);

/** @} */ /* END HIP_CTX_DEPRECATED */


/**
 * \defgroup HIP_MODULE Module Management
 *
 * ___MANBRIEF___ module management functions of the low-level HIP driver API
 * (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the module management functions of the low-level HIP
 * driver application programming interface.
 *
 * @{
 */

/**
 * \brief Loads a compute module
 *
 * Takes a filename \p fname and loads the corresponding module \p module into
 * the current context. The HIP driver API does not attempt to lazily
 * allocate the resources needed by a module; if the memory for functions and
 * data (constant and global) needed by the module cannot be allocated,
 * ::huModuleLoad() fails. The file should be a \e hubin file as output by
 * \b nvcc, or a \e PTX file either as output by \b nvcc or handwritten, or
 * a \e fatbin file as output by \b nvcc from toolchain 4.0 or later.
 *
 * \param module - Returned module
 * \param fname  - Filename of module to load
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_PTX,
 * ::HIP_ERROR_NOT_FOUND,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_FILE_NOT_FOUND,
 * ::HIP_ERROR_NO_BINARY_FOR_GPU,
 * ::HIP_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED,
 * ::HIP_ERROR_JIT_COMPILER_NOT_FOUND
 * \notefnerr
 *
 * \sa ::huModuleGetFunction,
 * ::huModuleGetGlobal,
 * ::huModuleGetTexRef,
 * ::huModuleLoadData,
 * ::huModuleLoadDataEx,
 * ::huModuleLoadFatBinary,
 * ::huModuleUnload
 */
HUresult HIPAPI huModuleLoad(HUmodule *module, const char *fname);

/**
 * \brief Load a module's data
 *
 * Takes a pointer \p image and loads the corresponding module \p module into
 * the current context. The pointer may be obtained by mapping a \e hubin or
 * \e PTX or \e fatbin file, passing a \e hubin or \e PTX or \e fatbin file
 * as a NULL-terminated text string, or incorporating a \e hubin or \e fatbin
 * object into the executable resources and using operating system calls such
 * as Windows \c FindResource() to obtain the pointer.
 *
 * \param module - Returned module
 * \param image  - Module data to load
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_PTX,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_NO_BINARY_FOR_GPU,
 * ::HIP_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED,
 * ::HIP_ERROR_JIT_COMPILER_NOT_FOUND
 * \notefnerr
 *
 * \sa ::huModuleGetFunction,
 * ::huModuleGetGlobal,
 * ::huModuleGetTexRef,
 * ::huModuleLoad,
 * ::huModuleLoadDataEx,
 * ::huModuleLoadFatBinary,
 * ::huModuleUnload
 */
HUresult HIPAPI huModuleLoadData(HUmodule *module, const void *image);

/**
 * \brief Load a module's data with options
 *
 * Takes a pointer \p image and loads the corresponding module \p module into
 * the current context. The pointer may be obtained by mapping a \e hubin or
 * \e PTX or \e fatbin file, passing a \e hubin or \e PTX or \e fatbin file
 * as a NULL-terminated text string, or incorporating a \e hubin or \e fatbin
 * object into the executable resources and using operating system calls such
 * as Windows \c FindResource() to obtain the pointer. Options are passed as
 * an array via \p options and any corresponding parameters are passed in
 * \p optionValues. The number of total options is supplied via \p numOptions.
 * Any outputs will be returned via \p optionValues. 
 *
 * \param module       - Returned module
 * \param image        - Module data to load
 * \param numOptions   - Number of options
 * \param options      - Options for JIT
 * \param optionValues - Option values for JIT
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_PTX,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_NO_BINARY_FOR_GPU,
 * ::HIP_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED,
 * ::HIP_ERROR_JIT_COMPILER_NOT_FOUND
 * \notefnerr
 *
 * \sa ::huModuleGetFunction,
 * ::huModuleGetGlobal,
 * ::huModuleGetTexRef,
 * ::huModuleLoad,
 * ::huModuleLoadData,
 * ::huModuleLoadFatBinary,
 * ::huModuleUnload
 */
HUresult HIPAPI huModuleLoadDataEx(HUmodule *module, const void *image, unsigned int numOptions, HUjit_option *options, void **optionValues);

/**
 * \brief Load a module's data
 *
 * Takes a pointer \p fatCubin and loads the corresponding module \p module
 * into the current context. The pointer represents a <i>fat binary</i> object,
 * which is a collection of different \e hubin and/or \e PTX files, all
 * representing the same device code, but compiled and optimized for different
 * architectures.
 *
 * Prior to HIP 4.0, there was no documented API for constructing and using
 * fat binary objects by programmers.  Starting with HIP 4.0, fat binary
 * objects can be constructed by providing the <i>-fatbin option</i> to \b nvcc.
 * More information can be found in the \b nvcc document.
 *
 * \param module   - Returned module
 * \param fatCubin - Fat binary to load
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_PTX,
 * ::HIP_ERROR_NOT_FOUND,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_NO_BINARY_FOR_GPU,
 * ::HIP_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED,
 * ::HIP_ERROR_JIT_COMPILER_NOT_FOUND
 * \notefnerr
 *
 * \sa ::huModuleGetFunction,
 * ::huModuleGetGlobal,
 * ::huModuleGetTexRef,
 * ::huModuleLoad,
 * ::huModuleLoadData,
 * ::huModuleLoadDataEx,
 * ::huModuleUnload
 */
HUresult HIPAPI huModuleLoadFatBinary(HUmodule *module, const void *fatCubin);

/**
 * \brief Unloads a module
 *
 * Unloads a module \p hmod from the current context.
 *
 * \param hmod - Module to unload
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huModuleGetFunction,
 * ::huModuleGetGlobal,
 * ::huModuleGetTexRef,
 * ::huModuleLoad,
 * ::huModuleLoadData,
 * ::huModuleLoadDataEx,
 * ::huModuleLoadFatBinary
 */
HUresult HIPAPI huModuleUnload(HUmodule hmod);

/**
 * \brief Returns a function handle
 *
 * Returns in \p *hfunc the handle of the function of name \p name located in
 * module \p hmod. If no function of that name exists, ::huModuleGetFunction()
 * returns ::HIP_ERROR_NOT_FOUND.
 *
 * \param hfunc - Returned function handle
 * \param hmod  - Module to retrieve function from
 * \param name  - Name of function to retrieve
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_FOUND
 * \notefnerr
 *
 * \sa ::huModuleGetGlobal,
 * ::huModuleGetTexRef,
 * ::huModuleLoad,
 * ::huModuleLoadData,
 * ::huModuleLoadDataEx,
 * ::huModuleLoadFatBinary,
 * ::huModuleUnload
 */
HUresult HIPAPI huModuleGetFunction(HUfunction *hfunc, HUmodule hmod, const char *name);

/**
 * \brief Returns a global pointer from a module
 *
 * Returns in \p *dptr and \p *bytes the base pointer and size of the
 * global of name \p name located in module \p hmod. If no variable of that name
 * exists, ::huModuleGetGlobal() returns ::HIP_ERROR_NOT_FOUND. Both
 * parameters \p dptr and \p bytes are optional. If one of them is
 * NULL, it is ignored.
 *
 * \param dptr  - Returned global device pointer
 * \param bytes - Returned global size in bytes
 * \param hmod  - Module to retrieve global from
 * \param name  - Name of global to retrieve
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_FOUND
 * \notefnerr
 *
 * \sa ::huModuleGetFunction,
 * ::huModuleGetTexRef,
 * ::huModuleLoad,
 * ::huModuleLoadData,
 * ::huModuleLoadDataEx,
 * ::huModuleLoadFatBinary,
 * ::huModuleUnload,
 * ::hipGetSymbolAddress,
 * ::hipGetSymbolSize
 */
HUresult HIPAPI huModuleGetGlobal(HUdeviceptr *dptr, size_t *bytes, HUmodule hmod, const char *name);

/**
 * \brief Returns a handle to a texture reference
 *
 * Returns in \p *pTexRef the handle of the texture reference of name \p name
 * in the module \p hmod. If no texture reference of that name exists,
 * ::huModuleGetTexRef() returns ::HIP_ERROR_NOT_FOUND. This texture reference
 * handle should not be destroyed, since it will be destroyed when the module
 * is unloaded.
 *
 * \param pTexRef  - Returned texture reference
 * \param hmod     - Module to retrieve texture reference from
 * \param name     - Name of texture reference to retrieve
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_FOUND
 * \notefnerr
 *
 * \sa ::huModuleGetFunction,
 * ::huModuleGetGlobal,
 * ::huModuleGetSurfRef,
 * ::huModuleLoad,
 * ::huModuleLoadData,
 * ::huModuleLoadDataEx,
 * ::huModuleLoadFatBinary,
 * ::huModuleUnload,
 * ::hipGetTextureReference
 */
HUresult HIPAPI huModuleGetTexRef(HUtexref *pTexRef, HUmodule hmod, const char *name);

/**
 * \brief Returns a handle to a surface reference
 *
 * Returns in \p *pSurfRef the handle of the surface reference of name \p name
 * in the module \p hmod. If no surface reference of that name exists,
 * ::huModuleGetSurfRef() returns ::HIP_ERROR_NOT_FOUND.
 *
 * \param pSurfRef  - Returned surface reference
 * \param hmod     - Module to retrieve surface reference from
 * \param name     - Name of surface reference to retrieve
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_FOUND
 * \notefnerr
 *
 * \sa ::huModuleGetFunction,
 * ::huModuleGetGlobal,
 * ::huModuleGetTexRef,
 * ::huModuleLoad,
 * ::huModuleLoadData,
 * ::huModuleLoadDataEx,
 * ::huModuleLoadFatBinary,
 * ::huModuleUnload,
 * ::hipGetSurfaceReference
 */
HUresult HIPAPI huModuleGetSurfRef(HUsurfref *pSurfRef, HUmodule hmod, const char *name);

/**
 * \brief Creates a pending JIT linker invocation.
 *
 * If the call is successful, the caller owns the returned HUlinkState, which
 * should eventually be destroyed with ::huLinkDestroy.  The
 * device code machine size (32 or 64 bit) will match the calling application.
 *
 * Both linker and compiler options may be specified.  Compiler options will
 * be applied to inputs to this linker action which must be compiled from PTX.
 * The options ::HU_JIT_WALL_TIME,
 * ::HU_JIT_INFO_LOG_BUFFER_SIZE_BYTES, and ::HU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES
 * will accumulate data until the HUlinkState is destroyed.
 *
 * \p optionValues must remain valid for the life of the HUlinkState if output
 * options are used.  No other references to inputs are maintained after this
 * call returns.
 *
 * \param numOptions   Size of options arrays
 * \param options      Array of linker and compiler options
 * \param optionValues Array of option values, each cast to void *
 * \param stateOut     On success, this will contain a HUlinkState to specify
 *                     and complete this action
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_JIT_COMPILER_NOT_FOUND
 * \notefnerr
 *
 * \sa ::huLinkAddData,
 * ::huLinkAddFile,
 * ::huLinkComplete,
 * ::huLinkDestroy
 */
HUresult HIPAPI huLinkCreate(unsigned int numOptions, HUjit_option *options, void **optionValues, HUlinkState *stateOut);

/**
 * \brief Add an input to a pending linker invocation
 *
 * Ownership of \p data is retained by the caller.  No reference is retained to any
 * inputs after this call returns.
 *
 * This method accepts only compiler options, which are used if the data must
 * be compiled from PTX, and does not accept any of
 * ::HU_JIT_WALL_TIME, ::HU_JIT_INFO_LOG_BUFFER, ::HU_JIT_ERROR_LOG_BUFFER,
 * ::HU_JIT_TARGET_FROM_HUCONTEXT, or ::HU_JIT_TARGET.
 *
 * \param state        A pending linker action.
 * \param type         The type of the input data.
 * \param data         The input data.  PTX must be NULL-terminated.
 * \param size         The length of the input data.
 * \param name         An optional name for this input in log messages.
 * \param numOptions   Size of options.
 * \param options      Options to be applied only for this input (overrides options from ::huLinkCreate).
 * \param optionValues Array of option values, each cast to void *.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_IMAGE,
 * ::HIP_ERROR_INVALID_PTX,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_NO_BINARY_FOR_GPU
 *
 * \sa ::huLinkCreate,
 * ::huLinkAddFile,
 * ::huLinkComplete,
 * ::huLinkDestroy
 */
HUresult HIPAPI huLinkAddData(HUlinkState state, HUjitInputType type, void *data, size_t size, const char *name, unsigned int numOptions, HUjit_option *options, void **optionValues);

/**
 * \brief Add a file input to a pending linker invocation
 *
 * No reference is retained to any inputs after this call returns.
 *
 * This method accepts only compiler options, which are used if the input
 * must be compiled from PTX, and does not accept any of
 * ::HU_JIT_WALL_TIME, ::HU_JIT_INFO_LOG_BUFFER, ::HU_JIT_ERROR_LOG_BUFFER,
 * ::HU_JIT_TARGET_FROM_HUCONTEXT, or ::HU_JIT_TARGET.
 *
 * This method is equivalent to invoking ::huLinkAddData on the contents
 * of the file.
 *
 * \param state        A pending linker action
 * \param type         The type of the input data
 * \param path         Path to the input file
 * \param numOptions   Size of options
 * \param options      Options to be applied only for this input (overrides options from ::huLinkCreate)
 * \param optionValues Array of option values, each cast to void *
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_FILE_NOT_FOUND
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_IMAGE,
 * ::HIP_ERROR_INVALID_PTX,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_NO_BINARY_FOR_GPU
 *
 * \sa ::huLinkCreate,
 * ::huLinkAddData,
 * ::huLinkComplete,
 * ::huLinkDestroy
 */
HUresult HIPAPI huLinkAddFile(HUlinkState state, HUjitInputType type, const char *path, unsigned int numOptions, HUjit_option *options, void **optionValues);

/**
 * \brief Complete a pending linker invocation
 *
 * Completes the pending linker action and returns the hubin image for the linked
 * device code, which can be used with ::huModuleLoadData.  The hubin is owned by
 * \p state, so it should be loaded before \p state is destroyed via ::huLinkDestroy.
 * This call does not destroy \p state.
 *
 * \param state    A pending linker invocation
 * \param hubinOut On success, this will point to the output image
 * \param sizeOut  Optional parameter to receive the size of the generated image
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 *
 * \sa ::huLinkCreate,
 * ::huLinkAddData,
 * ::huLinkAddFile,
 * ::huLinkDestroy,
 * ::huModuleLoadData
 */
HUresult HIPAPI huLinkComplete(HUlinkState state, void **cubinOut, size_t *sizeOut);

/**
 * \brief Destroys state for a JIT linker invocation.
 *
 * \param state State object for the linker invocation
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_HANDLE
 *
 * \sa ::huLinkCreate
 */
HUresult HIPAPI huLinkDestroy(HUlinkState state);

/** @} */ /* END HIP_MODULE */


/**
 * \defgroup HIP_MEM Memory Management
 *
 * ___MANBRIEF___ memory management functions of the low-level HIP driver API
 * (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the memory management functions of the low-level HIP
 * driver application programming interface.
 *
 * @{
 */

/**
 * \brief Gets free and total memory
 *
 * Returns in \p *free and \p *total respectively, the free and total amount of
 * memory available for allocation by the HIP context, in bytes.
 *
 * \param free  - Returned free memory in bytes
 * \param total - Returned total memory in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemGetInfo
 */
HUresult HIPAPI huMemGetInfo(size_t *free, size_t *total);

/**
 * \brief Allocates device memory
 *
 * Allocates \p bytesize bytes of linear memory on the device and returns in
 * \p *dptr a pointer to the allocated memory. The allocated memory is suitably
 * aligned for any kind of variable. The memory is not cleared. If \p bytesize
 * is 0, ::huMemAlloc() returns ::HIP_ERROR_INVALID_VALUE.
 *
 * \param dptr     - Returned device pointer
 * \param bytesize - Requested allocation size in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMalloc
 */
HUresult HIPAPI huMemAlloc(HUdeviceptr *dptr, size_t bytesize);

/**
 * \brief Allocates pitched device memory
 *
 * Allocates at least \p WidthInBytes * \p Height bytes of linear memory on
 * the device and returns in \p *dptr a pointer to the allocated memory. The
 * function may pad the allocation to ensure that corresponding pointers in
 * any given row will continue to meet the alignment requirements for
 * coalescing as the address is updated from row to row. \p ElementSizeBytes
 * specifies the size of the largest reads and writes that will be performed
 * on the memory range. \p ElementSizeBytes may be 4, 8 or 16 (since coalesced
 * memory transactions are not possible on other data sizes). If
 * \p ElementSizeBytes is smaller than the actual read/write size of a kernel,
 * the kernel will run correctly, but possibly at reduced speed. The pitch
 * returned in \p *pPitch by ::huMemAllocPitch() is the width in bytes of the
 * allocation. The intended usage of pitch is as a separate parameter of the
 * allocation, used to compute addresses within the 2D array. Given the row
 * and column of an array element of type \b T, the address is computed as:
 * \code
   T* pElement = (T*)((char*)BaseAddress + Row * Pitch) + Column;
 * \endcode
 *
 * The pitch returned by ::huMemAllocPitch() is guaranteed to work with
 * ::huMemcpy2D() under all circumstances. For allocations of 2D arrays, it is
 * recommended that programmers consider performing pitch allocations using
 * ::huMemAllocPitch(). Due to alignment restrictions in the hardware, this is
 * especially true if the application will be performing 2D memory copies
 * between different regions of device memory (whether linear memory or HIP
 * arrays).
 *
 * The byte alignment of the pitch returned by ::huMemAllocPitch() is guaranteed
 * to match or exceed the alignment requirement for texture binding with
 * ::huTexRefSetAddress2D().
 *
 * \param dptr             - Returned device pointer
 * \param pPitch           - Returned pitch of allocation in bytes
 * \param WidthInBytes     - Requested allocation width in bytes
 * \param Height           - Requested allocation height in rows
 * \param ElementSizeBytes - Size of largest reads/writes for range
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMallocPitch
 */
HUresult HIPAPI huMemAllocPitch(HUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes);

/**
 * \brief Frees device memory
 *
 * Frees the memory space pointed to by \p dptr, which must have been returned
 * by a previous call to ::huMemAlloc() or ::huMemAllocPitch().
 *
 * \param dptr - Pointer to memory to free
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipFree
 */
HUresult HIPAPI huMemFree(HUdeviceptr dptr);

/**
 * \brief Get information on memory allocations
 *
 * Returns the base address in \p *pbase and size in \p *psize of the
 * allocation by ::huMemAlloc() or ::huMemAllocPitch() that contains the input
 * pointer \p dptr. Both parameters \p pbase and \p psize are optional. If one
 * of them is NULL, it is ignored.
 *
 * \param pbase - Returned base address
 * \param psize - Returned size of device memory allocation
 * \param dptr  - Device pointer to query
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_NOT_FOUND,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32
 */
HUresult HIPAPI huMemGetAddressRange(HUdeviceptr *pbase, size_t *psize, HUdeviceptr dptr);

/**
 * \brief Allocates page-locked host memory
 *
 * Allocates \p bytesize bytes of host memory that is page-locked and
 * accessible to the device. The driver tracks the virtual memory ranges
 * allocated with this function and automatically accelerates calls to
 * functions such as ::huMemcpy(). Since the memory can be accessed directly by
 * the device, it can be read or written with much higher bandwidth than
 * pageable memory obtained with functions such as ::malloc(). Allocating
 * excessive amounts of memory with ::huMemAllocHost() may degrade system
 * performance, since it reduces the amount of memory available to the system
 * for paging. As a result, this function is best used sparingly to allocate
 * staging areas for data exchange between host and device.
 *
 * Note all host memory allocated using ::huMemHostAlloc() will automatically
 * be immediately accessible to all contexts on all devices which support unified
 * addressing (as may be queried using ::HU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING).
 * The device pointer that may be used to access this host memory from those 
 * contexts is always equal to the returned host pointer \p *pp.
 * See \ref HIP_UNIFIED for additional details.
 *
 * \param pp       - Returned host pointer to page-locked memory
 * \param bytesize - Requested allocation size in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMallocHost
 */
HUresult HIPAPI huMemAllocHost(void **pp, size_t bytesize);

/**
 * \brief Frees page-locked host memory
 *
 * Frees the memory space pointed to by \p p, which must have been returned by
 * a previous call to ::huMemAllocHost().
 *
 * \param p - Pointer to memory to free
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipFreeHost
 */
HUresult HIPAPI huMemFreeHost(void *p);

/**
 * \brief Allocates page-locked host memory
 *
 * Allocates \p bytesize bytes of host memory that is page-locked and accessible
 * to the device. The driver tracks the virtual memory ranges allocated with
 * this function and automatically accelerates calls to functions such as
 * ::huMemcpyHtoD(). Since the memory can be accessed directly by the device,
 * it can be read or written with much higher bandwidth than pageable memory
 * obtained with functions such as ::malloc(). Allocating excessive amounts of
 * pinned memory may degrade system performance, since it reduces the amount
 * of memory available to the system for paging. As a result, this function is
 * best used sparingly to allocate staging areas for data exchange between
 * host and device.
 *
 * The \p Flags parameter enables different options to be specified that
 * affect the allocation, as follows.
 *
 * - ::HU_MEMHOSTALLOC_PORTABLE: The memory returned by this call will be
 *   considered as pinned memory by all HIP contexts, not just the one that
 *   performed the allocation.
 *
 * - ::HU_MEMHOSTALLOC_DEVICEMAP: Maps the allocation into the HIP address
 *   space. The device pointer to the memory may be obtained by calling
 *   ::huMemHostGetDevicePointer().
 *
 * - ::HU_MEMHOSTALLOC_WRITECOMBINED: Allocates the memory as write-combined
 *   (WC). WC memory can be transferred across the PCI Express bus more
 *   quickly on some system configurations, but cannot be read efficiently by
 *   most CPUs. WC memory is a good option for buffers that will be written by
 *   the CPU and read by the GPU via mapped pinned memory or host->device
 *   transfers.
 *
 * All of these flags are orthogonal to one another: a developer may allocate
 * memory that is portable, mapped and/or write-combined with no restrictions.
 *
 * The HIP context must have been created with the ::HU_CTX_MAP_HOST flag in
 * order for the ::HU_MEMHOSTALLOC_DEVICEMAP flag to have any effect.
 *
 * The ::HU_MEMHOSTALLOC_DEVICEMAP flag may be specified on HIP contexts for
 * devices that do not support mapped pinned memory. The failure is deferred
 * to ::huMemHostGetDevicePointer() because the memory may be mapped into
 * other HIP contexts via the ::HU_MEMHOSTALLOC_PORTABLE flag.
 *
 * The memory allocated by this function must be freed with ::huMemFreeHost().
 *
 * Note all host memory allocated using ::huMemHostAlloc() will automatically
 * be immediately accessible to all contexts on all devices which support unified
 * addressing (as may be queried using ::HU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING).
 * Unless the flag ::HU_MEMHOSTALLOC_WRITECOMBINED is specified, the device pointer 
 * that may be used to access this host memory from those contexts is always equal 
 * to the returned host pointer \p *pp.  If the flag ::HU_MEMHOSTALLOC_WRITECOMBINED
 * is specified, then the function ::huMemHostGetDevicePointer() must be used
 * to query the device pointer, even if the context supports unified addressing.
 * See \ref HIP_UNIFIED for additional details.
 *
 * \param pp       - Returned host pointer to page-locked memory
 * \param bytesize - Requested allocation size in bytes
 * \param Flags    - Flags for allocation request
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipHostAlloc
 */
HUresult HIPAPI huMemHostAlloc(void **pp, size_t bytesize, unsigned int Flags);

/**
 * \brief Passes back device pointer of mapped pinned memory
 *
 * Passes back the device pointer \p pdptr corresponding to the mapped, pinned
 * host buffer \p p allocated by ::huMemHostAlloc.
 *
 * ::huMemHostGetDevicePointer() will fail if the ::HU_MEMHOSTALLOC_DEVICEMAP
 * flag was not specified at the time the memory was allocated, or if the
 * function is called on a GPU that does not support mapped pinned memory.
 *
 * For devices that have a non-zero value for the device attribute
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_HOST_POINTER_FOR_REGISTERED_MEM, the memory
 * can also be accessed from the device using the host pointer \p p.
 * The device pointer returned by ::huMemHostGetDevicePointer() may or may not
 * match the original host pointer \p p and depends on the devices visible to the
 * application. If all devices visible to the application have a non-zero value for the
 * device attribute, the device pointer returned by ::huMemHostGetDevicePointer()
 * will match the original pointer \p p. If any device visible to the application
 * has a zero value for the device attribute, the device pointer returned by
 * ::huMemHostGetDevicePointer() will not match the original host pointer \p p,
 * but it will be suitable for use on all devices provided Unified Virtual Addressing
 * is enabled. In such systems, it is valid to access the memory using either pointer
 * on devices that have a non-zero value for the device attribute. Note however that
 * such devices should access the memory using only of the two pointers and not both.
 *
 * \p Flags provides for future releases. For now, it must be set to 0.
 *
 * \param pdptr - Returned device pointer
 * \param p     - Host pointer
 * \param Flags - Options (must be 0)
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipHostGetDevicePointer
 */
HUresult HIPAPI huMemHostGetDevicePointer(HUdeviceptr *pdptr, void *p, unsigned int Flags);

/**
 * \brief Passes back flags that were used for a pinned allocation
 *
 * Passes back the flags \p pFlags that were specified when allocating
 * the pinned host buffer \p p allocated by ::huMemHostAlloc.
 *
 * ::huMemHostGetFlags() will fail if the pointer does not reside in
 * an allocation performed by ::huMemAllocHost() or ::huMemHostAlloc().
 *
 * \param pFlags - Returned flags word
 * \param p     - Host pointer
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa
 * ::huMemAllocHost,
 * ::huMemHostAlloc,
 * ::hipHostGetFlags
 */
HUresult HIPAPI huMemHostGetFlags(unsigned int *pFlags, void *p);

/**
 * \brief Allocates memory that will be automatically managed by the Unified Memory system
 *
 * Allocates \p bytesize bytes of managed memory on the device and returns in
 * \p *dptr a pointer to the allocated memory. If the device doesn't support
 * allocating managed memory, ::HIP_ERROR_NOT_SUPPORTED is returned. Support
 * for managed memory can be queried using the device attribute
 * ::HU_DEVICE_ATTRIBUTE_MANAGED_MEMORY. The allocated memory is suitably
 * aligned for any kind of variable. The memory is not cleared. If \p bytesize
 * is 0, ::huMemAllocManaged returns ::HIP_ERROR_INVALID_VALUE. The pointer
 * is valid on the CPU and on all GPUs in the system that support managed memory.
 * All accesses to this pointer must obey the Unified Memory programming model.
 *
 * \p flags specifies the default stream association for this allocation.
 * \p flags must be one of ::HU_MEM_ATTACH_GLOBAL or ::HU_MEM_ATTACH_HOST. If
 * ::HU_MEM_ATTACH_GLOBAL is specified, then this memory is accessible from
 * any stream on any device. If ::HU_MEM_ATTACH_HOST is specified, then the
 * allocation should not be accessed from devices that have a zero value for the
 * device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS; an explicit call to
 * ::huStreamAttachMemAsync will be required to enable access on such devices.
 *
 * If the association is later changed via ::huStreamAttachMemAsync to
 * a single stream, the default association as specifed during ::huMemAllocManaged
 * is restored when that stream is destroyed. For __managed__ variables, the
 * default association is always ::HU_MEM_ATTACH_GLOBAL. Note that destroying a
 * stream is an asynchronous operation, and as a result, the change to default
 * association won't happen until all work in the stream has completed.
 *
 * Memory allocated with ::huMemAllocManaged should be released with ::huMemFree.
 *
 * Device memory oversubscription is possible for GPUs that have a non-zero value for the
 * device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS. Managed memory on
 * such GPUs may be evicted from device memory to host memory at any time by the Unified
 * Memory driver in order to make room for other allocations.
 *
 * In a multi-GPU system where all GPUs have a non-zero value for the device attribute
 * ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS, managed memory may not be populated when this
 * API returns and instead may be populated on access. In such systems, managed memory can
 * migrate to any processor's memory at any time. The Unified Memory driver will employ heuristics to
 * maintain data locality and prevent excessive page faults to the extent possible. The application
 * can also guide the driver about memory usage patterns via ::huMemAdvise. The application
 * can also explicitly migrate memory to a desired processor's memory via
 * ::huMemPrefetchAsync.
 *
 * In a multi-GPU system where all of the GPUs have a zero value for the device attribute
 * ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS and all the GPUs have peer-to-peer support
 * with each other, the physical storage for managed memory is created on the GPU which is active
 * at the time ::huMemAllocManaged is called. All other GPUs will reference the data at reduced
 * bandwidth via peer mappings over the PCIe bus. The Unified Memory driver does not migrate
 * memory among such GPUs.
 *
 * In a multi-GPU system where not all GPUs have peer-to-peer support with each other and
 * where the value of the device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS
 * is zero for at least one of those GPUs, the location chosen for physical storage of managed
 * memory is system-dependent.
 * - On Linux, the location chosen will be device memory as long as the current set of active
 * contexts are on devices that either have peer-to-peer support with each other or have a
 * non-zero value for the device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS.
 * If there is an active context on a GPU that does not have a non-zero value for that device
 * attribute and it does not have peer-to-peer support with the other devices that have active
 * contexts on them, then the location for physical storage will be 'zero-copy' or host memory.
 * Note that this means that managed memory that is located in device memory is migrated to
 * host memory if a new context is created on a GPU that doesn't have a non-zero value for
 * the device attribute and does not support peer-to-peer with at least one of the other devices
 * that has an active context. This in turn implies that context creation may fail if there is
 * insufficient host memory to migrate all managed allocations.
 * - On Windows, the physical storage is always created in 'zero-copy' or host memory.
 * All GPUs will reference the data at reduced bandwidth over the PCIe bus. In these
 * circumstances, use of the environment variable HIP_VISIBLE_DEVICES is recommended to
 * restrict HIP to only use those GPUs that have peer-to-peer support.
 * Alternatively, users can also set HIP_MANAGED_FORCE_DEVICE_ALLOC to a
 * non-zero value to force the driver to always use device memory for physical storage.
 * When this environment variable is set to a non-zero value, all contexts created in
 * that process on devices that support managed memory have to be peer-to-peer compatible
 * with each other. Context creation will fail if a context is created on a device that
 * supports managed memory and is not peer-to-peer compatible with any of the other
 * managed memory supporting devices on which contexts were previously created, even if
 * those contexts have been destroyed. These environment variables are described
 * in the HIP programming guide under the "HIP environment variables" section.
 * - On ARM, managed memory is not available on discrete gpu with Drive PX-2.
 *
 * \param dptr     - Returned device pointer
 * \param bytesize - Requested allocation size in bytes
 * \param flags    - Must be one of ::HU_MEM_ATTACH_GLOBAL or ::HU_MEM_ATTACH_HOST
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_NOT_SUPPORTED,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::huDeviceGetAttribute, ::huStreamAttachMemAsync,
 * ::hipMallocManaged
 */
HUresult HIPAPI huMemAllocManaged(HUdeviceptr *dptr, size_t bytesize, unsigned int flags);

/**
 * \brief Returns a handle to a compute device
 *
 * Returns in \p *device a device handle given a PCI bus ID string.
 *
 * \param dev      - Returned device handle
 *
 * \param pciBusId - String in one of the following forms: 
 * [domain]:[bus]:[device].[function]
 * [domain]:[bus]:[device]
 * [bus]:[device].[function]
 * where \p domain, \p bus, \p device, and \p function are all hexadecimal values
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGet,
 * ::huDeviceGetAttribute,
 * ::huDeviceGetPCIBusId,
 * ::hipDeviceGetByPCIBusId
 */
HUresult HIPAPI huDeviceGetByPCIBusId(HUdevice *dev, const char *pciBusId);

/**
 * \brief Returns a PCI Bus Id string for the device
 *
 * Returns an ASCII string identifying the device \p dev in the NULL-terminated
 * string pointed to by \p pciBusId. \p len specifies the maximum length of the
 * string that may be returned.
 *
 * \param pciBusId - Returned identifier string for the device in the following format
 * [domain]:[bus]:[device].[function]
 * where \p domain, \p bus, \p device, and \p function are all hexadecimal values.
 * pciBusId should be large enough to store 13 characters including the NULL-terminator.
 *
 * \param len      - Maximum length of string to store in \p name
 *
 * \param dev      - Device to get identifier string for
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huDeviceGet,
 * ::huDeviceGetAttribute,
 * ::huDeviceGetByPCIBusId,
 * ::hipDeviceGetPCIBusId
 */
HUresult HIPAPI huDeviceGetPCIBusId(char *pciBusId, int len, HUdevice dev);

/**
 * \brief Gets an interprocess handle for a previously allocated event
 *
 * Takes as input a previously allocated event. This event must have been 
 * created with the ::HU_EVENT_INTERPROCESS and ::HU_EVENT_DISABLE_TIMING 
 * flags set. This opaque handle may be copied into other processes and
 * opened with ::huIpcOpenEventHandle to allow efficient hardware
 * synchronization between GPU work in different processes.
 *
 * After the event has been opened in the importing process, 
 * ::huEventRecord, ::huEventSynchronize, ::huStreamWaitEvent and 
 * ::huEventQuery may be used in either process. Performing operations 
 * on the imported event after the exported event has been freed 
 * with ::huEventDestroy will result in undefined behavior.
 *
 * IPC functionality is restricted to devices with support for unified
 * addressing on Linux and Windows operating systems.
 * IPC functionality on Windows is restricted to GPUs in TCC mode
 *
 * \param pHandle - Pointer to a user allocated HUipcEventHandle
 *                    in which to return the opaque event handle
 * \param event   - Event allocated with ::HU_EVENT_INTERPROCESS and 
 *                    ::HU_EVENT_DISABLE_TIMING flags.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_MAP_FAILED
 *
 * \sa 
 * ::huEventCreate, 
 * ::huEventDestroy, 
 * ::huEventSynchronize,
 * ::huEventQuery,
 * ::huStreamWaitEvent,
 * ::huIpcOpenEventHandle,
 * ::huIpcGetMemHandle,
 * ::huIpcOpenMemHandle,
 * ::huIpcCloseMemHandle,
 * ::hipIpcGetEventHandle
 */
HUresult HIPAPI huIpcGetEventHandle(HUipcEventHandle *pHandle, HUevent event);

/**
 * \brief Opens an interprocess event handle for use in the current process
 *
 * Opens an interprocess event handle exported from another process with 
 * ::huIpcGetEventHandle. This function returns a ::HUevent that behaves like 
 * a locally created event with the ::HU_EVENT_DISABLE_TIMING flag specified. 
 * This event must be freed with ::huEventDestroy.
 *
 * Performing operations on the imported event after the exported event has 
 * been freed with ::huEventDestroy will result in undefined behavior.
 *
 * IPC functionality is restricted to devices with support for unified
 * addressing on Linux and Windows operating systems.
 * IPC functionality on Windows is restricted to GPUs in TCC mode
 *
 * \param phEvent - Returns the imported event
 * \param handle  - Interprocess handle to open
 *
 * \returns
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_MAP_FAILED,
 * ::HIP_ERROR_PEER_ACCESS_UNSUPPORTED,
 * ::HIP_ERROR_INVALID_HANDLE
 *
 * \sa
 * ::huEventCreate, 
 * ::huEventDestroy, 
 * ::huEventSynchronize,
 * ::huEventQuery,
 * ::huStreamWaitEvent,
 * ::huIpcGetEventHandle,
 * ::huIpcGetMemHandle,
 * ::huIpcOpenMemHandle,
 * ::huIpcCloseMemHandle,
 * ::hipIpcOpenEventHandle
 */
HUresult HIPAPI huIpcOpenEventHandle(HUevent *phEvent, HUipcEventHandle handle);

/**
 * \brief Gets an interprocess memory handle for an existing device memory
 * allocation
 *
 * Takes a pointer to the base of an existing device memory allocation created 
 * with ::huMemAlloc and exports it for use in another process. This is a 
 * lightweight operation and may be called multiple times on an allocation
 * without adverse effects. 
 *
 * If a region of memory is freed with ::huMemFree and a subsequent call
 * to ::huMemAlloc returns memory with the same device address,
 * ::huIpcGetMemHandle will return a unique handle for the
 * new memory. 
 *
 * IPC functionality is restricted to devices with support for unified
 * addressing on Linux and Windows operating systems.
 * IPC functionality on Windows is restricted to GPUs in TCC mode
 *
 * \param pHandle - Pointer to user allocated ::HUipcMemHandle to return
 *                    the handle in.
 * \param dptr    - Base pointer to previously allocated device memory 
 *
 * \returns
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_MAP_FAILED,
 * 
 * \sa
 * ::huMemAlloc,
 * ::huMemFree,
 * ::huIpcGetEventHandle,
 * ::huIpcOpenEventHandle,
 * ::huIpcOpenMemHandle,
 * ::huIpcCloseMemHandle,
 * ::hipIpcGetMemHandle
 */
HUresult HIPAPI huIpcGetMemHandle(HUipcMemHandle *pHandle, HUdeviceptr dptr);

/**
 * \brief Opens an interprocess memory handle exported from another process
 * and returns a device pointer usable in the local process.
 *
 * Maps memory exported from another process with ::huIpcGetMemHandle into
 * the current device address space. For contexts on different devices 
 * ::huIpcOpenMemHandle can attempt to enable peer access between the
 * devices as if the user called ::huCtxEnablePeerAccess. This behavior is 
 * controlled by the ::HU_IPC_MEM_LAZY_ENABLE_PEER_ACCESS flag. 
 * ::huDeviceCanAccessPeer can determine if a mapping is possible.
 *
 * Contexts that may open ::HUipcMemHandles are restricted in the following way.
 * ::HUipcMemHandles from each ::HUdevice in a given process may only be opened 
 * by one ::HUcontext per ::HUdevice per other process.
 *
 * Memory returned from ::huIpcOpenMemHandle must be freed with
 * ::huIpcCloseMemHandle.
 *
 * Calling ::huMemFree on an exported memory region before calling
 * ::huIpcCloseMemHandle in the importing context will result in undefined
 * behavior.
 *
 * IPC functionality is restricted to devices with support for unified
 * addressing on Linux and Windows operating systems.
 * IPC functionality on Windows is restricted to GPUs in TCC mode
 * 
 * \param pdptr  - Returned device pointer
 * \param handle - ::HUipcMemHandle to open
 * \param Flags  - Flags for this operation. Must be specified as ::HU_IPC_MEM_LAZY_ENABLE_PEER_ACCESS
 *
 * \returns
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_MAP_FAILED,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_TOO_MANY_PEERS
 *
 * \note No guarantees are made about the address returned in \p *pdptr.  
 * In particular, multiple processes may not receive the same address for the same \p handle.
 *
 * \sa
 * ::huMemAlloc,
 * ::huMemFree,
 * ::huIpcGetEventHandle,
 * ::huIpcOpenEventHandle,
 * ::huIpcGetMemHandle,
 * ::huIpcCloseMemHandle,
 * ::huCtxEnablePeerAccess,
 * ::huDeviceCanAccessPeer,
 * ::hipIpcOpenMemHandle
 */
HUresult HIPAPI huIpcOpenMemHandle(HUdeviceptr *pdptr, HUipcMemHandle handle, unsigned int Flags);

/**
 * \brief Close memory mapped with ::huIpcOpenMemHandle
 * 
 * Unmaps memory returnd by ::huIpcOpenMemHandle. The original allocation
 * in the exporting process as well as imported mappings in other processes
 * will be unaffected.
 *
 * Any resources used to enable peer access will be freed if this is the
 * last mapping using them.
 *
 * IPC functionality is restricted to devices with support for unified
 * addressing on Linux and Windows operating systems.
 * IPC functionality on Windows is restricted to GPUs in TCC mode
 *
 * \param dptr - Device pointer returned by ::huIpcOpenMemHandle
 * 
 * \returns
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_MAP_FAILED,
 * ::HIP_ERROR_INVALID_HANDLE,
 *
 * \sa
 * ::huMemAlloc,
 * ::huMemFree,
 * ::huIpcGetEventHandle,
 * ::huIpcOpenEventHandle,
 * ::huIpcGetMemHandle,
 * ::huIpcOpenMemHandle,
 * ::hipIpcCloseMemHandle
 */
HUresult HIPAPI huIpcCloseMemHandle(HUdeviceptr dptr);

/**
 * \brief Registers an existing host memory range for use by HIP
 *
 * Page-locks the memory range specified by \p p and \p bytesize and maps it
 * for the device(s) as specified by \p Flags. This memory range also is added
 * to the same tracking mechanism as ::huMemHostAlloc to automatically accelerate
 * calls to functions such as ::huMemcpyHtoD(). Since the memory can be accessed 
 * directly by the device, it can be read or written with much higher bandwidth 
 * than pageable memory that has not been registered.  Page-locking excessive
 * amounts of memory may degrade system performance, since it reduces the amount
 * of memory available to the system for paging. As a result, this function is
 * best used sparingly to register staging areas for data exchange between
 * host and device.
 *
 * This function has limited support on Mac OS X. OS 10.7 or higher is required.
 *
 * The \p Flags parameter enables different options to be specified that
 * affect the allocation, as follows.
 *
 * - ::HU_MEMHOSTREGISTER_PORTABLE: The memory returned by this call will be
 *   considered as pinned memory by all HIP contexts, not just the one that
 *   performed the allocation.
 *
 * - ::HU_MEMHOSTREGISTER_DEVICEMAP: Maps the allocation into the HIP address
 *   space. The device pointer to the memory may be obtained by calling
 *   ::huMemHostGetDevicePointer().
 *
 * - ::HU_MEMHOSTREGISTER_IOMEMORY: The pointer is treated as pointing to some
 *   I/O memory space, e.g. the PCI Express resource of a 3rd party device.
 *
 * All of these flags are orthogonal to one another: a developer may page-lock
 * memory that is portable or mapped with no restrictions.
 *
 * The HIP context must have been created with the ::HU_CTX_MAP_HOST flag in
 * order for the ::HU_MEMHOSTREGISTER_DEVICEMAP flag to have any effect.
 *
 * The ::HU_MEMHOSTREGISTER_DEVICEMAP flag may be specified on HIP contexts for
 * devices that do not support mapped pinned memory. The failure is deferred
 * to ::huMemHostGetDevicePointer() because the memory may be mapped into
 * other HIP contexts via the ::HU_MEMHOSTREGISTER_PORTABLE flag.
 *
 * For devices that have a non-zero value for the device attribute
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_HOST_POINTER_FOR_REGISTERED_MEM, the memory
 * can also be accessed from the device using the host pointer \p p.
 * The device pointer returned by ::huMemHostGetDevicePointer() may or may not
 * match the original host pointer \p ptr and depends on the devices visible to the
 * application. If all devices visible to the application have a non-zero value for the
 * device attribute, the device pointer returned by ::huMemHostGetDevicePointer()
 * will match the original pointer \p ptr. If any device visible to the application
 * has a zero value for the device attribute, the device pointer returned by
 * ::huMemHostGetDevicePointer() will not match the original host pointer \p ptr,
 * but it will be suitable for use on all devices provided Unified Virtual Addressing
 * is enabled. In such systems, it is valid to access the memory using either pointer
 * on devices that have a non-zero value for the device attribute. Note however that
 * such devices should access the memory using only of the two pointers and not both.
 *
 * The memory page-locked by this function must be unregistered with 
 * ::huMemHostUnregister().
 *
 * \param p        - Host pointer to memory to page-lock
 * \param bytesize - Size in bytes of the address range to page-lock
 * \param Flags    - Flags for allocation request
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_HOST_MEMORY_ALREADY_REGISTERED,
 * ::HIP_ERROR_NOT_PERMITTED,
 * ::HIP_ERROR_NOT_SUPPORTED
 * \notefnerr
 *
 * \sa
 * ::huMemHostUnregister,
 * ::huMemHostGetFlags,
 * ::huMemHostGetDevicePointer,
 * ::hipHostRegister
 */
HUresult HIPAPI huMemHostRegister(void *p, size_t bytesize, unsigned int Flags);

/**
 * \brief Unregisters a memory range that was registered with huMemHostRegister.
 *
 * Unmaps the memory range whose base address is specified by \p p, and makes
 * it pageable again.
 *
 * The base address must be the same one specified to ::huMemHostRegister().
 *
 * \param p - Host pointer to memory to unregister
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_HOST_MEMORY_NOT_REGISTERED,
 * \notefnerr
 *
 * \sa
 * ::huMemHostRegister,
 * ::hipHostUnregister
 */
HUresult HIPAPI huMemHostUnregister(void *p);

/**
 * \brief Copies memory
 *
 * Copies data between two pointers. 
 * \p dst and \p src are base pointers of the destination and source, respectively.  
 * \p ByteCount specifies the number of bytes to copy.
 * Note that this function infers the type of the transfer (host to host, host to 
 *   device, device to device, or device to host) from the pointer values.  This
 *   function is only allowed in contexts which support unified addressing.
 *
 * \param dst - Destination unified virtual address space pointer
 * \param src - Source unified virtual address space pointer
 * \param ByteCount - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpy,
 * ::hipMemcpyToSymbol,
 * ::hipMemcpyFromSymbol
 */
HUresult HIPAPI huMemcpy(HUdeviceptr dst, HUdeviceptr src, size_t ByteCount);

/**
 * \brief Copies device memory between two contexts
 *
 * Copies from device memory in one context to device memory in another
 * context. \p dstDevice is the base device pointer of the destination memory 
 * and \p dstContext is the destination context.  \p srcDevice is the base 
 * device pointer of the source memory and \p srcContext is the source pointer.  
 * \p ByteCount specifies the number of bytes to copy.
 *
 * \param dstDevice  - Destination device pointer
 * \param dstContext - Destination context
 * \param srcDevice  - Source device pointer
 * \param srcContext - Source context
 * \param ByteCount  - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huMemcpyDtoD, ::huMemcpy3DPeer, ::huMemcpyDtoDAsync, ::huMemcpyPeerAsync,
 * ::huMemcpy3DPeerAsync,
 * ::hipMemcpyPeer
 */
HUresult HIPAPI huMemcpyPeer(HUdeviceptr dstDevice, HUcontext dstContext, HUdeviceptr srcDevice, HUcontext srcContext, size_t ByteCount);

/**
 * \brief Copies memory from Host to Device
 *
 * Copies from host memory to device memory. \p dstDevice and \p srcHost are
 * the base addresses of the destination and source, respectively. \p ByteCount
 * specifies the number of bytes to copy.
 *
 * \param dstDevice - Destination device pointer
 * \param srcHost   - Source host pointer
 * \param ByteCount - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpy,
 * ::hipMemcpyToSymbol
 */
HUresult HIPAPI huMemcpyHtoD(HUdeviceptr dstDevice, const void *srcHost, size_t ByteCount);

/**
 * \brief Copies memory from Device to Host
 *
 * Copies from device to host memory. \p dstHost and \p srcDevice specify the
 * base pointers of the destination and source, respectively. \p ByteCount
 * specifies the number of bytes to copy.
 *
 * \param dstHost   - Destination host pointer
 * \param srcDevice - Source device pointer
 * \param ByteCount - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpy,
 * ::hipMemcpyFromSymbol
 */
HUresult HIPAPI huMemcpyDtoH(void *dstHost, HUdeviceptr srcDevice, size_t ByteCount);

/**
 * \brief Copies memory from Device to Device
 *
 * Copies from device memory to device memory. \p dstDevice and \p srcDevice
 * are the base pointers of the destination and source, respectively.
 * \p ByteCount specifies the number of bytes to copy.
 *
 * \param dstDevice - Destination device pointer
 * \param srcDevice - Source device pointer
 * \param ByteCount - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpy,
 * ::hipMemcpyToSymbol,
 * ::hipMemcpyFromSymbol
 */
HUresult HIPAPI huMemcpyDtoD(HUdeviceptr dstDevice, HUdeviceptr srcDevice, size_t ByteCount);

/**
 * \brief Copies memory from Device to Array
 *
 * Copies from device memory to a 1D HIP array. \p dstArray and \p dstOffset
 * specify the HIP array handle and starting index of the destination data.
 * \p srcDevice specifies the base pointer of the source. \p ByteCount
 * specifies the number of bytes to copy.
 *
 * \param dstArray  - Destination array
 * \param dstOffset - Offset in bytes of destination array
 * \param srcDevice - Source device pointer
 * \param ByteCount - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpyToArray
 */
HUresult HIPAPI huMemcpyDtoA(HUarray dstArray, size_t dstOffset, HUdeviceptr srcDevice, size_t ByteCount);

/**
 * \brief Copies memory from Array to Device
 *
 * Copies from one 1D HIP array to device memory. \p dstDevice specifies the
 * base pointer of the destination and must be naturally aligned with the HIP
 * array elements. \p srcArray and \p srcOffset specify the HIP array handle
 * and the offset in bytes into the array where the copy is to begin.
 * \p ByteCount specifies the number of bytes to copy and must be evenly
 * divisible by the array element size.
 *
 * \param dstDevice - Destination device pointer
 * \param srcArray  - Source array
 * \param srcOffset - Offset in bytes of source array
 * \param ByteCount - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpyFromArray
 */
HUresult HIPAPI huMemcpyAtoD(HUdeviceptr dstDevice, HUarray srcArray, size_t srcOffset, size_t ByteCount);

/**
 * \brief Copies memory from Host to Array
 *
 * Copies from host memory to a 1D HIP array. \p dstArray and \p dstOffset
 * specify the HIP array handle and starting offset in bytes of the destination
 * data.  \p pSrc specifies the base address of the source. \p ByteCount specifies
 * the number of bytes to copy.
 *
 * \param dstArray  - Destination array
 * \param dstOffset - Offset in bytes of destination array
 * \param srcHost   - Source host pointer
 * \param ByteCount - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpyToArray
 */
HUresult HIPAPI huMemcpyHtoA(HUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount);

/**
 * \brief Copies memory from Array to Host
 *
 * Copies from one 1D HIP array to host memory. \p dstHost specifies the base
 * pointer of the destination. \p srcArray and \p srcOffset specify the HIP
 * array handle and starting offset in bytes of the source data.
 * \p ByteCount specifies the number of bytes to copy.
 *
 * \param dstHost   - Destination device pointer
 * \param srcArray  - Source array
 * \param srcOffset - Offset in bytes of source array
 * \param ByteCount - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpyFromArray
 */
HUresult HIPAPI huMemcpyAtoH(void *dstHost, HUarray srcArray, size_t srcOffset, size_t ByteCount);

/**
 * \brief Copies memory from Array to Array
 *
 * Copies from one 1D HIP array to another. \p dstArray and \p srcArray
 * specify the handles of the destination and source HIP arrays for the copy,
 * respectively. \p dstOffset and \p srcOffset specify the destination and
 * source offsets in bytes into the HIP arrays. \p ByteCount is the number of
 * bytes to be copied. The size of the elements in the HIP arrays need not be
 * the same format, but the elements must be the same size; and count must be
 * evenly divisible by that size.
 *
 * \param dstArray  - Destination array
 * \param dstOffset - Offset in bytes of destination array
 * \param srcArray  - Source array
 * \param srcOffset - Offset in bytes of source array
 * \param ByteCount - Size of memory copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpyArrayToArray
 */
HUresult HIPAPI huMemcpyAtoA(HUarray dstArray, size_t dstOffset, HUarray srcArray, size_t srcOffset, size_t ByteCount);

/**
 * \brief Copies memory for 2D arrays
 *
 * Perform a 2D memory copy according to the parameters specified in \p pCopy.
 * The ::HIP_MEMCPY2D structure is defined as:
 *
 * \code
   typedef struct HIP_MEMCPY2D_st {
      unsigned int srcXInBytes, srcY;
      HUmemorytype srcMemoryType;
          const void *srcHost;
          HUdeviceptr srcDevice;
          HUarray srcArray;
          unsigned int srcPitch;

      unsigned int dstXInBytes, dstY;
      HUmemorytype dstMemoryType;
          void *dstHost;
          HUdeviceptr dstDevice;
          HUarray dstArray;
          unsigned int dstPitch;

      unsigned int WidthInBytes;
      unsigned int Height;
   } HIP_MEMCPY2D;
 * \endcode
 * where:
 * - ::srcMemoryType and ::dstMemoryType specify the type of memory of the
 *   source and destination, respectively; ::HUmemorytype_enum is defined as:
 *
 * \code
   typedef enum HUmemorytype_enum {
      HU_MEMORYTYPE_HOST = 0x01,
      HU_MEMORYTYPE_DEVICE = 0x02,
      HU_MEMORYTYPE_ARRAY = 0x03,
      HU_MEMORYTYPE_UNIFIED = 0x04
   } HUmemorytype;
 * \endcode
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::srcDevice and ::srcPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::srcArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_HOST, ::srcHost and ::srcPitch
 * specify the (host) base address of the source data and the bytes per row to
 * apply. ::srcArray is ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_DEVICE, ::srcDevice and ::srcPitch
 * specify the (device) base address of the source data and the bytes per row
 * to apply. ::srcArray is ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_ARRAY, ::srcArray specifies the
 * handle of the source data. ::srcHost, ::srcDevice and ::srcPitch are
 * ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_HOST, ::dstHost and ::dstPitch
 * specify the (host) base address of the destination data and the bytes per
 * row to apply. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::dstDevice and ::dstPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::dstArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_DEVICE, ::dstDevice and ::dstPitch
 * specify the (device) base address of the destination data and the bytes per
 * row to apply. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_ARRAY, ::dstArray specifies the
 * handle of the destination data. ::dstHost, ::dstDevice and ::dstPitch are
 * ignored.
 *
 * - ::srcXInBytes and ::srcY specify the base address of the source data for
 *   the copy.
 *
 * \par
 * For host pointers, the starting address is
 * \code
  void* Start = (void*)((char*)srcHost+srcY*srcPitch + srcXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr Start = srcDevice+srcY*srcPitch+srcXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::srcXInBytes must be evenly divisible by the array
 * element size.
 *
 * - ::dstXInBytes and ::dstY specify the base address of the destination data
 *   for the copy.
 *
 * \par
 * For host pointers, the base address is
 * \code
  void* dstStart = (void*)((char*)dstHost+dstY*dstPitch + dstXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr dstStart = dstDevice+dstY*dstPitch+dstXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::dstXInBytes must be evenly divisible by the array
 * element size.
 *
 * - ::WidthInBytes and ::Height specify the width (in bytes) and height of
 *   the 2D copy being performed.
 * - If specified, ::srcPitch must be greater than or equal to ::WidthInBytes +
 *   ::srcXInBytes, and ::dstPitch must be greater than or equal to
 *   ::WidthInBytes + dstXInBytes.
 *
 * \par
 * ::huMemcpy2D() returns an error if any pitch is greater than the maximum
 * allowed (::HU_DEVICE_ATTRIBUTE_MAX_PITCH). ::huMemAllocPitch() passes back
 * pitches that always work with ::huMemcpy2D(). On intra-device memory copies
 * (device to device, HIP array to device, HIP array to HIP array),
 * ::huMemcpy2D() may fail for pitches not computed by ::huMemAllocPitch().
 * ::huMemcpy2DUnaligned() does not have this restriction, but may run
 * significantly slower in the cases where ::huMemcpy2D() would have returned
 * an error code.
 *
 * \param pCopy - Parameters for the memory copy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpy2D,
 * ::hipMemcpy2DToArray,
 * ::hipMemcpy2DFromArray
 */
HUresult HIPAPI huMemcpy2D(const HIP_MEMCPY2D *pCopy);

/**
 * \brief Copies memory for 2D arrays
 *
 * Perform a 2D memory copy according to the parameters specified in \p pCopy.
 * The ::HIP_MEMCPY2D structure is defined as:
 *
 * \code
   typedef struct HIP_MEMCPY2D_st {
      unsigned int srcXInBytes, srcY;
      HUmemorytype srcMemoryType;
      const void *srcHost;
      HUdeviceptr srcDevice;
      HUarray srcArray;
      unsigned int srcPitch;
      unsigned int dstXInBytes, dstY;
      HUmemorytype dstMemoryType;
      void *dstHost;
      HUdeviceptr dstDevice;
      HUarray dstArray;
      unsigned int dstPitch;
      unsigned int WidthInBytes;
      unsigned int Height;
   } HIP_MEMCPY2D;
 * \endcode
 * where:
 * - ::srcMemoryType and ::dstMemoryType specify the type of memory of the
 *   source and destination, respectively; ::HUmemorytype_enum is defined as:
 *
 * \code
   typedef enum HUmemorytype_enum {
      HU_MEMORYTYPE_HOST = 0x01,
      HU_MEMORYTYPE_DEVICE = 0x02,
      HU_MEMORYTYPE_ARRAY = 0x03,
      HU_MEMORYTYPE_UNIFIED = 0x04
   } HUmemorytype;
 * \endcode
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::srcDevice and ::srcPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::srcArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_HOST, ::srcHost and ::srcPitch
 * specify the (host) base address of the source data and the bytes per row to
 * apply. ::srcArray is ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_DEVICE, ::srcDevice and ::srcPitch
 * specify the (device) base address of the source data and the bytes per row
 * to apply. ::srcArray is ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_ARRAY, ::srcArray specifies the
 * handle of the source data. ::srcHost, ::srcDevice and ::srcPitch are
 * ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::dstDevice and ::dstPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::dstArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_HOST, ::dstHost and ::dstPitch
 * specify the (host) base address of the destination data and the bytes per
 * row to apply. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_DEVICE, ::dstDevice and ::dstPitch
 * specify the (device) base address of the destination data and the bytes per
 * row to apply. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_ARRAY, ::dstArray specifies the
 * handle of the destination data. ::dstHost, ::dstDevice and ::dstPitch are
 * ignored.
 *
 * - ::srcXInBytes and ::srcY specify the base address of the source data for
 *   the copy.
 *
 * \par
 * For host pointers, the starting address is
 * \code
  void* Start = (void*)((char*)srcHost+srcY*srcPitch + srcXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr Start = srcDevice+srcY*srcPitch+srcXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::srcXInBytes must be evenly divisible by the array
 * element size.
 *
 * - ::dstXInBytes and ::dstY specify the base address of the destination data
 *   for the copy.
 *
 * \par
 * For host pointers, the base address is
 * \code
  void* dstStart = (void*)((char*)dstHost+dstY*dstPitch + dstXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr dstStart = dstDevice+dstY*dstPitch+dstXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::dstXInBytes must be evenly divisible by the array
 * element size.
 *
 * - ::WidthInBytes and ::Height specify the width (in bytes) and height of
 *   the 2D copy being performed.
 * - If specified, ::srcPitch must be greater than or equal to ::WidthInBytes +
 *   ::srcXInBytes, and ::dstPitch must be greater than or equal to
 *   ::WidthInBytes + dstXInBytes.
 *
 * \par
 * ::huMemcpy2D() returns an error if any pitch is greater than the maximum
 * allowed (::HU_DEVICE_ATTRIBUTE_MAX_PITCH). ::huMemAllocPitch() passes back
 * pitches that always work with ::huMemcpy2D(). On intra-device memory copies
 * (device to device, HIP array to device, HIP array to HIP array),
 * ::huMemcpy2D() may fail for pitches not computed by ::huMemAllocPitch().
 * ::huMemcpy2DUnaligned() does not have this restriction, but may run
 * significantly slower in the cases where ::huMemcpy2D() would have returned
 * an error code.
 *
 * \param pCopy - Parameters for the memory copy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpy2D,
 * ::hipMemcpy2DToArray,
 * ::hipMemcpy2DFromArray
 */
HUresult HIPAPI huMemcpy2DUnaligned(const HIP_MEMCPY2D *pCopy);

/**
 * \brief Copies memory for 3D arrays
 *
 * Perform a 3D memory copy according to the parameters specified in
 * \p pCopy. The ::HIP_MEMCPY3D structure is defined as:
 *
 * \code
        typedef struct HIP_MEMCPY3D_st {

            unsigned int srcXInBytes, srcY, srcZ;
            unsigned int srcLOD;
            HUmemorytype srcMemoryType;
                const void *srcHost;
                HUdeviceptr srcDevice;
                HUarray srcArray;
                unsigned int srcPitch;  // ignored when src is array
                unsigned int srcHeight; // ignored when src is array; may be 0 if Depth==1

            unsigned int dstXInBytes, dstY, dstZ;
            unsigned int dstLOD;
            HUmemorytype dstMemoryType;
                void *dstHost;
                HUdeviceptr dstDevice;
                HUarray dstArray;
                unsigned int dstPitch;  // ignored when dst is array
                unsigned int dstHeight; // ignored when dst is array; may be 0 if Depth==1

            unsigned int WidthInBytes;
            unsigned int Height;
            unsigned int Depth;
        } HIP_MEMCPY3D;
 * \endcode
 * where:
 * - ::srcMemoryType and ::dstMemoryType specify the type of memory of the
 *   source and destination, respectively; ::HUmemorytype_enum is defined as:
 *
 * \code
   typedef enum HUmemorytype_enum {
      HU_MEMORYTYPE_HOST = 0x01,
      HU_MEMORYTYPE_DEVICE = 0x02,
      HU_MEMORYTYPE_ARRAY = 0x03,
      HU_MEMORYTYPE_UNIFIED = 0x04
   } HUmemorytype;
 * \endcode
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::srcDevice and ::srcPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::srcArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_HOST, ::srcHost, ::srcPitch and
 * ::srcHeight specify the (host) base address of the source data, the bytes
 * per row, and the height of each 2D slice of the 3D array. ::srcArray is
 * ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_DEVICE, ::srcDevice, ::srcPitch and
 * ::srcHeight specify the (device) base address of the source data, the bytes
 * per row, and the height of each 2D slice of the 3D array. ::srcArray is
 * ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_ARRAY, ::srcArray specifies the
 * handle of the source data. ::srcHost, ::srcDevice, ::srcPitch and
 * ::srcHeight are ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::dstDevice and ::dstPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::dstArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_HOST, ::dstHost and ::dstPitch
 * specify the (host) base address of the destination data, the bytes per row,
 * and the height of each 2D slice of the 3D array. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_DEVICE, ::dstDevice and ::dstPitch
 * specify the (device) base address of the destination data, the bytes per
 * row, and the height of each 2D slice of the 3D array. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_ARRAY, ::dstArray specifies the
 * handle of the destination data. ::dstHost, ::dstDevice, ::dstPitch and
 * ::dstHeight are ignored.
 *
 * - ::srcXInBytes, ::srcY and ::srcZ specify the base address of the source
 *   data for the copy.
 *
 * \par
 * For host pointers, the starting address is
 * \code
  void* Start = (void*)((char*)srcHost+(srcZ*srcHeight+srcY)*srcPitch + srcXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr Start = srcDevice+(srcZ*srcHeight+srcY)*srcPitch+srcXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::srcXInBytes must be evenly divisible by the array
 * element size.
 *
 * - dstXInBytes, ::dstY and ::dstZ specify the base address of the
 *   destination data for the copy.
 *
 * \par
 * For host pointers, the base address is
 * \code
  void* dstStart = (void*)((char*)dstHost+(dstZ*dstHeight+dstY)*dstPitch + dstXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr dstStart = dstDevice+(dstZ*dstHeight+dstY)*dstPitch+dstXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::dstXInBytes must be evenly divisible by the array
 * element size.
 *
 * - ::WidthInBytes, ::Height and ::Depth specify the width (in bytes), height
 *   and depth of the 3D copy being performed.
 * - If specified, ::srcPitch must be greater than or equal to ::WidthInBytes +
 *   ::srcXInBytes, and ::dstPitch must be greater than or equal to
 *   ::WidthInBytes + dstXInBytes.
 * - If specified, ::srcHeight must be greater than or equal to ::Height +
 *   ::srcY, and ::dstHeight must be greater than or equal to ::Height + ::dstY.
 *
 * \par
 * ::huMemcpy3D() returns an error if any pitch is greater than the maximum
 * allowed (::HU_DEVICE_ATTRIBUTE_MAX_PITCH).
 *
 * The ::srcLOD and ::dstLOD members of the ::HIP_MEMCPY3D structure must be
 * set to 0.
 *
 * \param pCopy - Parameters for the memory copy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMemcpy3D
 */
HUresult HIPAPI huMemcpy3D(const HIP_MEMCPY3D *pCopy);

/**
 * \brief Copies memory between contexts
 *
 * Perform a 3D memory copy according to the parameters specified in
 * \p pCopy.  See the definition of the ::HIP_MEMCPY3D_PEER structure
 * for documentation of its parameters.
 *
 * \param pCopy - Parameters for the memory copy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_sync
 *
 * \sa ::huMemcpyDtoD, ::huMemcpyPeer, ::huMemcpyDtoDAsync, ::huMemcpyPeerAsync,
 * ::huMemcpy3DPeerAsync,
 * ::hipMemcpy3DPeer
 */
HUresult HIPAPI huMemcpy3DPeer(const HIP_MEMCPY3D_PEER *pCopy);

/**
 * \brief Copies memory asynchronously
 *
 * Copies data between two pointers. 
 * \p dst and \p src are base pointers of the destination and source, respectively.  
 * \p ByteCount specifies the number of bytes to copy.
 * Note that this function infers the type of the transfer (host to host, host to 
 *   device, device to device, or device to host) from the pointer values.  This
 *   function is only allowed in contexts which support unified addressing.
 *
 * \param dst       - Destination unified virtual address space pointer
 * \param src       - Source unified virtual address space pointer
 * \param ByteCount - Size of memory copy in bytes
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemcpyAsync,
 * ::hipMemcpyToSymbolAsync,
 * ::hipMemcpyFromSymbolAsync
 */
HUresult HIPAPI huMemcpyAsync(HUdeviceptr dst, HUdeviceptr src, size_t ByteCount, HUstream hStream);

/**
 * \brief Copies device memory between two contexts asynchronously.
 *
 * Copies from device memory in one context to device memory in another
 * context. \p dstDevice is the base device pointer of the destination memory 
 * and \p dstContext is the destination context.  \p srcDevice is the base 
 * device pointer of the source memory and \p srcContext is the source pointer.  
 * \p ByteCount specifies the number of bytes to copy.
 *
 * \param dstDevice  - Destination device pointer
 * \param dstContext - Destination context
 * \param srcDevice  - Source device pointer
 * \param srcContext - Source context
 * \param ByteCount  - Size of memory copy in bytes
 * \param hStream    - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huMemcpyDtoD, ::huMemcpyPeer, ::huMemcpy3DPeer, ::huMemcpyDtoDAsync, 
 * ::huMemcpy3DPeerAsync,
 * ::hipMemcpyPeerAsync
 */
HUresult HIPAPI huMemcpyPeerAsync(HUdeviceptr dstDevice, HUcontext dstContext, HUdeviceptr srcDevice, HUcontext srcContext, size_t ByteCount, HUstream hStream);

/**
 * \brief Copies memory from Host to Device
 *
 * Copies from host memory to device memory. \p dstDevice and \p srcHost are
 * the base addresses of the destination and source, respectively. \p ByteCount
 * specifies the number of bytes to copy.
 *
 * \param dstDevice - Destination device pointer
 * \param srcHost   - Source host pointer
 * \param ByteCount - Size of memory copy in bytes
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemcpyAsync,
 * ::hipMemcpyToSymbolAsync
 */
HUresult HIPAPI huMemcpyHtoDAsync(HUdeviceptr dstDevice, const void *srcHost, size_t ByteCount, HUstream hStream);

/**
 * \brief Copies memory from Device to Host
 *
 * Copies from device to host memory. \p dstHost and \p srcDevice specify the
 * base pointers of the destination and source, respectively. \p ByteCount
 * specifies the number of bytes to copy.
 *
 * \param dstHost   - Destination host pointer
 * \param srcDevice - Source device pointer
 * \param ByteCount - Size of memory copy in bytes
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemcpyAsync,
 * ::hipMemcpyFromSymbolAsync
 */
HUresult HIPAPI huMemcpyDtoHAsync(void *dstHost, HUdeviceptr srcDevice, size_t ByteCount, HUstream hStream);

/**
 * \brief Copies memory from Device to Device
 *
 * Copies from device memory to device memory. \p dstDevice and \p srcDevice
 * are the base pointers of the destination and source, respectively.
 * \p ByteCount specifies the number of bytes to copy.
 *
 * \param dstDevice - Destination device pointer
 * \param srcDevice - Source device pointer
 * \param ByteCount - Size of memory copy in bytes
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemcpyAsync,
 * ::hipMemcpyToSymbolAsync,
 * ::hipMemcpyFromSymbolAsync
 */
HUresult HIPAPI huMemcpyDtoDAsync(HUdeviceptr dstDevice, HUdeviceptr srcDevice, size_t ByteCount, HUstream hStream);

/**
 * \brief Copies memory from Host to Array
 *
 * Copies from host memory to a 1D HIP array. \p dstArray and \p dstOffset
 * specify the HIP array handle and starting offset in bytes of the
 * destination data. \p srcHost specifies the base address of the source.
 * \p ByteCount specifies the number of bytes to copy.
 *
 * \param dstArray  - Destination array
 * \param dstOffset - Offset in bytes of destination array
 * \param srcHost   - Source host pointer
 * \param ByteCount - Size of memory copy in bytes
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemcpyToArrayAsync
 */
HUresult HIPAPI huMemcpyHtoAAsync(HUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount, HUstream hStream);

/**
 * \brief Copies memory from Array to Host
 *
 * Copies from one 1D HIP array to host memory. \p dstHost specifies the base
 * pointer of the destination. \p srcArray and \p srcOffset specify the HIP
 * array handle and starting offset in bytes of the source data.
 * \p ByteCount specifies the number of bytes to copy.
 *
 * \param dstHost   - Destination pointer
 * \param srcArray  - Source array
 * \param srcOffset - Offset in bytes of source array
 * \param ByteCount - Size of memory copy in bytes
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemcpyFromArrayAsync
 */
HUresult HIPAPI huMemcpyAtoHAsync(void *dstHost, HUarray srcArray, size_t srcOffset, size_t ByteCount, HUstream hStream);

/**
 * \brief Copies memory for 2D arrays
 *
 * Perform a 2D memory copy according to the parameters specified in \p pCopy.
 * The ::HIP_MEMCPY2D structure is defined as:
 *
 * \code
   typedef struct HIP_MEMCPY2D_st {
      unsigned int srcXInBytes, srcY;
      HUmemorytype srcMemoryType;
      const void *srcHost;
      HUdeviceptr srcDevice;
      HUarray srcArray;
      unsigned int srcPitch;
      unsigned int dstXInBytes, dstY;
      HUmemorytype dstMemoryType;
      void *dstHost;
      HUdeviceptr dstDevice;
      HUarray dstArray;
      unsigned int dstPitch;
      unsigned int WidthInBytes;
      unsigned int Height;
   } HIP_MEMCPY2D;
 * \endcode
 * where:
 * - ::srcMemoryType and ::dstMemoryType specify the type of memory of the
 *   source and destination, respectively; ::HUmemorytype_enum is defined as:
 *
 * \code
   typedef enum HUmemorytype_enum {
      HU_MEMORYTYPE_HOST = 0x01,
      HU_MEMORYTYPE_DEVICE = 0x02,
      HU_MEMORYTYPE_ARRAY = 0x03,
      HU_MEMORYTYPE_UNIFIED = 0x04
   } HUmemorytype;
 * \endcode
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_HOST, ::srcHost and ::srcPitch
 * specify the (host) base address of the source data and the bytes per row to
 * apply. ::srcArray is ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::srcDevice and ::srcPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::srcArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_DEVICE, ::srcDevice and ::srcPitch
 * specify the (device) base address of the source data and the bytes per row
 * to apply. ::srcArray is ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_ARRAY, ::srcArray specifies the
 * handle of the source data. ::srcHost, ::srcDevice and ::srcPitch are
 * ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::dstDevice and ::dstPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::dstArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_HOST, ::dstHost and ::dstPitch
 * specify the (host) base address of the destination data and the bytes per
 * row to apply. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_DEVICE, ::dstDevice and ::dstPitch
 * specify the (device) base address of the destination data and the bytes per
 * row to apply. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_ARRAY, ::dstArray specifies the
 * handle of the destination data. ::dstHost, ::dstDevice and ::dstPitch are
 * ignored.
 *
 * - ::srcXInBytes and ::srcY specify the base address of the source data for
 *   the copy.
 *
 * \par
 * For host pointers, the starting address is
 * \code
  void* Start = (void*)((char*)srcHost+srcY*srcPitch + srcXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr Start = srcDevice+srcY*srcPitch+srcXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::srcXInBytes must be evenly divisible by the array
 * element size.
 *
 * - ::dstXInBytes and ::dstY specify the base address of the destination data
 *   for the copy.
 *
 * \par
 * For host pointers, the base address is
 * \code
  void* dstStart = (void*)((char*)dstHost+dstY*dstPitch + dstXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr dstStart = dstDevice+dstY*dstPitch+dstXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::dstXInBytes must be evenly divisible by the array
 * element size.
 *
 * - ::WidthInBytes and ::Height specify the width (in bytes) and height of
 *   the 2D copy being performed.
 * - If specified, ::srcPitch must be greater than or equal to ::WidthInBytes +
 *   ::srcXInBytes, and ::dstPitch must be greater than or equal to
 *   ::WidthInBytes + dstXInBytes.
 * - If specified, ::srcPitch must be greater than or equal to ::WidthInBytes +
 *   ::srcXInBytes, and ::dstPitch must be greater than or equal to
 *   ::WidthInBytes + dstXInBytes.
 * - If specified, ::srcHeight must be greater than or equal to ::Height +
 *   ::srcY, and ::dstHeight must be greater than or equal to ::Height + ::dstY.
 *
 * \par
 * ::huMemcpy2DAsync() returns an error if any pitch is greater than the maximum
 * allowed (::HU_DEVICE_ATTRIBUTE_MAX_PITCH). ::huMemAllocPitch() passes back
 * pitches that always work with ::huMemcpy2D(). On intra-device memory copies
 * (device to device, HIP array to device, HIP array to HIP array),
 * ::huMemcpy2DAsync() may fail for pitches not computed by ::huMemAllocPitch().
 *
 * \param pCopy   - Parameters for the memory copy
 * \param hStream - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemcpy2DAsync,
 * ::hipMemcpy2DToArrayAsync,
 * ::hipMemcpy2DFromArrayAsync
 */
HUresult HIPAPI huMemcpy2DAsync(const HIP_MEMCPY2D *pCopy, HUstream hStream);

/**
 * \brief Copies memory for 3D arrays
 *
 * Perform a 3D memory copy according to the parameters specified in
 * \p pCopy. The ::HIP_MEMCPY3D structure is defined as:
 *
 * \code
        typedef struct HIP_MEMCPY3D_st {

            unsigned int srcXInBytes, srcY, srcZ;
            unsigned int srcLOD;
            HUmemorytype srcMemoryType;
                const void *srcHost;
                HUdeviceptr srcDevice;
                HUarray srcArray;
                unsigned int srcPitch;  // ignored when src is array
                unsigned int srcHeight; // ignored when src is array; may be 0 if Depth==1

            unsigned int dstXInBytes, dstY, dstZ;
            unsigned int dstLOD;
            HUmemorytype dstMemoryType;
                void *dstHost;
                HUdeviceptr dstDevice;
                HUarray dstArray;
                unsigned int dstPitch;  // ignored when dst is array
                unsigned int dstHeight; // ignored when dst is array; may be 0 if Depth==1

            unsigned int WidthInBytes;
            unsigned int Height;
            unsigned int Depth;
        } HIP_MEMCPY3D;
 * \endcode
 * where:
 * - ::srcMemoryType and ::dstMemoryType specify the type of memory of the
 *   source and destination, respectively; ::HUmemorytype_enum is defined as:
 *
 * \code
   typedef enum HUmemorytype_enum {
      HU_MEMORYTYPE_HOST = 0x01,
      HU_MEMORYTYPE_DEVICE = 0x02,
      HU_MEMORYTYPE_ARRAY = 0x03,
      HU_MEMORYTYPE_UNIFIED = 0x04
   } HUmemorytype;
 * \endcode
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::srcDevice and ::srcPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::srcArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_HOST, ::srcHost, ::srcPitch and
 * ::srcHeight specify the (host) base address of the source data, the bytes
 * per row, and the height of each 2D slice of the 3D array. ::srcArray is
 * ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_DEVICE, ::srcDevice, ::srcPitch and
 * ::srcHeight specify the (device) base address of the source data, the bytes
 * per row, and the height of each 2D slice of the 3D array. ::srcArray is
 * ignored.
 *
 * \par
 * If ::srcMemoryType is ::HU_MEMORYTYPE_ARRAY, ::srcArray specifies the
 * handle of the source data. ::srcHost, ::srcDevice, ::srcPitch and
 * ::srcHeight are ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_UNIFIED, ::dstDevice and ::dstPitch
 *   specify the (unified virtual address space) base address of the source data 
 *   and the bytes per row to apply.  ::dstArray is ignored.  
 * This value may be used only if unified addressing is supported in the calling 
 *   context.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_HOST, ::dstHost and ::dstPitch
 * specify the (host) base address of the destination data, the bytes per row,
 * and the height of each 2D slice of the 3D array. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_DEVICE, ::dstDevice and ::dstPitch
 * specify the (device) base address of the destination data, the bytes per
 * row, and the height of each 2D slice of the 3D array. ::dstArray is ignored.
 *
 * \par
 * If ::dstMemoryType is ::HU_MEMORYTYPE_ARRAY, ::dstArray specifies the
 * handle of the destination data. ::dstHost, ::dstDevice, ::dstPitch and
 * ::dstHeight are ignored.
 *
 * - ::srcXInBytes, ::srcY and ::srcZ specify the base address of the source
 *   data for the copy.
 *
 * \par
 * For host pointers, the starting address is
 * \code
  void* Start = (void*)((char*)srcHost+(srcZ*srcHeight+srcY)*srcPitch + srcXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr Start = srcDevice+(srcZ*srcHeight+srcY)*srcPitch+srcXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::srcXInBytes must be evenly divisible by the array
 * element size.
 *
 * - dstXInBytes, ::dstY and ::dstZ specify the base address of the
 *   destination data for the copy.
 *
 * \par
 * For host pointers, the base address is
 * \code
  void* dstStart = (void*)((char*)dstHost+(dstZ*dstHeight+dstY)*dstPitch + dstXInBytes);
 * \endcode
 *
 * \par
 * For device pointers, the starting address is
 * \code
  HUdeviceptr dstStart = dstDevice+(dstZ*dstHeight+dstY)*dstPitch+dstXInBytes;
 * \endcode
 *
 * \par
 * For HIP arrays, ::dstXInBytes must be evenly divisible by the array
 * element size.
 *
 * - ::WidthInBytes, ::Height and ::Depth specify the width (in bytes), height
 *   and depth of the 3D copy being performed.
 * - If specified, ::srcPitch must be greater than or equal to ::WidthInBytes +
 *   ::srcXInBytes, and ::dstPitch must be greater than or equal to
 *   ::WidthInBytes + dstXInBytes.
 * - If specified, ::srcHeight must be greater than or equal to ::Height +
 *   ::srcY, and ::dstHeight must be greater than or equal to ::Height + ::dstY.
 *
 * \par
 * ::huMemcpy3DAsync() returns an error if any pitch is greater than the maximum
 * allowed (::HU_DEVICE_ATTRIBUTE_MAX_PITCH).
 *
 * The ::srcLOD and ::dstLOD members of the ::HIP_MEMCPY3D structure must be
 * set to 0.
 *
 * \param pCopy - Parameters for the memory copy
 * \param hStream - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemcpy3DAsync
 */
HUresult HIPAPI huMemcpy3DAsync(const HIP_MEMCPY3D *pCopy, HUstream hStream);

/**
 * \brief Copies memory between contexts asynchronously.
 *
 * Perform a 3D memory copy according to the parameters specified in
 * \p pCopy.  See the definition of the ::HIP_MEMCPY3D_PEER structure
 * for documentation of its parameters.
 *
 * \param pCopy - Parameters for the memory copy
 * \param hStream - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huMemcpyDtoD, ::huMemcpyPeer, ::huMemcpyDtoDAsync, ::huMemcpyPeerAsync,
 * ::huMemcpy3DPeerAsync,
 * ::hipMemcpy3DPeerAsync
 */
HUresult HIPAPI huMemcpy3DPeerAsync(const HIP_MEMCPY3D_PEER *pCopy, HUstream hStream);

/**
 * \brief Initializes device memory
 *
 * Sets the memory range of \p N 8-bit values to the specified value
 * \p uc.
 *
 * \param dstDevice - Destination device pointer
 * \param uc        - Value to set
 * \param N         - Number of elements
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemset
 */
HUresult HIPAPI huMemsetD8(HUdeviceptr dstDevice, unsigned char uc, size_t N);

/**
 * \brief Initializes device memory
 *
 * Sets the memory range of \p N 16-bit values to the specified value
 * \p us. The \p dstDevice pointer must be two byte aligned.
 *
 * \param dstDevice - Destination device pointer
 * \param us        - Value to set
 * \param N         - Number of elements
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemset
 */
HUresult HIPAPI huMemsetD16(HUdeviceptr dstDevice, unsigned short us, size_t N);

/**
 * \brief Initializes device memory
 *
 * Sets the memory range of \p N 32-bit values to the specified value
 * \p ui. The \p dstDevice pointer must be four byte aligned.
 *
 * \param dstDevice - Destination device pointer
 * \param ui        - Value to set
 * \param N         - Number of elements
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32Async,
 * ::hipMemset
 */
HUresult HIPAPI huMemsetD32(HUdeviceptr dstDevice, unsigned int ui, size_t N);

/**
 * \brief Initializes device memory
 *
 * Sets the 2D memory range of \p Width 8-bit values to the specified value
 * \p uc. \p Height specifies the number of rows to set, and \p dstPitch
 * specifies the number of bytes between each row. This function performs
 * fastest when the pitch is one that has been passed back by
 * ::huMemAllocPitch().
 *
 * \param dstDevice - Destination device pointer
 * \param dstPitch  - Pitch of destination device pointer
 * \param uc        - Value to set
 * \param Width     - Width of row
 * \param Height    - Number of rows
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemset2D
 */
HUresult HIPAPI huMemsetD2D8(HUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height);

/**
 * \brief Initializes device memory
 *
 * Sets the 2D memory range of \p Width 16-bit values to the specified value
 * \p us. \p Height specifies the number of rows to set, and \p dstPitch
 * specifies the number of bytes between each row. The \p dstDevice pointer
 * and \p dstPitch offset must be two byte aligned. This function performs
 * fastest when the pitch is one that has been passed back by
 * ::huMemAllocPitch().
 *
 * \param dstDevice - Destination device pointer
 * \param dstPitch  - Pitch of destination device pointer
 * \param us        - Value to set
 * \param Width     - Width of row
 * \param Height    - Number of rows
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemset2D
 */
HUresult HIPAPI huMemsetD2D16(HUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height);

/**
 * \brief Initializes device memory
 *
 * Sets the 2D memory range of \p Width 32-bit values to the specified value
 * \p ui. \p Height specifies the number of rows to set, and \p dstPitch
 * specifies the number of bytes between each row. The \p dstDevice pointer
 * and \p dstPitch offset must be four byte aligned. This function performs
 * fastest when the pitch is one that has been passed back by
 * ::huMemAllocPitch().
 *
 * \param dstDevice - Destination device pointer
 * \param dstPitch  - Pitch of destination device pointer
 * \param ui        - Value to set
 * \param Width     - Width of row
 * \param Height    - Number of rows
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemset2D
 */
HUresult HIPAPI huMemsetD2D32(HUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height);

/**
 * \brief Sets device memory
 *
 * Sets the memory range of \p N 8-bit values to the specified value
 * \p uc.
 *
 * \param dstDevice - Destination device pointer
 * \param uc        - Value to set
 * \param N         - Number of elements
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemsetAsync
 */
HUresult HIPAPI huMemsetD8Async(HUdeviceptr dstDevice, unsigned char uc, size_t N, HUstream hStream);

/**
 * \brief Sets device memory
 *
 * Sets the memory range of \p N 16-bit values to the specified value
 * \p us. The \p dstDevice pointer must be two byte aligned.
 *
 * \param dstDevice - Destination device pointer
 * \param us        - Value to set
 * \param N         - Number of elements
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemsetAsync
 */
HUresult HIPAPI huMemsetD16Async(HUdeviceptr dstDevice, unsigned short us, size_t N, HUstream hStream);

/**
 * \brief Sets device memory
 *
 * Sets the memory range of \p N 32-bit values to the specified value
 * \p ui. The \p dstDevice pointer must be four byte aligned.
 *
 * \param dstDevice - Destination device pointer
 * \param ui        - Value to set
 * \param N         - Number of elements
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async, ::huMemsetD32,
 * ::hipMemsetAsync
 */
HUresult HIPAPI huMemsetD32Async(HUdeviceptr dstDevice, unsigned int ui, size_t N, HUstream hStream);

/**
 * \brief Sets device memory
 *
 * Sets the 2D memory range of \p Width 8-bit values to the specified value
 * \p uc. \p Height specifies the number of rows to set, and \p dstPitch
 * specifies the number of bytes between each row. This function performs
 * fastest when the pitch is one that has been passed back by
 * ::huMemAllocPitch().
 *
 * \param dstDevice - Destination device pointer
 * \param dstPitch  - Pitch of destination device pointer
 * \param uc        - Value to set
 * \param Width     - Width of row
 * \param Height    - Number of rows
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemset2DAsync
 */
HUresult HIPAPI huMemsetD2D8Async(HUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, HUstream hStream);

/**
 * \brief Sets device memory
 *
 * Sets the 2D memory range of \p Width 16-bit values to the specified value
 * \p us. \p Height specifies the number of rows to set, and \p dstPitch
 * specifies the number of bytes between each row. The \p dstDevice pointer 
 * and \p dstPitch offset must be two byte aligned. This function performs
 * fastest when the pitch is one that has been passed back by
 * ::huMemAllocPitch().
 *
 * \param dstDevice - Destination device pointer
 * \param dstPitch  - Pitch of destination device pointer
 * \param us        - Value to set
 * \param Width     - Width of row
 * \param Height    - Number of rows
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D32, ::huMemsetD2D32Async,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemset2DAsync
 */
HUresult HIPAPI huMemsetD2D16Async(HUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, HUstream hStream);

/**
 * \brief Sets device memory
 *
 * Sets the 2D memory range of \p Width 32-bit values to the specified value
 * \p ui. \p Height specifies the number of rows to set, and \p dstPitch
 * specifies the number of bytes between each row. The \p dstDevice pointer
 * and \p dstPitch offset must be four byte aligned. This function performs
 * fastest when the pitch is one that has been passed back by
 * ::huMemAllocPitch().
 *
 * \param dstDevice - Destination device pointer
 * \param dstPitch  - Pitch of destination device pointer
 * \param ui        - Value to set
 * \param Width     - Width of row
 * \param Height    - Number of rows
 * \param hStream   - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 * \note_memset
 * \note_null_stream
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D8Async,
 * ::huMemsetD2D16, ::huMemsetD2D16Async, ::huMemsetD2D32,
 * ::huMemsetD8, ::huMemsetD8Async, ::huMemsetD16, ::huMemsetD16Async,
 * ::huMemsetD32, ::huMemsetD32Async,
 * ::hipMemset2DAsync
 */
HUresult HIPAPI huMemsetD2D32Async(HUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, HUstream hStream);

/**
 * \brief Creates a 1D or 2D HIP array
 *
 * Creates a HIP array according to the ::HIP_ARRAY_DESCRIPTOR structure
 * \p pAllocateArray and returns a handle to the new HIP array in \p *pHandle.
 * The ::HIP_ARRAY_DESCRIPTOR is defined as:
 *
 * \code
    typedef struct {
        unsigned int Width;
        unsigned int Height;
        HUarray_format Format;
        unsigned int NumChannels;
    } HIP_ARRAY_DESCRIPTOR;
 * \endcode
 * where:
 *
 * - \p Width, and \p Height are the width, and height of the HIP array (in
 * elements); the HIP array is one-dimensional if height is 0, two-dimensional
 * otherwise;
 * - ::Format specifies the format of the elements; ::HUarray_format is
 * defined as:
 * \code
    typedef enum HUarray_format_enum {
        HU_AD_FORMAT_UNSIGNED_INT8 = 0x01,
        HU_AD_FORMAT_UNSIGNED_INT16 = 0x02,
        HU_AD_FORMAT_UNSIGNED_INT32 = 0x03,
        HU_AD_FORMAT_SIGNED_INT8 = 0x08,
        HU_AD_FORMAT_SIGNED_INT16 = 0x09,
        HU_AD_FORMAT_SIGNED_INT32 = 0x0a,
        HU_AD_FORMAT_HALF = 0x10,
        HU_AD_FORMAT_FLOAT = 0x20
    } HUarray_format;
 *  \endcode
 * - \p NumChannels specifies the number of packed components per HIP array
 * element; it may be 1, 2, or 4;
 *
 * Here are examples of HIP array descriptions:
 *
 * Description for a HIP array of 2048 floats:
 * \code
    HIP_ARRAY_DESCRIPTOR desc;
    desc.Format = HU_AD_FORMAT_FLOAT;
    desc.NumChannels = 1;
    desc.Width = 2048;
    desc.Height = 1;
 * \endcode
 *
 * Description for a 64 x 64 HIP array of floats:
 * \code
    HIP_ARRAY_DESCRIPTOR desc;
    desc.Format = HU_AD_FORMAT_FLOAT;
    desc.NumChannels = 1;
    desc.Width = 64;
    desc.Height = 64;
 * \endcode
 *
 * Description for a \p width x \p height HIP array of 64-bit, 4x16-bit
 * float16's:
 * \code
    HIP_ARRAY_DESCRIPTOR desc;
    desc.FormatFlags = HU_AD_FORMAT_HALF;
    desc.NumChannels = 4;
    desc.Width = width;
    desc.Height = height;
 * \endcode
 *
 * Description for a \p width x \p height HIP array of 16-bit elements, each
 * of which is two 8-bit unsigned chars:
 * \code
    HIP_ARRAY_DESCRIPTOR arrayDesc;
    desc.FormatFlags = HU_AD_FORMAT_UNSIGNED_INT8;
    desc.NumChannels = 2;
    desc.Width = width;
    desc.Height = height;
 * \endcode
 *
 * \param pHandle        - Returned array
 * \param pAllocateArray - Array descriptor
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMallocArray
 */
HUresult HIPAPI huArrayCreate(HUarray *pHandle, const HIP_ARRAY_DESCRIPTOR *pAllocateArray);

/**
 * \brief Get a 1D or 2D HIP array descriptor
 *
 * Returns in \p *pArrayDescriptor a descriptor containing information on the
 * format and dimensions of the HIP array \p hArray. It is useful for
 * subroutines that have been passed a HIP array, but need to know the HIP
 * array parameters for validation or other purposes.
 *
 * \param pArrayDescriptor - Returned array descriptor
 * \param hArray           - Array to get descriptor of
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_HANDLE
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipArrayGetInfo
 */
HUresult HIPAPI huArrayGetDescriptor(HIP_ARRAY_DESCRIPTOR *pArrayDescriptor, HUarray hArray);

/**
 * \brief Destroys a HIP array
 *
 * Destroys the HIP array \p hArray.
 *
 * \param hArray - Array to destroy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_ARRAY_IS_MAPPED
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipFreeArray
 */
HUresult HIPAPI huArrayDestroy(HUarray hArray);

/**
 * \brief Creates a 3D HIP array
 *
 * Creates a HIP array according to the ::HIP_ARRAY3D_DESCRIPTOR structure
 * \p pAllocateArray and returns a handle to the new HIP array in \p *pHandle.
 * The ::HIP_ARRAY3D_DESCRIPTOR is defined as:
 *
 * \code
    typedef struct {
        unsigned int Width;
        unsigned int Height;
        unsigned int Depth;
        HUarray_format Format;
        unsigned int NumChannels;
        unsigned int Flags;
    } HIP_ARRAY3D_DESCRIPTOR;
 * \endcode
 * where:
 *
 * - \p Width, \p Height, and \p Depth are the width, height, and depth of the
 * HIP array (in elements); the following types of HIP arrays can be allocated:
 *     - A 1D array is allocated if \p Height and \p Depth extents are both zero.
 *     - A 2D array is allocated if only \p Depth extent is zero.
 *     - A 3D array is allocated if all three extents are non-zero.
 *     - A 1D layered HIP array is allocated if only \p Height is zero and the 
 *       ::HIP_ARRAY3D_LAYERED flag is set. Each layer is a 1D array. The number 
 *       of layers is determined by the depth extent.
 *     - A 2D layered HIP array is allocated if all three extents are non-zero and 
 *       the ::HIP_ARRAY3D_LAYERED flag is set. Each layer is a 2D array. The number 
 *       of layers is determined by the depth extent.
 *     - A hubemap HIP array is allocated if all three extents are non-zero and the
 *       ::HIP_ARRAY3D_CUBEMAP flag is set. \p Width must be equal to \p Height, and 
 *       \p Depth must be six. A hubemap is a special type of 2D layered HIP array, 
 *       where the six layers represent the six faces of a hube. The order of the six 
 *       layers in memory is the same as that listed in ::HUarray_cubemap_face.
 *     - A hubemap layered HIP array is allocated if all three extents are non-zero, 
 *       and both, ::HIP_ARRAY3D_CUBEMAP and ::HIP_ARRAY3D_LAYERED flags are set. 
 *       \p Width must be equal to \p Height, and \p Depth must be a multiple of six. 
 *       A hubemap layered HIP array is a special type of 2D layered HIP array that 
 *       consists of a collection of hubemaps. The first six layers represent the first 
 *       hubemap, the next six layers form the second hubemap, and so on.
 *
 * - ::Format specifies the format of the elements; ::HUarray_format is
 * defined as:
 * \code
    typedef enum HUarray_format_enum {
        HU_AD_FORMAT_UNSIGNED_INT8 = 0x01,
        HU_AD_FORMAT_UNSIGNED_INT16 = 0x02,
        HU_AD_FORMAT_UNSIGNED_INT32 = 0x03,
        HU_AD_FORMAT_SIGNED_INT8 = 0x08,
        HU_AD_FORMAT_SIGNED_INT16 = 0x09,
        HU_AD_FORMAT_SIGNED_INT32 = 0x0a,
        HU_AD_FORMAT_HALF = 0x10,
        HU_AD_FORMAT_FLOAT = 0x20
    } HUarray_format;
 *  \endcode
 *
 * - \p NumChannels specifies the number of packed components per HIP array
 * element; it may be 1, 2, or 4;
 *
 * - ::Flags may be set to 
 *   - ::HIP_ARRAY3D_LAYERED to enable creation of layered HIP arrays. If this flag is set, 
 *     \p Depth specifies the number of layers, not the depth of a 3D array.
 *   - ::HIP_ARRAY3D_SURFACE_LDST to enable surface references to be bound to the HIP array.  
 *     If this flag is not set, ::huSurfRefSetArray will fail when attempting to bind the HIP array 
 *     to a surface reference.
 *   - ::HIP_ARRAY3D_CUBEMAP to enable creation of hubemaps. If this flag is set, \p Width must be
 *     equal to \p Height, and \p Depth must be six. If the ::HIP_ARRAY3D_LAYERED flag is also set,
 *     then \p Depth must be a multiple of six.
 *   - ::HIP_ARRAY3D_TEXTURE_GATHER to indicate that the HIP array will be used for texture gather.
 *     Texture gather can only be performed on 2D HIP arrays.
 *
 * \p Width, \p Height and \p Depth must meet certain size requirements as listed in the following table. 
 * All values are specified in elements. Note that for brevity's sake, the full name of the device attribute 
 * is not specified. For ex., TEXTURE1D_WIDTH refers to the device attribute 
 * ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_WIDTH.
 *
 * Note that 2D HIP arrays have different size requirements if the ::HIP_ARRAY3D_TEXTURE_GATHER flag 
 * is set. \p Width and \p Height must not be greater than ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_WIDTH 
 * and ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_HEIGHT respectively, in that case.
 *
 * <table>
 * <tr><td><b>HIP array type</b></td>
 * <td><b>Valid extents that must always be met<br>{(width range in elements), (height range), 
 * (depth range)}</b></td>
 * <td><b>Valid extents with HIP_ARRAY3D_SURFACE_LDST set<br> 
 * {(width range in elements), (height range), (depth range)}</b></td></tr>
 * <tr><td>1D</td>
 * <td><small>{ (1,TEXTURE1D_WIDTH), 0, 0 }</small></td>
 * <td><small>{ (1,SURFACE1D_WIDTH), 0, 0 }</small></td></tr>
 * <tr><td>2D</td>
 * <td><small>{ (1,TEXTURE2D_WIDTH), (1,TEXTURE2D_HEIGHT), 0 }</small></td>
 * <td><small>{ (1,SURFACE2D_WIDTH), (1,SURFACE2D_HEIGHT), 0 }</small></td></tr>
 * <tr><td>3D</td>
 * <td><small>{ (1,TEXTURE3D_WIDTH), (1,TEXTURE3D_HEIGHT), (1,TEXTURE3D_DEPTH) }
 * <br>OR<br>{ (1,TEXTURE3D_WIDTH_ALTERNATE), (1,TEXTURE3D_HEIGHT_ALTERNATE), 
 * (1,TEXTURE3D_DEPTH_ALTERNATE) }</small></td>
 * <td><small>{ (1,SURFACE3D_WIDTH), (1,SURFACE3D_HEIGHT), 
 * (1,SURFACE3D_DEPTH) }</small></td></tr>
 * <tr><td>1D Layered</td>
 * <td><small>{ (1,TEXTURE1D_LAYERED_WIDTH), 0, 
 * (1,TEXTURE1D_LAYERED_LAYERS) }</small></td>
 * <td><small>{ (1,SURFACE1D_LAYERED_WIDTH), 0, 
 * (1,SURFACE1D_LAYERED_LAYERS) }</small></td></tr>
 * <tr><td>2D Layered</td>
 * <td><small>{ (1,TEXTURE2D_LAYERED_WIDTH), (1,TEXTURE2D_LAYERED_HEIGHT), 
 * (1,TEXTURE2D_LAYERED_LAYERS) }</small></td>
 * <td><small>{ (1,SURFACE2D_LAYERED_WIDTH), (1,SURFACE2D_LAYERED_HEIGHT), 
 * (1,SURFACE2D_LAYERED_LAYERS) }</small></td></tr>
 * <tr><td>Cubemap</td>
 * <td><small>{ (1,TEXTURECUBEMAP_WIDTH), (1,TEXTURECUBEMAP_WIDTH), 6 }</small></td>
 * <td><small>{ (1,SURFACECUBEMAP_WIDTH), 
 * (1,SURFACECUBEMAP_WIDTH), 6 }</small></td></tr>
 * <tr><td>Cubemap Layered</td>
 * <td><small>{ (1,TEXTURECUBEMAP_LAYERED_WIDTH), (1,TEXTURECUBEMAP_LAYERED_WIDTH), 
 * (1,TEXTURECUBEMAP_LAYERED_LAYERS) }</small></td>
 * <td><small>{ (1,SURFACECUBEMAP_LAYERED_WIDTH), (1,SURFACECUBEMAP_LAYERED_WIDTH), 
 * (1,SURFACECUBEMAP_LAYERED_LAYERS) }</small></td></tr>
 * </table>
 *
 * Here are examples of HIP array descriptions:
 *
 * Description for a HIP array of 2048 floats:
 * \code
    HIP_ARRAY3D_DESCRIPTOR desc;
    desc.Format = HU_AD_FORMAT_FLOAT;
    desc.NumChannels = 1;
    desc.Width = 2048;
    desc.Height = 0;
    desc.Depth = 0;
 * \endcode
 *
 * Description for a 64 x 64 HIP array of floats:
 * \code
    HIP_ARRAY3D_DESCRIPTOR desc;
    desc.Format = HU_AD_FORMAT_FLOAT;
    desc.NumChannels = 1;
    desc.Width = 64;
    desc.Height = 64;
    desc.Depth = 0;
 * \endcode
 *
 * Description for a \p width x \p height x \p depth HIP array of 64-bit,
 * 4x16-bit float16's:
 * \code
    HIP_ARRAY3D_DESCRIPTOR desc;
    desc.FormatFlags = HU_AD_FORMAT_HALF;
    desc.NumChannels = 4;
    desc.Width = width;
    desc.Height = height;
    desc.Depth = depth;
 * \endcode
 *
 * \param pHandle        - Returned array
 * \param pAllocateArray - 3D array descriptor
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa ::huArray3DGetDescriptor, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipMalloc3DArray
 */
HUresult HIPAPI huArray3DCreate(HUarray *pHandle, const HIP_ARRAY3D_DESCRIPTOR *pAllocateArray);

/**
 * \brief Get a 3D HIP array descriptor
 *
 * Returns in \p *pArrayDescriptor a descriptor containing information on the
 * format and dimensions of the HIP array \p hArray. It is useful for
 * subroutines that have been passed a HIP array, but need to know the HIP
 * array parameters for validation or other purposes.
 *
 * This function may be called on 1D and 2D arrays, in which case the \p Height
 * and/or \p Depth members of the descriptor struct will be set to 0.
 *
 * \param pArrayDescriptor - Returned 3D array descriptor
 * \param hArray           - 3D array to get descriptor of
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_HANDLE
 * \notefnerr
 *
 * \sa ::huArray3DCreate, ::huArrayCreate,
 * ::huArrayDestroy, ::huArrayGetDescriptor, ::huMemAlloc, ::huMemAllocHost,
 * ::huMemAllocPitch, ::huMemcpy2D, ::huMemcpy2DAsync, ::huMemcpy2DUnaligned,
 * ::huMemcpy3D, ::huMemcpy3DAsync, ::huMemcpyAtoA, ::huMemcpyAtoD,
 * ::huMemcpyAtoH, ::huMemcpyAtoHAsync, ::huMemcpyDtoA, ::huMemcpyDtoD, ::huMemcpyDtoDAsync,
 * ::huMemcpyDtoH, ::huMemcpyDtoHAsync, ::huMemcpyHtoA, ::huMemcpyHtoAAsync,
 * ::huMemcpyHtoD, ::huMemcpyHtoDAsync, ::huMemFree, ::huMemFreeHost,
 * ::huMemGetAddressRange, ::huMemGetInfo, ::huMemHostAlloc,
 * ::huMemHostGetDevicePointer, ::huMemsetD2D8, ::huMemsetD2D16,
 * ::huMemsetD2D32, ::huMemsetD8, ::huMemsetD16, ::huMemsetD32,
 * ::hipArrayGetInfo
 */
HUresult HIPAPI huArray3DGetDescriptor(HIP_ARRAY3D_DESCRIPTOR *pArrayDescriptor, HUarray hArray);

/**
 * \brief Creates a HIP mipmapped array
 *
 * Creates a HIP mipmapped array according to the ::HIP_ARRAY3D_DESCRIPTOR structure
 * \p pMipmappedArrayDesc and returns a handle to the new HIP mipmapped array in \p *pHandle.
 * \p numMipmapLevels specifies the number of mipmap levels to be allocated. This value is
 * clamped to the range [1, 1 + floor(log2(max(width, height, depth)))].
 *
 * The ::HIP_ARRAY3D_DESCRIPTOR is defined as:
 *
 * \code
    typedef struct {
        unsigned int Width;
        unsigned int Height;
        unsigned int Depth;
        HUarray_format Format;
        unsigned int NumChannels;
        unsigned int Flags;
    } HIP_ARRAY3D_DESCRIPTOR;
 * \endcode
 * where:
 *
 * - \p Width, \p Height, and \p Depth are the width, height, and depth of the
 * HIP array (in elements); the following types of HIP arrays can be allocated:
 *     - A 1D mipmapped array is allocated if \p Height and \p Depth extents are both zero.
 *     - A 2D mipmapped array is allocated if only \p Depth extent is zero.
 *     - A 3D mipmapped array is allocated if all three extents are non-zero.
 *     - A 1D layered HIP mipmapped array is allocated if only \p Height is zero and the 
 *       ::HIP_ARRAY3D_LAYERED flag is set. Each layer is a 1D array. The number 
 *       of layers is determined by the depth extent.
 *     - A 2D layered HIP mipmapped array is allocated if all three extents are non-zero and 
 *       the ::HIP_ARRAY3D_LAYERED flag is set. Each layer is a 2D array. The number 
 *       of layers is determined by the depth extent.
 *     - A hubemap HIP mipmapped array is allocated if all three extents are non-zero and the
 *       ::HIP_ARRAY3D_CUBEMAP flag is set. \p Width must be equal to \p Height, and 
 *       \p Depth must be six. A hubemap is a special type of 2D layered HIP array, 
 *       where the six layers represent the six faces of a hube. The order of the six 
 *       layers in memory is the same as that listed in ::HUarray_cubemap_face.
 *     - A hubemap layered HIP mipmapped array is allocated if all three extents are non-zero, 
 *       and both, ::HIP_ARRAY3D_CUBEMAP and ::HIP_ARRAY3D_LAYERED flags are set. 
 *       \p Width must be equal to \p Height, and \p Depth must be a multiple of six. 
 *       A hubemap layered HIP array is a special type of 2D layered HIP array that 
 *       consists of a collection of hubemaps. The first six layers represent the first 
 *       hubemap, the next six layers form the second hubemap, and so on.
 *
 * - ::Format specifies the format of the elements; ::HUarray_format is
 * defined as:
 * \code
    typedef enum HUarray_format_enum {
        HU_AD_FORMAT_UNSIGNED_INT8 = 0x01,
        HU_AD_FORMAT_UNSIGNED_INT16 = 0x02,
        HU_AD_FORMAT_UNSIGNED_INT32 = 0x03,
        HU_AD_FORMAT_SIGNED_INT8 = 0x08,
        HU_AD_FORMAT_SIGNED_INT16 = 0x09,
        HU_AD_FORMAT_SIGNED_INT32 = 0x0a,
        HU_AD_FORMAT_HALF = 0x10,
        HU_AD_FORMAT_FLOAT = 0x20
    } HUarray_format;
 *  \endcode
 *
 * - \p NumChannels specifies the number of packed components per HIP array
 * element; it may be 1, 2, or 4;
 *
 * - ::Flags may be set to 
 *   - ::HIP_ARRAY3D_LAYERED to enable creation of layered HIP mipmapped arrays. If this flag is set, 
 *     \p Depth specifies the number of layers, not the depth of a 3D array.
 *   - ::HIP_ARRAY3D_SURFACE_LDST to enable surface references to be bound to individual mipmap levels of
 *     the HIP mipmapped array. If this flag is not set, ::huSurfRefSetArray will fail when attempting to 
 *     bind a mipmap level of the HIP mipmapped array to a surface reference.
  *   - ::HIP_ARRAY3D_CUBEMAP to enable creation of mipmapped hubemaps. If this flag is set, \p Width must be
 *     equal to \p Height, and \p Depth must be six. If the ::HIP_ARRAY3D_LAYERED flag is also set,
 *     then \p Depth must be a multiple of six.
 *   - ::HIP_ARRAY3D_TEXTURE_GATHER to indicate that the HIP mipmapped array will be used for texture gather.
 *     Texture gather can only be performed on 2D HIP mipmapped arrays.
 *
 * \p Width, \p Height and \p Depth must meet certain size requirements as listed in the following table. 
 * All values are specified in elements. Note that for brevity's sake, the full name of the device attribute 
 * is not specified. For ex., TEXTURE1D_MIPMAPPED_WIDTH refers to the device attribute 
 * ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_MIPMAPPED_WIDTH.
 *
 * <table>
 * <tr><td><b>HIP array type</b></td>
 * <td><b>Valid extents that must always be met<br>{(width range in elements), (height range), 
 * (depth range)}</b></td>
 * <td><b>Valid extents with HIP_ARRAY3D_SURFACE_LDST set<br> 
 * {(width range in elements), (height range), (depth range)}</b></td></tr>
 * <tr><td>1D</td>
 * <td><small>{ (1,TEXTURE1D_MIPMAPPED_WIDTH), 0, 0 }</small></td>
 * <td><small>{ (1,SURFACE1D_WIDTH), 0, 0 }</small></td></tr>
 * <tr><td>2D</td>
 * <td><small>{ (1,TEXTURE2D_MIPMAPPED_WIDTH), (1,TEXTURE2D_MIPMAPPED_HEIGHT), 0 }</small></td>
 * <td><small>{ (1,SURFACE2D_WIDTH), (1,SURFACE2D_HEIGHT), 0 }</small></td></tr>
 * <tr><td>3D</td>
 * <td><small>{ (1,TEXTURE3D_WIDTH), (1,TEXTURE3D_HEIGHT), (1,TEXTURE3D_DEPTH) }
 * <br>OR<br>{ (1,TEXTURE3D_WIDTH_ALTERNATE), (1,TEXTURE3D_HEIGHT_ALTERNATE), 
 * (1,TEXTURE3D_DEPTH_ALTERNATE) }</small></td>
 * <td><small>{ (1,SURFACE3D_WIDTH), (1,SURFACE3D_HEIGHT), 
 * (1,SURFACE3D_DEPTH) }</small></td></tr>
 * <tr><td>1D Layered</td>
 * <td><small>{ (1,TEXTURE1D_LAYERED_WIDTH), 0, 
 * (1,TEXTURE1D_LAYERED_LAYERS) }</small></td>
 * <td><small>{ (1,SURFACE1D_LAYERED_WIDTH), 0, 
 * (1,SURFACE1D_LAYERED_LAYERS) }</small></td></tr>
 * <tr><td>2D Layered</td>
 * <td><small>{ (1,TEXTURE2D_LAYERED_WIDTH), (1,TEXTURE2D_LAYERED_HEIGHT), 
 * (1,TEXTURE2D_LAYERED_LAYERS) }</small></td>
 * <td><small>{ (1,SURFACE2D_LAYERED_WIDTH), (1,SURFACE2D_LAYERED_HEIGHT), 
 * (1,SURFACE2D_LAYERED_LAYERS) }</small></td></tr>
 * <tr><td>Cubemap</td>
 * <td><small>{ (1,TEXTURECUBEMAP_WIDTH), (1,TEXTURECUBEMAP_WIDTH), 6 }</small></td>
 * <td><small>{ (1,SURFACECUBEMAP_WIDTH), 
 * (1,SURFACECUBEMAP_WIDTH), 6 }</small></td></tr>
 * <tr><td>Cubemap Layered</td>
 * <td><small>{ (1,TEXTURECUBEMAP_LAYERED_WIDTH), (1,TEXTURECUBEMAP_LAYERED_WIDTH), 
 * (1,TEXTURECUBEMAP_LAYERED_LAYERS) }</small></td>
 * <td><small>{ (1,SURFACECUBEMAP_LAYERED_WIDTH), (1,SURFACECUBEMAP_LAYERED_WIDTH), 
 * (1,SURFACECUBEMAP_LAYERED_LAYERS) }</small></td></tr>
 * </table>
 *
 *
 * \param pHandle             - Returned mipmapped array
 * \param pMipmappedArrayDesc - mipmapped array descriptor
 * \param numMipmapLevels     - Number of mipmap levels
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa
 * ::huMipmappedArrayDestroy,
 * ::huMipmappedArrayGetLevel,
 * ::huArrayCreate,
 * ::hipMallocMipmappedArray
 */
HUresult HIPAPI huMipmappedArrayCreate(HUmipmappedArray *pHandle, const HIP_ARRAY3D_DESCRIPTOR *pMipmappedArrayDesc, unsigned int numMipmapLevels);

/**
 * \brief Gets a mipmap level of a HIP mipmapped array
 *
 * Returns in \p *pLevelArray a HIP array that represents a single mipmap level
 * of the HIP mipmapped array \p hMipmappedArray.
 *
 * If \p level is greater than the maximum number of levels in this mipmapped array,
 * ::HIP_ERROR_INVALID_VALUE is returned.
 *
 * \param pLevelArray     - Returned mipmap level HIP array
 * \param hMipmappedArray - HIP mipmapped array
 * \param level           - Mipmap level
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_HANDLE
 * \notefnerr
 *
 * \sa
 * ::huMipmappedArrayCreate,
 * ::huMipmappedArrayDestroy,
 * ::huArrayCreate,
 * ::hipGetMipmappedArrayLevel
 */
HUresult HIPAPI huMipmappedArrayGetLevel(HUarray *pLevelArray, HUmipmappedArray hMipmappedArray, unsigned int level);

/**
 * \brief Destroys a HIP mipmapped array
 *
 * Destroys the HIP mipmapped array \p hMipmappedArray.
 *
 * \param hMipmappedArray - Mipmapped array to destroy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_ARRAY_IS_MAPPED
 * \notefnerr
 *
 * \sa
 * ::huMipmappedArrayCreate,
 * ::huMipmappedArrayGetLevel,
 * ::huArrayCreate,
 * ::hipFreeMipmappedArray
 */
HUresult HIPAPI huMipmappedArrayDestroy(HUmipmappedArray hMipmappedArray);

/** @} */ /* END HIP_MEM */

/**
 * \defgroup HIP_UNIFIED Unified Addressing
 *
 * ___MANBRIEF___ unified addressing functions of the low-level HIP driver
 * API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the unified addressing functions of the 
 * low-level HIP driver application programming interface.
 *
 * @{
 *
 * \section HIP_UNIFIED_overview Overview
 *
 * HIP devices can share a unified address space with the host.  
 * For these devices there is no distinction between a device
 * pointer and a host pointer -- the same pointer value may be 
 * used to access memory from the host program and from a kernel 
 * running on the device (with exceptions enumerated below).
 *
 * \section HIP_UNIFIED_support Supported Platforms
 * 
 * Whether or not a device supports unified addressing may be 
 * queried by calling ::huDeviceGetAttribute() with the device 
 * attribute ::HU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING.
 *
 * Unified addressing is automatically enabled in 64-bit processes 
 *
 * \section HIP_UNIFIED_lookup Looking Up Information from Pointer Values
 *
 * It is possible to look up information about the memory which backs a 
 * pointer value.  For instance, one may want to know if a pointer points
 * to host or device memory.  As another example, in the case of device 
 * memory, one may want to know on which HIP device the memory 
 * resides.  These properties may be queried using the function 
 * ::huPointerGetAttribute()
 *
 * Since pointers are unique, it is not necessary to specify information
 * about the pointers specified to the various copy functions in the 
 * HIP API.  The function ::huMemcpy() may be used to perform a copy
 * between two pointers, ignoring whether they point to host or device
 * memory (making ::huMemcpyHtoD(), ::huMemcpyDtoD(), and ::huMemcpyDtoH()
 * unnecessary for devices supporting unified addressing).  For 
 * multidimensional copies, the memory type ::HU_MEMORYTYPE_UNIFIED may be
 * used to specify that the HIP driver should infer the location of the
 * pointer from its value.
 *
 * \section HIP_UNIFIED_automaphost Automatic Mapping of Host Allocated Host Memory
 *
 * All host memory allocated in all contexts using ::huMemAllocHost() and
 * ::huMemHostAlloc() is always directly accessible from all contexts on
 * all devices that support unified addressing.  This is the case regardless 
 * of whether or not the flags ::HU_MEMHOSTALLOC_PORTABLE and
 * ::HU_MEMHOSTALLOC_DEVICEMAP are specified.
 *
 * The pointer value through which allocated host memory may be accessed 
 * in kernels on all devices that support unified addressing is the same 
 * as the pointer value through which that memory is accessed on the host,
 * so it is not necessary to call ::huMemHostGetDevicePointer() to get the device 
 * pointer for these allocations.
 * 
 * Note that this is not the case for memory allocated using the flag
 * ::HU_MEMHOSTALLOC_WRITECOMBINED, as discussed below.
 *
 * \section HIP_UNIFIED_autopeerregister Automatic Registration of Peer Memory
 *
 * Upon enabling direct access from a context that supports unified addressing 
 * to another peer context that supports unified addressing using 
 * ::huCtxEnablePeerAccess() all memory allocated in the peer context using 
 * ::huMemAlloc() and ::huMemAllocPitch() will immediately be accessible 
 * by the current context.  The device pointer value through
 * which any peer memory may be accessed in the current context
 * is the same pointer value through which that memory may be
 * accessed in the peer context.
 *
 * \section HIP_UNIFIED_exceptions Exceptions, Disjoint Addressing
 * 
 * Not all memory may be accessed on devices through the same pointer
 * value through which they are accessed on the host.  These exceptions
 * are host memory registered using ::huMemHostRegister() and host memory
 * allocated using the flag ::HU_MEMHOSTALLOC_WRITECOMBINED.  For these 
 * exceptions, there exists a distinct host and device address for the
 * memory.  The device address is guaranteed to not overlap any valid host
 * pointer range and is guaranteed to have the same value across all 
 * contexts that support unified addressing.  
 * 
 * This device address may be queried using ::huMemHostGetDevicePointer() 
 * when a context using unified addressing is current.  Either the host 
 * or the unified device pointer value may be used to refer to this memory 
 * through ::huMemcpy() and similar functions using the 
 * ::HU_MEMORYTYPE_UNIFIED memory type.
 *
 */

/**
 * \brief Returns information about a pointer
 * 
 * The supported attributes are:
 * 
 * - ::HU_POINTER_ATTRIBUTE_CONTEXT: 
 * 
 *      Returns in \p *data the ::HUcontext in which \p ptr was allocated or 
 *      registered.   
 *      The type of \p data must be ::HUcontext *.  
 *      
 *      If \p ptr was not allocated by, mapped by, or registered with
 *      a ::HUcontext which uses unified virtual addressing then 
 *      ::HIP_ERROR_INVALID_VALUE is returned.
 * 
 * - ::HU_POINTER_ATTRIBUTE_MEMORY_TYPE: 
 *    
 *      Returns in \p *data the physical memory type of the memory that 
 *      \p ptr addresses as a ::HUmemorytype enumerated value.
 *      The type of \p data must be unsigned int.
 *      
 *      If \p ptr addresses device memory then \p *data is set to 
 *      ::HU_MEMORYTYPE_DEVICE.  The particular ::HUdevice on which the 
 *      memory resides is the ::HUdevice of the ::HUcontext returned by the 
 *      ::HU_POINTER_ATTRIBUTE_CONTEXT attribute of \p ptr.
 *      
 *      If \p ptr addresses host memory then \p *data is set to 
 *      ::HU_MEMORYTYPE_HOST.
 *      
 *      If \p ptr was not allocated by, mapped by, or registered with
 *      a ::HUcontext which uses unified virtual addressing then 
 *      ::HIP_ERROR_INVALID_VALUE is returned.
 *
 *      If the current ::HUcontext does not support unified virtual 
 *      addressing then ::HIP_ERROR_INVALID_CONTEXT is returned.
 *    
 * - ::HU_POINTER_ATTRIBUTE_DEVICE_POINTER:
 * 
 *      Returns in \p *data the device pointer value through which
 *      \p ptr may be accessed by kernels running in the current 
 *      ::HUcontext.
 *      The type of \p data must be HUdeviceptr *.
 * 
 *      If there exists no device pointer value through which
 *      kernels running in the current ::HUcontext may access
 *      \p ptr then ::HIP_ERROR_INVALID_VALUE is returned.
 * 
 *      If there is no current ::HUcontext then 
 *      ::HIP_ERROR_INVALID_CONTEXT is returned.
 *      
 *      Except in the exceptional disjoint addressing cases discussed 
 *      below, the value returned in \p *data will equal the input 
 *      value \p ptr.
 * 
 * - ::HU_POINTER_ATTRIBUTE_HOST_POINTER:
 * 
 *      Returns in \p *data the host pointer value through which 
 *      \p ptr may be accessed by by the host program.
 *      The type of \p data must be void **.
 *      If there exists no host pointer value through which
 *      the host program may directly access \p ptr then 
 *      ::HIP_ERROR_INVALID_VALUE is returned.
 * 
 *      Except in the exceptional disjoint addressing cases discussed 
 *      below, the value returned in \p *data will equal the input 
 *      value \p ptr.
 *
 * - ::HU_POINTER_ATTRIBUTE_P2P_TOKENS:
 *
 *      Returns in \p *data two tokens for use with the nv-p2p.h Linux
 *      kernel interface. \p data must be a struct of type
 *      HIP_POINTER_ATTRIBUTE_P2P_TOKENS.
 *
 *      \p ptr must be a pointer to memory obtained from :cuMemAlloc().
 *      Note that p2pToken and vaSpaceToken are only valid for the
 *      lifetime of the source allocation. A subsequent allocation at
 *      the same address may return completely different tokens.
 *      Querying this attribute has a side effect of setting the attribute
 *      ::HU_POINTER_ATTRIBUTE_SYNC_MEMOPS for the region of memory that
 *      \p ptr points to.
 * 
 * - ::HU_POINTER_ATTRIBUTE_SYNC_MEMOPS:
 *
 *      A boolean attribute which when set, ensures that synchronous memory operations
 *      initiated on the region of memory that \p ptr points to will always synchronize.
 *      See further documentation in the section titled "API synchronization behavior"
 *      to learn more about cases when synchronous memory operations can
 *      exhibit asynchronous behavior.
 *
 * - ::HU_POINTER_ATTRIBUTE_BUFFER_ID:
 *
 *      Returns in \p *data a buffer ID which is guaranteed to be unique within the process.
 *      \p data must point to an unsigned long long.
 *
 *      \p ptr must be a pointer to memory obtained from a HIP memory allocation API.
 *      Every memory allocation from any of the HIP memory allocation APIs will
 *      have a unique ID over a process lifetime. Subsequent allocations do not reuse IDs
 *      from previous freed allocations. IDs are only unique within a single process.
 *
 *
 * - ::HU_POINTER_ATTRIBUTE_IS_MANAGED:
 *
 *      Returns in \p *data a boolean that indicates whether the pointer points to
 *      managed memory or not.
 *
 * - ::HU_POINTER_ATTRIBUTE_DEVICE_ORDINAL:
 *      
 *      Returns in \p *data an integer representing a device ordinal of a device against 
 *      which the memory was allocated or registered.
 *
 * \par
 *
 * Note that for most allocations in the unified virtual address space
 * the host and device pointer for accessing the allocation will be the 
 * same.  The exceptions to this are
 *  - user memory registered using ::huMemHostRegister 
 *  - host memory allocated using ::huMemHostAlloc with the 
 *    ::HU_MEMHOSTALLOC_WRITECOMBINED flag
 * For these types of allocation there will exist separate, disjoint host 
 * and device addresses for accessing the allocation.  In particular 
 *  - The host address will correspond to an invalid unmapped device address 
 *    (which will result in an exception if accessed from the device) 
 *  - The device address will correspond to an invalid unmapped host address 
 *    (which will result in an exception if accessed from the host).
 * For these types of allocations, querying ::HU_POINTER_ATTRIBUTE_HOST_POINTER 
 * and ::HU_POINTER_ATTRIBUTE_DEVICE_POINTER may be used to retrieve the host 
 * and device addresses from either address.
 *
 * \param data      - Returned pointer attribute value
 * \param attribute - Pointer attribute to query
 * \param ptr       - Pointer
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huPointerSetAttribute,
 * ::huMemAlloc,
 * ::huMemFree,
 * ::huMemAllocHost,
 * ::huMemFreeHost,
 * ::huMemHostAlloc,
 * ::huMemHostRegister,
 * ::huMemHostUnregister,
 * ::hipPointerGetAttributes
 */
HUresult HIPAPI huPointerGetAttribute(void *data, HUpointer_attribute attribute, HUdeviceptr ptr);

/**
 * \brief Prefetches memory to the specified destination device
 *
 * Prefetches memory to the specified destination device.  \p devPtr is the 
 * base device pointer of the memory to be prefetched and \p dstDevice is the 
 * destination device. \p count specifies the number of bytes to copy. \p hStream
 * is the stream in which the operation is enqueued. The memory range must refer
 * to managed memory allocated via ::huMemAllocManaged or declared via __managed__ variables.
 *
 * Passing in HU_DEVICE_CPU for \p dstDevice will prefetch the data to host memory. If
 * \p dstDevice is a GPU, then the device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS
 * must be non-zero. Additionally, \p hStream must be associated with a device that has a
 * non-zero value for the device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS.
 *
 * The start address and end address of the memory range will be rounded down and rounded up
 * respectively to be aligned to CPU page size before the prefetch operation is enqueued
 * in the stream.
 *
 * If no physical memory has been allocated for this region, then this memory region
 * will be populated and mapped on the destination device. If there's insufficient
 * memory to prefetch the desired region, the Unified Memory driver may evict pages from other
 * ::huMemAllocManaged allocations to host memory in order to make room. Device memory
 * allocated using ::huMemAlloc or ::huArrayCreate will not be evicted.
 *
 * By default, any mappings to the previous location of the migrated pages are removed and
 * mappings for the new location are only setup on \p dstDevice. The exact behavior however
 * also depends on the settings applied to this memory range via ::huMemAdvise as described
 * below:
 *
 * If ::HU_MEM_ADVISE_SET_READ_MOSTLY was set on any subset of this memory range,
 * then that subset will create a read-only copy of the pages on \p dstDevice.
 *
 * If ::HU_MEM_ADVISE_SET_PREFERRED_LOCATION was called on any subset of this memory
 * range, then the pages will be migrated to \p dstDevice even if \p dstDevice is not the
 * preferred location of any pages in the memory range.
 *
 * If ::HU_MEM_ADVISE_SET_ACCESSED_BY was called on any subset of this memory range,
 * then mappings to those pages from all the appropriate processors are updated to
 * refer to the new location if establishing such a mapping is possible. Otherwise,
 * those mappings are cleared.
 *
 * Note that this API is not required for functionality and only serves to improve performance
 * by allowing the application to migrate data to a suitable location before it is accessed.
 * Memory accesses to this range are always coherent and are allowed even when the data is
 * actively being migrated.
 *
 * Note that this function is asynchronous with respect to the host and all work
 * on other devices.
 *
 * \param devPtr    - Pointer to be prefetched
 * \param count     - Size in bytes
 * \param dstDevice - Destination device to prefetch to
 * \param hStream    - Stream to enqueue prefetch operation
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huMemcpy, ::huMemcpyPeer, ::huMemcpyAsync,
 * ::huMemcpy3DPeerAsync, ::huMemAdvise,
 * ::hipMemPrefetchAsync
 */
HUresult HIPAPI huMemPrefetchAsync(HUdeviceptr devPtr, size_t count, HUdevice dstDevice, HUstream hStream);

/**
 * \brief Advise about the usage of a given memory range
 *
 * Advise the Unified Memory subsystem about the usage pattern for the memory range
 * starting at \p devPtr with a size of \p count bytes. The start address and end address of the memory
 * range will be rounded down and rounded up respectively to be aligned to CPU page size before the
 * advice is applied. The memory range must refer to managed memory allocated via ::huMemAllocManaged
 * or declared via __managed__ variables. The memory range could also refer to system-allocated pageable
 * memory provided it represents a valid, host-accessible region of memory and all additional constraints
 * imposed by \p advice as outlined below are also satisfied. Specifying an invalid system-allocated pageable
 * memory range results in an error being returned.
 *
 * The \p advice parameter can take the following values:
 * - ::HU_MEM_ADVISE_SET_READ_MOSTLY: This implies that the data is mostly going to be read
 * from and only occasionally written to. Any read accesses from any processor to this region will create a
 * read-only copy of at least the accessed pages in that processor's memory. Additionally, if ::huMemPrefetchAsync
 * is called on this region, it will create a read-only copy of the data on the destination processor.
 * If any processor writes to this region, all copies of the corresponding page will be invalidated
 * except for the one where the write occurred. The \p device argument is ignored for this advice.
 * Note that for a page to be read-duplicated, the accessing processor must either be the CPU or a GPU
 * that has a non-zero value for the device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS.
 * Also, if a context is created on a device that does not have the device attribute
 * ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS set, then read-duplication will not occur until
 * all such contexts are destroyed.
 * If the memory region refers to valid system-allocated pageable memory, then the accessing device must
 * have a non-zero value for the device attribute ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS for a read-only
 * copy to be created on that device. Note however that if the accessing device also has a non-zero value for the
 * device attribute ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES, then setting this advice
 * will not create a read-only copy when that device accesses this memory region.
 *
 * - ::HU_MEM_ADVISE_UNSET_READ_MOSTLY:  Undoes the effect of ::HU_MEM_ADVISE_SET_READ_MOSTLY and also prevents the
 * Unified Memory driver from attempting heuristic read-duplication on the memory range. Any read-duplicated
 * copies of the data will be collapsed into a single copy. The location for the collapsed
 * copy will be the preferred location if the page has a preferred location and one of the read-duplicated
 * copies was resident at that location. Otherwise, the location chosen is arbitrary.
 *
 * - ::HU_MEM_ADVISE_SET_PREFERRED_LOCATION: This advice sets the preferred location for the
 * data to be the memory belonging to \p device. Passing in HU_DEVICE_CPU for \p device sets the
 * preferred location as host memory. If \p device is a GPU, then it must have a non-zero value for the
 * device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS. Setting the preferred location
 * does not cause data to migrate to that location immediately. Instead, it guides the migration policy
 * when a fault occurs on that memory region. If the data is already in its preferred location and the
 * faulting processor can establish a mapping without requiring the data to be migrated, then
 * data migration will be avoided. On the other hand, if the data is not in its preferred location
 * or if a direct mapping cannot be established, then it will be migrated to the processor accessing
 * it. It is important to note that setting the preferred location does not prevent data prefetching
 * done using ::huMemPrefetchAsync.
 * Having a preferred location can override the page thrash detection and resolution logic in the Unified
 * Memory driver. Normally, if a page is detected to be constantly thrashing between for example host and device
 * memory, the page may eventually be pinned to host memory by the Unified Memory driver. But
 * if the preferred location is set as device memory, then the page will continue to thrash indefinitely.
 * If ::HU_MEM_ADVISE_SET_READ_MOSTLY is also set on this memory region or any subset of it, then the
 * policies associated with that advice will override the policies of this advice, unless read accesses from
 * \p device will not result in a read-only copy being created on that device as outlined in description for
 * the advice ::HU_MEM_ADVISE_SET_READ_MOSTLY.
 * If the memory region refers to valid system-allocated pageable memory, then \p device must have a non-zero
 * value for the device attribute ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS. Additionally, if \p device has
 * a non-zero value for the device attribute ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES,
 * then this call has no effect. Note however that this behavior may change in the future.
 *
 * - ::HU_MEM_ADVISE_UNSET_PREFERRED_LOCATION: Undoes the effect of ::HU_MEM_ADVISE_SET_PREFERRED_LOCATION
 * and changes the preferred location to none.
 *
 * - ::HU_MEM_ADVISE_SET_ACCESSED_BY: This advice implies that the data will be accessed by \p device.
 * Passing in ::HU_DEVICE_CPU for \p device will set the advice for the CPU. If \p device is a GPU, then
 * the device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS must be non-zero.
 * This advice does not cause data migration and has no impact on the location of the data per se. Instead,
 * it causes the data to always be mapped in the specified processor's page tables, as long as the
 * location of the data permits a mapping to be established. If the data gets migrated for any reason,
 * the mappings are updated accordingly.
 * This advice is recommended in scenarios where data locality is not important, but avoiding faults is.
 * Consider for example a system containing multiple GPUs with peer-to-peer access enabled, where the
 * data located on one GPU is occasionally accessed by peer GPUs. In such scenarios, migrating data
 * over to the other GPUs is not as important because the accesses are infrequent and the overhead of
 * migration may be too high. But preventing faults can still help improve performance, and so having
 * a mapping set up in advance is useful. Note that on CPU access of this data, the data may be migrated
 * to host memory because the CPU typically cannot access device memory directly. Any GPU that had the
 * ::HU_MEM_ADVISE_SET_ACCESSED_BY flag set for this data will now have its mapping updated to point to the
 * page in host memory.
 * If ::HU_MEM_ADVISE_SET_READ_MOSTLY is also set on this memory region or any subset of it, then the
 * policies associated with that advice will override the policies of this advice. Additionally, if the
 * preferred location of this memory region or any subset of it is also \p device, then the policies
 * associated with ::HU_MEM_ADVISE_SET_PREFERRED_LOCATION will override the policies of this advice.
 * If the memory region refers to valid system-allocated pageable memory, then \p device must have a non-zero
 * value for the device attribute ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS. Additionally, if \p device has
 * a non-zero value for the device attribute ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES,
 * then this call has no effect.
 *
 * - ::HU_MEM_ADVISE_UNSET_ACCESSED_BY: Undoes the effect of ::HU_MEM_ADVISE_SET_ACCESSED_BY. Any mappings to
 * the data from \p device may be removed at any time causing accesses to result in non-fatal page faults.
 * If the memory region refers to valid system-allocated pageable memory, then \p device must have a non-zero
 * value for the device attribute ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS. Additionally, if \p device has
 * a non-zero value for the device attribute ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES,
 * then this call has no effect.
 *
 * \param devPtr - Pointer to memory to set the advice for
 * \param count  - Size in bytes of the memory range
 * \param advice - Advice to be applied for the specified memory range
 * \param device - Device to apply the advice for
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huMemcpy, ::huMemcpyPeer, ::huMemcpyAsync,
 * ::huMemcpy3DPeerAsync, ::huMemPrefetchAsync,
 * ::hipMemAdvise
 */
HUresult HIPAPI huMemAdvise(HUdeviceptr devPtr, size_t count, HUmem_advise advice, HUdevice device);

/**
 * \brief Query an attribute of a given memory range
 * 
 * Query an attribute about the memory range starting at \p devPtr with a size of \p count bytes. The
 * memory range must refer to managed memory allocated via ::huMemAllocManaged or declared via
 * __managed__ variables.
 *
 * The \p attribute parameter can take the following values:
 * - ::HU_MEM_RANGE_ATTRIBUTE_READ_MOSTLY: If this attribute is specified, \p data will be interpreted
 * as a 32-bit integer, and \p dataSize must be 4. The result returned will be 1 if all pages in the given
 * memory range have read-duplication enabled, or 0 otherwise.
 * - ::HU_MEM_RANGE_ATTRIBUTE_PREFERRED_LOCATION: If this attribute is specified, \p data will be
 * interpreted as a 32-bit integer, and \p dataSize must be 4. The result returned will be a GPU device
 * id if all pages in the memory range have that GPU as their preferred location, or it will be HU_DEVICE_CPU
 * if all pages in the memory range have the CPU as their preferred location, or it will be HU_DEVICE_INVALID
 * if either all the pages don't have the same preferred location or some of the pages don't have a
 * preferred location at all. Note that the actual location of the pages in the memory range at the time of
 * the query may be different from the preferred location. 
 * - ::HU_MEM_RANGE_ATTRIBUTE_ACCESSED_BY: If this attribute is specified, \p data will be interpreted
 * as an array of 32-bit integers, and \p dataSize must be a non-zero multiple of 4. The result returned
 * will be a list of device ids that had ::HU_MEM_ADVISE_SET_ACCESSED_BY set for that entire memory range.
 * If any device does not have that advice set for the entire memory range, that device will not be included.
 * If \p data is larger than the number of devices that have that advice set for that memory range,
 * HU_DEVICE_INVALID will be returned in all the extra space provided. For ex., if \p dataSize is 12
 * (i.e. \p data has 3 elements) and only device 0 has the advice set, then the result returned will be
 * { 0, HU_DEVICE_INVALID, HU_DEVICE_INVALID }. If \p data is smaller than the number of devices that have
 * that advice set, then only as many devices will be returned as can fit in the array. There is no
 * guarantee on which specific devices will be returned, however.
 * - ::HU_MEM_RANGE_ATTRIBUTE_LAST_PREFETCH_LOCATION: If this attribute is specified, \p data will be
 * interpreted as a 32-bit integer, and \p dataSize must be 4. The result returned will be the last location
 * to which all pages in the memory range were prefetched explicitly via ::huMemPrefetchAsync. This will either be
 * a GPU id or HU_DEVICE_CPU depending on whether the last location for prefetch was a GPU or the CPU
 * respectively. If any page in the memory range was never explicitly prefetched or if all pages were not
 * prefetched to the same location, HU_DEVICE_INVALID will be returned. Note that this simply returns the
 * last location that the applicaton requested to prefetch the memory range to. It gives no indication as to
 * whether the prefetch operation to that location has completed or even begun.
 *
 * \param data      - A pointers to a memory location where the result
 *                    of each attribute query will be written to.
 * \param dataSize  - Array containing the size of data
 * \param attribute - The attribute to query
 * \param devPtr    - Start of the range to query
 * \param count     - Size of the range to query
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 * \note_async
 * \note_null_stream
 *
 * \sa ::huMemRangeGetAttributes, ::huMemPrefetchAsync,
 * ::huMemAdvise,
 * ::hipMemRangeGetAttribute
 */
HUresult HIPAPI huMemRangeGetAttribute(void *data, size_t dataSize, HUmem_range_attribute attribute, HUdeviceptr devPtr, size_t count);

/**
 * \brief Query attributes of a given memory range.
 *
 * Query attributes of the memory range starting at \p devPtr with a size of \p count bytes. The
 * memory range must refer to managed memory allocated via ::huMemAllocManaged or declared via
 * __managed__ variables. The \p attributes array will be interpreted to have \p numAttributes
 * entries. The \p dataSizes array will also be interpreted to have \p numAttributes entries.
 * The results of the query will be stored in \p data.
 *
 * The list of supported attributes are given below. Please refer to ::huMemRangeGetAttribute for
 * attribute descriptions and restrictions.
 *
 * - ::HU_MEM_RANGE_ATTRIBUTE_READ_MOSTLY
 * - ::HU_MEM_RANGE_ATTRIBUTE_PREFERRED_LOCATION
 * - ::HU_MEM_RANGE_ATTRIBUTE_ACCESSED_BY
 * - ::HU_MEM_RANGE_ATTRIBUTE_LAST_PREFETCH_LOCATION
 *
 * \param data          - A two-dimensional array containing pointers to memory
 *                        locations where the result of each attribute query will be written to.
 * \param dataSizes     - Array containing the sizes of each result
 * \param attributes    - An array of attributes to query
 *                        (numAttributes and the number of attributes in this array should match)
 * \param numAttributes - Number of attributes to query
 * \param devPtr        - Start of the range to query
 * \param count         - Size of the range to query
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa ::huMemRangeGetAttribute, ::huMemAdvise
 * ::huMemPrefetchAsync,
 * ::hipMemRangeGetAttributes
 */
HUresult HIPAPI huMemRangeGetAttributes(void **data, size_t *dataSizes, HUmem_range_attribute *attributes, size_t numAttributes, HUdeviceptr devPtr, size_t count);

/**
 * \brief Set attributes on a previously allocated memory region
 *
 * The supported attributes are:
 *
 * - ::HU_POINTER_ATTRIBUTE_SYNC_MEMOPS:
 *
 *      A boolean attribute that can either be set (1) or unset (0). When set,
 *      the region of memory that \p ptr points to is guaranteed to always synchronize
 *      memory operations that are synchronous. If there are some previously initiated
 *      synchronous memory operations that are pending when this attribute is set, the
 *      function does not return until those memory operations are complete.
 *      See further documentation in the section titled "API synchronization behavior"
 *      to learn more about cases when synchronous memory operations can
 *      exhibit asynchronous behavior.
 *      \p value will be considered as a pointer to an unsigned integer to which this attribute is to be set.
 *
 * \param value     - Pointer to memory containing the value to be set
 * \param attribute - Pointer attribute to set
 * \param ptr       - Pointer to a memory region allocated using HIP memory allocation APIs
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa ::huPointerGetAttribute,
 * ::huPointerGetAttributes,
 * ::huMemAlloc,
 * ::huMemFree,
 * ::huMemAllocHost,
 * ::huMemFreeHost,
 * ::huMemHostAlloc,
 * ::huMemHostRegister,
 * ::huMemHostUnregister
 */
HUresult HIPAPI huPointerSetAttribute(const void *value, HUpointer_attribute attribute, HUdeviceptr ptr);

/**
 * \brief Returns information about a pointer.
 *
 * The supported attributes are (refer to ::huPointerGetAttribute for attribute descriptions and restrictions):
 *
 * - ::HU_POINTER_ATTRIBUTE_CONTEXT
 * - ::HU_POINTER_ATTRIBUTE_MEMORY_TYPE
 * - ::HU_POINTER_ATTRIBUTE_DEVICE_POINTER
 * - ::HU_POINTER_ATTRIBUTE_HOST_POINTER
 * - ::HU_POINTER_ATTRIBUTE_SYNC_MEMOPS
 * - ::HU_POINTER_ATTRIBUTE_BUFFER_ID
 * - ::HU_POINTER_ATTRIBUTE_IS_MANAGED
 * - ::HU_POINTER_ATTRIBUTE_DEVICE_ORDINAL
 *
 * \param numAttributes - Number of attributes to query
 * \param attributes    - An array of attributes to query
 *                      (numAttributes and the number of attributes in this array should match)
 * \param data          - A two-dimensional array containing pointers to memory
 *                      locations where the result of each attribute query will be written to.
 * \param ptr           - Pointer to query
 *
 * Unlike ::huPointerGetAttribute, this function will not return an error when the \p ptr
 * encountered is not a valid HIP pointer. Instead, the attributes are assigned default NULL values
 * and HIP_SUCCESS is returned.
 *
 * If \p ptr was not allocated by, mapped by, or registered with a ::HUcontext which uses UVA
 * (Unified Virtual Addressing), ::HIP_ERROR_INVALID_CONTEXT is returned.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huPointerGetAttribute,
 * ::huPointerSetAttribute,
 * ::hipPointerGetAttributes
 */
HUresult HIPAPI huPointerGetAttributes(unsigned int numAttributes, HUpointer_attribute *attributes, void **data, HUdeviceptr ptr);

/** @} */ /* END HIP_UNIFIED */

/**
 * \defgroup HIP_STREAM Stream Management
 *
 * ___MANBRIEF___ stream management functions of the low-level HIP driver API
 * (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the stream management functions of the low-level HIP
 * driver application programming interface.
 *
 * @{
 */

/**
 * \brief Create a stream
 *
 * Creates a stream and returns a handle in \p phStream.  The \p Flags argument
 * determines behaviors of the stream.  Valid values for \p Flags are:
 * - ::HU_STREAM_DEFAULT: Default stream creation flag.
 * - ::HU_STREAM_NON_BLOCKING: Specifies that work running in the created 
 *   stream may run concurrently with work in stream 0 (the NULL stream), and that
 *   the created stream should perform no implicit synchronization with stream 0.
 *
 * \param phStream - Returned newly created stream
 * \param Flags    - Parameters for stream creation
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa ::huStreamDestroy,
 * ::huStreamCreateWithPriority,
 * ::huStreamGetPriority,
 * ::huStreamGetFlags,
 * ::huStreamWaitEvent,
 * ::huStreamQuery,
 * ::huStreamSynchronize,
 * ::huStreamAddCallback,
 * ::hipStreamCreate,
 * ::hipStreamCreateWithFlags
 */
HUresult HIPAPI huStreamCreate(HUstream *phStream, unsigned int Flags);

/**
 * \brief Create a stream with the given priority
 *
 * Creates a stream with the specified priority and returns a handle in \p phStream.
 * This API alters the scheduler priority of work in the stream. Work in a higher
 * priority stream may preempt work already executing in a low priority stream.
 *
 * \p priority follows a convention where lower numbers represent higher priorities.
 * '0' represents default priority. The range of meaningful numerical priorities can
 * be queried using ::huCtxGetStreamPriorityRange. If the specified priority is
 * outside the numerical range returned by ::huCtxGetStreamPriorityRange,
 * it will automatically be clamped to the lowest or the highest number in the range.
 *
 * \param phStream    - Returned newly created stream
 * \param flags       - Flags for stream creation. See ::huStreamCreate for a list of
 *                      valid flags
 * \param priority    - Stream priority. Lower numbers represent higher priorities.
 *                      See ::huCtxGetStreamPriorityRange for more information about
 *                      meaningful stream priorities that can be passed.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \note Stream priorities are supported only on GPUs
 * with compute capability 3.5 or higher.
 *
 * \note In the current implementation, only compute kernels launched in
 * priority streams are affected by the stream's priority. Stream priorities have
 * no effect on host-to-device and device-to-host memory operations.
 *
 * \sa ::huStreamDestroy,
 * ::huStreamCreate,
 * ::huStreamGetPriority,
 * ::huCtxGetStreamPriorityRange,
 * ::huStreamGetFlags,
 * ::huStreamWaitEvent,
 * ::huStreamQuery,
 * ::huStreamSynchronize,
 * ::huStreamAddCallback,
 * ::hipStreamCreateWithPriority
 */
HUresult HIPAPI huStreamCreateWithPriority(HUstream *phStream, unsigned int flags, int priority);


/**
 * \brief Query the priority of a given stream
 *
 * Query the priority of a stream created using ::huStreamCreate or ::huStreamCreateWithPriority
 * and return the priority in \p priority. Note that if the stream was created with a
 * priority outside the numerical range returned by ::huCtxGetStreamPriorityRange,
 * this function returns the clamped priority.
 * See ::huStreamCreateWithPriority for details about priority clamping.
 *
 * \param hStream    - Handle to the stream to be queried
 * \param priority   - Pointer to a signed integer in which the stream's priority is returned
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa ::huStreamDestroy,
 * ::huStreamCreate,
 * ::huStreamCreateWithPriority,
 * ::huCtxGetStreamPriorityRange,
 * ::huStreamGetFlags,
 * ::hipStreamGetPriority
 */
HUresult HIPAPI huStreamGetPriority(HUstream hStream, int *priority);

/**
 * \brief Query the flags of a given stream
 *
 * Query the flags of a stream created using ::huStreamCreate or ::huStreamCreateWithPriority
 * and return the flags in \p flags.
 *
 * \param hStream    - Handle to the stream to be queried
 * \param flags      - Pointer to an unsigned integer in which the stream's flags are returned
 *                     The value returned in \p flags is a logical 'OR' of all flags that
 *                     were used while creating this stream. See ::huStreamCreate for the list
 *                     of valid flags
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa ::huStreamDestroy,
 * ::huStreamCreate,
 * ::huStreamGetPriority,
 * ::hipStreamGetFlags
 */
HUresult HIPAPI huStreamGetFlags(HUstream hStream, unsigned int *flags);

/**
 * \brief Query the context associated with a stream
 *
 * Returns the HIP context that the stream is associated with. 
 *
 * The stream handle \p hStream can refer to any of the following:
 * <ul>
 *   <li>a stream created via any of the HIP driver APIs such as ::huStreamCreate
 *   and ::huStreamCreateWithPriority, or their runtime API equivalents such as
 *   ::hipStreamCreate, ::hipStreamCreateWithFlags and ::hipStreamCreateWithPriority.
 *   The returned context is the context that was active in the calling thread when the
 *   stream was created. Passing an invalid handle will result in undefined behavior.</li>
 *   <li>any of the special streams such as the NULL stream, ::HU_STREAM_LEGACY and
 *   ::HU_STREAM_PER_THREAD. The runtime API equivalents of these are also accepted,
 *   which are NULL, ::hipStreamLegacy and ::hipStreamPerThread respectively.
 *   Specifying any of the special handles will return the context current to the
 *   calling thread. If no context is current to the calling thread,
 *   ::HIP_ERROR_INVALID_CONTEXT is returned.</li>
 * </ul>
 *
 * \param hStream - Handle to the stream to be queried
 * \param pctx    - Returned context associated with the stream
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * \notefnerr
 *
 * \sa ::huStreamDestroy,
 * ::huStreamCreateWithPriority,
 * ::huStreamGetPriority,
 * ::huStreamGetFlags,
 * ::huStreamWaitEvent,
 * ::huStreamQuery,
 * ::huStreamSynchronize,
 * ::huStreamAddCallback,
 * ::hipStreamCreate,
 * ::hipStreamCreateWithFlags
 */
HUresult HIPAPI huStreamGetCtx(HUstream hStream, HUcontext *pctx);

/**
 * \brief Make a compute stream wait on an event
 *
 * Makes all future work submitted to \p hStream wait for all work captured in
 * \p hEvent.  See ::huEventRecord() for details on what is captured by an event.
 * The synchronization will be performed efficiently on the device when applicable.
 * \p hEvent may be from a different context or device than \p hStream.
 *
 * \param hStream - Stream to wait
 * \param hEvent  - Event to wait on (may not be NULL)
 * \param Flags   - Parameters for the operation (must be 0)
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huStreamCreate,
 * ::huEventRecord,
 * ::huStreamQuery,
 * ::huStreamSynchronize,
 * ::huStreamAddCallback,
 * ::huStreamDestroy,
 * ::hipStreamWaitEvent
 */
HUresult HIPAPI huStreamWaitEvent(HUstream hStream, HUevent hEvent, unsigned int Flags);

/**
 * \brief Add a callback to a compute stream
 *
 * Adds a callback to be called on the host after all currently enqueued
 * items in the stream have completed.  For each 
 * huStreamAddCallback call, the callback will be executed exactly once.
 * The callback will block later work in the stream until it is finished.
 *
 * The callback may be passed ::HIP_SUCCESS or an error code.  In the event
 * of a device error, all subsequently executed callbacks will receive an
 * appropriate ::HUresult.
 *
 * Callbacks must not make any HIP API calls.  Attempting to use a HIP API
 * will result in ::HIP_ERROR_NOT_PERMITTED.  Callbacks must not perform any
 * synchronization that may depend on outstanding device work or other callbacks
 * that are not mandated to run earlier.  Callbacks without a mandated order
 * (in independent streams) execute in undefined order and may be serialized.
 *
 * For the purposes of Unified Memory, callback execution makes a number of
 * guarantees:
 * <ul>
 *   <li>The callback stream is considered idle for the duration of the
 *   callback.  Thus, for example, a callback may always use memory attached
 *   to the callback stream.</li>
 *   <li>The start of execution of a callback has the same effect as
 *   synchronizing an event recorded in the same stream immediately prior to
 *   the callback.  It thus synchronizes streams which have been "joined"
 *   prior to the callback.</li>
 *   <li>Adding device work to any stream does not have the effect of making
 *   the stream active until all preceding callbacks have executed.  Thus, for
 *   example, a callback might use global attached memory even if work has
 *   been added to another stream, if it has been properly ordered with an
 *   event.</li>
 *   <li>Completion of a callback does not cause a stream to become
 *   active except as described above.  The callback stream will remain idle
 *   if no device work follows the callback, and will remain idle across
 *   consecutive callbacks without device work in between.  Thus, for example,
 *   stream synchronization can be done by signaling from a callback at the
 *   end of the stream.</li>
 * </ul>
 *
 * \param hStream  - Stream to add callback to
 * \param callback - The function to call once preceding stream operations are complete
 * \param userData - User specified data to be passed to the callback function
 * \param flags    - Reserved for future use, must be 0
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_NOT_SUPPORTED
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huStreamCreate,
 * ::huStreamQuery,
 * ::huStreamSynchronize,
 * ::huStreamWaitEvent,
 * ::huStreamDestroy,
 * ::huMemAllocManaged,
 * ::huStreamAttachMemAsync,
 * ::hipStreamAddCallback
 */
HUresult HIPAPI huStreamAddCallback(HUstream hStream, HUstreamCallback callback, void *userData, unsigned int flags);

/**
 * \brief Attach memory to a stream asynchronously
 *
 * Enqueues an operation in \p hStream to specify stream association of
 * \p length bytes of memory starting from \p dptr. This function is a
 * stream-ordered operation, meaning that it is dependent on, and will
 * only take effect when, previous work in stream has completed. Any
 * previous association is automatically replaced.
 *
 * \p dptr must point to one of the following types of memories:
 * - managed memory declared using the __managed__ keyword or allocated with
 *   ::huMemAllocManaged.
 * - a valid host-accessible region of system-allocated pageable memory. This
 *   type of memory may only be specified if the device associated with the
 *   stream reports a non-zero value for the device attribute
 *   ::HU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS.
 *
 * For managed allocations, \p length must be either zero or the entire
 * allocation's size. Both indicate that the entire allocation's stream
 * association is being changed. Currently, it is not possible to change stream
 * association for a portion of a managed allocation.
 *
 * For pageable host allocations, \p length must be non-zero.
 *
 * The stream association is specified using \p flags which must be
 * one of ::HUmemAttach_flags.
 * If the ::HU_MEM_ATTACH_GLOBAL flag is specified, the memory can be accessed
 * by any stream on any device.
 * If the ::HU_MEM_ATTACH_HOST flag is specified, the program makes a guarantee
 * that it won't access the memory on the device from any stream on a device that
 * has a zero value for the device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS.
 * If the ::HU_MEM_ATTACH_SINGLE flag is specified and \p hStream is associated with
 * a device that has a zero value for the device attribute ::HU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS,
 * the program makes a guarantee that it will only access the memory on the device
 * from \p hStream. It is illegal to attach singly to the NULL stream, because the
 * NULL stream is a virtual global stream and not a specific stream. An error will
 * be returned in this case.
 *
 * When memory is associated with a single stream, the Unified Memory system will
 * allow CPU access to this memory region so long as all operations in \p hStream
 * have completed, regardless of whether other streams are active. In effect,
 * this constrains exclusive ownership of the managed memory region by
 * an active GPU to per-stream activity instead of whole-GPU activity.
 *
 * Accessing memory on the device from streams that are not associated with
 * it will produce undefined results. No error checking is performed by the
 * Unified Memory system to ensure that kernels launched into other streams
 * do not access this region.
 *
 * It is a program's responsibility to order calls to ::huStreamAttachMemAsync
 * via events, synchronization or other means to ensure legal access to memory
 * at all times. Data visibility and coherency will be changed appropriately
 * for all kernels which follow a stream-association change.
 *
 * If \p hStream is destroyed while data is associated with it, the association is
 * removed and the association reverts to the default visibility of the allocation
 * as specified at ::huMemAllocManaged. For __managed__ variables, the default
 * association is always ::HU_MEM_ATTACH_GLOBAL. Note that destroying a stream is an
 * asynchronous operation, and as a result, the change to default association won't
 * happen until all work in the stream has completed.
 *
 * \param hStream - Stream in which to enqueue the attach operation
 * \param dptr    - Pointer to memory (must be a pointer to managed memory or
*                   to a valid host-accessible region of system-allocated
*                   pageable memory)
 * \param length  - Length of memory
 * \param flags   - Must be one of ::HUmemAttach_flags
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_NOT_SUPPORTED
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huStreamCreate,
 * ::huStreamQuery,
 * ::huStreamSynchronize,
 * ::huStreamWaitEvent,
 * ::huStreamDestroy,
 * ::huMemAllocManaged,
 * ::hipStreamAttachMemAsync
 */
HUresult HIPAPI huStreamAttachMemAsync(HUstream hStream, HUdeviceptr dptr, size_t length, unsigned int flags);

/**
 * \brief Determine status of a compute stream
 *
 * Returns ::HIP_SUCCESS if all operations in the stream specified by
 * \p hStream have completed, or ::HIP_ERROR_NOT_READY if not.
 *
 * For the purposes of Unified Memory, a return value of ::HIP_SUCCESS
 * is equivalent to having called ::huStreamSynchronize().
 *
 * \param hStream - Stream to query status of
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_NOT_READY
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huStreamCreate,
 * ::huStreamWaitEvent,
 * ::huStreamDestroy,
 * ::huStreamSynchronize,
 * ::huStreamAddCallback,
 * ::hipStreamQuery
 */
HUresult HIPAPI huStreamQuery(HUstream hStream);

/**
 * \brief Wait until a stream's tasks are completed
 *
 * Waits until the device has completed all operations in the stream specified
 * by \p hStream. If the context was created with the 
 * ::HU_CTX_SCHED_BLOCKING_SYNC flag, the CPU thread will block until the
 * stream is finished with all of its tasks.
 *
 * \param hStream - Stream to wait for
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huStreamCreate,
 * ::huStreamDestroy,
 * ::huStreamWaitEvent,
 * ::huStreamQuery,
 * ::huStreamAddCallback,
 * ::hipStreamSynchronize
 */
HUresult HIPAPI huStreamSynchronize(HUstream hStream);

/**
 * \brief Destroys a stream
 *
 * Destroys the stream specified by \p hStream.  
 *
 * In case the device is still doing work in the stream \p hStream
 * when ::huStreamDestroy() is called, the function will return immediately 
 * and the resources associated with \p hStream will be released automatically 
 * once the device has completed all work in \p hStream.
 *
 * \param hStream - Stream to destroy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huStreamCreate,
 * ::huStreamWaitEvent,
 * ::huStreamQuery,
 * ::huStreamSynchronize,
 * ::huStreamAddCallback,
 * ::hipStreamDestroy
 */
HUresult HIPAPI huStreamDestroy(HUstream hStream);

/** @} */ /* END HIP_STREAM */


/**
 * \defgroup HIP_EVENT Event Management
 *
 * ___MANBRIEF___ event management functions of the low-level HIP driver API
 * (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the event management functions of the low-level HIP
 * driver application programming interface.
 *
 * @{
 */

/**
 * \brief Creates an event
 *
 * Creates an event *phEvent for the current context with the flags specified via
 * \p Flags. Valid flags include:
 * - ::HU_EVENT_DEFAULT: Default event creation flag.
 * - ::HU_EVENT_BLOCKING_SYNC: Specifies that the created event should use blocking
 *   synchronization.  A CPU thread that uses ::huEventSynchronize() to wait on
 *   an event created with this flag will block until the event has actually
 *   been recorded.
 * - ::HU_EVENT_DISABLE_TIMING: Specifies that the created event does not need
 *   to record timing data.  Events created with this flag specified and
 *   the ::HU_EVENT_BLOCKING_SYNC flag not specified will provide the best
 *   performance when used with ::huStreamWaitEvent() and ::huEventQuery().
 * - ::HU_EVENT_INTERPROCESS: Specifies that the created event may be used as an
 *   interprocess event by ::huIpcGetEventHandle(). ::HU_EVENT_INTERPROCESS must
 *   be specified along with ::HU_EVENT_DISABLE_TIMING.
 *
 * \param phEvent - Returns newly created event
 * \param Flags   - Event creation flags
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_OUT_OF_MEMORY
 * \notefnerr
 *
 * \sa
 * ::huEventRecord,
 * ::huEventQuery,
 * ::huEventSynchronize,
 * ::huEventDestroy,
 * ::huEventElapsedTime,
 * ::hipEventCreate,
 * ::hipEventCreateWithFlags
 */
HUresult HIPAPI huEventCreate(HUevent *phEvent, unsigned int Flags);

/**
 * \brief Records an event
 *
 * Captures in \p hEvent the contents of \p hStream at the time of this call.
 * \p hEvent and \p hStream must be from the same context.
 * Calls such as ::huEventQuery() or ::huStreamWaitEvent() will then
 * examine or wait for completion of the work that was captured. Uses of
 * \p hStream after this call do not modify \p hEvent. See note on default
 * stream behavior for what is captured in the default case.
 *
 * ::huEventRecord() can be called multiple times on the same event and
 * will overwrite the previously captured state. Other APIs such as
 * ::huStreamWaitEvent() use the most recently captured state at the time
 * of the API call, and are not affected by later calls to
 * ::huEventRecord(). Before the first call to ::huEventRecord(), an
 * event represents an empty set of work, so for example ::huEventQuery()
 * would return ::HIP_SUCCESS.
 *
 * \param hEvent  - Event to record
 * \param hStream - Stream to record event for
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_VALUE
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huEventCreate,
 * ::huEventQuery,
 * ::huEventSynchronize,
 * ::huStreamWaitEvent,
 * ::huEventDestroy,
 * ::huEventElapsedTime,
 * ::hipEventRecord
 */
HUresult HIPAPI huEventRecord(HUevent hEvent, HUstream hStream);

/**
 * \brief Queries an event's status
 *
 * Queries the status of all work currently captured by \p hEvent. See
 * ::huEventRecord() for details on what is captured by an event.
 *
 * Returns ::HIP_SUCCESS if all captured work has been completed, or
 * ::HIP_ERROR_NOT_READY if any captured work is incomplete.
 *
 * For the purposes of Unified Memory, a return value of ::HIP_SUCCESS
 * is equivalent to having called ::huEventSynchronize().
 *
 * \param hEvent - Event to query
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_READY
 * \notefnerr
 *
 * \sa ::huEventCreate,
 * ::huEventRecord,
 * ::huEventSynchronize,
 * ::huEventDestroy,
 * ::huEventElapsedTime,
 * ::hipEventQuery
 */
HUresult HIPAPI huEventQuery(HUevent hEvent);

/**
 * \brief Waits for an event to complete
 *
 * Waits until the completion of all work currently captured in \p hEvent.
 * See ::huEventRecord() for details on what is captured by an event.
 *
 * Waiting for an event that was created with the ::HU_EVENT_BLOCKING_SYNC
 * flag will cause the calling CPU thread to block until the event has
 * been completed by the device.  If the ::HU_EVENT_BLOCKING_SYNC flag has
 * not been set, then the CPU thread will busy-wait until the event has
 * been completed by the device.
 *
 * \param hEvent - Event to wait for
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE
 * \notefnerr
 *
 * \sa ::huEventCreate,
 * ::huEventRecord,
 * ::huEventQuery,
 * ::huEventDestroy,
 * ::huEventElapsedTime,
 * ::hipEventSynchronize
 */
HUresult HIPAPI huEventSynchronize(HUevent hEvent);

/**
 * \brief Destroys an event
 *
 * Destroys the event specified by \p hEvent.
 *
 * An event may be destroyed before it is complete (i.e., while
 * ::huEventQuery() would return ::HIP_ERROR_NOT_READY). In this case, the
 * call does not block on completion of the event, and any associated
 * resources will automatically be released asynchronously at completion.
 *
 * \param hEvent - Event to destroy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE
 * \notefnerr
 *
 * \sa ::huEventCreate,
 * ::huEventRecord,
 * ::huEventQuery,
 * ::huEventSynchronize,
 * ::huEventElapsedTime,
 * ::hipEventDestroy
 */
HUresult HIPAPI huEventDestroy(HUevent hEvent);

/**
 * \brief Computes the elapsed time between two events
 *
 * Computes the elapsed time between two events (in milliseconds with a
 * resolution of around 0.5 microseconds).
 *
 * If either event was last recorded in a non-NULL stream, the resulting time
 * may be greater than expected (even if both used the same stream handle). This
 * happens because the ::huEventRecord() operation takes place asynchronously
 * and there is no guarantee that the measured latency is actually just between
 * the two events. Any number of other different stream operations could execute
 * in between the two measured events, thus altering the timing in a significant
 * way.
 *
 * If ::huEventRecord() has not been called on either event then
 * ::HIP_ERROR_INVALID_HANDLE is returned. If ::huEventRecord() has been called
 * on both events but one or both of them has not yet been completed (that is,
 * ::huEventQuery() would return ::HIP_ERROR_NOT_READY on at least one of the
 * events), ::HIP_ERROR_NOT_READY is returned. If either event was created with
 * the ::HU_EVENT_DISABLE_TIMING flag, then this function will return
 * ::HIP_ERROR_INVALID_HANDLE.
 *
 * \param pMilliseconds - Time between \p hStart and \p hEnd in ms
 * \param hStart        - Starting event
 * \param hEnd          - Ending event
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_NOT_READY
 * \notefnerr
 *
 * \sa ::huEventCreate,
 * ::huEventRecord,
 * ::huEventQuery,
 * ::huEventSynchronize,
 * ::huEventDestroy,
 * ::hipEventElapsedTime
 */
HUresult HIPAPI huEventElapsedTime(float *pMilliseconds, HUevent hStart, HUevent hEnd);

/** @} */ /* END HIP_EVENT */

/**
 * \defgroup HIP_MEMOP Stream memory operations
 *
 * ___MANBRIEF___ Stream memory operations of the low-level HIP driver API
 * (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the stream memory operations of the low-level HIP
 * driver application programming interface.
 *
 * The whole set of operations is disabled by default. Users are required
 * to explicitly enable them, e.g. on Linux by passing the kernel module
 * parameter shown below:
 *     modprobe nvidia NVreg_EnableStreamMemOPs=1
 * There is currently no way to enable these operations on other operating
 * systems.
 *
 * Users can programmatically query whether the device supports these
 * operations with ::huDeviceGetAttribute() and
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_MEM_OPS.
 *
 * Support for the ::HU_STREAM_WAIT_VALUE_NOR flag can be queried with
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_WAIT_VALUE_NOR.
 *
 * Support for the ::huStreamWriteValue64() and ::huStreamWaitValue64()
 * functions, as well as for the ::HU_STREAM_MEM_OP_WAIT_VALUE_64 and
 * ::HU_STREAM_MEM_OP_WRITE_VALUE_64 flags, can be queried with
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_64_BIT_STREAM_MEM_OPS.
 *
 * Support for both ::HU_STREAM_WAIT_VALUE_FLUSH and
 * ::HU_STREAM_MEM_OP_FLUSH_REMOTE_WRITES requires dedicated platform
 * hardware features and can be queried with ::huDeviceGetAttribute() and
 * ::HU_DEVICE_ATTRIBUTE_CAN_FLUSH_REMOTE_WRITES.
 *
 * Note that all memory pointers passed as parameters to these operations
 * are device pointers. Where necessary a device pointer should be
 * obtained, for example with ::huMemHostGetDevicePointer().
 *
 * None of the operations accepts pointers to managed memory buffers
 * (::huMemAllocManaged).
 *
 * @{
 */

/**
 * \brief Wait on a memory location
 *
 * Enqueues a synchronization of the stream on the given memory location. Work
 * ordered after the operation will block until the given condition on the
 * memory is satisfied. By default, the condition is to wait for
 * (int32_t)(*addr - value) >= 0, a cyclic greater-or-equal.
 * Other condition types can be specified via \p flags.
 *
 * If the memory was registered via ::huMemHostRegister(), the device pointer
 * should be obtained with ::huMemHostGetDevicePointer(). This function cannot
 * be used with managed memory (::huMemAllocManaged).
 *
 * Support for this can be queried with ::huDeviceGetAttribute() and
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_MEM_OPS.
 *
 * Support for HU_STREAM_WAIT_VALUE_NOR can be queried with ::huDeviceGetAttribute() and
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_WAIT_VALUE_NOR.
 *
 * \param stream The stream to synchronize on the memory location.
 * \param addr The memory location to wait on.
 * \param value The value to compare with the memory location.
 * \param flags See ::HUstreamWaitValue_flags.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_SUPPORTED
 * \notefnerr
 *
 * \sa ::huStreamWaitValue64,
 * ::huStreamWriteValue32,
 * ::huStreamWriteValue64
 * ::huStreamBatchMemOp,
 * ::huMemHostRegister,
 * ::huStreamWaitEvent
 */
HUresult HIPAPI huStreamWaitValue32(HUstream stream, HUdeviceptr addr, huuint32_t value, unsigned int flags);

/**
 * \brief Wait on a memory location
 *
 * Enqueues a synchronization of the stream on the given memory location. Work
 * ordered after the operation will block until the given condition on the
 * memory is satisfied. By default, the condition is to wait for
 * (int64_t)(*addr - value) >= 0, a cyclic greater-or-equal.
 * Other condition types can be specified via \p flags.
 *
 * If the memory was registered via ::huMemHostRegister(), the device pointer
 * should be obtained with ::huMemHostGetDevicePointer().
 *
 * Support for this can be queried with ::huDeviceGetAttribute() and
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_64_BIT_STREAM_MEM_OPS.
 *
 * \param stream The stream to synchronize on the memory location.
 * \param addr The memory location to wait on.
 * \param value The value to compare with the memory location.
 * \param flags See ::HUstreamWaitValue_flags.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_SUPPORTED
 * \notefnerr
 *
 * \sa ::huStreamWaitValue32,
 * ::huStreamWriteValue32,
 * ::huStreamWriteValue64,
 * ::huStreamBatchMemOp,
 * ::huMemHostRegister,
 * ::huStreamWaitEvent
 */
HUresult HIPAPI huStreamWaitValue64(HUstream stream, HUdeviceptr addr, huuint64_t value, unsigned int flags);

/**
 * \brief Write a value to memory
 *
 * Write a value to memory. Unless the ::HU_STREAM_WRITE_VALUE_NO_MEMORY_BARRIER
 * flag is passed, the write is preceded by a system-wide memory fence,
 * equivalent to a __threadfence_system() but scoped to the stream
 * rather than a HIP thread.
 *
 * If the memory was registered via ::huMemHostRegister(), the device pointer
 * should be obtained with ::huMemHostGetDevicePointer(). This function cannot
 * be used with managed memory (::huMemAllocManaged).
 *
 * Support for this can be queried with ::huDeviceGetAttribute() and
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_MEM_OPS.
 *
 * \param stream The stream to do the write in.
 * \param addr The device address to write to.
 * \param value The value to write.
 * \param flags See ::HUstreamWriteValue_flags.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_SUPPORTED
 * \notefnerr
 *
 * \sa ::huStreamWriteValue64,
 * ::huStreamWaitValue32,
 * ::huStreamWaitValue64,
 * ::huStreamBatchMemOp,
 * ::huMemHostRegister,
 * ::huEventRecord
 */
HUresult HIPAPI huStreamWriteValue32(HUstream stream, HUdeviceptr addr, huuint32_t value, unsigned int flags);

/**
 * \brief Write a value to memory
 *
 * Write a value to memory. Unless the ::HU_STREAM_WRITE_VALUE_NO_MEMORY_BARRIER
 * flag is passed, the write is preceded by a system-wide memory fence,
 * equivalent to a __threadfence_system() but scoped to the stream
 * rather than a HIP thread.
 *
 * If the memory was registered via ::huMemHostRegister(), the device pointer
 * should be obtained with ::huMemHostGetDevicePointer().
 *
 * Support for this can be queried with ::huDeviceGetAttribute() and
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_64_BIT_STREAM_MEM_OPS.
 *
 * \param stream The stream to do the write in.
 * \param addr The device address to write to.
 * \param value The value to write.
 * \param flags See ::HUstreamWriteValue_flags.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_SUPPORTED
 * \notefnerr
 *
 * \sa ::huStreamWriteValue32,
 * ::huStreamWaitValue32,
 * ::huStreamWaitValue64,
 * ::huStreamBatchMemOp,
 * ::huMemHostRegister,
 * ::huEventRecord
 */
HUresult HIPAPI huStreamWriteValue64(HUstream stream, HUdeviceptr addr, huuint64_t value, unsigned int flags);

/**
 * \brief Batch operations to synchronize the stream via memory operations
 *
 * This is a batch version of ::huStreamWaitValue32() and ::huStreamWriteValue32().
 * Batching operations may avoid some performance overhead in both the API call
 * and the device execution versus adding them to the stream in separate API
 * calls. The operations are enqueued in the order they appear in the array.
 *
 * See ::HUstreamBatchMemOpType for the full set of supported operations, and
 * ::huStreamWaitValue32(), ::huStreamWaitValue64(), ::huStreamWriteValue32(),
 * and ::huStreamWriteValue64() for details of specific operations.
 *
 * Basic support for this can be queried with ::huDeviceGetAttribute() and
 * ::HU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_MEM_OPS. See related APIs for details
 * on querying support for specific operations.
 *
 * \param stream The stream to enqueue the operations in.
 * \param count The number of operations in the array. Must be less than 256.
 * \param paramArray The types and parameters of the individual operations.
 * \param flags Reserved for future expansion; must be 0.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_NOT_SUPPORTED
 * \notefnerr
 *
 * \sa ::huStreamWaitValue32,
 * ::huStreamWaitValue64,
 * ::huStreamWriteValue32,
 * ::huStreamWriteValue64,
 * ::huMemHostRegister
 */
HUresult HIPAPI huStreamBatchMemOp(HUstream stream, unsigned int count, HUstreamBatchMemOpParams *paramArray, unsigned int flags);

/** @} */ /* END HIP_MEMOP */

/**
 * \defgroup HIP_EXEC Execution Control
 *
 * ___MANBRIEF___ execution control functions of the low-level HIP driver API
 * (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the execution control functions of the low-level HIP
 * driver application programming interface.
 *
 * @{
 */

/**
 * \brief Returns information about a function
 *
 * Returns in \p *pi the integer value of the attribute \p attrib on the kernel
 * given by \p hfunc. The supported attributes are:
 * - ::HU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK: The maximum number of threads
 *   per block, beyond which a launch of the function would fail. This number
 *   depends on both the function and the device on which the function is
 *   currently loaded.
 * - ::HU_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES: The size in bytes of
 *   statically-allocated shared memory per block required by this function.
 *   This does not include dynamically-allocated shared memory requested by
 *   the user at runtime.
 * - ::HU_FUNC_ATTRIBUTE_CONST_SIZE_BYTES: The size in bytes of user-allocated
 *   constant memory required by this function.
 * - ::HU_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES: The size in bytes of local memory
 *   used by each thread of this function.
 * - ::HU_FUNC_ATTRIBUTE_NUM_REGS: The number of registers used by each thread
 *   of this function.
 * - ::HU_FUNC_ATTRIBUTE_PTX_VERSION: The PTX virtual architecture version for
 *   which the function was compiled. This value is the major PTX version * 10
 *   + the minor PTX version, so a PTX version 1.3 function would return the
 *   value 13. Note that this may return the undefined value of 0 for hubins
 *   compiled prior to HIP 3.0.
 * - ::HU_FUNC_ATTRIBUTE_BINARY_VERSION: The binary architecture version for
 *   which the function was compiled. This value is the major binary
 *   version * 10 + the minor binary version, so a binary version 1.3 function
 *   would return the value 13. Note that this will return a value of 10 for
 *   legacy hubins that do not have a properly-encoded binary architecture
 *   version.
 * - ::HU_FUNC_CACHE_MODE_CA: The attribute to indicate whether the function has  
 *   been compiled with user specified option "-Xptxas --dlcm=ca" set .
 * - ::HU_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES: The maximum size in bytes of
 *   dynamically-allocated shared memory. 
 * - ::HU_FUNC_ATTRIBUTE_PREFERRED_SHARED_MEMORY_CARVEOUT: Preferred shared memory-L1 
 *   cache split ratio in percent of total shared memory.
 *
 * \param pi     - Returned attribute value
 * \param attrib - Attribute requested
 * \param hfunc  - Function to query attribute of
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huCtxGetCacheConfig,
 * ::huCtxSetCacheConfig,
 * ::huFuncSetCacheConfig,
 * ::huLaunchKernel,
 * ::hipFuncGetAttributes
 * ::hipFuncSetAttribute
 */
HUresult HIPAPI huFuncGetAttribute(int *pi, HUfunction_attribute attrib, HUfunction hfunc);

/**
 * \brief Sets information about a function
 *
 * This call sets the value of a specified attribute \p attrib on the kernel given
 * by \p hfunc to an integer value specified by \p val
 * This function returns HIP_SUCCESS if the new value of the attribute could be
 * successfully set. If the set fails, this call will return an error.
 * Not all attributes can have values set. Attempting to set a value on a read-only
 * attribute will result in an error (HIP_ERROR_INVALID_VALUE)
 *
 * Supported attributes for the huFuncSetAttribute call are:
 * - ::HU_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES: This maximum size in bytes of
 *   dynamically-allocated shared memory. The value should contain the requested
 *   maximum size of dynamically-allocated shared memory. The sum of this value and
 *   the function attribute ::HU_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES cannot exceed the
 *   device attribute ::HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK_OPTIN.
 *   The maximal size of requestable dynamic shared memory may differ by GPU
 *   architecture.
 * - ::HU_FUNC_ATTRIBUTE_PREFERRED_SHARED_MEMORY_CARVEOUT: On devices where the L1 
 *   cache and shared memory use the same hardware resources, this sets the shared memory
 *   carveout preference, in percent of the total shared memory. 
 *   See ::HU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_MULTIPROCESSOR
 *   This is only a hint, and the driver can choose a different ratio if required to execute the function.
 *
 * \param hfunc  - Function to query attribute of
 * \param attrib - Attribute requested
 * \param value   - The value to set
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huCtxGetCacheConfig,
 * ::huCtxSetCacheConfig,
 * ::huFuncSetCacheConfig,
 * ::huLaunchKernel,
 * ::hipFuncGetAttributes
 * ::hipFuncSetAttribute
 */
HUresult HIPAPI huFuncSetAttribute(HUfunction hfunc, HUfunction_attribute attrib, int value);

/**
 * \brief Sets the preferred cache configuration for a device function
 *
 * On devices where the L1 cache and shared memory use the same hardware
 * resources, this sets through \p config the preferred cache configuration for
 * the device function \p hfunc. This is only a preference. The driver will use
 * the requested configuration if possible, but it is free to choose a different
 * configuration if required to execute \p hfunc.  Any context-wide preference
 * set via ::huCtxSetCacheConfig() will be overridden by this per-function
 * setting unless the per-function setting is ::HU_FUNC_CACHE_PREFER_NONE. In
 * that case, the current context-wide setting will be used.
 *
 * This setting does nothing on devices where the size of the L1 cache and
 * shared memory are fixed.
 *
 * Launching a kernel with a different preference than the most recent
 * preference setting may insert a device-side synchronization point.
 *
 *
 * The supported cache configurations are:
 * - ::HU_FUNC_CACHE_PREFER_NONE: no preference for shared memory or L1 (default)
 * - ::HU_FUNC_CACHE_PREFER_SHARED: prefer larger shared memory and smaller L1 cache
 * - ::HU_FUNC_CACHE_PREFER_L1: prefer larger L1 cache and smaller shared memory
 * - ::HU_FUNC_CACHE_PREFER_EQUAL: prefer equal sized L1 cache and shared memory
 *
 * \param hfunc  - Kernel to configure cache for
 * \param config - Requested cache configuration
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT
 * \notefnerr
 *
 * \sa ::huCtxGetCacheConfig,
 * ::huCtxSetCacheConfig,
 * ::huFuncGetAttribute,
 * ::huLaunchKernel,
 * ::hipFuncSetCacheConfig
 */
HUresult HIPAPI huFuncSetCacheConfig(HUfunction hfunc, HUfunc_cache config);

/**
 * \brief Sets the shared memory configuration for a device function.
 *
 * On devices with configurable shared memory banks, this function will 
 * force all subsequent launches of the specified device function to have
 * the given shared memory bank size configuration. On any given launch of the
 * function, the shared memory configuration of the device will be temporarily
 * changed if needed to suit the function's preferred configuration. Changes in
 * shared memory configuration between subsequent launches of functions, 
 * may introduce a device side synchronization point.
 *
 * Any per-function setting of shared memory bank size set via 
 * ::huFuncSetSharedMemConfig will override the context wide setting set with
 * ::huCtxSetSharedMemConfig.
 *
 * Changing the shared memory bank size will not increase shared memory usage
 * or affect occupancy of kernels, but may have major effects on performance. 
 * Larger bank sizes will allow for greater potential bandwidth to shared memory,
 * but will change what kinds of accesses to shared memory will result in bank 
 * conflicts.
 *
 * This function will do nothing on devices with fixed shared memory bank size.
 *
 * The supported bank configurations are:
 * - ::HU_SHARED_MEM_CONFIG_DEFAULT_BANK_SIZE: use the context's shared memory 
 *   configuration when launching this function.
 * - ::HU_SHARED_MEM_CONFIG_FOUR_BYTE_BANK_SIZE: set shared memory bank width to
 *   be natively four bytes when launching this function.
 * - ::HU_SHARED_MEM_CONFIG_EIGHT_BYTE_BANK_SIZE: set shared memory bank width to
 *   be natively eight bytes when launching this function.
 *
 * \param hfunc  - kernel to be given a shared memory config
 * \param config - requested shared memory configuration
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT
 * \notefnerr
 *
 * \sa ::huCtxGetCacheConfig,
 * ::huCtxSetCacheConfig,
 * ::huCtxGetSharedMemConfig,
 * ::huCtxSetSharedMemConfig,
 * ::huFuncGetAttribute,
 * ::huLaunchKernel,
 * ::hipFuncSetSharedMemConfig
 */
HUresult HIPAPI huFuncSetSharedMemConfig(HUfunction hfunc, HUsharedconfig config);

/**
 * \brief Launches a HIP function
 *
 * Invokes the kernel \p f on a \p gridDimX x \p gridDimY x \p gridDimZ
 * grid of blocks. Each block contains \p blockDimX x \p blockDimY x
 * \p blockDimZ threads.
 *
 * \p sharedMemBytes sets the amount of dynamic shared memory that will be
 * available to each thread block.
 *
 * Kernel parameters to \p f can be specified in one of two ways:
 *
 * 1) Kernel parameters can be specified via \p kernelParams.  If \p f
 * has N parameters, then \p kernelParams needs to be an array of N
 * pointers.  Each of \p kernelParams[0] through \p kernelParams[N-1]
 * must point to a region of memory from which the actual kernel
 * parameter will be copied.  The number of kernel parameters and their
 * offsets and sizes do not need to be specified as that information is
 * retrieved directly from the kernel's image.
 *
 * 2) Kernel parameters can also be packaged by the application into
 * a single buffer that is passed in via the \p extra parameter.
 * This places the burden on the application of knowing each kernel
 * parameter's size and alignment/padding within the buffer.  Here is
 * an example of using the \p extra parameter in this manner:
 * \code
    size_t argBufferSize;
    char argBuffer[256];

    // populate argBuffer and argBufferSize

    void *config[] = {
        HU_LAUNCH_PARAM_BUFFER_POINTER, argBuffer,
        HU_LAUNCH_PARAM_BUFFER_SIZE,    &argBufferSize,
        HU_LAUNCH_PARAM_END
    };
    status = huLaunchKernel(f, gx, gy, gz, bx, by, bz, sh, s, NULL, config);
 * \endcode
 *
 * The \p extra parameter exists to allow ::huLaunchKernel to take
 * additional less commonly used arguments.  \p extra specifies a list of
 * names of extra settings and their corresponding values.  Each extra
 * setting name is immediately followed by the corresponding value.  The
 * list must be terminated with either NULL or ::HU_LAUNCH_PARAM_END.
 *
 * - ::HU_LAUNCH_PARAM_END, which indicates the end of the \p extra
 *   array;
 * - ::HU_LAUNCH_PARAM_BUFFER_POINTER, which specifies that the next
 *   value in \p extra will be a pointer to a buffer containing all
 *   the kernel parameters for launching kernel \p f;
 * - ::HU_LAUNCH_PARAM_BUFFER_SIZE, which specifies that the next
 *   value in \p extra will be a pointer to a size_t containing the
 *   size of the buffer specified with ::HU_LAUNCH_PARAM_BUFFER_POINTER;
 *
 * The error ::HIP_ERROR_INVALID_VALUE will be returned if kernel
 * parameters are specified with both \p kernelParams and \p extra
 * (i.e. both \p kernelParams and \p extra are non-NULL).
 *
 * Calling ::huLaunchKernel() sets persistent function state that is
 * the same as function state set through the following deprecated APIs:
 *  ::huFuncSetBlockShape(),
 *  ::huFuncSetSharedSize(),
 *  ::huParamSetSize(),
 *  ::huParamSeti(),
 *  ::huParamSetf(),
 *  ::huParamSetv().
 *
 * When the kernel \p f is launched via ::huLaunchKernel(), the previous
 * block shape, shared size and parameter info associated with \p f
 * is overwritten.
 *
 * Note that to use ::huLaunchKernel(), the kernel \p f must either have
 * been compiled with toolchain version 3.2 or later so that it will
 * contain kernel parameter information, or have no kernel parameters.
 * If either of these conditions is not met, then ::huLaunchKernel() will
 * return ::HIP_ERROR_INVALID_IMAGE.
 *
 * \param f              - Kernel to launch
 * \param gridDimX       - Width of grid in blocks
 * \param gridDimY       - Height of grid in blocks
 * \param gridDimZ       - Depth of grid in blocks
 * \param blockDimX      - X dimension of each thread block
 * \param blockDimY      - Y dimension of each thread block
 * \param blockDimZ      - Z dimension of each thread block
 * \param sharedMemBytes - Dynamic shared-memory size per thread block in bytes
 * \param hStream        - Stream identifier
 * \param kernelParams   - Array of pointers to kernel parameters
 * \param extra          - Extra options
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_IMAGE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_LAUNCH_FAILED,
 * ::HIP_ERROR_LAUNCH_OUT_OF_RESOURCES,
 * ::HIP_ERROR_LAUNCH_TIMEOUT,
 * ::HIP_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huCtxGetCacheConfig,
 * ::huCtxSetCacheConfig,
 * ::huFuncSetCacheConfig,
 * ::huFuncGetAttribute,
 * ::hipLaunchKernel
 */
HUresult HIPAPI huLaunchKernel(HUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, HUstream hStream, void **kernelParams, void **extra);

/**
 * \brief Launches a HIP function where thread blocks can cooperate and synchronize as they execute
 *
 * Invokes the kernel \p f on a \p gridDimX x \p gridDimY x \p gridDimZ
 * grid of blocks. Each block contains \p blockDimX x \p blockDimY x
 * \p blockDimZ threads.
 *
 * \p sharedMemBytes sets the amount of dynamic shared memory that will be
 * available to each thread block.
 *
 * The device on which this kernel is invoked must have a non-zero value for
 * the device attribute ::HU_DEVICE_ATTRIBUTE_COOPERATIVE_LAUNCH.
 *
 * The total number of blocks launched cannot exceed the maximum number of blocks per
 * multiprocessor as returned by ::huOccupancyMaxActiveBlocksPerMultiprocessor (or
 * ::huOccupancyMaxActiveBlocksPerMultiprocessorWithFlags) times the number of multiprocessors
 * as specified by the device attribute ::HU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT.
 *
 * The kernel cannot make use of HIP dynamic parallelism.
 *
 * Kernel parameters must be specified via \p kernelParams.  If \p f
 * has N parameters, then \p kernelParams needs to be an array of N
 * pointers.  Each of \p kernelParams[0] through \p kernelParams[N-1]
 * must point to a region of memory from which the actual kernel
 * parameter will be copied.  The number of kernel parameters and their
 * offsets and sizes do not need to be specified as that information is
 * retrieved directly from the kernel's image.
 *
 * Calling ::huLaunchCooperativeKernel() sets persistent function state that is
 * the same as function state set through ::huLaunchKernel API
 *
 * When the kernel \p f is launched via ::huLaunchCooperativeKernel(), the previous
 * block shape, shared size and parameter info associated with \p f
 * is overwritten.
 *
 * Note that to use ::huLaunchCooperativeKernel(), the kernel \p f must either have
 * been compiled with toolchain version 3.2 or later so that it will
 * contain kernel parameter information, or have no kernel parameters.
 * If either of these conditions is not met, then ::huLaunchCooperativeKernel() will
 * return ::HIP_ERROR_INVALID_IMAGE.
 *
 * \param f              - Kernel to launch
 * \param gridDimX       - Width of grid in blocks
 * \param gridDimY       - Height of grid in blocks
 * \param gridDimZ       - Depth of grid in blocks
 * \param blockDimX      - X dimension of each thread block
 * \param blockDimY      - Y dimension of each thread block
 * \param blockDimZ      - Z dimension of each thread block
 * \param sharedMemBytes - Dynamic shared-memory size per thread block in bytes
 * \param hStream        - Stream identifier
 * \param kernelParams   - Array of pointers to kernel parameters
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_IMAGE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_LAUNCH_FAILED,
 * ::HIP_ERROR_LAUNCH_OUT_OF_RESOURCES,
 * ::HIP_ERROR_LAUNCH_TIMEOUT,
 * ::HIP_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING,
 * ::HIP_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huCtxGetCacheConfig,
 * ::huCtxSetCacheConfig,
 * ::huFuncSetCacheConfig,
 * ::huFuncGetAttribute,
 * ::huLaunchCooperativeKernelMultiDevice,
 * ::hipLaunchCooperativeKernel
 */
HUresult HIPAPI huLaunchCooperativeKernel(HUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, HUstream hStream, void **kernelParams);

/**
 * \brief Launches HIP functions on multiple devices where thread blocks can cooperate and synchronize as they execute
 *
 * Invokes kernels as specified in the \p launchParamsList array where each element
 * of the array specifies all the parameters required to perform a single kernel launch.
 * These kernels can cooperate and synchronize as they execute. The size of the array is
 * specified by \p numDevices.
 *
 * No two kernels can be launched on the same device. All the devices targeted by this
 * multi-device launch must be identical. All devices must have a non-zero value for the
 * device attribute ::HU_DEVICE_ATTRIBUTE_COOPERATIVE_MULTI_DEVICE_LAUNCH.
 * 
 * All kernels launched must be identical with respect to the compiled code. Note that
 * any __device__, __constant__ or __managed__ variables present in the module that owns
 * the kernel launched on each device, are independently instantiated on every device.
 * It is the application's responsiblity to ensure these variables are initialized and
 * used appropriately.
 *
 * The size of the grids as specified in blocks, the size of the blocks themselves
 * and the amount of shared memory used by each thread block must also match across
 * all launched kernels.
 *
 * The streams used to launch these kernels must have been created via either ::huStreamCreate
 * or ::huStreamCreateWithPriority. The NULL stream or ::HU_STREAM_LEGACY or ::HU_STREAM_PER_THREAD
 * cannot be used.
 *
 * The total number of blocks launched per kernel cannot exceed the maximum number of blocks
 * per multiprocessor as returned by ::huOccupancyMaxActiveBlocksPerMultiprocessor (or
 * ::huOccupancyMaxActiveBlocksPerMultiprocessorWithFlags) times the number of multiprocessors
 * as specified by the device attribute ::HU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT. Since the
 * total number of blocks launched per device has to match across all devices, the maximum
 * number of blocks that can be launched per device will be limited by the device with the
 * least number of multiprocessors.
 *
 * The kernels cannot make use of HIP dynamic parallelism.
 *
 * The ::HIP_LAUNCH_PARAMS structure is defined as:
 * \code
        typedef struct HIP_LAUNCH_PARAMS_st
        {
            HUfunction function;
            unsigned int gridDimX;
            unsigned int gridDimY;
            unsigned int gridDimZ;
            unsigned int blockDimX;
            unsigned int blockDimY;
            unsigned int blockDimZ;
            unsigned int sharedMemBytes;
            HUstream hStream;
            void **kernelParams;
        } HIP_LAUNCH_PARAMS;
 * \endcode
 * where:
 * - ::HIP_LAUNCH_PARAMS::function specifies the kernel to be launched. All functions must
 *   be identical with respect to the compiled code.
 * - ::HIP_LAUNCH_PARAMS::gridDimX is the width of the grid in blocks. This must match across
 *   all kernels launched.
 * - ::HIP_LAUNCH_PARAMS::gridDimY is the height of the grid in blocks. This must match across
 *   all kernels launched.
 * - ::HIP_LAUNCH_PARAMS::gridDimZ is the depth of the grid in blocks. This must match across
 *   all kernels launched.
 * - ::HIP_LAUNCH_PARAMS::blockDimX is the X dimension of each thread block. This must match across
 *   all kernels launched.
 * - ::HIP_LAUNCH_PARAMS::blockDimX is the Y dimension of each thread block. This must match across
 *   all kernels launched.
 * - ::HIP_LAUNCH_PARAMS::blockDimZ is the Z dimension of each thread block. This must match across
 *   all kernels launched.
 * - ::HIP_LAUNCH_PARAMS::sharedMemBytes is the dynamic shared-memory size per thread block in bytes.
 *   This must match across all kernels launched.
 * - ::HIP_LAUNCH_PARAMS::hStream is the handle to the stream to perform the launch in. This cannot
 *   be the NULL stream or ::HU_STREAM_LEGACY or ::HU_STREAM_PER_THREAD. The HIP context associated
 *   with this stream must match that associated with ::HIP_LAUNCH_PARAMS::function.
 * - ::HIP_LAUNCH_PARAMS::kernelParams is an array of pointers to kernel parameters. If
 *   ::HIP_LAUNCH_PARAMS::function has N parameters, then ::HIP_LAUNCH_PARAMS::kernelParams
 *   needs to be an array of N pointers. Each of ::HIP_LAUNCH_PARAMS::kernelParams[0] through
 *   ::HIP_LAUNCH_PARAMS::kernelParams[N-1] must point to a region of memory from which the actual
 *   kernel parameter will be copied. The number of kernel parameters and their offsets and sizes
 *   do not need to be specified as that information is retrieved directly from the kernel's image.
 *
 * By default, the kernel won't begin execution on any GPU until all prior work in all the specified
 * streams has completed. This behavior can be overridden by specifying the flag
 * ::HIP_COOPERATIVE_LAUNCH_MULTI_DEVICE_NO_PRE_LAUNCH_SYNC. When this flag is specified, each kernel
 * will only wait for prior work in the stream corresponding to that GPU to complete before it begins
 * execution.
 *
 * Similarly, by default, any subsequent work pushed in any of the specified streams will not begin
 * execution until the kernels on all GPUs have completed. This behavior can be overridden by specifying
 * the flag ::HIP_COOPERATIVE_LAUNCH_MULTI_DEVICE_NO_POST_LAUNCH_SYNC. When this flag is specified,
 * any subsequent work pushed in any of the specified streams will only wait for the kernel launched
 * on the GPU corresponding to that stream to complete before it begins execution.
 *
 * Calling ::huLaunchCooperativeKernelMultiDevice() sets persistent function state that is
 * the same as function state set through ::huLaunchKernel API when called individually for each
 * element in \p launchParamsList.
 *
 * When kernels are launched via ::huLaunchCooperativeKernelMultiDevice(), the previous
 * block shape, shared size and parameter info associated with each ::HIP_LAUNCH_PARAMS::function
 * in \p launchParamsList is overwritten.
 *
 * Note that to use ::huLaunchCooperativeKernelMultiDevice(), the kernels must either have
 * been compiled with toolchain version 3.2 or later so that it will
 * contain kernel parameter information, or have no kernel parameters.
 * If either of these conditions is not met, then ::huLaunchCooperativeKernelMultiDevice() will
 * return ::HIP_ERROR_INVALID_IMAGE.
 *
 * \param launchParamsList - List of launch parameters, one per device
 * \param numDevices       - Size of the \p launchParamsList array
 * \param flags            - Flags to control launch behavior
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_IMAGE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_LAUNCH_FAILED,
 * ::HIP_ERROR_LAUNCH_OUT_OF_RESOURCES,
 * ::HIP_ERROR_LAUNCH_TIMEOUT,
 * ::HIP_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING,
 * ::HIP_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huCtxGetCacheConfig,
 * ::huCtxSetCacheConfig,
 * ::huFuncSetCacheConfig,
 * ::huFuncGetAttribute,
 * ::huLaunchCooperativeKernel,
 * ::hipLaunchCooperativeKernelMultiDevice
 */
HUresult HIPAPI huLaunchCooperativeKernelMultiDevice(HIP_LAUNCH_PARAMS *launchParamsList, unsigned int numDevices, unsigned int flags);

/** @} */ /* END HIP_EXEC */

/**
 * \defgroup HIP_EXEC_DEPRECATED Execution Control [DEPRECATED]
 *
 * ___MANBRIEF___ deprecated execution control functions of the low-level HIP
 * driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the deprecated execution control functions of the
 * low-level HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Sets the block-dimensions for the function
 *
 * \deprecated
 *
 * Specifies the \p x, \p y, and \p z dimensions of the thread blocks that are
 * created when the kernel given by \p hfunc is launched.
 *
 * \param hfunc - Kernel to specify dimensions of
 * \param x     - X dimension
 * \param y     - Y dimension
 * \param z     - Z dimension
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huFuncSetSharedSize,
 * ::huFuncSetCacheConfig,
 * ::huFuncGetAttribute,
 * ::huParamSetSize,
 * ::huParamSeti,
 * ::huParamSetf,
 * ::huParamSetv,
 * ::huLaunch,
 * ::huLaunchGrid,
 * ::huLaunchGridAsync,
 * ::huLaunchKernel
 */
__HIP_DEPRECATED HUresult HIPAPI huFuncSetBlockShape(HUfunction hfunc, int x, int y, int z);

/**
 * \brief Sets the dynamic shared-memory size for the function
 *
 * \deprecated
 *
 * Sets through \p bytes the amount of dynamic shared memory that will be
 * available to each thread block when the kernel given by \p hfunc is launched.
 *
 * \param hfunc - Kernel to specify dynamic shared-memory size for
 * \param bytes - Dynamic shared-memory size per thread in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huFuncSetBlockShape,
 * ::huFuncSetCacheConfig,
 * ::huFuncGetAttribute,
 * ::huParamSetSize,
 * ::huParamSeti,
 * ::huParamSetf,
 * ::huParamSetv,
 * ::huLaunch,
 * ::huLaunchGrid,
 * ::huLaunchGridAsync,
 * ::huLaunchKernel
 */
__HIP_DEPRECATED HUresult HIPAPI huFuncSetSharedSize(HUfunction hfunc, unsigned int bytes);

/**
 * \brief Sets the parameter size for the function
 *
 * \deprecated
 *
 * Sets through \p numbytes the total size in bytes needed by the function
 * parameters of the kernel corresponding to \p hfunc.
 *
 * \param hfunc    - Kernel to set parameter size for
 * \param numbytes - Size of parameter list in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huFuncSetBlockShape,
 * ::huFuncSetSharedSize,
 * ::huFuncGetAttribute,
 * ::huParamSetf,
 * ::huParamSeti,
 * ::huParamSetv,
 * ::huLaunch,
 * ::huLaunchGrid,
 * ::huLaunchGridAsync,
 * ::huLaunchKernel
 */
__HIP_DEPRECATED HUresult HIPAPI huParamSetSize(HUfunction hfunc, unsigned int numbytes);

/**
 * \brief Adds an integer parameter to the function's argument list
 *
 * \deprecated
 *
 * Sets an integer parameter that will be specified the next time the
 * kernel corresponding to \p hfunc will be invoked. \p offset is a byte offset.
 *
 * \param hfunc  - Kernel to add parameter to
 * \param offset - Offset to add parameter to argument list
 * \param value  - Value of parameter
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huFuncSetBlockShape,
 * ::huFuncSetSharedSize,
 * ::huFuncGetAttribute,
 * ::huParamSetSize,
 * ::huParamSetf,
 * ::huParamSetv,
 * ::huLaunch,
 * ::huLaunchGrid,
 * ::huLaunchGridAsync,
 * ::huLaunchKernel
 */
__HIP_DEPRECATED HUresult HIPAPI huParamSeti(HUfunction hfunc, int offset, unsigned int value);

/**
 * \brief Adds a floating-point parameter to the function's argument list
 *
 * \deprecated
 *
 * Sets a floating-point parameter that will be specified the next time the
 * kernel corresponding to \p hfunc will be invoked. \p offset is a byte offset.
 *
 * \param hfunc  - Kernel to add parameter to
 * \param offset - Offset to add parameter to argument list
 * \param value  - Value of parameter
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huFuncSetBlockShape,
 * ::huFuncSetSharedSize,
 * ::huFuncGetAttribute,
 * ::huParamSetSize,
 * ::huParamSeti,
 * ::huParamSetv,
 * ::huLaunch,
 * ::huLaunchGrid,
 * ::huLaunchGridAsync,
 * ::huLaunchKernel
 */
__HIP_DEPRECATED HUresult HIPAPI huParamSetf(HUfunction hfunc, int offset, float value);

/**
 * \brief Adds arbitrary data to the function's argument list
 *
 * \deprecated
 *
 * Copies an arbitrary amount of data (specified in \p numbytes) from \p ptr
 * into the parameter space of the kernel corresponding to \p hfunc. \p offset
 * is a byte offset.
 *
 * \param hfunc    - Kernel to add data to
 * \param offset   - Offset to add data to argument list
 * \param ptr      - Pointer to arbitrary data
 * \param numbytes - Size of data to copy in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa ::huFuncSetBlockShape,
 * ::huFuncSetSharedSize,
 * ::huFuncGetAttribute,
 * ::huParamSetSize,
 * ::huParamSetf,
 * ::huParamSeti,
 * ::huLaunch,
 * ::huLaunchGrid,
 * ::huLaunchGridAsync,
 * ::huLaunchKernel
 */
__HIP_DEPRECATED HUresult HIPAPI huParamSetv(HUfunction hfunc, int offset, void *ptr, unsigned int numbytes);

/**
 * \brief Launches a HIP function
 *
 * \deprecated
 *
 * Invokes the kernel \p f on a 1 x 1 x 1 grid of blocks. The block
 * contains the number of threads specified by a previous call to
 * ::huFuncSetBlockShape().
 *
 * \param f - Kernel to launch
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_LAUNCH_FAILED,
 * ::HIP_ERROR_LAUNCH_OUT_OF_RESOURCES,
 * ::HIP_ERROR_LAUNCH_TIMEOUT,
 * ::HIP_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED
 * \notefnerr
 *
 * \sa ::huFuncSetBlockShape,
 * ::huFuncSetSharedSize,
 * ::huFuncGetAttribute,
 * ::huParamSetSize,
 * ::huParamSetf,
 * ::huParamSeti,
 * ::huParamSetv,
 * ::huLaunchGrid,
 * ::huLaunchGridAsync,
 * ::huLaunchKernel
 */
__HIP_DEPRECATED HUresult HIPAPI huLaunch(HUfunction f);

/**
 * \brief Launches a HIP function
 *
 * \deprecated
 *
 * Invokes the kernel \p f on a \p grid_width x \p grid_height grid of
 * blocks. Each block contains the number of threads specified by a previous
 * call to ::huFuncSetBlockShape().
 *
 * \param f           - Kernel to launch
 * \param grid_width  - Width of grid in blocks
 * \param grid_height - Height of grid in blocks
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_LAUNCH_FAILED,
 * ::HIP_ERROR_LAUNCH_OUT_OF_RESOURCES,
 * ::HIP_ERROR_LAUNCH_TIMEOUT,
 * ::HIP_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED
 * \notefnerr
 *
 * \sa ::huFuncSetBlockShape,
 * ::huFuncSetSharedSize,
 * ::huFuncGetAttribute,
 * ::huParamSetSize,
 * ::huParamSetf,
 * ::huParamSeti,
 * ::huParamSetv,
 * ::huLaunch,
 * ::huLaunchGridAsync,
 * ::huLaunchKernel
 */
__HIP_DEPRECATED HUresult HIPAPI huLaunchGrid(HUfunction f, int grid_width, int grid_height);

/**
 * \brief Launches a HIP function
 *
 * \deprecated
 *
 * Invokes the kernel \p f on a \p grid_width x \p grid_height grid of
 * blocks. Each block contains the number of threads specified by a previous
 * call to ::huFuncSetBlockShape().
 *
 * \param f           - Kernel to launch
 * \param grid_width  - Width of grid in blocks
 * \param grid_height - Height of grid in blocks
 * \param hStream     - Stream identifier
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_LAUNCH_FAILED,
 * ::HIP_ERROR_LAUNCH_OUT_OF_RESOURCES,
 * ::HIP_ERROR_LAUNCH_TIMEOUT,
 * ::HIP_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING,
 * ::HIP_ERROR_SHARED_OBJECT_INIT_FAILED
 *
 * \note In certain cases where hubins are created with no ABI (i.e., using \p ptxas \p --abi-compile \p no), 
 *       this function may serialize kernel launches. In order to force the HIP driver to retain 
 *		 asynchronous behavior, set the ::HU_CTX_LMEM_RESIZE_TO_MAX flag during context creation (see ::huCtxCreate).
 *       
 * \note_null_stream
 * \notefnerr
 *
 * \sa ::huFuncSetBlockShape,
 * ::huFuncSetSharedSize,
 * ::huFuncGetAttribute,
 * ::huParamSetSize,
 * ::huParamSetf,
 * ::huParamSeti,
 * ::huParamSetv,
 * ::huLaunch,
 * ::huLaunchGrid,
 * ::huLaunchKernel
 */
__HIP_DEPRECATED HUresult HIPAPI huLaunchGridAsync(HUfunction f, int grid_width, int grid_height, HUstream hStream);


/**
 * \brief Adds a texture-reference to the function's argument list
 *
 * \deprecated
 *
 * Makes the HIP array or linear memory bound to the texture reference
 * \p hTexRef available to a device program as a texture. In this version of
 * HIP, the texture-reference must be obtained via ::huModuleGetTexRef() and
 * the \p texunit parameter must be set to ::HU_PARAM_TR_DEFAULT.
 *
 * \param hfunc   - Kernel to add texture-reference to
 * \param texunit - Texture unit (must be ::HU_PARAM_TR_DEFAULT)
 * \param hTexRef - Texture-reference to add to argument list
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 */
__HIP_DEPRECATED HUresult HIPAPI huParamSetTexRef(HUfunction hfunc, int texunit, HUtexref hTexRef);
/** @} */ /* END HIP_EXEC_DEPRECATED */

/**
 * \defgroup HIP_OCCUPANCY Occupancy
 *
 * ___MANBRIEF___ occupancy calculation functions of the low-level HIP driver
 * API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the occupancy calculation functions of the low-level HIP
 * driver application programming interface.
 *
 * @{
 */

/**
 * \brief Returns occupancy of a function
 *
 * Returns in \p *numBlocks the number of the maximum active blocks per
 * streaming multiprocessor.
 *
 * \param numBlocks       - Returned occupancy
 * \param func            - Kernel for which occupancy is calculated
 * \param blockSize       - Block size the kernel is intended to be launched with
 * \param dynamicSMemSize - Per-block dynamic shared memory usage intended, in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa
 * ::hipOccupancyMaxActiveBlocksPerMultiprocessor
 */
HUresult HIPAPI huOccupancyMaxActiveBlocksPerMultiprocessor(int *numBlocks, HUfunction func, int blockSize, size_t dynamicSMemSize);

/**
 * \brief Returns occupancy of a function
 *
 * Returns in \p *numBlocks the number of the maximum active blocks per
 * streaming multiprocessor.
 *
 * The \p Flags parameter controls how special cases are handled. The
 * valid flags are:
 *
 * - ::HU_OCCUPANCY_DEFAULT, which maintains the default behavior as
 *   ::huOccupancyMaxActiveBlocksPerMultiprocessor;
 *
 * - ::HU_OCCUPANCY_DISABLE_CACHING_OVERRIDE, which suppresses the
 *   default behavior on platform where global caching affects
 *   occupancy. On such platforms, if caching is enabled, but
 *   per-block SM resource usage would result in zero occupancy, the
 *   occupancy calculator will calculate the occupancy as if caching
 *   is disabled. Setting ::HU_OCCUPANCY_DISABLE_CACHING_OVERRIDE makes
 *   the occupancy calculator to return 0 in such cases. More information
 *   can be found about this feature in the "Unified L1/Texture Cache"
 *   section of the Maxwell tuning guide.
 *
 * \param numBlocks       - Returned occupancy
 * \param func            - Kernel for which occupancy is calculated
 * \param blockSize       - Block size the kernel is intended to be launched with
 * \param dynamicSMemSize - Per-block dynamic shared memory usage intended, in bytes
 * \param flags           - Requested behavior for the occupancy calculator
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa
 * ::hipOccupancyMaxActiveBlocksPerMultiprocessorWithFlags
 */
HUresult HIPAPI huOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int *numBlocks, HUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags);
    
/**
 * \brief Suggest a launch configuration with reasonable occupancy
 *
 * Returns in \p *blockSize a reasonable block size that can achieve
 * the maximum occupancy (or, the maximum number of active warps with
 * the fewest blocks per multiprocessor), and in \p *minGridSize the
 * minimum grid size to achieve the maximum occupancy.
 *
 * If \p blockSizeLimit is 0, the configurator will use the maximum
 * block size permitted by the device / function instead.
 *
 * If per-block dynamic shared memory allocation is not needed, the
 * user should leave both \p blockSizeToDynamicSMemSize and \p
 * dynamicSMemSize as 0.
 *
 * If per-block dynamic shared memory allocation is needed, then if
 * the dynamic shared memory size is constant regardless of block
 * size, the size should be passed through \p dynamicSMemSize, and \p
 * blockSizeToDynamicSMemSize should be NULL.
 *
 * Otherwise, if the per-block dynamic shared memory size varies with
 * different block sizes, the user needs to provide a unary function
 * through \p blockSizeToDynamicSMemSize that computes the dynamic
 * shared memory needed by \p func for any given block size. \p
 * dynamicSMemSize is ignored. An example signature is:
 *
 * \code
 *    // Take block size, returns dynamic shared memory needed
 *    size_t blockToSmem(int blockSize);
 * \endcode
 *
 * \param minGridSize - Returned minimum grid size needed to achieve the maximum occupancy
 * \param blockSize   - Returned maximum block size that can achieve the maximum occupancy
 * \param func        - Kernel for which launch configuration is calculated
 * \param blockSizeToDynamicSMemSize - A function that calculates how much per-block dynamic shared memory \p func uses based on the block size
 * \param dynamicSMemSize - Dynamic shared memory usage intended, in bytes
 * \param blockSizeLimit  - The maximum block size \p func is designed to handle
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa
 * ::hipOccupancyMaxPotentialBlockSize
 */
HUresult HIPAPI huOccupancyMaxPotentialBlockSize(int *minGridSize, int *blockSize, HUfunction func, HUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit);

/**
 * \brief Suggest a launch configuration with reasonable occupancy
 *
 * An extended version of ::huOccupancyMaxPotentialBlockSize. In
 * addition to arguments passed to ::huOccupancyMaxPotentialBlockSize,
 * ::huOccupancyMaxPotentialBlockSizeWithFlags also takes a \p Flags
 * parameter.
 *
 * The \p Flags parameter controls how special cases are handled. The
 * valid flags are:
 *
 * - ::HU_OCCUPANCY_DEFAULT, which maintains the default behavior as
 *   ::huOccupancyMaxPotentialBlockSize;
 *
 * - ::HU_OCCUPANCY_DISABLE_CACHING_OVERRIDE, which suppresses the
 *   default behavior on platform where global caching affects
 *   occupancy. On such platforms, the launch configurations that
 *   produces maximal occupancy might not support global
 *   caching. Setting ::HU_OCCUPANCY_DISABLE_CACHING_OVERRIDE
 *   guarantees that the the produced launch configuration is global
 *   caching compatible at a potential cost of occupancy. More information
 *   can be found about this feature in the "Unified L1/Texture Cache"
 *   section of the Maxwell tuning guide.
 *
 * \param minGridSize - Returned minimum grid size needed to achieve the maximum occupancy
 * \param blockSize   - Returned maximum block size that can achieve the maximum occupancy
 * \param func        - Kernel for which launch configuration is calculated
 * \param blockSizeToDynamicSMemSize - A function that calculates how much per-block dynamic shared memory \p func uses based on the block size
 * \param dynamicSMemSize - Dynamic shared memory usage intended, in bytes
 * \param blockSizeLimit  - The maximum block size \p func is designed to handle
 * \param flags       - Options
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa
 * ::hipOccupancyMaxPotentialBlockSizeWithFlags
 */
HUresult HIPAPI huOccupancyMaxPotentialBlockSizeWithFlags(int *minGridSize, int *blockSize, HUfunction func, HUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags);

/** @} */ /* END HIP_OCCUPANCY */

/**
 * \defgroup HIP_TEXREF Texture Reference Management
 *
 * ___MANBRIEF___ texture reference management functions of the low-level HIP
 * driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the texture reference management functions of the
 * low-level HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Binds an array as a texture reference
 *
 * Binds the HIP array \p hArray to the texture reference \p hTexRef. Any
 * previous address or HIP array state associated with the texture reference
 * is superseded by this function. \p Flags must be set to
 * ::HU_TRSA_OVERRIDE_FORMAT. Any HIP array previously bound to \p hTexRef is
 * unbound.
 *
 * \param hTexRef - Texture reference to bind
 * \param hArray  - Array to bind
 * \param Flags   - Options (must be ::HU_TRSA_OVERRIDE_FORMAT)
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTextureToArray
 */
HUresult HIPAPI huTexRefSetArray(HUtexref hTexRef, HUarray hArray, unsigned int Flags);

/**
 * \brief Binds a mipmapped array to a texture reference
 *
 * Binds the HIP mipmapped array \p hMipmappedArray to the texture reference \p hTexRef.
 * Any previous address or HIP array state associated with the texture reference
 * is superseded by this function. \p Flags must be set to ::HU_TRSA_OVERRIDE_FORMAT. 
 * Any HIP array previously bound to \p hTexRef is unbound.
 *
 * \param hTexRef         - Texture reference to bind
 * \param hMipmappedArray - Mipmapped array to bind
 * \param Flags           - Options (must be ::HU_TRSA_OVERRIDE_FORMAT)
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTextureToMipmappedArray
 */
HUresult HIPAPI huTexRefSetMipmappedArray(HUtexref hTexRef, HUmipmappedArray hMipmappedArray, unsigned int Flags);

/**
 * \brief Binds an address as a texture reference
 *
 * Binds a linear address range to the texture reference \p hTexRef. Any
 * previous address or HIP array state associated with the texture reference
 * is superseded by this function. Any memory previously bound to \p hTexRef
 * is unbound.
 *
 * Since the hardware enforces an alignment requirement on texture base
 * addresses, ::huTexRefSetAddress() passes back a byte offset in
 * \p *ByteOffset that must be applied to texture fetches in order to read from
 * the desired memory. This offset must be divided by the texel size and
 * passed to kernels that read from the texture so they can be applied to the
 * ::tex1Dfetch() function.
 *
 * If the device memory pointer was returned from ::huMemAlloc(), the offset
 * is guaranteed to be 0 and NULL may be passed as the \p ByteOffset parameter.
 *
 * The total number of elements (or texels) in the linear address range
 * cannot exceed ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LINEAR_WIDTH.
 * The number of elements is computed as (\p bytes / bytesPerElement),
 * where bytesPerElement is determined from the data format and number of 
 * components set using ::huTexRefSetFormat().
 *
 * \param ByteOffset - Returned byte offset
 * \param hTexRef    - Texture reference to bind
 * \param dptr       - Device pointer to bind
 * \param bytes      - Size of memory to bind in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTexture
 */
HUresult HIPAPI huTexRefSetAddress(size_t *ByteOffset, HUtexref hTexRef, HUdeviceptr dptr, size_t bytes);

/**
 * \brief Binds an address as a 2D texture reference
 *
 * Binds a linear address range to the texture reference \p hTexRef. Any
 * previous address or HIP array state associated with the texture reference
 * is superseded by this function. Any memory previously bound to \p hTexRef
 * is unbound.
 *
 * Using a ::tex2D() function inside a kernel requires a call to either
 * ::huTexRefSetArray() to bind the corresponding texture reference to an
 * array, or ::huTexRefSetAddress2D() to bind the texture reference to linear
 * memory.
 *
 * Function calls to ::huTexRefSetFormat() cannot follow calls to
 * ::huTexRefSetAddress2D() for the same texture reference.
 *
 * It is required that \p dptr be aligned to the appropriate hardware-specific
 * texture alignment. You can query this value using the device attribute
 * ::HU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT. If an unaligned \p dptr is
 * supplied, ::HIP_ERROR_INVALID_VALUE is returned.
 *
 * \p Pitch has to be aligned to the hardware-specific texture pitch alignment.
 * This value can be queried using the device attribute 
 * ::HU_DEVICE_ATTRIBUTE_TEXTURE_PITCH_ALIGNMENT. If an unaligned \p Pitch is 
 * supplied, ::HIP_ERROR_INVALID_VALUE is returned.
 *
 * Width and Height, which are specified in elements (or texels), cannot exceed
 * ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_WIDTH and
 * ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_HEIGHT respectively.
 * \p Pitch, which is specified in bytes, cannot exceed 
 * ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_PITCH.
 *
 * \param hTexRef - Texture reference to bind
 * \param desc    - Descriptor of HIP array
 * \param dptr    - Device pointer to bind
 * \param Pitch   - Line pitch in bytes
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTexture2D
 */
HUresult HIPAPI huTexRefSetAddress2D(HUtexref hTexRef, const HIP_ARRAY_DESCRIPTOR *desc, HUdeviceptr dptr, size_t Pitch);

/**
 * \brief Sets the format for a texture reference
 *
 * Specifies the format of the data to be read by the texture reference
 * \p hTexRef. \p fmt and \p NumPackedComponents are exactly analogous to the
 * ::Format and ::NumChannels members of the ::HIP_ARRAY_DESCRIPTOR structure:
 * They specify the format of each component and the number of components per
 * array element.
 *
 * \param hTexRef             - Texture reference
 * \param fmt                 - Format to set
 * \param NumPackedComponents - Number of components per array element
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipCreateChannelDesc,
 * ::hipBindTexture,
 * ::hipBindTexture2D,
 * ::hipBindTextureToArray,
 * ::hipBindTextureToMipmappedArray
 */
HUresult HIPAPI huTexRefSetFormat(HUtexref hTexRef, HUarray_format fmt, int NumPackedComponents);

/**
 * \brief Sets the addressing mode for a texture reference
 *
 * Specifies the addressing mode \p am for the given dimension \p dim of the
 * texture reference \p hTexRef. If \p dim is zero, the addressing mode is
 * applied to the first parameter of the functions used to fetch from the
 * texture; if \p dim is 1, the second, and so on. ::HUaddress_mode is defined
 * as:
 * \code
   typedef enum HUaddress_mode_enum {
      HU_TR_ADDRESS_MODE_WRAP = 0,
      HU_TR_ADDRESS_MODE_CLAMP = 1,
      HU_TR_ADDRESS_MODE_MIRROR = 2,
      HU_TR_ADDRESS_MODE_BORDER = 3
   } HUaddress_mode;
 * \endcode
 *
 * Note that this call has no effect if \p hTexRef is bound to linear memory.
 * Also, if the flag, ::HU_TRSF_NORMALIZED_COORDINATES, is not set, the only 
 * supported address mode is ::HU_TR_ADDRESS_MODE_CLAMP.
 *
 * \param hTexRef - Texture reference
 * \param dim     - Dimension
 * \param am      - Addressing mode to set
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTexture,
 * ::hipBindTexture2D,
 * ::hipBindTextureToArray,
 * ::hipBindTextureToMipmappedArray
 */
HUresult HIPAPI huTexRefSetAddressMode(HUtexref hTexRef, int dim, HUaddress_mode am);

/**
 * \brief Sets the filtering mode for a texture reference
 *
 * Specifies the filtering mode \p fm to be used when reading memory through
 * the texture reference \p hTexRef. ::HUfilter_mode_enum is defined as:
 *
 * \code
   typedef enum HUfilter_mode_enum {
      HU_TR_FILTER_MODE_POINT = 0,
      HU_TR_FILTER_MODE_LINEAR = 1
   } HUfilter_mode;
 * \endcode
 *
 * Note that this call has no effect if \p hTexRef is bound to linear memory.
 *
 * \param hTexRef - Texture reference
 * \param fm      - Filtering mode to set
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTextureToArray
 */
HUresult HIPAPI huTexRefSetFilterMode(HUtexref hTexRef, HUfilter_mode fm);

/**
 * \brief Sets the mipmap filtering mode for a texture reference
 *
 * Specifies the mipmap filtering mode \p fm to be used when reading memory through
 * the texture reference \p hTexRef. ::HUfilter_mode_enum is defined as:
 *
 * \code
   typedef enum HUfilter_mode_enum {
      HU_TR_FILTER_MODE_POINT = 0,
      HU_TR_FILTER_MODE_LINEAR = 1
   } HUfilter_mode;
 * \endcode
 *
 * Note that this call has no effect if \p hTexRef is not bound to a mipmapped array.
 *
 * \param hTexRef - Texture reference
 * \param fm      - Filtering mode to set
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTextureToMipmappedArray
 */
HUresult HIPAPI huTexRefSetMipmapFilterMode(HUtexref hTexRef, HUfilter_mode fm);

/**
 * \brief Sets the mipmap level bias for a texture reference
 *
 * Specifies the mipmap level bias \p bias to be added to the specified mipmap level when 
 * reading memory through the texture reference \p hTexRef.
 *
 * Note that this call has no effect if \p hTexRef is not bound to a mipmapped array.
 *
 * \param hTexRef - Texture reference
 * \param bias    - Mipmap level bias
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTextureToMipmappedArray
 */
HUresult HIPAPI huTexRefSetMipmapLevelBias(HUtexref hTexRef, float bias);

/**
 * \brief Sets the mipmap min/max mipmap level clamps for a texture reference
 *
 * Specifies the min/max mipmap level clamps, \p minMipmapLevelClamp and \p maxMipmapLevelClamp
 * respectively, to be used when reading memory through the texture reference 
 * \p hTexRef.
 *
 * Note that this call has no effect if \p hTexRef is not bound to a mipmapped array.
 *
 * \param hTexRef        - Texture reference
 * \param minMipmapLevelClamp - Mipmap min level clamp
 * \param maxMipmapLevelClamp - Mipmap max level clamp
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTextureToMipmappedArray
 */
HUresult HIPAPI huTexRefSetMipmapLevelClamp(HUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp);

/**
 * \brief Sets the maximum anisotropy for a texture reference
 *
 * Specifies the maximum anisotropy \p maxAniso to be used when reading memory through
 * the texture reference \p hTexRef. 
 *
 * Note that this call has no effect if \p hTexRef is bound to linear memory.
 *
 * \param hTexRef  - Texture reference
 * \param maxAniso - Maximum anisotropy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTextureToArray,
 * ::hipBindTextureToMipmappedArray
 */
HUresult HIPAPI huTexRefSetMaxAnisotropy(HUtexref hTexRef, unsigned int maxAniso);

/**
 * \brief Sets the border color for a texture reference
 *
 * Specifies the value of the RGBA color via the \p pBorderColor to the texture reference
 * \p hTexRef. The color value supports only float type and holds color components in
 * the following sequence:
 * pBorderColor[0] holds 'R' component
 * pBorderColor[1] holds 'G' component
 * pBorderColor[2] holds 'B' component
 * pBorderColor[3] holds 'A' component
 *
 * Note that the color values can be set only when the Address mode is set to
 * HU_TR_ADDRESS_MODE_BORDER using ::huTexRefSetAddressMode.
 * Applications using integer border color values have to "reinterpret_cast" their values to float.
 *
 * \param hTexRef       - Texture reference
 * \param pBorderColor  - RGBA color
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddressMode,
 * ::huTexRefGetAddressMode, ::huTexRefGetBorderColor,
 * ::hipBindTexture,
 * ::hipBindTexture2D,
 * ::hipBindTextureToArray,
 * ::hipBindTextureToMipmappedArray
 */
HUresult HIPAPI huTexRefSetBorderColor(HUtexref hTexRef, float *pBorderColor);

/**
 * \brief Sets the flags for a texture reference
 *
 * Specifies optional flags via \p Flags to specify the behavior of data
 * returned through the texture reference \p hTexRef. The valid flags are:
 *
 * - ::HU_TRSF_READ_AS_INTEGER, which suppresses the default behavior of
 *   having the texture promote integer data to floating point data in the
 *   range [0, 1]. Note that texture with 32-bit integer format
 *   would not be promoted, regardless of whether or not this
 *   flag is specified;
 * - ::HU_TRSF_NORMALIZED_COORDINATES, which suppresses the 
 *   default behavior of having the texture coordinates range
 *   from [0, Dim) where Dim is the width or height of the HIP
 *   array. Instead, the texture coordinates [0, 1.0) reference
 *   the entire breadth of the array dimension;
 *
 * \param hTexRef - Texture reference
 * \param Flags   - Optional flags to set
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat,
 * ::hipBindTexture,
 * ::hipBindTexture2D,
 * ::hipBindTextureToArray,
 * ::hipBindTextureToMipmappedArray
 */
HUresult HIPAPI huTexRefSetFlags(HUtexref hTexRef, unsigned int Flags);

/**
 * \brief Gets the address associated with a texture reference
 *
 * Returns in \p *pdptr the base address bound to the texture reference
 * \p hTexRef, or returns ::HIP_ERROR_INVALID_VALUE if the texture reference
 * is not bound to any device memory range.
 *
 * \param pdptr   - Returned device address
 * \param hTexRef - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetAddress(HUdeviceptr *pdptr, HUtexref hTexRef);

/**
 * \brief Gets the array bound to a texture reference
 *
 * Returns in \p *phArray the HIP array bound to the texture reference
 * \p hTexRef, or returns ::HIP_ERROR_INVALID_VALUE if the texture reference
 * is not bound to any HIP array.
 *
 * \param phArray - Returned array
 * \param hTexRef - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetArray(HUarray *phArray, HUtexref hTexRef);

/**
 * \brief Gets the mipmapped array bound to a texture reference
 *
 * Returns in \p *phMipmappedArray the HIP mipmapped array bound to the texture 
 * reference \p hTexRef, or returns ::HIP_ERROR_INVALID_VALUE if the texture reference
 * is not bound to any HIP mipmapped array.
 *
 * \param phMipmappedArray - Returned mipmapped array
 * \param hTexRef          - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetMipmappedArray(HUmipmappedArray *phMipmappedArray, HUtexref hTexRef);

/**
 * \brief Gets the addressing mode used by a texture reference
 *
 * Returns in \p *pam the addressing mode corresponding to the
 * dimension \p dim of the texture reference \p hTexRef. Currently, the only
 * valid value for \p dim are 0 and 1.
 *
 * \param pam     - Returned addressing mode
 * \param hTexRef - Texture reference
 * \param dim     - Dimension
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetAddressMode(HUaddress_mode *pam, HUtexref hTexRef, int dim);

/**
 * \brief Gets the filter-mode used by a texture reference
 *
 * Returns in \p *pfm the filtering mode of the texture reference
 * \p hTexRef.
 *
 * \param pfm     - Returned filtering mode
 * \param hTexRef - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFlags, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetFilterMode(HUfilter_mode *pfm, HUtexref hTexRef);

/**
 * \brief Gets the format used by a texture reference
 *
 * Returns in \p *pFormat and \p *pNumChannels the format and number
 * of components of the HIP array bound to the texture reference \p hTexRef.
 * If \p pFormat or \p pNumChannels is NULL, it will be ignored.
 *
 * \param pFormat      - Returned format
 * \param pNumChannels - Returned number of components
 * \param hTexRef      - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags
 */
HUresult HIPAPI huTexRefGetFormat(HUarray_format *pFormat, int *pNumChannels, HUtexref hTexRef);

/**
 * \brief Gets the mipmap filtering mode for a texture reference
 *
 * Returns the mipmap filtering mode in \p pfm that's used when reading memory through
 * the texture reference \p hTexRef.
 *
 * \param pfm     - Returned mipmap filtering mode
 * \param hTexRef - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetMipmapFilterMode(HUfilter_mode *pfm, HUtexref hTexRef);

/**
 * \brief Gets the mipmap level bias for a texture reference
 *
 * Returns the mipmap level bias in \p pBias that's added to the specified mipmap
 * level when reading memory through the texture reference \p hTexRef.
 *
 * \param pbias   - Returned mipmap level bias
 * \param hTexRef - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetMipmapLevelBias(float *pbias, HUtexref hTexRef);

/**
 * \brief Gets the min/max mipmap level clamps for a texture reference
 *
 * Returns the min/max mipmap level clamps in \p pminMipmapLevelClamp and \p pmaxMipmapLevelClamp
 * that's used when reading memory through the texture reference \p hTexRef. 
 *
 * \param pminMipmapLevelClamp - Returned mipmap min level clamp
 * \param pmaxMipmapLevelClamp - Returned mipmap max level clamp
 * \param hTexRef              - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetMipmapLevelClamp(float *pminMipmapLevelClamp, float *pmaxMipmapLevelClamp, HUtexref hTexRef);

/**
 * \brief Gets the maximum anisotropy for a texture reference
 *
 * Returns the maximum anisotropy in \p pmaxAniso that's used when reading memory through
 * the texture reference \p hTexRef. 
 *
 * \param pmaxAniso - Returned maximum anisotropy
 * \param hTexRef   - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFlags, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetMaxAnisotropy(int *pmaxAniso, HUtexref hTexRef);

/**
 * \brief Gets the border color used by a texture reference
 *
 * Returns in \p pBorderColor, values of the RGBA color used by
 * the texture reference \p hTexRef.
 * The color value is of type float and holds color components in
 * the following sequence:
 * pBorderColor[0] holds 'R' component
 * pBorderColor[1] holds 'G' component
 * pBorderColor[2] holds 'B' component
 * pBorderColor[3] holds 'A' component
 *
 * \param hTexRef  - Texture reference
 * \param pBorderColor   - Returned Type and Value of RGBA color
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddressMode,
 * ::huTexRefSetAddressMode, ::huTexRefSetBorderColor
 */
HUresult HIPAPI huTexRefGetBorderColor(float *pBorderColor, HUtexref hTexRef);

/**
 * \brief Gets the flags used by a texture reference
 *
 * Returns in \p *pFlags the flags of the texture reference \p hTexRef.
 *
 * \param pFlags  - Returned flags
 * \param hTexRef - Texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefSetAddress,
 * ::huTexRefSetAddress2D, ::huTexRefSetAddressMode, ::huTexRefSetArray,
 * ::huTexRefSetFilterMode, ::huTexRefSetFlags, ::huTexRefSetFormat,
 * ::huTexRefGetAddress, ::huTexRefGetAddressMode, ::huTexRefGetArray,
 * ::huTexRefGetFilterMode, ::huTexRefGetFormat
 */
HUresult HIPAPI huTexRefGetFlags(unsigned int *pFlags, HUtexref hTexRef);

/** @} */ /* END HIP_TEXREF */

/**
 * \defgroup HIP_TEXREF_DEPRECATED Texture Reference Management [DEPRECATED]
 *
 * ___MANBRIEF___ deprecated texture reference management functions of the
 * low-level HIP driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the deprecated texture reference management
 * functions of the low-level HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Creates a texture reference
 *
 * \deprecated
 *
 * Creates a texture reference and returns its handle in \p *pTexRef. Once
 * created, the application must call ::huTexRefSetArray() or
 * ::huTexRefSetAddress() to associate the reference with allocated memory.
 * Other texture reference functions are used to specify the format and
 * interpretation (addressing, filtering, etc.) to be used when the memory is
 * read through this texture reference.
 *
 * \param pTexRef - Returned texture reference
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefDestroy
 */
__HIP_DEPRECATED HUresult HIPAPI huTexRefCreate(HUtexref *pTexRef);

/**
 * \brief Destroys a texture reference
 *
 * \deprecated
 *
 * Destroys the texture reference specified by \p hTexRef.
 *
 * \param hTexRef - Texture reference to destroy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huTexRefCreate
 */
__HIP_DEPRECATED HUresult HIPAPI huTexRefDestroy(HUtexref hTexRef);

/** @} */ /* END HIP_TEXREF_DEPRECATED */


/**
 * \defgroup HIP_SURFREF Surface Reference Management
 *
 * ___MANBRIEF___ surface reference management functions of the low-level HIP
 * driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the surface reference management functions of the
 * low-level HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Sets the HIP array for a surface reference.
 *
 * Sets the HIP array \p hArray to be read and written by the surface reference
 * \p hSurfRef.  Any previous HIP array state associated with the surface
 * reference is superseded by this function.  \p Flags must be set to 0.
 * The ::HIP_ARRAY3D_SURFACE_LDST flag must have been set for the HIP array.
 * Any HIP array previously bound to \p hSurfRef is unbound.

 * \param hSurfRef - Surface reference handle
 * \param hArray - HIP array handle
 * \param Flags - set to 0
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::huModuleGetSurfRef,
 * ::huSurfRefGetArray,
 * ::hipBindSurfaceToArray
 */
HUresult HIPAPI huSurfRefSetArray(HUsurfref hSurfRef, HUarray hArray, unsigned int Flags);

/**
 * \brief Passes back the HIP array bound to a surface reference.
 *
 * Returns in \p *phArray the HIP array bound to the surface reference
 * \p hSurfRef, or returns ::HIP_ERROR_INVALID_VALUE if the surface reference
 * is not bound to any HIP array.

 * \param phArray - Surface reference handle
 * \param hSurfRef - Surface reference handle
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa ::huModuleGetSurfRef, ::huSurfRefSetArray
 */
HUresult HIPAPI huSurfRefGetArray(HUarray *phArray, HUsurfref hSurfRef);

/** @} */ /* END HIP_SURFREF */

/**
 * \defgroup HIP_TEXOBJECT Texture Object Management
 *
 * ___MANBRIEF___ texture object management functions of the low-level HIP
 * driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the texture object management functions of the
 * low-level HIP driver application programming interface. The texture
 * object API is only supported on devices of compute capability 3.0 or higher.
 *
 * @{
 */

/**
 * \brief Creates a texture object
 *
 * Creates a texture object and returns it in \p pTexObject. \p pResDesc describes
 * the data to texture from. \p pTexDesc describes how the data should be sampled.
 * \p pResViewDesc is an optional argument that specifies an alternate format for
 * the data described by \p pResDesc, and also describes the subresource region
 * to restrict access to when texturing. \p pResViewDesc can only be specified if
 * the type of resource is a HIP array or a HIP mipmapped array.
 *
 * Texture objects are only supported on devices of compute capability 3.0 or higher.
 * Additionally, a texture object is an opaque value, and, as such, should only be
 * accessed through HIP API calls.
 *
 * The ::HIP_RESOURCE_DESC structure is defined as:
 * \code
        typedef struct HIP_RESOURCE_DESC_st
        {
            HUresourcetype resType;

            union {
                struct {
                    HUarray hArray;
                } array;
                struct {
                    HUmipmappedArray hMipmappedArray;
                } mipmap;
                struct {
                    HUdeviceptr devPtr;
                    HUarray_format format;
                    unsigned int numChannels;
                    size_t sizeInBytes;
                } linear;
                struct {
                    HUdeviceptr devPtr;
                    HUarray_format format;
                    unsigned int numChannels;
                    size_t width;
                    size_t height;
                    size_t pitchInBytes;
                } pitch2D;
            } res;

            unsigned int flags;
        } HIP_RESOURCE_DESC;

 * \endcode
 * where:
 * - ::HIP_RESOURCE_DESC::resType specifies the type of resource to texture from.
 * HUresourceType is defined as:
 * \code
        typedef enum HUresourcetype_enum {
            HU_RESOURCE_TYPE_ARRAY           = 0x00,
            HU_RESOURCE_TYPE_MIPMAPPED_ARRAY = 0x01,
            HU_RESOURCE_TYPE_LINEAR          = 0x02,
            HU_RESOURCE_TYPE_PITCH2D         = 0x03
        } HUresourcetype;
 * \endcode
 *
 * \par
 * If ::HIP_RESOURCE_DESC::resType is set to ::HU_RESOURCE_TYPE_ARRAY, ::HIP_RESOURCE_DESC::res::array::hArray
 * must be set to a valid HIP array handle.
 *
 * \par
 * If ::HIP_RESOURCE_DESC::resType is set to ::HU_RESOURCE_TYPE_MIPMAPPED_ARRAY, ::HIP_RESOURCE_DESC::res::mipmap::hMipmappedArray
 * must be set to a valid HIP mipmapped array handle.
 *
 * \par
 * If ::HIP_RESOURCE_DESC::resType is set to ::HU_RESOURCE_TYPE_LINEAR, ::HIP_RESOURCE_DESC::res::linear::devPtr
 * must be set to a valid device pointer, that is aligned to ::HU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT.
 * ::HIP_RESOURCE_DESC::res::linear::format and ::HIP_RESOURCE_DESC::res::linear::numChannels
 * describe the format of each component and the number of components per array element. ::HIP_RESOURCE_DESC::res::linear::sizeInBytes
 * specifies the size of the array in bytes. The total number of elements in the linear address range cannot exceed 
 * ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LINEAR_WIDTH. The number of elements is computed as (sizeInBytes / (sizeof(format) * numChannels)).
 *
 * \par
 * If ::HIP_RESOURCE_DESC::resType is set to ::HU_RESOURCE_TYPE_PITCH2D, ::HIP_RESOURCE_DESC::res::pitch2D::devPtr
 * must be set to a valid device pointer, that is aligned to ::HU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT.
 * ::HIP_RESOURCE_DESC::res::pitch2D::format and ::HIP_RESOURCE_DESC::res::pitch2D::numChannels
 * describe the format of each component and the number of components per array element. ::HIP_RESOURCE_DESC::res::pitch2D::width
 * and ::HIP_RESOURCE_DESC::res::pitch2D::height specify the width and height of the array in elements, and cannot exceed
 * ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_WIDTH and ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_HEIGHT respectively.
 * ::HIP_RESOURCE_DESC::res::pitch2D::pitchInBytes specifies the pitch between two rows in bytes and has to be aligned to 
 * ::HU_DEVICE_ATTRIBUTE_TEXTURE_PITCH_ALIGNMENT. Pitch cannot exceed ::HU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_PITCH.
 *
 * - ::flags must be set to zero.
 *
 *
 * The ::HIP_TEXTURE_DESC struct is defined as
 * \code
        typedef struct HIP_TEXTURE_DESC_st {
            HUaddress_mode addressMode[3];
            HUfilter_mode filterMode;
            unsigned int flags;
            unsigned int maxAnisotropy;
            HUfilter_mode mipmapFilterMode;
            float mipmapLevelBias;
            float minMipmapLevelClamp;
            float maxMipmapLevelClamp;
        } HIP_TEXTURE_DESC;
 * \endcode
 * where
 * - ::HIP_TEXTURE_DESC::addressMode specifies the addressing mode for each dimension of the texture data. ::HUaddress_mode is defined as:
 *   \code
        typedef enum HUaddress_mode_enum {
            HU_TR_ADDRESS_MODE_WRAP = 0,
            HU_TR_ADDRESS_MODE_CLAMP = 1,
            HU_TR_ADDRESS_MODE_MIRROR = 2,
            HU_TR_ADDRESS_MODE_BORDER = 3
        } HUaddress_mode;
 *   \endcode
 *   This is ignored if ::HIP_RESOURCE_DESC::resType is ::HU_RESOURCE_TYPE_LINEAR. Also, if the flag, ::HU_TRSF_NORMALIZED_COORDINATES 
 *   is not set, the only supported address mode is ::HU_TR_ADDRESS_MODE_CLAMP.
 *
 * - ::HIP_TEXTURE_DESC::filterMode specifies the filtering mode to be used when fetching from the texture. HUfilter_mode is defined as:
 *   \code
        typedef enum HUfilter_mode_enum {
            HU_TR_FILTER_MODE_POINT = 0,
            HU_TR_FILTER_MODE_LINEAR = 1
        } HUfilter_mode;
 *   \endcode
 *   This is ignored if ::HIP_RESOURCE_DESC::resType is ::HU_RESOURCE_TYPE_LINEAR.
 *
 * - ::HIP_TEXTURE_DESC::flags can be any combination of the following:
 *   - ::HU_TRSF_READ_AS_INTEGER, which suppresses the default behavior of having the texture promote integer data to floating point data in the
 *     range [0, 1]. Note that texture with 32-bit integer format would not be promoted, regardless of whether or not this flag is specified.
 *   - ::HU_TRSF_NORMALIZED_COORDINATES, which suppresses the default behavior of having the texture coordinates range from [0, Dim) where Dim is
 *     the width or height of the HIP array. Instead, the texture coordinates [0, 1.0) reference the entire breadth of the array dimension; Note
 *     that for HIP mipmapped arrays, this flag has to be set.
 *
 * - ::HIP_TEXTURE_DESC::maxAnisotropy specifies the maximum anisotropy ratio to be used when doing anisotropic filtering. This value will be
 *   clamped to the range [1,16].
 *
 * - ::HIP_TEXTURE_DESC::mipmapFilterMode specifies the filter mode when the calculated mipmap level lies between two defined mipmap levels.
 *
 * - ::HIP_TEXTURE_DESC::mipmapLevelBias specifies the offset to be applied to the calculated mipmap level.
 *
 * - ::HIP_TEXTURE_DESC::minMipmapLevelClamp specifies the lower end of the mipmap level range to clamp access to.
 *
 * - ::HIP_TEXTURE_DESC::maxMipmapLevelClamp specifies the upper end of the mipmap level range to clamp access to.
 *
 *
 * The ::HIP_RESOURCE_VIEW_DESC struct is defined as
 * \code
        typedef struct HIP_RESOURCE_VIEW_DESC_st
        {
            HUresourceViewFormat format;
            size_t width;
            size_t height;
            size_t depth;
            unsigned int firstMipmapLevel;
            unsigned int lastMipmapLevel;
            unsigned int firstLayer;
            unsigned int lastLayer;
        } HIP_RESOURCE_VIEW_DESC;
 * \endcode
 * where:
 * - ::HIP_RESOURCE_VIEW_DESC::format specifies how the data contained in the HIP array or HIP mipmapped array should
 *   be interpreted. Note that this can incur a change in size of the texture data. If the resource view format is a block
 *   compressed format, then the underlying HIP array or HIP mipmapped array has to have a base of format ::HU_AD_FORMAT_UNSIGNED_INT32.
 *   with 2 or 4 channels, depending on the block compressed format. For ex., BC1 and BC4 require the underlying HIP array to have
 *   a format of ::HU_AD_FORMAT_UNSIGNED_INT32 with 2 channels. The other BC formats require the underlying resource to have the same base
 *   format but with 4 channels.
 *
 * - ::HIP_RESOURCE_VIEW_DESC::width specifies the new width of the texture data. If the resource view format is a block
 *   compressed format, this value has to be 4 times the original width of the resource. For non block compressed formats,
 *   this value has to be equal to that of the original resource.
 *
 * - ::HIP_RESOURCE_VIEW_DESC::height specifies the new height of the texture data. If the resource view format is a block
 *   compressed format, this value has to be 4 times the original height of the resource. For non block compressed formats,
 *   this value has to be equal to that of the original resource.
 *
 * - ::HIP_RESOURCE_VIEW_DESC::depth specifies the new depth of the texture data. This value has to be equal to that of the
 *   original resource.
 *
 * - ::HIP_RESOURCE_VIEW_DESC::firstMipmapLevel specifies the most detailed mipmap level. This will be the new mipmap level zero.
 *   For non-mipmapped resources, this value has to be zero.::HIP_TEXTURE_DESC::minMipmapLevelClamp and ::HIP_TEXTURE_DESC::maxMipmapLevelClamp
 *   will be relative to this value. For ex., if the firstMipmapLevel is set to 2, and a minMipmapLevelClamp of 1.2 is specified,
 *   then the actual minimum mipmap level clamp will be 3.2.
 *
 * - ::HIP_RESOURCE_VIEW_DESC::lastMipmapLevel specifies the least detailed mipmap level. For non-mipmapped resources, this value
 *   has to be zero.
 *
 * - ::HIP_RESOURCE_VIEW_DESC::firstLayer specifies the first layer index for layered textures. This will be the new layer zero.
 *   For non-layered resources, this value has to be zero.
 *
 * - ::HIP_RESOURCE_VIEW_DESC::lastLayer specifies the last layer index for layered textures. For non-layered resources, 
 *   this value has to be zero.
 *
 *
 * \param pTexObject   - Texture object to create
 * \param pResDesc     - Resource descriptor
 * \param pTexDesc     - Texture descriptor
 * \param pResViewDesc - Resource view descriptor 
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::huTexObjectDestroy,
 * ::hipCreateTextureObject
 */
HUresult HIPAPI huTexObjectCreate(HUtexObject *pTexObject, const HIP_RESOURCE_DESC *pResDesc, const HIP_TEXTURE_DESC *pTexDesc, const HIP_RESOURCE_VIEW_DESC *pResViewDesc);

/**
 * \brief Destroys a texture object
 *
 * Destroys the texture object specified by \p texObject.
 *
 * \param texObject - Texture object to destroy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::huTexObjectCreate,
 * ::hipDestroyTextureObject
 */
HUresult HIPAPI huTexObjectDestroy(HUtexObject texObject);

/**
 * \brief Returns a texture object's resource descriptor
 *
 * Returns the resource descriptor for the texture object specified by \p texObject.
 *
 * \param pResDesc  - Resource descriptor
 * \param texObject - Texture object
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::huTexObjectCreate,
 * ::hipGetTextureObjectResourceDesc,
 */
HUresult HIPAPI huTexObjectGetResourceDesc(HIP_RESOURCE_DESC *pResDesc, HUtexObject texObject);

/**
 * \brief Returns a texture object's texture descriptor
 *
 * Returns the texture descriptor for the texture object specified by \p texObject.
 *
 * \param pTexDesc  - Texture descriptor
 * \param texObject - Texture object
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::huTexObjectCreate,
 * ::hipGetTextureObjectTextureDesc
 */
HUresult HIPAPI huTexObjectGetTextureDesc(HIP_TEXTURE_DESC *pTexDesc, HUtexObject texObject);

/**
 * \brief Returns a texture object's resource view descriptor
 *
 * Returns the resource view descriptor for the texture object specified by \p texObject.
 * If no resource view was set for \p texObject, the ::HIP_ERROR_INVALID_VALUE is returned.
 *
 * \param pResViewDesc - Resource view descriptor
 * \param texObject    - Texture object
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::huTexObjectCreate,
 * ::hipGetTextureObjectResourceViewDesc
 */
HUresult HIPAPI huTexObjectGetResourceViewDesc(HIP_RESOURCE_VIEW_DESC *pResViewDesc, HUtexObject texObject);

/** @} */ /* END HIP_TEXOBJECT */

/**
 * \defgroup HIP_SURFOBJECT Surface Object Management
 *
 * ___MANBRIEF___ surface object management functions of the low-level HIP
 * driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the surface object management functions of the
 * low-level HIP driver application programming interface. The surface
 * object API is only supported on devices of compute capability 3.0 or higher.
 *
 * @{
 */

/**
 * \brief Creates a surface object
 *
 * Creates a surface object and returns it in \p pSurfObject. \p pResDesc describes
 * the data to perform surface load/stores on. ::HIP_RESOURCE_DESC::resType must be 
 * ::HU_RESOURCE_TYPE_ARRAY and  ::HIP_RESOURCE_DESC::res::array::hArray
 * must be set to a valid HIP array handle. ::HIP_RESOURCE_DESC::flags must be set to zero.
 *
 * Surface objects are only supported on devices of compute capability 3.0 or higher.
 * Additionally, a surface object is an opaque value, and, as such, should only be
 * accessed through HIP API calls.
 *
 * \param pSurfObject - Surface object to create
 * \param pResDesc    - Resource descriptor
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::huSurfObjectDestroy,
 * ::hipCreateSurfaceObject
 */
HUresult HIPAPI huSurfObjectCreate(HUsurfObject *pSurfObject, const HIP_RESOURCE_DESC *pResDesc);

/**
 * \brief Destroys a surface object
 *
 * Destroys the surface object specified by \p surfObject.
 *
 * \param surfObject - Surface object to destroy
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::huSurfObjectCreate,
 * ::hipDestroySurfaceObject
 */
HUresult HIPAPI huSurfObjectDestroy(HUsurfObject surfObject);

/**
 * \brief Returns a surface object's resource descriptor
 *
 * Returns the resource descriptor for the surface object specified by \p surfObject.
 *
 * \param pResDesc   - Resource descriptor
 * \param surfObject - Surface object
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE
 *
 * \sa
 * ::huSurfObjectCreate,
 * ::hipGetSurfaceObjectResourceDesc
 */
HUresult HIPAPI huSurfObjectGetResourceDesc(HIP_RESOURCE_DESC *pResDesc, HUsurfObject surfObject);

/** @} */ /* END HIP_SURFOBJECT */

/**
 * \defgroup HIP_PEER_ACCESS Peer Context Memory Access
 *
 * ___MANBRIEF___ direct peer context memory access functions of the low-level
 * HIP driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the direct peer context memory access functions 
 * of the low-level HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Queries if a device may directly access a peer device's memory.
 *
 * Returns in \p *canAccessPeer a value of 1 if contexts on \p dev are capable of
 * directly accessing memory from contexts on \p peerDev and 0 otherwise.
 * If direct access of \p peerDev from \p dev is possible, then access may be
 * enabled on two specific contexts by calling ::huCtxEnablePeerAccess().
 *
 * \param canAccessPeer - Returned access capability
 * \param dev           - Device from which allocations on \p peerDev are to
 *                        be directly accessed.
 * \param peerDev       - Device on which the allocations to be directly accessed 
 *                        by \p dev reside.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_DEVICE
 * \notefnerr
 *
 * \sa
 * ::huCtxEnablePeerAccess,
 * ::huCtxDisablePeerAccess,
 * ::hipDeviceCanAccessPeer
 */
HUresult HIPAPI huDeviceCanAccessPeer(int *canAccessPeer, HUdevice dev, HUdevice peerDev);

/**
 * \brief Enables direct access to memory allocations in a peer context.
 *
 * If both the current context and \p peerContext are on devices which support unified
 * addressing (as may be queried using ::HU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING) and same
 * major compute capability, then on success all allocations from \p peerContext will
 * immediately be accessible by the current context.  See \ref HIP_UNIFIED for additional
 * details.
 *
 * Note that access granted by this call is unidirectional and that in order to access
 * memory from the current context in \p peerContext, a separate symmetric call 
 * to ::huCtxEnablePeerAccess() is required.
 *
 * There is a system-wide maximum of eight peer connections per device.
 *
 * Returns ::HIP_ERROR_PEER_ACCESS_UNSUPPORTED if ::huDeviceCanAccessPeer() indicates
 * that the ::HUdevice of the current context cannot directly access memory
 * from the ::HUdevice of \p peerContext.
 *
 * Returns ::HIP_ERROR_PEER_ACCESS_ALREADY_ENABLED if direct access of
 * \p peerContext from the current context has already been enabled.
 *
 * Returns ::HIP_ERROR_TOO_MANY_PEERS if direct peer access is not possible 
 * because hardware resources required for peer access have been exhausted.
 *
 * Returns ::HIP_ERROR_INVALID_CONTEXT if there is no current context, \p peerContext
 * is not a valid context, or if the current context is \p peerContext.
 *
 * Returns ::HIP_ERROR_INVALID_VALUE if \p Flags is not 0.
 *
 * \param peerContext - Peer context to enable direct access to from the current context
 * \param Flags       - Reserved for future use and must be set to 0
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_PEER_ACCESS_ALREADY_ENABLED,
 * ::HIP_ERROR_TOO_MANY_PEERS,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_PEER_ACCESS_UNSUPPORTED,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa
 * ::huDeviceCanAccessPeer,
 * ::huCtxDisablePeerAccess,
 * ::hipDeviceEnablePeerAccess
 */
HUresult HIPAPI huCtxEnablePeerAccess(HUcontext peerContext, unsigned int Flags);

/**
 * \brief Disables direct access to memory allocations in a peer context and 
 * unregisters any registered allocations.
 *
  Returns ::HIP_ERROR_PEER_ACCESS_NOT_ENABLED if direct peer access has 
 * not yet been enabled from \p peerContext to the current context.
 *
 * Returns ::HIP_ERROR_INVALID_CONTEXT if there is no current context, or if
 * \p peerContext is not a valid context.
 *
 * \param peerContext - Peer context to disable direct access to
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_PEER_ACCESS_NOT_ENABLED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * \notefnerr
 *
 * \sa
 * ::huDeviceCanAccessPeer,
 * ::huCtxEnablePeerAccess,
 * ::hipDeviceDisablePeerAccess
 */
HUresult HIPAPI huCtxDisablePeerAccess(HUcontext peerContext);

/**
 * \brief Queries attributes of the link between two devices.
 *
 * Returns in \p *value the value of the requested attribute \p attrib of the
 * link between \p srcDevice and \p dstDevice. The supported attributes are:
 * - ::HU_DEVICE_P2P_ATTRIBUTE_PERFORMANCE_RANK: A relative value indicating the
 *   performance of the link between two devices.
 * - ::HU_DEVICE_P2P_ATTRIBUTE_ACCESS_SUPPORTED P2P: 1 if P2P Access is enable.
 * - ::HU_DEVICE_P2P_ATTRIBUTE_NATIVE_ATOMIC_SUPPORTED: 1 if Atomic operations over
 *   the link are supported.
 * - ::HU_DEVICE_P2P_ATTRIBUTE_HIP_ARRAY_ACCESS_SUPPORTED: 1 if hipArray can
 *   be accessed over the link.
 *
 * Returns ::HIP_ERROR_INVALID_DEVICE if \p srcDevice or \p dstDevice are not valid
 * or if they represent the same device.
 *
 * Returns ::HIP_ERROR_INVALID_VALUE if \p attrib is not valid or if \p value is
 * a null pointer.
 *
 * \param value         - Returned value of the requested attribute
 * \param attrib        - The requested attribute of the link between \p srcDevice and \p dstDevice.
 * \param srcDevice     - The source device of the target link.
 * \param dstDevice     - The destination device of the target link.
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_DEVICE,
 * ::HIP_ERROR_INVALID_VALUE
 * \notefnerr
 *
 * \sa
 * ::huCtxEnablePeerAccess,
 * ::huCtxDisablePeerAccess,
 * ::huDeviceCanAccessPeer,
 * ::hipDeviceGetP2PAttribute
 */
HUresult HIPAPI huDeviceGetP2PAttribute(int* value, HUdevice_P2PAttribute attrib, HUdevice srcDevice, HUdevice dstDevice);

/** @} */ /* END HIP_PEER_ACCESS */

/**
 * \defgroup HIP_GRAPHICS Graphics Interoperability
 *
 * ___MANBRIEF___ graphics interoperability functions of the low-level HIP
 * driver API (___CURRENT_FILE___) ___ENDMANBRIEF___
 *
 * This section describes the graphics interoperability functions of the
 * low-level HIP driver application programming interface.
 *
 * @{
 */

/**
 * \brief Unregisters a graphics resource for access by HIP
 *
 * Unregisters the graphics resource \p resource so it is not accessible by
 * HIP unless registered again.
 *
 * If \p resource is invalid then ::HIP_ERROR_INVALID_HANDLE is
 * returned.
 *
 * \param resource - Resource to unregister
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_UNKNOWN
 * \notefnerr
 *
 * \sa
 * ::huGraphicsD3D9RegisterResource,
 * ::huGraphicsD3D10RegisterResource,
 * ::huGraphicsD3D11RegisterResource,
 * ::huGraphicsGLRegisterBuffer,
 * ::huGraphicsGLRegisterImage,
 * ::hipGraphicsUnregisterResource
 */
HUresult HIPAPI huGraphicsUnregisterResource(HUgraphicsResource resource);

/**
 * \brief Get an array through which to access a subresource of a mapped graphics resource.
 *
 * Returns in \p *pArray an array through which the subresource of the mapped
 * graphics resource \p resource which corresponds to array index \p arrayIndex
 * and mipmap level \p mipLevel may be accessed.  The value set in \p *pArray may
 * change every time that \p resource is mapped.
 *
 * If \p resource is not a texture then it cannot be accessed via an array and
 * ::HIP_ERROR_NOT_MAPPED_AS_ARRAY is returned.
 * If \p arrayIndex is not a valid array index for \p resource then
 * ::HIP_ERROR_INVALID_VALUE is returned.
 * If \p mipLevel is not a valid mipmap level for \p resource then
 * ::HIP_ERROR_INVALID_VALUE is returned.
 * If \p resource is not mapped then ::HIP_ERROR_NOT_MAPPED is returned.
 *
 * \param pArray      - Returned array through which a subresource of \p resource may be accessed
 * \param resource    - Mapped resource to access
 * \param arrayIndex  - Array index for array textures or hubemap face
 *                      index as defined by ::HUarray_cubemap_face for
 *                      hubemap textures for the subresource to access
 * \param mipLevel    - Mipmap level for the subresource to access
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_NOT_MAPPED,
 * ::HIP_ERROR_NOT_MAPPED_AS_ARRAY
 * \notefnerr
 *
 * \sa
 * ::huGraphicsResourceGetMappedPointer,
 * ::hipGraphicsSubResourceGetMappedArray
 */
HUresult HIPAPI huGraphicsSubResourceGetMappedArray(HUarray *pArray, HUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel);

/**
 * \brief Get a mipmapped array through which to access a mapped graphics resource.
 *
 * Returns in \p *pMipmappedArray a mipmapped array through which the mapped graphics 
 * resource \p resource. The value set in \p *pMipmappedArray may change every time 
 * that \p resource is mapped.
 *
 * If \p resource is not a texture then it cannot be accessed via a mipmapped array and
 * ::HIP_ERROR_NOT_MAPPED_AS_ARRAY is returned.
 * If \p resource is not mapped then ::HIP_ERROR_NOT_MAPPED is returned.
 *
 * \param pMipmappedArray - Returned mipmapped array through which \p resource may be accessed
 * \param resource        - Mapped resource to access
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_NOT_MAPPED,
 * ::HIP_ERROR_NOT_MAPPED_AS_ARRAY
 * \notefnerr
 *
 * \sa
 * ::huGraphicsResourceGetMappedPointer,
 * ::hipGraphicsResourceGetMappedMipmappedArray
 */
HUresult HIPAPI huGraphicsResourceGetMappedMipmappedArray(HUmipmappedArray *pMipmappedArray, HUgraphicsResource resource);

/**
 * \brief Get a device pointer through which to access a mapped graphics resource.
 *
 * Returns in \p *pDevPtr a pointer through which the mapped graphics resource
 * \p resource may be accessed.
 * Returns in \p pSize the size of the memory in bytes which may be accessed from that pointer.
 * The value set in \p pPointer may change every time that \p resource is mapped.
 *
 * If \p resource is not a buffer then it cannot be accessed via a pointer and
 * ::HIP_ERROR_NOT_MAPPED_AS_POINTER is returned.
 * If \p resource is not mapped then ::HIP_ERROR_NOT_MAPPED is returned.
 * *
 * \param pDevPtr    - Returned pointer through which \p resource may be accessed
 * \param pSize      - Returned size of the buffer accessible starting at \p *pPointer
 * \param resource   - Mapped resource to access
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_NOT_MAPPED,
 * ::HIP_ERROR_NOT_MAPPED_AS_POINTER
 * \notefnerr
 *
 * \sa
 * ::huGraphicsMapResources,
 * ::huGraphicsSubResourceGetMappedArray,
 * ::hipGraphicsResourceGetMappedPointer
 */
HUresult HIPAPI huGraphicsResourceGetMappedPointer(HUdeviceptr *pDevPtr, size_t *pSize, HUgraphicsResource resource);

/**
 * \brief Set usage flags for mapping a graphics resource
 *
 * Set \p flags for mapping the graphics resource \p resource.
 *
 * Changes to \p flags will take effect the next time \p resource is mapped.
 * The \p flags argument may be any of the following:

 * - ::HU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE: Specifies no hints about how this
 *   resource will be used. It is therefore assumed that this resource will be
 *   read from and written to by HIP kernels.  This is the default value.
 * - ::HU_GRAPHICS_MAP_RESOURCE_FLAGS_READONLY: Specifies that HIP kernels which
 *   access this resource will not write to this resource.
 * - ::HU_GRAPHICS_MAP_RESOURCE_FLAGS_WRITEDISCARD: Specifies that HIP kernels
 *   which access this resource will not read from this resource and will
 *   write over the entire contents of the resource, so none of the data
 *   previously stored in the resource will be preserved.
 *
 * If \p resource is presently mapped for access by HIP then
 * ::HIP_ERROR_ALREADY_MAPPED is returned.
 * If \p flags is not one of the above values then ::HIP_ERROR_INVALID_VALUE is returned.
 *
 * \param resource - Registered resource to set flags for
 * \param flags    - Parameters for resource mapping
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_VALUE,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_ALREADY_MAPPED
 * \notefnerr
 *
 * \sa
 * ::huGraphicsMapResources,
 * ::hipGraphicsResourceSetMapFlags
 */
HUresult HIPAPI huGraphicsResourceSetMapFlags(HUgraphicsResource resource, unsigned int flags);

/**
 * \brief Map graphics resources for access by HIP
 *
 * Maps the \p count graphics resources in \p resources for access by HIP.
 *
 * The resources in \p resources may be accessed by HIP until they
 * are unmapped. The graphics API from which \p resources were registered
 * should not access any resources while they are mapped by HIP. If an
 * application does so, the results are undefined.
 *
 * This function provides the synchronization guarantee that any graphics calls
 * issued before ::huGraphicsMapResources() will complete before any subsequent HIP
 * work issued in \p stream begins.
 *
 * If \p resources includes any duplicate entries then ::HIP_ERROR_INVALID_HANDLE is returned.
 * If any of \p resources are presently mapped for access by HIP then ::HIP_ERROR_ALREADY_MAPPED is returned.
 *
 * \param count      - Number of resources to map
 * \param resources  - Resources to map for HIP usage
 * \param hStream    - Stream with which to synchronize
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_ALREADY_MAPPED,
 * ::HIP_ERROR_UNKNOWN
 * \note_null_stream
 * \notefnerr
 *
 * \sa
 * ::huGraphicsResourceGetMappedPointer,
 * ::huGraphicsSubResourceGetMappedArray,
 * ::huGraphicsUnmapResources,
 * ::hipGraphicsMapResources
 */
HUresult HIPAPI huGraphicsMapResources(unsigned int count, HUgraphicsResource *resources, HUstream hStream);

/**
 * \brief Unmap graphics resources.
 *
 * Unmaps the \p count graphics resources in \p resources.
 *
 * Once unmapped, the resources in \p resources may not be accessed by HIP
 * until they are mapped again.
 *
 * This function provides the synchronization guarantee that any HIP work issued
 * in \p stream before ::huGraphicsUnmapResources() will complete before any
 * subsequently issued graphics work begins.
 *
 *
 * If \p resources includes any duplicate entries then ::HIP_ERROR_INVALID_HANDLE is returned.
 * If any of \p resources are not presently mapped for access by HIP then ::HIP_ERROR_NOT_MAPPED is returned.
 *
 * \param count      - Number of resources to unmap
 * \param resources  - Resources to unmap
 * \param hStream    - Stream with which to synchronize
 *
 * \return
 * ::HIP_SUCCESS,
 * ::HIP_ERROR_DEINITIALIZED,
 * ::HIP_ERROR_NOT_INITIALIZED,
 * ::HIP_ERROR_INVALID_CONTEXT,
 * ::HIP_ERROR_INVALID_HANDLE,
 * ::HIP_ERROR_NOT_MAPPED,
 * ::HIP_ERROR_UNKNOWN
 * \note_null_stream
 * \notefnerr
 *
 * \sa
 * ::huGraphicsMapResources,
 * ::hipGraphicsUnmapResources
 */
HUresult HIPAPI huGraphicsUnmapResources(unsigned int count, HUgraphicsResource *resources, HUstream hStream);

/** @} */ /* END HIP_GRAPHICS */

HUresult HIPAPI huGetExportTable(const void **ppExportTable, const HUuuid *pExportTableId);

#ifdef __cplusplus
}
#endif

#undef __HIP_API_VERSION
#undef __HIP_DEPRECATED

#endif /* HIP_INCLUDE_HIP_HCC_DETAIL_HIP_DRIVER_H  */

