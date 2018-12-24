#include "hu_internal.h"

HUresult huArray3DCreate(HUarray *pHandle, const HIP_ARRAY3D_DESCRIPTOR *pAllocateArray) {
    HU_INIT_API(huArray3DCreate, pHandle, pAllocateArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huArray3DGetDescriptor(HIP_ARRAY3D_DESCRIPTOR *pArrayDescriptor, HUarray hArray) {
    HU_INIT_API(huArray3DGetDescriptor, pArrayDescriptor, hArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huArrayCreate(HUarray *pHandle, const HIP_ARRAY_DESCRIPTOR *pAllocateArray) {
    HU_INIT_API(huArrayCreate, pHandle, pAllocateArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huArrayDestroy(HUarray hArray) {
    HU_INIT_API(huArrayDestroy, hArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huArrayGetDescriptor(HIP_ARRAY_DESCRIPTOR *pArrayDescriptor, HUarray hArray) {
    HU_INIT_API(huArrayGetDescriptor, pArrayDescriptor, hArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMipmappedArrayCreate(HUmipmappedArray *pHandle, const HIP_ARRAY3D_DESCRIPTOR *pMipmappedArrayDesc, unsigned int numMipmapLevels) {
    HU_INIT_API(huMipmappedArrayCreate, pHandle, pMipmappedArrayDesc, numMipmapLevels);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMipmappedArrayDestroy(HUmipmappedArray hMipmappedArray) {
    HU_INIT_API(huMipmappedArrayDestroy, hMipmappedArray);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huMipmappedArrayGetLevel(HUarray *pLevelArray, HUmipmappedArray hMipmappedArray, unsigned int level) {
    HU_INIT_API(huMipmappedArrayGetLevel, pLevelArray, hMipmappedArray, level);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

