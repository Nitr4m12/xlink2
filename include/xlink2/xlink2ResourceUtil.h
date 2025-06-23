#pragma once

#include <basis/seadTypes.h>
#include "xlink2/xlink2ResActionTrigger.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResContainerParam.h"
#include "xlink2/xlink2TriggerType.h"

namespace xlink2 {
class ResourceUtil {
public:
    static ResContainerParam* getResContainerParam(const ResAssetCallTable&);
    static ResContainerParam* getResSwitchContainerParam(const ResAssetCallTable&);
    static ResContainerParam* getResSequenceContainerParam(const ResAssetCallTable&);

    static TriggerType getActionTriggerType(ResActionTrigger const&);
};
}  // namespace xlink2
