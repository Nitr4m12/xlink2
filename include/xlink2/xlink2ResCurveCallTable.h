#pragma once

#include "basis/seadTypes.h"
namespace xlink2 {
class ResCurveCallTable {
    u16 curvePointStartPos;
    u16 numPoint;
    u16 curveType;
    u16 isPropGlobal;
    u32 propName;
    u32 propIdx;
    s16 localPropertyNameIdx;
    u8 padding[2];
};
}  // namespace xlink2