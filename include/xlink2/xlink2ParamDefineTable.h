#pragma once

#include "xlink2/xlink2Resource.h"

namespace xlink2 {
class ParamDefineTable {
public:
    void reset();
    void setup(u8*, u32, bool);
    void dump_();

    const char* getUserParamName(u32) const;
    const char* getAssetParamName(u32) const;
    const char* getTriggerParamName(u32) const;

    s32 searchAssetParamIdxFromCustomParamName(const char*) const;
    s32 searchUserParamIdxFromCustomParamName(const char*) const;

    ParamValueType getUserParamType(u32) const;
    ParamValueType getAssetParamType(u32) const;
    ParamValueType getTriggerParamType(u32) const;

    s32 getUserParamDefaultValueInt(u32) const;
    f32 getUserParamDefaultValueFloat(u32) const;
    const char* getUserParamDefaultValueString(u32) const;

    s32 getAssetParamDefaultValueInt(u32) const;
    f32 getAssetParamDefaultValueFloat(u32) const;
    const char* getAssetParamDefaultValueString(u32) const;

    s32 getTriggerParamDefaultValueInt(u32) const;
    f32 getTriggerParamDefaultValueFloat(u32) const;
    const char* getTriggerParamDefaultValueString(u32) const;

    u32 getSize() const { return mDataSize; }
    u32 getNumAssetParam() const { return mNumAssetParam; }
    u32 getNumUserParam() const { return mNumUserParam; }
    u32 getNumTriggerParam() const { return mNumTriggerParam; }
    u32 get0() const { return mNumCustomAssetParam; }
    u32 getNumCustomParam() const { return mNumStandardAssetParam; }
    bool isInitialized() const { return mIsInitialized; }
    u32 getNumCustomUserParam() const { return mNumCustomUserParam; }

private:
    u32 mNumUserParam;
    u32 mNumAssetParam;
    u32 mNumTriggerParam;
    ResParamDefine* mpUserParamDefine;
    ResParamDefine* mpAssetParamDefine;
    ResParamDefine* mpTriggerParamDefine;
    u32 mStringTablePos;
    u32 mNumCustomAssetParam;
    u32 mNumStandardAssetParam;
    u32 mNumStandardUserParam;
    u32 mNumCustomUserParam;
    u32 mDataSize;
    bool mIsInitialized;
};
static_assert(sizeof(ParamDefineTable) == 0x48, "xlink2::ParamDefineTable size mismatch");

}  // namespace xlink2