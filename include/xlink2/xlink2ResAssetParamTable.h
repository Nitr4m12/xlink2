#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

namespace xlink2 {
struct ResAssetParamTable {
    sead::BitFlag32 mask;
    u32 rawValues[1];
};
}