#include "hu_internal.h"

HUresult huFuncGetAttribute(int *pi, HUfunction_attribute attrib, HUfunction hfunc) {
    HU_INIT_API(huFuncGetAttribute, pi, attrib, hfunc);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetAttribute(HUfunction hfunc, HUfunction_attribute attrib, int value) {
    HU_INIT_API(huFuncSetAttribute, hfunc, attrib, value);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetBlockShape(HUfunction hfunc, int x, int y, int z) {
    HU_INIT_API(huFuncSetBlockShape, hfunc, x, y, z);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetCacheConfig(HUfunction hfunc, HUfunc_cache config) {
    HU_INIT_API(huFuncSetCacheConfig, hfunc, config);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetSharedMemConfig(HUfunction hfunc, HUsharedconfig config) {
    HU_INIT_API(huFuncSetSharedMemConfig, hfunc, config);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huFuncSetSharedSize(HUfunction hfunc, unsigned int bytes) {
    HU_INIT_API(huFuncSetSharedSize, hfunc, bytes);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSetSize(HUfunction hfunc, unsigned int numbytes) {
    HU_INIT_API(huParamSetSize, hfunc, numbytes);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSetTexRef(HUfunction hfunc, int texunit, HUtexref hTexRef) {
    HU_INIT_API(huParamSetTexRef, hfunc, texunit, hTexRef);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSetf(HUfunction hfunc, int offset, float value) {
    HU_INIT_API(huParamSetf, hfunc, offset, value);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSeti(HUfunction hfunc, int offset, unsigned int value) {
    HU_INIT_API(huParamSeti, hfunc, offset, value);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huParamSetv(HUfunction hfunc, int offset, void *ptr, unsigned int numbytes) {
    HU_INIT_API(huParamSetv, hfunc, offset, ptr, numbytes);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

