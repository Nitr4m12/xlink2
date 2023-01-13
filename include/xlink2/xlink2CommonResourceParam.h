#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ResAssetParamTable.h"
namespace xlink2 {
struct CommonResourceParam {
    u32 mask;
    // 0x4
    u32 resAssetParamTablePos;
    // 0x28
    ResAssetParamTable* resAssetParamTable;
};
}  // namespace xlink2