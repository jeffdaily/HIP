#include "hu_internal.h"

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

