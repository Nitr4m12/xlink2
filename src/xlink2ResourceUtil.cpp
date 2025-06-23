#include "xlink2/xlink2ResourceUtil.h"
#include "xlink2/xlink2ResContainerParam.h"
#include "xlink2/xlink2TriggerType.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {

ResContainerParam* ResourceUtil::getResContainerParam(const ResAssetCallTable& asset_ctb)
{
    if (asset_ctb.flag.isOnBit(0))
        return calcOffset<ResContainerParam>(asset_ctb.paramStartPos);
    
    return nullptr;
}
TriggerType ResourceUtil::getActionTriggerType(const ResActionTrigger& action_trigger) {
    // sead::BitFlag16 flag {action_trigger.flag};

    if ((action_trigger.flag & 16) == 0)
        return TriggerType::Action;

    if (action_trigger.flag | 8)
        return TriggerType::Always;

    if (action_trigger.flag | 4)
        return TriggerType::Property;

    return TriggerType::None;
}
}  // namespace xlink2::ResourceUtil