#include <xlink2/xlink2ResourceAccessorELink.h>
#include <xlink2/xlink2ResourceUtil.h>

namespace xlink2 {
bool ResourceAccessorELink::isBlankAsset(const ResAssetCallTable& asset_ctb) const
{
    const char* param_name;
    if (checkAndErrorIsAsset_(asset_ctb, "isBlankAsset")) {
        const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, 1)};

        if (asset_param == nullptr)
            param_name = this->mSystem->getParamDefineTable()->getAssetParamDefaultValueString(1);
        else
            param_name = this->getResParamValueString_(*asset_param);

        return strncmp(param_name, "@Blank", 6) == 0;
    }

    return false;
}

const char* ResourceAccessorELink::getAssetName(const ResAssetCallTable& asset_ctb) const
{
    return getResParamValueString("getAssetName", asset_ctb, 1, "");
    
}

const char* ResourceAccessorELink::getGroupName(const ResAssetCallTable& asset_ctb) const
{
    return getResParamValueString("getGroupName", asset_ctb, 3, "");
}

ResourceAccessorELink::ClipType ResourceAccessorELink::getClipType(const ResAssetCallTable& asset_ctb) const
{
    u32 param_value {0};
    if (checkAndErrorIsAsset_(asset_ctb, "getClipType")) {
        const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, 7)};
        if (asset_param == nullptr)
            param_value = this->mSystem->getParamDefineTable()->getAssetParamDefaultValueInt(7);
        else
            param_value = this->getResParamValueInt_(*asset_param);

        if (param_value == 0) {
            if (this->isNeedObserve(asset_ctb)) {
                return ClipType::NeedObserve;
            }
            return ClipType::Kill;
        }
    }

    return static_cast<ClipType>(param_value);

}

bool ResourceAccessorELink::isAutoOneTimeFade(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag(asset_ctb).isOnBit(0);
}

bool ResourceAccessorELink::isForceLoopAsset(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag(asset_ctb).isOnBit(3);
}

s32 ResourceAccessorELink::getForceCalc(const ResAssetCallTable& asset_ctb) const
{   
    return getResParamValueInt("getForceCalc", asset_ctb, 8, 0);
}

s32 ResourceAccessorELink::getMtxSetType(const ResAssetCallTable& asset_ctb) const
{
    return getResParamValueInt("getMtxSetType", asset_ctb, 9, 0);
}

s32 ResourceAccessorELink::getRotateSourceType(const ResAssetCallTable& asset_ctb) const
{
    return getResParamValueInt("getRotateSourceType", asset_ctb, 10, 0);
}

bool ResourceAccessorELink::isFollow(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag(asset_ctb).isOnBit(1);
}

bool ResourceAccessorELink::isUseOneEmitter(const ResAssetCallTable& asset_ctb) const
{
    return getAssetBitFlag(asset_ctb).isOnBit(2);
}

f32 ResourceAccessorELink::getDelay(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloatWithLimit("getDelay", asset_ctb, 5, 0.0, user_instance);
}

f32 ResourceAccessorELink::getDuration(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloatWithLimit("getDuration", asset_ctb, 6, 0.0, user_instance);
}

const char* ResourceAccessorELink::getBoneName(const ResAssetCallTable& asset_ctb) const
{
    return getResParamValueString("getBoneName", asset_ctb, 11, "");
}

f32 ResourceAccessorELink::getScale(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getScale", asset_ctb, 12, 1.0, user_instance);
}

f32 ResourceAccessorELink::getPositionX(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getPositionX", asset_ctb, 13, 0.0, user_instance);
}

f32 ResourceAccessorELink::getPositionY(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getPositionY", asset_ctb, 14, 0.0, user_instance);
}

f32 ResourceAccessorELink::getPositionZ(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getPositionZ", asset_ctb, 15, 0.0, user_instance);
}

f32 ResourceAccessorELink::getRotationX(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getRotationX", asset_ctb, 16, 0.0, user_instance);
}

f32 ResourceAccessorELink::getRotationY(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getRotationY", asset_ctb, 17, 0.0, user_instance);
}

f32 ResourceAccessorELink::getRotationZ(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getRotationZ", asset_ctb, 18, 0.0, user_instance);
}

