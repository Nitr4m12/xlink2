#include "xlink2/xlink2AssetExecutorELink.h"

#include "xlink2/xlink2ResourceAccessorELink.h"
#include "xlink2/xlink2UserInstanceELink.h"

namespace xlink2 {
AssetExecutorELink::~AssetExecutorELink() = default;

ResourceAccessorELink* AssetExecutorELink::getResourceAccessor_() const {
    return ((UserInstanceELink*)mpUserInstance)->getResourceAccessor();
}

bool AssetExecutorELink::isLoopEvent() const {
    if (!mpAssetCallTable)
        return false;

    auto* res_accessor {getResourceAccessor_()};
    return res_accessor->isLoopAsset(*mpAssetCallTable);
}

void AssetExecutorELink::onResetOverwriteParam_() {
    if (mpAssetCallTable) {
        auto* accessor{((UserInstanceELink*)mpUserInstance)->getResourceAccessor()};
        if (accessor->isFollow(*mpAssetCallTable))
            _5 |= 1;
    }
}

void AssetExecutorELink::onFinalize_() {}

void AssetExecutorELink::setInnerParam_() {
    mPosition.x = setInnerParamBit_(ELinkAssetParamId::PositionX, ELinkEventParam::PositionX);
    mPosition.y = setInnerParamBit_(ELinkAssetParamId::PositionY, ELinkEventParam::PositionY);
    mPosition.z = setInnerParamBit_(ELinkAssetParamId::PositionZ, ELinkEventParam::PositionZ);
    mRotation.x = setInnerParamBit_(ELinkAssetParamId::RotationX, ELinkEventParam::RotationX);
    mRotation.y = setInnerParamBit_(ELinkAssetParamId::RotationY, ELinkEventParam::RotationY);
    mRotation.z = setInnerParamBit_(ELinkAssetParamId::RotationZ, ELinkEventParam::RotationZ);
}

f32 AssetExecutorELink::setInnerParamBit_(ELinkAssetParamId param_id, ELinkEventParam param) {
    auto* accessor{((UserInstanceELink*)mpUserInstance)->getResourceAccessor()};
    u32 unk = (u64)mpTriggerOverwriteParam;
    bool is_param_overwritten{accessor->isParamOverwritten(unk, (u32)param_id)};
    bool unknown_check;
    f32 param_value{0.0};

    if (is_param_overwritten) {
        switch ((u32)param_id - 13) {
        case 0:
            param_value = accessor->getOverwritePositionX(unk, mpUserInstance);
            break;
        case 1:
            param_value = accessor->getOverwritePositionY(unk, mpUserInstance);
            break;
        case 2:
            param_value = accessor->getOverwritePositionZ(unk, mpUserInstance);
            break;
        case 3:
            param_value = accessor->getOverwriteRotationX(unk, mpUserInstance);
            break;
        case 4:
            param_value = accessor->getOverwriteRotationY(unk, mpUserInstance);
            break;
        case 5:
            param_value = accessor->getOverwriteRotationZ(unk, mpUserInstance);
            break;
        default:
            param_value = 0.0;
        }
        unknown_check =
            accessor->isOverwriteParamTypeEqual((ValueReferenceType)2, *mpTriggerOverwriteParam, (u32)param_id);
    } else {
        switch ((u32)param_id - 13) {
        case 0:
            param_value = accessor->getPositionX(*mpAssetCallTable, mpUserInstance);
            break;
        case 1:
            param_value = accessor->getPositionY(*mpAssetCallTable, mpUserInstance);
            break;
        case 2:
            param_value = accessor->getPositionZ(*mpAssetCallTable, mpUserInstance);
            break;
        case 3:
            param_value = accessor->getRotationX(*mpAssetCallTable, mpUserInstance);
            break;
        case 4:
            param_value = accessor->getRotationY(*mpAssetCallTable, mpUserInstance);
            break;
        case 5:
            param_value = accessor->getRotationZ(*mpAssetCallTable, mpUserInstance);
            break;
        default:
            param_value = 0.0;
        }
        unknown_check =
            accessor->isParamTypeEqual((ValueReferenceType)2, *mpAssetCallTable, (u32)param_id);
    }
    if (unknown_check)
        _10 |= 1 << (u32)param;

    return param_value;
}

void AssetExecutorELink::requestReEmit(bool param1) {
    if (!param1)
        _5 &= 0xdf;
    else
        _5 |= 0x20;
}

bool AssetExecutorELink::isRequestReEmit() const {
    return _5 >> 5 & 1;
}

}  // namespace xlink2