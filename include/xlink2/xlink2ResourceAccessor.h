#pragma once

#include <prim/seadBitFlag.h>

#include "math/seadMathCalcCommon.h"
#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ParamValueType.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResContainerParam.h"
#include "xlink2/xlink2ResCurveCallTable.h"
#include "xlink2/xlink2ResParam.h"
#include "xlink2/xlink2ResRandomCallTable.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2ValueReferenceType.h"

namespace xlink2 {
class UserInstance;
class System;
class ContainerBase;

class ResourceAccessor {
public:
    virtual ~ResourceAccessor() = 0;
    virtual bool isBlankAsset(const ResAssetCallTable&) const = 0;
    virtual const char* getBoneName(const ResAssetCallTable&) const = 0;
    virtual bool isBoneNameOverwritten(u32) const = 0;
    virtual const char* getOverwriteBoneName(u32) const = 0;
    virtual bool isAutoOneTimeFade(const ResAssetCallTable&) const = 0;
    virtual bool isForceBoolAsset(const ResAssetCallTable&) const = 0;
    virtual f32 getDelayWithOverwrite(const ResAssetCallTable&, u32, UserInstance const*) const = 0;
    virtual f32 getDuration(const ResAssetCallTable&, UserInstance const*) const = 0;
    virtual s32 getTriggerOverwriteParamId_(u32) const = 0;
    virtual sead::BitFlag32 getAssetBitFlag_(const ResAssetCallTable&) const = 0;

    const ResAssetCallTable* searchCallTable(char const*) const;
    void searchCallTable(Locator*, char const*) const;

    const ResAssetCallTable* getCallTable(u32) const;

    void setError_(char const*, ...) const;

    const char* getKeyName(const ResAssetCallTable&) const;

    ContainerType getCallTableType(const ResAssetCallTable&) const;

    const ContainerBase* getContainer(ResAssetCallTable const&) const;

    const sead::SafeString* getCallTableTypeName(const ResAssetCallTable&) const;

    bool isContainer(const ResAssetCallTable&) const;

    const char* getCustomParamValueString(u32, const ResAssetCallTable&) const;

    bool checkAndErrorIsAsset_(const ResAssetCallTable&, const char*, ...) const;

    const ResParam* getResParamFromAssetParamPos(u32, u32) const;

    const char* getResParamValueString_(const ResParam&) const;

    bool getCustomParamValueBool(u32, const ResAssetCallTable&) const;

    s32 getResParamValueInt_(const ResParam&) const;
    s32 getCustomParamValueInt(u32, const ResAssetCallTable&) const;
    
    f32 getCustomParamValueFloat(u32, const ResAssetCallTable&, const UserInstance*) const;
    f32 getResParamValueFloat_(const ResParam&, const UserInstance*) const;

    const char* getCustomParamValueString(const char*, const ResAssetCallTable&) const;
    bool getCustomParamValueBool(const char*, const ResAssetCallTable&) const;
    s32 getCustomParamValueInt(const char*, const ResAssetCallTable&) const;
    f32 getCustomParamValueFloat(const char*, const ResAssetCallTable&, const UserInstance*) const;

    bool isCustomParamString(u32) const;
    bool isCustomParamString(const char*) const;

    bool isCustomParamBool(u32) const;
    bool isCustomParamBool(const char*) const;

    bool isCustomParamInt(u32) const;
    bool isCustomParamInt(const char*) const;

    bool isCustomParamFloat(u32) const;
    bool isCustomParamFloat(const char*) const;

    bool isCustomParamValueUsingCurve(u32, const ResAssetCallTable&) const;

    bool isParamTypeEqual(ValueReferenceType, const ResAssetCallTable&, u32) const;

    const char* getUserCustomParamValueString(s32) const;
    bool isOutOfRangeUserCustom_(u32) const;
    bool isMismatchTypeUserCustom_(u32, ParamValueType, const char*) const;

    bool getUserCustomParamValueBool(s32) const;
    s32 getUserCustomParamValueInt(s32) const;
    f32 getUserCustomParamValueFloat(s32, const UserInstance*) const;

    const char* getUserCustomParamValueString(const char*) const;
    bool isOutOfRangeUserCustom_(const char*) const;
    bool isMismatchTypeUserCustom_(const char*, ParamValueType, const char*) const;

    bool getUserCustomParamValueBool(const char*) const;
    s32 getUserCustomParamValueInt(const char*) const;
    f32 getUserCustomParamValueFloat(const char*, const UserInstance*) const;

