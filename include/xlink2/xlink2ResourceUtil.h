#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2Resource.h"

namespace xlink2 {
class ResourceUtil {
public:
    static ResContainerParam* getResContainerParam(const ResAssetCallTable&);
    static ResSwitchContainerParam* getResSwitchContainerParam(const ResAssetCallTable&);
    static ResSequenceContainerParam* getResSequenceContainerParam(const ResAssetCallTable&);

    static TriggerType getActionTriggerType(const ResActionTrigger& action_trigger)
    {
        
        if (action_trigger.flag.isOnBit(2))
            return TriggerType::Property;

        if (action_trigger.flag.isOnBit(3))
            return TriggerType::Always;

        if (action_trigger.flag.isOnBit(4))
            return TriggerType::None;

        return TriggerType::Action;
    }
};
}  // namespace xlink2
