#pragma once

#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2ResAction.h"
#include "xlink2/xlink2ResActionSlot.h"
#include "xlink2/xlink2ResActionTrigger.h"
#include "xlink2/xlink2ResAlwaysTrigger.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResParam.h"
#include "xlink2/xlink2ResProperty.h"
#include "xlink2/xlink2ResPropertyTrigger.h"
#include "xlink2/xlink2ResUserHeader.h"

namespace xlink2 {
struct UserBinParam {
    CommonResourceParam* commonResourceParam;
    ResUserHeader* resUserHeader;
    void* _0;
    ResParam* userParamArray;
    u32* localPropertyNameRefTable;
    ResAssetCallTable* resAssetCallTable;
    u32 containerTableLower;
    ResActionSlot* resActionSlotTable;
    ResAction* resActionTable;
    ResActionTrigger* resActionTriggerTable;
    ResProperty* resPropertyTable;
    ResPropertyTrigger* resPropertyTriggerTable;
    ResAlwaysTrigger* resAlwaysTriggerTable;
};
}  // namespace xlink2