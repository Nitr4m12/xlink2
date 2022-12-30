#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResAlwaysTrigger {
    s32 guId;
    u32 assetCtb;
    u16 flag;
    s16 overwriteHash;
    u32 overwriteParamPos;
};
}