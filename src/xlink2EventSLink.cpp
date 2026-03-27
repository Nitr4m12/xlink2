#include "xlink2/xlink2EventSLink.h"

#include "xlink2/xlink2AssetExecutorSLink.h"
#include "xlink2/xlink2SystemSLink.h"

namespace xlink2 {
void EventSLink::initializeImpl_() 
{
    mBitFlag2.makeAllZero();
    mVolumeScale = 1.0;
    mVolumeTvScale = -1.0;
    mPitchScale = 1.0;
    mLpfScale = 0.0;
    mAngle = 0.0;
    mPriorityScale = 1.0;
    mBiquadType = 0;
    mBiquadValue = 0.0;
    mPosition = {0, 0, 0};
    mVelocity = {0, 0, 0};
    _0xd8 = nullptr;
    _0xe0 = 0;
}

bool EventSLink::getPos(sead::Vector3f* pos) const
{
    if (mBitFlag2.isOnBit(8)) {
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

s32 EventSLink::getSoundHandle(sead::PtrArray<aal::Handle>* handle_ptrs) const
{
    s32 num_handle {0};
    for (auto& executor : mAliveAssetExecutors) {
        auto& executor_slink {static_cast<AssetExecutorSLink&>(executor)};

        if (handle_ptrs->isFull()) {
            SystemSLink::instance()->addError(Error::Type::ListToGetterIsFull, 
                                              mpUserInstance->getUser(), 
                                              "getSoundHandle(maxSize=%d) failed", 
                                              handle_ptrs->capacity());
            return num_handle;
        }

        if (executor.isAssetValid()) {
            handle_ptrs->pushBack(reinterpret_cast<aal::Handle*>(executor_slink.getHandle()));
            ++num_handle;
        }
    }
    return num_handle;
}
} // namespace xlink2