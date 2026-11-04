#include "xlink2/xlink2ResourceAccessorSLink.h"

#include "xlink2/xlink2SLinkAssetParamId.h"
#include "xlink2/xlink2UserResourceSLink.h"

namespace xlink2 {
const char* ResourceAccessorSLink::getUserDistanceParamSetName() const
{
    if (mpUserResource == nullptr)
        return "";

    auto* user_resource {static_cast<UserResourceSLink*>(mpUserResource)};
    auto* user_resource_param {user_resource->getParamSLinkWithSetupCheck()};
    if (user_resource_param == nullptr)
        return "";

    const char* set_name {user_resource_param->distanceParamSetName};
    return set_name != nullptr ? set_name : "";
}

s32 ResourceAccessorSLink::getUserLimitType() const
{
    if (mpUserResource == nullptr)
        return 0;

    auto* user_resource {static_cast<UserResourceSLink*>(mpUserResource)};
    auto* user_resource_param {user_resource->getParamSLinkWithSetupCheck()};
    if (user_resource_param == nullptr)
        return 0;

    return user_resource_param->limitType;
}

s32 ResourceAccessorSLink::getUserPlayableLimitNum() const
{
    if (mpUserResource == nullptr)
        return 0;

    auto* user_resource {static_cast<UserResourceSLink*>(mpUserResource)};
    auto* user_resource_param {user_resource->getParamSLinkWithSetupCheck()};
    if (user_resource_param == nullptr)
        return 0;

    return user_resource_param->playableLimitNum;
}

f32 ResourceAccessorSLink::getUserPriority() const
{
    if (mpUserResource == nullptr)
        return 0.0;

    auto* user_resource {static_cast<UserResourceSLink*>(mpUserResource)};
    auto* user_resource_param {user_resource->getParamSLinkWithSetupCheck()};
    if (user_resource_param == nullptr)
        return 0;

    return user_resource_param->priority;
}

bool ResourceAccessorSLink::isUserNoPos() const
{
    if (mpUserResource == nullptr)
        return false;

    auto* user_resource {static_cast<UserResourceSLink*>(mpUserResource)};
    auto* user_resource_param {user_resource->getParamSLinkWithSetupCheck()};
    if (user_resource_param == nullptr)
        return false;

    return user_resource_param->isNoPos;
}

f32 ResourceAccessorSLink::getUserDopplerFactor() const
{
    if (mpUserResource == nullptr)
        return 0.0;

    auto* user_resource {static_cast<UserResourceSLink*>(mpUserResource)};
    auto* user_resource_param {user_resource->getParamSLinkWithSetupCheck()};
    if (user_resource_param == nullptr)
        return 0.0;

    return user_resource_param->dopplerFactor;
}

bool ResourceAccessorSLink::isBlankAsset(const ResAssetCallTable& asset_ctb) const
{
    const char* runtime_asset_name;
    if (!checkAndErrorIsAsset_(asset_ctb, "isBlankAsset"))
        return false;

    const ResParam* asset_param {
        getResParamFromAssetParamPos(asset_ctb.paramStartPos,
                                     s32(SLinkAssetParamId::RuntimeAssetName)),
    };

    if (asset_param == nullptr)
        runtime_asset_name = mpSystem->getParamDefineTable()->getAssetParamDefaultValueString(
            s32(SLinkAssetParamId::RuntimeAssetName));
    else
        runtime_asset_name = getResParamValueString_(*asset_param);

    return strncmp(runtime_asset_name, "@Blank", 6) == 0;
}

const char* ResourceAccessorSLink::getAssetName(const ResAssetCallTable& asset_ctb) const
{
    return getValueString_("getAssetName", asset_ctb, s32(SLinkAssetParamId::RuntimeAssetName), "");
}

const char* ResourceAccessorSLink::getGroupName(const ResAssetCallTable& asset_ctb) const
{
    return getValueString_("getGroupName", asset_ctb, s32(SLinkAssetParamId::GroupName), "");
}

bool ResourceAccessorSLink::isFollow(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(0);
}

bool ResourceAccessorSLink::isNoParamUpdate(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(1);
}

bool ResourceAccessorSLink::isNoPos(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(2);
}

bool ResourceAccessorSLink::isStopWhenEmitterDestroying(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(3);
}

bool ResourceAccessorSLink::isUnified(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(4);
}

bool ResourceAccessorSLink::isAutoOneTimeFade(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(5);
}

bool ResourceAccessorSLink::isForceLoopAsset(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag_(asset_ctb).isOnBit(6);
}

f32 ResourceAccessorSLink::getVolume(const ResAssetCallTable& asset_ctb,
                                     const UserInstance* user_instance) const
{
    return getValueFloatWithLowerLimit_("getVolume", asset_ctb, s32(SLinkAssetParamId::Volume), 0.0,
                                        user_instance);
}

f32 ResourceAccessorSLink::getVolumeTv(const ResAssetCallTable& asset_ctb,
                                       const UserInstance* user_instance) const
{
    return getValueFloat_("getVolumeTv", asset_ctb, s32(SLinkAssetParamId::VolumeTv), -1.0,
                          user_instance);
}

f32 ResourceAccessorSLink::getVolumeDrc(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getVolumeDrc", asset_ctb, s32(SLinkAssetParamId::VolumeDrc), -1.0,
                          user_instance);
}

