#pragma once

#include <basis/seadTypes.h>
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class DirectValue {};
class CurvePoint {};
struct CommonResourceParam {
    u32 numResParam;
    u32 numResAssetParam;
    u32 numResTriggerOverwriteParam;
    u32 numLocalPropertyNameRefTable;
    u32 numLocalPropertyEnumNameRefTable;
    u32 numDirectValueTable;
    u32 numRandomTable;
    u32 numCurveTable;
    u32 numCurvePointTable;
    ResAssetCallTable* resAssetCallTable;
    u32 triggerOverwriteParamTablePos;
    u32 _0;
    void* localPropertyNameRefTable;
    void* localPropertyEnumNameRefTable;
    u32* directValueTable;
    u32* randomCallTable;
    u32* curveCallTable;
    u32* curvePointTable;
    u32 conditionTablePos;
    u32 exRegionPos;
    u32 nameTablePos;
};
}  // namespace xlink2