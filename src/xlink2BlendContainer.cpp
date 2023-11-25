#include "xlink2/xlink2BlendContainer.h"

namespace xlink2 {
BlendContainer::~BlendContainer() = default;

bool BlendContainer::start() {  callAllChildContainer_(); }

bool BlendContainer::initialize(Event* event, const ResAssetCallTable& res_asset_call_table) {
    ContainerBase::initialize(event, res_asset_call_table);
    ResourceUtil::getResContainerParam(mResAssetCallTable);
    return true;
}
}  // namespace xlink2