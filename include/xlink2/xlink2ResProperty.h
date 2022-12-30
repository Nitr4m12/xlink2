#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResProperty {
    u32 watchPropertyNamePos;
    s32 isGlobal;
    s32 triggerStartIdx;
    s32 triggerEndIdx;
};
}  // namespace xlink2