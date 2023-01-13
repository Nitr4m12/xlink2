#pragma once

#include "basis/seadTypes.h"

#include "xlink2/xlink2ResActionTrigger.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2TriggerType.h"

namespace xlink2::ResourceUtil {
TriggerType getActionTriggerType(ResActionTrigger const&);
u32 getResContainerParam(ResAssetCallTable*);
u32 getResSequenceContainerParam(ResAssetCallTable const&);
u32 getResSwitchContainerParam(ResAssetCallTable const&);
}  // namespace xlink2::ResourceUtil