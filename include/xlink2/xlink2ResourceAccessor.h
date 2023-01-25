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
    void checkAndErrorIsAsset(ResAssetCallTable const&, char const*) const;

    ResAssetCallTable* getCallTable(u32 num_call_table) const;
    s32 getCallTableType(ResAssetCallTable const&) const;
    char* getCallTableTypeName(ResAssetCallTable const&) const;

    u64 getContainer(ResAssetCallTable const&) const;
    u64 getContainerChildCallTable(ResContainerParam const&, u32) const;
    s32 getContainerChildNum(ResAssetCallTable const&) const;
    s32 getContainerChildNum(ResContainerParam const&) const;

    void* getCurveCallTable(ResAssetCallTable const&, u32) const;
    f32 getCurveValue(ResCurveCallTable const&, UserInstance const*);

    bool getCustomParamValueBool(u32 custom_param_idx, ResAssetCallTable const&) const;
    bool getCustomParamValueBool(char const* param_name, ResAssetCallTable const&) const;

    f64 getCustomParamValueFloat(u32 custom_param_idx, ResAssetCallTable const&,
                                 UserInstance const*) const;
    f64 getCustomParamValueFloat(char const* param_name, ResAssetCallTable const&,
                                 UserInstance const*) const;

    u64 getCustomParamValueInt(u32 custom_param_idx, ResAssetCallTable const&) const;
    u64 getCustomParamValueInt(char const* param_name, ResAssetCallTable const&) const;

    char* getCustomParamValueString(u32 custom_param_idx, ResAssetCallTable const&) const;
    char* getCustomParamValueString(char const* param_name, ResAssetCallTable const&) const;

    char* getKeyName(ResAssetCallTable const&) const;

    char* getParamType(ResAssetCallTable const&, u32) const;

    void* getRandomCallTable(ResAssetCallTable const&, u32) const;
    f32 getRandomValue(ResRandomCallTable const&) const;
    f32 getRandomValue(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMax(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMin(ResRandomCallTable const&, f32) const;

    f32 getResOverwriteParamValueFloat(u32, u32, UserInstance const*) const;

    char* getResOverwriteParamValueString(u32, u32) const;

    s64 getResParamFromAssetParamPos(u32, u32) const;
    s64 getResParamFromOverwriteParamPos(u32, u32) const;
    f64 getResParamValueFloat(ResParam const& reference_type, UserInstance const*) const;
    u32 getResParamValueInt(ResParam const& reference_type) const;
    char* getResParamValueString(ResParam const& reference_type) const;

    s64 getResRandomCallTable(ResParam const& reference_type) const;

    bool getUserCustomParamValueBool(s32 user_custom_param_idx) const;
    bool getUserCustomParamValueBool(char const* user_param_name) const;

    f32 getUserCustomParamValueFloat(s32 user_custom_param_idx, UserInstance const*);
    f32 getUserCustomParamValueFloat(char const* user_param_name, UserInstance const*);

    u32 getUserCustomParamValueInt(s32 user_custom_param_idx) const;
    u32 getUserCustomParamValueInt(char const* user_param_name) const;

    char* getUserCustomParamValueString(s32 user_custom_param_idx) const;
    char* getUserCustomParamValueString(char const* user_param_name) const;

    bool isContainer(ResAssetCallTable const&) const;

    bool isCustomParamBool(u32 custom_param_idx) const;
    bool isCustomParamBool(char const* param_name) const;

    bool isCustomParamFloat(u32 custom_param_idx) const;
    bool isCustomParamFloat(char const* param_name) const;

    bool isCustomParamInt(u32 custom_param_idx) const;
    bool isCustomParamInt(char const* param_name) const;

    bool isCustomParamString(u32 custom_param_idx) const;
    bool isCustomParamString(char const* param_name) const;

    bool isCustomParamValueUsingCurve(u32 custom_param_idx, ResAssetCallTable const&) const;

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
    void* _0;
    UserResource* mUserResource;
    System* mSystem;
};
}  // namespace xlink2