#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResAssetCallTable {
    u32 keyNamePos;
    s16 assetId;
    u8 flag;
    s32 duration;
    s32 parentIndex;
    u16 enumIndex;
    u8 isSolved;
    u8 unknown;
    u32 keyNameHash;
    u32 paramStartPos;
    u32 conditionPos;
};
}  // namespace xlink2