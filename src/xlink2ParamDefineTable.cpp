#include <cstring>

#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
void ParamDefineTable::reset() {
    // MATCHING
    mNumUserParam = 0;
    mNumAssetParam = 0;
    mNumTriggerParam = 0;
    mUserParams = nullptr;
    mTriggerParams = nullptr;
    mAssetParams = nullptr;
    mStringTablePos = 0;
    _0 = 0;
    mNumCustomParam = 0;
    mSize = 0;
    mIsInitialized = false;
}

void ParamDefineTable::setup(unsigned char* bin, u32 non_user_param_num, bool /*unused*/) {
    if (!mIsInitialized) {
        mSize = *(u32*)bin;
    }
}

void ParamDefineTable::dump_() {}

const char* ParamDefineTable::getUserParamName(u32 idx) const {
    if (mUserParams)
        return solveOffset<char>(mUserParams[idx].namePos);
    return nullptr;
}

const char* ParamDefineTable::getAssetParamName(u32 idx) const {
    if (idx < mNumAssetParam)
        return solveOffset<char>(mAssetParams[idx].namePos);
    return nullptr;
}

const char* ParamDefineTable::getTriggerParamName(u32 idx) const {
    if (mTriggerParams)
        return solveOffset<char>(mTriggerParams[idx].namePos);
    return nullptr;
}

u32 ParamDefineTable::searchAssetParamIdxFromCustomParamName(char const* custom_param_name) const {
    if (custom_param_name) {
        u32 asset_param_idx = mNumCustomParam;
        if (asset_param_idx < mNumAssetParam) {
            while (true) {
                char* asset_param_name = solveOffset<char>(mAssetParams[asset_param_idx].namePos);
                if (asset_param_name && std::strcmp(custom_param_name, asset_param_name) == 0)
                    break;
                u32 next_idx = asset_param_idx + 1;
                if (next_idx >= mNumAssetParam)
                    return -1;
                asset_param_idx = next_idx;
            }
            return asset_param_idx;
        }
    }
    return -1;
}

// NON-MATCHING / WIP
u32 ParamDefineTable::searchUserParamIdxFromCustomParamName(const char* custom_param_name) const {
    if (custom_param_name) {
        u32 user_param_idx = mNumNonUserParam;
        if (user_param_idx <= mNumUserParam && mNumUserParam - mNumNonUserParam > 0) {
            if (mUserParams) {
                while (true) {
                    char* user_param_name = solveOffset<char>(mUserParams[user_param_idx].namePos);
                    if (user_param_name && std::strcmp(custom_param_name, user_param_name) == 0)
                        break;
                    u32 next_idx = user_param_idx + 1;
                    if (next_idx >= mNumUserParam)
                        return -1;
                    user_param_idx = next_idx;
                }
            }
            return user_param_idx;
        }
        u32 i = 0;
        if (6 < (mNumUserParam - 1) - mNumNonUserParam) {
            i = mNumUserParam - mNumNonUserParam & 7;
            for (;i < 0; i += 8) {}
        }
        if (i != 0) {
            i = -i;
            for (;i < 0; ++i) {}
        }

    }
    return -1;
}

ParamValueType ParamDefineTable::getUserParamType(u32 user_param_idx) const {
    if (mUserParams)
        return mUserParams[user_param_idx].type;
    return ParamValueType::Invalid;
}

ParamValueType ParamDefineTable::getAssetParamType(u32 asset_param_idx) const {
    if (asset_param_idx < mNumAssetParam)
        return mAssetParams[asset_param_idx].type;
    return ParamValueType::Invalid;
}

ParamValueType ParamDefineTable::getTriggerParamType(u32 trigger_param_idx) const {
    if (mTriggerParams)
        return mTriggerParams[trigger_param_idx].type;
    return ParamValueType::Invalid;
}

u32 ParamDefineTable::getUserParamDefaultValueInt(u32 user_param_idx) const {
    if (mUserParams)
        return mUserParams[user_param_idx].defaultValueInt;
    return 0;
}

f32 ParamDefineTable::getUserParamDefaultValueFloat(u32 user_param_idx) const {
    if (mUserParams)
        return mUserParams[user_param_idx].defaultValueFloat;
    return 0;
}

const char* ParamDefineTable::getUserParamDefaultValueString(u32 user_param_idx) const {
    if (mUserParams)
        return solveOffset<char>(mUserParams[user_param_idx].defaultValueString);
    return "";
}

u32 ParamDefineTable::getAssetParamDefaultValueInt(u32 asset_param_idx) const {
    if (asset_param_idx < mNumAssetParam)
        return mAssetParams[asset_param_idx].defaultValueInt;
    return 0;
}

f32 ParamDefineTable::getAssetParamDefaultValueFloat(u32 asset_param_idx) const {
    if (asset_param_idx < mNumAssetParam)
        return mAssetParams[asset_param_idx].defaultValueFloat;
    return 0;
}

const char* ParamDefineTable::getAssetParamDefaultValueString(u32 asset_param_idx) const {
    if (asset_param_idx < mNumAssetParam)
        return solveOffset<char>(mAssetParams[asset_param_idx].defaultValueString);
    return "";
}

u32 ParamDefineTable::getTriggerParamDefaultValueInt(u32 trigger_param_idx) const {
    if (mTriggerParams)
        return mTriggerParams[trigger_param_idx].defaultValueInt;
    return 0;
}

f32 ParamDefineTable::getTriggerParamDefaultValueFloat(u32 trigger_param_idx) const {
    if (mTriggerParams)
        return mTriggerParams[trigger_param_idx].defaultValueFloat;
    return 0;
}

const char* ParamDefineTable::getTriggerParamDefaultValueString(u32 trigger_param_idx) const {
    if (mTriggerParams)
        return solveOffset<char>(mTriggerParams[trigger_param_idx].defaultValueString);
    return nullptr;
}

}  // namespace xlink2