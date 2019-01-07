#include "hu_internal.h"

#if defined(__HCC__) && (__hcc_minor__ < 3)
enum queue_priority
{
    priority_high = 0,
    priority_normal = 0,
    priority_low = 0
};
#else
enum queue_priority
{
    priority_high = Kalmar::priority_high,
    priority_normal = Kalmar::priority_normal,
    priority_low = Kalmar::priority_low
};
#endif

HUresult huStreamAddCallback(HUstream hStream, HUstreamCallback callback, void *userData, unsigned int flags) {
    HU_INIT_API(huStreamAddCallback, hStream, callback, userData, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamAttachMemAsync(HUstream hStream, HUdeviceptr dptr, size_t length, unsigned int flags) {
    HU_INIT_API(huStreamAttachMemAsync, hStream, dptr, length, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamBatchMemOp(HUstream stream, unsigned int count, HUstreamBatchMemOpParams *paramArray, unsigned int flags) {
    HU_INIT_API(huStreamBatchMemOp, stream, count, paramArray, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

static inline HUresult ihuStreamCreate(HUstream *stream, unsigned int flags, int priority) {
    ihipCtx_t* ctx = ihipGetTlsDefaultCtx();

    HUresult e = HIP_SUCCESS;

    if (ctx) {
        if (HIP_FORCE_NULL_STREAM) {
            *stream = 0;
        } else {
            hc::accelerator acc = ctx->getWriteableDevice()->_acc;

            // TODO - se try-catch loop to detect memory exception?
            //
            // Note this is an execute_in_order queue, so all kernels submitted will atuomatically
            // wait for prev to complete: This matches CUDA stream behavior:

            {
                // Obtain mutex access to the device critical data, release by destructor
                LockedAccessor_CtxCrit_t ctxCrit(ctx->criticalData());

#if defined(__HCC__) && (__hcc_minor__ < 3)
                auto istream = new ihipStream_t(ctx, acc.create_view(), flags);
#else
                auto istream = new ihipStream_t(ctx, acc.create_view(Kalmar::execute_in_order, Kalmar::queuing_mode_automatic, (Kalmar::queue_priority)priority), flags);
#endif

                ctxCrit->addStream(istream);
                *stream = istream;
            }
        }

        tprintf(DB_SYNC, "ihuStreamCreate, %s\n", ToString(*stream).c_str());
    } else {
        e = HIP_ERROR_INVALID_DEVICE;
    }

    return e;
}

HUresult huStreamCreate(HUstream *phStream, unsigned int flags) {
    HU_INIT_API(huStreamCreate, phStream, flags);

    HUresult e = ihuStreamCreate(phStream, flags, priority_normal);

    return ihuLogStatus(e);
}

HUresult huStreamCreateWithPriority(HUstream *phStream, unsigned int flags, int priority) {
    HU_INIT_API(huStreamCreateWithPriority, phStream, flags, priority);

    HUresult e = ihuStreamCreate(phStream, flags, priority);

    return ihuLogStatus(e);
}

HUresult huStreamDestroy(HUstream hStream) {
    HU_INIT_API(huStreamDestroy, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamGetCtx(HUstream hStream, HUcontext *pctx) {
    HU_INIT_API(huStreamGetCtx, hStream, pctx);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamGetFlags(HUstream hStream, unsigned int *flags) {
    HU_INIT_API(huStreamGetFlags, hStream, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamGetPriority(HUstream hStream, int *priority) {
    HU_INIT_API(huStreamGetPriority, hStream, priority);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamQuery(HUstream hStream) {
    HU_INIT_API(huStreamQuery, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamSynchronize(HUstream hStream) {
    HU_INIT_API(huStreamSynchronize, hStream);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamWaitEvent(HUstream stream, HUevent event, unsigned int flags) {
    HU_INIT_API(huStreamWaitEvent, stream, event, flags);

    HUresult e = HIP_SUCCESS;

    auto ecd = event->locked_copyCrit();

    if (event == nullptr) {
        e = HIP_ERROR_INVALID_HANDLE;

    } else if ((ecd._state != hipEventStatusUnitialized) && (ecd._state != hipEventStatusCreated)) {
        if (HIP_SYNC_STREAM_WAIT || (HIP_SYNC_NULL_STREAM && (stream == 0))) {
            // conservative wait on host for the specified event to complete:
            // return _stream->locked_eventWaitComplete(this, waitMode);
            //
            ecd._stream->locked_eventWaitComplete(
                ecd.marker(), (event->_flags & hipEventBlockingSync) ? hc::hcWaitModeBlocked
                                                                     : hc::hcWaitModeActive);
        } else {
            stream = ihipSyncAndResolveStream(stream);
            // This will use create_blocking_marker to wait on the specified queue.
            stream->locked_streamWaitEvent(ecd);
        }

    }  // else event not recorded, return immediately and don't create marker.

    return ihuLogStatus(e);
}

HUresult huStreamWaitValue32(HUstream stream, HUdeviceptr addr, huuint32_t value, unsigned int flags) {
    HU_INIT_API(huStreamWaitValue32, stream, addr, value, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamWaitValue64(HUstream stream, HUdeviceptr addr, huuint64_t value, unsigned int flags) {
    HU_INIT_API(huStreamWaitValue64, stream, addr, value, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamWriteValue32(HUstream stream, HUdeviceptr addr, huuint32_t value, unsigned int flags) {
    HU_INIT_API(huStreamWriteValue32, stream, addr, value, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

HUresult huStreamWriteValue64(HUstream stream, HUdeviceptr addr, huuint64_t value, unsigned int flags) {
    HU_INIT_API(huStreamWriteValue64, stream, addr, value, flags);

    return ihuLogStatus(HIP_ERROR_NOT_SUPPORTED);;
}

