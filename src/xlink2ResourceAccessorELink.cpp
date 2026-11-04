#include <xlink2/xlink2ResourceAccessorELink.h>

#include "xlink2/xlink2ELinkAssetParamId.h"
#include "xlink2/xlink2UserResourceELink.h"

namespace xlink2 {
bool ResourceAccessorELink::isBlankAsset(const ResAssetCallTable& asset_ctb) const
{
    const char* param_name {""};
    if (!checkAndErrorIsAsset_(asset_ctb, "isBlankAsset"))
        return false;

    const ResParam* asset_param {getResParamFromAssetParamPos(asset_ctb.paramStartPos, s32(ELinkAssetParamId::RuntimeAssetName))};

    if (asset_param == nullptr)
        param_name = mpSystem->getParamDefineTable()->getAssetParamDefaultValueString(s32(ELinkAssetParamId::RuntimeAssetName));
    else
        param_name = getResParamValueString_(*asset_param);

    return strncmp(param_name, "@Blank", 6) == 0;
}

const char* ResourceAccessorELink::getAssetName(const ResAssetCallTable& asset_ctb) const
{
    return getValueString_("getAssetName", asset_ctb, s32(ELinkAssetParamId::RuntimeAssetName), "");
}

s16 ResourceAccessorELink::getEsetVal(const ResAssetCallTable& asset_ctb) const
{
    UserResourceELink* user_resource {static_cast<UserResourceELink*>(mpUserResource)};
    auto* solved_asset_param {user_resource->getSolvedAssetParameterELink(asset_ctb)};
    if (solved_asset_param == nullptr)
        return -1;

    return static_cast<s16>(solved_asset_param->esetVal);
}

const char* ResourceAccessorELink::getGroupName(const ResAssetCallTable& asset_ctb) const
{
    return getValueString_("getGroupName", asset_ctb, s32(ELinkAssetParamId::GroupName), "");
}

s8 ResourceAccessorELink::getGroupId(const ResAssetCallTable& asset_ctb) const
{
    UserResourceELink* user_resource {static_cast<UserResourceELink*>(mpUserResource)};
    auto* solved_asset_param {user_resource->getSolvedAssetParameterELink(asset_ctb)};
    if (solved_asset_param == nullptr)
        return -1;

    return solved_asset_param->groupId;
}

ResourceAccessorELink::ClipType
ResourceAccessorELink::getClipType(const ResAssetCallTable& asset_ctb) const
{
    u32 param_value {0};
    if (!checkAndErrorIsAsset_(asset_ctb, "getClipType"))
        return ClipType::None;

    const ResParam* asset_param {getResParamFromAssetParamPos(asset_ctb.paramStartPos, s32(ELinkAssetParamId::Clip))};
    if (asset_param == nullptr)
        param_value = mpSystem->getParamDefineTable()->getAssetParamDefaultValueInt(s32(ELinkAssetParamId::Clip));
    else
        param_value = getResParamValueInt_(*asset_param);

    if (param_value == 0) {
        if (isNeedObserve(asset_ctb)) {
            return ClipType::NeedObserve;
        }
        return ClipType::Kill;
    }

    return static_cast<ClipType>(param_value);
}

bool ResourceAccessorELink::isAutoOneTimeFade(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(s32(ELinkAssetParamId::AssetName));
}

bool ResourceAccessorELink::isForceLoopAsset(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(s32(ELinkAssetParamId::GroupName));
}

s32 ResourceAccessorELink::getForceCalc(const ResAssetCallTable& asset_ctb) const
{
    return getValueInt_("getForceCalc", asset_ctb, s32(ELinkAssetParamId::ForceCalc), 0);
}

s32 ResourceAccessorELink::getMtxSetType(const ResAssetCallTable& asset_ctb) const
{
    return getValueInt_("getMtxSetType", asset_ctb, s32(ELinkAssetParamId::MtxSetType), 0);
}

s32 ResourceAccessorELink::getRotateSourceType(const ResAssetCallTable& asset_ctb) const
{
    return getValueInt_("getRotateSourceType", asset_ctb, s32(ELinkAssetParamId::RotateSourceType), 0);
}

bool ResourceAccessorELink::isFollow(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(1);
}

bool ResourceAccessorELink::isUseOneEmitter(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(2);
}

f32 ResourceAccessorELink::getDelay(const ResAssetCallTable& asset_ctb,
                                    const UserInstance* user_instance) const
{
    return getValueFloatWithLowerLimit_("getDelay", asset_ctb, s32(ELinkAssetParamId::Delay), 0.0, user_instance);
}

f32 ResourceAccessorELink::getDuration(const ResAssetCallTable& asset_ctb,
                                       const UserInstance* user_instance) const
{
    return getValueFloatWithLowerLimit_("getDuration", asset_ctb, s32(ELinkAssetParamId::Duration), 0.0, user_instance);
}

const char* ResourceAccessorELink::getBoneName(const ResAssetCallTable& asset_ctb) const
{
    return getValueString_("getBoneName", asset_ctb, s32(ELinkAssetParamId::BoneName), "");
}

f32 ResourceAccessorELink::getScale(const ResAssetCallTable& asset_ctb,
                                    const UserInstance* user_instance) const
{
    return getValueFloat_("getScale", asset_ctb, s32(ELinkAssetParamId::Scale), 1.0, user_instance);
}

f32 ResourceAccessorELink::getPositionX(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getPositionX", asset_ctb, s32(ELinkAssetParamId::PositionX), 0.0, user_instance);
}

f32 ResourceAccessorELink::getPositionY(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getPositionY", asset_ctb, s32(ELinkAssetParamId::PositionY), 0.0, user_instance);
}

f32 ResourceAccessorELink::getPositionZ(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getPositionZ", asset_ctb, s32(ELinkAssetParamId::PositionZ), 0.0, user_instance);
}

f32 ResourceAccessorELink::getRotationX(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getRotationX", asset_ctb, s32(ELinkAssetParamId::RotationX), 0.0, user_instance);
}

f32 ResourceAccessorELink::getRotationY(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getRotationY", asset_ctb, s32(ELinkAssetParamId::RotationY), 0.0, user_instance);
}

f32 ResourceAccessorELink::getRotationZ(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getRotationZ", asset_ctb, s32(ELinkAssetParamId::RotationZ), 0.0, user_instance);
}

f32 ResourceAccessorELink::getColorRed(const ResAssetCallTable& asset_ctb,
                                       const UserInstance* user_instance) const
{
    return getValueFloat_("getColorRed", asset_ctb, s32(ELinkAssetParamId::ColorRed), 1.0, user_instance);
}

f32 ResourceAccessorELink::getColorGreen(const ResAssetCallTable& asset_ctb,
                                         const UserInstance* user_instance) const
{
    return getValueFloat_("getColorGreen", asset_ctb, s32(ELinkAssetParamId::ColorGreen), 1.0, user_instance);
}

f32 ResourceAccessorELink::getColorBlue(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getColorBlue", asset_ctb, s32(ELinkAssetParamId::ColorBlue), 1.0, user_instance);
}

f32 ResourceAccessorELink::getAlpha(const ResAssetCallTable& asset_ctb,
                                    const UserInstance* user_instance) const
{
    return getValueFloat_("getAlpha", asset_ctb, s32(ELinkAssetParamId::Alpha), 1.0, user_instance);
}

f32 ResourceAccessorELink::getEmissionRate(const ResAssetCallTable& asset_ctb,
                                           const UserInstance* user_instance) const
{
    return getValueFloat_("getEmissionRate", asset_ctb, s32(ELinkAssetParamId::EmissionRate), 1.0, user_instance);
}

f32 ResourceAccessorELink::getEmissionScale(const ResAssetCallTable& asset_ctb,
                                            const UserInstance* user_instance) const
{
    return getValueFloat_("getEmissionScale", asset_ctb, s32(ELinkAssetParamId::EmissionScale), 1.0, user_instance);
}

f32 ResourceAccessorELink::getEmissionInterval(const ResAssetCallTable& asset_ctb,
                                               const UserInstance* user_instance) const
{
    return getValueFloat_("getEmissionInterval", asset_ctb, s32(ELinkAssetParamId::EmissionInterval), 1.0, user_instance);
}

f32 ResourceAccessorELink::getDirectionalVel(const ResAssetCallTable& asset_ctb,
                                             const UserInstance* user_instance) const
{
    return getValueFloat_("getDirectionalVel", asset_ctb, s32(ELinkAssetParamId::DirectionalVel), 1.0, user_instance);
}

f32 ResourceAccessorELink::getLifeScale(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getLifeScale", asset_ctb, s32(ELinkAssetParamId::LifeScale), 1.0, user_instance);
}

f32 ResourceAccessorELink::getOverwriteDelay(u32 idx, const UserInstance* user_instance) const
{
    return getOverwriteValueFloatWithLimit_(idx, s32(ELinkAssetParamId::Delay), user_instance);
}

const char* ResourceAccessorELink::getOverwriteBoneName(u32 idx) const
{
    return getResOverwriteParamValueString_(idx, s32(ELinkAssetParamId::BoneName));
}

f32 ResourceAccessorELink::getOverwriteScale(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::Scale), user_instance);
}

