#pragma once

#include "xlink2/xlink2Resource.h"

namespace xlink2 {
struct UserBinParam {
    ResUserHeader* pResUserHeader {};
    u32* pLocalPropertyNameRefTable {};
    ResParam* userParamArray {};
    u16* pSortedAssetIdTable {};
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