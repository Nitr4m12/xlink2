#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResAlwaysTrigger {
    u32 guId;
    u32 assetCtb;
    u16 flag;
    u16 overwriteHash;
    u32 overwriteParamPos;
    u8 padding[16];
};
}