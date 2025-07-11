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

namespace xlink2 {
struct UserBinParam {
    CommonResourceParam* commonResourceParam {};
    u32* pLocalPropertyNameRefTable {};
    ResParam* userParamArray {};
    s16* pSortedAssetIdTable {};
    ResAssetCallTable* pResAssetCallTable {};
    u32 containerTablePos {};
    ResActionSlot* pResActionSlotTable {};
    ResAction* pResActionTable {};
    ResActionTrigger* pResActionTriggerTable {};
    ResProperty* pResPropertyTable {};
    ResPropertyTrigger* pResPropertyTriggerTable {};
    ResAlwaysTrigger* pResAlwaysTriggerTable {};
};
}  // namespace xlink2