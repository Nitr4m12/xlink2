#include "xlink2/xlink2BlendContainer.h"

namespace xlink2 {
u8 BlendContainer::start() { return callAllChildContainer(); }

void BlendContainer::initialize(Event* event, const ResAssetCallTable& res_asset_call_table) {
    ContainerBase::initialize(event, res_asset_call_table);
    ResourceUtil::getResContainerParam(mResAssetCallTable);
}
}  // namespace xlink2