#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResAction {
    u32 name;
    u16 triggerStartIdx;
    u16 triggerEndIdx;
    u8 padding[4];
};
}  // namespace xlink2