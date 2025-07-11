#pragma once

#include <container/seadBuffer.h>

#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2Condition.h"
#include "xlink2/xlink2ResAction.h"
#include "xlink2/xlink2UserBinParam.h"

namespace xlink2 {
struct UserResourceParam {
    CommonResourceParam* pCommonResourceParam;
    UserBinParam userBinParam;
    sead::Buffer<SwitchCondition> conditionTableBuffer;
    sead::Buffer<ResAssetCallTable> callTableBuffer;
    sead::Buffer<ResAction> actionBuffer;
    sead::BitFlag64 bitFlag;
    void* _2;
    bool isSetup;
};
static_assert(sizeof(UserResourceParam) == 0xb0, "Wrong size for 'xlink2::UserResourceParam'");

}  // namespace xlink2