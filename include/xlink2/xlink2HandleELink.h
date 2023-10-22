#pragma once

#include <math/seadVectorFwd.h>

#include "xlink2/xlink2Handle.h"

namespace xlink2 {
class HandleELink : Handle /*, nn::vfx::Handle*/{
public:
    sead::Vector3f setMtxUp(sead::Vector3f const&, sead::Vector3f const&, f32);
    HandleELink* setMtxZ(sead::Vector3f const&, sead::Vector3f const&, f32);
};
static_assert(sizeof(HandleELink) == 0x10, "Wrong size for 'xlink2::HandleELink'");

};  // namespace xlink2