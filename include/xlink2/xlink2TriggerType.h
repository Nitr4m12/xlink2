#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
enum class TriggerType : s32 {
    Action = 0,
    Property,
    Always,
    None,
    Invalid = -1
};
}