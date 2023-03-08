#pragma once

#include "xlink2/xlink2ContainerType.h"

namespace xlink2 {
struct ResCondition {
    ContainerType parentContainerType;
    u32 propertyType;
    u32 compareType;
    u32 value;
    u16 localPropertyEnumNameIdx;
    bool isSolved;
    bool isGlobal;
};

struct RandomCondition {
    ContainerType parentContainerType;
    f32 weight;
};
}  // namespace xlink2