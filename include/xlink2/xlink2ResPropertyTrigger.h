#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResPropertyTrigger {
    s32 guId;
    u32 assetCtbPos;
    u32 condition;
    u16 flag;
    s16 overwriteHash;
    u32 overwriteParamPos;
};
}  // namespace xlink2