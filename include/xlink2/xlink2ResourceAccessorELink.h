#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ParamValueType.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class ResourceAccessorELink : public ResourceAccessor {
public:
    enum class ClipType {
        None,
        Kill,
        NeedObserve,
        Unknown
    };

    ~ResourceAccessorELink() override;

    bool isBlankAsset(const ResAssetCallTable& asset_ctb) const override;

    const char* getAssetName(const ResAssetCallTable& asset_ctb) const;
    
    u64 getEsetVal(const ResAssetCallTable& asset_ctb) const;
    
    const char* getGroupName(const ResAssetCallTable& asset_ctb) const;
    u64 getGroupId(const ResAssetCallTable& asset_ctb) const;
    
    ClipType getClipType(const ResAssetCallTable& asset_ctb) const;

    bool isAutoOneTimeFade(const ResAssetCallTable& asset_ctb) const override;
    bool isForceLoopAsset(const ResAssetCallTable& asset_ctb) const;

    s32 getForceCalc(const ResAssetCallTable& asset_ctb) const;
    s32 getMtxSetType(const ResAssetCallTable& asset_ctb) const;
    s32 getRotateSourceType(const ResAssetCallTable& asset_ctb) const;

    bool isFollow(const ResAssetCallTable& asset_ctb) const;
    bool isUseOneEmitter(const ResAssetCallTable& asset_ctb) const;

    f32 getDelay(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getDuration(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const override;

    const char* getBoneName(const ResAssetCallTable& asset_ctb) const override;

    f32 getScale(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;

    f32 getPositionX(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getPositionY(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getPositionZ(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;

    f32 getRotationX(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getRotationY(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getRotationZ(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;

    f32 getColorRed(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getColorGreen(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getColorBlue(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getAlpha(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;

    f32 getEmissionRate(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getEmissionScale(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getEmissionInterval(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;

    f32 getDirectionalVel(const ResAssetCallTable& asset_ctb, UserInstance const*) const;

    f32 getLifeScale(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;

    f32 getOverwriteDelay(u32, const UserInstance* user_instance) const;

    const char* getOverwriteBoneName(u32 idx) const override;

    f32 getOverwriteScale(u32, const UserInstance* user_instance) const;

    f32 getOverwritePositionX(u32, const UserInstance* user_instance) const;
    f32 getOverwritePositionY(u32, const UserInstance* user_instance) const;
    f32 getOverwritePositionZ(u32, const UserInstance* user_instance) const;

    f32 getOverwriteRotationX(u32, const UserInstance* user_instance) const;
    f32 getOverwriteRotationY(u32, const UserInstance* user_instance) const;
    f32 getOverwriteRotationZ(u32, const UserInstance* user_instance) const;

    f32 getOverwriteColorRed(u32, const UserInstance* user_instance) const;
    f32 getOverwriteColorGreen(u32, const UserInstance* user_instance) const;
    f32 getOverwriteColorBlue(u32, const UserInstance* user_instance) const;
    f32 getOverwriteAlpha(u32, const UserInstance* user_instance) const;

    f32 getOverwriteEmissionRate(u32, const UserInstance* user_instance) const;

    f32 getDelayWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const override;

    const char* getBoneNameWithOverwrite(const ResAssetCallTable& asset_ctb, u32) const;

    u64 getScaleWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;

    f32 getPositionXWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;
    f32 getPositionYWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;
    f32 getPositionZWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;

    f32 getRotationXWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;
    f32 getRotationYWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;
    f32 getRotationZWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;

    u64 getColorRedWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;
    u64 getColorGreenWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;
    u64 getColorBlueWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;
    f64 getAlphaWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;

    u64 getEmissionRateWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance* user_instance) const;

    u32 getTriggerOverwriteParamId(u32) const;

    sead::BitFlag32 getAssetBitFlag(const ResAssetCallTable& asset_ctb) const override;

    bool isBoneNameOverwritten(u32) const override;

private:
    const char* getResParamValueString(const char* func_name, const ResAssetCallTable& asset_ctb, s32 param_idx, const char* default_value) const
    {
        if (!checkAndErrorIsAsset_(asset_ctb, "getGroupName"))
            return default_value;

        const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, param_idx)};
        if (asset_param != nullptr)
            return this->getResParamValueString_(*asset_param);

        return this->mSystem->getParamDefineTable()->getAssetParamDefaultValueString(param_idx);
    }

    s32 getResParamValueInt(const char* func_name, const ResAssetCallTable& asset_ctb, s32 param_idx, s32 default_value) const
    {
        if (!checkAndErrorIsAsset_(asset_ctb, func_name))
            return default_value;
    
        const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, param_idx)};
        if (asset_param != nullptr)
            return this->getResParamValueInt_(*asset_param);

        return this->mSystem->getParamDefineTable()->getAssetParamDefaultValueInt(param_idx);
    }

    f32 getResParamValueFloat(const char* func_name, const ResAssetCallTable& asset_ctb, 
                              s32 param_idx, f32 default_value, const UserInstance* user_instance) const
    {
        if (!checkAndErrorIsAsset_(asset_ctb, func_name))
            return default_value;
    
        const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, param_idx)};
        if (asset_param != nullptr)
            return this->getResParamValueFloat_(*asset_param, user_instance);
        
        return this->mSystem->getParamDefineTable()->getAssetParamDefaultValueFloat(param_idx);
    }
    
    f32 getResParamValueFloatWithLimit(const char* func_name, const ResAssetCallTable& asset_ctb, 
                                       s32 param_idx, f32 default_value, const UserInstance* user_instance) const
    {
        f32 param_value {default_value};
        if (!checkAndErrorIsAsset_(asset_ctb, func_name))
            return param_value;
        
        const ResParam* asset_param {this->getResParamFromAssetParamPos(asset_ctb.paramStartPos, param_idx)};
        if (asset_param != nullptr)
            param_value = this->getResParamValueFloat_(*asset_param, user_instance);
        else
            param_value = this->mSystem->getParamDefineTable()->getAssetParamDefaultValueFloat(param_idx);

        if (param_value < 0.0)
            return 0.0;
        return param_value;
    }
};
}  // namespace xlink2