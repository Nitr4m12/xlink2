#include "xlink2/xlink2BlendContainer.h"
#include "xlink2/xlink2ResourceUtil.h"

namespace xlink2 {
BlendContainer::~BlendContainer() = default;

bool BlendContainer::start()
{
    return callAllChildContainer_();
}

bool BlendContainer::initialize(Event* event, const ResAssetCallTable& res_asset_call_table)
{
    ContainerBase::initialize(event, res_asset_call_table);
    ResourceUtil::getResContainerParam(mAssetCallTable);
    return true;
}
}  // namespace xlink2