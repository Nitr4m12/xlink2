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
    s32 getUserLimitType() const;
    s32 getUserPlayableLimitNum() const;
    s32 getUserPriority() const;
    bool isUserNoPos() const;
    s32 getUserDopplerFactor() const;

    bool isBlankAsset(const ResAssetCallTable& asset_ctb) const override;
    const char* getAssetName(const ResAssetCallTable& asset_ctb) const;

    const char* getGroupName(const ResAssetCallTable& asset_ctb) const;

    bool isFollow(const ResAssetCallTable& asset_ctb) const;
    bool isNoParamUpdate(const ResAssetCallTable& asset_ctb) const;
    bool isNoPos(const ResAssetCallTable& asset_ctb) const;
    bool isStopWhenEmitterDestroying(const ResAssetCallTable& asset_ctb) const;
    bool isUnified(const ResAssetCallTable& asset_ctb) const;
    bool isAutoOneTimeFade(const ResAssetCallTable& asset_ctb) const override;
    bool isForceLoopAsset(const ResAssetCallTable& asset_ctb) const;

    f32 getVolume(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getVolumeTv(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getVolumeDrc(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getPitch(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getLpf(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getStopFrame(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getFadeInTime(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getFadeCurveType(const ResAssetCallTable& asset_ctb);
    f32 getDelay(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getDuration(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const override;
    f32 getPriority(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    f32 getDopplerFactor(const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const;
    const char* getBoneName(const ResAssetCallTable& asset_ctb) const override;
    const char* getDistanceParamSetName(const ResAssetCallTable& asset_ctb) const;

    f32 getOverwriteVolume(u32 idx, const UserInstance* user_instance) const;
    f32 getOverwritePitch(u32 idx, const UserInstance* user_instance) const;
    f32 getOverwriteLpf(u32 idx, const UserInstance* user_instance) const;
    f32 getOverwriteStopFrame(u32 idx, const UserInstance* user_instance) const;
    f32 getOverwriteFadeInTime(u32 idx, const UserInstance* user_instance) const;
    f32 getOverwriteDelay(u32 idx, const UserInstance* user_instance) const;
    f32 getOverwritePriority(u32 idx, const UserInstance* user_instance) const;
    const char* getOverwriteBoneName(u32 idx) const override;

    f32 getVolumeWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const;
    f32 getPitchWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const;
    f32 getLpfWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance);
    f32 getStopFrameWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const;
    f32 getFadeInTimeWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, UserInstance*) const;
    f32 getDelayWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const override;
    f32 getPriorityWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx, const UserInstance* user_instance) const;
    const char* getBoneNameWithOverwrite(const ResAssetCallTable& asset_ctb, u32 idx) const;

    s32 getTriggerOverwriteParamId_(u32 idx) const override;

    sead::BitFlag32 getAssetBitFlag_(const ResAssetCallTable& asset_ctb) const override;

    bool isBoneNameOverwritten(u32 idx) const override;
};
}  // namespace xlink2