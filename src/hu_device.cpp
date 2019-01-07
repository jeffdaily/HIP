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

    HUresult e = HIP_SUCCESS;

    auto ctx = ihipGetTlsDefaultCtx();

    if (device != nullptr) {
        if (ctx == nullptr) {
            e = HIP_ERROR_INVALID_DEVICE;  // TODO, check error code.
            *device = -1;
        } else {
            *device = ctx->getDevice()->_deviceId;
        }
    } else {
        e = HIP_ERROR_INVALID_VALUE;
    }

    return ihuLogStatus(e);
}

HUresult huDeviceGetAttribute(int *pi, HUdevice_attribute attr, HUdevice device) {
    HU_INIT_API(huDeviceGetAttribute, pi, attr, device);

    HUresult e = HIP_SUCCESS;

    if (pi == nullptr) {
        e = HIP_ERROR_INVALID_VALUE;
    }
    else {
        auto* hipDevice = ihipGetDevice(device);
        if (hipDevice == nullptr) {
            e = HIP_ERROR_INVALID_DEVICE;
        }
        else {
            hipDeviceProp_t* prop = &hipDevice->_props;
            if (hipDevice) {
                switch (attr) {
                    case hipDeviceAttributeMaxThreadsPerBlock:
                        *pi = prop->maxThreadsPerBlock;
                        break;
                    case hipDeviceAttributeMaxBlockDimX:
                        *pi = prop->maxThreadsDim[0];
                        break;
                    case hipDeviceAttributeMaxBlockDimY:
                        *pi = prop->maxThreadsDim[1];
                        break;
                    case hipDeviceAttributeMaxBlockDimZ:
                        *pi = prop->maxThreadsDim[2];
                        break;
                    case hipDeviceAttributeMaxGridDimX:
                        *pi = prop->maxGridSize[0];
                        break;
                    case hipDeviceAttributeMaxGridDimY:
                        *pi = prop->maxGridSize[1];
                        break;
                    case hipDeviceAttributeMaxGridDimZ:
                        *pi = prop->maxGridSize[2];
                        break;
                    case hipDeviceAttributeMaxSharedMemoryPerBlock:
                        *pi = prop->sharedMemPerBlock;
                        break;
                    case hipDeviceAttributeTotalConstantMemory:
                        *pi = prop->totalConstMem;
                        break;
                    case hipDeviceAttributeWarpSize:
                        *pi = prop->warpSize;
                        break;
                    case hipDeviceAttributeMaxRegistersPerBlock:
                        *pi = prop->regsPerBlock;
                        break;
                    case hipDeviceAttributeClockRate:
                        *pi = prop->clockRate;
                        break;
                    case hipDeviceAttributeMemoryClockRate:
                        *pi = prop->memoryClockRate;
                        break;
                    case hipDeviceAttributeMemoryBusWidth:
                        *pi = prop->memoryBusWidth;
                        break;
                    case hipDeviceAttributeMultiprocessorCount:
                        *pi = prop->multiProcessorCount;
                        break;
                    case hipDeviceAttributeComputeMode:
                        *pi = prop->computeMode;
                        break;
                    case hipDeviceAttributeL2CacheSize:
                        *pi = prop->l2CacheSize;
                        break;
                    case hipDeviceAttributeMaxThreadsPerMultiProcessor:
                        *pi = prop->maxThreadsPerMultiProcessor;
                        break;
                    case hipDeviceAttributeComputeCapabilityMajor:
                        *pi = prop->major;
                        break;
                    case hipDeviceAttributeComputeCapabilityMinor:
                        *pi = prop->minor;
                        break;
                    case hipDeviceAttributePciBusId:
                        *pi = prop->pciBusID;
                        break;
                    case hipDeviceAttributeConcurrentKernels:
                        *pi = prop->concurrentKernels;
                        break;
                    case hipDeviceAttributePciDeviceId:
                        *pi = prop->pciDeviceID;
                        break;
                    case hipDeviceAttributeMaxSharedMemoryPerMultiprocessor:
                        *pi = prop->maxSharedMemoryPerMultiProcessor;
                        break;
                    case hipDeviceAttributeIsMultiGpuBoard:
                        *pi = prop->isMultiGpuBoard;
                        break;
                    case hipDeviceAttributeIntegrated:
                        *pi = prop->integrated;
                        break;
                    default:
                        e = HIP_ERROR_INVALID_VALUE;
                        break;
                }
            } else {
                e = HIP_ERROR_INVALID_DEVICE;
            }
        }
    }
    return ihuLogStatus(e);
}

