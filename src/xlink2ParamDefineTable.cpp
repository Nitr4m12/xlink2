#include <cstring>

#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2Resource.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
void ParamDefineTable::reset() 
{
    mNumUserParam = 0;
    mNumAssetParam = 0;
    mNumTriggerParam = 0;
    mpUserParamDefine = nullptr;
    mpTriggerParamDefine = nullptr;
    mpAssetParamDefine = nullptr;
    mStringTablePos = 0;
    mNumCustomAssetParam = 0;
    mNumStandardAssetParam = 0;
    mDataSize = 0;
    mIsInitialized = false;
}

void ParamDefineTable::setup(unsigned char* bin, u32 num_non_user_param, bool /*unused*/) 
{
    if (!mIsInitialized) {
        auto* header {reinterpret_cast<ResParamDefineTableHeader*>(bin)};

        mDataSize = header->size;
        u32 num_user_param = header->numUserParam;
        mNumUserParam = num_user_param;
        mNumStandardUserParam = num_user_param - num_non_user_param;
        mNumCustomUserParam = num_non_user_param;
        mNumAssetParam = header->numAssetParam;
        mNumCustomAssetParam = header->numCustomAssetParam;
        mNumStandardAssetParam = mNumAssetParam - mNumCustomAssetParam;
        mNumTriggerParam = header->numTriggerParam;

        auto* user_params = (ResParamDefine*)(&header->numTriggerParam + 1);
        ResParamDefine* asset_params = &user_params[header->numUserParam];
        ResParamDefine* trigger_params = &asset_params[header->numAssetParam];
        u64 string_table_pos = (long)(&trigger_params[header->numTriggerParam]);

        mStringTablePos = string_table_pos;

        if (mNumUserParam != 0) {
            mpUserParamDefine = user_params;
            for (u32 i {0}; i < mNumUserParam; ++i) {
                mpUserParamDefine[i].namePos = mStringTablePos + mpUserParamDefine[i].namePos;

                if (mpUserParamDefine[i].type == ParamValueType::String)
                    mpUserParamDefine[i].defaultValueString = mStringTablePos + mpUserParamDefine[i].defaultValueString;
            }
        }

        if (mNumAssetParam != 0) {
            mpAssetParamDefine = asset_params;
            for (u32 i {0}; i < mNumAssetParam; ++i) {
                mpAssetParamDefine[i].namePos = mStringTablePos + mpAssetParamDefine[i].namePos;

                if (mpAssetParamDefine[i].type == ParamValueType::String)
                    mpAssetParamDefine[i].defaultValueString = mStringTablePos + mpAssetParamDefine[i].defaultValueString;
            }
        }

        if (mNumTriggerParam != 0) {
            mpTriggerParamDefine = trigger_params;
            for (u32 i {0}; i < mNumTriggerParam; ++i) {
                mpTriggerParamDefine[i].namePos = mStringTablePos + mpTriggerParamDefine[i].namePos;

                if (mpTriggerParamDefine[i].type == ParamValueType::String)
                    mpTriggerParamDefine[i].defaultValueString = mStringTablePos + mpTriggerParamDefine[i].defaultValueString;
            }
        }
        mIsInitialized = true;
    }
}

void ParamDefineTable::dump_() {}

const char* ParamDefineTable::getUserParamName(u32 idx) const 
{
    if (mpUserParamDefine)
        return calcOffset<char>(mpUserParamDefine[idx].namePos);
    return nullptr;
}

const char* ParamDefineTable::getAssetParamName(u32 idx) const 
{
    if (idx < mNumAssetParam)
        return calcOffset<char>(mpAssetParamDefine[idx].namePos);
    return nullptr;
}

const char* ParamDefineTable::getTriggerParamName(u32 idx) const 
{
    if (mpTriggerParamDefine)
        return calcOffset<char>(mpTriggerParamDefine[idx].namePos);
    return nullptr;
}

s32 ParamDefineTable::searchAssetParamIdxFromCustomParamName(const char* custom_param_name) const 
{
    if (custom_param_name != nullptr) {
        for (u32 asset_param_idx {mNumStandardAssetParam}; asset_param_idx < mNumAssetParam; ++asset_param_idx) {
            char* asset_param_name = calcOffset<char>(mpAssetParamDefine[asset_param_idx].namePos);
            if (asset_param_name && std::strcmp(custom_param_name, asset_param_name) == 0)
                return asset_param_idx;
        }
    }
    return -1;
}

// NON-MATCHING / WIP
s32 ParamDefineTable::searchUserParamIdxFromCustomParamName(const char* custom_param_name) const 
{
    if (custom_param_name != nullptr) {
        for (u32 user_param_idx {mNumCustomUserParam}; user_param_idx < mNumUserParam; ++user_param_idx) {
            char* user_param_name = calcOffset<char>(mpUserParamDefine[user_param_idx].namePos);
            if (user_param_name && std::strcmp(custom_param_name, user_param_name) == 0)
                return user_param_idx;
        }
    }
    return -1;
}

ParamValueType ParamDefineTable::getUserParamType(u32 id) const 
{
    if (mpUserParamDefine)
        return mpUserParamDefine[id].type;
    return ParamValueType::Invalid;
}

ParamValueType ParamDefineTable::getAssetParamType(u32 id) const 
{
    if (id < mNumAssetParam)
        return mpAssetParamDefine[id].type;
    return ParamValueType::Invalid;
}

ParamValueType ParamDefineTable::getTriggerParamType(u32 id) const 
{
    if (mpTriggerParamDefine)
        return mpTriggerParamDefine[id].type;
    return ParamValueType::Invalid;
}

s32 ParamDefineTable::getUserParamDefaultValueInt(u32 id) const 
{
    if (mpUserParamDefine)
        return mpUserParamDefine[id].defaultValueInt;
    return 0;
}

f32 ParamDefineTable::getUserParamDefaultValueFloat(u32 id) const 
{
    if (mpUserParamDefine)
        return mpUserParamDefine[id].defaultValueFloat;
    return 0;
}

const char* ParamDefineTable::getUserParamDefaultValueString(u32 id) const 
{
    if (mpUserParamDefine)
        return calcOffset<char>(mpUserParamDefine[id].defaultValueString);
    return "";
}

s32 ParamDefineTable::getAssetParamDefaultValueInt(u32 id) const 
{
    if (id < mNumAssetParam)
        return mpAssetParamDefine[id].defaultValueInt;
    return 0;
}

f32 ParamDefineTable::getAssetParamDefaultValueFloat(u32 id) const 
{
    if (id < mNumAssetParam)
        return mpAssetParamDefine[id].defaultValueFloat;
    return 0;
}

const char* ParamDefineTable::getAssetParamDefaultValueString(u32 id) const 
{
    if (id < mNumAssetParam)
        return calcOffset<char>(mpAssetParamDefine[id].defaultValueString);
    return "";
}

s32 ParamDefineTable::getTriggerParamDefaultValueInt(u32 id) const 
{
    if (mpTriggerParamDefine)
        return mpTriggerParamDefine[id].defaultValueInt;
    return 0;
}

f32 ParamDefineTable::getTriggerParamDefaultValueFloat(u32 id) const 
{
    if (mpTriggerParamDefine)
        return mpTriggerParamDefine[id].defaultValueFloat;
    return 0;
}

const char* ParamDefineTable::getTriggerParamDefaultValueString(u32 id) const 
{
    if (mpTriggerParamDefine)
        return calcOffset<char>(mpTriggerParamDefine[id].defaultValueString);
    return nullptr;
}

}  // namespace xlink2