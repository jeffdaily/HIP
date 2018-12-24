#include "hu_internal.h"

HUresult huMemAdvise(HUdeviceptr devPtr, size_t count, HUmem_advise advice, HUdevice device) {
    HU_INIT_API(huMemAdvise, devPtr, count, advice, device);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemAlloc(HUdeviceptr *dptr, size_t bytesize) {
    HU_INIT_API(huMemAlloc, dptr, bytesize);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemAllocHost(void **pp, size_t bytesize) {
    HU_INIT_API(huMemAllocHost, pp, bytesize);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemAllocManaged(HUdeviceptr *dptr, size_t bytesize, unsigned int flags) {
    HU_INIT_API(huMemAllocManaged, dptr, bytesize, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemAllocPitch(HUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes) {
    HU_INIT_API(huMemAllocPitch, dptr, pPitch, WidthInBytes, Height, ElementSizeBytes);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemFree(HUdeviceptr dptr) {
    HU_INIT_API(huMemFree, dptr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemFreeHost(void *p) {
    HU_INIT_API(huMemFreeHost, p);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemGetAddressRange(HUdeviceptr *pbase, size_t *psize, HUdeviceptr dptr) {
    HU_INIT_API(huMemGetAddressRange, pbase, psize, dptr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemGetInfo(size_t *free, size_t *total) {
    HU_INIT_API(huMemGetInfo, free, total);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemHostAlloc(void **pp, size_t bytesize, unsigned int Flags) {
    HU_INIT_API(huMemHostAlloc, pp, bytesize, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
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

HUresult huMemcpyDtoD(HUdeviceptr dstDevice, HUdeviceptr srcDevice, size_t ByteCount) {
    HU_INIT_API(huMemcpyDtoD, dstDevice, srcDevice, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyDtoDAsync(HUdeviceptr dstDevice, HUdeviceptr srcDevice, size_t ByteCount, HUstream hStream) {
    HU_INIT_API(huMemcpyDtoDAsync, dstDevice, srcDevice, ByteCount, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyDtoH(void *dstHost, HUdeviceptr srcDevice, size_t ByteCount) {
    HU_INIT_API(huMemcpyDtoH, dstHost, srcDevice, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyDtoHAsync(void *dstHost, HUdeviceptr srcDevice, size_t ByteCount, HUstream hStream) {
    HU_INIT_API(huMemcpyDtoHAsync, dstHost, srcDevice, ByteCount, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyHtoA(HUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount) {
    HU_INIT_API(huMemcpyHtoA, dstArray, dstOffset, srcHost, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyHtoAAsync(HUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount, HUstream hStream) {
    HU_INIT_API(huMemcpyHtoAAsync, dstArray, dstOffset, srcHost, ByteCount, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyHtoD(HUdeviceptr dstDevice, const void *srcHost, size_t ByteCount) {
    HU_INIT_API(huMemcpyHtoD, dstDevice, srcHost, ByteCount);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemcpyHtoDAsync(HUdeviceptr dstDevice, const void *srcHost, size_t ByteCount, HUstream hStream) {
    HU_INIT_API(huMemcpyHtoDAsync, dstDevice, srcHost, ByteCount, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
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

HUresult huMemsetD32(HUdeviceptr dstDevice, unsigned int ui, size_t N) {
    HU_INIT_API(huMemsetD32, dstDevice, ui, N);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMemsetD32Async(HUdeviceptr dstDevice, unsigned int ui, size_t N, HUstream hStream) {
    HU_INIT_API(huMemsetD32Async, dstDevice, ui, N, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
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

