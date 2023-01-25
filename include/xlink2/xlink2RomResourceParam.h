#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2CommonResourceParam.h"

namespace xlink2 {
struct RomResourceParam : CommonResourceParam {
    u64 _0;
    u64 nameHash;
    u64 binPos;
    s32 _1;
};
}  // namespace xlink2