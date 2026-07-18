#pragma once

#include "xlink2/xlink2Handle.h"

namespace xlink2 {
class HandleSLink : public Handle /* aal::Handle*/ {
public:
    using Handle::Handle;
};
static_assert(sizeof(HandleSLink) == 0x10, "xlink2::HandleSLink size mismatch");
}