#include <cstring>

#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
void ParamDefineTable::reset() 
{
    mNumUserParam = 0;
    mNumAssetParam = 0;
    mNumTriggerParam = 0;
    mDefaultUserParams = nullptr;
    mDefaultTriggerParams = nullptr;
    mDefaultAssetParams = nullptr;
    mStringTablePos = 0;
    _0 = 0;
    mNumCustomParam = 0;
    mSize = 0;
    mIsInitialized = false;
}

void ParamDefineTable::setup(unsigned char* bin, u32 num_non_user_param, bool /*unused*/) 
{
    if (!mIsInitialized) {
        mSize = *(u32*)bin;
        u32 num_user_param = *(u32*)(&bin[4]);
        mNumUserParam = num_user_param;
        mNumStandardAssetParam = num_user_param - num_non_user_param;
        mNumCustomUserParam = num_non_user_param;
        mNumAssetParam = *(u32*)(&bin[8]);
        _0 = *(u32*)(&bin[0xC]);
        mNumCustomParam = mNumAssetParam - _0;
        mNumTriggerParam = *(u32*)(&bin[0x10]);


        auto* user_params = (ResParamDefine*)(&bin[0x14]);
        ResParamDefine* asset_params = &user_params[*(u32*)(&bin[4])];
        ResParamDefine* trigger_params = &asset_params[*(u32*)(&bin[8])];
        u64 string_table_pos = (long)(trigger_params + *(u32*)(&bin[0x10]));

        mStringTablePos = string_table_pos;

        if (mNumUserParam != 0) {
            mDefaultUserParams = user_params;
            for (u32 i {0}; i < mNumUserParam; ++i) {
                mDefaultUserParams[i].namePos = mStringTablePos + mDefaultUserParams[i].namePos;

                if (mDefaultUserParams[i].type == ParamValueType::String)
                    mDefaultUserParams[i].defaultValueString = mStringTablePos + mDefaultUserParams[i].defaultValueString;
            }
        }

        if (mNumAssetParam != 0) {
            mDefaultAssetParams = asset_params;
            for (u32 i {0}; i < mNumAssetParam; ++i) {
                mDefaultAssetParams[i].namePos = mStringTablePos + mDefaultAssetParams[i].namePos;

                if (mDefaultAssetParams[i].type == ParamValueType::String)
                    mDefaultAssetParams[i].defaultValueString = mStringTablePos + mDefaultAssetParams[i].defaultValueString;
            }
        }

        if (mNumTriggerParam != 0) {
            mDefaultTriggerParams = trigger_params;
            for (u32 i {0}; i < mNumTriggerParam; ++i) {
                mDefaultTriggerParams[i].namePos = mStringTablePos + mDefaultTriggerParams[i].namePos;

                if (mDefaultTriggerParams[i].type == ParamValueType::String)
                    mDefaultTriggerParams[i].defaultValueString = mStringTablePos + mDefaultTriggerParams[i].defaultValueString;
            }
        }
        mIsInitialized = true;
    }
}

void ParamDefineTable::dump_() {}

const char* ParamDefineTable::getUserParamName(u32 idx) const 
{
    if (mDefaultUserParams)
        return calcOffset<char>(mDefaultUserParams[idx].namePos);
    return nullptr;
}

const char* ParamDefineTable::getAssetParamName(u32 idx) const 
{
    if (idx < mNumAssetParam)
        return calcOffset<char>(mDefaultAssetParams[idx].namePos);
    return nullptr;
}

const char* ParamDefineTable::getTriggerParamName(u32 idx) const 
{
    if (mDefaultTriggerParams)
        return calcOffset<char>(mDefaultTriggerParams[idx].namePos);
    return nullptr;
}

