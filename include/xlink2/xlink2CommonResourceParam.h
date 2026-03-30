#pragma once

#include <basis/seadTypes.h>
#include <math/seadVectorFwd.h>

#include "xlink2/xlink2Resource.h"

namespace xlink2 {
struct CommonResourceParam {
    CommonResourceParam() {}

    u32 numResParam {0};
    u32 numResAssetParam {0};
    u32 numResTriggerOverwriteParam {0};
    u32 numLocalPropertyNameRefTable {0};
    u32 numLocalPropertyEnumNameRefTable {0};
    u32 numDirectValueTable {0};
    u32 numRandomTable {0};
    u32 numCurveTable {0};
    u32 numCurvePointTable {0};
    ResAssetParam* assetParamTable {nullptr};
    u32 triggerOverwriteParamTablePos {0};
    u32* localPropertyNameRefTable {nullptr};
    u32* localPropertyEnumNameRefTable {nullptr};
    s32* directValueTable {nullptr};
    ResRandomCallTable* randomCallTable {nullptr};
    ResCurveCallTable* curveCallTable {nullptr};
    sead::Vector2f* curvePointTable {nullptr};
    u32 conditionTablePos {0};
    u32 exRegionPos {0};
    u32 nameTablePos {0};

    void reset()
    {
        numResParam = 0;
        numResAssetParam = 0;
        numResTriggerOverwriteParam = 0;
        numLocalPropertyNameRefTable = 0;
        numLocalPropertyEnumNameRefTable = 0;
        numDirectValueTable = 0;
        numRandomTable = 0;
        numCurveTable = 0;
        numCurvePointTable = 0;
        assetParamTable = nullptr;
        triggerOverwriteParamTablePos = 0;
        localPropertyNameRefTable = nullptr;
        localPropertyEnumNameRefTable = nullptr;
        directValueTable = nullptr;
        randomCallTable = nullptr;
        curveCallTable = nullptr;
        curvePointTable = nullptr;
        conditionTablePos = 0;
        exRegionPos = 0;
        nameTablePos = 0;
    }
};
}  // namespace xlink2