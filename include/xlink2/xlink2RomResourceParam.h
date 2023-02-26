#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2CommonResourceParam.h"

namespace xlink2 {
struct RomResourceParam : CommonResourceParam {
    void* _0;
    u64 nameHash;
    u64 binPos;
    u8 _1;
    s32 _2;
};
}  // namespace xlink2