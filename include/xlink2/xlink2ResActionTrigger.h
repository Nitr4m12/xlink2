#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResActionTrigger {
    s32 guId;
    u32 assetCtbPos;
    s32 startFrame;
    s32 endFrame;
    u16 flag;
    s16 overwriteHash;
    u32 overwriteParamPos;
};
}  // namespace xlink2