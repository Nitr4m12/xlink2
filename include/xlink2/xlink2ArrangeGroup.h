#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
struct ArrangeGroupParam {
    u32 groupNamePos;
    s8 limitType;
    s8 limitThreshold;
    s8 _0x6;
};
static_assert(sizeof(ArrangeGroupParam) == 0x8, "'xlink2::ArrangeGroupParam' size mismatch");

struct ArrangeGroup {
    u32 numParam;
    ArrangeGroupParam* arrangeGroupParams;
};
}  // namespace xlink2