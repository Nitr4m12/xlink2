#include "xlink2/xlink2ResourceUtil.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
ResContainerParam* ResourceUtil::getResContainerParam(const ResAssetCallTable& asset_ctb)
{
    if (asset_ctb.flag.isOnBit(0))
        return calcOffset<ResContainerParam>(asset_ctb.paramStartPos);
    
    return nullptr;
}

ResSwitchContainerParam* ResourceUtil::getResSwitchContainerParam(const ResAssetCallTable& asset_ctb)
{
    if (getResContainerParam(asset_ctb) != nullptr)
        return getResContainerParam(asset_ctb)->type == ContainerType::Switch ? static_cast<ResSwitchContainerParam*>(getResContainerParam(asset_ctb)) : nullptr;

    return nullptr;
}

ResSequenceContainerParam* ResourceUtil::getResSequenceContainerParam(const ResAssetCallTable& asset_ctb)
{
    ResContainerParam* param {getResContainerParam(asset_ctb)};

    if (param != nullptr)
        return param->type == ContainerType::Sequence ? static_cast<ResSequenceContainerParam*>(param) : nullptr;
    
    return nullptr;
}
}  // namespace xlink2