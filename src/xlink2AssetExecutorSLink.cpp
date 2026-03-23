#include "xlink2/xlink2AssetExecutorSLink.h"

#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2ResourceAccessorSLink.h"
#include "xlink2/xlink2UserResourceSLink.h"

namespace xlink2 {
AssetExecutorSLink::~AssetExecutorSLink() = default;

void AssetExecutorSLink::updateParam_()
{
    auto* accessor {static_cast<UserResourceSLink*>(getUserInstance()->getUserResource())->getAccessorPtr()};
    u32 overwrite_param_pos = reinterpret_cast<u64>(mpTriggerOverwriteParam);
    if (mParamFlag.isOnBit(0)) {
        if (accessor->isParamOverwritten(overwrite_param_pos, 3))
            mVolume = accessor->getOverwriteVolume(overwrite_param_pos, mpUserInstance);
        else
            mVolume = accessor->getVolume(*mpAssetCallTable, mpUserInstance);
    }

    if (mParamFlag.isOnBit(1)) {
        mVolumeTv = accessor->getVolumeTv(*mpAssetCallTable, mpUserInstance);
    }

    if (mParamFlag.isOnBit(2)) {
        if (accessor->isParamOverwritten(overwrite_param_pos, 6))
            mPitch = accessor->getOverwritePitch(overwrite_param_pos, mpUserInstance);
        else
            mPitch = accessor->getPitch(*mpAssetCallTable, mpUserInstance);
    }

    if (mParamFlag.isOnBit(3)) {
        if (accessor->isParamOverwritten(overwrite_param_pos, 7))
            mLpf = accessor->getOverwriteLpf(overwrite_param_pos, mpUserInstance);
        else
            mLpf = accessor->getLpf(*mpAssetCallTable, mpUserInstance);
    }

    if (mParamFlag.isOnBit(5)) {
        if (accessor->isParamOverwritten(overwrite_param_pos, 13))
            mPriority = accessor->getOverwritePriority(overwrite_param_pos, mpUserInstance);
        else
            mPriority = accessor->getPriority(*mpAssetCallTable, mpUserInstance);
    }

    applyParam_(false);
}

bool AssetExecutorSLink::isLoopEvent() const 
{
    if (!mpAssetCallTable)
        return false;

    auto* res_accessor = mpUserInstance->getUser()->getUserResource()->getAccessorPtr();
    return res_accessor->isLoopAsset(*mpAssetCallTable);
}

void AssetExecutorSLink::requestReEmit(bool check) 
{
    if (check)
        mBitFlag.setBit(0);
    else
        mBitFlag.resetBit(0);
}

bool AssetExecutorSLink::isRequestReEmit() const 
{
    return mBitFlag.isOnBit(0);
}

void AssetExecutorSLink::onFinalize_() 
{
    _9 = nullptr;
}
}  // namespace xlink2