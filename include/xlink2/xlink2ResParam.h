#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ParamValueType.h"

namespace xlink2 {
struct ResParam {
    u32 namePos;
    ParamValueType type;
    u32 defaultValue;
};
}  // namespace xlink2