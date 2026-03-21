#pragma once

#include <container/seadPtrArray.h>

#include "xlink2/xlink2SolvedAssetParam.h"
#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
struct UserResourceParamELink : public UserResourceParam {
    sead::PtrArray<SolvedAssetParamELink> solvedAssetParamPtrs;
};
static_assert(sizeof(UserResourceParamELink) == 0xc0, "Incorrect size of 'xlink2::UserResourceParamELink'");
}  // namespace xlink2