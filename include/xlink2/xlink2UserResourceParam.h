#pragma once

#include "container/seadBuffer.h"
#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2ResourceAccessor.h"

namespace xlink2 {
class ResourceAccessor;
struct UserResourceParam : public CommonResourceParam {
    // size=0xb0
    sead::Buffer<ResAssetCallTable> resCallTableBuffer;
    sead::Buffer<bool> actionTriggerBoolBuffer;
    u64 propertyAssignedBitfield;
    ResourceAccessor* resourceAccessor;
    bool isSetup;
};
}  // namespace xlink2