#pragma once

#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2Handle.h"

namespace xlink2 {
struct ModelTriggerConnection {
    BoneMtx rootMtx;
    Handle handle;
    s16 entryValue;
    bool isActive;
};
static_assert(sizeof(ModelTriggerConnection) == 0x28, "xlink2::ModelTriggerConnection size mismatch");
}  // namespace xlink2