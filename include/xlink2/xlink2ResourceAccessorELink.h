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
    f64 getRotateSourceType(const ResAssetCallTable& asset_ctb) const;

    bool isFollow(const ResAssetCallTable& asset_ctb) const;
    bool isUseOneEmitter(const ResAssetCallTable& asset_ctb) const;

    f32 getDelay(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    f32 getDuration(const ResAssetCallTable& asset_ctb, const UserInstance*) const override;

    const char* getBoneName(const ResAssetCallTable& asset_ctb) const override;

    u64 getScale(const ResAssetCallTable& asset_ctb, const UserInstance*) const;

    f32 getPositionX(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    f32 getPositionY(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    f32 getPositionZ(const ResAssetCallTable& asset_ctb, const UserInstance*) const;

    f32 getRotationX(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    f32 getRotationY(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    f32 getRotationZ(const ResAssetCallTable& asset_ctb, const UserInstance*) const;

    u64 getColorRed(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    u64 getColorGreen(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    u64 getColorBlue(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    f64 getAlpha(const ResAssetCallTable& asset_ctb, const UserInstance*) const;

    u64 getEmissionRate(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    u64 getEmissionScale(const ResAssetCallTable& asset_ctb, const UserInstance*) const;
    u64 getEmissionInterval(const ResAssetCallTable& asset_ctb, const UserInstance*) const;

    u64 getDirectionalVel(const ResAssetCallTable& asset_ctb, UserInstance const*) const;

    u64 getLifeScale(const ResAssetCallTable& asset_ctb, const UserInstance*) const;

    f32 getOverwriteDelay(u32, const UserInstance*) const;

    const char* getOverwriteBoneName(u32) const override;

    f32 getOverwriteScale(u32, const UserInstance*) const;

    f32 getOverwritePositionX(u32, const UserInstance*) const;
    f32 getOverwritePositionY(u32, const UserInstance*) const;
    f32 getOverwritePositionZ(u32, const UserInstance*) const;

    f32 getOverwriteRotationX(u32, const UserInstance*) const;
    f32 getOverwriteRotationY(u32, const UserInstance*) const;
    f32 getOverwriteRotationZ(u32, const UserInstance*) const;

    f32 getOverwriteColorRed(u32, const UserInstance*) const;
    f32 getOverwriteColorGreen(u32, const UserInstance*) const;
    f32 getOverwriteColorBlue(u32, const UserInstance*) const;
    f32 getOverwriteAlpha(u32, const UserInstance*) const;

    f32 getOverwriteEmissionRate(u32, const UserInstance*) const;

    f32 getDelayWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const override;

    const char* getBoneNameWithOverwrite(const ResAssetCallTable& asset_ctb, u32) const;

    u64 getScaleWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;

    f32 getPositionXWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;
    f32 getPositionYWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;
    f32 getPositionZWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;

    f32 getRotationXWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;
    f32 getRotationYWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;
    f32 getRotationZWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;

    u64 getColorRedWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;
    u64 getColorGreenWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;
    u64 getColorBlueWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;
    f64 getAlphaWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;

    u64 getEmissionRateWithOverwrite(const ResAssetCallTable& asset_ctb, u32, const UserInstance*) const;

    u32 getTriggerOverwriteParamId(u32) const;

    sead::BitFlag32 getAssetBitFlag(const ResAssetCallTable& asset_ctb) const override;

    bool isBoneNameOverwritten(u32) const override;
};
}  // namespace xlink2