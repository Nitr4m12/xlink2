#pragma once

#include <math/seadVectorFwd.h>

#include "xlink2/xlink2Handle.h"
#include "xlink2/xlink2UserInstanceELink.h"

namespace xlink2 {
class HandleELink : public Handle /*, nn::vfx::Handle*/{
public:
    using Handle::Handle;

    HandleELink(UserInstanceELink* user_instance, const char* asset_key_name)
    {
        user_instance->searchAndHold(asset_key_name, this);
    }

    sead::Vector3f setMtxUp(const sead::Vector3f&, const sead::Vector3f&, f32);
    HandleELink* setMtxZ(const sead::Vector3f&, const sead::Vector3f&, f32);
};
static_assert(sizeof(HandleELink) == 0x10, "xlink2::HandleELink size mismatch");

};  // namespace xlink2