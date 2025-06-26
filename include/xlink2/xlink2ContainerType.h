#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace xlink2 {
static sead::SafeString sContainerNames[6] {"Switch", "Random", "Random2", "Blend", "Sequence", "Asset"};

enum class ContainerType : u32 {
    Switch,
    Random,
    Random2,
    Blend,
    Sequence,
    Asset
};
}