#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ResCurveCallTable.h"
#include "xlink2/xlink2ResParam.h"
#include "xlink2/xlink2ResRandomCallTable.h"

namespace xlink2 {
class DirectValue {};
struct CurvePoint {
    float x;
    float y;
};
struct CommonResourceParam {
    u32 numResParam {};
    u32 numResAssetParam {};
    u32 numResTriggerOverwriteParam {};
    u32 numLocalPropertyNameRefTable {};
    u32 numLocalPropertyEnumNameRefTable {};
    u32 numDirectValueTable {};
    u32 numRandomTable {};
    u32 numCurveTable {};
    u32 numCurvePointTable {};
    ResAssetParam* assetParamTable {};
    u32 triggerOverwriteParamTablePos {};
    u32* localPropertyNameRefTable {};
    u32* localPropertyEnumNameRefTable {};
    s32* directValueTable {};
    ResRandomCallTable* randomCallTable {};
    ResCurveCallTable* curveCallTable {};
    CurvePoint* curvePointTable {};
    u32 conditionTablePos {};
    u32 exRegionPos {};
    u32 nameTablePos {};
};
}  // namespace xlink2