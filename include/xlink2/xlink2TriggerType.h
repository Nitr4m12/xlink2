#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
enum class TriggerType : u32 {
    Action = 0,
    Property,
    Always,
    Invalid = 0xffffffff
};
}