f32 ResourceAccessorELink::getColorRed(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getColorRed", asset_ctb, 19, 1.0, user_instance);
}

f32 ResourceAccessorELink::getColorGreen(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getColorGreen", asset_ctb, 20, 1.0, user_instance);
}

f32 ResourceAccessorELink::getColorBlue(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getColorBlue", asset_ctb, 21, 1.0, user_instance);
}

f32 ResourceAccessorELink::getAlpha(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getAlpha", asset_ctb, 22, 1.0, user_instance);
}

f32 ResourceAccessorELink::getEmissionRate(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getEmissionRate", asset_ctb, 23, 1.0, user_instance);
}

f32 ResourceAccessorELink::getEmissionScale(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getEmissionScale", asset_ctb, 24, 1.0, user_instance);
}

f32 ResourceAccessorELink::getEmissionInterval(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getEmissionInterval", asset_ctb, 25, 1.0, user_instance);
}

f32 ResourceAccessorELink::getDirectionalVel(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getDirectionalVel", asset_ctb, 26, 1.0, user_instance);
}

f32 ResourceAccessorELink::getLifeScale(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    return getResParamValueFloat("getLifeScale", asset_ctb, 27, 1.0, user_instance);
}

f32 ResourceAccessorELink::getOverwriteDelay(u32 idx, const UserInstance* user_instance) const
{
    return getResOverwriteParamValueFloatWithLimit(idx, 5, user_instance);
}

const char* ResourceAccessorELink::getOverwriteBoneName(u32 idx) const
{
    return this->getResOverwriteParamValueString_(idx, 11);
}

f32 ResourceAccessorELink::getOverwriteScale(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 12, user_instance);
}

f32 ResourceAccessorELink::getOverwritePositionX(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 13, user_instance);
}

f32 ResourceAccessorELink::getOverwritePositionY(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 14, user_instance);
}

f32 ResourceAccessorELink::getOverwritePositionZ(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 15, user_instance);
}

f32 ResourceAccessorELink::getOverwriteRotationX(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 16, user_instance);
}

f32 ResourceAccessorELink::getOverwriteRotationY(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 17, user_instance);
}

f32 ResourceAccessorELink::getOverwriteRotationZ(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 18, user_instance);
}

f32 ResourceAccessorELink::getOverwriteColorRed(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 19, user_instance);
}

f32 ResourceAccessorELink::getOverwriteColorGreen(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 20, user_instance);
}

f32 ResourceAccessorELink::getOverwriteColorBlue(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 21, user_instance);
}

f32 ResourceAccessorELink::getOverwriteAlpha(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 22, user_instance);
}

f32 ResourceAccessorELink::getOverwriteEmissionRate(u32 idx, const UserInstance* user_instance) const
{
    return this->getResOverwriteParamValueFloat_(idx, 23, user_instance);
}

f32 ResourceAccessorELink::getDelayWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 5))
        return getOverwriteDelay(idx, user_instance);

    return getDelay(asset_ctb, user_instance);
}

const char* ResourceAccessorELink::getBoneNameWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx) const
{
    if (this->isParamOverwritten(idx, 11))
        return getOverwriteBoneName(idx);

    return getBoneName(asset_ctb);
}

f32 ResourceAccessorELink::getScaleWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 12))
        return getOverwriteScale(idx, user_instance);

    return getScale(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getPositionXWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 13))
        return getOverwritePositionX(idx, user_instance);

    return getPositionX(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getPositionYWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 14))
        return getOverwritePositionY(idx, user_instance);

    return getPositionY(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getPositionZWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 15))
        return getOverwritePositionZ(idx, user_instance);

    return getPositionZ(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getRotationXWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 16))
        return getOverwriteRotationX(idx, user_instance);

    return getRotationX(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getRotationYWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 17))
        return getOverwriteRotationY(idx, user_instance);

    return getRotationY(asset_ctb, user_instance);
}

f32 ResourceAccessorELink::getRotationZWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const
{
    if (this->isParamOverwritten(idx, 18))
        return getOverwriteRotationZ(idx, user_instance);

    return getRotationZ(asset_ctb, user_instance);
}
}
}  // namespace xlink2