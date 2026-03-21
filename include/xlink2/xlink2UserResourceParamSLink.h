#pragma once

#include "xlink2/xlink2ArrangeGroup.h"
#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
struct UserResourceParamSLink : public UserResourceParam {
    u32 _2;
    ResParam userParam {};
    u32 groupNamePos {0};
    const char* distanceParamSetName {};
    s32 limitType {0};
    s32 playableLimitNum {-1};
    f32 priority {1.0};
    bool isNoPos {false};
    f32 dopplerFactor {-1.0};
    u32 numArrangeGroupParam {0};
    ArrangeGroupParam* arrangeGroupParams {};
};
static_assert(sizeof(UserResourceParamSLink) == 0xe0, "'xlink2::UserResourceParamSLink' size mismatch");
}  // namespace xlink2