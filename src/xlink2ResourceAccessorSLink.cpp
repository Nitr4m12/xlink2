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
    return this->getResParamValueFloatWithLimit("getVolume", asset_ctb, 3, 0.0, user_instance);
}

f32 ResourceAccessorSLink::getVolumeTv(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloat("getVolumeTv", asset_ctb, 4, -1.0, user_instance);
}

f32 ResourceAccessorSLink::getVolumeDrc(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return this->getResParamValueFloat("getVolumeDrc", asset_ctb, 5, -1.0, user_instance);
}

bool ResourceAccessorSLink::isBoneNameOverwritten(u32 p1) const {
    return isParamOverwritten(p1, 0xf);
}
}