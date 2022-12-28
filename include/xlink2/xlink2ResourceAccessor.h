#pragma once

#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ParamValueType.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResContainerParam.h"
#include "xlink2/xlink2ResCurveCallTable.h"
#include "xlink2/xlink2ResParam.h"
#include "xlink2/xlink2ResRandomCallTable.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2ValueReferenceType.h"

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
}  // namespace xlink2