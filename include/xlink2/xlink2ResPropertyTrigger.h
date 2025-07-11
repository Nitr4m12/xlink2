#pragma once

#include "basis/seadTypes.h"
#include "prim/seadBitFlag.h"

namespace xlink2 {
struct ResPropertyTrigger {
    s32 guId;
    s32 assetCtbPos;
    s32 condition;
    sead::BitFlag16 flag;
    s16 overwriteHash;
    s32 overwriteParamPos;
};
}  // namespace xlink2