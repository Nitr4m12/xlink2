#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

#include "xlink2/xlink2ValueReferenceType.h"

namespace xlink2 {
struct ResParam {
    u32 rawValue;

    u32 getValue() const { return rawValue & 0xffffff; }
    ValueReferenceType getRefType() const { return static_cast<ValueReferenceType>(rawValue >> 0x18); }
};

struct ResAssetParam {
    sead::BitFlag64 mask;
    ResParam rawValues[0];
};

struct ResTriggerOverwriteParam {
    sead::BitFlag32 mask;
    ResParam* rawValues{};


};
}  // namespace xlink2