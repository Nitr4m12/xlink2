#include "xlink2/xlink2AssetExecutorELink.h"

namespace xlink2 {
ResourceAccessor* AssetExecutorELink::getResourceAccessor_() const {
    return mUserInstance->getResourceAccessor();
}

u8 AssetExecutorELink::isRequestReEmit() const {
    return _5 >> 5 & 1;
}

void AssetExecutorELink::onFinalize_() {}

void AssetExecutorELink::setInnerParam_() {
    mPositionXWithOverwrite = setInnerParamBit(ELinkAssetParamId::PositionX, (ELinkEventParam)0);
    mPositionYWithOverwrite = setInnerParamBit(ELinkAssetParamId::PositionY, (ELinkEventParam)1);
    mPositionZWithOverwrite = setInnerParamBit(ELinkAssetParamId::PositionZ, (ELinkEventParam)2);
    mRotationXWithOverwrite = setInnerParamBit(ELinkAssetParamId::RotationX, (ELinkEventParam)3);
    mRotationYWithOverwrite = setInnerParamBit(ELinkAssetParamId::RotationY, (ELinkEventParam)4);
    mRotationZWithOverwrite = setInnerParamBit(ELinkAssetParamId::RotationZ, (ELinkEventParam)5);
}
}  // namespace xlink2