#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class ResourceAccessorELink : ResourceAccessor {
public:
    ~ResourceAccessorELink() override;

    bool isBlankAsset(ResAssetCallTable const&) const override;

    const char* getAssetName(ResAssetCallTable const&) const;
    u64 getEsetVal(ResAssetCallTable const&) const;
    const char* getGroupName(ResAssetCallTable const&) const;
    u64 getGroupId(ResAssetCallTable const&) const;
    u64 getClipType(ResAssetCallTable const&) const;

    bool isAutoOneTimeFade(ResAssetCallTable const&) const override;
    bool isForceLoopAsset(ResAssetCallTable const&) const;

    u64 getForceCalc(ResAssetCallTable const&) const;
    u64 getMtxSetType(ResAssetCallTable const&) const;
    f64 getRotateSourceType(ResAssetCallTable const&) const;

    bool isFollow(ResAssetCallTable const&) const;
    bool isUseOneEmitter(ResAssetCallTable const&) const;

    f32 getDelay(ResAssetCallTable const&, UserInstance const*) const;
    f32 getDuration(ResAssetCallTable const&, UserInstance const*) const override;

    const char* getBoneName(ResAssetCallTable const&) const override;

    u64 getScale(ResAssetCallTable const&, UserInstance const*) const;

    f32 getPositionX(ResAssetCallTable const&, UserInstance const*) const;
    f32 getPositionY(ResAssetCallTable const&, UserInstance const*) const;
    f32 getPositionZ(ResAssetCallTable const&, UserInstance const*) const;

    f32 getRotationX(ResAssetCallTable const&, UserInstance const*) const;
    f32 getRotationY(ResAssetCallTable const&, UserInstance const*) const;
    f32 getRotationZ(ResAssetCallTable const&, UserInstance const*) const;

    u64 getColorRed(ResAssetCallTable const&, UserInstance const*) const;
    u64 getColorGreen(ResAssetCallTable const&, UserInstance const*) const;
    u64 getColorBlue(ResAssetCallTable const&, UserInstance const*) const;
    f64 getAlpha(ResAssetCallTable const&, UserInstance const*) const;

    u64 getEmissionRate(ResAssetCallTable const&, UserInstance const*) const;
    u64 getEmissionScale(ResAssetCallTable const&, UserInstance const*) const;
    u64 getEmissionInterval(ResAssetCallTable const&, UserInstance const*) const;

    u64 getDirectionalVel(ResAssetCallTable const&, UserInstance const*) const;

    u64 getLifeScale(ResAssetCallTable const&, UserInstance const*) const;

    f32 getOverwriteDelay(u32, UserInstance const*) const;

    const char* getOverwriteBoneName(u32) const override;

    f32 getOverwriteScale(u32, UserInstance const*) const;

    f32 getOverwritePositionX(u32, UserInstance const*) const;
    f32 getOverwritePositionY(u32, UserInstance const*) const;
    f32 getOverwritePositionZ(u32, UserInstance const*) const;

    f32 getOverwriteRotationX(u32, UserInstance const*) const;
    f32 getOverwriteRotationY(u32, UserInstance const*) const;
    f32 getOverwriteRotationZ(u32, UserInstance const*) const;

    f32 getOverwriteColorRed(u32, UserInstance const*) const;
    f32 getOverwriteColorGreen(u32, UserInstance const*) const;
    f32 getOverwriteColorBlue(u32, UserInstance const*) const;
    f32 getOverwriteAlpha(u32, UserInstance const*) const;

    f32 getOverwriteEmissionRate(u32, UserInstance const*) const;

    f32 getDelayWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const override;

    const char* getBoneNameWithOverwrite(ResAssetCallTable const&, u32) const;

    u64 getScaleWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;

    f32 getPositionXWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getPositionYWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getPositionZWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;

    f32 getRotationXWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getRotationYWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getRotationZWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;

    u64 getColorRedWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u64 getColorGreenWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u64 getColorBlueWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f64 getAlphaWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;

    u64 getEmissionRateWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;

    u32 getTriggerOverwriteParamId(u32) const;

    s32 getAssetBitFlag(ResAssetCallTable const&) const override;

    bool isBoneNameOverwritten(u32) const override;
};
}  // namespace xlink2