#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2PropertyType.h"

namespace xlink2 {
class PropertyDefinition {
public:
    virtual ~PropertyDefinition();

    PropertyType getType() const { return mType; }

protected:
    void* _0;
    sead::FixedSafeString<64>* mUserName;
    u32 _2;
    u32 _3;
    u32 mUserNamePos;
    u8 unknown[54];
    PropertyType mType;
    u8 _1;
    u64 _4;
};
static_assert(sizeof(PropertyDefinition) == 0x70, "Wrong size for 'xlink2::PropertyDefinition'");

}  // namespace xlink2