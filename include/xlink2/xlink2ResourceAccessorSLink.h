#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class ResourceAccessorSLink : ResourceAccessor {

public:
    ~ResourceAccessorSLink() override;

    const char* getUserDistanceParamSetName() const;
    u32 getUserLimitType() const;
    u32 getUserPlayableLimitNum() const;
    u32 getUserPriority() const;

    bool isUserNoPos() const;

    u32 getUserDopplerFactor() const;

    bool isBlankAsset(ResAssetCallTable const&) const override;
    const char* getAssetName(ResAssetCallTable const&) const;

    const char* getGroupName(ResAssetCallTable const&) const;

    bool isFollow(ResAssetCallTable const&) const;
    bool isNoParamUpdate(ResAssetCallTable const&) const;
    bool isNoPos(ResAssetCallTable const&) const;
    bool isStopWhenEmitterDestroying(ResAssetCallTable const&) const;
    bool isUnified(ResAssetCallTable const&) const;
    bool isAutoOneTimeFade(ResAssetCallTable const&) const override;
    bool isForceLoopAsset(ResAssetCallTable const&) const;

    f32 getVolume(ResAssetCallTable const&, UserInstance const*) const;
    f32 getVolumeTv(ResAssetCallTable const&, UserInstance const*) const;
    f32 getVolumeDrc(ResAssetCallTable const&, UserInstance const*) const;
    f32 getPitch(ResAssetCallTable const&, UserInstance const*) const;
    u64 getLpf(ResAssetCallTable const&, UserInstance const*) const;
    f32 getStopFrame(ResAssetCallTable const&, UserInstance const*) const;
    u64 getFadeInTime(ResAssetCallTable const&, UserInstance*) const;
    u32 getFadeCurveType(ResAssetCallTable const&);
    f32 getDelay(ResAssetCallTable const&, UserInstance const*) const;
    f32 getDuration(ResAssetCallTable const&, UserInstance const*) const override;
    f32 getPriority(ResAssetCallTable const&, UserInstance const*) const;
    u64 getDopplerFactor(ResAssetCallTable const&, UserInstance const*) const;
    const char* getBoneName(ResAssetCallTable const&) const override;
    const char* getDistanceParamSetName(ResAssetCallTable const&) const;

    u64 getOverwriteVolume(u32, UserInstance const*) const;
    u64 getOverwritePitch(u32, UserInstance const*) const;
    u64 getOverwriteLpf(u32, UserInstance const*) const;
    u64 getOverwriteStopFrame(u32, UserInstance const*) const;
    u64 getOverwriteFadeInTime(u32, UserInstance const*) const;
    f32 getOverwriteDelay(u32, UserInstance const*) const;
    u64 getOverwritePriority(u32, UserInstance const*) const;
    const char* getOverwriteBoneName(u32) const override;

    f32 getVolumeWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getPitchWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getLpfWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*);
    f32 getStopFrameWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u64 getFadeInTimeWithOverwrite(ResAssetCallTable const&, u32, UserInstance*) const;
    f32 getDelayWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const override;
    f32 getPriorityWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    const char* getBoneNameWithOverwrite(ResAssetCallTable const&, u32) const;

    s32 getTriggerOverwriteParamId_(u32) const override;

    sead::BitFlag32 getAssetBitFlag_(ResAssetCallTable const&) const override;

    bool isBoneNameOverwritten(u32) const override;
};
}  // namespace xlink2