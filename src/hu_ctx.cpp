#include "hu_internal.h"

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

