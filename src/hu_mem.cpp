#include "hu_internal.h"

namespace hip_internal {
void* allocAndSharePtr(
        const char* msg, size_t sizeBytes, ihipCtx_t* ctx, bool shareWithAll,
        unsigned amFlags, unsigned hipFlags, size_t alignment);
}

static inline HUresult memcpyAsync(
        void* dst, const void* src, size_t sizeBytes, hipMemcpyKind kind, hipStream_t stream) {
    HUresult e = HIP_SUCCESS;

    // Return success if number of bytes to copy is 0
    if (sizeBytes == 0) return e;

    stream = ihipSyncAndResolveStream(stream);

    if ((dst == NULL) || (src == NULL)) {
        e = HIP_ERROR_INVALID_VALUE;
    } else if (stream) {
        try {
            stream->locked_copyAsync(dst, src, sizeBytes, kind);
        } catch (ihipException& ex) {
            //e = ex._code;
            e = HIP_ERROR_NOT_SUPPORTED;
        }
    } else {
        e = HIP_ERROR_INVALID_VALUE;
    }

    return e;
}

HUresult huMemAdvise(HUdeviceptr devPtr, size_t count, HUmem_advise advice, HUdevice device) {
    HU_INIT_API(huMemAdvise, devPtr, count, advice, device);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemAlloc(HUdeviceptr *ptr, size_t sizeBytes) {
    HU_INIT_API(huMemAlloc, ptr, sizeBytes);
    HIP_SET_DEVICE();

    HUresult hip_status = HIP_SUCCESS;

    auto ctx = ihipGetTlsDefaultCtx();
    // return NULL pointer when malloc size is 0
    if (sizeBytes == 0) {
        *ptr = NULL;
        hip_status = HIP_SUCCESS;

    } else if ((ctx == nullptr) || (ptr == nullptr)) {
        hip_status = HIP_ERROR_INVALID_VALUE;

    } else {
        auto device = ctx->getWriteableDevice();
        *ptr = hip_internal::allocAndSharePtr("device_mem", sizeBytes, ctx, false /*shareWithAll*/,
                                              0 /*amFlags*/, 0 /*hipFlags*/, 0);

        if (sizeBytes && (*ptr == NULL)) {
            hip_status = HIP_ERROR_OUT_OF_MEMORY;
        }
    }

    return ihuLogStatus(hip_status);
}

HUresult huMemAllocHost(void **pp, size_t bytesize) {
    HU_INIT_API(huMemAllocHost, pp, bytesize);

    HUresult e = huMemHostAlloc(pp, bytesize, 0);

    return ihuLogStatus(e);
}

HUresult huMemAllocManaged(HUdeviceptr *dptr, size_t bytesize, unsigned int flags) {
    HU_INIT_API(huMemAllocManaged, dptr, bytesize, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemAllocPitch(HUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes) {
    HU_INIT_API(huMemAllocPitch, dptr, pPitch, WidthInBytes, Height, ElementSizeBytes);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemFree(HUdeviceptr ptr) {
    HU_INIT_API(huMemFree, dptr);

    HUresult hipStatus = HIP_ERROR_INVALID_VALUE;

    // Synchronize to ensure all work has finished.
    ihipGetTlsDefaultCtx()->locked_waitAllStreams();  // ignores non-blocking streams, this waits
                                                      // for all activity to finish.

    if (ptr) {
        hc::accelerator acc;
#if (__hcc_workweek__ >= 17332)
        hc::AmPointerInfo amPointerInfo(NULL, NULL, NULL, 0, acc, 0, 0);
#else
        hc::AmPointerInfo amPointerInfo(NULL, NULL, 0, acc, 0, 0);
#endif
        am_status_t status = hc::am_memtracker_getinfo(&amPointerInfo, ptr);
        if (status == AM_SUCCESS) {
            if (amPointerInfo._hostPointer == NULL) {
                hc::am_free(ptr);
                hipStatus = HIP_SUCCESS;
            }
        }
    } else {
        // free NULL pointer succeeds and is common technique to initialize runtime
        hipStatus = HIP_SUCCESS;
    }

    return ihuLogStatus(hipStatus);
}

HUresult huMemFreeHost(void *ptr) {
    HU_INIT_API(huMemFreeHost, ptr);

    // Synchronize to ensure all work has finished.
    ihipGetTlsDefaultCtx()->locked_waitAllStreams();  // ignores non-blocking streams, this waits
                                                      // for all activity to finish.

    HUresult hipStatus = HIP_ERROR_INVALID_VALUE;
    if (ptr) {
        hc::accelerator acc;
#if (__hcc_workweek__ >= 17332)
        hc::AmPointerInfo amPointerInfo(NULL, NULL, NULL, 0, acc, 0, 0);
#else
        hc::AmPointerInfo amPointerInfo(NULL, NULL, 0, acc, 0, 0);
#endif
        am_status_t status = hc::am_memtracker_getinfo(&amPointerInfo, ptr);
        if (status == AM_SUCCESS) {
            if (amPointerInfo._hostPointer == ptr) {
                hc::am_free(ptr);
                hipStatus = HIP_SUCCESS;
            }
        }
    } else {
        // free NULL pointer succeeds and is common technique to initialize runtime
        hipStatus = HIP_SUCCESS;
    }

    return ihuLogStatus(hipStatus);
}

HUresult huMemGetAddressRange(HUdeviceptr *pbase, size_t *psize, HUdeviceptr dptr) {
    HU_INIT_API(huMemGetAddressRange, pbase, psize, dptr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemGetInfo(size_t *free, size_t *total) {
    HU_INIT_API(huMemGetInfo, free, total);

    HUresult e = HIP_SUCCESS;

    ihipCtx_t* ctx = ihipGetTlsDefaultCtx();
    if (ctx) {
        auto device = ctx->getWriteableDevice();
        if (total) {
            *total = device->_props.totalGlobalMem;
        } else {
            e = HIP_ERROR_INVALID_VALUE;
        }

        if (free) {
            // TODO - replace with kernel-level for reporting free memory:
            size_t deviceMemSize, hostMemSize, userMemSize;
            hc::am_memtracker_sizeinfo(device->_acc, &deviceMemSize, &hostMemSize, &userMemSize);

            *free = device->_props.totalGlobalMem - deviceMemSize;

            // Deduct the amount of memory from the free memory reported from the system
            if (HIP_HIDDEN_FREE_MEM) *free -= (size_t)HIP_HIDDEN_FREE_MEM * 1024 * 1024;
        } else {
            e = HIP_ERROR_INVALID_VALUE;
        }

    } else {
        e = HIP_ERROR_INVALID_DEVICE;
    }

    return ihuLogStatus(e);
}

HUresult huMemHostAlloc(void **ptr, size_t sizeBytes, unsigned int flags) {
    HU_INIT_API(huMemHostAlloc, ptr, sizeBytes, flags);
    HIP_SET_DEVICE();

    HUresult hip_status = HIP_SUCCESS;

    if (HIP_SYNC_HOST_ALLOC) {
        hipDeviceSynchronize();
    }

    auto ctx = ihipGetTlsDefaultCtx();

    if (sizeBytes == 0) {
        hip_status = HIP_SUCCESS;
        // TODO - should size of 0 return err or be siliently ignored?
    } else if ((ctx == nullptr) || (ptr == nullptr)) {
        hip_status = HIP_ERROR_INVALID_VALUE;
    } else {
        unsigned trueFlags = flags;
        if (flags == hipHostMallocDefault) {
            // HCC/ROCM provide a modern system with unified memory and should set both of these
            // flags by default:
            trueFlags = hipHostMallocMapped | hipHostMallocPortable;
        }


        const unsigned supportedFlags = hipHostMallocPortable | hipHostMallocMapped |
                                        hipHostMallocWriteCombined | hipHostMallocCoherent |
                                        hipHostMallocNonCoherent;


        const unsigned coherencyFlags = hipHostMallocCoherent | hipHostMallocNonCoherent;

        if ((flags & ~supportedFlags) || ((flags & coherencyFlags) == coherencyFlags)) {
            *ptr = nullptr;
            // can't specify unsupported flags, can't specify both Coherent + NonCoherent
            hip_status = HIP_ERROR_INVALID_VALUE;
        } else {
            auto device = ctx->getWriteableDevice();

            unsigned amFlags = 0;
            if (flags & hipHostMallocCoherent) {
                amFlags = amHostCoherent;
            } else if (flags & hipHostMallocNonCoherent) {
                amFlags = amHostNonCoherent;
            } else {
                // depends on env variables:
                amFlags = HIP_HOST_COHERENT ? amHostCoherent : amHostNonCoherent;
            }


            *ptr = hip_internal::allocAndSharePtr(
                (amFlags & amHostCoherent) ? "finegrained_host" : "pinned_host", sizeBytes, ctx,
                (trueFlags & hipHostMallocPortable) /*shareWithAll*/, amFlags, flags, 0);

            if (sizeBytes && (*ptr == NULL)) {
                hip_status = HIP_ERROR_OUT_OF_MEMORY;
            }
        }
    }

    if (HIP_SYNC_HOST_ALLOC) {
        hipDeviceSynchronize();
    }

    return ihuLogStatus(hip_status);
}

HUresult huMemHostGetDevicePointer(HUdeviceptr *pdptr, void *p, unsigned int Flags) {
    HU_INIT_API(huMemHostGetDevicePointer, pdptr, p, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemHostGetFlags(unsigned int *pFlags, void *p) {
    HU_INIT_API(huMemHostGetFlags, pFlags, p);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemHostRegister(void *p, size_t bytesize, unsigned int Flags) {
    HU_INIT_API(huMemHostRegister, p, bytesize, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemHostUnregister(void *p) {
    HU_INIT_API(huMemHostUnregister, p);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemPrefetchAsync(HUdeviceptr devPtr, size_t count, HUdevice dstDevice, HUstream hStream) {
    HU_INIT_API(huMemPrefetchAsync, devPtr, count, dstDevice, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemRangeGetAttribute(void *data, size_t dataSize, HUmem_range_attribute attribute, HUdeviceptr devPtr, size_t count) {
    HU_INIT_API(huMemRangeGetAttribute, data, dataSize, attribute, devPtr, count);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemRangeGetAttributes(void **data, size_t *dataSizes, HUmem_range_attribute *attributes, size_t numAttributes, HUdeviceptr devPtr, size_t count) {
    HU_INIT_API(huMemRangeGetAttributes, data, dataSizes, attributes, numAttributes, devPtr, count);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpy(HUdeviceptr dst, HUdeviceptr src, size_t ByteCount) {
    HU_INIT_API(huMemcpy, dst, src, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpy2D(const HIP_MEMCPY2D *pCopy) {
    HU_INIT_API(huMemcpy2D, pCopy);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpy2DAsync(const HIP_MEMCPY2D *pCopy, HUstream hStream) {
    HU_INIT_API(huMemcpy2DAsync, pCopy, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpy2DUnaligned(const HIP_MEMCPY2D *pCopy) {
    HU_INIT_API(huMemcpy2DUnaligned, pCopy);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpy3D(const HIP_MEMCPY3D *pCopy) {
    HU_INIT_API(huMemcpy3D, pCopy);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpy3DAsync(const HIP_MEMCPY3D *pCopy, HUstream hStream) {
    HU_INIT_API(huMemcpy3DAsync, pCopy, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpy3DPeer(const HIP_MEMCPY3D_PEER *pCopy) {
    HU_INIT_API(huMemcpy3DPeer, pCopy);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpy3DPeerAsync(const HIP_MEMCPY3D_PEER *pCopy, HUstream hStream) {
    HU_INIT_API(huMemcpy3DPeerAsync, pCopy, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyAsync(HUdeviceptr dst, HUdeviceptr src, size_t ByteCount, HUstream hStream) {
    HU_INIT_API(huMemcpyAsync, dst, src, ByteCount, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyAtoA(HUarray dstArray, size_t dstOffset, HUarray srcArray, size_t srcOffset, size_t ByteCount) {
    HU_INIT_API(huMemcpyAtoA, dstArray, dstOffset, srcArray, srcOffset, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyAtoD(HUdeviceptr dstDevice, HUarray srcArray, size_t srcOffset, size_t ByteCount) {
    HU_INIT_API(huMemcpyAtoD, dstDevice, srcArray, srcOffset, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyAtoH(void *dstHost, HUarray srcArray, size_t srcOffset, size_t ByteCount) {
    HU_INIT_API(huMemcpyAtoH, dstHost, srcArray, srcOffset, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyAtoHAsync(void *dstHost, HUarray srcArray, size_t srcOffset, size_t ByteCount, HUstream hStream) {
    HU_INIT_API(huMemcpyAtoHAsync, dstHost, srcArray, srcOffset, ByteCount, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyDtoA(HUarray dstArray, size_t dstOffset, HUdeviceptr srcDevice, size_t ByteCount) {
    HU_INIT_API(huMemcpyDtoA, dstArray, dstOffset, srcDevice, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyDtoD(HUdeviceptr dst, HUdeviceptr src, size_t sizeBytes) {
    HU_INIT_API(huMemcpyDtoD, dst, src, sizeBytes);

    hipStream_t stream = ihipSyncAndResolveStream(hipStreamNull);

    hc::completion_future marker;

    HUresult e = HIP_SUCCESS;

    try {
        stream->locked_copySync((void*)dst, (void*)src, sizeBytes, hipMemcpyDeviceToDevice, false);
    } catch (ihipException& ex) {
        //e = ex._code;
        e = HIP_ERROR_NOT_SUPPORTED;
    }

    return ihuLogStatus(e);
}

HUresult huMemcpyDtoDAsync(HUdeviceptr dst, HUdeviceptr src, size_t sizeBytes, HUstream stream) {
    HU_INIT_API(huMemcpyDtoDAsync, dst, src, sizeBytes, stream);

    return ihuLogStatus(memcpyAsync(dst, src, sizeBytes, hipMemcpyDeviceToDevice, stream));
}

HUresult huMemcpyDtoH(void *dst, HUdeviceptr src, size_t sizeBytes) {
    HU_INIT_API(huMemcpyDtoH, dst, src, sizeBytes);

    hipStream_t stream = ihipSyncAndResolveStream(hipStreamNull);

    hc::completion_future marker;

    HUresult e = HIP_SUCCESS;

    try {
        stream->locked_copySync((void*)dst, (void*)src, sizeBytes, hipMemcpyDeviceToHost, false);
    } catch (ihipException& ex) {
        //e = ex._code;
        e = HIP_ERROR_NOT_SUPPORTED;
    }

    return ihuLogStatus(e);
}

HUresult huMemcpyDtoHAsync(void *dst, HUdeviceptr src, size_t sizeBytes, HUstream stream) {
    HU_INIT_API(huMemcpyDtoHAsync, dst, src, sizeBytes, stream);

    return ihuLogStatus(memcpyAsync(dst, src, sizeBytes, hipMemcpyDeviceToHost, stream));
}

HUresult huMemcpyHtoA(HUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount) {
    HU_INIT_API(huMemcpyHtoA, dstArray, dstOffset, srcHost, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyHtoAAsync(HUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount, HUstream hStream) {
    HU_INIT_API(huMemcpyHtoAAsync, dstArray, dstOffset, srcHost, ByteCount, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyHtoD(HUdeviceptr dst, const void *src, size_t sizeBytes) {
    HU_INIT_API(huMemcpyHtoD, dst, src, sizeBytes);

    hipStream_t stream = ihipSyncAndResolveStream(hipStreamNull);

    hc::completion_future marker;

    HUresult e = HIP_SUCCESS;

    try {
        stream->locked_copySync((void*)dst, (void*)src, sizeBytes, hipMemcpyHostToDevice, false);
    } catch (ihipException& ex) {
        //e = ex._code;
        e = HIP_ERROR_NOT_SUPPORTED;
    }

    return ihuLogStatus(e);
}

HUresult huMemcpyHtoDAsync(HUdeviceptr dst, const void *src, size_t sizeBytes, HUstream stream) {
    HU_INIT_API(huMemcpyHtoDAsync, dst, src, sizeBytes, stream);

    return ihuLogStatus(memcpyAsync(dst, src, sizeBytes, hipMemcpyHostToDevice, stream));
}

HUresult huMemcpyPeer(HUdeviceptr dstDevice, HUcontext dstContext, HUdeviceptr srcDevice, HUcontext srcContext, size_t ByteCount) {
    HU_INIT_API(huMemcpyPeer, dstDevice, dstContext, srcDevice, srcContext, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyPeerAsync(HUdeviceptr dstDevice, HUcontext dstContext, HUdeviceptr srcDevice, HUcontext srcContext, size_t ByteCount, HUstream hStream) {
    HU_INIT_API(huMemcpyPeerAsync, dstDevice, dstContext, srcDevice, srcContext, ByteCount, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD16(HUdeviceptr dstDevice, unsigned short us, size_t N) {
    HU_INIT_API(huMemsetD16, dstDevice, us, N);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD16Async(HUdeviceptr dstDevice, unsigned short us, size_t N, HUstream hStream) {
    HU_INIT_API(huMemsetD16Async, dstDevice, us, N, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD2D16(HUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height) {
    HU_INIT_API(huMemsetD2D16, dstDevice, dstPitch, us, Width, Height);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD2D16Async(HUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, HUstream hStream) {
    HU_INIT_API(huMemsetD2D16Async, dstDevice, dstPitch, us, Width, Height, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD2D32(HUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height) {
    HU_INIT_API(huMemsetD2D32, dstDevice, dstPitch, ui, Width, Height);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD2D32Async(HUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, HUstream hStream) {
    HU_INIT_API(huMemsetD2D32Async, dstDevice, dstPitch, ui, Width, Height, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD2D8(HUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height) {
    HU_INIT_API(huMemsetD2D8, dstDevice, dstPitch, uc, Width, Height);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD2D8Async(HUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, HUstream hStream) {
    HU_INIT_API(huMemsetD2D8Async, dstDevice, dstPitch, uc, Width, Height, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD32(HUdeviceptr location, unsigned int value, size_t uint32_count) {
    HU_INIT_API(huMemsetD32, location, value, uint32_count);

    //void * pointer = absl::bit_cast<void *>(location);
    void * pointer = location;
    unsigned char valueC = static_cast<unsigned char>(value);
    uint32_t value32 = (valueC << 24) | (valueC << 16) | (valueC << 8) | (valueC) ;
    assert (value32 == value); // if mismatch this indicates case where hipMemsetAsyc can't emulate hipMemSetD32
    hipError_t res = hipMemset(pointer, static_cast<int>(value), uint32_count*4);
    if (hipSuccess == res) {
        return ihuLogStatus(HIP_SUCCESS);
    } else {
        return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);
    }
}

HUresult huMemsetD32Async(HUdeviceptr location, unsigned int value, size_t uint32_count, HUstream stream) {
    HU_INIT_API(huMemsetD32, location, value, uint32_count, stream);

    //void * pointer = absl::bit_cast<void *>(location);
    void * pointer = location;
    unsigned char valueC = static_cast<unsigned char>(value);
    uint32_t value32 = (valueC << 24) | (valueC << 16) | (valueC << 8) | (valueC) ;
    assert (value32 == value); // if mismatch this indicates case where hipMemsetAsyc can't emulate hipMemSetD32
    hipError_t res = hipMemsetAsync(pointer, static_cast<int>(value), uint32_count*4, stream);
    if (hipSuccess == res) {
        return ihuLogStatus(HIP_SUCCESS);
    } else {
        return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);
    }
}

HUresult huMemsetD8(HUdeviceptr dstDevice, unsigned char uc, size_t N) {
    HU_INIT_API(huMemsetD8, dstDevice, uc, N);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD8Async(HUdeviceptr dstDevice, unsigned char uc, size_t N, HUstream hStream) {
    HU_INIT_API(huMemsetD8Async, dstDevice, uc, N, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huPointerGetAttribute(void *data, HUpointer_attribute attribute, HUdeviceptr ptr) {
    HU_INIT_API(huPointerGetAttribute, data, attribute, ptr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huPointerGetAttributes(unsigned int numAttributes, HUpointer_attribute *attributes, void **data, HUdeviceptr ptr) {
    HU_INIT_API(huPointerGetAttributes, numAttributes, attributes, data, ptr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huPointerSetAttribute(const void *value, HUpointer_attribute attribute, HUdeviceptr ptr) {
    HU_INIT_API(huPointerSetAttribute, value, attribute, ptr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

