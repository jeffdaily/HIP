#include <hc.hpp>

#include "hip/hip_common.h"
#include "hip/hip_driver.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

std::ostream& operator<<(std::ostream& os, const HUstream_st& s) {
	return os;
}

std::ostream& operator<<(std::ostream& os, const HUipcEventHandle_st& s) {
	return os;
}

std::ostream& operator<<(std::ostream& os, const HUipcMemHandle_st& s) {
	return os;
}

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

HUresult huArray3DCreate(HUarray *pHandle, const HIP_ARRAY3D_DESCRIPTOR *pAllocateArray) {
    HU_INIT_API(huArray3DCreate, pHandle, pAllocateArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huArray3DGetDescriptor(HIP_ARRAY3D_DESCRIPTOR *pArrayDescriptor, HUarray hArray) {
    HU_INIT_API(huArray3DGetDescriptor, pArrayDescriptor, hArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huArrayCreate(HUarray *pHandle, const HIP_ARRAY_DESCRIPTOR *pAllocateArray) {
    HU_INIT_API(huArrayCreate, pHandle, pAllocateArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huArrayDestroy(HUarray hArray) {
    HU_INIT_API(huArrayDestroy, hArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huArrayGetDescriptor(HIP_ARRAY_DESCRIPTOR *pArrayDescriptor, HUarray hArray) {
    HU_INIT_API(huArrayGetDescriptor, pArrayDescriptor, hArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxAttach(HUcontext *pctx, unsigned int flags) {
    HU_INIT_API(huCtxAttach, pctx, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxCreate(HUcontext *pctx, unsigned int flags, HUdevice dev) {
    HU_INIT_API(huCtxCreate, pctx, flags, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxDestroy(HUcontext ctx) {
    HU_INIT_API(huCtxDestroy, ctx);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxDetach(HUcontext ctx) {
    HU_INIT_API(huCtxDetach, ctx);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxDisablePeerAccess(HUcontext peerContext) {
    HU_INIT_API(huCtxDisablePeerAccess, peerContext);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxEnablePeerAccess(HUcontext peerContext, unsigned int Flags) {
    HU_INIT_API(huCtxEnablePeerAccess, peerContext, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxGetApiVersion(HUcontext ctx, unsigned int *version) {
    HU_INIT_API(huCtxGetApiVersion, ctx, version);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxGetCacheConfig(HUfunc_cache *pconfig) {
    HU_INIT_API(huCtxGetCacheConfig, pconfig);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxGetCurrent(HUcontext *pctx) {
    HU_INIT_API(huCtxGetCurrent, pctx);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxGetDevice(HUdevice *device) {
    HU_INIT_API(huCtxGetDevice, device);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxGetFlags(unsigned int *flags) {
    HU_INIT_API(huCtxGetFlags, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxGetLimit(size_t *pvalue, HUlimit limit) {
    HU_INIT_API(huCtxGetLimit, pvalue, limit);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxGetSharedMemConfig(HUsharedconfig *pConfig) {
    HU_INIT_API(huCtxGetSharedMemConfig, pConfig);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxGetStreamPriorityRange(int *leastPriority, int *greatestPriority) {
    HU_INIT_API(huCtxGetStreamPriorityRange, leastPriority, greatestPriority);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxPopCurrent(HUcontext *pctx) {
    HU_INIT_API(huCtxPopCurrent, pctx);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxPushCurrent(HUcontext ctx) {
    HU_INIT_API(huCtxPushCurrent, ctx);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxSetCacheConfig(HUfunc_cache config) {
    HU_INIT_API(huCtxSetCacheConfig, config);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxSetCurrent(HUcontext ctx) {
    HU_INIT_API(huCtxSetCurrent, ctx);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxSetLimit(HUlimit limit, size_t value) {
    HU_INIT_API(huCtxSetLimit, limit, value);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxSetSharedMemConfig(HUsharedconfig config) {
    HU_INIT_API(huCtxSetSharedMemConfig, config);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huCtxSynchronize(void) {
    HU_INIT_API(huCtxSynchronize);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceCanAccessPeer(int *canAccessPeer, HUdevice dev, HUdevice peerDev) {
    HU_INIT_API(huDeviceCanAccessPeer, canAccessPeer, dev, peerDev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceComputeCapability(int *major, int *minor, HUdevice dev) {
    HU_INIT_API(huDeviceComputeCapability, major, minor, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGet(HUdevice *device, int ordinal) {
    HU_INIT_API(huDeviceGet, device, ordinal);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetAttribute(int *pi, HUdevice_attribute attrib, HUdevice dev) {
    HU_INIT_API(huDeviceGetAttribute, pi, attrib, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetByPCIBusId(HUdevice *dev, const char *pciBusId) {
    HU_INIT_API(huDeviceGetByPCIBusId, dev, pciBusId);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetCount(int *count) {
    HU_INIT_API(huDeviceGetCount, count);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetName(char *name, int len, HUdevice dev) {
    HU_INIT_API(huDeviceGetName, name, len, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetP2PAttribute(int* value, HUdevice_P2PAttribute attrib, HUdevice srcDevice, HUdevice dstDevice) {
    HU_INIT_API(huDeviceGetP2PAttribute, value, attrib, srcDevice, dstDevice);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetPCIBusId(char *pciBusId, int len, HUdevice dev) {
    HU_INIT_API(huDeviceGetPCIBusId, pciBusId, len, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetProperties(HUdevprop *prop, HUdevice dev) {
    HU_INIT_API(huDeviceGetProperties, prop, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetUuid(HUuuid *uuid, HUdevice dev) {
    HU_INIT_API(huDeviceGetUuid, uuid, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDevicePrimaryCtxGetState(HUdevice dev, unsigned int *flags, int *active) {
    HU_INIT_API(huDevicePrimaryCtxGetState, dev, flags, active);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDevicePrimaryCtxRelease(HUdevice dev) {
    HU_INIT_API(huDevicePrimaryCtxRelease, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDevicePrimaryCtxReset(HUdevice dev) {
    HU_INIT_API(huDevicePrimaryCtxReset, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDevicePrimaryCtxRetain(HUcontext *pctx, HUdevice dev) {
    HU_INIT_API(huDevicePrimaryCtxRetain, pctx, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDevicePrimaryCtxSetFlags(HUdevice dev, unsigned int flags) {
    HU_INIT_API(huDevicePrimaryCtxSetFlags, dev, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceTotalMem(size_t *bytes, HUdevice dev) {
    HU_INIT_API(huDeviceTotalMem, bytes, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDriverGetVersion(int *driverVersion) {
    HU_INIT_API(huDriverGetVersion, driverVersion);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huEventCreate(HUevent *phEvent, unsigned int Flags) {
    HU_INIT_API(huEventCreate, phEvent, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huEventDestroy(HUevent hEvent) {
    HU_INIT_API(huEventDestroy, hEvent);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huEventElapsedTime(float *pMilliseconds, HUevent hStart, HUevent hEnd) {
    HU_INIT_API(huEventElapsedTime, pMilliseconds, hStart, hEnd);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huEventQuery(HUevent hEvent) {
    HU_INIT_API(huEventQuery, hEvent);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huEventRecord(HUevent hEvent, HUstream hStream) {
    HU_INIT_API(huEventRecord, hEvent, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huEventSynchronize(HUevent hEvent) {
    HU_INIT_API(huEventSynchronize, hEvent);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncGetAttribute(int *pi, HUfunction_attribute attrib, HUfunction hfunc) {
    HU_INIT_API(huFuncGetAttribute, pi, attrib, hfunc);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetAttribute(HUfunction hfunc, HUfunction_attribute attrib, int value) {
    HU_INIT_API(huFuncSetAttribute, hfunc, attrib, value);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetBlockShape(HUfunction hfunc, int x, int y, int z) {
    HU_INIT_API(huFuncSetBlockShape, hfunc, x, y, z);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetCacheConfig(HUfunction hfunc, HUfunc_cache config) {
    HU_INIT_API(huFuncSetCacheConfig, hfunc, config);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetSharedMemConfig(HUfunction hfunc, HUsharedconfig config) {
    HU_INIT_API(huFuncSetSharedMemConfig, hfunc, config);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetSharedSize(HUfunction hfunc, unsigned int bytes) {
    HU_INIT_API(huFuncSetSharedSize, hfunc, bytes);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGetErrorName(HUresult error, const char **pStr) {
    HU_INIT_API(huGetErrorName, error, pStr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGetErrorString(HUresult error, const char **pStr) {
    HU_INIT_API(huGetErrorString, error, pStr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGetExportTable(const void **ppExportTable, const HUuuid *pExportTableId) {
    HU_INIT_API(huGetExportTable, ppExportTable, pExportTableId);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGraphicsMapResources(unsigned int count, HUgraphicsResource *resources, HUstream hStream) {
    HU_INIT_API(huGraphicsMapResources, count, resources, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGraphicsResourceGetMappedMipmappedArray(HUmipmappedArray *pMipmappedArray, HUgraphicsResource resource) {
    HU_INIT_API(huGraphicsResourceGetMappedMipmappedArray, pMipmappedArray, resource);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGraphicsResourceGetMappedPointer(HUdeviceptr *pDevPtr, size_t *pSize, HUgraphicsResource resource) {
    HU_INIT_API(huGraphicsResourceGetMappedPointer, pDevPtr, pSize, resource);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGraphicsResourceSetMapFlags(HUgraphicsResource resource, unsigned int flags) {
    HU_INIT_API(huGraphicsResourceSetMapFlags, resource, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGraphicsSubResourceGetMappedArray(HUarray *pArray, HUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel) {
    HU_INIT_API(huGraphicsSubResourceGetMappedArray, pArray, resource, arrayIndex, mipLevel);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGraphicsUnmapResources(unsigned int count, HUgraphicsResource *resources, HUstream hStream) {
    HU_INIT_API(huGraphicsUnmapResources, count, resources, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGraphicsUnregisterResource(HUgraphicsResource resource) {
    HU_INIT_API(huGraphicsUnregisterResource, resource);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huInit(unsigned int Flags) {
    HU_INIT_API(huInit, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huIpcCloseMemHandle(HUdeviceptr dptr) {
    HU_INIT_API(huIpcCloseMemHandle, dptr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huIpcGetEventHandle(HUipcEventHandle *pHandle, HUevent event) {
    HU_INIT_API(huIpcGetEventHandle, pHandle, event);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huIpcGetMemHandle(HUipcMemHandle *pHandle, HUdeviceptr dptr) {
    HU_INIT_API(huIpcGetMemHandle, pHandle, dptr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huIpcOpenEventHandle(HUevent *phEvent, HUipcEventHandle handle) {
    HU_INIT_API(huIpcOpenEventHandle, phEvent, handle);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huIpcOpenMemHandle(HUdeviceptr *pdptr, HUipcMemHandle handle, unsigned int Flags) {
    HU_INIT_API(huIpcOpenMemHandle, pdptr, handle, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLaunch(HUfunction f) {
    HU_INIT_API(huLaunch, f);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLaunchCooperativeKernel(HUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, HUstream hStream, void **kernelParams) {
    HU_INIT_API(huLaunchCooperativeKernel, f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLaunchCooperativeKernelMultiDevice(HIP_LAUNCH_PARAMS *launchParamsList, unsigned int numDevices, unsigned int flags) {
    HU_INIT_API(huLaunchCooperativeKernelMultiDevice, launchParamsList, numDevices, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLaunchGrid(HUfunction f, int grid_width, int grid_height) {
    HU_INIT_API(huLaunchGrid, f, grid_width, grid_height);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLaunchGridAsync(HUfunction f, int grid_width, int grid_height, HUstream hStream) {
    HU_INIT_API(huLaunchGridAsync, f, grid_width, grid_height, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLaunchKernel(HUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, HUstream hStream, void **kernelParams, void **extra) {
    HU_INIT_API(huLaunchKernel, f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams, extra);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLinkAddData(HUlinkState state, HUjitInputType type, void *data, size_t size, const char *name, unsigned int numOptions, HUjit_option *options, void **optionValues) {
    HU_INIT_API(huLinkAddData, state, type, data, size, name, numOptions, options, optionValues);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLinkAddFile(HUlinkState state, HUjitInputType type, const char *path, unsigned int numOptions, HUjit_option *options, void **optionValues) {
    HU_INIT_API(huLinkAddFile, state, type, path, numOptions, options, optionValues);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLinkComplete(HUlinkState state, void **cubinOut, size_t *sizeOut) {
    HU_INIT_API(huLinkComplete, state, cubinOut, sizeOut);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLinkCreate(unsigned int numOptions, HUjit_option *options, void **optionValues, HUlinkState *stateOut) {
    HU_INIT_API(huLinkCreate, numOptions, options, optionValues, stateOut);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLinkDestroy(HUlinkState state) {
    HU_INIT_API(huLinkDestroy, state);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

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

HUresult huMipmappedArrayCreate(HUmipmappedArray *pHandle, const HIP_ARRAY3D_DESCRIPTOR *pMipmappedArrayDesc, unsigned int numMipmapLevels) {
    HU_INIT_API(huMipmappedArrayCreate, pHandle, pMipmappedArrayDesc, numMipmapLevels);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMipmappedArrayDestroy(HUmipmappedArray hMipmappedArray) {
    HU_INIT_API(huMipmappedArrayDestroy, hMipmappedArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMipmappedArrayGetLevel(HUarray *pLevelArray, HUmipmappedArray hMipmappedArray, unsigned int level) {
    HU_INIT_API(huMipmappedArrayGetLevel, pLevelArray, hMipmappedArray, level);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleGetFunction(HUfunction *hfunc, HUmodule hmod, const char *name) {
    HU_INIT_API(huModuleGetFunction, hfunc, hmod, name);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleGetGlobal(HUdeviceptr *dptr, size_t *bytes, HUmodule hmod, const char *name) {
    HU_INIT_API(huModuleGetGlobal, dptr, bytes, hmod, name);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleGetSurfRef(HUsurfref *pSurfRef, HUmodule hmod, const char *name) {
    HU_INIT_API(huModuleGetSurfRef, pSurfRef, hmod, name);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleGetTexRef(HUtexref *pTexRef, HUmodule hmod, const char *name) {
    HU_INIT_API(huModuleGetTexRef, pTexRef, hmod, name);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleLoad(HUmodule *module, const char *fname) {
    HU_INIT_API(huModuleLoad, module, fname);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleLoadData(HUmodule *module, const void *image) {
    HU_INIT_API(huModuleLoadData, module, image);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleLoadDataEx(HUmodule *module, const void *image, unsigned int numOptions, HUjit_option *options, void **optionValues) {
    HU_INIT_API(huModuleLoadDataEx, module, image, numOptions, options, optionValues);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleLoadFatBinary(HUmodule *module, const void *fatCubin) {
    HU_INIT_API(huModuleLoadFatBinary, module, fatCubin);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleUnload(HUmodule hmod) {
    HU_INIT_API(huModuleUnload, hmod);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huOccupancyMaxActiveBlocksPerMultiprocessor(int *numBlocks, HUfunction func, int blockSize, size_t dynamicSMemSize) {
    HU_INIT_API(huOccupancyMaxActiveBlocksPerMultiprocessor, numBlocks, func, blockSize, dynamicSMemSize);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int *numBlocks, HUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags) {
    HU_INIT_API(huOccupancyMaxActiveBlocksPerMultiprocessorWithFlags, numBlocks, func, blockSize, dynamicSMemSize, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huOccupancyMaxPotentialBlockSize(int *minGridSize, int *blockSize, HUfunction func, HUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit) {
    HU_INIT_API(huOccupancyMaxPotentialBlockSize, minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huOccupancyMaxPotentialBlockSizeWithFlags(int *minGridSize, int *blockSize, HUfunction func, HUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags) {
    HU_INIT_API(huOccupancyMaxPotentialBlockSizeWithFlags, minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSetSize(HUfunction hfunc, unsigned int numbytes) {
    HU_INIT_API(huParamSetSize, hfunc, numbytes);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSetTexRef(HUfunction hfunc, int texunit, HUtexref hTexRef) {
    HU_INIT_API(huParamSetTexRef, hfunc, texunit, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSetf(HUfunction hfunc, int offset, float value) {
    HU_INIT_API(huParamSetf, hfunc, offset, value);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSeti(HUfunction hfunc, int offset, unsigned int value) {
    HU_INIT_API(huParamSeti, hfunc, offset, value);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSetv(HUfunction hfunc, int offset, void *ptr, unsigned int numbytes) {
    HU_INIT_API(huParamSetv, hfunc, offset, ptr, numbytes);

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

HUresult huStreamAddCallback(HUstream hStream, HUstreamCallback callback, void *userData, unsigned int flags) {
    HU_INIT_API(huStreamAddCallback, hStream, callback, userData, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamAttachMemAsync(HUstream hStream, HUdeviceptr dptr, size_t length, unsigned int flags) {
    HU_INIT_API(huStreamAttachMemAsync, hStream, dptr, length, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamBatchMemOp(HUstream stream, unsigned int count, HUstreamBatchMemOpParams *paramArray, unsigned int flags) {
    HU_INIT_API(huStreamBatchMemOp, stream, count, paramArray, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamCreate(HUstream *phStream, unsigned int Flags) {
    HU_INIT_API(huStreamCreate, phStream, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamCreateWithPriority(HUstream *phStream, unsigned int flags, int priority) {
    HU_INIT_API(huStreamCreateWithPriority, phStream, flags, priority);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamDestroy(HUstream hStream) {
    HU_INIT_API(huStreamDestroy, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamGetCtx(HUstream hStream, HUcontext *pctx) {
    HU_INIT_API(huStreamGetCtx, hStream, pctx);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamGetFlags(HUstream hStream, unsigned int *flags) {
    HU_INIT_API(huStreamGetFlags, hStream, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamGetPriority(HUstream hStream, int *priority) {
    HU_INIT_API(huStreamGetPriority, hStream, priority);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamQuery(HUstream hStream) {
    HU_INIT_API(huStreamQuery, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamSynchronize(HUstream hStream) {
    HU_INIT_API(huStreamSynchronize, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamWaitEvent(HUstream hStream, HUevent hEvent, unsigned int Flags) {
    HU_INIT_API(huStreamWaitEvent, hStream, hEvent, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamWaitValue32(HUstream stream, HUdeviceptr addr, huuint32_t value, unsigned int flags) {
    HU_INIT_API(huStreamWaitValue32, stream, addr, value, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamWaitValue64(HUstream stream, HUdeviceptr addr, huuint64_t value, unsigned int flags) {
    HU_INIT_API(huStreamWaitValue64, stream, addr, value, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamWriteValue32(HUstream stream, HUdeviceptr addr, huuint32_t value, unsigned int flags) {
    HU_INIT_API(huStreamWriteValue32, stream, addr, value, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamWriteValue64(HUstream stream, HUdeviceptr addr, huuint64_t value, unsigned int flags) {
    HU_INIT_API(huStreamWriteValue64, stream, addr, value, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huSurfObjectCreate(HUsurfObject *pSurfObject, const HIP_RESOURCE_DESC *pResDesc) {
    HU_INIT_API(huSurfObjectCreate, pSurfObject, pResDesc);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huSurfObjectDestroy(HUsurfObject surfObject) {
    HU_INIT_API(huSurfObjectDestroy, surfObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huSurfObjectGetResourceDesc(HIP_RESOURCE_DESC *pResDesc, HUsurfObject surfObject) {
    HU_INIT_API(huSurfObjectGetResourceDesc, pResDesc, surfObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huSurfRefGetArray(HUarray *phArray, HUsurfref hSurfRef) {
    HU_INIT_API(huSurfRefGetArray, phArray, hSurfRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huSurfRefSetArray(HUsurfref hSurfRef, HUarray hArray, unsigned int Flags) {
    HU_INIT_API(huSurfRefSetArray, hSurfRef, hArray, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectCreate(HUtexObject *pTexObject, const HIP_RESOURCE_DESC *pResDesc, const HIP_TEXTURE_DESC *pTexDesc, const HIP_RESOURCE_VIEW_DESC *pResViewDesc) {
    HU_INIT_API(huTexObjectCreate, pTexObject, pResDesc, pTexDesc, pResViewDesc);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectDestroy(HUtexObject texObject) {
    HU_INIT_API(huTexObjectDestroy, texObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectGetResourceDesc(HIP_RESOURCE_DESC *pResDesc, HUtexObject texObject) {
    HU_INIT_API(huTexObjectGetResourceDesc, pResDesc, texObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectGetResourceViewDesc(HIP_RESOURCE_VIEW_DESC *pResViewDesc, HUtexObject texObject) {
    HU_INIT_API(huTexObjectGetResourceViewDesc, pResViewDesc, texObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectGetTextureDesc(HIP_TEXTURE_DESC *pTexDesc, HUtexObject texObject) {
    HU_INIT_API(huTexObjectGetTextureDesc, pTexDesc, texObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefCreate(HUtexref *pTexRef) {
    HU_INIT_API(huTexRefCreate, pTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefDestroy(HUtexref hTexRef) {
    HU_INIT_API(huTexRefDestroy, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetAddress(HUdeviceptr *pdptr, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetAddress, pdptr, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetAddressMode(HUaddress_mode *pam, HUtexref hTexRef, int dim) {
    HU_INIT_API(huTexRefGetAddressMode, pam, hTexRef, dim);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetArray(HUarray *phArray, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetArray, phArray, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetBorderColor(float *pBorderColor, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetBorderColor, pBorderColor, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetFilterMode(HUfilter_mode *pfm, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetFilterMode, pfm, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetFlags(unsigned int *pFlags, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetFlags, pFlags, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetFormat(HUarray_format *pFormat, int *pNumChannels, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetFormat, pFormat, pNumChannels, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMaxAnisotropy(int *pmaxAniso, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMaxAnisotropy, pmaxAniso, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMipmapFilterMode(HUfilter_mode *pfm, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMipmapFilterMode, pfm, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMipmapLevelBias(float *pbias, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMipmapLevelBias, pbias, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMipmapLevelClamp(float *pminMipmapLevelClamp, float *pmaxMipmapLevelClamp, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMipmapLevelClamp, pminMipmapLevelClamp, pmaxMipmapLevelClamp, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMipmappedArray(HUmipmappedArray *phMipmappedArray, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMipmappedArray, phMipmappedArray, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetAddress(size_t *ByteOffset, HUtexref hTexRef, HUdeviceptr dptr, size_t bytes) {
    HU_INIT_API(huTexRefSetAddress, ByteOffset, hTexRef, dptr, bytes);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetAddress2D(HUtexref hTexRef, const HIP_ARRAY_DESCRIPTOR *desc, HUdeviceptr dptr, size_t Pitch) {
    HU_INIT_API(huTexRefSetAddress2D, hTexRef, desc, dptr, Pitch);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetAddressMode(HUtexref hTexRef, int dim, HUaddress_mode am) {
    HU_INIT_API(huTexRefSetAddressMode, hTexRef, dim, am);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetArray(HUtexref hTexRef, HUarray hArray, unsigned int Flags) {
    HU_INIT_API(huTexRefSetArray, hTexRef, hArray, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetBorderColor(HUtexref hTexRef, float *pBorderColor) {
    HU_INIT_API(huTexRefSetBorderColor, hTexRef, pBorderColor);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetFilterMode(HUtexref hTexRef, HUfilter_mode fm) {
    HU_INIT_API(huTexRefSetFilterMode, hTexRef, fm);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetFlags(HUtexref hTexRef, unsigned int Flags) {
    HU_INIT_API(huTexRefSetFlags, hTexRef, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetFormat(HUtexref hTexRef, HUarray_format fmt, int NumPackedComponents) {
    HU_INIT_API(huTexRefSetFormat, hTexRef, fmt, NumPackedComponents);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMaxAnisotropy(HUtexref hTexRef, unsigned int maxAniso) {
    HU_INIT_API(huTexRefSetMaxAnisotropy, hTexRef, maxAniso);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMipmapFilterMode(HUtexref hTexRef, HUfilter_mode fm) {
    HU_INIT_API(huTexRefSetMipmapFilterMode, hTexRef, fm);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMipmapLevelBias(HUtexref hTexRef, float bias) {
    HU_INIT_API(huTexRefSetMipmapLevelBias, hTexRef, bias);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMipmapLevelClamp(HUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp) {
    HU_INIT_API(huTexRefSetMipmapLevelClamp, hTexRef, minMipmapLevelClamp, maxMipmapLevelClamp);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMipmappedArray(HUtexref hTexRef, HUmipmappedArray hMipmappedArray, unsigned int Flags) {
    HU_INIT_API(huTexRefSetMipmappedArray, hTexRef, hMipmappedArray, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