f32 ResourceAccessorSLink::getPitch(const ResAssetCallTable& asset_ctb,
                                    const UserInstance* user_instance) const
{
    return getValueFloatWithLowerLimit_("getPitch", asset_ctb, s32(SLinkAssetParamId::Pitch), 1.0,
                                        user_instance);
}

f32 ResourceAccessorSLink::getLpf(const ResAssetCallTable& asset_ctb,
                                  const UserInstance* user_instance) const
{
    return getValueFloat_("getLpf", asset_ctb, s32(SLinkAssetParamId::Lpf), 0.0, user_instance);
}

f32 ResourceAccessorSLink::getStopFrame(const ResAssetCallTable& asset_ctb,
                                        const UserInstance* user_instance) const
{
    return getValueFloat_("getStopFrame", asset_ctb, s32(SLinkAssetParamId::StopFrame), 0.0,
                          user_instance);
}

f32 ResourceAccessorSLink::getFadeInTime(const ResAssetCallTable& asset_ctb,
                                         const UserInstance* user_instance) const
{
    return getValueFloat_("getFadeInTime", asset_ctb, s32(SLinkAssetParamId::FadeInTime), 0.0,
                          user_instance);
}

aal::FadeCurveType ResourceAccessorSLink::getFadeCurveType(const ResAssetCallTable& asset_ctb) const
{
    return static_cast<aal::FadeCurveType>(
        getValueInt_("getFadeCurveType", asset_ctb, s32(SLinkAssetParamId::FadeCurveType), 0));
}

f32 ResourceAccessorSLink::getDelay(const ResAssetCallTable& asset_ctb,
                                    const UserInstance* user_instance) const
{
    return getValueFloatWithLowerLimit_("getDelay", asset_ctb, s32(SLinkAssetParamId::Delay), 0.0,
                                        user_instance);
}

f32 ResourceAccessorSLink::getDuration(const ResAssetCallTable& asset_ctb,
                                       const UserInstance* user_instance) const
{
    return getValueFloatWithLowerLimit_("getDuration", asset_ctb, s32(SLinkAssetParamId::Duration),
                                        0.0, user_instance);
}

f32 ResourceAccessorSLink::getPriority(const ResAssetCallTable& asset_ctb,
                                       const UserInstance* user_instance) const
{
    return getValueFloat_("getPriority", asset_ctb, s32(SLinkAssetParamId::Priority), 0.0,
                          user_instance);
}

f32 ResourceAccessorSLink::getDopplerFactor(const ResAssetCallTable& asset_ctb,
                                            const UserInstance* user_instance) const
{
    return getValueFloat_("getDopplerFactor", asset_ctb, s32(SLinkAssetParamId::DopplerFactor), 0.0,
                          user_instance);
}

const char* ResourceAccessorSLink::getBoneName(const ResAssetCallTable& asset_ctb) const
{
    return getValueString_("getBoneName", asset_ctb, s32(SLinkAssetParamId::BoneName), "");
}

const char* ResourceAccessorSLink::getDistanceParamSetName(const ResAssetCallTable& asset_ctb) const
{
    return getValueString_("getDistanceParamSetName", asset_ctb,
                           s32(SLinkAssetParamId::DistanceParamSetName), "");
}

f32 ResourceAccessorSLink::getOverwriteVolume(u32 overwrite_param_pos,
                                              const UserInstance* user_instance) const
{
    return getOverwriteValueFloatWithLimit_(overwrite_param_pos, s32(SLinkAssetParamId::Volume),
                                            user_instance);
}

f32 ResourceAccessorSLink::getOverwritePitch(u32 overwrite_param_pos,
                                             const UserInstance* user_instance) const
{
    return getOverwriteValueFloatWithLimit_(overwrite_param_pos, s32(SLinkAssetParamId::Pitch),
                                            user_instance);
}

f32 ResourceAccessorSLink::getOverwriteLpf(u32 overwrite_param_pos,
                                           const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(overwrite_param_pos, s32(SLinkAssetParamId::Lpf),
                                           user_instance);
}

f32 ResourceAccessorSLink::getOverwriteStopFrame(u32 overwrite_param_pos,
                                                 const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(overwrite_param_pos, s32(SLinkAssetParamId::StopFrame),
                                           user_instance);
}

f32 ResourceAccessorSLink::getOverwriteFadeInTime(u32 overwrite_param_pos,
                                                  const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(overwrite_param_pos, s32(SLinkAssetParamId::FadeInTime),
                                           user_instance);
}

f32 ResourceAccessorSLink::getOverwriteDelay(u32 overwrite_param_pos,
                                             const UserInstance* user_instance) const
{
    return getOverwriteValueFloatWithLimit_(overwrite_param_pos, s32(SLinkAssetParamId::Delay),
                                            user_instance);
}

f32 ResourceAccessorSLink::getOverwritePriority(u32 overwrite_param_pos,
                                                const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloat_(overwrite_param_pos, s32(SLinkAssetParamId::Priority),
                                           user_instance);
}

