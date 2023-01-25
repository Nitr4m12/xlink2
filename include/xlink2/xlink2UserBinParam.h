#pragma once

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
    ResUserHeader* resUserHeader;
    u32* localPropertyRefArray;
    ResParam* userParamArray;
    u16* sortedAssetIdTable;
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