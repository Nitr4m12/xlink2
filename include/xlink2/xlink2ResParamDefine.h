#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ParamValueType.h"

namespace xlink2 {
struct ResParamDefine {
    u32 namePos;
    ParamValueType type;
    union {
        s32 defaultValueInt;
        f32 defaultValueFloat;
        u32 defaultValueString;
    };
};
}