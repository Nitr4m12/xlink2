#pragma once

#include <basis/seadTypes.h>
#include <math/seadVectorFwd.h>

#include "xlink2/xlink2Resource.h"

namespace xlink2 {
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
    sead::Vector2f* curvePointTable {};
    u32 conditionTablePos {};
    u32 exRegionPos {};
    u32 nameTablePos {};

    void reset()
    {
        *this = {};
    }
};
}  // namespace xlink2