#include "hu_internal.h"

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