HUresult huDeviceGetByPCIBusId(HUdevice *dev, const char *pciBusId) {
    HU_INIT_API(huDeviceGetByPCIBusId, dev, pciBusId);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetCount(int *count) {
    HU_INIT_API(huDeviceGetCount, count);
    HUresult e = HIP_SUCCESS;
    if (count != nullptr) {
        *count = g_deviceCnt;
        if (*count > 0) {
            e = HIP_SUCCESS;
        } else {
            e = HIP_ERROR_NO_DEVICE;
        }
    } else {
        e = HIP_ERROR_INVALID_VALUE;
    }
    return ihuLogStatus(e);
}

HUresult huDeviceGetName(char *name, int len, HUdevice device) {
    HU_INIT_API(huDeviceGetName, name, len, dev);

    HUresult e = HIP_SUCCESS;
    if ((device < 0) || (device >= g_deviceCnt)) {
        e = HIP_ERROR_INVALID_DEVICE;
    } else {
        auto deviceHandle = ihipGetDevice(device);
        int nameLen = strlen(deviceHandle->_props.name);
        if (nameLen <= len) memcpy(name, deviceHandle->_props.name, nameLen);
    }

    return ihuLogStatus(e);
}

HUresult huDeviceGetP2PAttribute(int* value, HUdevice_P2PAttribute attrib, HUdevice srcDevice, HUdevice dstDevice) {
    HU_INIT_API(huDeviceGetP2PAttribute, value, attrib, srcDevice, dstDevice);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceGetPCIBusId(char *pciBusId, int len, HUdevice device) {
    // Cast to void* here to avoid printing garbage in debug modes.
    HU_INIT_API(huDeviceGetPCIBusId, (void*)pciBusId, len, device);

    HUresult e = HIP_ERROR_INVALID_VALUE;
    if ((device < 0) || (device >= g_deviceCnt)) {
        e = HIP_ERROR_INVALID_DEVICE;
    } else {
        if ((pciBusId != nullptr) && (len > 0)) {
            auto deviceHandle = ihipGetDevice(device);
            int retVal =
                snprintf(pciBusId, len, "%04x:%02x:%02x.0", deviceHandle->_props.pciDomainID,
                         deviceHandle->_props.pciBusID, deviceHandle->_props.pciDeviceID);
            if (retVal > 0 && retVal < len) {
                e = HIP_SUCCESS;
            }
        }
    }

    return ihuLogStatus(e);
}

HUresult huDeviceGetProperties(HUdevprop *props, HUdevice device) {
    HU_INIT_API(huDeviceGetProperties, props, device);

    HUresult e;

    if (props != nullptr) {
        auto* hipDevice = ihipGetDevice(device);
        if (hipDevice) {
            // copy saved props
            *props = hipDevice->_props;
            e = HIP_SUCCESS;
        } else {
            e = HIP_ERROR_INVALID_DEVICE;
        }
    } else {
        e = HIP_ERROR_INVALID_VALUE;
    }

    return ihuLogStatus(e);
}

HUresult huDeviceGetUuid(HUuuid *uuid, HUdevice dev) {
    HU_INIT_API(huDeviceGetUuid, uuid, dev);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDevicePrimaryCtxGetState(HUdevice dev, unsigned int *flags, int *active) {
    HU_INIT_API(huDevicePrimaryCtxGetState, dev, flags, active);

    HUresult e = HIP_SUCCESS;

    if (flags == NULL || active == NULL) {
        e = HIP_ERROR_INVALID_VALUE;
    }
    else {
        auto deviceHandle = ihipGetDevice(dev);
        if (deviceHandle == NULL) {
            e = HIP_ERROR_INVALID_DEVICE;
        }
        else {
            ihipCtx_t* tempCtx = ihipGetTlsDefaultCtx();
            ihipCtx_t* primaryCtx = deviceHandle->_primaryCtx;
            if (tempCtx == primaryCtx) {
                *active = 1;
                //*flags = tempCtx->_ctxFlags;
                *flags = 0;
            } else {
                *active = 0;
                //*flags = primaryCtx->_ctxFlags;
                *flags = 0;
            }
        }
    }

    return ihuLogStatus(e);
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

    HUresult e = HIP_SUCCESS;

    if (pctx == NULL) {
        e = HIP_ERROR_INVALID_VALUE;
    }
    else {
        auto deviceHandle = ihipGetDevice(dev);
        if (deviceHandle == NULL) {
            e = HIP_ERROR_INVALID_DEVICE;
        }
        else {
            *pctx = deviceHandle->_primaryCtx;
        }
    }

    return ihuLogStatus(e);;
}

HUresult huDevicePrimaryCtxSetFlags(HUdevice dev, unsigned int flags) {
    HU_INIT_API(huDevicePrimaryCtxSetFlags, dev, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huDeviceTotalMem(size_t *bytes, HUdevice device) {
    HU_INIT_API(huDeviceTotalMem, bytes, dev);

    HUresult e = HIP_SUCCESS;
    if ((device < 0) || (device >= g_deviceCnt)) {
        e = HIP_ERROR_INVALID_DEVICE;
    } else {
        auto deviceHandle = ihipGetDevice(device);
        *bytes = deviceHandle->_props.totalGlobalMem;
    }

    return ihuLogStatus(e);
}

