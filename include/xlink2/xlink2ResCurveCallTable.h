#pragma once

#include "basis/seadTypes.h"
namespace xlink2 {
struct ResCurveCallTable {
    u16 curvePointStartPos;
    u16 numPoint;
    u16 curveType;
    u16 isPropGlobal;
    u32 propName;
    s32 propIdx;
    s16 localPropertyNameIdx;
};
static_assert(sizeof(ResCurveCallTable) == 0x14, "xlink2::ResCurveCallTable size mismatch");
}  // namespace xlink2