f32 ResourceAccessorELink::getOverwritePositionX(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::PositionX), user_instance);
}

f32 ResourceAccessorELink::getOverwritePositionY(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::PositionY), user_instance);
}

f32 ResourceAccessorELink::getOverwritePositionZ(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::PositionZ), user_instance);
}

f32 ResourceAccessorELink::getOverwriteRotationX(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::RotationX), user_instance);
}

f32 ResourceAccessorELink::getOverwriteRotationY(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::RotationY), user_instance);
}

f32 ResourceAccessorELink::getOverwriteRotationZ(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::RotationZ), user_instance);
}

f32 ResourceAccessorELink::getOverwriteColorRed(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::ColorRed), user_instance);
}

f32 ResourceAccessorELink::getOverwriteColorGreen(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::ColorGreen), user_instance);
}

f32 ResourceAccessorELink::getOverwriteColorBlue(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::ColorBlue), user_instance);
}

f32 ResourceAccessorELink::getOverwriteAlpha(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::Alpha), user_instance);
}

f32 ResourceAccessorELink::getOverwriteEmissionRate(u32 idx,
                                                    const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(idx, s32(ELinkAssetParamId::EmissionRate), user_instance);
}

f32 ResourceAccessorELink::getDelayWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                 const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::Delay)))
        return getOverwriteDelay(idx, user_instance);

    return getDelay(asset_ctb, user_instance);
}