const char* ResourceAccessorSLink::getOverwriteBoneName(u32 overwrite_param_pos) const
{
    return getResOverwriteParamValueString_(overwrite_param_pos, s32(SLinkAssetParamId::BoneName));
}

f32 ResourceAccessorSLink::getVolumeWithOverwrite(const ResAssetCallTable& asset_ctb,
                                                  u32 overwrite_param_pos,
                                                  const UserInstance* user_instance) const
{
    if (!isParamOverwritten(overwrite_param_pos, s32(SLinkAssetParamId::Volume)))
        return getVolume(asset_ctb, user_instance);

    return getOverwriteVolume(overwrite_param_pos, user_instance);
}

f32 ResourceAccessorSLink::getPitchWithOverwrite(const ResAssetCallTable& asset_ctb,
                                                 u32 overwrite_param_pos,
                                                 const UserInstance* user_instance) const
{
    if (!isParamOverwritten(overwrite_param_pos, s32(SLinkAssetParamId::Pitch)))
        return getPitch(asset_ctb, user_instance);

    return getOverwritePitch(overwrite_param_pos, user_instance);
}

f32 ResourceAccessorSLink::getLpfWithOverwrite(const ResAssetCallTable& asset_ctb,
                                               u32 overwrite_param_pos,
                                               const UserInstance* user_instance) const
{
    if (!isParamOverwritten(overwrite_param_pos, s32(SLinkAssetParamId::Lpf)))
        return getLpf(asset_ctb, user_instance);

    return getOverwriteLpf(overwrite_param_pos, user_instance);
}

f32 ResourceAccessorSLink::getStopFrameWithOverwrite(const ResAssetCallTable& asset_ctb,
                                                     u32 overwrite_param_pos,
                                                     const UserInstance* user_instance) const
{
    if (!isParamOverwritten(overwrite_param_pos, s32(SLinkAssetParamId::StopFrame)))
        return getStopFrame(asset_ctb, user_instance);

    return getOverwriteStopFrame(overwrite_param_pos, user_instance);
}

f32 ResourceAccessorSLink::getFadeInTimeWithOverwrite(const ResAssetCallTable& asset_ctb,
                                                      u32 overwrite_param_pos,
                                                      const UserInstance* user_instance) const
{
    if (!isParamOverwritten(overwrite_param_pos, s32(SLinkAssetParamId::FadeInTime)))
        return getFadeInTime(asset_ctb, user_instance);

    return getOverwriteFadeInTime(overwrite_param_pos, user_instance);
}

f32 ResourceAccessorSLink::getDelayWithOverwrite(const ResAssetCallTable& asset_ctb,
                                                 u32 overwrite_param_pos,
                                                 const UserInstance* user_instance) const
{
    if (!isParamOverwritten(overwrite_param_pos, s32(SLinkAssetParamId::Delay)))
        return getDelay(asset_ctb, user_instance);

    return getOverwriteDelay(overwrite_param_pos, user_instance);
}

f32 ResourceAccessorSLink::getPriorityWithOverwrite(const ResAssetCallTable& asset_ctb,
                                                    u32 overwrite_param_pos,
                                                    const UserInstance* user_instance) const
{
    if (!isParamOverwritten(overwrite_param_pos, s32(SLinkAssetParamId::Priority)))
        return getPriority(asset_ctb, user_instance);

    return getOverwritePriority(overwrite_param_pos, user_instance);
}

const char* ResourceAccessorSLink::getBoneNameWithOverwrite(const ResAssetCallTable& asset_ctb,
                                                            u32 overwrite_param_pos) const
{
    if (!isParamOverwritten(overwrite_param_pos, s32(SLinkAssetParamId::BoneName)))
        return getBoneName(asset_ctb);

    return getOverwriteBoneName(overwrite_param_pos);
}

s32 ResourceAccessorSLink::getTriggerOverwriteParamId_(u32 param_id) const
{
    auto param_type {static_cast<SLinkAssetParamId>(param_id)};
    switch (param_type) {
    case SLinkAssetParamId::Volume:
        return 0;
    case SLinkAssetParamId::Pitch:
        return 1;
    case SLinkAssetParamId::Lpf:
        return 2;
    case SLinkAssetParamId::StopFrame:
        return 3;
    case SLinkAssetParamId::FadeInTime:
        return 4;
    case SLinkAssetParamId::Delay:
        return 5;
    case SLinkAssetParamId::Priority:
        return 6;
    case SLinkAssetParamId::BoneName:
        return 7;
    default:
        return -1;
    }
}

sead::BitFlag32 ResourceAccessorSLink::getAssetBitFlag_(const ResAssetCallTable& asset_ctb) const
{
    return getValueInt_("getAssetBitFlag_", asset_ctb, s32(SLinkAssetParamId::BitFlag), 0);
}

bool ResourceAccessorSLink::isBoneNameOverwritten(u32 overwrite_param_pos) const
{
    return isParamOverwritten(overwrite_param_pos, s32(SLinkAssetParamId::BoneName));
}
}  // namespace xlink2