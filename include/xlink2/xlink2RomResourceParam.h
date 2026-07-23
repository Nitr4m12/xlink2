#pragma once

#include "xlink2/xlink2CommonResourceParam.h"

namespace xlink2 {
struct RomResourceParam : CommonResourceParam {
    ResourceHeader* pResHeader {nullptr};
    u32* nameHashTable {nullptr};
    u32* offsetTable {nullptr};
    u32 numUser {0};
    bool isInitialized {false};

    void reset() {
        CommonResourceParam::reset();
        pResHeader = nullptr;
        nameHashTable = nullptr;
        offsetTable = nullptr;
        numUser = 0;
        isInitialized = false;
    }
};
static_assert(sizeof(RomResourceParam) == 0x98, "xlink2::RomResourceParam size mismatch");

}  // namespace xlink2