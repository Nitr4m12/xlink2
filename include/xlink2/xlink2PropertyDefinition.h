#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2PropertyType.h"

namespace xlink2 {
class PropertyDefinition {
public:
    virtual ~PropertyDefinition();

    PropertyType getType() const { return mType; }
    sead::FixedSafeString<64>* getPropertyName() { return &mPropertyName; }

protected:
    sead::FixedSafeString<64> mPropertyName;
    PropertyType mType;
    u64 _0;
    u64 _1;
};
static_assert(sizeof(PropertyDefinition) == 0x78, "Wrong size for 'xlink2::PropertyDefinition'");

}  // namespace xlink2
