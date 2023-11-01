#pragma once

#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
class UserResourceParamELink : UserResourceParam {
private:
    u64 _0{0};
    u64 _1{0};
};
static_assert(sizeof(UserResourceParamELink) == 0xc0, "Incorrect size of 'xlink2::UserResourceParamELink'");
}  // namespace xlink2