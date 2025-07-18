#include "xlink2/xlink2ResourceUtil.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
ResContainerParam* ResourceUtil::getResContainerParam(const ResAssetCallTable& asset_ctb)
{
    if (asset_ctb.flag.isOnBit(0))
        return calcOffset<ResContainerParam>(asset_ctb.paramStartPos);
    
    return nullptr;
}

ResContainerParam* ResourceUtil::getResSwitchContainerParam(const ResAssetCallTable& asset_ctb)
{
    if (getResContainerParam(asset_ctb) != nullptr)
        return getResContainerParam(asset_ctb)->type == ContainerType::Switch ? getResContainerParam(asset_ctb) : nullptr;

    return nullptr;
}

ResContainerParam* ResourceUtil::getResSequenceContainerParam(const ResAssetCallTable& asset_ctb)
{
    ResContainerParam* param {getResContainerParam(asset_ctb)};

    if (param != nullptr)
        return param->type == ContainerType::Sequence ? param : nullptr;
    
    return nullptr;
}
}  // namespace xlink2