#include "hu_internal.h"

HUresult huSurfObjectCreate(HUsurfObject *pSurfObject, const HIP_RESOURCE_DESC *pResDesc) {
    HU_INIT_API(huSurfObjectCreate, pSurfObject, pResDesc);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huSurfObjectDestroy(HUsurfObject surfObject) {
    HU_INIT_API(huSurfObjectDestroy, surfObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huSurfObjectGetResourceDesc(HIP_RESOURCE_DESC *pResDesc, HUsurfObject surfObject) {
    HU_INIT_API(huSurfObjectGetResourceDesc, pResDesc, surfObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huSurfRefGetArray(HUarray *phArray, HUsurfref hSurfRef) {
    HU_INIT_API(huSurfRefGetArray, phArray, hSurfRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huSurfRefSetArray(HUsurfref hSurfRef, HUarray hArray, unsigned int Flags) {
    HU_INIT_API(huSurfRefSetArray, hSurfRef, hArray, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectCreate(HUtexObject *pTexObject, const HIP_RESOURCE_DESC *pResDesc, const HIP_TEXTURE_DESC *pTexDesc, const HIP_RESOURCE_VIEW_DESC *pResViewDesc) {
    HU_INIT_API(huTexObjectCreate, pTexObject, pResDesc, pTexDesc, pResViewDesc);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectDestroy(HUtexObject texObject) {
    HU_INIT_API(huTexObjectDestroy, texObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectGetResourceDesc(HIP_RESOURCE_DESC *pResDesc, HUtexObject texObject) {
    HU_INIT_API(huTexObjectGetResourceDesc, pResDesc, texObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectGetResourceViewDesc(HIP_RESOURCE_VIEW_DESC *pResViewDesc, HUtexObject texObject) {
    HU_INIT_API(huTexObjectGetResourceViewDesc, pResViewDesc, texObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexObjectGetTextureDesc(HIP_TEXTURE_DESC *pTexDesc, HUtexObject texObject) {
    HU_INIT_API(huTexObjectGetTextureDesc, pTexDesc, texObject);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefCreate(HUtexref *pTexRef) {
    HU_INIT_API(huTexRefCreate, pTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefDestroy(HUtexref hTexRef) {
    HU_INIT_API(huTexRefDestroy, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetAddress(HUdeviceptr *pdptr, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetAddress, pdptr, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetAddressMode(HUaddress_mode *pam, HUtexref hTexRef, int dim) {
    HU_INIT_API(huTexRefGetAddressMode, pam, hTexRef, dim);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetArray(HUarray *phArray, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetArray, phArray, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetBorderColor(float *pBorderColor, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetBorderColor, pBorderColor, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetFilterMode(HUfilter_mode *pfm, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetFilterMode, pfm, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetFlags(unsigned int *pFlags, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetFlags, pFlags, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetFormat(HUarray_format *pFormat, int *pNumChannels, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetFormat, pFormat, pNumChannels, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMaxAnisotropy(int *pmaxAniso, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMaxAnisotropy, pmaxAniso, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMipmapFilterMode(HUfilter_mode *pfm, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMipmapFilterMode, pfm, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMipmapLevelBias(float *pbias, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMipmapLevelBias, pbias, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMipmapLevelClamp(float *pminMipmapLevelClamp, float *pmaxMipmapLevelClamp, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMipmapLevelClamp, pminMipmapLevelClamp, pmaxMipmapLevelClamp, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefGetMipmappedArray(HUmipmappedArray *phMipmappedArray, HUtexref hTexRef) {
    HU_INIT_API(huTexRefGetMipmappedArray, phMipmappedArray, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetAddress(size_t *ByteOffset, HUtexref hTexRef, HUdeviceptr dptr, size_t bytes) {
    HU_INIT_API(huTexRefSetAddress, ByteOffset, hTexRef, dptr, bytes);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetAddress2D(HUtexref hTexRef, const HIP_ARRAY_DESCRIPTOR *desc, HUdeviceptr dptr, size_t Pitch) {
    HU_INIT_API(huTexRefSetAddress2D, hTexRef, desc, dptr, Pitch);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetAddressMode(HUtexref hTexRef, int dim, HUaddress_mode am) {
    HU_INIT_API(huTexRefSetAddressMode, hTexRef, dim, am);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetArray(HUtexref hTexRef, HUarray hArray, unsigned int Flags) {
    HU_INIT_API(huTexRefSetArray, hTexRef, hArray, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetBorderColor(HUtexref hTexRef, float *pBorderColor) {
    HU_INIT_API(huTexRefSetBorderColor, hTexRef, pBorderColor);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetFilterMode(HUtexref hTexRef, HUfilter_mode fm) {
    HU_INIT_API(huTexRefSetFilterMode, hTexRef, fm);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetFlags(HUtexref hTexRef, unsigned int Flags) {
    HU_INIT_API(huTexRefSetFlags, hTexRef, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetFormat(HUtexref hTexRef, HUarray_format fmt, int NumPackedComponents) {
    HU_INIT_API(huTexRefSetFormat, hTexRef, fmt, NumPackedComponents);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMaxAnisotropy(HUtexref hTexRef, unsigned int maxAniso) {
    HU_INIT_API(huTexRefSetMaxAnisotropy, hTexRef, maxAniso);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMipmapFilterMode(HUtexref hTexRef, HUfilter_mode fm) {
    HU_INIT_API(huTexRefSetMipmapFilterMode, hTexRef, fm);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMipmapLevelBias(HUtexref hTexRef, float bias) {
    HU_INIT_API(huTexRefSetMipmapLevelBias, hTexRef, bias);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMipmapLevelClamp(HUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp) {
    HU_INIT_API(huTexRefSetMipmapLevelClamp, hTexRef, minMipmapLevelClamp, maxMipmapLevelClamp);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huTexRefSetMipmappedArray(HUtexref hTexRef, HUmipmappedArray hMipmappedArray, unsigned int Flags) {
    HU_INIT_API(huTexRefSetMipmappedArray, hTexRef, hMipmappedArray, Flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

