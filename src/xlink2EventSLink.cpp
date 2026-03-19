#include "xlink2/xlink2EventSLink.h"

#include "xlink2/xlink2AssetExecutorSLink.h"
#include "xlink2/xlink2SystemSLink.h"

namespace xlink2 {
void EventSLink::initializeImpl_() {}

bool EventSLink::getPos(sead::Vector3f* pos) const
{
    if (_0x99.isOnBit(0)) {
        pos->set(mPosition);
        return true;
    }

    return false;
}

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

s32 EventSLink::getAliveAssetExecutor(sead::PtrArray<AssetExecutorSLink>* executor_ptr_array) const
{
    s32 num_alive_executor {0};
    for (auto& executor : mAliveAssetExecutors) {
        if (executor_ptr_array->isFull()) {
            SystemSLink::instance()->addError(Error::Type::ListToGetterIsFull, mpUserInstance->getUser(), 
                                              "getAliveAssetExecutor(maxSize=%d) failed", executor_ptr_array->capacity());
            return num_alive_executor;
        }

        if (executor.isAssetValid()) {
            if (!executor_ptr_array->isFull())
                executor_ptr_array->pushBack(static_cast<AssetExecutorSLink*>(&executor));
            ++num_alive_executor;
        }
    }

    return num_alive_executor;
}
} // namespace xlink2