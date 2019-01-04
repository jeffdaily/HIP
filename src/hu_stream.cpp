#include "hu_internal.h"

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

