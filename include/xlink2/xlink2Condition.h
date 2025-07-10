#pragma once

#include "xlink2/xlink2PropertyType.h"
#include "xlink2/xlink2ResContainerParam.h"

namespace xlink2 {
enum class CompareType : s32 {
    NotEqual,
    LessThanOrEqual,
    LessThan,
    GreaterThanOrEqual,
    GreaterThan,
    Equal,
};

struct ResCondition {
    ContainerType parentContainerType;
};

struct SwitchCondition : public ResCondition {
    PropertyType propertyType;
    CompareType compareType;
    s32 value;
    s16 localPropertyEnumNameIdx;
    bool isSolved;
    bool isGlobal;
};

struct RandomCondition : public ResCondition {
    f32 weight;
};
}  // namespace xlink2