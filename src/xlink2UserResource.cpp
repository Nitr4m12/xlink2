#include <xlink2/xlink2UserResource.h>
#include "xlink2/xlink2.h"

namespace xlink2 {
u64 UserResource::getEditorSetupTime() const {
    return 0;
}
void UserResource::checkAndAddErrorMultipleKeyByTrigger(const ResAssetCallTable& /*unused*/,
                                                        TriggerType /*unused*/) {}
void UserResource::onSetupResourceParam_(UserResourceParam* /*unused*/,
                                         const ParamDefineTable* /*unused*/,
                                         sead::Heap* /*unused*/) {}

UserResource::~UserResource() = default;
UserResource::UserResource(User* user) {
    mUser = user;
    mResMode = (ResMode)0;
    mParams[0] = nullptr;
    mParams[1] = nullptr;
}

void UserResource::freeResourceParam_(UserResourceParam* param) {
    if (param->nameTable != nullptr) {
        delete[] param->nameTable;
        param->nameTable = nullptr;
        param->nameTableNum = 0;
    }

    if (param->_1 != nullptr) {
        delete[] param->_1;
        param->_1 = nullptr;
        param->_0 = 0;
    }

    if (param->_3 != nullptr) {
        delete[] param->_3;
        param->_3 = nullptr;
        param->_2 = 0;
    }
}

// NON_MATCHING: one sub instruction reordered
void* UserResource::getActionTriggerTableItem(s32 index) const {
    auto* param = mParams[int(mResMode)];

    if (!param || !param->isSetup || index >= param->resUserHeader->numResActionTrigger || index < 0)
        return nullptr;
    return &param->directValueTable[index * sizeof(Dummy)];
}

// NON_MATCHING: one sub instruction reordered
void* UserResource::getAlwaysTriggerTableItem(s32 index) const {
    auto* param = mParams[int(mResMode)];

    if (!param || !param->isSetup || index >= param->resUserHeader->numResAlwaysTrigger || index < 0)
        return nullptr;
    return &param->curvePointTable[index * sizeof(Dummy2)];
}

// NON_MATCHING: one sub instruction reordered
void* UserResource::getAssetCallTableItem(s32 index) const {
    auto* param = mParams[int(mResMode)];

    if (!param || !param->isSetup || index >= param->resUserHeader->numCallTable || index < 0)
        return nullptr;
    return &param->resAssetCallTable[index * sizeof(Dummy3)];
}

ResUserHeader* UserResource::getUserHeader() const {
    auto* param = mParams[int(mResMode)];

    if (!param || !param->isSetup)
        return nullptr;
    return param->resUserHeader;
}

void UserResource::destroy() {
    if (mParams[0] != nullptr)
        this->freeResourceParam_(mParams[0]);

    if (mParams[1] != nullptr)
        this->freeResourceParam_(mParams[1]);

}

// TODO
u32* UserResource::doBinarySearchAsset_(const char * name, TriggerType type) const {
    auto* param = mParams[int(mResMode)];
    u32 num_asset = param->resUserHeader->numCallTable;

    if (!param || !param->isSetup || num_asset == 0 || num_asset < 0)
        return nullptr;

    s32 v1 = 0;
    s64 v2 = param->numCurvePointTable;
    ResAssetCallTable* res_param_table = param->resAssetCallTable;

    while (v1 <= num_asset - 1) {
        s32 v3 = v1 + (num_asset - 1);
        if (v3 < 0)
            ++v3;
        v3 >>= 1;
        u32* asset = &num_asset + (v2 + v3 * 2) * sizeof(Dummy3);
        if (asset == nullptr)
            return nullptr;

        char* asset_name = (char*)(sMinAddressHigh | *asset);
        if (*asset < sMinAddressLow)
            asset_name += 0x100000000;

        if (strcmp(name, asset_name) == 0)
            return asset;

        s32 v4 = v3 - 1;
        if (strcmp(name, asset_name) > 0) {
            v1 = v3 + 1;
            v4 = num_asset - 1;
        }
    }
}

bool UserResource::hasGlobalPropertyTrigger() const {
    auto* param {mParams[int(mResMode)]};

    if (!param || !param->isSetup || param->resUserHeader->numResProperty == 0)
        return false;

    ResRandomCallTable* random_table {param->randomCallTable};
    u32 max_val {random_table->maxValue};
    for (int i {0};i<param->resUserHeader->numResProperty;++i) {
        if (max_val != 0)
            return true;

        max_val += 16;
    }
    return false;
}

}  // namespace xlink2