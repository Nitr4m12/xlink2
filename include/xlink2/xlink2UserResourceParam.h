#pragma once

#include <container/seadBuffer.h>

#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2UserBinParam.h"

namespace xlink2 {
struct CallTableParam {
    s16 assetId;
    sead::BitFlag8 bitFlag;
    s8 _3;
};

struct UserResourceParam {
    const CommonResourceParam* pCommonResourceParam {};
    UserBinParam userBinParam {};
    sead::Buffer<s8> localPropertyIdxBuffer;
    sead::Buffer<CallTableParam> callTableParamBuffer;
    sead::Buffer<bool> actionNeedToCalcBuffer;
    sead::BitFlag64 bitFlag;
    ResourceAccessor* accessor {nullptr};
    bool isSetup {false};
};
static_assert(sizeof(UserResourceParam) == 0xb0, "Wrong size for 'xlink2::UserResourceParam'");

}  // namespace xlink2