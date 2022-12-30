#pragma once

#include "xlink2/xlink2ContainerType.h"

namespace xlink2 {
struct Condition {
    ContainerType parentContainerType;
    s32 propertyType;
    s32 compareType;
    s32 value;
    s32 localPropertyEnumNameIdx;
    bool isSolved;
    bool isGlobal;
};

struct RandomCondition {
    ContainerType parentContainerType;
    f32 weight;
};
}