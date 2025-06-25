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
    if (checkAndErrorIsAsset_(asset_ctb, "getAssetName")) {
        const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, 1)};
        if (asset_param != nullptr)
            return this->getResParamValueString_(*asset_param);

        return this->mSystem->getParamDefineTable()->getAssetParamDefaultValueString(1);
    }

    return "";
    
}

const char* ResourceAccessorELink::getGroupName(const ResAssetCallTable& asset_ctb) const
{
    if (checkAndErrorIsAsset_(asset_ctb, "getGroupName")) {
        const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, 3)};
        if (asset_param != nullptr)
            return this->getResParamValueString_(*asset_param);

        return this->mSystem->getParamDefineTable()->getAssetParamDefaultValueString(3);
    }

    return "";
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
    if (!checkAndErrorIsAsset_(asset_ctb, "getForceCalc"))
        return 0;
    
    const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, 8)};
    if (asset_param != nullptr)
        return this->getResParamValueInt_(*asset_param);

    return this->mSystem->getParamDefineTable()->getAssetParamDefaultValueInt(8);
}

s32 ResourceAccessorELink::getMtxSetType(const ResAssetCallTable& asset_ctb) const
{
    if (!checkAndErrorIsAsset_(asset_ctb, "getMtxSetType"))
        return 0;
    
    const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, 9)};
    if (asset_param != nullptr)
        return this->getResParamValueInt_(*asset_param);

    return this->mSystem->getParamDefineTable()->getAssetParamDefaultValueInt(9);
}

s32 ResourceAccessorELink::getRotateSourceType(const ResAssetCallTable& asset_ctb) const
{
    if (!checkAndErrorIsAsset_(asset_ctb, "getRotateSourceType"))
        return 0;
    
    const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, 10)};
    if (asset_param != nullptr)
        return this->getResParamValueInt_(*asset_param);

    return this->mSystem->getParamDefineTable()->getAssetParamDefaultValueInt(10);
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
    f32 param_value {0.0};
    if (!checkAndErrorIsAsset_(asset_ctb, "getDelay"))
        return param_value;
    
    const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, 5)};
    if (asset_param != nullptr)
        param_value = this->getResParamValueFloat_(*asset_param, user_instance);
    else
        param_value = this->mSystem->getParamDefineTable()->getAssetParamDefaultValueFloat(5);

    if (param_value < 0.0)
        return 0.0;
    return param_value;
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