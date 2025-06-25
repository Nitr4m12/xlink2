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

f32 ResourceAccessorELink::getOverwriteAlpha(u32 p1, const UserInstance* p2) const {
    return ResourceAccessor::getResOverwriteParamValueFloat_(p1, 0x16, p2);
}

const char* ResourceAccessorELink::getOverwriteBoneName(u32 p1) const {
    return ResourceAccessor::getResOverwriteParamValueString_(p1, 0xb);
}

f32 ResourceAccessorELink::getOverwriteColorBlue(u32 p1, const UserInstance* p2) const {
    return ResourceAccessor::getResOverwriteParamValueFloat_(p1, 0x15, p2);
}

f32 ResourceAccessorELink::getOverwriteColorGreen(u32 p1, const UserInstance* p2) const {
    return ResourceAccessor::getResOverwriteParamValueFloat_(p1, 0x14, p2);
}

f32 ResourceAccessorELink::getOverwriteColorRed(u32 p1, const UserInstance* p2) const {
    return ResourceAccessor::getResOverwriteParamValueFloat_(p1, 0x13, p2);
}

bool ResourceAccessorELink::isBoneNameOverwritten(u32 p1) const {
    return isParamOverwritten(p1, 0xb);
}
}  // namespace xlink2