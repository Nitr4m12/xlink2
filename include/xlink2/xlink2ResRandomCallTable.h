#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResRandomCallTable {
    f32 minValue;
    f32 maxValue;
};
static_assert(sizeof(ResRandomCallTable) == 8, "xlink2::ResRandomCallTable size mismatch");
}  // namespace xlink2