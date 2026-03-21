#pragma once

#include "xlink2/xlink2SolvedAssetParam.h"
#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
struct UserResourceParamELink : public UserResourceParam {
    sead::Buffer<SolvedAssetParamELink> solvedAssetParamBuffer;
};
static_assert(sizeof(UserResourceParamELink) == 0xc0, "'xlink2::UserResourceParamELink' size mismatch");
}  // namespace xlink2