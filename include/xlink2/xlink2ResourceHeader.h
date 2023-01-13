#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
struct ResourceHeader {
    u8 magic[4];
    u32 dataSize;
    u32 version;
    u32 numResParam;
    u32 numResAssetParam;
    u32 numResTriggerOverwriteParam;
    u32 triggerOverwriteParamTablePos;
    u32 localPropertyNameRefTablePos;
    u32 numLocalPropertyNameRefTable;
    u32 numLocalPropertyEnumNameRefTable;
    u32 numDirectValueTable;
    u32 numRandomTable;
    u32 numCurveTable;
    u32 numCurvePointTable;
    u32 exRegionPos;
    u32 numUser;
    u32 conditionTablePos;
    u32 nameTablePos;
};
}  // namespace xlink2