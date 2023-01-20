#pragma once

#include <basis/seadTypes.h>
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResCurveCallTable.h"
#include "xlink2/xlink2ResRandomCallTable.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"
#include "xlink2/xlink2ResUserHeader.h"

namespace xlink2 {
class DirectValue {};
class CurvePoint {};
struct CommonResourceParam {
    u32 numResParam;
    u32 numResAssetParam;
    ResUserHeader* resUserHeader;
    u32 numLocalPropertyEnumNameRefTable;
    u32 numDirectValueTable;
    u32 numRandomCallTable;
    u32 numCurveCallTable;
    u32 numCurvePointTable;
    ResAssetCallTable* resAssetCallTable;
    ResTriggerOverwriteParam* resTriggerOverwriteParamTable;
    void* localPropertyNameRefTable;
    void* localPropertyEnumNameRefTable;
    DirectValue* directValueTable;
    ResRandomCallTable* randomCallTable;
    ResCurveCallTable* curveCallTable;
    CurvePoint* curvePointTable;
    u32 nameTableNum;
    char* nameTable;
};
}  // namespace xlink2