#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct CallTableParam {
    u32 keyNamePos;
    s16 assetId;
    u16 flag;
    s32 duration;
    s32 parentIndex;
    u16 enumIndex;
    u8 isSolved;
    u8 unknown;
    u32 keyNameHash;
    u32 paramStartPos;
    u32 conditionPos;
};

struct ResAssetCallTable {
    CallTableParam params[1];
};
}  // namespace xlink2