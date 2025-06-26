#include <xlink2/xlink2ResourceAccessorSLink.h>
#include "xlink2/xlink2UserResourceParamSLink.h"

namespace xlink2 {
s32 ResourceAccessorSLink::getUserLimitType() const
{
    if (mpUserResource != nullptr) {
        UserResourceParamSLink* user_resource_param {static_cast<UserResourceParamSLink*>(mpUserResource->getParamWithSetupCheck())};
        if (user_resource_param != nullptr)
            return user_resource_param->limitType;
    }

    return 0;
}

s32 ResourceAccessorSLink::getUserPlayableLimitNum() const
{
    if (mpUserResource != nullptr) {
        UserResourceParamSLink* user_resource_param {static_cast<UserResourceParamSLink*>(mpUserResource->getParamWithSetupCheck())};
        if (user_resource_param != nullptr)
            return user_resource_param->playableLimitNum;
    }

    return 0;
}

bool ResourceAccessorSLink::isBlankAsset(const ResAssetCallTable& asset_ctb) const
{
    const char* param_name;
    if (checkAndErrorIsAsset_(asset_ctb, "isBlankAsset")) {
        const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, 1)};

        if (asset_param == nullptr)
            param_name = this->mpSystem->getParamDefineTable()->getAssetParamDefaultValueString(1);
        else
            param_name = this->getResParamValueString_(*asset_param);

        return strncmp(param_name, "@Blank", 6) == 0;
    }

    return false;
}

const char* ResourceAccessorSLink::getAssetName(const ResAssetCallTable& asset_ctb) const
{
    return this->getResParamValueString("getAssetName", asset_ctb, 1, "");
}

const char* ResourceAccessorSLink::getGroupName(const ResAssetCallTable& asset_ctb) const
{
    return this->getResParamValueString("getGroupName", asset_ctb, 2, "");
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

f32 ResourceAccessorSLink::getVolume(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloatWithLowerLimit("getVolume", asset_ctb, 3, 0.0, user_instance);
}

f32 ResourceAccessorSLink::getVolumeTv(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloat("getVolumeTv", asset_ctb, 4, -1.0, user_instance);
}

f32 ResourceAccessorSLink::getVolumeDrc(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloat("getVolumeDrc", asset_ctb, 5, -1.0, user_instance);
}

f32 ResourceAccessorSLink::getPitch(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloatWithLowerLimit("getPitch", asset_ctb, 6, 1.0, user_instance);
}

f32 ResourceAccessorSLink::getLpf(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloat("getLpf", asset_ctb, 7, 0.0, user_instance);
}

f32 ResourceAccessorSLink::getStopFrame(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloat("getStopFrame", asset_ctb, 8, 0.0, user_instance);
}

f32 ResourceAccessorSLink::getFadeInTime(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloat("getFadeInTime", asset_ctb, 9, 0.0, user_instance);
}

aal::FadeCurveType ResourceAccessorSLink::getFadeCurveType(const ResAssetCallTable& asset_ctb) const
{
    return static_cast<aal::FadeCurveType>(this->getResParamValueInt("getFadeCurveType", asset_ctb, 10, 0));
}

f32 ResourceAccessorSLink::getDelay(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloatWithLowerLimit("getDelay", asset_ctb, 11, 0.0, user_instance);
}

f32 ResourceAccessorSLink::getDuration(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloatWithLowerLimit("getDuration", asset_ctb, 12, 0.0, user_instance);
}

f32 ResourceAccessorSLink::getPriority(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloat("getPriority", asset_ctb, 13, 0.0, user_instance);
}

f32 ResourceAccessorSLink::getDopplerFactor(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloat("getDopplerFactor", asset_ctb, 14, 0.0, user_instance);
}

const char* ResourceAccessorSLink::getBoneName(const ResAssetCallTable& asset_ctb) const
{
    return this->getResParamValueString("getBoneName", asset_ctb, 15, "");
}

const char* ResourceAccessorSLink::getDistanceParamSetName(const ResAssetCallTable& asset_ctb) const
{
    return this->getResParamValueString("getDistanceParamSetName", asset_ctb, 16, "");
}

f32 ResourceAccessorSLink::getOverwriteVolume(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloatWithLimit(idx, 3, user_instance);
}

f32 ResourceAccessorSLink::getOverwritePitch(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloatWithLimit(idx, 6, user_instance);
}

f32 ResourceAccessorSLink::getOverwriteLpf(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 7, user_instance);
}

f32 ResourceAccessorSLink::getOverwriteStopFrame(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 8, user_instance);
}

f32 ResourceAccessorSLink::getOverwriteFadeInTime(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 9, user_instance);
}

f32 ResourceAccessorSLink::getOverwriteDelay(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloatWithLimit(idx, 11, user_instance);
}

f32 ResourceAccessorSLink::getOverwritePriority(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 13, user_instance);
}

char const* ResourceAccessorSLink::getOverwriteBoneName(u32 idx) const
{
    return this->getResOverwriteParamValueString_(idx, 15);
}

f32 ResourceAccessorSLink::getVolumeWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 3))
        return getOverwriteVolume(idx, user_instance);

    return getVolume(asset_ctb, user_instance);
}

f32 ResourceAccessorSLink::getPitchWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 6))
        return getOverwritePitch(idx, user_instance);

    return getPitch(asset_ctb, user_instance);
}

f32 ResourceAccessorSLink::getLpfWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 7))
        return getOverwriteLpf(idx, user_instance);

    return getLpf(asset_ctb, user_instance);
}

f32 ResourceAccessorSLink::getStopFrameWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 8))
        return getOverwriteStopFrame(idx, user_instance);

    return getStopFrame(asset_ctb, user_instance);
}

f32 ResourceAccessorSLink::getFadeInTimeWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 9))
        return getOverwriteFadeInTime(idx, user_instance);

    return getFadeInTime(asset_ctb, user_instance);
}

f32 ResourceAccessorSLink::getDelayWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 11))
        return getOverwriteDelay(idx, user_instance);

    return getDelay(asset_ctb, user_instance);
}

f32 ResourceAccessorSLink::getPriorityWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 13))
        return getOverwritePriority(idx, user_instance);

    return getPriority(asset_ctb, user_instance);
}

const char* ResourceAccessorSLink::getBoneNameWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx) const
{
    if (this->isParamOverwritten(idx, 15))
        return getOverwriteBoneName(idx);

    return getBoneName(asset_ctb);
}

s32 ResourceAccessorSLink::getTriggerOverwriteParamId_(u32 idx) const
{
    constexpr s32 OVERWRITE_PARAM_IDS[13] {0, -1, -1, 1, 2, 3, 4, -1, 5, -1, 6, -1, 7};

    if (idx - 3 < 13)
        return OVERWRITE_PARAM_IDS[(s32)idx - 3];

    return -1;
}

sead::BitFlag32 ResourceAccessorSLink::getAssetBitFlag_(const ResAssetCallTable& asset_ctb) const
{
    return this->getResParamValueInt("getAssetBitFlag_", asset_ctb, 17, 0);
}

bool ResourceAccessorSLink::isBoneNameOverwritten(u32 idx) const
{
    return this->isParamOverwritten(idx, 15);
}
}