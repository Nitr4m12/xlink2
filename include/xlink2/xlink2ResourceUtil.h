#pragma once

#include <basis/seadTypes.h>
#include "xlink2/xlink2ResActionTrigger.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResContainerParam.h"
#include "xlink2/xlink2TriggerType.h"

namespace xlink2 {
class ResourceUtil {
public:
    static ResContainerParam* getResContainerParam(ResAssetCallTable*);
    static u32 getResSwitchContainerParam(ResAssetCallTable const&);
    static u32 getResSequenceContainerParam(ResAssetCallTable const&);

    static TriggerType getActionTriggerType(ResActionTrigger const&);
};
}  // namespace xlink2
