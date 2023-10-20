#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2CommonResourceParam.h"

namespace xlink2 {
struct RomResourceParam : CommonResourceParam {
    void* _0;
    u32* nameHashTable;
    u32* offsetTable;
    u32 numUser;
    bool isInitialized;
};
static_assert(sizeof(RomResourceParam) == 0x98, "Wrong size for 'xlink2::RomResourceParam'");

}  // namespace xlink2