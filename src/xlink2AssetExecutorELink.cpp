#include "xlink2/xlink2AssetExecutorELink.h"

namespace xlink2 {
ResourceAccessor* AssetExecutorELink::getResourceAccessor_() const {
    return mUserInstance->getResourceAccessor();
}

bool AssetExecutorELink::isRequestReEmit() const {
    return _5 >> 5 & 1;
}

bool AssetExecutorELink::isLoopEvent() const {
    if (!mResAssetCallTable)
        return false;

    auto* res_accessor = getResourceAccessor_();
    return res_accessor->isLoopAsset(*mResAssetCallTable);
}


void AssetExecutorELink::onFinalize_() {}

void AssetExecutorELink::setInnerParam_() {
    mPositionX = setInnerParamBit(ELinkAssetParamId::PositionX, (ELinkEventParam)0);
    mPositionY = setInnerParamBit(ELinkAssetParamId::PositionY, (ELinkEventParam)1);
    mPositionZ = setInnerParamBit(ELinkAssetParamId::PositionZ, (ELinkEventParam)2);
    mRotationX = setInnerParamBit(ELinkAssetParamId::RotationX, (ELinkEventParam)3);
    mRotationY = setInnerParamBit(ELinkAssetParamId::RotationY, (ELinkEventParam)4);
    mRotationZ = setInnerParamBit(ELinkAssetParamId::RotationZ, (ELinkEventParam)5);
}
}  // namespace xlink2