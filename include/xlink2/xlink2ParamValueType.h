#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
enum ParamValueType : u32 {
    UInt32,
    Float,
    Bool,
    Enum,
    String,
    Unknown,
    Invalid = 0xFFFFFFFF
};
}  // namespace xlink2