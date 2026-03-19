#include "xlink2/xlink2EventSLink.h"

#include "xlink2/xlink2AssetExecutorSLink.h"
#include "xlink2/xlink2SystemSLink.h"

namespace xlink2 {
void EventSLink::initializeImpl_() {}

const sead::Vector3f& EventSLink::getVelocity() const
{
    return mVelocity;
}

AssetExecutorSLink* EventSLink::getAliveAssetExecutor() const
{
    if (mAliveAssetExecutors.size() == 1)
        return static_cast<AssetExecutorSLink*>(&*mAliveAssetExecutors.begin());

    if (mAliveAssetExecutors.size() > 1)
        SystemSLink::instance()->addError(Error::Type::EventHasMultipleAsset, mpUserInstance->getUser(), "getAliveAssetExecutor failed");

    return nullptr;
}
} // namespace xlink2