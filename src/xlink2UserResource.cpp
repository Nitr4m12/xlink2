#include <xlink2/xlink2UserResource.h>

namespace xlink2 {
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

    if (!param || !param->setup || index >= param->resUserHeader->numResActionTrigger || index < 0)
        return nullptr;
    return &param->directValueTable[index * sizeof(Dummy)];
}

// NON_MATCHING: one sub instruction reordered
void* UserResource::getAlwaysTriggerTableItem(s32 index) const {
    auto* param = mParams[int(mResMode)];

    if (!param || !param->setup || index >= param->resUserHeader->numResAlwaysTrigger || index < 0)
        return nullptr;
    return &param->curvePointTable[index * sizeof(Dummy2)];
}

// NON_MATCHING: one sub instruction reordered
void* UserResource::getAssetCallTableItem(s32 index) const {
    auto* param = mParams[int(mResMode)];

    if (!param || !param->setup || index >= param->resUserHeader->numCallTable || index < 0)
        return nullptr;
    return &param->resAssetParamTable[index * sizeof(Dummy3)];
}

// // TODO
ResUserHeader* UserResource::getUserHeader() const {
    auto* param = mParams[int(mResMode)];

    if (!param || !param->setup)
        return nullptr;
    return param->resUserHeader;
}

u64 UserResource::getEditorSetupTime() const {
    return 0;
}
void UserResource::checkAndAddErrorMultipleKeyByTrigger(const ResAssetCallTable&, TriggerType) {}
void UserResource::onSetupResourceParam_(UserResourceParam*, const ParamDefineTable*, sead::Heap*) {
}
}  // namespace xlink2