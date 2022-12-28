#pragma once

#include "xlink2/xlink2.h"
#include "xlink2/xlink2Locator.h"

namespace xlink2 {
class ResourceAccessor {
    virtual ~ResourceAccessor();

public:
    void checkAndErrorIsAsset(ResAssetCallTable const&, char const*) const;
    u64 getCallTable(u32) const;
    s32 getCallTableType(ResAssetCallTable const&) const;
    char* getCallTableTypeName(ResAssetCallTable const&) const;
    u64 getContainer(ResAssetCallTable const&) const;
    u64 getContainerChildCallTable(ResContainerParam const&, u32) const;
    s32 getContainerChildNum(ResAssetCallTable const&) const;
    s32 getContainerChildNum(ResContainerParam const&) const;
    void* getCurveCallTable(ResAssetCallTable const&, u32) const;
    f32 getCurveValue(ResCurveCallTable const&, UserInstance const*);
    bool getCustomParamValueBool(u32, ResAssetCallTable const&) const;
    bool getCustomParamValueBool(char const*, ResAssetCallTable const&) const;
    f64 getCustomParamValueFloat(u32, ResAssetCallTable const&, UserInstance const*) const;
    f64 getCustomParamValueFloat(char const*, ResAssetCallTable const&, UserInstance const*) const;
    u64 getCustomParamValueInt(u32, ResAssetCallTable const&) const;
    u64 getCustomParamValueInt(char const*, ResAssetCallTable const&) const;
    char* getCustomValueString(u32, ResAssetCallTable const&) const;
    char* getCustomValueString(char const*, ResAssetCallTable const&) const;
    char* getKeyName(ResAssetCallTable const&) const;
    char* getParamType(ResAssetCallTable const&, u32) const;
    void* getRandomCallTable(ResAssetCallTable const&, u32) const;
    f32 getRandomValue(ResRandomCallTable const&) const;
    f32 getRandomValue(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMax(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMin(ResRandomCallTable const&, f32) const;
    f64 getResOverwriteParamValueFloat(u32, u32, UserInstance const*) const;
    char* getResOverwriteParamValueString(u32, u32) const;
    s64 getResParamFromAssetParamPos(u32, u32) const;
    s64 getResParamFromOverwriteParamPos(u32, u32) const;
    f64 getResParamValueFloat(ResParam const&, UserInstance const*) const;
    u32 getResParamValueInt(ResParam const&) const;
    char* getResParamValueString(ResParam const&) const;
    s64 getResRandomCallTable(ResParam const&) const;
    bool getUserCustomParamValueBool(int) const;
    bool getUserCustomParamValueBool(char const*) const;
    f32 getUserCustomParamValueFloat(int, UserInstance const*);
    f32 getUserCustomParamValueFloat(char const*, UserInstance const*);
    u32 getUserCustomParamValueInt(int) const;
    u32 getUserCustomParamValueInt(char const*) const;
    char* getUserCustomParamValueString(int) const;
    char* getUserCustomParamValueString(char const*) const;
    bool isContainer(ResAssetCallTable const&) const;
    bool isCustomParamBool(u32) const;
    bool isCustomParamBool(char const*) const;
    bool isCustomParamFloat(u32) const;
    bool isCustomParamFloat(char const*) const;
    bool isCustomParamInt(u32) const;
    bool isCustomParamInt(char const*) const;
    bool isCustomParamString(u32) const;
    bool isCustomParamString(char const*) const;
    bool isCustomParamValueUsingCurve(u32, ResAssetCallTable const&) const;
    bool isLoopAsset(ResAssetCallTable const&) const;
    bool isMismatchTypeUserCustom(u32, ParamValueType, char const*) const;
    bool isMismatchTypeUserCustom(char const*, ParamValueType, char const*) const;
    bool isNeedObserve(ResAssetCallTable const&) const;
    bool isOutOfRangeUserCustom(u32) const;
    bool isOutOfRangeUserCustom(char*) const;
    bool isOverwriteParamTypeEqual(ValueReferenceType, ResTriggerOverwriteParam const&, u32) const;
    bool isParamOverwritten(u32, u32) const;
    bool isParamTypeEqual(ValueReferenceType, ResAssetCallTable const&, u32) const;
    void searchCallTable(char const*) const;
    void searchCallTable(Locator*, char const*) const;
    void setError(char const*, ...) const;

private:
};

class ResourceAccessor2 {
public:
    f32 getCurveValue(ResParam const&) const;
    f32 getRandomValue(ResRandomCallTable const&) const;
    f32 getRandomValue(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMax(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMin(ResRandomCallTable const&, f32) const;
    s64 getResRandomCallTable(ResParam const&) const;

private:
};

class ResourceAccessorELink {
    virtual ~ResourceAccessorELink();

public:
    f64 getAlpha(ResAssetCallTable const&, UserInstance const*) const;
    f64 getAlphaWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u32 getAssetBitFlag(ResAssetCallTable const&) const;
    char* getAssetName(ResAssetCallTable const&) const;
    char* getBoneName(ResAssetCallTable const&) const;
    char* getBoneNameWithOverwrite(ResAssetCallTable const&, u32) const;
    u64 getClipType(ResAssetCallTable const&) const;
    u64 getColorBlue(ResAssetCallTable const&, UserInstance const*) const;
    u64 getColorBlueWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u64 getColorGreen(ResAssetCallTable const&, UserInstance const*) const;
    u64 getColorGreenWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u64 getColorRed(ResAssetCallTable const&, UserInstance const*) const;
    u64 getColorRedWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getDelay(ResAssetCallTable const&, UserInstance const*) const;
    f32 getDelayWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u64 getDirectionalVel(ResAssetCallTable const&, UserInstance const*) const;
    u64 getDuration(ResAssetCallTable const&, UserInstance const*) const;
    u64 getEmissionInterval(ResAssetCallTable const&, UserInstance const*) const;
    u64 getEmissionRate(ResAssetCallTable const&, UserInstance const*) const;
    u64 getEmissionRateWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u64 getEmissionScale(ResAssetCallTable const&, UserInstance const*) const;
    u64 getEsetVal(ResAssetCallTable const&) const;
    u64 getForceCalc(ResAssetCallTable const&) const;
    u64 getGroupId(ResAssetCallTable const&) const;
    char* getGroupName(ResAssetCallTable const&) const;
    u64 getLifeScale(ResAssetCallTable const&, UserInstance const*) const;
    u64 getMtxSetType(ResAssetCallTable const&) const;
    void getOverwriteAlpha(u32, UserInstance const*);
    char* getOverwriteBoneName(u32) const;
    void getOverwriteColorBlue(u32, UserInstance const*) const;
    void getOverwriteColorGreen(u32, UserInstance const*) const;
    void getOverwriteColorRed(u32, UserInstance const*) const;
    f32 getOverwriteDelay(u32, UserInstance const*) const;
    f32 getOverwriteEmissionRate(u32, UserInstance const*) const;
    f32 getOverwritePositionX(u32, UserInstance const*) const;
    f32 getOverwritePositionY(u32, UserInstance const*) const;
    f32 getOverwritePositionZ(u32, UserInstance const*) const;
    f32 getOverwriteRotationX(u32, UserInstance const*) const;
    f32 getOverwriteRotationY(u32, UserInstance const*) const;
    f32 getOverwriteRotationZ(u32, UserInstance const*) const;
    f32 getOverwriteScale(u32, UserInstance const*) const;
    f32 getPositionX(ResAssetCallTable const&, UserInstance const*) const;
    f32 getPositionXWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getPositionY(ResAssetCallTable const&, UserInstance const*) const;
    f32 getPositionYWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getPositionZ(ResAssetCallTable const&, UserInstance const*) const;
    f32 getPositionZWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f64 getRotateSourceType(ResAssetCallTable const&) const;
    f32 getRotationX(ResAssetCallTable const&, UserInstance const*) const;
    f32 getRotationXWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getRotationY(ResAssetCallTable const&, UserInstance const*) const;
    f32 getRotationYWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getRotationZ(ResAssetCallTable const&, UserInstance const*) const;
    f32 getRotationZWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u64 getScale(ResAssetCallTable const&, UserInstance const*) const;
    u64 getScaleWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u32 getTriggerOverwriteParamId(u32) const;
    bool isAutoOneTimeFade(ResAssetCallTable const&) const;
    bool isBlankAsset(ResAssetCallTable const&) const;
    bool isBoneNameOverwritten(u32) const;
    bool isFollow(ResAssetCallTable const&) const;
    bool isForceLoopAsset(ResAssetCallTable const&) const;
    bool isUseOneEmitter(ResAssetCallTable const&) const;

private:
};

class ResourceAccessorSLink {
    virtual ~ResourceAccessorSLink();
public:
    u32 getAssetBitFlag(ResAssetCallTable const&) const;
    char* getAssetName(ResAssetCallTable const&) const;
    char* getBoneName(ResAssetCallTable const&) const;
    char* getBoneNameWithOverwrite(ResAssetCallTable const&, u32) const;
    f32 getDelay(ResAssetCallTable const&, UserInstance const*) const;
    f32 getDelayWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    char* getDistanceParamSetName(ResAssetCallTable const&) const;
    u64 getDopplerFactor(ResAssetCallTable const&, UserInstance const*) const;
    f32 getDuration(ResAssetCallTable const&, UserInstance const*) const;
    u32 getFadeCurveType(ResAssetCallTable const&);
    u64 getFadeInTime(ResAssetCallTable const&, UserInstance*) const;
    u64 getFadeInTimeWithOverwrite(ResAssetCallTable const&, u32, UserInstance*) const;
    char* getGroupName(ResAssetCallTable const&) const;
    u64 getLpf(ResAssetCallTable const&, UserInstance const*) const;
    u64 getLpf(ResAssetCallTable const&, u32, UserInstance const*) const;
    char* getOverwriteBoneName(u32) const;
    f32 getOverwriteDelay(u32, UserInstance const*) const;
    u64 getOverwriteFadeInTime(u32, UserInstance const*) const;
    u64 getOverwriteLpf(u32, UserInstance const*) const;
    u64 getOverwritePitch(u32, UserInstance const*) const;
    u64 getOverwritePriority(u32, UserInstance const*) const;
    u64 getOverwriteStopFrame(u32, UserInstance const*) const;
    u64 getOverwriteVolume(u32, UserInstance const*) const;
    f32 getPitch(ResAssetCallTable const&, UserInstance const*) const;
    f32 getPitchWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getPriority(ResAssetCallTable const&, UserInstance const*) const;
    f32 getPriorityWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    f32 getStopFrame(ResAssetCallTable const&, UserInstance const*) const;
    f32 getStopFrameWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    u32 getTriggerOverwriteParamId(u32) const;
    char* getUserDistanceParamSetName() const;
    u32 getUserDopplerFactor() const;
    u32 getUserLimitType() const;
    u32 getUserPlayableLimitNum() const;
    u32 getUserPriority() const;
    f32 getVolume(ResAssetCallTable const&, UserInstance const*) const;
    f32 getVolumeDrc(ResAssetCallTable const&, UserInstance const*) const;
    f32 getVolumeTv(ResAssetCallTable const&, UserInstance const*) const;
    f32 getVolumeWithOverwrite(ResAssetCallTable const&, u32, UserInstance const*) const;
    bool isAutoOneTimeFade(ResAssetCallTable const&) const;
    bool isBlankAsset(ResAssetCallTable const&) const;
    bool isBoneNameOverwritten(u32) const;
    bool isFollow(ResAssetCallTable const&) const;
    bool isForceLoopAsset(ResAssetCallTable const&) const;
    bool isNoParamUpdate(ResAssetCallTable const&) const;
    bool isNoPos(ResAssetCallTable const&) const;
    bool isStopWhenEmitterDestroying(ResAssetCallTable const&) const;
    bool isUnified(ResAssetCallTable const&) const;
    bool isUserNoPos() const;

private:
};
}  // namespace xlink2