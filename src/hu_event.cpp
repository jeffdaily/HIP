#include "hu_internal.h"

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

