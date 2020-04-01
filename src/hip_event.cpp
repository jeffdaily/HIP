/*
Copyright (c) 2015 - present Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "hip/hip_runtime.h"
#include "hip_hcc_internal.h"
#include "trace_helper.h"

#include <errno.h> // errno, ENOENT
#include <fcntl.h> // O_RDWR, O_CREATE
#include <sys/mman.h> // shm_open, shm_unlink, mmap, munmap, PROT_READ, PROT_WRITE, MAP_SHARED, MAP_FAILED
#include <unistd.h> // ftruncate, close

namespace {

    inline
    const char* hsa_to_string(hsa_status_t err) noexcept
    {
        const char* r{};

        if (hsa_status_string(err, &r) == HSA_STATUS_SUCCESS) return r;

        return "Unknown.";
    }

    template<std::size_t m, std::size_t n>
    inline
    void throwing_result_check(hsa_status_t res, const char (&file)[m],
                               const char (&function)[n], int line) {
        if (res == HSA_STATUS_SUCCESS) return;

        throw std::runtime_error{"Failed in file " + (file +
                                 (", in function \"" + (function +
                                 ("\", on line " + std::to_string(line))))) +
                                 ", with error: " + hsa_to_string(res)};
    }

    template<std::size_t m, std::size_t n>
    inline
    void throwing_retval_check(int good, int retval, const char (&file)[m],
                                const char (&function)[n], int line) {
        if (retval == good) return;

        throw std::runtime_error{"Failed in file " + (file +
                                 (", in function \"" + (function +
                                 ("\", on line " + std::to_string(line))))) +
                                 ", with error: " + strerror(retval)};
    }

    template<std::size_t m, std::size_t n>
    inline
    void throwing_errno_check(bool bad, const char (&file)[m],
                              const char (&function)[n], int line) {
        if (!bad) return;

        throw std::runtime_error{"Failed in file " + (file +
                                 (", in function \"" + (function +
                                 ("\", on line " + std::to_string(line))))) +
                                 ", with error: " + strerror(errno)};
    }

} // Unnamed namespace.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Events
//---


ihipEvent_t::ihipEvent_t(unsigned flags) : _criticalData(this) { _flags = flags; };


// Attach to an existing completion future:
void ihipEvent_t::attachToCompletionFuture(const hc::completion_future* cf, hipStream_t stream,
                                           ihipEventType_t eventType) {
    LockedAccessor_EventCrit_t crit(_criticalData);
    crit->_eventData.marker(*cf);
    crit->_eventData._type = eventType;
    crit->_eventData._stream = stream;
    crit->_eventData._state = hipEventStatusRecording;
}


static void createIpcEventShmemIfNeeded(ihipEventData_t &ecd) {
    if (!ecd._ipc_name.empty()) return;

    // create random shmem name
    char name_template[] = "/tmp/eventXXXXXX";
    int temp_fd = mkstemp(name_template);
    throwing_errno_check(-1 == temp_fd, __FILE__, __func__, __LINE__);

    // copy shmem name into event data, reformat to use a single slash
    ecd._ipc_name = name_template;
    ecd._ipc_name.replace(0, 5, "/hip_");

    // open shmem
    ecd._ipc_fd = shm_open(ecd._ipc_name.c_str(), O_RDWR | O_CREAT, 0777);
    throwing_errno_check(ecd._ipc_fd < 0, __FILE__, __func__, __LINE__);

    // size it
    throwing_retval_check(0, ftruncate(ecd._ipc_fd, sizeof(ihipIpcEventShmem_t)), __FILE__, __func__, __LINE__);

    // mmap it
    ecd._ipc_shmem = (ihipIpcEventShmem_t*)mmap(0, sizeof(ihipIpcEventShmem_t), PROT_READ | PROT_WRITE, MAP_SHARED, ecd._ipc_fd, 0);
    throwing_errno_check(NULL == ecd._ipc_shmem, __FILE__, __func__, __LINE__);

    // initialize mutex
    pthread_mutexattr_t attr;
    throwing_retval_check(0, pthread_mutexattr_init(&attr), __FILE__, __func__, __LINE__);
    throwing_retval_check(0, pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED), __FILE__, __func__, __LINE__);
    throwing_retval_check(0, pthread_mutex_init(&ecd._ipc_shmem->mutex, &attr), __FILE__, __func__, __LINE__);

    // initialize shared state
    ecd._ipc_shmem->status = ecd._state;
    ecd._ipc_shmem->signal_id = 0;

    // remove temp file
    throwing_errno_check(-1 == close(temp_fd), __FILE__, __func__, __LINE__);
    throwing_errno_check(-1 == unlink(name_template), __FILE__, __func__, __LINE__);
}

void ihipEvent_t::refreshIpcEvent(ihipEventData_t &ecd) {
    if (ecd._ipc_shmem == NULL) return;

    PthreadMutexRAII guard(&ecd._ipc_shmem->mutex);

    if (ecd._ipc_last_signal_id != ecd._ipc_shmem->signal_id) {
        // new signal was recorded, refresh local handle
        if (ecd._ipc_signal.handle != 0) {
            // free previous handle
            throwing_result_check(
                hsa_signal_destroy(ecd._ipc_signal),
                __FILE__, __func__, __LINE__);
        }
        throwing_result_check(
            hsa_amd_ipc_signal_attach(&ecd._ipc_shmem->ipc_handle, &(ecd._ipc_signal)),
            __FILE__, __func__, __LINE__);
        ecd._ipc_last_signal_id = ecd._ipc_shmem->signal_id;
    }
    ecd._state = ecd._ipc_shmem->status;
}


static std::pair<hipEventStatus_t, uint64_t> refreshEventStatus(ihipEventData_t &ecd) {
    if (ecd._state == hipEventStatusRecording && ecd.marker().is_ready()) {
        if ((ecd._type == hipEventTypeIndependent) ||
            (ecd._type == hipEventTypeStopCommand)) {
            ecd._timestamp = ecd.marker().get_end_tick();
        } else if (ecd._type == hipEventTypeStartCommand) {
            ecd._timestamp = ecd.marker().get_begin_tick();
        } else {
            ecd._timestamp = 0;
            assert(0);  // TODO - move to debug assert
        }

        ecd._state = hipEventStatusComplete;

        return std::pair<hipEventStatus_t, uint64_t>(ecd._state,
                                                     ecd._timestamp);
    }

    // Not complete path here:
    return std::pair<hipEventStatus_t, uint64_t>(ecd._state, ecd._timestamp);
}


hipError_t ihipEventCreate(hipEvent_t* event, unsigned flags) {
    hipError_t e = hipSuccess;

    unsigned supportedFlags = hipEventDefault | hipEventBlockingSync | hipEventDisableTiming |
                              hipEventReleaseToDevice | hipEventReleaseToSystem |
                              hipEventInterprocess;
    const unsigned releaseFlags = (hipEventReleaseToDevice | hipEventReleaseToSystem);

    const bool illegalFlags =
        (flags & ~supportedFlags) ||             // can't set any unsupported flags.
        (flags & releaseFlags) == releaseFlags;  // can't set both release flags

    if (event && !illegalFlags) {
        *event = new ihipEvent_t(flags);
    } else {
        e = hipErrorInvalidValue;
    }

    return e;
}

hipError_t hipEventCreateWithFlags(hipEvent_t* event, unsigned flags) {
    HIP_INIT_API(hipEventCreateWithFlags, event, flags);

    return ihipLogStatus(ihipEventCreate(event, flags));
}

hipError_t hipEventCreate(hipEvent_t* event) {
    HIP_INIT_API(hipEventCreate, event);

    return ihipLogStatus(ihipEventCreate(event, 0));
}

hipError_t hipEventRecord(hipEvent_t event, hipStream_t stream) {
    HIP_INIT_SPECIAL_API(hipEventRecord, TRACE_SYNC, event, stream);
    if (!event) return ihipLogStatus(hipErrorInvalidHandle);
    stream = ihipSyncAndResolveStream(stream);
    LockedAccessor_EventCrit_t eCrit(event->criticalData());
    if (eCrit->_eventData._state == hipEventStatusUnitialized) return ihipLogStatus(hipErrorInvalidHandle);
    if (HIP_SYNC_NULL_STREAM && stream->isDefaultStream()) {
        // TODO-HIP_SYNC_NULL_STREAM : can remove this code when HIP_SYNC_NULL_STREAM = 0
        // If default stream , then wait on all queues.
        ihipCtx_t* ctx = ihipGetTlsDefaultCtx();
        ctx->locked_syncDefaultStream(true, true);
        eCrit->_eventData.marker(hc::completion_future());  // reset event
        eCrit->_eventData._stream = stream;
        eCrit->_eventData._timestamp = hc::get_system_ticks();
        eCrit->_eventData._state = hipEventStatusComplete;
    }
    else {
        // Record the event in the stream:
        eCrit->_eventData.marker(stream->locked_recordEvent(event));
        eCrit->_eventData._stream = stream;
        eCrit->_eventData._timestamp = 0;
        eCrit->_eventData._state = hipEventStatusRecording;
        if (event->_flags & hipEventInterprocess) {
            createIpcEventShmemIfNeeded(eCrit->_eventData);
            PthreadMutexRAII guard(&eCrit->_eventData._ipc_shmem->mutex);
            // remove existing signal, if any
            if (eCrit->_eventData._ipc_signal.handle != 0) {
                throwing_result_check(
                    hsa_signal_destroy(eCrit->_eventData._ipc_signal),
                    __FILE__, __func__, __LINE__);
            }
            // create new HSA IPC signal, initial value 1
            throwing_result_check(
                hsa_amd_signal_create(1, 0, NULL, HSA_AMD_SIGNAL_IPC, &eCrit->_eventData._ipc_signal),
                __FILE__, __func__, __LINE__);
            // Create HSA IPC handle
            throwing_result_check(
                hsa_amd_ipc_signal_create(eCrit->_eventData._ipc_signal, &eCrit->_eventData._ipc_shmem->ipc_handle),
                __FILE__, __func__, __LINE__);
            // update shared state
            eCrit->_eventData._ipc_shmem->status = hipEventStatusRecording;
            eCrit->_eventData._ipc_shmem->signal_id += 1;
            // update local signal id to match
            eCrit->_eventData._ipc_last_signal_id = eCrit->_eventData._ipc_shmem->signal_id;
            // forward signal state from local signal to IPC signal via host callback
            // create callback that can be passed to hsa_amd_signal_async_handler
            // this function decrements the IPC signal by 1 to indicate completion
            auto signal{eCrit->_eventData._ipc_signal};
            auto t{new std::function<void()>{[=]() {
                hsa_signal_subtract_relaxed(signal, 1);
            }}};
            // register above callback with HSA runtime to be called when local signal
            // is decremented from 1 to 0 by CP
            auto local_signal = *reinterpret_cast<hsa_signal_t*>(eCrit->_eventData.marker().get_native_handle());
            hsa_amd_signal_async_handler(local_signal, HSA_SIGNAL_CONDITION_LT, 1,
                [](hsa_signal_value_t x, void* p) {
                    (*static_cast<decltype(t)>(p))();
                    delete static_cast<decltype(t)>(p);
                    return false;
                }, t);
        }
    }
    return ihipLogStatus(hipSuccess);
}


hipError_t hipEventDestroy(hipEvent_t event) {
    HIP_INIT_API(hipEventDestroy, event);

    if (event) {
        LockedAccessor_EventCrit_t crit(event->criticalData());
        auto &ecd{crit->_eventData};
        if (ecd._ipc_signal.handle) {
            throwing_result_check(
                hsa_signal_destroy(ecd._ipc_signal),
                __FILE__, __func__, __LINE__);
        }
        if (ecd._ipc_shmem) {
            throwing_errno_check(
                -1 == munmap(ecd._ipc_shmem, sizeof(ihipIpcEventShmem_t)),
                __FILE__, __func__, __LINE__);
        }
        if (ecd._ipc_fd) {
            throwing_errno_check(-1 == close(ecd._ipc_fd), __FILE__, __func__, __LINE__);
        }
        delete event;
        return ihipLogStatus(hipSuccess);
    } else {
        return ihipLogStatus(hipErrorInvalidHandle);
    }
}

hipError_t hipEventSynchronize(hipEvent_t event) {
    HIP_INIT_SPECIAL_API(hipEventSynchronize, TRACE_SYNC, event);

    if (event){
        if (!(event->_flags & hipEventReleaseToSystem)) {
            tprintf(DB_WARN,
                "hipEventSynchronize on event without system-scope fence ; consider creating with "
                "hipEventReleaseToSystem\n");
        }
        auto ecd = event->locked_copyCrit();

        // this event is either from an ipc handle, or the owner of a local ipc event
        if (ecd._ipc_signal.handle) {
            auto waitMode = (event->_flags & hipEventBlockingSync) ? HSA_WAIT_STATE_BLOCKED
                                                                   : HSA_WAIT_STATE_ACTIVE;
            hsa_signal_wait_scacquire(ecd._ipc_signal, HSA_SIGNAL_CONDITION_LT, 1, UINT64_MAX, waitMode);
            return ihipLogStatus(hipSuccess);
        }

        if (ecd._state == hipEventStatusUnitialized) {
            return ihipLogStatus(hipErrorInvalidHandle);
        } else if (ecd._state == hipEventStatusCreated) {
            // Created but not actually recorded on any device:
            return ihipLogStatus(hipSuccess);
        } else if (HIP_SYNC_NULL_STREAM && (ecd._stream->isDefaultStream())) {
            auto* ctx = ihipGetTlsDefaultCtx();
            // TODO-HIP_SYNC_NULL_STREAM - can remove this code
            ctx->locked_syncDefaultStream(true, true);
            return ihipLogStatus(hipSuccess);
        } else {
            ecd.marker().wait((event->_flags & hipEventBlockingSync) ? hc::hcWaitModeBlocked
                                                                     : hc::hcWaitModeActive);
            return ihipLogStatus(hipSuccess);
        }
    } else {
        return ihipLogStatus(hipErrorInvalidHandle);
    }
}

hipError_t hipEventElapsedTime(float* ms, hipEvent_t start, hipEvent_t stop) {
    HIP_INIT_API(hipEventElapsedTime, ms, start, stop);

    if (ms == nullptr) return ihipLogStatus(hipErrorInvalidValue);
    if ((start == nullptr) || (stop == nullptr)) return ihipLogStatus(hipErrorInvalidHandle);

    *ms = 0.0f;
    auto startEcd = start->locked_copyCrit();
    auto stopEcd = stop->locked_copyCrit();

    if ((start->_flags & hipEventDisableTiming) ||
        (startEcd._state == hipEventStatusUnitialized) ||
        (startEcd._state == hipEventStatusCreated) ||
        (stop->_flags & hipEventDisableTiming) ||
        (stopEcd._state == hipEventStatusUnitialized) ||
        (stopEcd._state == hipEventStatusCreated)) {
        // Both events must be at least recorded else return hipErrorInvalidHandle
        return ihipLogStatus(hipErrorInvalidHandle);
    }

    // Refresh status, if still recording...

    auto startStatus = refreshEventStatus(startEcd);  // pair < state, timestamp >
    auto stopStatus = refreshEventStatus(stopEcd);    // pair < state, timestamp >

    if ((startStatus.first == hipEventStatusComplete) &&
        (stopStatus.first == hipEventStatusComplete)) {
        // Common case, we have good information for both events.  'second' is the timestamp:
        int64_t tickDiff = (stopStatus.second - startStatus.second);
        uint64_t freqHz;
        hsa_system_get_info(HSA_SYSTEM_INFO_TIMESTAMP_FREQUENCY, &freqHz);
        if (freqHz) {
            *ms = ((double)(tickDiff) / (double)(freqHz)) * 1000.0f;
            return ihipLogStatus(hipSuccess);
        } else {
            *ms = 0.0f;
            return ihipLogStatus(hipErrorInvalidValue);
        }
    } else if ((startStatus.first == hipEventStatusRecording) ||
               (stopStatus.first == hipEventStatusRecording)) {
        return ihipLogStatus(hipErrorNotReady);
    } else {
        assert(0); // TODO should we return hipErrorUnknown ?
    }

    return ihipLogStatus(hipSuccess);
}

hipError_t hipEventQuery(hipEvent_t event) {
    HIP_INIT_SPECIAL_API(hipEventQuery, TRACE_QUERY, event);
 
    if (!event) return ihipLogStatus(hipErrorInvalidHandle);

    if (!(event->_flags & hipEventReleaseToSystem)) {
        tprintf(DB_WARN,
                "hipEventQuery on event without system-scope fence ; consider creating with "
                "hipEventReleaseToSystem\n");
    }

    auto ecd = event->locked_copyCrit();

    // this event is either from an ipc handle, or the owner of a local ipc event
    if (event->_flags & hipEventInterprocess) {
        if (ecd._ipc_signal.handle) {
            if (hsa_signal_load_scacquire(ecd._ipc_signal) == 0) {
                return ihipLogStatus(hipSuccess);
            }
            else {
                return ihipLogStatus(hipErrorNotReady);
            }
        }
    }
    // normal event
    else {
        if (ecd._state == hipEventStatusRecording && !ecd.marker().is_ready()) {
            return ihipLogStatus(hipErrorNotReady);
        }
    }

    return ihipLogStatus(hipSuccess);
}

hipError_t hipIpcGetEventHandle(hipIpcEventHandle_t* handle, hipEvent_t event)
{
    HIP_INIT_API(hipIpcGetEventHandle, handle, event);

#if USE_IPC
    if (!handle) return ihipLogStatus(hipErrorInvalidHandle);
    if (!event) return ihipLogStatus(hipErrorInvalidHandle);
    if (!(event->_flags & hipEventInterprocess)) return ihipLogStatus(hipErrorInvalidHandle);
    if (!(event->_flags & hipEventDisableTiming)) return ihipLogStatus(hipErrorInvalidHandle);

    LockedAccessor_EventCrit_t crit(event->criticalData());

    auto &ecd{crit->_eventData};
    createIpcEventShmemIfNeeded(ecd);
    // copy name into handle
    ihipIpcEventHandle_t* iHandle = (ihipIpcEventHandle_t*)handle;
    memset(iHandle->shmem_name, 0, HIP_IPC_HANDLE_SIZE);
    ecd._ipc_name.copy(iHandle->shmem_name, std::string::npos);

    return ihipLogStatus(hipSuccess);
#else
    return ihipLogStatus(hipErrorNotSupported);
#endif
}

hipError_t hipIpcOpenEventHandle(hipEvent_t* event, hipIpcEventHandle_t handle)
{
    HIP_INIT_API(hipIpcOpenEventHandle, event, &handle);

#if USE_IPC
    if (!event) return ihipLogStatus(hipErrorInvalidHandle);

    // create a new event with timing disabled, per spec
    auto hip_status = ihipEventCreate(event, hipEventDisableTiming | hipEventInterprocess);
    if (hip_status != hipSuccess) return ihipLogStatus(hip_status);

    LockedAccessor_EventCrit_t crit((*event)->criticalData());
    auto &ecd{crit->_eventData};
    ihipIpcEventHandle_t* iHandle = (ihipIpcEventHandle_t*)&handle;
    ecd._ipc_name = iHandle->shmem_name;
    // open shmem
    ecd._ipc_fd = shm_open(ecd._ipc_name.c_str(), O_RDWR, 0777);
    throwing_errno_check(ecd._ipc_fd < 0, __FILE__, __func__, __LINE__);
    // mmap it
    ecd._ipc_shmem = (ihipIpcEventShmem_t*)mmap(0, sizeof(ihipIpcEventShmem_t), PROT_READ | PROT_WRITE, MAP_SHARED, ecd._ipc_fd, 0);
    throwing_errno_check(NULL == ecd._ipc_shmem, __FILE__, __func__, __LINE__);

    return ihipLogStatus(hipSuccess);
#else
    return ihipLogStatus(hipErrorNotSupported);
#endif
}
