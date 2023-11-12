#pragma once

#include "xlink2/xlink2Event.h"

namespace xlink2 {
struct ModelTriggerConnection {
    void* _0;
    sead::PtrArray<Event>* mEventPtrs;
    Event* mEvent;
    u32 _2;
    void* _3;
};
}  // namespace xlink2