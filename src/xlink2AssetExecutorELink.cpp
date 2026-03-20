#include "xlink2/xlink2AssetExecutorELink.h"

#include "xlink2/xlink2ELinkAssetParamId.h"
#include "xlink2/xlink2ELinkEventParam.h"
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
            mBitFlag.setBit(0);
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

f32 AssetExecutorELink::setInnerParamBit_(ELinkAssetParamId param_id, ELinkEventParam param) 
{
    auto* accessor{((UserInstanceELink*)mpUserInstance)->getResourceAccessor()};
    u32 overwrite_param_pos = (u64)mpTriggerOverwriteParam;
    bool is_param_curve;
    f32 param_value{0.0};

    ELinkEventParam current_param {(s32)param_id - (s32)ELinkAssetParamId::PositionX};

    bool is_param_overwritten{accessor->isParamOverwritten(overwrite_param_pos, (u32)param_id)};
    if (is_param_overwritten) {
        switch (current_param) {
        case ELinkEventParam::PositionX:
            param_value = accessor->getOverwritePositionX(overwrite_param_pos, mpUserInstance);
            break;
        case ELinkEventParam::PositionY:
            param_value = accessor->getOverwritePositionY(overwrite_param_pos, mpUserInstance);
            break;
        case ELinkEventParam::PositionZ:
            param_value = accessor->getOverwritePositionZ(overwrite_param_pos, mpUserInstance);
            break;
        case ELinkEventParam::RotationX:
            param_value = accessor->getOverwriteRotationX(overwrite_param_pos, mpUserInstance);
            break;
        case ELinkEventParam::RotationY:
            param_value = accessor->getOverwriteRotationY(overwrite_param_pos, mpUserInstance);
            break;
        case ELinkEventParam::RotationZ:
            param_value = accessor->getOverwriteRotationZ(overwrite_param_pos, mpUserInstance);
            break;
        default:
            param_value = 0.0;
        }
        is_param_curve =
            accessor->isOverwriteParamTypeEqual(ValueReferenceType::Curve, *mpTriggerOverwriteParam, (u32)param_id);
    } 
    else {
        switch (current_param) {
        case ELinkEventParam::PositionX:
            param_value = accessor->getPositionX(*mpAssetCallTable, mpUserInstance);
            break;
        case ELinkEventParam::PositionY:
            param_value = accessor->getPositionY(*mpAssetCallTable, mpUserInstance);
            break;
        case ELinkEventParam::PositionZ:
            param_value = accessor->getPositionZ(*mpAssetCallTable, mpUserInstance);
            break;
        case ELinkEventParam::RotationX:
            param_value = accessor->getRotationX(*mpAssetCallTable, mpUserInstance);
            break;
        case ELinkEventParam::RotationY:
            param_value = accessor->getRotationY(*mpAssetCallTable, mpUserInstance);
            break;
        case ELinkEventParam::RotationZ:
            param_value = accessor->getRotationZ(*mpAssetCallTable, mpUserInstance);
            break;
        default:
            param_value = 0.0;
        }
        is_param_curve =
            accessor->isParamTypeEqual(ValueReferenceType::Curve, *mpAssetCallTable, (u32)param_id);
    }
    if (is_param_curve)
        mPositionFlag.setBit(static_cast<s32>(param));

    return param_value;
}

void AssetExecutorELink::requestReEmit(bool param1) 
{
    if (param1)
        mBitFlag.setBit(5);
    else
        mBitFlag.resetBit(5);
}

bool AssetExecutorELink::isRequestReEmit() const 
{
    return mBitFlag.isOnBit(5);
}

}  // namespace xlink2