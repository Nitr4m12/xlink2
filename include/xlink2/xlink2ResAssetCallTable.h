#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResAssetCallTable {
    u32 keyNamePos;
    u16 assetId;
    u16 flag;
    s32 duration;
    u32 parentIndex;
    u16 enumIndex;
    u8 isSolved;
    u8 unknown;
    u32 keyNameHash;
    s32 paramStartPos;
    s32 conditionPos;
};
}