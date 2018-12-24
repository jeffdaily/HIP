#include "hu_internal.h"

HUresult huModuleGetFunction(HUfunction *hfunc, HUmodule hmod, const char *name) {
    HU_INIT_API(huModuleGetFunction, hfunc, hmod, name);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleGetGlobal(HUdeviceptr *dptr, size_t *bytes, HUmodule hmod, const char *name) {
    HU_INIT_API(huModuleGetGlobal, dptr, bytes, hmod, name);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleGetSurfRef(HUsurfref *pSurfRef, HUmodule hmod, const char *name) {
    HU_INIT_API(huModuleGetSurfRef, pSurfRef, hmod, name);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleGetTexRef(HUtexref *pTexRef, HUmodule hmod, const char *name) {
    HU_INIT_API(huModuleGetTexRef, pTexRef, hmod, name);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleLoad(HUmodule *module, const char *fname) {
    HU_INIT_API(huModuleLoad, module, fname);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleLoadData(HUmodule *module, const void *image) {
    HU_INIT_API(huModuleLoadData, module, image);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleLoadDataEx(HUmodule *module, const void *image, unsigned int numOptions, HUjit_option *options, void **optionValues) {
    HU_INIT_API(huModuleLoadDataEx, module, image, numOptions, options, optionValues);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleLoadFatBinary(HUmodule *module, const void *fatCubin) {
    HU_INIT_API(huModuleLoadFatBinary, module, fatCubin);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huModuleUnload(HUmodule hmod) {
    HU_INIT_API(huModuleUnload, hmod);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

