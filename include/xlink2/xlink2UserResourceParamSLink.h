#pragma once

#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
class UserResourceParamSLink : public UserResourceParam {
public:
    u64 _1;
    char* distanceParamSetName;
    s32 limitType;
    s32 playableLimitNum;
    f32 priority;
    bool isNoPos;
    f32 dopplerFactor;
};
static_assert(sizeof(UserResourceParamSLink) == 0xd8, "Incorrect size of 'xlink2::UserResourceParamSLink'");
}  // namespace xlink2