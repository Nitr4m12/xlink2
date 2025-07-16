#pragma once

#include <math/seadVectorFwd.h>

#include "xlink2/xlink2Handle.h"

namespace xlink2 {
class HandleELink : Handle /*, nn::vfx::Handle*/{
public:
    sead::Vector3f setMtxUp(const sead::Vector3f&, const sead::Vector3f&, f32);
    HandleELink* setMtxZ(const sead::Vector3f&, const sead::Vector3f&, f32);
};
static_assert(sizeof(HandleELink) == 0x10, "xlink2::HandleELink size mismatch");

};  // namespace xlink2