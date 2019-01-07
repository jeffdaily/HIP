#include "hu_internal.h"

HUresult huEventCreate(HUevent *event, unsigned int flags) {
    HU_INIT_API(huEventCreate, event, flags);

    HUresult e = HIP_SUCCESS;

    // TODO-IPC - support hipEventInterprocess.
    unsigned supportedFlags = hipEventDefault | hipEventBlockingSync | hipEventDisableTiming |
                              hipEventReleaseToDevice | hipEventReleaseToSystem;
    const unsigned releaseFlags = (hipEventReleaseToDevice | hipEventReleaseToSystem);

    const bool illegalFlags =
        (flags & ~supportedFlags) ||             // can't set any unsupported flags.
        (flags & releaseFlags) == releaseFlags;  // can't set both release flags

    if (!illegalFlags) {
        *event = new ihipEvent_t(flags);
    } else {
        e = HIP_ERROR_INVALID_VALUE;
    }

    return ihuLogStatus(e);
}

HUresult huEventDestroy(HUevent event) {
    HU_INIT_API(huEventDestroy, event);

    if (event) {
        delete event;
        return ihuLogStatus(HIP_SUCCESS);
    } else {
        return ihuLogStatus(HIP_ERROR_INVALID_HANDLE);
    }
}

HUresult huEventElapsedTime(float *ms, HUevent start, HUevent stop) {
    HU_INIT_API(huEventElapsedTime, ms, start, stop);

    HUresult status = HIP_SUCCESS;

    *ms = 0.0f;

    if ((start == nullptr) || (stop == nullptr)) {
        status = HIP_ERROR_INVALID_HANDLE;
    } else {
        auto startEcd = start->locked_copyCrit();
        auto stopEcd = stop->locked_copyCrit();

        if ((start->_flags & hipEventDisableTiming) ||
            (startEcd._state == hipEventStatusUnitialized) ||
            (startEcd._state == hipEventStatusCreated) || (stop->_flags & hipEventDisableTiming) ||
            (stopEcd._state == hipEventStatusUnitialized) ||
            (stopEcd._state == hipEventStatusCreated)) {
            // Both events must be at least recorded else return hipErrorInvalidResourceHandle

            status = HIP_ERROR_INVALID_HANDLE;

        } else {
            // Refresh status, if still recording...

            auto startStatus = start->refreshEventStatus();  // pair < state, timestamp >
            auto stopStatus = stop->refreshEventStatus();    // pair < state, timestamp >

            if ((startStatus.first == hipEventStatusComplete) &&
                (stopStatus.first == hipEventStatusComplete)) {
                // Common case, we have good information for both events.  'second" is the
                // timestamp:
                int64_t tickDiff = (stopStatus.second - startStatus.second);

                uint64_t freqHz;
                hsa_system_get_info(HSA_SYSTEM_INFO_TIMESTAMP_FREQUENCY, &freqHz);
                if (freqHz) {
                    *ms = ((double)(tickDiff) / (double)(freqHz)) * 1000.0f;
                    status = HIP_SUCCESS;
                } else {
                    *ms = 0.0f;
                    status = HIP_ERROR_INVALID_VALUE;
                }


            } else if ((startStatus.first == hipEventStatusRecording) ||
                       (stopStatus.first == hipEventStatusRecording)) {
                status = HIP_ERROR_NOT_READY;
            } else {
                assert(0);
            }
        }
    }

    return ihuLogStatus(status);
}

HUresult huEventQuery(HUevent event) {
    HU_INIT_API(huEventQuery, event);

    if (!(event->_flags & hipEventReleaseToSystem)) {
        tprintf(DB_WARN,
                "hipEventQuery on event without system-scope fence ; consider creating with "
                "hipEventReleaseToSystem\n");
    }

    auto ecd = event->locked_copyCrit();

    if ((ecd._state == hipEventStatusRecording) && !ecd._stream->locked_eventIsReady(event)) {
        return ihuLogStatus(HIP_ERROR_NOT_READY);
    } else {
        return ihuLogStatus(HIP_SUCCESS);
    }
}

HUresult huEventRecord(HUevent event, HUstream stream) {
    HU_INIT_API(huEventRecord, event, stream);

    auto ecd = event->locked_copyCrit();

    if (event && ecd._state != hipEventStatusUnitialized) {
        stream = ihipSyncAndResolveStream(stream);

        if (HIP_SYNC_NULL_STREAM && stream->isDefaultStream()) {
            // TODO-HIP_SYNC_NULL_STREAM : can remove this code when HIP_SYNC_NULL_STREAM = 0
            //
            // If default stream , then wait on all queues.
            ihipCtx_t* ctx = ihipGetTlsDefaultCtx();
            ctx->locked_syncDefaultStream(true, true);

            {
                LockedAccessor_EventCrit_t eCrit(event->criticalData());
                eCrit->_eventData.marker(hc::completion_future());  // reset event
                eCrit->_eventData._stream = stream;
                eCrit->_eventData._timestamp = hc::get_system_ticks();
                eCrit->_eventData._state = hipEventStatusComplete;
            }
            return ihuLogStatus(HIP_SUCCESS);
        } else {
            // Record the event in the stream:
            // Keep a copy outside the critical section so we lock stream first, then event - to
            // avoid deadlock
            hc::completion_future cf = stream->locked_recordEvent(event);

            {
                LockedAccessor_EventCrit_t eCrit(event->criticalData());
                eCrit->_eventData.marker(cf);
                eCrit->_eventData._stream = stream;
                eCrit->_eventData._timestamp = 0;
                eCrit->_eventData._state = hipEventStatusRecording;
            }

            return ihuLogStatus(HIP_SUCCESS);
        }
    } else {
        return ihuLogStatus(HIP_ERROR_INVALID_HANDLE);
    }
}

HUresult huEventSynchronize(HUevent event) {
    HU_INIT_API(huEventSynchronize, event);

    if (!(event->_flags & hipEventReleaseToSystem)) {
        tprintf(DB_WARN,
                "hipEventSynchronize on event without system-scope fence ; consider creating with "
                "hipEventReleaseToSystem\n");
    }
    auto ecd = event->locked_copyCrit();

    if (event) {
        if (ecd._state == hipEventStatusUnitialized) {
            return ihuLogStatus(HIP_ERROR_INVALID_HANDLE);
        } else if (ecd._state == hipEventStatusCreated) {
            // Created but not actually recorded on any device:
            return ihuLogStatus(HIP_SUCCESS);
        } else if (HIP_SYNC_NULL_STREAM && (ecd._stream->isDefaultStream())) {
            auto* ctx = ihipGetTlsDefaultCtx();
            // TODO-HIP_SYNC_NULL_STREAM - can remove this code
            ctx->locked_syncDefaultStream(true, true);
            return ihuLogStatus(HIP_SUCCESS);
        } else {
            ecd._stream->locked_eventWaitComplete(
                ecd.marker(), (event->_flags & hipEventBlockingSync) ? hc::hcWaitModeBlocked
                                                                     : hc::hcWaitModeActive);

            return ihuLogStatus(HIP_SUCCESS);
        }
    } else {
        return ihuLogStatus(HIP_ERROR_INVALID_HANDLE);
    }
}

