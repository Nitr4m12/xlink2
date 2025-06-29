#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

#include "xlink2/xlink2ResParam.h"

namespace xlink2 {
struct ResAssetParamTable {
    sead::BitFlag32 mask;
    ResParam* rawValues;
};
}