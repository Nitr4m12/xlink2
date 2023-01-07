#pragma once

#include "basis/seadTypes.h"
namespace xlink2 {
struct EditorHeader {
    u8 unknown[4];
    u32 numResParam;
    u32 numResAssetParam;
    u32 triggerOverwriteParamTablePos;
    u32 localPropertyNameRefTablePos;
    u32 numResTriggerOverwriteParam;
    u32 numLocalPropertyNameRefTable;
    u32 numLocalPropertyEnumNameRefTable;
    u32 numDirectValueTable;
    u32 numRandomTable;
    u32 numCurveTable;
    u32 numCurvePointTable;
    u32 exDataRegionPos;
    u32 userNamePos;
    u32 userBinPos;
    u32 conditionTablePos;
    u32 nameTablePos;
};
}  // namespace xlink2