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
class UserResource;
class UserInstance;
class System;

class ResourceAccessor {
public:
    virtual ~ResourceAccessor();

    void searchCallTable(char const*) const;
    void searchCallTable(Locator*, char const*) const;


    ResAssetCallTable* getCallTable(u32 num_call_table) const;

    void setError_(char const*, ...) const;

    char* getKeyName(ResAssetCallTable const&) const;
    s32 getCallTableType(ResAssetCallTable const&) const;
    u64 getContainer(ResAssetCallTable const&) const;
    char* getCallTableTypeName(ResAssetCallTable const&) const;
    bool isContainer(ResAssetCallTable const&) const;
    char* getCustomParamValueString(u32, ResAssetCallTable const&) const;

    void checkAndErrorIsAsset_(ResAssetCallTable const&, char const*) const;

    s64 getResParamFromAssetParamPos(u32, u32) const;
    char* getResParamValueString_(ResParam const&) const;

    bool getCustomParamValueBool(u32, ResAssetCallTable const&) const;

    u32 getResParamValueInt_(ResParam const&) const;
    u64 getCustomParamValueInt(u32, ResAssetCallTable const&) const;

    f64 getCustomParamValueFloat(u32, ResAssetCallTable const&,
                                 UserInstance const*) const;
    f64 getResParamValueFloat_(ResParam const&, UserInstance const*) const;

    char* getCustomParamValueString(char const*, ResAssetCallTable const&) const;
    bool getCustomParamValueBool(char const*, ResAssetCallTable const&) const;
    u64 getCustomParamValueInt(char const*, ResAssetCallTable const&) const;
    f64 getCustomParamValueFloat(char const*, ResAssetCallTable const&,
                                 UserInstance const*) const;

    bool isCustomParamString(u32) const;
    bool isCustomParamString(char const*) const;

    bool isCustomParamBool(u32) const;
    bool isCustomParamBool(char const*) const;

    bool isCustomParamInt(u32) const;
    bool isCustomParamInt(char const*) const;

    bool isCustomParamFloat(u32) const;
    bool isCustomParamFloat(char const*) const;

    bool isCustomParamValueUsingCurve(u32, ResAssetCallTable const&) const;

    bool isParamTypeEqual(ValueReferenceType, ResAssetCallTable const&, u32) const;

    char* getUserCustomParamValueString(s32) const;
    bool isOutOfRangeUserCustom_(u32) const;
    bool isMismatchTypeUserCustom_(u32, ParamValueType, char const*) const;

    bool getUserCustomParamValueBool(s32) const;
    u32 getUserCustomParamValueInt(s32) const;
    f32 getUserCustomParamValueFloat(s32, UserInstance const*);

    char* getUserCustomParamValueString(char const*) const;
    bool isOutOfRangeUserCustom_(char*) const;
    bool isMismatchTypeUserCustom_(char const*, ParamValueType, char const*) const;

    bool getUserCustomParamValueBool(char const*) const;
    u32 getUserCustomParamValueInt(char const*) const;
    f32 getUserCustomParamValueFloat(char const*, UserInstance const*);

    bool isLoopAsset(ResAssetCallTable const&) const;
    bool isNeedObserve(ResAssetCallTable const&) const;

    char* getParamType(ResAssetCallTable const&, u32) const;

    void* getCurveCallTable(ResAssetCallTable const&, u32) const;
    void* getRandomCallTable(ResAssetCallTable const&, u32) const;

    f32 getCurveValue(ResCurveCallTable const&, UserInstance const*);

    f32 getRandomValue(ResRandomCallTable const&) const;
    f32 getRandomValue(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMin(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMax(ResRandomCallTable const&, f32) const;

    s32 getContainerChildNum(ResAssetCallTable const&) const;
    s32 getContainerChildNum(ResContainerParam const&) const;
    u64 getContainerChildCallTable(ResContainerParam const&, u32) const;

    bool isParamOverwritten(u32, u32) const;
    bool isOverwriteParamTypeEqual(ValueReferenceType, ResTriggerOverwriteParam const&, u32) const;

    s64 getResParamFromOverwriteParamPos_(u32, u32) const;

    s64 getResRandomCallTable_(ResParam const&) const;

    f32 getResOverwriteParamValueFloat_(u32, u32, UserInstance const*) const;
    char* getResOverwriteParamValueString_(u32, u32) const;

private:
    void* _0;
    UserResource* mUserResource;
    System* mSystem;
};
}  // namespace xlink2