const char* ResourceAccessorELink::getBoneNameWithOverwrite(const ResAssetCallTable& asset_ctb,
                                                            u32 idx) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::BoneName)))
        return getOverwriteBoneName(idx);

    return getBoneName(asset_ctb);
}

f32 ResourceAccessorELink::getScaleWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                 const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::Scale)))
        return getOverwriteScale(idx, user_instance);

    return getScale(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getPositionXWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                     const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::PositionX)))
        return getOverwritePositionX(idx, user_instance);

    return getPositionX(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getPositionYWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                     const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::PositionY)))
        return getOverwritePositionY(idx, user_instance);

    return getPositionY(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getPositionZWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                     const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::PositionZ)))
        return getOverwritePositionZ(idx, user_instance);

    return getPositionZ(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getRotationXWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                     const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::RotationX)))
        return getOverwriteRotationX(idx, user_instance);

    return getRotationX(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getRotationYWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                     const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::RotationY)))
        return getOverwriteRotationY(idx, user_instance);

    return getRotationY(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getRotationZWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                     const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::RotationZ)))
        return getOverwriteRotationZ(idx, user_instance);

    return getRotationZ(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getColorRedWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                    const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::ColorRed)))
        return getOverwriteColorRed(idx, user_instance);

    return getColorRed(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getColorGreenWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                      const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::ColorGreen)))
        return getOverwriteColorGreen(idx, user_instance);

    return getColorGreen(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getColorBlueWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                     const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::ColorBlue)))
        return getOverwriteColorBlue(idx, user_instance);

    return getColorBlue(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getAlphaWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                 const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::Alpha)))
        return getOverwriteAlpha(idx, user_instance);

    return getAlpha(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getEmissionRateWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx,
                                                        const UserInstance* user_instance) const
{
    if (isParamOverwritten(idx, s32(ELinkAssetParamId::EmissionRate)))
        return getOverwriteEmissionRate(idx, user_instance);

    return getEmissionRate(asset_ctb, user_instance);
}

s32 ResourceAccessorELink::getTriggerOverwriteParamId_(u32 param_id) const
{
    auto id_type {static_cast<ELinkAssetParamId>(param_id)};
    switch (id_type) {
    case ELinkAssetParamId::Delay:
        return 0;
    case ELinkAssetParamId::BoneName:
        return 1;
    case ELinkAssetParamId::Scale:
        return 2;
    case ELinkAssetParamId::PositionX:
        return 3;
    case ELinkAssetParamId::PositionY:
        return 4;
    case ELinkAssetParamId::PositionZ:
        return 5;
    case ELinkAssetParamId::RotationX:
        return 6;
    case ELinkAssetParamId::RotationY:
        return 7;
    case ELinkAssetParamId::RotationZ:
        return 8;
    case ELinkAssetParamId::ColorRed:
        return 9;
    case ELinkAssetParamId::ColorGreen:
        return 10;
    case ELinkAssetParamId::ColorBlue:
        return 11;
    case ELinkAssetParamId::Alpha:
        return 12;
    case ELinkAssetParamId::EmissionRate:
        return 13;
    default:
        return -1;
    }
}

sead::BitFlag32 ResourceAccessorELink::getAssetBitFlag_(const ResAssetCallTable& asset_ctb) const
{
    return getValueInt_("getAssetBitFlag_", asset_ctb, s32(ELinkAssetParamId::BitFlag), 0);
}

bool ResourceAccessorELink::isBoneNameOverwritten(u32 idx) const
{
    return isParamOverwritten(idx, s32(ELinkAssetParamId::BoneName));
}
}  // namespace xlink2