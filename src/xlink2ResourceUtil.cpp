#include "xlink2/xlink2ResourceUtil.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
ResContainerParam* ResourceUtil::getResContainerParam(const ResAssetCallTable& asset_ctb)
{
    if (asset_ctb.flag.isOffBit(0))
        return nullptr;

    return solveOffset<ResContainerParam>(asset_ctb.paramStartPos);
}

ResSwitchContainerParam*
ResourceUtil::getResSwitchContainerParam(const ResAssetCallTable& asset_ctb)
{
    if (getResContainerParam(asset_ctb) == nullptr)
        return nullptr;

    if (getResContainerParam(asset_ctb)->type != ContainerType_Switch)
        return nullptr;

    return static_cast<ResSwitchContainerParam*>(getResContainerParam(asset_ctb));
}

ResSequenceContainerParam*
ResourceUtil::getResSequenceContainerParam(const ResAssetCallTable& asset_ctb)
{
    ResContainerParam* param {getResContainerParam(asset_ctb)};

    if (param == nullptr)
        return nullptr;

    return param->type == ContainerType_Sequence ? static_cast<ResSequenceContainerParam*>(param) :
                                                   nullptr;
}
}  // namespace xlink2