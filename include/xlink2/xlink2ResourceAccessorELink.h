#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class ResourceAccessorELink : public ResourceAccessor {
public:
    ~ResourceAccessorELink() override;

    bool isBlankAsset(const ResAssetCallTable& asset_ctb) const override;

    const char* getAssetName(const ResAssetCallTable& asset_ctb) const;
    u64 getEsetVal(const ResAssetCallTable&) const;
    const char* getGroupName(const ResAssetCallTable&) const;
    u64 getGroupId(const ResAssetCallTable&) const;
    u64 getClipType(const ResAssetCallTable&) const;

    bool isAutoOneTimeFade(const ResAssetCallTable&) const override;
    bool isForceLoopAsset(const ResAssetCallTable&) const;

    u64 getForceCalc(const ResAssetCallTable&) const;
    u64 getMtxSetType(const ResAssetCallTable&) const;
    f64 getRotateSourceType(const ResAssetCallTable&) const;

    bool isFollow(const ResAssetCallTable&) const;
    bool isUseOneEmitter(const ResAssetCallTable&) const;

    f32 getDelay(const ResAssetCallTable&, const UserInstance*) const;
    f32 getDuration(const ResAssetCallTable&, const UserInstance*) const override;

    const char* getBoneName(const ResAssetCallTable&) const override;

    u64 getScale(const ResAssetCallTable&, const UserInstance*) const;

    f32 getPositionX(const ResAssetCallTable&, const UserInstance*) const;
    f32 getPositionY(const ResAssetCallTable&, const UserInstance*) const;
    f32 getPositionZ(const ResAssetCallTable&, const UserInstance*) const;

    f32 getRotationX(const ResAssetCallTable&, const UserInstance*) const;
    f32 getRotationY(const ResAssetCallTable&, const UserInstance*) const;
    f32 getRotationZ(const ResAssetCallTable&, const UserInstance*) const;

    u64 getColorRed(const ResAssetCallTable&, const UserInstance*) const;
    u64 getColorGreen(const ResAssetCallTable&, const UserInstance*) const;
    u64 getColorBlue(const ResAssetCallTable&, const UserInstance*) const;
    f64 getAlpha(const ResAssetCallTable&, const UserInstance*) const;

    u64 getEmissionRate(const ResAssetCallTable&, const UserInstance*) const;
    u64 getEmissionScale(const ResAssetCallTable&, const UserInstance*) const;
    u64 getEmissionInterval(const ResAssetCallTable&, const UserInstance*) const;

    u64 getDirectionalVel(const ResAssetCallTable&, UserInstance const*) const;

    u64 getLifeScale(const ResAssetCallTable&, const UserInstance*) const;

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

    f32 getDelayWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const override;

    const char* getBoneNameWithOverwrite(const ResAssetCallTable&, u32) const;

    u64 getScaleWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;

    f32 getPositionXWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;
    f32 getPositionYWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;
    f32 getPositionZWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;

    f32 getRotationXWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;
    f32 getRotationYWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;
    f32 getRotationZWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;

    u64 getColorRedWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;
    u64 getColorGreenWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;
    u64 getColorBlueWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;
    f64 getAlphaWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;

    u64 getEmissionRateWithOverwrite(const ResAssetCallTable&, u32, const UserInstance*) const;

    u32 getTriggerOverwriteParamId(u32) const;

    s32 getAssetBitFlag(const ResAssetCallTable&) const override;

    bool isBoneNameOverwritten(u32) const override;
};
}  // namespace xlink2