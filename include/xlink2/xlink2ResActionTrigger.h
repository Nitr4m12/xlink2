#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResActionTrigger {
    u32 guId;
    u32 assetCtbPos;
    u32 startFrame;
    u32 endFrame;
    u16 flag;
    u16 overwriteHash;
    s32 overwriteParamPos;
};
}  // namespace xlink2