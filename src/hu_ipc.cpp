#include "hu_internal.h"

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

