#include "hu_internal.h"

HUresult huLinkAddData(HUlinkState state, HUjitInputType type, void *data, size_t size, const char *name, unsigned int numOptions, HUjit_option *options, void **optionValues) {
    HU_INIT_API(huLinkAddData, state, type, data, size, name, numOptions, options, optionValues);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLinkAddFile(HUlinkState state, HUjitInputType type, const char *path, unsigned int numOptions, HUjit_option *options, void **optionValues) {
    HU_INIT_API(huLinkAddFile, state, type, path, numOptions, options, optionValues);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLinkComplete(HUlinkState state, void **cubinOut, size_t *sizeOut) {
    HU_INIT_API(huLinkComplete, state, cubinOut, sizeOut);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLinkCreate(unsigned int numOptions, HUjit_option *options, void **optionValues, HUlinkState *stateOut) {
    HU_INIT_API(huLinkCreate, numOptions, options, optionValues, stateOut);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huLinkDestroy(HUlinkState state) {
    HU_INIT_API(huLinkDestroy, state);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

