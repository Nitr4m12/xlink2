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

ResContainerParam* ResourceUtil::getResSequenceContainerParam(const ResAssetCallTable& asset_ctb)
{
    ResContainerParam* param {getResContainerParam(asset_ctb)};

    if (param != nullptr)
        return param->type == ContainerType::Sequence ? param : nullptr;
    
    return nullptr;
}

TriggerType ResourceUtil::getActionTriggerType(const ResActionTrigger& action_trigger) 
{
    if (action_trigger.flag.isOnBit(2))
        return TriggerType::Property;

    if (action_trigger.flag.isOnBit(3))
        return TriggerType::Always;

    if (action_trigger.flag.isOnBit(4))
    return TriggerType::None;

    return TriggerType::Action;
}
}  // namespace xlink2::ResourceUtil