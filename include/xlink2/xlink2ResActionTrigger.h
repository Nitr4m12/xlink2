#pragma once

#include "basis/seadTypes.h"
#include "prim/seadBitFlag.h"

namespace xlink2 {
struct ResActionTrigger {
    s32 guId;
    u32 assetCtbPos;
    s32 startFrame;
    s32 endFrame;
    sead::BitFlag16 flag;
    s16 overwriteHash;
    u32 overwriteParamPos;
};
}  // namespace xlink2