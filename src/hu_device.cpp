#include "hu_internal.h"

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

