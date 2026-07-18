#pragma once

#include "xlink2/xlink2Handle.h"
#include "xlink2/xlink2UserInstanceSLink.h"

namespace xlink2 {
class HandleSLink : public Handle /* aal::Handle*/ {
public:
    using Handle::Handle;

    HandleSLink(UserInstanceSLink* user_instance, const char* asset_key_name)
    {
        user_instance->searchAndHold(asset_key_name, this);
    }
};
static_assert(sizeof(HandleSLink) == 0x10, "xlink2::HandleSLink size mismatch");
}