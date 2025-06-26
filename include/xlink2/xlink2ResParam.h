#pragma once

#include <basis/seadTypes.h>
#include <xlink2/xlink2ValueReferenceType.h>

namespace xlink2 {
struct ResParam {
    u32 rawValue;

    u32 getValue() const { return rawValue & 0xffffff; }
    ValueReferenceType getRefType() const { return static_cast<ValueReferenceType>(rawValue >> 0x18); }
};
}  // namespace xlink2