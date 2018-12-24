#include "hu_internal.h"

namespace {

HU_STATIC_THREAD_LOCAL_POD(ThreadLocalData, tls_data);

struct ThreadLocalData* get_tls() {
    return &tls_data.get();
}

} // namespace

std::ostream& operator<<(std::ostream& os, const HUstream_st& s) {
	return os;
}

std::ostream& operator<<(std::ostream& os, const HUipcEventHandle_st& s) {
	return os;
}

std::ostream& operator<<(std::ostream& os, const HUipcMemHandle_st& s) {
	return os;
}

HUresult huDriverGetVersion(int *driverVersion) {
    HU_INIT_API(huDriverGetVersion, driverVersion);

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

HUresult huInit(unsigned int Flags) {
    HU_INIT_API(huInit, Flags);

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

