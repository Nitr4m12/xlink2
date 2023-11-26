#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ResAssetParam.h"

namespace xlink2 {
class ParamDefineTable {
public:
    void reset();
    void setup(u8*, u32, bool);
    void dump_();

    const char* getUserParamName(u32) const;
    const char* getAssetParamName(u32) const;
    const char* getTriggerParamName(u32) const;

    u32 searchAssetParamIdxFromCustomParamName(char const*) const;
    u32 searchUserParamIdxFromCustomParamName(char const*) const;

    ParamValueType getUserParamType(u32) const;
    ParamValueType getAssetParamType(u32) const;
    ParamValueType getTriggerParamType(u32) const;

    u32 getUserParamDefaultValueInt(u32) const;
    f32 getUserParamDefaultValueFloat(u32) const;
    const char* getUserParamDefaultValueString(u32) const;

    u32 getAssetParamDefaultValueInt(u32) const;
    f32 getAssetParamDefaultValueFloat(u32) const;
    const char* getAssetParamDefaultValueString(u32) const;

    u32 getTriggerParamDefaultValueInt(u32) const;
    f32 getTriggerParamDefaultValueFloat(u32) const;
    const char* getTriggerParamDefaultValueString(u32) const;

    u32 getSize() const { return mSize; }
    u32 getNumAssetParam() const { return mNumAssetParam; }
    u32 getNumUserParam() const { return mNumUserParam; }
    u32 get0() const { return _0; }
    u32 getNumCustomParam() const { return mNumCustomParam; }
    bool isInitilized() const { return mIsInitialized; }

private:
    u32 mNumUserParam;
    u32 mNumAssetParam;
    u32 mNumTriggerParam;
    ResAssetParam* mUserParams;
    ResAssetParam* mAssetParams;
    ResAssetParam* mTriggerParams;
    u32 mStringTablePos;
    u32 _0;
    s32 mNumCustomParam;
    u32 mNumStandardAssetParam;
    u32 mNumNonUserParam;
    u32 mSize;
    bool mIsInitialized;
};
static_assert(sizeof(ParamDefineTable) == 0x48, "Wrong size for 'xlink2::ParamDefineTable'");

}  // namespace xlink2