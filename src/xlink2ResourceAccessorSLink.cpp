#include <xlink2/xlink2ResourceAccessorSLink.h>

namespace xlink2 {

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

bool ResourceAccessorSLink::isBoneNameOverwritten(u32 p1) const {
    return isParamOverwritten(p1, 0xf);
}
}