#include "hu_internal.h"

namespace {

HU_STATIC_THREAD_LOCAL_POD(ThreadLocalData, tls_data);

struct ThreadLocalData* get_tls() {
    return &tls_data.get();
}

} // namespace

std::ostream& operator<<(std::ostream& os, const HUipcEventHandle_st& s) {
	return os;
}

std::ostream& operator<<(std::ostream& os, const HUipcMemHandle_st& s) {
	return os;
}

HUresult huDriverGetVersion(int *driverVersion) {
    HU_INIT_API(huDriverGetVersion, driverVersion);

    HUresult e = HIP_SUCCESS;
    if (driverVersion) {
        *driverVersion = 4;
    } else {
        e = HIP_ERROR_INVALID_VALUE;
    }

    return ihuLogStatus(e);;
}

#define HU_ERROR_NAME(error) case error: *pStr = #error; break;
HUresult huGetErrorName(HUresult error, const char **pStr) {
    HU_INIT_API(huGetErrorName, error, pStr);

    switch (error) {
        HU_ERROR_NAME(HIP_SUCCESS)
        HU_ERROR_NAME(HIP_ERROR_INVALID_VALUE)
        HU_ERROR_NAME(HIP_ERROR_OUT_OF_MEMORY)
        HU_ERROR_NAME(HIP_ERROR_NOT_INITIALIZED)
        HU_ERROR_NAME(HIP_ERROR_DEINITIALIZED)
        HU_ERROR_NAME(HIP_ERROR_PROFILER_DISABLED)
        HU_ERROR_NAME(HIP_ERROR_PROFILER_NOT_INITIALIZED)
        HU_ERROR_NAME(HIP_ERROR_PROFILER_ALREADY_STARTED)
        HU_ERROR_NAME(HIP_ERROR_PROFILER_ALREADY_STOPPED)
        HU_ERROR_NAME(HIP_ERROR_NO_DEVICE)
        HU_ERROR_NAME(HIP_ERROR_INVALID_DEVICE)
        HU_ERROR_NAME(HIP_ERROR_INVALID_IMAGE)
        HU_ERROR_NAME(HIP_ERROR_INVALID_CONTEXT)
        HU_ERROR_NAME(HIP_ERROR_CONTEXT_ALREADY_CURRENT)
        HU_ERROR_NAME(HIP_ERROR_MAP_FAILED)
        HU_ERROR_NAME(HIP_ERROR_UNMAP_FAILED)
        HU_ERROR_NAME(HIP_ERROR_ARRAY_IS_MAPPED)
        HU_ERROR_NAME(HIP_ERROR_ALREADY_MAPPED)
        HU_ERROR_NAME(HIP_ERROR_NO_BINARY_FOR_GPU)
        HU_ERROR_NAME(HIP_ERROR_ALREADY_ACQUIRED)
        HU_ERROR_NAME(HIP_ERROR_NOT_MAPPED)
        HU_ERROR_NAME(HIP_ERROR_NOT_MAPPED_AS_ARRAY)
        HU_ERROR_NAME(HIP_ERROR_NOT_MAPPED_AS_POINTER)
        HU_ERROR_NAME(HIP_ERROR_ECC_UNCORRECTABLE)
        HU_ERROR_NAME(HIP_ERROR_UNSUPPORTED_LIMIT)
        HU_ERROR_NAME(HIP_ERROR_CONTEXT_ALREADY_IN_USE)
        HU_ERROR_NAME(HIP_ERROR_PEER_ACCESS_UNSUPPORTED)
        HU_ERROR_NAME(HIP_ERROR_INVALID_PTX)
        HU_ERROR_NAME(HIP_ERROR_INVALID_GRAPHICS_CONTEXT)
        HU_ERROR_NAME(HIP_ERROR_NVLINK_UNCORRECTABLE)
        HU_ERROR_NAME(HIP_ERROR_JIT_COMPILER_NOT_FOUND)
        HU_ERROR_NAME(HIP_ERROR_INVALID_SOURCE)
        HU_ERROR_NAME(HIP_ERROR_FILE_NOT_FOUND)
        HU_ERROR_NAME(HIP_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND)
        HU_ERROR_NAME(HIP_ERROR_SHARED_OBJECT_INIT_FAILED)
        HU_ERROR_NAME(HIP_ERROR_OPERATING_SYSTEM)
        HU_ERROR_NAME(HIP_ERROR_INVALID_HANDLE)
        HU_ERROR_NAME(HIP_ERROR_NOT_FOUND)
        HU_ERROR_NAME(HIP_ERROR_NOT_READY)
        HU_ERROR_NAME(HIP_ERROR_ILLEGAL_ADDRESS)
        HU_ERROR_NAME(HIP_ERROR_LAUNCH_OUT_OF_RESOURCES)
        HU_ERROR_NAME(HIP_ERROR_LAUNCH_TIMEOUT)
        HU_ERROR_NAME(HIP_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING)
        HU_ERROR_NAME(HIP_ERROR_PEER_ACCESS_ALREADY_ENABLED)
        HU_ERROR_NAME(HIP_ERROR_PEER_ACCESS_NOT_ENABLED)
        HU_ERROR_NAME(HIP_ERROR_PRIMARY_CONTEXT_ACTIVE)
        HU_ERROR_NAME(HIP_ERROR_CONTEXT_IS_DESTROYED)
        HU_ERROR_NAME(HIP_ERROR_ASSERT)
        HU_ERROR_NAME(HIP_ERROR_TOO_MANY_PEERS)
        HU_ERROR_NAME(HIP_ERROR_HOST_MEMORY_ALREADY_REGISTERED)
        HU_ERROR_NAME(HIP_ERROR_HOST_MEMORY_NOT_REGISTERED)
        HU_ERROR_NAME(HIP_ERROR_HARDWARE_STACK_ERROR)
        HU_ERROR_NAME(HIP_ERROR_ILLEGAL_INSTRUCTION)
        HU_ERROR_NAME(HIP_ERROR_MISALIGNED_ADDRESS)
        HU_ERROR_NAME(HIP_ERROR_INVALID_ADDRESS_SPACE)
        HU_ERROR_NAME(HIP_ERROR_INVALID_PC)
        HU_ERROR_NAME(HIP_ERROR_LAUNCH_FAILED)
        HU_ERROR_NAME(HIP_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE)
        HU_ERROR_NAME(HIP_ERROR_NOT_PERMITTED)
        HU_ERROR_NAME(HIP_ERROR_NOT_SUPPORTED)
        HU_ERROR_NAME(HIP_ERROR_UNKNOWN)
    }

    return ihuLogStatus(HIP_SUCCESS);
}

HUresult huGetErrorString(HUresult error, const char **pStr) {
    HU_INIT_API(huGetErrorString, error, pStr);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huGetExportTable(const void **ppExportTable, const HUuuid *pExportTableId) {
    HU_INIT_API(huGetExportTable, ppExportTable, pExportTableId);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huInit(unsigned int Flags) {
    HU_INIT_API(huInit, Flags);

    return ihuLogStatus(HIP_SUCCESS);;
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

