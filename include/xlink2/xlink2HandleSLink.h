#pragma once

#include "xlink2/xlink2Handle.h"

namespace xlink2 {
class HandleSLink : Handle /* :: xlink2::Handle, aal::Handle*/ {

};
static_assert(sizeof(HandleSLink) == 0x10, "Wrong size for 'xlink2::HandleSLink'");
}