    bool isLoopAsset(const ResAssetCallTable&) const;
    bool isNeedObserve(const ResAssetCallTable&) const;

    ParamValueType getParamType(const ResAssetCallTable&, u32) const;

    const ResCurveCallTable* getCurveCallTable(const ResAssetCallTable&, u32) const;
    const ResRandomCallTable* getRandomCallTable(const ResAssetCallTable&, u32) const;

    f32 getCurveValue(const ResCurveCallTable&, const UserInstance*) const;

    f32 getRandomValue(const ResRandomCallTable&) const;
    f32 getRandomValue(const ResRandomCallTable&, f32) const;
    f32 getRandomValueWeightMin(const ResRandomCallTable&, f32) const;
    f32 getRandomValueWeightMax(const ResRandomCallTable&, f32) const;

    s32 getContainerChildNum(const ResAssetCallTable&) const;
    s32 getContainerChildNum(const ResContainerParam&) const;
    u64 getContainerChildCallTable(const ResContainerParam&, u32) const;

    bool isParamOverwritten(u32, u32) const;
    bool isOverwriteParamTypeEqual(ValueReferenceType, ResTriggerOverwriteParam const&, u32) const;

    const ResParam* getResParamFromOverwriteParamPos_(u32, u32) const;

    const ResRandomCallTable* getResRandomCallTable_(const ResParam&) const;

    f32 getResOverwriteParamValueFloat_(u32, u32, const UserInstance*) const;
    const char* getResOverwriteParamValueString_(u32, u32) const;

protected:
    ResUserHeader* mpUserHeader {nullptr};
    UserResource* mpUserResource {nullptr};
    System* mpSystem {nullptr};

    const char* getResParamValueString(const char* func_name, const ResAssetCallTable& asset_ctb, s32 param_idx, const char* fallback) const
    {
        if (!checkAndErrorIsAsset_(asset_ctb, func_name))
            return fallback;

        const ResParam* asset_param {getResParamFromAssetParamPos(asset_ctb.paramStartPos, param_idx)};
        if (asset_param != nullptr)
            return getResParamValueString_(*asset_param);

        return mpSystem->getParamDefineTable()->getAssetParamDefaultValueString(param_idx);
    }

    s32 getResParamValueInt(const char* func_name, const ResAssetCallTable& asset_ctb, s32 param_idx, s32 fallback) const
    {
        if (!checkAndErrorIsAsset_(asset_ctb, func_name))
            return fallback;
    
        const ResParam* asset_param {getResParamFromAssetParamPos(asset_ctb.paramStartPos, param_idx)};
        if (asset_param != nullptr)
            return getResParamValueInt_(*asset_param);

        return mpSystem->getParamDefineTable()->getAssetParamDefaultValueInt(param_idx);
    }

    f32 getResParamValueFloat(const char* func_name, const ResAssetCallTable& asset_ctb, 
                              s32 param_idx, f32 fallback, const UserInstance* user_instance) const
    {
        if (!checkAndErrorIsAsset_(asset_ctb, func_name))
            return fallback;
    
        const ResParam* asset_param {getResParamFromAssetParamPos(asset_ctb.paramStartPos, param_idx)};
        if (asset_param != nullptr)
            return getResParamValueFloat_(*asset_param, user_instance);
        
        return mpSystem->getParamDefineTable()->getAssetParamDefaultValueFloat(param_idx);
    }
    
    f32 getResParamValueFloatWithLowerLimit(const char* func_name, const ResAssetCallTable& asset_ctb, 
                                       s32 param_idx, f32 fallback, const UserInstance* user_instance) const
    {
        f32 param_value {fallback};
        if (!checkAndErrorIsAsset_(asset_ctb, func_name))
            return param_value;
        
        const ResParam* asset_param {getResParamFromAssetParamPos(asset_ctb.paramStartPos, param_idx)};
        if (asset_param != nullptr)
            param_value = getResParamValueFloat_(*asset_param, user_instance);
        else
            param_value = mpSystem->getParamDefineTable()->getAssetParamDefaultValueFloat(param_idx);

        return sead::MathCalcCommon<f32>::max(param_value, 0.0);
    }

    f32 getResOverwriteParamValueFloatWithLimit(u32 idx, u32 define_idx, const UserInstance* user_instance) const
    {
        f32 param_value {getResOverwriteParamValueFloat_(idx, define_idx, user_instance)};
        return sead::MathCalcCommon<float>::max(param_value, 0.0);
    }
};
}  // namespace xlink2