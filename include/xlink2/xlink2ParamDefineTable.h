#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
class ParamDefineTable {
public:
    void dump();

    f32 getAssetParamDefaultValueFloat(u32) const;
    s32 getAssetParamDefaultValueInt(u32) const;
    char* getAssetParamDefaultValueString(u32) const;
    char* getAssetParamName(u32) const;
    u32 getAssetParamType(u32) const;
    f32 getTriggerParamDefaultValueFloat(u32) const;
    s32 getTriggerParamDefaultValueInt(u32) const;
    char* getTriggerParamDefaultValueString(u32) const;
    char* getTriggerParamName(u32) const;
    u32 getTriggerParamType(u32) const;
    f32 getUserParamDefaultValueFloat(u32) const;
    s32 getUserParamDefaultValueInt(u32) const;
    char* getUserParamDefaultValueString(u32) const;
    char* getUserParamName(u32) const;
    u32 getUserParamType(u32) const;

    void reset();

    u64 searchAssetParamIdxFromCustomParamName(char const*) const;
    u64 searchUserParamIdxFromCustomParamName(char const*) const;

    void setup(u8*, u32, bool);
private:
};
}  // namespace xlink2