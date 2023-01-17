#include <xlink2/xlink2UserResource.h>

namespace xlink2 {
UserResource::~UserResource() = default;
UserResource::UserResource(User* user) {
    mUser = user;
    mResMode = (ResMode)0;
    mUserResourceParam = nullptr;
    _1 = nullptr;
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

// TODO
void* UserResource::getActionTriggerTableItem(s32 index) const {
    UserResourceParam*const* param_ptr_ptr;
    UserResourceParam* param_ptr;

    // Adding an enum to a the address of a pointer? Maybe navigating through the class
    param_ptr_ptr = &mUserResourceParam + (int)mResMode;
    if (2 > (u32)mResMode) {
        param_ptr_ptr = &mUserResourceParam;
    }
    param_ptr = *param_ptr_ptr;
    if (param_ptr != nullptr) {
        if (param_ptr->_7 != 0) {
            if (-1 < index)
                if (param_ptr->resUserHeader->numResActionTrigger <= index)
                    return nullptr;
            return param_ptr->directValueTable + index*0x18;
        }
    }
    return nullptr;
}

// TODO
void* UserResource::getAlwaysTriggerTableItem(s32 index) const {
    UserResourceParam*const* param_ptr_ptr;
    UserResourceParam* param_ptr;

    param_ptr_ptr = &mUserResourceParam + (int)mResMode;
    if (2 > (u32)mResMode) {
        param_ptr_ptr = &mUserResourceParam;
    }
    param_ptr = *param_ptr_ptr;
    if (param_ptr != nullptr) {
        if (param_ptr->_7 != 0) {
            if (-1 < index)
                if (param_ptr->resUserHeader->numResAlwaysTrigger <= index)
                    return nullptr;
            return param_ptr->curvePointTable + index*0x10;
        }
    }
    return nullptr;
}

// TODO
void* UserResource::getAssetCallTableItem(s32 index) const {
    UserResourceParam*const* param_ptr_ptr;
    UserResourceParam* param_ptr;

    param_ptr_ptr = &mUserResourceParam + (int)mResMode;
    if (2 > (u32)mResMode) {
        param_ptr_ptr = &mUserResourceParam;
    }
    param_ptr = *param_ptr_ptr;
    if (param_ptr != nullptr) {
        if (param_ptr->_7 != 0) {
            if (-1 < index)
                if (param_ptr->resUserHeader->numCallTable <= (long)index)
                    return nullptr;
            return param_ptr->resAssetParamTable + index*0x20;
        }
    }
    return nullptr;
}

// TODO
ResUserHeader* UserResource::getUserHeader() const {
    UserResourceParam*const* param_ptr_ptr;
    UserResourceParam* param_ptr;

    param_ptr_ptr = ResMode::Editor > mResMode ? &mUserResourceParam : &mUserResourceParam + (s32)mResMode;
    param_ptr = *param_ptr_ptr;
    if (param_ptr != nullptr) {
        if (param_ptr->_7 != 0) {
            return param_ptr->resUserHeader;
        }
    }
    return nullptr;
}

void UserResource::checkAndAddErrorMultipleKeyByTrigger(const ResAssetCallTable&, TriggerType) {}
void UserResource::onSetupResourceParam_(UserResourceParam*, const ParamDefineTable*, sead::Heap*) {
}
}  // namespace xlink2