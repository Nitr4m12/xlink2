#pragma once

#include "xlink2/xlink2Event.h"

namespace xlink2 {
struct ModelTriggerConnection {
    void* _0;
    sead::PtrArray<Event>* mEventPtrs;
    Event* mEvent;
    u32 _2;
    u8 padding[6];
    bool isActive;
};
static_assert(sizeof(ModelTriggerConnection) == 0x28, "'xlink2::ModelTriggerConnection' is not of the correct size");
}  // namespace xlink2