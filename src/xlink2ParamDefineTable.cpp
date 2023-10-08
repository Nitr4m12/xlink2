#include "xlink2/xlink2ParamDefineTable.h"

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
    mNumUserAssetParam = 0;
    mSize = 0;
    mInitialized = false;
}

void ParamDefineTable::setup(unsigned char* bin, u32 non_user_param_num, bool /*unused*/) {

    if (!mInitialized) {
        mSize = *(u32*)bin;
        u32 num_user_param = *(u32*)(&bin[4]);
        mNumUserParam = num_user_param;
        mNumStandardAssetParam = num_user_param - non_user_param_num;
        mNumNonUserParam = non_user_param_num;
        mNumAssetParam = *(u32*)(&bin[8]);
        _0 = *(u32*)(&bin[0xC]);
        mNumUserAssetParam = mNumAssetParam - _0;
        mNumTriggerParam = *(u32*)(&bin[0x10]);


        auto* user_params = (ResParam*)(&bin[0x14]);
        ResParam* asset_params = &user_params[*(u32*)(&bin[4])];
        ResParam* trigger_params = &asset_params[*(u32*)(&bin[8])];
        u32* stringTablePos = (u32*)trigger_params + *(u32*)(&bin[0x10]) * sizeof(ResParam);

        mStringTablePos = (long)stringTablePos;

        u64 num_asset_param = mNumAssetParam + (u64)mNumUserParam;

        if (mNumUserParam != 0) {
            mUserParams = user_params;
            for (u32 i {0}; i < mNumUserParam; ++i) {
                mUserParams[i].namePos = mStringTablePos + mUserParams[i].namePos;

                if (mUserParams[i].type == ParamValueType::String)
                    mUserParams[i].defaultValue = mStringTablePos + mUserParams[i].defaultValue;
            }
            num_asset_param >>= 0x20;
        }

        if (num_asset_param != 0) {
            mAssetParams = asset_params;
            for (u32 i {0}; i < num_asset_param; ++i) {
                mAssetParams[i].namePos = mAssetParams[i].namePos + mStringTablePos;

                if (mAssetParams[i].type == ParamValueType::String)
                    mAssetParams[i].defaultValue = mStringTablePos + mAssetParams[i].defaultValue;
            }
        }

        if (mNumTriggerParam != 0) {
            mTriggerParams = trigger_params;
            for (u32 i {0}; i < mNumTriggerParam; ++i) {
                mTriggerParams[i].namePos = mStringTablePos + mTriggerParams[i].namePos;

                if (mTriggerParams[i].type == ParamValueType::String)
                    mTriggerParams[i].defaultValue = mStringTablePos + mTriggerParams[i].defaultValue;
            }
        }
        mInitialized = true;
    }


}

void ParamDefineTable::dump_() {}

}