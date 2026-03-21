#pragma once

#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
struct UserResourceParamSLink : public UserResourceParam {
    void* _0xb0 {};
    char* distanceParamSetName {};
    s32 limitType {0};
    s32 playableLimitNum {-1};
    f32 priority {1.0};
    bool isNoPos {false};
    f32 dopplerFactor {-1.0};
    u32 _0xd4 {0};
    void* _0xd8 {};
};
static_assert(sizeof(UserResourceParamSLink) == 0xe0, "'xlink2::UserResourceParamSLink' size mismatch");
}  // namespace xlink2