#pragma once

#include "container/seadBuffer.h"
#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2ResourceAccessor.h"

namespace xlink2 {
class ResourceAccessor;
struct UserResourceParam : public CommonResourceParam {
    sead::Buffer<ResAssetCallTable> resCallTableBuffer;
    sead::Buffer<bool> actionTriggerBoolBuffer;
    u64 propertyAssignedBitfield;
    ResourceAccessor* resourceAccessor;
    bool isSetup;
};
static_assert(sizeof(UserResourceParam) == 0xb0, "Wrong size for 'xlink2::UserResourceParam'");

}  // namespace xlink2