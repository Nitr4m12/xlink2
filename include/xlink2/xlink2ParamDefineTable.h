#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ResParam.h"

namespace xlink2 {
class ParamDefineTable {
public:
    void reset();
    void setup(u8*, u32, bool);
    void dump_();

    char* getUserParamName(u32) const;
    char* getAssetParamName(u32) const;
    char* getTriggerParamName(u32) const;

    u64 searchAssetParamIdxFromCustomParamName(char const*) const;
    u64 searchUserParamIdxFromCustomParamName(char const*) const;

    u32 getUserParamType(u32) const;
    u32 getAssetParamType(u32) const;
    u32 getTriggerParamType(u32) const;

    s32 getUserParamDefaultValueInt(u32) const;
    f32 getUserParamDefaultValueFloat(u32) const;
    char* getUserParamDefaultValueString(u32) const;

    s32 getAssetParamDefaultValueInt(u32) const;
    f32 getAssetParamDefaultValueFloat(u32) const;
    char* getAssetParamDefaultValueString(u32) const;

    s32 getTriggerParamDefaultValueInt(u32) const;
    f32 getTriggerParamDefaultValueFloat(u32) const;
    char* getTriggerParamDefaultValueString(u32) const;

    u32 getSize() const { return mSize; }
    u32 getAssetParamNum() const { return mNumAssetParam; }
    u32 getUserParamNum() const { return mNumUserParam; }
    u32 get0() const { return _0; }

private:
    u32 mNumUserParam;
    u32 mNumAssetParam;
    u32 mNumTriggerParam;
    ResParam* mUserParams;
    ResParam* mAssetParams;
    ResParam* mTriggerParams;
    u32 mStringTablePos;
    u32 _0;
    u32 mNumUserAssetParam;
    u32 mNumStandardAssetParam;
    u32 mNumNonUserParam;
    u32 mSize;
    bool mInitialized;
};

static_assert(sizeof(ParamDefineTable) == 0x48, "Wrong size for 'xlink2::ParamDefineTable'");
}  // namespace xlink2