s32 ParamDefineTable::searchAssetParamIdxFromCustomParamName(const char* custom_param_name) const 
{
    if (custom_param_name) {
        u32 asset_param_idx = mNumCustomParam;
        if (asset_param_idx < mNumAssetParam) {
            while (true) {
                char* asset_param_name = calcOffset<char>(mDefaultAssetParams[asset_param_idx].namePos);
                if (asset_param_name && std::strcmp(custom_param_name, asset_param_name) == 0)
                    return asset_param_idx;
                if (asset_param_idx + 1 >= mNumAssetParam)
                    return -1;
                ++asset_param_idx;
            }
        }
    }
    return -1;
}

// NON-MATCHING / WIP
s32 ParamDefineTable::searchUserParamIdxFromCustomParamName(const char* custom_param_name) const 
{
    if (custom_param_name != nullptr) {
        u32 user_param_idx = mNumCustomUserParam;
        if (user_param_idx < mNumUserParam && mNumUserParam - mNumCustomUserParam > 0) {
            if (mDefaultUserParams != nullptr) {
                while (true) {
                    char* user_param_name = calcOffset<char>(mDefaultUserParams[user_param_idx].namePos);
                    if (user_param_name && std::strcmp(custom_param_name, user_param_name) == 0)
                        break;
                    if (user_param_idx + 1 >= mNumUserParam)
                        return -1;
                    ++user_param_idx;
                }
                return user_param_idx;
            }
        }
    }
    return -1;
}

ParamValueType ParamDefineTable::getUserParamType(u32 id) const 
{
    if (mDefaultUserParams)
        return mDefaultUserParams[id].type;
    return ParamValueType::Invalid;
}

ParamValueType ParamDefineTable::getAssetParamType(u32 id) const 
{
    if (id < mNumAssetParam)
        return mDefaultAssetParams[id].type;
    return ParamValueType::Invalid;
}

ParamValueType ParamDefineTable::getTriggerParamType(u32 id) const 
{
    if (mDefaultTriggerParams)
        return mDefaultTriggerParams[id].type;
    return ParamValueType::Invalid;
}

s32 ParamDefineTable::getUserParamDefaultValueInt(u32 id) const 
{
    if (mDefaultUserParams)
        return mDefaultUserParams[id].defaultValueInt;
    return 0;
}

f32 ParamDefineTable::getUserParamDefaultValueFloat(u32 id) const 
{
    if (mDefaultUserParams)
        return mDefaultUserParams[id].defaultValueFloat;
    return 0;
}

const char* ParamDefineTable::getUserParamDefaultValueString(u32 id) const 
{
    if (mDefaultUserParams)
        return calcOffset<char>(mDefaultUserParams[id].defaultValueString);
    return "";
}

s32 ParamDefineTable::getAssetParamDefaultValueInt(u32 id) const 
{
    if (id < mNumAssetParam)
        return mDefaultAssetParams[id].defaultValueInt;
    return 0;
}

f32 ParamDefineTable::getAssetParamDefaultValueFloat(u32 id) const 
{
    if (id < mNumAssetParam)
        return mDefaultAssetParams[id].defaultValueFloat;
    return 0;
}

const char* ParamDefineTable::getAssetParamDefaultValueString(u32 id) const 
{
    if (id < mNumAssetParam)
        return calcOffset<char>(mDefaultAssetParams[id].defaultValueString);
    return "";
}

s32 ParamDefineTable::getTriggerParamDefaultValueInt(u32 id) const 
{
    if (mDefaultTriggerParams)
        return mDefaultTriggerParams[id].defaultValueInt;
    return 0;
}

f32 ParamDefineTable::getTriggerParamDefaultValueFloat(u32 id) const 
{
    if (mDefaultTriggerParams)
        return mDefaultTriggerParams[id].defaultValueFloat;
    return 0;
}

const char* ParamDefineTable::getTriggerParamDefaultValueString(u32 id) const 
{
    if (mDefaultTriggerParams)
        return calcOffset<char>(mDefaultTriggerParams[id].defaultValueString);
    return nullptr;
}

}  // namespace xlink2