#pragma once

#include <container/seadBuffer.h>

#include "xlink2/xlink2Condition.h"
#include "xlink2/xlink2ResAction.h"
#include "xlink2/xlink2UserBinParam.h"

namespace xlink2 {
struct UserResourceParam : public UserBinParam {
    sead::Buffer<ResCondition> conditionTableBuffer;
    sead::Buffer<CallTableParam> callTableBuffer;
    sead::Buffer<ResAction> actionBuffer;
    void* _1;
    void* _2;
    bool isSetup;
};
static_assert(sizeof(UserResourceParam) == 0xb0, "Wrong size for 'xlink2::UserResourceParam'");

}  // namespace xlink2