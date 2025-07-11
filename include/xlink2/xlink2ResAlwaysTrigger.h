#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResAlwaysTrigger {
    s32 guId;
    s32 assetCtbPos;
    u16 flag;
    s16 overwriteHash;
    s32 overwriteParamPos;
};
}  // namespace xlink2