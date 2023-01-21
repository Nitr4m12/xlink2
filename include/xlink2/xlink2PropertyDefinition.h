#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2PropertyType.h"

namespace xlink2 {
class PropertyDefinition {
public:
    virtual ~PropertyDefinition();

protected:
    void* _0;
    sead::FixedSafeString<64>* mUserName;
    u8 unknown[70];
    PropertyType mType;
    u8 _1;
};
}  // namespace xlink2